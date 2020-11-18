#pragma once

#ifdef AUDIO_ENABLE
#define STARTUP_SONG SONG(PLANCK_SOUND)
#endif

#define MIDI_BASIC

#define ENCODER_RESOLUTION 4

/*
  Set any config.h overrides for your specific keymap here.
  See config.h options at https://docs.qmk.fm/#/config_options?id=the-configh-file
*/
#define ORYX_CONFIGURATOR
#define FIRMWARE_VERSION u8"L4agy/x6pE5"
#define RGB_MATRIX_STARTUP_SPD 60

#define PLANCK_EZ_USER_LEDS

// These should be the default values, but I'll overwrite them here because I depend on their values
#define RAW_USAGE_PAGE 0x1122
#define RAW_USAGE_ID 0x61
