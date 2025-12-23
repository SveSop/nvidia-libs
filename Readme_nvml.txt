WINE-NVML

Due to upstream changes, nvml lib can no longer be symlinked to the prefix.
See: https://github.com/Saancreed/wine-nvml/blob/master/README.md

You can use nvml_setup.sh script incuded to install nvml into your
wine binary folders. Using a custom wine install is recommended for this
as using system wine install requires root access and file placements MAY
differ from various distros.

You can use WINEDLLPATH env variable with wine.
eg. WINEDLLPATH='/home/my-user/nvidia-libs/x64/wine'

When using >= wine-10, this will make the PE version (nvml.dll) install into
the WINEPREFIX. With older versions of wine, this needs manual copy/symlink
to the WINEPREFIX.

Only 64bit NVML is provided.
