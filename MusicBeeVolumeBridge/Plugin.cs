using System;
using System.Globalization;
using System.IO;
using System.IO.Pipes;
using System.Security.AccessControl;
using System.Security.Principal;
using System.Text;
using System.Threading;

namespace MusicBeePlugin
{
    /// <summary>
    /// Original MusicBee companion for Taskbar Media Presence. It publishes
    /// MusicBee through the official Windows media-session API and exposes only
    /// MusicBee's internal volume through a private, per-user named pipe.
    /// </summary>
    public partial class Plugin
    {
        private const string PipeName = "TaskbarMediaPresence.MusicBeeVolume.v1";
        private const int PipeMaximumRequestBytes = 128;
        private const int PipeRequestTimeoutMilliseconds = 2000;
        private const int PipeShutdownWaitMilliseconds = 3000;
        private const int WorkerShutdownWaitMilliseconds = 4000;
        private const int StartupMetadataRetryTicks = 30;

        private readonly object _serverLock = new object();
        private MusicBeeApiInterface _api;
        private SerializedWorker _worker;
        private System.Threading.Timer _pollTimer;
        private MediaSessionPublisher _mediaSession;
        private Thread _serverThread;
        private NamedPipeServerStream _activeServer;
        private CancellationTokenSource _serverCancellation;
        private volatile bool _closing;
        private int _closeStarted;
        private int _refreshQueued;
        private bool _metadataDirty;
        private bool _artworkDirty;
        private int _startupRetryTicksRemaining;

        public PluginInfo Initialise(IntPtr apiInterfacePtr)
        {
            _api = new MusicBeeApiInterface();
            _api.Initialise(apiInterfacePtr);

            var info = new PluginInfo
            {
                PluginInfoVersion = PluginInfoVersion,
                Type = PluginType.General,
                Name = "Taskbar Media Presence",
                Description = "Publishes MusicBee media controls and lets Taskbar Media Presence control MusicBee's internal volume.",
                Author = "MrBoxik",
                TargetApplication = "",
                VersionMajor = 1,
                VersionMinor = 0,
                Revision = 0,
                MinInterfaceVersion = MinInterfaceVersion,
                MinApiRevision = MinApiRevision,
                ReceiveNotifications = ReceiveNotificationFlags.PlayerEvents,
                ConfigurationPanelHeight = 0,
            };

            if (_api.ApiRevision < MinApiRevision)
                return info;

            _closing = false;
            Interlocked.Exchange(ref _closeStarted, 0);
            Interlocked.Exchange(ref _refreshQueued, 0);

            // Plugin.Initialise and player notifications are not guaranteed to
            // run on a window thread. A dedicated MTA worker is the sole owner
            // of MusicBee API and SMTC operations; no GUI message pump is
            // required.
            _worker = new SerializedWorker(
                "Taskbar Media Presence MusicBee worker",
                TraceWorkerException);
            if (!_worker.Post(InitialiseWorkerState))
                throw new InvalidOperationException("Could not start the MusicBee worker.");

            _pollTimer = new System.Threading.Timer(
                PollTimerOnTick,
                null,
                1000,
                1000);

            _serverCancellation = new CancellationTokenSource();
            _serverThread = new Thread(ServerLoop)
            {
                IsBackground = true,
                Name = "Taskbar Media Presence MusicBee bridge",
            };
            _serverThread.Start();

            return info;
        }

        public bool Configure(IntPtr panelHandle) => false;
        public void SaveSettings() { }
        public void Uninstall() { }

        public void ReceiveNotification(string sourceFileUrl, NotificationType type)
        {
            SerializedWorker worker = _worker;
            if (_closing || worker == null)
                return;

            worker.Post(() => HandleNotification(type));
        }

