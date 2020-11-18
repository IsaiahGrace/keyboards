#! /usr/bin/zsh

cd ~/qmk_firmware
~/qmk_firmware/util/docker_build.sh clean
rm -rfv *.bin
