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

#ifndef __WINE_CUVIDDEC_H
#define __WINE_CUVIDDEC_H

#include "cuda.h"

typedef void *CUvideodecoder;
typedef void *CUvideoctxlock;

typedef int cudaVideoCodec;
typedef int cudaVideoChromaFormat;
typedef int cudaVideoSurfaceFormat;
typedef int cudaVideoDeinterlaceMode;

/* the following structures are documented but we don't need to know the content */
typedef struct _CUVIDPROCPARAMS CUVIDPROCPARAMS;

typedef struct _LINUX_CUVIDDECODECREATEINFO
{
    unsigned long ulWidth;
    unsigned long ulHeight;
    unsigned long ulNumDecodeSurfaces;
    cudaVideoCodec CodecType;
    cudaVideoChromaFormat ChromaFormat;
    unsigned long ulCreationFlags;
    unsigned long Reserved1[5];
    struct
    {
        short left;
        short top;
        short right;
        short bottom;
    } display_area;
    cudaVideoSurfaceFormat OutputFormat;
    cudaVideoDeinterlaceMode DeinterlaceMode;
    unsigned long ulTargetWidth;
    unsigned long ulTargetHeight;
    unsigned long ulNumOutputSurfaces;
    CUvideoctxlock vidLock;
    struct
    {
        short left;
        short top;
        short right;
        short bottom;
    } target_rect;
    unsigned long Reserved2[5];
} LINUX_CUVIDDECODECREATEINFO;

typedef struct _CUVIDDECODECREATEINFO
{
    ULONG ulWidth;
    ULONG ulHeight;
    ULONG ulNumDecodeSurfaces;
    cudaVideoCodec CodecType;
    cudaVideoChromaFormat ChromaFormat;
    ULONG ulCreationFlags;
    ULONG Reserved1[5];
    struct
    {
        short left;
        short top;
        short right;
        short bottom;
    } display_area;
    cudaVideoSurfaceFormat OutputFormat;
    cudaVideoDeinterlaceMode DeinterlaceMode;
    ULONG ulTargetWidth;
    ULONG ulTargetHeight;
    ULONG ulNumOutputSurfaces;
    CUvideoctxlock vidLock;
    struct
    {
        short left;
        short top;
        short right;
        short bottom;
    } target_rect;
    ULONG Reserved2[5];
} CUVIDDECODECREATEINFO;

#endif /* __WINE_CUVIDDEC_H */
