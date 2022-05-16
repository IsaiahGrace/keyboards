MCU = atmega32u4

# Left hand: Elite-C
# qmk flash -bl dfu-split-left
BOOTLOADER = atmel-dfu

# Right hand: Arduino Pro micro
# qmk flash -bl avrdude-split-right
#BOOTLOADER = caterina

SPLIT_KEYBOARD = yes
SERIAL_DRIVER = bitbang

AUTO_SHIFT_ENABLE = yes
LTO_ENABLE        = yes
MOUSEKEY_ENABLE   = yes

NKRO_ENABLE       = no
OLED_ENABLE       = no
RGBLIGHT_ENABLE   = no
