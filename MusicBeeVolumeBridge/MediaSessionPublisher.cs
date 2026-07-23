using System;
using System.Diagnostics;
using System.Drawing;
using System.Drawing.Drawing2D;
using System.Drawing.Imaging;
using System.IO;
using System.Runtime.InteropServices;
using System.Runtime.InteropServices.WindowsRuntime;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using Windows.Media;
using Windows.Storage;
using Windows.Storage.Streams;
using MetaDataType = MusicBeePlugin.Plugin.MetaDataType;
using MusicBeeApiInterface = MusicBeePlugin.Plugin.MusicBeeApiInterface;
using PictureLocations = MusicBeePlugin.Plugin.PictureLocations;
using PlayButtonType = MusicBeePlugin.Plugin.PlayButtonType;
using PlayState = MusicBeePlugin.Plugin.PlayState;
using RepeatMode = MusicBeePlugin.Plugin.RepeatMode;

namespace MusicBeePlugin
{
    internal sealed class MediaSessionPublisher : IDisposable
    {
        private const int ArtworkShutdownWaitMilliseconds = 3000;
        private const int MaximumArtworkSide = 1024;

        // MusicBeeApiInterface is a mutable value type whose API entry points
        // are delegate fields. Keeping it in an init-only field makes access to
        // those delegates unverifiable IL on .NET Framework (the compiler takes
        // the address of the readonly struct). The plugin runs at full trust,
        // but a normal field keeps the assembly verifiable and loader-friendly.
        private MusicBeeApiInterface _api;
        private readonly Func<Action, bool> _postToWorker;
        private readonly CancellationTokenSource _cancellation = new CancellationTokenSource();
        private readonly object _artworkTaskLock = new object();
        private SystemMediaTransportControls _controls;
        private Task _artworkTask;
        private IntPtr _windowHandle;
        private string _lastMetadataSignature = "";
        private string _lastArtworkTrack = "";
        private string _currentArtworkPath;
        private string _pendingArtworkPath;
        private int _artworkGeneration;
        private int _artworkRefreshInFlight;
        private volatile bool _disposed;

        public MediaSessionPublisher(
            MusicBeeApiInterface api,
            Func<Action, bool> postToWorker)
        {
            _api = api;
            _postToWorker = postToWorker ??
                throw new ArgumentNullException(nameof(postToWorker));
            CleanupStaleArtworkFiles();
        }

        public bool HasMetadata { get; private set; }
        public bool HasArtwork { get; private set; }
        public bool ArtworkRefreshDeferred { get; private set; }

        public bool EnsureStarted(IntPtr musicBeeWindow)
        {
            if (_disposed)
                return false;
            if (_controls != null && musicBeeWindow == _windowHandle)
                return true;
            if (musicBeeWindow == IntPtr.Zero)
                return false;

            if (_controls != null)
                ReleaseControls(false);

            // A recreated MusicBee window gets a different SMTC instance. Force
            // all state to be republished even when the same track is playing.
            Interlocked.Increment(ref _artworkGeneration);
            _lastMetadataSignature = "";
            _lastArtworkTrack = "";
            HasMetadata = false;
            HasArtwork = false;

            try
            {
                object factory = WindowsRuntimeMarshal.GetActivationFactory(
                    typeof(SystemMediaTransportControls));
                var interop = (ISystemMediaTransportControlsInterop)factory;
                // IID of Windows.Media.ISystemMediaTransportControls from the
                // Windows SDK. Type.GUID is the projected runtime-class GUID,
                // not the interface IID required by GetForWindow.
                Guid iid = new Guid("99fa3ff4-1742-42a6-902e-087d41f965ec");
                IntPtr controlsPointer;
                int result = interop.GetForWindow(musicBeeWindow, ref iid, out controlsPointer);
                Marshal.ThrowExceptionForHR(result);
                try
                {
                    _controls = (SystemMediaTransportControls)
                        Marshal.GetObjectForIUnknown(controlsPointer);
                }
                finally
                {
                    if (controlsPointer != IntPtr.Zero)
                        Marshal.Release(controlsPointer);
                }

                _windowHandle = musicBeeWindow;

                ConfigureControls();
                return true;
            }
            catch
            {
                ReleaseControls(false);
                return false;
            }
        }

        public void Invalidate()
        {
            if (_disposed)
                return;
            ReleaseControls(false);
            Interlocked.Increment(ref _artworkGeneration);
            _lastMetadataSignature = "";
            _lastArtworkTrack = "";
            HasMetadata = false;
            HasArtwork = false;
        }

