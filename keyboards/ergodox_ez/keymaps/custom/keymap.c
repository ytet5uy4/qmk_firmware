#include QMK_KEYBOARD_H
#include "version.h"

// Layers
#define INSERT 0
#define NORMAL 3
#define VISUAL 6
#define MOUSE 2
#define FN 7

typedef struct {
  bool is_press_action;
  int state;
} tap;

enum {
  SINGLE_TAP = 1,
  SINGLE_HOLD = 2,
  DOUBLE_TAP = 3
};

enum {
  LXCAPE = 0,
  RXCAPE = 1,
};

int cur_dance (qk_tap_dance_state_t *state);

void lx_finished (qk_tap_dance_state_t *state, void *user_data);
void lx_reset (qk_tap_dance_state_t *state, void *user_data);

void rx_finished (qk_tap_dance_state_t *state, void *user_data);
void rx_reset (qk_tap_dance_state_t *state, void *user_data);

qk_tap_dance_action_t tap_dance_actions[] = {
  [LXCAPE] = ACTION_TAP_DANCE_FN_ADVANCED_TIME(NULL, lx_finished, lx_reset, 275),
  [RXCAPE] = ACTION_TAP_DANCE_FN_ADVANCED_TIME(NULL, rx_finished, rx_reset, 275),
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
                  SS_TAP(X_END)
                );
                break;
            } else {
                VIM_LEADER(VIM_G);
                break;
            }
          case VIM_G:
            VIM_LEADER(KC_NO);
            SEND_STRING(SS_TAP(X_HOME));
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

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Insert Layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * | Grv    |   1  |   2  |   3  |   4  |   5  |      |           |      |   6  |   7  |   8  |   9  |   0  |Backspace|
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+---------|
 * | Tab    |   Q  |   W  |   E  |   R  |   T  |      |           |      |   Y  |   U  |   I  |   O  |   P  |   \     |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+---------|
 * | LXCAPE |   A  |   S  |   D  |   F  |   G  |------|           |------|   H  |   J  |   K  |   L  |   ;  | RXCAPE  |
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
  KC_GRV,     KC_1,    KC_2,    KC_3,      KC_4,       KC_5, KC_TRNS,
  KC_TAB,     KC_Q,    KC_W,    KC_E,      KC_R,       KC_T, KC_TRNS,
  TD(LXCAPE), KC_A,    KC_S,    KC_D,      KC_F,       KC_G,
  KC_LSPO,    KC_Z,    KC_X,    KC_C,      KC_V,       KC_B, KC_TRNS,
  MO(FN),     KC_MINS, KC_EQL,  KC_RALT,   KC_LGUI,
                                                    KC_TRNS, KC_TRNS,
                                                             KC_TRNS,
                                            KC_SPC, KC_TRNS, KC_TRNS,
  // right hand
  KC_TRNS, KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
  KC_TRNS, KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSLS,
           KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, TD(RXCAPE),
  KC_TRNS, KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSPC,
           KC_RGUI, KC_LALT, KC_LBRC, KC_RBRC, MO(FN),
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
  KC_NO, KC_NO,   KC_NO,   KC_NO,      KC_NO,    KC_NO,   KC_RSFT,
         KC_NO,   KC_NO,   KC_NO,      KC_NO,    KC_NO,
  KC_NO, KC_NO,
  KC_NO,
  KC_NO, KC_NO, KC_NO
),
// VISUAL layer
[VISUAL] = LAYOUT_ergodox(
  // left hand
  KC_NO,      KC_NO,  KC_NO,   KC_NO,   KC_NO, KC_NO, KC_NO,
  KC_NO,      KC_NO,  KC_NO,   KC_NO,   KC_NO, KC_NO, KC_NO,
  TG(VISUAL), KC_NO,  KC_NO,   C(KC_X), KC_NO, KC_NO,
  KC_NO,      KC_NO,  C(KC_X), KC_NO,   KC_NO, KC_NO, KC_NO,
              KC_NO,  KC_NO,   KC_NO,   KC_NO, KC_NO,
                                               KC_NO, KC_NO,
                                                      KC_NO,
                                        KC_NO, KC_NO, KC_NO,
  // right hand
  KC_NO, KC_NO,      KC_NO,      KC_NO,    KC_NO,       KC_NO,   KC_NO,
  KC_NO, C(KC_C),    KC_NO,      KC_NO,    KC_NO,       C(KC_V), KC_NO,
         S(KC_LEFT), S(KC_DOWN), S(KC_UP), S(KC_RIGHT), KC_NO,   KC_NO,
  KC_NO, KC_NO,      KC_NO,      KC_NO,    KC_NO,       KC_NO,   KC_NO,
         KC_NO,      KC_NO,      KC_NO,    KC_NO,       KC_NO,
  KC_NO, KC_NO,
  KC_NO,
  KC_NO, KC_NO, KC_NO
),
/* Mouse layer
 *
 * ,---------------------------------------------------.           ,--------------------------------------------------.
 * |         |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |---------+------+------+------+------+------+------|           |------+------+------+------+------+------+--------|
 * |         |      |      |      |      |      |      |           |      |      |WhDown| MsUp | WhUp |      |        |
 * |---------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |         |      |      |      |      |      |------|           |------|      |MsLeft|MsDown|MsRght| Rclk | Insert |
 * |---------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |         |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * `---------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |       |      |      |      |      |                                       |      |      |      |      |      |
 *   `-----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 |      |      |------|       |------|      | Lclk |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
[MOUSE] = LAYOUT_ergodox(
  // left hand
  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
           KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                                               KC_TRNS, KC_TRNS,
                                                        KC_TRNS,
                                      KC_TRNS, KC_TRNS, KC_TRNS,
  // right hand
  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
  KC_TRNS, KC_TRNS, KC_WH_D, KC_MS_U, KC_WH_U, KC_TRNS, KC_TRNS,
           KC_TRNS, KC_MS_L, KC_MS_D, KC_MS_R, KC_BTN2, TG(MOUSE),
  KC_TRNS, KC_TRNS, KC_PGDN, KC_PGUP, KC_TRNS, KC_TRNS, KC_TRNS,
           KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
  KC_TRNS, KC_TRNS,
  KC_TRNS,
  KC_TRNS, KC_TRNS, KC_BTN1
),
/* Function layer
 *
 * ,---------------------------------------------------.           ,--------------------------------------------------.
 * |    PLY1 |  F1  |  F2  |  F3  |  F4  |  F5  |      |           |      |  F6  |  F7  |  F8  |  F9  |  F10 |   Del  |
 * |---------+------+------+------+------+------+------|           |------+------+------+------+------+------+--------|
 * |    PLY2 |      |      |      |      |      |      |           |      |      |      |      |      |      |  RSTP  |
 * |---------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |         |      |      |      |      |      |------|           |------|      |      |      |      | PSCR |        |
 * |---------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |         |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * `---------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   | RESET | BNDN | BNUP |  F11 |  F12 |                                       | REC1 | REC2 | VolDn| VolUp| Mute |
 *   `-----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 |      |      |------|       |------|      |      |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
[FN] = LAYOUT_ergodox(
  // left hand
  DM_PLY1, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_TRNS,
  DM_PLY2, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
           RESET,   KC_BRID, KC_BRIU, KC_F11,  KC_F12,
                                               KC_TRNS, KC_TRNS,
                                                        KC_TRNS,
                                      KC_TRNS, KC_TRNS, KC_TRNS,
  // right hand
  KC_TRNS, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_DEL,
  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, DM_RSTP,
           KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_PSCR, KC_TRNS,
  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
           DM_REC1, DM_REC2, KC_VOLD, KC_VOLU, KC_MUTE,
  KC_TRNS, KC_TRNS,
  KC_TRNS,
  KC_TRNS, KC_TRNS, KC_TRNS
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
    return DOUBLE_TAP;
  }
  else return 8;
}

// LXCAPE
static tap lx_tap_state = {
  .is_press_action = true,
  .state = 0
};

void lx_finished (qk_tap_dance_state_t *state, void *user_data) {
  lx_tap_state.state = cur_dance(state);
  switch (lx_tap_state.state) {
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
  }
}

void lx_reset (qk_tap_dance_state_t *state, void *user_data) {
  if (lx_tap_state.state==SINGLE_HOLD) {
    layer_off(NORMAL);
  }
  unregister_mods(MOD_BIT(KC_LCTL));
  lx_tap_state.state = 0;
}

// RXCAPE
static tap rx_tap_state = {
  .is_press_action = true,
  .state = 0
};

void rx_finished (qk_tap_dance_state_t *state, void *user_data) {
  rx_tap_state.state = cur_dance(state);
  switch (rx_tap_state.state) {
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
  }
}

void rx_reset (qk_tap_dance_state_t *state, void *user_data) {
  if (rx_tap_state.state==SINGLE_HOLD) {
    layer_off(MOUSE);
  }
  unregister_mods(MOD_BIT(KC_RCTL));
  rx_tap_state.state = 0;
}
