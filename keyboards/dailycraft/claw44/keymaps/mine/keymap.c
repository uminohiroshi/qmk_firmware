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

#define TAPPING_TERM_LONG   (300)

enum layer_number {
    _DEFAULT = 0,
    _DEFAULT2,
    _LOWER,
    _RAISE,
	_ADJUST,
    _NAVI,
    _NAVI2,
  	_L_MAX,  /* レイヤー最大数 */
};

enum custom_keycodes {
  K_ModClr = SAFE_RANGE,    // 全Modifierをクリア
};

// mod-tap, layer-tap
#define K_L_SPC     LT(_LOWER, KC_SPC)      // lower + Space
#define K_R_BS      LT(_RAISE, KC_BSPC)     // raise + BS
#define K_R_ENT     LT(_RAISE, KC_ENT)      // raise + Enter
#define K_A_TAB     LT(_ADJUST, KC_TAB)     // adjust + tab
#define K_A_AT      LT(_ADJUST, JP_AT)      // adjust + @
#define K_N_F13     LT(_NAVI, KC_F13)       // navi + F13
//#define K_N_LEAD    TD(LEAD_LAYR)           // LEADER
#define K_N_F14     LT(_NAVI2, KC_F14)      // navi + F14
#define K_C_CLN     RCTL_T(JP_COLN)         // CTL + :
#define K_S_BSL     RSFT_T(JP_BSLS)         // SFT + "\"
#define K_S_CIRC    RSFT_T(JP_CIRC)         // SFT + "^"
//KC_LCPO   LCTL + "
//KC_RCPC   RCTL + '

#define K_DF        DF(_DEFAULT)
#define K_DF2       DF(_DEFAULT2)

// home row mod
#define K_G_A       LGUI_T(KC_A)
#define K_A_S       LALT_T(KC_S)
#define K_C_D       LCTL_T(KC_D)
#define K_S_F       LSFT_T(KC_F)
#define K_CS_G      C_S_T(KC_G)     // LSFT+LCTL

#define K_CS_H      RCS_T(KC_H)     // RSFT+RCTL
#define K_S_J       RSFT_T(KC_J)
#define K_C_K       RCTL_T(KC_K)
#define K_A_L       RALT_T(KC_L)
#define K_G_SCLN    RGUI_T(JP_SCLN)

// bottom row mod
#define K_G_Z       LGUI_T(KC_Z)
#define K_A_X       LALT_T(KC_X)
#define K_C_C       LCTL_T(KC_C)
#define K_S_V       LSFT_T(KC_V)
#define K_CS_B      C_S_T(KC_B)     // LSFT+LCTL

#define K_CS_N      RCS_T(KC_N)     // RSFT+RCTL
#define K_S_M       RSFT_T(KC_M)
#define K_C_COMM    RCTL_T(KC_COMM)
#define K_A_DOT     RALT_T(KC_DOT)
#define K_G_SLSH    RGUI_T(JP_SLSH)

//
#define K_A_PSCR    LALT(KC_PSCR)


#if 0 //DYNAMIC_MACRO_ENABLE
/*----------------------------------------------------------------------------------*/
/* for Dynamic Macro                                                                */
/*----------------------------------------------------------------------------------*/
bool isRecording = false;
#endif // DYNAMIC_MACRO_ENABLE


// swap hand
const keypos_t PROGMEM hand_swap_config[MATRIX_ROWS][MATRIX_COLS] = {
  {{0, 4}, {1, 4}, {2, 4}, {3, 4}, {4, 4}, {5, 4}},
  {{0, 5}, {1, 5}, {2, 5}, {3, 5}, {4, 5}, {5, 5}},
  {{0, 6}, {1, 6}, {2, 6}, {3, 6}, {4, 6}, {5, 6}},
  {{0, 7}, {1, 7}, {2, 7}, {3, 7}, {4, 7}, {5, 7}},
  {{0, 0}, {1, 0}, {2, 0}, {3, 0}, {4, 0}, {5, 0}},
  {{0, 1}, {1, 1}, {2, 1}, {3, 1}, {4, 1}, {5, 1}},
  {{0, 2}, {1, 2}, {2, 2}, {3, 2}, {4, 2}, {5, 2}},
  {{0, 3}, {1, 3}, {2, 3}, {3, 3}, {4, 3}, {5, 3}},
};

