# MusicBee companion

This is the single MusicBee plugin for Taskbar Media Presence. It is an original implementation built on MusicBee's official plugin API and Microsoft's official System Media Transport Controls API. It does not include code from `mb_MediaControl` or any other third-party MusicBee plugin.

It provides:

- title, artist, album, centre-cropped artwork, playback state and timeline to Windows;
- previous, play/pause, next, seek, shuffle and repeat requests from Windows;
- MusicBee's internal volume and mute through the private local Taskbar Media Presence pipe;
- guarded cold-start retries so an unfinished MusicBee restore is never published as `Untitled`;
- clean session and temporary-artwork removal when MusicBee closes or disables the plugin.

## Install

1. Obtain `mb_TaskbarMediaPresence.dll` from the project's GitHub release or from `..\build\musicbee` after a local build.
2. For a downloaded DLL, right-click it, choose **Properties**, and select **Unblock** if Windows shows that option.
3. In MusicBee, open **Edit > Preferences > Plugins**, choose **Add Plugin**, and select the DLL. Use this method for the Microsoft Store edition; do not copy files into its protected WindowsApps folder.
4. Remove the old `mb_MediaControl.dll` and `mb_TaskbarVolumeBridge.dll` if present. Uninstall listed copies from the same Plugins page. For a manual or portable installation, close MusicBee and remove those DLLs from that installation's `Plugins` folder. Keeping either one creates duplicate or stale Windows media sessions.
5. Restart MusicBee and confirm **Taskbar Media Presence** is enabled under **Edit > Preferences > Plugins**.

Only this one DLL is needed. It does not need a bot token, Discord secret, cloud service, or network access at runtime.

## Runtime model

MusicBee notifications, Windows media-control callbacks, artwork completions, and local volume requests are serialized on one background worker. The one-second status timer only coalesces a refresh onto that worker; it never calls MusicBee directly. Pipe requests have a two-second execution bound. Shutdown stops the timer and pipe, disposes the Windows media session on its owner worker, cancels queued work, and waits a bounded time for both background threads. Both threads are marked as background safeguards, so a stalled external API cannot keep MusicBee running.

## Upgrade

Download and unblock the new DLL, use **Edit > Preferences > Plugins > Add Plugin** again, accept the replacement, and restart MusicBee. For a manual or portable installation, close MusicBee before replacing `mb_TaskbarMediaPresence.dll` in its `Plugins` folder.

## Uninstall

Select **Taskbar Media Presence** under **Edit > Preferences > Plugins**, choose **Uninstall**, and restart MusicBee. If a manually installed DLL remains, close MusicBee and remove `mb_TaskbarMediaPresence.dll` from that installation's `Plugins` folder.

## Build

Run `build.ps1` in this directory. The build targets .NET Framework 4.8 and x86, downloads only MusicBee's official `MusicBeeInterface.cs` contract, verifies its pinned SHA-256 before compiling, discovers the installed Windows SDK, and writes the deterministic artifact name:

```text
..\build\musicbee\mb_TaskbarMediaPresence.dll
```

You can pass `-MusicBeeSdkPath <path>` to use an already downloaded copy of the pinned official MusicBee interface file. The build fails closed if that file's SHA-256 differs from the reviewed contract.
