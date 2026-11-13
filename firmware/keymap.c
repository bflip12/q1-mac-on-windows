// SPDX-License-Identifier: GPL-2.0-or-later
/* Keychron Q1 V2 ANSI knob: custom keymap
 *
 * Based on Keychron's VIA keymap, with:
 *  - the Mac-style Windows layout baked in as the default (Mac-style top row, keycap-matched right column,
 *    bottom-right keys matched to Mac keycaps: Cmd, Option, Fn; Keychron's stock map has Cmd, Fn, Ctrl)
 *  - Double-tap Fn toggles Fn lock (on by default, switchable in VIA)
 *  - FN_LOCK custom keycode (VIA "Custom" tab), default on Fn+Home. Keeps the Fn layer on until
 *    toggled off; holding/releasing Fn doesn't cancel it. Windows mode only.
 *  - Fn-lock indicator (any mix of: top row, the Fn Lock key, the Fn key) and Caps Lock indicator, colours/brightness
 *    editable in VIA (custom "Indicators" menu, saved on the keyboard)
 *  - Fn+Esc held 2 s = jump to bootloader (update mode) without wiping settings; short press = Esc;
 *    while Fn-locked, Esc is always plain Esc
 *  - Fn lock can be switched by the PC over VIA's raw HID channel (value id 8) for auto-lock in games
 */

#include QMK_KEYBOARD_H

enum layers {
    MAC_BASE,
    MAC_FN,
    WIN_BASE,
    WIN_FN,
};

enum custom_keycodes {
    FN_LOCK = QK_KB_0, // first entry of customKeycodes in the VIA definition
};

#define KC_TASK LGUI(KC_TAB)
#define KC_FLXP LGUI(KC_E)

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [MAC_BASE] = LAYOUT_ansi_82(
        KC_ESC,   KC_BRID,  KC_BRIU,  KC_MCTL,  KC_LPAD,  RGB_VAD,  RGB_VAI,  KC_MPRV,  KC_MPLY,  KC_MNXT,  KC_MUTE,  KC_VOLD,    KC_VOLU,  KC_DEL,             KC_MUTE,
        KC_GRV,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,    KC_EQL,   KC_BSPC,            KC_HOME,
        KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,    KC_RBRC,  KC_BSLS,            KC_PGUP,
        KC_CAPS,  KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,              KC_ENT,             KC_PGDN,
        KC_LSFT,            KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,              KC_RSFT,  KC_UP,
        KC_LCTL,  KC_LOPT,  KC_LCMD,                                KC_SPC,                                 KC_RCMD,  KC_ROPT,  MO(MAC_FN), KC_LEFT,  KC_DOWN,  KC_RGHT),

    [MAC_FN] = LAYOUT_ansi_82(
        QK_BOOT,  KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,     KC_F12,   _______,            RGB_TOG,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,    _______,  _______,            _______,
        RGB_TOG,  RGB_MOD,  RGB_VAI,  RGB_HUI,  RGB_SAI,  RGB_SPI,  _______,  _______,  _______,  _______,  _______,  _______,    _______,  _______,            _______,
        _______,  RGB_RMOD, RGB_VAD,  RGB_HUD,  RGB_SAD,  RGB_SPD,  _______,  _______,  _______,  _______,  _______,  _______,              _______,            _______,
        _______,            _______,  _______,  _______,  _______,  _______,  NK_TOGG,  _______,  _______,  _______,  _______,              _______,  _______,
        _______,  _______,  _______,                                _______,                                _______,  _______,    _______,  _______,  _______,  _______),

    // Windows base: F1/F2 = F13/F14 (Twinkle Tray brightness), F3 Task View, F4 Start, F5/F6 backlight, F7-F12 media
    [WIN_BASE] = LAYOUT_ansi_82(
        KC_ESC,   KC_F13,   KC_F14,   KC_TASK,  KC_LGUI,  RGB_VAD,  RGB_VAI,  KC_MPRV,  KC_MPLY,  KC_MNXT,  KC_MUTE,  KC_VOLD,    KC_VOLU,  KC_DEL,             KC_MUTE,
        KC_GRV,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,    KC_EQL,   KC_BSPC,            KC_HOME,
        KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,    KC_RBRC,  KC_BSLS,            KC_PGUP,
        KC_CAPS,  KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,              KC_ENT,             KC_PGDN,
        KC_LSFT,            KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,              KC_RSFT,  KC_UP,
        KC_LCTL,  KC_LGUI,  KC_LALT,                                KC_SPC,                                 KC_RALT,  KC_RGUI,  MO(WIN_FN), KC_LEFT,  KC_DOWN,  KC_RGHT),

    // Windows Fn (also what Fn lock keeps on): plain F1-F12, Fn+Home = Fn lock, Fn+Esc = update mode
    [WIN_FN] = LAYOUT_ansi_82(
        QK_BOOT,  KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,     KC_F12,   _______,            _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,    _______,  _______,            FN_LOCK,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,    _______,  _______,            _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,              _______,            _______,
        _______,            _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,              _______,  _______,
        _______,  _______,  _______,                                _______,                                _______,  _______,    _______,  _______,  _______,  _______),
};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [MAC_BASE] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [MAC_FN]   = { ENCODER_CCW_CW(RGB_VAD, RGB_VAI)},
    [WIN_BASE] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [WIN_FN]   = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU)}   // knob stays volume while Fn-locked
};
#endif
// clang-format on

