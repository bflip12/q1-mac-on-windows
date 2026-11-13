# Firmware

Keyboard: Keychron Q1 V2, ANSI, knob (`keychron/q1v2/ansi_encoder`, USB 3434:0107).
Source tree: [Keychron/qmk_firmware](https://github.com/Keychron/qmk_firmware), branch `playground`.

## Build

Easiest: download the `.bin` from this repo's GitHub Releases (built by `.github/workflows/build-firmware.yml`). To build it yourself:

```sh
git clone -b playground --depth 1 https://github.com/Keychron/qmk_firmware.git
cd qmk_firmware && git submodule update --init --recursive --depth 1
pip install qmk && pip install -r requirements.txt
# toolchain: gcc-arm-none-eabi, libnewlib-arm-none-eabi, dfu-util (for dfu-suffix)
mkdir -p keyboards/keychron/q1v2/ansi_encoder/keymaps/mac_fnlock
cp /path/to/this/repo/firmware/{keymap.c,config.h,rules.mk} keyboards/keychron/q1v2/ansi_encoder/keymaps/mac_fnlock/
make keychron/q1v2/ansi_encoder:mac_fnlock
# -> .build/keychron_q1v2_ansi_encoder_mac_fnlock.bin
```

## Flash (Windows)

1. Install [QMK Toolbox](https://github.com/qmk/qmk_toolbox/releases); accept the driver install.
2. Close any VIA / Keychron Launcher tabs. Open the `.bin` in QMK Toolbox.
3. Enter update mode: unplug, hold **Esc**, plug in (this also wipes saved settings, which is fine before a flash). If nothing appears, pull the spacebar keycap and hold the reset button underneath while plugging in. Once this firmware is installed, **hold Fn+Esc for 2 seconds** (with Fn lock off) to do it without the wipe.
4. Click **Flash**. The keyboard restarts when done.

The layout is compiled in, so a wipe comes back to it. Lighting effect and colour return to Keychron defaults.

## VIA

usevia.app → Settings → **Show Design tab** → Design → load `via/q1-via-definition.json`. Then:

- **Configure → Indicators:** Caps Lock (on/off, colour, brightness) and Fn Lock (live on/off, double-tap Fn on/off, which parts light up — F1–F12, Fn key, Fn Lock key — colour, brightness).
- **Custom** key tab: **FnLk** — drag it to any key or layer to move the Fn-lock toggle.

The Keychron Launcher can't load custom definitions, so it won't show these extras.

## How Fn lock works

Holding Fn turns layer `WIN_FN` on with `MO()`. A plain `TG()` on an Fn combo cancels itself (releasing Fn turns the same layer off), so this keymap keeps its own `fn_locked` flag and re-adds `WIN_FN` in `layer_state_set_user()` while it's set. Windows mode only; switching to Mac mode clears it.

## PC control (auto-lock)

The lock state is VIA custom value channel 0, id 8. A host can set it over raw HID (usage page 0xFF60) with the 32-byte report `[0x07, 0x00, 0x08, 1|0]` — e.g. to lock automatically while a game has focus.
