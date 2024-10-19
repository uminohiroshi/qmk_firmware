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
    _RAISE,
    _LOWER,
	_ADJUST,
    _NUMKEYS,
  	_L_MAX,  /* レイヤー最大数 */
};

enum custom_keycodes {
  K_ModClr = SAFE_RANGE,    // 全Modifierをクリア
};


#define K_R_SPC     LT(_RAISE, KC_SPC)      // raise + Space
#define K_L_BS      LT(_LOWER, KC_BSPC)     // lower + BS
#define K_L_ENT     LT(_LOWER, KC_ENT)      // lower + Enter
#define K_A_TAB     LT(_ADJUST, KC_TAB)     // adjust + tab
#define K_A_AT      LT(_ADJUST, JP_AT)      // adjust + @
#define K_N_F13     LT(_NUMKEYS, KC_F13)    // numkeys + F13
//#define K_N_LEAD    TD(LEAD_LAYR)           // numkeys + LEADER
#define K_N_F14     LT(_NUMKEYS, KC_F14)    // numkeys + F14
#define K_C_CLN     RCTL_T(JP_COLN)         // CTL  + :
#define K_S_BSL     RSFT_T(JP_BSLS)         // SFT  + "
#define K_S_CIRC    RSFT_T(JP_CIRC)
//KC_LCPO   LCTL + "
//KC_RCPC   RCTL + '

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

// 下段モディファイア
//#define K_G_Z       LGUI_T(KC_Z)
//#define K_A_X       LALT_T(KC_X)
//#define K_C_C       LCTL_T(KC_C)
//#define K_S_V       LSFT_T(KC_V)

//#define K_S_M       RSFT_T(KC_M)
//#define K_C_COMM    RCTL_T(KC_COMM)
//#define K_A_DOT     RALT_T(KC_DOT)
//#define K_G_SLSH    RGUI_T(JP_SLSH)

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
// left side : left-right
const uint16_t PROGMEM cmb_tr[]       = {KC_T,     KC_R,     COMBO_END};
const uint16_t PROGMEM cmb_gf[]       = {K_CS_G,   K_S_F,    COMBO_END};
const uint16_t PROGMEM cmb_bv[]       = {KC_B,     KC_V,     COMBO_END};
const uint16_t PROGMEM cmb_re[]       = {KC_R,     KC_E,     COMBO_END};
const uint16_t PROGMEM cmb_fd[]       = {K_S_F,    K_C_D,    COMBO_END};
const uint16_t PROGMEM cmb_vc[]       = {KC_V,     KC_C,     COMBO_END};
const uint16_t PROGMEM cmb_ew[]       = {KC_E,     KC_W,     COMBO_END};
const uint16_t PROGMEM cmb_ds[]       = {K_C_D,    K_A_S,    COMBO_END};
const uint16_t PROGMEM cmb_cx[]       = {KC_C,     KC_X,     COMBO_END};
const uint16_t PROGMEM cmb_wq[]       = {KC_W,     KC_Q,     COMBO_END};
const uint16_t PROGMEM cmb_sa[]       = {K_A_S,    K_G_A,    COMBO_END};
const uint16_t PROGMEM cmb_xz[]       = {KC_X,     KC_Z,     COMBO_END};

// left size : diagonally above
const uint16_t PROGMEM cmb_gr[]       = {K_CS_G,   KC_R,     COMBO_END};
const uint16_t PROGMEM cmb_bf[]       = {KC_B,     K_S_F,    COMBO_END};
const uint16_t PROGMEM cmb_fe[]       = {K_S_F,    KC_E,     COMBO_END};
const uint16_t PROGMEM cmb_vd[]       = {KC_V,     K_C_D,    COMBO_END};
const uint16_t PROGMEM cmb_es[]       = {KC_E,     K_A_S,    COMBO_END};
const uint16_t PROGMEM cmb_dx[]       = {K_C_D,    KC_X,     COMBO_END};
const uint16_t PROGMEM cmb_wa[]       = {KC_W,     K_G_A,    COMBO_END};
const uint16_t PROGMEM cmb_sz[]       = {K_A_S,    KC_Z,     COMBO_END};

