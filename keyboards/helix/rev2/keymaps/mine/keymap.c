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
  kcF22,  // F22を押して次の一般キーでF22を離す特殊キー(AHKマクロ起動用)
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


#define TAPPING_TERM2  50    // メインキーのタッピング
static const layer_def_t layer_def[] = {
  { false, _L_EDIT,   KC_SPC,  TAPPING_TERM, },  /* LM0 */
  { false, _L_EDIT,   KC_SPC,  TAPPING_TERM, },  /* LM1 */
  { false, _L_MARK,   KC_BSPC, TAPPING_TERM, },  /* LM2 */
  { false, _L_FUNC,   KC_ENT,  TAPPING_TERM, },  /* LM3 */
  { false, _L_MAC,    KC_F23,  TAPPING_TERM, },  /* LM4 */
  { false, _L_ADJUST, KC_TAB,  TAPPING_TERM, },  /* LM5 */
  { false, _L_ADJUST, JP_AT,   TAPPING_TERM, },  /* LM6 */
  { true,  _L_EDIT,   KC_F,    TAPPING_TERM2, },  /* LM7 */
  { true,  _L_EDIT,   KC_G,    TAPPING_TERM2, },  /* LM8 */
  { true,  _L_EDIT,   KC_H,    TAPPING_TERM2, },  /* LM9 */
  { true,  _L_EDIT,   KC_J,    TAPPING_TERM2, },  /* LM10 */
};
static layer_ctrl_t layer_ctrl[sizeof(layer_def)/sizeof(layer_def[0])] = {0, };
static uint8_t  layer_ctrl_wait = 0;  /* 待ち状態キー番号, 0=(なし), 1...=(ワンショットレイヤー番号+1)  */
static uint16_t layer_ctrl_time = 0;  /* 待ち状態開始時刻 */
static uint8_t  layer_cnt[_L_MAX] = {0,};     /* レイヤーキーが複数押されているケース対応 */

static bool process_user_custom_layer(uint16_t keycode, keyrecord_t *record, uint8_t no);
static bool process_user_custom_layer_otherkey_down(void);
static void process_user_custom_layer_time_check(void);

#if 0
/* コンボキー */
enum combos{
  COMBO_FD,
  COMBO_FS,
  COMBO_DS,
  COMBO_JK,
  COMBO_JL,
  COMBO_KL,
};

const uint16_t PROGMEM fd_combo[] = {KC_F, KC_D, COMBO_END};
const uint16_t PROGMEM fs_combo[] = {KC_F, KC_S, COMBO_END};
const uint16_t PROGMEM ds_combo[] = {KC_D, KC_S, COMBO_END};
const uint16_t PROGMEM jk_combo[] = {KC_J, KC_K, COMBO_END};
const uint16_t PROGMEM jl_combo[] = {KC_J, KC_L, COMBO_END};
const uint16_t PROGMEM kl_combo[] = {KC_K, KC_L, COMBO_END};

combo_t key_combos[COMBO_COUNT] = {
  [COMBO_FD] = COMBO(fd_combo, KC_BSPC),
  [COMBO_FS] = COMBO(fs_combo, JP_MHEN),
  [COMBO_DS] = COMBO(ds_combo, KC_DEL),
  [COMBO_JK] = COMBO(jk_combo, KC_ENT),
  [COMBO_JL] = COMBO(jl_combo, JP_HENK),
  [COMBO_KL] = COMBO(kl_combo, KC_ESC),
};
#endif

//enum macro_keycodes {
//  KC_SAMPLEMACRO,
//};

