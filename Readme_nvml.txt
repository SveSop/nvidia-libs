WINE-NVML

Due to upstream changes, nvml lib can no longer be symlinked to the prefix.
See: https://github.com/Saancreed/wine-nvml/blob/master/README.md

You can use nvml_setup.sh script incuded to install nvml into your
wine binary install. Using a custom wine install is recommended for this
as using system wine install requires root access and file placements MAY
differ from various distros.

See the README.md (link above) for manual method if you choose.

OBS! Previously created WINEPREFIX with symlinks to nvml will NOT WORK. You
need to remove symlinks and dll-overrides in older WINEPREFIX

By default 32-bit and 64-bit is being built, and you can install these either
into your regular wine binaries by running nvml_setup.sh, or by running the
proton_setup.sh script and answer the questions accordingly. 

Be aware that by default 32-bit nvml only allows calls from NVAPI, but this can
be overridden by using:
WINE_NVML_ALLOW_32BIT=1
If you set 
WINE_NVML_ALLOW_32BIT=0 32-bit NVML is disabled.
