// Copyright 2025 QMK
// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once

#define AUDIO_PIN B5


#if 0
#define OLED_TIMEOUT 60000  // 60秒で自動オフ
#endif

#if 0
// LEDアニメーション設定(定義のあるもの有効)
#define RGBLIGHT_EFFECT_BREATHING
#define RGBLIGHT_EFFECT_RAINBOW_MOOD
#define RGBLIGHT_EFFECT_RAINBOW_SWIRL
#define RGBLIGHT_EFFECT_SNAKE
#define RGBLIGHT_EFFECT_KNIGHT
#define RGBLIGHT_EFFECT_CHRISTMAS
#define RGBLIGHT_EFFECT_STATIC_GRADIENT
#define RGBLIGHT_EFFECT_RGB_TEST
#define RGBLIGHT_EFFECT_ALTERNATING
#define RGBLIGHT_EFFECT_TWINKLE
#endif

// 基本設定
#define DYNAMIC_MACRO_DELAY         20      // 再生delay
#define DYNAMIC_KEYMAP_LAYER_COUNT  7

// 自分用カスタマイズ
#define TAP_CODE_DELAY  10
#undef  TAPPING_TERM
#undef  TAPPING_FORCE_HOLD
#define TAPPING_TERM    200                 // タッピング判定時間

#define TAPPING_TERM_PER_KEY                // key毎に tapping termを切り替える
#define PERMISSIVE_HOLD_PER_KEY             // key毎に 許容ホールドを設定する
#define HOLD_ON_OTHER_KEY_PRESS_PER_KEY     // key毎に hold機能優先を設定する
//#define TAPPING_FORCE_HOLD_PER_KEY          // key毎に タッピング強制holdを設定する

// LCTL + ", RCTL + '
//#define LCPO_KEYS   KC_LCTL, KC_LSFT, KC_2  // [LCTL] + ["]
#define RCPC_KEYS   KC_RCTL, KC_RSFT, KC_7  // [RCTL] + [']

// COMBOを使う
#define COMBO_COUNT 6
#define COMBO_TERM  10
