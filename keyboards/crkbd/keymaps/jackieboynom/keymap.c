#include QMK_KEYBOARD_H

extern keymap_config_t keymap_config;

#ifdef RGBLIGHT_ENABLE
//Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
#endif

#ifdef OLED_ENABLE
static uint32_t oled_timer = 0;
#endif

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
enum layers {
  QWERTY,
  FNUC,
  CODE,
  ADJ,
  AIC
};

enum custom_keycodes {
  RGBRST = SAFE_RANGE,
  TOOLS_1
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [QWERTY] = LAYOUT( \
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,  KC_BSPC,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LCTL,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                         KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN, KC_QUOT,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH,  KC_ESC,\
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LGUI,MO(FNUC),  KC_ENT,     KC_SPC,MO(CODE), KC_RALT \
                                      //`--------------------------'  `--------------------------'
  ),

  [FNUC] = LAYOUT( \
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      XXXXXXX, XXXXXXX, KC_BTN1, KC_MS_U, KC_BTN2, KC_WH_D,                      KC_HOME,  KC_END, KC_PGUP, KC_PGDN, XXXXXXX, KC_VOLU,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX,   KC_F1, KC_MS_L, KC_MS_D, KC_MS_R, KC_WH_U,                      KC_LEFT, KC_DOWN,   KC_UP,KC_RIGHT,  KC_F12, KC_VOLD,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,                        KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11, KC_MUTE,\
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______,MO(FNUC), XXXXXXX,    XXXXXXX, MO(ADJ), _______ \
                                      //`--------------------------'  `--------------------------'
  ),

  [CODE] = LAYOUT( \
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      KC_TILD, KC_EXLM,   KC_AT, KC_HASH,  KC_DLR, KC_PERC,                      KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN,  KC_DEL,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       KC_GRV,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                      KC_LCBR, KC_RCBR, KC_LBRC, KC_RBRC, KC_PIPE, KC_BSLS,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,                      KC_UNDS, KC_MINS, KC_PLUS,  KC_EQL, XXXXXXX, XXXXXXX,\
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          XXXXXXX, MO(AIC), XXXXXXX,    XXXXXXX,MO(CODE), _______ \
                                      //`--------------------------'  `--------------------------'
  ),

  [ADJ] = LAYOUT( \
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                       EE_CLR, XXXXXXX, XXXXXXX, XXXXXXX,  RGBRST,  QK_RBT,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, RGB_SPI, RGB_VAI, RGB_SAI, RGB_HUI, RGB_TOG,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, RGB_SPD, RGB_VAD, RGB_SAD, RGB_HUD, RGB_MOD,\
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, MO(ADJ), XXXXXXX \
                                      //`--------------------------'  `--------------------------'
  ),

  [AIC] = LAYOUT( \
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, TOOLS_1, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,\
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          XXXXXXX, MO(AIC), XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX \
                                      //`--------------------------'  `--------------------------'
  )
};

int RGB_current_mode;

void matrix_init_user(void) {
    #ifdef RGBLIGHT_ENABLE
    RGB_current_mode = rgblight_config.mode;
    #endif
}

#ifdef OLED_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (!is_keyboard_master()) {
        return OLED_ROTATION_180; // flips the display 180 degrees if offhand
    }
    return rotation;
}

void render_blank_line(void) {
    static const char PROGMEM blank[] = {
        0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0};
    oled_write_P(blank, false);
}

