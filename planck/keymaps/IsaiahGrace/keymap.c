#include QMK_KEYBOARD_H
#ifdef AUDIO_ENABLE
#include "muse.h"
#endif
#include "eeprom.h"
#include "raw_hid.h"

#define KC_MAC_UNDO LGUI(KC_Z)
#define KC_MAC_CUT LGUI(KC_X)
#define KC_MAC_COPY LGUI(KC_C)
#define KC_MAC_PASTE LGUI(KC_V)
#define KC_PC_UNDO LCTL(KC_Z)
#define KC_PC_CUT LCTL(KC_X)
#define KC_PC_COPY LCTL(KC_C)
#define KC_PC_PASTE LCTL(KC_V)
#define ES_LESS_MAC KC_GRAVE
#define ES_GRTR_MAC LSFT(KC_GRAVE)
#define ES_BSLS_MAC ALGR(KC_6)
#define NO_PIPE_ALT KC_GRAVE
#define NO_BSLS_ALT KC_EQUAL
#define LSA_T(kc) MT(MOD_LSFT | MOD_LALT, kc)
#define BP_NDSH_MAC ALGR(KC_8)

#define MUSICAL_LIGHTS_OFF_COLOR 0
#define MUSICAL_LIGHTS_OFF_TOLERANCE 0
#define MUSICAL_LIGHTS_ON_TOLERANCE 40

enum planck_keycodes {
  RGB_SLD = EZ_SAFE_RANGE,
};

enum planck_layers {
  _BASE,
  _LOWER,
  _RAISE,
  _ADJUST,
  _GAME,
};

#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT_planck_grid(
			       KC_ESCAPE,KC_Q,KC_W,KC_E,KC_R,KC_T,KC_Y,KC_U,KC_I,KC_O,KC_P,KC_BSPACE,
			       KC_TAB,KC_A,KC_S,KC_D,KC_F,KC_G,KC_H,KC_J,KC_K,KC_L,KC_SCOLON,KC_QUOTE,
			       KC_LSHIFT,KC_Z,KC_X,KC_C,KC_V,KC_B,KC_N,KC_M,KC_COMMA,KC_DOT,KC_SLASH,KC_ENTER,
			       KC_LCTRL,RGB_MOD,KC_LALT,KC_LGUI,LOWER,KC_SPACE,KC_NO,RAISE,KC_LEFT,KC_DOWN,KC_UP,KC_RIGHT),

  [_LOWER] = LAYOUT_planck_grid(
				KC_TILD,KC_EXLM,KC_AT,KC_HASH,KC_DLR,KC_PERC,KC_CIRC,KC_AMPR,KC_ASTR,KC_LPRN,KC_RPRN,KC_TRANSPARENT,
				KC_DELETE,KC_F1,KC_F2,KC_F3,KC_F4,KC_F5,KC_F6,KC_UNDS,KC_PLUS,KC_LCBR,KC_RCBR,KC_PIPE,KC_TRANSPARENT,
				KC_F7,KC_F8,KC_F9,KC_F10,KC_F11,KC_F12,LALT(KC_F4),KC_TRANSPARENT,KC_HOME,KC_END,KC_TRANSPARENT,KC_TRANSPARENT,
				KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_NO,KC_TRANSPARENT,KC_MEDIA_NEXT_TRACK,KC_AUDIO_VOL_DOWN,KC_AUDIO_VOL_UP,KC_MEDIA_PLAY_PAUSE),

  [_RAISE] = LAYOUT_planck_grid(
				KC_GRAVE,KC_1,KC_2,KC_3,KC_4,KC_5,KC_6,KC_7,KC_8,KC_9,KC_0,KC_TRANSPARENT,
				KC_DELETE,KC_F1,KC_F2,KC_F3,KC_F4,KC_F5,KC_F6,KC_MINUS,KC_EQUAL,KC_LBRACKET,KC_RBRACKET,KC_BSLASH,KC_TRANSPARENT,
				KC_F7,KC_F8,KC_F9,KC_F10,KC_F11,KC_F12,LALT(KC_F4),KC_TRANSPARENT,KC_PGDOWN,KC_PGUP,KC_TRANSPARENT,KC_TRANSPARENT,
				KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_NO,KC_TRANSPARENT,KC_MEDIA_NEXT_TRACK,KC_AUDIO_VOL_DOWN,KC_AUDIO_VOL_UP,KC_MEDIA_PLAY_PAUSE),

  [_ADJUST] = LAYOUT_planck_grid(
				 KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_MS_LEFT,KC_MS_DOWN,KC_MS_UP,KC_MS_RIGHT,KC_TRANSPARENT,
				 KC_DELETE,KC_TRANSPARENT,AU_ON,AU_OFF,AU_TOG,LALT(LCTL(KC_LEFT)),LALT(LCTL(KC_RIGHT)),KC_TRANSPARENT,RGB_VAI,RGB_VAD,KC_TRANSPARENT,RESET,
				 KC_TRANSPARENT,KC_TRANSPARENT,MU_ON,MU_OFF,MU_TOG,LALT(LCTL(LSFT(KC_LEFT))),LALT(LCTL(LSFT(KC_RIGHT))),TO(4),RGB_HUI,RGB_HUD,KC_TRANSPARENT,KC_TRANSPARENT,
				 WEBUSB_PAIR,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_NO,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT),

  [_GAME] = LAYOUT_planck_grid(
				 KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,
				 KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,
				 KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,
				 KC_TRANSPARENT,TO(0),KC_TRANSPARENT,KC_TRANSPARENT,KC_SPACE,LOWER,KC_NO,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT),
  
};

