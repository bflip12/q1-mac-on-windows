# Keychron Q1 V2: Mac habits on Windows

A sketch for using a Keychron Q1 V2 (ANSI, knob) on Windows with Mac muscle memory, without giving up gaming.

- **Firmware (QMK):** Mac-style top row in Windows mode, a real Fn lock (double-tap Fn, or Fn+Home; both configurable in VIA), lit indicators for Fn lock and Caps Lock with colours you set in VIA, hold Fn+Esc to enter update mode.
- **AutoHotkey v2 script:** ⌘+C/V/Z…, ⌘/Option + arrows and Backspace like macOS, window snapping, tab switching. Turns itself off in World of Warcraft (add your own games) and switches the keyboard’s Fn lock on while the game has focus; works in admin windows, runs for every user.
- **Companion apps:** PowerToys Command Palette on ⌘+Space (the script maps it to the palette's default shortcut), Twinkle Tray for external-monitor brightness on F1/F2.

Status: working on the author's machine. The firmware compiles cleanly; flash at your own risk (you can always reflash Keychron's stock firmware).

**Download (latest release):** [q1-mac-firmware.bin](https://github.com/bflip12/q1-mac-on-windows/releases/latest/download/q1-mac-firmware.bin) · [q1-via-definition.json](https://github.com/bflip12/q1-mac-on-windows/releases/latest/download/q1-via-definition.json) · [all releases](https://github.com/bflip12/q1-mac-on-windows/releases). Flashing steps are in [`firmware/README.md`](firmware/README.md#flash-windows).

## What's here

| Path | What |
| --- | --- |
| `firmware/` | QMK keymap (`keymap.c`, `config.h`, `rules.mk`) and build/flash notes. Only the keymap lives here; CI builds it on top of Keychron's QMK tree |
| `.github/workflows/build-firmware.yml` | Builds the `.bin` on every change; tagged versions attach it to a Release |
| `via/q1-via-definition.json` | VIA definition: adds the Indicators menu and the Fn Lock custom key |
| `windows/mac-keys.ahk` | The Mac-shortcuts script |
| `windows/setup-all-users.ahk` | One-time: copies the script to `C:\Users\Public\Scripts` and starts it for all users |
| `windows/setup-admin-windows.ahk` | One-time: starts the script through AutoHotkey's UI Access build so it works in admin windows |
| `docs/setup-guide.md` | Full setup, start to finish |

## Key map (Windows mode)

| Key | Plain | With Fn / Fn lock |
| --- | --- | --- |
| F1 / F2 | F13 / F14 → brightness via Twinkle Tray | F1 / F2 |
| F3 / F4 | Task View / Start | F3 / F4 |
| F5 / F6 | Backlight down / up | F5 / F6 |
| F7–F9 | Previous / Play-pause / Next | F7–F9 |
| F10–F12 | Mute / Volume down / Volume up | F10–F12 |
| Home | Home | Fn lock on/off |
| Fn (double-tap) | Nothing | Fn lock on/off (toggle in VIA) |
| Esc | Esc | Hold 2 s: update mode (plain Esc while Fn lock is on) |
| Knob | Volume, press = mute | same |

Physical modifiers in Windows mode: ⌘ = Alt, Option = Win, Control = Ctrl. The script turns ⌘ combos into Ctrl combos.

## Decisions

- 2026-11-12: Firmware binaries aren't committed. CI builds them from `firmware/` on Keychron's `playground` branch and attaches them to tagged releases, so every `.bin` matches published source.
- 2026-11-12: Only the keymap lives here; Keychron's QMK tree is cloned at build time instead of forked, and each release notes the exact upstream commit.
- 2026-11-12: GPL-2.0-or-later for everything, since the firmware is derived from QMK.

## License

Firmware files are derived from Keychron's QMK code and are GPL-2.0-or-later, like QMK. The rest is offered under the same license. See [LICENSE](LICENSE).
