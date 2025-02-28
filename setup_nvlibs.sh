#!/bin/bash

nvlibs_dir="$(dirname "$(readlink -fm "$0")")"
lib='x32'

if [ ! -f "$nvlibs_dir/$lib/nvcuda.dll" ]; then
    echo "Files not found in $nvlibs_dir/$lib" >&2
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

wine_path="$(which wine 2>/dev/null)"
wine64_path="$(which wine64 2>/dev/null)"

if [ -n "$wine_path" ] && [ -n "$wine64_path" ] && [ "$(dirname "$wine_path")" != "$(dirname "$wine64_path")" ]; then
    echo "Multiple Wine installations detected:"
    echo "1) $wine_path"
    echo "2) $wine64_path"

    while true; do
        read -p "Select the Wine binary to use (1 or 2): " choice
        case "$choice" in
          1) wine="wine"; break ;;
          2) wine="wine64"; break ;;
          *) echo "Invalid choice. Please enter 1 or 2." ;;
        esac
    done
else
    if [ -n "$wine_path" ]; then
      wine="wine"
    fi
    if [ -n "$wine64_path" ]; then
      wine="wine64"
    fi
fi

winever=$($wine --version | grep wine)
if [ -z "$winever" ]; then
    echo "$wine:  Not a wine executable. Check your $wine." >&2
    exit 1
fi
echo "Using: $winever"

win64=true
win32=true

win64_sys_path="$($wine cmd /c '%SystemRoot%\system32\winepath.exe -u C:\windows\system32' 2>/dev/null)"
win64_sys_path="${win64_sys_path/$'\r'/}"

[ -z "$win64_sys_path" ] && win64=false

if grep --quiet -e '#arch=win32' "${WINEPREFIX:-$HOME/.wine}/system.reg"; then
  win32_sys_path=$win64_sys_path
  win64=false
  win32=true
else
  win32_sys_path="$($wine cmd /c '%SystemRoot%\syswow64\winepath.exe -u C:\windows\system32' 2>/dev/null)"
  win32_sys_path="${win32_sys_path/$'\r'/}"

  [ -z "$win32_sys_path" ] && win32=false
fi

if [ -z "$win32_sys_path" ] && [ -z "$win64_sys_path" ]; then
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
    local dll="$sys_path/$1.dll"
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
    ln -sf "$nvlibs_dir/$lib/$1.dll" "$sys_path/$1.dll"
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

if [ $win32 = "true" ]; then
    sys_path="$win32_sys_path"

    echo '[1/4] nvcuda :'
    $fun nvcuda
    echo '[2/4] nvcuvid :'
    $fun nvcuvid
    echo '[3/4] nvencodeapi :'
    $fun nvencodeapi
    echo '[4/4] nvapi :'
    $fun nvapi
fi

if [ $win64 = "true" ]; then
    lib='x64'
    sys_path="$win64_sys_path"

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
fi

if [ "$fun" = removeOverride ]; then
   echo "Rebooting prefix!"
   wineboot -u
   echo "All done!"
else
   echo "Symlinks created in $WINEPREFIX. Do NOT remove this source folder!"
   echo "OBS! NVML is NOT enabled by default. See Readme_nvml.txt for info or run nvml_setup.sh"
   echo "You need to REMOVE old overrides if older version of nvml have been used in $WINEPREFIX"
fi