//Macros
#define M_SAMPLE M(KC_SAMPLEMACRO)

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
   0,  0,  0,  0,  8,  9        , 10, 11,  0,  0,  0,  0,       \
   0,  0,  0,  0,  0,  0        ,  0,  0,  0,  0,  0,  0,       \
   0,  0,  0,  0,  3,  1,  0,  5,  2,  4,  0,  0 , 0,  0        \
);


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  /* default
   * ,-----------------------------------------.             ,-----------------------------------------.
   * | Tab  |   Q  |   W  |   E  |   R  |   T  |             |   Y  |   U  |   I  |   O  |   P  | @`   |
   * | *ADJ |      |      |      |      |      |             |      |      |      |      |      | *ADJ |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      |   A  |   S  |   D  |   F  |   G  |             |   H  |   J  |   K  |   L  |  ;+  | :*   |
   * | LCtl l      |      |      |      |      |             |      |      |      |      |      | RCtl |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      |   Z  |   X  |   C  |   V  |   B  |             |   N  |   M  |  ,<  |  .>  |  /?  | \_   |
   * | LSft |      |      |      |      |      |             |      |      |      |      |      | RSft |
   * |------+------+------+------+------+------+-------------+------+------+------+------+------+------|
   * |      |      |      |      | BS   |Space | -F22 | F23  |Space |Enter |      |      |      |      |
   * | (SH) | -L8  | LWin | LAlt | *MRK | *EDT |      |*MAC  | *EDT | *FNC | RAlt | RWin | -L9  | (SH) |
   * `-------------------------------------------------------------------------------------------------'
   */
  [_L_DEFAULT] = LAYOUT( \
      KC_TAB,  KC_Q,   KC_W,    KC_E,    KC_R   , KC_T,                     KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    JP_AT,           \
      KC_LCTL, KC_A,   KC_S,    KC_D,    KC_F   , KC_G,                     KC_H,    KC_J,    KC_K,    KC_L,    JP_SCLN, RCTL_T(JP_COLN), \
      KC_LSFT, KC_Z,   KC_X,    KC_C,    KC_V   , KC_B,                     KC_N,    KC_M,    KC_COMM, KC_DOT,  JP_SLSH, RSFT_T(JP_BSLS), \
      SH_MON,  MO(8),  KC_LWIN, KC_LALT, KC_BSPC, KC_SPC,  kcF22,  KC_F23,  KC_SPC,  KC_ENT,  KC_RALT, KC_RWIN, MO(9),   SH_MON           \
      ),

  /* edit layer
   * ,-----------------------------------------.             ,-----------------------------------------.
   * |  △  | PrScr| Home |  ↑  |  End | PgUp |             |      |無変換| 変換 |      |      |  △  |
   * |      |      |      |      |      |      |             |      |      |      |      |      |      |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |  △  | 漢字 |  ←  |  ↓  |  →  | PgDn |             |  BS  | ESC  | Del  |      |      |  △  |
   * |      l      |      |      |      |      |             |      |      |      |      |      |      |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |  △  |      |      |      |      |      |             |      |Enter |      |      |      |  △  |
   * |      |      |      |      |      |      |             |      |      |      |      |      |      |
   * |------+------+------+------+------+------+-------------+------+------+------+------+------+------|
   * |  △  |  △  |  △  |  △  |  △  |  △  |  △  |  △  |  △  |  △  |  △  |  △  |  △  |  △  |
   * |      |      |      |      |      |      |      |      |      |      |      |      |      |      |
   * `-------------------------------------------------------------------------------------------------'
   */
  [_L_EDIT] = LAYOUT( \
      _______, KC_PSCR, KC_HOME, KC_UP  , KC_END , KC_PGUP                  , KC_NO  , JP_MHEN, JP_HENK, KC_NO  , KC_NO  , _______, \
      _______, JP_ZKHK, KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN                  , KC_BSPC, KC_ESC , KC_DEL , KC_NO  , KC_NO  , _______, \
      _______, KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO                    , KC_NO  , KC_ENT , KC_NO  , KC_NO  , KC_NO  , _______, \
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______  \
      ),

  /* mark layer
   * ,-----------------------------------------.             ,-----------------------------------------.
   * |  △  |  =   |  )   |  (   |  '   |  {   |             |  [{  |  7'  |  8(  |  9)  |  -=  |  △  |
   * |      |      |      |      |      |      |             |      |      |      |      |      |      |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |  △  |  ~   |  &   |  %   |  $   |  }   |             |  ]}  |  4$  |  5%  |  6&  |  ^~  |  △  |
   * |      l      |      |      |      |      |             |      |      |      |      |      |      |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |  △  |  |   |  #   |  "   |  !   |  _   |             |  0   |  1!  |  2"  |  3#  |  \|  |  △  |
   * |      |      |      |      |      |      |             |      |      |      |      |      |      |
   * |------+------+------+------+------+------+-------------+------+------+------+------+------+------|
   * |  △  |  △  |  △  |  △  |  △  |  △  |  △  |  △  |  △  |  △  |  △  |  △  |  △  |  △  |
   * |      |      |      |      |      |      |      |      |      |      |      |      |      |      |
   * `-------------------------------------------------------------------------------------------------'
   */
  [_L_MARK] = LAYOUT( \
      _______, JP_EQL , JP_RPRN, JP_LPRN, JP_QUOT, JP_LCBR                  , JP_LBRC, JP_7   , JP_8   , JP_9   , JP_MINS, _______, \
      _______, JP_TILD, JP_AMPR, JP_PERC, JP_DLR , JP_RCBR                  , JP_RBRC, JP_4   , JP_5   , JP_6   , JP_CIRC, _______, \
      _______, JP_PIPE, JP_HASH, JP_DQUO, JP_EXLM, JP_UNDS                  , JP_0   , JP_1   , JP_2   , JP_3   , JP_BSLS, _______, \
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______  \
      ),

  /* FunctionKey layer
   * ,-----------------------------------------.             ,-----------------------------------------.
   * |  △  | F12  | F11  | F10  |  F9  | 英数 |             | かな |  F9  | F10  | F11  | F12  |  △  |
   * |      |      |      |      |      |      |             |      |      |      |      |      |      |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |  △  |  F8  |  F7  |  F6  |  F5  | ESC  |             |PrnScr|  F5  |  F6  |  F7  |  F8  |  △  |
   * |      l      |      |      |      |      |             |      |      |      |      |      |      |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |  △  |  F4  |  F3  |  F2  |  F1  |ScrLck|             |Pause |  F1  |  F2  |  F3  |  F4  |  △  |
   * |      |      |      |      |      |      |             |      |      |      |      |      |      |
   * |------+------+------+------+------+------+-------------+------+------+------+------+------+------|
   * |  △  |  △  |  △  |  △  |  △  |  △  |  △  |  △  |  △  |  △  |  △  |  △  |  △  |  △  |
   * |      |      |      |      |      |      |      |      |      |      |      |      |      |      |
   * `-------------------------------------------------------------------------------------------------'
   */
  [_L_FUNC] = LAYOUT( \
      _______, KC_F12 , KC_F11 , KC_F10 , KC_F9  , JP_EISU                  , JP_KANA, KC_F9  , KC_F10 , KC_F11 , KC_F12 , _______, \
      _______, KC_F8  , KC_F7  , KC_F6  , KC_F5  , KC_ESC                   , KC_PSCR, KC_F5  , KC_F6  , KC_F7  , KC_F8  , _______, \
      _______, KC_F4  , KC_F3  , KC_F2  , KC_F1  , KC_SLCK                  , KC_PAUS, KC_F1  , KC_F2  , KC_F3  , KC_F4  , _______, \
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______  \
      ),
  
  /* macro
   * ,-----------------------------------------.             ,-----------------------------------------.
   * |  △  |      |      |      |      |      |             |      |      |      |      |      |  △  |
   * |      |      |      |      |      |      |             |      |      |      |      |      |      |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |  △  |      |      |      |      |      |             |      |      |      |      |      |  △  |
   * |      l      |      |      |      |      |             |      |      |      |      |      |      |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |  △  |      |      |      |      |      |             |      |      |      |      |      |  △  |
   * |      |      |      |      |      |      |             |      |      |      |      |      |      |
   * |------+------+------+------+------+------+-------------+------+------+------+------+------+------|
   * |  △  |  △  |  △  |  △  |  △  |  △  |  △  |  △  |  △  |  △  |  △  |  △  |  △  |  △  |
   * |      |      |      |      |      |      |      |      |      |      |      |      |      |      |
   * `-------------------------------------------------------------------------------------------------'
   */
  [_L_MAC] = LAYOUT( \
      _______, KC_MSTP, KC_MPLY, KC_MYCM, KC_CALC, KC_NO                    , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , _______, \
      _______, KC_MPRV, KC_MNXT, KC_VOLD, KC_VOLU, KC_MUTE                  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , _______, \
      _______, KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO                    , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , _______, \
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______  \
      ),
  /* Adjust(Keyboard Control) Layer
   * ,-----------------------------------------.             ,-----------------------------------------.
   * |  △  |      |      |      |      |      |             |      |      |      |      |      |  △  |
   * |      |      |      |      |      |      |             |      |      |      |      |      |      |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |  △  |      |      |      |      |      |             |      |      |      |      |      |  △  |
   * |      l      |      |      |      |      |             |      |      |      |      |      |      |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |  △  |      |      |      |      |      |             |      |      |      |      |      |  △  |
   * |      |      |      |      |      |      |             |      |      |      |      |      |      |
   * |------+------+------+------+------+------+-------------+------+------+------+------+------+------|
   * |  △  |  △  |  △  |  △  |  △  |  △  |  △  |  △  |  △  |  △  |  △  |  △  |  △  |  △  |
   * |      |      |      |      |      |      |      |      |      |      |      |      |      |      |
   * `-------------------------------------------------------------------------------------------------'
   */
  [_L_ADJUST] = LAYOUT( \
      _______, KC_NO   , KC_NO   , KC_NO  , KC_NO  , RESET                    , RESET  , RGB_MOD, RGB_RMOD, RGB_HUI, RGB_HUD, _______, \
      _______, RGB_M_SN, RGB_M_SW, RGB_M_R, RGB_M_B, RGB_TOG                  , RGB_TOG, RGB_SPI, RGB_SPD , RGB_SAI, RGB_SAD, _______, \
      _______, RGB_M_T , RGB_M_G , RGB_M_X, RGB_M_K, RGB_M_P                  , KC_NO  , RGB_VAI, RGB_VAD , KC_NO  , KC_NO  , _______, \
      _______, _______ , _______ , _______, _______, _______, _______, _______, _______, _______, _______ , _______, _______, _______  \
      ),

  /* format
   * ,-----------------------------------------.             ,-----------------------------------------.
   * |  △  |      |      |      |      |      |             |      |      |      |      |      |  △  |
   * |      |      |      |      |      |      |             |      |      |      |      |      |      |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |  △  |      |      |      |      |      |             |      |      |      |      |      |  △  |
   * |      l      |      |      |      |      |             |      |      |      |      |      |      |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |  △  |      |      |      |      |      |             |      |      |      |      |      |  △  |
   * |      |      |      |      |      |      |             |      |      |      |      |      |      |
   * |------+------+------+------+------+------+-------------+------+------+------+------+------+------|
   * |  △  |  △  |  △  |  △  |  △  |  △  |  △  |  △  |  △  |  △  |  △  |  △  |  △  |  △  |
   * |      |      |      |      |      |      |      |      |      |      |      |      |      |      |
   * `-------------------------------------------------------------------------------------------------'
   */
};
#else
#error "undefined keymaps"
#endif


