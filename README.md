# NVIDIA Libs

Release: 0.8.1  
Recommended nVidia proprietary driver branch 550+ for best compatibility with OptiX and CUDA.  

CUDA SDK >12.x should now mostly be supported. There can still be missing functions  
Up to OptiX ABI 93 (SDK 8.1.0) should be supported. Additional logging: `WINEDEBUG=+nvoptix`  

Older drivers that does not support SDK 10 and older may also fail/crash. Report any crashes with  
logs on the issue page. However these are highly outdated drivers in general and will probably not  
see too much attention in that regard.  

Create logs typically with: `WINEDEBUG=-all,+nvcuda,+nvml wine ./yourapp.exe > yourapp.log 2>&1`  
If you suspect errors with video encoding/decoding (NVENC), you can create a log like this:  
`WINEDEBUG=-all,+nvcuvid,+nvencodeapi wine ./yourapp.exe > yourapp.log 2>&1`
Also see notes about DXVK-NVAPI below for additional logging.  

Library contains:  
nvapi (dxvk-nvapi + additions - [https://github.com/SveSop/dxvk-nvapi/tree/experimental](https://github.com/SveSop/dxvk-nvapi/tree/experimental))  
nvcuda (wine-staging + development - [https://github.com/SveSop/nvcuda](https://github.com/SveSop/nvcuda))  
nvcuvid/nvencodeapi (wine-staging + development - [https://github.com/SveSop/nvenc](https://github.com/SveSop/nvenc))  
nvml (wine-nvml - [https://github.com/Saancreed/wine-nvml](https://github.com/Saancreed/wine-nvml))  
nvoptix (wine-nvoptix - [https://github.com/SveSop/wine-nvoptix](https://github.com/SveSop/wine-nvoptix))  
nvofapi64_cuda - relay (nvofapi for cuda - [https://github.com/SveSop/nvofapi-relay](https://github.com/SveSop/nvofapi-relay)  

## Build requirements:  
- [WINE] (version >= 9.0) [https://www.winehq.org/](https://www.winehq.org/)  
- [Meson] (version >= 0.61) [http://mesonbuild.com/](http://mesonbuild.com/)  
- [NINJA] [https://ninja-build.org/](https://ninja-build.org/)  
- [MINGW] (version >= 10.0) [https://www.mingw-w64.org/](https://www.mingw-w64.org/)  
- [GCC/G++] (version >= 10.0) [https://gcc.gnu.org/](https://gcc.gnu.org/)  

## How to build  

./package-release.sh name destdir  

## How to install  

### Wineprefix  
You can install symlinks and dll-overrides to the libraries in your wineprefix like this:  
`WINEPREFIX=/your/wine/prefix ./setup_nvlibs.sh install`  

To uninstall:  
`WINEPREFIX=/your/wine/prefix ./setup_nvlibs.sh uninstall`  

### DXVK-NVAPI
Check out README file usage of DXVK-NVAPI.  
[https://github.com/SveSop/dxvk-nvapi/blob/master/README.md](https://github.com/SveSop/dxvk-nvapi/blob/master/README.md)  
Typical log level usage:  
`DXVK_NVAPI_LOG_LEVEL=none` (Default) No output.  
`DXVK_NVAPI_LOG_LEVEL=info` Informational output of function calls.  
`DXVK_NVAPI_LOG_LEVEL=trace` Detailed debug information.  

For misbehaving games that do not work too well with DLSS or otherwise do not work with  
the detected architecture, you can override detected architecture like this:  
`DXVK_NVAPI_GPU_ARCH=` with one of the following options:  

`GK100` (Kepler)  
`GM200` (Maxwell)  
`GP100` (Pascal)  
`GV100` (Volta)  
`TU100` (Turing)  
`GA100` (Ampere)  
`AD100` (Ada)  

Known games that may need override:  
Monster Hunter World : `DXVK_NVAPI_GPU_ARCH=GP100`  
War Thunder : `DXVK_NVAPI_GPU_ARCH=GP100`  
Ghost of Tsushima : `DXVK_NVAPI_GPU_ARCH=GA100`  
Indiana Jones and the Great Circle: (See own section below).  

### WINE-NVML  
In order to use DXVK-NVAPI (NvAPI) with some extra GPU information (temps and the likes)  
you need to copy the NVML binaries to your wine binaries folder. You can do this by  
running the included `nvml_setup.sh` script. NVML is only available as 64-bit  
See the Readme_nvml.txt file.  

### Tests  
You can run tests of your adapter and functions by running the test case file:  
`WINEPREFIX=/your/wine/prefix wine bin/nvapi64-tests.exe`  

PS. You must install said libraryfile in your WINEPREFIX (see above)  

### Bottles
Added a script that will install the libraries in a bottle.  
This assumes you are using bottles installed via `FlatPak`.  

Run `./bottles-install.sh` for a list of your available bottles, and use it like this:  
`./bottles-install.sh YourBottle` to install the libraries in the `YourBottle` bottle.  

You will want to run the script ever time you upgrade `nvidia-libs` binaries, and possibly  
if you change/update your runner. Eg. switching from Caffe-9.7 to Caffe-9.8.  

## Proton  
You can drop-in the libraries in Proton8 - Experimental or GE-Proton-8 or newer like this:
  
`PROTON_LIBS='$HOME/.steam/compatibilitytools.d/Proton-8.27-GE' ./proton_setup.sh`  

This will replace or add the libs to Proton for use with games.  
The installscript is no longer compatible with older Proton-6.3 or Proton-GE-6/7 versions.  

OBS!  
You can add:  
   `"DXVK_ENABLE_NVAPI": "1",`  
   `"PROTON_ENABLE_NVAPI": "1",`  
to your user_settings.py script in the proton folder eg:  
`PROTON_LIBS='$HOME/.steam/compatibilitytools.d/GE-Proton-8.27/user_settings.py'`  

Or you can run the game with `PROTON_ENABLE_NVAPI=1 DXVK_ENABLE_NVAPI=1 %command%`  

Some additional tweaks may be required depending on game used and version of Proton.  
It is HIGHLY RECOMMENDED that you re-create the game-prefix after installing the nvidia-libs  
package, to make sure they are used in the new prefix. The game prefixes are typically located  
in `$HOME/.steam/steam/steamapps/compatdata/XXXXXXX` where XXXXXXX is the steam AppID.  

## Indiana Jones and the Great Circle
To have FrameGeneration when using a RTX40xx series card in this game you can use the included install  
script for proton (see Proton section above). This will then install `nvcuda.dll`,  
`nvofapi64_cuda.dll` and a custom version of `nvofapi64.dll` in the the Proton binary tree.  

You then run the game with `DXVK_NVAPI_GPU_ARCH=AD100 __GL_13ebad=0x1 %command%` option in steam.  

## DAZ Studio

In case you do NOT use nvml (wine-nvml) library to emulate nvml.dll, DAZ Studio MAY  
show 2 "adapters" for rendering. Choose the one that show your GPU name, and NOT the other.  

NVML can be installed by using the `setup_nvml.sh` script included in the package and for  
DAZ Studio it is recommended.  
 
## Quirks
Some older SDK samples may require specifying LD_LIBRARY_PATH to the system folder  
where libcuda.so.1 and other libnvidia-xxx.so libraries reside. This varies depending  
on distro. Ubuntu typicall uses `/lib/x86-64-linux-gnu/` for 64-bit and  
`/lib/i386-linux-gnu/` for 32-bit.  

For instance to get the NVIDIA SuperSonic Sled demo to run on Ubuntu you can load wine  
with using `LD_LIBRARY_PATH=/lib/i386-linux-gnu:$LD_LIBRARY_PATH`  

## Info  

Loads of reference info here:  

[NVIDIA NvAPI](https://docs.nvidia.com/gameworks/content/gameworkslibrary/coresdk/nvapi/annotated.html)  
[NVIDIA OPTIX](https://developer.nvidia.com/optix)  

Tool to check various GPU options:  
[http://www.ozone3d.net/gpu_caps_viewer/](http://www.ozone3d.net/gpu_caps_viewer/)  
