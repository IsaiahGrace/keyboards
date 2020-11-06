/*
  Copyright 2020 Isaiah Grace

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
#define PRODUCT_ID      0x6060
#define DEVICE_VER      0x0001
#define MANUFACTURER    Isaiah Grace
#define PRODUCT         IBM Wheelwriter30

/* Key matrix size */
#define MATRIX_ROWS 8
#define MATRIX_COLS 14

/* Key matrix pins */
#define MATRIX_ROW_PINS { } // TODO: Figure out the pinouts!
#define MATRIX_COL_PINS { }
#define UNUSED_PINS
#define MATRIX_HAS_GHOST // IMPORTANT! The keyboard has no diodes

// I bought the Proton C and the speaker, so i'll enable this...
#ifdef AUDIO_ENABLE
#define STARTUP_SONG_DOOM SONG(E1M1_DOOM)
#define STARTUP_SONG SONG( \
    Q__NOTE(_E6), \
    Q__NOTE(_A6), \
    H__NOTE(_E7), \
    Q__NOTE(_E6), \
    Q__NOTE(_E7) \
)
#endif

/* OLED */
// OLED would be cool someday, so i'll leave this here to remind me
// Don't forget to enable OLED_DRIVER_ENABLE in rules.mk
// #define OLED_FONT_H "glcdfont_d48.c"
// #define OLED_TIMEOUT 0
// #define OLED_SCROLL_TIMEOUT 1000
