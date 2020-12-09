#include QMK_KEYBOARD_H
#include "md_rgb_matrix.h"

enum alt_keycodes {
    U_T_AUTO = SAFE_RANGE, //USB Extra Port Toggle Auto Detect / Always Active
    U_T_AGCR,              //USB Toggle Automatic GCR control
    DBG_TOG,               //DEBUG Toggle On / Off
    DBG_MTRX,              //DEBUG Toggle Matrix Prints
    DBG_KBD,               //DEBUG Toggle Keyboard Prints
    DBG_MOU,               //DEBUG Toggle Mouse Prints
    MD_BOOT,               //Restart into bootloader after hold timeout
};

enum LAYERS {
    DEFAULT = 0,
    TYPING,
    MAC,
    MODIFIERS,
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [DEFAULT] = LAYOUT_65_ansi_blocker(
        KC_ESC,               KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,       KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS,         KC_EQL,  KC_BSPC, KC_DEL,  \
        KC_TAB,               KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,       KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC,         KC_RBRC, KC_BSLS, KC_HOME, \
        KC_CAPS,              KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,       KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,                  KC_ENT,  KC_PGUP, \
        KC_LSFT,              KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,       KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,                  KC_UP,   KC_PGDN, \
        KC_LCTL,              KC_LGUI, KC_LALT,                            KC_SPC,                                KC_RALT, MO(MODIFIERS),   KC_LEFT, KC_DOWN, KC_RGHT  \
    ),
    [TYPING] = LAYOUT_65_ansi_blocker(
        KC_GRV,               KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,       KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS,         KC_EQL,  KC_BSPC, KC_DEL,  \
        KC_TAB,               KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,       KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC,         KC_RBRC, KC_BSLS, KC_HOME, \
        MT(MOD_LCTL, KC_ESC), KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,       KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,                  KC_ENT,  KC_PGUP, \
        KC_LSFT,              KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,       KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,                  KC_UP,   KC_PGDN, \
        KC_LCTL,              KC_LGUI, KC_LALT,                            KC_SPC,                                KC_RALT, MO(MODIFIERS),   KC_LEFT, KC_DOWN, KC_RGHT  \
    ),
    [MAC] = LAYOUT_65_ansi_blocker(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______, \
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______, \
        _______, KC_LALT, KC_LGUI,                            _______,                            _______, _______, _______, _______, _______  \
    ),
    [MODIFIERS] = LAYOUT_65_ansi_blocker(
        KC_ESC,               KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,      KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,          KC_F12,  _______, KC_MUTE, \
        _______,              RGB_SPD, RGB_VAI, RGB_SPI, RGB_HUI, RGB_SAI, _______,    U_T_AUTO,U_T_AGCR,_______, KC_PSCR, KC_SLCK,         KC_PAUS, _______, KC_END, \
        _______,              RGB_RMOD,RGB_VAD, RGB_MOD, RGB_HUD, RGB_SAD, _______,    _______, _______, _______, _______, _______,                  _______, KC_VOLU, \
        _______,              RGB_TOG, _______, _______, _______, MD_BOOT, NK_TOGG,    DBG_TOG, _______, _______, _______, _______,                  KC_PGUP, KC_VOLD, \
        _______,              _______, _______,                            TG(TYPING),                            TG(MAC), _______,         KC_HOME, KC_PGDN, KC_END  \
    ),
    /*
    [X] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______, \
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______, \
        _______, _______, _______,                            _______,                            _______, _______, _______, _______, _______  \
    ),
    */
};

#define MODS_SHIFT  (get_mods() & MOD_BIT(KC_LSHIFT) || get_mods() & MOD_BIT(KC_RSHIFT))
#define MODS_CTRL  (get_mods() & MOD_BIT(KC_LCTL) || get_mods() & MOD_BIT(KC_RCTRL))
#define MODS_ALT  (get_mods() & MOD_BIT(KC_LALT) || get_mods() & MOD_BIT(KC_RALT))

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    static uint32_t key_timer;

    switch (keycode) {
        case U_T_AUTO:
            if (record->event.pressed && MODS_SHIFT && MODS_CTRL) {
                TOGGLE_FLAG_AND_PRINT(usb_extra_manual, "USB extra port manual mode");
            }
            return false;
        case U_T_AGCR:
            if (record->event.pressed && MODS_SHIFT && MODS_CTRL) {
                TOGGLE_FLAG_AND_PRINT(usb_gcr_auto, "USB GCR auto mode");
            }
            return false;
        case DBG_TOG:
            if (record->event.pressed) {
                TOGGLE_FLAG_AND_PRINT(debug_enable, "Debug mode");
            }
            return false;
        case DBG_MTRX:
            if (record->event.pressed) {
                TOGGLE_FLAG_AND_PRINT(debug_matrix, "Debug matrix");
            }
            return false;
        case DBG_KBD:
            if (record->event.pressed) {
                TOGGLE_FLAG_AND_PRINT(debug_keyboard, "Debug keyboard");
            }
            return false;
        case DBG_MOU:
            if (record->event.pressed) {
                TOGGLE_FLAG_AND_PRINT(debug_mouse, "Debug mouse");
            }
            return false;
        case MD_BOOT:
            if (record->event.pressed) {
                key_timer = timer_read32();
            } else {
                if (timer_elapsed32(key_timer) >= 500) {
                    reset_keyboard();
                }
            }
            return false;
        case RGB_TOG:
            if (record->event.pressed) {
              switch (rgb_matrix_get_flags()) {
                case LED_FLAG_ALL: {
                    rgb_matrix_set_flags(LED_FLAG_KEYLIGHT | LED_FLAG_MODIFIER | LED_FLAG_INDICATOR);
                    rgb_matrix_set_color_all(0, 0, 0);
                  }
                  break;
                case (LED_FLAG_KEYLIGHT | LED_FLAG_MODIFIER | LED_FLAG_INDICATOR): {
                    rgb_matrix_set_flags(LED_FLAG_UNDERGLOW);
                    rgb_matrix_set_color_all(0, 0, 0);
                  }
                  break;
                case LED_FLAG_UNDERGLOW: {
                    rgb_matrix_set_flags(LED_FLAG_NONE);
                    rgb_matrix_disable_noeeprom();
                  }
                  break;
                default: {
                    rgb_matrix_set_flags(LED_FLAG_ALL);
                    rgb_matrix_enable_noeeprom();
                  }
                  break;
              }
            }
            return false;
        default:
            return true; //Process all other keycodes normally
    }
}

