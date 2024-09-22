#include QMK_KEYBOARD_H



#include "keymap_japanese.h"  // JPキーボードシンボル

enum layer_number {
    _DEFAULT = 0,
    _RAISE,
    _LOWER,
    _NUMKEYS,
	_ADJUST,
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

// for Combo
// left side : left-right
const uint16_t PROGMEM my_combo00[] = {KC_T,     KC_R,     COMBO_END};
const uint16_t PROGMEM my_combo01[] = {KC_G,     K_S_F,    COMBO_END};
const uint16_t PROGMEM my_combo02[] = {KC_B,     K_S_V,    COMBO_END};
const uint16_t PROGMEM my_combo03[] = {KC_R,     KC_E,     COMBO_END};
const uint16_t PROGMEM my_combo04[] = {K_S_F,    K_C_D,    COMBO_END};
const uint16_t PROGMEM my_combo05[] = {K_S_V,    K_C_C,    COMBO_END};
const uint16_t PROGMEM my_combo06[] = {KC_E,     KC_W,     COMBO_END};
const uint16_t PROGMEM my_combo07[] = {K_C_D,    K_A_S,    COMBO_END};
const uint16_t PROGMEM my_combo08[] = {K_C_C,    K_A_X,    COMBO_END};
const uint16_t PROGMEM my_combo09[] = {KC_W,     KC_Q,     COMBO_END};
const uint16_t PROGMEM my_combo10[] = {K_A_S,    K_G_A,    COMBO_END};
const uint16_t PROGMEM my_combo11[] = {K_A_X,    K_G_Z,    COMBO_END};
// right side : left-right
const uint16_t PROGMEM my_combo12[] = {KC_Y,     KC_U,     COMBO_END};
const uint16_t PROGMEM my_combo13[] = {KC_H,     K_S_J,    COMBO_END};
const uint16_t PROGMEM my_combo14[] = {KC_N,     K_S_M,    COMBO_END};
const uint16_t PROGMEM my_combo15[] = {KC_U,     KC_I,     COMBO_END};
const uint16_t PROGMEM my_combo16[] = {K_S_J,    K_C_K,    COMBO_END};
const uint16_t PROGMEM my_combo17[] = {K_S_M,    K_C_COMM, COMBO_END};
const uint16_t PROGMEM my_combo18[] = {KC_I,     KC_O,     COMBO_END};
const uint16_t PROGMEM my_combo19[] = {K_C_K,    K_A_L,    COMBO_END};
const uint16_t PROGMEM my_combo20[] = {K_C_COMM, K_A_DOT, COMBO_END};
const uint16_t PROGMEM my_combo21[] = {KC_O,     KC_P,     COMBO_END};
const uint16_t PROGMEM my_combo22[] = {K_A_L,    K_G_SCLN, COMBO_END};
const uint16_t PROGMEM my_combo23[] = {K_A_DOT,  K_G_SLSH, COMBO_END};
// left side : up-down
const uint16_t PROGMEM my_combo24[] = {KC_T,     KC_G,     COMBO_END};
const uint16_t PROGMEM my_combo25[] = {KC_G,     KC_B,     COMBO_END};
const uint16_t PROGMEM my_combo26[] = {KC_R,     K_S_F,    COMBO_END};
const uint16_t PROGMEM my_combo27[] = {K_S_F,    K_S_V,    COMBO_END};
const uint16_t PROGMEM my_combo28[] = {KC_E,     K_C_D,    COMBO_END};
const uint16_t PROGMEM my_combo29[] = {K_C_D,    K_C_C,    COMBO_END};
const uint16_t PROGMEM my_combo30[] = {KC_W,     K_A_S,    COMBO_END};
const uint16_t PROGMEM my_combo31[] = {K_A_S,    K_A_X,    COMBO_END};
const uint16_t PROGMEM my_combo32[] = {KC_Q,     K_G_A,    COMBO_END};


const uint16_t PROGMEM my_combo33[] = {K_G_A,    K_G_Z,    COMBO_END};
// right side : up-down
const uint16_t PROGMEM my_combo34[] = {KC_Y,     KC_H,     COMBO_END};
const uint16_t PROGMEM my_combo35[] = {KC_H,     KC_N,     COMBO_END};
const uint16_t PROGMEM my_combo36[] = {KC_U,     K_S_J,    COMBO_END};
const uint16_t PROGMEM my_combo37[] = {K_S_J,    K_S_M,    COMBO_END};
const uint16_t PROGMEM my_combo38[] = {KC_I,     K_C_K,    COMBO_END};
const uint16_t PROGMEM my_combo39[] = {K_C_K,    K_C_COMM, COMBO_END};
const uint16_t PROGMEM my_combo40[] = {KC_O,     K_A_L,    COMBO_END};
const uint16_t PROGMEM my_combo41[] = {K_A_L,    K_A_DOT,  COMBO_END};
const uint16_t PROGMEM my_combo42[] = {KC_P,     K_G_SCLN, COMBO_END};
const uint16_t PROGMEM my_combo43[] = {K_G_SCLN, K_G_SLSH, COMBO_END};

combo_t key_combos[] = {
    COMBO(my_combo03, KC_ENT),
    COMBO(my_combo05, LCTL(KC_V)),
    COMBO(my_combo06, KC_ESC),
    COMBO(my_combo08, LCTL(KC_C)),
    COMBO(my_combo15, KC_BSPC),
    COMBO(my_combo18, KC_DEL),
    COMBO(my_combo24, JP_PERC),
    COMBO(my_combo25, JP_MINS),
    COMBO(my_combo34, JP_CIRC),
    COMBO(my_combo35, JP_UNDS),
};

uint16_t get_combo_term(uint16_t index, combo_t *combo) {

    return COMBO_TERM;
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_DEFAULT] = LAYOUT( \
    //,--------+--------+--------+--------+--------+--------+--------+                          .--------+--------+--------+--------+--------+--------+--------.
        KC_ESC , KC_1   , KC_2   , KC_3   , KC_4   , KC_5   , KC_PSCR                           , JP_CIRC, KC_6   , KC_7   , KC_8   , KC_9   , KC_0   ,JP_MINS ,
    //,--------+--------+--------+--------+--------+--------+--------+                          .--------+--------+--------+--------+--------+--------+--------.
        K_A_TAB, KC_Q   , KC_W   , KC_E   , KC_R   , KC_T   , KC_ESC                            , JP_LBRC, KC_Y   , KC_U   , KC_I   , KC_O   , KC_P   , K_A_AT ,
    //,--------+--------+--------+--------+--------+--------+--------+                          .--------+--------+--------+--------+--------+--------+--------.
        KC_LCTL, K_G_A  , K_A_S  , K_C_D  , K_S_F  , KC_G   , KC_INS                            , JP_RBRC, KC_H   , K_S_J  , K_C_K  , K_A_L  ,K_G_SCLN, K_C_CLN,
    //,--------+--------+--------+--------+--------+--------+--------+                          .--------+--------+--------+--------+--------+--------+--------.
        KC_LSFT, K_G_Z  , K_A_X  , K_C_C  , K_S_V  , KC_B   , KC_PAUS                           , KC_LSCR, KC_N   , K_S_M  ,K_C_COMM, K_A_DOT,K_G_SLSH, K_S_BSL,
    //,--------+--------+--------+--------+--------+--------+--------+--------+        .--------+--------+--------+--------+--------+--------+--------+--------.
        KC_LCTL, KC_LALT, KC_LWIN, KC_NO           , K_L_BS , K_R_SPC, K_N_F13         , K_N_F14, K_R_SPC, K_L_ENT         , KC_NO  , KC_RWIN, KC_RALT, KC_RCTL
    //,--------+--------+--------+--------+--------+--------+--------+--------+        .--------+--------+--------+--------+--------+--------+--------+--------.
    ),


