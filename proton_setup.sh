#!/bin/bash

nvlibs_dir="$(dirname "$(readlink -fm "$0")")"
lib='lib/wine'
arch='i386'

if [ ! -f "$nvlibs_dir/x32/nvcuda.dll" ]; then
    echo "Files not found in $nvlibs_dir" >&2
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

cp -f "$nvlibs_dir/x32/nvcuda.dll" "$PROTON_LIBS/files/$lib/$arch-windows/nvcuda.dll"
cp -f "$nvlibs_dir/x32/nvapi.dll" "$PROTON_LIBS/files/$lib/nvapi"
cp -f "$nvlibs_dir/x32/nvcuvid.dll" "$PROTON_LIBS/files/$lib/$arch-windows/nvcuvid.dll"
cp -f "$nvlibs_dir/x32/nvencodeapi.dll" "$PROTON_LIBS/files/$lib/$arch-windows/nvencodeapi.dll"
cd "$PROTON_LIBS/files/share/default_pfx/drive_c/windows/syswow64"
ln -sf "../../../../../lib/wine/$arch-windows/nvcuvid.dll" "nvcuvid.dll"
ln -sf "../../../../../lib/wine/$arch-windows/nvencodeapi.dll" "nvencodeapi.dll"

arch='x86_64'
lib='lib64/wine'
cd "$nvlibs_dir"

cp -f "$nvlibs_dir/x64/nvcuda.dll" "$PROTON_LIBS/files/$lib/$arch-windows/nvcuda.dll"
cp -f "$nvlibs_dir/x64/nvcuvid.dll" "$PROTON_LIBS/files/$lib/$arch-windows/nvcuvid.dll"
cp -f "$nvlibs_dir/x64/nvencodeapi64.dll" "$PROTON_LIBS/files/$lib/$arch-windows/nvencodeapi64.dll"
cp -f "$nvlibs_dir/x64/nvoptix.dll" "$PROTON_LIBS/files/$lib/$arch-windows/nvoptix.dll"
cp -f "$nvlibs_dir/x64/nvapi64.dll" "$PROTON_LIBS/files/$lib/nvapi"
cp -f "$nvlibs_dir/x64/nvofapi64.dll" "$PROTON_LIBS/files/$lib/nvapi"

cd "$PROTON_LIBS/files/share/default_pfx/drive_c/windows/system32"
ln -sf "../../../../../lib64/wine/$arch-windows/nvcuvid.dll" "nvcuvid.dll"
ln -sf "../../../../../lib64/wine/$arch-windows/nvencodeapi64.dll" "nvencodeapi64.dll"
ln -sf "../../../../../lib64/wine/$arch-windows/nvoptix.dll" "nvoptix.dll"

echo -n "Do you want to install 64-bit NVML files to proton? (This can break games like Portal RTX!) (Y/N): "
read -n 1 -r response
echo
if [[ "$response" =~ ^[Yy]$ ]]; then
    echo -ne "Copying 64-bit NVML files..."
    cp -f "$nvlibs_dir/x64/wine/$arch-unix/nvml.so" "$PROTON_LIBS/files/$lib/$arch-unix"
    cp -f "$nvlibs_dir/x64/wine/$arch-windows/nvml.dll" "$PROTON_LIBS/files/$lib/$arch-windows"
    ln -sf "../../../../../lib64/wine/$arch-windows/nvml.dll" "nvml.dll"
    echo -ne "NVML Copied successfully\n"
    echo -ne "Do you want to install 32-bit NVML libraries? (Y/N): "
    read -n 1 -r response
    echo
    if [[ "$response" =~ ^[Yy]$ ]]; then
        echo -ne "Copying 32-bit NVML files..."
        arch='i386'
        lib='lib/wine'
        cd "$PROTON_LIBS/files/share/default_pfx/drive_c/windows/syswow64"
        cp -f "$nvlibs_dir/x32/wine/$arch-unix/nvml.so" "$PROTON_LIBS/files/$lib/$arch-unix"
        cp -f "$nvlibs_dir/x32/wine/$arch-windows/nvml.dll" "$PROTON_LIBS/files/$lib/$arch-windows"
        ln -sf "../../../../../lib/wine/$arch-windows/nvml.dll" "nvml.dll"
        echo -ne "NVML Copied successfully\n"
    else
        echo -ne "Skipping 32-bit NVML files\n"
    fi
else
    echo -ne "Skipping NVML files\n"
fi

cd "$nvlibs_dir"
echo -ne "All done - Files dropped in $PROTON_LIBS\n"