// right side : left-right
const uint16_t PROGMEM cmb_yu[]       = {KC_Y,     KC_U,     COMBO_END};
const uint16_t PROGMEM cmb_hj[]       = {K_CS_H,   K_S_J,    COMBO_END};
const uint16_t PROGMEM cmb_nm[]       = {KC_N,     KC_M,     COMBO_END};
const uint16_t PROGMEM cmb_ui[]       = {KC_U,     KC_I,     COMBO_END};
const uint16_t PROGMEM cmb_jk[]       = {K_S_J,    K_C_K,    COMBO_END};
const uint16_t PROGMEM cmb_mcomm[]    = {KC_M,     KC_COMM,  COMBO_END};
const uint16_t PROGMEM cmb_io[]       = {KC_I,     KC_O,     COMBO_END};
const uint16_t PROGMEM cmb_kl[]       = {K_C_K,    K_A_L,    COMBO_END};
const uint16_t PROGMEM cmb_commdot[]  = {KC_COMM,  KC_DOT,   COMBO_END};
const uint16_t PROGMEM cmb_op[]       = {KC_O,     KC_P,     COMBO_END};
const uint16_t PROGMEM cmb_lscln[]    = {K_A_L,    K_G_SCLN, COMBO_END};
const uint16_t PROGMEM cmb_dotslsh[]  = {KC_DOT,   KC_SLSH,  COMBO_END};

// left size : diagonally above
const uint16_t PROGMEM cmb_hu[]       = {K_CS_H,   KC_U,     COMBO_END};
const uint16_t PROGMEM cmb_nj[]       = {KC_N,     K_S_J,    COMBO_END};
const uint16_t PROGMEM cmb_ji[]       = {K_S_J,    KC_I,     COMBO_END};
const uint16_t PROGMEM cmb_mk[]       = {KC_M,     K_C_K,    COMBO_END};
const uint16_t PROGMEM cmb_il[]       = {KC_I,     K_A_L,    COMBO_END};
const uint16_t PROGMEM cmb_kdot[]     = {K_C_K,    KC_DOT,   COMBO_END};
const uint16_t PROGMEM cmb_oscln[]    = {KC_O,     K_G_SCLN, COMBO_END};
const uint16_t PROGMEM cmb_lslsh[]    = {K_A_L,    KC_SLSH,  COMBO_END};


// left side : up-down
const uint16_t PROGMEM cmb_tg[]       = {KC_T,     K_CS_G,   COMBO_END};
const uint16_t PROGMEM cmb_gb[]       = {K_CS_G,   KC_B,     COMBO_END};
const uint16_t PROGMEM cmb_rf[]       = {KC_R,     K_S_F,    COMBO_END};
const uint16_t PROGMEM cmb_fv[]       = {K_S_F,    KC_V,     COMBO_END};
const uint16_t PROGMEM cmb_ed[]       = {KC_E,     K_C_D,    COMBO_END};
const uint16_t PROGMEM cmb_dc[]       = {K_C_D,    KC_C,     COMBO_END};
const uint16_t PROGMEM cmb_ws[]       = {KC_W,     K_A_S,    COMBO_END};
const uint16_t PROGMEM cmb_sx[]       = {K_A_S,    KC_X,     COMBO_END};
const uint16_t PROGMEM cmb_qa[]       = {KC_Q,     K_G_A,    COMBO_END};
const uint16_t PROGMEM cmb_az[]       = {K_G_A,    KC_Z,     COMBO_END};
const uint16_t PROGMEM cmb_tablctl[]  = {K_A_TAB,  KC_LCTL,  COMBO_END};
const uint16_t PROGMEM cmb_lctllsft[] = {KC_LCTL,  KC_LSFT,  COMBO_END};

// right side : up-down
const uint16_t PROGMEM cmb_yh[]       = {KC_Y,     K_CS_H,   COMBO_END};
const uint16_t PROGMEM cmb_hn[]       = {K_CS_H,   KC_N,     COMBO_END};
const uint16_t PROGMEM cmb_uj[]       = {KC_U,     K_S_J,    COMBO_END};
const uint16_t PROGMEM cmb_jm[]       = {K_S_J,    KC_M,     COMBO_END};
const uint16_t PROGMEM cmb_ik[]       = {KC_I,     K_C_K,    COMBO_END};
const uint16_t PROGMEM cmb_kcomm[]    = {K_C_K,    KC_COMM,  COMBO_END};
const uint16_t PROGMEM cmb_ol[]       = {KC_O,     K_A_L,    COMBO_END};
const uint16_t PROGMEM cmb_ldot[]     = {K_A_L,    KC_DOT,   COMBO_END};
const uint16_t PROGMEM cmb_pscln[]    = {KC_P,     K_G_SCLN, COMBO_END};
const uint16_t PROGMEM cmb_sclnslsh[] = {K_G_SCLN, KC_SLSH,  COMBO_END};
const uint16_t PROGMEM cmb_atcln[]    = {K_A_AT,   K_C_CLN,  COMBO_END};
const uint16_t PROGMEM cmb_clnbsl[]   = {K_C_CLN,  K_S_BSL,  COMBO_END};