#if 0
/*----------------------------------------------------------------------------------*/
/* for Tap-Dance                                                                    */
/*----------------------------------------------------------------------------------*/
// Define a type for as many tap dance states as you need
typedef enum {
    TD_NONE,
    TD_UNKNOWN,
    TD_SINGLE_TAP,
    TD_SINGLE_HOLD,
    TD_DOUBLE_TAP
} td_state_t;

typedef struct {
    bool is_press_action;
    td_state_t state;
} td_tap_t;

enum {
    LEAD_LAYR, // Our custom tap dance key; add any other tap dance keys to this enum
};

// Declare the functions to be used with your tap dance key(s)

// Function associated with all tap dances
td_state_t cur_dance(tap_dance_state_t *state);

// Functions associated with individual tap dances
void ql_finished(tap_dance_state_t *state, void *user_data);
void ql_reset(tap_dance_state_t *state, void *user_data);
#endif

// for Combo
// left top
const uint16_t PROGMEM cmb_tabq[]     = {KC_TAB,   KC_Q,     COMBO_END};
const uint16_t PROGMEM cmb_qw[]       = {KC_Q,     KC_W,     COMBO_END};
const uint16_t PROGMEM cmb_we[]       = {KC_W,     KC_E,     COMBO_END};
const uint16_t PROGMEM cmb_er[]       = {KC_E,     KC_R,     COMBO_END};
const uint16_t PROGMEM cmb_rt[]       = {KC_R,     KC_T,     COMBO_END};
// left home
const uint16_t PROGMEM cmb_capsa[]    = {KC_LCTL,  KC_A,     COMBO_END};
const uint16_t PROGMEM cmb_as[]       = {KC_A,     KC_S,     COMBO_END};
const uint16_t PROGMEM cmb_sd[]       = {KC_S,     KC_D,     COMBO_END};
const uint16_t PROGMEM cmb_df[]       = {KC_D,     KC_F,     COMBO_END};
const uint16_t PROGMEM cmb_fg[]       = {KC_F,     KC_G,     COMBO_END};
// left bottom
const uint16_t PROGMEM cmb_lsftz[]    = {KC_LSFT,  KC_Z,     COMBO_END};
const uint16_t PROGMEM cmb_zx[]       = {KC_Z,     KC_X,     COMBO_END};
const uint16_t PROGMEM cmb_xc[]       = {KC_X,     KC_C,     COMBO_END};
const uint16_t PROGMEM cmb_cv[]       = {KC_C,     KC_V,     COMBO_END};
const uint16_t PROGMEM cmb_vb[]       = {KC_V,     KC_B,     COMBO_END};
// right top
const uint16_t PROGMEM cmb_yu[]       = {KC_Y,     KC_U,     COMBO_END};
const uint16_t PROGMEM cmb_ui[]       = {KC_U,     KC_I,     COMBO_END};
const uint16_t PROGMEM cmb_io[]       = {KC_I,     KC_O,     COMBO_END};
const uint16_t PROGMEM cmb_op[]       = {KC_O,     KC_P,     COMBO_END};
const uint16_t PROGMEM cmb_pat[]      = {KC_P,     JP_AT,    COMBO_END};
// right home
const uint16_t PROGMEM cmb_hj[]       = {KC_H,     KC_J,     COMBO_END};
const uint16_t PROGMEM cmb_jk[]       = {KC_J,     KC_K,     COMBO_END};
const uint16_t PROGMEM cmb_kl[]       = {KC_K,     KC_L,     COMBO_END};
const uint16_t PROGMEM cmb_lscln[]    = {KC_L,     JP_SCLN,  COMBO_END};
const uint16_t PROGMEM cmb_sclncln[]  = {JP_SCLN,  JP_COLN,  COMBO_END};
// right bottom
const uint16_t PROGMEM cmb_nm[]       = {KC_N,     KC_M,     COMBO_END};
const uint16_t PROGMEM cmb_mcomm[]    = {KC_M,     KC_COMM,  COMBO_END};
const uint16_t PROGMEM cmb_commdot[]  = {KC_COMM,  KC_DOT,   COMBO_END};
const uint16_t PROGMEM cmb_dotslsh[]  = {KC_DOT,   JP_SLSH,  COMBO_END};
const uint16_t PROGMEM cmb_slshbsl[]  = {JP_SLSH,  JP_BSLS,  COMBO_END};

