#include QMK_KEYBOARD_H
#include "version.h"

// Layers
#define INSERT 0
#define NORMAL 3
#define MOUSE 2
#define FN 7

typedef struct {
  bool is_press_action;
  int state;
} tap;

enum {
  SINGLE_TAP = 1,
  SINGLE_HOLD = 2,
  DOUBLE_TAP = 3,
  DOUBLE_HOLD = 4,
};

enum {
  TD_XCAPE = 0,
  TD_QUOT = 1,
  TD_GUI = 2,
  TD_ALT = 3,
};

int cur_dance (qk_tap_dance_state_t *state);

void tdx_finished (qk_tap_dance_state_t *state, void *user_data);
void tdx_reset (qk_tap_dance_state_t *state, void *user_data);

void tdq_finished (qk_tap_dance_state_t *state, void *user_data);
void tdq_reset (qk_tap_dance_state_t *state, void *user_data);

void tdg_finished (qk_tap_dance_state_t *state, void *user_data);
void tdg_reset (qk_tap_dance_state_t *state, void *user_data);

void tda_finished (qk_tap_dance_state_t *state, void *user_data);
void tda_reset (qk_tap_dance_state_t *state, void *user_data);

qk_tap_dance_action_t tap_dance_actions[] = {
  [TD_XCAPE] = ACTION_TAP_DANCE_FN_ADVANCED_TIME(NULL, tdx_finished, tdx_reset, 275),
  [TD_QUOT] = ACTION_TAP_DANCE_FN_ADVANCED_TIME(NULL, tdq_finished, tdq_reset, 275),
  [TD_GUI] = ACTION_TAP_DANCE_FN_ADVANCED_TIME(NULL, tdg_finished, tdg_reset, 275),
  [TD_ALT] = ACTION_TAP_DANCE_FN_ADVANCED_TIME(NULL, tda_finished, tda_reset, 275),
};

// Macros
uint16_t VIM_QUEUE = KC_NO;

enum custom_keycodes {
  PLACEHOLDER = SAFE_RANGE,
  VIM_G,
  VIM_T,
  VIM_DLR,
};

void VIM_LEADER(uint16_t keycode) {
  VIM_QUEUE = keycode;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  bool SHIFTED = (keyboard_report->mods & MOD_BIT(KC_LSFT)) |
                 (keyboard_report->mods & MOD_BIT(KC_RSFT));

  switch (keycode) {
    case VIM_G:
      if (record->event.pressed) {
        switch(VIM_QUEUE) {
          case KC_NO:
            if (SHIFTED) {
                VIM_LEADER(KC_NO);
                SEND_STRING(
                  SS_UP(X_LSHIFT)
                  SS_UP(X_RSHIFT)
                  SS_DOWN(X_LCTRL)
                  SS_DOWN(X_RCTRL)
                  SS_TAP(X_END)
                  SS_UP(X_LCTRL)
                  SS_UP(X_RCTRL)
                );
                break;
            } else {
                VIM_LEADER(VIM_G);
                break;
            }
          case VIM_G:
            VIM_LEADER(KC_NO);
            SEND_STRING(
                SS_DOWN(X_LCTRL)
                SS_DOWN(X_RCTRL)
                SS_TAP(X_HOME)
                SS_UP(X_LCTRL)
                SS_UP(X_RCTRL)
            );
            break;
        }
      }
      break;

    case VIM_T:
      if (record->event.pressed) {
        switch(VIM_QUEUE) {
          case VIM_G:
            VIM_LEADER(KC_NO);
            SEND_STRING(
              SS_DOWN(X_LCTL)
              SS_DOWN(X_RCTL)
              SS_TAP(X_TAB)
              SS_UP(X_LCTL)
              SS_UP(X_RCTL)
            );
            break;
        }
      }
      break;

    case VIM_DLR:
      if (record->event.pressed) {
        if (SHIFTED) {
          SEND_STRING(
            SS_UP(X_LSHIFT)
            SS_UP(X_RSHIFT)
            SS_TAP(X_END)
          );
          break;
        }
      }
      break;
  }
  return true;
};

// Combos
enum combos {
  C_F11,
  C_F12
};

const uint16_t PROGMEM f11_combo[] = {KC_F10, KC_F1, COMBO_END};
const uint16_t PROGMEM f12_combo[] = {KC_F10, KC_F2, COMBO_END};

