#! /usr/bin/zsh

# take the contents of this repo and merge it into the QMK fork
rsync -av ./wheelwriter30 ~/qmk_firmware/keyboards/

# Execute a docker build of my firmware
# Compatable with the Wally programmer from Ergodox
cd ~/qmk_firmware
~/qmk_firmware/util/docker_build.sh wheelwriter:IsaiahGrace

cp -fv ~/qmk_firmware/wheelwriter_IsaiahGrace.bin ~/keyboards/bin/wheelwriter_IsaiahGrace-`date --iso`.bin

