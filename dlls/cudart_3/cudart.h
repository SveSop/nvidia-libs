/*
 * Copyright (C) 2024 Sveinar Søpler
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

#ifndef __WINE_CUDART_H
#define __WINE_CUDART_H

#define CUDARTAPI

typedef void* cudaStream_t;

typedef struct {
    unsigned int x, y, z;
} dim3;

typedef struct {
    unsigned int x, y, z;
} uint3;

typedef struct cudaFuncAttributes {
    int binaryVersion;
    int constSizeBytes;
    int localSizeBytes;
    int maxThreadsPerBlock;
    int numRegs;
    int ptxVersion;
    int sharedSizeBytes;
} cudaFuncAttributes;

typedef enum cudaError {
    cudaSuccess = 0,
    cudaErrorMissingConfiguration,
    cudaErrorMemoryAllocation,
    cudaErrorInitializationError,
    cudaErrorLaunchFailure,
    cudaErrorPriorLaunchFailure,
    cudaErrorLaunchTimeout,
    cudaErrorLaunchOutOfResources,
    cudaErrorInvalidDeviceFunction,
    cudaErrorInvalidConfiguration,
    cudaErrorInvalidDevice,
    cudaErrorInvalidValue,
    cudaErrorInvalidPitchValue,
    cudaErrorInvalidSymbol,
    cudaErrorMapBufferObjectFailed,
    cudaErrorUnmapBufferObjectFailed,
    cudaErrorInvalidHostPointer,
    cudaErrorInvalidDevicePointer,
    cudaErrorInvalidTexture,
    cudaErrorInvalidTextureBinding,
    cudaErrorInvalidChannelDescriptor,
    cudaErrorInvalidMemcpyDirection,
    cudaErrorAddressOfConstant,
    cudaErrorTextureFetchFailed,
    cudaErrorTextureNotBound,
    cudaErrorSynchronizationError,
    cudaErrorInvalidFilterSetting,
    cudaErrorInvalidNormSetting,
    cudaErrorMixedDeviceExecution,
    cudaErrorCudartUnloading,
    cudaErrorUnknown,
    cudaErrorNotYetImplemented,
    cudaErrorMemoryValueTooLarge,
    cudaErrorInvalidResourceHandle,
    cudaErrorNotReady,
    cudaErrorInsufficientDriver,
    cudaErrorSetOnActiveProcess,
    cudaErrorInvalidSurface,
    cudaErrorNoDevice,
    cudaErrorECCUncorrectable,
    cudaErrorSharedObjectSymbolNotFound,
    cudaErrorSharedObjectInitFailed,
    cudaErrorUnsupportedLimit,
    cudaErrorDuplicateVariableName,
    cudaErrorDuplicateTextureName,
    cudaErrorDuplicateSurfaceName,
    cudaErrorDevicesUnavailable,
    cudaErrorInvalidKernelImage,
    cudaErrorNoKernelImageForDevice,
    cudaErrorIncompatibleDriverContext,
    cudaErrorPeerAccessAlreadyEnabled,
    cudaErrorPeerAccessNotEnabled,
    cudaErrorDeviceAlreadyInUse,
    cudaErrorProfilerDisabled,
    cudaErrorProfilerNotInitialized,
    cudaErrorProfilerAlreadyStarted,
    cudaErrorProfilerAlreadyStopped,
    cudaErrorAssert,
    cudaErrorTooManyPeers,
    cudaErrorHostMemoryAlreadyRegistered,
    cudaErrorHostMemoryNotRegistered,
    cudaErrorOperatingSystem,
    cudaErrorPeerAccessUnsupported,
    cudaErrorLaunchMaxDepthExceeded,
    cudaErrorLaunchFileScopedTex,
    cudaErrorLaunchFileScopedSurf,
    cudaErrorSyncDepthExceeded,
    cudaErrorLaunchPendingCountExceeded,
    cudaErrorNotPermitted,
    cudaErrorNotSupported,
    cudaErrorHardwareStackError,
    cudaErrorIllegalInstruction,
    cudaErrorMisalignedAddress,
    cudaErrorInvalidAddressSpace,
    cudaErrorInvalidPc,
    cudaErrorIllegalAddress,
    cudaErrorInvalidPtx,
    cudaErrorInvalidGraphicsContext,
    cudaErrorNvlinkUncorrectable,
    cudaErrorJitCompilerNotFound,
    cudaErrorCooperativeLaunchTooLarge,
    cudaErrorStartupFailure,
    cudaErrorApiFailureBase = 10000
} cudaError_t;

typedef enum cudaChannelFormatKind {
    cudaChannelFormatKindSigned   = 0,
    cudaChannelFormatKindUnsigned = 1,
    cudaChannelFormatKindFloat    = 2,
    cudaChannelFormatKindNone     = 3
} cudaChannelFormatKind;

typedef struct cudaChannelFormatDesc {
    int x;
    int y;
    int z;
    int w;
    enum cudaChannelFormatKind f;
} cudaChannelFormatDesc;

typedef enum cudaMemcpyKind {
    cudaMemcpyHostToHost     = 0,
    cudaMemcpyHostToDevice   = 1,
    cudaMemcpyDeviceToHost   = 2,
    cudaMemcpyDeviceToDevice = 3,
    cudaMemcpyDefault        = 4
} cudaMemcpyKind;

typedef struct cudaExtent {
    size_t width;
    size_t height;
    size_t depth;
} cudaExtent;

typedef struct cudaPos {
    size_t x;
    size_t y;
    size_t z;
} cudaPos;

typedef struct cudaPitchedPtr {
    void* ptr;
    size_t pitch;
    size_t xsize;
    size_t ysize;
} cudaPitchedPtr;

typedef struct cudaMemcpy3DParms {
    void*                 srcArray;
    cudaPos               srcPos;
    cudaPitchedPtr        srcPtr;
    void*                 dstArray;
    cudaPos               dstPos;
    cudaPitchedPtr        dstPtr;
    cudaExtent            extent;
    cudaMemcpyKind        kind;
} cudaMemcpy3DParms;

#endif // __WINE_CUDART_H