combo_t key_combos[COMBO_COUNT] = {
  [C_F11] = COMBO(f11_combo, KC_F11),
  [C_F12] = COMBO(f12_combo, KC_F12)
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Insert Layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * | Grv    |   1  |   2  |   3  |   4  |   5  |      |           |      |   6  |   7  |   8  |   9  |   0  |Backspace|
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+---------|
 * | Tab    |   Q  |   W  |   E  |   R  |   T  |      |           |      |   Y  |   U  |   I  |   O  |   P  |   \     |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+---------|
 * |TD_XCAPE|   A  |   S  |   D  |   F  |   G  |------|           |------|   H  |   J  |   K  |   L  |   ;  | TD_QUOT |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+---------|
 * | LSPO   |   Z  |   X  |   C  |   V  |   B  |      |           |      |   N  |   M  |   ,  |   .  |   /  | RSPC    |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+---------'
 *   | FN   |   -  |   =  |   Alt| Super|                                       | Super|   Alt|   [  |   ]  | FN   |
 *   `----------------------------------'                                       `----------------------------------'
 *                                         ,------------.       ,------------.
 *                                         |     |      |       |      |     |
 *                                  ,------|-----|------|       |------+-----+------.
 *                                  |      |     |      |       |      |     |      |
 *                                  |Space |     |------|       |------|     |Enter |
 *                                  |      |     |      |       |      |     |      |
 *                                  `-------------------'       `------------------x'
 */
[INSERT] = LAYOUT_ergodox(
  // left hand
  KC_GRV,       KC_1,    KC_2,   KC_3,       KC_4,       KC_5, KC_TRNS,
  KC_TAB,       KC_Q,    KC_W,   KC_E,       KC_R,       KC_T, KC_TRNS,
  TD(TD_XCAPE), KC_A,    KC_S,   KC_D,       KC_F,       KC_G,
  KC_LSPO,      KC_Z,    KC_X,   KC_C,       KC_V,       KC_B, KC_TRNS,
  MO(FN),       KC_MINS, KC_EQL, TD(TD_ALT), TD(TD_GUI),
                                                      KC_TRNS, KC_TRNS,
                                                               KC_TRNS,
                                              KC_SPC, KC_TRNS, KC_TRNS,
  // right hand
  KC_TRNS, KC_6,       KC_7,   KC_8,    KC_9,    KC_0,    KC_BSPC,
  KC_TRNS, KC_Y,       KC_U,   KC_I,    KC_O,    KC_P,    KC_BSLS,
           KC_H,       KC_J,   KC_K,    KC_L,    KC_SCLN, TD(TD_QUOT),
  KC_TRNS, KC_N,       KC_M,   KC_COMM, KC_DOT,  KC_SLSH, KC_RSPC,
           TD(TD_GUI), TD(TD_ALT), KC_LBRC, KC_RBRC, MO(FN),
  KC_TRNS, KC_TRNS,
  KC_TRNS,
  KC_TRNS, KC_TRNS, KC_ENT
),
// Normal Layer
[NORMAL] = LAYOUT_ergodox(
  // left hand
  KC_NO,   KC_NO, KC_NO, KC_NO, VIM_DLR, KC_NO, KC_NO,
  KC_NO,   KC_NO, KC_NO, KC_NO, KC_NO,   VIM_T, KC_NO,
  KC_NO,   KC_NO, KC_NO, KC_NO, KC_NO,   VIM_G,
  KC_LSFT, KC_NO, KC_NO, KC_NO, KC_NO,   KC_NO, KC_NO,
           KC_NO, KC_NO, KC_NO, KC_NO,   KC_NO,
                                         KC_NO, KC_NO,
                                                KC_NO,
                                  KC_NO, KC_NO, KC_NO,
  // right hand
  KC_NO, KC_NO,   KC_NO,   KC_NO,      KC_NO,    KC_HOME, KC_NO,
  KC_NO, C(KC_C), KC_NO,   TG(NORMAL), KC_NO,    C(KC_V), KC_NO,
         KC_LEFT, KC_DOWN, KC_UP,      KC_RIGHT, KC_NO,   KC_NO,
  KC_NO, KC_NO,   KC_NO,   KC_NO,      KC_NO,    C(KC_F),   KC_RSFT,
         KC_NO,   KC_NO,   KC_NO,      KC_NO,    KC_NO,
  KC_NO, KC_NO,
  KC_NO,
  KC_NO, KC_NO, KC_NO
),
/* Mouse layer
 *
 * ,---------------------------------------------------.           ,--------------------------------------------------.
 * |         |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |---------+------+------+------+------+------+------|           |------+------+------+------+------+------+--------|
 * |         |      |WhDown| MsUp | WhUp |      |      |           |      |      |      |      |      |      |        |
 * |---------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |         |      |MsLeft|MsDown|MsRght|      |------|           |------|      |      |      |      |      |        |
 * |---------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |         |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * `---------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |       |      |      |      |      |                                       |      |      |      |      |      |
 *   `-----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 | Lclk |      |------|       |------|      | Rclk |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
[MOUSE] = LAYOUT_ergodox(
  // left hand
  KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
  KC_TRNS,  KC_TRNS, KC_WH_D, KC_MS_U, KC_WH_U, KC_TRNS, KC_TRNS,
  KC_LCTRL, KC_TRNS, KC_MS_L, KC_MS_D, KC_MS_R, KC_TRNS,
  KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
            KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                                                KC_TRNS, KC_TRNS,
                                                         KC_TRNS,
                                       KC_BTN1, KC_TRNS, KC_TRNS,
  // right hand
  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,   KC_TRNS, KC_TRNS, KC_TRNS,
  KC_TRNS, C(KC_C), KC_TRNS, TG(MOUSE), KC_TRNS, C(KC_V), KC_TRNS,
           KC_TRNS, KC_TRNS, KC_TRNS,   KC_TRNS, KC_TRNS, KC_TRNS,
  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,   KC_TRNS, KC_TRNS, KC_TRNS,
           KC_TRNS, KC_TRNS, KC_TRNS,   KC_TRNS, KC_TRNS,
  KC_TRNS, KC_TRNS,
  KC_TRNS,
  KC_TRNS, KC_TRNS, KC_BTN2
),
/* Function layer
 *
 * ,---------------------------------------------------.           ,--------------------------------------------------.
 * |   RSTP  |  F1  |  F2  |  F3  |  F4  |  F5  |      |           |      |  F6  |  F7  |  F8  |  F9  |  F10 |   Del  |
 * |---------+------+------+------+------+------+------|           |------+------+------+------+------+------+--------|
 * |         |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |---------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |         |      |      |      |      |      |------|           |------|      |      |      |      |      |        |
 * |---------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |         |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * `---------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   | RESET | BNDN | BNUP |      |      |                                       |      |      | VolDn| VolUp| Mute |
 *   `-----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      | PLY1 |       | REC1 |      |      |
 *                                 |      |      |------|       |------|      |      |
 *                                 |      |      | PLY2 |       | REC2 |      |      |
 *                                 `--------------------'       `--------------------'
 */
[FN] = LAYOUT_ergodox(
  // left hand
  DM_RSTP, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_TRNS,
  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
           RESET,   KC_BRID, KC_BRIU, KC_TRNS, KC_TRNS,
                                               KC_TRNS, KC_TRNS,
                                                        DM_PLY1,
                                      KC_TRNS, KC_TRNS, DM_PLY2,
  // right hand
  KC_TRNS, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_DEL,
  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
           KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
           KC_TRNS, KC_TRNS, KC_VOLD, KC_VOLU, KC_MUTE,
  KC_TRNS, KC_TRNS,
  DM_REC1,
  DM_REC2, KC_TRNS, KC_TRNS
),
};

// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {
#ifdef RGBLIGHT_COLOR_LAYER_0
  rgblight_setrgb(RGBLIGHT_COLOR_LAYER_0);
#endif
};

// Runs whenever there is a layer state change.
layer_state_t layer_state_set_user(layer_state_t state) {
  ergodox_board_led_off();
  ergodox_right_led_1_off();
  ergodox_right_led_2_off();
  ergodox_right_led_3_off();

  uint8_t layer = biton32(state);
  switch (layer) {
      case 0:
        #ifdef RGBLIGHT_COLOR_LAYER_0
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_0);
        #else
        #ifdef RGBLIGHT_ENABLE
          rgblight_init();
        #endif
        #endif
        break;
      case 1:
        ergodox_right_led_1_on();
        #ifdef RGBLIGHT_COLOR_LAYER_1
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_1);
        #endif
        break;
      case 2:
        ergodox_right_led_2_on();
        #ifdef RGBLIGHT_COLOR_LAYER_2
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_2);
        #endif
        break;
      case 3:
        ergodox_right_led_3_on();
        #ifdef RGBLIGHT_COLOR_LAYER_3
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_3);
        #endif
        break;
      case 4:
        ergodox_right_led_1_on();
        ergodox_right_led_2_on();
        #ifdef RGBLIGHT_COLOR_LAYER_4
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_4);
        #endif
        break;
      case 5:
        ergodox_right_led_1_on();
        ergodox_right_led_3_on();
        #ifdef RGBLIGHT_COLOR_LAYER_5
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_5);
        #endif
        break;
      case 6:
        ergodox_right_led_2_on();
        ergodox_right_led_3_on();
        #ifdef RGBLIGHT_COLOR_LAYER_6
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_6);
        #endif
        break;
      case 7:
        ergodox_right_led_1_on();
        ergodox_right_led_2_on();
        ergodox_right_led_3_on();
        #ifdef RGBLIGHT_COLOR_LAYER_7
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_7);
        #endif
        break;
      default:
        break;
    }

  return state;
};

// Tap Dance
int cur_dance (qk_tap_dance_state_t *state) {
  if (state->count == 1) {
    if (!state->pressed) {
      return SINGLE_TAP;
    } else {
      return SINGLE_HOLD;
    }
  } else if (state->count == 2) {
    if (!state->pressed) {
      return DOUBLE_TAP;
    } else {
      return DOUBLE_HOLD;
    }
  }
  else return 8;
}