#define RGB(i) led_buffer[i]
#define ANIM_LENGTH 1500

#define LAYER_KEY_COUNT 2

static uint8_t layer_keys[LAYER_KEY_COUNT][2] = {
  {MAC, 62},
  {TYPING, 61}
};
static uint16_t anim_timer;
static bool showing_mods = false;
static RGB prev_colors[LAYER_KEY_COUNT];

layer_state_t layer_state_set_user(layer_state_t state) {
  if (layer_state_cmp(state, MODIFIERS) && showing_mods == false) {
    showing_mods = true;
    anim_timer = timer_read();
    for (uint8_t i = 0; i < LAYER_KEY_COUNT; i ++) {
      prev_colors[i].r = RGB(layer_keys[i][1]).r;
      prev_colors[i].g = RGB(layer_keys[i][1]).g;
      prev_colors[i].b = RGB(layer_keys[i][1]).b;
    }
  }
  if (showing_mods == true) {
    for (uint8_t i = 0; i < LAYER_KEY_COUNT; i ++) {
      if (!layer_state_cmp(state, MODIFIERS) || !layer_state_cmp(state, layer_keys[i][0])) {
        RGB(layer_keys[i][1]).r = prev_colors[i].r ;
        RGB(layer_keys[i][1]).g = prev_colors[i].g;
        RGB(layer_keys[i][1]).b = prev_colors[i].b;
      }
    }
  }
  if (!layer_state_cmp(state, MODIFIERS) && showing_mods == true) {
    showing_mods = false;
  }
  if (layer_state_cmp(state, TYPING) && host_keyboard_led_state().caps_lock) {
    tap_code(KC_CAPS);
  }
  return state;
}

#define CAPS_LOCATION 30
#define CAPS_RGB RGB(CAPS_LOCATION)
#define CAPS_ANIMATION_LENGTH 1500

static bool caps_on = false;
static RGB old_color;
static uint16_t caps_timer;

float easeOutQuad(float perc) {
  return perc * perc;
}

bool led_update_user(led_t led_state) {
  if (caps_on != led_state.caps_lock && led_state.caps_lock == false) {
    caps_on = false;
    CAPS_RGB.r = old_color.r;
    CAPS_RGB.g = old_color.g;
    CAPS_RGB.b = old_color.b;
  } if (caps_on != led_state.caps_lock && led_state.caps_lock == true) {
    caps_on = true;
    caps_timer = timer_read();
    old_color.r = CAPS_RGB.r;
    old_color.g = CAPS_RGB.g;
    old_color.b = CAPS_RGB.b;
  }

  return true;
}

void rgb_matrix_indicators_user() {
  if (caps_on) {
    float raw_perc = (timer_elapsed(caps_timer) % CAPS_ANIMATION_LENGTH) / (CAPS_ANIMATION_LENGTH / 2.0);
    if (raw_perc > 1) {
      raw_perc = 2.0 - raw_perc;
    }

    uint8_t red = 255 - (easeOutQuad(raw_perc) * 255);
    CAPS_RGB.r = red;
    CAPS_RGB.b = 0;
    CAPS_RGB.g = 0;
  }

  if (layer_state_is(MODIFIERS)) {
    float raw_perc = (timer_elapsed(caps_timer) % ANIM_LENGTH) / (ANIM_LENGTH / 2.0);
    if (raw_perc > 1) {
      raw_perc = 2.0 - raw_perc;
    }

    for (uint8_t i = 0; i < LAYER_KEY_COUNT; i ++) {
      if (layer_state_is(layer_keys[i][0])) {
        uint8_t red = 255 - (easeOutQuad(raw_perc) * 255);
        RGB(layer_keys[i][1]).r = red;
        RGB(layer_keys[i][1]).b = 0;
        RGB(layer_keys[i][1]).g = 0;
      }
    }
  }
}

