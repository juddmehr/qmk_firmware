// This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 2 of the License, or (at your option) any later version. This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details. You should have received a copy of the GNU General Public License along with this program. If not, see <http://www.gnu.org/licenses/>.
#pragma once

#include QMK_KEYBOARD_H

//Enumerate layers for easy reference
enum layers { QWERTY, MEDIA, NAV, NUM, FUN, TNAV };

//Mac clipboard commands
#define U_RDO SCMD(KC_Z)
#define U_PST LCMD(KC_V)
#define U_CPY LCMD(KC_C)
#define U_CUT LCMD(KC_X)
#define U_UND LCMD(KC_Z)

/* Custom Commands: */
#define KC_DELWRD LOPT(KC_BSPC) //deletes whole word
#define KC_TOLINEBEGIN LCTL(KC_A) //terminal: goes to beginning of line
#define KC_TOLINEEND LCTL(KC_E) //terminal: goes to beginning of line
#define KC_FOREWORD LOPT(KC_A) //terminal: goes to beginning of line
#define KC_BACKWORD LOPT(KC_B) //terminal: goes to beginning of line
#define U_NA KC_NO // present but not available for use
#define U_NU KC_NO // available but not used
