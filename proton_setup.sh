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

cp -f "$nvlibs_dir/$lib/$arch-unix/nvcuda.dll.so" "$PROTON_LIBS/files/$lib/$arch-windows/nvcuda.dll"
cp -f "$nvlibs_dir/$lib/$arch-windows/nvapi.dll" "$PROTON_LIBS/files/$lib/nvapi"

arch='x86_64'
lib='lib64/wine'

cp -f "$nvlibs_dir/$lib/$arch-unix/nvcuda.dll.so" "$PROTON_LIBS/files/$lib/$arch-windows/nvcuda.dll"
cp -f "$nvlibs_dir/$lib/$arch-unix/nvoptix.dll.so" "$PROTON_LIBS/files/$lib/$arch-windows/nvoptix.dll"
cp -f "$nvlibs_dir/$lib/$arch-unix/nvml.so" "$PROTON_LIBS/files/$lib/$arch-unix"
cp -f "$nvlibs_dir/$lib/$arch-windows/nvml.dll" "$PROTON_LIBS/files/$lib/$arch-windows"
cp -f "$nvlibs_dir/$lib/$arch-windows/nvapi64.dll" "$PROTON_LIBS/files/$lib/nvapi"
cd "$PROTON_LIBS/files/share/default_pfx/drive_c/windows/system32"
ln -sf "../../../../../lib64/wine/$arch-windows/nvml.dll" "nvml.dll"
ln -sf "../../../../../lib64/wine/$arch-windows/nvoptix.dll" "nvoptix.dll"
cd "$nvlibs_dir"

echo -ne "All done - Files dropped in $PROTON_LIBS\n"
