# Taskbar Media Presence 1.0.0

[![Support on Buy Me a Coffee](https://img.shields.io/badge/Support-Buy%20Me%20a%20Coffee-FFDD00?logo=buymeacoffee&logoColor=000000)](https://buymeacoffee.com/mrboxik)
[![License: MIT](https://img.shields.io/badge/License-MIT-blue.svg)](LICENSE)

Taskbar Media Presence is a Windows 11 Windhawk mod that puts an interactive music player directly on the taskbar. It uses Windows Global System Media Transport Controls (GSMTC), so one widget can work with MusicBee, Media Player, Spotify, browsers, and other applications that publish a Windows media session.

## Features

- Album art, title, artist, Previous, Play/Pause, Next, Shuffle, Repeat, and a dynamic speaker icon.
- Per-application volume without changing Windows master volume.
- A single original MusicBee companion for its media session and exact internal player volume.
- Automatic source selection or a preferred application selected from the right-click **Media source** menu.
- One selected monitor or an interactive mirrored widget on every taskbar.
- After-apps, left, adaptive middle/far-left, tray-side, and custom placement.
- One-way marquee, bounce, or fixed ellipsis for long titles.
- Transparent widget and transparent Windows taskbar toggles.
- Optional Discord Rich Presence with timeline progress and matched HTTPS artwork.

The widget intentionally has no visualizer or Stop control.

## Requirements

- Windows 11 with the modern XAML taskbar.
- [Windhawk](https://windhawk.net/).
- A player that publishes a Windows GSMTC/SMTC session.

Taskbar internals can change in future Windows builds. The mod fails closed when it cannot safely identify the current taskbar structure instead of guessing an Explorer pointer.

## Install the Windhawk mod

After the mod is accepted into the Windhawk repository, install **Taskbar Media Presence** from Windhawk's **Explore** page.

For a local test build:

1. In Windhawk, choose **Create a new mod**.
2. Replace the sample with [`taskbar-media-presence.wh.cpp`](taskbar-media-presence.wh.cpp).
3. Choose **Compile Mod**, then enable it.
4. Play media and right-click the widget to select a source, position, or monitor.

## MusicBee: install the single companion

MusicBee needs the companion if it does not already publish a reliable Windows media session, and for the taskbar slider to change MusicBee's own internal volume.

1. Download [`mb_TaskbarMediaPresence.dll`](https://github.com/MrBoxik/Taskbar-Media-Presence/releases/latest/download/mb_TaskbarMediaPresence.dll).
2. Right-click the downloaded DLL, choose **Properties**, and select **Unblock** if Windows shows that option.
3. In MusicBee, open **Edit > Preferences > Plugins**, choose **Add Plugin**, and select the downloaded DLL. Use this method for the Microsoft Store edition; do not copy files into its protected WindowsApps folder.
4. Remove both legacy plugins if present: `mb_MediaControl.dll` and `mb_TaskbarVolumeBridge.dll`. Uninstall listed copies from the same Plugins page. For a manual or portable installation, close MusicBee and remove those DLLs from that installation's `Plugins` folder.
5. Restart MusicBee and confirm **Taskbar Media Presence** is enabled under **Edit > Preferences > Plugins**.

Only `mb_TaskbarMediaPresence.dll` is needed. It is an original implementation based on MusicBee's official plugin interface and Microsoft's SMTC APIs; it does not contain code from `mb_MediaControl`, Music Presence, or another third-party plugin.

The companion provides metadata, centre-cropped artwork, playback state, timeline, seeking, Shuffle/Repeat, transport commands, and MusicBee's internal volume over a current-user-only local named pipe.

### Upgrade or uninstall the MusicBee companion

- To upgrade, download and unblock the new DLL, use **Edit > Preferences > Plugins > Add Plugin** again, accept the replacement, and restart MusicBee. For a manual or portable install, close MusicBee before replacing the DLL in its `Plugins` folder.
- To uninstall, select **Taskbar Media Presence** under **Edit > Preferences > Plugins**, choose **Uninstall**, and restart MusicBee. If a manually installed DLL remains, close MusicBee and remove `mb_TaskbarMediaPresence.dll` from that installation's `Plugins` folder.

## Controls and source selection

- Click the speaker again while its flyout is open to close it.
- Drag upward for 100% and downward for 0%, or use the mouse wheel in 2% steps.
- Repeat cycles Off → Repeat all → Repeat one.
- Shuffle toggles on/off.
- Right-click **Media source** to choose **Automatic** or a specific active application. The selected source drives both the taskbar widget and Discord presence.
- Right-click **Monitor** to use one numbered monitor or every monitor.

For non-MusicBee players, volume is controlled through that application's Windows audio session. The mod searches every active output device and matches packaged identities and common Media Player process aliases. An application that separates playback into an unrelated process may expose transport controls without exposing a matchable volume session.

## Positioning

**After applications** follows the last real taskbar button and reserves space on a left-aligned taskbar. On a centered Windows taskbar it avoids moving the centered app group and falls back to the free physical left area when the widget would collide with the tray.

The **Adaptive middle / free far-left** preset uses:

- a true centre overlay when Windows taskbar buttons are left aligned;
- the free far-left area when Windows taskbar buttons are centered.

Use **Custom** for detailed taskbar/tray anchors and an X/Y offset.

## Discord Rich Presence

Discord publishing is disabled by default and is strictly opt-in. When enabled, it uses the included public Application ID unless you replace it. No bot, token, OAuth secret, or account authorization is required.

When both Discord presence and **Look up album artwork online** are enabled, the mod publishes the selected song with the fallback asset and searches Apple Music, Deezer, and MusicBrainz/Cover Art Archive for a strictly matched HTTPS cover. No catalog lookup occurs while Discord presence is disabled. Turn off the artwork option to keep the current title, artist, and album from being sent to those catalogs while still using Discord presence.

Discord controls the `Listening to <application>` header from the application's name in the [Discord Developer Portal](https://discord.com/developers/applications). A local Rich Presence payload cannot replace that header. **Song detail template** changes the main song line and supports `{title}`, `{artist}`, `{album}`, and `{app}`.

To use a custom Discord application:

1. Create it in the Discord Developer Portal and copy its numeric Application ID.
2. Upload [`assets/taskbar_media_presence.png`](assets/taskbar_media_presence.png) under **Rich Presence > Art Assets** with the key `taskbar_media_presence`.
3. Enter the Application ID and fallback asset key in the mod's Discord settings.

New Discord assets can take several minutes to become available.

## Troubleshooting

- If the widget is missing during sign-in, allow a few seconds for Explorer and the Windows media broker to finish starting. Version 1.0 retries both safely without needing a Windhawk off/on cycle.
- If MusicBee shows stale or duplicate sessions, close it, remove both legacy plugin DLLs, and keep only `mb_TaskbarMediaPresence.dll`.
- If MusicBee reports that the companion is blocked or does not load, close MusicBee, open the downloaded DLL's **Properties**, select **Unblock**, and install it again with **Add Plugin**.
- If a player appears but volume does not work, verify that it has an active entry in Windows Volume Mixer and that its audio process belongs to the same application identity as its media session.
- If multiple applications are playing, choose one under **Media source** instead of **Automatic**.
- Enable **Advanced / troubleshooting > Dump XAML element names** only when collecting a diagnostic log.

## Build

`build.ps1` uses the installed Windhawk compiler and derives the artifact version from the source metadata:

```powershell
.\build.ps1 -Architecture 64
.\build.ps1 -Architecture arm64
```

Use `-Architecture all` to verify both targets in one pass. The public mod uses Windhawk's `x86-64` architecture metadata; for the predefined `explorer.exe` target, Windhawk maps that metadata to the native ARM64 build on ARM64 Windows.

`MusicBeeVolumeBridge\build.ps1` builds the deterministic x86/.NET Framework 4.8 companion against MusicBee's official `MusicBeeInterface.cs` contract:

```powershell
.\MusicBeeVolumeBridge\build.ps1
```

Artifacts are written under `build` and are intentionally not committed.

## Attribution and license

Taskbar Media Presence is maintained by [MrBoxik](https://github.com/MrBoxik). If it is useful to you, [support the project](https://buymeacoffee.com/mrboxik).

This project is an attributed derivative of [Taskbar Fluent Media Player](https://github.com/Salyts/Taskbar-Fluent-Media-Player) by Salyts. It is distributed under the [MIT License](LICENSE). The full license notice is also embedded in the single-file Windhawk source submitted to the Windhawk repository.
