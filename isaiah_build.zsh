#! /usr/bin/zsh

# take the contents of this repo and merge it into the QMK fork
rsync -av ./planck ~/qmk_firmware/keyboards/
rsync -av ./wheelwriter30 ~/qmk_firmware/keyboards/

# Execute a docker build of my firmware
# Compatable with the Wally programmer from Ergodox
cd ~/qmk_firmware
~/qmk_firmware/util/docker_build.sh planck/ez/glow:IsaiahGrace

cp -fv ~/qmk_firmware/planck_ez_glow_IsaiahGrace.bin ~/plankEZ/planck_ez_glow_IsaiahGrace-`date --iso`.bin