        public void Close(PluginCloseReason reason)
        {
            if (Interlocked.Exchange(ref _closeStarted, 1) != 0)
                return;
            _closing = true;

            // Stop timer callbacks first. Dispose(WaitHandle) waits for a
            // callback that was already running; callbacks only enqueue work.
            System.Threading.Timer pollTimer =
                Interlocked.Exchange(ref _pollTimer, null);
            if (pollTimer != null)
            {
                using (var stopped = new ManualResetEvent(false))
                {
                    try
                    {
                        if (pollTimer.Dispose(stopped))
                            stopped.WaitOne(PipeRequestTimeoutMilliseconds);
                    }
                    catch { }
                }
            }

            CancellationTokenSource serverCancellation = _serverCancellation;
            try { serverCancellation?.Cancel(); } catch (ObjectDisposedException) { }

            lock (_serverLock)
            {
                try { _activeServer?.Dispose(); } catch { }
                _activeServer = null;
            }

            Thread serverThread = _serverThread;
            bool serverExited = serverThread == null;
            try
            {
                if (serverThread != null)
                    serverExited = serverThread.Join(PipeShutdownWaitMilliseconds);
            }
            catch { }

            if (serverExited)
            {
                _serverThread = null;
                _serverCancellation = null;
                try { serverCancellation?.Dispose(); } catch { }
            }

            // Dispose the apartment-bound SMTC object on its owner worker. Old
            // queued notifications observe _closing and become no-ops.
            SerializedWorker worker = _worker;
            if (worker != null)
            {
                // Queue cleanup before closing the worker. Stop(false) drains
                // this final item, and if a third-party API is temporarily
                // stuck the background worker will still dispose SMTC when it
                // eventually recovers.
                worker.Post(() =>
                {
                    try { _mediaSession?.Dispose(); } catch { }
                    _mediaSession = null;
                });

                bool workerExited = false;
                try
                {
                    workerExited = worker.Stop(
                        false,
                        WorkerShutdownWaitMilliseconds);
                }
                catch { }
                if (workerExited)
                {
                    worker.Dispose();
                    _worker = null;
                }
            }
        }

        private void InitialiseWorkerState()
        {
            if (_closing)
                return;

            _metadataDirty = true;
            _artworkDirty = true;
            _startupRetryTicksRemaining = StartupMetadataRetryTicks;
            _mediaSession = new MediaSessionPublisher(_api, PostToWorker);

            // Try immediately, then keep retrying from the timer. On a cold
            // Windows start MusicBee can notify plugins before its HWND or tags
            // are ready; retries avoid publishing an empty/Untitled session.
            RefreshMediaSession();
        }

        private void HandleNotification(NotificationType type)
        {
            if (_closing)
                return;

            switch (type)
            {
                case NotificationType.PluginStartup:
                case NotificationType.MusicBeeStarted:
                case NotificationType.TrackChanged:
                case NotificationType.LibrarySwitched:
                    _metadataDirty = true;
                    _artworkDirty = true;
                    _startupRetryTicksRemaining = StartupMetadataRetryTicks;
                    break;

                case NotificationType.ApplicationWindowChanged:
                    _mediaSession?.Invalidate();
                    _metadataDirty = true;
                    _artworkDirty = true;
                    _startupRetryTicksRemaining = StartupMetadataRetryTicks;
                    break;

                case NotificationType.TrackChanging:
                    _mediaSession?.SetChanging();
                    _metadataDirty = true;
                    _artworkDirty = true;
                    _startupRetryTicksRemaining = StartupMetadataRetryTicks;
                    break;

                case NotificationType.NowPlayingArtworkReady:
                    _artworkDirty = true;
                    break;

                case NotificationType.PlayStateChanged:
                case NotificationType.PlayerRepeatChanged:
                case NotificationType.PlayerShuffleChanged:
                    break;

                case NotificationType.ShutdownStarted:
                    return;
            }

            RefreshMediaSession();
        }

        private void PollTimerOnTick(object state)
        {
            QueueRefresh();
        }

        private void QueueRefresh()
        {
            if (_closing || Interlocked.Exchange(ref _refreshQueued, 1) != 0)
                return;

            SerializedWorker worker = _worker;
            if (worker == null || !worker.Post(() =>
                {
                    try
                    {
                        if (!_closing)
                            RefreshMediaSession();
                    }
                    finally
                    {
                        Volatile.Write(ref _refreshQueued, 0);
                    }
                }))
            {
                Volatile.Write(ref _refreshQueued, 0);
            }
        }