// TD_XCAPE
static tap tdx_tap_state = {
  .is_press_action = true,
  .state = 0
};

void tdx_finished (qk_tap_dance_state_t *state, void *user_data) {
  tdx_tap_state.state = cur_dance(state);
  switch (tdx_tap_state.state) {
    case SINGLE_TAP:
      tap_code(KC_ESC);
      break;
    case SINGLE_HOLD:
      register_mods(MOD_BIT(KC_LCTL));
      break;
    case DOUBLE_TAP:
      if (layer_state_is(NORMAL)) {
        layer_off(NORMAL);
      } else {
        layer_on(NORMAL);
      }
      break;
    case DOUBLE_HOLD:
      register_mods(MOD_BIT(KC_LCTL));
      register_mods(MOD_BIT(KC_LSHIFT));
      break;
  }
}

void tdx_reset (qk_tap_dance_state_t *state, void *user_data) {
  if (tdx_tap_state.state==SINGLE_HOLD) {
    layer_off(NORMAL);
  }
  unregister_mods(MOD_BIT(KC_LCTL));
  unregister_mods(MOD_BIT(KC_LSHIFT));
  tdx_tap_state.state = 0;
}

// TD_QUOT
static tap tdq_tap_state = {
  .is_press_action = true,
  .state = 0
};

void tdq_finished (qk_tap_dance_state_t *state, void *user_data) {
  tdq_tap_state.state = cur_dance(state);
  switch (tdq_tap_state.state) {
    case SINGLE_TAP:
      tap_code(KC_QUOT);
      break;
    case SINGLE_HOLD:
      register_mods(MOD_BIT(KC_RCTL));
      break;
    case DOUBLE_TAP:
      if (layer_state_is(MOUSE)) {
        layer_off(MOUSE);
      } else {
        layer_on(MOUSE);
      }
      break;
    case DOUBLE_HOLD:
      register_mods(MOD_BIT(KC_RCTL));
      register_mods(MOD_BIT(KC_RSHIFT));
      break;
  }
}

void tdq_reset (qk_tap_dance_state_t *state, void *user_data) {
  if (tdq_tap_state.state==SINGLE_HOLD) {
    layer_off(MOUSE);
  }
  unregister_mods(MOD_BIT(KC_RCTL));
  unregister_mods(MOD_BIT(KC_RSHIFT));
  tdq_tap_state.state = 0;
}

// TD_GUI
static tap tdg_tap_state = {
  .is_press_action = true,
  .state = 0
};

void tdg_finished (qk_tap_dance_state_t *state, void *user_data) {
  tdg_tap_state.state = cur_dance(state);
  switch (tdg_tap_state.state) {
    case SINGLE_HOLD:
      register_mods(MOD_BIT(KC_LGUI));
      register_mods(MOD_BIT(KC_RGUI));
      break;
    case DOUBLE_HOLD:
      register_mods(MOD_BIT(KC_LGUI));
      register_mods(MOD_BIT(KC_RGUI));
      register_mods(MOD_BIT(KC_LSHIFT));
      register_mods(MOD_BIT(KC_RSHIFT));
      break;
  }
}

void tdg_reset (qk_tap_dance_state_t *state, void *user_data) {
  clear_oneshot_mods();
  unregister_mods(MOD_BIT(KC_LGUI));
  unregister_mods(MOD_BIT(KC_RGUI));
  unregister_mods(MOD_BIT(KC_LSHIFT));
  unregister_mods(MOD_BIT(KC_RSHIFT));
  tdg_tap_state.state = 0;
}

// TD_ALT
static tap tda_tap_state = {
  .is_press_action = true,
  .state = 0
};

void tda_finished (qk_tap_dance_state_t *state, void *user_data) {
  tda_tap_state.state = cur_dance(state);
  switch (tda_tap_state.state) {
    case SINGLE_HOLD:
      register_mods(MOD_BIT(KC_LALT));
      register_mods(MOD_BIT(KC_RALT));
      break;
    case DOUBLE_HOLD:
      register_mods(MOD_BIT(KC_LALT));
      register_mods(MOD_BIT(KC_RALT));
      register_mods(MOD_BIT(KC_LSHIFT));
      register_mods(MOD_BIT(KC_RSHIFT));
      break;
  }
}

void tda_reset (qk_tap_dance_state_t *state, void *user_data) {
  unregister_mods(MOD_BIT(KC_LALT));
  unregister_mods(MOD_BIT(KC_RALT));
  unregister_mods(MOD_BIT(KC_LSHIFT));
  unregister_mods(MOD_BIT(KC_RSHIFT));
  tda_tap_state.state = 0;
}