    [_RAISE] = LAYOUT( \
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


    [_LOWER] = LAYOUT( \
    //,--------+--------+--------+--------+--------+--------+--------+                          .--------+--------+--------+--------+--------+--------+--------.
        _______, KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO                             , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  ,
    //,--------+--------+--------+--------+--------+--------+--------+                          .--------+--------+--------+--------+--------+--------+--------.
        KC_F12 , KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_F5  , _______                           , _______, KC_F6  , KC_F7  , KC_F8  , KC_F9  , KC_F10 , KC_F11 ,
    //,--------+--------+--------+--------+--------+--------+--------+                          .--------+--------+--------+--------+--------+--------+--------.
        KC_LCTL, JP_1   , JP_2   , JP_3   , JP_4   , JP_5   , _______                           , _______, JP_6   , JP_7   , JP_8   , JP_9   , JP_0   , KC_RCTL,
    //,--------+--------+--------+--------+--------+--------+--------+                          .--------+--------+--------+--------+--------+--------+--------.
        KC_LSFT, KC_SPC , KC_PAUS, KC_F14 , KC_F13 , KC_PSCR, _______                           , _______,K_A_PSCR,KC_F13 , KC_F14 , KC_LSCR , KC_SPC ,K_ModClr,
    //,--------+--------+--------+--------+--------+--------+--------+--------+        .--------+--------+--------+--------+--------+--------+--------+--------.
        _______, _______, _______, _______         , _______, _______, _______         , _______, _______, _______         , _______, _______, _______, _______
    //,--------+--------+--------+--------+--------+--------+--------+--------+        .--------+--------+--------+--------+--------+--------+--------+--------.
    ),


    [_NUMKEYS] = LAYOUT( \
    //,--------+--------+--------+--------+--------+--------+--------+                          .--------+--------+--------+--------+--------+--------+--------.
        _______, KC_NO  , KC_NO  , KC_NO  ,  KC_NO , KC_NO  , KC_NO                             , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  ,
    //,--------+--------+--------+--------+--------+--------+--------+                          .--------+--------+--------+--------+--------+--------+--------.
        KC_TAB , DM_REC1, DM_REC2, KC_NO  , KC_NO  , KC_NO  , _______                           , _______, KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  ,
    //,--------+--------+--------+--------+--------+--------+--------+                          .--------+--------+--------+--------+--------+--------+--------.
        _______, DM_PLY1, DM_PLY2, KC_NO  , KC_NO  , KC_NO  , _______                           , _______, KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  ,
    //,--------+--------+--------+--------+--------+--------+--------+                          .--------+--------+--------+--------+--------+--------+--------.
        _______, DM_RSTP, DM_RSTP, KC_NO  , KC_NO  , KC_NO  , _______                           , _______, KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  ,
    //,--------+--------+--------+--------+--------+--------+--------+--------+        .--------+--------+--------+--------+--------+--------+--------+--------.
        _______, _______, _______, _______         , _______, _______, _______         , _______, _______, _______         , _______, _______, _______, _______
    //,--------+--------+--------+--------+--------+--------+--------+--------+        .--------+--------+--------+--------+--------+--------+--------+--------.
    ),


    [_ADJUST] = LAYOUT( \
    //,--------+--------+--------+--------+--------+--------+--------+                          .--------+--------+--------+--------+--------+--------+--------.
        KC_NO  , KC_NO  , KC_NO  , KC_NO  ,  KC_NO , KC_NO  , KC_NO                             , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  ,
    //,--------+--------+--------+--------+--------+--------+--------+                          .--------+--------+--------+--------+--------+--------+--------.
        _______, KC_NO  , KC_NO  , KC_NO  , KC_NO  , QK_BOOT, _______                           , _______, QK_BOOT, KC_NO  ,KC_NO   , KC_NO  , KC_NO  , _______,
    //,--------+--------+--------+--------+--------+--------+--------+                          .--------+--------+--------+--------+--------+--------+--------.
        _______, KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , _______                           , _______, KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , _______,
    //,--------+--------+--------+--------+--------+--------+--------+                          .--------+--------+--------+--------+--------+--------+--------.
        _______, KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , _______                           , _______, KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , _______,
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
    case K_G_Z:
    case K_A_X:
    case K_C_C:
    case K_S_V:
    case K_S_M:
    case K_C_COMM:
    case K_A_DOT:
    case K_G_SLSH:
    // home row mod
    case K_G_A:
    case K_A_S:
    case K_C_D:
    case K_S_F:
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

