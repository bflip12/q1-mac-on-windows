# Setup guide

About 30 minutes. Assumes Windows 11, the keyboard on a cable, and Chrome or Edge.

## 1. Keyboard

1. Slide the side switch to **Win**.
2. Flash the firmware: see `firmware/README.md`.
3. Load the VIA definition and set your indicator colours.

No-firmware alternative: in VIA (stock firmware), set layer 2's top row to F13, F14, LGUI(Tab), LGUI, backlight down/up, previous, play, next, mute, volume down/up, and layer 3's to F1–F12. You get everything except a working Fn lock and the indicators.

## 2. Apps

- **AutoHotkey v2** from autohotkey.com. Keep the UI Access option on.
- **PowerToys**, installed for all users: `winget install --id Microsoft.PowerToys --scope machine` in an admin terminal. If a per-user copy exists, uninstall it from Settings → Apps first, as the normal user; an elevated process can't remove it.
- **Twinkle Tray** from the Microsoft Store (per user).

## 3. Mac shortcuts script

1. Put `mac-keys.ahk`, `setup-all-users.ahk` and `setup-admin-windows.ahk` in one folder.
2. Run `setup-all-users.ahk` and approve the admin prompt. It copies the script to `C:\Users\Public\Scripts`, adds it to the all-users Startup folder and starts it.
3. Run `setup-admin-windows.ahk` and approve. It points the startup shortcut at `AutoHotkey64_UIA.exe` so the shortcuts also work in admin windows; if that build is missing, it creates a scheduled task instead.
4. To edit later: change `C:\Users\Public\Scripts\mac-keys.ahk`, then tray icon → Reload Script.

In games listed in the script's `Games` group, the shortcuts are off, tapping Option/⌘ alone does nothing, and ⌘+Space is swallowed so the launcher doesn't pop over the game.

## 4. Per-user settings

- PowerToys → Command Palette: leave the activation shortcut on its default, **Win+Alt+Space**. The script maps ⌘+Space to it, so nothing needs setting per user.
- Twinkle Tray → enable DDC/CI on the monitor, then Hotkeys: add F13 → adjust −10 (all displays) and F14 → +10 (press F1/F2 to record them).

## 5. Test

⌘+C/V, ⌘+←/→, Option+←/→, ⌘+Backspace, ⌘+Space, ⌘+click in Chrome (opens a background tab), F1/F2 brightness, F7–F12 media, Fn+Home lock (top row lights up), Caps Lock light, and in your game: F-keys with the lock on, no Start menu on Option.

## Known quirks

- ⌘+Backspace selects to line start and then deletes, so you may see a brief highlight; Windows has no native "delete to line start".
- Other people on the PC get the Mac mappings too; they can pause them from the tray icon (Suspend Hotkeys).
- If the board's RGB is switched off entirely, the indicators don't show.
