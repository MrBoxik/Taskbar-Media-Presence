# Taskbar Media Presence 0.10.1

[![Support on Buy Me a Coffee](https://img.shields.io/badge/Support-Buy%20Me%20a%20Coffee-FFDD00?logo=buymeacoffee&logoColor=000000)](https://buymeacoffee.com/mrboxik)

Taskbar Media Presence is a Windows 11 Windhawk mod that embeds a long music controller in the taskbar. It reads Windows Global System Media Transport Controls (GSMTC), so MusicBee works through `mb_MediaControl`/SMTC. It can also publish the current song to Discord Desktop by itself, without the separate Music Presence application.

The default widget includes:

- album art, song title, and artist;
- Shuffle, Repeat, Previous, Play/Pause, Next, and dynamic Volume controls;
- a compact vertical volume flyout with 100% at the top and 0% at the bottom;
- exact control of MusicBee's own internal player volume through the included companion plugin;
- Windows per-app volume control across all active output devices, including packaged players such as Windows Media Player;
- a top-level transparent-background toggle in the right-click menu;
- an independent transparent-Windows-taskbar toggle that applies to every monitor;
- a true one-way title marquee, optional bounce, or a fixed `...` ellipsis mode;
- one selectable monitor or a mirrored interactive widget on every monitor;
- Left, After applications, Middle, Right, and Custom position presets;
- built-in Discord Rich Presence with real track progress, customizable activity naming, multi-catalog artwork lookup, and a project-owned fallback icon.

The visualizer has been completely removed. It did not reliably represent the selected song and needlessly increased complexity and resource use.

## Install in Windhawk

1. Open Windhawk and choose **Create a new mod**.
2. Replace the example source with the contents of `taskbar-media-presence.wh.cpp`.
3. Click **Compile Mod**, then enable **Taskbar Media Presence**.
4. Start a song in MusicBee. If its title and artist appear in Windows media controls, the required media session is configured correctly.

The DLLs under `build` are local verification artifacts. Installing from the source lets Windhawk register the settings and compile for your system.

## Install the MusicBee internal-volume bridge

MusicBee's internal player volume is separate from its Windows audio-session volume. To control the same slider shown inside MusicBee:

1. Open **MusicBee > Edit > Preferences > Plugins**.
2. Choose **Add Plugin** and select `build\musicbee\mb_TaskbarVolumeBridge.dll`.
3. Restart MusicBee.

The bridge is a small original plugin built against MusicBee's official plugin interface. It only exposes MusicBee's volume and mute methods locally to this taskbar widget. It does not contain Music Presence code.

If the bridge is missing, mouse-wheel control can still use MusicBee's official `/VolumeUp` and `/VolumeDown` commands, which move in 10% steps. The exact slider and 2% steps require the bridge.

## Controls

- Click the taskbar speaker button to open the small vertical slider.
- For MusicBee, the slider and wheel change MusicBee's internal volume by 2% when the bridge is installed. Windows master volume is never changed.
- The taskbar speaker icon updates to full, low, or muted as the volume changes.
- Right-click the player to toggle **Transparent media widget** and **Transparent taskbar**, or select **Position** and **Monitor** directly. The unused playback, session-switching, and app-launch menu entries were removed.
- Double-click album art to open the media application.
- Shuffle toggles on/off and highlights when active. Repeat cycles Off → Repeat all → Repeat one, changing its icon on every click. The standard transport buttons remain Previous, Play/Pause, and Next.

## Long title behavior

Under **Main settings > Text area > Scroll mode**:

- **One-way loop** moves the full title from right to left. It completely exits on the left, waits for the configured interval, and then re-enters from the right; it never reverses direction or duplicates the text.
- **No movement; end with ...** keeps the title still and trims only text that does not fit.
- **Bounce back and forth** remains available for users who prefer the older behavior.

## Position and monitor settings

The common choices are also available immediately under the widget's right-click **Position** and **Monitor** submenus.

Under **Main settings > Media player**:

- **Taskbar monitor mode = Only selected monitor** displays one widget. Monitor 1 is primary; 2 and above are secondary taskbars ordered left to right.
- **Taskbar monitor mode = All monitors** creates a separate interactive widget on every Windows taskbar.
- **Immediately after taskbar applications** is the default and reserves enough taskbar space to avoid covering app buttons.
- **Left side before Start** and **Right side before system tray** also reserve space.
- **Middle** is an overlay.
- **Custom** exposes detailed taskbar/tray anchors and an X/Y pixel offset.

After physically adding or removing a monitor, reapply the mod settings or re-enable the mod so Explorer's taskbar list is rediscovered.

## Transparent Windows taskbar

Enable **Appearance settings > Taskbar Appearance > Transparent taskbar**, or use the widget's right-click **Transparent taskbar** command. It hides the Windows 11 XAML taskbar background and border on every monitor without making the Start button, pinned applications, tray, clock, or media widget invisible. The normal taskbar background is restored when the option is disabled or the mod unloads.

This is separate from **Transparent media widget**, which affects only the music controller. Other taskbar styling tools such as TranslucentTB or Windows 11 Taskbar Styler can target the same background, so use only one of them to control taskbar transparency at a time.

## Discord Rich Presence

The widget contains its own small local Discord publisher. It does not depend on Music Presence and does not use any Music Presence source code or Discord application identity.

The included Taskbar Media Presence Application ID (`1528896038163710112`) works by default. To use a different Discord application:

1. Open the [Discord Developer Portal](https://discord.com/developers/applications) and create an application.
2. On **General Information**, copy the numeric **Application ID**.
3. Open this mod's Windhawk settings, expand **Discord Presence**, replace **Discord Application ID**, and save.

Keep the normal Discord desktop app running and start a song. The presence uses the Windows media timeline to show the real elapsed and total track time. While playing, Discord advances the progress automatically; paused tracks omit the moving timeline so they do not falsely continue counting.

**Activity name** controls the text after “Listening to”. It supports `{title}`, `{artist}`, and `{album}` placeholders or arbitrary text such as `;`. Leave it empty to use the registered Taskbar Media Presence application name. Whitespace-only names might be rejected by Discord.

Discord cannot use MusicBee's local thumbnail bytes because Rich Presence images must be reachable through HTTPS. The mod now searches three public catalogs in this order:

1. Apple Music/iTunes Search, requesting a 600×600 center crop.
2. Deezer, using its square album image.
3. MusicBrainz plus Cover Art Archive, but only when MusicBee supplies an album tag.

Every result must pass normalized title and artist checks. Album metadata ranks Apple and Deezer releases, while MusicBrainz requires both artist and album to match. This deliberately prefers the fallback icon over a confidently wrong cover. The Discord image has no hover text and no click URL.

Spotify and YouTube are intentionally not queried. Spotify's Web API requires authorization for all requests, and YouTube search requires a developer key and has a search quota. Shipping either credential inside a public Windhawk mod would expose it to every installation.

### Install the fallback/application icon

The original project icon is at `assets/taskbar_media_presence.png`. In the Discord Developer Portal for the Application ID used by the mod:

1. Upload it as the application's icon under **General Information**.
2. Open **Rich Presence > Art Assets** and upload the same PNG with the asset key `taskbar_media_presence`.
3. In Windhawk settings, set **Discord Presence > Fallback image asset key** to `taskbar_media_presence`.

Discord can take several minutes to process a newly uploaded Rich Presence asset. After that, any song not found by all three catalogs uses this icon instead of a question mark.

Music Presence achieves exact local covers by temporarily uploading a cropped copy to its own proxy service. This project intentionally does not reuse that service or its code. Exact local-only artwork would require a separately hosted upload proxy; the current implementation avoids silently uploading personal cover files to an unrelated host.

The Application ID and application name are public. No bot, bot token, OAuth secret, or Discord account authorization is needed. Discord uses the developer-application name as the activity name and can show the music activity alongside a running game.

## Compatibility

- Designed for the Windows 11 XAML taskbar. Internal taskbar symbols can change after Windows updates.
- The player must publish a GSMTC/SMTC media session.
- Exact MusicBee internal volume requires the included companion plugin. Other players use their Windows per-app audio session. Packaged application IDs are matched to their processes, and every active render device is searched so players routed away from the default speakers can still be controlled.
- Playback metadata and transport controls require the player to publish a Windows GSMTC/SMTC session. Shuffle and Repeat are enabled only when that player reports support for those operations.
- The Discord feature connects only to the local Discord desktop IPC endpoint and publishes title, artist, play/pause state, timestamps, and a cover URL. It does not log into Discord or call Discord's HTTP API.
- Online artwork lookup sends the current title, artist, and album to Apple and Deezer. MusicBrainz receives artist and album only when the first two catalogs fail. Disable lookup in Discord Presence settings if you prefer only the static uploaded asset. Exact matching deliberately favors the fallback over a wrong release.
- Music Presence is not bundled, modified, copied, or required. The local publisher in this project is an original implementation and uses the Application ID supplied by you.
- Mod metadata and documentation are English-only; no Russian localization files are included.

## Building locally

Run `build.ps1` from PowerShell. It uses the installed Windhawk compiler and writes 32-bit and 64-bit verification DLLs under `build`.

Run `MusicBeeVolumeBridge\build.ps1` to rebuild the MusicBee bridge. It downloads MusicBee's official interface source at build time and writes the plugin to `build\musicbee`.

## Attribution and license

Taskbar Media Presence is maintained by [MrBoxik](https://github.com/MrBoxik). If you enjoy the project, you can [support its development on Buy Me a Coffee](https://buymeacoffee.com/mrboxik).

This is an attributed derivative of [Taskbar Fluent Media Player](https://github.com/Salyts/Taskbar-Fluent-Media-Player) 1.5.0 by Salyts. The upstream Git history and MIT `LICENSE` are retained. No Music Presence source code was copied or incorporated.