combo_t key_combos[] = {
    // left top
    COMBO(cmb_qw, KC_MENU),
    COMBO(cmb_we, KC_ESC),
    COMBO(cmb_er, KC_ENT),
    COMBO(cmb_rt, KC_DEL),
    // right top

    COMBO(cmb_yu, MS_BTN1),
    COMBO(cmb_ui, MS_WHLU),
    COMBO(cmb_io, MS_WHLD),
    COMBO(cmb_op, MS_BTN2),
    COMBO(cmb_pat, MS_BTN3),
};

uint16_t get_combo_term(uint16_t index, combo_t *combo) {

    return COMBO_TERM;
}

/*
uint16_t get_combo_term(uint16_t index, combo_t *combo) {
    uint16_t combo_term = COMBO_TERM;
    bool need_continue = false;
    switch(combo->keycode) {
        // quick-speed left-side
        case KC_ENT:
        case QK_REPEAT_KEY:
        case LCTL(KC_V):
            combo_term = 15;
            break;

        // quick-speed right-side
        case KC_BSPC:
        case JP_LPRN:
        case JP_LBRC:
            combo_term = 15;
            break;

        // middle-speed left-side
        case KC_ESC:
        case KC_TAB:
        case LCTL(KC_C):
            combo_term = 15;
            break;

        // middle-speed left-side
        case KC_DEL:
        case JP_RPRN:
        case JP_RBRC:
            combo_term = 15;
            break;

        // slow speed left side
        //case KC_TAB:
        case KC_LCTL:
        case KC_LSFT:
            combo_term = 30;
            break;

        // slow speed right side
        //case JP_AT:
        case JP_COLN:
        //case JP_BSLS:
            combo_term = 30;
            break;

        // 上下 left-side
        case JP_PERC:
        case JP_TILD:
        case JP_DLR:
        case JP_EQL:
        case JP_HASH:
        case JP_BSLS:
        case JP_AT:
        case LSFT(JP_AT):
        case JP_EXLM:
            combo_term=100;   // 上下comoboは受付長くする。
            break;

        // 上下 right-side
        case JP_CIRC:
        case JP_UNDS:
        case JP_PLUS:
        case JP_MINS:
        case JP_ASTR:
        case JP_SLSH:
        case JP_AMPR:
        case JP_PIPE:
            combo_term=100;   // 上下comoboは受付長くする。
            break;
        default:
            need_continue = true;
    }

    if(need_continue) {
        switch(combo->keys[0]) {
            // 小指
            case KC_Q:
            case K_G_A:
            case KC_Z:
            case KC_P:
            case K_G_SCLN:
            case KC_SLSH:
                combo_term = 50;
            // 薬指
            case KC_W:
            case K_A_S:
            case KC_X:
            case KC_O:
            case K_A_L:
            case KC_DOT:
                combo_term = 50;
            // 中指
            case KC_E:
            case K_C_D:
            case KC_C:
            case KC_I:
            case K_C_K:
            case KC_COMM:
                combo_term = 25;
            // その他
            default:
                combo_term = COMBO_TERM;
        }
    }

    return combo_term;
}
*/

