using System;
using System.Collections.Generic;
using System.Globalization;
using System.IO;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;

namespace MusicBeePlugin
{
    internal sealed class EmbeddedMp3Lyrics
    {
        internal sealed class Line
        {
            internal long Time;
            internal string Text;
            internal List<Word> Words = new List<Word>();
        }

        internal struct Word
        {
            internal long Time;
            internal int Start;
            internal int Length;
        }

        private const int MaximumTagSize = 64 * 1024 * 1024;
        private const int MaximumLyricSize = 512 * 1024;
        private static readonly Regex LineTime = new Regex(
            @"\G\[([0-9]{1,6}):([0-9]{1,2}(?:[.,][0-9]{1,3})?)\]", RegexOptions.CultureInvariant);
        private static readonly Regex WordTime = new Regex(
            @"<([0-9]{1,6}):([0-9]{1,2}(?:[.,][0-9]{1,3})?)>", RegexOptions.CultureInvariant);
        private static readonly Regex Offset = new Regex(
            @"^\s*\[offset:\s*([+-]?\d+)\s*\]\s*$", RegexOptions.IgnoreCase | RegexOptions.CultureInvariant);

        private readonly Line[] _lines;
        internal readonly string Longest;

        private EmbeddedMp3Lyrics(List<Line> lines)
        {
            _lines = lines.OrderBy(line => line.Time).ToArray();
            Longest = _lines.OrderByDescending(line => line.Text.Length).First().Text;
        }

        internal Line At(long position)
        {
            int low = 0;
            int high = _lines.Length;
            while (low < high)
            {
                int middle = low + (high - low) / 2;
                if (_lines[middle].Time <= position)
                    low = middle + 1;
                else
                    high = middle;
            }
            return low == 0 ? null : _lines[low - 1];
        }

        internal static EmbeddedMp3Lyrics Read(string path)
        {
            using (var stream = new FileStream(path, FileMode.Open, FileAccess.Read,
                FileShare.ReadWrite | FileShare.Delete))
            using (var reader = new BinaryReader(stream))
            {
                byte[] header = reader.ReadBytes(10);
                if (header.Length != 10 || header[0] != 'I' || header[1] != 'D' || header[2] != '3')
                    return null;
                int version = header[3];
                int size = SyncSafe(header, 6);
                if ((version != 3 && version != 4) || size < 0 || size > MaximumTagSize ||
                    size > stream.Length - stream.Position)
                    return null;

                bool unsync = (header[5] & 0x80) != 0;
                if (version == 3 && unsync)
                {
                    // v2.3 inserts escape bytes across the tag, including frame headers.
                    using (var tag = new MemoryStream(RemoveUnsync(reader.ReadBytes(size))))
                    using (var tagReader = new BinaryReader(tag))
                        return ReadFrames(tagReader, tag.Length, version, header[5], false);
                }
                return ReadFrames(reader, stream.Position + size, version, header[5], unsync);
            }
        }

