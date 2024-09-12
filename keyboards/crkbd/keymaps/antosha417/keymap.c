// Copyright 2021 Anton Kavalkou (@antosha417)
// SPDX-License-Identifier: GPL-2.0-or-later
#include QMK_KEYBOARD_H
#include "sendstring_dvorak.h"
#include "luna.c"

typedef union {
  uint32_t raw;
  struct {
    bool is_win :1;
  };
} user_config;

user_config config;

enum layers {
  _QWERTY,
  _DVORAK,
  _SYMBOLS,
  _NUMS,
  _RIGHT,
  _LEFT,
};

enum keycodes {
  QWERTY = SAFE_RANGE,

  RUS_LANG,
  EN_LANG,
  HEB_LANG,

  CHNGE_OS,
  DELETE_WORD,
};

#define SYMBOLS LT(_SYMBOLS, KC_ENT)
#define NUMS    LT(_NUMS,    KC_ESC)
#define RIGHT   LT(_RIGHT,   KC_BSPC)
#define LEFT    LT(_LEFT,    KC_TAB)

#define LSFT_SP LSFT_T(KC_SPC)
#define RSFT_SP RSFT_T(KC_SPC)

#define LANG  TG(_DVORAK)

#define A_ALT LALT_T(KC_A)
#define O_GUI LGUI_T(KC_O)
#define U_CTRL LCTL_T(KC_U)

#define S_ALT RALT_T(KC_S)
#define N_GUI RGUI_T(KC_N)
#define H_CTRL RCTL_T(KC_H)

// I use LT(0) to be able to override hold action. Layer 0 is always active
#define F_CTLQ LT(0, KC_F)
#define S_GUIQ LT(0, KC_S)
#define L_GUIQ LT(0, KC_L)
#define J_CTLQ LT(0, KC_J)
#define A_ALTQ LT(0, KC_A)
#define SCLN_Q LT(0, KC_SCLN)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[_QWERTY] = LAYOUT_split_3x6_3(
//,-----------------------------------------------------.                    ,-----------------------------------------------------.
     KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,    KC_P, KC_BSPC,
//|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
     KC_ESC,  A_ALTQ,  S_GUIQ,    KC_D,  F_CTLQ,    KC_G,                         KC_H,  J_CTLQ,    KC_K,  L_GUIQ,  SCLN_Q, KC_QUOT,
//|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
    KC_LSFT,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH,  KC_ENT,
//|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                         LEFT, LSFT_SP, SYMBOLS,       NUMS, RSFT_SP,   RIGHT
                                    //`--------------------------'  `--------------------------'
),

[_DVORAK] = LAYOUT_split_3x6_3(
//,-----------------------------------------------------.                    ,-----------------------------------------------------.
     KC_TAB, KC_QUOT, KC_COMM,  KC_DOT,    KC_P,    KC_Y,                         KC_F,    KC_G,    KC_C,    KC_R,    KC_L, KC_BSPC,
//|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
     KC_ESC,   A_ALT,   O_GUI,    KC_E,  U_CTRL,    KC_I,                         KC_D,  H_CTRL,    KC_T,   N_GUI,   S_ALT, KC_QUOT,
//|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
    KC_LSFT, KC_SCLN,    KC_Q,    KC_J,    KC_K,    KC_X,                         KC_B,    KC_M,    KC_W,    KC_V,   KC_Z,   KC_ENT,
//|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                        _______, _______, _______,    _______, _______, _______
                                    //`--------------------------'  `--------------------------'
),

[_SYMBOLS] = LAYOUT_split_3x6_3(
//,-----------------------------------------------------.                    ,-----------------------------------------------------.
     KC_F11, KC_UNDS, KC_MINS, KC_TILD, KC_PERC, KC_QUOT,                      _______, KC_CIRC,  KC_GRV, KC_BSLS, KC_PIPE, _______,
//|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
    _______, KC_LBRC, KC_LCBR, KC_PLUS, KC_LPRN,  KC_EQL,                      KC_ASTR, KC_RPRN, KC_EXLM, KC_RCBR, KC_RBRC, _______,
//|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
    _______, _______, _______, _______,    LANG, _______,                      _______, _______, _______, _______, _______, _______,
//|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                        _______, _______, _______,    _______, _______, _______
                                    //`--------------------------'  `--------------------------'
                                                        //^^^^^^^
),


[_NUMS] = LAYOUT_split_3x6_3(
//,-----------------------------------------------------.                    ,-----------------------------------------------------.
     KC_F11, _______, _______, KC_DLR,  KC_AMPR, _______,                     KC_COLON, KC_QUES,   KC_AT, KC_HASH, KC_SLSH, KC_F12,
//|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
    _______,    KC_7,    KC_5,    KC_3,    KC_1,    KC_9,                         KC_0,    KC_2,    KC_4,    KC_6,    KC_8, _______,
//|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
    _______,   KC_F7,   KC_F5,   KC_F3,   KC_F1,   KC_F9,                       KC_F10,   KC_F2,   KC_F4,   KC_F6,   KC_F8, _______,
//|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                        _______, _______, _______,    _______, _______, _______
                                    //`--------------------------'  `--------------------------'
                                                                    //^^^^^^^
),