/*----------------------------------------------------------------------------------*/
/* KeyMap                                                                           */
/*----------------------------------------------------------------------------------*/
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_DEFAULT] = LAYOUT( \
    //,--------+--------+---------+--------+---------+--------.   ,--------+---------+--------+---------+--------+--------.
        KC_TAB , KC_Q   , KC_W    , KC_E   , KC_R    , KC_T   ,     KC_Y   , KC_U    , KC_I   , KC_O    , KC_P   , K_A_AT ,
    //|--------+--------+---------+--------+---------+--------|   |--------+---------+--------+---------+--------+--------|
        KC_LCTL, K_G_A  , K_A_S   , K_C_D  , K_S_F   , K_CS_G ,     K_CS_H , K_S_J   , K_C_K  , K_A_L   ,K_G_SCLN, K_C_CLN,
    //|--------+--------+---------+--------+---------+--------|   |--------+---------+--------+---------+--------+--------|
        KC_LSFT, KC_Z   , KC_X    , KC_C   , KC_V    , KC_B   ,     KC_N   , KC_M    , KC_COMM, KC_DOT  , KC_SLSH, K_S_BSL,
    //`--------+--------+---------+--------+---------+--------/   \--------+---------+--------+---------+--------+--------'
                          KC_LALT , K_R_BS , K_L_SPC ,K_N_F13 ,    K_N_F14 , K_L_SPC , K_R_ENT, KC_RALT
    //                 `----------+--------+---------+--------'   `--------+---------+--------+---------'
    ),

    [_DEFAULT2] = LAYOUT( \
    //,--------+--------+---------+--------+---------+--------.   ,--------+---------+--------+---------+--------+--------.
        _______, KC_Q   , KC_W    , KC_E   , KC_R    , KC_T   ,     KC_Y   , KC_U    , KC_I   , KC_O    , KC_P   , _______,
    //|--------+--------+---------+--------+---------+--------|   |--------+---------+--------+---------+--------+--------|
        _______, KC_A   , KC_S    , KC_D   , KC_F    , KC_G   ,     KC_H   , KC_J    , KC_K   , KC_L    , KC_SCLN, _______,
    //|--------+--------+---------+--------+---------+--------|   |--------+---------+--------+---------+--------+--------|
        _______, KC_Z   , KC_X    , KC_C   , KC_V    , KC_B   ,     KC_N   , KC_M    , KC_COMM, KC_DOT  , KC_SLSH, _______,
    //`--------+--------+---------+--------+---------+--------/   \--------+---------+--------+---------+--------+--------'
                          _______ , _______, _______ ,_______ ,    _______ , _______ , _______, _______
    //                 `----------+--------+---------+--------'   `--------+---------+--------+---------'
    ),

    [_LOWER] = LAYOUT( \
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

    [_RAISE] = LAYOUT( \
    //,--------+--------+---------+--------+---------+--------.   ,--------+---------+--------+---------+--------+--------.
        KC_F12 ,  KC_F1  , KC_F2  , KC_F3  , KC_F4   , KC_F5  ,     KC_F6  , KC_F7   , KC_F8  , KC_F9   , KC_F10 , KC_F11 ,
    //,--------+--------+---------+--------+---------+--------.   ,--------+---------+--------+---------+--------+--------.
        _______,  JP_1  , JP_2    , JP_3   , JP_4    , JP_5   ,     JP_6   , JP_7    , JP_8   , JP_9    , JP_0   , KC_RCTL,
    //,--------+--------+---------+--------+---------+--------.   ,--------+---------+--------+---------+--------+--------.
        _______,  KC_NO ,  KC_NO  ,  KC_NO ,  KC_NO  , KC_PSCR,    K_A_PSCR,  KC_NO  ,  KC_NO ,  KC_NO  ,K_ModClr, KC_RSFT,
    //,--------+--------+---------+--------+---------+--------.   ,--------+---------+--------+---------+--------+--------.
                          _______ , _______, _______ , _______,     _______, _______ , _______, _______
    //                 `----------+--------+---------+--------'   `--------+---------+--------+---------'
    ),

    [_ADJUST] = LAYOUT( \
    //,--------+--------+---------+--------+---------+--------.   ,--------+---------+--------+---------+--------+--------.
        KC_NO  , KC_NO  , KC_NO   , KC_NO  , KC_NO   , QK_BOOT,     QK_BOOT, KC_NO   , KC_NO  , KC_NO   , KC_NO  , KC_NO  ,
    //,--------+--------+---------+--------+---------+--------.   ,--------+---------+--------+---------+--------+--------.
        KC_NO  , KC_NO  , KC_NO   , KC_NO  , KC_NO   , KC_NO  ,     KC_NO  , KC_NO   , KC_NO  , KC_NO   , K_DF   , KC_NO  ,
    //,--------+--------+---------+--------+---------+--------.   ,--------+---------+--------+---------+--------+--------.
        KC_NO  , KC_NO  , KC_NO   , KC_PAUS, KC_LSCR , KC_INS ,     KC_NO  , KC_NO   , KC_NO  , KC_NO   , K_DF2  , KC_NO  ,
    //,--------+--------+---------+--------+---------+--------.   ,--------+---------+--------+---------+--------+--------.
                          _______ , _______, _______ , _______,     _______, _______ , _______, _______
    //                 `----------+--------+---------+--------'   `--------+---------+--------+---------'
    ),

    [_NAVI] = LAYOUT( \
    //,--------+--------+---------+--------+---------+--------.   ,--------+---------+--------+---------+--------+--------.
        KC_TAB , DM_REC1, DM_REC2 , KC_NO  , KC_NO   , KC_NO  ,     MS_WHLU, MS_BTN1 , MS_UP  , MS_BTN3 , MS_BTN2, KC_NO  ,
    //,--------+--------+---------+--------+---------+--------.   ,--------+---------+-------- +--------+--------+--------.
        _______, DM_PLY1, DM_PLY2 , KC_NO  , KC_NO   , KC_NO  ,     MS_WHLD, MS_LEFT , MS_DOWN, MS_RGHT , KC_NO  , KC_NO  ,
    //,--------+--------+---------+--------+---------+--------.   ,--------+---------+------- -+--------+--------+--------.
        _______, DM_RSTP, DM_RSTP , KC_NO  , KC_NO   , KC_NO  ,     MS_WHLL, MS_WHLR , KC_NO  , KC_NO   , KC_NO  , KC_NO  ,
    //,--------+--------+---------+--------+---------+--------.   ,--------+---------+--------+---------+--------+--------.
                          _______ , _______, _______ , _______,     _______, _______ , _______, _______
    //                 `----------+--------+---------+--------'   `--------+---------+--------+---------'
    ),

    [_NAVI2] = LAYOUT( \
    //,--------+--------+---------+--------+---------+--------.   ,--------+---------+--------+---------+--------+--------.
        KC_TAB , DM_REC1, DM_REC2 , KC_NO  , KC_NO   , KC_NO  ,     MS_WHLU, MS_BTN1 , MS_UP  , MS_BTN3 , MS_BTN2, KC_NO  ,
    //,--------+--------+---------+--------+---------+--------.   ,--------+---------+-------- +--------+--------+--------.
        _______, DM_PLY1, DM_PLY2 , KC_NO  , KC_NO   , KC_NO  ,     MS_WHLD, MS_LEFT , MS_DOWN, MS_RGHT , KC_NO  , KC_NO  ,
    //,--------+--------+---------+--------+---------+--------.   ,--------+---------+------- -+--------+--------+--------.
        _______, DM_RSTP, DM_RSTP , KC_NO  , KC_NO   , KC_NO  ,     MS_WHLL, MS_WHLR , KC_NO  , KC_NO   , KC_NO  , KC_NO  ,
    //,--------+--------+---------+--------+---------+--------.   ,--------+---------+--------+---------+--------+--------.
                          _______ , _______, _______ , _______,     _______, _______ , _______, _______
    //                 `----------+--------+---------+--------'   `--------+---------+--------+---------'
    ),
};

