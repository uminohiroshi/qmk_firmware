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

#pragma once

#define MASTER_LEFT
#define OLED_FONT_H "keyboards/dailycraft/claw44/lib/glcdfont.c"

//#define DEBOUNCE                    10     // キーチャタリング対策

//#define LEADER_TIMEOUT              1000    // LEADER_PER_KEY_TIMEOUT使うときのmax=300
//#define LEADER_NO_TIMEOUT                   // 先頭のキーはタイムアウトなし

#define DYNAMIC_MACRO_DELAY         20      // 再生delay
#define DYNAMIC_KEYMAP_LAYER_COUNT  8


// 自分用カスタマイズ
#undef  TAPPING_TERM
#undef  TAPPING_FORCE_HOLD
#define TAPPING_TERM    200                 // タッピング判定時間

#define TAPPING_TERM_PER_KEY                // key毎に tapping termを切り替える
#define PERMISSIVE_HOLD_PER_KEY             // key毎に 許容ホールドを設定する
#define HOLD_ON_OTHER_KEY_PRESS_PER_KEY     // key毎に hold機能優先を設定する
//#define TAPPING_FORCE_HOLD_PER_KEY          // key毎に タッピング強制holdを設定する

// LCTL + ", RCTL + '
//#define LCPO_KEYS   KC_LCTL, KC_LSFT, KC_2  // [LCTL] + ["] // 未使用
#define RCPC_KEYS   KC_RCTL, KC_RSFT, KC_7  // [RCTL] + [']

//#define CONSOLE_BAUD 921600

// combo
#define COMBO_TERM          10
#define COMBO_STRICT_TIMER
#define COMBO_TERM_PER_COMBO

// keylogger
// #define KEY_LOGGING
