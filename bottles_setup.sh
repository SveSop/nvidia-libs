#!/bin/bash

nvlibs_dir="$(dirname "$(readlink -fm "$0")")"
bottles_dir="$HOME/.var/app/com.usebottles.bottles/data/bottles/bottles"
win='drive_c/windows/system32'
lib='x64'

if [ ! -f "$nvlibs_dir/$lib/nvcuda.dll" ]; then
    echo "Files not found in $nvlibs_dir/$lib" >&2
    exit 1
fi

if [ -z "$1" ]; then
    echo -ne "BOTTLE is not set!\n"
    echo -ne "This is a list of your available bottles:\n"
    echo -ne "\n=========================================\n"
    ls -1 $bottles_dir
    echo -ne "=========================================\n\n"
    echo -ne "Specify your bottle. Eg: ./bottles-install.sh MyBottle\n"
    exit 1
fi

if [ ! -f "$bottles_dir/$1/$win/dxgi.dll" ]; then
    echo -ne "Windows files not found in $bottles_dir\$1! check bottle installation\n" >&2
    exit 1
else
    BOTTLE="$1"
fi

function install {
    cp -f "$nvlibs_dir/$lib/$1" "$bottles_dir/$BOTTLE/$win/"
}

fun=install
$fun nvcuda.dll
$fun nvcuvid.dll
$fun nvencodeapi64.dll
$fun nvoptix.dll
$fun nvofapi64.dll

lib='x32'
if [ -f "$nvlibs_dir/$lib/nvcuda.dll" ]; then
    win='drive_c/windows/syswow64'
    $fun nvcuda.dll
    $fun nvcuvid.dll
    $fun nvencodeapi.dll
fi

echo -ne "All done - NVIDIA libraries copied to $BOTTLE\n"

echo -ne "Do you want to add the experimental version of nvapi to Bottles? (Y/N):\n"
read -n 1 -r response
echo
if [[ "$response" =~ ^[Yy]$ ]]; then
    lib='x64'
    nvapi_ver="dxvk-nvapi-$(cat version | grep DXVK | cut -d' ' -f2- | tr -d '\"')"
    nvapi_dir="$HOME/.var/app/com.usebottles.bottles/data/bottles/nvapi/$nvapi_ver"
    if [ -f "$nvapi_dir/$lib/nvapi64.dll" ]; then
        echo -ne "Already installed! Skipping\n" >&2
    else
        echo -ne "Adding NVAPI to:\n    $nvapi_dir\n\n"
        mkdir -p "$nvapi_dir/$lib"
        cp -f "$nvlibs_dir/$lib/nvapi64.dll" "$nvapi_dir/$lib"
        cp -f "$nvlibs_dir/$lib/nvofapi64.dll" "$nvapi_dir/$lib"
        cp -f "$nvlibs_dir/bin/nvapi64-tests.exe" "$nvapi_dir/$lib"
        cp -f "$nvlibs_dir/bin/nvofapi64-tests.exe" "$nvapi_dir/$lib"
        lib='x32'
        mkdir -p "$nvapi_dir/$lib"
        cp -f "$nvlibs_dir/$lib/nvapi.dll" "$nvapi_dir/$lib"
        echo -ne "To use the custom nvapi version you need to select:\n    $nvapi_ver\nAs your nvapi version in bottles settings!\n\n"
    fi
else
    echo -ne "Skipping experimental version of nvapi\n\n"
fi

echo -ne "Remeber! You need to run this script every time you upgrade the nvidia-libs package\n"
echo -ne "and probably should if you upgrade/change your runner\n"
