# NVIDIA Libs

Requires nVidia proprietary driver version 460.x or newer  

Library contains:  
nvapi (dxvk-nvapi)  
nvcuda (staging)  
nvcuvid (staging)  
nvencodeapi (staging)  
nvml (wine-nvml)  

## Build requirements:  
- [WINE] (version >= 6.12) [https://www.winehq.org/](https://www.winehq.org/)  
- [Meson] [http://mesonbuild.com/](http://mesonbuild.com/)  
- [NINJA] [https://ninja-build.org/](https://ninja-build.org/)  

## How to build  

./package-release.sh destdir  

## How to install  

### Wineprefix  
You can install symlinks and dll-overrides to the libraries in your wineprefix like this:  
`WINEPREFIX=/your/wine/prefix ./setup_nvlibs.sh install`  

To uninstall:  
`WINEPREFIX=/your/wine/prefix ./setup_nvlibs.sh uninstall`  

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

[https://docs.nvidia.com/gameworks/content/gameworkslibrary/coresdk/nvapi/annotated.html](https://docs.nvidia.com/gameworks/content/gameworkslibrary/coresdk/nvapi/annotated.html)  
[https://github.com/jp7677/dxvk-nvapi](https://github.com/jp7677/dxvk-nvapi)  
[https://github.com/Saancreed/wine-nvml](https://github.com/Saancreed/wine-nvml)  

Tool to check various GPU options:  
[http://www.ozone3d.net/gpu_caps_viewer/](http://www.ozone3d.net/gpu_caps_viewer/)  