[_RIGHT] = LAYOUT_split_3x6_3(
//,-----------------------------------------------------.                    ,-----------------------------------------------------.
    _______,CHNGE_OS, _______, _______, _______, _______,                      _______, _______, _______, _______, _______, _______,
//|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
    _______, _______, _______, _______, KC_PGUP, _______,                      _______, _______, _______, _______, _______, _______,
//|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
    _______, _______, _______, KC_DOWN, KC_UP,   _______,                      _______, _______, _______, _______, _______, _______,
//|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                        _______, _______, _______,    _______, _______, _______
                                    //`--------------------------'  `--------------------------'
                                                                                      //^^^^^^^
),

[_LEFT] = LAYOUT_split_3x6_3(
//,-----------------------------------------------------.                    ,-----------------------------------------------------.
    _______, _______, _______, _______, _______, _______,                      _______, _______, _______, _______, KC_RGHT, _______,
//|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
    _______, _______, _______, _______, _______, _______,                      KC_PGDN, KC_LEFT, _______, _______, _______, _______,
//|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
    _______, _______, _______, _______, _______, _______,                      _______, KC_VOLD, KC_VOLU, _______, _______, _______,
//|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                        _______, _______, _______,    _______, _______, KC_BSPC
                                    //`--------------------------'  `--------------------------'
                                    //  ^^^^^^^
)
};

enum combo_events {
  // combos for dvorak layer
  RU_COMBO,
  EN_COMBO,
  HEB_COMBO,
  TAB_COMBO,
  DEL_COMBO,

  // combos for qwerty layer
  RUQ_COMBO,
  ENQ_COMBO,
  HEBQ_COMBO,
  TABQ_COMBO,
  DELQ_COMBO,

  COMBO_LENGTH
};
uint16_t COMBO_LEN = COMBO_LENGTH;

const uint16_t PROGMEM ru_combo[] = {KC_R, U_CTRL, COMBO_END};
const uint16_t PROGMEM en_combo[] = {U_CTRL, S_ALT, COMBO_END};
const uint16_t PROGMEM heb_combo[] = {KC_I, KC_V, COMBO_END};
const uint16_t PROGMEM tab_combo[] = {KC_T, A_ALT, COMBO_END};
const uint16_t PROGMEM del_combo[] = {KC_D, KC_E, COMBO_END};

const uint16_t PROGMEM ruq_combo[] = {KC_O, F_CTLQ, COMBO_END};
const uint16_t PROGMEM enq_combo[] = {F_CTLQ, SCLN_Q, COMBO_END};
const uint16_t PROGMEM hebq_combo[] = {KC_G, KC_DOT, COMBO_END};
const uint16_t PROGMEM tabq_combo[] = {KC_K, A_ALTQ, COMBO_END};
const uint16_t PROGMEM delq_combo[] = {KC_H, KC_D, COMBO_END};

combo_t key_combos[] = {
    [RU_COMBO] = COMBO(ru_combo, RUS_LANG),
    [EN_COMBO] = COMBO(en_combo, EN_LANG),
    [HEB_COMBO] = COMBO(heb_combo, HEB_LANG),
    [TAB_COMBO] = COMBO(tab_combo, KC_TAB),
    [DEL_COMBO] = COMBO(del_combo, KC_DEL),

    [RUQ_COMBO] = COMBO(ruq_combo, RUS_LANG),
    [ENQ_COMBO] = COMBO(enq_combo, EN_LANG),
    [HEBQ_COMBO] = COMBO(hebq_combo, HEB_LANG),
    [TABQ_COMBO] = COMBO(tabq_combo, KC_TAB),
    [DELQ_COMBO] = COMBO(delq_combo, KC_DEL),
};


#ifdef OLED_ENABLE

void oled_render_layer_state(void) {
    oled_write_P(PSTR("layer: "), false);
    switch (get_highest_layer(layer_state|default_layer_state)) {
      case _QWERTY:
        oled_write_ln_P(PSTR("qwerty"), false);
        break;
      case _DVORAK:
        oled_write_ln_P(PSTR("dvorak"), false);
        break;
      case _SYMBOLS:
        oled_write_ln_P(PSTR("symbols"), false);
        break;
      case _NUMS:
        oled_write_ln_P(PSTR("numbers"), false);
        break;
      case _RIGHT:
        oled_write_ln_P(PSTR("right"), false);
        break;
      case _LEFT:
        oled_write_ln_P(PSTR("left"), false);
        break;
      default:
        oled_write_ln_P(PSTR("unknown"), false);
        break;
    }
}

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  return OLED_ROTATION_270;
}

bool oled_task_user(void) {
    if (is_keyboard_master()) {
      #ifdef LUNA
      render_luna();
      #endif
    } else {
      oled_write_ln_P(PSTR("nice cock"), false);
    }
    return false;
}

