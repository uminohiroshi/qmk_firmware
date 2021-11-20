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

#include "keymap_jp.h"

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
enum layer_number {
  _L_DEFAULT = 0,
  _L_EDIT,
  _L_MARK,
  _L_FUNC,
  _L_MAC,  /* macro */
  _L_ADJUST,
  _L_MAX,  /* レイヤー最大数 */
};

enum custom_keycodes {
  // 独自レイヤーキー
  LM0 = SAFE_RANGE,
  LM1, LM2, LM3, LM4, LM5, LM6, LM7, LM8, LM9, LM10, LM11, LM12, LM13, LM14, LM15,
};

// RGB制御
int RGB_current_mode;


/* 独自レイヤコントロール */
typedef struct {
  uint8_t   retro;    /* 単打時に必ずタッピング動作する(true)/タイムアウトする(false) */
  uint8_t   layer;    /* レイヤー番号 */
  uint16_t  keycode;  /* 16bitキーコード */
  uint16_t  tapping_term; /* タップ判定時間 */
} layer_def_t;

typedef struct {
  uint8_t   state;
  uint16_t  time;     /* 前回イベント時刻 */
  uint16_t  keycode;  /* 最後のキーコード */
} layer_ctrl_t;

enum LayerState_e_t {
  LayerStateInit,     // 初期状態
  LayerStateDown,     // 押下開始状態
  LayerStateModHold,  // ModをHoldしている状態
  LayerStateHold,     // KeyをHoldしている状態
};


#define TAPPING_TERM2  10    // メインキーのタッピング
static const layer_def_t layer_def[] = {
  { false, _L_EDIT,   KC_SPC,  TAPPING_TERM, },  /* LM0 */
  { false, _L_EDIT,   KC_SPC,  TAPPING_TERM, },  /* LM1 */
  { false, _L_MARK,   KC_BSPC, TAPPING_TERM, },  /* LM2 */
  { false, _L_FUNC,   KC_ENT,  TAPPING_TERM, },  /* LM3 */
  { false, _L_MAC,    KC_F23,  TAPPING_TERM, },  /* LM4 */
  { false, _L_ADJUST, KC_TAB,  TAPPING_TERM, },  /* LM5 */
  { false, _L_ADJUST, JP_AT,   TAPPING_TERM, },  /* LM6 */
//  { true,  _L_EDIT,   KC_F,    TAPPING_TERM2, },  /* LM7 */
//  { true,  _L_EDIT,   KC_G,    TAPPING_TERM2, },  /* LM8 */
//  { true,  _L_EDIT,   KC_H,    TAPPING_TERM2, },  /* LM9 */
//  { true,  _L_EDIT,   KC_J,    TAPPING_TERM2, },  /* LM10 */
};
static layer_ctrl_t layer_ctrl[sizeof(layer_def)/sizeof(layer_def[0])] = {0, };
static uint8_t  layer_ctrl_wait = 0;  /* 待ち状態キー番号, 0=(なし), 1...=(ワンショットレイヤー番号+1)  */
static uint16_t layer_ctrl_time = 0;  /* 待ち状態開始時刻 */
static uint8_t  layer_cnt[_L_MAX] = {0,};     /* レイヤーキーが複数押されているケース対応 */

static bool process_user_custom_layer(uint16_t keycode, keyrecord_t *record, uint8_t no);
static bool process_user_custom_layer_otherkey_down(void);
static void process_user_custom_layer_time_check(void);

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

// 独自レイヤー定義
const uint8_t defMineKeyCode[MATRIX_ROWS][MATRIX_COLS] = LAYOUT(  \
   6,  0,  0,  0,  0,  0        ,  0,  0,  0,  0,  0,  7,       \
   0,  0,  0,  0,  0,  0        ,  0,  0,  0,  0,  0,  0,       \
   0,  0,  0,  0,  0,  0        ,  0,  0,  0,  0,  0,  0,       \
   0,  0,  0,  0,  3,  1,  0,  5,  2,  4,  0,  0 , 0,  0        \
);