        private void RefreshMediaSession()
        {
            if (_closing || _mediaSession == null)
                return;

            try
            {
                IntPtr musicBeeWindow = _api.MB_GetWindowHandle();
                if (!_mediaSession.EnsureStarted(musicBeeWindow))
                    return;

                bool startupRetry = _startupRetryTicksRemaining > 0;
                if (startupRetry)
                    _startupRetryTicksRemaining--;

                bool refreshMetadata = _metadataDirty || startupRetry || !_mediaSession.HasMetadata;
                bool refreshArtwork =
                    _artworkDirty || (startupRetry && !_mediaSession.HasArtwork);
                if (refreshMetadata || refreshArtwork)
                {
                    bool metadataReady = _mediaSession.RefreshMetadata(refreshArtwork);
                    _metadataDirty = !metadataReady;
                    // Keep an artwork notification pending while MusicBee is
                    // still restoring the track title. Once metadata is ready,
                    // only a request deferred behind an older worker remains.
                    _artworkDirty = refreshArtwork &&
                        (!metadataReady || _mediaSession.ArtworkRefreshDeferred);
                }

                _mediaSession.RefreshPlaybackAndTimeline();
            }
            catch (Exception exception)
            {
                // A media-session failure must never take MusicBee down. Trace
                // once through MusicBee and let the next timer tick recover.
                try { _api.MB_Trace("Taskbar Media Presence: " + exception.Message); } catch { }
                _mediaSession?.Invalidate();
                _metadataDirty = true;
                _artworkDirty = true;
            }
        }

        private void TraceWorkerException(Exception exception)
        {
            // Called by SerializedWorker on the worker itself, preserving the
            // single-threaded MusicBee API contract.
            try
            {
                _api.MB_Trace(
                    "Taskbar Media Presence worker: " +
                    (exception?.Message ?? "unknown error"));
            }
            catch { }
        }

        private void ServerLoop()
        {
            CancellationToken cancellation =
                _serverCancellation?.Token ?? CancellationToken.None;
            while (!_closing && !cancellation.IsCancellationRequested)
            {
                NamedPipeServerStream server = null;
                try
                {
                    server = CreatePipeServer(PipeName);
                    lock (_serverLock) _activeServer = server;
                    server.WaitForConnectionAsync(cancellation).GetAwaiter().GetResult();
                    if (!_closing && !cancellation.IsCancellationRequested)
                        HandleClient(server, cancellation);
                }
                catch (OperationCanceledException) when (cancellation.IsCancellationRequested) { }
                catch (IOException)
                {
                    // Another copy of an older bridge can temporarily own the
                    // single-instance pipe. Back off instead of spinning.
                    if (!_closing) Thread.Sleep(250);
                }
                catch (ObjectDisposedException) { }
                catch (InvalidOperationException) { }
                catch (Exception)
                {
                    // The SMTC publisher is still useful if a machine's pipe
                    // security policy rejects the optional volume bridge. Never
                    // let a background bridge failure terminate MusicBee.
                    if (!_closing) Thread.Sleep(500);
                }
                finally
                {
                    lock (_serverLock)
                    {
                        if (ReferenceEquals(_activeServer, server))
                            _activeServer = null;
                    }
                    try { server?.Dispose(); } catch { }
                }
            }
        }

        private static NamedPipeServerStream CreatePipeServer(string pipeName)
        {
            var security = new PipeSecurity();
            SecurityIdentifier currentUser;
            using (WindowsIdentity identity = WindowsIdentity.GetCurrent())
                currentUser = identity.User;
            if (currentUser == null)
                throw new InvalidOperationException("The current Windows user has no security identifier.");

            security.SetOwner(currentUser);
            security.SetAccessRuleProtection(true, false);
            security.AddAccessRule(new PipeAccessRule(
                currentUser,
                PipeAccessRights.FullControl,
                AccessControlType.Allow));

            return new NamedPipeServerStream(
                pipeName,
                PipeDirection.InOut,
                1,
                PipeTransmissionMode.Byte,
                PipeOptions.Asynchronous,
                1024,
                1024,
                security);
        }

