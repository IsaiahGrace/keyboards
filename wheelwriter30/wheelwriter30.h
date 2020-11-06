/* Copyright 2020 Isaiah Grace
 * Adapted from work by Ben Chapman, available on GitHub
 *
 * This work is a derivative of "modelm101"
 * (https://github.com/qmk/qmk_firmware/tree/master/keyboards/converter/modelm101)
 * by iw0rm3r (https://github.com/iw0rm3r)
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

#pragma once

#include "quantum.h" // TODO: Why? Do I need this?

/* This is a shortcut to help you visually see your layout.
 *
 * The first section contains all of the arguments representing the physical
 * layout of the board and position of the keys.
 *
 * The second converts the arguments into a two-dimensional array which
 * represents the switch matrix.
 */

/* This is what is printed on each keycap:

  Frmat Mar_Rel  +-     1 2 3 4 5 6 7 8 9 0 -  +  Backspace  Home Paper_Up   Print_Mode
  Store Lmar     Tab    Q W E R T Y U I O P ¼  [  Enter      End  Paper_Down Justify
  Play  Rmar     Lock   A S D F G H J K L ; “     RShift     Find Reloc      Chng
  Del   T_Set    LShift Z X C V B N M . , /?                      UP
  Menu  T_Clr           Code  Space               Word       LEFT DOWN       RIGHT

*/

#define LAYOUT(	\
	       K0A,K0B,  K0C,K0D,K0E,K0F,K0G,K0H,K0I,K0J,K0K,K0L,K0M,K0N,K0O,K0P,  K0Q,K0R,K0S, \
	       K1A,K1B,  K1C,K1D,K1E,K1F,K1G,K1H,K1I,K1J,K1K,K1L,K1M,K1N,K1O,K1P,  K1Q,K1R,K1S, \
	       K2A,K2B,  K2C,K2D,K2E,K2F,K2G,K2H,K2I,K2J,K2K,K2L,K2M,K2N,    K2P,  K2Q,K2R,K2S, \
	       K3A,K3B,  K3C,K3D,K3E,K3F,K3G,K3H,K3I,K3J,K3K,K3L,K3M,                  K3R,     \
	       K4A,K4B,      K4D,        K4G,                                K4P,  K4Q,K4R,K4S  \
		) \
  { \
    {K4B,   K4A,   KC_NO, KC_NO, KC_NO, KC_NO, K2H,   K2I,   KC_NO, KC_NO, K2N,   K1P,   K4R,   KC_NO}, \
    {K3A,   K3B,   KC_NO, K2D,   K2E,   K2F,   K2G,   K2J,   K2K,   K2L,   K2M,   K2Q,   K2R,   KC_NO}, \
    {K0A,   K0B,   KC_NO, K0C,   KC_NO, KC_NO, K0H,   K0I,   K0O,   KC_NO, K0N,   K0P,   K0R,   KC_NO}, \
    {K1A,   KC_NO, KC_NO, K0D,   K0E,   K0F,   K0G,   K0J,   K0K,   K0L,   K0M,   K0Q,   K0S,   KC_NO}, \
    {K1B,   K1C,   KC_NO, K1D,   K1E,   K1F,   K1G,   K1J,   K1K,   K1L,   K1M,   K1Q,   K1R,   KC_NO}, \
    {K2A,   K2B,   KC_NO, KC_NO, KC_NO, KC_NO, K1H,   K1I,   K1O,   KC_NO, K1N,   KC_NO, K1S,   KC_NO}, \
    {KC_NO, K2C,   K2P,   K3D,   K3E,   K3F,   K3G,   K3J,   K3K,   K3L,   KC_NO, K3R,   K2S,   KC_NO}, \
    {K4G,   K4P,   K3C,   KC_NO, KC_NO, KC_NO, K3H,   K3I,   KC_NO, KC_NO, K3M,   K4Q,   K4S,   K4D  }  \
  }
