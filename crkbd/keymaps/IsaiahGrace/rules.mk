MCU = atmega32u4

# Left hand: Elite-C
# qmk flash -bl dfu-split-left
#BOOTLOADER = atmel-dfu

# Right hand: Arduino Pro micro
# qmk flash -bl avrdude-split-right
BOOTLOADER = caterina

SPLIT_KEYBOARD = yes
SERIAL_DRIVER = bitbang

MOUSEKEY_ENABLE = yes
RGBLIGHT_ENABLE = no
OLED_ENABLE     = no
LTO_ENABLE      = yes
