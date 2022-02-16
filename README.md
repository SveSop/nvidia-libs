# NVIDIA Libs

Release: 0.7.1  
Requires nVidia proprietary driver branch 470+ (495+ for best compatibility with OptiX)  

Library contains:  
nvapi (dxvk-nvapi)  
nvcuda (staging)  
nvml (wine-nvml)  
nvoptix (wine-nvoptix)  

## Build requirements:  
- [WINE] (version >= 6.23) [https://www.winehq.org/](https://www.winehq.org/)  
- [Meson] [http://mesonbuild.com/](http://mesonbuild.com/)  
- [NINJA] [https://ninja-build.org/](https://ninja-build.org/)  
- [MINGW] (version >= 9.0) [https://www.mingw-w64.org/](https://www.mingw-w64.org/)  

## How to build  

./package-release.sh destdir  

## How to install  

### Wineprefix  
You can install symlinks and dll-overrides to the libraries in your wineprefix like this:  
`WINEPREFIX=/your/wine/prefix ./setup_nvlibs.sh install`  

To uninstall:  
`WINEPREFIX=/your/wine/prefix ./setup_nvlibs.sh uninstall`  

### Tests  
You can run tests of your adapter and functions by running the test case file:  
`WINEPREFIX=/your/wine/prefix wine bin/nvapi64-tests.exe`  

PS. You must install said libraryfile in your WINEPREFIX (see above)  

### Proton  
You can drop-in the libraries in Proton - Experimental or Proton-6.12-GE-1 or newer like this:
  
`PROTON_LIBS='$HOME/.steam/compatibilitytools.d/Proton-6.12-GE-1' ./proton_setup.sh`  

This will replace or add the libs to Proton for use with games.  
OBS!  
Remember to add:  
   `"PROTON_ENABLE_NVAPI": "1",`  
to your user_settings.py script in the proton folder eg:  
`PROTON_LIBS='$HOME/.steam/compatibilitytools.d/Proton-6.12-GE-1/user_settings.py'`  

Or you can run the game with `PROTON_ENABLE_NVAPI=1 %command%`  

You also need a working `dxvk.conf` file in the games binary folder with the setting:  
`dxgi.nvapiHack = False`  

Eg:  
`$HOME/.steam/steam/steamapps/common/Batman Arkham Knight/Binaries/Win64/dxvk.conf`  

## Info  

Loads of reference info here:  

[NVIDIA NvAPI](https://docs.nvidia.com/gameworks/content/gameworkslibrary/coresdk/nvapi/annotated.html)  
[NVIDIA OPTIX](https://developer.nvidia.com/optix)  
[DXVK-NVAPI](https://github.com/jp7677/dxvk-nvapi)  
[WINE-NVML](https://github.com/Saancreed/wine-nvml)  
[WINE-NVOPTIX](https://github.com/SveSop/wine-nvoptix)  

Tool to check various GPU options:  
[http://www.ozone3d.net/gpu_caps_viewer/](http://www.ozone3d.net/gpu_caps_viewer/)  
