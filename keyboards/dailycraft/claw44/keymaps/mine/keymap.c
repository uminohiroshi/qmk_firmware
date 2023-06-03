/*
Copyright 2012 Jun Wako <wakojun@gmail.com>
Copyright 2015 Jack Humbert
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.
This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H
#include <stdio.h>

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.

#include "keymap_japanese.h"  // JPキーボードシンボル

enum layer_number {
    _DEFAULT = 0,
    _RAISE,
    _LOWER,
	_ADJUST,
    _NUMKEYS,
  	_L_MAX,  /* レイヤー最大数 */
};

enum custom_keycodes {
  K_Mac1 = SAFE_RANGE,
};


#define K_R_SPC     LT(_RAISE, KC_SPC)      // raise + Space
#define K_L_BS      LT(_LOWER, KC_BSPC)     // lower + BS
#define K_L_ENT     LT(_LOWER, KC_ENT)      // lower + Enter
#define K_A_TAB     LT(_ADJUST, KC_TAB)     // adjust + tab
#define K_A_AT      LT(_ADJUST, JP_AT)      // adjust + @
#define K_N_F13     LT(_NUMKEYS, KC_F13)    // numkeys + F13
#define K_N_F14     LT(_NUMKEYS, KC_F14)    // numkeys + F14
#define K_C_CLN     RCTL_T(JP_COLN)         // CTL  + :
#define K_S_BSL     RSFT_T(JP_BSLS)         // SFT  + "\"
#define K_S_CIRC    RSFT_T(JP_CIRC)
//KC_LCPO   LCTL + "
//KC_RCPC   RCTL + '

// home row mod
#define K_G_A       LGUI_T(KC_A)
#define K_A_S       LALT_T(KC_S)
#define K_C_D       LCTL_T(KC_D)
#define K_S_F       LSFT_T(KC_F)

#define K_S_J       RSFT_T(KC_J)
#define K_C_K       RCTL_T(KC_K)
#define K_A_L       RALT_T(KC_L)
#define K_G_SCLN    RGUI_T(JP_SCLN)

// 下段モディファイア
#define K_G_Z       LGUI_T(KC_Z)
#define K_A_X       LALT_T(KC_X)
#define K_C_C       LCTL_T(KC_C)
#define K_S_V       LSFT_T(KC_V)

#define K_S_M       RSFT_T(KC_M)
#define K_C_COMM    RCTL_T(KC_COMM)
#define K_A_DOT     RALT_T(KC_DOT)
#define K_G_SLSH    RGUI_T(JP_SLSH)

//
#define K_A_PSCR    LALT(KC_PSCR)



