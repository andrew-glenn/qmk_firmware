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
};
/*
 ROTARY | CIRCLE  | TRIANGE | SQUARE | X     |
   M1   | NUMLOCK |  /      |  *     | -     |
   M2   |   7     |  8      |  9     | +     |
   M3   |   4     |  5      |  6     | (nc)  |
   M4   |   1     |  2      |  3     | ENTER |
   M5   |   0     | (nc)    | (dot)  | (nc)  |
*/

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [BASE] = LAYOUT_numpad_6x5(
        KC_MUTE,        KC_NO,        KC_NO,          KC_NO,          KC_NO,
        QK_BOOTLOADER,  KC_NO,        KC_NO,          KC_NO,          LSFT(KC_F12),
        KC_NO,          KC_NO,        KC_NO,          KC_NO,          LSFT(KC_F11),
        KC_NO,          KC_NO,        KC_NO,          KC_NO,
        KC_NO,          KC_NO,        KC_NO,          KC_NO,          KC_KP_ENTER,
        KC_NO,          KC_NO,                        KC_NO),
};


bool process_record_user(uint16_t keycode, keyrecord_t* record) {
  switch (keycode) {
    case LT(0, KC_Z):
        if (record->tap.count && record->event.pressed) {
            tap_code16(KC_X); // Tap Z
        } else if (record->event.pressed) {
            tap_code16(KC_Y); // Hold for layer toggle
        } else {
            return true;
        }
        return false;
  }
};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [BASE] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
   // [FUNC] = { ENCODER_CCW_CW(RGB_VAD, RGB_VAI) },
};
#endif // ENCODER_MAP_ENABLE
