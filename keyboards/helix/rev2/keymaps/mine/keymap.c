/* Copyright 2020 yushakobo
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
#include "bootloader.h"
#ifdef PROTOCOL_LUFA
#include "lufa.h"
#include "split_util.h"
#endif
#ifdef AUDIO_ENABLE
  #include "audio.h"
#endif


// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.

#include "keymap_jp.h"  // JPキーボードシンボル

enum layer_number {
    _DEFAULT = 0,
    _RAISE,
    _LOWER,
	_ADJUST,
  	_L_MAX,  /* レイヤー最大数 */
};

#define K_R_SPC     LT(_RAISE, KC_SPC)      // raise + Space
#define K_L_BS      LT(_LOWER, KC_BSPC)     // lower + BS
#define K_L_ENT     LT(_LOWER, KC_ENT)      // lower + Enter
#define K_A_TAB     LT(_ADJUST, KC_TAB)     // adjust + tab
#define K_A_AT      LT(_ADJUST, JP_AT)      // adjust + @
#define K_C_CLN     RCTL_T(JP_COLN)         // CTL  + :
#define K_S_BSL     RSFT_T(JP_BSLS)         // SFT  + "\"
#define K_C_F13     LCTL_T(KC_F13)          // CTL  + F13(launcher)
#define K_S_PSCR    LSFT_T(KC_PSCR)
#define K_S_CIRC    RSFT_T(JP_CIRC)
//KC_LCPO   LCTL + "
//KC_RCPC   RCTL + '

// 下段モディファイア
#define K_G_Z       LGUI_T(KC_Z)
#define K_A_X       LALT_T(KC_X)
#define K_C_C       LCTL_T(KC_C)
#define K_S_V       LSFT_T(KC_V)

#define K_S_M       RSFT_T(KC_M)
#define K_C_COMM    RCTL_T(KC_COMM)
#define K_A_DOT     RALT_T(KC_DOT)
#define K_G_SLSH    RGUI_T(JP_SLSH)

// RGB制御
int RGB_current_mode;


#if 0
// コンボキー定義
enum combos {
  FS_LWIN,
  FD_LALT,
  FA_LSFT,
  JK_RWIN,
  JL_RALT,
  JSCLN_RSFT,
};

const uint16_t PROGMEM fs_lwin[] = {KC_F, KC_S, COMBO_END};
const uint16_t PROGMEM fd_lalt[] = {KC_F, KC_D, COMBO_END};
const uint16_t PROGMEM fa_lsft[] = {KC_F, KC_A, COMBO_END};
const uint16_t PROGMEM jk_rwin[] = {KC_J, KC_K, COMBO_END};
const uint16_t PROGMEM jl_ralt[] = {KC_J, KC_L, COMBO_END};
const uint16_t PROGMEM jscln_rsft[] = {KC_J, JP_SCLN, COMBO_END};

combo_t key_combos[COMBO_COUNT] = {
  [FS_LWIN] = COMBO(fs_lwin, KC_LWIN),
  [FD_LALT] = COMBO(fd_lalt, KC_LALT),
  [FA_LSFT] = COMBO(fa_lsft, KC_LSFT),
  [JK_RWIN] = COMBO(jk_rwin, KC_RWIN),
  [JL_RALT] = COMBO(jl_ralt, KC_RALT),
  [JSCLN_RSFT] = COMBO(jscln_rsft, KC_RSFT),
};
#endif



#if MATRIX_ROWS == 8 // HELIX_ROWS == 4

