// ==WindhawkMod==
// @id              taskbar-media-presence
// @name            Taskbar Media Presence
// @description     Taskbar music controls with album art, per-app volume, multi-monitor placement, and Discord Rich Presence.
// @version         0.10.1
// @author          MrBoxik; based on Taskbar Fluent Media Player by Salyts
// @github          https://github.com/MrBoxik
// @homepage        https://github.com/MrBoxik/Taskbar-Media-Presence
// @include         explorer.exe
// @compilerOptions -lole32 -loleaut32 -lruntimeobject -lversion -luuid -luser32 -lwindowsapp -lshell32 -lgdi32 -lshlwapi -lwindowscodecs -ldwmapi -lshcore -lksuser -lcomctl32 -lwinhttp
// ==/WindhawkMod==

// ==WindhawkModReadme==
/*
# Taskbar Media Presence 0.10.1

A compact Windows 11 taskbar player for any application that publishes a Windows media session.

## Highlights

- Album art, title, artist, Shuffle, Repeat, Previous, Play/Pause, Next, and per-app volume.
- MusicBee internal-volume control through the included optional companion plugin.
- Selected-monitor or all-monitor placement with safe taskbar-space reservation.
- One-way title marquee, ellipsis, and bounce modes.
- Transparent widget and transparent Windows taskbar options.
- Built-in Discord Rich Presence with progress and matched online artwork.

## Compatibility

The player must expose a GSMTC/SMTC media session. Shuffle and Repeat appear disabled when the media application does not support them. MusicBee needs `mb_MediaControl`/SMTC for media controls and the Taskbar Media Presence Volume Bridge for its internal volume slider. Other players use their Windows per-application audio session.

## Links

- **[Source code and documentation](https://github.com/MrBoxik/Taskbar-Media-Presence)**
- **[Report a bug or request a feature](https://github.com/MrBoxik/Taskbar-Media-Presence/issues)**
- **[Support the project](https://buymeacoffee.com/mrboxik)**

## Credits

Created and maintained by **[MrBoxik](https://github.com/MrBoxik)**. Based on **[Taskbar Fluent Media Player](https://github.com/Salyts/Taskbar-Fluent-Media-Player)** by Salyts and distributed under the MIT License.
*/
// ==/WindhawkModReadme==

// ==WindhawkModSettings==
/*
- MainSettings:
  - PlayerSetting:
    - taskbarMode: "selected"
      $name: Taskbar monitor mode
      $description: Show one widget on the selected monitor, or mirror a working widget on every Windows taskbar.
      $options:
      - "selected": "Only selected monitor"
      - "all": "All monitors"
    - taskbarNumber: 1
      $name: Taskbar monitor number
      $description: Used in Only selected monitor mode. 1 is primary; 2 and above are secondary taskbars ordered left to right.
    - positionPreset: "apps"
      $name: Position preset
      $description: Next to apps, Left, and Right reserve taskbar space. Middle is an overlay. Choose Custom to use the detailed anchor and offset below.
      $options:
      - "left": "Left side before Start (no app overlap)"
      - "apps": "Immediately after taskbar applications (no overlap)"
      - "middle": "Middle of taskbar (overlay)"
      - "right": "Right side before system tray (no app overlap)"
      - "custom": "Custom anchor"
    - position: "taskbar_after_apps"
      $name: Custom position anchor
      $description: Used only when Position preset is Custom. Overlay choices can cover taskbar apps; tracked and tray choices reserve space.
      $options:
      - "taskbar_left_edge": "Taskbar - Left edge (Overlay)"
      - "taskbar_center_edge": "Taskbar - Center (Overlay)"
      - "taskbar_right_edge": "Taskbar - Right edge (Overlay)"
      - "taskbar_left_start": "Taskbar - Left of Start button"
      - "taskbar_right_start": "Taskbar - Right of Start button"
      - "taskbar_after_apps": "Taskbar - After application buttons"
      - "taskbar_after_search_left": "Taskbar - Left of Search button"
      - "taskbar_after_search_right": "Taskbar - Right of Search button"
      - "taskbar_after_taskview_left": "Taskbar - Left of Task View button"
      - "taskbar_after_taskview_right": "Taskbar - Right of Task View button"
      - "taskbar_after_widgets_left": "Taskbar - Left of Widgets button"
      - "taskbar_after_widgets_right": "Taskbar - Right of Widgets button"
      - "tray_left": "Tray - Far left"
      - "tray_right": "Tray - Far right"
      - "tray_before_clock": "Tray - Left of Clock"
      - "tray_after_clock": "Tray - Right of Clock"
      - "tray_before_omni_left": "Tray - Left of Network/Volume button"
      - "tray_before_omni_right": "Tray - Right of Network/Volume button"
      - "tray_language_left": "Tray - Left of Language button"
      - "tray_language_right": "Tray - Right of Language button"
      - "tray_icons_left": "Tray - Left of Tray Icons"
      - "tray_icons_right": "Tray - Right of Tray Icons"
      - "tray_hidden_icons_left": "Tray - Left of Hidden icons button"
      - "tray_hidden_icons_right": "Tray - Right of Hidden icons button"
      - "tray_after_showdesktop_left": "Tray - Left of Show Desktop"
      - "tray_after_showdesktop_right": "Tray - Right of Show Desktop"
    - customOffset: "0 0"
      $name: Custom offset (X Y)
      $description: Used with Custom position. Moves the widget horizontally and vertically in pixels after applying the selected anchor.
    - playerWidth: "460 460"
      $name: Media player width (min max)
      $description: The first number is the minimum size, and the second is the maximum. You can also set it to 0, which means no limit.
    - playerHeight: "40 40"
      $name: Media player height (min max)
    - playerMargin: "4 4"
      $name: Media player margin (left right)
      $description: The first number is the distance to the left, and the second is to the right.
    - mirrorLayout: false
      $name: Mirror layout
      $description: Album art, text, and buttons will be displayed on the opposite side
    $name: Media player

  - AlbumArtSetting:
    - showAlbumArt: true
      $name: Show album art
    - albumArtWidth: "36 36"
      $name: Album art width (min max)
    - albumArtHeight: "36 36"
      $name: Album art height (min max)
    - albumArtMargin: "0 0"
      $name: Album art margin (left right)
    $name: Album art

  - TextAreaSetting:
    - showTrackTitle: true
      $name: Show track title
    - showTrackArtist: true
      $name: Show artist name
    - textAreaWidth: "220 250"
      $name: Text area width (min max)
    - textAreaHeight: "0 0"
      $name: Text area height (min max)
    - textAreaMargin: "5 5"
      $name: Text area margin (left right)
    - textSpacing: -1
      $name: Spacing between title and artist
    - enableTitleScrolling: true
      $name: Enable track title scrolling
      $description: When enabled, the track title will scroll horizontally if it overflows the text area.
    - enableArtistScrolling: false
      $name: Enable artist name scrolling
      $description: When enabled, the artist name will scroll horizontally if it overflows the text area.
    - scrollSpeed: 1
      $name: Scroll speed (1-10)
      $description: Controls how fast the text scrolls. 1 = slowest, 10 = fastest.
    - scrollPauseDuration: 1000
      $name: Pause duration (ms)
      $description: How long the title remains still before a marquee pass, or at each edge in Bounce mode.
    - scrollMode: "marquee"
      $name: Scroll mode
      $description: One-way loop and Bounce use the scrolling toggles above. No movement overrides them and trims overflowing text with an ellipsis.
      $options:
      - "marquee": "One-way loop (exit left, enter right)"
      - "ellipsis": "No movement; end with ..."
      - "bounce": "Bounce back and forth"
    - loopGap: 40
      $name: Marquee gap (px)
      $description: Extra blank distance before the text re-enters from the right in One-way loop mode.
    - swapTitleArtist: false
      $name: Swap artist name and track title
    - emptyTitleText: "Untitled"
      $name: Title text when track has no name
      $description: Shown in the title field when a track is playing but has no title. Leave empty to hide the title text in this case.
    - noMediaTitleText: "Not Playing"
      $name: Title text when nothing is playing
      $description: Shown in the title field when there is no media session at all. Leave empty to hide the title text in this case.
    - emptyArtistText: ""
      $name: Artist text when track has no artist
      $description: Shown in the artist field when a track is playing but has no artist specified. Leave empty to hide the artist text in this case.
    - noMediaArtistText: ""
      $name: Artist text when nothing is playing
      $description: Shown in the artist field when there is no media session at all. Leave empty to hide the artist text in this case.
    $name: Text area

  - MediaButtonsSettings:
    - showMediaButtons: true
      $name: Show media buttons
    - mediaButtons: [shuffle, repeat, prev, play, next, volume]
      $name: Media buttons order
      $description: Select which media control buttons to display and their order. Duplicates are ignored.
      $options:
      - none: Nothing
      - prev: Previous Track
      - play: Play/Pause
      - next: Next Track
      - volume: Open media-app volume slider
      - rewind: Rewind 5s
      - forward: Forward 5s
      - shuffle: Toggle Shuffle
      - repeat: Toggle Repeat
      - switch_sessions: Switch Sessions
    - mediaButtonsMargin: "2 2"
      $name: Media buttons margin (left right)
    - buttonSize: 28
      $name: Button size
    - hideUnsupportedButtons: false
      $name: Hide unsupported buttons
      $description: When enabled, buttons for actions not supported by the current media session are completely hidden instead of shown as disabled.
    $name: Media buttons

  $name: Player

- AppearanceSettings:
  - BackgroundStyleSettings:
    - backgroundType: "acrylic"
      $name: Background type
      $options:
      - "none":           "None (transparent)"
      - "solid":          "Solid color"
      - "gradient":       "Gradient"
      - "acrylic":        "Acrylic"
      - "mica":           "Mica"
      - "mica_alt":       "Mica Alt"
      - "album_art_blur": "Blurred album cover"
    - solidColor: "35 35 35"
      $name: Background color (RGB)
      $description: "Use '-1 -1 -1' for the system contrast color and '-2 -2 -2' for the album art color. You can also specify two colors separated by a $ symbol (e.g., '0 0 0$255 255 255') where the first color is for light theme and the second for dark theme."
    - solidColor2: "35 35 35"
      $name: Gradient color 1 (RGB)
    - gradientColor2: "128 128 128"
      $name: Gradient color 2 (RGB)
    - solidOpacity: 100
      $name: Solid color opacity (0-100)
    - gradientAngle: 50
      $name: Gradient rotation angle (0-360)
    - gradientBalance: 50
      $name: Gradient color balance (0-100)
    - acrylicTintOpacity: 50
      $name: Acrylic tint opacity (0-100)
    - micaOpacity: 50
      $name: Mica/Mica Alt opacity (0-100)
    - blurOpacity: 65
      $name: Album art blur opacity (0-100)
    - blurRadius: 11
      $name: Album art blur strength (1-50)
    - cornerRadius: "4"
      $name: Media player corner radius
      $description: "Use single value (e.g., '4') for uniform corners, or four space-separated values (e.g., '4 2 4 2') for individual corners."
    - enablePlayerHoverEffect: "auto"
      $name: Player hover effect
      $options:
      - "auto":  "Auto (theme changes automatically)"
      - "black": "Black"
      - "white": "White"
      - "off":   "Disable hover effect"
    - enableMediaButtonsHoverEffect: "auto"
      $name: Media buttons hover effect
      $options:
      - "auto":  "Auto (theme changes automatically)"
      - "black": "Black"
      - "white": "White"
      - "off":   "Disable hover effect"
    $name: Background

  - TaskbarAppearanceSettings:
    - transparentTaskbar: false
      $name: Transparent taskbar
      $description: Makes the Windows taskbar background fully transparent on every monitor. This is independent from the media widget background and is restored when the option or mod is disabled.
    $name: Windows taskbar

  - MediaButtonsStyleSettings:
    - iconStyle: "fluent_outline"
      $name: Icon style
      $options:
      - "fluent_outline": "Segoe Fluent Icons (Outline)"
      - "fluent_filled":  "Segoe Fluent Icons (Filled)"
      - "mdl2_outline":   "Segoe MDL2 Assets (Outline)"
      - "mdl2_filled":    "Segoe MDL2 Assets (Filled)"
    - buttonSpacing: 0
      $name: Spacing between media buttons
    - buttonIconSize: 12
      $name: Button icon size
    - buttonCornerRadius: "4"
      $name: Media buttons corner radius
      $description: "Use single value (e.g., '4') for uniform corners, or four space-separated values (e.g., '4 2 4 2') for individual corners."
    - buttonColor: "0 0 0$255 255 255"
      $name: Media buttons icons color (RGB)
      $description: "Use '-1 -1 -1' for the system contrast color and '-2 -2 -2' for the album art color. You can also specify two colors separated by a $ symbol (e.g., '0 0 0$255 255 255') where the first color is for light theme and the second for dark theme."
    - buttonColorOpacity: 100
      $name: Media buttons icons opacity (0-100)
    $name: Media buttons

  - TitleTextStyleSettings:
    - titleColor: "0 0 0$255 255 255"
      $name: Title color (RGB)
      $description: "Use '-1 -1 -1' for the system contrast color and '-2 -2 -2' for the album art color. You can also specify two colors separated by a $ symbol (e.g., '0 0 0$255 255 255') where the first color is for light theme and the second for dark theme."
    - titleColorOpacity: 100
      $name: Title opacity (0-100)
    - titleFont: segoe_ui_variable
      $name: Title font
      $options:
      - segoe_ui_variable: Segoe UI Variable Display
      - segoe_ui:          Segoe UI
      - aptos:             Aptos
      - calibri:           Calibri
      - cambria:           Cambria
      - candara:           Candara
      - consolas:          Consolas
      - corbel:            Corbel
      - arial:             Arial
      - trebuchet:         Trebuchet MS
      - verdana:           Verdana
      - tahoma:            Tahoma
      - georgia:           Georgia
      - times_new_roman:   Times New Roman
      - custom:            Custom...
    - titleFontSize: 12
      $name: Title font size
    - titleFontFamily: ""
      $name: Title font family (for Custom option)
      $description: >-
        For a list of fonts that are shipped with Windows 11, refer to the
        following page:
        https://learn.microsoft.com/en-us/typography/fonts/windows_11_font_list
    - titleFontWeight: ""
      $name: Title font weight
      $options:
      - "":          Default
      - Thin:        Thin
      - ExtraLight:  Extra light
      - Light:       Light
      - SemiLight:   Semi light
      - Normal:      Normal
      - Medium:      Medium
      - SemiBold:    Semi bold
      - Bold:        Bold
      - ExtraBold:   Extra bold
      - Black:       Black
      - ExtraBlack:  Extra black
    - titleFontStyle: ""
      $name: Title font style
      $options:
      - "":       Default
      - Normal:   Normal
      - Oblique:  Oblique
      - Italic:   Italic
    - titleCharacterSpacing: 0
      $name: Title character spacing
      $description: Can be a positive or a negative number.
    $name: Title text

  - ArtistTextStyleSettings:
    - artistColor: "0 0 0$255 255 255"
      $name: Artist color (RGB)
      $description: "Use '-1 -1 -1' for system contrast color, '-2 -2 -2' for album art color. You can also specify two colors separated by a $ symbol (e.g., '0 0 0$255 255 255') where the first color is for light theme and the second for dark theme."
    - artistColorOpacity: 80
      $name: Artist opacity (0-100)
    - artistFont: segoe_ui_variable
      $name: Artist font
      $options:
      - segoe_ui_variable: Segoe UI Variable Display
      - segoe_ui:          Segoe UI
      - aptos:             Aptos
      - calibri:           Calibri
      - cambria:           Cambria
      - candara:           Candara
      - consolas:          Consolas
      - corbel:            Corbel
      - arial:             Arial
      - trebuchet:         Trebuchet MS
      - verdana:           Verdana
      - tahoma:            Tahoma
      - georgia:           Georgia
      - times_new_roman:   Times New Roman
      - custom:            Custom...
    - artistFontSize: 11
      $name: Artist font size
    - artistFontFamily: ""
      $name: Artist font family (for Custom option)
      $description: >-
        For a list of fonts that are shipped with Windows 11, refer to the
        following page:
        https://learn.microsoft.com/en-us/typography/fonts/windows_11_font_list
    - artistFontWeight: ""
      $name: Artist font weight
      $options:
      - "":          Default
      - Thin:        Thin
      - ExtraLight:  Extra light
      - Light:       Light
      - SemiLight:   Semi light
      - Normal:      Normal
      - Medium:      Medium
      - SemiBold:    Semi bold
      - Bold:        Bold
      - ExtraBold:   Extra bold
      - Black:       Black
      - ExtraBlack:  Extra black
    - artistFontStyle: ""
      $name: Artist font style
      $options:
      - "":       Default
      - Normal:   Normal
      - Oblique:  Oblique
      - Italic:   Italic
    - artistCharacterSpacing: 0
      $name: Artist character spacing
      $description: Can be a positive or a negative number.
    $name: Artist text

  - AlbumArtDisplaySettings:
    - albumArtEmptyBehavior: "show"
      $name: Album art behavior when no cover available
      $options:
      - "show":          "Show area"
      - "hide":          "Hide area"
      - "show_icon":     "Show area with icon"
    - emptyIconGlyph: "E189"
      $name: Icon glyph code (hex)
      $description: "Hex code of the glyph to show, e.g. 'E189' for music note. See https://learn.microsoft.com/en-us/windows/apps/design/iconography/segoe-ui-symbol-font"
    - emptyIconSize: 16
      $name: Icon size
    - emptyIconFont: "segoe_fluent"
      $name: Icon font style
      $options:
      - "segoe_fluent": "Segoe Fluent Icons"
      - "segoe_mdl2":   "Segoe MDL2 Assets"
    - emptyIconColor: "140 140 140"
      $name: Icon color (RGB)
      $description: "Use '-1 -1 -1' for the system accent color and '-2 -2 -2' for the album art color. You can also specify two colors separated by a $ symbol (e.g., '0 0 0$255 255 255') where the first color is for light theme and the second for dark theme."
    - emptyIconOpacity: 100
      $name: Icon opacity (0-100)
    - albumArtQuality: "medium"
      $name: Album art quality
      $options:
      - "low":    "Low (faster, less memory)"
      - "medium": "Medium (default)"
      - "high":   "High (best quality)"
    - showPauseOverlay: true
      $name: Show pause icon overlay on album art when paused
    - pauseOverlayIconSize: 16
      $name: Pause icon size
    - pauseOverlayOpacity: 60
      $name: Pause overlay background opacity (0-100)
    - albumArtOpacity: 100
      $name: Album art opacity (0-100)
    - albumArtCornerRadius: "4"
      $name: Album art corner radius
      $description: "Use single value (e.g., '4') for uniform corners, or four space-separated values (e.g., '4 2 4 2') for individual corners."
    - showAppIcon: false
      $name: Show media app icon overlay
    - appIconCorner: "bottom_right"
      $name: App icon corner
      $options:
      - "top_left":     "Top left"
      - "top_right":    "Top right"
      - "bottom_left":  "Bottom left"
      - "bottom_right": "Bottom right"
    - appIconSize: 12
      $name: App icon size
    $name: Album art

  $name: Appearance

- BehaviorSettings:
  - disableAlbumArtClick: false
    $name: Let clicks pass through album art
    $description: When enabled, the album art itself does not capture mouse clicks.
  - ClickActionSettings:
      - - object: player
          $name: Object
          $options:
          - none:       Nothing
          - player:     Player area
          - album_art:  Album art area
        - click: left_click
          $name: Click type
          $options:
          - none:                Nothing
          - left_click:          Left click
          - left_double_click:   Left double click
          - right_click:         Right click
          - right_double_click:  Right double click
          - middle_click:        Middle click
          - middle_double_click: Middle double click
        - action: play_pause
          $name: Action
          $options:
          - none:            Nothing
          - switch_session:  Switch active media session
          - play_pause:      Play/Pause
          - next_track:      Next track
          - prev_track:      Previous track
          - stop:            Stop playback
          - rewind_5s:       Rewind 5s
          - forward_5s:      Forward 5s
          - toggle_shuffle:  Toggle Shuffle
          - toggle_repeat:   Toggle Repeat
          - open_app:        Open media app
          - open_context_menu: Open context menu
      - - object: player
        - click: right_click
        - action: open_context_menu
      - - object: album_art
        - click: left_double_click
        - action: open_app
    $name: Click actions
  - MouseWheelActionSettings:
      - - object: player
          $name: Object
          $options:
          - none:       Nothing
          - player:     Player area
          - album_art:  Album art area
        - click: mouse_wheel
          $name: Mouse type
          $options:
          - none:             Nothing
          - mouse_wheel:      Mouse wheel
          - mouse_wheel_up:   Mouse wheel up
          - mouse_wheel_down: Mouse wheel down
        - action: app_sound
          $name: Action
          $options:
          - none:                      Nothing
          - "switch_tracks":           "Switch tracks"
          - "switch_tracks_inverted":  "Switch tracks (inverted)"
          - "switch_sessions":         "Switch sessions"
          - "app_sound":               "Change app sound volume"
      - - object: album_art
        - click: mouse_wheel
        - action: switch_sessions
    $name: Mouse-wheel actions
  - hideWhenNoMedia: true
    $name: Hide when no media is playing
  - hideFullscreen: true
    $name: Hide when a fullscreen app is running
  - idleHideSeconds: 0
    $name: Idle auto-hide timeout (seconds, 0 = disabled)
  - showFullTitleOnHover: true
    $name: Show full track title on hover (tooltip)
  $name: Behavior

- AnimationSettings:
  - enableSmoothPositionAnimation: true
    $name: Enable smooth position animation
  $name: Animation

- DiscordPresenceSettings:
  - enabled: true
    $name: Publish Discord Rich Presence
    $description: Publishes the current song directly to the running Discord desktop app. The project Application ID is included below and can be replaced.
  - applicationId: "1528896038163710112"
    $name: Discord Application ID
    $description: The Taskbar Media Presence application ID is included by default. You can replace it with another numeric Application ID. This value is public, not a secret.
  - showPaused: true
    $name: Show paused songs
  - activityName: "{title}"
    $name: Activity name
    $description: Replaces the name after Listening to. Use {title}, {artist}, or {album}, enter custom text such as a semicolon, or leave empty to use the registered Taskbar Media Presence application name. Discord may reject whitespace-only names.
  - fetchOnlineArtwork: true
    $name: Look up album artwork online
    $description: Searches Apple Music first, then Deezer, then MusicBrainz/Cover Art Archive. Strict title and artist checks avoid using an unrelated cover. Disable this to use only the static asset key below.
  - largeImageKey: "taskbar_media_presence"
    $name: Fallback image asset key
    $description: Asset key uploaded under your Discord application's Rich Presence assets. Used whenever every online catalog fails. Upload assets/taskbar_media_presence.png with this key.
  $name: Discord presence

- DebugSettings:
  - ignoredProcesses: ""
    $name: Ignore media from processes (separate with ; )
  - enableTreeDump: false
    $name: Dump XAML element names to log on inject
  - showDebugBorders: false
    $name: Show debug borders
  - showLayoutAnchors: false
    $name: Show layout anchors and centers
  $name: Advanced / troubleshooting
*/
// ==/WindhawkModSettings==

#undef GetCurrentTime

#include <winrt/base.h>
#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.Foundation.Collections.h>
#include <winrt/Windows.UI.Core.h>
#include <winrt/Windows.UI.Text.h>
#include <winrt/Windows.UI.Input.h>
#include <winrt/Windows.UI.Xaml.h>
#include <winrt/Windows.UI.Xaml.Controls.Primitives.h>
#include <winrt/Windows.UI.Xaml.Controls.h>
#include <winrt/Windows.UI.Xaml.Media.h>
#include <winrt/Windows.UI.Xaml.Media.Imaging.h>
#include <winrt/Windows.UI.Xaml.Shapes.h>
#include <winrt/Windows.UI.Xaml.Media.Animation.h>
#include <winrt/Windows.UI.Xaml.Markup.h>
#include <winrt/Windows.UI.Xaml.Interop.h>
#include <winrt/Windows.UI.Xaml.Input.h>
#include <winrt/Windows.UI.Xaml.Automation.h>
#include <winrt/Windows.UI.ViewManagement.h>
#include <winrt/Windows.Media.Control.h>
#include <winrt/Windows.Storage.Streams.h>
#include <winrt/Windows.Graphics.Imaging.h>
#include <robuffer.h>
#include <shcore.h>

#include <windows.h>
#include <appmodel.h>
#include <shellapi.h>
#include <shlobj.h>
#include <shlwapi.h>
#include <shobjidl.h>
#include <commoncontrols.h>
#include <wincodec.h>
#include <propsys.h>
#include <dwmapi.h>
#include <windhawk_utils.h>
#include <audiopolicy.h>
#include <mmdeviceapi.h>
#include <endpointvolume.h>
#include <audioclient.h>
#include <winhttp.h>

#include <propkey.h>

#include <atomic>
#include <functional>
#include <memory>
#include <utility>
#include <mutex>
#include <string>
#include <vector>
#include <set>
#include <algorithm>
#include <thread>
#include <cmath>
#include <chrono>
#include <cctype>
#include <cwctype>
#include <cstdio>
#include <cstring>

using namespace winrt::Windows::UI::Xaml;
using namespace winrt::Windows::UI::Xaml::Controls;
using namespace winrt::Windows::UI::Xaml::Media;
using namespace winrt::Windows::UI::Xaml::Media::Imaging;
using namespace winrt::Windows::UI::Xaml::Media::Animation;
using namespace winrt::Windows::UI::Xaml::Input;
using namespace winrt::Windows::Media::Control;
using namespace winrt::Windows::Storage::Streams;

struct ModSettings {
    std::wstring taskbarMode         = L"selected";
    int          taskbarNumber        = 1;
    std::wstring positionPreset       = L"apps";
    std::wstring position             = L"taskbar_after_apps";
    int          customOffsetX        = 0;
    int          customOffsetY        = 0;
    std::wstring albumArtLeftClick    = L"none";
    std::wstring albumArtRightClick   = L"none";
    std::wstring albumArtMiddleClick  = L"none";
    std::wstring albumArtLeftDoubleClick  = L"none";
    std::wstring albumArtRightDoubleClick = L"none";
    std::wstring albumArtWheelAction  = L"none";
    std::wstring playerLeftClick      = L"none";
    std::wstring playerRightClick     = L"none";
    std::wstring playerMiddleClick    = L"none";
    std::wstring playerLeftDoubleClick  = L"none";
    std::wstring playerRightDoubleClick = L"none";
    std::wstring playerWheelAction    = L"none";
    bool         mirrorLayout         = false;
    bool         showMediaButtons     = true;
    int          playerMinWidth       = 460;
    int          playerMaxWidth       = 460;
    int          playerMinHeight      = 40;
    int          playerMaxHeight      = 40;
    bool         showAlbumArt         = true;
    std::wstring albumArtEmptyBehavior = L"show";
    std::wstring emptyIconGlyph       = L"E189";
    int          emptyIconSize        = 16;
    std::wstring emptyIconFont        = L"segoe_fluent";
    std::wstring emptyIconColor       = L"255 255 255";
    int          emptyIconOpacity     = 100;
    std::wstring albumArtQuality      = L"medium";
    bool         showPauseOverlay     = true;
    int          pauseOverlayIconSize = 16;
    int          pauseOverlayOpacity  = 60;
    int          albumArtMinWidth     = 36;
    int          albumArtMaxWidth     = 36;
    int          albumArtMinHeight    = 36;
    int          albumArtMaxHeight    = 36;
    int          albumArtOpacity      = 100;
    int          albumArtLeftMargin   = 0;
    int          albumArtRightMargin  = 0;
    bool         showTrackTitle       = true;
    bool         showFullTitleOnHover = true;
    bool         showTrackArtist      = true;
    bool         swapTitleArtist      = false;
    std::wstring emptyTitleText       = L"Untitled";
    std::wstring noMediaTitleText     = L"Not Playing";
    std::wstring emptyArtistText      = L"";
    std::wstring noMediaArtistText    = L"";
    std::wstring iconStyle            = L"fluent_outline";
    bool         showAppIcon          = false;
    std::wstring appIconCorner        = L"bottom_right";
    int          appIconSize          = 12;
    bool         hideWhenNoMedia      = true;
    std::wstring playerHoverEffectMode = L"auto";
    std::wstring mediaButtonsHoverEffectMode = L"auto";
    bool         enableSmoothPositionAnimation = true;
    int          playerMarginLeft     = 4;
    int          playerMarginRight    = 4;
    int          mediaButtonsLeftMargin  = 2;
    int          mediaButtonsRightMargin = 2;
    int          textAreaMinWidth     = 220;
    int          textAreaMaxWidth     = 250;
    int          textAreaMinHeight    = 0;
    int          textAreaMaxHeight    = 0;
    int          textAreaLeftMargin   = 5;
    int          textAreaRightMargin  = 5;
    bool         hideFullscreen       = true;
    int          idleHideSeconds      = 0;
    std::wstring backgroundType       = L"acrylic";
    int          blurOpacity          = 65;
    int          blurRadius           = 11;
    double       cornerRadiusTL       = 4;
    double       cornerRadiusTR       = 4;
    double       cornerRadiusBR       = 4;
    double       cornerRadiusBL       = 4;
    double       albumArtCornerRadiusTL = 4;
    double       albumArtCornerRadiusTR = 4;
    double       albumArtCornerRadiusBR = 4;
    double       albumArtCornerRadiusBL = 4;
    int          buttonSpacing        = 0;
    int          buttonSize           = 28;
    int          buttonIconSize       = 12;
    double       buttonCornerRadiusTL = 4;
    double       buttonCornerRadiusTR = 4;
    double       buttonCornerRadiusBR = 4;
    double       buttonCornerRadiusBL = 4;
    int          titleFontSize        = 12;
    int          artistFontSize       = 11;
    std::wstring titleFont            = L"segoe_ui_variable";
    std::wstring artistFont           = L"segoe_ui_variable";
    std::wstring titleFontFamily      = L"";
    std::wstring artistFontFamily     = L"";
    std::wstring titleFontWeight      = L"";
    std::wstring artistFontWeight     = L"";
    std::wstring titleFontStyle       = L"";
    std::wstring artistFontStyle      = L"";
    int          titleCharacterSpacing  = 0;
    int          artistCharacterSpacing = 0;
    int          textSpacing          = -1;
    bool         enableArtistScrolling = false;
    bool         enableTitleScrolling = true;
    int          scrollSpeed          = 1;
    int          scrollPauseDuration  = 1000;
    std::wstring scrollMode           = L"marquee";
    int          loopGap              = 40;
    std::wstring solidColor           = L"35 35 35";
    std::wstring solidColor2          = L"35 35 35";
    std::wstring gradientColor2       = L"128 128 128";
    int          solidOpacity         = 100;
    int          gradientAngle        = 50;
    int          gradientBalance      = 50;
    int          acrylicTintOpacity   = 50;
    int          micaOpacity          = 50;
    bool         transparentTaskbar   = false;
    std::wstring buttonColor          = L"255 255 255";
    int          buttonColorOpacity   = 100;
    std::wstring titleColor           = L"255 255 255";
    int          titleColorOpacity    = 100;
    std::wstring artistColor          = L"255 255 255";
    int          artistColorOpacity   = 80;
    std::wstring ignoredProcesses     = L"";
    bool         enableTreeDump       = false;
    bool         showDebugBorders     = false;
    bool         showLayoutAnchors    = false;
    bool         hideUnsupportedButtons  = false;
    bool         disableAlbumArtClick    = false;
    bool         discordPresenceEnabled   = true;
    std::wstring discordApplicationId     = L"1528896038163710112";
    bool         discordShowPaused        = true;
    std::wstring discordActivityName      = L"{title}";
    bool         discordFetchOnlineArtwork = true;
    std::wstring discordLargeImageKey = L"taskbar_media_presence";
};
static ModSettings g_settings;

static void ParseTwoInts(const std::wstring& s, int& a, int& b) {
    size_t sp = s.find(L' ');
    if (sp == std::wstring::npos) return;
    try {
        a = std::stoi(s.substr(0, sp));
        b = std::stoi(s.substr(sp + 1));
    } catch (...) {}
}

enum class MediaButtonType {
    Previous = 1,
    PlayPause = 2,
    Next = 3,
    Stop = 4,
    Rewind5s = 5,
    Forward5s = 6,
    Shuffle = 7,
    Repeat = 8,
    SwitchSessions = 9,
    Volume = 10,
};

struct MediaButtonDefinition {
    std::wstring keyword;
    MediaButtonType type;
    int cmd;
};

static const std::vector<MediaButtonDefinition> g_mediaButtonDefinitions = {
    {L"prev", MediaButtonType::Previous, 1},
    {L"play", MediaButtonType::PlayPause, 2},
    {L"next", MediaButtonType::Next, 3},
    {L"rewind", MediaButtonType::Rewind5s, 5},
    {L"forward", MediaButtonType::Forward5s, 6},
    {L"shuffle", MediaButtonType::Shuffle, 7},
    {L"repeat", MediaButtonType::Repeat, 8},
    {L"switch_sessions", MediaButtonType::SwitchSessions, 9},
    {L"volume", MediaButtonType::Volume, 13},
};

struct MediaButtonConfig {
    MediaButtonType type;
    int cmd;
};

static std::vector<MediaButtonConfig> g_mediaButtons;
static std::mutex g_mediaButtonsMutex;

static std::wstring MapFontName(const std::wstring& key) {
    if (key == L"custom") return L"";
    if (key == L"segoe_ui_variable") return L"Segoe UI Variable Display";
    if (key == L"segoe_ui") return L"Segoe UI";
    if (key == L"segoe_ui_semibold") return L"Segoe UI Semibold";
    if (key == L"segoe_ui_bold") return L"Segoe UI Bold";
    if (key == L"segoe_ui_light") return L"Segoe UI Light";
    if (key == L"segoe_ui_semilight") return L"Segoe UI Semilight";
    if (key == L"aptos") return L"Aptos";
    if (key == L"calibri") return L"Calibri";
    if (key == L"cambria") return L"Cambria";
    if (key == L"candara") return L"Candara";
    if (key == L"consolas") return L"Consolas";
    if (key == L"corbel") return L"Corbel";
    if (key == L"arial") return L"Arial";
    if (key == L"trebuchet") return L"Trebuchet MS";
    if (key == L"verdana") return L"Verdana";
    if (key == L"tahoma") return L"Tahoma";
    if (key == L"georgia") return L"Georgia";
    if (key == L"times_new_roman") return L"Times New Roman";
    return L"Segoe UI Variable Display";
}

static void LoadSettings() {
    auto Str = [](const wchar_t* key, const wchar_t* def) -> std::wstring {
        PCWSTR p = Wh_GetStringSetting(key);
        std::wstring r = (*p != L'\0') ? p : def;
        Wh_FreeStringSetting(p);
        return r;
    };
    auto StrAllowEmpty = [](const wchar_t* key, const wchar_t* def) -> std::wstring {
        PCWSTR p = Wh_GetStringSetting(key);
        std::wstring r = p ? p : def;
        Wh_FreeStringSetting(p);
        return r;
    };
    auto Int = [](const wchar_t* key, int lo, int hi, int /*def*/) -> int {
        return std::clamp(Wh_GetIntSetting(key), lo, hi);
    };
    auto ParseMargin = [&Str](const wchar_t* key, const wchar_t* def, int& left, int& right) {
        std::wstring val = Str(key, def);
        try {
            size_t space = val.find(L' ');
            if (space != std::wstring::npos) {
                left  = std::stoi(val.substr(0, space));
                right = std::stoi(val.substr(space + 1));
            } else if (!val.empty()) {
                left = right = std::stoi(val);
            }
        } catch (...) {
            std::wstring d(def);
            size_t space = d.find(L' ');
            try {
                if (space != std::wstring::npos) {
                    left  = std::stoi(d.substr(0, space));
                    right = std::stoi(d.substr(space + 1));
                } else {
                    left = right = std::stoi(d);
                }
            } catch (...) { left = right = 0; }
        }
    };
    auto ParseCornerRadius = [&Str](const wchar_t* key, const wchar_t* def, double& tl, double& tr, double& br, double& bl) {
        std::wstring val = Str(key, def);
        std::vector<double> values;
        try {
            size_t pos = 0;
            while (pos < val.length()) {
                size_t space = val.find(L' ', pos);
                if (space == std::wstring::npos) space = val.length();
                std::wstring part = val.substr(pos, space - pos);
                if (!part.empty()) {
                    double v = std::stod(part);
                    values.push_back(v < 0.0 ? 0.0 : v);
                }
                pos = space + 1;
            }
        } catch (...) {}

        if (values.empty()) {
            try {
                std::wstring d(def);
                double v = std::stod(d);
                values.push_back(v < 0.0 ? 0.0 : v);
            } catch (...) {
                values.push_back(4.0);
            }
        }

        if (values.size() == 1) {
            tl = tr = br = bl = values[0];
        } else if (values.size() == 4) {
            tl = values[0];
            tr = values[1];
            br = values[2];
            bl = values[3];
        } else {
            tl = tr = br = bl = values[0];
        }
    };
    auto HoverMode = [&Str](const wchar_t* key) -> std::wstring {
        std::wstring mode = Str(key, L"auto");
        if (mode == L"black") return L"black";
        if (mode == L"white") return L"white";
        if (mode == L"off")   return L"off";
        return L"auto";
    };

    g_settings.taskbarMode          = Str(L"MainSettings.PlayerSetting.taskbarMode", L"selected");
    g_settings.taskbarNumber        = Int(L"MainSettings.PlayerSetting.taskbarNumber", 1, 16, 1);
    g_settings.positionPreset       = Str(L"MainSettings.PlayerSetting.positionPreset", L"apps");
    g_settings.position             = Str(L"MainSettings.PlayerSetting.position", L"taskbar_after_apps");
    ParseTwoInts(Str(L"MainSettings.PlayerSetting.customOffset", L"0 0"),
                 g_settings.customOffsetX, g_settings.customOffsetY);
    g_settings.customOffsetX = std::clamp(g_settings.customOffsetX, -4000, 4000);
    g_settings.customOffsetY = std::clamp(g_settings.customOffsetY, -4000, 4000);

    ParseMargin(L"MainSettings.PlayerSetting.playerMargin", L"4 4", g_settings.playerMarginLeft, g_settings.playerMarginRight);
    ParseMargin(L"MainSettings.PlayerSetting.playerWidth", L"460 460", g_settings.playerMinWidth, g_settings.playerMaxWidth);
    ParseMargin(L"MainSettings.PlayerSetting.playerHeight", L"40 40", g_settings.playerMinHeight, g_settings.playerMaxHeight);

    ParseMargin(L"MainSettings.AlbumArtSetting.albumArtWidth", L"36 36", g_settings.albumArtMinWidth, g_settings.albumArtMaxWidth);
    ParseMargin(L"MainSettings.AlbumArtSetting.albumArtHeight", L"36 36", g_settings.albumArtMinHeight, g_settings.albumArtMaxHeight);
    ParseMargin(L"MainSettings.AlbumArtSetting.albumArtMargin", L"0 0", g_settings.albumArtLeftMargin, g_settings.albumArtRightMargin);

    ParseMargin(L"MainSettings.TextAreaSetting.textAreaWidth", L"220 250", g_settings.textAreaMinWidth, g_settings.textAreaMaxWidth);
    if (g_settings.textAreaMinWidth == 150 && g_settings.textAreaMaxWidth == 170) {
        // Migrate the previous compact default while preserving custom widths.
        g_settings.textAreaMinWidth = 220;
        g_settings.textAreaMaxWidth = 250;
    }
    ParseMargin(L"MainSettings.TextAreaSetting.textAreaHeight", L"0 0", g_settings.textAreaMinHeight, g_settings.textAreaMaxHeight);
    ParseMargin(L"MainSettings.TextAreaSetting.textAreaMargin", L"5 5", g_settings.textAreaLeftMargin, g_settings.textAreaRightMargin);

    g_settings.mirrorLayout         = Wh_GetIntSetting(L"MainSettings.PlayerSetting.mirrorLayout") != 0;
    g_settings.showMediaButtons     = Wh_GetIntSetting(L"MainSettings.MediaButtonsSettings.showMediaButtons") != 0;
    ParseMargin(L"MainSettings.MediaButtonsSettings.mediaButtonsMargin", L"2 2", g_settings.mediaButtonsLeftMargin, g_settings.mediaButtonsRightMargin);
    g_settings.showTrackTitle       = Wh_GetIntSetting(L"MainSettings.TextAreaSetting.showTrackTitle")    != 0;
    g_settings.showFullTitleOnHover = Wh_GetIntSetting(L"BehaviorSettings.showFullTitleOnHover") != 0;
    g_settings.showTrackArtist      = Wh_GetIntSetting(L"MainSettings.TextAreaSetting.showTrackArtist")   != 0;
    g_settings.swapTitleArtist      = Wh_GetIntSetting(L"MainSettings.TextAreaSetting.swapTitleArtist")   != 0;
    g_settings.emptyTitleText       = StrAllowEmpty(L"MainSettings.TextAreaSetting.emptyTitleText",    L"Untitled");
    g_settings.noMediaTitleText     = StrAllowEmpty(L"MainSettings.TextAreaSetting.noMediaTitleText",  L"Not Playing");
    g_settings.emptyArtistText      = StrAllowEmpty(L"MainSettings.TextAreaSetting.emptyArtistText",   L"");
    g_settings.noMediaArtistText    = StrAllowEmpty(L"MainSettings.TextAreaSetting.noMediaArtistText", L"");
    g_settings.showAlbumArt         = Wh_GetIntSetting(L"MainSettings.AlbumArtSetting.showAlbumArt")      != 0;
    g_settings.albumArtEmptyBehavior = Str(L"AppearanceSettings.AlbumArtDisplaySettings.albumArtEmptyBehavior", L"show");
    g_settings.emptyIconGlyph       = Str(L"AppearanceSettings.AlbumArtDisplaySettings.emptyIconGlyph",       L"E189");
    g_settings.emptyIconSize        = Int(L"AppearanceSettings.AlbumArtDisplaySettings.emptyIconSize",          1, 256, 16);
    g_settings.emptyIconFont        = Str(L"AppearanceSettings.AlbumArtDisplaySettings.emptyIconFont",        L"segoe_fluent");
    g_settings.emptyIconColor       = Str(L"AppearanceSettings.AlbumArtDisplaySettings.emptyIconColor",       L"255 255 255");
    g_settings.emptyIconOpacity     = Int(L"AppearanceSettings.AlbumArtDisplaySettings.emptyIconOpacity",       0, 100, 100);
    g_settings.albumArtQuality      = Str(L"AppearanceSettings.AlbumArtDisplaySettings.albumArtQuality", L"medium");
    g_settings.showPauseOverlay     = Wh_GetIntSetting(L"AppearanceSettings.AlbumArtDisplaySettings.showPauseOverlay")  != 0;
    g_settings.pauseOverlayIconSize = Int(L"AppearanceSettings.AlbumArtDisplaySettings.pauseOverlayIconSize",     1, 256, 16);
    g_settings.pauseOverlayOpacity  = Int(L"AppearanceSettings.AlbumArtDisplaySettings.pauseOverlayOpacity",     0, 100,  60);
    g_settings.iconStyle            = Str(L"AppearanceSettings.MediaButtonsStyleSettings.iconStyle", L"fluent_outline");
    g_settings.showAppIcon          = Wh_GetIntSetting(L"AppearanceSettings.AlbumArtDisplaySettings.showAppIcon")       != 0;
    g_settings.appIconCorner        = Str(L"AppearanceSettings.AlbumArtDisplaySettings.appIconCorner",  L"bottom_right");
    g_settings.appIconSize          = Int(L"AppearanceSettings.AlbumArtDisplaySettings.appIconSize",         8,  32,  12);

    g_settings.backgroundType       = Str(L"AppearanceSettings.BackgroundStyleSettings.backgroundType", L"acrylic");
    g_settings.blurOpacity          = Int(L"AppearanceSettings.BackgroundStyleSettings.blurOpacity",           0, 100, 65);
    g_settings.blurRadius           = Int(L"AppearanceSettings.BackgroundStyleSettings.blurRadius",            1,  50,  11);
    ParseCornerRadius(L"AppearanceSettings.BackgroundStyleSettings.cornerRadius", L"4",
                      g_settings.cornerRadiusTL, g_settings.cornerRadiusTR,
                      g_settings.cornerRadiusBR, g_settings.cornerRadiusBL);
    g_settings.albumArtOpacity      = Int(L"AppearanceSettings.AlbumArtDisplaySettings.albumArtOpacity",       0, 100, 100);
    ParseCornerRadius(L"AppearanceSettings.AlbumArtDisplaySettings.albumArtCornerRadius", L"4",
                      g_settings.albumArtCornerRadiusTL, g_settings.albumArtCornerRadiusTR,
                      g_settings.albumArtCornerRadiusBR, g_settings.albumArtCornerRadiusBL);
    g_settings.buttonSpacing        = Wh_GetIntSetting(L"AppearanceSettings.MediaButtonsStyleSettings.buttonSpacing");
    g_settings.buttonSize           = Int(L"MainSettings.MediaButtonsSettings.buttonSize",          16,  48,  28);
    g_settings.buttonIconSize       = Int(L"AppearanceSettings.MediaButtonsStyleSettings.buttonIconSize",       8,  32,  12);
    ParseCornerRadius(L"AppearanceSettings.MediaButtonsStyleSettings.buttonCornerRadius", L"4",
                      g_settings.buttonCornerRadiusTL, g_settings.buttonCornerRadiusTR,
                      g_settings.buttonCornerRadiusBR, g_settings.buttonCornerRadiusBL);
    g_settings.titleFontSize        = Int(L"AppearanceSettings.TitleTextStyleSettings.titleFontSize",         7,  24,  12);
    g_settings.titleFont            = MapFontName(Str(L"AppearanceSettings.TitleTextStyleSettings.titleFont", L"segoe_ui_variable"));
    g_settings.titleFontFamily      = Str(L"AppearanceSettings.TitleTextStyleSettings.titleFontFamily", L"");
    g_settings.titleFontWeight      = Str(L"AppearanceSettings.TitleTextStyleSettings.titleFontWeight", L"");
    g_settings.titleFontStyle       = Str(L"AppearanceSettings.TitleTextStyleSettings.titleFontStyle", L"");
    g_settings.titleCharacterSpacing = Wh_GetIntSetting(L"AppearanceSettings.TitleTextStyleSettings.titleCharacterSpacing");
    g_settings.artistFontSize       = Int(L"AppearanceSettings.ArtistTextStyleSettings.artistFontSize",        7,  24,  11);
    g_settings.artistFont           = MapFontName(Str(L"AppearanceSettings.ArtistTextStyleSettings.artistFont", L"segoe_ui_variable"));
    g_settings.artistFontFamily     = Str(L"AppearanceSettings.ArtistTextStyleSettings.artistFontFamily", L"");
    g_settings.artistFontWeight     = Str(L"AppearanceSettings.ArtistTextStyleSettings.artistFontWeight", L"");
    g_settings.artistFontStyle      = Str(L"AppearanceSettings.ArtistTextStyleSettings.artistFontStyle", L"");
    g_settings.artistCharacterSpacing = Wh_GetIntSetting(L"AppearanceSettings.ArtistTextStyleSettings.artistCharacterSpacing");
    g_settings.textSpacing          = Wh_GetIntSetting(L"MainSettings.TextAreaSetting.textSpacing");
    g_settings.enableArtistScrolling = Wh_GetIntSetting(L"MainSettings.TextAreaSetting.enableArtistScrolling") != 0;
    g_settings.enableTitleScrolling = Wh_GetIntSetting(L"MainSettings.TextAreaSetting.enableTitleScrolling") != 0;
    g_settings.scrollSpeed          = Int(L"MainSettings.TextAreaSetting.scrollSpeed", 1, 10, 1);
    g_settings.scrollPauseDuration  = Int(L"MainSettings.TextAreaSetting.scrollPauseDuration", 0, 10000, 1000);
    g_settings.scrollMode           = Str(L"MainSettings.TextAreaSetting.scrollMode", L"marquee");
    // "loop" was the name used by earlier builds for the single-copy marquee.
    // Keep existing installations compatible while exposing the clearer name.
    if (g_settings.scrollMode == L"loop") {
        g_settings.scrollMode = L"marquee";
    } else if (g_settings.scrollMode != L"marquee" &&
               g_settings.scrollMode != L"bounce" &&
               g_settings.scrollMode != L"ellipsis") {
        g_settings.scrollMode = L"marquee";
    }
    // Ellipsis mode deliberately bypasses the Canvas-based scrolling views so
    // XAML can trim each line with CharacterEllipsis.
    if (g_settings.scrollMode == L"ellipsis") {
        g_settings.enableTitleScrolling = false;
        g_settings.enableArtistScrolling = false;
    }
    g_settings.loopGap              = Int(L"MainSettings.TextAreaSetting.loopGap", 0, 500, 40);
    g_settings.solidColor           = Str(L"AppearanceSettings.BackgroundStyleSettings.solidColor", L"35 35 35");
    g_settings.solidColor2          = Str(L"AppearanceSettings.BackgroundStyleSettings.solidColor2", L"35 35 35");
    g_settings.gradientColor2       = Str(L"AppearanceSettings.BackgroundStyleSettings.gradientColor2", L"128 128 128");
    g_settings.solidOpacity         = Int(L"AppearanceSettings.BackgroundStyleSettings.solidOpacity", 0, 100, 100);
    g_settings.gradientAngle        = Int(L"AppearanceSettings.BackgroundStyleSettings.gradientAngle", 0, 360, 50);
    g_settings.gradientBalance      = Int(L"AppearanceSettings.BackgroundStyleSettings.gradientBalance", 0, 100, 50);
    g_settings.acrylicTintOpacity   = Int(L"AppearanceSettings.BackgroundStyleSettings.acrylicTintOpacity", 0, 100, 50);
    g_settings.micaOpacity          = Int(L"AppearanceSettings.BackgroundStyleSettings.micaOpacity", 0, 100, 50);
    g_settings.transparentTaskbar =
        Wh_GetIntSetting(L"AppearanceSettings.TaskbarAppearanceSettings.transparentTaskbar") != 0;
    g_settings.buttonColor          = Str(L"AppearanceSettings.MediaButtonsStyleSettings.buttonColor", L"255 255 255");
    g_settings.buttonColorOpacity   = Int(L"AppearanceSettings.MediaButtonsStyleSettings.buttonColorOpacity", 0, 100, 100);
    g_settings.titleColor           = Str(L"AppearanceSettings.TitleTextStyleSettings.titleColor", L"255 255 255");
    g_settings.titleColorOpacity    = Int(L"AppearanceSettings.TitleTextStyleSettings.titleColorOpacity", 0, 100, 100);
    g_settings.artistColor          = Str(L"AppearanceSettings.ArtistTextStyleSettings.artistColor", L"255 255 255");
    g_settings.artistColorOpacity   = Int(L"AppearanceSettings.ArtistTextStyleSettings.artistColorOpacity", 0, 100, 80);
    g_settings.albumArtLeftClick        = L"none";
    g_settings.albumArtRightClick       = L"none";
    g_settings.albumArtMiddleClick      = L"none";
    g_settings.albumArtLeftDoubleClick  = L"none";
    g_settings.albumArtRightDoubleClick = L"none";
    g_settings.playerLeftClick          = L"none";
    g_settings.playerRightClick         = L"none";
    g_settings.playerMiddleClick        = L"none";
    g_settings.playerLeftDoubleClick    = L"none";
    g_settings.playerRightDoubleClick   = L"none";

    for (int i = 0; i < 20; i++) {
        PCWSTR objectStr = Wh_GetStringSetting(L"BehaviorSettings.ClickActionSettings[%d].object", i);
        PCWSTR clickStr = Wh_GetStringSetting(L"BehaviorSettings.ClickActionSettings[%d].click", i);
        PCWSTR actionStr = Wh_GetStringSetting(L"BehaviorSettings.ClickActionSettings[%d].action", i);

        if (*objectStr == L'\0' || *clickStr == L'\0' || *actionStr == L'\0') {
            Wh_FreeStringSetting(objectStr);
            Wh_FreeStringSetting(clickStr);
            Wh_FreeStringSetting(actionStr);
            break;
        }

        std::wstring object(objectStr);
        std::wstring click(clickStr);
        std::wstring action(actionStr);

        Wh_FreeStringSetting(objectStr);
        Wh_FreeStringSetting(clickStr);
        Wh_FreeStringSetting(actionStr);

        if (object.empty()) object = L"none";
        if (click.empty()) click = L"none";
        if (action.empty()) action = L"none";

        if (object == L"none" || click == L"none") {
            continue;
        }

        if (object == L"album_art") {
            if (click == L"left_click") g_settings.albumArtLeftClick = action;
            else if (click == L"right_click") g_settings.albumArtRightClick = action;
            else if (click == L"middle_click") g_settings.albumArtMiddleClick = action;
            else if (click == L"left_double_click") g_settings.albumArtLeftDoubleClick = action;
            else if (click == L"right_double_click") g_settings.albumArtRightDoubleClick = action;
        } else if (object == L"player") {
            if (click == L"left_click") g_settings.playerLeftClick = action;
            else if (click == L"right_click") g_settings.playerRightClick = action;
            else if (click == L"middle_click") g_settings.playerMiddleClick = action;
            else if (click == L"left_double_click") g_settings.playerLeftDoubleClick = action;
            else if (click == L"right_double_click") g_settings.playerRightDoubleClick = action;
        }
    }

    g_settings.albumArtWheelAction = L"none";
    g_settings.playerWheelAction   = L"none";

    for (int i = 0; i < 20; i++) {
        PCWSTR objectStr = Wh_GetStringSetting(L"BehaviorSettings.MouseWheelActionSettings[%d].object", i);
        PCWSTR clickStr = Wh_GetStringSetting(L"BehaviorSettings.MouseWheelActionSettings[%d].click", i);
        PCWSTR actionStr = Wh_GetStringSetting(L"BehaviorSettings.MouseWheelActionSettings[%d].action", i);

        if (*objectStr == L'\0' || *clickStr == L'\0' || *actionStr == L'\0') {
            Wh_FreeStringSetting(objectStr);
            Wh_FreeStringSetting(clickStr);
            Wh_FreeStringSetting(actionStr);
            break;
        }

        std::wstring object(objectStr);
        std::wstring click(clickStr);
        std::wstring action(actionStr);

        Wh_FreeStringSetting(objectStr);
        Wh_FreeStringSetting(clickStr);
        Wh_FreeStringSetting(actionStr);

        if (object.empty()) object = L"none";
        if (click.empty()) click = L"none";
        if (action.empty()) action = L"none";

        if (object == L"none" || click == L"none") {
            continue;
        }

        if (object == L"album_art" && click == L"mouse_wheel") {
            g_settings.albumArtWheelAction = action;
        } else if (object == L"player" && click == L"mouse_wheel") {
            g_settings.playerWheelAction = action;
        }
    }
    g_settings.hideWhenNoMedia      = Wh_GetIntSetting(L"BehaviorSettings.hideWhenNoMedia")   != 0;
    g_settings.hideFullscreen       = Wh_GetIntSetting(L"BehaviorSettings.hideFullscreen")    != 0;
    g_settings.idleHideSeconds      = std::max(Wh_GetIntSetting(L"BehaviorSettings.idleHideSeconds"), 0);
    g_settings.playerHoverEffectMode = HoverMode(L"AppearanceSettings.BackgroundStyleSettings.enablePlayerHoverEffect");
    g_settings.mediaButtonsHoverEffectMode = HoverMode(L"AppearanceSettings.BackgroundStyleSettings.enableMediaButtonsHoverEffect");

    g_settings.enableSmoothPositionAnimation = Wh_GetIntSetting(L"AnimationSettings.enableSmoothPositionAnimation") != 0;

    g_settings.discordPresenceEnabled =
        Wh_GetIntSetting(L"DiscordPresenceSettings.enabled") != 0;
    g_settings.discordApplicationId = StrAllowEmpty(
        L"DiscordPresenceSettings.applicationId", L"1528896038163710112");
    g_settings.discordShowPaused =
        Wh_GetIntSetting(L"DiscordPresenceSettings.showPaused") != 0;
    g_settings.discordActivityName = StrAllowEmpty(
        L"DiscordPresenceSettings.activityName", L"{title}");
    g_settings.discordFetchOnlineArtwork =
        Wh_GetIntSetting(L"DiscordPresenceSettings.fetchOnlineArtwork") != 0;
    g_settings.discordLargeImageKey = StrAllowEmpty(
        L"DiscordPresenceSettings.largeImageKey", L"taskbar_media_presence");

    g_settings.hideUnsupportedButtons  = Wh_GetIntSetting(L"MainSettings.MediaButtonsSettings.hideUnsupportedButtons") != 0;

    g_settings.disableAlbumArtClick    = Wh_GetIntSetting(L"BehaviorSettings.disableAlbumArtClick") != 0;

    g_settings.ignoredProcesses     = Str(L"DebugSettings.ignoredProcesses", L"");
    g_settings.enableTreeDump       = Wh_GetIntSetting(L"DebugSettings.enableTreeDump")    != 0;
    g_settings.showDebugBorders     = Wh_GetIntSetting(L"DebugSettings.showDebugBorders")  != 0;
    g_settings.showLayoutAnchors    = Wh_GetIntSetting(L"DebugSettings.showLayoutAnchors") != 0;
    try {
        std::lock_guard<std::mutex> lock(g_mediaButtonsMutex);
        g_mediaButtons.clear();
        std::set<MediaButtonType> seen;

        for (int i = 0; i < 10; i++) {
            try {
                PCWSTR itemStr = Wh_GetStringSetting(L"MainSettings.MediaButtonsSettings.mediaButtons[%d]", i);
                if (!itemStr || !*itemStr) {
                    Wh_FreeStringSetting(itemStr);
                    break;
                }

                std::wstring keyword(itemStr);
                Wh_FreeStringSetting(itemStr);

                for (const auto& def : g_mediaButtonDefinitions) {
                    if (def.keyword == keyword && seen.insert(def.type).second) {
                        g_mediaButtons.push_back({def.type, def.cmd});
                        break;
                    }
                }
            } catch (...) {
                Wh_Log(L"LoadSettings: Exception parsing media button at index %d", i);
            }
        }

        // Preserve custom layouts, but upgrade the exact pre-0.10 default so
        // existing users receive the new playback-mode controls automatically.
        if (g_mediaButtons.size() == 4 &&
            g_mediaButtons[0].type == MediaButtonType::Previous &&
            g_mediaButtons[1].type == MediaButtonType::PlayPause &&
            g_mediaButtons[2].type == MediaButtonType::Next &&
            g_mediaButtons[3].type == MediaButtonType::Volume) {
            g_mediaButtons.insert(g_mediaButtons.begin(), {
                {MediaButtonType::Shuffle, 7},
                {MediaButtonType::Repeat, 8}
            });
        }

        if (g_mediaButtons.empty()) {
            Wh_Log(L"LoadSettings: No media buttons configured, showing none");
        }
    } catch (...) {
        Wh_Log(L"LoadSettings: Critical exception in media buttons parsing, using defaults");
        try {
            std::lock_guard<std::mutex> lock(g_mediaButtonsMutex);
            g_mediaButtons = {
                {MediaButtonType::Shuffle, 7},
                {MediaButtonType::Repeat, 8},
                {MediaButtonType::Previous, 1},
                {MediaButtonType::PlayPause, 2},
                {MediaButtonType::Next, 3},
                {MediaButtonType::Volume, 13}
            };
        } catch (...) {}
    }

    if (g_settings.position == L"taskbar_left")
        g_settings.position = L"taskbar_left_start";
    else if (g_settings.position == L"taskbar_right")
        g_settings.position = L"taskbar_right_start";
    else if (g_settings.position == L"taskbar_after_start")
        g_settings.position = L"taskbar_after_search_right";
    else if (g_settings.position == L"taskbar_after_search")
        g_settings.position = L"taskbar_after_search_right";
    else if (g_settings.position == L"tray_before_omni")
        g_settings.position = L"tray_before_omni_right";
    else if (g_settings.position == L"tray_after_showdesktop")
        g_settings.position = L"tray_after_showdesktop_right";

    int quickPositionPreset = Wh_GetIntValue(L"quickPositionPreset", -1);
    if (quickPositionPreset == 0) g_settings.positionPreset = L"apps";
    else if (quickPositionPreset == 1) g_settings.positionPreset = L"left";
    else if (quickPositionPreset == 2) g_settings.positionPreset = L"middle";
    else if (quickPositionPreset == 3) g_settings.positionPreset = L"right";
    else if (quickPositionPreset == 4) g_settings.positionPreset = L"custom";

    int quickTaskbarMode = Wh_GetIntValue(L"quickTaskbarMode", -1);
    if (quickTaskbarMode == 0) g_settings.taskbarMode = L"selected";
    else if (quickTaskbarMode == 1) g_settings.taskbarMode = L"all";
    int quickTaskbarNumber = Wh_GetIntValue(L"quickTaskbarNumber", -1);
    if (quickTaskbarNumber > 0) g_settings.taskbarNumber = quickTaskbarNumber;

    if (g_settings.positionPreset == L"left") {
        g_settings.position = L"taskbar_left_start";
    } else if (g_settings.positionPreset == L"apps") {
        g_settings.position = L"taskbar_after_apps";
    } else if (g_settings.positionPreset == L"middle") {
        g_settings.position = L"taskbar_center_edge";
    } else if (g_settings.positionPreset == L"right") {
        g_settings.position = L"tray_left";
    }

    int quickBackground = Wh_GetIntValue(L"quickBackground", -1);
    if (quickBackground == 0) g_settings.backgroundType = L"none";
    else if (quickBackground == 1) g_settings.backgroundType = L"acrylic";

    int quickTransparentTaskbar = Wh_GetIntValue(L"quickTransparentTaskbar", -1);
    if (quickTransparentTaskbar == 0) g_settings.transparentTaskbar = false;
    else if (quickTransparentTaskbar == 1) g_settings.transparentTaskbar = true;

    // The widget wheel never modifies Windows master volume.
    if (g_settings.playerWheelAction == L"system_sound") {
        g_settings.playerWheelAction = L"app_sound";
    }
    if (g_settings.albumArtWheelAction == L"system_sound") {
        g_settings.albumArtWheelAction = L"app_sound";
    }
}

static HWND FindCurrentProcessTaskbarWnd();
static void DispatchMediaUpdate();
static void ApplySettings();
static void ApplyTaskbarTransparencyToAll();

static std::atomic<bool> g_unloading{false};
static std::atomic<bool> g_applyingSettings{false};
static std::atomic<bool> g_hookInjectionInProgress{false};
static std::atomic<int>  g_hookFailCount{0};

static const CLSID XIID_MMDeviceEnumerator = __uuidof(MMDeviceEnumerator);
static const IID XIID_IMMDeviceEnumerator = __uuidof(IMMDeviceEnumerator);
static const IID XIID_IAudioSessionManager2 = __uuidof(IAudioSessionManager2);

static HWND             g_taskbarWnd      = nullptr;
static Grid             g_playerGrid      = nullptr;
static FrameworkElement g_injectionParent = nullptr;
static int              g_playerColumn    = -1;
static std::atomic<bool> g_needsUiUpdate{false};

struct MirrorPlayerInstance {
    HWND taskbarWindow = nullptr;
    Grid playerGrid{nullptr};
    Grid targetGrid{nullptr};
    int playerColumn = -1;
    FrameworkElement trackedElement{nullptr};
    Thickness trackedOriginalMargin{};
    winrt::event_token layoutUpdatedToken{};
};

static std::vector<std::shared_ptr<MirrorPlayerInstance>> g_mirrorPlayers;
static bool g_refreshingMirrorPlayers = false;
static bool g_updatingMirrorVisibility = false;
static bool g_refreshingMirrorTheme = false;

static FrameworkElement g_trackedElement = nullptr;
static Thickness g_trackedElementOriginalMargin{};
static bool g_hasTrackedElementOriginalMargin = false;
static std::wstring g_trackPosition = L"";
static winrt::event_token g_layoutUpdateToken{};

using CTaskBand_GetTaskbarHost_t  = void*(WINAPI*)(void*, void*);
using CSecondaryTaskBand_GetTaskbarHost_t = void*(WINAPI*)(void*, void*);
using TaskbarHost_FrameHeight_t   = int  (WINAPI*)(void*);
using Std_Ref_Decref_t            = void (WINAPI*)(void*);

static CTaskBand_GetTaskbarHost_t  CTaskBand_GetTaskbarHost_Original  = nullptr;
static CSecondaryTaskBand_GetTaskbarHost_t CSecondaryTaskBand_GetTaskbarHost_Original = nullptr;
static TaskbarHost_FrameHeight_t   TaskbarHost_FrameHeight_Original   = nullptr;
static Std_Ref_Decref_t            Std_Ref_Decref_Original            = nullptr;
static void* CTaskBand_ITaskListWndSite_vftable = nullptr;
static void* CSecondaryTaskBand_ITaskListWndSite_vftable = nullptr;

using WindowThreadProc = void(*)(void*);

static bool RunFromWindowThread(HWND hWnd, WindowThreadProc proc, void* param) {
    static const UINT kMsg = RegisterWindowMessage(L"Windhawk_RunFromWindowThread_" WH_MOD_ID);

    struct Payload { WindowThreadProc proc; void* param; };

    DWORD tid = GetWindowThreadProcessId(hWnd, nullptr);
    if (!tid) return false;

    if (tid == GetCurrentThreadId()) {
        proc(param);
        return true;
    }

    HHOOK hook = SetWindowsHookExW(WH_CALLWNDPROC,
        [](int code, WPARAM w, LPARAM l) CALLBACK -> LRESULT {
            if (code == HC_ACTION) {
                auto* cwp = reinterpret_cast<const CWPSTRUCT*>(l);
                static const UINT kM = RegisterWindowMessage(L"Windhawk_RunFromWindowThread_" WH_MOD_ID);
                if (cwp->message == kM) {
                    auto* p = reinterpret_cast<Payload*>(cwp->lParam);
                    p->proc(p->param);
                }
            }
            return CallNextHookEx(nullptr, code, w, l);
        }, nullptr, tid);

    if (!hook) return false;

    Payload pay{proc, param};
    SendMessageW(hWnd, kMsg, 0, reinterpret_cast<LPARAM>(&pay));
    UnhookWindowsHookEx(hook);
    return true;
}

struct MediaState {
    std::wstring      title;
    std::wstring      artist;
    std::wstring      albumTitle;
    std::wstring      appUserModelId;
    bool              isPlaying     = false;
    bool              hasMedia      = false;
    int64_t           positionSeconds = 0;
    int64_t           durationSeconds = 0;
    ULONGLONG         timelineSampleTick = 0;
    std::vector<BYTE> thumbnailBytes;
    uint64_t          thumbnailHash = 0;
    std::vector<BYTE> appIconBytes;
    std::wstring      appIconKey;
    bool              canSkipPrevious  = true;
    bool              canSkipNext      = true;
    bool              canShuffle       = true;
    bool              canRepeat        = true;
    bool              canSeek          = true;
};

static MediaState g_media;
static std::mutex g_mediaMtx;

// Discord's desktop Rich Presence RPC requires a registered application ID.
// This is an original, minimal local IPC client: it publishes the current
// title, artist, play state, timeline, and a resolved cover URL. It never
// authenticates as the user or contacts the Discord HTTP API.
static HANDLE g_discordPresenceThread = nullptr;
static HANDLE g_discordPresenceStopEvent = nullptr;
static HANDLE g_discordPresenceUpdateEvent = nullptr;
static std::atomic<uint64_t> g_discordNonce{1};

struct DiscordIpcHeader {
    uint32_t opcode;
    uint32_t length;
};

static bool IsValidDiscordApplicationId(const std::wstring& value) {
    if (value.size() < 5 || value.size() > 32) return false;
    return std::all_of(value.begin(), value.end(), [](wchar_t c) {
        return c >= L'0' && c <= L'9';
    });
}

static std::string ToUtf8(const std::wstring& value) {
    try {
        return winrt::to_string(winrt::hstring(value));
    } catch (...) {
        return {};
    }
}

static std::wstring FromUtf8(const std::string& value) {
    try {
        return std::wstring(winrt::to_hstring(value));
    } catch (...) {
        return {};
    }
}

static std::string LimitUtf8(std::string value, size_t limit = 120) {
    if (value.size() <= limit) return value;
    size_t cut = limit;
    while (cut > 0 &&
           (static_cast<unsigned char>(value[cut]) & 0xC0) == 0x80) {
        --cut;
    }
    value.resize(cut);
    return value;
}

static std::string JsonEscapeUtf8(const std::string& value) {
    std::string escaped;
    escaped.reserve(value.size() + 16);
    static const char kHex[] = "0123456789abcdef";
    for (unsigned char c : value) {
        switch (c) {
            case '\"': escaped += "\\\""; break;
            case '\\': escaped += "\\\\"; break;
            case '\b': escaped += "\\b"; break;
            case '\f': escaped += "\\f"; break;
            case '\n': escaped += "\\n"; break;
            case '\r': escaped += "\\r"; break;
            case '\t': escaped += "\\t"; break;
            default:
                if (c < 0x20) {
                    escaped += "\\u00";
                    escaped += kHex[(c >> 4) & 0x0F];
                    escaped += kHex[c & 0x0F];
                } else {
                    escaped.push_back(static_cast<char>(c));
                }
                break;
        }
    }
    return escaped;
}

static std::wstring UrlEncodeQueryValue(const std::wstring& value) {
    std::string utf8 = ToUtf8(value);
    std::string encoded;
    encoded.reserve(utf8.size() * 3);
    static const char kHex[] = "0123456789ABCDEF";
    for (unsigned char c : utf8) {
        if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') ||
            (c >= '0' && c <= '9') || c == '-' || c == '_' ||
            c == '.' || c == '~') {
            encoded.push_back(static_cast<char>(c));
        } else if (c == ' ') {
            encoded.push_back('+');
        } else {
            encoded.push_back('%');
            encoded.push_back(kHex[(c >> 4) & 0x0F]);
            encoded.push_back(kHex[c & 0x0F]);
        }
    }
    return std::wstring(encoded.begin(), encoded.end());
}

static std::string WinHttpGetUtf8(const wchar_t* host,
                                  const std::wstring& path) {
    HINTERNET session = WinHttpOpen(
        L"Taskbar Media Presence/0.10.1",
        WINHTTP_ACCESS_TYPE_AUTOMATIC_PROXY,
        WINHTTP_NO_PROXY_NAME, WINHTTP_NO_PROXY_BYPASS, 0);
    if (!session) return {};
    WinHttpSetTimeouts(session, 2000, 2000, 2000, 2000);

    HINTERNET connection = WinHttpConnect(
        session, host, INTERNET_DEFAULT_HTTPS_PORT, 0);
    if (!connection) {
        WinHttpCloseHandle(session);
        return {};
    }

    HINTERNET request = WinHttpOpenRequest(
        connection, L"GET", path.c_str(), nullptr, WINHTTP_NO_REFERER,
        WINHTTP_DEFAULT_ACCEPT_TYPES, WINHTTP_FLAG_SECURE | WINHTTP_FLAG_REFRESH);
    if (!request) {
        WinHttpCloseHandle(connection);
        WinHttpCloseHandle(session);
        return {};
    }

    std::string body;
    bool success = WinHttpSendRequest(
        request, L"Accept: application/json\r\n", -1L,
        WINHTTP_NO_REQUEST_DATA, 0, 0, 0) &&
        WinHttpReceiveResponse(request, nullptr);
    DWORD statusCode = 0;
    DWORD statusSize = sizeof(statusCode);
    if (success) {
        success = WinHttpQueryHeaders(
            request, WINHTTP_QUERY_STATUS_CODE | WINHTTP_QUERY_FLAG_NUMBER,
            WINHTTP_HEADER_NAME_BY_INDEX, &statusCode, &statusSize,
            WINHTTP_NO_HEADER_INDEX) && statusCode == 200;
    }

    while (success && body.size() < 512 * 1024) {
        DWORD available = 0;
        if (!WinHttpQueryDataAvailable(request, &available)) {
            success = false;
            break;
        }
        if (!available) break;
        DWORD requestSize = std::min<DWORD>(available, 16 * 1024);
        std::vector<char> buffer(requestSize);
        DWORD bytesRead = 0;
        if (!WinHttpReadData(request, buffer.data(), requestSize, &bytesRead)) {
            success = false;
            break;
        }
        if (!bytesRead) break;
        body.append(buffer.data(), bytesRead);
    }

    WinHttpCloseHandle(request);
    WinHttpCloseHandle(connection);
    WinHttpCloseHandle(session);
    return success ? body : std::string{};
}

static DWORD WinHttpHeadStatus(const wchar_t* host,
                               const std::wstring& path) {
    HINTERNET session = WinHttpOpen(
        L"Taskbar Media Presence/0.10.1",
        WINHTTP_ACCESS_TYPE_AUTOMATIC_PROXY,
        WINHTTP_NO_PROXY_NAME, WINHTTP_NO_PROXY_BYPASS, 0);
    if (!session) return 0;
    WinHttpSetTimeouts(session, 2000, 2000, 2000, 2000);

    HINTERNET connection = WinHttpConnect(
        session, host, INTERNET_DEFAULT_HTTPS_PORT, 0);
    if (!connection) {
        WinHttpCloseHandle(session);
        return 0;
    }

    HINTERNET request = WinHttpOpenRequest(
        connection, L"HEAD", path.c_str(), nullptr, WINHTTP_NO_REFERER,
        WINHTTP_DEFAULT_ACCEPT_TYPES, WINHTTP_FLAG_SECURE | WINHTTP_FLAG_REFRESH);
    DWORD statusCode = 0;
    if (request && WinHttpSendRequest(
            request, WINHTTP_NO_ADDITIONAL_HEADERS, 0,
            WINHTTP_NO_REQUEST_DATA, 0, 0, 0) &&
        WinHttpReceiveResponse(request, nullptr)) {
        DWORD statusSize = sizeof(statusCode);
        if (!WinHttpQueryHeaders(
            request, WINHTTP_QUERY_STATUS_CODE | WINHTTP_QUERY_FLAG_NUMBER,
            WINHTTP_HEADER_NAME_BY_INDEX, &statusCode, &statusSize,
            WINHTTP_NO_HEADER_INDEX)) {
            statusCode = 0;
        }
    }

    if (request) WinHttpCloseHandle(request);
    WinHttpCloseHandle(connection);
    WinHttpCloseHandle(session);
    return statusCode;
}

static int JsonHexDigit(char value) {
    if (value >= '0' && value <= '9') return value - '0';
    if (value >= 'a' && value <= 'f') return value - 'a' + 10;
    if (value >= 'A' && value <= 'F') return value - 'A' + 10;
    return -1;
}

static void AppendUtf8CodePoint(std::string& value, uint32_t codePoint) {
    if (codePoint <= 0x7F) {
        value.push_back(static_cast<char>(codePoint));
    } else if (codePoint <= 0x7FF) {
        value.push_back(static_cast<char>(0xC0 | (codePoint >> 6)));
        value.push_back(static_cast<char>(0x80 | (codePoint & 0x3F)));
    } else if (codePoint <= 0xFFFF) {
        value.push_back(static_cast<char>(0xE0 | (codePoint >> 12)));
        value.push_back(static_cast<char>(0x80 | ((codePoint >> 6) & 0x3F)));
        value.push_back(static_cast<char>(0x80 | (codePoint & 0x3F)));
    } else if (codePoint <= 0x10FFFF) {
        value.push_back(static_cast<char>(0xF0 | (codePoint >> 18)));
        value.push_back(static_cast<char>(0x80 | ((codePoint >> 12) & 0x3F)));
        value.push_back(static_cast<char>(0x80 | ((codePoint >> 6) & 0x3F)));
        value.push_back(static_cast<char>(0x80 | (codePoint & 0x3F)));
    }
}

static std::string ExtractJsonStringField(const std::string& json,
                                          const char* fieldName,
                                          size_t searchStart = 0,
                                          size_t searchEnd = std::string::npos) {
    searchEnd = std::min(searchEnd, json.size());
    std::string marker = "\"" + std::string(fieldName) + "\":\"";
    size_t position = json.find(marker, searchStart);
    if (position == std::string::npos || position + marker.size() > searchEnd) {
        return {};
    }
    position += marker.size();

    std::string value;
    for (size_t i = position; i < searchEnd; ++i) {
        char c = json[i];
        if (c == '"') return value;
        if (c != '\\') {
            value.push_back(c);
            continue;
        }
        if (++i >= json.size()) return {};
        char escaped = json[i];
        if (escaped == '"' || escaped == '\\' || escaped == '/') {
            value.push_back(escaped);
        } else if (escaped == 'b') {
            value.push_back('\b');
        } else if (escaped == 'f') {
            value.push_back('\f');
        } else if (escaped == 'n') {
            value.push_back('\n');
        } else if (escaped == 'r') {
            value.push_back('\r');
        } else if (escaped == 't') {
            value.push_back('\t');
        } else if (escaped == 'u' && i + 4 < searchEnd) {
            int codePoint = 0;
            bool valid = true;
            for (int digit = 0; digit < 4; ++digit) {
                int valueDigit = JsonHexDigit(json[i + 1 + digit]);
                if (valueDigit < 0) {
                    valid = false;
                    break;
                }
                codePoint = codePoint * 16 + valueDigit;
            }
            if (!valid) return {};
            if (codePoint >= 0xD800 && codePoint <= 0xDBFF) {
                if (i + 10 >= searchEnd || json[i + 5] != '\\' ||
                    json[i + 6] != 'u') {
                    return {};
                }
                int lowSurrogate = 0;
                for (int digit = 0; digit < 4; ++digit) {
                    int valueDigit = JsonHexDigit(json[i + 7 + digit]);
                    if (valueDigit < 0) return {};
                    lowSurrogate = lowSurrogate * 16 + valueDigit;
                }
                if (lowSurrogate < 0xDC00 || lowSurrogate > 0xDFFF) return {};
                codePoint = 0x10000 + ((codePoint - 0xD800) << 10) +
                    (lowSurrogate - 0xDC00);
                i += 10;
            } else {
                if (codePoint >= 0xDC00 && codePoint <= 0xDFFF) return {};
                i += 4;
            }
            AppendUtf8CodePoint(value, static_cast<uint32_t>(codePoint));
        } else {
            return {};
        }
    }
    return {};
}

static std::wstring NormalizeArtworkMatchText(const std::wstring& value) {
    std::wstring normalized;
    normalized.reserve(value.size());
    for (wchar_t c : value) {
        if (iswalnum(c)) {
            normalized.push_back(towlower(c));
        } else if (c == L'&') {
            normalized += L"and";
        }
    }
    return normalized;
}

static bool ArtworkFieldMatches(const std::wstring& expected,
                                const std::wstring& candidate,
                                bool allowContainedMatch = false) {
    std::wstring left = NormalizeArtworkMatchText(expected);
    std::wstring right = NormalizeArtworkMatchText(candidate);
    if (left.empty()) return true;
    if (right.empty()) return false;
    if (left == right) return true;
    return allowContainedMatch && std::min(left.size(), right.size()) >= 5 &&
        (left.find(right) != std::wstring::npos ||
         right.find(left) != std::wstring::npos);
}

static std::wstring ResolveAppleAlbumArtwork(const MediaState& media) {
    std::wstring query = media.title;
    if (!media.artist.empty()) query += L" " + media.artist;
    if (!media.albumTitle.empty()) query += L" " + media.albumTitle;
    if (query.empty()) return {};

    std::wstring path = L"/search?term=" + UrlEncodeQueryValue(query) +
        L"&media=music&entity=song&limit=10";
    std::string response = WinHttpGetUtf8(L"itunes.apple.com", path);
    size_t resultsMarker = response.find("\"results\"");
    size_t arrayStart = resultsMarker == std::string::npos
        ? std::string::npos
        : response.find('[', resultsMarker);
    if (arrayStart == std::string::npos) return {};

    std::string bestArtwork;
    int bestScore = -1;
    bool inString = false;
    bool escaped = false;
    int objectDepth = 0;
    size_t objectStart = std::string::npos;
    for (size_t i = arrayStart + 1; i < response.size(); ++i) {
        char c = response[i];
        if (inString) {
            if (escaped) {
                escaped = false;
            } else if (c == '\\') {
                escaped = true;
            } else if (c == '"') {
                inString = false;
            }
            continue;
        }
        if (c == '"') {
            inString = true;
        } else if (c == '{') {
            if (objectDepth++ == 0) objectStart = i;
        } else if (c == '}' && objectDepth > 0) {
            if (--objectDepth != 0 || objectStart == std::string::npos) continue;
            size_t objectEnd = i + 1;
            std::wstring candidateTitle = FromUtf8(ExtractJsonStringField(
                response, "trackName", objectStart, objectEnd));
            std::wstring candidateArtist = FromUtf8(ExtractJsonStringField(
                response, "artistName", objectStart, objectEnd));
            std::wstring candidateAlbum = FromUtf8(ExtractJsonStringField(
                response, "collectionName", objectStart, objectEnd));
            std::string candidateArtwork = ExtractJsonStringField(
                response, "artworkUrl100", objectStart, objectEnd);

            // Prefer no artwork over a confidently wrong release. The title
            // must match exactly after punctuation/case normalization. Artist
            // collaborations may use a longer API value. Album metadata ranks
            // releases but is not mandatory because local tags often abbreviate it.
            if (!ArtworkFieldMatches(media.title, candidateTitle) ||
                !ArtworkFieldMatches(media.artist, candidateArtist, true) ||
                candidateArtwork.rfind("https://", 0) != 0) {
                objectStart = std::string::npos;
                continue;
            }

            int score = 100;
            if (NormalizeArtworkMatchText(media.artist) ==
                NormalizeArtworkMatchText(candidateArtist)) {
                score += 50;
            }
            if (!media.albumTitle.empty() &&
                NormalizeArtworkMatchText(media.albumTitle) ==
                NormalizeArtworkMatchText(candidateAlbum)) {
                score += 30;
            } else if (!media.albumTitle.empty() &&
                       ArtworkFieldMatches(media.albumTitle,
                                           candidateAlbum, true)) {
                score += 15;
            }
            if (score > bestScore) {
                bestScore = score;
                bestArtwork = std::move(candidateArtwork);
            }
            objectStart = std::string::npos;
        } else if (c == ']' && objectDepth == 0) {
            break;
        }
    }
    if (bestArtwork.empty()) return {};

    // Apple's image endpoint returns a square center crop for the cc variant.
    size_t sizeMarker = bestArtwork.rfind("100x100bb");
    if (sizeMarker != std::string::npos) {
        bestArtwork.replace(sizeMarker, strlen("100x100bb"), "600x600cc");
    }
    return FromUtf8(bestArtwork);
}

static std::wstring ResolveDeezerAlbumArtwork(const MediaState& media) {
    std::wstring query = media.title;
    if (!media.artist.empty()) query += L" " + media.artist;
    if (!media.albumTitle.empty()) query += L" " + media.albumTitle;
    if (query.empty()) return {};

    std::wstring path = L"/search?q=" + UrlEncodeQueryValue(query) +
        L"&limit=10";
    std::string response = WinHttpGetUtf8(L"api.deezer.com", path);
    size_t dataMarker = response.find("\"data\"");
    size_t arrayStart = dataMarker == std::string::npos
        ? std::string::npos
        : response.find('[', dataMarker);
    if (arrayStart == std::string::npos) return {};

    std::string bestArtwork;
    int bestScore = -1;
    bool inString = false;
    bool escaped = false;
    int objectDepth = 0;
    size_t objectStart = std::string::npos;
    for (size_t i = arrayStart + 1; i < response.size(); ++i) {
        char c = response[i];
        if (inString) {
            if (escaped) {
                escaped = false;
            } else if (c == '\\') {
                escaped = true;
            } else if (c == '"') {
                inString = false;
            }
            continue;
        }
        if (c == '"') {
            inString = true;
        } else if (c == '{') {
            if (objectDepth++ == 0) objectStart = i;
        } else if (c == '}' && objectDepth > 0) {
            if (--objectDepth != 0 || objectStart == std::string::npos) continue;
            size_t objectEnd = i + 1;
            std::wstring candidateTitle = FromUtf8(ExtractJsonStringField(
                response, "title_short", objectStart, objectEnd));
            std::wstring candidateArtist = FromUtf8(ExtractJsonStringField(
                response, "name", objectStart, objectEnd));
            size_t albumMarker = response.find("\"album\":", objectStart);
            std::wstring candidateAlbum;
            if (albumMarker != std::string::npos && albumMarker < objectEnd) {
                candidateAlbum = FromUtf8(ExtractJsonStringField(
                    response, "title", albumMarker, objectEnd));
            }
            std::string candidateArtwork = ExtractJsonStringField(
                response, "cover_xl", objectStart, objectEnd);
            if (candidateArtwork.empty()) {
                candidateArtwork = ExtractJsonStringField(
                    response, "cover_big", objectStart, objectEnd);
            }

            if (!ArtworkFieldMatches(media.title, candidateTitle) ||
                !ArtworkFieldMatches(media.artist, candidateArtist, true) ||
                candidateArtwork.rfind("https://", 0) != 0) {
                objectStart = std::string::npos;
                continue;
            }

            int score = 100;
            if (NormalizeArtworkMatchText(media.artist) ==
                NormalizeArtworkMatchText(candidateArtist)) {
                score += 50;
            }
            if (!media.albumTitle.empty() &&
                NormalizeArtworkMatchText(media.albumTitle) ==
                NormalizeArtworkMatchText(candidateAlbum)) {
                score += 30;
            } else if (!media.albumTitle.empty() &&
                       ArtworkFieldMatches(media.albumTitle,
                                           candidateAlbum, true)) {
                score += 15;
            }
            if (score > bestScore) {
                bestScore = score;
                bestArtwork = std::move(candidateArtwork);
            }
            objectStart = std::string::npos;
        } else if (c == ']' && objectDepth == 0) {
            break;
        }
    }
    return FromUtf8(bestArtwork);
}

static bool IsMusicBrainzId(const std::string& value) {
    if (value.size() != 36) return false;
    for (size_t i = 0; i < value.size(); ++i) {
        if (i == 8 || i == 13 || i == 18 || i == 23) {
            if (value[i] != '-') return false;
        } else if (!std::isxdigit(static_cast<unsigned char>(value[i]))) {
            return false;
        }
    }
    return true;
}

static std::wstring ResolveMusicBrainzAlbumArtwork(const MediaState& media) {
    // Release-group lookup is deliberately used only when the player provides
    // an album tag. Matching an artist and album is much safer than guessing a
    // release from a track title alone.
    if (media.albumTitle.empty() || media.artist.empty()) return {};

    std::wstring query = L"releasegroup:\"" + media.albumTitle +
        L"\" AND artist:\"" + media.artist + L"\"";
    std::wstring path = L"/ws/2/release-group/?query=" +
        UrlEncodeQueryValue(query) + L"&fmt=json&limit=5";
    std::string response = WinHttpGetUtf8(L"musicbrainz.org", path);
    size_t resultsMarker = response.find("\"release-groups\"");
    size_t arrayStart = resultsMarker == std::string::npos
        ? std::string::npos
        : response.find('[', resultsMarker);
    if (arrayStart == std::string::npos) return {};

    bool inString = false;
    bool escaped = false;
    int objectDepth = 0;
    size_t objectStart = std::string::npos;
    int checkedCovers = 0;
    for (size_t i = arrayStart + 1; i < response.size(); ++i) {
        char c = response[i];
        if (inString) {
            if (escaped) {
                escaped = false;
            } else if (c == '\\') {
                escaped = true;
            } else if (c == '"') {
                inString = false;
            }
            continue;
        }
        if (c == '"') {
            inString = true;
        } else if (c == '{') {
            if (objectDepth++ == 0) objectStart = i;
        } else if (c == '}' && objectDepth > 0) {
            if (--objectDepth != 0 || objectStart == std::string::npos) continue;
            size_t objectEnd = i + 1;
            std::string candidateId = ExtractJsonStringField(
                response, "id", objectStart, objectEnd);
            std::wstring candidateAlbum = FromUtf8(ExtractJsonStringField(
                response, "title", objectStart, objectEnd));
            std::wstring candidateArtist = FromUtf8(ExtractJsonStringField(
                response, "name", objectStart, objectEnd));

            if (IsMusicBrainzId(candidateId) &&
                ArtworkFieldMatches(media.albumTitle, candidateAlbum, true) &&
                ArtworkFieldMatches(media.artist, candidateArtist, true)) {
                std::wstring id(candidateId.begin(), candidateId.end());
                std::wstring coverPath = L"/release-group/" + id +
                    L"/front-500";
                DWORD coverStatus = WinHttpHeadStatus(
                    L"coverartarchive.org", coverPath);
                // A transport failure here should not discard a valid catalog
                // match: Discord fetches the HTTPS image independently. An
                // explicit 404, however, means this release group has no front art.
                if (coverStatus == 0 ||
                    (coverStatus >= 200 && coverStatus < 400)) {
                    return L"https://coverartarchive.org" + coverPath;
                }
                if (++checkedCovers >= 2) return {};
            }
            objectStart = std::string::npos;
        } else if (c == ']' && objectDepth == 0) {
            break;
        }
    }
    return {};
}

static std::wstring ResolveOnlineAlbumArtwork(const MediaState& media) {
    std::wstring artwork = ResolveAppleAlbumArtwork(media);
    if (!artwork.empty()) {
        Wh_Log(L"Discord presence: artwork source Apple Music");
        return artwork;
    }

    artwork = ResolveDeezerAlbumArtwork(media);
    if (!artwork.empty()) {
        Wh_Log(L"Discord presence: artwork source Deezer");
        return artwork;
    }

    artwork = ResolveMusicBrainzAlbumArtwork(media);
    if (!artwork.empty()) {
        Wh_Log(L"Discord presence: artwork source Cover Art Archive");
    }
    return artwork;
}

static void ReplaceAll(std::wstring& value, const std::wstring& marker,
                       const std::wstring& replacement) {
    if (marker.empty()) return;
    size_t position = 0;
    while ((position = value.find(marker, position)) != std::wstring::npos) {
        value.replace(position, marker.size(), replacement);
        position += replacement.size();
    }
}

static std::wstring ResolveDiscordActivityName(
    const std::wstring& nameTemplate, const MediaState& media) {
    std::wstring result = nameTemplate;
    ReplaceAll(result, L"{title}", media.title);
    ReplaceAll(result, L"{artist}", media.artist);
    ReplaceAll(result, L"{album}", media.albumTitle);
    return result;
}

struct DiscordActivityTiming {
    bool valid = false;
    int64_t startEpochSeconds = 0;
    int64_t endEpochSeconds = 0;
};

static DiscordActivityTiming GetDiscordActivityTiming(
    const MediaState& media) {
    DiscordActivityTiming result;
    if (!media.isPlaying || media.durationSeconds <= 0) return result;

    int64_t position = std::clamp<int64_t>(
        media.positionSeconds, 0, media.durationSeconds);
    ULONGLONG nowTick = GetTickCount64();
    if (media.timelineSampleTick && nowTick > media.timelineSampleTick) {
        position = std::min<int64_t>(
            media.durationSeconds,
            position + static_cast<int64_t>(
                (nowTick - media.timelineSampleTick) / 1000));
    }

    int64_t nowEpoch = std::chrono::duration_cast<std::chrono::seconds>(
        std::chrono::system_clock::now().time_since_epoch()).count();
    result.valid = true;
    result.startEpochSeconds = nowEpoch - position;
    result.endEpochSeconds = result.startEpochSeconds + media.durationSeconds;
    return result;
}

static bool DiscordPipeWriteAll(HANDLE pipe, const void* data, DWORD size) {
    const BYTE* cursor = static_cast<const BYTE*>(data);
    while (size > 0) {
        DWORD written = 0;
        if (!WriteFile(pipe, cursor, size, &written, nullptr) || !written) {
            return false;
        }
        cursor += written;
        size -= written;
    }
    return true;
}

static bool DiscordPipeWaitForBytes(HANDLE pipe, DWORD count,
                                    DWORD timeoutMs) {
    ULONGLONG deadline = GetTickCount64() + timeoutMs;
    while (GetTickCount64() < deadline) {
        if (g_discordPresenceStopEvent &&
            WaitForSingleObject(g_discordPresenceStopEvent, 0) == WAIT_OBJECT_0) {
            return false;
        }
        DWORD available = 0;
        if (!PeekNamedPipe(pipe, nullptr, 0, nullptr, &available, nullptr)) {
            return false;
        }
        if (available >= count) return true;
        Sleep(10);
    }
    return false;
}

static bool DiscordPipeReadAll(HANDLE pipe, void* data, DWORD size,
                               DWORD timeoutMs) {
    BYTE* cursor = static_cast<BYTE*>(data);
    while (size > 0) {
        if (!DiscordPipeWaitForBytes(pipe, 1, timeoutMs)) return false;
        DWORD read = 0;
        if (!ReadFile(pipe, cursor, size, &read, nullptr) || !read) {
            return false;
        }
        cursor += read;
        size -= read;
    }
    return true;
}

static bool DiscordPipeWriteFrame(HANDLE pipe, uint32_t opcode,
                                  const std::string& payload) {
    if (payload.size() > 1024 * 1024) return false;
    DiscordIpcHeader header{opcode, static_cast<uint32_t>(payload.size())};
    return DiscordPipeWriteAll(pipe, &header, sizeof(header)) &&
           DiscordPipeWriteAll(pipe, payload.data(), header.length);
}

static bool DiscordPipeReadFrame(HANDLE pipe, uint32_t& opcode,
                                 std::string& payload, DWORD timeoutMs) {
    DiscordIpcHeader header{};
    if (!DiscordPipeReadAll(pipe, &header, sizeof(header), timeoutMs) ||
        header.length > 1024 * 1024) {
        return false;
    }
    payload.assign(header.length, '\0');
    if (header.length &&
        !DiscordPipeReadAll(pipe, payload.data(), header.length, timeoutMs)) {
        return false;
    }
    opcode = header.opcode;
    return true;
}

static HANDLE ConnectDiscordPresencePipe(const std::wstring& applicationId) {
    HANDLE pipe = INVALID_HANDLE_VALUE;
    for (int i = 0; i < 10 && pipe == INVALID_HANDLE_VALUE; ++i) {
        std::wstring path = L"\\\\.\\pipe\\discord-ipc-" +
                            std::to_wstring(i);
        pipe = CreateFileW(path.c_str(), GENERIC_READ | GENERIC_WRITE,
                           0, nullptr, OPEN_EXISTING, 0, nullptr);
    }
    if (pipe == INVALID_HANDLE_VALUE) return INVALID_HANDLE_VALUE;

    std::string handshake = "{\"v\":1,\"client_id\":\"" +
        JsonEscapeUtf8(ToUtf8(applicationId)) + "\"}";
    if (!DiscordPipeWriteFrame(pipe, 0, handshake)) {
        CloseHandle(pipe);
        return INVALID_HANDLE_VALUE;
    }

    for (int attempt = 0; attempt < 4; ++attempt) {
        uint32_t opcode = 0;
        std::string response;
        if (!DiscordPipeReadFrame(pipe, opcode, response, 1200)) break;
        if (opcode == 3) {
            if (!DiscordPipeWriteFrame(pipe, 4, response)) break;
            continue;
        }
        if (opcode == 1 &&
            response.find("\"evt\":\"READY\"") != std::string::npos) {
            Wh_Log(L"Discord presence: connected");
            return pipe;
        }
        if (opcode == 2 || response.find("ERROR") != std::string::npos) break;
    }

    CloseHandle(pipe);
    return INVALID_HANDLE_VALUE;
}

static std::string MakeDiscordActivityCommand(
    const MediaState& media, bool publish,
    const DiscordActivityTiming& timing,
    const std::wstring& largeImage,
    const std::wstring& activityName) {
    uint64_t nonce = g_discordNonce.fetch_add(1);
    std::string command = "{\"cmd\":\"SET_ACTIVITY\",\"args\":{";
    command += "\"pid\":" + std::to_string(GetCurrentProcessId()) +
               ",\"activity\":";

    if (!publish) {
        command += "null";
    } else {
        std::string title = JsonEscapeUtf8(LimitUtf8(ToUtf8(media.title)));
        std::wstring stateText = media.artist.empty()
            ? L"Unknown artist"
            : media.artist;
        if (!media.isPlaying) stateText = L"Paused - " + stateText;
        std::string state = JsonEscapeUtf8(LimitUtf8(ToUtf8(stateText)));
        command += "{\"type\":2";
        if (!activityName.empty()) {
            command += ",\"name\":\"" +
                JsonEscapeUtf8(LimitUtf8(ToUtf8(activityName), 128)) + "\"";
        }
        command += ",\"details\":\"" + title +
                   "\",\"state\":\"" + state + "\"";
        if (timing.valid) {
            command += ",\"timestamps\":{\"start\":" +
                std::to_string(timing.startEpochSeconds) +
                ",\"end\":" + std::to_string(timing.endEpochSeconds) + "}";
        }
        if (!largeImage.empty()) {
            command += ",\"assets\":{\"large_image\":\"" +
                JsonEscapeUtf8(LimitUtf8(ToUtf8(largeImage), 512)) +
                "\"}";
        }
        command += ",\"instance\":true}";
    }

    command += "},\"nonce\":\"" + std::to_string(nonce) + "\"}";
    return command;
}

static bool SendDiscordActivity(HANDLE pipe, const MediaState& media,
                                bool publish,
                                const DiscordActivityTiming& timing,
                                const std::wstring& largeImage,
                                const std::wstring& activityName) {
    std::string command = MakeDiscordActivityCommand(
        media, publish, timing, largeImage, activityName);
    if (!DiscordPipeWriteFrame(pipe, 1, command)) return false;

    for (int attempt = 0; attempt < 4; ++attempt) {
        uint32_t opcode = 0;
        std::string response;
        if (!DiscordPipeReadFrame(pipe, opcode, response, 1000)) return false;
        if (opcode == 3) {
            if (!DiscordPipeWriteFrame(pipe, 4, response)) return false;
            continue;
        }
        return opcode == 1 &&
               response.find("\"evt\":\"ERROR\"") == std::string::npos;
    }
    return false;
}

static DWORD WINAPI DiscordPresenceThreadProc(void*) {
    const std::wstring applicationId = g_settings.discordApplicationId;
    const bool showPaused = g_settings.discordShowPaused;
    const std::wstring activityNameTemplate = g_settings.discordActivityName;
    const bool fetchOnlineArtwork = g_settings.discordFetchOnlineArtwork;
    const std::wstring fallbackImageKey = g_settings.discordLargeImageKey;
    HANDLE pipe = INVALID_HANDLE_VALUE;
    std::wstring lastStateKey;
    std::wstring artworkTrackKey;
    std::wstring resolvedArtwork;
    ULONGLONG lastArtworkLookupTick = 0;
    bool published = false;

    while (WaitForSingleObject(g_discordPresenceStopEvent, 0) != WAIT_OBJECT_0) {
        MediaState media;
        {
            std::lock_guard<std::mutex> lock(g_mediaMtx);
            media = g_media;
        }
        bool shouldPublish = media.hasMedia && !media.title.empty() &&
                             (media.isPlaying || showPaused);
        std::wstring currentArtworkTrackKey = media.title + L"\n" +
            media.artist + L"\n" + media.albumTitle;
        if (shouldPublish && fetchOnlineArtwork &&
            currentArtworkTrackKey != artworkTrackKey) {
            artworkTrackKey = currentArtworkTrackKey;
            resolvedArtwork.clear();

            ULONGLONG nowTick = GetTickCount64();
            if (lastArtworkLookupTick && nowTick - lastArtworkLookupTick < 3100) {
                DWORD delay = static_cast<DWORD>(
                    3100 - (nowTick - lastArtworkLookupTick));
                if (WaitForSingleObject(g_discordPresenceStopEvent, delay) ==
                    WAIT_OBJECT_0) {
                    break;
                }
            }
            lastArtworkLookupTick = GetTickCount64();
            resolvedArtwork = ResolveOnlineAlbumArtwork(media);
            Wh_Log(L"Discord presence: album artwork %ls",
                   resolvedArtwork.empty() ? L"not found; using fallback"
                                           : L"resolved");

            MediaState currentMedia;
            {
                std::lock_guard<std::mutex> lock(g_mediaMtx);
                currentMedia = g_media;
            }
            std::wstring currentKey = currentMedia.title + L"\n" +
                currentMedia.artist + L"\n" + currentMedia.albumTitle;
            if (currentKey != artworkTrackKey) continue;
        }

        std::wstring largeImage = !resolvedArtwork.empty()
            ? resolvedArtwork
            : fallbackImageKey;
        std::wstring activityName = ResolveDiscordActivityName(
            activityNameTemplate, media);
        DiscordActivityTiming timing = GetDiscordActivityTiming(media);
        std::wstring stateKey = shouldPublish
            ? media.title + L"\n" + media.artist + L"\n" + media.albumTitle +
                L"\n" + (media.isPlaying ? L"playing" : L"paused") +
                L"\n" + largeImage + L"\n" + activityName + L"\n" +
                (timing.valid
                    ? std::to_wstring(timing.startEpochSeconds) + L":" +
                        std::to_wstring(timing.endEpochSeconds)
                    : L"no-timeline")
            : L"<clear>";

        if (pipe == INVALID_HANDLE_VALUE) {
            pipe = ConnectDiscordPresencePipe(applicationId);
            lastStateKey.clear();
        }

        if (pipe != INVALID_HANDLE_VALUE && stateKey != lastStateKey) {
            if (SendDiscordActivity(pipe, media, shouldPublish,
                                    timing, largeImage, activityName)) {
                lastStateKey = stateKey;
                published = shouldPublish;
                Wh_Log(L"Discord presence: %ls",
                       shouldPublish ? L"activity updated" : L"activity cleared");
            } else {
                CloseHandle(pipe);
                pipe = INVALID_HANDLE_VALUE;
                lastStateKey.clear();
            }
        }

        HANDLE waits[] = {g_discordPresenceStopEvent,
                          g_discordPresenceUpdateEvent};
        DWORD wait = WaitForMultipleObjects(2, waits, FALSE, 5000);
        if (wait == WAIT_OBJECT_0) break;
        if (wait == WAIT_TIMEOUT && pipe != INVALID_HANDLE_VALUE) {
            DWORD available = 0;
            if (!PeekNamedPipe(pipe, nullptr, 0, nullptr, &available, nullptr)) {
                CloseHandle(pipe);
                pipe = INVALID_HANDLE_VALUE;
                lastStateKey.clear();
            }
        }
    }

    if (pipe != INVALID_HANDLE_VALUE) {
        if (published) {
            MediaState empty;
            SendDiscordActivity(pipe, empty, false,
                                DiscordActivityTiming{}, L"", L"");
        }
        CloseHandle(pipe);
    }
    return 0;
}

static void SignalDiscordPresenceUpdate() {
    if (g_discordPresenceUpdateEvent) {
        SetEvent(g_discordPresenceUpdateEvent);
    }
}

static void StartDiscordPresenceThread() {
    if (g_discordPresenceThread || !g_settings.discordPresenceEnabled) return;
    if (!IsValidDiscordApplicationId(g_settings.discordApplicationId)) {
        if (!g_settings.discordApplicationId.empty()) {
            Wh_Log(L"Discord presence: Application ID must contain only digits");
        } else {
            Wh_Log(L"Discord presence: waiting for an Application ID in settings");
        }
        return;
    }

    g_discordPresenceStopEvent = CreateEventW(nullptr, TRUE, FALSE, nullptr);
    g_discordPresenceUpdateEvent = CreateEventW(nullptr, FALSE, TRUE, nullptr);
    if (!g_discordPresenceStopEvent || !g_discordPresenceUpdateEvent) {
        Wh_Log(L"Discord presence: failed to create worker events");
        if (g_discordPresenceStopEvent) {
            CloseHandle(g_discordPresenceStopEvent);
            g_discordPresenceStopEvent = nullptr;
        }
        if (g_discordPresenceUpdateEvent) {
            CloseHandle(g_discordPresenceUpdateEvent);
            g_discordPresenceUpdateEvent = nullptr;
        }
        return;
    }
    g_discordPresenceThread = CreateThread(
        nullptr, 0, DiscordPresenceThreadProc, nullptr, 0, nullptr);
    if (!g_discordPresenceThread) {
        CloseHandle(g_discordPresenceStopEvent);
        CloseHandle(g_discordPresenceUpdateEvent);
        g_discordPresenceStopEvent = nullptr;
        g_discordPresenceUpdateEvent = nullptr;
    }
}

static void StopDiscordPresenceThread() {
    if (g_discordPresenceStopEvent) SetEvent(g_discordPresenceStopEvent);
    if (g_discordPresenceThread) {
        using CancelSynchronousIoFn = BOOL(WINAPI*)(HANDLE);
        HMODULE kernel32 = GetModuleHandleW(L"kernel32.dll");
        auto cancelSynchronousIo = kernel32
            ? reinterpret_cast<CancelSynchronousIoFn>(
                  GetProcAddress(kernel32, "CancelSynchronousIo"))
            : nullptr;
        if (cancelSynchronousIo) {
            cancelSynchronousIo(g_discordPresenceThread);
        }
        DWORD waitResult = WaitForSingleObject(g_discordPresenceThread, 12000);
        if (waitResult != WAIT_OBJECT_0) {
            Wh_Log(L"Discord presence: worker did not stop safely (result %lu)",
                   waitResult);
            return;
        }
        CloseHandle(g_discordPresenceThread);
        g_discordPresenceThread = nullptr;
    }
    if (g_discordPresenceStopEvent) {
        CloseHandle(g_discordPresenceStopEvent);
        g_discordPresenceStopEvent = nullptr;
    }
    if (g_discordPresenceUpdateEvent) {
        CloseHandle(g_discordPresenceUpdateEvent);
        g_discordPresenceUpdateEvent = nullptr;
    }
}

enum class RepeatMode {
    Off = 0,
    All = 1,
    One = 2,
};

static std::atomic<bool> g_shuffleEnabled{false};
static std::atomic<RepeatMode> g_repeatMode{RepeatMode::Off};

static std::wstring g_cachedAlbumTitle;
static std::wstring g_cachedAlbumArtist;
static std::vector<BYTE> g_cachedThumbnailBytes;
static int g_cachedAppIconSize = -1;

static std::wstring g_scrollCachedTitle;
static std::wstring g_scrollCachedArtist;

struct BlurBgCache {
    std::vector<BYTE>  blurredPixels;
    int                width  = 0;
    int                height = 0;
    size_t             artHash = 0;

    void Invalidate() {
        blurredPixels.clear();
        width = height = 0;
        artHash = 0;
    }
} g_blurBgCache;

struct AlbumPalette {
    winrt::Windows::UI::Color primary;
    winrt::Windows::UI::Color secondary;
};

static AlbumPalette g_cachedAlbumPalette = {
    winrt::Windows::UI::Color{255, 18, 18, 18},
    winrt::Windows::UI::Color{255, 45, 45, 45}
};
static size_t g_cachedPaletteHash = 0;


static GlobalSystemMediaTransportControlsSessionManager g_sessionMgr     = nullptr;
static GlobalSystemMediaTransportControlsSession        g_currentSession = nullptr;
static std::mutex  g_sessionMtx;
static bool g_userSwitchedSession = false;
static std::atomic<bool> g_forceSessionRefresh{false};
static std::atomic<int> g_sessionCount{0};

static winrt::event_token g_evSessionsChanged{};
static winrt::event_token g_evCurrentChanged{};
static winrt::event_token g_evMediaProps{};
static winrt::event_token g_evPlayback{};
static winrt::event_token g_evTimeline{};

static HANDLE g_mediaThread    = nullptr;
static HANDLE g_mediaStopEvent = nullptr;

static bool IsSystemLightTheme() {
    DWORD v = 0, sz = sizeof(v);
    if (RegGetValueW(HKEY_CURRENT_USER,
        L"Software\\Microsoft\\Windows\\CurrentVersion\\Themes\\Personalize",
        L"SystemUsesLightTheme", RRF_RT_DWORD, nullptr, &v, &sz) == ERROR_SUCCESS) {
        return v != 0;
    }
    v = 0; sz = sizeof(v);
    RegGetValueW(HKEY_CURRENT_USER,
        L"Software\\Microsoft\\Windows\\CurrentVersion\\Themes\\Personalize",
        L"AppsUseLightTheme", RRF_RT_DWORD, nullptr, &v, &sz);
    return v != 0;
}

static SolidColorBrush MakeBrush(winrt::Windows::UI::Color c) {
    SolidColorBrush b; b.Color(c); return b;
}

static bool IsHoverEffectEnabled(std::wstring const& mode) {
    return mode != L"off";
}

static bool IsHoverLightTheme(std::wstring const& mode) {
    if (mode == L"white") return true;
    if (mode == L"black") return false;
    return IsSystemLightTheme();
}

static winrt::Windows::UI::Color GetSystemButtonHoverColor(std::wstring const& mode) {
    if (IsHoverLightTheme(mode)) {
        return winrt::Windows::UI::Color{0x99, 0xFF, 0xFF, 0xFF};
    }
    return winrt::Windows::UI::Color{0x0F, 0xFF, 0xFF, 0xFF};
}

static winrt::Windows::UI::Color GetSystemButtonPressedColor(std::wstring const& mode) {
    if (IsHoverLightTheme(mode)) {
        return winrt::Windows::UI::Color{0x4D, 0xFF, 0xFF, 0xFF};
    }
    return winrt::Windows::UI::Color{0x0A, 0xFF, 0xFF, 0xFF};
}

static winrt::Windows::UI::Color GetSystemButtonBorderColor(std::wstring const& mode) {
    if (IsHoverLightTheme(mode)) {
        return winrt::Windows::UI::Color{0x08, 0x00, 0x00, 0x00};
    }
    return winrt::Windows::UI::Color{0x14, 0xFF, 0xFF, 0xFF};
}

static winrt::Windows::UI::Color GetSystemButtonBorderPressedColor(std::wstring const& mode) {
    if (IsHoverLightTheme(mode)) {
        return winrt::Windows::UI::Color{0x05, 0x00, 0x00, 0x00};
    }
    return winrt::Windows::UI::Color{0x0A, 0xFF, 0xFF, 0xFF};
}

static SolidColorBrush g_mediaHoverBrush   = nullptr;
static SolidColorBrush g_mediaPressedBrush = nullptr;
static SolidColorBrush g_playerHoverBrush   = nullptr;
static SolidColorBrush g_playerPressedBrush = nullptr;
static SolidColorBrush g_playerBorderBrush  = nullptr;
static SolidColorBrush g_playerBorderPressedBrush = nullptr;

static void EnsureHoverBrushes() {
    if (!g_mediaHoverBrush) {
        g_mediaHoverBrush   = SolidColorBrush(GetSystemButtonHoverColor(g_settings.mediaButtonsHoverEffectMode));
        g_mediaPressedBrush = SolidColorBrush(GetSystemButtonPressedColor(g_settings.mediaButtonsHoverEffectMode));
    }
    if (!g_playerHoverBrush) {
        g_playerHoverBrush   = SolidColorBrush(GetSystemButtonHoverColor(g_settings.playerHoverEffectMode));
        g_playerPressedBrush = SolidColorBrush(GetSystemButtonPressedColor(g_settings.playerHoverEffectMode));
        g_playerBorderBrush  = SolidColorBrush(GetSystemButtonBorderColor(g_settings.playerHoverEffectMode));
        g_playerBorderPressedBrush = SolidColorBrush(GetSystemButtonBorderPressedColor(g_settings.playerHoverEffectMode));
    }
}

static void UpdateHoverBrushColors() {
    if (g_mediaHoverBrush) {
        try { g_mediaHoverBrush.Color(GetSystemButtonHoverColor(g_settings.mediaButtonsHoverEffectMode)); } catch (...) {}
    } else {
        try { g_mediaHoverBrush = SolidColorBrush(GetSystemButtonHoverColor(g_settings.mediaButtonsHoverEffectMode)); } catch (...) {}
    }
    if (g_mediaPressedBrush) {
        try { g_mediaPressedBrush.Color(GetSystemButtonPressedColor(g_settings.mediaButtonsHoverEffectMode)); } catch (...) {}
    } else {
        try { g_mediaPressedBrush = SolidColorBrush(GetSystemButtonPressedColor(g_settings.mediaButtonsHoverEffectMode)); } catch (...) {}
    }

    if (g_playerHoverBrush) {
        try { g_playerHoverBrush.Color(GetSystemButtonHoverColor(g_settings.playerHoverEffectMode)); } catch (...) {}
    } else {
        try { g_playerHoverBrush = SolidColorBrush(GetSystemButtonHoverColor(g_settings.playerHoverEffectMode)); } catch (...) {}
    }
    if (g_playerPressedBrush) {
        try { g_playerPressedBrush.Color(GetSystemButtonPressedColor(g_settings.playerHoverEffectMode)); } catch (...) {}
    } else {
        try { g_playerPressedBrush = SolidColorBrush(GetSystemButtonPressedColor(g_settings.playerHoverEffectMode)); } catch (...) {}
    }
    if (g_playerBorderBrush) {
        try { g_playerBorderBrush.Color(GetSystemButtonBorderColor(g_settings.playerHoverEffectMode)); } catch (...) {}
    } else {
        try { g_playerBorderBrush = SolidColorBrush(GetSystemButtonBorderColor(g_settings.playerHoverEffectMode)); } catch (...) {}
    }
    if (g_playerBorderPressedBrush) {
        try { g_playerBorderPressedBrush.Color(GetSystemButtonBorderPressedColor(g_settings.playerHoverEffectMode)); } catch (...) {}
    } else {
        try { g_playerBorderPressedBrush = SolidColorBrush(GetSystemButtonBorderPressedColor(g_settings.playerHoverEffectMode)); } catch (...) {}
    }
}

static ObjectAnimationUsingKeyFrames MakeDiscreteObjectAnimation(
    DependencyObject const& target,
    const wchar_t* propertyPath,
    winrt::Windows::Foundation::IInspectable const& value)
{
    ObjectAnimationUsingKeyFrames anim;
    anim.EnableDependentAnimation(true);
    DiscreteObjectKeyFrame kf;
    kf.Value(value);
    anim.KeyFrames().Append(kf);
    Storyboard::SetTarget(anim, target);
    Storyboard::SetTargetProperty(anim, winrt::hstring(propertyPath));
    return anim;
}

static Storyboard MakeRootBorderStoryboard(
    Border const& root,
    Brush const& background,
    Brush const& borderBrush)
{
    Storyboard sb;
    sb.Children().Append(MakeDiscreteObjectAnimation(
        root, L"Background", winrt::box_value(background)));
    sb.Children().Append(MakeDiscreteObjectAnimation(
        root, L"BorderBrush", winrt::box_value(borderBrush)));
    return sb;
}

static VisualState FindVisualState(VisualStateGroup const& group, std::wstring_view name) {
    for (auto const& state : group.States()) {
        if (state.Name() == name) return state;
    }
    return nullptr;
}

static Border GetButtonTemplateRoot(Button const& btn) {
    if (!btn) return nullptr;
    try {
        btn.ApplyTemplate();
        if (VisualTreeHelper::GetChildrenCount(btn) > 0) {
            if (auto border = VisualTreeHelper::GetChild(btn, 0).try_as<Border>())
                return border;
        }
        if (auto named = btn.FindName(L"Root")) {
            if (auto border = named.try_as<Border>()) return border;
        }
    } catch (...) {}
    return nullptr;
}

static VisualStateGroup FindCommonStatesGroup(Button const& btn) {
    if (auto root = GetButtonTemplateRoot(btn)) {
        for (auto const& group : VisualStateManager::GetVisualStateGroups(root)) {
            if (group.Name() == L"CommonStates") return group;
        }
    }
    for (auto const& group : VisualStateManager::GetVisualStateGroups(btn)) {
        if (group.Name() == L"CommonStates") return group;
    }
    return nullptr;
}

static Style CreateFluentMediaButtonStyle() {
    static const wchar_t kStyleXaml[] = LR"(<Style TargetType="Button"
    xmlns="http://schemas.microsoft.com/winfx/2006/xaml/presentation"
    xmlns:x="http://schemas.microsoft.com/winfx/2006/xaml">
  <Setter Property="Background" Value="Transparent"/>
  <Setter Property="BorderBrush" Value="Transparent"/>
  <Setter Property="BorderThickness" Value="0"/>
  <Setter Property="UseSystemFocusVisuals" Value="False"/>
  <Setter Property="Template">
    <Setter.Value>
      <ControlTemplate TargetType="Button">
        <Border x:Name="Root"
                Background="{TemplateBinding Background}"
                BorderBrush="{TemplateBinding BorderBrush}"
                BorderThickness="{TemplateBinding BorderThickness}"
                CornerRadius="{TemplateBinding CornerRadius}"
                Padding="{TemplateBinding Padding}">
          <VisualStateManager.VisualStateGroups>
            <VisualStateGroup x:Name="CommonStates">
              <VisualState x:Name="Normal"/>
              <VisualState x:Name="PointerOver"/>
              <VisualState x:Name="Pressed"/>
              <VisualState x:Name="Disabled"/>
            </VisualStateGroup>
          </VisualStateManager.VisualStateGroups>
          <ContentPresenter Content="{TemplateBinding Content}"
                            ContentTransitions="{TemplateBinding ContentTransitions}"
                            ContentTemplate="{TemplateBinding ContentTemplate}"
                            HorizontalContentAlignment="{TemplateBinding HorizontalContentAlignment}"
                            VerticalContentAlignment="{TemplateBinding VerticalContentAlignment}"/>
        </Border>
      </ControlTemplate>
    </Setter.Value>
  </Setter>
</Style>)";

    try {
        return winrt::Windows::UI::Xaml::Markup::XamlReader::Load(
            winrt::hstring(kStyleXaml)).as<Style>();
    } catch (...) {
        return nullptr;
    }
}

static Style GetFluentMediaButtonStyle() {
    return CreateFluentMediaButtonStyle();
}

static void ApplyFluentMediaButtonStyle(Button const& btn) {
    if (auto style = GetFluentMediaButtonStyle()) {
        btn.Style(style);
    }
}

static void ApplyFreshFluentMediaButtonStyle(Button const& btn) {
    if (auto style = CreateFluentMediaButtonStyle()) {
        btn.Style(style);
    }
}

static void SetupCommonStates(
    Button const& btn,
    Brush const& normalBackground,
    Brush const& pointerOverBackground,
    Brush const& pressedBackground,
    Brush const& disabledBackground,
    Brush const& normalBorderBrush,
    Brush const& pointerOverBorderBrush,
    Brush const& pressedBorderBrush,
    Brush const& disabledBorderBrush)
{
    auto root = GetButtonTemplateRoot(btn);
    if (!root) return;

    auto commonStates = FindCommonStatesGroup(btn);
    if (!commonStates) return;

    auto assignStoryboard = [&](std::wstring_view name, Brush const& bg, Brush const& border) {
        if (auto state = FindVisualState(commonStates, name)) {
            state.Storyboard(MakeRootBorderStoryboard(root, bg, border));
        }
    };

    assignStoryboard(L"Normal", normalBackground, normalBorderBrush);
    assignStoryboard(L"PointerOver", pointerOverBackground, pointerOverBorderBrush);
    assignStoryboard(L"Pressed", pressedBackground, pressedBorderBrush);
    assignStoryboard(L"Disabled", disabledBackground, disabledBorderBrush);
}

static void GoToCommonState(Button const& btn, bool effectEnabled, bool pressed, bool hovered) {
    if (!btn) return;
    winrt::hstring stateName = L"Normal";
    if (effectEnabled) {
        if (pressed) {
            stateName = L"Pressed";
        } else if (hovered) {
            stateName = L"PointerOver";
        }
    }
    try {
        VisualStateManager::GoToState(btn, stateName, true);
    } catch (...) {}
}

static void RunWhenButtonReady(Button const& btn, std::function<void()> const& action) {
    if (!btn || !action) return;
    auto run = std::make_shared<std::function<void()>>(action);
    auto invoke = [btn, run]() {
        try {
            btn.ApplyTemplate();
            (*run)();
        } catch (...) {}
    };
    try {
        if (btn.IsLoaded()) {
            invoke();
        } else {
            btn.Loaded([invoke](auto const&, auto const&) { invoke(); });
        }
    } catch (...) {
        invoke();
    }
}

static void SetupMediaButtonCommonStates(Button const& btn) {
    auto transparent = MakeBrush({0x00, 0, 0, 0});
    if (!IsHoverEffectEnabled(g_settings.mediaButtonsHoverEffectMode)) {
        SetupCommonStates(
            btn,
            transparent, transparent, transparent, transparent,
            transparent, transparent, transparent, transparent);
        return;
    }
    EnsureHoverBrushes();
    SetupCommonStates(
        btn,
        transparent,
        g_mediaHoverBrush,
        g_mediaPressedBrush,
        transparent,
        transparent, transparent, transparent, transparent);
}

static Brush MakeElevationBorderBrush(std::wstring const& mode) {
    bool light = IsHoverLightTheme(mode);
    winrt::Windows::UI::Color topColor, bottomColor;
    if (light) {
        topColor    = winrt::Windows::UI::Color{0x08, 0x00, 0x00, 0x00};
        bottomColor = winrt::Windows::UI::Color{0x10, 0x00, 0x00, 0x00};
    } else {
        topColor    = winrt::Windows::UI::Color{0x28, 0xFF, 0xFF, 0xFF};
        bottomColor = winrt::Windows::UI::Color{0x0A, 0xFF, 0xFF, 0xFF};
    }
    try {
        winrt::Windows::UI::Xaml::Media::LinearGradientBrush brush;
        brush.StartPoint(winrt::Windows::Foundation::Point(0.5f, 0.0f));
        brush.EndPoint(winrt::Windows::Foundation::Point(0.5f, 1.0f));
        winrt::Windows::UI::Xaml::Media::GradientStop s1, s2;
        s1.Color(topColor);    s1.Offset(0.0);
        s2.Color(bottomColor); s2.Offset(1.0);
        brush.GradientStops().Append(s1);
        brush.GradientStops().Append(s2);
        return brush;
    } catch (...) {
        return MakeBrush(topColor);
    }
}

static void SetupPlayerCommonStates(Button const& btn, Brush const& normalBg) {
    auto transparent = MakeBrush({0x00, 0, 0, 0});
    if (!IsHoverEffectEnabled(g_settings.playerHoverEffectMode)) {
        SetupCommonStates(
            btn,
            normalBg, normalBg, normalBg, normalBg,
            transparent, transparent, transparent, transparent);
        return;
    }
    EnsureHoverBrushes();
    auto elevBorder        = MakeElevationBorderBrush(g_settings.playerHoverEffectMode);
    auto elevBorderPressed = MakeBrush(GetSystemButtonBorderPressedColor(g_settings.playerHoverEffectMode));
    SetupCommonStates(
        btn,
        normalBg,
        g_playerHoverBrush,
        g_playerPressedBrush,
        normalBg,
        transparent,
        elevBorder,
        elevBorderPressed,
        transparent);
}

static void ApplyPlayerButtonState(Button const& btn, Brush const& /*normalBg*/, bool hovered, bool pressed) {
    if (!btn) return;
    try {
        GoToCommonState(btn, IsHoverEffectEnabled(g_settings.playerHoverEffectMode), pressed, hovered);
    } catch (...) {}
}

static bool DecodeImageToBGRA(const std::vector<BYTE>& imgBytes,
                               std::vector<BYTE>& outPixels,
                               int& outW, int& outH)
{
    if (imgBytes.empty()) return false;
    IWICImagingFactory* pFactory = nullptr;
    if (FAILED(CoCreateInstance(CLSID_WICImagingFactory, nullptr,
                                CLSCTX_INPROC_SERVER,
                                IID_PPV_ARGS(&pFactory))) || !pFactory)
        return false;
    IStream* pStream = SHCreateMemStream(imgBytes.data(), (UINT)imgBytes.size());
    if (!pStream) { pFactory->Release(); return false; }
    bool ok = false;
    IWICBitmapDecoder* pDecoder = nullptr;
    if (SUCCEEDED(pFactory->CreateDecoderFromStream(
            pStream, nullptr, WICDecodeMetadataCacheOnDemand, &pDecoder))) {
        IWICBitmapFrameDecode* pFrame = nullptr;
        if (SUCCEEDED(pDecoder->GetFrame(0, &pFrame))) {
            IWICFormatConverter* pConv = nullptr;
            if (SUCCEEDED(pFactory->CreateFormatConverter(&pConv))) {
                if (SUCCEEDED(pConv->Initialize(
                        pFrame, GUID_WICPixelFormat32bppBGRA,
                        WICBitmapDitherTypeNone, nullptr, 0.0,
                        WICBitmapPaletteTypeMedianCut))) {
                    UINT w = 0, h = 0;
                    pConv->GetSize(&w, &h);
                    if (w > 0 && h > 0) {
                        outPixels.resize((size_t)w * h * 4);
                        if (SUCCEEDED(pConv->CopyPixels(nullptr, w * 4,
                                (UINT)outPixels.size(), outPixels.data()))) {
                            outW = (int)w; outH = (int)h; ok = true;
                        }
                    }
                }
                pConv->Release();
            }
            pFrame->Release();
        }
        pDecoder->Release();
    }
    pStream->Release();
    pFactory->Release();
    return ok;
}

static void DownsampleBGRA(const std::vector<BYTE>& src, int srcW, int srcH,
                            std::vector<BYTE>& dst, int dstW, int dstH)
{
    dst.resize((size_t)dstW * dstH * 4);
    float xr = (float)srcW / dstW, yr = (float)srcH / dstH;
    for (int dy = 0; dy < dstH; ++dy) {
        for (int dx = 0; dx < dstW; ++dx) {
            float sx = (dx + 0.5f) * xr - 0.5f;
            float sy = (dy + 0.5f) * yr - 0.5f;
            int x0 = (int)sx; if (x0 < 0) x0 = 0;
            int y0 = (int)sy; if (y0 < 0) y0 = 0;
            int x1 = x0 + 1; if (x1 >= srcW) x1 = srcW - 1;
            int y1 = y0 + 1; if (y1 >= srcH) y1 = srcH - 1;
            float fx = sx - (float)x0; if (fx < 0) fx = 0;
            float fy = sy - (float)y0; if (fy < 0) fy = 0;
            const BYTE* p00 = &src[((size_t)y0 * srcW + x0) * 4];
            const BYTE* p10 = &src[((size_t)y0 * srcW + x1) * 4];
            const BYTE* p01 = &src[((size_t)y1 * srcW + x0) * 4];
            const BYTE* p11 = &src[((size_t)y1 * srcW + x1) * 4];
            BYTE* d = &dst[((size_t)dy * dstW + dx) * 4];
            for (int c = 0; c < 4; ++c) {
                float v = p00[c]*(1-fx)*(1-fy) + p10[c]*fx*(1-fy)
                        + p01[c]*(1-fx)*fy     + p11[c]*fx*fy;
                d[c] = (BYTE)(v < 0 ? 0 : v > 255 ? 255 : (int)v);
            }
        }
    }
}

static void ApplyBoxBlurBGRA(std::vector<BYTE>& pixels, int w, int h, int radius)
{
    if (radius < 1 || w < 1 || h < 1) return;
    std::vector<BYTE> temp(pixels.size());

    for (int y = 0; y < h; ++y) {
        for (int x = 0; x < w; ++x) {
            int r = 0, g = 0, b = 0, a = 0, count = 0;
            for (int dx = -radius; dx <= radius; ++dx) {
                int sx = x + dx;
                if (sx >= 0 && sx < w) {
                    const BYTE* p = &pixels[((size_t)y * w + sx) * 4];
                    b += p[0]; g += p[1]; r += p[2]; a += p[3];
                    count++;
                }
            }
            BYTE* d = &temp[((size_t)y * w + x) * 4];
            d[0] = (BYTE)(b / count);
            d[1] = (BYTE)(g / count);
            d[2] = (BYTE)(r / count);
            d[3] = (BYTE)(a / count);
        }
    }

    for (int y = 0; y < h; ++y) {
        for (int x = 0; x < w; ++x) {
            int r = 0, g = 0, b = 0, a = 0, count = 0;
            for (int dy = -radius; dy <= radius; ++dy) {
                int sy = y + dy;
                if (sy >= 0 && sy < h) {
                    const BYTE* p = &temp[((size_t)sy * w + x) * 4];
                    b += p[0]; g += p[1]; r += p[2]; a += p[3];
                    count++;
                }
            }
            BYTE* d = &pixels[((size_t)y * w + x) * 4];
            d[0] = (BYTE)(b / count);
            d[1] = (BYTE)(g / count);
            d[2] = (BYTE)(r / count);
            d[3] = (BYTE)(a / count);
        }
    }
}

static bool UpdateAlbumBlurBgCache(const std::vector<BYTE>& thumbBytes,
                                    int targetW, int targetH)
{
    if (thumbBytes.empty() || targetW <= 0 || targetH <= 0) {
        g_blurBgCache.Invalidate(); return false;
    }
    size_t artHash = 0;
    for (size_t i = 0; i < thumbBytes.size(); i += 512)
        artHash = artHash * 31 + thumbBytes[i];
    if (g_blurBgCache.artHash == artHash && g_blurBgCache.width == targetW &&
        g_blurBgCache.height == targetH && !g_blurBgCache.blurredPixels.empty())
        return true;

    std::vector<BYTE> srcPixels; int srcW = 0, srcH = 0;
    if (!DecodeImageToBGRA(thumbBytes, srcPixels, srcW, srcH)) return false;

    int blurDiv = 8;
    int smallW = srcW / blurDiv; if (smallW < 1) smallW = 1;
    int smallH = srcH / blurDiv; if (smallH < 1) smallH = 1;

    std::vector<BYTE> small;
    DownsampleBGRA(srcPixels, srcW, srcH, small, smallW, smallH);

    int blurRadius = std::clamp(g_settings.blurRadius, 1, 50);
    for (int i = 0; i < 3; ++i) {
        ApplyBoxBlurBGRA(small, smallW, smallH, blurRadius);
    }

    std::vector<BYTE> blurred;
    DownsampleBGRA(small, smallW, smallH, blurred, targetW, targetH);

    g_blurBgCache.blurredPixels = std::move(blurred);
    g_blurBgCache.width   = targetW;
    g_blurBgCache.height  = targetH;
    g_blurBgCache.artHash = artHash;
    return true;
}

static AlbumPalette ExtractAlbumPalette(const std::vector<BYTE>& thumbBytes) {
    const winrt::Windows::UI::Color fallbackPrimary{255, 18, 18, 18};
    const winrt::Windows::UI::Color fallbackSecondary{255, 45, 45, 45};

    if (thumbBytes.empty())
        return {fallbackPrimary, fallbackSecondary};

    try {
        std::vector<BYTE> pixels;
        int w = 0, h = 0;
        if (!DecodeImageToBGRA(thumbBytes, pixels, w, h) || w <= 0 || h <= 0 ||
            pixels.size() < (size_t)w * h * 4)
            return {fallbackPrimary, fallbackSecondary};

        struct Bucket { uint32_t r=0, g=0, b=0, n=0; };
        Bucket buckets[16][16][16]{};

        for (int y = 0; y < h; y += 4) {
            for (int x = 0; x < w; x += 4) {
                size_t idx = ((size_t)y * w + x) * 4;
                if (idx + 4 > pixels.size()) continue;

                BYTE pb = pixels[idx];
                BYTE pg = pixels[idx + 1];
                BYTE pr = pixels[idx + 2];

                int luma = (pr * 299 + pg * 587 + pb * 114) / 1000;
                if (luma < 24 || luma > 235) continue;

                auto& bk = buckets[pr >> 4][pg >> 4][pb >> 4];
                bk.r += pr; bk.g += pg; bk.b += pb; bk.n++;
            }
        }

        struct Cand { float w; BYTE r, g, b; };
        std::vector<Cand> cands;
        cands.reserve(64);

        for (int R = 0; R < 16; R++)
            for (int G = 0; G < 16; G++)
                for (int B = 0; B < 16; B++) {
                    auto& bk = buckets[R][G][B];
                    if (bk.n < 8) continue;
                    float fr = bk.r / (float)bk.n / 255.f;
                    float fg = bk.g / (float)bk.n / 255.f;
                    float fb = bk.b / (float)bk.n / 255.f;
                    float mx = std::max({fr, fg, fb});
                    float mn = std::min({fr, fg, fb});
                    float sat = mx > 0 ? (mx - mn) / mx : 0;
                    cands.push_back({bk.n * (0.3f + sat),
                                     (BYTE)(fr * 255), (BYTE)(fg * 255), (BYTE)(fb * 255)});
                }

        if (cands.empty())
            return {fallbackPrimary, fallbackSecondary};

        std::sort(cands.begin(), cands.end(),
                  [](const Cand& a, const Cand& b){ return a.w > b.w; });

        winrt::Windows::UI::Color primary{255, cands[0].r, cands[0].g, cands[0].b};
        winrt::Windows::UI::Color secondary = primary;

        for (auto& c : cands) {
            int dr = (int)c.r - (int)cands[0].r;
            int dg = (int)c.g - (int)cands[0].g;
            int db = (int)c.b - (int)cands[0].b;
            if (dr*dr + dg*dg + db*db > 3264) {
                secondary = winrt::Windows::UI::Color{255, c.r, c.g, c.b};
                break;
            }
        }

        return {primary, secondary};
    } catch (...) {
        return {fallbackPrimary, fallbackSecondary};
    }
}

static DWORD GetWindowsAccentColor() {
    DWORD color = 0;
    BOOL opaque = FALSE;
    if (SUCCEEDED(DwmGetColorizationColor(&color, &opaque)))
        return 0xFF000000 | (color & 0x00FFFFFF);
    return 0xFF0078D4;
}

static winrt::Windows::UI::Color ParseColorWithSpecialValues(const std::wstring& colorStr, BYTE alpha = 255) {
    int r = 255, g = 255, b = 255;
    size_t pos1 = colorStr.find(L' ');
    size_t pos2 = colorStr.find(L' ', pos1 + 1);

    if (pos1 != std::wstring::npos && pos2 != std::wstring::npos) {
        try {
            r = std::stoi(colorStr.substr(0, pos1));
            g = std::stoi(colorStr.substr(pos1 + 1, pos2 - pos1 - 1));
            b = std::stoi(colorStr.substr(pos2 + 1));

            if (r == -1 && g == -1 && b == -1) {
                DWORD accentColor = GetWindowsAccentColor();
                return winrt::Windows::UI::Color{alpha,
                    (BYTE)((accentColor >> 16) & 0xFF),
                    (BYTE)((accentColor >> 8) & 0xFF),
                    (BYTE)(accentColor & 0xFF)};
            }

            if (r == -2 && g == -2 && b == -2) {
                if (g_cachedPaletteHash == 0) {
                    return winrt::Windows::UI::Color{0, 255, 255, 255};
                }
                return winrt::Windows::UI::Color{alpha,
                    g_cachedAlbumPalette.primary.R,
                    g_cachedAlbumPalette.primary.G,
                    g_cachedAlbumPalette.primary.B};
            }

            r = std::clamp(r, 0, 255);
            g = std::clamp(g, 0, 255);
            b = std::clamp(b, 0, 255);
        } catch (...) {}
    }

    return winrt::Windows::UI::Color{alpha, (BYTE)r, (BYTE)g, (BYTE)b};
}

static winrt::Windows::UI::Color ParseColorWithThemeSupport(const std::wstring& colorStr, BYTE alpha) {
    size_t dollarPos = colorStr.find(L'$');

    if (dollarPos != std::wstring::npos) {
        std::wstring lightColorStr = colorStr.substr(0, dollarPos);
        std::wstring darkColorStr = colorStr.substr(dollarPos + 1);

        lightColorStr.erase(0, lightColorStr.find_first_not_of(L" \t"));
        lightColorStr.erase(lightColorStr.find_last_not_of(L" \t") + 1);
        darkColorStr.erase(0, darkColorStr.find_first_not_of(L" \t"));
        darkColorStr.erase(darkColorStr.find_last_not_of(L" \t") + 1);

        if (IsSystemLightTheme()) {
            return ParseColorWithSpecialValues(lightColorStr, alpha);
        } else {
            return ParseColorWithSpecialValues(darkColorStr, alpha);
        }
    } else {
        return ParseColorWithSpecialValues(colorStr, alpha);
    }
}

static winrt::Windows::UI::Color TextColor() {
    BYTE alpha = (BYTE)((g_settings.titleColorOpacity / 100.0) * 255);
    return ParseColorWithThemeSupport(g_settings.titleColor, alpha);
}

static winrt::Windows::UI::Color ArtistColor() {
    BYTE alpha = (BYTE)((g_settings.artistColorOpacity / 100.0) * 255);
    return ParseColorWithThemeSupport(g_settings.artistColor, alpha);
}

static winrt::Windows::UI::Color ButtonColor() {
    BYTE alpha = (BYTE)((g_settings.buttonColorOpacity / 100.0) * 255);
    return ParseColorWithThemeSupport(g_settings.buttonColor, alpha);
}

static winrt::Windows::UI::Color ContextMenuIconColor() {
    return ButtonColor();
}

static const std::wstring& ContextMenuIconStyle() {
    return g_settings.iconStyle;
}

static Brush MakeAlbumBlurBrush(const std::vector<BYTE>& thumbBytes,
                                  int panelW, int panelH)
{
    if (!UpdateAlbumBlurBgCache(thumbBytes, panelW, panelH) ||
        g_blurBgCache.blurredPixels.empty())
        return MakeBrush({0x00, 0x00, 0x00, 0x00});
    try {
        size_t bytesNeeded = (size_t)panelW * panelH * 4;
        WriteableBitmap wb(panelW, panelH);
        auto buf = wb.PixelBuffer();
        auto byteAccess = buf.as<Windows::Storage::Streams::IBufferByteAccess>();
        BYTE* pixels = nullptr;
        byteAccess->Buffer(&pixels);
        if (pixels && g_blurBgCache.blurredPixels.size() >= bytesNeeded)
            memcpy(pixels, g_blurBgCache.blurredPixels.data(), bytesNeeded);
        buf.Length(static_cast<uint32_t>(bytesNeeded));
        wb.Invalidate();
        ImageBrush brush;
        brush.ImageSource(wb);
        brush.Stretch(Stretch::UniformToFill);
        return brush;
    } catch (...) {}
    return MakeBrush({0x00, 0x00, 0x00, 0x00});
}
static Brush MakeBackgroundBrush() {
    auto& t = g_settings.backgroundType;

    BYTE opacity = (BYTE)((g_settings.solidOpacity / 100.0) * 255);
    auto color1 = ParseColorWithThemeSupport(g_settings.solidColor, opacity);
    auto color2 = ParseColorWithSpecialValues(g_settings.solidColor2, opacity);
    auto gradientColor2 = ParseColorWithSpecialValues(g_settings.gradientColor2, opacity);

    if (t == L"gradient") {
        try {
            winrt::Windows::UI::Xaml::Media::LinearGradientBrush brush;

            double angleRad = (g_settings.gradientAngle % 360) * 3.14159265358979323846 / 180.0;
            double startX = 0.5 - 0.5 * std::cos(angleRad);
            double startY = 0.5 - 0.5 * std::sin(angleRad);
            double endX = 0.5 + 0.5 * std::cos(angleRad);
            double endY = 0.5 + 0.5 * std::sin(angleRad);

            brush.StartPoint(winrt::Windows::Foundation::Point((float)startX, (float)startY));
            brush.EndPoint(winrt::Windows::Foundation::Point((float)endX, (float)endY));

            double balancePoint = std::clamp(g_settings.gradientBalance, 0, 100) / 100.0;

            winrt::Windows::UI::Xaml::Media::GradientStop stop1;
            stop1.Color(color2);
            stop1.Offset(0.0);

            winrt::Windows::UI::Xaml::Media::GradientStop stop2;
            stop2.Color(gradientColor2);
            stop2.Offset(balancePoint);

            winrt::Windows::UI::Xaml::Media::GradientStop stop3;
            stop3.Color(gradientColor2);
            stop3.Offset(1.0);

            brush.GradientStops().Append(stop1);
            brush.GradientStops().Append(stop2);
            brush.GradientStops().Append(stop3);

            return brush;
        } catch (...) {}
    }

    if (t == L"acrylic") {
        try {
            winrt::Windows::UI::Xaml::Media::AcrylicBrush brush;
            brush.BackgroundSource(winrt::Windows::UI::Xaml::Media::AcrylicBackgroundSource::HostBackdrop);
            auto col = winrt::Windows::UI::Color{0xFF, color1.R, color1.G, color1.B};
            brush.TintColor(col);
            brush.TintOpacity(g_settings.acrylicTintOpacity / 100.0);
            brush.FallbackColor(winrt::Windows::UI::Color{0xCC, color1.R, color1.G, color1.B});
            return brush;
        } catch (...) {}
    }

    if (t == L"mica" || t == L"mica_alt") {
        BYTE micaAlpha = (BYTE)((g_settings.micaOpacity / 100.0) * 255);
        auto col = winrt::Windows::UI::Color{micaAlpha, color1.R, color1.G, color1.B};
        return MakeBrush(col);
    }

    if (t == L"solid") {
        return MakeBrush(color1);
    }

    if (t == L"album_art_blur") {
        return MakeBrush({0x00, 0x00, 0x00, 0x00});
    }

    return MakeBrush({0x00, 0x00, 0x00, 0x00});
}

static FrameworkElement FindChildByName(FrameworkElement const& root, std::wstring_view name, int depth = 32) {
    if (!root || depth == 0) return nullptr;
    int n = VisualTreeHelper::GetChildrenCount(root);
    for (int i = 0; i < n; ++i) {
        auto child = VisualTreeHelper::GetChild(root, i).try_as<FrameworkElement>();
        if (!child) continue;
        if (child.Name() == name) return child;
        if (auto found = FindChildByName(child, name, depth - 1)) return found;
    }
    return nullptr;
}

static void DumpXamlTree(DependencyObject const& node, int depth, int maxDepth) {
    if (!node || depth > maxDepth) return;
    std::wstring indent(depth * 2, L' ');
    auto fe = node.try_as<FrameworkElement>();
    std::wstring name  = fe ? std::wstring(fe.Name()) : L"";
    winrt::hstring typeHstr = winrt::get_class_name(node);
    std::wstring type  = std::wstring(typeHstr);
    auto dot = type.rfind(L'.');
    if (dot != std::wstring::npos) type = type.substr(dot + 1);

    int col = fe ? Grid::GetColumn(fe) : -1;
    if (!name.empty()) Wh_Log(L"%ls[%ls] name='%ls' col=%d", indent.c_str(), type.c_str(), name.c_str(), col);
    else Wh_Log(L"%ls[%ls]", indent.c_str(), type.c_str());

    int n = VisualTreeHelper::GetChildrenCount(node);
    for (int i = 0; i < n; ++i) {
        auto child = VisualTreeHelper::GetChild(node, i);
        if (child) DumpXamlTree(child, depth + 1, maxDepth);
    }
}

static constexpr wchar_t kGridName[]        = L"FluentMediaBar";
static constexpr wchar_t kArtImageName[]    = L"FluentMedia_Art";
static constexpr wchar_t kAppIconImageName[]= L"FluentMedia_AppIcon";
static constexpr wchar_t kAnchorOverlayName[]= L"FluentMedia_DebugAnchorTarget";
static constexpr wchar_t kTextStackName[]   = L"FluentMedia_TextStack";
static constexpr wchar_t kTitleBlockName[]  = L"FluentMedia_Title";
static constexpr wchar_t kArtistBlockName[] = L"FluentMedia_Artist";
static constexpr wchar_t kPlayBtnName[]     = L"FluentMedia_Play";
static constexpr wchar_t kPrevBtnName[]     = L"FluentMedia_Prev";
static constexpr wchar_t kNextBtnName[]     = L"FluentMedia_Next";
static constexpr wchar_t kStopBtnName[]     = L"FluentMedia_Stop";
static constexpr wchar_t kVolumeBtnName[]   = L"FluentMedia_Volume";
static constexpr wchar_t kRewindBtnName[]   = L"FluentMedia_Rewind";
static constexpr wchar_t kForwardBtnName[]  = L"FluentMedia_Forward";
static constexpr wchar_t kShuffleBtnName[]  = L"FluentMedia_Shuffle";
static constexpr wchar_t kRepeatBtnName[]   = L"FluentMedia_Repeat";
static constexpr wchar_t kSwitchSessionsBtnName[] = L"FluentMedia_SwitchSessions";

static int  g_idleSeconds  = 0;
static int  g_idleTicks    = 0;
static bool g_hiddenByIdle = false;
static std::chrono::steady_clock::time_point g_lastMediaTime = std::chrono::steady_clock::now();

static void SwitchMediaSession();
static void ShowAppVolumeFlyout(FrameworkElement const& target);

static void SendMediaCommandAsync(int cmd) {
    std::thread([cmd]() {
        if (g_unloading) return;
        winrt::init_apartment(winrt::apartment_type::multi_threaded);
        try {
            GlobalSystemMediaTransportControlsSession session{nullptr};
            { std::lock_guard<std::mutex> lk(g_sessionMtx); session = g_currentSession; }
            if (session) {
                switch (cmd) {
                    case 1: session.TrySkipPreviousAsync().get();    break;
                    case 2: session.TryTogglePlayPauseAsync().get(); break;
                    case 3: session.TrySkipNextAsync().get();        break;
                    case 4:
                        try {
                            Wh_Log(L"SendMediaCommandAsync: Attempting to stop playback");

                            auto result = session.TryStopAsync().get();
                            Wh_Log(L"SendMediaCommandAsync: TryStopAsync returned %d", result);

                            if (!result) {
                                Wh_Log(L"SendMediaCommandAsync: Stop not supported, using pause + seek fallback");
                                session.TryPauseAsync().get();
                                session.TryChangePlaybackPositionAsync(0).get();
                            }
                        } catch (...) {
                            Wh_Log(L"SendMediaCommandAsync: Stop failed, trying pause + seek fallback");

                            try {
                                session.TryPauseAsync().get();
                                session.TryChangePlaybackPositionAsync(0).get();
                            } catch (...) {
                                Wh_Log(L"SendMediaCommandAsync: Fallback also failed");
                            }
                        }
                        break;
                    case 5:
                        try {
                            auto timeline = session.GetTimelineProperties();
                            auto currentPos = timeline.Position();
                            auto newPos = currentPos - std::chrono::seconds(5);
                            if (newPos.count() < 0) newPos = std::chrono::seconds(0);
                            session.TryChangePlaybackPositionAsync(newPos.count()).get();
                        } catch (...) {}
                        break;
                    case 6:
                        try {
                            auto timeline = session.GetTimelineProperties();
                            auto currentPos = timeline.Position();
                            auto endTime = timeline.EndTime();
                            auto newPos = currentPos + std::chrono::seconds(5);
                            if (newPos > endTime) newPos = endTime;
                            session.TryChangePlaybackPositionAsync(newPos.count()).get();
                        } catch (...) {}
                        break;
                    case 7:
                        try {
                            bool currentShuffle = g_shuffleEnabled.load();
                            if (session.TryChangeShuffleActiveAsync(!currentShuffle).get()) {
                                g_shuffleEnabled = !currentShuffle;
                                DispatchMediaUpdate();
                            }
                        } catch (...) {}
                        break;
                    case 8:
                        try {
                            RepeatMode current = g_repeatMode.load();
                            winrt::Windows::Media::MediaPlaybackAutoRepeatMode mode;
                            RepeatMode next;

                            switch (current) {
                                case RepeatMode::Off:
                                    mode = winrt::Windows::Media::MediaPlaybackAutoRepeatMode::List;
                                    next = RepeatMode::All;
                                    break;
                                case RepeatMode::All:
                                    mode = winrt::Windows::Media::MediaPlaybackAutoRepeatMode::Track;
                                    next = RepeatMode::One;
                                    break;
                                case RepeatMode::One:
                                default:
                                    mode = winrt::Windows::Media::MediaPlaybackAutoRepeatMode::None;
                                    next = RepeatMode::Off;
                                    break;
                            }

                            if (session.TryChangeAutoRepeatModeAsync(mode).get()) {
                                g_repeatMode = next;
                                DispatchMediaUpdate();
                            }
                        } catch (...) {}
                        break;
                    case 9:
                        SwitchMediaSession();
                        break;
                    case 10:
                        try {
                            if (session.TryChangeAutoRepeatModeAsync(winrt::Windows::Media::MediaPlaybackAutoRepeatMode::None).get()) {
                                g_repeatMode = RepeatMode::Off;
                                DispatchMediaUpdate();
                            }
                        } catch (...) {}
                        break;
                    case 11:
                        try {
                            if (session.TryChangeAutoRepeatModeAsync(winrt::Windows::Media::MediaPlaybackAutoRepeatMode::List).get()) {
                                g_repeatMode = RepeatMode::All;
                                DispatchMediaUpdate();
                            }
                        } catch (...) {}
                        break;
                    case 12:
                        try {
                            if (session.TryChangeAutoRepeatModeAsync(winrt::Windows::Media::MediaPlaybackAutoRepeatMode::Track).get()) {
                                g_repeatMode = RepeatMode::One;
                                DispatchMediaUpdate();
                            }
                        } catch (...) {}
                        break;
                }
            }
        } catch (...) {}
        winrt::uninit_apartment();
    }).detach();
}

struct TextScrollState {
    double offset    = 0.0;
    double textWidth = 0.0;
    double viewWidth = 0.0;
    bool   forward   = true;
    bool   active    = false;
    bool   pausing   = false;
    int    pauseTick = 0;
    int    tickMs    = 16;
};

static TextScrollState g_titleScroll;
static TextScrollState g_artistScroll;

static void ResetScrollState(TextScrollState& s);

static void FetchMediaPropertiesAsync();
static void FetchPlaybackInfoAsync();
static void OnSessionsChanged();
static void AttachToSession(GlobalSystemMediaTransportControlsSession session);
static void SwitchMediaSession();

static void SwitchMediaSession() {
    GlobalSystemMediaTransportControlsSession nextSession{nullptr};
    {
        std::lock_guard<std::mutex> lk(g_sessionMtx);
        if (!g_sessionMgr) return;
        g_userSwitchedSession = true;
        try {
            auto sessions = g_sessionMgr.GetSessions();
            int count = (int)sessions.Size();
            if (count <= 1) return;

            int currentIndex = -1;
            if (g_currentSession) {
                auto curId = g_currentSession.SourceAppUserModelId();
                for (int i = 0; i < count; ++i) {
                    if (sessions.GetAt(i).SourceAppUserModelId() == curId) {
                        currentIndex = i;
                        break;
                    }
                }
            }
            int nextIndex = (currentIndex + 1) % count;
            nextSession = sessions.GetAt(nextIndex);
        } catch (...) { return; }
    }
    if (nextSession) {
        AttachToSession(nextSession);
    }
}

static std::wstring ToLowerCopy(std::wstring value);
static std::wstring PathFileStem(std::wstring path);

static std::wstring ProcessApplicationUserModelId(HANDLE process) {
    if (!process) return L"";

    UINT32 length = 0;
    LONG result = GetApplicationUserModelId(process, &length, nullptr);
    if (result != ERROR_INSUFFICIENT_BUFFER || length == 0) return L"";

    std::vector<wchar_t> buffer(length);
    result = GetApplicationUserModelId(process, &length, buffer.data());
    if (result != ERROR_SUCCESS || buffer.empty() || !buffer[0]) return L"";
    return std::wstring(buffer.data());
}

static bool SamePackagedAppIdentity(const std::wstring& first,
                                    const std::wstring& second) {
    if (first.empty() || second.empty()) return false;

    std::wstring a = ToLowerCopy(first);
    std::wstring b = ToLowerCopy(second);
    if (a == b) return true;

    auto packagePart = [](const std::wstring& value) {
        size_t separator = value.find(L'!');
        return value.substr(0, separator);
    };
    std::wstring packageA = packagePart(a);
    std::wstring packageB = packagePart(b);
    return !packageA.empty() && packageA == packageB;
}

static bool KnownMediaPlayerProcessAlias(const std::wstring& appLower,
                                         const std::wstring& processStemLower) {
    // The current Microsoft Media Player publishes the historic ZuneMusic
    // package identity while its executable is Microsoft.Media.Player.exe.
    if ((appLower.find(L"microsoft.zunemusic") != std::wstring::npos ||
         appLower.find(L"windowsmediaplayer") != std::wstring::npos) &&
        (processStemLower == L"microsoft.media.player" ||
         processStemLower == L"music.ui" ||
         processStemLower == L"wmplayer")) {
        return true;
    }

    return false;
}

static bool AudioSessionMatchesApp(IAudioSessionControl2* sessionControl2,
                                   const std::wstring& appUserModelId) {
    if (!sessionControl2 || appUserModelId.empty()) return false;

    std::wstring appLower = ToLowerCopy(appUserModelId);
    std::wstring appStem = ToLowerCopy(PathFileStem(appUserModelId));
    if (appStem == L"applicationframehost" || appStem == L"explorer") {
        appStem.clear();
    }

    LPWSTR rawSessionId = nullptr;
    if (SUCCEEDED(sessionControl2->GetSessionIdentifier(&rawSessionId)) && rawSessionId) {
        std::wstring sessionIdLower = ToLowerCopy(rawSessionId);
        CoTaskMemFree(rawSessionId);
        if (sessionIdLower.find(appLower) != std::wstring::npos ||
            (!appStem.empty() && sessionIdLower.find(appStem) != std::wstring::npos)) {
            return true;
        }
    }

    DWORD processId = 0;
    if (FAILED(sessionControl2->GetProcessId(&processId)) || !processId) return false;

    HANDLE process = OpenProcess(PROCESS_QUERY_LIMITED_INFORMATION, FALSE, processId);
    if (!process) return false;

    wchar_t imagePath[32768]{};
    DWORD imagePathLength = ARRAYSIZE(imagePath);
    bool matches = false;
    std::wstring processAumid = ProcessApplicationUserModelId(process);
    if (SamePackagedAppIdentity(appUserModelId, processAumid)) {
        matches = true;
    }
    if (QueryFullProcessImageNameW(process, 0, imagePath, &imagePathLength)) {
        std::wstring processPath(imagePath, imagePathLength);
        std::wstring processLower = ToLowerCopy(processPath);
        std::wstring processStem = ToLowerCopy(PathFileStem(processPath));
        matches = matches || processLower == appLower ||
                  (!appStem.empty() && processStem == appStem) ||
                  (!processStem.empty() && appLower.find(processStem) != std::wstring::npos) ||
                  KnownMediaPlayerProcessAlias(appLower, processStem);
    }
    CloseHandle(process);
    return matches;
}

static bool ForEachMatchingAudioSession(
    const std::wstring& appUserModelId,
    IMMDeviceEnumerator* deviceEnumerator,
    const std::function<void(IAudioSessionControl*, IAudioSessionControl2*)>& visitor) {
    if (appUserModelId.empty()) return false;
    winrt::com_ptr<IMMDeviceEnumerator> localDeviceEnumerator;
    if (!deviceEnumerator) {
        if (FAILED(CoCreateInstance(XIID_MMDeviceEnumerator, nullptr, CLSCTX_INPROC_SERVER,
                                    XIID_IMMDeviceEnumerator,
                                    localDeviceEnumerator.put_void()))) {
            return false;
        }
        deviceEnumerator = localDeviceEnumerator.get();
    }
    if (!deviceEnumerator) return false;

    bool found = false;
    winrt::com_ptr<IMMDeviceCollection> devices;
    HRESULT hr = deviceEnumerator->EnumAudioEndpoints(
        eRender, DEVICE_STATE_ACTIVE, devices.put());
    if (FAILED(hr) || !devices) return false;

    UINT deviceCount = 0;
    if (FAILED(devices->GetCount(&deviceCount))) return false;

    for (UINT deviceIndex = 0; deviceIndex < deviceCount; ++deviceIndex) {
        winrt::com_ptr<IMMDevice> device;
        if (FAILED(devices->Item(deviceIndex, device.put())) || !device) continue;

        winrt::com_ptr<IAudioSessionManager2> sessionManager;
        if (FAILED(device->Activate(XIID_IAudioSessionManager2, CLSCTX_ALL,
                                    nullptr, sessionManager.put_void())) ||
            !sessionManager) {
            continue;
        }

        winrt::com_ptr<IAudioSessionEnumerator> sessionEnumerator;
        if (FAILED(sessionManager->GetSessionEnumerator(sessionEnumerator.put())) ||
            !sessionEnumerator) {
            continue;
        }

        int sessionCount = 0;
        if (FAILED(sessionEnumerator->GetCount(&sessionCount))) continue;

        for (int sessionIndex = 0; sessionIndex < sessionCount; ++sessionIndex) {
            winrt::com_ptr<IAudioSessionControl> sessionControl;
            if (FAILED(sessionEnumerator->GetSession(sessionIndex,
                                                     sessionControl.put())) ||
                !sessionControl) {
                continue;
            }

            winrt::com_ptr<IAudioSessionControl2> sessionControl2;
            if (FAILED(sessionControl->QueryInterface(
                    __uuidof(IAudioSessionControl2), sessionControl2.put_void())) ||
                !sessionControl2) {
                continue;
            }

            if (AudioSessionMatchesApp(sessionControl2.get(), appUserModelId)) {
                found = true;
                visitor(sessionControl.get(), sessionControl2.get());
            }
        }
    }

    return found;
}

static bool GetAppVolumeByAUMID(const std::wstring& appUserModelId, float& volume) {
    bool volumeRead = false;
    ForEachMatchingAudioSession(appUserModelId, nullptr,
        [&](IAudioSessionControl* sessionControl, IAudioSessionControl2*) {
            if (volumeRead) return;
            winrt::com_ptr<ISimpleAudioVolume> appVolume;
            if (SUCCEEDED(sessionControl->QueryInterface(__uuidof(ISimpleAudioVolume),
                                                         appVolume.put_void())) &&
                SUCCEEDED(appVolume->GetMasterVolume(&volume))) {
                volumeRead = true;
            }
        });
    return volumeRead;
}

static bool SetAppVolumeByAUMID(const std::wstring& appUserModelId, float volume) {
    bool changed = false;
    volume = std::clamp(volume, 0.0f, 1.0f);
    ForEachMatchingAudioSession(appUserModelId, nullptr,
        [&](IAudioSessionControl* sessionControl, IAudioSessionControl2*) {
            winrt::com_ptr<ISimpleAudioVolume> appVolume;
            if (SUCCEEDED(sessionControl->QueryInterface(__uuidof(ISimpleAudioVolume),
                                                         appVolume.put_void())) &&
                SUCCEEDED(appVolume->SetMasterVolume(volume, nullptr))) {
                changed = true;
            }
        });
    return changed;
}

static bool GetAppMuteByAUMID(const std::wstring& appUserModelId, bool& muted) {
    bool stateRead = false;
    ForEachMatchingAudioSession(appUserModelId, nullptr,
        [&](IAudioSessionControl* sessionControl, IAudioSessionControl2*) {
            if (stateRead) return;
            winrt::com_ptr<ISimpleAudioVolume> appVolume;
            BOOL isMuted = FALSE;
            if (SUCCEEDED(sessionControl->QueryInterface(__uuidof(ISimpleAudioVolume),
                                                         appVolume.put_void())) &&
                SUCCEEDED(appVolume->GetMute(&isMuted))) {
                muted = isMuted != FALSE;
                stateRead = true;
            }
        });
    return stateRead;
}

static bool SetAppMuteByAUMID(const std::wstring& appUserModelId, bool muted) {
    bool changed = false;
    ForEachMatchingAudioSession(appUserModelId, nullptr,
        [&](IAudioSessionControl* sessionControl, IAudioSessionControl2*) {
            winrt::com_ptr<ISimpleAudioVolume> appVolume;
            if (SUCCEEDED(sessionControl->QueryInterface(__uuidof(ISimpleAudioVolume),
                                                         appVolume.put_void())) &&
                SUCCEEDED(appVolume->SetMute(muted ? TRUE : FALSE, nullptr))) {
                changed = true;
            }
        });
    return changed;
}

static bool AdjustAppVolumeByAUMID(const std::wstring& appUserModelId, float volumeDelta) {
    bool changed = false;
    ForEachMatchingAudioSession(appUserModelId, nullptr,
        [&](IAudioSessionControl* sessionControl, IAudioSessionControl2*) {
            winrt::com_ptr<ISimpleAudioVolume> appVolume;
            float currentVolume = 0.0f;
            if (SUCCEEDED(sessionControl->QueryInterface(__uuidof(ISimpleAudioVolume),
                                                         appVolume.put_void())) &&
                SUCCEEDED(appVolume->GetMasterVolume(&currentVolume)) &&
                SUCCEEDED(appVolume->SetMasterVolume(
                    std::clamp(currentVolume + volumeDelta, 0.0f, 1.0f), nullptr))) {
                changed = true;
            }
        });
    return changed;
}

static std::wstring GetWindowAppUserModelId(HWND hWnd);
static void ShowMediaContextMenu(FrameworkElement const& target);

[[maybe_unused]]
static void ExecuteMediaAction(const std::wstring& action, FrameworkElement const& sourceElement = nullptr) {
    if (action == L"none") {
        return;
    } else if (action == L"open_context_menu") {
        if (sourceElement) {
            ShowMediaContextMenu(sourceElement);
        }
        return;
    } else if (action == L"switch_session") {
        SwitchMediaSession();
    } else if (action == L"play_pause") {
        SendMediaCommandAsync(2);
        DispatchMediaUpdate();
    } else if (action == L"next_track") {
        SendMediaCommandAsync(3);
        DispatchMediaUpdate();
    } else if (action == L"prev_track") {
        SendMediaCommandAsync(1);
        DispatchMediaUpdate();
    } else if (action == L"stop") {
        g_forceSessionRefresh = true;
        SendMediaCommandAsync(4);
        DispatchMediaUpdate();
        std::thread([]() {
            for (DWORD delay : {300, 1200, 2500}) {
                Sleep(delay);
                if (g_unloading) return;
                g_forceSessionRefresh = true;
                OnSessionsChanged();
                FetchPlaybackInfoAsync();
                FetchMediaPropertiesAsync();
            }
        }).detach();
    } else if (action == L"rewind_5s") {
        SendMediaCommandAsync(5);
        DispatchMediaUpdate();
    } else if (action == L"forward_5s") {
        SendMediaCommandAsync(6);
        DispatchMediaUpdate();
    } else if (action == L"toggle_shuffle") {
        SendMediaCommandAsync(7);
        DispatchMediaUpdate();
    } else if (action == L"toggle_repeat") {
        SendMediaCommandAsync(8);
        DispatchMediaUpdate();
} else if (action == L"open_app") {
        std::thread([]() {
            std::wstring title, appAumid;
            {
                std::lock_guard<std::mutex> lk(g_mediaMtx);
                title = g_media.title;
            }
            {
                std::lock_guard<std::mutex> lk(g_sessionMtx);
                if (g_currentSession) {
                    try {
                        appAumid = std::wstring(g_currentSession.SourceAppUserModelId());
                    } catch (...) {}
                }
            }

            struct WindowSearch {
                std::wstring targetTitle;
                std::wstring targetAumid;
                HWND aumidHwnd = nullptr;
                HWND processHwnd = nullptr;
                HWND titleHwnd = nullptr;
            };
            WindowSearch search;

            search.targetTitle = title;
            std::transform(search.targetTitle.begin(), search.targetTitle.end(), search.targetTitle.begin(), ::towlower);

            search.targetAumid = appAumid;
            std::transform(search.targetAumid.begin(), search.targetAumid.end(), search.targetAumid.begin(), ::towlower);

            EnumWindows([](HWND hwnd, LPARAM lParam) CALLBACK -> BOOL {
                if (!IsWindowVisible(hwnd)) return TRUE;
                WINDOWINFO wi{};
                wi.cbSize = sizeof(wi);
                GetWindowInfo(hwnd, &wi);
                if ((wi.dwStyle & WS_CHILD) != 0) return TRUE;

                auto* s = reinterpret_cast<WindowSearch*>(lParam);

                if (!s->aumidHwnd && !s->targetAumid.empty()) {
                    IPropertyStore* pps = nullptr;
                    if (SUCCEEDED(SHGetPropertyStoreForWindow(hwnd, IID_PPV_ARGS(&pps)))) {
                        PROPVARIANT var;
                        PropVariantInit(&var);
                        if (SUCCEEDED(pps->GetValue(PKEY_AppUserModel_ID, &var)) && var.vt == VT_LPWSTR) {
                            std::wstring winAumid(var.pwszVal);
                            std::transform(winAumid.begin(), winAumid.end(), winAumid.begin(), ::towlower);
                            if (winAumid == s->targetAumid ||
                                winAumid.find(s->targetAumid) != std::wstring::npos ||
                                s->targetAumid.find(winAumid) != std::wstring::npos) {
                                s->aumidHwnd = hwnd;
                            }
                        }
                        PropVariantClear(&var);
                        pps->Release();
                    }
                }

                if (!s->processHwnd && !s->targetAumid.empty()) {
                    DWORD pid = 0;
                    GetWindowThreadProcessId(hwnd, &pid);
                    if (pid) {
                        wchar_t procPath[MAX_PATH]{};
                        HANDLE hProc = OpenProcess(PROCESS_QUERY_LIMITED_INFORMATION, FALSE, pid);
                        if (hProc) {
                            DWORD sz = MAX_PATH;
                            QueryFullProcessImageNameW(hProc, 0, procPath, &sz);
                            CloseHandle(hProc);
                        }
                        if (procPath[0]) {
                            std::wstring stem = procPath;
                            auto slash = stem.find_last_of(L"\\/");
                            if (slash != std::wstring::npos) stem = stem.substr(slash + 1);
                            auto dot = stem.rfind(L'.');
                            if (dot != std::wstring::npos) stem = stem.substr(0, dot);
                            std::transform(stem.begin(), stem.end(), stem.begin(), ::towlower);

                            if (!stem.empty() &&
                                (s->targetAumid.find(stem) != std::wstring::npos ||
                                 stem.find(s->targetAumid) != std::wstring::npos)) {
                                s->processHwnd = hwnd;
                            }
                        }
                    }
                }

                if (!s->titleHwnd && !s->targetTitle.empty()) {
                    wchar_t windowTitle[512];
                    if (GetWindowTextW(hwnd, windowTitle, 512) > 0) {
                        std::wstring wTitle(windowTitle);
                        std::transform(wTitle.begin(), wTitle.end(), wTitle.begin(), ::towlower);
                        if (wTitle.find(s->targetTitle) != std::wstring::npos) {
                            s->titleHwnd = hwnd;
                        }
                    }
                }

                return TRUE;
            }, reinterpret_cast<LPARAM>(&search));

            HWND targetWindow = search.aumidHwnd
                ? search.aumidHwnd
                : (search.processHwnd ? search.processHwnd : search.titleHwnd);

            if (targetWindow) {
                if (IsIconic(targetWindow)) {
                    ShowWindow(targetWindow, SW_RESTORE);
                }
                
                HWND hCurWnd = GetForegroundWindow();
                if (hCurWnd && hCurWnd != targetWindow) {
                    DWORD dwMyID = GetCurrentThreadId();
                    DWORD dwCurID = GetWindowThreadProcessId(hCurWnd, NULL);
                    AttachThreadInput(dwCurID, dwMyID, TRUE);
                    SetForegroundWindow(targetWindow);
                    BringWindowToTop(targetWindow);
                    AttachThreadInput(dwCurID, dwMyID, FALSE);
                } else {
                    SetForegroundWindow(targetWindow);
                    BringWindowToTop(targetWindow);
                }
                return;
            }

            if (!appAumid.empty()) {
                std::wstring shellPath = L"shell:AppsFolder\\" + appAumid;
                ShellExecuteW(nullptr, L"open", shellPath.c_str(), nullptr, nullptr, SW_SHOWNORMAL);
            }

        }).detach();
    }
}

static std::wstring ToLowerCopy(std::wstring value) {
    for (auto& c : value) c = towlower(c);
    return value;
}

static std::wstring PathFileStem(std::wstring path) {
    auto slash = path.find_last_of(L"\\/");
    if (slash != std::wstring::npos) path = path.substr(slash + 1);
    auto dot = path.rfind(L'.');
    if (dot != std::wstring::npos) path = path.substr(0, dot);
    return path;
}

static HWND g_volumePopupWindow = nullptr;
static HWND g_volumePopupPercent = nullptr;
static std::wstring g_volumePopupAppUserModelId;
static HBRUSH g_volumePopupBrush = nullptr;
static constexpr UINT kVolumeStateChangedMessage = WM_APP + 0x431;
static constexpr int kVolumeTrackCenterX = 42;
static constexpr int kVolumeTrackTop = 34;
static constexpr int kVolumeTrackBottom = 146;
static int g_volumePopupValue = 0;
static bool g_volumePopupDragging = false;
static bool g_volumePopupEnabled = false;
static std::atomic<int> g_currentVolumePercent{-1};
static std::atomic<bool> g_currentVolumeMuted{false};
static std::atomic<bool> g_musicBeeVolumeBridgeAvailable{false};

static std::wstring CurrentMediaAppUserModelId() {
    std::wstring appUserModelId;
    {
        std::lock_guard<std::mutex> lk(g_mediaMtx);
        appUserModelId = g_media.appUserModelId;
    }
    if (appUserModelId.empty()) {
        std::lock_guard<std::mutex> lk(g_sessionMtx);
        if (g_currentSession) {
            try {
                appUserModelId = std::wstring(g_currentSession.SourceAppUserModelId());
            } catch (...) {}
        }
    }
    return appUserModelId;
}

static std::wstring FriendlyMediaAppName(const std::wstring& appUserModelId) {
    if (appUserModelId.empty()) return L"Media app";

    if (ToLowerCopy(appUserModelId).find(L"musicbee") != std::wstring::npos) {
        return L"MusicBee";
    }

    size_t separator = appUserModelId.rfind(L'!');
    if (separator != std::wstring::npos && separator + 1 < appUserModelId.size()) {
        std::wstring suffix = appUserModelId.substr(separator + 1);
        if (_wcsicmp(suffix.c_str(), L"app") != 0) return suffix;
    }

    std::wstring package = separator == std::wstring::npos
        ? appUserModelId
        : appUserModelId.substr(0, separator);
    size_t dot = package.rfind(L'.');
    if (dot != std::wstring::npos && dot + 1 < package.size()) {
        std::wstring name = package.substr(dot + 1);
        size_t underscore = name.find(L'_');
        if (underscore != std::wstring::npos) name.resize(underscore);
        if (!name.empty()) return name;
    }

    std::wstring stem = PathFileStem(appUserModelId);
    return stem.empty() ? L"Media app" : stem;
}

static bool IsMusicBeeAppId(const std::wstring& appUserModelId) {
    return ToLowerCopy(appUserModelId).find(L"musicbee") != std::wstring::npos;
}

static const wchar_t* VolumeGlyphForState(int percent, bool muted) {
    if (muted || percent <= 0) return L"\uE74F"; // muted
    if (percent <= 45) return L"\uE993";         // one wave
    return L"\uE995";                            // full waves
}

static void PublishVolumeState(int percent, bool muted) {
    percent = std::clamp(percent, 0, 100);
    int oldPercent = g_currentVolumePercent.exchange(percent);
    bool oldMuted = g_currentVolumeMuted.exchange(muted);
    if (oldPercent != percent || oldMuted != muted) {
        g_needsUiUpdate = true;
        if (g_volumePopupWindow && IsWindow(g_volumePopupWindow)) {
            PostMessageW(g_volumePopupWindow, kVolumeStateChangedMessage,
                         static_cast<WPARAM>(percent), muted ? 1 : 0);
        }
    }
}

static bool ExchangeMusicBeeVolumeBridge(const char* request,
                                          int& percent, bool& muted) {
    static constexpr wchar_t kPipeName[] =
        L"\\\\.\\pipe\\TaskbarMediaPresence.MusicBeeVolume.v1";

    HANDLE pipe = CreateFileW(kPipeName, GENERIC_READ | GENERIC_WRITE,
                              0, nullptr, OPEN_EXISTING, 0, nullptr);
    if (pipe == INVALID_HANDLE_VALUE && GetLastError() == ERROR_PIPE_BUSY &&
        WaitNamedPipeW(kPipeName, 40)) {
        pipe = CreateFileW(kPipeName, GENERIC_READ | GENERIC_WRITE,
                           0, nullptr, OPEN_EXISTING, 0, nullptr);
    }
    if (pipe == INVALID_HANDLE_VALUE) {
        g_musicBeeVolumeBridgeAvailable = false;
        return false;
    }

    DWORD written = 0;
    DWORD requestLength = static_cast<DWORD>(strlen(request));
    bool success = WriteFile(pipe, request, requestLength, &written, nullptr) &&
                   written == requestLength;
    char response[96]{};
    DWORD read = 0;
    if (success) {
        success = ReadFile(pipe, response, sizeof(response) - 1, &read, nullptr) != FALSE;
    }
    CloseHandle(pipe);
    if (!success) {
        g_musicBeeVolumeBridgeAvailable = false;
        return false;
    }

    response[std::min<DWORD>(read, sizeof(response) - 1)] = '\0';
    int muteValue = 0;
    if (std::sscanf(response, "OK %d %d", &percent, &muteValue) != 2) {
        return false;
    }
    percent = std::clamp(percent, 0, 100);
    muted = muteValue != 0;
    g_musicBeeVolumeBridgeAvailable = true;
    PublishVolumeState(percent, muted);
    return true;
}

static bool GetCurrentControllableVolume(int& percent, bool& muted) {
    std::wstring appUserModelId = CurrentMediaAppUserModelId();
    if (appUserModelId.empty()) return false;

    if (IsMusicBeeAppId(appUserModelId)) {
        return ExchangeMusicBeeVolumeBridge("GET\n", percent, muted);
    }

    float volume = 0.0f;
    if (!GetAppVolumeByAUMID(appUserModelId, volume)) return false;
    bool appMuted = false;
    GetAppMuteByAUMID(appUserModelId, appMuted);
    percent = std::clamp((int)std::lround(volume * 100.0f), 0, 100);
    muted = appMuted;
    PublishVolumeState(percent, muted);
    return true;
}

static bool SetCurrentControllableVolume(int requestedPercent) {
    requestedPercent = std::clamp(requestedPercent, 0, 100);
    std::wstring appUserModelId = CurrentMediaAppUserModelId();
    if (appUserModelId.empty()) return false;

    if (IsMusicBeeAppId(appUserModelId)) {
        char request[32]{};
        std::snprintf(request, sizeof(request), "SET %d\n", requestedPercent);
        int actualPercent = requestedPercent;
        bool muted = false;
        return ExchangeMusicBeeVolumeBridge(request, actualPercent, muted);
    }

    bool changed = SetAppVolumeByAUMID(
        appUserModelId, requestedPercent / 100.0f);
    if (changed && requestedPercent > 0) {
        SetAppMuteByAUMID(appUserModelId, false);
    }
    if (changed) PublishVolumeState(requestedPercent, false);
    return changed;
}

static std::wstring FindMatchingAudioProcessPath(
    const std::wstring& appUserModelId) {
    std::wstring processPath;
    ForEachMatchingAudioSession(appUserModelId, nullptr,
        [&](IAudioSessionControl*, IAudioSessionControl2* sessionControl2) {
            if (!processPath.empty()) return;
            DWORD processId = 0;
            if (FAILED(sessionControl2->GetProcessId(&processId)) || !processId) return;
            HANDLE process = OpenProcess(PROCESS_QUERY_LIMITED_INFORMATION,
                                         FALSE, processId);
            if (!process) return;
            wchar_t path[MAX_PATH]{};
            DWORD pathLength = ARRAYSIZE(path);
            if (QueryFullProcessImageNameW(process, 0, path, &pathLength)) {
                processPath.assign(path, pathLength);
            }
            CloseHandle(process);
        });
    return processPath;
}

static bool SendMusicBeeVolumeStep(const std::wstring& appUserModelId,
                                    bool increase) {
    std::wstring executable = FindMatchingAudioProcessPath(appUserModelId);
    if (executable.empty()) return false;
    std::wstring commandLine = L"\"" + executable + L"\" " +
        (increase ? L"/VolumeUp" : L"/VolumeDown");
    std::vector<wchar_t> mutableCommand(commandLine.begin(), commandLine.end());
    mutableCommand.push_back(L'\0');
    STARTUPINFOW startup{sizeof(startup)};
    PROCESS_INFORMATION processInfo{};
    bool started = CreateProcessW(executable.c_str(), mutableCommand.data(),
                                  nullptr, nullptr, FALSE, CREATE_NO_WINDOW,
                                  nullptr, nullptr, &startup, &processInfo) != FALSE;
    if (started) {
        CloseHandle(processInfo.hThread);
        CloseHandle(processInfo.hProcess);
    }
    return started;
}

static void AdjustCurrentMediaAppVolumeAsync(int wheelDelta) {
    std::wstring appUserModelId = CurrentMediaAppUserModelId();
    if (appUserModelId.empty() || wheelDelta == 0) return;
    bool increase = wheelDelta > 0;
    std::thread([appUserModelId, increase]() {
        HRESULT apartmentResult = CoInitializeEx(nullptr, COINIT_MULTITHREADED);
        bool changed = false;
        if (IsMusicBeeAppId(appUserModelId)) {
            int percent = 0;
            bool muted = false;
            if (ExchangeMusicBeeVolumeBridge("GET\n", percent, muted)) {
                int next = std::clamp(percent + (increase ? 2 : -2), 0, 100);
                changed = SetCurrentControllableVolume(next);
            } else {
                // The official command-line fallback still changes MusicBee's
                // internal player volume, but only in MusicBee's 10% steps.
                changed = SendMusicBeeVolumeStep(appUserModelId, increase);
            }
        } else {
            changed = AdjustAppVolumeByAUMID(
                appUserModelId, increase ? 0.02f : -0.02f);
            if (changed) {
                int percent = 0;
                bool muted = false;
                GetCurrentControllableVolume(percent, muted);
            }
        }
        if (!changed) {
            Wh_Log(L"Volume control: no supported volume endpoint for %ls",
                   appUserModelId.c_str());
        }
        if (SUCCEEDED(apartmentResult)) CoUninitialize();
    }).detach();
}

static void UpdateVolumePopupPercent(int volumePercent) {
    volumePercent = std::clamp(volumePercent, 0, 100);
    g_volumePopupValue = volumePercent;
    if (g_volumePopupPercent) {
        std::wstring text = std::to_wstring(volumePercent) + L"%";
        SetWindowTextW(g_volumePopupPercent, text.c_str());
    }
    if (g_volumePopupWindow) {
        InvalidateRect(g_volumePopupWindow, nullptr, FALSE);
    }
}

static int VolumePercentFromPopupY(int y) {
    y = std::clamp(y, kVolumeTrackTop, kVolumeTrackBottom);
    double ratio = static_cast<double>(kVolumeTrackBottom - y) /
                   static_cast<double>(kVolumeTrackBottom - kVolumeTrackTop);
    return std::clamp(static_cast<int>(std::lround(ratio * 100.0)), 0, 100);
}

static int PopupYFromVolumePercent(int percent) {
    percent = std::clamp(percent, 0, 100);
    double ratio = percent / 100.0;
    return static_cast<int>(std::lround(
        kVolumeTrackBottom - ratio *
        (kVolumeTrackBottom - kVolumeTrackTop)));
}

static bool IsPointInVolumeTrack(int x, int y) {
    return x >= 20 && x <= 64 &&
           y >= kVolumeTrackTop - 10 && y <= kVolumeTrackBottom + 10;
}

static void SetPopupVolumeFromY(HWND window, int y) {
    if (!g_volumePopupEnabled) return;
    int requested = VolumePercentFromPopupY(y);
    if (requested == g_volumePopupValue) return;

    int previous = g_volumePopupValue;
    UpdateVolumePopupPercent(requested);
    if (!SetCurrentControllableVolume(requested)) {
        UpdateVolumePopupPercent(previous);
    }
    InvalidateRect(window, nullptr, FALSE);
}

static LRESULT CALLBACK VolumePopupWindowProc(HWND window, UINT message,
                                               WPARAM wParam, LPARAM lParam) {
    switch (message) {
        case WM_CREATE: {
            HFONT font = (HFONT)GetStockObject(DEFAULT_GUI_FONT);
            std::wstring title = FriendlyMediaAppName(g_volumePopupAppUserModelId);

            HWND titleLabel = CreateWindowExW(
                0, L"STATIC", title.c_str(), WS_CHILD | WS_VISIBLE | SS_CENTER | SS_ENDELLIPSIS,
                6, 8, 72, 20, window, nullptr, GetModuleHandleW(nullptr), nullptr);
            SendMessageW(titleLabel, WM_SETFONT, (WPARAM)font, TRUE);

            g_volumePopupPercent = CreateWindowExW(
                0, L"STATIC", L"0%", WS_CHILD | WS_VISIBLE | SS_CENTER,
                10, 154, 64, 22, window, nullptr, GetModuleHandleW(nullptr), nullptr);
            SendMessageW(g_volumePopupPercent, WM_SETFONT, (WPARAM)font, TRUE);

            int volumePercent = std::max(g_currentVolumePercent.load(), 0);
            bool muted = g_currentVolumeMuted.load();
            bool hasVolumeControl = GetCurrentControllableVolume(
                volumePercent, muted);
            g_volumePopupEnabled = hasVolumeControl;
            UpdateVolumePopupPercent(volumePercent);
            if (!hasVolumeControl && IsMusicBeeAppId(g_volumePopupAppUserModelId)) {
                SetWindowTextW(titleLabel, L"Install bridge");
            }
            SetTimer(window, 2001, 120, nullptr);
            return 0;
        }
        case WM_LBUTTONDOWN: {
            int x = static_cast<short>(LOWORD(lParam));
            int y = static_cast<short>(HIWORD(lParam));
            if (g_volumePopupEnabled && IsPointInVolumeTrack(x, y)) {
                g_volumePopupDragging = true;
                SetCapture(window);
                SetPopupVolumeFromY(window, y);
            }
            return 0;
        }
        case WM_MOUSEMOVE:
            if (g_volumePopupDragging && GetCapture() == window) {
                SetPopupVolumeFromY(
                    window, static_cast<short>(HIWORD(lParam)));
            }
            return 0;
        case WM_LBUTTONUP:
            if (g_volumePopupDragging) {
                SetPopupVolumeFromY(
                    window, static_cast<short>(HIWORD(lParam)));
                g_volumePopupDragging = false;
                if (GetCapture() == window) ReleaseCapture();
            }
            return 0;
        case WM_CAPTURECHANGED:
            g_volumePopupDragging = false;
            return 0;
        case WM_MOUSEWHEEL:
            if (g_volumePopupEnabled) {
                int next = std::clamp(
                    g_volumePopupValue +
                    (GET_WHEEL_DELTA_WPARAM(wParam) > 0 ? 2 : -2),
                    0, 100);
                if (SetCurrentControllableVolume(next)) {
                    UpdateVolumePopupPercent(g_currentVolumePercent.load());
                }
            }
            return 0;
        case kVolumeStateChangedMessage:
            UpdateVolumePopupPercent(
                std::clamp(static_cast<int>(wParam), 0, 100));
            return 0;
        case WM_MOUSEACTIVATE:
            return MA_NOACTIVATE;
        case WM_TIMER:
            if (wParam == 2001 && !g_volumePopupDragging &&
                ((GetAsyncKeyState(VK_LBUTTON) & 0x8000) ||
                 (GetAsyncKeyState(VK_RBUTTON) & 0x8000) ||
                 (GetAsyncKeyState(VK_MBUTTON) & 0x8000))) {
                POINT cursor{};
                RECT popupRect{};
                GetCursorPos(&cursor);
                GetWindowRect(window, &popupRect);
                if (!PtInRect(&popupRect, cursor)) {
                    DestroyWindow(window);
                }
            }
            return 0;
        case WM_CTLCOLORSTATIC: {
            HDC dc = (HDC)wParam;
            SetTextColor(dc, RGB(245, 245, 245));
            SetBkMode(dc, TRANSPARENT);
            return (LRESULT)g_volumePopupBrush;
        }
        case WM_CTLCOLORBTN: {
            HDC dc = (HDC)wParam;
            SetTextColor(dc, RGB(245, 245, 245));
            SetBkMode(dc, TRANSPARENT);
            return (LRESULT)g_volumePopupBrush;
        }
        case WM_PAINT: {
            PAINTSTRUCT paint{};
            HDC dc = BeginPaint(window, &paint);
            RECT client{};
            GetClientRect(window, &client);
            FillRect(dc, &client, g_volumePopupBrush);

            HPEN oldPen = static_cast<HPEN>(
                SelectObject(dc, GetStockObject(NULL_PEN)));
            HBRUSH trackBrush = CreateSolidBrush(RGB(96, 96, 102));
            HBRUSH fillBrush = CreateSolidBrush(
                g_volumePopupEnabled ? RGB(0, 120, 215) : RGB(100, 100, 104));

            HBRUSH oldBrush = static_cast<HBRUSH>(SelectObject(dc, trackBrush));
            RoundRect(dc, kVolumeTrackCenterX - 2, kVolumeTrackTop,
                      kVolumeTrackCenterX + 2, kVolumeTrackBottom, 4, 4);

            int thumbY = PopupYFromVolumePercent(g_volumePopupValue);
            if (thumbY < kVolumeTrackBottom) {
                SelectObject(dc, fillBrush);
                RoundRect(dc, kVolumeTrackCenterX - 2, thumbY,
                          kVolumeTrackCenterX + 2, kVolumeTrackBottom, 4, 4);
            }
            SelectObject(dc, fillBrush);
            Ellipse(dc, kVolumeTrackCenterX - 7, thumbY - 7,
                    kVolumeTrackCenterX + 7, thumbY + 7);

            SelectObject(dc, oldBrush);
            SelectObject(dc, oldPen);
            DeleteObject(trackBrush);
            DeleteObject(fillBrush);
            EndPaint(window, &paint);
            return 0;
        }
        case WM_ERASEBKGND: {
            RECT rect{};
            GetClientRect(window, &rect);
            FillRect((HDC)wParam, &rect, g_volumePopupBrush);
            return 1;
        }
        case WM_NCDESTROY:
            KillTimer(window, 2001);
            if (GetCapture() == window) ReleaseCapture();
            g_volumePopupWindow = nullptr;
            g_volumePopupPercent = nullptr;
            g_volumePopupDragging = false;
            g_volumePopupEnabled = false;
            return 0;
    }
    return DefWindowProcW(window, message, wParam, lParam);
}

static void DestroyVolumePopup() {
    if (g_volumePopupWindow && IsWindow(g_volumePopupWindow)) {
        DWORD windowThread = GetWindowThreadProcessId(g_volumePopupWindow, nullptr);
        if (windowThread == GetCurrentThreadId()) {
            DestroyWindow(g_volumePopupWindow);
        } else {
            PostMessageW(g_volumePopupWindow, WM_CLOSE, 0, 0);
        }
    }
}

static void ShowAppVolumeFlyout(FrameworkElement const& target) {
    if (!target || g_unloading) return;
    g_volumePopupAppUserModelId = CurrentMediaAppUserModelId();
    if (g_volumePopupAppUserModelId.empty()) return;

    DestroyVolumePopup();
    static constexpr wchar_t kVolumePopupClass[] =
        L"TaskbarMediaPresenceVolumePopup_v070";
    WNDCLASSEXW windowClass{sizeof(windowClass)};
    windowClass.lpfnWndProc = VolumePopupWindowProc;
    windowClass.hInstance = GetModuleHandleW(nullptr);
    windowClass.hCursor = LoadCursorW(nullptr, IDC_ARROW);
    windowClass.lpszClassName = kVolumePopupClass;
    RegisterClassExW(&windowClass);

    if (!g_volumePopupBrush) {
        g_volumePopupBrush = CreateSolidBrush(RGB(36, 36, 40));
    }

    constexpr int popupWidth = 84;
    constexpr int popupHeight = 184;
    POINT cursor{};
    GetCursorPos(&cursor);
    MONITORINFO monitorInfo{sizeof(monitorInfo)};
    GetMonitorInfoW(MonitorFromPoint(cursor, MONITOR_DEFAULTTONEAREST), &monitorInfo);
    int x = std::clamp(cursor.x - popupWidth / 2,
                       monitorInfo.rcWork.left,
                       monitorInfo.rcWork.right - popupWidth);
    int y = monitorInfo.rcWork.bottom - popupHeight - 8;
    if (monitorInfo.rcWork.top > monitorInfo.rcMonitor.top) {
        y = monitorInfo.rcWork.top + 8;
    }

    g_volumePopupWindow = CreateWindowExW(
        WS_EX_TOOLWINDOW | WS_EX_TOPMOST | WS_EX_NOACTIVATE,
        kVolumePopupClass, L"Media app volume", WS_POPUP,
        x, y, popupWidth, popupHeight, g_taskbarWnd, nullptr,
        GetModuleHandleW(nullptr), nullptr);
    if (!g_volumePopupWindow) return;

    const int cornerPreference = 2;
    DwmSetWindowAttribute(g_volumePopupWindow, 33, &cornerPreference,
                          sizeof(cornerPreference));
    const BOOL useDarkMode = TRUE;
    DwmSetWindowAttribute(g_volumePopupWindow, 20, &useDarkMode,
                          sizeof(useDarkMode));
    ShowWindow(g_volumePopupWindow, SW_SHOWNOACTIVATE);
    SetWindowPos(g_volumePopupWindow, HWND_TOPMOST, x, y, popupWidth, popupHeight,
                 SWP_SHOWWINDOW | SWP_NOACTIVATE);
}

static std::wstring TrimCopy(std::wstring value) {
    const wchar_t* ws = L" \t\r\n";
    size_t first = value.find_first_not_of(ws);
    if (first == std::wstring::npos) return L"";
    size_t last = value.find_last_not_of(ws);
    return value.substr(first, last - first + 1);
}

static bool IsIgnoredMediaApp(const std::wstring& appUserModelId) {
    if (g_settings.ignoredProcesses.empty() || appUserModelId.empty()) return false;

    std::wstring appLower = ToLowerCopy(appUserModelId);
    std::wstring appStemLower = ToLowerCopy(PathFileStem(appUserModelId));
    size_t start = 0;
    while (start <= g_settings.ignoredProcesses.size()) {
        size_t end = g_settings.ignoredProcesses.find(L';', start);
        std::wstring item = TrimCopy(g_settings.ignoredProcesses.substr(
            start, end == std::wstring::npos ? std::wstring::npos : end - start));
        if (!item.empty()) {
            std::wstring itemLower = ToLowerCopy(item);
            std::wstring itemStemLower = ToLowerCopy(PathFileStem(item));
            if (appLower == itemLower ||
                appStemLower == itemStemLower ||
                appLower.find(itemLower) != std::wstring::npos ||
                appLower.find(itemStemLower) != std::wstring::npos) {
                return true;
            }
        }
        if (end == std::wstring::npos) break;
        start = end + 1;
    }
    return false;
}

static std::wstring GetWindowAppUserModelId(HWND hWnd) {
    static const PROPERTYKEY kAppUserModelIdKey = {
        {0x9F4C2855, 0x9F79, 0x4B39, {0xA8, 0xD0, 0xE1, 0xD4, 0x2D, 0xE1, 0xD5, 0xF3}},
        5
    };
    std::wstring result;
    IPropertyStore* store = nullptr;
    if (SUCCEEDED(SHGetPropertyStoreForWindow(hWnd, IID_PPV_ARGS(&store))) && store) {
        PROPVARIANT pv;
        PropVariantInit(&pv);
        if (SUCCEEDED(store->GetValue(kAppUserModelIdKey, &pv)) && pv.vt == VT_LPWSTR && pv.pwszVal) {
            result = pv.pwszVal;
        }
        PropVariantClear(&pv);
        store->Release();
    }
    return result;
}

static bool AppIdMatchesProcess(const std::wstring& appUserModelId, HWND hWnd, DWORD* outPid = nullptr, std::wstring* outProcPath = nullptr) {
    DWORD pid = 0;
    GetWindowThreadProcessId(hWnd, &pid);
    if (outPid) *outPid = pid;
    if (!pid) return false;

    std::wstring windowAumid = GetWindowAppUserModelId(hWnd);
    std::wstring appLower = ToLowerCopy(appUserModelId);
    std::wstring windowAumidLower = ToLowerCopy(windowAumid);

    if (!windowAumidLower.empty() &&
        (appLower == windowAumidLower ||
         appLower.find(windowAumidLower) != std::wstring::npos ||
         windowAumidLower.find(appLower) != std::wstring::npos)) {
        return true;
    }

    wchar_t procPath[MAX_PATH] = {};
    HANDLE hProc = OpenProcess(PROCESS_QUERY_LIMITED_INFORMATION, FALSE, pid);
    if (hProc) {
        DWORD sz = MAX_PATH;
        QueryFullProcessImageNameW(hProc, 0, procPath, &sz);
        CloseHandle(hProc);
    }
    if (outProcPath) *outProcPath = procPath;

    std::wstring procLower = ToLowerCopy(PathFileStem(procPath));
    if (procLower.empty()) return false;

    std::wstring appStemLower = ToLowerCopy(PathFileStem(appUserModelId));
    return appLower.find(procLower) != std::wstring::npos ||
           procLower.find(appLower) != std::wstring::npos ||
           appStemLower.find(procLower) != std::wstring::npos ||
           procLower.find(appStemLower) != std::wstring::npos ||
           (!windowAumidLower.empty() &&
            (windowAumidLower.find(procLower) != std::wstring::npos ||
             procLower.find(windowAumidLower) != std::wstring::npos));
}

static std::vector<BYTE> RenderIconToBytes(HICON hIcon, int iconSize) {
    if (!hIcon || iconSize <= 0) return {};

    ICONINFO ii{};
    if (!GetIconInfo(hIcon, &ii)) return {};

    BITMAP bm{};
    GetObjectW(ii.hbmColor ? ii.hbmColor : ii.hbmMask, sizeof(bm), &bm);
    if (ii.hbmColor) DeleteObject(ii.hbmColor);
    if (ii.hbmMask)  DeleteObject(ii.hbmMask);

    int srcW = bm.bmWidth  > 0 ? bm.bmWidth  : iconSize;
    int srcH = bm.bmHeight > 0 ? bm.bmHeight : iconSize;

    HDC screenDC = GetDC(nullptr);
    HDC hdc      = CreateCompatibleDC(screenDC);
    HBITMAP hBmp = CreateCompatibleBitmap(screenDC, srcW, srcH);
    ReleaseDC(nullptr, screenDC);
    HBITMAP hOld = (HBITMAP)SelectObject(hdc, hBmp);

    RECT rc{ 0, 0, srcW, srcH };
    HBRUSH hBr = (HBRUSH)GetStockObject(BLACK_BRUSH);
    FillRect(hdc, &rc, hBr);
    DrawIconEx(hdc, 0, 0, hIcon, srcW, srcH, 0, nullptr, DI_NORMAL);

    BITMAPINFO bi{};
    bi.bmiHeader.biSize        = sizeof(BITMAPINFOHEADER);
    bi.bmiHeader.biWidth       = srcW;
    bi.bmiHeader.biHeight      = -srcH;
    bi.bmiHeader.biPlanes      = 1;
    bi.bmiHeader.biBitCount    = 32;
    bi.bmiHeader.biCompression = BI_RGB;

    std::vector<BYTE> src(srcW * srcH * 4, 0);
    GetDIBits(hdc, hBmp, 0, srcH, src.data(), &bi, DIB_RGB_COLORS);
    SelectObject(hdc, hOld);
    DeleteObject(hBmp);
    DeleteDC(hdc);

    for (int i = 0; i + 3 < (int)src.size(); i += 4)
        std::swap(src[i], src[i + 2]);

    if (srcW == iconSize && srcH == iconSize)
        return src;

    std::vector<BYTE> dst(iconSize * iconSize * 4, 0);
    float scaleX = (float)srcW / iconSize;
    float scaleY = (float)srcH / iconSize;
    for (int dy = 0; dy < iconSize; ++dy) {
        for (int dx = 0; dx < iconSize; ++dx) {
            float fx = (dx + 0.5f) * scaleX - 0.5f;
            float fy = (dy + 0.5f) * scaleY - 0.5f;
            int x0 = (int)fx; int y0 = (int)fy;
            int x1 = x0 + 1;  int y1 = y0 + 1;
            x0 = x0 < 0 ? 0 : (x0 > srcW - 1 ? srcW - 1 : x0);
            y0 = y0 < 0 ? 0 : (y0 > srcH - 1 ? srcH - 1 : y0);
            x1 = x1 < 0 ? 0 : (x1 > srcW - 1 ? srcW - 1 : x1);
            y1 = y1 < 0 ? 0 : (y1 > srcH - 1 ? srcH - 1 : y1);
            float wx = fx - (int)fx; float wy = fy - (int)fy;
            int di = (dy * iconSize + dx) * 4;
            for (int c = 0; c < 4; ++c) {
                float v = src[(y0 * srcW + x0) * 4 + c] * (1-wx)*(1-wy)
                        + src[(y0 * srcW + x1) * 4 + c] * wx    *(1-wy)
                        + src[(y1 * srcW + x0) * 4 + c] * (1-wx)* wy
                        + src[(y1 * srcW + x1) * 4 + c] * wx    * wy;
                dst[di + c] = (BYTE)(v + 0.5f);
            }
        }
    }
    return dst;
}

static std::vector<BYTE> FetchAppIconBytes(const std::wstring& appUserModelId, int iconSize) {
    std::vector<BYTE> result;
    if (appUserModelId.empty()) return result;

    auto Render = [&](HICON h, bool own) -> bool {
        if (!h) return false;
        result = RenderIconToBytes(h, iconSize);
        if (own) DestroyIcon(h);
        return !result.empty();
    };

    {
        std::wstring shellPath = L"shell:AppsFolder\\" + appUserModelId;
        PIDLIST_ABSOLUTE pidl = nullptr;
        if (SUCCEEDED(SHParseDisplayName(shellPath.c_str(), nullptr, &pidl, 0, nullptr)) && pidl) {
            SHFILEINFOW sfi{};
            DWORD flags = SHGFI_PIDL | SHGFI_ICON | SHGFI_LARGEICON;
            if (SHGetFileInfoW(reinterpret_cast<LPCWSTR>(pidl), 0, &sfi, sizeof(sfi), flags) && sfi.hIcon) {
                CoTaskMemFree(pidl);
                if (Render(sfi.hIcon, true)) return result;
            } else {
                CoTaskMemFree(pidl);
            }
        }
    }
    {
        struct EnumCtx {
            const std::wstring* aumid;
            HICON  exactIcon = nullptr;
            HICON  fuzzyIcon = nullptr;
            DWORD  exactPid  = 0;
            DWORD  fuzzyPid  = 0;
            std::wstring exactPath;
            std::wstring fuzzyPath;
        };
        EnumCtx ctx{ &appUserModelId };

        EnumWindows([](HWND hWnd, LPARAM lParam) CALLBACK -> BOOL {
            if (!IsWindowVisible(hWnd)) return TRUE;
            auto* c = reinterpret_cast<EnumCtx*>(lParam);

            if (!c->exactIcon) {
                IPropertyStore* pps = nullptr;
                if (SUCCEEDED(SHGetPropertyStoreForWindow(hWnd, IID_PPV_ARGS(&pps)))) {
                    PROPVARIANT var;
                    PropVariantInit(&var);
                    if (SUCCEEDED(pps->GetValue(PKEY_AppUserModel_ID, &var)) && var.vt == VT_LPWSTR) {
                        std::wstring winAumid  = ToLowerCopy(std::wstring(var.pwszVal));
                        std::wstring wantAumid = ToLowerCopy(*c->aumid);
                        if (winAumid == wantAumid) {
                            HICON icon = (HICON)SendMessageW(hWnd, WM_GETICON, ICON_BIG,   0);
                            if (!icon) icon = (HICON)SendMessageW(hWnd, WM_GETICON, ICON_SMALL, 0);
                            if (!icon) icon = (HICON)GetClassLongPtrW(hWnd, GCLP_HICON);
                            if (!icon) icon = (HICON)GetClassLongPtrW(hWnd, GCLP_HICONSM);
                            if (icon) {
                                c->exactIcon = icon;
                                GetWindowThreadProcessId(hWnd, &c->exactPid);
                                wchar_t path[MAX_PATH]{};
                                HANDLE hProc = OpenProcess(PROCESS_QUERY_LIMITED_INFORMATION, FALSE, c->exactPid);
                                if (hProc) { DWORD sz = MAX_PATH; QueryFullProcessImageNameW(hProc, 0, path, &sz); CloseHandle(hProc); }
                                c->exactPath = path;
                                return FALSE;
                            }
                        }
                    }
                    PropVariantClear(&var);
                    pps->Release();
                }
            }

            if (!c->exactIcon && !c->fuzzyIcon) {
                std::wstring windowAumid = GetWindowAppUserModelId(hWnd);
                if (windowAumid.empty()) {
                    DWORD pid = 0;
                    std::wstring procPath;
                    if (AppIdMatchesProcess(*c->aumid, hWnd, &pid, &procPath)) {
                        HICON icon = (HICON)SendMessageW(hWnd, WM_GETICON, ICON_BIG,   0);
                        if (!icon) icon = (HICON)SendMessageW(hWnd, WM_GETICON, ICON_SMALL, 0);
                        if (!icon) icon = (HICON)GetClassLongPtrW(hWnd, GCLP_HICON);
                        if (!icon) icon = (HICON)GetClassLongPtrW(hWnd, GCLP_HICONSM);
                        if (icon) {
                            c->fuzzyIcon = icon;
                            c->fuzzyPid  = pid;
                            c->fuzzyPath = procPath;
                        } else if (!c->fuzzyPid) {
                            c->fuzzyPid  = pid;
                            c->fuzzyPath = procPath;
                        }
                    }
                }
            }

            return TRUE;
        }, reinterpret_cast<LPARAM>(&ctx));

        if (ctx.exactIcon && Render(ctx.exactIcon, false)) return result;

        if (ctx.fuzzyIcon) {
            HANDLE hProc = OpenProcess(PROCESS_QUERY_LIMITED_INFORMATION, FALSE, ctx.fuzzyPid);
            if (hProc) {
                DWORD exitCode = 0;
                if (GetExitCodeProcess(hProc, &exitCode) && exitCode == STILL_ACTIVE) {
                    CloseHandle(hProc);
                    if (Render(ctx.fuzzyIcon, false)) return result;
                } else {
                    CloseHandle(hProc);
                }
            }
        }

        auto resolvePid = [](DWORD pid) -> std::wstring {
            if (!pid) return {};
            wchar_t path[MAX_PATH]{};
            HANDLE hProc = OpenProcess(PROCESS_QUERY_LIMITED_INFORMATION, FALSE, pid);
            if (hProc) { DWORD sz = MAX_PATH; QueryFullProcessImageNameW(hProc, 0, path, &sz); CloseHandle(hProc); }
            return path;
        };

        auto tryExePath = [&](const std::wstring& path) -> bool {
            if (path.empty()) return false;
            SHFILEINFOW sfi{};
            if (SHGetFileInfoW(path.c_str(), 0, &sfi, sizeof(sfi), SHGFI_ICON | SHGFI_LARGEICON) && sfi.hIcon)
                return Render(sfi.hIcon, true);
            if (SHGetFileInfoW(path.c_str(), 0, &sfi, sizeof(sfi), SHGFI_ICON | SHGFI_SMALLICON) && sfi.hIcon)
                return Render(sfi.hIcon, true);
            return false;
        };

        auto tryExtractIconEx = [&](const std::wstring& path) -> bool {
            if (path.empty()) return false;
            HICON hL = nullptr, hS = nullptr;
            if (ExtractIconExW(path.c_str(), 0, &hL, &hS, 1)) {
                HICON chosen = hL ? hL : hS;
                if (chosen) {
                    bool ok = Render(chosen, false);
                    if (hL) DestroyIcon(hL);
                    if (hS) DestroyIcon(hS);
                    if (ok) return true;
                }
            }
            return false;
        };

        std::wstring ep = ctx.exactPath.empty() ? resolvePid(ctx.exactPid) : ctx.exactPath;
        std::wstring fp = ctx.fuzzyPath.empty() ? resolvePid(ctx.fuzzyPid) : ctx.fuzzyPath;

        if (tryExePath(ep))        return result;
        if (tryExePath(fp))        return result;
        if (tryExtractIconEx(ep))  return result;
        if (tryExtractIconEx(fp))  return result;
    }

    if (appUserModelId.find(L".exe") != std::wstring::npos) {
        std::wstring exePath = appUserModelId;
        if (exePath.size() >= 2 && exePath.front() == L'"' && exePath.back() == L'"')
            exePath = exePath.substr(1, exePath.size() - 2);

        SHFILEINFOW sfi{};
        if (SHGetFileInfoW(exePath.c_str(), 0, &sfi, sizeof(sfi), SHGFI_ICON | SHGFI_LARGEICON) && sfi.hIcon)
            if (Render(sfi.hIcon, true)) return result;

        HICON hL = nullptr, hS = nullptr;
        if (ExtractIconExW(exePath.c_str(), 0, &hL, &hS, 1)) {
            HICON chosen = hL ? hL : hS;
            if (chosen) {
                Render(chosen, false);
                if (hL) DestroyIcon(hL);
                if (hS) DestroyIcon(hS);
                if (!result.empty()) return result;
            }
        }
    }

    return result;
}
static void UpdateMediaTimeline(
    const GlobalSystemMediaTransportControlsSession& session) {
    if (!session) return;
    try {
        auto timeline = session.GetTimelineProperties();
        constexpr int64_t kTicksPerSecond = 10'000'000;
        int64_t startTicks = timeline.StartTime().count();
        int64_t endTicks = timeline.EndTime().count();
        int64_t positionTicks = timeline.Position().count();
        int64_t durationSeconds = std::max<int64_t>(
            0, (endTicks - startTicks) / kTicksPerSecond);
        int64_t positionSeconds = std::clamp<int64_t>(
            (positionTicks - startTicks) / kTicksPerSecond,
            0, durationSeconds);

        std::lock_guard<std::mutex> lock(g_mediaMtx);
        g_media.positionSeconds = positionSeconds;
        g_media.durationSeconds = durationSeconds;
        g_media.timelineSampleTick = GetTickCount64();
    } catch (...) {
        Wh_Log(L"Media timeline: unavailable");
    }
}

static void FetchMediaPropertiesAsync() {
    Wh_Log(L"FetchMediaPropertiesAsync: Called");
    std::thread([]() {
        if (g_unloading) return;
        winrt::init_apartment(winrt::apartment_type::multi_threaded);
        try {
            GlobalSystemMediaTransportControlsSession session{nullptr};
            std::wstring aumid;
            {
                std::lock_guard<std::mutex> lk(g_sessionMtx);
                session = g_currentSession;
                if (session) {
                    try {
                        aumid = std::wstring(session.SourceAppUserModelId());
                    } catch (...) {
                        winrt::uninit_apartment();
                        return;
                    }
                }
            }
            if (!session) {
                winrt::uninit_apartment();
                return;
            }

            try {
                auto props = session.TryGetMediaPropertiesAsync().get();
                if (!props) {
                    winrt::uninit_apartment();
                    return;
                }

                std::vector<BYTE> thumbBytes;
                uint64_t          thumbHash = 0;

                if (auto thumbRef = props.Thumbnail()) {
                    try {
                        auto stream = thumbRef.OpenReadAsync().get();
                        if (stream) {
                            UINT64 sz = stream.Size();
                            if (sz > 0 && sz < 4 * 1024 * 1024) {
                                DataReader reader(stream);
                                reader.LoadAsync((UINT32)sz).get();
                                thumbBytes.resize((size_t)sz);
                                reader.ReadBytes(winrt::array_view<BYTE>(thumbBytes));
                                reader.DetachStream();
                                for (size_t i = 0; i < thumbBytes.size(); i += 1024)
                                    thumbHash = thumbHash * 31 + thumbBytes[i];
                            }
                        }
                    } catch (...) { thumbBytes.clear(); }
                }

                std::vector<BYTE> appIconBytes;
                std::wstring      appIconKey;
                bool forceIconRefresh = false;
                {
                    std::lock_guard<std::mutex> lk(g_mediaMtx);
                    appIconKey = g_media.appIconKey;
                    appIconBytes = g_media.appIconBytes;
                }
                {
                    std::lock_guard<std::mutex> lk(g_sessionMtx);
                    forceIconRefresh = g_userSwitchedSession;
                }
                if (g_settings.showAppIcon && (aumid != appIconKey || appIconBytes.empty() || forceIconRefresh || g_cachedAppIconSize != g_settings.appIconSize)) {
                    try {
                        appIconBytes = FetchAppIconBytes(aumid, g_settings.appIconSize);
                        appIconKey   = aumid;
                        g_cachedAppIconSize = g_settings.appIconSize;
                    } catch (...) {

                    }
                }

                {
                    std::lock_guard<std::mutex> lk(g_mediaMtx);
                    try {
                        g_media.title          = std::wstring(props.Title());
                        g_media.artist         = std::wstring(props.Artist());
                        g_media.albumTitle     = std::wstring(props.AlbumTitle());
                        g_media.hasMedia       = !g_media.title.empty() || !g_media.artist.empty();
                        g_media.thumbnailBytes = std::move(thumbBytes);
                        g_media.thumbnailHash  = thumbHash;
                        g_media.appUserModelId = aumid;
                        if (g_settings.showAppIcon) {
                            g_media.appIconBytes   = std::move(appIconBytes);
                            g_media.appIconKey     = appIconKey;
                        }
                        Wh_Log(L"FetchMediaPropertiesAsync: Set hasMedia=%d (title='%s', artist='%s')",
                               g_media.hasMedia, g_media.title.c_str(), g_media.artist.c_str());
                    } catch (...) {

                    }
                }

                if (forceIconRefresh && !appIconBytes.empty()) {
                    std::lock_guard<std::mutex> lk(g_sessionMtx);
                    g_userSwitchedSession = false;
                    Wh_Log(L"FetchMediaPropertiesAsync: Icon refreshed after session switch");
                }
                UpdateMediaTimeline(session);
            } catch (...) {

            }
        } catch (...) {}
        Wh_Log(L"FetchMediaPropertiesAsync: About to call DispatchMediaUpdate");
        DispatchMediaUpdate();
        winrt::uninit_apartment();
    }).detach();
}

static void FetchPlaybackInfoAsync() {
    Wh_Log(L"FetchPlaybackInfoAsync: Called");
    std::thread([]() {
        if (g_unloading) return;
        winrt::init_apartment(winrt::apartment_type::multi_threaded);
        try {
            GlobalSystemMediaTransportControlsSession session{nullptr};
            { std::lock_guard<std::mutex> lk(g_sessionMtx); session = g_currentSession; }
            if (session) {
                try {
                    auto info = session.GetPlaybackInfo();
                    if (!info) {
                        winrt::uninit_apartment();
                        return;
                    }

                    auto status = info.PlaybackStatus();
                    bool playing = (status == GlobalSystemMediaTransportControlsSessionPlaybackStatus::Playing);
                    bool wasPlaying = false;
                    {
                        std::lock_guard<std::mutex> lk(g_mediaMtx);
                        wasPlaying = g_media.isPlaying;
                        g_media.isPlaying = playing;
                    }
                    UpdateMediaTimeline(session);

                    if (playing != wasPlaying) {
                        Wh_Log(L"Playback state changed: %s -> %s",
                            wasPlaying ? L"Playing" : L"Not Playing",
                            playing ? L"Playing" : L"Not Playing");
                    }

                    try {
                        auto shuffleRef = info.IsShuffleActive();
                        if (shuffleRef) {
                            g_shuffleEnabled = shuffleRef.Value();
                        }
                    } catch (...) {}

                    try {
                        auto repeatRef = info.AutoRepeatMode();
                        if (repeatRef) {
                            using RM = winrt::Windows::Media::MediaPlaybackAutoRepeatMode;
                            auto v = repeatRef.Value();
                            if (v == RM::Track) g_repeatMode = RepeatMode::One;
                            else if (v == RM::List) g_repeatMode = RepeatMode::All;
                            else g_repeatMode = RepeatMode::Off;
                        }
                    } catch (...) {}

                    try {
                        auto controls = info.Controls();
                        if (controls) {
                            bool canPrev   = controls.IsPreviousEnabled();
                            bool canNext   = controls.IsNextEnabled();
                            bool canShuf   = controls.IsShuffleEnabled();
                            bool canRep    = controls.IsRepeatEnabled();
                            bool canSeek   = controls.IsPlaybackPositionEnabled();
                            {
                                std::lock_guard<std::mutex> lk(g_mediaMtx);
                                g_media.canSkipPrevious = canPrev;
                                g_media.canSkipNext     = canNext;
                                g_media.canShuffle      = canShuf;
                                g_media.canRepeat       = canRep;
                                g_media.canSeek         = canSeek;
                            }
                        }
                    } catch (...) {}
                } catch (...) {

                }
            }
        } catch (...) {}
        Wh_Log(L"FetchPlaybackInfoAsync: About to call DispatchMediaUpdate");
        DispatchMediaUpdate();
        winrt::uninit_apartment();
    }).detach();
}

static void DetachCurrentSession() {
    std::lock_guard<std::mutex> lk(g_sessionMtx);
    if (!g_currentSession) return;
    try {
        if (g_evMediaProps.value) { g_currentSession.MediaPropertiesChanged(g_evMediaProps); g_evMediaProps = {}; }
        if (g_evPlayback.value)   { g_currentSession.PlaybackInfoChanged(g_evPlayback); g_evPlayback = {}; }
        if (g_evTimeline.value)   { g_currentSession.TimelinePropertiesChanged(g_evTimeline); g_evTimeline = {}; }
    } catch (...) {}
    g_currentSession = nullptr;
    {
        std::lock_guard<std::mutex> lkm(g_mediaMtx);
        g_media.canSkipPrevious = true;
        g_media.canSkipNext     = true;
        g_media.canShuffle      = true;
        g_media.canRepeat       = true;
        g_media.canSeek         = true;
        g_media.positionSeconds = 0;
        g_media.durationSeconds = 0;
        g_media.timelineSampleTick = 0;
    }
}

static GlobalSystemMediaTransportControlsSession PickBestSession() {
    if (!g_sessionMgr) return nullptr;
    try {
        auto sessions = g_sessionMgr.GetSessions();
        int sessionCount = sessions.Size();
        Wh_Log(L"PickBestSession: Found %d media sessions", sessionCount);

        GlobalSystemMediaTransportControlsSession best{nullptr};
        int index = 0;
        for (auto const& s : sessions) {
            try {
                std::wstring appId = s.SourceAppUserModelId().c_str();
                if (IsIgnoredMediaApp(appId)) {
                    Wh_Log(L"PickBestSession: Session %d (%s) is ignored", index, appId.c_str());
                    index++;
                    continue;
                }

                auto pb = s.GetPlaybackInfo();
                if (!pb) {
                    Wh_Log(L"PickBestSession: Session %d (%s) has no playback info", index, appId.c_str());
                    index++;
                    continue;
                }

                auto status = pb.PlaybackStatus();
                const wchar_t* statusStr = L"Unknown";
                if (status == GlobalSystemMediaTransportControlsSessionPlaybackStatus::Playing) statusStr = L"Playing";
                else if (status == GlobalSystemMediaTransportControlsSessionPlaybackStatus::Paused) statusStr = L"Paused";
                else if (status == GlobalSystemMediaTransportControlsSessionPlaybackStatus::Stopped) statusStr = L"Stopped";

                Wh_Log(L"PickBestSession: Session %d (%s) status: %s", index, appId.c_str(), statusStr);

                if (status == GlobalSystemMediaTransportControlsSessionPlaybackStatus::Playing) {
                    Wh_Log(L"PickBestSession: Selected playing session %d (%s)", index, appId.c_str());
                    return s;
                }
                if (!best) best = s;
            } catch (...) {
                Wh_Log(L"PickBestSession: Exception processing session %d", index);
            }
            index++;
        }

        if (best) {
            try {
                std::wstring appId = best.SourceAppUserModelId().c_str();
                Wh_Log(L"PickBestSession: No playing session, selected first available (%s)", appId.c_str());
            } catch (...) {
                Wh_Log(L"PickBestSession: No playing session, selected first available (app ID unavailable)");
            }
        } else {
            Wh_Log(L"PickBestSession: No suitable session found");
        }

        return best;
    } catch (...) {
        Wh_Log(L"PickBestSession: Exception occurred");
        return nullptr;
    }
}

static void AttachToSession(GlobalSystemMediaTransportControlsSession session) {
    if (!session) {
        Wh_Log(L"AttachToSession: No session provided, detaching current session");
        DetachCurrentSession();
        {
            std::lock_guard<std::mutex> lk(g_mediaMtx);
            g_media = MediaState{};
            Wh_Log(L"AttachToSession: Cleared media state (hasMedia=false)");
        }
        DispatchMediaUpdate();
        return;
    }

    bool needsReattach = false;
    {
        std::lock_guard<std::mutex> lk(g_sessionMtx);
        if (g_currentSession == session) {
            if (!g_evMediaProps.value || !g_evPlayback.value ||
                !g_evTimeline.value) {
                Wh_Log(L"AttachToSession: Same session but events not attached, reattaching");
                needsReattach = true;
            } else {
                Wh_Log(L"AttachToSession: Same session already attached, fetching data");
                goto fetch;
            }
        }
    }
    (void)needsReattach;

    try {
        std::wstring appId = session.SourceAppUserModelId().c_str();
        Wh_Log(L"AttachToSession: Attaching to new session from app: %s", appId.c_str());
    } catch (...) {
        Wh_Log(L"AttachToSession: Attaching to new session (app ID unavailable)");
    }

    DetachCurrentSession();

    // Do not carry the previous player's volume glyph/value into the new
    // session while its own audio session is being discovered.
    g_currentVolumePercent = -1;
    g_currentVolumeMuted = false;

    {
        std::lock_guard<std::mutex> lk(g_mediaMtx);
        g_media.appIconKey   = L"";
        g_media.appIconBytes.clear();
    }
    g_cachedAppIconSize = -1;

    ResetScrollState(g_titleScroll);
    ResetScrollState(g_artistScroll);

    {
        std::lock_guard<std::mutex> lk(g_sessionMtx);
        g_currentSession = session;
        try {
            g_evMediaProps = g_currentSession.MediaPropertiesChanged([](auto const&, auto const&) {
                Wh_Log(L"MediaPropertiesChanged event fired");
                if (!g_unloading) FetchMediaPropertiesAsync();
            });
            g_evPlayback = g_currentSession.PlaybackInfoChanged([](auto const&, auto const&) {
                Wh_Log(L"PlaybackInfoChanged event fired");
                if (!g_unloading) FetchPlaybackInfoAsync();
            });
            g_evTimeline = g_currentSession.TimelinePropertiesChanged([](auto const&, auto const&) {
                Wh_Log(L"TimelinePropertiesChanged event fired");
                if (!g_unloading) FetchPlaybackInfoAsync();
            });
            Wh_Log(L"AttachToSession: Event handlers attached successfully");
        } catch (...) {
            Wh_Log(L"AttachToSession: Failed to attach event handlers");
            g_currentSession = nullptr;
            return;
        }
    }
fetch:
    FetchMediaPropertiesAsync();
    FetchPlaybackInfoAsync();
}

static void OnSessionsChanged() {
    if (g_unloading) return;
    bool userSwitched = false;
    bool forceRefresh = g_forceSessionRefresh.exchange(false);
    {
        std::lock_guard<std::mutex> lk(g_sessionMtx);
        userSwitched = g_userSwitchedSession;
    }

    try {
        if (g_sessionMgr) {
            auto sessions = g_sessionMgr.GetSessions();
            g_sessionCount.store((int)sessions.Size());
        }
    } catch (...) {}

    Wh_Log(L"OnSessionsChanged: userSwitched=%d, forceRefresh=%d", userSwitched, forceRefresh);

    if (forceRefresh || !userSwitched) {
        try {
            auto newSession = PickBestSession();
            if (newSession) {
                try {
                    auto pb = newSession.GetPlaybackInfo();
                    if (pb && pb.PlaybackStatus() == GlobalSystemMediaTransportControlsSessionPlaybackStatus::Playing) {
                        Wh_Log(L"OnSessionsChanged: Found actively playing session, resetting user switch flag");
                        std::lock_guard<std::mutex> lk(g_sessionMtx);
                        g_userSwitchedSession = false;
                    }
                } catch (...) {}
            } else {
                Wh_Log(L"OnSessionsChanged: No session found, resetting user switch flag");
                std::lock_guard<std::mutex> lk(g_sessionMtx);
                g_userSwitchedSession = false;
            }
            AttachToSession(newSession);
        } catch (...) {
            Wh_Log(L"OnSessionsChanged: Exception occurred");
        }
    } else {
        Wh_Log(L"OnSessionsChanged: Skipping due to user switch - checking if current session still exists");
        try {
            bool currentSessionExists = false;
            GlobalSystemMediaTransportControlsSession currentSession{nullptr};
            {
                std::lock_guard<std::mutex> lk(g_sessionMtx);
                currentSession = g_currentSession;
            }

            if (currentSession) {
                auto sessions = g_sessionMgr.GetSessions();
                for (auto const& s : sessions) {
                    if (s == currentSession) {
                        currentSessionExists = true;
                        break;
                    }
                }
            }

            if (!currentSessionExists) {
                Wh_Log(L"OnSessionsChanged: Current session no longer exists, resetting user switch flag and picking new session");
                {
                    std::lock_guard<std::mutex> lk(g_sessionMtx);
                    g_userSwitchedSession = false;
                }
                auto newSession = PickBestSession();
                AttachToSession(newSession);
            } else {
                Wh_Log(L"OnSessionsChanged: Current session still exists, keeping it");
            }
        } catch (...) {
            Wh_Log(L"OnSessionsChanged: Exception checking current session validity");
        }
    }
}

static DWORD WINAPI MediaThreadProc(void*) {
    Wh_Log(L"MediaThreadProc: Starting media thread");
    try {
        winrt::init_apartment(winrt::apartment_type::multi_threaded);
        Wh_Log(L"MediaThreadProc: Requesting session manager");
        auto op = GlobalSystemMediaTransportControlsSessionManager::RequestAsync();
        while (op.Status() == winrt::Windows::Foundation::AsyncStatus::Started) {
            if (WaitForSingleObject(g_mediaStopEvent, 50) == WAIT_OBJECT_0) goto done;
        }
        g_sessionMgr = op.GetResults();
        Wh_Log(L"MediaThreadProc: Session manager obtained");

        g_evSessionsChanged = g_sessionMgr.SessionsChanged([](auto const&, auto const&) {
            Wh_Log(L"MediaThreadProc: SessionsChanged event fired");
            OnSessionsChanged();
        });
        g_evCurrentChanged  = g_sessionMgr.CurrentSessionChanged([](auto const&, auto const&) {
            Wh_Log(L"MediaThreadProc: CurrentSessionChanged event fired");
            OnSessionsChanged();
        });

        Wh_Log(L"MediaThreadProc: Initial session check");
        OnSessionsChanged();

        Wh_Log(L"MediaThreadProc: Waiting 2 seconds before retry check");
        if (WaitForSingleObject(g_mediaStopEvent, 2000) == WAIT_TIMEOUT) {
            if (!g_unloading) {
                Wh_Log(L"MediaThreadProc: Performing retry session check");
                g_forceSessionRefresh = true;
                OnSessionsChanged();
            }
        }

        Wh_Log(L"MediaThreadProc: Entering wait loop");
        WaitForSingleObject(g_mediaStopEvent, INFINITE);

        Wh_Log(L"MediaThreadProc: Shutting down");
        try { if (g_evSessionsChanged.value) g_sessionMgr.SessionsChanged(g_evSessionsChanged); } catch (...) { Wh_Log(L"MediaThreadProc: Failed to unregister SessionsChanged event"); }
        try { if (g_evCurrentChanged.value)  g_sessionMgr.CurrentSessionChanged(g_evCurrentChanged); } catch (...) { Wh_Log(L"MediaThreadProc: Failed to unregister CurrentSessionChanged event"); }
        DetachCurrentSession();
        g_sessionMgr = nullptr;
    done:
        winrt::uninit_apartment();
        Wh_Log(L"MediaThreadProc: Media thread ended");
    } catch (...) {
        Wh_Log(L"MediaThreadProc: Exception in media thread");
    }
    return 0;
}

static void StartMediaThread() {
    if (g_mediaThread) return;
    g_mediaStopEvent = CreateEventW(nullptr, TRUE, FALSE, nullptr);
    if (!g_mediaStopEvent) return;
    g_mediaThread = CreateThread(nullptr, 0, MediaThreadProc, nullptr, 0, nullptr);
    if (!g_mediaThread) { CloseHandle(g_mediaStopEvent); g_mediaStopEvent = nullptr; }
}
static void StopMediaThread() {
    if (g_mediaStopEvent) SetEvent(g_mediaStopEvent);
    if (g_mediaThread) { WaitForSingleObject(g_mediaThread, 5000); CloseHandle(g_mediaThread); g_mediaThread = nullptr; }
    if (g_mediaStopEvent) { CloseHandle(g_mediaStopEvent); g_mediaStopEvent = nullptr; }
}

static HANDLE g_timerThread    = nullptr;
static HANDLE g_timerStopEvent = nullptr;
static HANDLE g_timerUpdateEvent = nullptr;

static winrt::Windows::UI::Xaml::DispatcherTimer g_scrollDispatcherTimer{nullptr};
static winrt::event_token                        g_scrollDispatcherTimerToken{};
static bool                                       g_scrollDispatcherTimerHasToken = false;

static void TickScrollState(TextScrollState& s, int stepPx, int pauseMs, const std::wstring& mode) {
    if (!s.active) return;

    if (s.pausing) {
        s.pauseTick -= s.tickMs;
        if (s.pauseTick <= 0) {
            s.pausing = false;
            s.pauseTick = 0;
        }
        return;
    }

    double maxOff = s.textWidth - s.viewWidth + 10.0;
    if (maxOff < 0.0) maxOff = 0.0;

    if (mode == L"marquee") {
        // A true single-copy marquee: move only right-to-left until every
        // character has left the viewport, then restart beyond the right edge.
        // There is never a reflected/bouncing pass or a duplicated title.
        s.offset -= stepPx;
        if (s.offset <= -s.textWidth) {
            s.offset = s.viewWidth + g_settings.loopGap;
            s.pausing = true;
            s.pauseTick = pauseMs;
        }
    } else {

        if (s.forward) {
            s.offset += stepPx;
            if (s.offset >= maxOff) {
                s.offset = maxOff;
                s.forward = false;
                s.pausing = true;
                s.pauseTick = pauseMs;
            }
        } else {
            s.offset -= stepPx;
            if (s.offset <= 0.0) {
                s.offset = 0.0;
                s.forward = true;
                s.pausing = true;
                s.pauseTick = pauseMs;
            }
        }
    }
}

static void UpdateScrollTransforms();

static void ScrollTimerTick(winrt::Windows::Foundation::IInspectable const&,
                             winrt::Windows::Foundation::IInspectable const&) {
    if (g_unloading || g_applyingSettings) return;

    bool needsScroll = (g_titleScroll.active || g_artistScroll.active);
    if (!needsScroll) return;

    int stepPx = std::max(1, g_settings.scrollSpeed);
    int pauseMs = g_settings.scrollPauseDuration;

    TickScrollState(g_titleScroll, stepPx, pauseMs, g_settings.scrollMode);
    TickScrollState(g_artistScroll, stepPx, pauseMs, g_settings.scrollMode);

    UpdateScrollTransforms();
}

static void StartScrollTimer() {
    HWND hWnd = g_taskbarWnd;
    if (!hWnd || !IsWindow(hWnd)) return;

    RunFromWindowThread(hWnd, [](void*) {
        try {
            if (!g_scrollDispatcherTimer) {
                g_scrollDispatcherTimer = winrt::Windows::UI::Xaml::DispatcherTimer();
                g_scrollDispatcherTimer.Interval(
                    winrt::Windows::Foundation::TimeSpan{std::chrono::milliseconds(16)});
                g_scrollDispatcherTimerToken = g_scrollDispatcherTimer.Tick(&ScrollTimerTick);
                g_scrollDispatcherTimerHasToken = true;
            }
            g_scrollDispatcherTimer.Start();
        } catch (...) {}
    }, nullptr);
}

static void StopScrollTimer() {
    HWND hWnd = g_taskbarWnd;

    auto stop = [](void*) {
        try {
            if (g_scrollDispatcherTimer) {
                g_scrollDispatcherTimer.Stop();
                if (g_unloading) {
                    if (g_scrollDispatcherTimerHasToken) {
                        g_scrollDispatcherTimer.Tick(g_scrollDispatcherTimerToken);
                        g_scrollDispatcherTimerHasToken = false;
                    }
                    g_scrollDispatcherTimer = nullptr;
                }
            }
        } catch (...) {}
    };

    if (hWnd && IsWindow(hWnd)) {
        RunFromWindowThread(hWnd, stop, nullptr);
    } else {
        stop(nullptr);
    }
}

static void ResetScrollState(TextScrollState& s) {
    s.offset    = 0.0;
    s.textWidth = 0.0;
    s.viewWidth = 0.0;
    s.forward   = true;
    s.active    = false;
    s.pausing  = true;
    s.pauseTick = g_settings.scrollPauseDuration;
}

static constexpr wchar_t kTitleScrollViewName[]  = L"FluentMedia_TitleScrollView";
static constexpr wchar_t kArtistScrollViewName[] = L"FluentMedia_ArtistScrollView";
static constexpr wchar_t kTitleCloneName[]       = L"FluentMedia_TitleClone";
static constexpr wchar_t kArtistCloneName[]      = L"FluentMedia_ArtistClone";
static constexpr wchar_t kPanelGridName[]        = L"FluentMedia_PanelGrid";

static double GetAvailableScrollTextAreaWidth() {
    try {
        if (g_settings.playerMaxWidth <= 0) return 0.0;

        if (!g_playerGrid) return 0.0;
        auto panelFe = FindChildByName(g_playerGrid, kPanelGridName);
        if (!panelFe) return 0.0;
        auto panelGrid = panelFe.try_as<Grid>();
        if (!panelGrid) return 0.0;

        double total = panelGrid.ActualWidth();
        if (total <= 0.0) return 0.0;

        auto cols = panelGrid.ColumnDefinitions();
        double used = 0.0;
        for (uint32_t i = 0; i < cols.Size(); i++) {
            if (i == 1) continue;
            used += cols.GetAt(i).ActualWidth();
        }

        double leftMargin  = (double)g_settings.textAreaLeftMargin;
        double rightMargin = (double)g_settings.textAreaRightMargin;

        double available = total - used - leftMargin - rightMargin;
        if (available < 0.0) available = 0.0;
        return available;
    } catch (...) {
        return 0.0;
    }
}


static void UpdateScrollTransforms() {
    if (!g_playerGrid || (!g_settings.enableTitleScrolling && !g_settings.enableArtistScrolling)) return;
    bool isMarquee = (g_settings.scrollMode == L"marquee");

    if (g_settings.enableTitleScrolling) {
        try {
            if (auto fe = FindChildByName(g_playerGrid, kTitleScrollViewName)) {
                if (auto cv = fe.try_as<Canvas>()) {
                    int n = VisualTreeHelper::GetChildrenCount(cv);
                    for (int i = 0; i < n; i++) {
                        auto child = VisualTreeHelper::GetChild(cv, i);
                        if (auto tb = child.try_as<TextBlock>()) {
                            auto name = tb.Name();
                            if (name == kTitleBlockName) {
                                Canvas::SetLeft(tb, isMarquee
                                    ? g_titleScroll.offset
                                    : -g_titleScroll.offset);
                            } else if (name == kTitleCloneName) {
                                tb.Visibility(Visibility::Collapsed);
                            }
                        }
                    }
                }
            }
        } catch (...) {}
    }

    if (g_settings.enableArtistScrolling) {
        try {
            if (auto fe = FindChildByName(g_playerGrid, kArtistScrollViewName)) {
                if (auto cv = fe.try_as<Canvas>()) {
                    int n = VisualTreeHelper::GetChildrenCount(cv);
                    for (int i = 0; i < n; i++) {
                        auto child = VisualTreeHelper::GetChild(cv, i);
                        if (auto ab = child.try_as<TextBlock>()) {
                            auto name = ab.Name();
                            if (name == kArtistBlockName) {
                                Canvas::SetLeft(ab, isMarquee
                                    ? g_artistScroll.offset
                                    : -g_artistScroll.offset);
                            } else if (name == kArtistCloneName) {
                                ab.Visibility(Visibility::Collapsed);
                            }
                        }
                    }
                }
            }
        } catch (...) {}
    }
}

static void DispatchMediaUpdate() {
    if (g_unloading || g_applyingSettings) return;

    g_needsUiUpdate = true;
    SignalDiscordPresenceUpdate();
    if (g_timerUpdateEvent) {
        SetEvent(g_timerUpdateEvent);
    }
}

static void RefreshPlayerContents();
static void UpdateVisibility();
static void RefreshThemeColors();
static void RemovePlayerGrid();
static bool InjectPlayerGrid();


static std::atomic<bool> g_themeChangePending{false};

static DWORD WINAPI TimerThreadProc(void*) {
    static bool lastThemeWasLight = IsSystemLightTheme();
    ULONGLONG nextVolumePollTick = 0;
    HRESULT timerApartment = CoInitializeEx(nullptr, COINIT_MULTITHREADED);

    HKEY hKey = nullptr;
    HANDLE hEvent = CreateEventW(nullptr, FALSE, FALSE, nullptr);
    if (RegOpenKeyExW(HKEY_CURRENT_USER, L"Software\\Microsoft\\Windows\\CurrentVersion\\Themes\\Personalize", 0, KEY_NOTIFY, &hKey) == ERROR_SUCCESS) {
        RegNotifyChangeKeyValue(hKey, FALSE, REG_NOTIFY_CHANGE_LAST_SET, hEvent, TRUE);
    }

    while (!g_unloading) {
        HANDLE handles[] = {g_timerStopEvent, hEvent, g_timerUpdateEvent};
        DWORD wait = WaitForMultipleObjects(3, handles, FALSE, 500);

        if (wait == WAIT_OBJECT_0) break;
        if (g_applyingSettings) continue;

        HWND hWnd = g_taskbarWnd;
        if (!hWnd || !IsWindow(hWnd)) {
            hWnd = FindCurrentProcessTaskbarWnd();
            g_taskbarWnd = hWnd;
            if (!hWnd) continue;
        }

        if (wait == WAIT_OBJECT_0 + 1) {
            if (hKey) {
                RegNotifyChangeKeyValue(hKey, FALSE, REG_NOTIFY_CHANGE_LAST_SET, hEvent, TRUE);
            }
            bool currentThemeIsLight = IsSystemLightTheme();
            if (currentThemeIsLight != lastThemeWasLight) {
                lastThemeWasLight = currentThemeIsLight;
                g_themeChangePending = true;
                g_needsUiUpdate = true;
                if (g_timerUpdateEvent) SetEvent(g_timerUpdateEvent);
            }
        }

        if (g_themeChangePending.exchange(false)) {
            Sleep(150);
            if (!g_unloading && !g_applyingSettings) {
                RunFromWindowThread(hWnd, [](void*) {
                    if (!g_unloading && !g_applyingSettings && g_playerGrid) {
                        RefreshThemeColors();
                    }
                }, nullptr);
            }
        }

        // Audio-session enumeration is comparatively expensive. Poll quickly
        // while the volume flyout is visible, otherwise refresh only every
        // 1.5 seconds or immediately after a media-state update.
        ULONGLONG nowTick = GetTickCount64();
        bool volumePopupVisible = g_volumePopupWindow &&
                                  IsWindowVisible(g_volumePopupWindow);
        bool mediaUpdateSignaled = wait == WAIT_OBJECT_0 + 2;
        if (mediaUpdateSignaled || nowTick >= nextVolumePollTick) {
            int currentVolume = 0;
            bool currentMuted = false;
            GetCurrentControllableVolume(currentVolume, currentMuted);
            nextVolumePollTick = nowTick + (volumePopupVisible ? 250 : 1500);
        }

        bool needsUpdate = g_needsUiUpdate.exchange(false);

        if (g_settings.idleHideSeconds > 0) {
            bool playing = false;
            { std::lock_guard<std::mutex> lk(g_mediaMtx); playing = g_media.isPlaying; }
            if (playing) {
                g_idleSeconds = 0;
                g_idleTicks   = 0;
                if (g_hiddenByIdle) {
                    g_hiddenByIdle = false;
                    needsUpdate = true;
                }
            } else {
                ++g_idleTicks;
                if (g_idleTicks >= 2) {
                    g_idleTicks = 0;
                    ++g_idleSeconds;
                }
                if (!g_hiddenByIdle && g_idleSeconds >= g_settings.idleHideSeconds) {
                    g_hiddenByIdle = true;
                    needsUpdate = true;
                }
            }
        } else {
            if (g_hiddenByIdle) {
                g_hiddenByIdle = false;
                g_idleSeconds  = 0;
                g_idleTicks    = 0;
                needsUpdate    = true;
            }
        }

        if (needsUpdate) {
            RunFromWindowThread(hWnd, [](void*) {
                if (g_unloading || g_applyingSettings) return;
                if (g_playerGrid) {
                    g_hookFailCount = 0;
                    RefreshPlayerContents();
                    UpdateVisibility();
                }
            }, nullptr);
        }
    }

    if (hKey) RegCloseKey(hKey);
    if (hEvent) CloseHandle(hEvent);
    if (SUCCEEDED(timerApartment)) CoUninitialize();
    return 0;
}

static void StartTimerThread() {
    if (g_timerThread) return;
    g_timerStopEvent = CreateEventW(nullptr, TRUE, FALSE, nullptr);
    g_timerUpdateEvent = CreateEventW(nullptr, FALSE, FALSE, nullptr);
    if (!g_timerStopEvent || !g_timerUpdateEvent) {
        if (g_timerStopEvent) CloseHandle(g_timerStopEvent);
        if (g_timerUpdateEvent) CloseHandle(g_timerUpdateEvent);
        g_timerStopEvent = nullptr;
        g_timerUpdateEvent = nullptr;
        return;
    }

    g_timerThread    = CreateThread(nullptr, 0, TimerThreadProc, nullptr, 0, nullptr);
    if (!g_timerThread) {
        CloseHandle(g_timerStopEvent);
        g_timerStopEvent = nullptr;
        CloseHandle(g_timerUpdateEvent);
        g_timerUpdateEvent = nullptr;
        return;
    }

    if (g_settings.enableTitleScrolling || g_settings.enableArtistScrolling) {
        StartScrollTimer();
    }
    StartDiscordPresenceThread();
}
static void StopTimerThread() {
    StopDiscordPresenceThread();
    StopScrollTimer();
    if (g_timerStopEvent) SetEvent(g_timerStopEvent);
    if (g_timerThread) {
        DWORD tid = GetCurrentThreadId();
        HWND hTaskbar = g_taskbarWnd;
        bool isUiThread = hTaskbar && (GetWindowThreadProcessId(hTaskbar, nullptr) == tid);
        if (isUiThread) {
            DWORD result = WAIT_TIMEOUT;
            DWORD deadline = GetTickCount() + 2000;
            while (result == WAIT_TIMEOUT && GetTickCount() < deadline) {
                result = MsgWaitForMultipleObjects(1, &g_timerThread, FALSE, 50, QS_SENDMESSAGE);
                if (result == WAIT_OBJECT_0 + 1) {
                    MSG msg;
                    while (PeekMessageW(&msg, nullptr, 0, 0, PM_REMOVE | PM_QS_SENDMESSAGE)) {
                        TranslateMessage(&msg);
                        DispatchMessageW(&msg);
                    }
                    result = WAIT_TIMEOUT;
                }
            }
        } else {
            WaitForSingleObject(g_timerThread, 2000);
        }
        CloseHandle(g_timerThread);
        g_timerThread = nullptr;
    }
    if (g_timerStopEvent) { CloseHandle(g_timerStopEvent); g_timerStopEvent = nullptr; }
    if (g_timerUpdateEvent) { CloseHandle(g_timerUpdateEvent); g_timerUpdateEvent = nullptr; }
}

static void RefreshThemeColors() {
    if (!g_refreshingMirrorTheme && !g_mirrorPlayers.empty()) {
        g_refreshingMirrorTheme = true;
        Grid originalGrid = g_playerGrid;
        RefreshThemeColors();
        for (const auto& instance : g_mirrorPlayers) {
            if (!instance || !instance->playerGrid) continue;
            g_playerGrid = instance->playerGrid;
            RefreshThemeColors();
        }
        g_playerGrid = originalGrid;
        g_refreshingMirrorTheme = false;
        return;
    }
    if (!g_playerGrid || g_unloading || g_applyingSettings) return;
    try {
        UpdateHoverBrushColors();

        auto textClr = TextColor();
        auto artistClr = ArtistColor();
        auto buttonClr = ButtonColor();

        if (auto bgFe = FindChildByName(g_playerGrid, L"FluentMedia_Background")) {
            if (auto bgBorder = bgFe.try_as<Border>()) {
                auto& bgType = g_settings.backgroundType;

                if (bgType == L"album_art_blur") {
                    if (!g_cachedThumbnailBytes.empty()) {
                        int w = (int)bgBorder.ActualWidth();
                        int h = (int)bgBorder.ActualHeight();
                        if (w > 0 && h > 0) {
                            bgBorder.Background(MakeAlbumBlurBrush(g_cachedThumbnailBytes, w, h));
                        }
                    } else {
                        auto fallbackCol = IsSystemLightTheme()
                            ? winrt::Windows::UI::Color{0xCC, 0xF3, 0xF3, 0xF3}
                            : winrt::Windows::UI::Color{0xCC, 0x20, 0x20, 0x20};
                        bgBorder.Background(MakeBrush(fallbackCol));
                    }
                    bgBorder.Visibility(Visibility::Visible);
                    bgBorder.Opacity(g_settings.blurOpacity / 100.0);
                } else if (bgType == L"solid" || bgType == L"gradient" || bgType == L"acrylic" || bgType == L"mica" || bgType == L"mica_alt") {
                    bgBorder.Background(MakeBackgroundBrush());
                    bgBorder.Visibility(Visibility::Visible);
                    bgBorder.Opacity(1.0);
                } else {
                    bgBorder.Background(nullptr);
                    bgBorder.Visibility(Visibility::Collapsed);
                }
            }
        }

        if (auto fe = FindChildByName(g_playerGrid, L"FluentMedia_OuterBorder")) {
            if (auto btn = fe.try_as<Button>()) {
                try {
                    auto normalBg = MakeBackgroundBrush();
                    ApplyFreshFluentMediaButtonStyle(btn);
                    btn.ApplyTemplate();
                    SetupPlayerCommonStates(btn, normalBg);
                    GoToCommonState(btn, IsHoverEffectEnabled(g_settings.playerHoverEffectMode), false, false);
                } catch (...) {}
            }
        }

        if (auto fe = FindChildByName(g_playerGrid, kTitleBlockName))
            if (auto tb = fe.try_as<TextBlock>()) tb.Foreground(MakeBrush(textClr));

        if (auto fe = FindChildByName(g_playerGrid, kArtistBlockName))
            if (auto ab = fe.try_as<TextBlock>()) ab.Foreground(MakeBrush(artistClr));

        for (const wchar_t* name : {kPrevBtnName, kPlayBtnName, kNextBtnName, kStopBtnName, kVolumeBtnName, kRewindBtnName, kForwardBtnName, kShuffleBtnName, kRepeatBtnName, kSwitchSessionsBtnName}) {
            if (auto fe = FindChildByName(g_playerGrid, name)) {
                if (auto btn = fe.try_as<Button>()) {
                    if (auto ct = btn.Content().try_as<TextBlock>()) ct.Foreground(MakeBrush(buttonClr));
                    ApplyFreshFluentMediaButtonStyle(btn);
                    btn.ApplyTemplate();
                    SetupMediaButtonCommonStates(btn);
                    try { VisualStateManager::GoToState(btn, L"Normal", false); } catch (...) {}
                }
            }
        }
    } catch (...) {}
}

struct TaskbarWindowInfo {
    HWND hWnd;
    bool primary;
    RECT monitorRect;
};

static std::vector<TaskbarWindowInfo> EnumerateTaskbarWindows() {
    std::vector<TaskbarWindowInfo> windows;
    EnumWindows([](HWND hWnd, LPARAM lp) CALLBACK -> BOOL {
        DWORD pid = 0;
        wchar_t cls[64] = {};
        if (!GetWindowThreadProcessId(hWnd, &pid) ||
            pid != GetCurrentProcessId() ||
            !GetClassNameW(hWnd, cls, ARRAYSIZE(cls))) {
            return TRUE;
        }

        bool primary = _wcsicmp(cls, L"Shell_TrayWnd") == 0;
        bool secondary = _wcsicmp(cls, L"Shell_SecondaryTrayWnd") == 0;
        if (!primary && !secondary) return TRUE;

        MONITORINFO monitorInfo{sizeof(monitorInfo)};
        RECT monitorRect{};
        if (HMONITOR monitor = MonitorFromWindow(hWnd, MONITOR_DEFAULTTONEAREST)) {
            if (GetMonitorInfoW(monitor, &monitorInfo)) {
                monitorRect = monitorInfo.rcMonitor;
            }
        }

        reinterpret_cast<std::vector<TaskbarWindowInfo>*>(lp)->push_back(
            {hWnd, primary, monitorRect});
        return TRUE;
    }, reinterpret_cast<LPARAM>(&windows));

    std::sort(windows.begin(), windows.end(), [](const auto& a, const auto& b) {
        if (a.primary != b.primary) return a.primary;
        if (a.monitorRect.left != b.monitorRect.left) {
            return a.monitorRect.left < b.monitorRect.left;
        }
        if (a.monitorRect.top != b.monitorRect.top) {
            return a.monitorRect.top < b.monitorRect.top;
        }
        return reinterpret_cast<UINT_PTR>(a.hWnd) <
               reinterpret_cast<UINT_PTR>(b.hWnd);
    });

    return windows;
}

static HWND FindCurrentProcessTaskbarWnd() {
    auto windows = EnumerateTaskbarWindows();
    if (windows.empty()) return nullptr;

    int requestedTaskbar = std::max(g_settings.taskbarNumber, 1);
    if (requestedTaskbar == 1) {
        auto primary = std::find_if(windows.begin(), windows.end(),
                                    [](const auto& item) { return item.primary; });
        return primary != windows.end() ? primary->hWnd : windows.front().hWnd;
    }

    int secondaryIndex = requestedTaskbar - 2;
    for (const auto& item : windows) {
        if (!item.primary && secondaryIndex-- == 0) {
            return item.hWnd;
        }
    }

    Wh_Log(L"Requested taskbar %d was not found; falling back to the primary taskbar",
           requestedTaskbar);
    auto primary = std::find_if(windows.begin(), windows.end(),
                                [](const auto& item) { return item.primary; });
    return primary != windows.end() ? primary->hWnd : windows.front().hWnd;
}

static XamlRoot GetTaskbarXamlRoot(HWND hTaskbarWnd) {
    wchar_t cls[64] = {};
    bool isSecondary = GetClassNameW(hTaskbarWnd, cls, ARRAYSIZE(cls)) &&
                       _wcsicmp(cls, L"Shell_SecondaryTrayWnd") == 0;

    HWND hTaskSwWnd = isSecondary
        ? FindWindowExW(hTaskbarWnd, nullptr, L"WorkerW", nullptr)
        : (HWND)GetProp(hTaskbarWnd, L"TaskbandHWND");
    if (!hTaskSwWnd) return nullptr;

    void* taskBand = (void*)GetWindowLongPtrW(hTaskSwWnd, 0);
    if (!taskBand) return nullptr;

    void* expectedVftable = isSecondary
        ? CSecondaryTaskBand_ITaskListWndSite_vftable
        : CTaskBand_ITaskListWndSite_vftable;
    auto getTaskbarHost = isSecondary
        ? CSecondaryTaskBand_GetTaskbarHost_Original
        : CTaskBand_GetTaskbarHost_Original;
    if (!expectedVftable || !getTaskbarHost) return nullptr;

    void* taskBandForTaskListWndSite = taskBand;
    for (int i = 0; *(void**)taskBandForTaskListWndSite !=
                    expectedVftable;
         i++) {
        if (i == 20) return nullptr;
        taskBandForTaskListWndSite = (void**)taskBandForTaskListWndSite + 1;
    }

    void* taskbarHostSharedPtr[2]{};
    getTaskbarHost(taskBandForTaskListWndSite, taskbarHostSharedPtr);
    if (!taskbarHostSharedPtr[0]) {
        if (taskbarHostSharedPtr[1] && Std_Ref_Decref_Original)
            Std_Ref_Decref_Original(taskbarHostSharedPtr[1]);
        return nullptr;
    }

    size_t taskbarElementIUnknownOffset = 0x10;
#if defined(_M_X64) || defined(__x86_64__)
    {
        // 48:83EC 28 | sub rsp,28
        // 48:83C1 48 | add rcx,48
        const BYTE* b = (const BYTE*)TaskbarHost_FrameHeight_Original;
        if (b[0] == 0x48 && b[1] == 0x83 && b[2] == 0xEC && b[4] == 0x48 &&
            b[5] == 0x83 && b[6] == 0xC1 && b[7] <= 0x7F) {
            taskbarElementIUnknownOffset = b[7];
        } else {
            Wh_Log(L"Unsupported TaskbarHost::FrameHeight pattern (x64)");
        }
    }
#elif defined(_M_ARM64) || defined(__aarch64__)
    {
        // 7f2303d5 pacibsp
        // fd7bbfa9 stp fp, lr, [sp, #-0x10]!
        // fd030091 mov fp, sp
        // 080c41f8 ldr x8, [x0, #0x10]!
        const DWORD* p = (const DWORD*)TaskbarHost_FrameHeight_Original;
        if (p[0] == 0xD503237F && (p[1] & 0xFFC07FFF) == 0xA9807BFD &&
            p[2] == 0x910003FD && (p[3] & 0xFFF00FE0) == 0xF8400C00) {
            taskbarElementIUnknownOffset = (p[3] >> 12) & 0xFF;
        } else {
            Wh_Log(L"Unsupported TaskbarHost::FrameHeight pattern (arm64)");
        }
    }
#else
    Wh_Log(L"GetTaskbarXamlRoot: Unknown architecture, using default offset 0x10");
#endif

    auto* taskbarElementIUnknown =
        *(IUnknown**)((BYTE*)taskbarHostSharedPtr[0] +
                      taskbarElementIUnknownOffset);

    if (!taskbarElementIUnknown) {
        if (taskbarHostSharedPtr[1] && Std_Ref_Decref_Original)
            Std_Ref_Decref_Original(taskbarHostSharedPtr[1]);
        return nullptr;
    }

    FrameworkElement taskbarElement{nullptr};
    HRESULT queryResult = taskbarElementIUnknown->QueryInterface(
        winrt::guid_of<FrameworkElement>(), winrt::put_abi(taskbarElement));
    auto result = taskbarElement ? taskbarElement.XamlRoot() : nullptr;

    if (taskbarHostSharedPtr[1] && Std_Ref_Decref_Original)
        Std_Ref_Decref_Original(taskbarHostSharedPtr[1]);
    return SUCCEEDED(queryResult) ? result : nullptr;
}

static FrameworkElement FindDescendantByRuntimeClass(
    FrameworkElement const& root, std::wstring_view className,
    int depth = 48) {
    if (!root || depth < 0) return nullptr;
    try {
        if (winrt::get_class_name(root) == className) return root;
        int childCount = VisualTreeHelper::GetChildrenCount(root);
        for (int i = 0; i < childCount; ++i) {
            auto child = VisualTreeHelper::GetChild(root, i)
                             .try_as<FrameworkElement>();
            if (!child) continue;
            auto match = FindDescendantByRuntimeClass(
                child, className, depth - 1);
            if (match) return match;
        }
    } catch (...) {}
    return nullptr;
}

static bool ApplyTaskbarTransparencyToWindow(HWND taskbarWindow,
                                              bool transparent) {
    try {
        auto xamlRoot = GetTaskbarXamlRoot(taskbarWindow);
        auto root = xamlRoot
            ? xamlRoot.Content().try_as<FrameworkElement>()
            : nullptr;
        if (!root) return false;

        auto taskbarFrame = FindDescendantByRuntimeClass(
            root, L"Taskbar.TaskbarFrame");
        if (!taskbarFrame) taskbarFrame = root;

        auto taskbarBackground = FindDescendantByRuntimeClass(
            taskbarFrame, L"Taskbar.TaskbarBackground");
        if (taskbarBackground &&
            taskbarBackground.Name() != L"HoverFlyoutBackgroundControl") {
            taskbarBackground.Opacity(transparent ? 0.0 : 1.0);
            Wh_Log(L"Taskbar transparency: %ls on %p",
                   transparent ? L"enabled" : L"restored", taskbarWindow);
            return true;
        }

        // Fallback for taskbar builds where the background control's runtime
        // class changed but the established XAML element names stayed intact.
        bool changed = false;
        for (const wchar_t* name : {L"BackgroundFill", L"BackgroundStroke"}) {
            if (auto element = FindChildByName(taskbarFrame, name)) {
                element.Opacity(transparent ? 0.0 : 1.0);
                changed = true;
            }
        }
        if (changed) {
            Wh_Log(L"Taskbar transparency: %ls via named background elements on %p",
                   transparent ? L"enabled" : L"restored", taskbarWindow);
        }
        return changed;
    } catch (...) {
        Wh_Log(L"Taskbar transparency: failed on %p", taskbarWindow);
        return false;
    }
}

static void ApplyTaskbarTransparencyToAll() {
    const bool transparent = g_settings.transparentTaskbar;
    for (const auto& taskbar : EnumerateTaskbarWindows()) {
        struct TransparencyWork {
            HWND window;
            bool transparent;
        } work{taskbar.hWnd, transparent};

        RunFromWindowThread(taskbar.hWnd, [](void* param) {
            auto* workItem = static_cast<TransparencyWork*>(param);
            ApplyTaskbarTransparencyToWindow(
                workItem->window, workItem->transparent);
        }, &work);
    }
}

static const wchar_t* GetGlyph(int cmd, bool isPlaying = false) {
    bool isFluent = (g_settings.iconStyle == L"fluent_outline" || g_settings.iconStyle == L"fluent_filled");
    bool isFilled = (g_settings.iconStyle == L"fluent_filled" || g_settings.iconStyle == L"mdl2_filled");

    switch (cmd) {
        case 1:
            if (isFilled) return L"\uF8AC";
            return L"\uE892";
        case 2:
            if (isPlaying) {
                if (isFluent && isFilled) return L"\uE62E";
                if (!isFluent && isFilled) return L"\uF8AE";
                return L"\uE769";
            } else {
                if (isFilled) return L"\uF5B0";
                return L"\uE768";
            }
        case 3:
            if (isFilled) return L"\uF8AD";
            return L"\uE893";
        case 4:
            return L"\uE71A";
        case 5:
            if (isFilled) return L"\uE627";
            return L"\uEB9E";
        case 6:
            if (isFilled) return L"\uE628";
            return L"\uEB9D";
        case 7:
            return L"\uE8B1";
        case 8: {
            RepeatMode mode = g_repeatMode.load();
            switch (mode) {
                case RepeatMode::Off: return L"\uF5E7";
                case RepeatMode::All: return L"\uE8EE";
                case RepeatMode::One: return L"\uE8ED";
            }
        }
        case 9:
            return L"\uE974";
        case 10: return L"\uF5E7";
        case 11: return L"\uE8EE";
        case 12: return L"\uE8ED";
        case 13: return L"\uE767";
    }
    return L"";
}

static TextBlock MakeIconText(const wchar_t* glyph, double sz, winrt::Windows::UI::Color c) {
    TextBlock t;
    t.Text(glyph);
    t.FontSize(sz);
    t.Foreground(MakeBrush(c));
    t.VerticalAlignment(VerticalAlignment::Center);
    t.HorizontalAlignment(HorizontalAlignment::Center);

    bool useFluent = (g_settings.iconStyle == L"fluent_outline" || g_settings.iconStyle == L"fluent_filled");

    try {
        if (useFluent) {
            t.FontFamily(FontFamily(L"Segoe Fluent Icons"));
        } else {
            t.FontFamily(FontFamily(L"Segoe MDL2 Assets"));
        }
    } catch (...) {
        try {
            t.FontFamily(FontFamily(L"Segoe MDL2 Assets"));
        } catch (...) {
            try {
                t.FontFamily(FontFamily(L"Segoe UI Symbol"));
            } catch (...) {}
        }
    }
    return t;
}

static Button MakeControlButton(int cmd, bool isPlaying, winrt::Windows::UI::Color iconColor) {
    Button btn;
    try {

        if (!((cmd >= 1 && cmd <= 9) || cmd == 13)) {
            Wh_Log(L"MakeControlButton: Invalid command %d, defaulting to 2 (play/pause)", cmd);
            cmd = 2;
        }

        btn.Width((double)g_settings.buttonSize);
        btn.Height((double)g_settings.buttonSize);
        btn.Padding({1,1,1,1});
        btn.CornerRadius({
            g_settings.buttonCornerRadiusTL,
            g_settings.buttonCornerRadiusTR,
            g_settings.buttonCornerRadiusBR,
            g_settings.buttonCornerRadiusBL
        });
        btn.BorderThickness({0,0,0,0});
        btn.VerticalAlignment(VerticalAlignment::Center);
        btn.HorizontalAlignment(HorizontalAlignment::Center);

        const wchar_t* glyph = GetGlyph(cmd, isPlaying);

        double opacity = 1.0;
        if (cmd == 7 && !g_shuffleEnabled.load()) {
            opacity = 0.4;
        }

        auto iconText = MakeIconText(glyph, (double)g_settings.buttonIconSize, iconColor);
        iconText.Opacity(opacity);
        btn.Content(winrt::box_value(iconText));

        btn.Click([cmd](auto const& sender, auto const&) {
            if (!g_unloading) {
                try {
                    if (cmd == 13) {
                        ShowAppVolumeFlyout(sender.template try_as<FrameworkElement>());
                    } else {
                        SendMediaCommandAsync(cmd);
                        DispatchMediaUpdate();
                    }
                } catch (...) {
                    Wh_Log(L"MakeControlButton: Exception in Click handler for cmd %d", cmd);
                }
            }
        });

        if (cmd == 13) {
            btn.PointerWheelChanged([](auto const&, PointerRoutedEventArgs const& e) {
                if (g_unloading) return;
                int delta = e.GetCurrentPoint(nullptr).Properties().MouseWheelDelta();
                AdjustCurrentMediaAppVolumeAsync(delta);
                e.Handled(true);
            });
        }

        ApplyFluentMediaButtonStyle(btn);

        auto isPressed = std::make_shared<bool>(false);
        auto isHovered = std::make_shared<bool>(false);

        auto updateBtnVisualState = [btn, isPressed, isHovered]() {
            try {
                GoToCommonState(btn, IsHoverEffectEnabled(g_settings.mediaButtonsHoverEffectMode), *isPressed, *isHovered);
            } catch (...) {

            }
        };

        RunWhenButtonReady(btn, [btn, updateBtnVisualState]() {
            try {
                SetupMediaButtonCommonStates(btn);
                updateBtnVisualState();
            } catch (...) {
                Wh_Log(L"MakeControlButton: Exception in RunWhenButtonReady");
            }
        });

        btn.PointerEntered([isHovered, updateBtnVisualState](auto const&, auto const&) {
            *isHovered = true;
            updateBtnVisualState();
        });

        btn.PointerExited([isHovered, updateBtnVisualState](auto const&, auto const&) {
            *isHovered = false;
            updateBtnVisualState();
        });

        btn.PointerPressed([isPressed, updateBtnVisualState](auto const& sender, winrt::Windows::UI::Xaml::Input::PointerRoutedEventArgs const& e) {
            if (auto elem = sender.template try_as<UIElement>()) {
                elem.CapturePointer(e.Pointer());
            }
            *isPressed = true;
            updateBtnVisualState();
        });

        btn.PointerReleased([isPressed, isHovered, updateBtnVisualState](auto const& sender, winrt::Windows::UI::Xaml::Input::PointerRoutedEventArgs const& e) {
            bool actuallyHovered = false;

            if (auto elem = sender.template try_as<UIElement>()) {
                elem.ReleasePointerCapture(e.Pointer());
                try {
                    auto bounds = elem.RenderSize();
                    auto pos = e.GetCurrentPoint(elem).Position();
                    actuallyHovered = (pos.X >= 0 && pos.X <= bounds.Width && pos.Y >= 0 && pos.Y <= bounds.Height);
                } catch (...) {}
            }
            *isPressed = false;
            *isHovered = actuallyHovered;
            updateBtnVisualState();

            e.Handled(true);
        });

        btn.PointerCanceled([isPressed, isHovered, updateBtnVisualState](auto const&, auto const&) {
            *isPressed = false;
            *isHovered = false;
            updateBtnVisualState();
        });

        btn.PointerCaptureLost([isPressed, isHovered, updateBtnVisualState](auto const& sender, winrt::Windows::UI::Xaml::Input::PointerRoutedEventArgs const& e) {
            *isPressed = false;
            if (auto elem = sender.template try_as<UIElement>()) {
                try {
                    auto bounds = elem.RenderSize();
                    auto pos = e.GetCurrentPoint(elem).Position();
                    *isHovered = (pos.X >= 0 && pos.X <= bounds.Width && pos.Y >= 0 && pos.Y <= bounds.Height);
                } catch (...) { *isHovered = false; }
            }
            updateBtnVisualState();
        });

    } catch (...) {}
    return btn;
}

static void AddLayoutAnchorOverlay(Grid const& target, const wchar_t* name, winrt::Windows::UI::Color color) {
    if (!target || !g_settings.showLayoutAnchors) return;
    try {
        Grid overlay;
        overlay.Name(name);
        overlay.IsHitTestVisible(false);
        overlay.HorizontalAlignment(HorizontalAlignment::Stretch);
        overlay.VerticalAlignment(VerticalAlignment::Stretch);

        winrt::Windows::UI::Xaml::Shapes::Rectangle vLine;
        vLine.Width(1);
        vLine.Fill(MakeBrush(color));
        vLine.HorizontalAlignment(HorizontalAlignment::Center);
        vLine.VerticalAlignment(VerticalAlignment::Stretch);

        winrt::Windows::UI::Xaml::Shapes::Rectangle hLine;
        hLine.Height(1);
        hLine.Fill(MakeBrush(color));
        hLine.HorizontalAlignment(HorizontalAlignment::Stretch);
        hLine.VerticalAlignment(VerticalAlignment::Center);

        Border outline;
        outline.BorderBrush(MakeBrush(color));
        outline.BorderThickness({1,1,1,1});
        outline.HorizontalAlignment(HorizontalAlignment::Stretch);
        outline.VerticalAlignment(VerticalAlignment::Stretch);

        overlay.Children().Append(outline);
        overlay.Children().Append(vLine);
        overlay.Children().Append(hLine);
        Canvas::SetZIndex(overlay, 5000);
        target.Children().Append(overlay);
    } catch (...) {}
}

static MenuFlyoutItem MakeActionContextMenuItem(const wchar_t* glyph, const wchar_t* label,
                                                 std::function<void()> onClick) {
    MenuFlyoutItem item;
    item.Text(label);
    item.IsEnabled(true);

    try {
        FontIcon icon;
        icon.Glyph(glyph);
        icon.FontSize((double)g_settings.buttonIconSize);
        bool useFluent = (ContextMenuIconStyle() == L"fluent_outline" || ContextMenuIconStyle() == L"fluent_filled");
        try {
            icon.FontFamily(FontFamily(useFluent ? L"Segoe Fluent Icons" : L"Segoe MDL2 Assets"));
        } catch (...) {
            try {
                icon.FontFamily(FontFamily(L"Segoe MDL2 Assets"));
            } catch (...) {}
        }
        icon.Foreground(MakeBrush(ContextMenuIconColor()));
        icon.Opacity(1.0);
        item.Icon(icon);
    } catch (...) {}

    item.Click([onClick](winrt::Windows::Foundation::IInspectable const&, RoutedEventArgs const&) {
        if (g_unloading) return;
        try {
            onClick();
        } catch (...) {}
    });

    return item;
}

static void QueueQuickSettingsRebuild() {
    if (g_unloading) return;
    try {
        auto coreWindow = winrt::Windows::UI::Core::CoreWindow::GetForCurrentThread();
        if (!coreWindow) {
            ApplySettings();
            return;
        }
        coreWindow.Dispatcher().RunAsync(
            winrt::Windows::UI::Core::CoreDispatcherPriority::Normal,
            []() {
                if (g_unloading) return;
                ApplySettings();
                g_needsUiUpdate = true;
            });
    } catch (...) {
        ApplySettings();
    }
}

static void QueueQuickMonitorRebuild() {
    if (g_unloading) return;
    try {
        auto coreWindow = winrt::Windows::UI::Core::CoreWindow::GetForCurrentThread();
        if (!coreWindow) return;
        coreWindow.Dispatcher().RunAsync(
            winrt::Windows::UI::Core::CoreDispatcherPriority::Normal,
            []() {
                if (g_unloading) return;
                try { RemovePlayerGrid(); } catch (...) {}
                HWND requestedTaskbar = FindCurrentProcessTaskbarWnd();
                if (!requestedTaskbar) return;
                g_taskbarWnd = requestedTaskbar;
                RunFromWindowThread(requestedTaskbar, [](void*) {
                    if (g_unloading) return;
                    InjectPlayerGrid();
                    UpdateVisibility();
                    g_needsUiUpdate = true;
                }, nullptr);
            });
    } catch (...) {}
}

static void OpenWindhawk() {
    std::thread([]() {
        wchar_t expanded[MAX_PATH]{};
        ExpandEnvironmentStringsW(L"%ProgramFiles%\\Windhawk\\windhawk.exe", expanded, MAX_PATH);

        DWORD attrs = GetFileAttributesW(expanded);
        if (attrs != INVALID_FILE_ATTRIBUTES && !(attrs & FILE_ATTRIBUTE_DIRECTORY)) {
            ShellExecuteW(nullptr, L"open", expanded, nullptr, nullptr, SW_SHOWNORMAL);
        } else {
            ShellExecuteW(nullptr, L"open", L"windhawk.exe", nullptr, nullptr, SW_SHOWNORMAL);
        }
    }).detach();
}

static void ShowMediaContextMenu(FrameworkElement const& target) {
    if (!target || g_unloading) return;

    try {
        MenuFlyout menu;
        try {
            menu.Placement(Controls::Primitives::FlyoutPlacementMode::Top);
        } catch (...) {}

        const bool transparent = g_settings.backgroundType == L"none";
        std::wstring transparentLabel = transparent
            ? L"\u2713 Transparent media widget"
            : L"Transparent media widget";
        menu.Items().Append(MakeActionContextMenuItem(
            L"\uE790", transparentLabel.c_str(), [transparent]() {
                g_settings.backgroundType = transparent ? L"acrylic" : L"none";
                Wh_SetIntValue(L"quickBackground", transparent ? 1 : 0);
                QueueQuickSettingsRebuild();
            }));

        const bool taskbarTransparent = g_settings.transparentTaskbar;
        std::wstring taskbarTransparentLabel = taskbarTransparent
            ? L"\u2713 Transparent taskbar"
            : L"Transparent taskbar";
        menu.Items().Append(MakeActionContextMenuItem(
            L"\uE7F4", taskbarTransparentLabel.c_str(),
            [taskbarTransparent]() {
                g_settings.transparentTaskbar = !taskbarTransparent;
                Wh_SetIntValue(
                    L"quickTransparentTaskbar", taskbarTransparent ? 0 : 1);
                ApplyTaskbarTransparencyToAll();
            }));

        MenuFlyoutSubItem positionMenu;
        positionMenu.Text(L"Position");
        try {
            FontIcon icon;
            icon.Glyph(L"\uE8AB");
            icon.FontFamily(FontFamily(L"Segoe MDL2 Assets"));
            positionMenu.Icon(icon);
        } catch (...) {}

        auto appendPosition = [&](const wchar_t* label, const wchar_t* preset,
                                  int persistedValue) {
            std::wstring itemLabel = g_settings.positionPreset == preset
                ? std::wstring(L"\u2713 ") + label
                : std::wstring(label);
            positionMenu.Items().Append(MakeActionContextMenuItem(
                L"\uE7C9", itemLabel.c_str(),
                [preset = std::wstring(preset), persistedValue]() {
                    g_settings.positionPreset = preset;
                    if (preset == L"apps") {
                        g_settings.position = L"taskbar_after_apps";
                    } else if (preset == L"left") {
                        g_settings.position = L"taskbar_left_start";
                    } else if (preset == L"middle") {
                        g_settings.position = L"taskbar_center_edge";
                    } else if (preset == L"right") {
                        g_settings.position = L"tray_left";
                    }
                    Wh_SetIntValue(L"quickPositionPreset", persistedValue);
                    QueueQuickSettingsRebuild();
                }));
        };

        appendPosition(L"After applications", L"apps", 0);
        appendPosition(L"Left of Start", L"left", 1);
        appendPosition(L"Middle", L"middle", 2);
        appendPosition(L"Before system tray", L"right", 3);

        std::wstring customLabel = g_settings.positionPreset == L"custom"
            ? L"\u2713 Custom position and offset..."
            : L"Custom position and offset...";
        positionMenu.Items().Append(MakeActionContextMenuItem(
            L"\uE713", customLabel.c_str(), []() {
                g_settings.positionPreset = L"custom";
                Wh_SetIntValue(L"quickPositionPreset", 4);
                QueueQuickSettingsRebuild();
                OpenWindhawk();
            }));
        menu.Items().Append(positionMenu);

        MenuFlyoutSubItem monitorMenu;
        monitorMenu.Text(L"Monitor");
        try {
            FontIcon icon;
            icon.Glyph(L"\uE7F4");
            icon.FontFamily(FontFamily(L"Segoe MDL2 Assets"));
            monitorMenu.Icon(icon);
        } catch (...) {}

        const bool allMonitors = g_settings.taskbarMode == L"all";
        std::wstring allLabel = allMonitors
            ? L"\u2713 All monitors"
            : L"All monitors";
        monitorMenu.Items().Append(MakeActionContextMenuItem(
            L"\uE8B9", allLabel.c_str(), []() {
                g_settings.taskbarMode = L"all";
                Wh_SetIntValue(L"quickTaskbarMode", 1);
                QueueQuickMonitorRebuild();
            }));

        int secondaryNumber = 2;
        for (const auto& taskbar : EnumerateTaskbarWindows()) {
            int monitorNumber = taskbar.primary ? 1 : secondaryNumber++;
            std::wstring label = L"Monitor " + std::to_wstring(monitorNumber);
            if (taskbar.primary) label += L" (Primary)";
            if (!allMonitors && g_settings.taskbarNumber == monitorNumber) {
                label = std::wstring(L"\u2713 ") + label;
            }

            monitorMenu.Items().Append(MakeActionContextMenuItem(
                L"\uE7F4", label.c_str(), [monitorNumber]() {
                    g_settings.taskbarMode = L"selected";
                    g_settings.taskbarNumber = monitorNumber;
                    Wh_SetIntValue(L"quickTaskbarMode", 0);
                    Wh_SetIntValue(L"quickTaskbarNumber", monitorNumber);
                    QueueQuickMonitorRebuild();
                }));
        }
        menu.Items().Append(monitorMenu);

        try {
            Controls::MenuFlyoutSeparator separator;
            menu.Items().Append(separator);
        } catch (...) {}

        menu.Items().Append(MakeActionContextMenuItem(
            L"\uE713", L"Open full Windhawk settings", []() {
                OpenWindhawk();
            }));

        menu.ShowAt(target);
    } catch (...) {
        Wh_Log(L"ShowMediaContextMenu: exception");
    }
}


static Grid BuildPlayerGrid() {
    try {
        auto textClr = TextColor();
        auto artistClr = ArtistColor();
        auto buttonClr = ButtonColor();
        auto bgBrush = MakeBackgroundBrush();
        double phMin = (double)g_settings.playerMinHeight;
        double phMax = (double)g_settings.playerMaxHeight;

        bool hasTextOrButtons = g_settings.showTrackTitle || g_settings.showTrackArtist || (g_settings.showMediaButtons && !g_mediaButtons.empty());

        Border backgroundBorder;
        backgroundBorder.Name(L"FluentMedia_Background");
        backgroundBorder.CornerRadius({
            g_settings.cornerRadiusTL,
            g_settings.cornerRadiusTR,
            g_settings.cornerRadiusBR,
            g_settings.cornerRadiusBL
        });
        backgroundBorder.HorizontalAlignment(HorizontalAlignment::Stretch);
        backgroundBorder.VerticalAlignment(VerticalAlignment::Stretch);
        backgroundBorder.IsHitTestVisible(false);
        backgroundBorder.Visibility(Visibility::Collapsed);

        Button playerButton;
        playerButton.Name(L"FluentMedia_OuterBorder");
        playerButton.CornerRadius({
            g_settings.cornerRadiusTL,
            g_settings.cornerRadiusTR,
            g_settings.cornerRadiusBR,
            g_settings.cornerRadiusBL
        });
        playerButton.BorderThickness({0, 0, 0, 0});
        playerButton.UseSystemFocusVisuals(false);
        playerButton.IsHitTestVisible(false);
        playerButton.HorizontalAlignment(HorizontalAlignment::Stretch);
        playerButton.VerticalAlignment(VerticalAlignment::Stretch);
        if (phMin > 0) {
            playerButton.MinHeight(phMin);
        }
        if (phMax > 0) {
            playerButton.MaxHeight(phMax);
        }

        Grid chromeFill;
        if (phMin > 0) {
            chromeFill.MinHeight(phMin);
        }
        if (phMax > 0) {
            chromeFill.MaxHeight(phMax);
        }
        chromeFill.IsHitTestVisible(false);
        playerButton.Content(chromeFill);

        if (g_settings.showDebugBorders) {
            playerButton.BorderBrush(MakeBrush({0xFF, 0xFF, 0x00, 0x00}));
            playerButton.BorderThickness({2, 2, 2, 2});
        }

        Grid panel;
        panel.Name(kPanelGridName);
        panel.VerticalAlignment(VerticalAlignment::Center);
        panel.HorizontalAlignment(HorizontalAlignment::Stretch);
        if (hasTextOrButtons) {
            panel.Margin({4, 2, 4, 2});
        }
        AddLayoutAnchorOverlay(panel, L"FluentMedia_DebugPanelAnchors", {0xD0, 0x00, 0xFF, 0x00});

        if (g_settings.showDebugBorders) {
            Border panelDebugBorder;
            panelDebugBorder.BorderBrush(MakeBrush({0xFF, 0x00, 0xFF, 0x00}));
            panelDebugBorder.BorderThickness({1,1,1,1});
            panel.Children().Append(panelDebugBorder);
        }

        bool buttonsLeft = g_settings.mirrorLayout;
        bool albumArtLeft = !g_settings.mirrorLayout;
        bool hasText = g_settings.showTrackTitle || g_settings.showTrackArtist;

        ColumnDefinition colFirst, colText, colSpacer, colLast;
        colFirst.Width({1.0, GridUnitType::Auto});

        if (hasText) {
            colText.Width({1.0, GridUnitType::Star});
        } else {
            colText.Width({0.0, GridUnitType::Pixel});
        }

        colSpacer.Width({0.0, GridUnitType::Pixel});

        colLast.Width({1.0, GridUnitType::Auto});
        panel.ColumnDefinitions().Append(colFirst);
        panel.ColumnDefinitions().Append(colText);
        panel.ColumnDefinitions().Append(colSpacer);
        panel.ColumnDefinitions().Append(colLast);

        Grid artContainer{nullptr};

        if (g_settings.showAlbumArt) {
            int iconSz = g_settings.appIconSize;

            artContainer = Grid();
            artContainer.VerticalAlignment(VerticalAlignment::Center);
            artContainer.HorizontalAlignment(HorizontalAlignment::Center);

            if (g_settings.albumArtMinWidth > 0) {
                artContainer.MinWidth((double)g_settings.albumArtMinWidth);
            }
            if (g_settings.albumArtMaxWidth > 0) {
                artContainer.MaxWidth((double)g_settings.albumArtMaxWidth);
            }
            if (g_settings.albumArtMinHeight > 0) {
                artContainer.MinHeight((double)g_settings.albumArtMinHeight);
            }
            if (g_settings.albumArtMaxHeight > 0) {
                artContainer.MaxHeight((double)g_settings.albumArtMaxHeight);
            }

            double artLeftMargin = (double)g_settings.albumArtLeftMargin;
            double artRightMargin = (double)g_settings.albumArtRightMargin;
            artContainer.Margin({artLeftMargin, 0, artRightMargin, 0});

            artContainer.Opacity(g_settings.albumArtOpacity / 100.0);
            artContainer.Background(MakeBrush({0x00,0x00,0x00,0x00}));
            AddLayoutAnchorOverlay(artContainer, L"FluentMedia_DebugArtAnchors", {0xD0, 0xFF, 0xFF, 0x00});

            if (g_settings.showDebugBorders) {
                Border artDebugBorder;
                artDebugBorder.BorderBrush(MakeBrush({0xFF, 0xFF, 0xFF, 0x00}));
                artDebugBorder.BorderThickness({2,2,2,2});
                artContainer.Children().Append(artDebugBorder);
            }

            winrt::Windows::UI::Xaml::Shapes::Rectangle placeholder;
            placeholder.Fill(MakeBrush({0x40,0x80,0x80,0x80}));

            double maxRadius = std::max({g_settings.albumArtCornerRadiusTL, g_settings.albumArtCornerRadiusTR,
                                         g_settings.albumArtCornerRadiusBR, g_settings.albumArtCornerRadiusBL});
            placeholder.RadiusX(maxRadius);
            placeholder.RadiusY(maxRadius);
            placeholder.HorizontalAlignment(HorizontalAlignment::Stretch);
            placeholder.VerticalAlignment(VerticalAlignment::Stretch);
            artContainer.Children().Append(placeholder);

            Border artBorder;
            artBorder.CornerRadius({
                g_settings.albumArtCornerRadiusTL,
                g_settings.albumArtCornerRadiusTR,
                g_settings.albumArtCornerRadiusBR,
                g_settings.albumArtCornerRadiusBL
            });
            artBorder.HorizontalAlignment(HorizontalAlignment::Stretch);
            artBorder.VerticalAlignment(VerticalAlignment::Stretch);

            Controls::Image artImage;
            artImage.Name(kArtImageName);

            bool isSquare = (g_settings.albumArtMinWidth == g_settings.albumArtMinHeight) &&
                           (g_settings.albumArtMaxWidth == g_settings.albumArtMaxHeight);
            artImage.Stretch(isSquare ? Stretch::UniformToFill : Stretch::Uniform);

            artImage.HorizontalAlignment(HorizontalAlignment::Center);
            artImage.VerticalAlignment(VerticalAlignment::Center);

            Grid artInnerGrid;
            artInnerGrid.HorizontalAlignment(HorizontalAlignment::Stretch);
            artInnerGrid.VerticalAlignment(VerticalAlignment::Stretch);
            artInnerGrid.Children().Append(artImage);

            {

                auto clipGeo = winrt::Windows::UI::Xaml::Media::RectangleGeometry();
                artInnerGrid.Clip(clipGeo);

                artInnerGrid.SizeChanged([clipGeo](
                    winrt::Windows::Foundation::IInspectable const& sender,
                    winrt::Windows::UI::Xaml::SizeChangedEventArgs const&) mutable {
                        try {
                            if (auto fe = sender.try_as<FrameworkElement>()) {
                                clipGeo.Rect({0, 0,
                                    (float)fe.ActualWidth(),
                                    (float)fe.ActualHeight()});
                            }
                        } catch (...) {}
                    });
            }

            artBorder.Child(artInnerGrid);
            artContainer.Children().Append(artBorder);

            Border artRing;
            artRing.CornerRadius({
                g_settings.albumArtCornerRadiusTL,
                g_settings.albumArtCornerRadiusTR,
                g_settings.albumArtCornerRadiusBR,
                g_settings.albumArtCornerRadiusBL
            });
            artRing.BorderThickness({1,1,1,1});
            artRing.BorderBrush(MakeBrush({0x25,0x80,0x80,0x80}));
            artContainer.Children().Append(artRing);

            if (g_settings.showAppIcon) {
                Grid iconOverlay;
                iconOverlay.VerticalAlignment(VerticalAlignment::Stretch);
                iconOverlay.HorizontalAlignment(HorizontalAlignment::Stretch);

                Controls::Image appIconImage;
                appIconImage.Name(kAppIconImageName);
                appIconImage.Width(iconSz);
                appIconImage.Height(iconSz);
                appIconImage.Stretch(Stretch::UniformToFill);
                appIconImage.Visibility(Visibility::Collapsed);

                const auto& corner = g_settings.appIconCorner;
                double margin_right  = 0, margin_bottom = 0;
                double margin_left   = 0, margin_top    = 0;
                HorizontalAlignment ha = HorizontalAlignment::Right;
                VerticalAlignment   va = VerticalAlignment::Bottom;

                if (corner == L"top_left") {
                    ha = HorizontalAlignment::Left;
                    va = VerticalAlignment::Top;
                } else if (corner == L"top_right") {
                    ha = HorizontalAlignment::Right;
                    va = VerticalAlignment::Top;
                } else if (corner == L"bottom_left") {
                    ha = HorizontalAlignment::Left;
                    va = VerticalAlignment::Bottom;
                } else {
                    ha = HorizontalAlignment::Right;
                    va = VerticalAlignment::Bottom;
                }

                appIconImage.HorizontalAlignment(ha);
                appIconImage.VerticalAlignment(va);
                appIconImage.Margin({margin_left, margin_top, margin_right, margin_bottom});

                iconOverlay.Children().Append(appIconImage);
                Canvas::SetZIndex(iconOverlay, 15);
                artContainer.Children().Append(iconOverlay);
            }

            if (g_settings.showPauseOverlay) {
                Border pauseBorder;
                pauseBorder.Name(L"PauseIconOverlay");
                pauseBorder.HorizontalAlignment(HorizontalAlignment::Stretch);
                pauseBorder.VerticalAlignment(VerticalAlignment::Stretch);
                BYTE opacity = (BYTE)((g_settings.pauseOverlayOpacity * 255) / 100);
                pauseBorder.Background(MakeBrush({opacity, 0x00, 0x00, 0x00}));
                pauseBorder.Visibility(Visibility::Collapsed);
                Canvas::SetZIndex(pauseBorder, 8);

                TextBlock pauseIcon;
                pauseIcon.Text(L"\uE769");
                pauseIcon.FontFamily(Media::FontFamily(L"Segoe MDL2 Assets"));
                pauseIcon.FontSize((double)g_settings.pauseOverlayIconSize);
                pauseIcon.Foreground(MakeBrush({0xFF, 0xFF, 0xFF, 0xFF}));
                pauseIcon.HorizontalAlignment(HorizontalAlignment::Center);
                pauseIcon.VerticalAlignment(VerticalAlignment::Center);

                pauseBorder.Child(pauseIcon);
                artInnerGrid.Children().Append(pauseBorder);
            }

            if (g_settings.disableAlbumArtClick) {
                artContainer.IsHitTestVisible(false);
            } else {
                artContainer.PointerPressed([](auto const& sender, winrt::Windows::UI::Xaml::Input::PointerRoutedEventArgs const& e) mutable {
                    if (auto elem = sender.template try_as<UIElement>()) {
                        elem.CapturePointer(e.Pointer());
                    }
                    e.Handled(true);
                });

                artContainer.PointerReleased([](auto const& sender, winrt::Windows::UI::Xaml::Input::PointerRoutedEventArgs const& e) mutable {
                    bool actuallyHovered = false;
                    if (auto elem = sender.template try_as<UIElement>()) {
                        elem.ReleasePointerCapture(e.Pointer());
                        try {
                            auto pointerPoint = e.GetCurrentPoint(elem);
                            auto bounds = elem.RenderSize();
                            auto pos = pointerPoint.Position();
                            actuallyHovered = (pos.X >= 0 && pos.X <= bounds.Width && pos.Y >= 0 && pos.Y <= bounds.Height);
                        } catch (...) { actuallyHovered = false; }
                    }

                    if (g_unloading) return;

                    if (actuallyHovered) {
                        auto kind = e.GetCurrentPoint(nullptr).Properties().PointerUpdateKind();
                        auto fe = sender.template try_as<FrameworkElement>();
                        if (kind == winrt::Windows::UI::Input::PointerUpdateKind::LeftButtonReleased) {
                            ExecuteMediaAction(g_settings.albumArtLeftClick, fe);
                        } else if (kind == winrt::Windows::UI::Input::PointerUpdateKind::RightButtonReleased) {
                            ExecuteMediaAction(g_settings.albumArtRightClick, fe);
                        } else if (kind == winrt::Windows::UI::Input::PointerUpdateKind::MiddleButtonReleased) {
                            ExecuteMediaAction(g_settings.albumArtMiddleClick, fe);
                        }
                    }
                    e.Handled(true);
                });

                artContainer.DoubleTapped([](auto const& sender, winrt::Windows::UI::Xaml::Input::DoubleTappedRoutedEventArgs const& e) mutable {
                    if (g_unloading) return;
                    ExecuteMediaAction(g_settings.albumArtLeftDoubleClick, sender.template try_as<FrameworkElement>());
                    e.Handled(true);
                });

                artContainer.PointerWheelChanged([](winrt::Windows::Foundation::IInspectable const&, winrt::Windows::UI::Xaml::Input::PointerRoutedEventArgs const& e) {
                    if (g_unloading) return;
                    auto action = g_settings.albumArtWheelAction;
                    if (action == L"none") return;

                    auto props = e.GetCurrentPoint(nullptr).Properties();
                    int delta = props.MouseWheelDelta();

                    if (action == L"switch_tracks") {
                        if (delta > 0) SendMediaCommandAsync(1);
                        else if (delta < 0) SendMediaCommandAsync(3);
                        DispatchMediaUpdate();
                    } else if (action == L"switch_tracks_inverted") {
                        if (delta > 0) SendMediaCommandAsync(3);
                        else if (delta < 0) SendMediaCommandAsync(1);
                        DispatchMediaUpdate();
                    } else if (action == L"switch_sessions") {
                        if (delta != 0) SwitchMediaSession();
                    } else if (action == L"app_sound") {
                        AdjustCurrentMediaAppVolumeAsync(delta);
                    }
                    e.Handled(true);
                });
            }

            artContainer.Tag(winrt::box_value(winrt::hstring(L"FluentMediaArtContainer")));

            if (albumArtLeft) {
                Grid::SetColumn(artContainer, 0);
            } else {
                Grid::SetColumn(artContainer, 3);
            }
            panel.Children().Append(artContainer);
        }

        if (g_settings.showTrackTitle || g_settings.showTrackArtist) {
            Border textContainer;
            textContainer.VerticalAlignment(VerticalAlignment::Center);

            if (albumArtLeft) {
                textContainer.HorizontalAlignment(HorizontalAlignment::Left);
            } else {
                textContainer.HorizontalAlignment(HorizontalAlignment::Right);
            }

            if (g_settings.textAreaMinWidth > 0) {
                textContainer.MinWidth((double)g_settings.textAreaMinWidth);
            }

            if (g_settings.textAreaMaxWidth > 0) {
                textContainer.MaxWidth((double)g_settings.textAreaMaxWidth);
            }
            if (g_settings.textAreaMinHeight > 0) {
                textContainer.MinHeight((double)g_settings.textAreaMinHeight);
            }
            if (g_settings.textAreaMaxHeight > 0) {
                textContainer.MaxHeight((double)g_settings.textAreaMaxHeight);
            }

            double leftMargin = (double)g_settings.textAreaLeftMargin;
            double rightMargin = (double)g_settings.textAreaRightMargin;
            textContainer.Margin({leftMargin, 0, rightMargin, 0});

            if (g_settings.showDebugBorders) {
                textContainer.BorderBrush(MakeBrush({0xFF, 0x00, 0xFF, 0xFF}));
                textContainer.BorderThickness({1,1,1,1});
            }

            StackPanel textStack;
            textStack.Name(kTextStackName);
            textStack.Orientation(Orientation::Vertical);
            textStack.VerticalAlignment(VerticalAlignment::Center);

            if (g_settings.enableTitleScrolling || g_settings.enableArtistScrolling) {
                textStack.HorizontalAlignment(HorizontalAlignment::Stretch);
            } else {
                textStack.HorizontalAlignment(g_settings.mirrorLayout ? HorizontalAlignment::Right : HorizontalAlignment::Left);
            }
            textStack.Spacing((double)g_settings.textSpacing);

            if (g_settings.showTrackTitle || g_settings.showTrackArtist) {
                TextBlock titleBlock{nullptr};
                TextBlock artistBlock{nullptr};

                if (g_settings.showTrackTitle) {
                    titleBlock = TextBlock();
                    titleBlock.Name(kTitleBlockName);
                    titleBlock.FontSize((double)g_settings.titleFontSize);

                    std::wstring titleFontName = g_settings.titleFont.empty() ? g_settings.titleFontFamily : g_settings.titleFont;
                    if (!titleFontName.empty()) {
                        try {
                            titleBlock.FontFamily(Media::FontFamily(titleFontName));
                        } catch (...) {}
                    }

                    if (!g_settings.titleFontWeight.empty()) {
                        try {
                            auto fontWeight = Markup::XamlBindingHelper::ConvertValue(
                                winrt::Windows::UI::Xaml::Interop::TypeName{
                                    winrt::hstring{L"Windows.UI.Text.FontWeight"},
                                    winrt::Windows::UI::Xaml::Interop::TypeKind::Metadata
                                },
                                winrt::box_value(g_settings.titleFontWeight))
                                .as<winrt::Windows::UI::Text::FontWeight>();
                            titleBlock.FontWeight(fontWeight);
                        } catch (...) {}
                    }

                    if (!g_settings.titleFontStyle.empty()) {
                        try {
                            auto fontStyle = Markup::XamlBindingHelper::ConvertValue(
                                winrt::Windows::UI::Xaml::Interop::TypeName{
                                    winrt::hstring{L"Windows.UI.Text.FontStyle"},
                                    winrt::Windows::UI::Xaml::Interop::TypeKind::Metadata
                                },
                                winrt::box_value(g_settings.titleFontStyle))
                                .as<winrt::Windows::UI::Text::FontStyle>();
                            titleBlock.FontStyle(fontStyle);
                        } catch (...) {}
                    }

                    if (g_settings.titleCharacterSpacing != 0) {
                        titleBlock.CharacterSpacing(g_settings.titleCharacterSpacing);
                    }

                    titleBlock.Foreground(MakeBrush(textClr));
                    titleBlock.TextWrapping(TextWrapping::NoWrap);
                    titleBlock.TextTrimming(TextTrimming::CharacterEllipsis);
                    titleBlock.TextAlignment(g_settings.mirrorLayout ? TextAlignment::Right : TextAlignment::Left);
                }

                if (g_settings.showTrackArtist) {
                    artistBlock = TextBlock();
                    artistBlock.Name(kArtistBlockName);
                    artistBlock.FontSize((double)g_settings.artistFontSize);

                    std::wstring artistFontName = g_settings.artistFont.empty() ? g_settings.artistFontFamily : g_settings.artistFont;
                    if (!artistFontName.empty()) {
                        try {
                            artistBlock.FontFamily(Media::FontFamily(artistFontName));
                        } catch (...) {}
                    }

                    if (!g_settings.artistFontWeight.empty()) {
                        try {
                            auto fontWeight = Markup::XamlBindingHelper::ConvertValue(
                                winrt::Windows::UI::Xaml::Interop::TypeName{
                                    winrt::hstring{L"Windows.UI.Text.FontWeight"},
                                    winrt::Windows::UI::Xaml::Interop::TypeKind::Metadata
                                },
                                winrt::box_value(g_settings.artistFontWeight))
                                .as<winrt::Windows::UI::Text::FontWeight>();
                            artistBlock.FontWeight(fontWeight);
                        } catch (...) {}
                    }

                    if (!g_settings.artistFontStyle.empty()) {
                        try {
                            auto fontStyle = Markup::XamlBindingHelper::ConvertValue(
                                winrt::Windows::UI::Xaml::Interop::TypeName{
                                    winrt::hstring{L"Windows.UI.Text.FontStyle"},
                                    winrt::Windows::UI::Xaml::Interop::TypeKind::Metadata
                                },
                                winrt::box_value(g_settings.artistFontStyle))
                                .as<winrt::Windows::UI::Text::FontStyle>();
                            artistBlock.FontStyle(fontStyle);
                        } catch (...) {}
                    }

                    if (g_settings.artistCharacterSpacing != 0) {
                        artistBlock.CharacterSpacing(g_settings.artistCharacterSpacing);
                    }

                    artistBlock.Foreground(MakeBrush(artistClr));
                    artistBlock.TextWrapping(TextWrapping::NoWrap);
                    artistBlock.TextTrimming(TextTrimming::CharacterEllipsis);
                    artistBlock.TextAlignment(g_settings.mirrorLayout ? TextAlignment::Right : TextAlignment::Left);
                }

                auto MakeScrollView = [&](Canvas& scrollView, TextBlock& block, const wchar_t* viewName, const wchar_t* blockName, const wchar_t* cloneName) {
                    scrollView = Canvas();
                    scrollView.Name(viewName);
                    scrollView.VerticalAlignment(VerticalAlignment::Center);
                    scrollView.HorizontalAlignment(g_settings.mirrorLayout ? HorizontalAlignment::Right : HorizontalAlignment::Left);

                    scrollView.Width(100.0);
                    block.Name(blockName);
                    block.TextTrimming(TextTrimming::None);
                    block.TextWrapping(TextWrapping::NoWrap);
                    Canvas::SetLeft(block, 0.0);
                    Canvas::SetTop(block, 0.0);
                    scrollView.Children().Append(block);

                    auto geo = winrt::Windows::UI::Xaml::Media::RectangleGeometry();
                    scrollView.Clip(geo);
                    block.SizeChanged([scrollView, geo](winrt::Windows::Foundation::IInspectable const&, SizeChangedEventArgs const& e) mutable {
                        try {
                            double h = e.NewSize().Height;
                            if (h < 1.0) h = 16.0;
                            double w = scrollView.Width();
                            scrollView.Height(h);
                            geo.Rect({0, 0, (float)w, (float)h});
                        } catch (...) {}
                    });
                };


                if (g_settings.swapTitleArtist) {
                    if (artistBlock) {
                        if (g_settings.enableArtistScrolling) {
                            Canvas artistScrollView;
                            MakeScrollView(artistScrollView, artistBlock, kArtistScrollViewName, kArtistBlockName, kArtistCloneName);
                            textStack.Children().Append(artistScrollView);
                        } else {
                            if (g_settings.textAreaMaxWidth > 0) {
                                artistBlock.MaxWidth((double)g_settings.textAreaMaxWidth);
                            }
                            textStack.Children().Append(artistBlock);
                        }
                    }
                    if (titleBlock) {
                        if (g_settings.enableTitleScrolling) {
                            Canvas titleScrollView;
                            MakeScrollView(titleScrollView, titleBlock, kTitleScrollViewName, kTitleBlockName, kTitleCloneName);
                            textStack.Children().Append(titleScrollView);
                        } else {
                            if (g_settings.textAreaMaxWidth > 0) {
                                titleBlock.MaxWidth((double)g_settings.textAreaMaxWidth);
                            }
                            textStack.Children().Append(titleBlock);
                        }
                    }
                } else {
                    if (titleBlock) {
                        if (g_settings.enableTitleScrolling) {
                            Canvas titleScrollView;
                            MakeScrollView(titleScrollView, titleBlock, kTitleScrollViewName, kTitleBlockName, kTitleCloneName);
                            textStack.Children().Append(titleScrollView);
                        } else {
                            if (g_settings.textAreaMaxWidth > 0) {
                                titleBlock.MaxWidth((double)g_settings.textAreaMaxWidth);
                            }
                            textStack.Children().Append(titleBlock);
                        }
                    }
                    if (artistBlock) {
                        if (g_settings.enableArtistScrolling) {
                            Canvas artistScrollView;
                            MakeScrollView(artistScrollView, artistBlock, kArtistScrollViewName, kArtistBlockName, kArtistCloneName);
                            textStack.Children().Append(artistScrollView);
                        } else {
                            if (g_settings.textAreaMaxWidth > 0) {
                                artistBlock.MaxWidth((double)g_settings.textAreaMaxWidth);
                            }
                            textStack.Children().Append(artistBlock);
                        }
                    }
                }
            }

            textContainer.Child(textStack);

            Grid::SetColumn(textContainer, 1);
            panel.Children().Append(textContainer);
        }

        if (g_settings.showMediaButtons) {
            StackPanel ctrlPanel;
            ctrlPanel.Orientation(Orientation::Horizontal);
            ctrlPanel.Spacing((double)g_settings.buttonSpacing);
            ctrlPanel.VerticalAlignment(VerticalAlignment::Center);
            ctrlPanel.HorizontalAlignment(buttonsLeft ? HorizontalAlignment::Left : HorizontalAlignment::Right);

            std::vector<MediaButtonConfig> currentButtons;
            try {
                std::lock_guard<std::mutex> lock(g_mediaButtonsMutex);
                if (!g_mediaButtons.empty()) {
                    currentButtons = g_mediaButtons;
                } else {
                    Wh_Log(L"CreatePlayerGrid: Media buttons vector is empty, using defaults");
                    currentButtons = {
                        {MediaButtonType::Shuffle, 7},
                        {MediaButtonType::Repeat, 8},
                        {MediaButtonType::Previous, 1},
                        {MediaButtonType::PlayPause, 2},
                        {MediaButtonType::Next, 3},
                        {MediaButtonType::Volume, 13}
                    };
                }
            } catch (const std::exception& e) {
                Wh_Log(L"CreatePlayerGrid: Exception accessing media buttons (std::exception), using defaults");
                currentButtons = {
                    {MediaButtonType::Shuffle, 7},
                    {MediaButtonType::Repeat, 8},
                    {MediaButtonType::Previous, 1},
                    {MediaButtonType::PlayPause, 2},
                    {MediaButtonType::Next, 3},
                    {MediaButtonType::Volume, 13}
                };
            } catch (...) {
                Wh_Log(L"CreatePlayerGrid: Unknown exception accessing media buttons, using defaults");
                currentButtons = {
                    {MediaButtonType::Shuffle, 7},
                    {MediaButtonType::Repeat, 8},
                    {MediaButtonType::Previous, 1},
                    {MediaButtonType::PlayPause, 2},
                    {MediaButtonType::Next, 3},
                    {MediaButtonType::Volume, 13}
                };
            }

            bool hasButtons = !currentButtons.empty();
            if (hasButtons) {
                try {
                    ctrlPanel.Margin({(double)g_settings.mediaButtonsLeftMargin, 0, (double)g_settings.mediaButtonsRightMargin, 0});
                } catch (...) {
                    Wh_Log(L"CreatePlayerGrid: Exception setting control panel margin");
                }
            }

            if (g_settings.showDebugBorders) {
                try {
                    Border ctrlDebugBorder;
                    ctrlDebugBorder.BorderBrush(MakeBrush({0xFF, 0xFF, 0x00, 0xFF}));
                    ctrlDebugBorder.BorderThickness({1,1,1,1});
                    Grid::SetColumn(ctrlDebugBorder, buttonsLeft ? 0 : 3);
                    panel.Children().Append(ctrlDebugBorder);
                } catch (...) {
                    Wh_Log(L"CreatePlayerGrid: Exception creating debug border");
                }
            }

            for (size_t i = 0; i < currentButtons.size(); i++) {
                try {
                    const auto& btnCfg = currentButtons[i];
                    auto btn = MakeControlButton(btnCfg.cmd, false, buttonClr);
                    if (!btn) {
                        Wh_Log(L"CreatePlayerGrid: MakeControlButton returned null for button %zu", i);
                        continue;
                    }

                    switch (btnCfg.type) {
                        case MediaButtonType::Previous:
                            btn.Name(kPrevBtnName);
                            break;
                        case MediaButtonType::PlayPause:
                            btn.Name(kPlayBtnName);
                            break;
                        case MediaButtonType::Next:
                            btn.Name(kNextBtnName);
                            break;
                        case MediaButtonType::Stop:
                            btn.Name(kStopBtnName);
                            break;
                        case MediaButtonType::Rewind5s:
                            btn.Name(kRewindBtnName);
                            break;
                        case MediaButtonType::Forward5s:
                            btn.Name(kForwardBtnName);
                            break;
                        case MediaButtonType::Shuffle:
                            btn.Name(kShuffleBtnName);
                            break;
                        case MediaButtonType::Repeat:
                            btn.Name(kRepeatBtnName);
                            break;
                        case MediaButtonType::SwitchSessions:
                            btn.Name(kSwitchSessionsBtnName);
                            break;
                        case MediaButtonType::Volume:
                            btn.Name(kVolumeBtnName);
                            break;
                        default:
                            Wh_Log(L"CreatePlayerGrid: Unknown button type %d", static_cast<int>(btnCfg.type));
                            continue;
                    }

                    ctrlPanel.Children().Append(btn);
                } catch (const winrt::hresult_error& e) {
                    Wh_Log(L"CreatePlayerGrid: WinRT exception creating button %zu: 0x%08X", i, static_cast<uint32_t>(e.code()));
                } catch (const std::exception& e) {
                    Wh_Log(L"CreatePlayerGrid: std::exception creating button %zu", i);
                } catch (...) {
                    Wh_Log(L"CreatePlayerGrid: Unknown exception creating button %zu, skipping", i);
                }
            }

            if (buttonsLeft) {
                Grid::SetColumn(ctrlPanel, 0);
            } else {
                Grid::SetColumn(ctrlPanel, 3);
            }

            if (hasButtons) {
                panel.Children().Append(ctrlPanel);
            }
        }

        Grid wrapper;
        wrapper.Name(kGridName);
        wrapper.VerticalAlignment(VerticalAlignment::Stretch);
        wrapper.HorizontalAlignment(HorizontalAlignment::Left);
        AddLayoutAnchorOverlay(wrapper, L"FluentMedia_DebugPlayerAnchors", {0xD0, 0xFF, 0x50, 0x50});

        try {
            if (g_settings.enableSmoothPositionAnimation) {
                TransitionCollection transitions;
                RepositionThemeTransition marginTransition;
                transitions.Append(marginTransition);
                wrapper.Transitions(transitions);
            }
        } catch (...) {}

        if (hasTextOrButtons && g_settings.playerMinWidth > 0) {
            wrapper.MinWidth((double)g_settings.playerMinWidth);
        }

        if (g_settings.playerMaxWidth > 0) {
            wrapper.MaxWidth((double)g_settings.playerMaxWidth);
        }

        if (g_settings.playerMinHeight > 0) {
            wrapper.MinHeight((double)g_settings.playerMinHeight);
        }

        if (g_settings.playerMaxHeight > 0) {
            wrapper.MaxHeight((double)g_settings.playerMaxHeight);
        }

        wrapper.Background(MakeBrush({0x00, 0, 0, 0}));

        Canvas::SetZIndex(backgroundBorder, 0);
        Canvas::SetZIndex(playerButton, 1);
        Canvas::SetZIndex(panel, 2);

        wrapper.Children().Append(backgroundBorder);
        wrapper.Children().Append(playerButton);
        wrapper.Children().Append(panel);

        ApplyFluentMediaButtonStyle(playerButton);
        if (!g_settings.showDebugBorders) {
            playerButton.BorderThickness({1, 1, 1, 1});
        }

        auto isPressed = std::make_shared<bool>(false);
        auto isHovered = std::make_shared<bool>(false);

        Brush playerNormalBg = MakeBackgroundBrush();

        auto updatePlayerVisualState = [playerButton, playerNormalBg, isPressed, isHovered]() {
            ApplyPlayerButtonState(playerButton, playerNormalBg, *isHovered, *isPressed);
        };

        RunWhenButtonReady(playerButton, [playerButton, playerNormalBg]() {
            try {
                SetupPlayerCommonStates(playerButton, playerNormalBg);
                GoToCommonState(playerButton, IsHoverEffectEnabled(g_settings.playerHoverEffectMode), false, false);
            } catch (...) {}
        });

        wrapper.Loaded([playerButton, playerNormalBg](auto const&, auto const&) {
            try {
                SetupPlayerCommonStates(playerButton, playerNormalBg);
                GoToCommonState(playerButton, IsHoverEffectEnabled(g_settings.playerHoverEffectMode), false, false);
            } catch (...) {}
        });

        panel.PointerEntered([isHovered, updatePlayerVisualState](auto const&, auto const&) {
            *isHovered = true;
            updatePlayerVisualState();
        });

        panel.PointerExited([wrapper, isHovered, updatePlayerVisualState](auto const&, PointerRoutedEventArgs const& e) {
            bool stillInside = false;
            try {
                auto pos = e.GetCurrentPoint(wrapper).Position();
                auto bounds = wrapper.RenderSize();
                stillInside = pos.X >= 0 && pos.X <= bounds.Width && pos.Y >= 0 && pos.Y <= bounds.Height;
            } catch (...) {}
            if (!stillInside) {
                *isHovered = false;
                updatePlayerVisualState();
            }
        });

        wrapper.PointerEntered([isHovered, updatePlayerVisualState](auto const&, auto const&) mutable {
            *isHovered = true;
            updatePlayerVisualState();
        });

        wrapper.PointerExited([isHovered, updatePlayerVisualState](auto const&, auto const&) mutable {
            *isHovered = false;
            updatePlayerVisualState();
        });

        wrapper.PointerPressed([isPressed, updatePlayerVisualState](auto const& sender, winrt::Windows::UI::Xaml::Input::PointerRoutedEventArgs const& e) mutable {
            if (auto elem = sender.template try_as<UIElement>()) {
                elem.CapturePointer(e.Pointer());
            }
            *isPressed = true;
            updatePlayerVisualState();
        });

        wrapper.PointerReleased([isPressed, isHovered, updatePlayerVisualState](auto const& sender, winrt::Windows::UI::Xaml::Input::PointerRoutedEventArgs const& e) mutable {
            *isPressed = false;
            bool actuallyHovered = false;
            if (auto elem = sender.template try_as<UIElement>()) {
                elem.ReleasePointerCapture(e.Pointer());
                try {
                    auto pointerPoint = e.GetCurrentPoint(elem);
                    auto bounds = elem.RenderSize();
                    auto pos = pointerPoint.Position();
                    actuallyHovered = (pos.X >= 0 && pos.X <= bounds.Width && pos.Y >= 0 && pos.Y <= bounds.Height);
                } catch (...) { actuallyHovered = false; }
            }
            *isHovered = actuallyHovered;
            updatePlayerVisualState();

            if (g_unloading || e.Handled()) return;

            if (actuallyHovered) {
                auto kind = e.GetCurrentPoint(nullptr).Properties().PointerUpdateKind();
                auto fe = sender.template try_as<FrameworkElement>();
                if (kind == winrt::Windows::UI::Input::PointerUpdateKind::LeftButtonReleased) {
                    ExecuteMediaAction(g_settings.playerLeftClick, fe);
                } else if (kind == winrt::Windows::UI::Input::PointerUpdateKind::RightButtonReleased) {
                    ExecuteMediaAction(g_settings.playerRightClick, fe);
                } else if (kind == winrt::Windows::UI::Input::PointerUpdateKind::MiddleButtonReleased) {
                    ExecuteMediaAction(g_settings.playerMiddleClick, fe);
                }
            }
        });

        wrapper.PointerCanceled([isPressed, isHovered, updatePlayerVisualState](auto const&, auto const&) mutable {
            *isPressed = false;
            *isHovered = false;
            updatePlayerVisualState();
        });

        wrapper.PointerCaptureLost([isPressed, isHovered, updatePlayerVisualState](auto const& sender, winrt::Windows::UI::Xaml::Input::PointerRoutedEventArgs const& e) mutable {
            *isPressed = false;
            if (auto elem = sender.template try_as<UIElement>()) {
                try {
                    auto pointerPoint = e.GetCurrentPoint(elem);
                    auto bounds = elem.RenderSize();
                    auto pos = pointerPoint.Position();
                    *isHovered = (pos.X >= 0 && pos.X <= bounds.Width && pos.Y >= 0 && pos.Y <= bounds.Height);
                } catch (...) { *isHovered = false; }
            }
            updatePlayerVisualState();
        });

        wrapper.DoubleTapped([isPressed, updatePlayerVisualState](auto const& sender, winrt::Windows::UI::Xaml::Input::DoubleTappedRoutedEventArgs const& e) mutable {
            *isPressed = false;
            updatePlayerVisualState();
            if (g_unloading) return;
            ExecuteMediaAction(g_settings.playerLeftDoubleClick, sender.template try_as<FrameworkElement>());
            e.Handled(true);
        });

        wrapper.Tag(winrt::box_value(winrt::hstring(L"FluentMediaBarWrapper")));

        wrapper.PointerWheelChanged([](auto const&, winrt::Windows::UI::Xaml::Input::PointerRoutedEventArgs const& e) {
            if (g_unloading) return;
            auto action = g_settings.playerWheelAction;
            if (action == L"none") return;

            auto props = e.GetCurrentPoint(nullptr).Properties();
            int delta = props.MouseWheelDelta();

            if (action == L"switch_tracks") {
                if (delta > 0) SendMediaCommandAsync(1);
                else if (delta < 0) SendMediaCommandAsync(3);
                DispatchMediaUpdate();
            } else if (action == L"switch_tracks_inverted") {
                if (delta > 0) SendMediaCommandAsync(3);
                else if (delta < 0) SendMediaCommandAsync(1);
                DispatchMediaUpdate();
            } else if (action == L"switch_sessions") {
                if (delta != 0) SwitchMediaSession();
            } else if (action == L"app_sound") {
                AdjustCurrentMediaAppVolumeAsync(delta);
            }
            e.Handled(true);
        });

        try {
            winrt::Windows::UI::Xaml::Interop::TypeName gridType;
            gridType.Name = L"Windows.UI.Xaml.Controls.Grid";
            gridType.Kind = winrt::Windows::UI::Xaml::Interop::TypeKind::Metadata;

            winrt::Windows::UI::Xaml::Style wrapperStyle(gridType);
            wrapper.Style(wrapperStyle);
        } catch (...) {}

        return wrapper;
    } catch (...) {
        Wh_Log(L"BuildPlayerGrid: Exception occurred");
        return nullptr;
    }
}

struct InjectionTarget {
    Grid grid;
    int  insertCol = 0;
};

static int RemovePlayerGridChildren(Grid const& targetGrid) {
    if (!targetGrid) return -1;

    int firstCol = -1;
    for (int i = (int)targetGrid.Children().Size() - 1; i >= 0; --i) {
        auto fe = targetGrid.Children().GetAt(i).try_as<FrameworkElement>();
        if (fe && fe.Name() == kGridName) {
            if (firstCol < 0) firstCol = Grid::GetColumn(fe);
            try { targetGrid.Children().RemoveAt(i); } catch (...) {}
        }
    }
    return firstCol;
}

static void RemoveAnchorDebugOverlays(Grid const& targetGrid) {
    if (!targetGrid) return;
    for (int i = (int)targetGrid.Children().Size() - 1; i >= 0; --i) {
        auto fe = targetGrid.Children().GetAt(i).try_as<FrameworkElement>();
        if (fe && fe.Name() == kAnchorOverlayName) {
            try { targetGrid.Children().RemoveAt(i); } catch (...) {}
        }
    }
}

static void UpdateAnchorDebugOverlay(Grid const& targetGrid, FrameworkElement const& targetElem) {
    if (!targetGrid) return;

    if (!g_settings.showLayoutAnchors || !targetElem) {
        RemoveAnchorDebugOverlays(targetGrid);
        return;
    }

    try {
        Border overlay{nullptr};
        for (uint32_t i = 0; i < targetGrid.Children().Size(); ++i) {
            auto fe = targetGrid.Children().GetAt(i).try_as<FrameworkElement>();
            if (fe && fe.Name() == kAnchorOverlayName) {
                overlay = fe.try_as<Border>();
                break;
            }
        }

        if (!overlay) {
            overlay = Border();
            overlay.Name(kAnchorOverlayName);
            overlay.IsHitTestVisible(false);
            overlay.BorderBrush(MakeBrush({0xE0, 0x00, 0xA2, 0xFF}));
            overlay.BorderThickness({2,2,2,2});
            overlay.Background(MakeBrush({0x20, 0x00, 0xA2, 0xFF}));
            overlay.HorizontalAlignment(HorizontalAlignment::Left);
            overlay.VerticalAlignment(VerticalAlignment::Top);
            Canvas::SetZIndex(overlay, 5001);
            targetGrid.Children().Append(overlay);
        }

        auto transform = targetElem.TransformToVisual(targetGrid);
        auto point = transform.TransformPoint({0, 0});
        overlay.Width(std::max(1.0, targetElem.ActualWidth()));
        overlay.Height(std::max(1.0, targetElem.ActualHeight()));
        overlay.Margin({point.X, point.Y, 0, 0});
        overlay.Visibility(Visibility::Visible);
    } catch (...) {
        RemoveAnchorDebugOverlays(targetGrid);
    }
}

static const wchar_t* const kStartButtonNames[] = {
    L"StartButton",
    L"StartMenuButton",
    L"StartMenuLaunchButton",
    L"LaunchListButton",
};

static Grid FindTaskbarRootGrid(FrameworkElement const& root) {
    FrameworkElement taskbarFrame = nullptr;
    int count = VisualTreeHelper::GetChildrenCount(root);

    for (int i = 0; i < count; i++) {
        auto c = VisualTreeHelper::GetChild(root, i).try_as<FrameworkElement>();
        if (c) {
            auto className = winrt::get_class_name(c);
            if (className == L"Taskbar.TaskbarFrame") {
                taskbarFrame = c;
                break;
            }
        }
    }

    if (!taskbarFrame) {
        return nullptr;
    }

    auto rootGrid = FindChildByName(taskbarFrame, L"RootGrid");

    return rootGrid ? rootGrid.try_as<Grid>() : nullptr;
}

static FrameworkElement FindElementInRepeater(FrameworkElement const& repeater, const wchar_t* const* names, int nameCount) {
    if (!repeater) return nullptr;

    int childCount = VisualTreeHelper::GetChildrenCount(repeater);
    for (int i = 0; i < childCount; i++) {
        auto child = VisualTreeHelper::GetChild(repeater, i).try_as<FrameworkElement>();
        if (!child) continue;

        for (int j = 0; j < nameCount; j++) {
            if (child.Name() == names[j]) return child;
        }
    }

    for (int i = 0; i < childCount; i++) {
        auto child = VisualTreeHelper::GetChild(repeater, i).try_as<FrameworkElement>();
        if (!child) continue;

        int subChildCount = VisualTreeHelper::GetChildrenCount(child);
        for (int k = 0; k < subChildCount; k++) {
            auto subChild = VisualTreeHelper::GetChild(child, k).try_as<FrameworkElement>();
            if (!subChild) continue;

            for (int j = 0; j < nameCount; j++) {
                if (subChild.Name() == names[j]) return subChild;
            }
        }
    }

    return nullptr;
}

static FrameworkElement FindElementByClassName(FrameworkElement const& parent, const wchar_t* className) {
    if (!parent) return nullptr;

    int childCount = VisualTreeHelper::GetChildrenCount(parent);
    for (int i = 0; i < childCount; i++) {
        auto child = VisualTreeHelper::GetChild(parent, i).try_as<FrameworkElement>();
        if (!child) continue;

        auto childClassName = winrt::get_class_name(child);
        if (childClassName == className) return child;
    }

    return nullptr;
}

static FrameworkElement FindNthElementByClassName(FrameworkElement const& parent, const wchar_t* className, int index) {
    if (!parent) return nullptr;

    int foundCount = 0;
    int childCount = VisualTreeHelper::GetChildrenCount(parent);

    for (int i = 0; i < childCount; i++) {
        auto child = VisualTreeHelper::GetChild(parent, i).try_as<FrameworkElement>();
        if (!child) continue;

        auto childClassName = winrt::get_class_name(child);
        if (childClassName == className) {
            if (foundCount == index) return child;
            foundCount++;
        }
    }

    return nullptr;
}

static FrameworkElement FindChildByClassName(FrameworkElement const& parent, const wchar_t* className, int depth = 32) {
    if (!parent || depth <= 0) return nullptr;

    int childCount = VisualTreeHelper::GetChildrenCount(parent);
    for (int i = 0; i < childCount; i++) {
        auto child = VisualTreeHelper::GetChild(parent, i).try_as<FrameworkElement>();
        if (!child) continue;

        if (winrt::get_class_name(child) == className) return child;
        if (auto found = FindChildByClassName(child, className, depth - 1)) return found;
    }

    return nullptr;
}

static double FindLeftmostVisibleChildX(FrameworkElement const& parent, UIElement const& relativeTo, int depth = 3) {
    if (!parent || !relativeTo || depth < 0) return -1.0;

    double leftmost = -1.0;
    int childCount = VisualTreeHelper::GetChildrenCount(parent);
    for (int i = 0; i < childCount; i++) {
        auto child = VisualTreeHelper::GetChild(parent, i).try_as<FrameworkElement>();
        if (!child) continue;

        try {
            if (child.Visibility() == Visibility::Visible && child.ActualWidth() > 1.0) {
                auto transform = child.TransformToVisual(relativeTo);
                auto point = transform.TransformPoint({0, 0});
                if (point.X >= 0.0 && (leftmost < 0.0 || point.X < leftmost))
                    leftmost = point.X;
            }
        } catch (...) {}

        double nested = FindLeftmostVisibleChildX(child, relativeTo, depth - 1);
        if (nested >= 0.0 && (leftmost < 0.0 || nested < leftmost))
            leftmost = nested;
    }

    return leftmost;
}

// TaskbarFrameRepeater can stretch across most of the taskbar even when its
// actual buttons occupy only a small area. Use the right edge of its compact
// visible descendants so "After applications" follows the final app button,
// not the repeater's tray-side edge.
static double FindRightmostTaskbarItemEdge(
    FrameworkElement const& parent, FrameworkElement const& relativeTo,
    int depth = 8) {
    if (!parent || !relativeTo || depth < 0) return -1.0;

    double rightmost = -1.0;
    int childCount = VisualTreeHelper::GetChildrenCount(parent);
    for (int i = 0; i < childCount; ++i) {
        auto child = VisualTreeHelper::GetChild(parent, i)
                         .try_as<FrameworkElement>();
        if (!child) continue;

        try {
            if (child.Visibility() == Visibility::Visible) {
                double width = child.ActualWidth();
                double height = child.ActualHeight();
                // Individual Start/Search/app buttons are compact. Excluding
                // stretched layout panels prevents selecting the tray edge.
                if (width > 1.0 && width <= 400.0 && height > 1.0) {
                    auto transform = child.TransformToVisual(relativeTo);
                    auto point = transform.TransformPoint({0, 0});
                    double edge = point.X + width;
                    if (point.X >= 0.0 &&
                        edge <= relativeTo.ActualWidth() + 4.0) {
                        rightmost = std::max(rightmost, edge);
                    }
                }
            }
        } catch (...) {}

        double nested = FindRightmostTaskbarItemEdge(
            child, relativeTo, depth - 1);
        rightmost = std::max(rightmost, nested);
    }

    return rightmost;
}

static FrameworkElement FindTrayElement(FrameworkElement const& trayGrid, FrameworkElement const& root, const wchar_t* name) {
    auto elem = FindChildByName(trayGrid, name);
    if (!elem) elem = FindChildByName(root, name);
    return elem;
}

static bool IsStartButtonModActive(FrameworkElement const& root) {
    try {
        auto rootGrid = FindTaskbarRootGrid(root);
        if (!rootGrid) return false;

        auto repeater = FindChildByName(rootGrid, L"TaskbarFrameRepeater");
        if (!repeater) return false;

        static const wchar_t* kStartNames[] = {L"StartButton"};
        auto startButton = FindElementInRepeater(repeater, kStartNames, 1);
        if (!startButton) return false;

        auto margin = startButton.Margin();
        return margin.Right < -10.0;
    } catch (...) {
        return false;
    }
}

static double GetStartButtonAdjustment(FrameworkElement const& root) {
    try {
        auto rootGrid = FindTaskbarRootGrid(root);
        if (!rootGrid) return 0.0;

        auto repeater = FindChildByName(rootGrid, L"TaskbarFrameRepeater");
        if (!repeater) return 0.0;

        static const wchar_t* kStartNames[] = {L"StartButton"};
        auto startButton = FindElementInRepeater(repeater, kStartNames, 1);
        if (!startButton) return 0.0;

        return startButton.ActualWidth();
    } catch (...) {
        return 0.0;
    }
}

static InjectionTarget ResolveInjectionTarget(
    FrameworkElement const& root,
    std::wstring_view position)
{
    auto trayFrame = FindChildByName(root, L"SystemTrayFrameGrid");
    if (auto trayGrid = trayFrame ? trayFrame.try_as<Grid>() : nullptr) {

        int col = -1;
        if      (position == L"tray_right")
            col = (int)trayGrid.ColumnDefinitions().Size();
        else if (position == L"tray_left")
            col = 0;
        else if (position == L"tray_before_clock") {
            auto clockBtn = FindChildByName(trayGrid, L"NotificationCenterButton");
            if (!clockBtn) clockBtn = FindChildByName(root, L"NotificationCenterButton");
            col = clockBtn ? Grid::GetColumn(clockBtn) : -1;
        }
        else if (position == L"tray_after_clock") {
            auto showDesktop = FindChildByName(trayGrid, L"ShowDesktopStack");
            if (!showDesktop) showDesktop = FindChildByName(root, L"ShowDesktopStack");
            col = showDesktop ? Grid::GetColumn(showDesktop) : -1;
        }
        else if (position == L"tray_before_omni_left") {
            auto omniBtn = FindChildByName(trayGrid, L"ControlCenterButton");
            if (!omniBtn) omniBtn = FindChildByName(root, L"ControlCenterButton");
            col = omniBtn ? Grid::GetColumn(omniBtn) : -1;
        }
        else if (position == L"tray_before_omni_right") {
            auto omniBtn = FindChildByName(trayGrid, L"ControlCenterButton");
            if (!omniBtn) omniBtn = FindChildByName(root, L"ControlCenterButton");
            if (omniBtn) col = Grid::GetColumn(omniBtn) + 1;
            else col = -1;
        }
        else if (position == L"tray_language_left") {
            auto languageBtn = FindTrayElement(trayGrid, root, L"NonActivatableStack");
            col = languageBtn ? Grid::GetColumn(languageBtn) : -1;
        }
        else if (position == L"tray_language_right") {
            auto languageBtn = FindTrayElement(trayGrid, root, L"NonActivatableStack");
            col = languageBtn ? Grid::GetColumn(languageBtn) + 1 : -1;
        }
        else if (position == L"tray_hidden_icons_left") {
            auto hiddenIconsBtn = FindTrayElement(trayGrid, root, L"NotifyIconStack");
            col = hiddenIconsBtn ? Grid::GetColumn(hiddenIconsBtn) : -1;
        }
        else if (position == L"tray_hidden_icons_right") {
            auto hiddenIconsBtn = FindTrayElement(trayGrid, root, L"NotifyIconStack");
            col = hiddenIconsBtn ? Grid::GetColumn(hiddenIconsBtn) + 1 : -1;
        }
        else if (position == L"tray_icons_left") {
            auto trayIcons = FindTrayElement(trayGrid, root, L"NotificationAreaIcons");
            col = trayIcons ? Grid::GetColumn(trayIcons) : -1;
        }
        else if (position == L"tray_icons_right") {
            auto trayIcons = FindTrayElement(trayGrid, root, L"NotificationAreaIcons");
            col = trayIcons ? Grid::GetColumn(trayIcons) + 1 : -1;
        }
        else if (position == L"tray_after_showdesktop_left") {
            auto showDesktop = FindChildByName(trayGrid, L"ShowDesktopStack");
            if (!showDesktop) showDesktop = FindChildByName(root, L"ShowDesktopStack");
            col = showDesktop ? Grid::GetColumn(showDesktop) : -1;
        }
        else if (position == L"tray_after_showdesktop_right") {
            auto showDesktop = FindChildByName(trayGrid, L"ShowDesktopStack");
            if (!showDesktop) showDesktop = FindChildByName(root, L"ShowDesktopStack");
            if (showDesktop) col = Grid::GetColumn(showDesktop) + 1;
            else col = (int)trayGrid.ColumnDefinitions().Size();
        }

        if (col >= 0) {
            return {trayGrid, col};
        }
    }

    if (position == L"taskbar_left_start"  ||
        position == L"taskbar_right_start" ||
        position == L"taskbar_after_apps" ||
        position == L"taskbar_after_search_left"||
        position == L"taskbar_after_search_right"||
        position == L"taskbar_after_taskview_left"||
        position == L"taskbar_after_taskview_right"||
        position == L"taskbar_after_widgets_left"||
        position == L"taskbar_after_widgets_right"||
        position == L"taskbar_left_edge"   ||
        position == L"taskbar_center_edge" ||
        position == L"taskbar_right_edge")
    {
        auto rootGrid = FindTaskbarRootGrid(root);
        if (!rootGrid) {
            auto tf2 = FindChildByName(root, L"SystemTrayFrameGrid");
            if (auto tg2 = tf2 ? tf2.try_as<Grid>() : nullptr)
                return {tg2, (int)tg2.ColumnDefinitions().Size()};
            return {};
        }

        return {rootGrid, -1};
    }

    return {};
}

static void ApplyCustomPlayerOffset(Grid const& playerGrid) {
    if (!playerGrid || g_settings.positionPreset != L"custom" ||
        (!g_settings.customOffsetX && !g_settings.customOffsetY)) {
        return;
    }
    TranslateTransform offset;
    offset.X((double)g_settings.customOffsetX);
    offset.Y((double)g_settings.customOffsetY);
    playerGrid.RenderTransform(offset);
}

static FrameworkElement FindTrackingElementForPosition(
    FrameworkElement const& root, Grid const& targetGrid,
    const std::wstring& position, bool& placeBefore) {
    placeBefore = false;
    auto repeater = FindChildByName(targetGrid, L"TaskbarFrameRepeater");
    if (!repeater) return nullptr;

    if (position == L"taskbar_after_apps") return repeater;
    if (position == L"taskbar_left_start" || position == L"taskbar_right_start") {
        placeBefore = position == L"taskbar_left_start";
        return FindElementInRepeater(
            repeater, kStartButtonNames, ARRAYSIZE(kStartButtonNames));
    }
    if (position == L"taskbar_after_search_left" ||
        position == L"taskbar_after_search_right") {
        placeBefore = position == L"taskbar_after_search_left";
        return FindElementByClassName(repeater, L"Taskbar.TaskbarExtensionElement");
    }
    if (position == L"taskbar_after_taskview_left" ||
        position == L"taskbar_after_taskview_right") {
        placeBefore = position == L"taskbar_after_taskview_left";
        return FindNthElementByClassName(
            repeater, L"Taskbar.ExperienceToggleButton", 1);
    }
    if (position == L"taskbar_after_widgets_left" ||
        position == L"taskbar_after_widgets_right") {
        placeBefore = position == L"taskbar_after_widgets_left";
        auto element = FindChildByName(repeater, L"AugmentedEntryPointButton");
        if (!element) {
            element = FindChildByClassName(
                repeater, L"Taskbar.AugmentedEntryPointButton");
        }
        return element;
    }
    return nullptr;
}

static bool InjectMirrorPlayer(HWND taskbarWindow) {
    try {
        auto xamlRoot = GetTaskbarXamlRoot(taskbarWindow);
        if (!xamlRoot) return false;
        auto root = xamlRoot.Content().try_as<FrameworkElement>();
        if (!root) return false;

        auto [targetGrid, insertCol] = ResolveInjectionTarget(root, g_settings.position);
        if (!targetGrid) return false;

        auto instance = std::make_shared<MirrorPlayerInstance>();
        instance->taskbarWindow = taskbarWindow;
        instance->targetGrid = targetGrid;
        instance->playerGrid = BuildPlayerGrid();
        if (!instance->playerGrid) return false;
        ApplyCustomPlayerOffset(instance->playerGrid);

        RemovePlayerGridChildren(targetGrid);
        bool isTrayGrid = targetGrid.Name() == L"SystemTrayFrameGrid";
        if (isTrayGrid) {
            ColumnDefinition newColumn;
            newColumn.Width({1.0, GridUnitType::Auto});
            if (insertCol >= (int)targetGrid.ColumnDefinitions().Size()) {
                targetGrid.ColumnDefinitions().Append(newColumn);
            } else {
                targetGrid.ColumnDefinitions().InsertAt(insertCol, newColumn);
                for (uint32_t i = 0; i < targetGrid.Children().Size(); ++i) {
                    auto child = targetGrid.Children().GetAt(i).try_as<FrameworkElement>();
                    if (child && Grid::GetColumn(child) >= insertCol) {
                        Grid::SetColumn(child, Grid::GetColumn(child) + 1);
                    }
                }
            }
            instance->playerGrid.Margin({
                (double)g_settings.playerMarginLeft, 0,
                (double)g_settings.playerMarginRight, 0});
            Grid::SetColumn(instance->playerGrid, insertCol);
            targetGrid.Children().Append(instance->playerGrid);
            instance->playerColumn = insertCol;
        } else {
            bool edgePosition =
                g_settings.position == L"taskbar_left_edge" ||
                g_settings.position == L"taskbar_center_edge" ||
                g_settings.position == L"taskbar_right_edge";

            instance->playerGrid.HorizontalAlignment(HorizontalAlignment::Left);
            if (edgePosition) {
                if (g_settings.position == L"taskbar_center_edge") {
                    instance->playerGrid.HorizontalAlignment(HorizontalAlignment::Center);
                } else if (g_settings.position == L"taskbar_right_edge") {
                    instance->playerGrid.HorizontalAlignment(HorizontalAlignment::Right);
                }
                instance->playerGrid.Margin({
                    (double)g_settings.playerMarginLeft, 0,
                    (double)g_settings.playerMarginRight, 0});
            } else {
                bool placeBefore = false;
                auto tracked = FindTrackingElementForPosition(
                    root, targetGrid, g_settings.position, placeBefore);
                if (!tracked) {
                    tracked = FindTrackingElementForPosition(
                        root, targetGrid, L"taskbar_after_apps", placeBefore);
                }
                if (tracked) {
                    instance->trackedElement = tracked;
                    instance->trackedOriginalMargin = tracked.Margin();
                    instance->layoutUpdatedToken = targetGrid.LayoutUpdated(
                        [instance, placeBefore](auto const&, auto const&) {
                            if (g_unloading || !instance->playerGrid ||
                                !instance->trackedElement) return;
                            try {
                                bool visible = instance->playerGrid.Visibility() == Visibility::Visible;
                                double width = visible ? instance->playerGrid.ActualWidth() : 0.0;
                                double gap = visible
                                    ? width + g_settings.playerMarginLeft + g_settings.playerMarginRight
                                    : 0.0;
                                auto margin = instance->trackedOriginalMargin;
                                if (placeBefore) margin.Left += gap;
                                else margin.Right += gap;
                                instance->trackedElement.Margin(margin);

                                auto transform = instance->trackedElement.TransformToVisual(
                                    instance->targetGrid);
                                auto point = transform.TransformPoint({0, 0});
                                double x = 0.0;
                                if (g_settings.position == L"taskbar_after_apps") {
                                    double appEdge = FindRightmostTaskbarItemEdge(
                                        instance->trackedElement,
                                        instance->targetGrid);
                                    x = appEdge >= 0.0
                                        ? appEdge + g_settings.playerMarginLeft
                                        : point.X + instance->trackedElement.ActualWidth() +
                                            g_settings.playerMarginLeft;
                                } else {
                                    x = placeBefore
                                        ? point.X - gap + g_settings.playerMarginLeft
                                        : point.X + instance->trackedElement.ActualWidth() +
                                            g_settings.playerMarginLeft;
                                }
                                instance->playerGrid.Margin({x, 0, 0, 0});
                            } catch (...) {}
                        });
                } else {
                    instance->playerGrid.Margin({
                        (double)g_settings.playerMarginLeft, 0,
                        (double)g_settings.playerMarginRight, 0});
                }
            }
            Grid::SetColumn(instance->playerGrid, 0);
            Canvas::SetZIndex(instance->playerGrid, 1000);
            targetGrid.Children().Append(instance->playerGrid);
        }

        instance->playerGrid.Visibility(Visibility::Visible);
        instance->playerGrid.UpdateLayout();
        g_mirrorPlayers.push_back(instance);
        return true;
    } catch (...) {
        Wh_Log(L"InjectMirrorPlayer: failed for taskbar %p", taskbarWindow);
        return false;
    }
}

static void InjectConfiguredMirrorPlayers() {
    if (g_settings.taskbarMode != L"all") return;
    for (const auto& taskbar : EnumerateTaskbarWindows()) {
        if (taskbar.hWnd == g_taskbarWnd) continue;
        DWORD threadId = GetWindowThreadProcessId(taskbar.hWnd, nullptr);
        if (threadId == GetCurrentThreadId()) {
            InjectMirrorPlayer(taskbar.hWnd);
        } else {
            struct MirrorWork { HWND window; } work{taskbar.hWnd};
            RunFromWindowThread(taskbar.hWnd, [](void* param) {
                InjectMirrorPlayer(static_cast<MirrorWork*>(param)->window);
            }, &work);
        }
    }
}

static void RemoveMirrorPlayers() {
    for (auto& instance : g_mirrorPlayers) {
        if (!instance) continue;
        try {
            if (instance->layoutUpdatedToken.value && instance->targetGrid) {
                instance->targetGrid.LayoutUpdated(instance->layoutUpdatedToken);
            }
            if (instance->trackedElement) {
                instance->trackedElement.Margin(instance->trackedOriginalMargin);
            }
            if (instance->targetGrid) {
                int playerColumn = RemovePlayerGridChildren(instance->targetGrid);
                if (instance->playerColumn >= 0 && playerColumn >= 0 &&
                    playerColumn < (int)instance->targetGrid.ColumnDefinitions().Size()) {
                    for (uint32_t i = 0; i < instance->targetGrid.Children().Size(); ++i) {
                        auto child = instance->targetGrid.Children().GetAt(i).try_as<FrameworkElement>();
                        if (child && Grid::GetColumn(child) > playerColumn) {
                            Grid::SetColumn(child, Grid::GetColumn(child) - 1);
                        }
                    }
                    instance->targetGrid.ColumnDefinitions().RemoveAt(playerColumn);
                }
            }
        } catch (...) {}
    }
    g_mirrorPlayers.clear();
}

static bool InjectPlayerGrid() {
    Wh_Log(L"InjectPlayerGrid: Starting");
    HWND hWnd = g_taskbarWnd ? g_taskbarWnd : FindCurrentProcessTaskbarWnd();
    if (!hWnd) {
        Wh_Log(L"InjectPlayerGrid: No taskbar window found");
        return false;
    }
    g_taskbarWnd = hWnd;

    try {
        auto xamlRoot = GetTaskbarXamlRoot(hWnd);
        if (!xamlRoot) {
            Wh_Log(L"InjectPlayerGrid: Failed to get XAML root");
            return false;
        }

        auto root = xamlRoot.Content().try_as<FrameworkElement>();
        if (!root) {
            Wh_Log(L"InjectPlayerGrid: Failed to get root FrameworkElement");
            return false;
        }

        Wh_Log(L"InjectPlayerGrid: Got XAML root and framework element");

        if (g_settings.enableTreeDump) {
            DumpXamlTree(root, 0, 5);
            auto rootGrid = FindTaskbarRootGrid(root);
            if (rootGrid) {
                auto repeater = FindChildByName(rootGrid, L"TaskbarFrameRepeater");
                if (repeater) {
                    DumpXamlTree(repeater, 0, 3);
                }
            }
        }

        auto [targetGrid, insertCol] = ResolveInjectionTarget(root, g_settings.position);

        if (!targetGrid) {
            if (g_settings.enableTreeDump) {
                DumpXamlTree(root, 0, 8);
            }
            return false;
        }

        Grid playerGrid = BuildPlayerGrid();
        if (!playerGrid) return false;
        ApplyCustomPlayerOffset(playerGrid);

        bool startButtonModActive = IsStartButtonModActive(root);
        (void)startButtonModActive;

        bool isTrayGrid = (targetGrid.Name() == L"SystemTrayFrameGrid");
        RemovePlayerGridChildren(targetGrid);
        RemoveAnchorDebugOverlays(targetGrid);

        if (isTrayGrid) {
            ColumnDefinition newCol;
            newCol.Width({1.0, GridUnitType::Auto});

            if (insertCol >= (int)targetGrid.ColumnDefinitions().Size()) {
                targetGrid.ColumnDefinitions().Append(newCol);
            } else {
                targetGrid.ColumnDefinitions().InsertAt(insertCol, newCol);
                for (uint32_t i = 0; i < targetGrid.Children().Size(); ++i) {
                    auto child = targetGrid.Children().GetAt(i).try_as<FrameworkElement>();
                    if (child) {
                        int childCol = Grid::GetColumn(child);
                        if (childCol >= insertCol)
                            Grid::SetColumn(child, childCol + 1);
                    }
                }
            }

            playerGrid.Margin({(double)g_settings.playerMarginLeft, 0,
                              (double)g_settings.playerMarginRight, 0});
            Grid::SetColumn(playerGrid, insertCol);
            targetGrid.Children().Append(playerGrid);
            g_playerColumn = insertCol;

        }
        else {
            auto repeater  = FindChildByName(targetGrid, L"TaskbarFrameRepeater");
            auto trayFrame = FindChildByName(targetGrid, L"SystemTrayFrameGrid");

            bool isEdgePosition = (g_settings.position == L"taskbar_left_edge" ||
                                   g_settings.position == L"taskbar_center_edge" ||
                                   g_settings.position == L"taskbar_right_edge");

            bool isTrackingPosition = (g_settings.position == L"taskbar_left_start" ||
                                       g_settings.position == L"taskbar_right_start" ||
                                       g_settings.position == L"taskbar_after_apps" ||
                                       g_settings.position == L"taskbar_after_search_left" ||
                                       g_settings.position == L"taskbar_after_search_right" ||
                                       g_settings.position == L"taskbar_after_taskview_left" ||
                                       g_settings.position == L"taskbar_after_taskview_right" ||
                                       g_settings.position == L"taskbar_after_widgets_left" ||
                                       g_settings.position == L"taskbar_after_widgets_right");

            if (isEdgePosition || isTrackingPosition) {
                double leftMargin  = (double)g_settings.playerMarginLeft;
                double rightMargin = (double)g_settings.playerMarginRight;

                playerGrid.HorizontalAlignment(HorizontalAlignment::Left);

                if (isEdgePosition) {
                    if (g_settings.position == L"taskbar_left_edge") {
                        playerGrid.Margin({leftMargin, 0, rightMargin, 0});
                    }
                    else if (g_settings.position == L"taskbar_center_edge") {
                        playerGrid.HorizontalAlignment(HorizontalAlignment::Center);
                        playerGrid.Margin({leftMargin, 0, rightMargin, 0});
                    }
                    else if (g_settings.position == L"taskbar_right_edge") {
                        playerGrid.HorizontalAlignment(HorizontalAlignment::Right);
                        if (trayFrame) rightMargin += trayFrame.ActualWidth() + 4;
                        playerGrid.Margin({leftMargin, 0, rightMargin, 0});
                    }
                } else if (isTrackingPosition) {
                    FrameworkElement targetElem = nullptr;
                    std::wstring trackSide = L"right";

                    if (repeater) {
                        if (g_settings.position == L"taskbar_after_apps") {
                            targetElem = repeater;
                            trackSide = L"after_apps";
                        } else if (g_settings.position == L"taskbar_left_start") {
                            targetElem = FindElementInRepeater(repeater, kStartButtonNames, ARRAYSIZE(kStartButtonNames));
                            trackSide = L"left";
                        } else if (g_settings.position == L"taskbar_right_start") {
                            targetElem = FindElementInRepeater(repeater, kStartButtonNames, ARRAYSIZE(kStartButtonNames));
                            trackSide = L"right";
                        } else if (g_settings.position == L"taskbar_after_search_left") {
                            targetElem = FindElementByClassName(repeater, L"Taskbar.TaskbarExtensionElement");
                            trackSide = L"left";
                        } else if (g_settings.position == L"taskbar_after_search_right") {
                            targetElem = FindElementByClassName(repeater, L"Taskbar.TaskbarExtensionElement");
                            trackSide = L"right";
                        } else if (g_settings.position == L"taskbar_after_taskview_left") {
                            targetElem = FindNthElementByClassName(repeater, L"Taskbar.ExperienceToggleButton", 1);
                            trackSide = L"left";
                        } else if (g_settings.position == L"taskbar_after_taskview_right") {
                            targetElem = FindNthElementByClassName(repeater, L"Taskbar.ExperienceToggleButton", 1);
                            trackSide = L"right";
                        } else if (g_settings.position == L"taskbar_after_widgets_left") {
                            targetElem = FindChildByName(repeater, L"AugmentedEntryPointButton");
                            if (!targetElem) targetElem = FindChildByClassName(repeater, L"Taskbar.AugmentedEntryPointButton");
                            trackSide = L"left";
                        } else if (g_settings.position == L"taskbar_after_widgets_right") {
                            targetElem = FindChildByName(repeater, L"AugmentedEntryPointButton");
                            if (!targetElem) targetElem = FindChildByClassName(repeater, L"Taskbar.AugmentedEntryPointButton");
                            trackSide = L"right";
                        }
                    }

                    if (targetElem) {
                        g_trackedElement = targetElem;
                        g_trackedElementOriginalMargin = targetElem.Margin();
                        g_hasTrackedElementOriginalMargin = true;
                        g_trackPosition = trackSide;

                        bool startButtonModActiveMod = IsStartButtonModActive(root);
                        double startButtonOffset = 0.0;

                        if (startButtonModActiveMod &&
                            (g_settings.position == L"taskbar_left_start" ||
                             g_settings.position == L"taskbar_right_start" ||
                             g_settings.position == L"taskbar_after_taskview_left" ||
                             g_settings.position == L"taskbar_after_taskview_right")) {
                            startButtonOffset = GetStartButtonAdjustment(root);
                        }

                        g_layoutUpdateToken = targetGrid.LayoutUpdated(
                            [targetGrid, startButtonModActiveMod, startButtonOffset](winrt::Windows::Foundation::IInspectable const&, winrt::Windows::Foundation::IInspectable const&) {
                                try {
                                    if (!g_playerGrid || !g_trackedElement || g_unloading) return;
                                    UpdateAnchorDebugOverlay(targetGrid, g_trackedElement);

                                    bool isVisible = (g_playerGrid.Visibility() == Visibility::Visible);
                                    double w = isVisible ? g_playerGrid.ActualWidth() : 0.0;

                                    double desiredGap = isVisible ? (w + g_settings.playerMarginLeft + g_settings.playerMarginRight) : 0.0;
                                    auto m = g_hasTrackedElementOriginalMargin ? g_trackedElementOriginalMargin : g_trackedElement.Margin();
                                    auto currentMargin = g_trackedElement.Margin();
                                    bool changedMargin = false;

                                    if (g_trackPosition == L"far_left") {
                                        try {
                                            double originalLeft = g_hasTrackedElementOriginalMargin ? g_trackedElementOriginalMargin.Left : 0.0;
                                            double currentLeftmost = FindLeftmostVisibleChildX(g_trackedElement, targetGrid, 4);
                                            double naturalLeft = currentLeftmost >= 0.0
                                                ? currentLeftmost - (currentMargin.Left - originalLeft)
                                                : desiredGap;
                                            double requiredExtra = std::max(0.0, desiredGap - naturalLeft);
                                            double targetLeft = originalLeft + requiredExtra;

                                            if (std::abs(currentMargin.Left - targetLeft) > 1.0 ||
                                                std::abs(currentMargin.Right - m.Right) > 1.0) {
                                                m.Left = targetLeft;
                                                changedMargin = true;
                                            }
                                        } catch (...) {
                                            if (g_hasTrackedElementOriginalMargin &&
                                                (std::abs(currentMargin.Left - m.Left) > 1.0 ||
                                                 std::abs(currentMargin.Right - m.Right) > 1.0)) {
                                                changedMargin = true;
                                            }
                                        }
                                    } else if (g_trackPosition == L"left") {
                                        if (std::abs(currentMargin.Left - desiredGap) > 1.0) { m.Left = desiredGap; changedMargin = true; }
                                    } else {
                                        if (std::abs(currentMargin.Right - desiredGap) > 1.0) { m.Right = desiredGap; changedMargin = true; }
                                    }

                                    if (changedMargin) g_trackedElement.Margin(m);

                                    if (isVisible) {
                                        try {
                                            auto transform = g_trackedElement.TransformToVisual(targetGrid);
                                            auto point = transform.TransformPoint({0, 0});
                                            double leftPos = point.X;

                                            if (g_trackPosition == L"far_left") {
                                                leftPos = g_settings.playerMarginLeft;
                                            } else if (g_trackPosition == L"left") {
                                                leftPos = point.X - desiredGap + g_settings.playerMarginLeft;
                                                if (startButtonModActiveMod && startButtonOffset > 0) {
                                                    leftPos += startButtonOffset;
                                                }
                                            } else if (g_trackPosition == L"after_apps") {
                                                double appEdge = FindRightmostTaskbarItemEdge(
                                                    g_trackedElement, targetGrid);
                                                leftPos = appEdge >= 0.0
                                                    ? appEdge + g_settings.playerMarginLeft
                                                    : point.X + g_trackedElement.ActualWidth() +
                                                        g_settings.playerMarginLeft;
                                            } else {
                                                leftPos = point.X + g_trackedElement.ActualWidth() + g_settings.playerMarginLeft;
                                            }

                                            auto pm = g_playerGrid.Margin();
                                            if (std::abs(pm.Left - leftPos) > 1.0) {
                                                g_playerGrid.Margin({leftPos, 0, 0, 0});
                                            }
                                        } catch (...) {}
                                    }
                                } catch (...) {
                                    Wh_Log(L"Player LayoutUpdated: tracked element became invalid, untracking");
                                    g_trackedElement = nullptr;
                                    g_hasTrackedElementOriginalMargin = false;
                                }
                            }
                        );
                    } else {
                        playerGrid.Margin({leftMargin, 0, rightMargin, 0});
                    }
                }

                Grid::SetColumn(playerGrid, 0);
                Canvas::SetZIndex(playerGrid, 1000);
                targetGrid.Children().Append(playerGrid);
                g_playerColumn = -1;
                Wh_Log(L"InjectPlayerGrid: Added player to targetGrid.Children (edge/tracking position), column=0, zindex=1000");
            }
            else {
                ColumnDefinition newCol;
                newCol.Width({1.0, GridUnitType::Auto});

                if (insertCol >= (int)targetGrid.ColumnDefinitions().Size()) {
                    targetGrid.ColumnDefinitions().Append(newCol);
                } else {
                    targetGrid.ColumnDefinitions().InsertAt(insertCol, newCol);
                    for (uint32_t i = 0; i < targetGrid.Children().Size(); ++i) {
                        auto child = targetGrid.Children().GetAt(i).try_as<FrameworkElement>();
                        if (child) {
                            int childCol = Grid::GetColumn(child);
                            if (childCol >= insertCol)
                                Grid::SetColumn(child, childCol + 1);
                        }
                    }
                }

                playerGrid.Margin({(double)g_settings.playerMarginLeft, 0,
                                  (double)g_settings.playerMarginRight, 0});
                Grid::SetColumn(playerGrid, insertCol);
                targetGrid.Children().Append(playerGrid);
                g_playerColumn = insertCol;
            }
        }

        g_playerGrid      = playerGrid;
        g_injectionParent = targetGrid;

        InjectConfiguredMirrorPlayers();
        RefreshPlayerContents();

        g_playerGrid.Visibility(Visibility::Visible);
        Wh_Log(L"InjectPlayerGrid: Set g_playerGrid.Visibility to Visible");
        g_playerGrid.UpdateLayout();

        Wh_Log(L"InjectPlayerGrid: Player size - ActualWidth=%f, ActualHeight=%f, Width=%f, Height=%f",
               g_playerGrid.ActualWidth(), g_playerGrid.ActualHeight(),
               g_playerGrid.Width(), g_playerGrid.Height());
        auto margin = g_playerGrid.Margin();
        Wh_Log(L"InjectPlayerGrid: Player margin - Left=%f, Top=%f, Right=%f, Bottom=%f",
               margin.Left, margin.Top, margin.Right, margin.Bottom);

        if (g_injectionParent) {
            g_injectionParent.UpdateLayout();
            Wh_Log(L"InjectPlayerGrid: Called UpdateLayout on injectionParent");
        }

        if (g_playerGrid.ActualWidth() == 0.0 && g_playerGrid.ActualHeight() == 0.0) {
            Wh_Log(L"InjectPlayerGrid: XAML not laid out yet, scheduling deferred update");
            g_needsUiUpdate = true;
            if (g_timerUpdateEvent) SetEvent(g_timerUpdateEvent);
        }

        auto dispatcher = g_playerGrid.Dispatcher();
        if (dispatcher) {
            try {
                dispatcher.RunAsync(winrt::Windows::UI::Core::CoreDispatcherPriority::Low, [=]() {
                    if (!g_unloading && g_playerGrid) RefreshThemeColors();
                });
            } catch (...) {
                Wh_Log(L"InjectPlayerGrid: Failed to dispatch RefreshThemeColors");
            }
        }

        Canvas::SetZIndex(g_playerGrid, 1000);

        OnSessionsChanged();
        g_needsUiUpdate = true;
        return true;
    } catch (...) {
        Wh_Log(L"InjectPlayerGrid: Exception during injection");
        return false;
    }
}

static void RemovePlayerGrid() {
    RemoveMirrorPlayers();
    if (!g_injectionParent) return;

    try {
        if (g_layoutUpdateToken.value) {
            auto targetGrid = g_injectionParent.try_as<Grid>();
            if (targetGrid) {
                try { targetGrid.LayoutUpdated(g_layoutUpdateToken); } catch (...) {}
            }
            g_layoutUpdateToken = {};
        }

        if (g_trackedElement) {
            try {
                if (g_hasTrackedElementOriginalMargin) {
                    g_trackedElement.Margin(g_trackedElementOriginalMargin);
                } else {
                    auto m = g_trackedElement.Margin();
                    if (g_trackPosition == L"left" || g_trackPosition == L"far_left") m.Left = 0;
                    if (g_trackPosition == L"right") m.Right = 0;
                    g_trackedElement.Margin(m);
                }
            } catch (...) {}
            g_trackedElement = nullptr;
        }
        g_hasTrackedElementOriginalMargin = false;
        g_trackPosition = L"";

        auto targetGrid = g_injectionParent.try_as<Grid>();
        int playerCol = -1;

        RemoveAnchorDebugOverlays(targetGrid);
        playerCol = RemovePlayerGridChildren(targetGrid);

        bool isTrackingPosition = (g_settings.position == L"taskbar_left_edge" ||
                                  g_settings.position == L"taskbar_center_edge" ||
                                  g_settings.position == L"taskbar_right_edge" ||
                                  g_settings.position == L"taskbar_left_start" ||
                                  g_settings.position == L"taskbar_right_start" ||
                                  g_settings.position == L"taskbar_after_apps" ||
                                  g_settings.position == L"taskbar_after_search_left" ||
                                  g_settings.position == L"taskbar_after_search_right" ||
                                  g_settings.position == L"taskbar_after_taskview_left" ||
                                  g_settings.position == L"taskbar_after_taskview_right" ||
                                  g_settings.position == L"taskbar_after_widgets_left" ||
                                  g_settings.position == L"taskbar_after_widgets_right");

        if (!isTrackingPosition && playerCol >= 0 && playerCol < (int)targetGrid.ColumnDefinitions().Size()) {
            for (uint32_t i = 0; i < targetGrid.Children().Size(); ++i) {
                auto child = targetGrid.Children().GetAt(i).try_as<FrameworkElement>();
                if (child) {
                    int childCol = Grid::GetColumn(child);
                    if (childCol > playerCol)
                        Grid::SetColumn(child, childCol - 1);

                }
            }
            targetGrid.ColumnDefinitions().RemoveAt(playerCol);
        }

        g_playerGrid      = nullptr;
        g_injectionParent = nullptr;
        g_playerColumn    = -1;

        g_cachedAlbumTitle.clear();
        g_cachedAlbumArtist.clear();
        g_cachedThumbnailBytes.clear();
        g_cachedPaletteHash = 0;
        g_blurBgCache.Invalidate();
        g_cachedAppIconSize = -1;

        g_scrollCachedTitle.clear();
        g_scrollCachedArtist.clear();

        ResetScrollState(g_titleScroll);
        ResetScrollState(g_artistScroll);
    } catch (...) {
        g_playerGrid      = nullptr;
        g_injectionParent = nullptr;
        g_playerColumn    = -1;

        g_cachedAlbumTitle.clear();
        g_cachedAlbumArtist.clear();
        g_cachedThumbnailBytes.clear();
        g_cachedPaletteHash = 0;
        g_blurBgCache.Invalidate();
        g_cachedAppIconSize = -1;

        ResetScrollState(g_titleScroll);
        ResetScrollState(g_artistScroll);
    }
}

static void RefreshPlayerContents() {
    if (!g_refreshingMirrorPlayers && !g_mirrorPlayers.empty()) {
        g_refreshingMirrorPlayers = true;
        Grid originalGrid = g_playerGrid;
        RefreshPlayerContents();
        for (const auto& instance : g_mirrorPlayers) {
            if (!instance || !instance->playerGrid) continue;
            g_playerGrid = instance->playerGrid;
            RefreshPlayerContents();
        }
        g_playerGrid = originalGrid;
        g_refreshingMirrorPlayers = false;
        return;
    }
    if (!g_playerGrid || g_unloading || g_applyingSettings) return;

    Wh_Log(L"RefreshPlayerContents: Starting");
    std::wstring      title, artist;
    bool              isPlaying = false, hasMedia = false;
    std::vector<BYTE> thumbBytes;
    std::vector<BYTE> appIconBytes;
    uint64_t          thumbHash = 0;
    bool              canSkipPrevious = true, canSkipNext = true;
    bool              canShuffle = true, canRepeat = true, canSeek = true;
    {
        std::lock_guard<std::mutex> lk(g_mediaMtx);
        title        = g_media.title;
        artist       = g_media.artist;
        isPlaying    = g_media.isPlaying;
        hasMedia     = g_media.hasMedia;
        thumbBytes   = g_media.thumbnailBytes;
        thumbHash    = g_media.thumbnailHash;
        appIconBytes = g_media.appIconBytes;
        canSkipPrevious = g_media.canSkipPrevious;
        canSkipNext     = g_media.canSkipNext;
        canShuffle      = g_media.canShuffle;
        canRepeat       = g_media.canRepeat;
        canSeek         = g_media.canSeek;
    }
    Wh_Log(L"RefreshPlayerContents: title='%s', artist='%s', isPlaying=%d, hasMedia=%d",
           title.c_str(), artist.c_str(), isPlaying, hasMedia);
    (void)hasMedia;
    bool hasSession = false;
    { std::lock_guard<std::mutex> lk(g_sessionMtx); hasSession = (g_currentSession != nullptr); }

    g_playerGrid.UpdateLayout();

    if (title != g_scrollCachedTitle || artist != g_scrollCachedArtist) {
        g_scrollCachedTitle  = title;
        g_scrollCachedArtist = artist;
        ResetScrollState(g_titleScroll);
        ResetScrollState(g_artistScroll);
        try {
            if (auto fe = FindChildByName(g_playerGrid, kTitleCloneName))
                if (auto cl = fe.try_as<TextBlock>())
                    cl.Visibility(Visibility::Collapsed);
        } catch (...) {}
        try {
            if (auto fe = FindChildByName(g_playerGrid, kArtistCloneName))
                if (auto cl = fe.try_as<TextBlock>())
                    cl.Visibility(Visibility::Collapsed);
        } catch (...) {}
        try {
            if (auto fe = FindChildByName(g_playerGrid, kTitleBlockName))
                if (auto tb = fe.try_as<TextBlock>())
                    Canvas::SetLeft(tb, 0.0);
        } catch (...) {}
        try {
            if (auto fe = FindChildByName(g_playerGrid, kArtistBlockName))
                if (auto ab = fe.try_as<TextBlock>())
                    Canvas::SetLeft(ab, 0.0);
        } catch (...) {}
    }

    bool titleVisible = false;
    bool artistVisible = false;

    if (auto fe = FindChildByName(g_playerGrid, kTitleBlockName))
        if (auto tb = fe.try_as<TextBlock>())
            try {
                std::wstring displayTitle = title;
                if (!hasSession) {
                    displayTitle = g_settings.noMediaTitleText;
                } else if (title.empty()) {
                    displayTitle = g_settings.emptyTitleText;
                }
                tb.Text(winrt::hstring(displayTitle));
                tb.Foreground(MakeBrush(TextColor()));
                bool visible = g_settings.showTrackTitle && !displayTitle.empty();
                titleVisible = visible;
                tb.Visibility(visible ? Visibility::Visible : Visibility::Collapsed);

                if (g_settings.showFullTitleOnHover && !title.empty() && hasSession) {
                    ToolTipService::SetToolTip(tb, winrt::box_value(winrt::hstring(title)));
                    ToolTipService::SetPlacement(tb, Controls::Primitives::PlacementMode::Top);
                } else {
                    ToolTipService::SetToolTip(tb, nullptr);
                }

                if (g_settings.enableTitleScrolling && visible) {
                    try {
                        if (auto viewFe = FindChildByName(g_playerGrid, kTitleScrollViewName))
                            viewFe.Visibility(Visibility::Visible);
                    } catch (...) {}
                    if (auto panelFe = FindChildByName(g_playerGrid, kPanelGridName)) {
                        panelFe.UpdateLayout();
                    }
                    tb.UpdateLayout();
                    double textW = tb.DesiredSize().Width;
                    if (auto viewFe = FindChildByName(g_playerGrid, kTitleScrollViewName)) {
                        if (auto viewCanvas = viewFe.try_as<Canvas>()) {
                            double minW = (double)g_settings.textAreaMinWidth;
                            double maxW = (double)g_settings.textAreaMaxWidth;
                            double viewW = textW;

                            if (maxW > 0 && viewW > maxW) viewW = maxW;

                            double availW = GetAvailableScrollTextAreaWidth();
                            if (availW > 0.0 && viewW > availW) {
                                viewW = (minW > 0.0) ? std::max(availW, minW) : availW;
                            }

                            if (minW > 0 && viewW < minW) viewW = minW;
                            if (std::abs(viewCanvas.Width() - viewW) > 0.5) {
                                viewCanvas.Width(viewW);
                                try {
                                    if (auto geo = viewCanvas.Clip().try_as<winrt::Windows::UI::Xaml::Media::RectangleGeometry>()) {
                                        auto r = geo.Rect();
                                        geo.Rect({0, 0, (float)viewW, r.Height});
                                    }
                                } catch (...) {}
                            }
                            bool wasActive = g_titleScroll.active;
                            g_titleScroll.textWidth = textW;
                            g_titleScroll.viewWidth = viewW;
                            g_titleScroll.active = (textW > viewW + 2.0);
                            if (!g_titleScroll.active) {
                                g_titleScroll.offset = 0.0;
                                g_titleScroll.forward = true;
                                Canvas::SetLeft(tb, 0.0);
                            } else if (!wasActive) {
                                g_titleScroll.offset = 0.0;
                                g_titleScroll.forward = true;
                                g_titleScroll.pausing  = true;
                                g_titleScroll.pauseTick = g_settings.scrollPauseDuration;
                            }
                            if (auto cloneFe = FindChildByName(g_playerGrid, kTitleCloneName)) {
                                if (auto clone = cloneFe.try_as<TextBlock>()) {
                                    clone.Text(tb.Text());
                                    clone.Foreground(tb.Foreground());
                                    clone.Visibility(Visibility::Collapsed);
                                }
                            }
                        }
                    }
                } else {
                    g_titleScroll.active = false;
                    g_titleScroll.offset = 0.0;
                    if (g_settings.enableTitleScrolling) {
                        try {
                            if (auto viewFe = FindChildByName(g_playerGrid, kTitleScrollViewName))
                                viewFe.Visibility(Visibility::Collapsed);
                        } catch (...) {}
                    }
                }
            } catch (...) {}

    if (auto fe = FindChildByName(g_playerGrid, kArtistBlockName))
        if (auto ab = fe.try_as<TextBlock>())
            try {
                std::wstring displayArtist = artist;
                if (!hasSession) {
                    displayArtist = g_settings.noMediaArtistText;
                } else if (artist.empty()) {
                    displayArtist = g_settings.emptyArtistText;
                }
                ab.Text(winrt::hstring(displayArtist));
                bool visible = g_settings.showTrackArtist && !displayArtist.empty();
                artistVisible = visible;
                ab.Visibility(visible ? Visibility::Visible : Visibility::Collapsed);
                ab.Foreground(MakeBrush(ArtistColor()));

                if (g_settings.showFullTitleOnHover && !artist.empty() && hasSession) {
                    ToolTipService::SetToolTip(ab, winrt::box_value(winrt::hstring(artist)));
                    ToolTipService::SetPlacement(ab, Controls::Primitives::PlacementMode::Top);
                } else {
                    ToolTipService::SetToolTip(ab, nullptr);
                }

                if (g_settings.enableArtistScrolling && visible) {
                    try {
                        if (auto viewFe = FindChildByName(g_playerGrid, kArtistScrollViewName))
                            viewFe.Visibility(Visibility::Visible);
                    } catch (...) {}
                    if (auto panelFe = FindChildByName(g_playerGrid, kPanelGridName)) {
                        panelFe.UpdateLayout();
                    }
                    ab.UpdateLayout();
                    double textW = ab.DesiredSize().Width;
                    if (auto viewFe = FindChildByName(g_playerGrid, kArtistScrollViewName)) {
                        if (auto viewCanvas = viewFe.try_as<Canvas>()) {
                            double minW = (double)g_settings.textAreaMinWidth;
                            double maxW = (double)g_settings.textAreaMaxWidth;
                            double viewW = textW;

                            if (maxW > 0 && viewW > maxW) viewW = maxW;

                            double availW = GetAvailableScrollTextAreaWidth();
                            if (availW > 0.0 && viewW > availW) {
                                viewW = (minW > 0.0) ? std::max(availW, minW) : availW;
                            }

                            if (minW > 0 && viewW < minW) viewW = minW;
                            if (std::abs(viewCanvas.Width() - viewW) > 0.5) {
                                viewCanvas.Width(viewW);
                                try {
                                    if (auto geo = viewCanvas.Clip().try_as<winrt::Windows::UI::Xaml::Media::RectangleGeometry>()) {
                                        auto r = geo.Rect();
                                        geo.Rect({0, 0, (float)viewW, r.Height});
                                    }
                                } catch (...) {}
                            }
                            bool wasActive = g_artistScroll.active;
                            g_artistScroll.textWidth = textW;
                            g_artistScroll.viewWidth = viewW;
                            g_artistScroll.active = (textW > viewW + 2.0);
                            if (!g_artistScroll.active) {
                                g_artistScroll.offset = 0.0;
                                g_artistScroll.forward = true;
                                Canvas::SetLeft(ab, 0.0);
                            } else if (!wasActive) {
                                g_artistScroll.offset = 0.0;
                                g_artistScroll.forward = true;
                                g_artistScroll.pausing  = true;
                                g_artistScroll.pauseTick = g_settings.scrollPauseDuration;
                            }
                            if (auto cloneFe = FindChildByName(g_playerGrid, kArtistCloneName)) {
                                if (auto clone = cloneFe.try_as<TextBlock>()) {
                                    clone.Text(ab.Text());
                                    clone.Foreground(ab.Foreground());
                                    clone.Visibility(Visibility::Collapsed);
                                }
                            }
                        }
                    }
                } else {
                    g_artistScroll.active = false;
                    g_artistScroll.offset = 0.0;
                    if (g_settings.enableArtistScrolling) {
                        try {
                            if (auto viewFe = FindChildByName(g_playerGrid, kArtistScrollViewName))
                                viewFe.Visibility(Visibility::Collapsed);
                        } catch (...) {}
                    }
                }
            } catch (...) {}

    try {
        if (auto stackFe = FindChildByName(g_playerGrid, kTextStackName)) {
            bool anyTextVisible = titleVisible || artistVisible;
            stackFe.Visibility(anyTextVisible ? Visibility::Visible : Visibility::Collapsed);
        }
    } catch (...) {}

    if (auto fe = FindChildByName(g_playerGrid, kPlayBtnName))
        if (auto btn = fe.try_as<Button>())
            try {
                if (auto ct = btn.Content().try_as<TextBlock>()) {
                    const wchar_t* glyph = GetGlyph(2, isPlaying);
                    ct.Text(winrt::hstring(glyph));
                    ct.Foreground(MakeBrush(ButtonColor()));
                }
            } catch (...) {}

    if (auto fe = FindChildByName(g_playerGrid, kPrevBtnName))
        if (auto btn = fe.try_as<Button>())
            try {
                bool supported = canSkipPrevious;
                btn.IsEnabled(supported);
                if (g_settings.hideUnsupportedButtons) {
                    btn.Visibility(supported ? Visibility::Visible : Visibility::Collapsed);
                } else {
                    btn.Visibility(Visibility::Visible);
                }
                if (auto ct = btn.Content().try_as<TextBlock>()) {
                    const wchar_t* glyph = GetGlyph(1);
                    ct.Text(winrt::hstring(glyph));
                    if (!supported && !g_settings.hideUnsupportedButtons) {
                        ct.Opacity(0.35);
                        ct.Foreground(MakeBrush(ButtonColor()));
                    } else {
                        ct.Opacity(1.0);
                        ct.Foreground(MakeBrush(ButtonColor()));
                    }
                }
            } catch (...) {}

    if (auto fe = FindChildByName(g_playerGrid, kNextBtnName))
        if (auto btn = fe.try_as<Button>())
            try {
                bool supported = canSkipNext;
                btn.IsEnabled(supported);
                if (g_settings.hideUnsupportedButtons) {
                    btn.Visibility(supported ? Visibility::Visible : Visibility::Collapsed);
                } else {
                    btn.Visibility(Visibility::Visible);
                }
                if (auto ct = btn.Content().try_as<TextBlock>()) {
                    const wchar_t* glyph = GetGlyph(3);
                    ct.Text(winrt::hstring(glyph));
                    ct.Opacity(supported ? 1.0 : 0.35);
                    ct.Foreground(MakeBrush(ButtonColor()));
                }
            } catch (...) {}

    if (auto fe = FindChildByName(g_playerGrid, kVolumeBtnName))
        if (auto btn = fe.try_as<Button>())
            try {
                if (auto ct = btn.Content().try_as<TextBlock>()) {
                    int percent = g_currentVolumePercent.load();
                    bool muted = g_currentVolumeMuted.load();
                    ct.Text(VolumeGlyphForState(
                        percent < 0 ? 100 : percent, muted));
                    ct.Foreground(MakeBrush(ButtonColor()));
                    ct.Opacity(1.0);
                }
            } catch (...) {}

    if (auto fe = FindChildByName(g_playerGrid, kRewindBtnName))
        if (auto btn = fe.try_as<Button>())
            try {
                bool supported = canSeek;
                btn.IsEnabled(supported);
                if (g_settings.hideUnsupportedButtons) {
                    btn.Visibility(supported ? Visibility::Visible : Visibility::Collapsed);
                } else {
                    btn.Visibility(Visibility::Visible);
                }
                if (auto ct = btn.Content().try_as<TextBlock>()) {
                    const wchar_t* glyph = GetGlyph(5);
                    ct.Text(winrt::hstring(glyph));
                    ct.Opacity(supported ? 1.0 : 0.35);
                    ct.Foreground(MakeBrush(ButtonColor()));
                }
            } catch (...) {}

    if (auto fe = FindChildByName(g_playerGrid, kForwardBtnName))
        if (auto btn = fe.try_as<Button>())
            try {
                bool supported = canSeek;
                btn.IsEnabled(supported);
                if (g_settings.hideUnsupportedButtons) {
                    btn.Visibility(supported ? Visibility::Visible : Visibility::Collapsed);
                } else {
                    btn.Visibility(Visibility::Visible);
                }
                if (auto ct = btn.Content().try_as<TextBlock>()) {
                    const wchar_t* glyph = GetGlyph(6);
                    ct.Text(winrt::hstring(glyph));
                    ct.Opacity(supported ? 1.0 : 0.35);
                    ct.Foreground(MakeBrush(ButtonColor()));
                }
            } catch (...) {}

    if (auto fe = FindChildByName(g_playerGrid, kShuffleBtnName))
        if (auto btn = fe.try_as<Button>())
            try {
                bool supported = canShuffle;
                btn.IsEnabled(supported);
                if (g_settings.hideUnsupportedButtons) {
                    btn.Visibility(supported ? Visibility::Visible : Visibility::Collapsed);
                } else {
                    btn.Visibility(Visibility::Visible);
                }
                if (auto ct = btn.Content().try_as<TextBlock>()) {
                    bool isEnabled = g_shuffleEnabled.load();
                    const wchar_t* glyph = L"\uE8B1";
                    ct.Text(winrt::hstring(glyph));
                    if (!supported && !g_settings.hideUnsupportedButtons) {
                        ct.Opacity(0.35);
                    } else {
                        ct.Opacity(isEnabled ? 1.0 : 0.4);
                    }
                    ct.Foreground(MakeBrush(ButtonColor()));
                }
            } catch (...) {}

    if (auto fe = FindChildByName(g_playerGrid, kRepeatBtnName))
        if (auto btn = fe.try_as<Button>())
            try {
                bool supported = canRepeat;
                btn.IsEnabled(supported);
                if (g_settings.hideUnsupportedButtons) {
                    btn.Visibility(supported ? Visibility::Visible : Visibility::Collapsed);
                } else {
                    btn.Visibility(Visibility::Visible);
                }
                if (auto ct = btn.Content().try_as<TextBlock>()) {
                    RepeatMode mode = g_repeatMode.load();
                    const wchar_t* glyph;
                    switch (mode) {
                        case RepeatMode::Off:
                            glyph = L"\uF5E7";
                            break;
                        case RepeatMode::All:
                            glyph = L"\uE8EE";
                            break;
                        case RepeatMode::One:
                            glyph = L"\uE8ED";
                            break;
                    }
                    ct.Text(winrt::hstring(glyph));
                    ct.Foreground(MakeBrush(ButtonColor()));
                    if (!supported && !g_settings.hideUnsupportedButtons) {
                        ct.Opacity(0.35);
                    } else {
                        ct.Opacity(1.0);
                    }
                }
            } catch (...) {}

    if (auto fe = FindChildByName(g_playerGrid, kSwitchSessionsBtnName))
        if (auto btn = fe.try_as<Button>())
            try {
                bool supported = g_sessionCount.load() > 1;
                btn.IsEnabled(supported);
                if (g_settings.hideUnsupportedButtons) {
                    btn.Visibility(supported ? Visibility::Visible : Visibility::Collapsed);
                } else {
                    btn.Visibility(Visibility::Visible);
                }
                if (auto ct = btn.Content().try_as<TextBlock>()) {
                    ct.Opacity(supported ? 1.0 : 0.35);
                    ct.Foreground(MakeBrush(ButtonColor()));
                }
            } catch (...) {}

    if (g_settings.showPauseOverlay && g_settings.showAlbumArt) {
        if (auto fe = FindChildByName(g_playerGrid, L"PauseIconOverlay"))
            if (auto overlay = fe.try_as<Border>()) {
                try {
                    bool showPause = !isPlaying;
                    overlay.Visibility(showPause ? Visibility::Visible : Visibility::Collapsed);

                    if (auto pauseIcon = overlay.Child().try_as<TextBlock>()) {
                        pauseIcon.Text(GetGlyph(2, true));
                        bool useFluent = (g_settings.iconStyle == L"fluent_outline" || g_settings.iconStyle == L"fluent_filled");
                        pauseIcon.FontFamily(Media::FontFamily(useFluent ? L"Segoe Fluent Icons" : L"Segoe MDL2 Assets"));
                        pauseIcon.FontSize((double)g_settings.pauseOverlayIconSize);
                    }

                    if (showPause) {
                        if (auto artImg = FindChildByName(g_playerGrid, kArtImageName)) {
                            if (auto parent = VisualTreeHelper::GetParent(artImg)) {
                                if (auto artInnerGrid = parent.try_as<Grid>()) {
                                    for (uint32_t i = 0; i < artInnerGrid.Children().Size(); ++i) {
                                        auto child = artInnerGrid.Children().GetAt(i);
                                        if (auto border = child.try_as<Border>()) {
                                            if (border.Name() == L"EmptyIconBorder") {
                                                border.Visibility(Visibility::Collapsed);
                                                break;
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                } catch (...) {}
            }
    }

    bool paletteChanged = false;

    if (auto fe = FindChildByName(g_playerGrid, kArtImageName))
        if (auto img = fe.try_as<Controls::Image>()) {
            if (!thumbBytes.empty() && g_settings.showAlbumArt) {
                bool isSameAlbum = (img.Source() &&
                                   !g_cachedThumbnailBytes.empty() &&
                                   title == g_cachedAlbumTitle &&
                                   artist == g_cachedAlbumArtist &&
                                   thumbBytes == g_cachedThumbnailBytes);

                size_t newHash = (size_t)thumbHash;
                if (newHash != g_cachedPaletteHash && newHash != 0) {
                    g_cachedAlbumPalette = ExtractAlbumPalette(thumbBytes);
                    g_cachedPaletteHash = newHash;
                    paletteChanged = true;
                }

                if (!isSameAlbum) {
                    try {
                        IStream* pRawStream = SHCreateMemStream(
                            thumbBytes.data(), static_cast<UINT>(thumbBytes.size()));
                        if (pRawStream) {
                            winrt::com_ptr<IStream> comStream;
                            comStream.attach(pRawStream);

                            winrt::Windows::Storage::Streams::IRandomAccessStream rasStream{ nullptr };
                            ::CreateRandomAccessStreamOverStream(
                                comStream.get(),
                                BSOS_DEFAULT,
                                winrt::guid_of<winrt::Windows::Storage::Streams::IRandomAccessStream>(),
                                winrt::put_abi(rasStream));

                            if (rasStream) {
                                BitmapImage bmp;

                                if (g_settings.albumArtQuality == L"low") {
                                    int baseHeight = g_settings.albumArtMaxHeight > 0 ? g_settings.albumArtMaxHeight : 64;
                                    int decodeHeight = baseHeight / 2;
                                    if (decodeHeight < 16) decodeHeight = 16;
                                    bmp.DecodePixelHeight(decodeHeight);
                                } else if (g_settings.albumArtQuality == L"medium") {
                                    if (g_settings.albumArtMaxHeight > 0) {
                                        bmp.DecodePixelHeight(g_settings.albumArtMaxHeight);
                                    }
                                }

                                bmp.ImageOpened([](auto const&, auto const&) {
                                    if (g_unloading || g_applyingSettings || !g_playerGrid) return;
                                    try {
                                        if (auto panelFe = FindChildByName(g_playerGrid, kPanelGridName)) {
                                            panelFe.UpdateLayout();
                                        }
                                        g_needsUiUpdate = true;
                                        if (g_timerUpdateEvent) SetEvent(g_timerUpdateEvent);
                                    } catch (...) {}
                                });

                                img.Source(bmp);
                                bmp.SetSourceAsync(rasStream);
                                img.Visibility(Visibility::Visible);

                                g_cachedAlbumTitle = title;
                                g_cachedAlbumArtist = artist;
                                g_cachedThumbnailBytes = thumbBytes;

                                if (auto parent = VisualTreeHelper::GetParent(img)) {
                                    if (auto artInnerGrid = parent.try_as<Grid>()) {
                                        if (auto grandParent = VisualTreeHelper::GetParent(artInnerGrid)) {
                                            if (auto container = grandParent.try_as<FrameworkElement>()) {
                                                if (auto greatGrandParent = VisualTreeHelper::GetParent(container)) {
                                                    if (auto artContainer = greatGrandParent.try_as<Grid>()) {
                                                        artContainer.Visibility(Visibility::Visible);
                                                    }
                                                }
                                            }
                                        }
                                        for (uint32_t i = 0; i < artInnerGrid.Children().Size(); ++i) {
                                            auto child = artInnerGrid.Children().GetAt(i);
                                            if (auto border = child.try_as<Border>()) {
                                                if (border.Name() == L"EmptyIconBorder") {
                                                    border.Visibility(Visibility::Collapsed);
                                                    break;
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    } catch (...) { try { img.Source(nullptr); } catch (...) {} }
                } else {
                    img.Visibility(Visibility::Visible);
                    if (auto parent = VisualTreeHelper::GetParent(img)) {
                        if (auto container = parent.try_as<FrameworkElement>()) {
                            if (auto grandParent = VisualTreeHelper::GetParent(container)) {
                                if (auto greatGrandParent = VisualTreeHelper::GetParent(grandParent)) {
                                    if (auto artContainer = greatGrandParent.try_as<Grid>()) {
                                        artContainer.Visibility(Visibility::Visible);
                                    }
                                }
                            }
                        }
                    }
                }

                if (auto bgFe = FindChildByName(g_playerGrid, L"FluentMedia_Background")) {
                    if (auto bgBorder = bgFe.try_as<Border>()) {
                        auto& bgType = g_settings.backgroundType;

                        if (bgType == L"album_art_blur") {
                            try {
                                g_blurBgCache.Invalidate();
                                bgBorder.Visibility(Visibility::Visible);
                                bgBorder.Opacity(g_settings.blurOpacity / 100.0);
                                auto applyBlur = [bgBorder, thumbBytesSnap = thumbBytes]() {
                                    try {
                                        int w = (int)bgBorder.ActualWidth();
                                        int h = (int)bgBorder.ActualHeight();
                                        if (w <= 0 || h <= 0) return;
                                        g_blurBgCache.Invalidate();
                                        bgBorder.Background(MakeAlbumBlurBrush(thumbBytesSnap, w, h));
                                        bgBorder.Opacity(g_settings.blurOpacity / 100.0);
                                        bgBorder.Visibility(Visibility::Visible);
                                    } catch (...) {}
                                };
                                if (bgBorder.ActualWidth() > 0 && bgBorder.ActualHeight() > 0) {
                                    applyBlur();
                                } else {
                                    auto tokenHolder = std::make_shared<winrt::event_token>();
                                    *tokenHolder = bgBorder.SizeChanged(
                                        [applyBlur, bgBorder, tokenHolder](auto const&, auto const&) mutable {
                                            applyBlur();
                                            try { bgBorder.SizeChanged(*tokenHolder); } catch (...) {}
                                        });
                                }
                            } catch (...) {}
                        } else if (bgType == L"solid" || bgType == L"gradient" || bgType == L"acrylic" || bgType == L"mica" || bgType == L"mica_alt") {
                            try {
                                bgBorder.Background(MakeBackgroundBrush());
                                bgBorder.Visibility(Visibility::Visible);
                                bgBorder.Opacity(1.0);
                            } catch (...) {}
                        }
                    }
                }
            } else {
                g_cachedAlbumTitle.clear();
                g_cachedAlbumArtist.clear();
                g_cachedThumbnailBytes.clear();
                g_cachedPaletteHash = 0;
                g_blurBgCache.Invalidate();

                if (auto bgFe = FindChildByName(g_playerGrid, L"FluentMedia_Background")) {
                    if (auto bgBorder = bgFe.try_as<Border>()) {
                        try {
                            auto& bgType = g_settings.backgroundType;
                            if (bgType == L"solid" || bgType == L"gradient" || bgType == L"acrylic" ||
                                bgType == L"mica" || bgType == L"mica_alt") {
                                bgBorder.Background(MakeBackgroundBrush());
                                bgBorder.Visibility(Visibility::Visible);
                                bgBorder.Opacity(1.0);
                            } else {
                                bgBorder.Background(nullptr);
                                bgBorder.Visibility(Visibility::Collapsed);
                            }
                        } catch (...) {}
                    }
                }

                try {
                    img.Source(nullptr);
                    img.Visibility(Visibility::Collapsed);

                    if (g_settings.albumArtEmptyBehavior == L"hide" && thumbBytes.empty()) {
                        if (auto parent = VisualTreeHelper::GetParent(img)) {
                            if (auto container = parent.try_as<FrameworkElement>()) {
                                if (auto grandParent = VisualTreeHelper::GetParent(container)) {
                                    if (auto greatGrandParent = VisualTreeHelper::GetParent(grandParent)) {
                                        if (auto artContainer = greatGrandParent.try_as<FrameworkElement>()) {
                                            artContainer.Visibility(Visibility::Collapsed);
                                        }
                                    }
                                }
                            }
                        }
                    } else if (g_settings.albumArtEmptyBehavior == L"show_icon" && thumbBytes.empty()) {
                        if (auto parent = VisualTreeHelper::GetParent(img)) {
                            if (auto artInnerGrid = parent.try_as<Grid>()) {
                                if (auto grandParent = VisualTreeHelper::GetParent(artInnerGrid)) {
                                    if (auto container = grandParent.try_as<FrameworkElement>()) {
                                        if (auto greatGrandParent = VisualTreeHelper::GetParent(container)) {
                                            if (auto artContainer = greatGrandParent.try_as<Grid>()) {
                                                artContainer.Visibility(Visibility::Visible);
                                            }
                                        }
                                    }
                                }

                                Border iconBorder = nullptr;
                                for (uint32_t i = 0; i < artInnerGrid.Children().Size(); ++i) {
                                    auto child = artInnerGrid.Children().GetAt(i);
                                    if (auto border = child.try_as<Border>()) {
                                        if (border.Name() == L"EmptyIconBorder") {
                                            iconBorder = border;
                                            break;
                                        }
                                    }
                                }

                                if (!iconBorder) {
                                    iconBorder = Border();
                                    iconBorder.Name(L"EmptyIconBorder");
                                    iconBorder.Background(MakeBrush({0x00, 0x00, 0x00, 0x00}));
                                    iconBorder.HorizontalAlignment(HorizontalAlignment::Stretch);
                                    iconBorder.VerticalAlignment(VerticalAlignment::Stretch);
                                    Canvas::SetZIndex(iconBorder, 5);

                                    TextBlock iconText = TextBlock();
                                    iconText.Name(L"EmptyIconText");
                                    iconText.HorizontalAlignment(HorizontalAlignment::Center);
                                    iconText.VerticalAlignment(VerticalAlignment::Center);

                                    iconBorder.Child(iconText);
                                    artInnerGrid.Children().InsertAt(0, iconBorder);
                                }

                                if (auto textBlock = iconBorder.Child().try_as<TextBlock>()) {
                                    std::wstring glyphStr;
                                    try {
                                        unsigned long cp = std::stoul(g_settings.emptyIconGlyph, nullptr, 16);
                                        if (cp <= 0xFFFF) {
                                            glyphStr = std::wstring(1, (wchar_t)cp);
                                        } else {
                                            cp -= 0x10000;
                                            glyphStr += (wchar_t)(0xD800 + (cp >> 10));
                                            glyphStr += (wchar_t)(0xDC00 + (cp & 0x3FF));
                                        }
                                    } catch (...) {
                                        glyphStr = L"\uE189";
                                    }
                                    textBlock.Text(glyphStr);

                                    bool useFluent = (g_settings.emptyIconFont == L"segoe_fluent");
                                    textBlock.FontFamily(Media::FontFamily(
                                        useFluent ? L"Segoe Fluent Icons" : L"Segoe MDL2 Assets"));
                                    textBlock.FontSize((double)g_settings.emptyIconSize);
                                    BYTE alpha = (BYTE)std::clamp((int)std::round(g_settings.emptyIconOpacity * 255.0 / 100.0), 0, 255);
                                    auto iconClr = ParseColorWithThemeSupport(g_settings.emptyIconColor, alpha);
                                    textBlock.Foreground(MakeBrush(iconClr));
                                }

                                iconBorder.Visibility(Visibility::Visible);
                            }
                        }
                    }
                } catch (...) {}
            }
        }

    if (paletteChanged) {
        try {
            if (g_settings.backgroundType == L"gradient" ||
                g_settings.backgroundType == L"solid" ||
                g_settings.backgroundType == L"acrylic" ||
                g_settings.backgroundType == L"mica" ||
                g_settings.backgroundType == L"mica_alt") {
                if (auto bgFe = FindChildByName(g_playerGrid, L"FluentMedia_Background")) {
                    if (auto bgBorder = bgFe.try_as<Border>()) {
                        bgBorder.Background(MakeBackgroundBrush());
                    }
                }
            }

            auto textClr = TextColor();
            auto artistClr = ArtistColor();

            if (auto titleFe = FindChildByName(g_playerGrid, kTitleBlockName)) {
                if (auto titleBlock = titleFe.try_as<TextBlock>()) {
                    titleBlock.Foreground(SolidColorBrush(textClr));
                }
            }

            if (auto artistFe = FindChildByName(g_playerGrid, kArtistBlockName)) {
                if (auto artistBlock = artistFe.try_as<TextBlock>()) {
                    artistBlock.Foreground(SolidColorBrush(artistClr));
                }
            }

            auto buttonClr = ButtonColor();
            for (const auto& btnName : {kPlayBtnName, kPrevBtnName, kNextBtnName, kStopBtnName, kVolumeBtnName,
                                        kRewindBtnName, kForwardBtnName, kShuffleBtnName, kRepeatBtnName}) {
                if (auto btnFe = FindChildByName(g_playerGrid, btnName)) {
                    if (auto btn = btnFe.try_as<Button>()) {
                        if (auto content = btn.Content()) {
                            if (auto icon = content.try_as<TextBlock>()) {
                                icon.Foreground(SolidColorBrush(buttonClr));
                            }
                        }
                    }
                }
            }
        } catch (...) {}
    }

    if (g_settings.showAppIcon) {
        if (auto fe = FindChildByName(g_playerGrid, kAppIconImageName))
            if (auto img = fe.try_as<Controls::Image>()) {
                bool sizeChanged = (g_cachedAppIconSize != g_settings.appIconSize);
                if (sizeChanged && !appIconBytes.empty()) {
                    std::wstring aumid;
                    {
                        std::lock_guard<std::mutex> lk(g_mediaMtx);
                        aumid = g_media.appUserModelId;
                    }
                    if (!aumid.empty()) {
                        appIconBytes = FetchAppIconBytes(aumid, g_settings.appIconSize);
                        {
                            std::lock_guard<std::mutex> lk(g_mediaMtx);
                            g_media.appIconBytes = appIconBytes;
                        }
                    }
                    g_cachedAppIconSize = g_settings.appIconSize;
                }

                if (!appIconBytes.empty()) {
                    try {
                        int iconSz = g_settings.appIconSize;
                        size_t expectedBytes = (size_t)iconSz * iconSz * 4;
                        if (appIconBytes.size() != expectedBytes) {
                            int computed = (int)std::sqrt((double)appIconBytes.size() / 4.0);
                            if (computed > 0 && (size_t)computed * computed * 4 == appIconBytes.size())
                                iconSz = computed;
                        }

                        img.Width(iconSz);
                        img.Height(iconSz);

                        size_t bytesNeeded = (size_t)iconSz * iconSz * 4;
                        winrt::Windows::UI::Xaml::Media::Imaging::WriteableBitmap wb(iconSz, iconSz);
                        auto buf = wb.PixelBuffer();

                        auto bufferByteAccess = buf.as<Windows::Storage::Streams::IBufferByteAccess>();
                        BYTE* pixels = nullptr;
                        bufferByteAccess->Buffer(&pixels);

                        if (appIconBytes.size() >= bytesNeeded && pixels) {
                            for (size_t i = 0; i + 3 < bytesNeeded; i += 4) {
                                pixels[i+0] = appIconBytes[i+2];
                                pixels[i+1] = appIconBytes[i+1];
                                pixels[i+2] = appIconBytes[i+0];
                                pixels[i+3] = appIconBytes[i+3];
                            }
                        }
                        buf.Length(static_cast<uint32_t>(bytesNeeded));
                        wb.Invalidate();
                        img.Source(wb);
                        img.Visibility(Visibility::Visible);
                    } catch (...) {
                        try { img.Source(nullptr); img.Visibility(Visibility::Collapsed); } catch (...) {}
                    }
                } else {
                    try { img.Source(nullptr); img.Visibility(Visibility::Collapsed); } catch (...) {}
                }
            }
    }
}

static bool IsFullscreenActive() {
    using Fn = HRESULT(WINAPI*)(int*);
    static Fn pfn = nullptr; static bool tried = false;
    if (!tried) {
        tried = true;
        HMODULE h = GetModuleHandleW(L"shell32.dll");
        if (!h) h = LoadLibraryW(L"shell32.dll");
        if (h) pfn = (Fn)GetProcAddress(h, (LPCSTR)2573);
    }
    if (!pfn) return false;
    int s = 0;
    return SUCCEEDED(pfn(&s)) && (s == 2 || s == 3 || s == 4);
}

static void UpdateVisibility() {
    if (!g_updatingMirrorVisibility && !g_mirrorPlayers.empty()) {
        g_updatingMirrorVisibility = true;

        Grid primaryGrid = g_playerGrid;
        FrameworkElement primaryParent = g_injectionParent;
        int primaryColumn = g_playerColumn;
        HWND primaryTaskbar = g_taskbarWnd;

        // Update the selected taskbar first. Mirror instances use immediate
        // visibility changes so a delayed animation can't act on restored
        // primary-instance globals.
        UpdateVisibility();
        bool smoothPositionAnimation = g_settings.enableSmoothPositionAnimation;
        g_settings.enableSmoothPositionAnimation = false;
        for (const auto& instance : g_mirrorPlayers) {
            if (!instance || !instance->playerGrid) continue;
            g_playerGrid = instance->playerGrid;
            g_injectionParent = instance->targetGrid;
            g_playerColumn = instance->playerColumn;
            g_taskbarWnd = instance->taskbarWindow;
            UpdateVisibility();
        }
        g_settings.enableSmoothPositionAnimation = smoothPositionAnimation;

        g_playerGrid = primaryGrid;
        g_injectionParent = primaryParent;
        g_playerColumn = primaryColumn;
        g_taskbarWnd = primaryTaskbar;
        g_updatingMirrorVisibility = false;
        return;
    }

    if (!g_playerGrid || g_unloading || g_applyingSettings) return;

    bool hide = false;
    if (g_settings.hideFullscreen && IsFullscreenActive()) hide = true;

    if (!hide && g_hiddenByIdle) hide = true;

    if (!hide) {
        bool hasMedia = false, hasSession = false;
        { std::lock_guard<std::mutex> lk(g_mediaMtx); hasMedia = g_media.hasMedia; }
        { std::lock_guard<std::mutex> lk(g_sessionMtx); hasSession = (g_currentSession != nullptr); }
        if (hasMedia || hasSession) {
            g_lastMediaTime = std::chrono::steady_clock::now();
        }

        if (g_settings.hideWhenNoMedia) {

            if (!hasSession) {
                hide = true;
            }

            else if (!hasMedia) {
                auto now = std::chrono::steady_clock::now();
                auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - g_lastMediaTime).count();

                if (elapsed > 2500) {
                    hide = true;
                } else {
                    // Recheck on the timer's normal 500 ms cadence. The old
                    // implementation spawned a detached thread for every
                    // check, which could create a short startup thread storm.
                    g_needsUiUpdate = true;
                }
            }
        }
    }

    try {
        if (g_playerColumn == -1) {
            if (hide) {
                g_playerGrid.Visibility(Visibility::Collapsed);
            } else {
                g_playerGrid.Visibility(Visibility::Visible);
            }
        } else {
            bool isTrackingPosition = (g_settings.position == L"taskbar_left_start" ||
                                      g_settings.position == L"taskbar_right_start" ||
                                      g_settings.position == L"taskbar_after_search_left" ||
                                      g_settings.position == L"taskbar_after_search_right" ||
                                      g_settings.position == L"taskbar_after_taskview_left" ||
                                      g_settings.position == L"taskbar_after_taskview_right" ||
                                      g_settings.position == L"taskbar_after_widgets_left" ||
                                      g_settings.position == L"taskbar_after_widgets_right" ||
                                      g_settings.position == L"taskbar_far_edge_left");

            if (hide && isTrackingPosition && g_settings.enableSmoothPositionAnimation) {
                g_playerGrid.Opacity(0.0);

                std::thread([]() {
                    std::this_thread::sleep_for(std::chrono::milliseconds(200));
                    try {
                        RunFromWindowThread(g_taskbarWnd, [](void* param) {
                            try {
                                if (g_playerGrid) {
                                    g_playerGrid.Visibility(Visibility::Collapsed);

                                    if (g_injectionParent) {
                                        if (auto targetGrid = g_injectionParent.try_as<Grid>()) {
                                            if (g_playerColumn < (int)targetGrid.ColumnDefinitions().Size()) {
                                                auto colDef = targetGrid.ColumnDefinitions().GetAt(g_playerColumn);
                                                colDef.Width({0.0, GridUnitType::Pixel});
                                            }
                                        }
                                    }

                                    g_playerGrid.MinWidth(0);
                                    g_playerGrid.MaxWidth(0);
                                    g_playerGrid.Width(0);
                                }
                            } catch (...) {}
                        }, nullptr);
                    } catch (...) {}
                }).detach();
            } else {
                g_playerGrid.Visibility(hide ? Visibility::Collapsed : Visibility::Visible);
                g_playerGrid.Opacity(hide ? 0.0 : 1.0);
                Wh_Log(L"UpdateVisibility: Set Visibility=%d, Opacity=%f", hide ? 0 : 1, hide ? 0.0 : 1.0);

                if (g_injectionParent) {
                    if (auto targetGrid = g_injectionParent.try_as<Grid>()) {
                        if (g_playerColumn < (int)targetGrid.ColumnDefinitions().Size()) {
                            auto colDef = targetGrid.ColumnDefinitions().GetAt(g_playerColumn);
                            if (hide) {
                                colDef.Width({0.0, GridUnitType::Pixel});
                                Wh_Log(L"UpdateVisibility: Set column width to 0");
                            } else {
                                colDef.Width({1.0, GridUnitType::Auto});
                                Wh_Log(L"UpdateVisibility: Set column width to Auto");
                            }
                        }
                    }
                } else {
                    Wh_Log(L"UpdateVisibility: g_injectionParent is NULL");
                }

                if (hide) {
                    g_playerGrid.MinWidth(0);
                    g_playerGrid.MaxWidth(0);
                    g_playerGrid.Width(0);
                } else {
                    bool hasTextOrButtons = g_settings.showTrackTitle || g_settings.showTrackArtist || (g_settings.showMediaButtons && !g_mediaButtons.empty());
                    if (hasTextOrButtons && g_settings.playerMinWidth > 0) {
                        g_playerGrid.MinWidth((double)g_settings.playerMinWidth);
                    } else {
                        g_playerGrid.MinWidth(0);
                    }
                    if (g_settings.playerMaxWidth > 0) {
                        g_playerGrid.MaxWidth((double)g_settings.playerMaxWidth);
                    } else {
                        g_playerGrid.ClearValue(FrameworkElement::MaxWidthProperty());
                    }
                    g_playerGrid.ClearValue(FrameworkElement::WidthProperty());
                }
            }
        }

        g_playerGrid.UpdateLayout();
    } catch (...) {}
}

static void ApplySettings() {
    Wh_Log(L"ApplySettings: Called");
    g_idleSeconds  = 0;
    g_idleTicks    = 0;
    g_hiddenByIdle = false;
    ApplyTaskbarTransparencyToAll();
    try { RemovePlayerGrid(); } catch (...) { Wh_Log(L"ApplySettings: Exception in RemovePlayerGrid"); }
    if (!g_unloading) {
        Wh_Log(L"ApplySettings: Calling InjectPlayerGrid");
        try { InjectPlayerGrid(); } catch (...) { Wh_Log(L"ApplySettings: Exception in InjectPlayerGrid"); }
    }
    Wh_Log(L"ApplySettings: Finished, g_playerGrid exists = %d", g_playerGrid ? 1 : 0);
}


static void ApplySettingsWithRetry(FrameworkElement xamlRootContent) {
    auto retry = [&]() {
        auto timer = DispatcherTimer();
        timer.Interval(winrt::Windows::Foundation::TimeSpan{
            std::chrono::milliseconds(100)});
        auto tickToken = std::make_shared<winrt::event_token>();
        *tickToken = timer.Tick(
            [timer, tickToken, xamlRootContent](
                winrt::Windows::Foundation::IInspectable const&,
                winrt::Windows::Foundation::IInspectable const&) {
                timer.Stop();
                timer.Tick(*tickToken);
                ApplySettingsWithRetry(xamlRootContent);
            });
        timer.Start();
    };

    if (g_unloading) {
        return;
    }

    auto systemTrayFrame = FindChildByClassName(xamlRootContent, L"SystemTray.SystemTrayFrame");
    if (!systemTrayFrame) {
        Wh_Log(L"SystemTrayFrame not found, retrying...");
        retry();
        return;
    }

    auto systemTrayFrameGrid = FindChildByName(systemTrayFrame, L"SystemTrayFrameGrid");
    if (!systemTrayFrameGrid) {
        Wh_Log(L"SystemTrayFrameGrid not found, retrying...");
        retry();
        return;
    }

    ApplySettings();
}

using TrayUI_StartTaskbar_t = void(WINAPI*)(void*);
static TrayUI_StartTaskbar_t TrayUI_StartTaskbar_Original = nullptr;

static void WINAPI TrayUI_StartTaskbar_Hook(void* pThis) {
    Wh_Log(L"TrayUI_StartTaskbar_Hook: Called");
    TrayUI_StartTaskbar_Original(pThis);

    if (g_unloading) {
        Wh_Log(L"TrayUI_StartTaskbar_Hook: Unloading, skipping");
        return;
    }

    HWND hWnd = FindCurrentProcessTaskbarWnd();
    if (!hWnd) {
        Wh_Log(L"TrayUI_StartTaskbar_Hook: Taskbar window not found");
        return;
    }

    Wh_Log(L"TrayUI_StartTaskbar_Hook: Reinitializing (hWnd=%p, prev=%p)", hWnd, g_taskbarWnd);
    // StartTaskbar replaces the XAML tree, so old mirror references no longer
    // have a live parent to detach from.
    g_mirrorPlayers.clear();
    g_playerGrid      = nullptr;
    g_injectionParent = nullptr;
    g_playerColumn    = -1;
    g_trackedElement  = nullptr;
    g_hasTrackedElementOriginalMargin = false;
    g_trackPosition   = L"";
    g_layoutUpdateToken = {};
    g_taskbarWnd = hWnd;

    g_cachedAlbumTitle.clear();
    g_cachedAlbumArtist.clear();
    g_cachedThumbnailBytes.clear();
    g_cachedPaletteHash = 0;
    g_cachedAppIconSize = -1;
    g_blurBgCache.Invalidate();

    g_hookFailCount = 0;

    StopScrollTimer();
    g_scrollDispatcherTimer = nullptr;
    g_scrollDispatcherTimerHasToken = false;

    if (g_settings.enableTitleScrolling || g_settings.enableArtistScrolling) {
        StartScrollTimer();
    }

    auto xamlRoot = GetTaskbarXamlRoot(hWnd);
    if (!xamlRoot) {
        Wh_Log(L"InjectPlayerGrid: Failed to get XAML root");
        return;
    }

    auto xamlRootContent = xamlRoot.Content().try_as<FrameworkElement>();
    if (!xamlRootContent) {
        Wh_Log(L"InjectPlayerGrid: Failed to get XAML root content");
        return;
    }

    ApplySettingsWithRetry(xamlRootContent);
}

static bool HookTaskbarDllSymbols() {
    static const wchar_t* const kCandidates[] = {
        L"taskbar.dll",
    };
    HMODULE h = nullptr;
    for (auto* name : kCandidates) {
        h = LoadLibraryExW(name, nullptr, LOAD_LIBRARY_SEARCH_SYSTEM32);
        if (h) break;
    }
    if (!h) { return FALSE; }
    WindhawkUtils::SYMBOL_HOOK taskbarDllHooks[] = {
        {{LR"(const CTaskBand::`vftable'{for `ITaskListWndSite'})"},
         &CTaskBand_ITaskListWndSite_vftable},
        {{LR"(const CSecondaryTaskBand::`vftable'{for `ITaskListWndSite'})"},
         &CSecondaryTaskBand_ITaskListWndSite_vftable},
        {{LR"(public: virtual class std::shared_ptr<class TaskbarHost> __cdecl CTaskBand::GetTaskbarHost(void)const )"},
         &CTaskBand_GetTaskbarHost_Original},
        {{LR"(public: virtual class std::shared_ptr<class TaskbarHost> __cdecl CSecondaryTaskBand::GetTaskbarHost(void)const )"},
         &CSecondaryTaskBand_GetTaskbarHost_Original},
        {{LR"(public: int __cdecl TaskbarHost::FrameHeight(void)const )"},
         &TaskbarHost_FrameHeight_Original},
        {{LR"(public: void __cdecl std::_Ref_count_base::_Decref(void))"},
         &Std_Ref_Decref_Original},
        {{LR"(public: virtual void __cdecl TrayUI::StartTaskbar(void))"},
         &TrayUI_StartTaskbar_Original,
         TrayUI_StartTaskbar_Hook},
    };
    if (!WindhawkUtils::HookSymbols(h, taskbarDllHooks, ARRAYSIZE(taskbarDllHooks))) {
        return FALSE;
    }
    return TRUE;
}

BOOL Wh_ModInit() {
    g_unloading = false;
    g_applyingSettings = false;
    g_hookInjectionInProgress = false;
    g_hookFailCount = 0;
    g_taskbarWnd = nullptr;
    g_needsUiUpdate = false;
    g_mirrorPlayers.clear();

    LoadSettings();

    if (!HookTaskbarDllSymbols()) {
        Wh_Log(L"Wh_ModInit: HookTaskbarDllSymbols failed");
        return FALSE;
    }
    return TRUE;
}

void Wh_ModAfterInit() {
    g_taskbarWnd = FindCurrentProcessTaskbarWnd();
    StartMediaThread();

    if (g_taskbarWnd) {
        RunFromWindowThread(g_taskbarWnd, [](void*) {
            g_cachedAlbumTitle.clear();
            g_cachedAlbumArtist.clear();
            g_cachedThumbnailBytes.clear();
            g_cachedPaletteHash = 0;
            g_cachedAppIconSize = -1;
            g_blurBgCache.Invalidate();
            ApplySettings();
            if (g_playerGrid) {
                UpdateVisibility();
                g_needsUiUpdate = true;
            }
        }, nullptr);
    }

    // Start polling and Discord only after the initial XAML injection so they
    // cannot contend with the visible startup path.
    StartTimerThread();
    if (g_timerUpdateEvent) SetEvent(g_timerUpdateEvent);
}

void Wh_ModUninit() {
    g_unloading = true;
    g_hookInjectionInProgress = false;
    g_hookFailCount = 0;

    StopTimerThread();
    StopMediaThread();
    g_settings.transparentTaskbar = false;
    ApplyTaskbarTransparencyToAll();
    if (g_taskbarWnd) {
        RunFromWindowThread(g_taskbarWnd, [](void*) { DestroyVolumePopup(); }, nullptr);
    } else {
        DestroyVolumePopup();
    }

    if (g_taskbarWnd)
        RunFromWindowThread(g_taskbarWnd, [](void*) {
            RemovePlayerGrid();
            g_mediaHoverBrush   = nullptr;
            g_mediaPressedBrush = nullptr;
            g_playerHoverBrush  = nullptr;
            g_playerPressedBrush = nullptr;
            g_playerBorderBrush  = nullptr;
            g_playerBorderPressedBrush = nullptr;
        }, nullptr);
    else {
        g_mediaHoverBrush   = nullptr;
        g_mediaPressedBrush = nullptr;
        g_playerHoverBrush  = nullptr;
        g_playerPressedBrush = nullptr;
        g_playerBorderBrush  = nullptr;
        g_playerBorderPressedBrush = nullptr;
    }

    if (g_volumePopupBrush) {
        DeleteObject(g_volumePopupBrush);
        g_volumePopupBrush = nullptr;
    }
}

void Wh_ModSettingsChanged() {
    g_applyingSettings = true;

    StopTimerThread();

    // Values selected from the compact context menu are temporary overrides.
    // Applying the full Windhawk settings makes the configured values authoritative.
    Wh_SetIntValue(L"quickPositionPreset", -1);
    Wh_SetIntValue(L"quickTaskbarMode", -1);
    Wh_SetIntValue(L"quickTaskbarNumber", -1);
    Wh_SetIntValue(L"quickBackground", -1);
    Wh_SetIntValue(L"quickTransparentTaskbar", -1);

    HWND previousTaskbarWnd = g_taskbarWnd;
    LoadSettings();

    HWND hWnd = FindCurrentProcessTaskbarWnd();
    if (!hWnd) {
        g_applyingSettings = false;
        StartTimerThread();
        return;
    }

    if (previousTaskbarWnd && previousTaskbarWnd != hWnd) {
        Wh_Log(L"Wh_ModSettingsChanged: Moving player from taskbar %p to %p",
               previousTaskbarWnd, hWnd);
        RunFromWindowThread(previousTaskbarWnd, [](void*) {
            try {
                RemovePlayerGrid();
            } catch (...) {
                g_playerGrid = nullptr;
                g_injectionParent = nullptr;
                g_playerColumn = -1;
            }
        }, nullptr);
    }
    g_taskbarWnd = hWnd;

    DWORD threadId = GetWindowThreadProcessId(hWnd, nullptr);
    if (threadId && threadId != GetCurrentThreadId()) {
        struct WorkData { HWND hWnd; };
        WorkData* data = new WorkData{hWnd};

        HANDLE hThread = CreateThread(nullptr, 0, [](LPVOID param) WINAPI -> DWORD {
            WorkData* data2 = (WorkData*)param;
            RunFromWindowThread(data2->hWnd, [](void*) {
                try {
                    RemovePlayerGrid();
                    g_cachedAlbumTitle.clear();
                    g_cachedAlbumArtist.clear();
                    g_cachedThumbnailBytes.clear();
                    g_cachedPaletteHash = 0;
                    g_blurBgCache.Invalidate();
                    g_applyingSettings = false;
                    if (!g_unloading) {
                        InjectPlayerGrid();
                        g_needsUiUpdate = true;
                    }
                } catch (...) {
                    Wh_Log(L"Wh_ModSettingsChanged: Exception during RemovePlayerGrid/InjectPlayerGrid");
                    g_applyingSettings = false;
                    g_playerGrid = nullptr;
                    g_injectionParent = nullptr;
                }
            }, nullptr);
            return 0;
        }, data, 0, nullptr);

        if (hThread) {
            WaitForSingleObject(hThread, 2000);
            CloseHandle(hThread);
        }
        delete data;
    } else {
        try {
            RemovePlayerGrid();
            g_cachedAlbumTitle.clear();
            g_cachedAlbumArtist.clear();
            g_cachedThumbnailBytes.clear();
            g_cachedPaletteHash = 0;
            g_blurBgCache.Invalidate();
            g_applyingSettings = false;
            if (!g_unloading) {
                InjectPlayerGrid();
                g_needsUiUpdate = true;
            }
        } catch (...) {
            Wh_Log(L"Wh_ModSettingsChanged: Exception during RemovePlayerGrid/InjectPlayerGrid (same thread)");
            g_applyingSettings = false;
            g_playerGrid = nullptr;
            g_injectionParent = nullptr;
        }
    }

    StartTimerThread();
}
