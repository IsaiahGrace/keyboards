#! /usr/bin/zsh

# take the contents of this repo and merge it into the QMK fork
rsync -avc ./augio ~/qmk_firmware/keyboards/