#ifdef OLED_ENABLE

void render_layer_state(void) {
    switch (get_highest_layer(layer_state)) {
        case _DEFAULT:
            oled_write_ln_P(PSTR("Layer: Default"), false);
            break;
        case _LOWER:
            oled_write_ln_P(PSTR("Layer: Lower"), false);
            break;
        case _RAISE:
            oled_write_ln_P(PSTR("Layer: Raise"), false);
            break;
        case _ADJUST:
            oled_write_ln_P(PSTR("Layer: Adjust"), false);
            break;
        case _NAVI:
            oled_write_ln_P(PSTR("Layer: Navi"), false);
            break;
        case _NAVI2:
            oled_write_ln_P(PSTR("Layer: Navi"), false);
            break;
        default:
            oled_write_ln_P(PSTR("Layer: Undefined"), false);
            break;
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
    snprintf(keylog_str, sizeof(keylog_str), "%dx%d 0x%04x:%c", record->event.key.row, record->event.key.col, keycode, name);

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
        #if 0 // DYNAMIC_MACRO_ENABLE
        oled_write_ln_P(PSTR("REC"), isRecording);  // DYNAMIC MACRO

        #endif // DYNAMIC_MACRO_ENABLE
        oled_write_ln(read_keylog(), false);
        oled_write_ln(read_keylogs(), false);
    } else {
        render_logo();
    }
    return false;
}

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (!is_keyboard_master()) return OLED_ROTATION_180;
    return rotation;
}
#endif


