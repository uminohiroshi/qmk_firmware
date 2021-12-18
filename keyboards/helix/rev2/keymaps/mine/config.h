/*
This is the c configuration file for the keymap

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

// place overrides here

// If you need more program area, try select and reduce rgblight modes to use.

// Selection of RGBLIGHT MODE to use.
#if defined(LED_ANIMATIONS)
   #define RGBLIGHT_EFFECT_BREATHING
   #define RGBLIGHT_EFFECT_RAINBOW_MOOD
   #define RGBLIGHT_EFFECT_RAINBOW_SWIRL
   #define RGBLIGHT_EFFECT_SNAKE
   #define RGBLIGHT_EFFECT_KNIGHT
   #define RGBLIGHT_EFFECT_CHRISTMAS
   #define RGBLIGHT_EFFECT_STATIC_GRADIENT
   //#define RGBLIGHT_EFFECT_RGB_TEST
   //#define RGBLIGHT_EFFECT_ALTERNATING
#endif

// 自分用カスタマイズ
#undef  TAPPING_TERM
#undef  TAPPING_FORCE_HOLD
#define TAPPING_TERM    200                 // タッピング判定時間

#define TAPPING_TERM_PER_KEY                // key毎に tapping termを切り替える
#define PERMISSIVE_HOLD_PER_KEY             // key毎に 許容ホールドを設定する
#define HOLD_ON_OTHER_KEY_PRESS_PER_KEY     // key毎に hold機能優先を設定する
#define IGNORE_MOD_TAP_INTERRUPT_PER_KEY    // key毎に モッドタップ割り込み無視を設定する
#define TAPPING_FORCE_HOLD_PER_KEY          // key毎に タッピング強制holdを設定する

// LCTL + ", RCTL + '
#define LCPO_KEYS   KC_LCTL, KC_LSFT, KC_2  // [LCTL] + ["]
#define RCPC_KEYS   KC_RCTL, KC_RSFT, KC_7  // [RCTL] + [']

// COMBOを使う
#define COMBO_COUNT 6
#define COMBO_TERM  10

// スワップハンド有効化
#define SWAP_HANDS_ENABLE