#define K_C_F13 LCTL_T(KC_F13)
#define K_C_CLN RCTL_T(JP_COLN)
#define K_S_Z   LSFT_T(KC_Z)
#define K_S_SLS RSFT_T(JP_SLSH)
#define K_S_BSL RSFT_T(JP_BSLS)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_L_DEFAULT] = LAYOUT( \
    //,--------+--------+--------+--------+--------+--------.                 ,--------+--------+--------+--------+--------+--------.
        KC_TAB , KC_Q   , KC_W   , KC_E   , KC_R   , KC_T                     , KC_Y   , KC_U   , KC_I   , KC_O   , KC_P   , JP_AT  , \
    //,--------+--------+--------+--------+--------+--------.                 ,--------+--------+--------+--------+--------+--------.
        K_C_F13, KC_A   , KC_S   , KC_D   , KC_F   , KC_G                     , KC_H   , KC_J   , KC_K   , KC_L   , JP_SCLN, K_C_CLN, \
    //,--------+--------+--------+--------+--------+--------.                 ,--------+--------+--------+--------+--------+--------.
        KC_LSFT, K_S_Z  , KC_X   , KC_C   , KC_V   , KC_B                     , KC_N   , KC_M   , KC_COMM, KC_DOT , K_S_SLS, K_S_BSL, \
    //,--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------.
        SH_MON , MO(8)  , KC_LWIN, KC_LALT,KC_BSPC , KC_SPC , KC_NO  , KC_NO  , KC_SPC , KC_ENT , KC_RALT, KC_RWIN, MO(9)  , SH_MON   \
    //,--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------.
    ),

    [_L_EDIT] = LAYOUT( \
    //,--------+--------+--------+--------+--------+--------.                 ,--------+--------+--------+--------+--------+--------.
        JP_PIPE, KC_PSCR, KC_HOME, KC_UP  , KC_END , KC_PGUP                  , JP_TILD, JP_LPRN, JP_RPRN, JP_EQL , JP_MINS, JP_CIRC, \
    //,--------+--------+--------+--------+--------+--------.                 ,--------+--------+--------+--------+--------+--------.
        _______, JP_ZKHK, KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN                  , KC_BSPC, KC_ESC , KC_DEL , JP_HENK, JP_MHEN, _______, \
    //,--------+--------+--------+--------+--------+--------.                 ,--------+--------+--------+--------+--------+--------.
        _______, JP_RCBR, JP_LCBR, KC_NO  , KC_NO  , KC_F14                   , JP_UNDS, KC_ENT , KC_NO  , JP_LBRC, JP_RBRC, _______, \
    //,--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------.
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______  \
    //,--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------.
    ),

    [_L_MARK] = LAYOUT( \
    //,--------+--------+--------+--------+--------+--------.                 ,--------+--------+--------+--------+--------+--------.
        _______, JP_EQL , JP_RPRN, JP_LPRN, JP_QUOT, JP_LCBR                  , JP_LBRC, JP_7   , JP_8   , JP_9   , JP_MINS, _______, \
    //,--------+--------+--------+--------+--------+--------.                 ,--------+--------+--------+--------+--------+--------.
        _______, JP_TILD, JP_AMPR, JP_PERC, JP_DLR , JP_RCBR                  , JP_RBRC, JP_4   , JP_5   , JP_6   , JP_CIRC, _______, \
    //,--------+--------+--------+--------+--------+--------.                 ,--------+--------+--------+--------+--------+--------.
        _______, JP_PIPE, JP_HASH, JP_DQUO, JP_EXLM, JP_UNDS                  , JP_0   , JP_1   , JP_2   , JP_3   , JP_BSLS, _______, \
    //,--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------.
        _______, _______, _______, _______, _______, _______, _______, _______, _______, JP_0   , _______, _______, _______, _______  \
    //,--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------.
    ),

    [_L_FUNC] = LAYOUT( \
    //,--------+--------+--------+--------+--------+--------.                 ,--------+--------+--------+--------+--------+--------.
        _______, KC_F12 , KC_F11 , KC_F10 , KC_F9  , JP_EISU                  , JP_KANA, KC_F9  , KC_F10 , KC_F11 , KC_F12 , _______, \
    //,--------+--------+--------+--------+--------+--------.                 ,--------+--------+--------+--------+--------+--------.
        _______, KC_F8  , KC_F7  , KC_F6  , KC_F5  , KC_ESC                   , KC_PSCR, KC_F5  , KC_F6  , KC_F7  , KC_F8  , _______, \
    //,--------+--------+--------+--------+--------+--------.                 ,--------+--------+--------+--------+--------+--------.
        _______, KC_F4  , KC_F3  , KC_F2  , KC_F1  , KC_SLCK                  , KC_PAUS, KC_F1  , KC_F2  , KC_F3  , KC_F4  , _______, \
    //,--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------.
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______  \
    //,--------+--------+--------+--------+--------+--------+--------+--------+--------+-------+--------+--------+--------+--------.
    ),

    [_L_MAC] = LAYOUT( \
    //,--------+--------+--------+--------+--------+--------.                 ,--------+--------+--------+--------+--------+--------.
        _______, KC_MSTP, KC_MPLY, KC_MYCM, KC_CALC, KC_NO                    , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , _______, \
    //,--------+--------+--------+--------+--------+--------.                 ,--------+--------+--------+--------+--------+--------.
        _______, KC_MPRV, KC_MNXT, KC_VOLD, KC_VOLU, KC_MUTE                  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , _______, \
    //,--------+--------+--------+--------+--------+--------.                 ,--------+--------+--------+--------+--------+--------.
        _______, KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO                    , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , _______, \
    //,--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------.
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______  \
    //,--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------.
    ),

    [_L_ADJUST] = LAYOUT( \
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


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  /* ワンショットレイヤー処理でキー押下イベントで状態遷移 */
  if(record->event.pressed) {
    bool ret = process_user_custom_layer_otherkey_down();    // 他キーdownによるレイヤー遷移
    if (ret) {
      // 状態変化があったら keycodeを更新
      keycode = get_record_keycode(record, true);  // 状態遷移による新しいキーコードの取得
    }
  }
  
  /* キー位置対応でのワンショットレイヤー処理 */
  {
    const uint8_t col = record->event.key.col;
    const uint8_t row = record->event.key.row;
    const uint8_t no = defMineKeyCode[row][col];
    if(no) {
      return process_user_custom_layer(keycode, record, no);
    }
  }
  
  switch (keycode) {
  case LM0 ... LM15:
    return process_user_custom_layer(keycode, record, keycode - LM0);
    break;
  
  default:
    process_user_custom_layer_otherkey_down();  /* layer制御で他キーが押されたことを通知 */
    break;
  }  
    
  return true;
}


