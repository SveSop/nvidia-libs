#!/bin/bash

set -e

shopt -s extglob

if [ -z "$1" ]; then
  echo "Usage: package-release.sh destdir"
  exit 1
fi

git submodule update --init --recursive

NVLIBS_SRC_DIR=`dirname $(readlink -f $0)`
NVLIBS_BUILD_DIR=$(realpath "$1")"/nvidia-libs"

if [ -e "$NVLIBS_BUILD_DIR" ]; then
  echo "Build directory $NVLIBS_BUILD_DIR already exists"
  exit 1
fi

function build_arch {
  export WINEARCH="win$1"

  cd "$NVLIBS_SRC_DIR"

  meson --cross-file "$NVLIBS_SRC_DIR/build-wine$1.txt"  \
        --buildtype release                              \
        --prefix "$NVLIBS_BUILD_DIR"                     \
        --libdir lib$1                                   \
	--strip                                          \
        "$NVLIBS_BUILD_DIR/build.$1"

  cd "$NVLIBS_BUILD_DIR/build.$1"
  ninja install

  cp "$NVLIBS_BUILD_DIR/build.$1/version" "$NVLIBS_BUILD_DIR/version"
  rm -R "$NVLIBS_BUILD_DIR/build.$1"
}

build_arch 64
build_arch 32

NVAPI_SRC_DIR=$NVLIBS_SRC_DIR"/dxvk-nvapi"

crossfile="build-win"

cd $NVAPI_SRC_DIR

function prepare {
  python3 validate-methods.py \
    src/nvapi.cpp \
    src/nvapi_sys.cpp \
    src/nvapi_disp.cpp \
    src/nvapi_mosaic.cpp \
    src/nvapi_drs.cpp \
    src/nvapi_gpu.cpp \
    src/nvapi_d3d.cpp \
    src/nvapi_d3d11.cpp \
    src/nvapi_d3d12.cpp \
    src/nvapi_interface.cpp \
    inc/nvapi_interface.h

  # remove existing version.h, because otherwise the existing one gets into the build instead of the generated one
  if [ -e version.h ]; then
    rm version.h
  fi
}

function build_arch {
  cd "$NVAPI_SRC_DIR"

  meson --cross-file "$NVAPI_SRC_DIR/$crossfile$1.txt" \
        --buildtype "release"                          \
        --prefix "$NVLIBS_BUILD_DIR"                   \
        --strip                                        \
        --libdir lib$1                                 \
        -Denable_tests=true                            \
        "$NVLIBS_BUILD_DIR/build.$1"

  cd "$NVLIBS_BUILD_DIR/build.$1"
  ninja install

  cp version.h "$NVAPI_SRC_DIR"
  rm -R "$NVLIBS_BUILD_DIR/build.$1"

}

prepare
build_arch 64
build_arch 32

# Copy installscript
cp "$NVLIBS_SRC_DIR/setup_nvlibs.sh" "$NVLIBS_BUILD_DIR/setup_nvlibs.sh"
chmod +x "$NVLIBS_BUILD_DIR/setup_nvlibs.sh"
cp "$NVLIBS_SRC_DIR/proton_setup.sh" "$NVLIBS_BUILD_DIR/proton_setup.sh"
chmod +x "$NVLIBS_BUILD_DIR/proton_setup.sh"

# cleanup
cd $NVLIBS_BUILD_DIR
find . -name \*.a -type f -delete
mv lib32 lib
echo "Done building!"
