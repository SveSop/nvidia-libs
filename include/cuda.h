/*
 * Copyright (C) 2015 Sebastian Lackner
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

#include <stdint.h>
#include <inttypes.h>

#ifndef __WINE_CUDA_H
#define __WINE_CUDA_H

#ifdef _WIN32
#define CUDA_CB __stdcall
#else
#define CUDA_CB
#endif

#define CUDA_SUCCESS                0
#define CUDA_ERROR_INVALID_VALUE    1
#define CUDA_ERROR_OUT_OF_MEMORY    2
#define CUDA_ERROR_INVALID_CONTEXT  201
#define CUDA_ERROR_FILE_NOT_FOUND   301
#define CUDA_ERROR_INVALID_HANDLE   400
#define CUDA_ERROR_NOT_SUPPORTED    801
#define CUDA_ERROR_UNKNOWN          999

#define CU_IPC_HANDLE_SIZE          64

#if defined(__x86_64) || defined(AMD64) || defined(_M_AMD64) || defined(__aarch64__)
typedef unsigned long long CUdeviceptr;
#else
typedef unsigned int CUdeviceptr;
#endif

typedef int CUGLDeviceList;
typedef int CUaddress_mode;
typedef int CUarray_format;
typedef int CUdevice;
typedef int CUdevice_attribute;
typedef int CUfilter_mode;
typedef int CUfunc_cache;
typedef int CUfunction_attribute;
typedef int CUipcMem_flags;
typedef int CUjitInputType;
typedef int CUjit_option;
typedef int CUlimit;
typedef int CUmemorytype;
typedef int CUpointer_attribute;
typedef int CUresourceViewFormat;
typedef int CUresourcetype;
typedef int CUresult;
typedef int CUsharedconfig;

typedef void *CUDA_ARRAY3D_DESCRIPTOR;
typedef void *CUDA_ARRAY_DESCRIPTOR;
typedef void *CUDA_MEMCPY2D;
typedef void *CUDA_MEMCPY3D;
typedef void *CUDA_MEMCPY3D_PEER;
typedef void *CUDA_RESOURCE_DESC;
typedef void *CUDA_RESOURCE_VIEW_DESC;
typedef void *CUDA_TEXTURE_DESC;
typedef void *CUarray;
typedef void *CUcontext;
typedef void *CUdevprop;
typedef void *CUevent;
typedef void *CUfunction;
typedef void *CUgraphicsResource;
typedef void *CUlinkState;
typedef void *CUmipmappedArray;
typedef void *CUmodule;
typedef void *CUstream;
typedef void *CUsurfref;
typedef void *CUtexref;
typedef void (CUDA_CB *CUhostFn)(void *userData);

typedef unsigned long long CUsurfObject;
typedef unsigned long long CUtexObject;

typedef uint32_t cuuint32_t;
typedef uint64_t cuuint64_t;

typedef enum CUstreamCaptureStatus_enum {
    CU_STREAM_CAPTURE_STATUS_NONE        = 0,
    CU_STREAM_CAPTURE_STATUS_ACTIVE      = 1,
    CU_STREAM_CAPTURE_STATUS_INVALIDATED = 2
} CUstreamCaptureStatus;

typedef struct CUgraph_st *CUgraph;
typedef struct CUgraphNode_st *CUgraphNode;
typedef struct CUgraphExec_st *CUgraphExec;

typedef struct CUDA_MEMCPY3D_st {
    size_t srcXInBytes;
    size_t srcY;
    size_t srcZ;
    size_t srcLOD;
    CUmemorytype srcMemoryType;
    const void *srcHost;
    CUdeviceptr srcDevice;
    CUarray srcArray;
    void *reserved0;
    size_t srcPitch;
    size_t srcHeight;

    size_t dstXInBytes;
    size_t dstY;
    size_t dstZ;
    size_t dstLOD;
    CUmemorytype dstMemoryType;
    void *dstHost;
    CUdeviceptr dstDevice;
    CUarray dstArray;
    void *reserved1;
    size_t dstPitch;
    size_t dstHeight;

    size_t WidthInBytes;
    size_t Height;
    size_t Depth;
} CUDA_MEMCPY3D_v2;

typedef struct CUDA_MEMSET_NODE_PARAMS_st {
    CUdeviceptr dst;
    size_t pitch;
    unsigned int value;
    unsigned int elementSize;
    size_t width;
    size_t height;
} CUDA_MEMSET_NODE_PARAMS_v1;

typedef struct CUDA_KERNEL_NODE_PARAMS_st {
    CUfunction func;
    unsigned int gridDimX;
    unsigned int gridDimY;
    unsigned int gridDimZ;
    unsigned int blockDimX;
    unsigned int blockDimY;
    unsigned int blockDimZ;
    unsigned int sharedMemBytes;
    void **kernelParams;
    void **extra;
} CUDA_KERNEL_NODE_PARAMS_v1;

typedef struct CUDA_HOST_NODE_PARAMS_st {
    CUhostFn fn;
    void* userData;
} CUDA_HOST_NODE_PARAMS_v1;

typedef struct CUipcEventHandle_st
{
    char reserved[CU_IPC_HANDLE_SIZE];
} CUipcEventHandle;

typedef struct CUipcMemHandle_st
{
    char reserved[CU_IPC_HANDLE_SIZE];
} CUipcMemHandle;

typedef struct CUuuid_st
{
    char bytes[16];
} CUuuid;

#endif /* __WINE_CUDA_H */
