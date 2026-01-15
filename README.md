# NVIDIA Libs

Release: 1.0.0  
Recommended nVidia proprietary driver branch 580+ for best compatibility with OptiX and CUDA.  

## Important info:
This provides 32bit library of dxvk-nvapi, but ALL other libraries are now 64bit.  
If 32bit nvcuda is needed, a separate package can be obtained from this branch:  
[https://github.com/SveSop/nvcuda/tree/32bit_only](https://github.com/SveSop/nvcuda/tree/32bit_only)  
There is also a 32bit released package for nvcuda v0.3 with installscripts under releases:
[https://github.com/SveSop/nvcuda/releases](https://github.com/SveSop/nvcuda/releases)  

## Support:
CUDA SDK up to 13.1 should now mostly be supported. There can still be missing functions  
Up to OptiX ABI 105 (SDK 9.0.0) should be supported. Additional logging: `WINEDEBUG=+nvoptix`  

Older drivers that does not support CUDA SDK 10 and older may also fail/crash. Report any crashes with  
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

## Build requirements:  
- [WINE] (version >= 10.0) [https://www.winehq.org/](https://www.winehq.org/)  
- [Meson] (version >= 0.61) [http://mesonbuild.com/](http://mesonbuild.com/)  
- [NINJA] [https://ninja-build.org/](https://ninja-build.org/)  
- [MINGW] (version >= 10.0) [https://www.mingw-w64.org/](https://www.mingw-w64.org/)  
- [GCC/G++] (version >= 12.0) [https://gcc.gnu.org/](https://gcc.gnu.org/)  

## How to build  

./package-release.sh name destdir  
eg. `./package-release.sh latest /home/yourname/`  
Will create a folder containing the libraries in `/home/yourname/nvidia-libs-latest`

### Optional build variables

If you put `--fakedll` after the buildscript like this:  
`./package-release.sh latest /home/yourname --fakedll`  
The library will be built as a winelib dll.so and a fakedll .dll placed in the  
output folder in typical wine folderstructure eg.  
`nvidia-libs-latest/lib/wine/x86_64-windows` and `nvidia-libs-latest/lib/wine/x86_64-unix`  
These can preferrably be used with the wine env variable `WINEDLLPATH` like this:  
`export WINEDLLPATH=/home/yourname/nvidia-libs-latest/lib/wine`  

This should make `wineboot -u` copy the fakedlls to your WINEPREFIX automatically if you  
use wine > 10.0. Be aware that you must use this ENV variable whenever you use that  
WINEPREFIX.  
This is true also for `dxvk-nvapi` dll's and `wine-nvml` library in the filestructure.  
The files can also be copied directly into the wine binary folders in the same folderstructure,  
and it should work the same way.  
OBS: No WINEPREFIX or PROTON install scripts will be available with this build method (for now).  

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
`GB200` (Blackwell)  

Known games that may need override:  
Monster Hunter World : `DXVK_NVAPI_GPU_ARCH=GP100`  
War Thunder : `DXVK_NVAPI_GPU_ARCH=GP100`  
Ghost of Tsushima : `DXVK_NVAPI_GPU_ARCH=GA100`  

### Vulkan Reflex Layer
This includes the Vulkan Reflex layer in /layer subfolder.  
Read about usage here:  
[https://github.com/jp7677/dxvk-nvapi#vulkan-reflex-layer](https://github.com/jp7677/dxvk-nvapi#vulkan-reflex-layer)  

### DXVK-NVAPI DLSS Settings
Various DLSS settings has been added to dxvk-nvapi. You can read more about various settings here:  
[https://github.com/jp7677/dxvk-nvapi/wiki/Passing-driver-settings](https://github.com/jp7677/dxvk-nvapi/wiki/Passing-driver-settings)  

### WINE-NVML  
In order to use DXVK-NVAPI (NvAPI) with some extra GPU information (temps and the likes)  
you need to copy the NVML binaries to your wine binaries folder. You can do this by  
running the included `nvml_setup.sh` script, or by using the `WINEDLLPATH` env variable like this:  
`export WINEDLLPATH=/home/yourname/nvidia-libs-v1.0.0/x64/wine`  
Also see the Readme_nvml.txt file.  

### Tests  
You can run tests of your adapter and functions by running the test case file:  
`WINEPREFIX=/your/wine/prefix wine bin/nvapi64-tests.exe`  
and you can run some small CUDA tests to verify your CUDA adapter like this:  
`WINEPREFIX=/your/wine/prefix wine bin/cudatest.exe`  

PS. You must install said libraryfiles in your WINEPREFIX (see above)  

### Bottles
Added a script that will install the libraries in a bottle.  
This assumes you are using bottles installed via `FlatPak`.  

Run `./bottles-install.sh` for a list of your available bottles, and use it like this:  
`./bottles-install.sh YourBottle` to install the libraries in the `YourBottle` bottle.  

You will want to run the script ever time you upgrade `nvidia-libs` binaries, and possibly  
if you change/update your runner. Eg. switching from Caffe-9.7 to Caffe-9.8.  

## Proton  
You can drop-in the libraries in Proton10 - Experimental or GE-Proton-10 or newer like this:  
`PROTON_LIBS='$HOME/.steam/compatibilitytools.d/Proton-10.25-GE' ./proton_setup.sh`  

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

## OpticalFlow usage
OpticalFlow for use with DLSS seems to have been discontinued with NVIDIA DLSS4.  

If OpticalFlow is required for some app or program, there is a archived version that can be  
used in the `nvofapi-workaround` branch if needed. This will however build an old version  
of nvapi & friends, and will (for now) not be updated.  

## DAZ Studio

In case you do NOT use nvml (wine-nvml) library to emulate nvml.dll, DAZ Studio MAY  
show 2 "adapters" for rendering. Choose the one that show your GPU name, and NOT the other.  

See above for installing or using the NVML library.  
 
## Quirks
Some older SDK samples may require specifying LD_LIBRARY_PATH to the system folder  
where libcuda.so.1 and other libnvidia-xxx.so libraries reside. This varies depending  
on distro. Ubuntu typicall uses `/lib/x86-64-linux-gnu/` for 64-bit.  

In cases where virtual or emulated hardware is used for nvcuda, wine may have issues getting  
the correct PCI ID from wine to obtain LUID from the cuDeviceGetLuid function. In those cases  
you can use a env variable to override this and generate a fake LUID like this:  
`CUDA_FAKE_LUID=1`  
Keep in mind that this should ONLY be used in the cases where the call to cuDeviceGetLuid  
fails, as this can introduce issues with apps using LUID from the CUDA adapter.  

SDK 13+ needs to use the file `nvcudart_hybrid64.dll`. This is a file included in the  
windows version of the NVIDIA driver, and must be extracted from the driver archive. I cannot  
provide the binary here.  

## Info  

Loads of reference info here:  

[NVIDIA NvAPI](https://docs.nvidia.com/gameworks/content/gameworkslibrary/coresdk/nvapi/annotated.html)  
[NVIDIA OPTIX](https://developer.nvidia.com/optix)  

Tool to check various GPU options:  
[http://www.ozone3d.net/gpu_caps_viewer/](http://www.ozone3d.net/gpu_caps_viewer/)  
