#!/bin/bash

nvlibs_dir="$(dirname "$(readlink -fm "$0")")"
lib='lib/wine'
arch='i386'

if [ ! -f "$nvlibs_dir/x64/nvcuda.dll" ]; then
    echo "Files not found in $nvlibs_dir" >&2
    exit 1
fi

if [ -z "$PROTON_LIBS" ]; then
    echo -ne "PROTON_LIBS is not set!\n"
    echo -ne "Example: PROTON_LIBS='$HOME/.steam/steam/steamapps/common/Proton - Experimental'\n"
    exit 1
else
    PROTON_LIBS="$(readlink -fm "$PROTON_LIBS")"
fi

if [ ! -f "$PROTON_LIBS/files/$lib/$arch-windows/dxgi.dll" ]; then
    echo -ne "Proton files not found in $PROTON_LIBS! Proton not installed or wrong path!\n" >&2
    exit 1
fi

# proton 10/Experimental support
if [ -d "$PROTON_LIBS/files/$lib/nvapi/$arch-windows" ]; then
    cp -f "$nvlibs_dir/x32/nvapi.dll" "$PROTON_LIBS/files/$lib/nvapi/$arch-windows"
else
    cp -f "$nvlibs_dir/x32/nvapi.dll" "$PROTON_LIBS/files/$lib/nvapi"
fi

arch='x86_64'

# proton 10/Experimental support
if [ -d "$PROTON_LIBS/files/lib64/wine" ]; then
    lib='lib64/wine'
elif [ -d "$PROTON_LIBS/files/lib/wine" ]; then
    lib='lib/wine'
else
    echo -ne "Proton files not found in $PROTON_LIBS! Proton not installed or wrong path!\n" >&2
    exit 1
fi

if [ -d "$PROTON_LIBS/files/$lib/nvapi/$arch-windows" ]; then

    cp -f "$nvlibs_dir/x64/nvapi64.dll" "$PROTON_LIBS/files/$lib/nvapi/$arch-windows"
    cp -f "$nvlibs_dir/x64/nvofapi64.dll" "$PROTON_LIBS/files/$lib/nvapi/$arch-windows"
else
    cp -f "$nvlibs_dir/x64/nvapi64.dll" "$PROTON_LIBS/files/$lib/nvapi"
    cp -f "$nvlibs_dir/x64/nvofapi64.dll" "$PROTON_LIBS/files/$lib/nvapi"
fi
cp -f "$nvlibs_dir/x64/nvcuda.dll" "$PROTON_LIBS/files/$lib/$arch-windows/nvcuda.dll"
cp -f "$nvlibs_dir/x64/nvcuvid.dll" "$PROTON_LIBS/files/$lib/$arch-windows/nvcuvid.dll"
cp -f "$nvlibs_dir/x64/nvencodeapi64.dll" "$PROTON_LIBS/files/$lib/$arch-windows/nvencodeapi64.dll"
cp -f "$nvlibs_dir/x64/nvoptix.dll" "$PROTON_LIBS/files/$lib/$arch-windows/nvoptix.dll"

ln -sfr "$PROTON_LIBS/files/$lib/$arch-windows/nvcuvid.dll" "$PROTON_LIBS/files/share/default_pfx/drive_c/windows/system32/nvcuvid.dll"
ln -sfr "$PROTON_LIBS/files/$lib/$arch-windows/nvencodeapi64.dll" "$PROTON_LIBS/files/share/default_pfx/drive_c/windows/system32/nvencodeapi64.dll"
ln -sfr "$PROTON_LIBS/files/$lib/$arch-windows/nvoptix.dll" "$PROTON_LIBS/files/share/default_pfx/drive_c/windows/system32/nvoptix.dll"

echo -n "Do you want to install 64-bit NVML files to proton? (This can break games like Portal RTX!) (Y/N): "
read -n 1 -r response
echo
if [[ "$response" =~ ^[Yy]$ ]]; then
    echo -ne "Copying 64-bit NVML files..."
    cp -f "$nvlibs_dir/x64/wine/$arch-unix/nvml.so" "$PROTON_LIBS/files/$lib/$arch-unix"
    cp -f "$nvlibs_dir/x64/wine/$arch-windows/nvml.dll" "$PROTON_LIBS/files/$lib/$arch-windows"
    ln -sfr "$PROTON_LIBS/files/$lib/$arch-windows/nvml.dll" "$PROTON_LIBS/files/share/default_pfx/drive_c/windows/system32/nvml.dll"
    echo -ne "NVML Copied successfully\n"
else
    echo -ne "Skipping NVML files\n"
fi

echo -ne "All done - Files dropped in $PROTON_LIBS\n"
