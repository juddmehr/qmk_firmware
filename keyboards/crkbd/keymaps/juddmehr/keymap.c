//includes:
#include "keymap.h"
#include <stdio.h>

// Tap Dance declarations
enum {
    TD_COLN_BSLS,
    TD_MINUS_UNDER,
    TD_LBRACKET_LBRACE,
    TD_RBRACKET_RBRACE,
    TD_DEL,
};

// Tap Dance definitions
tap_dance_action_t tap_dance_actions[] = {
    [TD_COLN_BSLS] = ACTION_TAP_DANCE_DOUBLE(KC_COLN, KC_BSLS),
    [TD_MINUS_UNDER] = ACTION_TAP_DANCE_DOUBLE(KC_MINUS, KC_UNDERSCORE),
    [TD_LBRACKET_LBRACE] = ACTION_TAP_DANCE_DOUBLE(KC_LEFT_BRACKET, KC_LEFT_CURLY_BRACE),
    [TD_RBRACKET_RBRACE] = ACTION_TAP_DANCE_DOUBLE(KC_RIGHT_BRACKET, KC_RIGHT_CURLY_BRACE),
    [TD_DEL] = ACTION_TAP_DANCE_DOUBLE(KC_BSPC, KC_DELWRD),
};

//KEYMAP
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
// QWERTY LAYER
  [QWERTY] = LAYOUT_split_3x6_3(
    //ROW 1
        KC_ESC,  KC_Q,  KC_W,  KC_E,  KC_R,  KC_T,  KC_Y,  KC_U,  KC_I,  KC_O,  KC_P,  KC_BSLS,
    //ROW 2
        KC_TAB,  LCTL_T(KC_A),  LOPT_T(KC_S),  CMD_T(KC_D),  LSFT_T(KC_F),  KC_G,  KC_H,  LSFT_T(KC_J),  CMD_T(KC_K),  LOPT_T(KC_L),  LCTL_T(KC_SCLN),  KC_QUOT,
    //ROW 3
        KC_CAPS,  KC_Z,  KC_X,  KC_C,  KC_V,  KC_B,  KC_N,  KC_M,  KC_COMM,  KC_DOT,  KC_SLSH,  KC_GRV,
    //THUMBS
        LT(MEDIA,KC_DEL),  LT(NUM,KC_BSPC),  KC_ENT,  LT(TNAV,KC_TAB),  LT(NAV,KC_SPC),  LT(FUN,  KC_ESC)
  ),
// MEDIA LAYER
  [MEDIA] = LAYOUT_split_3x6_3(
    //ROW 1
        KC_EJCT,  U_NU,  U_NU,  KC_KB_VOLUME_UP,  U_NU,  U_NU,  U_NU,  U_NU,  KC_KB_VOLUME_UP,  U_NU,  U_NU,  KC_EJCT,
    //ROW 2
        U_NU,  U_NU,  KC_MPRV,  KC_KB_VOLUME_DOWN,  KC_MNXT,  U_NU,  U_NU,  KC_MPRV,  KC_KB_VOLUME_DOWN,  KC_MNXT,  U_NU,  U_NU,
    //ROW 3
        U_NU,  U_NU,  U_NU,  U_NU,  U_NU,  U_NU,  U_NU,  U_NU,  U_NU,  U_NU,  U_NU,  U_NU,
    //THUMBS
        U_NA,  U_NA,  U_NA,  KC_MSTP,  KC_MPLY,  KC_MUTE
  ),
// NAVIGATION LAYER
  [NAV] = LAYOUT_split_3x6_3(
    //ROW 1
        U_NU,  U_NU,  U_NU,  U_NU,  U_NU,  U_NU,  KC_HOME,  KC_PAGE_DOWN,  KC_PAGE_UP,  KC_END,  KC_INS,  U_NU,
    //ROW 2
        U_NU,  KC_UNDO,  KC_CUT,  KC_COPY,  KC_PASTE,  KC_AGIN,  KC_LEFT,  KC_DOWN,  KC_UP,  KC_RIGHT,  TD(TD_COLN_BSLS),  U_NU,
    //ROW 3
        U_NU,  U_NU,  U_NU,  U_NU,  U_NU,  U_NU,  KC_AGIN,  KC_PASTE,  KC_COPY,  KC_CUT,  KC_UNDO,  U_NU,
    //THUMBS
        U_NA,  U_NA,  U_NA,  U_NU,  U_NU,  U_NU
  ),
// NUMBERS LAYER
  [NUM] = LAYOUT_split_3x6_3(
    //ROW 1
        TD(TD_LBRACKET_LBRACE), KC_EXLM,  KC_AT,  KC_HASH,  KC_DLR,  KC_PERC,    KC_CIRC,  KC_AMPR,  KC_ASTR,  KC_LPRN, KC_RPRN, TD(TD_RBRACKET_RBRACE),
    //ROW 2
        TD(TD_MINUS_UNDER), LCTL_T(KC_1), LOPT_T(KC_2), CMD_T(KC_3), LSFT_T(KC_4), KC_5,     KC_6, LSFT_T(KC_7), CMD_T(KC_8), LOPT_T(KC_9), LCTL_T(KC_0), KC_EQL,
    //ROW 3
        U_NU,  U_NU,  U_NU,  U_NU,  U_NU,  U_NU,    U_NU,  U_NU,  KC_COMM, KC_DOT, KC_SCLN, U_NU,
    //THUMBS
        U_NA,  U_NA,  U_NA, KC_TAB, LSFT_T(KC_SPC), KC_ENT
  ),
// FUNCTION LAYER
  [FUN] = LAYOUT_split_3x6_3(
    //ROW 1
         U_NU, KC_F12,  KC_F7,  KC_F8,  KC_F9,  KC_PSCR,  U_NU,  U_NU,  U_NU,  U_NU,  U_NU,  U_NU,
    //ROW 2
         U_NU, KC_F11,  KC_F4,  KC_F5,  KC_F6,  KC_PAUS,  U_NU, KC_LSFT,  KC_LCMD,  KC_LOPT,  KC_LCTL,  U_NU,
    //ROW 3
         U_NU, KC_F10,  KC_F1,  KC_F2,  KC_F3,  KC_SCRL,  U_NU,  U_NU,  U_NU,  U_NU,  U_NU,  U_NU,
    //THUMBS
        U_NU,  U_NU,  U_NU,  U_NA,  U_NA,  U_NA
  ),
// TERMINAL NAVIGATION LAYER
  [TNAV] = LAYOUT_split_3x6_3(
    //ROW 1
        U_NU,  U_NU,  U_NU,  U_NU,  U_NU,  U_NU,  U_NU,  U_NU,  U_NU,  U_NU,  U_NU,  U_NU,
    //ROW 2
        U_NU, U_NU, U_NU, U_NU, U_NU, U_NU, KC_BACKWORD,  KC_TOLINEEND,  KC_TOLINEBEGIN,  KC_FOREWORD,  U_NU,  U_NU,
    //ROW 3
        U_NU,  U_NU,  U_NU,  U_NU,  U_NU,  U_NU,  U_NU,  U_NU,  U_NU,  U_NU,  U_NU,  U_NU,
    //THUMBS
        U_NA,  U_NA,  U_NA,  U_NU,  U_NU,  U_NU
  ),
};
