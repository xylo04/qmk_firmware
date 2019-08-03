#include QMK_KEYBOARD_H
#include "muse.h"
#include "eeprom.h"
#include "keymap_german.h"
#include "keymap_nordic.h"
#include "keymap_french.h"
#include "keymap_spanish.h"
#include "keymap_hungarian.h"
#include "keymap_swedish.h"

#define KC_MAC_UNDO LGUI(KC_U)
#define KC_MAC_CUT LGUI(KC_X)
#define KC_MAC_COPY LGUI(KC_C)
#define KC_MAC_PASTE LGUI(KC_V)
#define KC_PC_UNDO LCTL(KC_U)
#define KC_PC_CUT LCTL(KC_X)
#define KC_PC_COPY LCTL(KC_C)
#define KC_PC_PASTE LCTL(KC_V)

enum planck_keycodes {
  RGB_SLD = SAFE_RANGE,
  TOGGLE_LAYER_COLOR,
  EPRM,
};

enum planck_layers {
  _BASE,
  _LOWER,
  _RAISE,
  _ADJUST,
};


#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT_planck_grid(KC_TAB,KC_Q,KC_W,KC_E,KC_R,KC_T,KC_Y,KC_U,KC_I,KC_O,KC_P,KC_BSPACE,KC_ESCAPE,KC_A,KC_S,KC_D,KC_F,KC_G,KC_H,KC_J,KC_K,KC_L,KC_SCOLON,KC_QUOTE,KC_LSHIFT,KC_Z,KC_X,KC_C,KC_V,KC_B,KC_N,KC_M,KC_COMMA,KC_DOT,KC_SLASH,KC_ENTER,KC_TRANSPARENT,KC_LCTRL,KC_LALT,KC_LGUI,LOWER,KC_SPACE,KC_NO,RAISE,KC_LEFT,KC_DOWN,KC_UP,KC_RIGHT),

  [_LOWER] = LAYOUT_planck_grid(KC_TILD,KC_EXLM,KC_AT,KC_HASH,KC_DLR,KC_PERC,KC_CIRC,KC_AMPR,KC_ASTR,KC_LPRN,KC_RPRN,KC_TRANSPARENT,KC_DELETE,KC_F1,KC_F2,KC_F3,KC_F4,KC_F5,KC_F6,KC_UNDS,KC_PLUS,KC_LCBR,KC_RCBR,KC_PIPE,KC_TRANSPARENT,KC_F7,KC_F8,KC_F9,KC_F10,KC_F11,KC_F12,KC_NONUS_HASH,KC_NONUS_BSLASH,KC_HOME,KC_END,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_NO,KC_TRANSPARENT,KC_MEDIA_NEXT_TRACK,KC_AUDIO_VOL_DOWN,KC_AUDIO_VOL_UP,KC_MEDIA_PLAY_PAUSE),

  [_RAISE] = LAYOUT_planck_grid(KC_GRAVE,KC_1,KC_2,KC_3,KC_4,KC_5,KC_6,KC_7,KC_8,KC_9,KC_0,KC_TRANSPARENT,KC_DELETE,KC_F1,KC_F2,KC_F3,KC_F4,KC_F5,KC_F6,KC_MINUS,KC_EQUAL,KC_LBRACKET,KC_RBRACKET,KC_BSLASH,KC_TRANSPARENT,KC_F7,KC_F8,KC_F9,KC_F10,KC_F11,KC_F12,KC_NONUS_HASH,KC_NONUS_BSLASH,KC_PGUP,KC_PGDOWN,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_NO,KC_TRANSPARENT,KC_MEDIA_NEXT_TRACK,KC_AUDIO_VOL_DOWN,KC_AUDIO_VOL_UP,KC_MEDIA_PLAY_PAUSE),

  [_ADJUST] = LAYOUT_planck_grid(KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_DELETE,KC_TRANSPARENT,AU_ON,AU_OFF,AU_TOG,KC_TRANSPARENT,KC_TRANSPARENT,RGB_TOG,RGB_VAI,RGB_VAD,KC_TRANSPARENT,RESET,KC_TRANSPARENT,KC_TRANSPARENT,MU_ON,MU_OFF,MU_TOG,KC_TRANSPARENT,KC_TRANSPARENT,RGB_MOD,RGB_HUI,RGB_HUD,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_NO,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT),

};



extern bool g_suspend_state;
extern rgb_config_t rgb_matrix_config;
bool disable_layer_color = 0;


void keyboard_post_init_user(void) {
  rgb_matrix_enable();
}

const uint8_t PROGMEM ledmap[][DRIVER_LED_TOTAL][3] = {
    [1] = { {0,0,0}, {255,220,201}, {255,220,201}, {255,220,201}, {255,220,201}, {255,220,201}, {233,218,217}, {233,218,217}, {233,218,217}, {233,218,217}, {233,218,217}, {0,0,0}, {0,0,0}, {255,220,201}, {255,220,201}, {255,220,201}, {255,220,201}, {255,220,201}, {233,218,217}, {233,218,217}, {233,218,217}, {243,222,234}, {233,218,217}, {0,0,0}, {0,0,0}, {255,220,201}, {255,220,201}, {255,220,201}, {255,220,201}, {255,220,201}, {233,218,217}, {233,218,217}, {233,218,217}, {233,218,217}, {233,218,217}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0} },

    [2] = { {0,0,0}, {180,255,233}, {180,255,233}, {180,255,233}, {180,255,233}, {180,255,233}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {180,255,233}, {180,255,233}, {180,255,233}, {180,255,233}, {180,255,233}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {180,255,233}, {180,255,233}, {180,255,233}, {180,255,233}, {180,255,233}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0} },

    [3] = { {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {10,225,255}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {134,255,213}, {0,0,0}, {0,0,0}, {32,176,255}, {32,176,255}, {32,176,255}, {10,225,255}, {10,225,255}, {243,222,234}, {243,222,234}, {243,222,234}, {0,0,0}, {134,255,213}, {0,0,0}, {0,0,0}, {32,176,255}, {32,176,255}, {32,176,255}, {0,0,0}, {0,0,0}, {243,222,234}, {243,222,234}, {243,222,234}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0} },

    [4] = { {0,0,0}, {0,0,0}, {0,0,0}, {85,203,158}, {0,0,0}, {0,0,0}, {0,0,0}, {85,203,158}, {85,203,158}, {85,203,158}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {85,203,158}, {85,203,158}, {85,203,158}, {0,0,0}, {0,0,0}, {85,203,158}, {85,203,158}, {85,203,158}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0} },

};

