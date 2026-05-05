# keyboard固有設定
## OLED設定 : デフォルトで有効
OLED_ENABLE = no        	# OLED無効
#OLED_DRIVER = ssd1306		# OLED driver : SSD1306, SH1106, SH1107
#OLED_TRANSPORT = i2c		# communication : I2C

## RGB Light設定 : デフォルトで有効
#RGBLIGHT_ENABLE = yes		# RGB Light(WS2812)
#RGBLIGHT_DRIVER = ws2812
#RGB_MATRIX_ENABLE = no		# MATRIXは使わない

# 個人設定 #############################################################
LTO_ENABLE = yes			# ROM削減のため
VIA_ENABLE = yes			# VIA有効

# 機能
MOUSEKEY_ENABLE = yes		# マウス操作有効 # 暫定無効でトライ
EXTRAKEY_ENABLE = yes		# マルチメディアキー有効
COMBO_ENABLE = yes			# combo
SWAP_HANDS_ENABLE = no		# swap hands無効
REPEAT_KEY_ENABLE = yes		# repeat key

DYNAMIC_MACRO_ENABLE = no	# 動的マクロ無効
LEADER_ENABLE = no			# leaderキー無効
TAP_DANCE_ENABLE = no		# tap dance無効

CONSOLE_ENABLE = no			# シリアル無効