        public void SetChanging()
        {
            if (_controls == null || _disposed)
                return;
            try { _controls.PlaybackStatus = MediaPlaybackStatus.Changing; } catch { }
        }

        public bool RefreshMetadata(bool refreshArtwork)
        {
            if (_controls == null || _disposed)
                return false;

            string trackUrl = SafeGet(() => _api.NowPlaying_GetFileUrl());
            string title = SafeGet(() => _api.NowPlaying_GetFileTag(MetaDataType.TrackTitle));
            string artist = SafeGet(() => _api.NowPlaying_GetFileTag(MetaDataType.Artist));
            string album = SafeGet(() => _api.NowPlaying_GetFileTag(MetaDataType.Album));
            string albumArtist = SafeGet(() => _api.NowPlaying_GetFileTag(MetaDataType.AlbumArtist));

            title = NormaliseText(title);
            artist = NormaliseText(artist);
            album = NormaliseText(album);
            albumArtist = NormaliseText(albumArtist);
            trackUrl = NormaliseText(trackUrl);

            if (title.Length == 0)
                title = TitleFromLocation(trackUrl);

            // Never publish the shell's synthetic "Untitled" fallback. When
            // MusicBee is still restoring its library/session, keep retrying.
            if (title.Length == 0)
            {
                if (!HasMetadata)
                    _controls.IsEnabled = false;
                return false;
            }

            string signature = string.Join("\u001f", trackUrl, title, artist, album, albumArtist);
            bool metadataChanged =
                !HasMetadata ||
                !string.Equals(signature, _lastMetadataSignature, StringComparison.Ordinal);
            if (metadataChanged)
            {
                var updater = _controls.DisplayUpdater;
                updater.Type = MediaPlaybackType.Music;
                updater.MusicProperties.Title = title;
                updater.MusicProperties.Artist = artist;
                updater.MusicProperties.AlbumTitle = album;
                updater.MusicProperties.AlbumArtist = albumArtist;
                // Publish a new track without the previous track's thumbnail.
                // Otherwise consumers can briefly pair the new title with the
                // old cover and cache that incorrect combination.
                if (refreshArtwork)
                {
                    updater.Thumbnail = null;
                    DeleteFileBestEffort(_currentArtworkPath);
                    _currentArtworkPath = null;
                    HasArtwork = false;
                }
                updater.Update();

                _lastMetadataSignature = signature;
                HasMetadata = true;
                _controls.IsEnabled = true;
            }

            bool artworkTrackChanged =
                !string.Equals(_lastArtworkTrack, trackUrl, StringComparison.Ordinal);
            if (refreshArtwork || artworkTrackChanged)
            {
                _lastArtworkTrack = trackUrl;
                RefreshArtwork(trackUrl, artworkTrackChanged);
            }

            return true;
        }