const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_DEFAULT] = LAYOUT( \
    //,--------+--------+---------+--------+---------+--------.   ,--------+---------+--------+---------+--------+--------.
        K_A_TAB, KC_Q   , KC_W    , KC_E   , KC_R    , KC_T   ,     KC_Y   , KC_U    , KC_I   , KC_O    , KC_P   , K_A_AT ,
    //|--------+--------+---------+--------+---------+--------|   |--------+---------+--------+---------+--------+--------|
        KC_LCTL, K_G_A  , K_A_S   , K_C_D  , K_S_F   , KC_G   ,     KC_H   , K_S_J   , K_C_K  , K_A_L   ,K_G_SCLN, K_C_CLN,
    //|--------+--------+---------+--------+---------+--------|   |--------+---------+--------+---------+--------+--------|
        KC_LSFT, K_G_Z  , K_A_X   , K_C_C  , K_S_V   , KC_B   ,     KC_N   , K_S_M   ,K_C_COMM, K_A_DOT ,K_G_SLSH, K_S_BSL,
    //`--------+--------+---------+--------+---------+--------/   \--------+---------+--------+---------+--------+--------'
                          KC_LALT , K_L_BS , K_R_SPC , K_N_F13,    K_N_F14 , K_R_SPC , K_L_ENT, KC_RALT
    //                 `----------+--------+---------+--------'   `--------+---------+--------+---------'
    ),

    [_RAISE] = LAYOUT( \
    //,--------+--------+---------+--------+---------+--------.   ,--------+---------+--------+---------+--------+--------
       JP_PIPE , JP_DQUO, KC_HOME , KC_UP  , KC_END  , KC_PGUP,    JP_LBRC , JP_LPRN , JP_RPRN, JP_RBRC , JP_MINS, JP_EQL ,
    //,--------+--------+---------+--------+---------+--------.   ,--------+---------+--------+---------+--------+--------.
        _______, JP_ZKHK, KC_LEFT , KC_DOWN, KC_RGHT , KC_PGDN,    KC_BSPC , KC_ESC  , KC_DEL , JP_HENK , JP_MHEN, SC_RCPC,
    //,--------+--------+---------+--------+---------+--------.   ,--------+---------+--------+---------+--------+--------.
        _______, JP_EXLM, JP_HASH , JP_DLR , JP_PERC , JP_TILD,    JP_UNDS , KC_ENT , JP_LCBR , JP_RCBR , JP_AMPR,K_S_CIRC,
    //,--------+--------+---------+--------+---------+--------.   ,--------+---------+--------+---------+--------+--------.
                           _______, _______,  _______, _______,     _______,  _______, _______,  _______
    //                 `----------+--------+---------+--------'   `--------+---------+--------+---------'
    ),

    [_LOWER] = LAYOUT( \
    //,--------+--------+---------+--------+---------+--------.   ,--------+---------+--------+---------+--------+--------.
        KC_F12 , KC_F1  ,  KC_F2  , KC_F3  , KC_F4   , KC_F5  ,     KC_F6  , KC_F7   , KC_F8  , KC_F9   , KC_F10 , KC_F11 ,
    //,--------+--------+---------+--------+---------+--------.   ,--------+---------+--------+---------+--------+--------.
        _______,  JP_1  , JP_2    , JP_3   , JP_4    , JP_5   ,     JP_6   , JP_7    , JP_8   , JP_9    , JP_0   , KC_RCTL,
    //,--------+--------+---------+--------+---------+--------.   ,--------+---------+--------+---------+--------+--------.
        _______, KC_SPC , KC_PAUS , KC_F14 , KC_F13  , KC_PSCR,    K_A_PSCR, KC_F13  , KC_F14 , KC_LSCR , KC_SPC , KC_RSFT,
    //,--------+--------+---------+--------+---------+--------.   ,--------+---------+--------+---------+--------+--------.
                          _______ , _______, _______ , _______,     _______, _______ , _______, _______
    //                 `----------+--------+---------+--------'   `--------+---------+--------+---------'
    ),

    [_NUMKEYS] = LAYOUT( \
    //,--------+--------+---------+--------+---------+--------.   ,--------+---------+--------+---------+--------+--------.
        KC_TAB , KC_F9  , KC_F10  , KC_F11 , KC_F12  , KC_NO  ,     JP_LPRN, JP_7   ,  JP_8   , JP_9    , JP_MINS, JP_RPRN,
    //,--------+--------+---------+--------+---------+--------.   ,--------+---------+--------+---------+--------+--------.
        _______, KC_F5  , KC_F6   , KC_F7  , KC_F8   , KC_ESC ,     JP_0   , JP_4    , JP_5   , JP_6    , JP_PLUS, KC_ENT ,
    //,--------+--------+---------+--------+---------+--------.   ,--------+---------+--------+---------+--------+--------.
        _______, KC_F1  , KC_F2   , KC_F3  , KC_F4   , JP_EQL ,     JP_DOT , JP_1    , JP_2   , JP_3    , JP_ASTR, JP_SLSH,
    //,--------+--------+---------+--------+---------+--------.   ,--------+---------+--------+---------+--------+--------.
                          _______ , _______, _______ , _______,     _______, _______ , _______, _______
    //                 `----------+--------+---------+--------'   `--------+---------+--------+---------'
    ),

    [_ADJUST] = LAYOUT( \
    //,--------+--------+---------+--------+---------+--------.   ,--------+---------+--------+---------+--------+--------.
        _______, KC_NO  , KC_NO   , KC_NO  , KC_NO   , QK_RBT ,     QK_RBT , KC_NO   , KC_NO  , KC_NO   , KC_NO  , _______,
    //,--------+--------+---------+--------+---------+--------.   ,--------+---------+--------+---------+--------+--------.
        _______, KC_NO  , KC_NO   , KC_NO  , KC_NO   , KC_NO  ,     KC_NO  , KC_NO   , KC_NO  , KC_NO   , KC_NO  , _______,
    //,--------+--------+---------+--------+---------+--------.   ,--------+---------+--------+---------+--------+--------.
        _______, KC_NO  , KC_NO   , KC_NO  , KC_NO   , KC_NO  ,     KC_NO  , KC_NO   , KC_NO  , KC_NO   , KC_NO  , _______,
    //,--------+--------+---------+--------+---------+--------.   ,--------+---------+--------+---------+--------+--------.
                          QK_RBT  , _______, _______ , _______,     _______, _______ , _______, QK_RBT
    //                 `----------+--------+---------+--------'   `--------+---------+--------+---------'
    ),
};

#ifdef OLED_ENABLE

void render_layer_state(void) {
    switch (get_highest_layer(layer_state)) {
        case _DEFAULT:
            oled_write_ln_P(PSTR("Layer: Default"), false);
            break;
        case _RAISE:
            oled_write_ln_P(PSTR("Layer: Raise"), false);
            break;
        case _LOWER:
            oled_write_ln_P(PSTR("Layer: Lower"), false);
            break;
        case _NUMKEYS:
            oled_write_ln_P(PSTR("Layer: Numkeys"), false);
            break;
        case _ADJUST:
            oled_write_ln_P(PSTR("Layer: Adjust"), false);
            break;
        default:
            oled_write_ln_P(PSTR("Layer: Undefined"), false);
    }
}