#include "rgb_matrix_types.h"

extern effect_params_t rgb_effect_params;

void set_layer_color(int layer) {
  uint8_t min = RGB_MATRIX_LED_PROCESS_LIMIT * rgb_effect_params.iter;
  uint8_t max = min + RGB_MATRIX_LED_PROCESS_LIMIT;
  if (max > DRIVER_LED_TOTAL)
    max = DRIVER_LED_TOTAL;


  for (int i = min; i < max; i++) {
    HSV hsv = {
      .h = pgm_read_byte(&ledmap[layer][i][0]),
      .s = pgm_read_byte(&ledmap[layer][i][1]),
      .v = pgm_read_byte(&ledmap[layer][i][2]),
    };
    if (!hsv.h && !hsv.s && !hsv.v) {
        rgb_matrix_set_color( i, 0, 0, 0 );
    } else {
        RGB rgb = hsv_to_rgb( hsv );
        float f = (float)rgb_matrix_config.hsv.v / UINT8_MAX;
        rgb_matrix_set_color( i, f * rgb.r, f * rgb.g, f * rgb.b );
    }
  }
}

void rgb_matrix_indicators_user(void) {
  if (g_suspend_state || disable_layer_color) { return; }
  switch (biton32(layer_state)) {
    case 1:
      set_layer_color(1);
      break;
    case 2:
      set_layer_color(2);
      break;
    case 3:
      set_layer_color(3);
      break;
    case 4:
      set_layer_color(4);
      break;
  }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case EPRM:
      if (record->event.pressed) {
        eeconfig_init();
      }
      return false;
    case RGB_SLD:
      if (record->event.pressed) {
        rgblight_mode(1);
      }
      return false;
    case RGB_TOG:
  if (record->event.pressed) {
    if (rgb_matrix_config.hsv.v) {
      rgb_matrix_sethsv(rgb_matrix_config.hsv.h, rgb_matrix_config.hsv.s, 0);
    } else {
      rgb_matrix_sethsv(rgb_matrix_config.hsv.h, rgb_matrix_config.hsv.s, 255);
    }
  }
  return false;
    case TOGGLE_LAYER_COLOR:
      if (record->event.pressed) {
        disable_layer_color ^= 1;
      }
      return false;
  }
  return true;
}

bool muse_mode = false;
uint8_t last_muse_note = 0;
uint16_t muse_counter = 0;
uint8_t muse_offset = 70;
uint16_t muse_tempo = 50;

void encoder_update(bool clockwise) {
    if (muse_mode) {
        if (IS_LAYER_ON(_RAISE)) {
            if (clockwise) {
                muse_offset++;
            } else {
                muse_offset--;
            }
        } else {
            if (clockwise) {
                muse_tempo+=1;
            } else {
                muse_tempo-=1;
            }
        }
    } else {
        if (clockwise) {
        #ifdef MOUSEKEY_ENABLE
            register_code(KC_MS_WH_DOWN);
            unregister_code(KC_MS_WH_DOWN);
        #else
            register_code(KC_PGDN);
            unregister_code(KC_PGDN);
        #endif
        } else {
        #ifdef MOUSEKEY_ENABLE
            register_code(KC_MS_WH_UP);
            unregister_code(KC_MS_WH_UP);
        #else
            register_code(KC_PGUP);
            unregister_code(KC_PGUP);
        #endif
        }
    }
}

void matrix_scan_user(void) {
#ifdef AUDIO_ENABLE
    if (muse_mode) {
        if (muse_counter == 0) {
            uint8_t muse_note = muse_offset + SCALE[muse_clock_pulse()];
            if (muse_note != last_muse_note) {
                stop_note(compute_freq_for_midi_note(last_muse_note));
                play_note(compute_freq_for_midi_note(muse_note), 0xF);
                last_muse_note = muse_note;
            }
        }
        muse_counter = (muse_counter + 1) % muse_tempo;
    }
#endif
}

bool music_mask_user(uint16_t keycode) {
    switch (keycode) {
    case RAISE:
    case LOWER:
        return false;
    default:
        return true;
    }
}
uint32_t layer_state_set_user(uint32_t state) {
    palClearPad(GPIOB, 8);
    palClearPad(GPIOB, 9);
    uint8_t layer = biton32(state);
    switch (layer) {
        case _LOWER:
            palSetPad(GPIOB, 9);
            break;
        case _RAISE:
            palSetPad(GPIOB, 8);
            break;
        case _ADJUST:
            palSetPad(GPIOB, 9);
            palSetPad(GPIOB, 8);
            break;
        default:
            break;
    }
    return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}
