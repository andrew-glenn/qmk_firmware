/* Copyright 2023 @ Keychron (https://www.keychron.com)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include QMK_KEYBOARD_H

// clang-format off

enum layers {
    BASE,
    JETBRAINS,
};
/*
 ROTARY | CIRCLE  | TRIANGE | SQUARE | X     |
   M1   | NUMLOCK |  /      |  *     | -     |
   M2   |   7     |  8      |  9     | +     |
   M3   |   4     |  5      |  6     | (nc)  |
   M4   |   1     |  2      |  3     | ENTER |
   M5   |   0     | (nc)    | (dot)  | (nc)  |
*/
uint16_t key_timer;
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [BASE] = LAYOUT_numpad_6x5(
        KC_MUTE,        KC_MEDIA_PLAY_PAUSE,        KC_MEDIA_NEXT_TRACK,          KC_NO,          KC_NO,
        QK_BOOTLOADER,  KC_NO,        KC_NO,          LSG(KC_H),          LSFT(KC_F12),
        KC_NO,          KC_NO,        KC_NO,          KC_NO,          LSFT(KC_F11),
        KC_NO,          KC_NO,        KC_NO,          KC_NO,
        KC_NO,          KC_NO,        KC_NO,          KC_NO,          KC_KP_ENTER,
        TO(JETBRAINS),          KC_NO,                        KC_NO),
    [JETBRAINS] = LAYOUT_numpad_6x5(
      KC_TRNS,        KC_NO,             KC_NO,             KC_NO,                         KC_NO,
      KC_NO,          HYPR(KC_A),        HYPR(KC_KP_SLASH), HYPR(KC_KP_ASTERISK),          HYPR(KC_KP_MINUS),
      KC_NO,          HYPR(KC_7),        HYPR(KC_8),        HYPR(KC_9),                    HYPR(KC_KP_PLUS),
      KC_NO,          HYPR(KC_4),        HYPR(KC_5),        HYPR(KC_6),
      KC_NO,          HYPR(KC_1),        HYPR(KC_2),        HYPR(KC_3),                    KC_TRNS,
      TO(BASE),       HYPR(KC_0),                           HYPR(KC_KP_DOT)),
};

void only_active_keys_leds(uint8_t led_min, uint8_t led_max, uint8_t x, uint8_t y, uint8_t z){
  uint8_t layer = get_highest_layer(layer_state);

  for (uint8_t row = 0; row < MATRIX_ROWS; ++row) {
    for (uint8_t col = 0; col < MATRIX_COLS; ++col) {
      uint8_t index = g_led_config.matrix_co[row][col];

      if (index >= led_min && index < led_max){
        if (index != NO_LED && keymap_key_to_keycode(layer, (keypos_t){col,row}) > KC_TRNS) {
          rgb_matrix_set_color(index, x,y,z);
        } /* else {
          rgb_matrix_set_color(index, 0,0,0);
        } */
      }
    }
  }
}


bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
  switch (get_highest_layer(layer_state)){
    case BASE:
      only_active_keys_leds(led_min, led_max, 0, 255, 255);
      break;
    case JETBRAINS:
      only_active_keys_leds(led_min, led_max, 51,255,51);
      break;
    default:
      break;
    }
   return false;
}

bool tap_hold(keyrecord_t* record, uint16_t tapkey, uint16_t holdkey){
  if (record->event.pressed){
    key_timer = timer_read();
  } else {
    if(timer_elapsed(key_timer) < TAPPING_TERM) {
      tap_code16(tapkey);
    } else {
      tap_code16(holdkey);
    }
  }
  return false;
}

bool process_record_user(uint16_t keycode, keyrecord_t* record) {
  switch(get_highest_layer(layer_state)){
    case BASE:
      switch (keycode) {
        case KC_MUTE:
          return tap_hold(record, LSG(KC_SPACE), KC_MUTE);
        case KC_KP_ENTER:
          return tap_hold(record, S(KC_F10), KC_Q);
      }
  }
  return true;
}

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [BASE] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [JETBRAINS] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
   // [FUNC] = { ENCODER_CCW_CW(RGB_VAD, RGB_VAI) },
};
#endif
