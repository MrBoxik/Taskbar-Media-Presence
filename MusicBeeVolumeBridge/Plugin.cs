using System;
using System.Globalization;
using System.IO;
using System.IO.Pipes;
using System.Text;
using System.Threading;
using System.Windows.Forms;

namespace MusicBeePlugin
{
    // This original companion plugin exposes only MusicBee's official
    // Player_GetVolume/Player_SetVolume/Player_GetMute/Player_SetMute methods
    // to Taskbar Media Presence through a local, per-user named pipe.
    public partial class Plugin
    {
        private const string PipeName = "TaskbarMediaPresence.MusicBeeVolume.v1";

        private MusicBeeApiInterface _api;
        private Control _dispatcher;
        private Thread _serverThread;
        private NamedPipeServerStream _activeServer;
        private volatile bool _closing;
        private readonly object _serverLock = new object();

        public PluginInfo Initialise(IntPtr apiInterfacePtr)
        {
            _api = new MusicBeeApiInterface();
            _api.Initialise(apiInterfacePtr);

            var info = new PluginInfo
            {
                PluginInfoVersion = PluginInfoVersion,
                Type = PluginType.General,
                Name = "Taskbar Media Presence Volume Bridge",
                Description = "Lets Taskbar Media Presence control MusicBee's internal player volume.",
                Author = "MrBoxik",
                TargetApplication = "",
                VersionMajor = 1,
                VersionMinor = 0,
                Revision = 0,
                MinInterfaceVersion = MinInterfaceVersion,
                MinApiRevision = MinApiRevision,
                ReceiveNotifications = ReceiveNotificationFlags.StartupOnly,
                ConfigurationPanelHeight = 0,
            };

            if (_api.ApiRevision < MinApiRevision)
                return info;

            // MusicBee initializes plugins on its UI thread. A hidden WinForms
            // control gives pipe requests a safe way to invoke the API there.
            _dispatcher = new Control();
            _dispatcher.CreateControl();

            _closing = false;
            _serverThread = new Thread(ServerLoop)
            {
                IsBackground = true,
                Name = "Taskbar Media Presence volume bridge",
            };
            _serverThread.Start();
            return info;
        }

        public bool Configure(IntPtr panelHandle) => false;
        public void SaveSettings() { }
        public void ReceiveNotification(string sourceFileUrl, NotificationType type) { }
        public void Uninstall() { }

        public void Close(PluginCloseReason reason)
        {
            _closing = true;
            lock (_serverLock)
            {
                try { _activeServer?.Dispose(); } catch { }
                _activeServer = null;
            }
            try { _serverThread?.Join(750); } catch { }
            _serverThread = null;
            try { _dispatcher?.Dispose(); } catch { }
            _dispatcher = null;
        }

        private void ServerLoop()
        {
            while (!_closing)
            {
                NamedPipeServerStream server = null;
                try
                {
                    server = new NamedPipeServerStream(
                        PipeName,
                        PipeDirection.InOut,
                        1,
                        PipeTransmissionMode.Byte,
                        PipeOptions.None,
                        1024,
                        1024);
                    lock (_serverLock) _activeServer = server;
                    server.WaitForConnection();
                    if (!_closing) HandleClient(server);
                }
                catch (IOException) { }
                catch (ObjectDisposedException) { }
                catch (InvalidOperationException) { }
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

        private void HandleClient(Stream stream)
        {
            using (var reader = new StreamReader(stream, new UTF8Encoding(false), false, 1024, true))
            using (var writer = new StreamWriter(stream, new UTF8Encoding(false), 1024, true) { AutoFlush = true })
            {
                string request = reader.ReadLine() ?? "";
                try
                {
                    if (request.Equals("GET", StringComparison.OrdinalIgnoreCase))
                    {
                        WriteSnapshot(writer, true);
                        return;
                    }

                    if (request.StartsWith("SET ", StringComparison.OrdinalIgnoreCase) &&
                        int.TryParse(request.Substring(4), NumberStyles.Integer,
                            CultureInfo.InvariantCulture, out int percent))
                    {
                        percent = Math.Max(0, Math.Min(100, percent));
                        bool changed = InvokeOnMusicBeeThread(() =>
                        {
                            bool success = _api.Player_SetVolume(percent / 100f);
                            if (success && percent > 0 && _api.Player_GetMute())
                                success = _api.Player_SetMute(false);
                            return success;
                        });
                        WriteSnapshot(writer, changed);
                        return;
                    }

                    if (request.StartsWith("MUTE ", StringComparison.OrdinalIgnoreCase))
                    {
                        bool mute = request.Substring(5).Trim() == "1";
                        bool changed = InvokeOnMusicBeeThread(() => _api.Player_SetMute(mute));
                        WriteSnapshot(writer, changed);
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

        private void WriteSnapshot(StreamWriter writer, bool operationSucceeded)
        {
            var state = InvokeOnMusicBeeThread(() =>
            {
                int percent = (int)Math.Round(
                    Math.Max(0f, Math.Min(1f, _api.Player_GetVolume())) * 100f,
                    MidpointRounding.AwayFromZero);
                return new VolumeState(percent, _api.Player_GetMute());
            });
            writer.WriteLine(string.Format(
                CultureInfo.InvariantCulture,
                "{0} {1} {2}",
                operationSucceeded ? "OK" : "ERR",
                state.Percent,
                state.Muted ? 1 : 0));
        }

        private T InvokeOnMusicBeeThread<T>(Func<T> action)
        {
            if (_dispatcher == null || _dispatcher.IsDisposed)
                throw new InvalidOperationException("MusicBee dispatcher is unavailable.");
            if (_dispatcher.InvokeRequired)
                return (T)_dispatcher.Invoke(action);
            return action();
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
