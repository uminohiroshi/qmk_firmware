#include QMK_KEYBOARD_H

#include "keymap_japanese.h"  // JPキーボードシンボル

enum layer_number {
    _DEFAULT = 0,
    _DEFAULT2,
    _LOWER,
    _RAISE,
	_ADJUST,
    _NAVI,
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
#define K_N_F14     LT(_NAVI, KC_F14)       // navi + F14
#define K_C_CLN     RCTL_T(JP_COLN)         // CTL + :
#define K_S_BSL     RSFT_T(JP_BSLS)         // SFT + "\"
#define K_S_CIRC    RSFT_T(JP_CIRC)         // SFT + "^"
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

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_DEFAULT] = LAYOUT( \
    //,--------+--------+--------+--------+--------+--------+--------+                          .--------+--------+--------+--------+--------+--------+--------.
        KC_ESC , KC_1   , KC_2   , KC_3   , KC_4   , KC_5   , KC_PSCR                           , JP_CIRC, KC_6   , KC_7   , KC_8   , KC_9   , KC_0   ,JP_MINS ,
    //,--------+--------+--------+--------+--------+--------+--------+                          .--------+--------+--------+--------+--------+--------+--------.
        KC_TAB , KC_Q   , KC_W   , KC_E   , KC_R   , KC_T   , KC_ESC                            , JP_LBRC, KC_Y   , KC_U   , KC_I   , KC_O   , KC_P   , JP_AT  ,
    //,--------+--------+--------+--------+--------+--------+--------+                          .--------+--------+--------+--------+--------+--------+--------.
        KC_LCTL, K_G_A  , K_A_S  , K_C_D  , K_S_F  , K_CS_G , KC_INS                            , JP_RBRC, K_CS_H , K_S_J  , K_C_K  , K_A_L  ,K_G_SCLN, K_C_CLN,
    //,--------+--------+--------+--------+--------+--------+--------+                          .--------+--------+--------+--------+--------+--------+--------.
        KC_LSFT, K_G_Z  , K_A_X  , K_C_C  , K_S_V  , K_CS_B , KC_NO                             , KC_NO  , K_CS_H , K_S_M  ,K_C_COMM, K_A_DOT,K_G_SLSH, K_S_BSL,
    //,--------+--------+--------+--------+--------+--------+--------+--------+        .--------+--------+--------+--------+--------+--------+--------+--------.
        KC_LCTL, KC_LALT, KC_LWIN, KC_LALT         , K_R_BS , K_L_SPC, K_N_F13         , K_N_F14, K_L_SPC, K_R_ENT         , KC_RALT, KC_RWIN, KC_RALT, KC_RCTL
    //,--------+--------+--------+--------+--------+--------+--------+--------+        .--------+--------+--------+--------+--------+--------+--------+--------.
    ),

    [_DEFAULT2] = LAYOUT( \
    //,--------+--------+--------+--------+--------+--------+--------+                          .--------+--------+--------+--------+--------+--------+--------.
        _______, _______, _______, _______, _______, _______, _______                           , _______, _______, _______, _______, _______, _______,_______ ,
    //,--------+--------+--------+--------+--------+--------+--------+                          .--------+--------+--------+--------+--------+--------+--------.
        _______, KC_Q   , KC_W   , KC_E   , KC_R   , KC_T   , _______                           , _______, KC_Y   , KC_U   , KC_I   , KC_O   , KC_P   , _______,
    //,--------+--------+--------+--------+--------+--------+--------+                          .--------+--------+--------+--------+--------+--------+--------.
        _______, KC_A   , KC_S   , KC_D   , KC_F   , KC_G   , _______                           , _______, KC_H   , KC_J   , KC_K   , KC_L   , KC_SCLN, _______,
    //,--------+--------+--------+--------+--------+--------+--------+                          .--------+--------+--------+--------+--------+--------+--------.
        _______, KC_Z   , KC_X   , KC_C   , KC_V   , KC_B   , _______                           , _______, KC_N   , KC_M   ,KC_COMM , KC_DOT , KC_SLSH, _______,
    //,--------+--------+--------+--------+--------+--------+--------+--------+        .--------+--------+--------+--------+--------+--------+--------+--------.
        _______, _______, _______, _______         , _______, _______, _______         , _______, _______, _______         , _______, _______, _______, _______
    //,--------+--------+--------+--------+--------+--------+--------+--------+        .--------+--------+--------+--------+--------+--------+--------+--------.
    ),

    [_LOWER] = LAYOUT( \
    //,--------+--------+--------+--------+--------+--------+--------+                          .--------+--------+--------+--------+--------+--------+--------.
        KC_F12 , KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_F5  , _______                           , _______, KC_F6  , KC_F7  , KC_F8  , KC_F9  , KC_F10 , KC_F11 ,
    //,--------+--------+--------+--------+--------+--------+--------+                          .--------+--------+--------+--------+--------+--------+--------.
        JP_PIPE, JP_DQUO, KC_HOME, KC_UP  , KC_END , KC_PGUP, _______                           , _______, JP_LBRC, JP_LPRN, JP_RPRN, JP_RBRC, JP_MINS, JP_EQL ,
    //,--------+--------+--------+--------+--------+--------+--------+                          .--------+--------+--------+--------+--------+--------+--------.
        _______, JP_ZKHK, KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN, _______                           , _______, KC_BSPC, KC_ESC , KC_DEL , JP_HENK, JP_MHEN, SC_RCPC,
    //,--------+--------+--------+--------+--------+--------+--------+                          .--------+--------+--------+--------+--------+--------+--------.
        _______, JP_EXLM, JP_HASH, JP_DLR , JP_PERC, JP_TILD, _______                           , _______, JP_UNDS, KC_ENT , JP_LCBR, JP_RCBR, JP_AMPR,K_S_CIRC,
    //,--------+--------+--------+--------+--------+--------+--------+--------+        .--------+--------+--------+--------+--------+--------+--------+--------.
        _______, _______, _______, _______         , _______, _______, _______         , _______, _______, _______         , _______, _______, _______, _______
    //,--------+--------+--------+--------+--------+--------+--------+--------+        .--------+--------+--------+--------+--------+--------+--------+--------.
    ),


    [_RAISE] = LAYOUT( \
    //,--------+--------+--------+--------+--------+--------+--------+                          .--------+--------+--------+--------+--------+--------+--------.
        KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO                             , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  ,
    //,--------+--------+--------+--------+--------+--------+--------+                          .--------+--------+--------+--------+--------+--------+--------.
        KC_F12 , KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_F5  , _______                           , _______, KC_F6  , KC_F7  , KC_F8  , KC_F9  , KC_F10 , KC_F11 ,
    //,--------+--------+--------+--------+--------+--------+--------+                          .--------+--------+--------+--------+--------+--------+--------.
        _______, JP_1   , JP_2   , JP_3   , JP_4   , JP_5   , _______                           , _______, JP_6   , JP_7   , JP_8   , JP_9   , JP_0   , KC_RCTL,
    //,--------+--------+--------+--------+--------+--------+--------+                          .--------+--------+--------+--------+--------+--------+--------.
        _______, KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_PSCR, _______                           , _______,K_A_PSCR, KC_NO  , KC_NO  , KC_NO  ,K_ModClr, KC_RSFT,
    //,--------+--------+--------+--------+--------+--------+--------+--------+        .--------+--------+--------+--------+--------+--------+--------+--------.
        _______, _______, _______, _______         , _______, _______, _______         , _______, _______, _______         , _______, _______, _______, _______
    //,--------+--------+--------+--------+--------+--------+--------+--------+        .--------+--------+--------+--------+--------+--------+--------+--------.
    ),

    [_ADJUST] = LAYOUT( \
    //,--------+--------+--------+--------+--------+--------+--------+                          .--------+--------+--------+--------+--------+--------+--------.
        KC_NO  , KC_NO  , KC_NO  , KC_NO  ,  KC_NO , KC_NO  , KC_NO                             , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  ,
    //,--------+--------+--------+--------+--------+--------+--------+                          .--------+--------+--------+--------+--------+--------+--------.
        KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , QK_BOOT, _______                           , _______, QK_BOOT, KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  ,
    //,--------+--------+--------+--------+--------+--------+--------+                          .--------+--------+--------+--------+--------+--------+--------.
        KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , _______                           , _______, KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  ,
    //,--------+--------+--------+--------+--------+--------+--------+                          .--------+--------+--------+--------+--------+--------+--------.
        KC_NO  , KC_NO  , KC_NO  , KC_PAUS, KC_LSCR, KC_INS , _______                           , _______, KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  ,
    //,--------+--------+--------+--------+--------+--------+--------+--------+        .--------+--------+--------+--------+--------+--------+--------+--------.
        _______, _______, _______, _______         , _______, _______, _______         , _______, _______, _______         , _______, _______, _______, _______
    //,--------+--------+--------+--------+--------+--------+--------+--------+        .--------+--------+--------+--------+--------+--------+--------+--------.
    ),

    [_NAVI] = LAYOUT( \
    //,--------+--------+--------+--------+--------+--------+--------+                          .--------+--------+--------+--------+--------+--------+--------.
        _______, KC_NO  , KC_NO  , KC_NO  ,  KC_NO , KC_NO  , KC_NO                             , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  ,
    //,--------+--------+--------+--------+--------+--------+--------+                          .--------+--------+--------+--------+--------+--------+--------.
        _______, DM_REC1, DM_REC2, KC_NO  , KC_NO  , KC_NO  , _______                           , _______, MS_WHLU, MS_BTN1, MS_UP  , MS_BTN3, MS_BTN2, KC_NO  ,
    //,--------+--------+--------+--------+--------+--------+--------+                          .--------+--------+--------+--------+--------+--------+--------.
        _______, DM_PLY1, DM_PLY2, KC_NO  , KC_NO  , KC_NO  , _______                           , _______, MS_WHLD, MS_LEFT, MS_DOWN, MS_RGHT, KC_NO  , KC_NO  ,
    //,--------+--------+--------+--------+--------+--------+--------+                          .--------+--------+--------+--------+--------+--------+--------.
        _______, DM_RSTP, DM_RSTP, KC_NO  , KC_NO  , KC_NO  , _______                           , _______, MS_WHLL, MS_WHLR, KC_NO  , KC_NO  , KC_NO  , KC_NO  ,
    //,--------+--------+--------+--------+--------+--------+--------+--------+        .--------+--------+--------+--------+--------+--------+--------+--------.
        _______, _______, _______, _______         , _______, _______, _______         , _______, _______, _______         , _______, _______, _______, _______
    //,--------+--------+--------+--------+--------+--------+--------+--------+        .--------+--------+--------+--------+--------+--------+--------+--------.
    ),
};


#ifdef AUDIO_ENABLE
float tone_qwerty[][2]     = SONG(QWERTY_SOUND);
#endif


/*----------------------------------------------------------------------------------*/
/* キーon/off時の独自処理                                                               */
/*----------------------------------------------------------------------------------*/
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    //if (record->event.pressed) {
    //    set_keylog(keycode, record);
    //}

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

    return true;
}

/*----------------------------------------------------------------------------------*/
/* hold動作時間の設定(親指・小指キーは長めにする)                                   */
/*----------------------------------------------------------------------------------*/
#define TAPPING_TERM_LONG   (300)

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    const uint8_t row = record->event.key.row;
    const uint8_t col = record->event.key.col;
    if((col <= 1) || (row == 4) || (row == 9)) {        // col == 0,1 or row == 4, 9
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