/* ---------- Saved indicator settings ---------- */

#define LIGHT_TOP_ROW  (1 << 0)
#define LIGHT_LOCK_KEY (1 << 1)
#define LIGHT_FN_KEY   (1 << 2)

typedef struct PACKED {
    uint8_t caps_on;     // 1 = light Caps Lock key when Caps Lock is on
    uint8_t caps_h, caps_s, caps_v;
    uint8_t lock_on;     // 1 = show Fn-lock indicator
    uint8_t lock_h, lock_s, lock_v;
    uint8_t lock_parts;  // bit 0 = top row (F1-F12), bit 1 = Fn Lock key(s), bit 2 = Fn key(s)
    uint8_t dbl_tap_fn;  // 1 = double-tap Fn toggles Fn lock
    uint8_t reserved[2];
} indicator_cfg_t;

_Static_assert(sizeof(indicator_cfg_t) == EECONFIG_USER_DATA_SIZE, "EECONFIG_USER_DATA_SIZE mismatch");

static indicator_cfg_t cfg;

static void cfg_defaults(void) {
    cfg = (indicator_cfg_t){
        .caps_on = 1, .caps_h = 128, .caps_s = 255, .caps_v = 255,  // cyan
        .lock_on = 1, .lock_h = 128, .lock_s = 255, .lock_v = 255,  // cyan (contrasts with red backlight)
        .lock_parts = LIGHT_TOP_ROW | LIGHT_FN_KEY,
        .dbl_tap_fn = 1,
    };
}

void eeconfig_init_user_datablock(void) {
    cfg_defaults();
    eeconfig_update_user_datablock(&cfg);
}

/* ---------- Fn lock ---------- */

static bool fn_locked = false;

static bool win_mode(void) {
    return get_highest_layer(default_layer_state) == WIN_BASE;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    // Releasing Fn (MO) turns WIN_FN off; while locked, put it straight back.
    if (fn_locked && win_mode()) {
        state |= ((layer_state_t)1 << WIN_FN);
    }
    return state;
}

static void set_fn_lock(bool on) {
    if (on && !win_mode()) return; // Windows mode only
    fn_locked = on;
    if (on) {
        layer_state_set(layer_state);
    } else {
        layer_off(WIN_FN);
    }
}

bool dip_switch_update_user(uint8_t index, bool active) {
    // active = Windows mode. Leaving Windows mode drops the lock.
    if (index == 0 && !active && fn_locked) {
        fn_locked = false;
        layer_off(WIN_FN);
    }
    return true;
}

/* Double-tap Fn: two quick taps of Fn (no other key in between) toggle the lock. */
#define FN_TAP_MAX_MS   200 // a tap = Fn held shorter than this
#define FN_DOUBLE_GAP_MS 300 // second tap must start within this of the first tap's release

static uint16_t fn_press_time   = 0;
static uint16_t fn_last_tap_end = 0;
static bool     fn_tap_pending  = false; // a qualifying first tap happened
static bool     fn_interrupted  = false; // another key was pressed while Fn was down

/* Fn+Esc = update mode, made safe:
 *  - while Fn lock is on, Esc is always plain Esc (the lock keeps the Fn layer on, so Esc alone
 *    would otherwise reach the bootloader key)
 *  - otherwise Fn+Esc must be HELD for 2 seconds; a short press sends Esc */
