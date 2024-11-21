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

win='drive_c/windows/syswow64'
lib='x32'

$fun nvcuda.dll
$fun nvcuvid.dll
$fun nvencodeapi.dll

echo -ne "All done - NVIDIA libraries copied to $BOTTLE\n"
echo -ne "Remeber! You need to run this script every time you upgrade the nvidia-libs package\n"
echo -ne "and probably should if you upgrade/change your runner\n"
