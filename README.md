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