#ifdef KEY_LOGGING
#define TIME_MEASURE_MAX    (32000u)
#define TIME_DIFF_NONE      (0xffffu)
uint16_t lastEventTime;
bool isTimeMeasuring = false;
#endif

/*----------------------------------------------------------------------------------*/
/* キーon/off時の独自処理                                                               */
/*----------------------------------------------------------------------------------*/
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
#ifdef OLED_ENABLE
    // OLED出力
    if (record->event.pressed) {
        set_keylog(keycode, record);
    }
#endif

    switch(keycode)
    {
        case K_ModClr:
            if(record->event.pressed) {
                // send all up events
                unregister_code(KC_LSFT);
                unregister_code(KC_LALT);
                unregister_code(KC_LWIN);
                unregister_code(KC_RCTL);
                unregister_code(KC_RSFT);
                unregister_code(KC_RALT);
                unregister_code(KC_RWIN);
                unregister_code(KC_LCTL);
            }
            break;
        default:
            break;
    }

#ifdef KEY_LOGGING
    {
        uint16_t    diff_time;
        if(isTimeMeasuring) {
            diff_time = timer_elapsed(lastEventTime);
        }
        else {
            diff_time = TIME_DIFF_NONE;
        }

        // 次回計測準備
        lastEventTime = timer_read();
        isTimeMeasuring = true;

        // シリアル出力
        if (record->event.pressed) {
            uprintf("%d,%d,%d,%d,d\n", record->event.key.row, record->event.key.col, keycode, diff_time);
        } else {
            uprintf("%d,%d,%d,%d,u\n", record->event.key.row, record->event.key.col, keycode, diff_time);
        }
    }
#endif

    return true;
}


#ifdef KEY_LOGGING
void matrix_scan_user(void) {
   if (isTimeMeasuring
      && (timer_elapsed(lastEventTime) > TIME_MEASURE_MAX)
   ) {
      isTimeMeasuring = false;
   }
}
#endif

/*----------------------------------------------------------------------------------*/
/* hold動作時間の設定(親指・小指キーは長めにする)                                   */
/*----------------------------------------------------------------------------------*/

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    const uint8_t row = record->event.key.row;
    const uint8_t col = record->event.key.col;
    if((col <= 1) || (row == 3) || (row == 7)) {        // col == 0,1 or row == 3, 7
        return TAPPING_TERM_LONG;
    }
    else {
        return TAPPING_TERM;
        switch (keycode) {
        case QK_TAP_DANCE ... QK_TAP_DANCE_MAX:
            return 275;
        default:
            return TAPPING_TERM;
        }
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
    // thumb row
    case K_L_SPC:
    case K_R_BS:
    case K_R_ENT:
    case K_N_F13:
    //case K_N_LEAD:
    case K_N_F14:
    // top row
    case K_A_TAB:
    case K_A_AT:
    // home row
    case K_C_CLN:
    // low row
    case K_S_BSL:
    case K_S_CIRC:
        return true;
        break;
    default:
        return false;
        break;
    }
}


