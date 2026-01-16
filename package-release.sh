#!/bin/bash

set -e

shopt -s extglob

if [ $# -lt 2 ]; then
  echo "Usage: $0 releasename destdir [--fakedll]"
  exit 1
fi

git submodule update --init --recursive

VERSION="$1"
DESTDIR="$2"
NVLIBS_SRC_DIR=$(dirname "$(readlink -f "$0")")
NVLIBS_BUILD_DIR=$(realpath "$2")"/nvidia-libs-$VERSION"
shift 2

FAKEDLL=""
LIBDIR='x64'

for arg in "$@"; do
  case "$arg" in
    --fakedll)
      FAKEDLL="-Dfakedll=true"
      LIBDIR='lib'
      ;;
    *)
      echo "Error: unknown option '$arg'"
      exit 1
      ;;
  esac
done

if [ -e "$NVLIBS_BUILD_DIR" ]; then
  echo "Build directory $NVLIBS_BUILD_DIR already exists"
  exit 1
fi

# Make version file

meson --prefix "$NVLIBS_BUILD_DIR" \
      --strip                      \
      "$NVLIBS_BUILD_DIR/build"

cd "$NVLIBS_BUILD_DIR/build"
ninja

cp "$NVLIBS_BUILD_DIR/build/version" "$NVLIBS_BUILD_DIR/version"
rm -R "$NVLIBS_BUILD_DIR/build"

# Build NVCUDA

NVCUDA_SRC_DIR=$NVLIBS_SRC_DIR"/nvcuda"

cd "$NVCUDA_SRC_DIR"

meson setup                                          \
    --cross-file "$NVCUDA_SRC_DIR/build-wine64.txt"  \
    --buildtype release                              \
    --prefix "$NVLIBS_BUILD_DIR"                     \
    --libdir $LIBDIR                                 \
    --strip                                          \
    $FAKEDLL                                         \
    "$NVLIBS_BUILD_DIR/build.64"

cd "$NVLIBS_BUILD_DIR/build.64"
ninja install

rm -R "$NVLIBS_BUILD_DIR/build.64"

# Build cuda tests executable

export WINEARCH="win64"

cd "$NVCUDA_SRC_DIR"
meson setup                                              \
    --cross-file "$NVCUDA_SRC_DIR/tests/build-win64.txt" \
    --buildtype release                                  \
    --prefix "$NVLIBS_BUILD_DIR"                         \
    --libdir bin                                         \
    --strip                                              \
    "$NVLIBS_BUILD_DIR/build.tests"                      \

cd "$NVLIBS_BUILD_DIR/build.tests"
ninja install

rm -R "$NVLIBS_BUILD_DIR/build.tests"

# Build NVENC

NVENC_SRC_DIR=$NVLIBS_SRC_DIR"/nvenc"

cd "$NVENC_SRC_DIR"

meson setup                                         \
    --cross-file "$NVENC_SRC_DIR/build-wine64.txt"  \
    --buildtype release                             \
    --prefix "$NVLIBS_BUILD_DIR"                    \
    --libdir $LIBDIR                                \
    --strip                                         \
    $FAKEDLL                                        \
    "$NVLIBS_BUILD_DIR/build.64"

cd "$NVLIBS_BUILD_DIR/build.64"
ninja install

rm -R "$NVLIBS_BUILD_DIR/build.64"

# Build wine-nvoptix

NVOPTIX_SRC_DIR=$NVLIBS_SRC_DIR"/wine-nvoptix"
cd $NVOPTIX_SRC_DIR

meson setup                                           \
    --cross-file "$NVOPTIX_SRC_DIR/build-wine64.txt"  \
    --buildtype release                               \
    --prefix "$NVLIBS_BUILD_DIR"                      \
    --libdir $LIBDIR                                  \
    --strip                                           \
    $FAKEDLL                                          \
    "$NVLIBS_BUILD_DIR/build"

cd "$NVLIBS_BUILD_DIR/build"
ninja install

rm -R "$NVLIBS_BUILD_DIR/build"

# Build wine-nvml

NVML_SRC_DIR=$NVLIBS_SRC_DIR"/wine-nvml"
cd $NVML_SRC_DIR"/src"
./make_nvml

cd $NVML_SRC_DIR
meson setup                                         \
    --cross-file "$NVML_SRC_DIR/cross-mingw64.txt"  \
    --buildtype release                             \
    --prefix "$NVLIBS_BUILD_DIR"                    \
    --libdir $LIBDIR                                \
    --strip                                         \
    "$NVLIBS_BUILD_DIR/build.mingw64"

cd "$NVLIBS_BUILD_DIR/build.mingw64"
ninja install

cd $NVML_SRC_DIR
meson setup                                        \
    --cross-file "$NVML_SRC_DIR/cross-wine64.txt"  \
    --buildtype release                            \
    --prefix "$NVLIBS_BUILD_DIR"                   \
    --libdir $LIBDIR                               \
    --strip                                        \
    "$NVLIBS_BUILD_DIR/build.wine64"