uint8_t fn_tracker = 0; /* F22, F23のワンショットファンクション */
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
    #if 0
    /* キー位置基準でレイヤー操作 */
    const uint8_t col = record->event.key.col;
    const uint8_t row = record->event.key.row;
    uint8_t no = 0xff;
    
    if((row == 0) && (col == 0)) {
      no = 5;
    }
    else if(row == 1) {
      if(col == 4) {
        no = 7;
      }
      else if(col == 5) {
        no = 8;
      }
    }
    else if(row == 3) {
      if(col == 4) {
        no = 2;
      }
      else if(col == 5) {
        no = 0;
      }
    }
    else if((row == 4) && (col == 0)) {
      no = 6;
    }
    else if(row == 5) {
      if(col == 5) {
        no = 9;
      }
      else if(col == 4) {
        no = 10;
      }
    }
    else if(row == 7) {
      if(col == 4) {
        no = 3;
      }
      else if(col == 5) {
        no = 1;
      }
      else if(col == 6) {
        no = 4;
      }
    }
    
    if(no != 0xff) {
      return process_user_custom_layer(keycode, record, no);
    }
    #endif
  }
  
  switch (keycode) {
  case LM0 ... LM15:
    return process_user_custom_layer(keycode, record, keycode - LM0);
    break;
  
  case kcF22:
    // 次の通常キーが押されるまで F22 を維持する。
    if (record->event.pressed) {
      register_code(KC_F22);      // F22 down
      fn_tracker |= 1;
    }
    return false;
    break;
  
  default:
    process_user_custom_layer_otherkey_down();  /* layer制御で他キーが押されたことを通知 */
    break;
  }
  return true;
}

void post_process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
  case KC_A ... KC_F21:
  case KC_F23 ... KC_EXSEL:
    if (!record->event.pressed) {
      if (fn_tracker & 1) {
          unregister_code(KC_F22); // F22 up
      }
      fn_tracker = 0;
    }
    break;
  }
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



  