        public void RefreshPlaybackAndTimeline()
        {
            if (_controls == null || _disposed)
                return;

            PlayState state = _api.Player_GetPlayState();
            switch (state)
            {
                case PlayState.Playing:
                    _controls.PlaybackStatus = MediaPlaybackStatus.Playing;
                    break;
                case PlayState.Paused:
                    _controls.PlaybackStatus = MediaPlaybackStatus.Paused;
                    break;
                case PlayState.Loading:
                    _controls.PlaybackStatus = MediaPlaybackStatus.Changing;
                    break;
                case PlayState.Stopped:
                    _controls.PlaybackStatus = MediaPlaybackStatus.Stopped;
                    break;
                default:
                    _controls.PlaybackStatus = MediaPlaybackStatus.Closed;
                    break;
            }

            bool previous = SafeGet(() => _api.Player_GetButtonEnabled(PlayButtonType.PreviousTrack), true);
            bool playPause = SafeGet(() => _api.Player_GetButtonEnabled(PlayButtonType.PlayPause), true);
            bool next = SafeGet(() => _api.Player_GetButtonEnabled(PlayButtonType.NextTrack), true);
            _controls.IsPreviousEnabled = previous;
            _controls.IsPlayEnabled = playPause;
            _controls.IsPauseEnabled = playPause;
            _controls.IsNextEnabled = next;
            _controls.IsStopEnabled = false;

            int durationMilliseconds = Math.Max(0, _api.NowPlaying_GetDuration());
            int positionMilliseconds = Math.Max(0, _api.Player_GetPosition());
            if (durationMilliseconds > 0)
                positionMilliseconds = Math.Min(positionMilliseconds, durationMilliseconds);

            if (durationMilliseconds > 0)
            {
                var timeline = new SystemMediaTransportControlsTimelineProperties
                {
                    StartTime = TimeSpan.Zero,
                    MinSeekTime = TimeSpan.Zero,
                    Position = TimeSpan.FromMilliseconds(positionMilliseconds),
                    MaxSeekTime = TimeSpan.FromMilliseconds(durationMilliseconds),
                    EndTime = TimeSpan.FromMilliseconds(durationMilliseconds),
                };
                _controls.UpdateTimelineProperties(timeline);
            }
            else
            {
                // Clear a previous finite track's timeline for live streams or
                // files whose duration is not available yet.
                var emptyTimeline = new SystemMediaTransportControlsTimelineProperties
                {
                    StartTime = TimeSpan.Zero,
                    MinSeekTime = TimeSpan.Zero,
                    Position = TimeSpan.Zero,
                    MaxSeekTime = TimeSpan.Zero,
                    EndTime = TimeSpan.Zero,
                };
                _controls.UpdateTimelineProperties(emptyTimeline);
            }

            _controls.ShuffleEnabled = _api.Player_GetShuffle();
            switch (_api.Player_GetRepeat())
            {
                case RepeatMode.One:
                    _controls.AutoRepeatMode = MediaPlaybackAutoRepeatMode.Track;
                    break;
                case RepeatMode.All:
                    _controls.AutoRepeatMode = MediaPlaybackAutoRepeatMode.List;
                    break;
                default:
                    _controls.AutoRepeatMode = MediaPlaybackAutoRepeatMode.None;
                    break;
            }
        }

        public void Dispose()
        {
            if (_disposed)
                return;
            _disposed = true;
            _cancellation.Cancel();

            Task artworkTask;
            lock (_artworkTaskLock)
                artworkTask = _artworkTask;

            bool artworkTaskFinished = artworkTask == null || artworkTask.IsCompleted;
            if (!artworkTaskFinished)
            {
                try
                {
                    artworkTaskFinished =
                        artworkTask.Wait(ArtworkShutdownWaitMilliseconds);
                }
                catch (AggregateException)
                {
                    artworkTaskFinished = true;
                }
                catch (ObjectDisposedException)
                {
                    artworkTaskFinished = true;
                }
            }

            DeleteFileBestEffort(TakePendingArtworkPath());
            ReleaseControls(true);
            Interlocked.Exchange(ref _artworkRefreshInFlight, 0);

            DeleteFileBestEffort(_currentArtworkPath);
            _currentArtworkPath = null;
            if (artworkTaskFinished)
            {
                _cancellation.Dispose();
            }
            else
            {
                artworkTask.ContinueWith(
                    ignored =>
                    {
                        DeleteFileBestEffort(TakePendingArtworkPath());
                        try { _cancellation.Dispose(); } catch { }
                    },
                    CancellationToken.None,
                    TaskContinuationOptions.ExecuteSynchronously,
                    TaskScheduler.Default);
            }
        }

        private void ConfigureControls()
        {
            _controls.IsEnabled = false;
            _controls.IsPlayEnabled = true;
            _controls.IsPauseEnabled = true;
            _controls.IsPreviousEnabled = true;
            _controls.IsNextEnabled = true;
            _controls.IsStopEnabled = false;
            _controls.IsFastForwardEnabled = false;
            _controls.IsRewindEnabled = false;

            _controls.ButtonPressed += ControlsOnButtonPressed;
            _controls.PlaybackPositionChangeRequested += ControlsOnPlaybackPositionChangeRequested;
            _controls.ShuffleEnabledChangeRequested += ControlsOnShuffleEnabledChangeRequested;
            _controls.AutoRepeatModeChangeRequested += ControlsOnAutoRepeatModeChangeRequested;
        }

        private void ReleaseControls(bool clearDisplay)
        {
            SystemMediaTransportControls controls = _controls;
            _controls = null;
            _windowHandle = IntPtr.Zero;
            if (controls == null)
                return;

            try
            {
                controls.ButtonPressed -= ControlsOnButtonPressed;
                controls.PlaybackPositionChangeRequested -= ControlsOnPlaybackPositionChangeRequested;
                controls.ShuffleEnabledChangeRequested -= ControlsOnShuffleEnabledChangeRequested;
                controls.AutoRepeatModeChangeRequested -= ControlsOnAutoRepeatModeChangeRequested;
                controls.IsEnabled = false;
                if (clearDisplay)
                {
                    controls.DisplayUpdater.ClearAll();
                    controls.DisplayUpdater.Update();
                }
            }
            catch { }
        }

