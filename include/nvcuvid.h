/*
 * Copyright (C) 2015 Michael Müller
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

#ifndef __WINE_NVCUVID_H
#define __WINE_NVCUVID_H

#include "cuviddec.h"

typedef void *CUvideosource;
typedef void *CUvideoparser;
typedef long long CUvideotimestamp;

typedef int cudaVideoState;

/* the following structures are documented but we don't need to know the details */
typedef struct _CUAUDIOFORMAT CUAUDIOFORMAT;
typedef struct _CUVIDEOFORMAT CUVIDEOFORMAT;
typedef struct _CUVIDEOFORMATEX CUVIDEOFORMATEX;
typedef struct _CUVIDPARSERDISPINFO CUVIDPARSERDISPINFO;
typedef struct _CUVIDPICPARAMS CUVIDPICPARAMS;

typedef struct _CUVIDPARSERPARAMS
{
    cudaVideoCodec CodecType;
    unsigned int ulMaxNumDecodeSurfaces;
    unsigned int ulClockRate;
    unsigned int ulErrorThreshold;
    unsigned int ulMaxDisplayDelay;
    unsigned int uReserved1[5];
    void *pUserData;
    void *pfnSequenceCallback;
    void *pfnDecodePicture;
    void *pfnDisplayPicture;
    void *pvReserved2[7];
    CUVIDEOFORMATEX *pExtVideoInfo;
} CUVIDPARSERPARAMS;

typedef struct _CUVIDSOURCEPARAMS
{
    unsigned int ulClockRate;
    unsigned int uReserved1[7];
    void *pUserData;
    void *pfnVideoDataHandler;
    void *pfnAudioDataHandler;
    void *pvReserved2[8];
} CUVIDSOURCEPARAMS;

typedef struct _LINUX_CUVIDSOURCEDATAPACKET
{
    unsigned long flags;
    unsigned long payload_size;
    const unsigned char *payload;
    CUvideotimestamp timestamp;
} LINUX_CUVIDSOURCEDATAPACKET;

typedef struct _CUVIDSOURCEDATAPACKET
{
    ULONG flags;
    ULONG payload_size;
    const unsigned char *payload;
    CUvideotimestamp timestamp DECLSPEC_ALIGN(8);
} CUVIDSOURCEDATAPACKET;

#endif /* __WINE_NVCUVID_H */