extern bool g_suspend_state;
extern rgb_config_t rgb_matrix_config;

uint8_t musical_lights_tolerance;
//uint8_t musical_lights_active;
struct {
  uint8_t red;
  uint8_t green;
  uint8_t blue;
} musical_lights_base;


void keyboard_post_init_user(void) {
  planck_ez_right_led_level(128);
  planck_ez_left_led_level(128);
  planck_ez_left_led_off();
  planck_ez_right_led_off();
  rgb_matrix_enable();
  
  musical_lights_base.red = MUSICAL_LIGHTS_OFF_COLOR;
  musical_lights_base.green = MUSICAL_LIGHTS_OFF_COLOR;
  musical_lights_base.blue = MUSICAL_LIGHTS_OFF_COLOR;
  musical_lights_tolerance = MUSICAL_LIGHTS_OFF_TOLERANCE;
  //musical_lights_active = 1;
}

const uint8_t PROGMEM ledmap[][DRIVER_LED_TOTAL][3] = {
  [4] = { {0,183,238}, {0,183,238},  {31,255,255}, {0,183,238},  {0,183,238},  {0,183,238}, {0,183,238}, {0,183,238}, {0,183,238}, {0,183,238}, {0,183,238}, {0,183,238},
	  {0,183,238}, {31,255,255}, {31,255,255}, {31,255,255}, {0,183,238},  {0,183,238}, {0,183,238}, {0,183,238}, {0,183,238}, {0,183,238}, {0,183,238}, {0,183,238},
	  {0,183,238}, {0,183,238},  {0,183,238},  {0,183,238},  {0,183,238},  {0,183,238}, {0,183,238}, {0,183,238}, {0,183,238}, {0,183,238}, {0,183,238}, {0,183,238},
	  {0,183,238}, {31,255,255}, {0,183,238},  {0,183,238},  {31,255,255}, {0,183,238}, {0,183,238}, {0,183,238}, {0,183,238}, {0,183,238}, {0,183,238} },

};

void set_layer_color(int layer) {
  for (int i = 0; i < DRIVER_LED_TOTAL; i++) {
    HSV hsv = {
      .h = pgm_read_byte(&ledmap[layer][i][0]),
      .s = pgm_read_byte(&ledmap[layer][i][1]),
      .v = pgm_read_byte(&ledmap[layer][i][2]),
    };
    if (!hsv.h && !hsv.s && !hsv.v) {
        rgb_matrix_set_color( i, 0, 0, 0 );
    } else {
        RGB rgb = hsv_to_rgb( hsv );
        float f = (float)rgb_matrix_config.hsv.v / UINT8_MAX;
        rgb_matrix_set_color( i, f * rgb.r, f * rgb.g, f * rgb.b );
    }
  }
}

void rgb_matrix_indicators_user(void) {
  if (g_suspend_state || keyboard_config.disable_layer_led) { return; }
  switch (biton32(layer_state)) {
    case 4:
      set_layer_color(4);
      break;
   default:
    if (rgb_matrix_get_flags() == LED_FLAG_NONE)
      rgb_matrix_set_color_all(0, 0, 0);
    break;
  }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case RGB_SLD:
      if (record->event.pressed) {
        rgblight_mode(1);
      }
      return false;
  }
  return true;
}

