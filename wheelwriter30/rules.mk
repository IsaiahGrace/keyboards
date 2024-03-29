#
#  Copyright 2020 Isaiah Grace
#
#  This program is free software: you can redistribute it and/or modify
#  it under the terms of the GNU General Public License as published by
#  the Free Software Foundation, either version 2 of the License, or
#  (at your option) any later version.
#
#  This program is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#  GNU General Public License for more details.
#
#  You should have received a copy of the GNU General Public License
#  along with this program.  If not, see <http://www.gnu.org/licenses/>.


MCU = STM32F303 # Proton C
BOOTLOADER = stm32-dfu

# Build Options
#   change yes to no to disable
#
AUDIO_DRIVER = dac_additive
AUDIO_ENABLE = yes
BACKLIGHT_ENABLE = no   # Enable keyboard backlight functionality
BOOTMAGIC_ENABLE = no   # Virtual DIP switch configuration
COMMAND_ENABLE = no     # Commands for debug and configuration
CONSOLE_ENABLE = no     # Console for debug
ENCODER_ENABLE = no
EXTRAKEY_ENABLE = yes   # Audio control and System control
MOUSEKEY_ENABLE = no    # Mouse keys
NKRO_ENABLE = no        # USB Nkey Rollover - if this doesn't work, see here: https://github.com/tmk/tmk_keyboard/wiki/FAQ#nkro-doesnt-work
OLED_DRIVER_ENABLE = no
RAW_ENABLE = yes
RGBLIGHT_ENABLE = no
SLEEP_LED_ENABLE = no   # Breathing sleep LED during USB suspend
UNICODE_ENABLE = yes
USE_I2C = no