combo_t key_combos[] = {
    // quick-speed left-side
    COMBO(cmb_re, KC_ENT),
    COMBO(cmb_fd, QK_REPEAT_KEY),
    COMBO(cmb_vc, LCTL(KC_V)),

    // quick-speed right-side
    COMBO(cmb_ui, KC_BSPC),
    COMBO(cmb_jk, JP_LPRN),
    COMBO(cmb_mcomm, JP_LBRC),

    // middle-speed left-side
    COMBO(cmb_ew, KC_ESC),
    COMBO(cmb_ds, KC_TAB),
    COMBO(cmb_cx, LCTL(KC_C)),

    // middle-speed right-side
    COMBO(cmb_io, KC_DEL),
    COMBO(cmb_kl, JP_RPRN),
    COMBO(cmb_commdot, JP_RBRC),

    // slow-speed left-side
    COMBO(cmb_wq, KC_TAB),
    COMBO(cmb_sa, KC_LCTL),
    COMBO(cmb_xz, KC_LSFT),

    // slow-speed right-side
    COMBO(cmb_op, JP_AT),
    COMBO(cmb_lscln, JP_COLN),
    COMBO(cmb_dotslsh, JP_BSLS),

    // 上下 left-side
    COMBO(cmb_tg, JP_PERC),
    COMBO(cmb_gb, JP_TILD),
    COMBO(cmb_rf, JP_DLR),
    COMBO(cmb_fv, JP_EQL),
    COMBO(cmb_ed, JP_HASH),
    COMBO(cmb_dc, JP_BSLS),
    COMBO(cmb_ws, JP_AT),
    COMBO(cmb_sx, LSFT(JP_AT)),
    COMBO(cmb_qa, JP_EXLM),

    // 上下 right-side
    COMBO(cmb_yh, JP_CIRC),
    COMBO(cmb_hn, JP_UNDS),
    COMBO(cmb_uj, JP_PLUS),
    COMBO(cmb_jm, JP_MINS),
    COMBO(cmb_ik, JP_ASTR),
    COMBO(cmb_kcomm, JP_SLSH),
    COMBO(cmb_ol, JP_AMPR),
    COMBO(cmb_ldot, JP_PIPE),
};

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


