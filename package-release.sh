#!/bin/bash

set -e

shopt -s extglob

if [ -z "$1" ] || [ -z "$2" ]; then
  echo "Usage: $0 release destdir"
  exit 1
fi

git submodule update --init --recursive

VERSION="$1"
NVLIBS_SRC_DIR=$(dirname "$(readlink -f "$0")")
NVLIBS_BUILD_DIR=$(realpath "$2")"/nvidia-libs-$VERSION"

if [ -e "$NVLIBS_BUILD_DIR" ]; then
  echo "Build directory $NVLIBS_BUILD_DIR already exists"
  exit 1
fi

# build nvcuda

function build_arch {
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

# Build wine-nvoptix

NVOPTIX_SRC_DIR=$NVLIBS_SRC_DIR"/wine-nvoptix"
cd $NVOPTIX_SRC_DIR

meson --cross-file "$NVOPTIX_SRC_DIR/build-wine64.txt"  \
      --buildtype release                               \
      --prefix "$NVLIBS_BUILD_DIR"                      \
      --libdir lib64                                    \
      --strip                                           \
      "$NVLIBS_BUILD_DIR/build"

cd "$NVLIBS_BUILD_DIR/build"
ninja install

rm -R "$NVLIBS_BUILD_DIR/build"
rm -R "$NVLIBS_BUILD_DIR/defs"

# Build wine-nvml

NVML_SRC_DIR=$NVLIBS_SRC_DIR"/wine-nvml"
cd $NVML_SRC_DIR"/src"
./make_nvml

function build_arch {
  cd $NVML_SRC_DIR
  meson --cross-file "$NVML_SRC_DIR/cross-mingw$1.txt"  \
        --buildtype release                             \
        --prefix "$NVLIBS_BUILD_DIR"                    \
        --libdir lib$1                                  \
        --strip                                         \
        "$NVLIBS_BUILD_DIR/build.mingw$1"

  cd "$NVLIBS_BUILD_DIR/build.mingw$1"
  ninja install

  cd $NVML_SRC_DIR
  meson --cross-file "$NVML_SRC_DIR/cross-wine$1.txt"  \
        --buildtype release                            \
        --prefix "$NVLIBS_BUILD_DIR"                   \
        --libdir lib$1                                 \
        --strip                                        \
        "$NVLIBS_BUILD_DIR/build.wine$1"

  cd "$NVLIBS_BUILD_DIR/build.wine$1"
  ninja install

  rm -R "$NVLIBS_BUILD_DIR/build.mingw$1"
  rm -R "$NVLIBS_BUILD_DIR/build.wine$1"
}

build_arch 64

# Build dxvk-nvapi

NVAPI_SRC_DIR=$NVLIBS_SRC_DIR"/dxvk-nvapi"

crossfile="build-win"

cd $NVAPI_SRC_DIR

function prepare {
  python3 validate-methods.py     \
    src/nvapi.cpp                 \
    src/nvapi_sys.cpp             \
    src/nvapi_disp.cpp            \
    src/nvapi_mosaic.cpp          \
    src/nvapi_drs.cpp             \
    src/nvapi_gpu.cpp             \
    src/nvapi_d3d.cpp             \
    src/nvapi_d3d11.cpp           \
    src/nvapi_d3d12.cpp           \
    src/nvapi_interface.cpp       \
    src/nvapi_interface_private.h \
    external/nvapi/nvapi_interface.h

  # remove existing version.h, because otherwise the existing one gets into the build instead of the generated one
  if [ -e version.h ]; then
    rm version.h
  fi
}

function build_arch {
  cd "$NVAPI_SRC_DIR"

  meson --cross-file "$NVAPI_SRC_DIR/$crossfile$1.txt" \
        --buildtype release                            \
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

# Copy installscripts
cp $NVLIBS_SRC_DIR/*.sh "$NVLIBS_BUILD_DIR/"
chmod +x $NVLIBS_BUILD_DIR/*.sh
cp "$NVLIBS_SRC_DIR/Readme_nvml.txt" "$NVLIBS_BUILD_DIR/Readme_nvml.txt"

# cleanup
cd $NVLIBS_BUILD_DIR
find . -name \*.a -type f -delete
mv lib32 lib
echo "Done building!"
