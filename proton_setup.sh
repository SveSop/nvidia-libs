#!/bin/bash

nvlibs_dir="$(dirname "$(readlink -fm "$0")")"
lib='lib/wine'
arch='i386'

if [ ! -f "$nvlibs_dir/$lib/$arch-unix/nvcuda.dll.so" ]; then
    echo "Files not found in $nvlibs_dir/$lib/$arch-unix" >&2
    exit 1
fi

if [ -z "$PROTON_LIBS" ]; then
    echo -ne "PROTON_LIBS is not set!\n"
    echo -ne "Example: PROTON_LIBS='$HOME/.steam/steam/steamapps/common/Proton - Experimental'\n"
    exit 1
fi

if [ ! -f "$PROTON_LIBS/files/$lib/$arch-windows/dxgi.dll" ]; then
    echo -ne "Proton files not found in $PROTON_LIBS! Proton not installed or wrong path!\n" >&2
    exit 1
fi

function fake_install {
    cp -f "$nvlibs_dir/$lib/$arch-windows/$1" "$PROTON_LIBS/files/$lib/$arch-windows/"
    chmod -w,+x "$PROTON_LIBS/files/$lib/$arch-windows/$1"
}

function install {
    cp -f "$nvlibs_dir/$lib/$arch-unix/$1" "$PROTON_LIBS/files/$lib/$arch-unix/"
    chmod -w,+x "$PROTON_LIBS/files/$lib/$arch-unix/$1"
}

function nvapi {
     cp -f "$nvlibs_dir/$lib/$arch-windows/$1" "$PROTON_LIBS/files/$lib/nvapi/"
     chmod -w,+x "$PROTON_LIBS/files/$lib/nvapi/$1"
}

function default_pfx {
     if [ "$arch" == "i386" ]; then
         cd "$PROTON_LIBS/files/share/default_pfx/drive_c/windows/syswow64"
         ln -sf "../../../../../lib/wine/$arch-windows/$1" "$1"
     else
         cd "$PROTON_LIBS/files/share/default_pfx/drive_c/windows/system32"
         ln -sf "../../../../../lib64/wine/$arch-windows/$1" "$1"
     fi
}

fun=fake_install
$fun nvcuda.dll
$fun nvml.dll

fun=install
$fun nvcuda.dll.so
$fun nvml.so

fun=nvapi
$fun nvapi.dll

fun=default_pfx
$fun nvcuda.dll
$fun nvml.dll

arch='x86_64'
lib='lib64/wine'
fun=fake_install
$fun nvcuda.dll
$fun nvml.dll
$fun nvoptix.dll

fun=install
$fun nvcuda.dll.so
$fun nvml.so
$fun nvoptix.dll.so

fun=nvapi
$fun nvapi64.dll

fun=default_pfx
$fun nvcuda.dll
$fun nvml.dll
$fun nvoptix.dll

echo -ne "All done - Files dropped in $PROTON_LIBS\n"