/*----------------------------------------------------------------------------------*/
/* KeyMap                                                                           */
/*----------------------------------------------------------------------------------*/
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_DEFAULT] = LAYOUT( \
    //,--------+--------+---------+--------+---------+--------.   ,--------+---------+--------+---------+--------+--------.
        K_A_TAB, KC_Q   , KC_W    , KC_E   , KC_R    , KC_T   ,     KC_Y   , KC_U    , KC_I   , KC_O    , KC_P   , K_A_AT ,
    //|--------+--------+---------+--------+---------+--------|   |--------+---------+--------+---------+--------+--------|
        KC_LCTL, K_G_A  , K_A_S   , K_C_D  , K_S_F   , K_CS_G ,     K_CS_H , K_S_J   , K_C_K  , K_A_L   ,K_G_SCLN, K_C_CLN,
    //|--------+--------+---------+--------+---------+--------|   |--------+---------+--------+---------+--------+--------|
        KC_LSFT, KC_Z   , KC_X    , KC_C   , KC_V    , KC_B   ,     KC_N   , KC_M    , KC_COMM, KC_DOT  ,KC_SLSH, K_S_BSL,
    //`--------+--------+---------+--------+---------+--------/   \--------+---------+--------+---------+--------+--------'
                          KC_LALT , K_L_BS , K_R_SPC ,K_N_F13 ,    K_N_F14 , K_R_SPC , K_L_ENT, KC_RALT
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
        KC_F12 ,  KC_F1  , KC_F2  , KC_F3  , KC_F4   , KC_F5  ,     KC_F6  , KC_F7   , KC_F8  , KC_F9   , KC_F10 , KC_F11 ,
    //,--------+--------+---------+--------+---------+--------.   ,--------+---------+--------+---------+--------+--------.
        _______,  JP_1  , JP_2    , JP_3   , JP_4    , JP_5   ,     JP_6   , JP_7    , JP_8   , JP_9    , JP_0   , KC_RCTL,
    //,--------+--------+---------+--------+---------+--------.   ,--------+---------+--------+---------+--------+--------.
        _______, KC_INS , KC_PAUS , KC_F14 , KC_F13  , KC_PSCR,    K_A_PSCR, KC_F13  , KC_F14 , KC_LSCR ,K_ModClr, KC_RSFT,
    //,--------+--------+---------+--------+---------+--------.   ,--------+---------+--------+---------+--------+--------.
                          _______ , _______, _______ , _______,     _______, _______ , _______, _______
    //                 `----------+--------+---------+--------'   `--------+---------+--------+---------'
    ),

    [_NUMKEYS] = LAYOUT( \
    //,--------+--------+---------+--------+---------+--------.   ,--------+---------+--------+---------+--------+--------.
        KC_TAB , DM_REC1, DM_REC2 , KC_NO  , KC_NO   , KC_NO  ,     KC_NO  , KC_NO   , KC_NO  , KC_NO   , KC_NO  , KC_NO  ,
    //,--------+--------+---------+--------+---------+--------.   ,--------+---------+-------- +--------+--------+--------.
        _______, DM_PLY1, DM_PLY2 , KC_NO  , KC_NO   , KC_NO  ,     KC_NO  , KC_NO   , KC_NO  , KC_NO   , KC_NO  , KC_NO  ,
    //,--------+--------+---------+--------+---------+--------.   ,--------+---------+------- -+--------+--------+--------.
        _______, DM_RSTP, DM_RSTP , KC_NO  , KC_NO   , KC_NO  ,     KC_NO  , KC_NO   , KC_NO  , KC_NO   , KC_NO  , KC_NO  ,
    //,--------+--------+---------+--------+---------+--------.   ,--------+---------+--------+---------+--------+--------.
                          _______ , _______, _______ , _______,     _______, _______ , _______, _______
    //                 `----------+--------+---------+--------'   `--------+---------+--------+---------'
    ),

    [_ADJUST] = LAYOUT( \
    //,--------+--------+---------+--------+---------+--------.   ,--------+---------+--------+---------+--------+--------.
        _______, KC_NO  , KC_NO   , KC_NO  , KC_NO   , QK_BOOT,     QK_BOOT, KC_NO   , KC_NO  , KC_NO   , KC_NO  , _______,
    //,--------+--------+---------+--------+---------+--------.   ,--------+---------+--------+---------+--------+--------.
        _______, KC_NO  , KC_NO   , KC_NO  , KC_NO   , SH_TOGG,     SH_TOGG, KC_NO   , KC_NO  , KC_NO   , KC_NO  , _______,
    //,--------+--------+---------+--------+---------+--------.   ,--------+---------+--------+---------+--------+--------.
        _______, KC_NO  , KC_NO   , KC_NO  , KC_NO   , KC_NO  ,     KC_NO  , KC_NO   , KC_NO  , KC_NO   , KC_NO  , _______,
    //,--------+--------+---------+--------+---------+--------.   ,--------+---------+--------+---------+--------+--------.
                          QK_BOOT , _______, _______ , _______,     _______, _______ , _______, QK_BOOT
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
    case K_R_SPC:
    case K_L_BS:
    case K_L_ENT:
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
    // low row mod
    //case K_G_Z:
    //case K_A_X:
    //case K_C_C:
    //case K_S_V:
    //case K_S_M:
    //case K_C_COMM:
    //case K_A_DOT:
    //case K_G_SLSH:
    // home row mod
    case K_G_A:
    case K_A_S:
    case K_C_D:
    case K_S_F:
    case K_S_J:
    case K_C_K:
    case K_A_L:
    case K_G_SCLN:
    // space
    //case K_R_SPC:
    //case K_L_BS:
    //case K_L_ENT:
        return true;
        break;
    default:
        return false;
    }
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