/*----------------------------------------------------------------------------------*/
/* 許容ホールド                                                                     */
/* (通常キーに配置したモッドタップは許容ホールド設定する)                           */
/*----------------------------------------------------------------------------------*/
bool get_permissive_hold(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    // bottom row mod
    case K_G_Z:
    case K_A_X:
    case K_C_C:
    case K_S_V:
    case K_CS_B:
    case K_CS_N:
    case K_S_M:
    case K_C_COMM:
    case K_A_DOT:
    case K_G_SLSH:
    // home row mod
    case K_G_A:
    case K_A_S:
    case K_C_D:
    case K_S_F:
    case K_CS_G:
    case K_CS_H:
    case K_S_J:
    case K_C_K:
    case K_A_L:
    case K_G_SCLN:
    // space
    //case K_L_SPC:
    //case K_R_BS:
    //case K_R_ENT:
        return true;
        break;
    default:
        return false;
    }
}

/*----------------------------------------------------------------------------------*/
/* 同時押しレイヤー定義                                                                  */
/*----------------------------------------------------------------------------------*/
layer_state_t layer_state_set_user(layer_state_t state) {
    return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

#if 0 // DYNAMIC_MACRO_ENABLE
/*----------------------------------------------------------------------------------*/
/* Dynamic Macro                                                                    */
/*----------------------------------------------------------------------------------*/
// Triggered when you start recording a macro.
void dynamic_macro_record_start_user(int8_t direction) {
    isRecording = true;
}

// Triggered when the macro recording is stopped.
void dynamic_macro_record_end_user(int8_t direction) {
    isRecording = false;
}
#endif // DYNAMIC_MACRO_ENABLE

#if 0 /* LEADER key */
/*----------------------------------------------------------------------------------*/
/* leader-key                                                                       */
/*----------------------------------------------------------------------------------*/
void leader_start_user(void) {
    // Do something when the leader key is pressed
}

void leader_end_user(void) {
    {
        /* 通常キーは [F13]+[キー]にして送る */
        uint16_t kc;
        for( kc=KC_A; kc<=KC_0; kc++) {
            if (leader_sequence_one_key(kc)) {
                register_code(KC_F13);
                tap_code(kc);
                unregister_code(KC_F13);
                break;
            }
        }
    }
}
#endif

#if 0 /* TAP_DANCE */
/*----------------------------------------------------------------------------------*/
/* TapDance                                                                         */
/*----------------------------------------------------------------------------------*/
// Determine the current tap dance state
td_state_t cur_dance(tap_dance_state_t *state) {
    if (state->count == 1) {
        if (!state->pressed) return TD_SINGLE_TAP;
        else return TD_SINGLE_HOLD;
    } else if (state->count == 2) return TD_DOUBLE_TAP;
    else return TD_UNKNOWN;
};

// Initialize tap structure associated with example tap dance key
static td_tap_t ql_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

// Functions that control what our tap dance key does
void ql_finished(tap_dance_state_t *state, void *user_data) {
    ql_tap_state.state = cur_dance(state);
    switch (ql_tap_state.state) {
        case TD_SINGLE_TAP:
            leader_start();
            break;
        case TD_SINGLE_HOLD:
            layer_on(_NUMKEYS);
            break;
        case TD_DOUBLE_TAP:
            // Check to see if the layer is already set
            if (layer_state_is(_NUMKEYS)) {
                // If already set, then switch it off
                layer_off(_NUMKEYS);
            } else {
                // If not already set, then switch the layer on
                layer_on(_NUMKEYS);
            }
            break;
        default:
            break;
    }
}

void ql_reset(tap_dance_state_t *state, void *user_data) {
    // If the key was held down and now is released then switch off the layer
    if (ql_tap_state.state == TD_SINGLE_HOLD) {
        layer_off(_NUMKEYS);
    }
    ql_tap_state.state = TD_NONE;
}

// Associate our tap dance key with its functionality
tap_dance_action_t tap_dance_actions[] = {
    [LEAD_LAYR] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, ql_finished, ql_reset)
};
#endif
