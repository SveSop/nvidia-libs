#!/bin/bash

nvlibs_dir="$(dirname "$(readlink -fm "$0")")"
wine="wine"
lib='x32'

if [ ! -f "$nvlibs_dir/$lib/nvcuda.dll" ]; then
    echo "Files not found in $nvlibs_dir/$lib" >&2
    exit 1
fi

winever=$($wine --version | grep wine)
if [ -z "$winever" ]; then
    echo "$wine:  Not a wine executable. Check your $wine." >&2
    exit 1
fi

if [ -z "$WINEPREFIX" ]; then
    echo -ne "WINEPREFIX is not set! This may create a wineprefix in the default distro folder)\nContinue? (Y/N)\n"
    old_stty_cfg=$(stty -g)
    stty raw -echo ; answer=$(head -c 1) ; stty $old_stty_cfg
    if echo "$answer" |grep -iq "^y" ;then
        wineboot -u
    else
        exit 1
    fi
else
    if ! [ -f "$WINEPREFIX/system.reg" ]; then
        echo -ne "WINEPREFIX does not point to an existing wine installation.\nProceeding will create a new one in $WINEPREFIX\nContinue? (Y/N)\n"
        old_stty_cfg=$(stty -g)
        stty raw -echo ; answer=$(head -c 1) ; stty $old_stty_cfg
        if echo "$answer" |grep -iq "^y" ;then
            wineboot -u
        else
            exit 1
        fi
    fi
fi

unix_sys_path=$($wine winepath -u 'C:\windows\system32' 2> /dev/null)

if [ -z "$unix_sys_path" ]; then
  echo 'Failed to resolve C:\windows\system32.' >&2
  exit 1
fi

function removeOverride {
    echo "    Removing override... "
    $wine reg delete 'HKEY_CURRENT_USER\Software\Wine\DllOverrides' /v "$1" /f > /dev/null 2>&1
    if [ $? -ne 0 ]; then
        echo "    Override does not exist for $1, trying next..."
        exit=2
    fi
    local dll="$unix_sys_path/$1.dll"
    echo "    Removing symlink... "
    if [ -h "$dll" ]; then
        out=$(rm "$dll" 2>&1)
        if [ $? -ne 0 ]; then
            echo -e "$out"
            exit=2
        fi
    else
        echo -e "'$dll' is not a link or doesn't exist."
        exit=2
    fi
}

function createOverride {
    echo "    Creating DLL override... "
    $wine reg add 'HKEY_CURRENT_USER\Software\Wine\DllOverrides' /v "$1" /d native /f >/dev/null 2>&1
    if [ $? -ne 0 ]; then
        echo -e "    Failed to create override"
        exit 1
    fi
    echo "    Creating symlink to $1.dll... "
    ln -sf "$nvlibs_dir/$lib/$1.dll" "$unix_sys_path/$1.dll"
    if [ $? -ne 0 ]; then
        echo -e "    Failed to create override"
        exit 1
    fi
}

case "$1" in
uninstall)
    fun=removeOverride
    ;;
install)
    fun=createOverride
    ;;
*)
    echo "Unrecognized option: $1"
    echo "Usage: $0 [install|uninstall]"
    exit 1
    ;;
esac

echo '[1/4] nvcuda :'
$fun nvcuda
echo '[2/4] nvcuvid :'
$fun nvcuvid
echo '[3/4] nvencodeapi :'
$fun nvencodeapi
echo '[4/4] nvapi :'
$fun nvapi

wine="wine64"
lib='x64'
unix_sys_path=$($wine winepath -u 'C:\windows\system32' 2> /dev/null)
echo '[1/6] 64 bit nvcuda :'
$fun nvcuda
echo '[2/6] 64 bit nvoptix :'
$fun nvoptix
echo '[3/6] 64 bit nvcuvid :'
$fun nvcuvid
echo '[4/6] 64 bit nvencodeapi64 :'
$fun nvencodeapi64
echo '[5/6] 64 bit nvapi64 :'
$fun nvapi64
echo '[6/6] 64 bit nvofapi64 :'
$fun nvofapi64

if [ "$fun" = removeOverride ]; then
   echo "Rebooting prefix!"
   wineboot -u
   echo "All done!"
else
   echo "Symlinks created in $WINEPREFIX. Do NOT remove this source folder!"
   echo "OBS! NVML is NOT enabled by default. See Readme_nvml.txt for info or run nvml_setup.sh"
   echo "You need to REMOVE old overrides if older version of nvml have been used in $WINEPREFIX"
fi
