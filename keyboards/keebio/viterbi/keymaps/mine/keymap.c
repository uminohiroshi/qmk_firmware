#include QMK_KEYBOARD_H

#include "keymap_jp.h"		// 日本語キーボード用コードの取り込み
//#include "sendstring_jis.h"	// Sendstringの日本語対応

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _QWERTY 0
#define _LOWER 1
#define _RAISE 2
#define _ADJUST 16

enum layer_number {
  _L_DEFAULT = 0,
  _L_EDIT,
  _L_MARK,
  _L_MAC,  /* macro */
  _L_ADJUST,
  _L_MAX,  /* レイヤー最大数 */
};

enum custom_keycodes {
  // 独自レイヤーキー
  LM0 = SAFE_RANGE,
  LM1, LM2, LM3, LM4, LM5, LM6, LM7, LM8, LM9, LM10, LM11, LM12, LM13, LM14, LM15,
};


/* 独自レイヤコントロール */
typedef struct {
  uint8_t   retro;    /* 単打時に必ずタッピング動作する(true)/タイムアウトする(false) */
  uint8_t   layer;        /* レイヤー番号, 0だとレイヤー動作しない */
  uint16_t  keycode_hold; /* ホールド時送信するモディファイアのキーコード, 0だと何もしない。 */
  uint16_t  keycode;      /* タップ時送信する16bitキーコード */
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

#define TAPPING_TERM_SHORT 100
#define TAPPING_TERM_LONG 300
#define TAPPING_TERM2  10    // メインキーのタッピング
static const layer_def_t layer_def[] = {
  { false, _L_EDIT,    KC_NO,   KC_SPC,  TAPPING_TERM_SHORT, },  /* 1:LM0 */
  { false, _L_EDIT,    KC_NO,   KC_SPC,  TAPPING_TERM_SHORT, },  /* 2:LM1 */
  { false, _L_MARK,    KC_NO,   KC_BSPC, TAPPING_TERM_SHORT, },  /* 3:LM2 */
  { false, _L_MARK,    KC_NO,   KC_ENT,  TAPPING_TERM_SHORT, },  /* 4:LM3 */
  { false, _L_MAC,     KC_NO,   KC_F23,  TAPPING_TERM_SHORT, },  /* 5:LM4 */
  { false, _L_ADJUST,  KC_NO,   KC_TAB,  TAPPING_TERM_LONG, },  /* 6:LM5 */
  { false, _L_ADJUST,  KC_NO,   JP_AT,   TAPPING_TERM_LONG, },  /* 7:LM6 */
  { false, _L_DEFAULT, KC_LCTL, JP_DQUO, TAPPING_TERM_LONG, },  /* 8:LSFT */
  { false, _L_DEFAULT, KC_RCTL, JP_QUOT, TAPPING_TERM_LONG, },  /* 9:RSFT */
};
static layer_ctrl_t layer_ctrl[sizeof(layer_def)/sizeof(layer_def[0])] = {0, };
static uint8_t  layer_ctrl_wait = 0;  /* 待ち状態キー番号, 0=(なし), 1...=(ワンショットレイヤー番号+1)  */
static uint16_t layer_ctrl_time = 0;  /* 待ち状態開始時刻 */
static uint8_t  layer_cnt[_L_MAX] = {0,};     /* レイヤーキーが複数押されているケース対応 */

static bool process_user_custom_layer(uint16_t keycode, keyrecord_t *record, uint8_t no);
static bool process_user_custom_layer_otherkey_down(void);
static void process_user_custom_layer_time_check(void);


// スワップハンド定義
const keypos_t hand_swap_config[MATRIX_ROWS][MATRIX_COLS] = {
  {{0, 5}, {1, 5}, {2, 5}, {3, 5}, {4, 5}, {5, 5}, {6, 5}}, 
  {{0, 6}, {1, 6}, {2, 6}, {3, 6}, {4, 6}, {5, 6}, {6, 6}}, 
  {{0, 7}, {1, 7}, {2, 7}, {3, 7}, {4, 7}, {5, 7}, {6, 7}}, 
  {{0, 8}, {1, 8}, {2, 8}, {3, 8}, {4, 8}, {5, 8}, {6, 8}}, 
  {{0, 9}, {1, 9}, {2, 9}, {3, 9}, {4, 9}, {5, 9}, {6, 9}}, 
  {{0, 0}, {1, 0}, {2, 0}, {3, 0}, {4, 0}, {5, 0}, {6, 0}}, 
  {{0, 1}, {1, 1}, {2, 1}, {3, 1}, {4, 1}, {5, 1}, {6, 1}}, 
  {{0, 2}, {1, 2}, {2, 2}, {3, 2}, {4, 2}, {5, 2}, {6, 2}}, 
  {{0, 3}, {1, 3}, {2, 3}, {3, 3}, {4, 3}, {5, 3}, {6, 3}}, 
  {{0, 4}, {1, 4}, {2, 4}, {3, 4}, {4, 4}, {5, 4}, {6, 4}}, 
};

// 独自レイヤー定義
const uint8_t defMineKeyCode[MATRIX_ROWS][MATRIX_COLS] = LAYOUT(  \
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,       \
   6,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  7,       \
   8,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  9,       \
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,       \
   0,  0,  0,  0,  3,  1,  0,  5,  2,  4,  0,  0 , 0,  0        \
);


#define K_C_F13 LCTL_T(KC_F13)
#define K_C_CLN RCTL_T(JP_COLN)
#define K_S_BSL RSFT_T(JP_BSLS)
#define K_OLWIN OSM(MOD_LGUI)     // LWINワンショット
#define K_ORWIN OSM(MOD_RGUI)     // RWINワンショット
#define K_OLALT OSM(MOD_LALT)     // LALTワンショット
#define K_ORALT OSM(MOD_RALT)     // RALTワンショット

#define K_S_PSCR LSFT_T(KC_PSCR)
#define K_S_CIRC RSFT_T(JP_CIRC)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_L_DEFAULT] = LAYOUT( \
  //,--------+--------+--------+--------+--------+--------+--------+        .--------+--------+--------+--------+--------+--------+--------.
      KC_ESC , KC_1   , KC_2   , KC_3   , KC_4   , KC_5   , JP_ZKHK         , JP_CIRC, KC_6   , KC_7   , KC_8   , KC_9   , KC_0   ,JP_MINS , \
  //,--------+--------+--------+--------+--------+--------+--------+        .--------+--------+--------+--------+--------+--------+--------.
      KC_TAB , KC_Q   , KC_W   , KC_E   , KC_R   , KC_T   , KC_PSCR         , JP_LBRC, KC_Y   , KC_U   , KC_I   , KC_O   , KC_P   , JP_AT  , \
  //,--------+--------+--------+--------+--------+--------+--------+        .--------+--------+--------+--------+--------+--------+--------.
      K_C_F13, KC_A   , KC_S   , KC_D   , KC_F   , KC_G   , KC_ESC          , JP_RBRC, KC_H   , KC_J   , KC_K   , KC_L   , JP_SCLN, K_C_CLN, \
  //,--------+--------+--------+--------+--------+--------+--------+        .--------+--------+--------+--------+--------+--------+--------.
      KC_LSFT, KC_Z   , KC_X   , KC_C   , KC_V   , KC_B   , KC_INS          , KC_NO  , KC_N   , KC_M   , JP_COMM, JP_DOT , KC_SLSH, K_S_BSL, \
  //,--------+--------+--------+--------+--------+--------+--------+        .--------+--------+--------+--------+--------+--------+--------.
      KC_RCTL, SH_MON , K_OLWIN, K_OLALT, KC_BSPC, KC_SPC , KC_NO           , KC_NO  , KC_SPC , KC_ENT , K_ORALT, K_ORWIN, SH_MON , KC_RCTL  \
  //,--------+--------+--------+--------+--------+--------+--------+        .--------+--------+--------+--------+--------+--------+--------.
  ),


  [_L_EDIT] = LAYOUT( \
  //,--------+--------+--------+--------+--------+--------+--------+        .--------+--------+--------+--------+--------+--------+--------.
      KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_F5  , KC_F6  , _______         , _______, KC_F7  , KC_F8  , KC_F9  , KC_F10 , KC_F11 , KC_F12 , \
  //,--------+--------+--------+--------+--------+--------+--------+        .--------+--------+--------+--------+--------+--------+--------.
      JP_PIPE, KC_F14 , KC_HOME, KC_UP  , KC_END , KC_PGUP, _______         , _______, JP_LBRC, JP_LPRN, JP_RPRN, JP_RBRC, JP_MINS, JP_EQL, \
  //,--------+--------+--------+--------+--------+--------+--------+        .--------+--------+--------+--------+--------+--------+--------.
      JP_DQUO, JP_ZKHK, KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN, _______         , _______, KC_BSPC, KC_ESC , KC_DEL , JP_HENK, JP_MHEN ,JP_QUOT, \
  //,--------+--------+--------+--------+--------+--------+--------+        .--------+--------+--------+--------+--------+--------+--------.
     K_S_PSCR, JP_EXLM, JP_HASH, JP_DLR , JP_PERC, JP_TILD, _______         , _______, JP_UNDS, KC_ENT , JP_LCBR, JP_RCBR, JP_AMPR,K_S_CIRC, \
  //,--------+--------+--------+--------+--------+--------+--------+        .--------+--------+--------+--------+--------+--------+--------.
      _______, _______, _______, _______, _______, _______, _______         , _______, _______, _______, _______, _______, _______, _______  \
  //,--------+--------+--------+--------+--------+--------+--------+        .--------+--------+--------+--------+--------+--------+--------.
  ),


  [_L_MARK] = LAYOUT( \
  //,--------+--------+--------+--------+--------+--------+--------+        .--------+--------+--------+--------+--------+--------+--------.
      _______, KC_NO  , KC_NO  , KC_NO  ,  KC_NO , KC_NO  , KC_NO           , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , \
  //,--------+--------+--------+--------+--------+--------+--------+        .--------+--------+--------+--------+--------+--------+--------.
      KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_F5  , KC_F6  , _______         , _______, KC_F7  , KC_F8  , KC_F9  , KC_F10 , KC_F11 , KC_F12 , \
  //,--------+--------+--------+--------+--------+--------+--------+        .--------+--------+--------+--------+--------+--------+--------.
      KC_LCTL, JP_1   , JP_2   , JP_3   , JP_4   , JP_5   , _______         , _______, JP_6   , JP_7   , JP_8   , JP_9   , JP_0   , KC_RCTL, \
  //,--------+--------+--------+--------+--------+--------+--------+        .--------+--------+--------+--------+--------+--------+--------.
      KC_LSFT, _______, _______, _______, _______, _______, _______         , _______, _______, _______, _______, _______, _______, KC_RSFT, \
  //,--------+--------+--------+--------+--------+--------+--------+        .--------+--------+--------+--------+--------+--------+--------.
      _______, _______, _______, _______, _______, _______, _______         , _______, _______, _______, _______, _______, _______, _______  \
  //,--------+--------+--------+--------+--------+--------+--------+        .--------+--------+--------+--------+--------+--------+--------.
  ),



  [_L_MAC] = LAYOUT( \
  //,--------+--------+--------+--------+--------+--------+--------+        .--------+--------+--------+--------+--------+--------+--------.
      KC_NO  , KC_NO  , KC_NO  , KC_NO  ,  KC_NO , KC_NO  , KC_NO           , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , \
  //,--------+--------+--------+--------+--------+--------+--------+        .--------+--------+--------+--------+--------+--------+--------.
      _______, KC_MSTP, KC_MPLY, KC_MYCM, KC_CALC, KC_NO  , _______         , _______, KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , _______, \
  //,--------+--------+--------+--------+--------+--------+--------+        .--------+--------+--------+--------+--------+--------+--------.
      _______, KC_MPRV, KC_MNXT, KC_VOLD, KC_VOLU, KC_MUTE, _______         , _______, KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , _______, \
  //,--------+--------+--------+--------+--------+--------+--------+        .--------+--------+--------+--------+--------+--------+--------.
      _______, KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , _______         , _______, KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , _______, \
  //,--------+--------+--------+--------+--------+--------+--------+        .--------+--------+--------+--------+--------+--------+--------.
      _______, _______, _______, _______, _______, _______, _______         , _______, _______, _______, _______, _______, _______, _______  \
  //,--------+--------+--------+--------+--------+--------+--------+        .--------+--------+--------+--------+--------+--------+--------.
  ),


  [_L_ADJUST] = LAYOUT( \
  //,--------+--------+--------+--------+--------+--------+--------+        .--------+--------+--------+--------+--------+--------+--------.
      KC_NO  , KC_NO  , KC_NO  , KC_NO  ,  KC_NO , KC_NO  , KC_NO           , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , \
  //,--------+--------+--------+--------+--------+--------+--------+        .--------+--------+--------+--------+--------+--------+--------.
      _______, KC_NO  , KC_NO  , KC_NO  , KC_NO  , RESET  , _______         , _______, RESET  , RGB_MOD,RGB_RMOD, RGB_HUI, RGB_HUD, _______, \
  //,--------+--------+--------+--------+--------+--------+--------+        .--------+--------+--------+--------+--------+--------+--------.
      _______,RGB_M_SN,RGB_M_SW, RGB_M_R, RGB_M_B, RGB_TOG, _______         , _______, RGB_TOG, RGB_SPI, RGB_SPD, RGB_SAI, RGB_SAD, _______, \
  //,--------+--------+--------+--------+--------+--------+--------+        .--------+--------+--------+--------+--------+--------+--------.
      _______, RGB_M_T, RGB_M_G, RGB_M_X, RGB_M_K, RGB_M_P, _______         , _______, KC_NO  , RGB_VAI, RGB_VAD, KC_NO  , KC_NO  , _______, \
  //,--------+--------+--------+--------+--------+--------+--------+        .--------+--------+--------+--------+--------+--------+--------.
      _______, _______, _______, _______, _______, _______, _______         , _______, _______, _______, _______, _______, _______, _______  \
  //,--------+--------+--------+--------+--------+--------+--------+        .--------+--------+--------+--------+--------+--------+--------.
  ),

};


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
      bool ret = process_user_custom_layer(keycode, record, no);
      if(!ret) return ret; // 処理継続不要なときは直接リターン
    }
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
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
  const uint8_t row = record->event.key.row;
  const uint8_t col = record->event.key.col;
  
  if((col <= 1) || ((row == 4) || (row == 9))) { /* col == 0,1 row == 4,9 で有効 */
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
  bool ret = false;
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
        /* レイヤー遷移 */
        if(def->layer) {
          layer_on(def->layer);
          layer_cnt[def->layer]++;
        }
        /* モディファイア送信 */
        if(def->keycode_hold) {
          register_code16(def->keycode_hold);
        }
      }
      
      // Down状態に待ち処理付きで入る
      layer_ctrl_wait = no + 1;
      layer_ctrl_time = record->event.time;
      ctrl->state = LayerStateDown;
      ctrl->keycode = keycode;
    }
    else {
      /* 2回目 Down → Hold動作 */
      register_code16(keycode);
      ctrl->keycode = keycode;
      ctrl->state = LayerStateHold;
      //ret = true;
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
        /* レイヤーを戻す */
        if(def->layer) {
          layer_cnt[def->layer]--;
          if(layer_cnt[def->layer] == 0) {
            layer_off(def->layer);
          }
        }
        /* モディファイアを離す */
        if(def->keycode_hold) {
          unregister_code16(def->keycode_hold);
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
      if(def->layer) {
        /* レイヤーを戻す */
        layer_cnt[def->layer]--;
        if(layer_cnt[def->layer] == 0) {
          layer_off(def->layer);
        }
      }
      /* モディファイアを離す */
      if(def->keycode_hold) {
        unregister_code16(def->keycode_hold);
      }
      // 状態遷移
      ctrl->state = LayerStateInit;
    }
    else if(ctrl->state == LayerStateHold) {
      // キーup処理
      unregister_code16(ctrl->keycode);
      // 状態遷移
      ctrl->state = LayerStateInit;
      //ret = true;
    }
    /* Up時刻記録 */
    ctrl->time = record->event.time;
  }
  return ret;
}


/* 他キーの tapが入ったときに呼び出す(状態変数ビットを1にするだけ) */
static bool process_user_custom_layer_otherkey_down(void) {
  if(layer_ctrl_wait) {
    bool ret = false; // レイヤー遷移有無を返す
    const uint8_t no = layer_ctrl_wait - 1;
    const layer_def_t*  const def = &layer_def[no];
    layer_ctrl_t* const ctrl = &layer_ctrl[no];
    
    if(def->retro) {
      // Hold優先時はここで初めてModを有効にする(→直後にMod対応でlキーが押される)
      layer_on(def->layer);
      layer_cnt[def->layer]++;
      ret = true;
    }
    else {
      // Mod優先時は何もしない
    }
    
    // 待ち状態終了    
    ctrl->state = LayerStateModHold;
    layer_ctrl_wait = 0;
    return ret;
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



  