#! /usr/bin/zsh

# take the contents of this repo and merge it into the QMK fork
rsync -avc ./planck ~/qmk_firmware/keyboards/

# Execute a docker build of my firmware
# Compatable with the Wally programmer from Ergodox
cd ~/qmk_firmware
~/qmk_firmware/util/docker_build.sh planck/ez/glow:IsaiahGrace

if [[ -e ~/qmk_firmware/planck_ez_glow_IsaiahGrace.bin ]]; then
    cp -fv ~/qmk_firmware/planck_ez_glow_IsaiahGrace.bin ~/keyboards/bin/planck_ez_glow_IsaiahGrace-`date --iso-8601=seconds | cut -d "-" -f 1-3`.bin
    rm ~/qmk_firmware/planck_ez_glow_IsaiahGrace.bin
fi