        private void HandleClient(Stream stream, CancellationToken cancellation)
        {
            using (var writer = new StreamWriter(stream, new UTF8Encoding(false), 1024, true) { AutoFlush = true })
            {
                string request = ReadRequestLine(stream, cancellation);
                if (request == null)
                {
                    if (!cancellation.IsCancellationRequested)
                        writer.WriteLine("ERR request-timeout-or-too-long");
                    return;
                }

                try
                {
                    if (request.Equals("GET", StringComparison.OrdinalIgnoreCase))
                    {
                        VolumeState state = InvokeOnWorker(ReadVolumeState);
                        WriteSnapshot(writer, true, state);
                        return;
                    }

                    if (request.StartsWith("SET ", StringComparison.OrdinalIgnoreCase) &&
                        int.TryParse(request.Substring(4), NumberStyles.Integer,
                            CultureInfo.InvariantCulture, out int percent))
                    {
                        percent = Math.Max(0, Math.Min(100, percent));
                        VolumeResult result = InvokeOnWorker(() =>
                        {
                            bool success = _api.Player_SetVolume(percent / 100f);
                            if (success && percent > 0 && _api.Player_GetMute())
                                success = _api.Player_SetMute(false);
                            return new VolumeResult(success, ReadVolumeState());
                        });
                        WriteSnapshot(writer, result.Succeeded, result.State);
                        return;
                    }

                    if (request.StartsWith("MUTE ", StringComparison.OrdinalIgnoreCase))
                    {
                        bool mute = request.Substring(5).Trim() == "1";
                        VolumeResult result = InvokeOnWorker(() =>
                        {
                            bool success = _api.Player_SetMute(mute);
                            return new VolumeResult(success, ReadVolumeState());
                        });
                        WriteSnapshot(writer, result.Succeeded, result.State);
                        return;
                    }

                    writer.WriteLine("ERR unsupported-command");
                }
                catch
                {
                    writer.WriteLine("ERR musicbee-api-failure");
                }
            }
        }

        private static string ReadRequestLine(
            Stream stream,
            CancellationToken cancellation)
        {
            using (var timeout = CancellationTokenSource.CreateLinkedTokenSource(cancellation))
            {
                timeout.CancelAfter(PipeRequestTimeoutMilliseconds);
                var request = new byte[PipeMaximumRequestBytes];
                var buffer = new byte[32];
                int requestLength = 0;
                try
                {
                    while (requestLength < request.Length)
                    {
                        int count = stream.ReadAsync(
                                buffer, 0, buffer.Length, timeout.Token)
                            .GetAwaiter()
                            .GetResult();
                        if (count == 0)
                            return Encoding.UTF8.GetString(request, 0, requestLength)
                                .TrimEnd('\r');

                        for (int index = 0; index < count; index++)
                        {
                            byte value = buffer[index];
                            if (value == (byte)'\n')
                            {
                                return Encoding.UTF8.GetString(
                                        request, 0, requestLength)
                                    .TrimEnd('\r');
                            }
                            if (requestLength >= request.Length)
                                return null;
                            request[requestLength++] = value;
                        }
                    }
                }
                catch (OperationCanceledException)
                {
                    if (cancellation.IsCancellationRequested)
                        throw;
                    return null;
                }
            }

            return null;
        }

        private VolumeState ReadVolumeState()
        {
            int percent = (int)Math.Round(
                Math.Max(0f, Math.Min(1f, _api.Player_GetVolume())) * 100f,
                MidpointRounding.AwayFromZero);
            return new VolumeState(percent, _api.Player_GetMute());
        }

        private static void WriteSnapshot(
            StreamWriter writer,
            bool operationSucceeded,
            VolumeState state)
        {
            writer.WriteLine(string.Format(
                CultureInfo.InvariantCulture,
                "{0} {1} {2}",
                operationSucceeded ? "OK" : "ERR",
                state.Percent,
                state.Muted ? 1 : 0));
        }

        private bool PostToWorker(Action action)
        {
            SerializedWorker worker = _worker;
            return !_closing && worker != null && worker.Post(action);
        }

        private T InvokeOnWorker<T>(Func<T> action)
        {
            SerializedWorker worker = _worker;
            if (_closing || worker == null)
                throw new InvalidOperationException("MusicBee worker is unavailable.");
            CancellationToken cancellation =
                _serverCancellation?.Token ?? CancellationToken.None;
            return worker.Invoke(
                action,
                PipeRequestTimeoutMilliseconds,
                cancellation);
        }

        private readonly struct VolumeResult
        {
            public VolumeResult(bool succeeded, VolumeState state)
            {
                Succeeded = succeeded;
                State = state;
            }

            public bool Succeeded { get; }
            public VolumeState State { get; }
        }

        private readonly struct VolumeState
        {
            public VolumeState(int percent, bool muted)
            {
                Percent = percent;
                Muted = muted;
            }

            public int Percent { get; }
            public bool Muted { get; }
        }
    }
}
