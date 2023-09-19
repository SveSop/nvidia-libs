# NVIDIA Libs

Release: 0.7.12  
Recommended nVidia proprietary driver branch 535+ for best compatibility with OptiX and CUDA.  

CUDA SDK >11.5 is not supported when samples/apps are using the CUDA RUNTIME API  
This is typically used by NVIDIA IRAY and OptiX, and this will eventually fail if used on OptiX  
sources that requires this.  
Older drivers that does not support SDK 10 and older may also fail/crash. Report any crashes with  
logs on the issue page. However these are highly outdated drivers in general and will probably not  
see too much attention in that regard.  

Create logs typically with: `WINEDEBUG=-all,+nvcuda wine ./yourapp.exe > yourapp.log 2>&1`  

Library contains:  
nvapi (dxvk-nvapi)  
nvcuda (staging)  
nvml (wine-nvml)  
nvoptix (wine-nvoptix)  

## Build requirements:  
- [WINE] (version >= 8.0) [https://www.winehq.org/](https://www.winehq.org/)  
- [Meson] [http://mesonbuild.com/](http://mesonbuild.com/)  
- [NINJA] [https://ninja-build.org/](https://ninja-build.org/)  
- [MINGW] (version >= 9.0) [https://www.mingw-w64.org/](https://www.mingw-w64.org/)  

## How to build  

./package-release.sh name destdir  

## How to install  

### Wineprefix  
You can install symlinks and dll-overrides to the libraries in your wineprefix like this:  
`WINEPREFIX=/your/wine/prefix ./setup_nvlibs.sh install`  

To uninstall:  
`WINEPREFIX=/your/wine/prefix ./setup_nvlibs.sh uninstall`  

### WINE-NVML  
In order to use DXVK-NVAPI (NvAPI) with some extra GPU information (temps and the likes)  
you need to copy the NVML binaries to your wine binaries folder. You can do this by  
running the included nvml_setup.sh script. NVML is only available as 64-bit  
See the Readme_nvml.txt file.  

### Tests  
You can run tests of your adapter and functions by running the test case file:  
`WINEPREFIX=/your/wine/prefix wine bin/nvapi64-tests.exe`  

PS. You must install said libraryfile in your WINEPREFIX (see above)  

### Proton  
You can drop-in the libraries in Proton7 - Experimental or GE-Proton-7 or newer like this:
  
`PROTON_LIBS='$HOME/.steam/compatibilitytools.d/Proton-6.12-GE-1' ./proton_setup.sh`  

This will replace or add the libs to Proton for use with games.  
The installscript is no longer compatible with older Proton-6.3 or Proton-GE-6/7 versions.  

OBS!  
Remember to add:  
   `"PROTON_ENABLE_NVAPI": "1",`  
to your user_settings.py script in the proton folder eg:  
`PROTON_LIBS='$HOME/.steam/compatibilitytools.d/Proton-6.12-GE-1/user_settings.py'`  

Or you can run the game with `PROTON_ENABLE_NVAPI=1 %command%`  

You can also put a `dxvk.conf` file in the games binary folder with the setting:  
`dxgi.hideNvidiaGpu = False`  

Eg:  
`$HOME/.steam/steam/steamapps/common/Batman Arkham Knight/Binaries/Win64/dxvk.conf`  
or use DXVK setting:  
`DXVK_CONFIG_FILE=$HOME/winesuff/dxvk.conf`  

## Info  

Loads of reference info here:  

[NVIDIA NvAPI](https://docs.nvidia.com/gameworks/content/gameworkslibrary/coresdk/nvapi/annotated.html)  
[NVIDIA OPTIX](https://developer.nvidia.com/optix)  
[DXVK-NVAPI](https://github.com/jp7677/dxvk-nvapi)  
[WINE-NVML](https://github.com/Saancreed/wine-nvml)  
[WINE-NVOPTIX](https://github.com/SveSop/wine-nvoptix)  

Tool to check various GPU options:  
[http://www.ozone3d.net/gpu_caps_viewer/](http://www.ozone3d.net/gpu_caps_viewer/)  
