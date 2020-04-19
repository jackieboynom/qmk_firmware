/* Copyright 2019 Franklin Harding
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

enum layers {
  _DEFAULT,
  _WAVEXCHANGE
};

// Defines the keycodes used by our macros in process_record_user
enum custom_keycodes {
    LINE = SAFE_RANGE, 
    STARTSERVER,
    RESTARTSERVER,
    STARTPORTAL,
    RESTARTPORTAL
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_DEFAULT] = LAYOUT(
      LINE,         KC_VOLU,
      KC_MUTE,      KC_VOLD,
      XXXXXXX,      MO(_WAVEXCHANGE)
    ),

    [_WAVEXCHANGE] = LAYOUT(
      STARTPORTAL,  RESTARTPORTAL,
      STARTSERVER,  RESTARTSERVER,
      XXXXXXX,      KC_TRNS
    )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case LINE:
      if (record->event.pressed) {
        SEND_STRING(SS_LGUI(SS_LSFT("a")));
      }
      break;
    case STARTSERVER:
      if (record->event.pressed) {
        SEND_STRING("cd wavexchange/server" SS_TAP(X_ENTER) "node server" SS_TAP(X_ENTER));
      }
      break;
    case RESTARTSERVER:
      if (record->event.pressed) {
        SEND_STRING(SS_LCTL("c") "node server" SS_TAP(X_ENTER));
      }
      break;
    case STARTPORTAL:
      if (record->event.pressed) {
        SEND_STRING("cd wavexchange/portal" SS_TAP(X_ENTER) "ng serve" SS_TAP(X_ENTER));
      }
      break;
    case RESTARTPORTAL:
      if (record->event.pressed) {
        SEND_STRING(SS_LCTL("c") "ng serve" SS_TAP(X_ENTER));
      }
      break;
  }

  return true;
}

void matrix_init_user(void) {}

void matrix_scan_user(void) {}

void led_set_user(uint8_t usb_led) {}
