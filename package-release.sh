#!/bin/bash

set -e

shopt -s extglob

if [ -z "$1" ]; then
  echo "Usage: package-release.sh destdir"
  exit 1
fi

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
        --libdir lib                                     \
	--strip                                          \
        "$NVLIBS_BUILD_DIR/build.$1"

  cd "$NVLIBS_BUILD_DIR/build.$1"
  ninja install

  rm -R "$NVLIBS_BUILD_DIR/build.$1"
}

build_arch 64
build_arch 32

NVAPI_SRC_DIR=$NVLIBS_SRC_DIR"/dxvk-nvapi"

crossfile="build-win"

cd $NVAPI_SRC_DIR

function prepare {
  python validate-methods.py \
    src/nvapi.cpp \
    src/nvapi_sys.cpp \
    src/nvapi_disp.cpp \
    src/nvapi_mosaic.cpp \
    src/nvapi_gpu.cpp \
    src/nvapi_d3d.cpp \
    src/nvapi_d3d11.cpp \
    src/nvapi_d3d12.cpp \
    src/nvapi_interface.cpp

  # remove existing version.h, because otherwise the existing one gets into the build instead of the generated one
  if [ -e version.h ]; then
    rm version.h
  fi
}

function build_arch {
  cd "$NVAPI_SRC_DIR"

  meson --cross-file "$NVAPI_SRC_DIR/$crossfile$1.txt" \
        --buildtype "release"                    \
        --prefix "$NVLIBS_BUILD_DIR"             \
        --strip                                  \
        --libdir lib                             \
        "$NVLIBS_BUILD_DIR/build.$1"

  cd "$NVLIBS_BUILD_DIR/build.$1"
  ninja install

  cp version.h "$NVAPI_SRC_DIR"
  rm -R "$NVLIBS_BUILD_DIR/build.$1"

}

prepare
build_arch 64
build_arch 32

# cleanup
cd $NVLIBS_BUILD_DIR
find . -name \*.a -type f -delete
