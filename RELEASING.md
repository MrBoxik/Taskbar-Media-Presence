# Release and Windhawk submission guide

This guide is for the project maintainer. Normal users install the mod from Windhawk's **Explore** page and do not need these steps.

## 1. Finish the project release

1. Merge the reviewed `agent/release-1.0.10` pull request into `main`.
2. From a clean checkout of `main`, verify the version in `taskbar-media-presence.wh.cpp` and run:

   ```powershell
   .\build.ps1 -Architecture all
   .\MusicBeeVolumeBridge\build.ps1
   git diff --check
   ```

3. Create a GitHub release with tag `v1.0.10` and title `Taskbar Media Presence 1.0.10`.
4. Attach `build\musicbee\mb_TaskbarMediaPresence.dll` with that exact filename. The README's MusicBee download link depends on it.
5. Mention that the Windhawk catalog listing is installed separately from Windhawk and that the DLL is needed only by MusicBee users who want the companion features.

Do not attach a hand-built or edited DLL. Always publish the artifact produced from the tagged source.

## 2. Fork the official Windhawk repository

Open <https://github.com/ramensoftware/windhawk-mods> while signed in as `MrBoxik`, select **Fork**, and create `MrBoxik/windhawk-mods`.

Alternatively, with GitHub CLI:

```powershell
gh repo fork ramensoftware/windhawk-mods --clone
cd windhawk-mods
git remote -v
git switch -c add-taskbar-media-presence
```

If the fork already exists, clone it and add the official repository as `upstream`:

```powershell
gh repo clone MrBoxik/windhawk-mods
cd windhawk-mods
git remote add upstream https://github.com/ramensoftware/windhawk-mods.git
git fetch upstream
git switch -c add-taskbar-media-presence upstream/main
```

## 3. Add exactly one Windhawk mod file

Copy the reviewed source to this exact path in the fork:

```text
mods/taskbar-media-presence.wh.cpp
```

The official new-mod pull request must contain only that one new file. Do not add the project README, MusicBee DLL, custom companion license, screenshots, build outputs, or other files to the Windhawk repository.

Before committing, verify:

- the filename matches `@id taskbar-media-presence`;
- `@github` is `https://github.com/MrBoxik` and the PR is opened by `MrBoxik`;
- `@version` is `1.0.10`;
- `@license` remains `MIT`, preserving the Salyts and MrBoxik notices embedded in the source;
- the diff contains only `mods/taskbar-media-presence.wh.cpp`.

Then commit and push:

```powershell
git add -- mods/taskbar-media-presence.wh.cpp
git diff --cached --check
git diff --cached --name-only
git commit -m "Add Taskbar Media Presence 1.0.10"
git push -u origin add-taskbar-media-presence
```

## 4. Open the official pull request

Open a pull request from `MrBoxik:add-taskbar-media-presence` to `ramensoftware/windhawk-mods:main`.

Keep the official pull-request template. For this first submission:

- leave the update-only changelog section empty or state that this is the initial catalog submission;
- under **Mod authorship**, select **The submitter, with AI assistance** and **ChatGPT**;
- briefly state that the mod is based on Taskbar Fluent Media Player and retains its MIT notice;
- state that both x64 and ARM64 builds and the official validation script passed.

Do not mark **The submitter, without AI assistance**.

## 5. Wait for review

Let the official CI checks finish. If a check or reviewer requests a change, update only `mods/taskbar-media-presence.wh.cpp`, keep `@version` consistent, push the fix to the same branch, and reply to the reviewer. Do not open a second pull request for the same submission.

After the official pull request is merged, the mod becomes available through Windhawk's catalog. Future updates use the same file, must increase `@version`, and should use a commit message that describes the new version because Windhawk uses it for the changelog.
