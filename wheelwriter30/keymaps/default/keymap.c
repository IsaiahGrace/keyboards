#include QMK_KEYBOARD_H
#include <string.h>
#include <stdio.h>

#include "raw_hid.h"

enum wheelwriter30_layers {
  _BASE,
  _CODE,
};

#define CODE MO(_CODE)
#define ___ KC_NO
#define ____ KC_TRANSPARENT


/* This is what is printed on each keycap:

  Frmat Mar_Rel  +-     1 2 3 4 5 6 7 8 9 0 -  +  Backspace  Home Paper_Up   Print_Mode
  Store Lmar     Tab    Q W E R T Y U I O P ¼  [  Enter      End  Paper_Down Justify
  Play  Rmar     Lock   A S D F G H J K L ; “     RShift     Find Reloc      Chng
  Del   T_Set    LShift Z X C V B N M . , /?                      UP
  Menu  T_Clr           Code  Space               Word       LEFT DOWN       RIGHT

*/

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT(
		   ___,___,  KC_ESCAPE  ,KC_1,KC_2,KC_3,KC_4,KC_5,KC_6,KC_7,KC_8,  KC_9,   KC_0,   KC_MINS, KC_EQL, KC_BSPC,  KC_HOME,KC_PGUP,KC_PSCREEN,
		   ___,___,  KC_TAB     ,KC_Q,KC_W,KC_E,KC_R,KC_T,KC_Y,KC_U,KC_I,  KC_O,   KC_P,   KC_NO,   KC_LBRC,KC_ENTER, KC_END, KC_PGDN,KC_NO,
		   ___,___,  KC_CAPSLOCK,KC_A,KC_S,KC_D,KC_F,KC_G,KC_H,KC_J,KC_K,  KC_L,   KC_SCLN,KC_QUOTE,        KC_RSHIFT,KC_FIND,KC_NO,  KC_NO,
		   ___,___,  KC_LSHIFT  ,KC_Z,KC_X,KC_C,KC_V,KC_B,KC_N,KC_M,KC_DOT,KC_COMM,KC_SLSH,                                   KC_UP,
		   ___,___,              CODE,          KC_SPACE,                                                   KC_DELETE,KC_LEFT,KC_DOWN,KC_RIGHT
		   ),
  [_CODE] = LAYOUT(
		   ____,____,  ____,____,____,____,____,____,____,____,____,____,____,____,____,____,____,____,____,
		   ____,____,  ____,____,____,____,____,____,____,____,____,____,____,____,____,____,____,____,____,
		   ____,____,  ____,____,____,____,____,____,____,____,____,____,____,____,     ____,____,____,____,
		   ____,____,  ____,____,____,____,____,____,____,____,____,____,____,                    ____,
		   ____,____,       ____,          ____,                                        ____,____,____,____
		   ),
};


// TODO: The fact that I have to define this here is extreemly sus. I should remove it as soon as I understand why
#ifndef RAW_EPSIZE
#define RAW_EPSIZE 32
#endif


// This function creates packets of exactly RAW_EPSIZE to be broken down and sent via raw_hid_send()
// This is because raw_hid_send will do nothing if length != RAW_EPSIZE
// INFO: As far as I can tell, a packet starting with 0 will not transmit that first byte
// Somehow someway, by the time the packet gets to my linux python scripts, the first zero of the packet is missing...
void raw_hid_send_pad(uint8_t *data, uint8_t length) {
  // if the length is already correct, just send it quick and don't bother with the slower packet conversion
  if (length == RAW_EPSIZE) {
    raw_hid_send(data, RAW_EPSIZE);
    return;
  }

  uint8_t packet[RAW_EPSIZE];
  uint8_t n = 0;
  
  while (n < length) {
    for (uint8_t i = 0; i < RAW_EPSIZE; i++) {
      packet[i] = i < length ? data[n] : 0;
      n++;
    }
    raw_hid_send(packet, RAW_EPSIZE);
  }
}


// Raw hid packets are arbitrary data from the host
void raw_hid_receive(uint8_t *data, uint8_t length) {
  // this code executes when a data packet is recieved from the host
  raw_hid_send_pad(data,length);
}