/* マトリックススキャンタイミングで呼び出す */
void matrix_scan_user(void) {
  process_user_custom_layer_time_check();
}

/*--------------------------------------------------------------------------------*/
/* タッピング時間切り替え(親指・小指キーを長時間とする                            */
/*--------------------------------------------------------------------------------*/
#define TAPPING_TERM_LONG 300
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
  const uint8_t row = record->event.key.row;
  const uint8_t col = record->event.key.col;
  
  if((col <= 1) || ((row & 3) == 3)) { /* col == 0,1 row == 3,7 で有効 */
    return TAPPING_TERM_LONG;
  }
  else {
    return TAPPING_TERM;
  }
}

/*--------------------------------------------------------------------------------*/
/* ワンショットレイヤーカスタマイズ                                               */
/*--------------------------------------------------------------------------------*/
/* レイヤー制御関数 */
/* 1tap  : tap "key"  */
/* 1hold : "layer" on */
/* 2tap  : tap "key"  */
/* 2hold : hold "key" */
static bool process_user_custom_layer(uint16_t keycode, keyrecord_t *record, uint8_t no_in) {
  const uint8_t no = no_in - 1;
  const layer_def_t*  const def = &layer_def[no];
  layer_ctrl_t* const ctrl = &layer_ctrl[no];
  
  // 設定テーブル要素数以上の引数が指定されたら何もせずリターン
  if(no >= (sizeof(layer_def)/sizeof(layer_def[0]))) {
    return true;
  }
  
  if (record->event.pressed) {
    /* keydownイベント */
    if ((record->event.time - ctrl->time) > def->tapping_term) {
      /* 初回 Down */
      if(!def->retro) { // Mod優先時はMod操作操作する
        layer_on(def->layer);
        layer_cnt[def->layer]++;
      }
      
      // Down状態に待ち処理付きで入る
      layer_ctrl_wait = no + 1;
      layer_ctrl_time = timer_read();
      ctrl->state = LayerStateDown;
      ctrl->keycode = keycode;
    }
    else {
      /* 2回目 Down → Hold動作 */
      register_code16(keycode);
      ctrl->keycode = keycode;
      ctrl->state = LayerStateHold;
    }
    // 時刻記録
    ctrl->time = record->event.time;
  }
  else {
    /* keyupイベント */
    if(ctrl->state == LayerStateDown) {
      /* Up */
      if (!def->retro) {  // Mod優先時はMod操作する
        /* レイヤーキーがすべて離されたらレイヤーをOFFにする */
        layer_cnt[def->layer]--;
        if(layer_cnt[def->layer] == 0) {
          layer_off(def->layer);
        }
      }
      
      /* タップ動作 */
      tap_code16(keycode);
      // 状態遷移
      ctrl->state = LayerStateInit;
      layer_ctrl_wait = 0;            // 待状態を終了
    }
    else if(ctrl->state == LayerStateModHold) {
      /* レイヤーキーがすべて離されたらレイヤーをOFFにする */
      layer_cnt[def->layer]--;
      if(layer_cnt[def->layer] == 0) {
        layer_off(def->layer);
      }
      // 状態遷移
      ctrl->state = LayerStateInit;
    }
    else if(ctrl->state == LayerStateHold) {
      // キーup処理
      unregister_code16(ctrl->keycode);
      // 状態遷移
      ctrl->state = LayerStateInit;
    }
    /* Up時刻記録 */
    ctrl->time = record->event.time;
  }
  return false;
}


