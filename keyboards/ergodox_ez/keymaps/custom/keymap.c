#include QMK_KEYBOARD_H
#include "version.h"

#define BASE 0 // default layer
#define FN   1 // function keys

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Keymap 0: Basic layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * | Grv    |   1  |   2  |   3  |   4  |   5  |      |           |      |   6  |   7  |   8  |   9  |   0  |Backspace|
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+---------|
 * | Tab    |   Q  |   W  |   E  |   R  |   T  |      |           |      |   Y  |   U  |   I  |   O  |   P  |   \     |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+---------|
 * |Ctrl/Esc|A / L1|   S  |   D  |   F  |   G  |------|           |------|   H  |   J  |   K  |   L  |; / L1|' / Ctrl |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+---------|
 * | LSPO   |   Z  |   X  |   C  |   V  |   B  |      |           |      |   N  |   M  |   ,  |   .  |   /  | RSPC    |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+---------'
 *   |      |   [  |   -  |Al/App|Super |                                       |Super |Al/App|   =  |   ]  |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                         ,------------.       ,------------.
 *                                         |     |      |       |      |     |
 *                                   ,-----|-----|------|       |------+-----+-----.
 *                                   |     |     |      |       |      |     |     |
 *                                   |Space|     |------|       |------|     |Enter|
 *                                   |     |     |      |       |      |     |     |
 *                                   `------------------'       `------------------'
 */
[BASE] = LAYOUT_ergodox(
  // left hand
  KC_GRV,          KC_1,         KC_2,    KC_3,          KC_4,    KC_5,    KC_TRNS,
  KC_TAB,          KC_Q,         KC_W,    KC_E,          KC_R,    KC_T,    KC_TRNS,
  CTL_T(KC_ESC),   LT(FN, KC_A), KC_S,    KC_D,          KC_F,    KC_G,
  KC_LSPO,         KC_Z,         KC_X,    KC_C,          KC_V,    KC_B,    KC_TRNS,
  KC_TRNS,         KC_LBRC,      KC_MINS, ALT_T(KC_APP), KC_LGUI,
                                                                 KC_TRNS, KC_TRNS,
                                                                          KC_TRNS,
                                                         KC_SPC, KC_TRNS, KC_TRNS,
  // right hand
  KC_TRNS,          KC_6,    KC_7,           KC_8,     KC_9,    KC_0,            KC_BSPC,
  KC_TRNS,          KC_Y,    KC_U,           KC_I,     KC_O,    KC_P,            KC_BSLS,
                    KC_H,    KC_J,           KC_K,     KC_L,    LT(FN, KC_SCLN), CTL_T(KC_QUOT),
  KC_TRNS,          KC_N,    KC_M,           KC_COMM,  KC_DOT,  KC_SLSH,         KC_RSPC,
                    KC_RGUI, ALT_T(KC_APP),  KC_EQL,   KC_RBRC, KC_TRNS,
  KC_TRNS, KC_TRNS,
  KC_TRNS,
  KC_TRNS, KC_TRNS, KC_ENT
),
/* Keymap 1: Function Keys
 *
 * ,---------------------------------------------------.           ,--------------------------------------------------.
 * |         |  F1  |  F2  |  F3  |  F4  |  F5  |      |           |      |  F6  |  F7  |  F8  |  F9  |  F10 |   Del  |
 * |---------+------+------+------+------+------+------|           |------+------+------+------+------+------+--------|
 * |         |      |WhDown| MsUp |WhUp  |      |      |           |      | WBAK | Lclk | Rclk | WFWD |      |        |
 * |---------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |         |      |MsLeft|MsDown|MsRght|      |------|           |------| Left | Down |  Up  |Right | PSCR |        |
 * |---------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |         |      |      |      |      |      |      |           |      | Home | PgDn | PgUp | End  |      |        |
 * `---------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   | RESET |      | VolDn| BNDN |  F11 |                                       |  F12 | BNUP | VolUp|      | Mute |
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
  KC_TRNS, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_TRNS,
  KC_TRNS, KC_TRNS, KC_WH_D, KC_MS_U, KC_WH_U, KC_TRNS, KC_TRNS,
  KC_TRNS, KC_TRNS, KC_MS_L, KC_MS_D, KC_MS_R, KC_TRNS,
  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
           RESET,   KC_TRNS, KC_VOLD, KC_BRID, KC_F11,
                                               KC_TRNS, KC_TRNS,
                                                        KC_TRNS,
                                      KC_TRNS, KC_TRNS, KC_TRNS,
  // right hand
  KC_TRNS, KC_F6,   KC_F7,   KC_F8,   KC_F9,    KC_F10,  KC_DEL,
  KC_TRNS, KC_WBAK, KC_BTN1, KC_BTN2, KC_WFWD,  KC_TRNS, KC_F12,
           KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT, KC_PSCR, KC_TRNS,
  KC_TRNS, KC_HOME, KC_PGDN, KC_PGUP, KC_END,   KC_TRNS, KC_TRNS,
           KC_F12,  KC_BRIU, KC_VOLU, KC_TRNS,  KC_MUTE,
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
