/*
  Copyright 2021 Isaiah Grace

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


/* USB Device descriptor parameter */
#define VENDOR_ID       0xFEED
#define PRODUCT_ID      0xBEEF
#define DEVICE_VER      0x0001
#define MANUFACTURER    Isaiah Grace
#define PRODUCT         AUGIO

/* Key matrix size */
#define MATRIX_ROWS 8
#define MATRIX_COLS 8

/* Key matrix pins */
//                  ROWS: 0   1   2   3   4   5   6   7
//        Pro Micro Pins: A3  A2  A1  A0  15  14  16  10
#define MATRIX_ROW_PINS { F4, F5, F6, F7, B1, B3, B2, B6 }
//                  COLS: 0   1   2   3   4   5   6   7
//        Pro Micro Pins: 9   8   7   6   5   4   3   2
#define MATRIX_COL_PINS { B5, B4, E6, D7, C6, D4, D0, D1 }
#define UNUSED_PINS
#define DIODE_DIRECTION COL2ROW

// Define the QMK DFU escape key, ROW 0, COL 7, upper left corner
#define QMK_ESC_OUTPUT D1 // usually COL
#define QMK_ESC_INPUT F4  // usually ROW

// Define an indicator light
#define QMK_LED B0
