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

#ifndef __WINE_CUDA_H
#define __WINE_CUDA_H

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

typedef unsigned long long CUsurfObject;
typedef unsigned long long CUtexObject;

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