#define BOOT_HOLD_MS 2000
static uint16_t boot_press_time = 0;
static bool     boot_as_esc     = false;

static bool handle_boot_key(keyrecord_t *record) {
    if (record->event.pressed) {
        boot_as_esc = fn_locked;
        if (boot_as_esc) {
            register_code(KC_ESC);
        } else {
            boot_press_time = timer_read();
        }
    } else {
        if (boot_as_esc) {
            unregister_code(KC_ESC);
        } else if (timer_elapsed(boot_press_time) >= BOOT_HOLD_MS) {
            reset_keyboard(); // jump to bootloader
        } else {
            tap_code(KC_ESC);
        }
    }
    return false;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (keycode == QK_BOOT) {
        return handle_boot_key(record);
    }
    if (keycode == FN_LOCK) {
        if (record->event.pressed) set_fn_lock(!fn_locked);
        return false;
    }

    if (keycode == MO(WIN_FN)) {
        if (record->event.pressed) {
            fn_interrupted = false;
            fn_press_time  = timer_read();
            if (cfg.dbl_tap_fn && fn_tap_pending && timer_elapsed(fn_last_tap_end) < FN_DOUBLE_GAP_MS) {
                fn_tap_pending = false;
                set_fn_lock(!fn_locked);
                fn_interrupted = true; // this press was used up; don't count it as a new first tap
            }
        } else {
            if (!fn_interrupted && timer_elapsed(fn_press_time) < FN_TAP_MAX_MS) {
                fn_tap_pending  = true;
                fn_last_tap_end = timer_read();
            } else {
                fn_tap_pending = false;
            }
        }
        return true; // Fn still works as a normal hold key
    }

    if (record->event.pressed) {
        fn_interrupted = true;  // Fn+key combos are not taps
        fn_tap_pending = false;
    }
    return true;
}

/* ---------- Where are the Fn Lock and Fn keys? (both can be moved in VIA) ---------- */

#define MAX_FOUND 4
typedef struct {
    uint8_t leds[MAX_FOUND];
    uint8_t count;
} found_keys_t;

static found_keys_t lock_keys, fn_keys;
static uint32_t     key_scan_timer = 0;

static void find_keys(found_keys_t *out, uint8_t layer_from, uint8_t layer_to, uint16_t keycode) {
    out->count = 0;
    for (uint8_t layer = layer_from; layer <= layer_to; layer++) {
        for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
            for (uint8_t col = 0; col < MATRIX_COLS; col++) {
                if (keymap_key_to_keycode(layer, (keypos_t){.row = row, .col = col}) != keycode) continue;
                uint8_t led = g_led_config.matrix_co[row][col];
                if (led == NO_LED || out->count >= MAX_FOUND) continue;
                out->leds[out->count++] = led;
            }
        }
    }
}

static void scan_keys(void) {
    find_keys(&lock_keys, WIN_BASE, WIN_FN, FN_LOCK);
    find_keys(&fn_keys, WIN_BASE, WIN_BASE, MO(WIN_FN));
}

void keyboard_post_init_user(void) {
    if (!eeconfig_is_user_datablock_valid()) {
        eeconfig_init_user_datablock(); // first boot after flashing: write defaults
    }
    eeconfig_read_user_datablock(&cfg);
    scan_keys();
}

void housekeeping_task_user(void) {
    if (timer_elapsed32(key_scan_timer) > 1000) {
        key_scan_timer = timer_read32();
        scan_keys();
    }
}

/* ---------- Indicators ---------- */

static RGB cfg_rgb(uint8_t h, uint8_t s, uint8_t v) {
    return hsv_to_rgb((HSV){.h = h, .s = s, .v = v});
}

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    if (cfg.caps_on && host_keyboard_led_state().caps_lock) {
        RGB c = cfg_rgb(cfg.caps_h, cfg.caps_s, cfg.caps_v);
        RGB_MATRIX_INDICATOR_SET_COLOR(CAPS_LOCK_LED_INDEX, c.r, c.g, c.b);
    }
    if (fn_locked && cfg.lock_on) {
        RGB c = cfg_rgb(cfg.lock_h, cfg.lock_s, cfg.lock_v);
        if (cfg.lock_parts & LIGHT_TOP_ROW) {
            for (uint8_t col = 1; col <= 12; col++) {
                uint8_t led = g_led_config.matrix_co[0][col];
                if (led != NO_LED) RGB_MATRIX_INDICATOR_SET_COLOR(led, c.r, c.g, c.b);
            }
        }
        if (cfg.lock_parts & LIGHT_LOCK_KEY) {
            for (uint8_t i = 0; i < lock_keys.count; i++) RGB_MATRIX_INDICATOR_SET_COLOR(lock_keys.leds[i], c.r, c.g, c.b);
        }
        if (cfg.lock_parts & LIGHT_FN_KEY) {
            for (uint8_t i = 0; i < fn_keys.count; i++) RGB_MATRIX_INDICATOR_SET_COLOR(fn_keys.leds[i], c.r, c.g, c.b);
        }
    }
    return false;
}

