/*
This is the c configuration file for the keymap

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


/* from default */
#pragma once

//#define USE_MATRIX_I2C

//Select hand configuration
#define MASTER_LEFT

#define USE_SERIAL_PD2

/*#define OLED_FONT_H "keyboards/crkbd/lib/glcdfont.c"*/
/*// #define OLED_UPDATE_INTERVAL 5 //update OLED every 5ms*/
/*#define OLED_BRIGHTNESS 185 //SET OLED BRIGHTNESS DIMMER (255 MAX)*/
/**/
/**/
/**/
/* From miryoku config */
// default but used in macros
#undef TAPPING_TERM
#define TAPPING_TERM 175

// Prevent normal rollover on alphas from accidentally triggering mods.
/*#define IGNORE_MOD_TAP_INTERRUPT*/

// Enable rapid switch from tap to hold, disables double tap hold auto-repeat.
#define TAPPING_FORCE_HOLD

// Auto Shift
#define NO_AUTO_SHIFT_ALPHA
#define AUTO_SHIFT_TIMEOUT TAPPING_TERM
#define AUTO_SHIFT_NO_SETUP

// Recommended for heavy chording.
#define QMK_KEYS_PER_SCAN 4
