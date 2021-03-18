#! /usr/bin/zsh

# take the contents of this repo and merge it into the QMK fork
rsync -avc ./augio ~/qmk_firmware/keyboards/

# Execute a docker build of my firmware
cd ~/qmk_firmware
~/qmk_firmware/util/docker_build.sh augio:IsaiahGrace

