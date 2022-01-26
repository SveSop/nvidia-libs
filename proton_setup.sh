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
elif [ -f "$PROTON_LIBS/files/$lib/fakedlls/dxgi.dll" ]; then
     EXP=1
else
     if [ ! -f "$PROTON_LIBS/dist/$lib/fakedlls/dxgi.dll" ]; then
        echo -ne "Proton files not found in $PROTON_LIBS! Proton not installed or wrong path!\n" >&2
        exit 1
     fi
fi

function fake_install {
     if [[ -v EXP ]]; then
        if [ -f "$PROTON_LIBS/files/$lib/fakedlls/$1" ]; then
          chmod +w "$PROTON_LIBS/files/$lib/fakedlls/$1"
        fi
        cp "$nvlibs_dir/$lib/$arch-windows/$1" "$PROTON_LIBS/files/$lib/fakedlls/"
        chmod -w,+x "$PROTON_LIBS/files/$lib/fakedlls/$1"
        if [ -f "$PROTON_LIBS/files/$lib/$1" ]; then
          chmod +w "$PROTON_LIBS/files/$lib/$1"
          rm "$PROTON_LIBS/files/$lib/$1"
        fi
     elif [[ -v GE ]]; then
        if [ -f "$PROTON_LIBS/files/$lib/$arch-windows/$1" ]; then
          chmod +w "$PROTON_LIBS/files/$lib/$arch-windows/$1"
        fi
        cp "$nvlibs_dir/$lib/$arch-windows/$1" "$PROTON_LIBS/files/$lib/$arch-windows/"
        chmod -w,+x "$PROTON_LIBS/files/$lib/$arch-windows/$1"
     else
        if [ -f "$PROTON_LIBS/dist/$lib/fakedlls/$1" ]; then
          chmod +w "$PROTON_LIBS/dist/$lib/fakedlls/$1"
        fi
        cp "$nvlibs_dir/$lib/$arch-windows/$1" "$PROTON_LIBS/dist/$lib/fakedlls/"
        chmod -w,+x "$PROTON_LIBS/dist/$lib/fakedlls/$1"
        if [ -f "$PROTON_LIBS/dist/$lib/$1" ]; then
          chmod +w "$PROTON_LIBS/dist/$lib/$1"
          rm "$PROTON_LIBS/dist/$lib/$1"
        fi
    fi
}

function install {
     if [[ -v EXP ]]; then
        if [ -f "$PROTON_LIBS/files/$lib/$1" ]; then
          chmod +w "$PROTON_LIBS/files/$lib/$1"
        fi
        cp "$nvlibs_dir/$lib/$arch-unix/$1" "$PROTON_LIBS/files/$lib/"
        chmod -w,+x "$PROTON_LIBS/files/$lib/$1"
     elif [[ -v GE ]]; then
        if [ -f "$PROTON_LIBS/files/$lib/$arch-unix/$1" ]; then
          chmod +w "$PROTON_LIBS/files/$lib/$arch-unix/$1"
        fi
        cp "$nvlibs_dir/$lib/$arch-unix/$1" "$PROTON_LIBS/files/$lib/$arch-unix/"
        chmod -w,+x "$PROTON_LIBS/files/$lib/$arch-unix/$1"
     else
        if [ -f "$PROTON_LIBS/dist/$lib/$1" ]; then
          chmod +w "$PROTON_LIBS/dist/$lib/$1"
        fi
        cp "$nvlibs_dir/$lib/$arch-unix/$1" "$PROTON_LIBS/dist/$lib/"
        chmod -w,+x "$PROTON_LIBS/dist/$lib/$1"
     fi
}

function nvapi {
     if [[ ! -v GE ]] && [[ ! -v EXP ]]; then
        if [ -f "$PROTON_LIBS/dist/$lib/nvapi/$1" ]; then
           chmod +w "$PROTON_LIBS/dist/$lib/nvapi/$1"
        fi
        cp "$nvlibs_dir/$lib/$arch-windows/$1" "$PROTON_LIBS/dist/$lib/nvapi/"
        chmod -w,+x "$PROTON_LIBS/dist/$lib/nvapi/$1"
     else
        if [ -f "$PROTON_LIBS/files/$lib/nvapi/$1" ]; then
           chmod +w "$PROTON_LIBS/files/$lib/nvapi/$1"
        fi
        cp "$nvlibs_dir/$lib/$arch-windows/$1" "$PROTON_LIBS/files/$lib/nvapi/"
        chmod -w,+x "$PROTON_LIBS/files/$lib/nvapi/$1"
     fi
}

function default_pfx {
     if [[ -v GE ]]; then
        if [ "$arch" == "i386" ]; then
           cd "$PROTON_LIBS/files/share/default_pfx/drive_c/windows/syswow64"
           if [ -f "$1" ];
              then rm "$1"
           fi
           ln -s "../../../../../lib/wine/i386-windows/$1" "$1"
        else
           cd "$PROTON_LIBS/files/share/default_pfx/drive_c/windows/system32"
           if [ -f "$1" ]; then
              rm "$1"
           fi
           ln -s "../../../../../lib64/wine/x86_64-windows/$1" "$1"
        fi
     elif [[ -v EXP ]]; then
        if [ "$arch" == "i386" ]; then
           cd "$PROTON_LIBS/files/share/default_pfx/drive_c/windows/syswow64"
           if [ -f "$1" ]; then
              rm "$1"
           fi
           ln -s "../../../../../lib/wine/fakedlls/$1" "$1"
        else
           cd "$PROTON_LIBS/files/share/default_pfx/drive_c/windows/system32"
           if [ -f "$1" ]; then
              rm "$1"
           fi
           ln -s "../../../../../lib64/wine/fakedlls/$1" "$1"
        fi
     else
        if [ "$arch" == "i386" ]; then
           cd "$PROTON_LIBS/dist/share/default_pfx/drive_c/windows/syswow64"
           if [ -f "$1" ]; then
              rm "$1"
           fi
           ln -s "../../../../../lib/wine/fakedlls/$1" "$1"
        else
           cd "$PROTON_LIBS/dist/share/default_pfx/drive_c/windows/system32"
           if [ -f "$1" ]; then
              rm "$1"
           fi
           ln -s "../../../../../lib64/wine/fakedlls/$1" "$1"
        fi
     fi
}

fun=fake_install
$fun nvcuda.dll
$fun nvml.dll
if [[ -v GE ]]; then
   $fun nvapi.dll
fi

fun=install
$fun nvcuda.dll.so
$fun nvml.dll.so

fun=nvapi
$fun nvapi.dll

fun=default_pfx
$fun nvcuda.dll
$fun nvml.dll
if [[ -v GE ]]; then
   $fun nvapi.dll
fi

arch='x86_64'
lib='lib64/wine'
fun=fake_install
$fun nvcuda.dll
$fun nvml.dll
if [[ -v GE ]]; then
   $fun nvapi64.dll
fi

fun=install
$fun nvcuda.dll.so
$fun nvml.dll.so

fun=nvapi
$fun nvapi64.dll

fun=default_pfx
$fun nvcuda.dll
$fun nvml.dll
if [[ -v GE ]]; then
   $fun nvapi64.dll
fi

echo -ne "All done - Files dropped in $PROTON_LIBS\n"