        private void ControlsOnButtonPressed(
            SystemMediaTransportControls sender,
            SystemMediaTransportControlsButtonPressedEventArgs args)
        {
            SystemMediaTransportControlsButton button = args.Button;
            _postToWorker(() =>
            {
                if (_disposed)
                    return;
                try
                {
                    switch (button)
                    {
                        case SystemMediaTransportControlsButton.Play:
                            if (_api.Player_GetPlayState() != PlayState.Playing)
                                _api.Player_PlayPause();
                            break;
                        case SystemMediaTransportControlsButton.Pause:
                            if (_api.Player_GetPlayState() == PlayState.Playing)
                                _api.Player_PlayPause();
                            break;
                        case SystemMediaTransportControlsButton.Previous:
                            _api.Player_PlayPreviousTrack();
                            break;
                        case SystemMediaTransportControlsButton.Next:
                            _api.Player_PlayNextTrack();
                            break;
                    }
                }
                catch { }
            });
        }

        private void ControlsOnPlaybackPositionChangeRequested(
            SystemMediaTransportControls sender,
            PlaybackPositionChangeRequestedEventArgs args)
        {
            long requested = (long)Math.Round(args.RequestedPlaybackPosition.TotalMilliseconds);
            _postToWorker(() =>
            {
                if (_disposed)
                    return;
                try
                {
                    int duration = Math.Max(0, _api.NowPlaying_GetDuration());
                    long upperBound = duration > 0 ? duration : int.MaxValue;
                    int position = (int)Math.Max(0, Math.Min(upperBound, requested));
                    _api.Player_SetPosition(position);
                }
                catch { }
            });
        }

        private void ControlsOnShuffleEnabledChangeRequested(
            SystemMediaTransportControls sender,
            ShuffleEnabledChangeRequestedEventArgs args)
        {
            bool requested = args.RequestedShuffleEnabled;
            _postToWorker(() =>
            {
                if (_disposed)
                    return;
                try { _api.Player_SetShuffle(requested); } catch { }
            });
        }

        private void ControlsOnAutoRepeatModeChangeRequested(
            SystemMediaTransportControls sender,
            AutoRepeatModeChangeRequestedEventArgs args)
        {
            RepeatMode requested;
            switch (args.RequestedAutoRepeatMode)
            {
                case MediaPlaybackAutoRepeatMode.Track:
                    requested = RepeatMode.One;
                    break;
                case MediaPlaybackAutoRepeatMode.List:
                    requested = RepeatMode.All;
                    break;
                default:
                    requested = RepeatMode.None;
                    break;
            }

            _postToWorker(() =>
            {
                if (_disposed)
                    return;
                try { _api.Player_SetRepeat(requested); } catch { }
            });
        }

