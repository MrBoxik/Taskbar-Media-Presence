# MusicBee Volume Bridge

This companion lets Taskbar Media Presence control MusicBee's internal player volume instead of the Windows per-application mixer volume.

## Install

1. Open **MusicBee > Edit > Preferences > Plugins**.
2. Click **Add Plugin**.
3. Select `..\build\musicbee\mb_TaskbarVolumeBridge.dll` from this project.
4. Restart MusicBee.

The plugin uses MusicBee's official `Player_GetVolume`, `Player_SetVolume`, `Player_GetMute`, and `Player_SetMute` APIs. It exposes only those operations through a local named pipe. It does not access the music library, network, Discord, or Music Presence.

## Build

Run `build.ps1` in this directory. The project targets .NET Framework 4.8 and x86 for the Microsoft Store x86 MusicBee installation. The script retrieves the official MusicBee interface source and outputs `..\build\musicbee\mb_TaskbarVolumeBridge.dll`.
