/*
 * Copyright (C) 2023-2024 Sveinar Søpler
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301, USA
 */
#ifndef ENCRYPTION_H
#define ENCRYPTION_H

#include <time.h>

struct EncryptInput1_st {
    unsigned int driverVersion;
    unsigned int cudaVersion;
    unsigned int processID;
    unsigned int threadID;
    const void *exportTable1;
    const void *exportTable2;
    void *funcPtr;
    time_t timestamp;
};
typedef struct EncryptInput1_st EncryptInput1;

struct EncryptInput2_st {
    CUuuid uuid;
    int pciDomain;
    int pciBus;
    int pciDevice;
};
typedef struct EncryptInput2_st EncryptInput2;

CUresult __attribute((visibility("hidden"))) WINAPI wine_cuDeviceGet(CUdevice *device, int ordinal);
CUresult __attribute((visibility("hidden"))) WINAPI wine_cuDeviceGetUuid(CUuuid *uuid, CUdevice device);
CUresult __attribute((visibility("hidden"))) WINAPI wine_cuDriverGetVersion(int *version);
CUresult __attribute((visibility("hidden"))) WINAPI wine_cuDeviceGetCount(int *count);
CUresult __attribute((visibility("hidden"))) WINAPI wine_cuDeviceGetAttribute(int *pi, CUdevice_attribute attrib, CUdevice device);
CUresult __attribute((visibility("hidden"))) WINAPI encrypt(EncryptInput1 *input1, __uint128_t *res);

#endif /* ENCRYPTION_H */