/* 他キーの tapが入ったときに呼び出す(状態変数ビットを1にするだけ) */
static bool process_user_custom_layer_otherkey_down(void) {
  if(layer_ctrl_wait) {
    const uint8_t no = layer_ctrl_wait - 1;
    const layer_def_t*  const def = &layer_def[no];
    layer_ctrl_t* const ctrl = &layer_ctrl[no];
    
    if(def->retro) {
      // Hold優先時はここで初めてModを有効にする(→直後にMod対応でlキーが押される)
      layer_on(def->layer);
      layer_cnt[def->layer]++;
    }
    else {
      // Mod優先時は何もしない
    }
    
    // 待ち状態終了    
    ctrl->state = LayerStateModHold;
    layer_ctrl_wait = 0;
    return true;
  }
  return false;
}


static void process_user_custom_layer_time_check(void) {
  if (layer_ctrl_wait) {
    // 時間待ち中のみ処理(負荷低減のため)
    const uint8_t no = layer_ctrl_wait - 1;
    
    const layer_def_t*  const def = &layer_def[no];
    layer_ctrl_t* const ctrl = &layer_ctrl[no];
    
    if(timer_elapsed(layer_ctrl_time) > def->tapping_term) {
      // 待ちイベント時刻終了を検出
      if(def->retro) {  // Hold優先時はキーを押す
        ctrl->state = LayerStateHold;
        
        // キーdown処理
        register_code16(ctrl->keycode);
      }
      else {
        // Mod優先時はModHold状態に遷移
        ctrl->state = LayerStateModHold;
      }
      
      // 待ち状態解除
      layer_ctrl_wait = 0;
    }
  }
  else {
    // 基準時刻を現在に更新する
    layer_ctrl_time = timer_read();
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



  