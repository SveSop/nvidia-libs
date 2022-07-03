WINE-NVML

Due to upstream changes, nvml lib can no longer be symlinked to the prefix.
See: https://github.com/Saancreed/wine-nvml/blob/master/README.md

You can use nvml_setup.sh script incuded to install nvml into your
wine binary install. Using a cust wine install is recommended for this
as using system wine install requires root access and file placements MAY
differ from various distros.

See the README.md (link above) for manual method if you choose.

OBS! Previously created WINEPREFIX with symlinks to nvml will NOT WORK. You
need to remove symlinks and dll-overrides in older WINEPREFIX!
