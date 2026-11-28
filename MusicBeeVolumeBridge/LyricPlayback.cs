using System;
using System.Collections.Generic;
using System.IO;
using System.Runtime.Serialization;
using System.Runtime.Serialization.Json;
using System.Text;

namespace MusicBeePlugin
{
    public partial class Plugin
    {
        private void RefreshEmbeddedLyrics()
        {
            if (_embeddedLyrics == null)
                return;
            try
            {
                string file = LocalAudioPath(_api.NowPlaying_GetFileUrl());
                var state = _api.Player_GetPlayState();
                if ((state != PlayState.Playing && state != PlayState.Paused) ||
                    file.StartsWith(@"\\", StringComparison.Ordinal) ||
                    !string.Equals(Path.GetExtension(file), ".mp3", StringComparison.OrdinalIgnoreCase))
                {
                    _embeddedLyrics.Clear();
                    return;
                }

                string title = MediaSessionPublisher.LyricIdentity(_api.NowPlaying_GetFileTag(MetaDataType.TrackTitle), file);
                string artist = MediaSessionPublisher.LyricIdentity(_api.NowPlaying_GetFileTag(MetaDataType.Artist), "");
                _embeddedLyrics.Update(file, title, artist, _api.Player_GetPosition(),
                    _api.NowPlaying_GetDuration(), state == PlayState.Playing);
            }
            catch (Exception exception)
            {
                _embeddedLyrics.Clear();
                TraceWorkerException(exception);
            }
        }

        [DataContract]
        private sealed class LyricPlayback
        {
            [DataMember(Name = "file")] public string File;
            [DataMember(Name = "title")] public string Title;
            [DataMember(Name = "artist")] public string Artist;
            [DataMember(Name = "positionMs")] public int PositionMs;
            [DataMember(Name = "durationMs")] public int DurationMs;
            [DataMember(Name = "playing")] public bool Playing;
            [DataMember(Name = "state")] public string State;
            [DataMember(Name = "upNext")] public string[] UpNext;
            [DataMember(Name = "autoDj")] public bool AutoDj;
        }

        private LyricPlayback ReadLyricPlayback()
        {
            string file = LocalAudioPath(_api.NowPlaying_GetFileUrl());
            var state = _api.Player_GetPlayState();
            bool autoDj = _api.Player_GetAutoDjEnabled?.Invoke() == true;
            var upcoming = new List<string>();
            if (file.Length > 0 && (autoDj || _api.NowPlayingList_IsAnyFollowingTracks()))
            {
                var seenIndices = new HashSet<int> { _api.NowPlayingList_GetCurrentIndex() };
                var seenFiles = new HashSet<string>(StringComparer.OrdinalIgnoreCase) { file };
                for (int offset = 1; offset <= 24; offset++)
                {
                    int index = _api.NowPlayingList_GetNextIndex(offset);
                    if (index < 0 || !seenIndices.Add(index))
                        break;
                    string path = LocalAudioPath(_api.NowPlayingList_GetListFileUrl(index));
                    if (path.Length > 0 && seenFiles.Add(path))
                        upcoming.Add(path);
                }
            }
            return new LyricPlayback
            {
                File = file,
                Title = MediaSessionPublisher.LyricIdentity(_api.NowPlaying_GetFileTag(MetaDataType.TrackTitle), file),
                Artist = MediaSessionPublisher.LyricIdentity(_api.NowPlaying_GetFileTag(MetaDataType.Artist), ""),
                PositionMs = Math.Max(0, _api.Player_GetPosition()),
                DurationMs = Math.Max(0, _api.NowPlaying_GetDuration()),
                Playing = state == PlayState.Playing,
                State = state.ToString(),
                UpNext = upcoming.ToArray(),
                AutoDj = autoDj,
            };
        }

        internal static string LocalAudioPath(string source)
        {
            if (Uri.TryCreate(source, UriKind.Absolute, out Uri uri) && uri.IsFile)
                return uri.LocalPath;
            return "";
        }

        private static void WriteLyricPlayback(StreamWriter writer, LyricPlayback playback)
        {
            var serializer = new DataContractJsonSerializer(typeof(LyricPlayback));
            using (var payload = new MemoryStream())
            {
                serializer.WriteObject(payload, playback);
                writer.WriteLine(Encoding.UTF8.GetString(payload.ToArray()));
            }
        }
    }
}