void render_first_line(uint8_t modifiers) {
    static const char PROGMEM corne_logo[] = {0x20, 0x20, 0x80, 0x81, 0x82, 0x83, 0x84, 0x20, 0x20, 0};

    static const char PROGMEM adjust_layer[] = {0x85, 0x86, 0x87, 0x20, 0};
    static const char PROGMEM code_layer[] = {0x88, 0x89, 0x8a, 0x20, 0};
    static const char PROGMEM qwerty_layer[] = {0x8b, 0x8c, 0x8d, 0x20, 0};
    static const char PROGMEM fn_layer[] = {0x8e, 0x8f, 0x90, 0x20, 0};

    static const char PROGMEM ctrl_off[] = {0x91, 0x92, 0};
    static const char PROGMEM alt_off[] = {0x93, 0x94, 0};
    static const char PROGMEM shift_off[] = {0x95, 0x96, 0x20, 0x20, 0};
    static const char PROGMEM ctrl_on[] = {0x97, 0x98, 0};
    static const char PROGMEM alt_on[] = {0x99, 0x9a, 0};
    static const char PROGMEM shift_on[] = {0x9b, 0x9c, 0x20, 0x20, 0};

    oled_write_P(corne_logo, false);

    if(layer_state_is(ADJ)) {
        oled_write_P(adjust_layer, false);
    } else if(layer_state_is(FNUC)) {
        oled_write_P(fn_layer, false);
    } else if(layer_state_is(CODE)) {
        oled_write_P(code_layer, false);
    } else {
        oled_write_P(qwerty_layer, false);
    }

    if(modifiers & MOD_MASK_CTRL) {
        oled_write_P(ctrl_on, false);
    } else {
        oled_write_P(ctrl_off, false);
    }
    if(modifiers & MOD_MASK_ALT) {
        oled_write_P(alt_on, false);
    } else {
        oled_write_P(alt_off, false);
    }
    if(modifiers & MOD_MASK_SHIFT) {
        oled_write_P(shift_on, false);
    } else {
        oled_write_P(shift_off, false);
    }
}

void render_second_line(uint8_t modifiers) {
    static const char PROGMEM corne_logo[] = {0x20, 0x20, 0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0x20, 0x20, 0};

    static const char PROGMEM adjust_layer[] = {0xa5, 0xa6, 0xa7, 0x20, 0};
    static const char PROGMEM code_layer[] = {0xa8, 0xa9, 0xaa, 0x20, 0};
    static const char PROGMEM qwerty_layer[] = {0xab, 0xac, 0xad, 0x20, 0};
    static const char PROGMEM fn_layer[] = {0xae, 0xaf, 0xb0, 0x20, 0};

    static const char PROGMEM ctrl_off[] = {0xb1, 0xb2, 0};
    static const char PROGMEM alt_off[] = {0xb3, 0xb4, 0};
    static const char PROGMEM shift_off[] = {0xb5, 0xb6, 0x20, 0x20, 0};
    static const char PROGMEM ctrl_on[] = {0xb7, 0xb8, 0};
    static const char PROGMEM alt_on[] = {0xb9, 0xba, 0};
    static const char PROGMEM shift_on[] = {0xbb, 0xbc, 0x20, 0x20, 0};

    oled_write_P(corne_logo, false);

    if(layer_state_is(ADJ)) {
        oled_write_P(adjust_layer, false);
    } else if(layer_state_is(FNUC)) {
        oled_write_P(fn_layer, false);
    } else if(layer_state_is(CODE)) {
        oled_write_P(code_layer, false);
    } else {
        oled_write_P(qwerty_layer, false);
    }

    if(modifiers & MOD_MASK_CTRL) {
        oled_write_P(ctrl_on, false);
    } else {
        oled_write_P(ctrl_off, false);
    }
    if(modifiers & MOD_MASK_ALT) {
        oled_write_P(alt_on, false);
    } else {
        oled_write_P(alt_off, false);
    }
    if(modifiers & MOD_MASK_SHIFT) {
        oled_write_P(shift_on, false);
    } else {
        oled_write_P(shift_off, false);
    }
}

