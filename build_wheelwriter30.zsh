#! /usr/bin/zsh

# take the contents of this repo and merge it into the QMK fork
rsync -avc ./wheelwriter30 ~/qmk_firmware/keyboards/

# Execute a docker build of my firmware
cd ~/qmk_firmware
~/qmk_firmware/util/docker_build.sh wheelwriter30:IsaiahGrace

if [[ -e ~/qmk_firmware/wheelwriter30_default.bin ]]; then
    cp -fv ~/qmk_firmware/wheelwriter30_default.bin ~/keyboards/bin/wheelwriter30_default-`date --iso-8601=seconds | cut -d "-" -f 1-3`.bin
    rm ~/qmk_firmware/wheelwriter30_default.bin
fi

