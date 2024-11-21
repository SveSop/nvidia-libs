#!/bin/bash

nvlibs_dir="$(dirname "$(readlink -fm "$0")")"
arch='x86_64'
lib='lib64/wine'

if [ ! -f "$nvlibs_dir/x64/wine/$arch-unix/nvml.so" ]; then
    echo "Files not found in $nvlibs_dir/x64/wine/$arch-unix" >&2
    exit 1
fi

if [ -z "$WINE_BIN" ]; then
    echo -ne "WINE_BIN is not set!\n"
    echo -ne "Example: WINE_BIN='/home/user/winebinaries/wine-staging/'\n"
    echo -ne "OBS. Installing to system wine install is not recommended.\n"
    echo -ne "Better use custom wine binary.\n"
    exit 1
fi

if [ ! -f "$WINE_BIN/$lib/$arch-windows/dxgi.dll" ]; then
    echo -ne "Wine binaries not found in $WINE_BIN! Wine not installed or wrong path!\n" >&2
    exit 1
fi

function win_install {
    cp -f "$nvlibs_dir/x64/wine/$arch-windows/$1" "$WINE_BIN/$lib/$arch-windows/"
}

function install {
    cp -f "$nvlibs_dir/x64/wine/$arch-unix/$1" "$WINE_BIN/$lib/$arch-unix/"
}

fun=win_install
$fun nvml.dll

fun=install
$fun nvml.so

echo -ne "All done - NVML copied to $WINE_BIN\n"
echo -ne "You need to run wineboot -u with a wineprefix to use nvml!\n"
