using System;
using System.IO;
using System.IO.MemoryMappedFiles;
using System.Runtime.InteropServices;
using System.Security;
using System.Text;
using System.Threading;

namespace MusicBeePlugin
{
    internal sealed class EmbeddedLyricsPublisher : IDisposable
    {
        internal const string MappingName = @"Local\TaskbarMediaPresence.MusicBeeLyrics.v3";
        private const int HeaderSize = 16;
        private const int MappingSize = 3224;
        private const int PollInterval = 100;
        private const int FileCheckInterval = 3000;
        private const int MaximumSampleAge = 2500;

        [DllImport("kernel32.dll")]
        private static extern long GetTickCount64();

        private readonly object _gate = new object();
        private readonly Timer _timer;
        private readonly byte[] _payload = new byte[MappingSize - HeaderSize];
        private MemoryMappedFile _mapping;
        private MemoryMappedViewAccessor _view;
        private bool _disposed;
        private int _sequence;
        private string _file = "";
        private long _nextFileCheck;
        private long _fileLength = -1;
        private DateTime _fileWriteTime;
        private EmbeddedMp3Lyrics _lyrics;
        private EmbeddedMp3Lyrics _currentLyrics;
        private string _title;
        private string _artist;
        private long _position;
        private long _duration;
        private bool _playing;
        private long _sampleTime;
        private bool _visible;

        internal EmbeddedLyricsPublisher()
        {
            _timer = new Timer(Publish, null, Timeout.Infinite, Timeout.Infinite);
        }

        // Called on the MusicBee API worker. The publication timer never opens files or calls MusicBee.
        internal void Update(string file, string title, string artist, int position, int duration, bool playing)
        {
            long now = GetTickCount64();
            if (!string.Equals(_file, file, StringComparison.OrdinalIgnoreCase))
            {
                Clear();
                _file = file;
                _fileLength = -1;
                _lyrics = null;
                _nextFileCheck = 0;
            }
            if (now >= _nextFileCheck)
            {
                _nextFileCheck = now + FileCheckInterval;
                RefreshFile();
            }

            if (_lyrics == null || title.Length == 0)
            {
                Clear();
                return;
            }
            lock (_gate)
            {
                bool startTimer = _currentLyrics == null;
                _currentLyrics = _lyrics;
                _title = title;
                _artist = artist;
                _position = Math.Max(0, position);
                _duration = duration;
                _playing = playing;
                _sampleTime = now;
                if (startTimer)
                    _timer.Change(0, PollInterval);
            }
        }

        private void RefreshFile()
        {
            try
            {
                var info = new FileInfo(_file);
                long length = info.Length;
                DateTime writeTime = info.LastWriteTimeUtc;
                if (length == _fileLength && writeTime == _fileWriteTime)
                    return;
                _lyrics = EmbeddedMp3Lyrics.Read(_file);
                _fileLength = length;
                _fileWriteTime = writeTime;
            }
            catch (IOException) { MarkFileUnavailable(); }
            catch (UnauthorizedAccessException) { MarkFileUnavailable(); }
            catch (SecurityException) { MarkFileUnavailable(); }
        }

        private void MarkFileUnavailable()
        {
            _lyrics = null;
            _fileLength = -1;
        }

        private void Publish(object state)
        {
            lock (_gate)
            {
                if (_disposed || _currentLyrics == null)
                    return;
                long now = GetTickCount64();
                long age = now - _sampleTime;
                if (age > MaximumSampleAge)
                {
                    Clear();
                    return;
                }
                long position = _position + (_playing ? age : 0);
                if (_duration > 0)
                    position = Math.Min(position, _duration);
                EmbeddedMp3Lyrics.Line line = _currentLyrics.At(position);
                if (line == null)
                {
                    Hide();
                    return;
                }
                try
                {
                    if (_view == null)
                    {
                        _mapping = MemoryMappedFile.CreateOrOpen(MappingName, MappingSize, MemoryMappedFileAccess.ReadWrite);
                        _view = _mapping.CreateViewAccessor(0, MappingSize, MemoryMappedFileAccess.Write);
                    }

                    Array.Clear(_payload, 0, _payload.Length);
                    WriteText(_title, 0, 160);
                    WriteText(_artist, 320, 160);
                    int textLength = WriteText(line.Text, 640, 512);
                    WriteText(_currentLyrics.Longest, 2184, 512);
                    long linePosition = position - line.Time;
                    for (int index = line.Words.Count - 1; index >= 0; index--)
                    {
                        EmbeddedMp3Lyrics.Word word = line.Words[index];
                        if (word.Time > linePosition)
                            continue;
                        if (word.Start + word.Length <= textLength)
                        {
                            WriteInt32(1664, word.Start);
                            WriteInt32(1668, word.Length);
                        }
                        break;
                    }
                    WriteSnapshot(now);
                    _visible = true;
                }
                catch (IOException) { CloseMapping(); }
                catch (UnauthorizedAccessException) { CloseMapping(); }
                catch (SecurityException) { CloseMapping(); }
            }
        }

        internal void Clear()
        {
            lock (_gate)
            {
                _currentLyrics = null;
                _timer.Change(Timeout.Infinite, Timeout.Infinite);
                Hide();
            }
        }

        private void Hide()
        {
            if (!_visible)
                return;
            Array.Clear(_payload, 0, _payload.Length);
            WriteSnapshot(0);
            _visible = false;
        }

        private void CloseMapping()
        {
            _view?.Dispose();
            _mapping?.Dispose();
            _view = null;
            _mapping = null;
            _visible = false;
        }

        private void WriteSnapshot(long tick)
        {
            _sequence = unchecked(_sequence + 2);
            _view.Write(0, unchecked(_sequence - 1));
            Thread.MemoryBarrier();
            _view.Write(4, 3);
            _view.Write(8, tick);
            _view.WriteArray(HeaderSize, _payload, 0, _payload.Length);
            Thread.MemoryBarrier();
            _view.Write(0, _sequence);
        }

        private int WriteText(string text, int start, int capacity)
        {
            int length = Math.Min(text.Length, capacity - 1);
            if (length > 0 && char.IsHighSurrogate(text[length - 1]))
                length--;
            Encoding.Unicode.GetBytes(text, 0, length, _payload, start);
            return length;
        }

        private void WriteInt32(int start, int value)
        {
            for (int index = 0; index < 4; index++)
                _payload[start + index] = unchecked((byte)(value >> (index * 8)));
        }

        public void Dispose()
        {
            lock (_gate)
            {
                _disposed = true;
                _timer.Dispose();
                Hide();
                CloseMapping();
            }
        }
    }
}
