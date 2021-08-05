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

if [ -f "$PROTON_LIBS/files/$lib/$arch-unix/nvcuda.dll.so" ]; then
     GE=1
else
     if [ ! -f "$PROTON_LIBS/files/$lib/fakedlls/dxgi.dll" ]; then
        echo -ne "Proton files not found in $PROTON_LIBS! Copy manually or check path.\n" >&2
        exit 1
     fi
fi

function fake_install {
     if [[ ! -v GE ]]; then
        if [ -f "$PROTON_LIBS/files/$lib/fakedlls/$1" ]; then
          chmod +w "$PROTON_LIBS/files/$lib/fakedlls/$1"
        fi
        cp "$nvlibs_dir/lib/wine/$arch-windows/$1" "$PROTON_LIBS/files/$lib/fakedlls/"
        chmod -w,+x "$PROTON_LIBS/files/$lib/fakedlls/$1"
     else
        if [ -f "$PROTON_LIBS/files/$lib/$arch-windows/$1" ]; then
          chmod +w "$PROTON_LIBS/files/$lib/$arch-windows/$1"
        fi
        cp "$nvlibs_dir/lib/wine/$arch-windows/$1" "$PROTON_LIBS/files/$lib/$arch-windows/"
        chmod -w,+x "$PROTON_LIBS/files/$lib/$arch-windows/$1"
     fi
}

function install {
     if [[ ! -v GE ]]; then
        if [ -f "$PROTON_LIBS/files/$lib/$1" ]; then
          chmod +w "$PROTON_LIBS/files/$lib/$1"
        fi
        cp "$nvlibs_dir/lib/wine/$arch-unix/$1" "$PROTON_LIBS/files/$lib/"
        chmod -w,+x "$PROTON_LIBS/files/$lib/$1"
     else
        if [ -f "$PROTON_LIBS/files/$lib/$arch-unix/$1" ]; then
          chmod +w "$PROTON_LIBS/files/$lib/$arch-unix/$1"
        fi
        cp "$nvlibs_dir/lib/wine/$arch-unix/$1" "$PROTON_LIBS/files/$lib/$arch-unix/"
        chmod -w,+x "$PROTON_LIBS/files/$lib/$arch-unix/$1"
     fi
}

function nvapi {
     if [ -f "$PROTON_LIBS/files/$lib/nvapi/$1" ]; then
        chmod +w "$PROTON_LIBS/files/$lib/nvapi/$1"
     fi
     cp "$nvlibs_dir/lib/wine/$arch-windows/$1" "$PROTON_LIBS/files/$lib/nvapi/"
     chmod -w,+x "$PROTON_LIBS/files/$lib/nvapi/$1"
}

fun=fake_install
$fun nvcuda.dll
$fun nvcuvid.dll
$fun nvencodeapi.dll
$fun nvml.dll
if [[ -v GE ]]; then
   $fun nvapi.dll
fi

fun=install
$fun nvcuda.dll.so
$fun nvcuvid.dll.so
$fun nvencodeapi.dll.so
$fun nvml.dll.so

fun=nvapi
$fun nvapi.dll

arch='x86_64'
lib='lib64/wine'
fun=fake_install
$fun nvcuda.dll
$fun nvcuvid.dll
$fun nvencodeapi64.dll
$fun nvml.dll
if [[ -v GE ]]; then
   $fun nvapi64.dll
fi

fun=install
$fun nvcuda.dll.so
$fun nvcuvid.dll.so
$fun nvencodeapi64.dll.so
$fun nvml.dll.so

fun=nvapi
$fun nvapi64.dll

echo -ne "All done - Files dropped in $PROTON_LIBS\n"
exit $ret