#ifdef AUDIO_ENABLE
bool muse_mode = false;
uint8_t last_muse_note = 0;
uint16_t muse_counter = 0;
uint8_t muse_offset = 70;
uint16_t muse_tempo = 50;

void encoder_update(bool clockwise) {
    if (muse_mode) {
        if (IS_LAYER_ON(_RAISE)) {
            if (clockwise) {
                muse_offset++;
            } else {
                muse_offset--;
            }
        } else {
            if (clockwise) {
                muse_tempo+=1;
            } else {
                muse_tempo-=1;
            }
        }
    } else {
        if (clockwise) {
        #ifdef MOUSEKEY_ENABLE
            register_code(KC_MS_WH_DOWN);
            unregister_code(KC_MS_WH_DOWN);
        #else
            register_code(KC_PGDN);
            unregister_code(KC_PGDN);
        #endif
        } else {
        #ifdef MOUSEKEY_ENABLE
            register_code(KC_MS_WH_UP);
            unregister_code(KC_MS_WH_UP);
        #else
            register_code(KC_PGUP);
            unregister_code(KC_PGUP);
        #endif
        }
    }
}

void matrix_scan_user(void) {
#ifdef AUDIO_ENABLE
    if (muse_mode) {
        if (muse_counter == 0) {
            uint8_t muse_note = muse_offset + SCALE[muse_clock_pulse()];
            if (muse_note != last_muse_note) {
                stop_note(compute_freq_for_midi_note(last_muse_note));
                play_note(compute_freq_for_midi_note(muse_note), 0xF);
                last_muse_note = muse_note;
            }
        }
        muse_counter = (muse_counter + 1) % muse_tempo;
    }
#endif
}

bool music_mask_user(uint16_t keycode) {
    switch (keycode) {
    case RAISE:
    case LOWER:
        return false;
    default:
        return true;
    }
}
#endif

uint32_t layer_state_set_user(uint32_t state) {

  state = update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
  
  // So state in this context is a layer_state
  // biton32 returns the highest set bit
  // The layers are represented as bits in state
  // BASE   0  1
  // LOWER  1  2
  // RAISE  2  4
  // ADJUST 3  8
  // GAME   4 16
  uint8_t layer = biton32(state);

  // Take care of the auto-shift
  if (layer == _GAME) {
    autoshift_disable();
    // update layer to remove the bit from the _GAME layer_state
    layer = biton32(state & ~(1 << _GAME));
  } else {
    autoshift_enable();
  }

  // Now Take care of the lights
  switch (layer) {
  case _BASE:
    planck_ez_left_led_off();
    planck_ez_right_led_off();
    break;
  case _LOWER:
    planck_ez_left_led_on();
    planck_ez_right_led_off();
    break;
  case _RAISE:
    planck_ez_left_led_off();
    planck_ez_right_led_on();
    break;
  case _ADJUST:
    planck_ez_left_led_on();
    planck_ez_right_led_on();
    break;
  }
  
  return state;
}

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

enum hid_codes {
  HID_PING  = 1,
  HID_START = 2,
  HID_COLOR = 3,
  HID_STOP  = 4,
};

// Raw hid packets are arbitrary data from the host
void raw_hid_receive(uint8_t *data, uint8_t length) {
  // this code executes when a data packet is recieved from the host
  switch (data[0]) {
  case HID_PING:
    // A packet starting with HID_PING will be echoed back to the host
    raw_hid_send_pad(data,length);
    break;
  case HID_START:
    break;
  case HID_COLOR:
    musical_lights_base.red = data[1];
    musical_lights_base.green = data[2];
    musical_lights_base.blue = data[3];
    musical_lights_tolerance = MUSICAL_LIGHTS_ON_TOLERANCE;
    break;
  case HID_STOP:
    musical_lights_base.red = MUSICAL_LIGHTS_OFF_COLOR;
    musical_lights_base.green = MUSICAL_LIGHTS_OFF_COLOR;
    musical_lights_base.blue = MUSICAL_LIGHTS_OFF_COLOR;
    musical_lights_tolerance = MUSICAL_LIGHTS_OFF_TOLERANCE;
    break;
  }
}