#endif // OLED_ENABLE

void keyboard_post_init_user(void) {
  config.raw = eeconfig_read_user();
  layer_on(_DVORAK);
}

void set_english_language(void) {
  layer_on(_DVORAK);
  tap_code16(LSFT(LCTL(LGUI(KC_1))));
}

void set_russian_language(void) {
  layer_off(_DVORAK);
  tap_code16(LSFT(LCTL(LGUI(KC_2))));
}

void set_hebrew_language(void) {
  layer_off(_DVORAK);
  tap_code16(LSFT(LCTL(LGUI(KC_3))));
}

void delete_word(void) {
  if (config.is_win) {
    tap_code16(C(KC_BSPC));
  } else {
    tap_code16(A(KC_BSPC));
  }
}

#define PRESS_OR_RELEASE(key_pressed_action, key_released_action) \
  if (record->event.pressed) {                                    \
    key_pressed_action;                                           \
  } else {                                                        \
    key_released_action;                                          \
  }

#define CASE_MOD_TAP_KEY_HOLD(keycode, key_hold_pressed_action, key_hold_released_action) \
  case (keycode):                                                                         \
    if (!record->tap.count) {                                                             \
      PRESS_OR_RELEASE(key_hold_pressed_action, key_hold_released_action)                 \
      passthrough = false;                                                                \
    }                                                                                     \
    break;

#define CASE_MOD_TAP_KEY_TAP(keycode, key_tap) \
  case (keycode):                              \
    if (record->tap.count) {                   \
      PRESS_OR_RELEASE(key_tap, {})            \
      passthrough = false;                     \
    }                                          \
    break;

#define CASE(keycode, key_pressed_action, key_released_action) \
  case (keycode):                                              \
    PRESS_OR_RELEASE(key_pressed_action, key_released_action)  \
    passthrough = false;                                       \
    break;

#define CASE_PRESSED(keycode, key_pressed_action) CASE(keycode, key_pressed_action, {});

#define PEEK(keycode, key_pressed_action, key_released_action)  \
  case (keycode):                                               \
    PRESS_OR_RELEASE(key_pressed_action, key_released_action)   \
    break;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  #if defined OLED_ENABLE && defined LUNA
  luna_update_keypress_timer();
  #endif

  bool passthrough = true;
  switch (keycode) {
    CASE_PRESSED(EN_LANG, set_english_language());
    CASE_PRESSED(RUS_LANG, set_russian_language());
    CASE_PRESSED(HEB_LANG, set_hebrew_language());

    CASE_PRESSED(CHNGE_OS, {config.is_win ^= 1; eeconfig_update_user(config.raw);});
    CASE_MOD_TAP_KEY_TAP(RIGHT, delete_word());
    CASE_MOD_TAP_KEY_HOLD(F_CTLQ, {layer_on(_DVORAK); register_code(KC_LCTL);}, {layer_off(_DVORAK); unregister_code(KC_LCTL);});
    CASE_MOD_TAP_KEY_HOLD(S_GUIQ, {layer_on(_DVORAK); register_code(KC_LGUI);}, {layer_off(_DVORAK); unregister_code(KC_LGUI);});
    CASE_MOD_TAP_KEY_HOLD(L_GUIQ, {layer_on(_DVORAK); register_code(KC_RGUI);}, {layer_off(_DVORAK); unregister_code(KC_RGUI);});
    CASE_MOD_TAP_KEY_HOLD(J_CTLQ, {layer_on(_DVORAK); register_code(KC_RCTL);}, {layer_off(_DVORAK); unregister_code(KC_RCTL);});
    CASE_MOD_TAP_KEY_HOLD(A_ALTQ, {layer_on(_DVORAK); register_code(KC_LALT);}, {layer_off(_DVORAK); unregister_code(KC_LALT);});
    CASE_MOD_TAP_KEY_HOLD(SCLN_Q, {layer_on(_DVORAK); register_code(KC_RALT);}, {layer_off(_DVORAK); unregister_code(KC_RALT);});

    #if defined OLED_ENABLE && defined LUNA
    PEEK(LSFT_SP, luna_jump(), luna_stop_jumping());
    PEEK(RSFT_SP, luna_jump(), luna_stop_jumping());
    #endif
  }
  return passthrough;
}

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case NUMS:
    case SYMBOLS:
    case LEFT:
    case RIGHT:
    case A_ALT:
    case S_ALT:
    case A_ALTQ:
    case SCLN_Q:
      return TAPPING_TERM * 3;
    default:
      return TAPPING_TERM;
  }
}

bool get_hold_on_other_key_press(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case NUMS:
    case SYMBOLS:
      // Immediately select the hold action when another key is pressed.
      return true;
    default:
      // Do not select the hold action when another key is pressed.
      return false;
  }
}

bool get_tapping_force_hold(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    // Select hold action when key is held after tapping it. Istead of repeating the key.
    case SYMBOLS:
      return true;
    default:
        return false;
  }
}