        private static EmbeddedMp3Lyrics ReadFrames(BinaryReader reader, long end, int version,
            byte flags, bool unsync)
        {
            Stream stream = reader.BaseStream;
            if ((flags & 0x40) != 0)
            {
                if (end - stream.Position < 4)
                    return null;
                byte[] size = reader.ReadBytes(4);
                long remaining = version == 3 ? BigEndian(size, 0) : SyncSafe(size, 0) - 4L;
                if (remaining < 0 || remaining > end - stream.Position)
                    return null;
                stream.Position += remaining;
            }

            EmbeddedMp3Lyrics synced = null;
            while (end - stream.Position >= 10)
            {
                byte[] frame = reader.ReadBytes(10);
                if (frame.Length != 10 || frame[0] == 0)
                    break;
                long length = version == 3 ? BigEndian(frame, 4) : (long)SyncSafe(frame, 4);
                if (length <= 0 || length > end - stream.Position)
                    break;
                string name = Encoding.ASCII.GetString(frame, 0, 4);
                int format = frame[9];
                bool unreadable = (format & (version == 3 ? 0xc0 : 0x0c)) != 0;
                if (length > MaximumLyricSize || unreadable ||
                    (name != "USLT" && name != "SYLT" && name != "TXXX"))
                {
                    stream.Position += length;
                    continue;
                }

                byte[] data = reader.ReadBytes((int)length);
                if (data.Length != length)
                    break;
                if (version == 4 && (unsync || (format & 2) != 0))
                    data = RemoveUnsync(data);
                int start = (format & (version == 3 ? 0x20 : 0x40)) != 0 ? 1 : 0;
                if (version == 4 && (format & 1) != 0)
                    start += 4;
                if (start >= data.Length || data[start] > 3)
                    continue;

                int descriptor = start + (name == "TXXX" ? 1 : name == "SYLT" ? 6 : 4);
                int encoding = data[start];
                int terminatorSize = encoding == 1 || encoding == 2 ? 2 : 1;
                int descriptionEnd = FindTerminator(data, descriptor, terminatorSize);
                if (descriptionEnd < 0)
                    continue;
                Encoding textEncoding = TextEncoding(encoding, data, descriptor);
                int body = descriptionEnd + terminatorSize;
                if (name == "SYLT")
                {
                    if (synced == null && data[start + 4] == 2 && data[start + 5] == 1)
                        synced = ParseSynced(data, body, terminatorSize, textEncoding);
                    continue;
                }
                if (name == "TXXX")
                {
                    string key = Decode(data, descriptor, descriptionEnd, textEncoding).Trim().ToLowerInvariant();
                    if (key != "lyrics" && key != "syncedlyrics" && key != "unsyncedlyrics" &&
                        key != "lyrics_sync" && key != "lyrics_synced")
                        continue;
                }
                var timed = ParseLrc(Decode(data, body, data.Length, textEncoding));
                if (timed != null)
                    return timed;
            }
            return synced;
        }

        private static EmbeddedMp3Lyrics ParseLrc(string value)
        {
            var lines = new List<Line>();
            long offset = 0;
            using (var reader = new StringReader(value))
            {
                string row;
                while ((row = reader.ReadLine()) != null)
                {
                    row = row.Trim();
                    Match offsetMatch = Offset.Match(row);
                    if (offsetMatch.Success)
                    {
                        int parsed;
                        if (int.TryParse(offsetMatch.Groups[1].Value, NumberStyles.Integer,
                            CultureInfo.InvariantCulture, out parsed))
                            offset = parsed;
                        continue;
                    }
                    Match stamp = LineTime.Match(row);
                    if (!stamp.Success)
                        continue;
                    var times = new List<long>();
                    int next = 0;
                    while (stamp.Success)
                    {
                        times.Add(Time(stamp));
                        next = stamp.Index + stamp.Length;
                        stamp = LineTime.Match(row, next);
                    }
                    Line line = ParseLrcLine(row.Substring(next).Trim(), times[0]);
                    if (line.Text.Length == 0)
                        continue;
                    foreach (long time in times)
                        lines.Add(new Line { Time = time, Text = line.Text, Words = line.Words });
                }
            }
            if (lines.Count == 0)
                return null;
            foreach (Line line in lines)
                line.Time += offset;
            return new EmbeddedMp3Lyrics(lines);
        }

        private static Line ParseLrcLine(string content, long time)
        {
            var line = new Line { Time = time };
            var text = new StringBuilder();
            int next = 0;
            long? wordTime = null;
            foreach (Match mark in WordTime.Matches(content))
            {
                AppendWord(line, text, content.Substring(next, mark.Index - next), wordTime);
                wordTime = Math.Max(0, Time(mark) - time);
                next = mark.Index + mark.Length;
            }
            AppendWord(line, text, content.Substring(next), wordTime);
            line.Text = text.ToString().TrimEnd();
            return line;
        }