// スワップハンド定義
const keypos_t hand_swap_config[MATRIX_ROWS][MATRIX_COLS] = {
  {{0, 4}, {1, 4}, {2, 4}, {3, 4}, {4, 4}, {5, 4}, {6, 4}}, 
  {{0, 5}, {1, 5}, {2, 5}, {3, 5}, {4, 5}, {5, 5}, {6, 5}}, 
  {{0, 6}, {1, 6}, {2, 6}, {3, 6}, {4, 6}, {5, 6}, {6, 6}}, 
  {{0, 7}, {1, 7}, {2, 7}, {3, 7}, {4, 7}, {5, 7}, {6, 7}}, 
  {{0, 0}, {1, 0}, {2, 0}, {3, 0}, {4, 0}, {5, 0}, {6, 0}}, 
  {{0, 1}, {1, 1}, {2, 1}, {3, 1}, {4, 1}, {5, 1}, {6, 1}}, 
  {{0, 2}, {1, 2}, {2, 2}, {3, 2}, {4, 2}, {5, 2}, {6, 2}}, 
  {{0, 3}, {1, 3}, {2, 3}, {3, 3}, {4, 3}, {5, 3}, {6, 3}}, 
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_DEFAULT] = LAYOUT( \
    //,--------+--------+--------+--------+--------+--------.                 ,--------+--------+--------+--------+--------+--------.
        K_A_TAB, KC_Q   , KC_W   , KC_E   , KC_R   , KC_T   ,                   KC_Y   , KC_U   , KC_I   , KC_O   , KC_P   , K_A_AT ,
    //,--------+--------+--------+--------+--------+--------.                 ,--------+--------+--------+--------+--------+--------.
        K_C_F13, KC_A   , KC_S   , KC_D   , KC_F   , KC_G   ,                   KC_H   , KC_J   , KC_K   , KC_L   ,JP_SCLN , K_C_CLN,
    //,--------+--------+--------+--------+--------+--------.                 ,--------+--------+--------+--------+--------+--------.
        KC_LSFT, K_G_Z  , K_A_X  , K_C_C  , K_S_V  , KC_B   ,                   KC_N   , K_S_M  ,K_C_COMM, K_A_DOT,K_G_SLSH, K_S_BSL,
    //,--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------.
        KC_LCTL, SH_MON , KC_LWIN, KC_LALT, K_L_BS , K_R_SPC, KC_LWIN, KC_RWIN, K_R_SPC, K_L_ENT, KC_RALT, KC_RWIN, SH_MON , KC_RCTL  \
    //,--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------.
    ),

    [_RAISE] = LAYOUT( \
    //,--------+--------+--------+--------+--------+--------.                 ,--------+--------+--------+--------+--------+--------.
        JP_PIPE, KC_F14 , KC_HOME, KC_UP  , KC_END , KC_PGUP,                   JP_LBRC, JP_LPRN, JP_RPRN, JP_RBRC, JP_MINS, JP_EQL , \
    //,--------+--------+--------+--------+--------+--------.                 ,--------+--------+--------+--------+--------+--------.
        KC_LCPO,JP_ZKHK ,KC_LEFT ,KC_DOWN ,KC_RGHT , KC_PGDN,                   KC_BSPC, KC_ESC , KC_DEL , JP_HENK, JP_MHEN, KC_RCPC, \
    //,--------+--------+--------+--------+--------+--------.                 ,--------+--------+--------+--------+--------+--------.
       K_S_PSCR, JP_EXLM, JP_HASH, JP_DLR , JP_PERC, JP_TILD,                   JP_UNDS, KC_ENT , JP_LCBR, JP_RCBR, JP_AMPR,K_S_CIRC, \
    //,--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------.
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______  \
    //,--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------.
    ),

    [_LOWER] = LAYOUT( \
    //,--------+--------+--------+--------+--------+--------.                 ,--------+--------+--------+--------+--------+--------.
        KC_F12 , KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_F5  ,                   KC_F6  , KC_F7  , KC_F8  , KC_F9  , KC_F10 , KC_F11 , \
    //,--------+--------+--------+--------+--------+--------.                 ,--------+--------+--------+--------+--------+--------.
        KC_LCTL, JP_1   , JP_2   , JP_3   , JP_4   , JP_5                     , JP_6   , JP_7   , JP_8   , JP_9   , JP_0   , KC_RCTL, \
    //,--------+--------+--------+--------+--------+--------.                 ,--------+--------+--------+--------+--------+--------.
        KC_LSFT, _______, _______, _______, _______, _______                  , _______, _______, _______, _______, _______, KC_RSFT, \
    //,--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------.
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______  \
    //,--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------.
    ),

    [_ADJUST] = LAYOUT( \
    //,--------+--------+--------+--------+--------+--------.                 ,--------+--------+--------+--------+--------+--------.
        _______, KC_NO  , KC_NO  , KC_NO  , KC_NO  , RESET                    , RESET  , RGB_MOD,RGB_RMOD, RGB_HUI, RGB_HUD, _______, \
    //,--------+--------+--------+--------+--------+--------.                 ,--------+--------+--------+--------+--------+--------.
        _______,RGB_M_SN,RGB_M_SW, RGB_M_R, RGB_M_B, RGB_TOG                  , RGB_TOG, RGB_SPI, RGB_SPD, RGB_SAI, RGB_SAD, _______, \
    //,--------+--------+--------+--------+--------+--------.                 ,--------+--------+--------+--------+--------+--------.
        _______, RGB_M_T, RGB_M_G, RGB_M_X, RGB_M_K, RGB_M_P                  , KC_NO  , RGB_VAI, RGB_VAD, KC_NO  , KC_NO  , _______, \
    //,--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------.
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______  \
    //,--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------.
    ),
};
#else
#error "undefined keymaps"
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
        return true;
    default:
        return false;
    }
}


/*----------------------------------------------------------------------------------*/
/* モッドタップ割り込みの無視                                                       */
/* (通常キーに配置したモッドタップは割り込みを禁止する)                             */
/*----------------------------------------------------------------------------------*/
bool get_ignore_mod_tap_interrupt(uint16_t keycode, keyrecord_t *record) {
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

#ifdef SSD1306OLED
  #include "ssd1306.h"
#endif

void matrix_init_user(void) {
    #ifdef RGBLIGHT_ENABLE
      RGB_current_mode = rgblight_get_mode();
    #endif
    //SSD1306 OLED init, make sure to add #define SSD1306OLED in config.h
    #ifdef SSD1306OLED
        iota_gfx_init(!has_usb());   // turns on the display
    #endif
}


