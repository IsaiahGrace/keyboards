/* Copyright 2021 Isaiah Grace
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

#include "quantum.h"

/* This is a shortcut to help you visually see your layout.
 *
 * The first section contains all of the arguments representing the physical
 * layout of the board and position of the keys.
 *
 * The second converts the arguments into a two-dimensional array which
 * represents the switch matrix.
 */

#define LAYOUT( \
  SW16,SW15,SW14,SW13,SW12,SW11,     SW10,SW09,SW08,SW07,SW06,SW05,  SW04,SW03,SW02,SW01, \
  SW32,SW31,SW30,SW29,SW28,SW27,     SW26,SW25,SW24,SW23,SW22,SW21,  SW20,SW19,SW18,SW17, \
  SW48,SW47,SW46,SW45,SW44,SW43,     SW42,SW41,SW40,SW39,SW38,SW37,  SW36,SW35,SW34,SW33, \
  SW63,SW62,SW61,SW60,SW59,     SW58,     SW57,SW56,SW55,SW54,SW53,  SW52,SW51,SW50,SW49  \
  ) \
  { \
    {SW02, SW04, SW06, SW08, SW10, SW12, SW14, SW16}, \
    {SW01, SW03, SW05, SW07, SW09, SW11, SW13, SW15}, \
    {SW18, SW20, SW22, SW24, SW26, SW28, SW30, SW32}, \
    {SW17, SW19, SW21, SW23, SW25, SW27, SW29, SW31}, \
    {SW34, SW36, SW38, SW40, SW42, SW44, SW46, SW48}, \
    {SW33, SW35, SW37, SW39, SW41, SW43, SW45, SW47}, \
    {SW50, SW52, SW54, SW56, KC_NO,SW59, SW61, SW63}, \
    {SW49, SW51, SW53, SW55, SW57, SW58, SW60, SW62}, \
  }