        private static void AppendWord(Line line, StringBuilder text, string fragment, long? time)
        {
            if (text.Length == 0)
                fragment = fragment.TrimStart();
            string trimmed = fragment.Trim();
            if (time.HasValue && trimmed.Length > 0)
            {
                line.Words.Add(new Word
                {
                    Time = time.Value,
                    Start = text.Length + fragment.Length - fragment.TrimStart().Length,
                    Length = trimmed.Length,
                });
            }
            text.Append(fragment);
        }

        private static EmbeddedMp3Lyrics ParseSynced(byte[] data, int body, int terminatorSize, Encoding encoding)
        {
            var lines = new List<Line>();
            while (body < data.Length)
            {
                int end = FindTerminator(data, body, terminatorSize);
                if (end < 0 || data.Length - end - terminatorSize < 4)
                    break;
                string text = Decode(data, body, end, encoding).Trim();
                long time = BigEndian(data, end + terminatorSize);
                if (text.Length > 0)
                    lines.Add(new Line { Time = time, Text = text });
                body = end + terminatorSize + 4;
            }
            return lines.Count > 0 ? new EmbeddedMp3Lyrics(lines) : null;
        }

        private static long Time(Match match)
        {
            long minutes = long.Parse(match.Groups[1].Value, CultureInfo.InvariantCulture);
            decimal seconds = decimal.Parse(match.Groups[2].Value.Replace(',', '.'), CultureInfo.InvariantCulture);
            return minutes * 60000 + (long)(seconds * 1000);
        }

        private static int FindTerminator(byte[] bytes, int start, int size)
        {
            for (int index = start; index <= bytes.Length - size; index += size)
            {
                if (bytes[index] == 0 && (size == 1 || bytes[index + 1] == 0))
                    return index;
            }
            return -1;
        }

        private static Encoding TextEncoding(int type, byte[] data, int start)
        {
            switch (type)
            {
                case 0: return Encoding.GetEncoding(28591);
                case 1: return start + 1 < data.Length && data[start] == 0xfe && data[start + 1] == 0xff
                    ? Encoding.BigEndianUnicode : Encoding.Unicode;
                case 2: return Encoding.BigEndianUnicode;
                default: return Encoding.UTF8;
            }
        }

        private static string Decode(byte[] data, int start, int end, Encoding encoding)
        {
            if (end - start >= 2 && (encoding == Encoding.Unicode || encoding == Encoding.BigEndianUnicode))
            {
                if (data[start] == 0xfe && data[start + 1] == 0xff)
                    return Encoding.BigEndianUnicode.GetString(data, start + 2, end - start - 2).TrimEnd('\0');
                if (data[start] == 0xff && data[start + 1] == 0xfe)
                    return Encoding.Unicode.GetString(data, start + 2, end - start - 2).TrimEnd('\0');
            }
            return encoding.GetString(data, start, end - start).Trim('\0', '\ufeff');
        }

        private static byte[] RemoveUnsync(byte[] bytes)
        {
            int length = 0;
            for (int index = 0; index < bytes.Length; index++)
            {
                byte value = bytes[index];
                bytes[length++] = value;
                if (value == 0xff && index + 1 < bytes.Length && bytes[index + 1] == 0)
                    index++;
            }
            Array.Resize(ref bytes, length);
            return bytes;
        }

        private static uint BigEndian(byte[] bytes, int start) =>
            (uint)bytes[start] << 24 | (uint)bytes[start + 1] << 16 |
            (uint)bytes[start + 2] << 8 | bytes[start + 3];

        private static int SyncSafe(byte[] bytes, int start)
        {
            if (((bytes[start] | bytes[start + 1] | bytes[start + 2] | bytes[start + 3]) & 0x80) != 0)
                return -1;
            return bytes[start] << 21 | bytes[start + 1] << 14 | bytes[start + 2] << 7 | bytes[start + 3];
        }
    }
}