/* ---------- VIA custom menu (channel 0) ---------- */

enum indicator_value_ids {
    id_caps_on     = 1,
    id_caps_color  = 2,
    id_caps_bright = 3,
    id_lock_on     = 4,
    id_lock_color  = 5,
    id_lock_bright = 6,
    id_light_top   = 7,
    id_lock_state  = 8, // live Fn-lock state (not saved); also used by the PC helper for auto-lock
    id_light_lock  = 9,
    id_light_fn    = 10,
    id_dbl_tap_fn  = 11,
};

static void indicator_set(uint8_t *d) {
    switch (d[0]) {
        case id_caps_on:     cfg.caps_on = d[1] ? 1 : 0; break;
        case id_caps_color:  cfg.caps_h = d[1]; cfg.caps_s = d[2]; break;
        case id_caps_bright: cfg.caps_v = d[1]; break;
        case id_lock_on:     cfg.lock_on = d[1] ? 1 : 0; break;
        case id_lock_color:  cfg.lock_h = d[1]; cfg.lock_s = d[2]; break;
        case id_lock_bright: cfg.lock_v = d[1]; break;
        case id_light_top:   cfg.lock_parts = d[1] ? (cfg.lock_parts | LIGHT_TOP_ROW) : (cfg.lock_parts & ~LIGHT_TOP_ROW); break;
        case id_light_lock:  cfg.lock_parts = d[1] ? (cfg.lock_parts | LIGHT_LOCK_KEY) : (cfg.lock_parts & ~LIGHT_LOCK_KEY); break;
        case id_dbl_tap_fn:  cfg.dbl_tap_fn = d[1] ? 1 : 0; break;
        case id_light_fn:    cfg.lock_parts = d[1] ? (cfg.lock_parts | LIGHT_FN_KEY) : (cfg.lock_parts & ~LIGHT_FN_KEY); break;
        case id_lock_state:  set_fn_lock(d[1] != 0); break;
    }
}

static void indicator_get(uint8_t *d) {
    switch (d[0]) {
        case id_caps_on:     d[1] = cfg.caps_on; break;
        case id_caps_color:  d[1] = cfg.caps_h; d[2] = cfg.caps_s; break;
        case id_caps_bright: d[1] = cfg.caps_v; break;
        case id_lock_on:     d[1] = cfg.lock_on; break;
        case id_lock_color:  d[1] = cfg.lock_h; d[2] = cfg.lock_s; break;
        case id_lock_bright: d[1] = cfg.lock_v; break;
        case id_light_top:   d[1] = (cfg.lock_parts & LIGHT_TOP_ROW) ? 1 : 0; break;
        case id_light_lock:  d[1] = (cfg.lock_parts & LIGHT_LOCK_KEY) ? 1 : 0; break;
        case id_dbl_tap_fn:  d[1] = cfg.dbl_tap_fn; break;
        case id_light_fn:    d[1] = (cfg.lock_parts & LIGHT_FN_KEY) ? 1 : 0; break;
        case id_lock_state:  d[1] = fn_locked ? 1 : 0; break;
    }
}

void via_custom_value_command_kb(uint8_t *data, uint8_t length) {
    // data = [ command_id, channel_id, value_id, value_data... ]
    uint8_t *command_id = &data[0];
    uint8_t *channel_id = &data[1];
    uint8_t *value      = &data[2];

    if (*channel_id != id_custom_channel) {
        *command_id = id_unhandled;
        return;
    }
    switch (*command_id) {
        case id_custom_set_value: indicator_set(value); break;
        case id_custom_get_value: indicator_get(value); break;
        case id_custom_save:      eeconfig_update_user_datablock(&cfg); break;
        default:                  *command_id = id_unhandled; break;
    }
}