        private void RefreshArtwork(string trackUrl, bool trackChanged)
        {
            if (trackChanged)
            {
                HasArtwork = false;
                // Cancel the result of an older track even if its image worker
                // is still winding down. The poller will retry this track after
                // that worker releases the in-flight slot.
                Interlocked.Increment(ref _artworkGeneration);
            }

            if (Interlocked.CompareExchange(ref _artworkRefreshInFlight, 1, 0) != 0)
            {
                ArtworkRefreshDeferred = true;
                return;
            }

            ArtworkRefreshDeferred = false;
            int generation = Interlocked.Increment(ref _artworkGeneration);
            HasArtwork = false;
            byte[] imageData = null;
            string artworkPath = "";

            if (trackUrl.Length > 0)
            {
                try
                {
                    PictureLocations locations;
                    string pictureUrl;
                    if (_api.Library_GetArtworkEx(
                            trackUrl,
                            0,
                            true,
                            out locations,
                            out pictureUrl,
                            out imageData) &&
                        imageData != null && imageData.Length == 0)
                    {
                        imageData = null;
                    }
                }
                catch { imageData = null; }
            }

            if (imageData == null)
            {
                artworkPath = SafeGet(() => _api.NowPlaying_GetArtwork());
                Uri artworkUri;
                if (Uri.TryCreate(artworkPath, UriKind.Absolute, out artworkUri) && artworkUri.IsFile)
                    artworkPath = artworkUri.LocalPath;
            }

            if ((imageData == null || imageData.Length == 0) &&
                (artworkPath.Length == 0 || !File.Exists(artworkPath)))
            {
                // Clear the previous track's cover immediately; MusicBee often
                // sends NowPlayingArtworkReady shortly afterwards.
                try
                {
                    if (generation == _artworkGeneration && _controls != null)
                    {
                        _controls.DisplayUpdater.Thumbnail = null;
                        _controls.DisplayUpdater.Update();
                        DeleteFileBestEffort(_currentArtworkPath);
                        _currentArtworkPath = null;
                    }
                }
                finally
                {
                    Interlocked.Exchange(ref _artworkRefreshInFlight, 0);
                }
                return;
            }

            byte[] capturedData = imageData;
            string capturedPath = artworkPath;
            CancellationToken cancellation = _cancellation.Token;
            Task artworkTask = Task.Run(async () =>
            {
                string generatedPath = null;
                try
                {
                    cancellation.ThrowIfCancellationRequested();
                    generatedPath = CreateNormalisedArtwork(capturedData, capturedPath, generation);
                    SetPendingArtworkPath(generatedPath);
                    StorageFile file = await StorageFile.GetFileFromPathAsync(generatedPath).AsTask(cancellation);
                    RandomAccessStreamReference reference = RandomAccessStreamReference.CreateFromFile(file);

                    if (_disposed || cancellation.IsCancellationRequested)
                    {
                        DeleteFileBestEffort(generatedPath);
                        ClearPendingArtworkPath(generatedPath);
                        Interlocked.Exchange(ref _artworkRefreshInFlight, 0);
                        return;
                    }

                    bool posted = _postToWorker(() =>
                    {
                        try
                        {
                            if (_disposed || generation != _artworkGeneration || _controls == null)
                            {
                                DeleteFileBestEffort(generatedPath);
                                return;
                            }

                            string oldPath = _currentArtworkPath;
                            _currentArtworkPath = generatedPath;
                            _controls.DisplayUpdater.Thumbnail = reference;
                            _controls.DisplayUpdater.Update();
                            HasArtwork = true;
                            if (!string.Equals(oldPath, generatedPath, StringComparison.OrdinalIgnoreCase))
                                DeleteFileBestEffort(oldPath);
                        }
                        catch
                        {
                            HasArtwork = false;
                            DeleteFileBestEffort(generatedPath);
                        }
                        finally
                        {
                            ClearPendingArtworkPath(generatedPath);
                            Interlocked.Exchange(ref _artworkRefreshInFlight, 0);
                        }
                    });
                    if (!posted)
                    {
                        DeleteFileBestEffort(generatedPath);
                        ClearPendingArtworkPath(generatedPath);
                        Interlocked.Exchange(ref _artworkRefreshInFlight, 0);
                    }
                }
                catch (OperationCanceledException)
                {
                    DeleteFileBestEffort(generatedPath);
                    ClearPendingArtworkPath(generatedPath);
                    Interlocked.Exchange(ref _artworkRefreshInFlight, 0);
                }
                catch
                {
                    DeleteFileBestEffort(generatedPath);
                    ClearPendingArtworkPath(generatedPath);
                    Interlocked.Exchange(ref _artworkRefreshInFlight, 0);
                }
            }, cancellation);
            lock (_artworkTaskLock)
                _artworkTask = artworkTask;
        }

        private static string CreateNormalisedArtwork(byte[] imageData, string sourcePath, int generation)
        {
            string directory = Path.Combine(Path.GetTempPath(), "TaskbarMediaPresence");
            Directory.CreateDirectory(directory);
            string targetPath = Path.Combine(
                directory,
                "musicbee-artwork-" + Process.GetCurrentProcess().Id + "-" + generation + ".png");
            DeleteFileBestEffort(targetPath);

            using (Stream input = imageData != null
                ? (Stream)new MemoryStream(imageData, false)
                : new FileStream(sourcePath, FileMode.Open, FileAccess.Read, FileShare.ReadWrite | FileShare.Delete))
            using (Image source = Image.FromStream(input, false, true))
            {
                int cropSide = Math.Min(source.Width, source.Height);
                int outputSide = Math.Min(MaximumArtworkSide, cropSide);
                if (outputSide <= 0)
                    throw new InvalidDataException("Artwork has invalid dimensions.");

                int sourceX = (source.Width - cropSide) / 2;
                int sourceY = (source.Height - cropSide) / 2;
                using (var output = new Bitmap(outputSide, outputSide, PixelFormat.Format32bppArgb))
                {
                    output.SetResolution(96, 96);
                    using (Graphics graphics = Graphics.FromImage(output))
                    {
                        graphics.CompositingMode = CompositingMode.SourceCopy;
                        graphics.CompositingQuality = CompositingQuality.HighQuality;
                        graphics.InterpolationMode = InterpolationMode.HighQualityBicubic;
                        graphics.PixelOffsetMode = PixelOffsetMode.HighQuality;
                        graphics.SmoothingMode = SmoothingMode.HighQuality;
                        graphics.DrawImage(
                            source,
                            new Rectangle(0, 0, outputSide, outputSide),
                            new Rectangle(sourceX, sourceY, cropSide, cropSide),
                            GraphicsUnit.Pixel);
                    }
                    output.Save(targetPath, ImageFormat.Png);
                }
            }

            return targetPath;
        }