void render_third_line(uint8_t modifiers) {
    static const char PROGMEM corne_logo[] = {0x20, 0x20, 0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0x20, 0x20, 0};

    static const char PROGMEM adjust_layer[] = {0xc5, 0xc6, 0xc7, 0xdd, 0};
    static const char PROGMEM code_layer[] = {0xc8, 0xc9, 0xca, 0xdd, 0};
    static const char PROGMEM qwerty_layer[] = {0xcb, 0xcc, 0xcd, 0xdd, 0};
    static const char PROGMEM fn_layer[] = {0xce, 0xcf, 0xd0, 0xdd, 0};

    static const char PROGMEM ctrl_off[] = {0xd1, 0xd2, 0};
    static const char PROGMEM alt_off[] = {0xd3, 0xd4, 0};
    static const char PROGMEM shift_off[] = {0xd5, 0xd6, 0x20, 0x20, 0};
    static const char PROGMEM ctrl_on[] = {0xd7, 0xd8, 0};
    static const char PROGMEM alt_on[] = {0xd9, 0xda, 0};
    static const char PROGMEM shift_on[] = {0xdb, 0xdc, 0x20, 0x20, 0};

    oled_write_P(corne_logo, false);

    if(layer_state_is(ADJ)) {
        oled_write_P(adjust_layer, false);
    } else if(layer_state_is(FNUC)) {
        oled_write_P(fn_layer, false);
    } else if(layer_state_is(CODE)) {
        oled_write_P(code_layer, false);
    } else {
        oled_write_P(qwerty_layer, false);
    }

    if(modifiers & MOD_MASK_CTRL) {
        oled_write_P(ctrl_on, false);
    } else {
        oled_write_P(ctrl_off, false);
    }
    if(modifiers & MOD_MASK_ALT) {
        oled_write_P(alt_on, false);
    } else {
        oled_write_P(alt_off, false);
    }
    if(modifiers & MOD_MASK_SHIFT) {
        oled_write_P(shift_on, false);
    } else {
        oled_write_P(shift_off, false);
    }
}

bool oled_task_user(void) {
    if (!is_keyboard_master()) {
        //render_blank_line();
        render_first_line(get_mods()|get_oneshot_mods());
        render_second_line(get_mods()|get_oneshot_mods());
        render_third_line(get_mods()|get_oneshot_mods());
    } else {
        render_blank_line();
        render_first_line(get_mods()|get_oneshot_mods());
        render_second_line(get_mods()|get_oneshot_mods());
        render_third_line(get_mods()|get_oneshot_mods());
    }
    return false;
}
#endif

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        #ifdef OLED_ENABLE
        oled_timer = timer_read32();
        #endif
    }
    switch (keycode) {
        case RGBRST:
            #ifdef RGBLIGHT_ENABLE
            if (record->event.pressed) {
              eeconfig_update_rgblight_default();
              rgblight_enable();
              RGB_current_mode = rgblight_config.mode;
            }
            #endif
            #ifdef RGB_MATRIX_ENABLE
            if (record->event.pressed) {
              eeconfig_update_rgb_matrix_default();
              rgb_matrix_enable();
            }
            #endif
            break;
        case TOOLS_1: //sum marketplace and usage, remove marketplace cells in billing
            if (record->event.pressed) {
                SEND_STRING("=sum(" SS_DELAY(50) SS_TAP(X_LEFT) SS_DELAY(50) SS_TAP(X_UP) SS_DELAY(50) "+" SS_DELAY(50) SS_TAP(X_LEFT) SS_DELAY(50) SS_TAP(X_ENT) SS_DELAY(50));

                SEND_STRING(SS_TAP(X_UP) SS_DELAY(50));

                SEND_STRING(SS_LGUI("c") SS_DELAY(50) SS_TAP(X_LEFT) SS_DELAY(50) SS_TAP(X_UP) SS_DELAY(50));

                register_code(KC_LGUI);
                register_code(KC_LSFT);
                SEND_STRING("v");
                unregister_code(KC_LSFT);
                unregister_code(KC_LGUI);

                SEND_STRING(SS_DELAY(50) SS_TAP(X_DOWN) SS_DELAY(50) SS_TAP(X_LEFT) SS_DELAY(50) SS_TAP(X_LEFT) SS_DELAY(50));

                register_code(KC_LSFT);
                SEND_STRING(SS_TAP(X_RIGHT) SS_DELAY(50) SS_TAP(X_RIGHT) SS_DELAY(50) SS_TAP(X_RIGHT) SS_DELAY(50));
                unregister_code(KC_LSFT);

                register_code(KC_RALT);
                SEND_STRING("/" SS_DELAY(50));
                unregister_code(KC_RALT);

                SEND_STRING("delete cells and shift up" SS_DELAY(50) SS_TAP(X_ENT) SS_DELAY(50));
            }
    }
    return true;
}

#ifdef RGB_MATRIX_ENABLE
void suspend_power_down_keymap(void) {
    rgb_matrix_set_suspend_state(true);
}

void suspend_wakeup_init_keymap(void) {
    rgb_matrix_set_suspend_state(false);
}
#endif
