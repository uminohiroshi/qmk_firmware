<<<<<<<< HEAD:keyboards/ibm/model_m/yacobo/yacobo.c
/* Copyright 2024 Stephen Edwards
========
/* Copyright 2020 GhostSeven <work@ghost7.com>
>>>>>>>> e6c16a4719 (Convert `eeconfig_init_kb` implementations to config (#24087)):keyboards/handwired/bento/rev1/config.h
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
 *
 * Adapted from the Model H Project by Jonathan Hawthorn.
 */
#pragma once

<<<<<<<< HEAD:keyboards/ibm/model_m/yacobo/yacobo.c
#include "quantum.h"


void keyboard_pre_init_kb(void) {
    gpio_set_pin_output(BLUE_PILL_STATUS_LED);
    gpio_write_pin(BLUE_PILL_STATUS_LED, 0);
    keyboard_pre_init_user();
}
========
#define RGBLIGHT_DEFAULT_MODE (RGBLIGHT_MODE_RAINBOW_SWIRL + 2)
>>>>>>>> e6c16a4719 (Convert `eeconfig_init_kb` implementations to config (#24087)):keyboards/handwired/bento/rev1/config.h
