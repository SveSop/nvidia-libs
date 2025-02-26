#!/bin/bash

nvlibs_dir="$(dirname "$(readlink -fm "$0")")"
arch='x86_64'
bits='x64'

if [ ! -f "$nvlibs_dir/$bits/wine/$arch-unix/nvml.so" ]; then
    echo "Files not found in $nvlibs_dir/$bits/wine/$arch-unix" >&2
    exit 1
fi

if [ -z "$WINE_BIN" ]; then
    echo -ne "WINE_BIN is not set!\n"
    echo -ne "Example: WINE_BIN='/home/user/winebinaries/wine-staging/'\n"
    echo -ne "OBS. Installing to system wine install is not recommended.\n"
    echo -ne "Better use custom wine binary.\n"
    exit 1
fi

if [[ -d "$WINE_BIN/lib/wine/$arch-windows" ]]; then
    lib="lib/wine"
elif [[ -d "$WINE_BIN/lib64/wine/$arch-windows" ]]; then
    lib="lib64/wine"
fi

if [ ! -f "$WINE_BIN/$lib/$arch-windows/dxgi.dll" ]; then
    echo -ne "Wine binaries not found in $WINE_BIN! Wine not installed or wrong path!\n" >&2
    exit 1
fi

function win_install {
    cp -f "$nvlibs_dir/$bits/wine/$arch-windows/$1" "$WINE_BIN/$lib/$arch-windows/"
}

function install {
    cp -f "$nvlibs_dir/$bits/wine/$arch-unix/$1" "$WINE_BIN/$lib/$arch-unix/"
}

win_install nvml.dll
install nvml.so

echo -ne "Do you want to install 32-bit NVML libraries? (Y/N): "
read -n 1 -r response
echo
if [[ "$response" =~ ^[Yy]$ ]]; then
    echo -ne "Copying 32-bit files..."
    arch='i386'
    lib="lib/wine"
    if ! [[ -d "$WINE_BIN/$lib/$arch-windows" ]]; then
        echo -ne "Cant find 32-bit libraries! Exiting\n"
        exit 1
    fi
    bits='x32'
    lib='lib/wine'
    win_install nvml.dll
    install nvml.so
    echo -ne "32-bit NVML copied successfully\n"
else
    echo -ne "Skipping 32-bit NVML libraries\n"
fi

echo -ne "All done - NVML copied to $WINE_BIN\n"
echo -ne "You need to run wineboot -u with a wineprefix to use nvml!\n"