void render_logo(void) {
    static const char PROGMEM logo[] = {0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f, 0x90, 0x91, 0x92, 0x93, 0x94, 0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xaf, 0xb0, 0xb1, 0xb2, 0xb3, 0xb4, 0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf, 0xd0, 0xd1, 0xd2, 0xd3, 0xd4, 0};
    oled_write_P(logo, false);
}

char keylog_str[24]  = {};
char keylogs_str[21] = {};
int  keylogs_str_idx = 0;

const char code_to_name[60] = {' ', ' ', ' ', ' ', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', 'R', 'E', 'B', 'T', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ';', '\'', ' ', ',', '.', '/', ' ', ' ', ' '};

void set_keylog(uint16_t keycode, keyrecord_t *record) {
    char name = ' ';
    if (keycode < 60) {
        name = code_to_name[keycode];
    }

    // update keylog
    snprintf(keylog_str, sizeof(keylog_str), "%dx%d, k%2d : %c", record->event.key.row, record->event.key.col, keycode, name);

    // update keylogs
    if (keylogs_str_idx == sizeof(keylogs_str) - 1) {
        keylogs_str_idx = 0;
        for (int i = 0; i < sizeof(keylogs_str) - 1; i++) {
            keylogs_str[i] = ' ';
        }
    }

    keylogs_str[keylogs_str_idx] = name;
    keylogs_str_idx++;
}

const char *read_keylog(void) { return keylog_str; }
const char *read_keylogs(void) { return keylogs_str; }

bool oled_task_user(void) {
    if (is_keyboard_master()) {
        render_layer_state();
        oled_write_ln(read_keylog(), false);
        oled_write_ln(read_keylogs(), false);
    } else {
        render_logo();
    }
    return false;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        set_keylog(keycode, record);
    }

    switch(keycode)
    {
        case K_Mac1:
            if(record->event.pressed) {
                // send all up events
                tap_code(KC_LSFT);
                tap_code(KC_LALT);
                tap_code(KC_LWIN);
                tap_code(KC_RCTL);
                tap_code(KC_RSFT);
                tap_code(KC_RALT);
                tap_code(KC_RWIN);
                tap_code(KC_LCTL);
            }

    }

    return true;
}

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (!is_keyboard_master()) return OLED_ROTATION_180;
    return rotation;
}

#endif


/*----------------------------------------------------------------------------------*/
/* hold動作時間の設定(親指・小指キーは長めにする)                                   */
/*----------------------------------------------------------------------------------*/
#define TAPPING_TERM_LONG   (300)

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    const uint8_t row = record->event.key.row;
    const uint8_t col = record->event.key.col;
    if((col <= 1) || (row == 3) || (row == 7)) {        // col == 0,1 or row == 3, 7
        return TAPPING_TERM_LONG;
    }
    else {
        return TAPPING_TERM;
    }
}



/*----------------------------------------------------------------------------------*/
/* layerキーを短時間でrolling入力したときlayerキーとして動作させる                  */
/* (設定変更しないと短時間入力はtapとして解釈されてしまう)                          */
/*----------------------------------------------------------------------------------*/
bool get_hold_on_other_key_press(uint16_t keycode, keyrecord_t *record) {
    // recordの row, colを使うと正しく判定できないので keycodeを使う
    // const uint8_t row = record->event.key.row;
    // const uint8_t col = record->event.key.col;

    switch(keycode) {
    case K_R_SPC:
    case K_L_BS:
    case K_L_ENT:
    case K_N_F13:
    case K_N_F14:
    case K_A_TAB:
    case K_A_AT:
    case K_C_CLN:
    case K_S_CIRC:
        return true;
        break;
    default:
        return false;
        break;
    }
}


/*----------------------------------------------------------------------------------*/
/* タッピング強制ホールド無視                                                       */
/* (tap→holdと入力した時に hold機能とする)                                         */
/*----------------------------------------------------------------------------------*/
bool get_tapping_force_hold(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case K_R_SPC:
    case K_L_BS:
    case K_L_ENT:
    case K_N_F13:
    case K_N_F14:
    case K_A_TAB:
    case K_A_AT:
    case K_C_CLN:
    case K_S_CIRC:
        return true;
    default:
        return false;
    }
}

/*----------------------------------------------------------------------------------*/
/* 許容ホールド                                                                     */
/* (通常キーに配置したモッドタップは許容ホールド設定する)                           */
/*----------------------------------------------------------------------------------*/
bool get_permissive_hold(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case K_G_Z:
    case K_A_X:
    case K_C_C:
    case K_S_V:
    case K_S_M:
    case K_C_COMM:
    case K_A_DOT:
    case K_G_SLSH:
        return true;
        break;
    default:
        return false;
    }
}