cd "$NVLIBS_BUILD_DIR/build.wine64"
ninja install

rm -R "$NVLIBS_BUILD_DIR/build.mingw64"
rm -R "$NVLIBS_BUILD_DIR/build.wine64"

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
    src/nvapi_ngx.cpp             \
    src/nvapi_drs.cpp             \
    src/nvapi_gpu.cpp             \
    src/nvapi_d3d.cpp             \
    src/nvapi_d3d11.cpp           \
    src/nvapi_d3d12.cpp           \
    src/nvapi_vulkan.cpp          \
    src/nvapi_interface.cpp       \
    src/nvapi_interface_private.h \
    external/nvapi/nvapi_interface.h
}

function build_arch {
  cd "$NVAPI_SRC_DIR"

  if [ -z "$FAKEDLL" ]; then
    DIRS="x$1"
  else
    DIRS="$LIBDIR"
  fi

  # remove generated files, because otherwise the existing
  # files get into the build instead of the generated ones
  rm -f version.h config.h

  meson setup                                          \
        --cross-file "$NVAPI_SRC_DIR/$crossfile$1.txt" \
        --buildtype release                            \
        --prefix "$NVLIBS_BUILD_DIR"                   \
        --strip                                        \
        --bindir $DIRS                                 \
        --libdir $DIRS                                 \
        -Denable_tests=true                            \
        "$NVLIBS_BUILD_DIR/build.$1"

  cd "$NVLIBS_BUILD_DIR/build.$1"
  ninja install

  cp version.h "$NVAPI_SRC_DIR"
  cp config.h "$NVAPI_SRC_DIR"
  rm -R "$NVLIBS_BUILD_DIR/build.$1"
}

prepare
build_arch 64
build_arch 32

# Save the DXVK-NVAPI version to nvidia libs versionfile
cat "$NVAPI_SRC_DIR"/version.h | grep DXVK | cut -d' ' -f2- >> "$NVLIBS_BUILD_DIR"/version

# Build Vulkan reflex layer
cd "$NVAPI_SRC_DIR"
rm -f "$NVAPI_SRC_DIR"/layer/{version,config}.h

meson setup                            \
  --buildtype "release"                \
  --prefix "$NVLIBS_BUILD_DIR/layer"   \
  --libdir ''                          \
  --strip                              \
  -Dabsolute_library_path=false        \
  -Dlibrary_path_prefix=./             \
  -Dmanifest_install_dir=.             \
  "$NVLIBS_BUILD_DIR/build.layer"      \
  "$NVAPI_SRC_DIR/layer"

cd "$NVLIBS_BUILD_DIR/build.layer"
ninja install

rm -R "$NVLIBS_BUILD_DIR/build.layer"

# Copy installscripts and README
if [ -z "$FAKEDLL" ]; then
  cp $NVLIBS_SRC_DIR/*.sh "$NVLIBS_BUILD_DIR/"
  rm $NVLIBS_BUILD_DIR/package-release.sh
  chmod +x $NVLIBS_BUILD_DIR/*.sh
  cp "$NVLIBS_SRC_DIR/Readme_nvml.txt" "$NVLIBS_BUILD_DIR/Readme_nvml.txt"
fi
cp "$NVLIBS_SRC_DIR/README.md" "$NVLIBS_BUILD_DIR/README.md"

# Move test
mkdir -p "$NVLIBS_BUILD_DIR/bin"
mv "$NVLIBS_BUILD_DIR/$LIBDIR/nvapi64-tests.exe" "$NVLIBS_BUILD_DIR/bin/"
mv "$NVLIBS_BUILD_DIR/$LIBDIR/nvofapi64-tests.exe" "$NVLIBS_BUILD_DIR/bin/"

# cleanup
cd $NVLIBS_BUILD_DIR
find . -name \*.a -type f -delete
if [ -z "$FAKEDLL" ]; then
  find . -name "*.dll.so" -type f -exec bash -c 'mv "$0" "${0%.so}"' {} \;
else
  # Hack the dxvk-nvapi dll's so that they look like wine builtin libraries
  winebuild --builtin "$NVLIBS_BUILD_DIR/$LIBDIR/nvapi64.dll"
  winebuild --builtin "$NVLIBS_BUILD_DIR/$LIBDIR/nvapi.dll"
  winebuild --builtin "$NVLIBS_BUILD_DIR/$LIBDIR/nvofapi64.dll"
  mkdir -p "$NVLIBS_BUILD_DIR/$LIBDIR/wine/i386-windows"
  mv "$NVLIBS_BUILD_DIR/$LIBDIR/nvapi.dll" "$NVLIBS_BUILD_DIR/$LIBDIR/wine/i386-windows"
  mv "$NVLIBS_BUILD_DIR/$LIBDIR/"*.dll "$NVLIBS_BUILD_DIR/$LIBDIR/wine/x86_64-windows"
fi
echo "Done building!"
