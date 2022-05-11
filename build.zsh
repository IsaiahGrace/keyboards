#! /bin/zsh

# This script is a simple wrapper around the docker_build.sh utility of QMK.
# This script lives in my personal keyboards repo and copies source files to the
# qmk_firmware directory before compiling. This way my personal keyboard config
# is independent from the qmk_firmware repository.

sync_sources() {
    if (( $# == 0 )); then
        echo "Error: sync_sources() called without argument"
        exit 1
    fi

    if [[ ! -d $1 ]]; then
        echo "Error: $1 not a directory."
        exit 1
    fi

    echo "Copying $1 to ../qmk_firmware/keyboards/"
    rsync -avc --exclude=doc $1 ../qmk_firmware/keyboards/
    echo
}

copy_binary() {
    if (( $# == 0 )); then
        echo "Error: copy_binary() called without argument"
        exit 1
    fi

    echo
    echo "Copying $1 binaries to bin/"

    mkdir -p bin
    tmp1=$(mktemp -d)
    tmp2=$(mktemp -d)

    bin_found=1

    ls ../qmk_firmware | grep -E "$1.*\.(bin|hex)" | while read file; do
        bin_found=0
        cp ../qmk_firmware/$file $tmp1/
    done

    if [[ ! $bin_found ]]; then
        echo "Couldn't find compiled .bin or .hex"
        echo "Looked for: ../qmk_firmware/$1*.(bin|hex)"
    fi

    for file in $tmp1/*; do
        build_time=$(date --iso-8601=seconds | cut -d "-" -f 1-3)
        root_name=$(echo $file | xargs basename | sed 's/.bin//; s/.hex//')
        file_type=$(echo $file | grep -oE "\.(bin|hex)")
        file_name=$root_name-$build_time$file_type
        mv $file $tmp2/$file_name
        echo "bin/$file_name"
    done

    mv $tmp2/* bin/
    rm -rf $tmp1 $tmp2
}

augio() {
    echo "Compiling augio firmware"
    sync_sources augio

    pushd ../qmk_firmware
    util/docker_build.sh augio:IsaiahGrace
    popd

    copy_binary augio
}

corne() {
    echo "Compiling corne (crkbd) firmware"
    sync_sources crkbd

    pushd ../qmk_firmware
    util/docker_build.sh crkbd:IsaiahGrace
    popd

    copy_binary crkbd
}

planck() {
    echo "Compiling plank firmware"
    sync_sources planck

    pushd ../qmk_firmware
    util/docker_build.sh planck/ez/glow::IsaiahGrace
    popd

    copy_binary planck
}

wheelwriter30() {
    echo "Compiling wheelwriter30 firmware"
    sync_sources wheelwriter30

    pushd ../qmk_firmware
    util/docker_build.sh wheelwriter30:IsaiahGrace
    popd

    copy_binary wheelwriter30
}

clean() {
    pushd ../qmk_firmware
    util/docker_build.sh clean
    popd
}

if [[ ! -d ../qmk_firmware ]]; then
    echo "This script must be executed from a directory with a ../qmk_firmware relative path"
    echo "Clone the qmk_firmware repo so that this repo and qmk_firmware are siblings."
    echo "For example:"
    echo "~/repos/qmk_firmware"
    echo "~/repos/keyboards"
    echo
    if read -q "clone?Automatically clone qmk_firmware in ../qmk_firmware? [y/N] "; then
        echo
        git clone --recurse-submodules git@github.com:qmk/qmk_firmware.git ../qmk_firmware
    else
        exit 1;
    fi
fi

if (( $# == 0 )); then
    echo "Specify one or more of:"
    echo "augio"
    echo "corne/crkbd"
    echo "planck"
    echo "wheelwriter30"
    echo "clean"
    exit 1;
fi

pushd ../qmk_firmware
make git-submodule
popd

while (( $# > 0 )); do
    case $1 in
        augio)         augio;;
        corne|crkbd)   corne;;
        planck)        planck;;
        wheelwriter30) wheelwriter30;;
        clean)         clean;;
        *) echo "Ignoring unknown keyboard: $1"
    esac
    shift 1
done