        private static string NormaliseText(string value)
        {
            if (string.IsNullOrWhiteSpace(value))
                return "";

            string trimmed = value.Trim();
            var clean = new StringBuilder(trimmed.Length);
            foreach (char character in trimmed)
            {
                if (!char.IsControl(character))
                    clean.Append(character);
            }
            return clean.ToString().Trim();
        }

        private static string TitleFromLocation(string location)
        {
            if (location.Length == 0)
                return "";
            try
            {
                Uri uri;
                if (Uri.TryCreate(location, UriKind.Absolute, out uri) && !uri.IsFile)
                {
                    string segment = Uri.UnescapeDataString(uri.Segments[uri.Segments.Length - 1]);
                    return Path.GetFileNameWithoutExtension(segment).Trim();
                }
                return Path.GetFileNameWithoutExtension(location).Trim();
            }
            catch
            {
                return "";
            }
        }

        private static string SafeGet(Func<string> getter)
        {
            try { return getter() ?? ""; }
            catch { return ""; }
        }

        private static T SafeGet<T>(Func<T> getter, T fallback)
        {
            try { return getter(); }
            catch { return fallback; }
        }

        private static void DeleteFileBestEffort(string path)
        {
            if (string.IsNullOrEmpty(path))
                return;
            try { File.Delete(path); } catch { }
        }

        private void SetPendingArtworkPath(string path)
        {
            lock (_artworkTaskLock)
                _pendingArtworkPath = path;
        }

        private void ClearPendingArtworkPath(string path)
        {
            if (string.IsNullOrEmpty(path))
                return;
            lock (_artworkTaskLock)
            {
                if (string.Equals(
                        _pendingArtworkPath, path,
                        StringComparison.OrdinalIgnoreCase))
                {
                    _pendingArtworkPath = null;
                }
            }
        }

        private string TakePendingArtworkPath()
        {
            lock (_artworkTaskLock)
            {
                string path = _pendingArtworkPath;
                _pendingArtworkPath = null;
                return path;
            }
        }

        private static void CleanupStaleArtworkFiles()
        {
            try
            {
                string directory = Path.Combine(Path.GetTempPath(), "TaskbarMediaPresence");
                if (!Directory.Exists(directory))
                    return;
                DateTime cutoff = DateTime.UtcNow.AddDays(-1);
                foreach (string path in Directory.EnumerateFiles(directory, "musicbee-artwork-*.png"))
                {
                    try
                    {
                        const string prefix = "musicbee-artwork-";
                        string name = Path.GetFileNameWithoutExtension(path);
                        int separator = name.IndexOf('-', prefix.Length);
                        int processId;
                        bool processStillRunning = false;
                        if (separator > prefix.Length &&
                            int.TryParse(name.Substring(prefix.Length, separator - prefix.Length), out processId))
                        {
                            try
                            {
                                using (Process process = Process.GetProcessById(processId))
                                    processStillRunning = !process.HasExited;
                            }
                            catch { }
                        }

                        if (!processStillRunning && File.GetLastWriteTimeUtc(path) < cutoff)
                            File.Delete(path);
                    }
                    catch { }
                }
            }
            catch { }
        }

        [ComImport]
        [Guid("ddb0472d-c911-4a1f-86d9-dc3d71a95f5a")]
        [InterfaceType(ComInterfaceType.InterfaceIsIInspectable)]
        private interface ISystemMediaTransportControlsInterop
        {
            [PreserveSig]
            int GetForWindow(IntPtr appWindow, [In] ref Guid riid, out IntPtr mediaTransportControl);
        }
    }
}
