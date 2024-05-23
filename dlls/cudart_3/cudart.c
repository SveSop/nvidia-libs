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

#include "config.h"
#include <dlfcn.h>
#include <stdarg.h>
#include <assert.h>
#include <stdlib.h>

#ifdef HAVE_PTHREAD_H
#include <pthread.h>
#endif

#include "windef.h"
#include "winbase.h"
#include "wine/debug.h"
#include "wine/list.h"
#include "wine/wgl.h"
#include "cudart.h"

WINE_DEFAULT_DEBUG_CHANNEL(nvcuda);

static cudaError_t (*pcudaBindTexture)(size_t *offset, void *texref, const void *devPtr, const void *desc, size_t size);
static cudaError_t (*pcudaBindTexture2D)(size_t *offset, const void *texref, const void *devPtr, const void *desc, size_t width, size_t height, size_t pitch);
static cudaError_t (*pcudaBindTextureToArray)(const void *texref, const void *array, const void *desc);
static cudaError_t (*pcudaChooseDevice)(int *device, const void *prop);
static cudaError_t (*pcudaConfigureCall)(dim3 gridDim, dim3 blockDim, size_t sharedMem, cudaStream_t stream);
static cudaError_t (*pcudaGetChannelDesc)(void *desc, const void *array);
static cudaError_t (*pcudaDriverGetVersion)(int *driverVersion);
static cudaError_t (*pcudaGetDeviceCount)(int *count);
static cudaError_t (*pcudaGetDeviceProperties)(void *prop, int device);
static cudaError_t (*pcudaRuntimeGetVersion)(int *runtimeVersion);
static cudaError_t (*pcudaEventCreate)(void *event);
static cudaError_t (*pcudaEventCreateWithFlags)(void *event, unsigned int flag);
static cudaError_t (*pcudaEventDestroy)(void *event);
static cudaError_t (*pcudaEventElapsedTime)(float *ms, void *start, void *end);
static cudaError_t (*pcudaEventQuery)(void *event);
static cudaError_t (*pcudaEventRecord)(void* event, cudaStream_t stream);
static cudaError_t (*pcudaEventSynchronize)(void *event);
static cudaError_t (*pcudaFree)(void *devPtr);
static cudaError_t (*pcudaFreeArray)(void *array);
static cudaError_t (*pcudaFreeHost)(void *ptr);
static cudaError_t (*pcudaFuncGetAttributes)(cudaFuncAttributes *attr, const void *func);
static cudaError_t (*pcudaFuncSetCacheConfig)(const void *func, void *cacheConfig);
static cudaError_t (*pcudaGetDevice)(int *device);
static cudaError_t (*pcudaGetErrorString)(void *error);
static cudaError_t (*pcudaGetLastError)(void);
static cudaError_t (*pcudaGetSymbolAddress)(void **devPtr, const char *symbol);
static cudaError_t (*pcudaGetSymbolSize)(size_t *size, const char *symbol);
static cudaError_t (*pcudaGetTextureAlignmentOffset)(size_t *offset, const void *texref);
static cudaError_t (*pcudaGetTextureReference)(const void **texref, const char *symbol);
static cudaError_t (*pcudaGLMapBufferObject)(void **devPtr, GLuint bufObj);
static cudaError_t (*pcudaGLRegisterBufferObject)(GLuint bufObj);
static cudaError_t (*pcudaGLSetBufferObjectMapFlags)(GLuint bufObj, unsigned int flags);
static cudaError_t (*pcudaGLSetGLDevice)(int device);
static cudaError_t (*pcudaGLUnmapBufferObject)(GLuint bufObj);
static cudaError_t (*pcudaGLUnmapBufferObjectAsync)(GLuint bufObj, cudaStream_t stream);
static cudaError_t (*pcudaGLUnregisterBufferObject)(GLuint bufObj);
static cudaError_t (*pcudaGraphicsGLRegisterBuffer)(void **resource, GLuint buffer, unsigned int flags);
static cudaError_t (*pcudaGraphicsGLRegisterImage)(void **resource, GLuint image, GLenum target, unsigned int flags);
static cudaError_t (*pcudaGraphicsMapResources)(int count, void *resources, cudaStream_t stream);
static cudaError_t (*pcudaGraphicsResourceGetMappedPointer)(void **devPtr, size_t *size, void *resource);
static cudaError_t (*pcudaGraphicsResourceSetMapFlags)(void *resource, unsigned int flags);
static cudaError_t (*pcudaGraphicsSubResourceGetMappedArray)(void *array, void *resource, unsigned int arrayIndex, unsigned int mipLevel);
static cudaError_t (*pcudaGraphicsUnmapResources)(int count, void *resources, cudaStream_t stream);
static cudaError_t (*pcudaGraphicsUnregisterResource)(void *resource);
static cudaError_t (*pcudaHostAlloc)(void **pHost, size_t size, unsigned int flags);
static cudaError_t (*pcudaHostGetDevicePointer)(void **pDevice, void *pHost, unsigned int flags);
static cudaError_t (*pcudaHostGetFlags)(unsigned int *pFlags, void *pHost);
static cudaError_t (*pcudaLaunch)(const char *symbol);
static cudaError_t (*pcudaMalloc)(void **devPtr, size_t size);
static cudaError_t (*pcudaMalloc3D)(void *pitchedDevPtr, cudaExtent extent);
static cudaError_t (*pcudaMalloc3DArray)(void* array, const void *desc, cudaExtent extent);
static cudaError_t (*pcudaMallocArray)(void *array, const void *desc, size_t width, size_t height);
static cudaError_t (*pcudaMallocHost)(void **ptr, size_t size);
static cudaError_t (*pcudaMallocPitch)(void **devPtr, size_t *pitch, size_t width, size_t height);
static cudaError_t (*pcudaMemcpy)(void *dst, const void *src, size_t count, cudaMemcpyKind kind);
static cudaError_t (*pcudaMemcpy2D)(void *dst, size_t dpitch, const void *src, size_t spitch, size_t width, size_t height, cudaMemcpyKind kind);
static cudaError_t (*pcudaMemcpy2DArrayToArray)(void *dst, size_t wOffsetDst, size_t hOffsetDst, void *src, size_t wOffsetSrc, size_t hOffsetSrc, size_t width, size_t height, cudaMemcpyKind kind);
static cudaError_t (*pcudaMemcpy2DAsync)(void *dst, size_t dpitch, const void *src, size_t spitch, size_t width, size_t height, cudaMemcpyKind kind, cudaStream_t stream);
static cudaError_t (*pcudaMemcpy2DFromArray)(void *dst, size_t dpitch, void *src, size_t wOffset, size_t hOffset, size_t width, size_t height, cudaMemcpyKind kind);
static cudaError_t (*pcudaMemcpy2DFromArrayAsync)(void *dst, size_t dpitch, void *src, size_t wOffset, size_t hOffset, size_t width, size_t height, cudaMemcpyKind kind, cudaStream_t stream);
static cudaError_t (*pcudaMemcpy2DToArray)(void *dst, size_t wOffset, size_t hOffset, const void *src, size_t spitch, size_t width, size_t height, cudaMemcpyKind kind);
static cudaError_t (*pcudaMemcpy2DToArrayAsync)(void *dst, size_t wOffset, size_t hOffset, const void *src, size_t spitch, size_t width, size_t height, cudaMemcpyKind kind, cudaStream_t stream);
static cudaError_t (*pcudaMemcpy3D)(const cudaMemcpy3DParms* p);
static cudaError_t (*pcudaMemcpy3DAsync)(const cudaMemcpy3DParms* p, cudaStream_t stream);
static cudaError_t (*pcudaMemcpyArrayToArray)(void *dst, size_t wOffsetDst, size_t hOffsetDst, void *src, size_t wOffsetSrc, size_t hOffsetSrc, size_t count, cudaMemcpyKind kind);
static cudaError_t (*pcudaMemcpyAsync)(void *dst, const void *src, size_t count, cudaMemcpyKind kind, cudaStream_t stream);
static cudaError_t (*pcudaMemcpyFromArray)(void *dst, void *src, size_t wOffset, size_t hOffset, size_t count, cudaMemcpyKind kind);
static cudaError_t (*pcudaMemcpyFromArrayAsync)(void *dst, void *src, size_t wOffset, size_t hOffset, size_t count, cudaMemcpyKind kind, cudaStream_t stream);
static cudaError_t (*pcudaMemcpyFromSymbol)(void *dst, const void *symbol, size_t count, size_t offset, cudaMemcpyKind kind);
static cudaError_t (*pcudaMemcpyFromSymbolAsync)(void *dst, const void *symbol, size_t count, size_t offset, cudaMemcpyKind kind, cudaStream_t stream);
static cudaError_t (*pcudaMemcpyToArray)(void *dst, size_t wOffset, size_t hOffset, const void *src, size_t count, cudaMemcpyKind kind);
static cudaError_t (*pcudaMemcpyToArrayAsync)(void *dst, size_t wOffset, size_t hOffset, const void *src, size_t count, cudaMemcpyKind kind, cudaStream_t stream);
static cudaError_t (*pcudaMemcpyToSymbol)(const void *symbol, const void *src, size_t count, size_t offset, cudaMemcpyKind kind);
static cudaError_t (*pcudaMemcpyToSymbolAsync)(const void *symbol, const void *src, size_t count, size_t offset, cudaMemcpyKind kind, cudaStream_t stream);
static cudaError_t (*pcudaMemGetInfo)(size_t *free, size_t *total);
static cudaError_t (*pcudaMemset)(void *devPtr, int value, size_t count);
static cudaError_t (*pcudaMemset2D)(void *devPtr, size_t pitch, int value, size_t width, size_t height);
static cudaError_t (*pcudaMemset3D)(void *pitchedDevPtr, int value, cudaExtent extent);
static cudaError_t (*pcudaSetDevice)(int device);
static cudaError_t (*pcudaSetDeviceFlags)(unsigned int flags);
static cudaError_t (*pcudaSetDoubleForDevice)(double *d);
static cudaError_t (*pcudaSetDoubleForHost)(double *d);
static cudaError_t (*pcudaSetupArgument)(const void *arg, size_t size, size_t offset);
static cudaError_t (*pcudaSetValidDevices)(int *device_arr, int len);
static cudaError_t (*pcudaStreamCreate)(cudaStream_t *stream);
static cudaError_t (*pcudaStreamDestroy)(cudaStream_t stream);
static cudaError_t (*pcudaStreamQuery)(cudaStream_t stream);
static cudaError_t (*pcudaStreamSynchronize)(cudaStream_t stream);
static cudaError_t (*pcudaThreadExit)(void);
static cudaError_t (*pcudaThreadSynchronize)(void);
static cudaError_t (*pcudaUnbindTexture)(const void *texref);
static cudaChannelFormatDesc (*pcudaCreateChannelDesc)( int x, int y, int z, int w, cudaChannelFormatKind f);
static cudaError_t (*p__cudaRegisterFatBinary)(void *fatCubin);
static cudaError_t (*p__cudaRegisterFunction)(void **fatCubinHandle, const char *hostFun, char *deviceFun, const char *deviceName, int thread_limit, uint3 *tid,
                                        uint3 *bid, dim3 *bDim, dim3 *gDim, int *wSize);
static cudaError_t (*p__cudaUnregisterFatBinary)(void *fatCubinHandle);
static cudaError_t (*p__cudaRegisterTexture)(void **fatCubinHandle, const void *hostVar, const void **deviceAddress, const char *deviceName, int dim, int norm, int ext);
static cudaError_t (*p__cudaRegisterSharedVar)(void **fatCubinHandle, void **devicePtr, size_t size, size_t alignment, int storage);
static cudaError_t (*p__cudaRegisterShared)(void **fatCubinHandle, void **devicePtr);
static cudaError_t (*p__cudaMutexOperation)(int lock);
static cudaError_t (*p__cudaSynchronizeThreads)(void **func, void *thread);
static cudaError_t (*p__cudaTextureFetch)(const void *tex, void *index, int integer, void *val);
static cudaError_t (*p__cudaRegisterVar)(void **fatCubinHandle, char *hostVar, char *deviceAddress, const char *deviceName, int ext, int size, int constant, int global);

static void *cudart_handle = NULL;

static BOOL load_functions(void)
{
    if (!(cudart_handle = dlopen("libcudart.so.3", RTLD_NOW)))
    {
        FIXME("Wine cannot find the cuda runtime library\n");
        FIXME("You need CUDA SDK 3.0!\n");
        return FALSE;
    }

    #define LOAD_FUNCPTR(f) if((*(void **)(&p##f) = dlsym(cudart_handle, #f)) == NULL){ERR("Can't find symbol %s\n", #f); return FALSE;}

    LOAD_FUNCPTR(cudaBindTexture);
    LOAD_FUNCPTR(cudaBindTexture2D);
    LOAD_FUNCPTR(cudaBindTextureToArray);
    LOAD_FUNCPTR(cudaChooseDevice);
    LOAD_FUNCPTR(cudaConfigureCall);
    LOAD_FUNCPTR(cudaGetChannelDesc);
    LOAD_FUNCPTR(cudaDriverGetVersion);
    LOAD_FUNCPTR(cudaGetDeviceCount);
    LOAD_FUNCPTR(cudaGetDeviceProperties);
    LOAD_FUNCPTR(cudaRuntimeGetVersion);
    LOAD_FUNCPTR(cudaEventCreate);
    LOAD_FUNCPTR(cudaEventCreateWithFlags);
    LOAD_FUNCPTR(cudaEventDestroy);
    LOAD_FUNCPTR(cudaEventElapsedTime);
    LOAD_FUNCPTR(cudaEventQuery);
    LOAD_FUNCPTR(cudaEventRecord);
    LOAD_FUNCPTR(cudaEventSynchronize);
    LOAD_FUNCPTR(cudaFree);
    LOAD_FUNCPTR(cudaFreeArray);
    LOAD_FUNCPTR(cudaFreeHost);
    LOAD_FUNCPTR(cudaFuncGetAttributes);
    LOAD_FUNCPTR(cudaFuncSetCacheConfig);
    LOAD_FUNCPTR(cudaGetDevice);
    LOAD_FUNCPTR(cudaGetErrorString);
    LOAD_FUNCPTR(cudaGetLastError);
    LOAD_FUNCPTR(cudaGetSymbolAddress);
    LOAD_FUNCPTR(cudaGetSymbolSize);
    LOAD_FUNCPTR(cudaGetTextureAlignmentOffset);
    LOAD_FUNCPTR(cudaGetTextureReference);
    LOAD_FUNCPTR(cudaGLMapBufferObject);
    LOAD_FUNCPTR(cudaGLRegisterBufferObject);
    LOAD_FUNCPTR(cudaGLSetBufferObjectMapFlags);
    LOAD_FUNCPTR(cudaGLSetGLDevice);
    LOAD_FUNCPTR(cudaGLUnmapBufferObject);
    LOAD_FUNCPTR(cudaGLUnmapBufferObjectAsync);
    LOAD_FUNCPTR(cudaGLUnregisterBufferObject);
    LOAD_FUNCPTR(cudaGraphicsGLRegisterBuffer);
    LOAD_FUNCPTR(cudaGraphicsGLRegisterImage);
    LOAD_FUNCPTR(cudaGraphicsMapResources);
    LOAD_FUNCPTR(cudaGraphicsResourceGetMappedPointer);
    LOAD_FUNCPTR(cudaGraphicsResourceSetMapFlags);
    LOAD_FUNCPTR(cudaGraphicsSubResourceGetMappedArray);
    LOAD_FUNCPTR(cudaGraphicsUnmapResources);
    LOAD_FUNCPTR(cudaGraphicsUnregisterResource);
    LOAD_FUNCPTR(cudaHostAlloc);
    LOAD_FUNCPTR(cudaHostGetDevicePointer);
    LOAD_FUNCPTR(cudaHostGetFlags);
    LOAD_FUNCPTR(cudaLaunch);
    LOAD_FUNCPTR(cudaMalloc);
    LOAD_FUNCPTR(cudaMalloc3D);
    LOAD_FUNCPTR(cudaMalloc3DArray);
    LOAD_FUNCPTR(cudaMallocArray);
    LOAD_FUNCPTR(cudaMallocHost);
    LOAD_FUNCPTR(cudaMallocPitch);
    LOAD_FUNCPTR(cudaMemcpy);
    LOAD_FUNCPTR(cudaMemcpy2D);
    LOAD_FUNCPTR(cudaMemcpy2DArrayToArray);
    LOAD_FUNCPTR(cudaMemcpy2DAsync);
    LOAD_FUNCPTR(cudaMemcpy2DFromArray);
    LOAD_FUNCPTR(cudaMemcpy2DFromArrayAsync);
    LOAD_FUNCPTR(cudaMemcpy2DToArray);
    LOAD_FUNCPTR(cudaMemcpy2DToArrayAsync);
    LOAD_FUNCPTR(cudaMemcpy3D);
    LOAD_FUNCPTR(cudaMemcpy3DAsync);
    LOAD_FUNCPTR(cudaMemcpyArrayToArray);
    LOAD_FUNCPTR(cudaMemcpyAsync);
    LOAD_FUNCPTR(cudaMemcpyFromArray);
    LOAD_FUNCPTR(cudaMemcpyFromArrayAsync);
    LOAD_FUNCPTR(cudaMemcpyFromSymbol);
    LOAD_FUNCPTR(cudaMemcpyFromSymbolAsync);
    LOAD_FUNCPTR(cudaMemcpyToArray);
    LOAD_FUNCPTR(cudaMemcpyToArrayAsync);
    LOAD_FUNCPTR(cudaMemcpyToSymbol);
    LOAD_FUNCPTR(cudaMemcpyToSymbolAsync);
    LOAD_FUNCPTR(cudaMemGetInfo);
    LOAD_FUNCPTR(cudaMemset);
    LOAD_FUNCPTR(cudaMemset2D);
    LOAD_FUNCPTR(cudaMemset3D);
    LOAD_FUNCPTR(cudaSetDevice);
    LOAD_FUNCPTR(cudaSetDeviceFlags);
    LOAD_FUNCPTR(cudaSetDoubleForDevice);
    LOAD_FUNCPTR(cudaSetDoubleForHost);
    LOAD_FUNCPTR(cudaSetupArgument);
    LOAD_FUNCPTR(cudaSetValidDevices);
    LOAD_FUNCPTR(cudaStreamCreate);
    LOAD_FUNCPTR(cudaStreamDestroy);
    LOAD_FUNCPTR(cudaStreamQuery);
    LOAD_FUNCPTR(cudaStreamSynchronize);
    LOAD_FUNCPTR(cudaThreadExit);
    LOAD_FUNCPTR(cudaThreadSynchronize);
    LOAD_FUNCPTR(cudaUnbindTexture);
    LOAD_FUNCPTR(cudaCreateChannelDesc);
    LOAD_FUNCPTR(__cudaRegisterFatBinary);
    LOAD_FUNCPTR(__cudaRegisterFunction);
    LOAD_FUNCPTR(__cudaUnregisterFatBinary);
    LOAD_FUNCPTR(__cudaRegisterTexture);
    LOAD_FUNCPTR(__cudaRegisterSharedVar);
    LOAD_FUNCPTR(__cudaRegisterShared);
    LOAD_FUNCPTR(__cudaMutexOperation);
    LOAD_FUNCPTR(__cudaSynchronizeThreads);
    LOAD_FUNCPTR(__cudaTextureFetch);
    LOAD_FUNCPTR(__cudaRegisterVar);

    #undef LOAD_FUNCPTR
    return TRUE;
}

cudaError_t WINAPI wine_cudaBindTexture(size_t *offset, void *texref, const void *devPtr, const void *desc, size_t size)
{
    TRACE("(%p, %p, %p, %p, %zu)\n", offset, texref, devPtr, desc, size);
    return pcudaBindTexture(offset, texref, devPtr, desc, size);
}

cudaError_t WINAPI wine_cudaBindTexture2D(size_t *offset, const void *texref, const void *devPtr, const void *desc, size_t width, size_t height, size_t pitch)
{
    TRACE("(%p, %p, %p, %p, %zu, %zu, %zu)\n", offset, texref, devPtr, desc, width, height, pitch);
    return pcudaBindTexture2D(offset, texref, devPtr, desc, width, height, pitch);
}

cudaError_t WINAPI wine_cudaBindTextureToArray(const void *texref, const void *array, const void *desc)
{
    TRACE("(%p, %p, %p)\n", texref, array, desc);
    return pcudaBindTextureToArray(texref, array, desc);
}

cudaError_t WINAPI wine_cudaChooseDevice(int *device, const void *prop)
{
    TRACE("(%p, %p)\n", device, prop);
    return pcudaChooseDevice(device, prop);
}

cudaError_t WINAPI wine_cudaConfigureCall(dim3 gridDim, dim3 blockDim, size_t sharedMem, cudaStream_t stream)
{
    TRACE("(%p, %p, %zu, %p)\n", (void*)&gridDim, (void*)&blockDim, sharedMem, stream);
    return pcudaConfigureCall(gridDim, blockDim, sharedMem, stream);
}

cudaError_t WINAPI wine_cudaGetChannelDesc(void *desc, const void *array)
{
    TRACE("(%p, %p)\n", desc, array);
    return pcudaGetChannelDesc(desc, array);
}

cudaError_t WINAPI wine_cudaDriverGetVersion(int *driverVersion)
{
    TRACE("(%p)\n", driverVersion);
    return pcudaDriverGetVersion(driverVersion);
}

cudaError_t WINAPI wine_cudaGetDeviceCount(int *count)
{
    TRACE("(%p)\n", count);
    return pcudaGetDeviceCount(count);
}

cudaError_t WINAPI wine_cudaGetDeviceProperties(void *prop, int device)
{
    TRACE("(%p, %d)\n", prop, device);
    return pcudaGetDeviceProperties(prop, device);
}

cudaError_t WINAPI wine_cudaRuntimeGetVersion(int *runtimeVersion)
{
    TRACE("(%p)\n", runtimeVersion);
    return pcudaRuntimeGetVersion(runtimeVersion);
}

cudaError_t WINAPI wine_cudaEventCreate(void *event)
{
    TRACE("(%p)\n", event);
    return pcudaEventCreate(event);
}

cudaError_t WINAPI wine_cudaEventCreateWithFlags(void *event, unsigned int flag)
{
    TRACE("(%p, %u)\n", event, flag);
    return pcudaEventCreateWithFlags(event, flag);
}

cudaError_t WINAPI wine_cudaEventDestroy(void *event)
{
    TRACE("(%p)\n", event);
    return pcudaEventDestroy(event);
}

cudaError_t WINAPI wine_cudaEventElapsedTime(float *ms, void *start, void *end)
{
    TRACE("(%p, %p, %p)\n", ms, start, end);
    return pcudaEventElapsedTime(ms, start, end);
}

cudaError_t WINAPI wine_cudaEventQuery(void *event)
{
    TRACE("(%p)\n", event);
    return pcudaEventQuery(event);
}

cudaError_t WINAPI wine_cudaEventRecord(void* event, cudaStream_t stream)
{
    TRACE("(%p, %p)\n", event, stream);
    return pcudaEventRecord(event, stream);
}

cudaError_t WINAPI wine_cudaEventSynchronize(void *event)
{
    TRACE("(%p)\n", event);
    return pcudaEventSynchronize(event);
}

cudaError_t WINAPI wine_cudaFree(void *devPtr)
{
    TRACE("(%p)\n", devPtr);
    return pcudaFree(devPtr);
}

cudaError_t WINAPI wine_cudaFreeArray(void *array)
{
    TRACE("(%p)\n", array);
    return pcudaFreeArray(array);
}

cudaError_t WINAPI wine_cudaFreeHost(void *ptr)
{
    TRACE("(%p)\n", ptr);
    return pcudaFreeHost(ptr);
}

cudaError_t WINAPI wine_cudaFuncGetAttributes(cudaFuncAttributes *attr, const void *func)
{
    TRACE("(%p, %p)\n", attr, func);
    return pcudaFuncGetAttributes(attr, func);
}

cudaError_t WINAPI wine_cudaFuncSetCacheConfig(const void *func, void *cacheConfig)
{
    TRACE("(%p, %p)\n", func, cacheConfig);
    return pcudaFuncSetCacheConfig(func, cacheConfig);
}

cudaError_t WINAPI wine_cudaGetDevice(int *device)
{
    TRACE("(%p)\n", device);
    return pcudaGetDevice(device);
}

cudaError_t WINAPI wine_cudaGetErrorString(void *error)
{
    TRACE("(%p)\n", error);
    return pcudaGetErrorString(error);
}

cudaError_t WINAPI wine_cudaGetLastError(void)
{
    TRACE("()\n");
    return pcudaGetLastError();
}

cudaError_t WINAPI wine_cudaGetSymbolAddress(void **devPtr, const char *symbol)
{
    TRACE("(%p, %s)\n", devPtr, symbol);
    return pcudaGetSymbolAddress(devPtr, symbol);
}

cudaError_t WINAPI wine_cudaGetSymbolSize(size_t *size, const char *symbol)
{
    TRACE("(%p, %s)\n", size, symbol);
    return pcudaGetSymbolSize(size, symbol);
}

cudaError_t WINAPI wine_cudaGetTextureAlignmentOffset(size_t *offset, const void *texref)
{
    TRACE("(%p, %p)\n", offset, texref);
    return pcudaGetTextureAlignmentOffset(offset, texref);
}

cudaError_t WINAPI wine_cudaGetTextureReference(const void **texref, const char *symbol)
{
    TRACE("(%p, %s)\n", texref, symbol);
    return pcudaGetTextureReference(texref, symbol);
}

cudaError_t WINAPI wine_cudaGLMapBufferObject(void** devPtr, GLuint bufObj)
{
    TRACE("(%p, %u)\n", devPtr, bufObj);
    return pcudaGLMapBufferObject(devPtr, bufObj);
}

cudaError_t WINAPI wine_cudaGLRegisterBufferObject(GLuint bufObj)
{
    TRACE("(%u)\n", bufObj);
    return pcudaGLRegisterBufferObject(bufObj);
}

cudaError_t WINAPI wine_cudaGLSetBufferObjectMapFlags(GLuint bufObj, unsigned int flags)
{
    TRACE("(%u, %u)\n", bufObj, flags);
    return pcudaGLSetBufferObjectMapFlags(bufObj, flags);
}

cudaError_t WINAPI wine_cudaGLSetGLDevice(int device)
{
    TRACE("(%d)\n", device);
    return pcudaGLSetGLDevice(device);
}

cudaError_t WINAPI wine_cudaGLUnmapBufferObject(GLuint bufObj)
{
    TRACE("(%u)\n", bufObj);
    return pcudaGLUnmapBufferObject(bufObj);
}

cudaError_t WINAPI wine_cudaGLUnmapBufferObjectAsync(GLuint bufObj, cudaStream_t stream)
{
    TRACE("(%u, %p)\n", bufObj, stream);
    return pcudaGLUnmapBufferObjectAsync(bufObj, stream);
}

cudaError_t WINAPI wine_cudaGLUnregisterBufferObject(GLuint bufObj)
{
    TRACE("(%u)\n", bufObj);
    return pcudaGLUnregisterBufferObject(bufObj);
}

cudaError_t WINAPI wine_cudaGraphicsGLRegisterBuffer(void **resource, GLuint buffer, unsigned int flags)
{
    TRACE("(%p, %u, %u)\n", resource, buffer, flags);
    return pcudaGraphicsGLRegisterBuffer(resource, buffer, flags);
}

cudaError_t WINAPI wine_cudaGraphicsGLRegisterImage(void** resource, GLuint image, GLenum target, unsigned int flags)
{
    TRACE("(%p, %u, %u, %u)\n", resource, image, target, flags);
    return pcudaGraphicsGLRegisterImage(resource, image, target, flags);
}

cudaError_t WINAPI wine_cudaGraphicsMapResources(int count, void *resources, cudaStream_t stream)
{
    TRACE("(%d, %p, %p)\n", count, resources, stream);
    return pcudaGraphicsMapResources(count, resources, stream);
}

cudaError_t WINAPI wine_cudaGraphicsResourceGetMappedPointer(void **devPtr, size_t *size, void *resource)
{
    TRACE("(%p, %p, %p)\n", devPtr, size, resource);
    return pcudaGraphicsResourceGetMappedPointer(devPtr, size, resource);
}

cudaError_t WINAPI wine_cudaGraphicsResourceSetMapFlags(void *resource, unsigned int flags)
{
    TRACE("(%p, %u)\n", resource, flags);
    return pcudaGraphicsResourceSetMapFlags(resource, flags);
}

cudaError_t WINAPI wine_cudaGraphicsSubResourceGetMappedArray(void *array, void *resource, unsigned int arrayIndex, unsigned int mipLevel)
{
    TRACE("(%p, %p, %u, %u)\n", array, resource, arrayIndex, mipLevel);
    return pcudaGraphicsSubResourceGetMappedArray(array, resource, arrayIndex, mipLevel);
}

cudaError_t WINAPI wine_cudaGraphicsUnmapResources(int count, void *resources, cudaStream_t stream)
{
    TRACE("(%d, %p, %p)\n", count, resources, stream);
    return pcudaGraphicsUnmapResources(count, resources, stream);
}

cudaError_t WINAPI wine_cudaGraphicsUnregisterResource(void *resource)
{
    TRACE("(%p)\n", resource);
    return pcudaGraphicsUnregisterResource(resource);
}

cudaError_t WINAPI wine_cudaHostAlloc(void **pHost, size_t size, unsigned int flags)
{
    TRACE("(%p, %zu, %u)\n", pHost, size, flags);
    return pcudaHostAlloc(pHost, size, flags);
}

cudaError_t WINAPI wine_cudaHostGetDevicePointer(void **pDevice, void *pHost, unsigned int flags)
{
    TRACE("(%p, %p, %u)\n", pDevice, pHost, flags);
    return pcudaHostGetDevicePointer(pDevice, pHost, flags);
}

cudaError_t WINAPI wine_cudaHostGetFlags(unsigned int *pFlags, void *pHost)
{
    TRACE("(%p, %p)\n", pFlags, pHost);
    return pcudaHostGetFlags(pFlags, pHost);
}

cudaError_t WINAPI wine_cudaLaunch(const char *symbol)
{
    TRACE("(%p)\n", symbol);
    return pcudaLaunch(symbol);
}

cudaError_t WINAPI wine_cudaMalloc(void **devPtr, size_t size)
{
    TRACE("(%p, %zu)\n", devPtr, size);
    return pcudaMalloc(devPtr, size);
}

cudaError_t WINAPI wine_cudaMalloc3D(void *pitchedDevPtr, cudaExtent extent)
{
    TRACE("(%p, %p)\n", pitchedDevPtr, (void*)&extent);
    return pcudaMalloc3D(pitchedDevPtr, extent);
}

cudaError_t WINAPI wine_cudaMalloc3DArray(void* array, const void *desc, cudaExtent extent)
{
    TRACE("(%p, %p, %p)\n", array, desc, (void*)&extent);
    return pcudaMalloc3DArray(array, desc, extent);
}

cudaError_t WINAPI wine_cudaMallocArray(void *array, const void *desc, size_t width, size_t height)
{
    TRACE("(%p, %p, %zu, %zu)\n", array, desc, width, height);
    return pcudaMallocArray(array, desc, width, height);
}

cudaError_t WINAPI wine_cudaMallocHost(void **ptr, size_t size)
{
    TRACE("(%p, %zu)\n", ptr, size);
    return pcudaMallocHost(ptr, size);
}

cudaError_t WINAPI wine_cudaMallocPitch(void **devPtr, size_t *pitch, size_t width, size_t height)
{
    TRACE("(%p, %p, %zu, %zu)\n", devPtr, pitch, width, height);
    return pcudaMallocPitch(devPtr, pitch, width, height);
}

cudaError_t WINAPI wine_cudaMemcpy(void *dst, const void *src, size_t count, cudaMemcpyKind kind)
{
    TRACE("(%p, %p, %zu, %d)\n", dst, src, count, kind);
    return pcudaMemcpy(dst, src, count, kind);
}

cudaError_t WINAPI wine_cudaMemcpy2D(void *dst, size_t dpitch, const void *src, size_t spitch, size_t width, size_t height, cudaMemcpyKind kind)
{
    TRACE("(%p, %zu, %p, %zu, %zu, %zu, %d)\n", dst, dpitch, src, spitch, width, height, kind);
    return pcudaMemcpy2D(dst, dpitch, src, spitch, width, height, kind);
}

cudaError_t WINAPI wine_cudaMemcpy2DArrayToArray(void *dst, size_t wOffsetDst, size_t hOffsetDst, void *src, size_t wOffsetSrc, size_t hOffsetSrc, size_t width, size_t height, cudaMemcpyKind kind)
{
    TRACE("(%p, %zu, %zu, %p, %zu, %zu, %zu, %zu, %d)\n", dst, wOffsetDst, hOffsetDst, src, wOffsetSrc, hOffsetSrc, width, height, kind);
    return pcudaMemcpy2DArrayToArray(dst, wOffsetDst, hOffsetDst, src, wOffsetSrc, hOffsetSrc, width, height, kind);
}

cudaError_t WINAPI wine_cudaMemcpy2DAsync(void *dst, size_t dpitch, const void *src, size_t spitch, size_t width, size_t height, cudaMemcpyKind kind, cudaStream_t stream)
{
    TRACE("(%p, %zu, %p, %zu, %zu, %zu, %d, %p)\n", dst, dpitch, src, spitch, width, height, kind, stream);
    return pcudaMemcpy2DAsync(dst, dpitch, src, spitch, width, height, kind, stream);
}

cudaError_t WINAPI wine_cudaMemcpy2DFromArray(void *dst, size_t dpitch, void *src, size_t wOffset, size_t hOffset, size_t width, size_t height, cudaMemcpyKind kind)
{
    TRACE("(%p, %zu, %p, %zu, %zu, %zu, %zu, %d)\n", dst, dpitch, src, wOffset, hOffset, width, height, kind);
    return pcudaMemcpy2DFromArray(dst, dpitch, src, wOffset, hOffset, width, height, kind);
}

cudaError_t WINAPI wine_cudaMemcpy2DFromArrayAsync(void *dst, size_t dpitch, void *src, size_t wOffset, size_t hOffset, size_t width, size_t height, cudaMemcpyKind kind, cudaStream_t stream)
{
    TRACE("(%p, %zu, %p, %zu, %zu, %zu, %zu, %d, %p)\n", dst, dpitch, src, wOffset, hOffset, width, height, kind, stream);
    return pcudaMemcpy2DFromArrayAsync(dst, dpitch, src, wOffset, hOffset, width, height, kind, stream);
}

cudaError_t WINAPI wine_cudaMemcpy2DToArray(void *dst, size_t wOffset, size_t hOffset, const void *src, size_t spitch, size_t width, size_t height, cudaMemcpyKind kind)
{
    TRACE("(%p, %zu, %zu, %p, %zu, %zu, %zu, %d)\n", dst, wOffset, hOffset, src, spitch, width, height, kind);
    return pcudaMemcpy2DToArray(dst, wOffset, hOffset, src, spitch, width, height, kind);
}

cudaError_t WINAPI wine_cudaMemcpy2DToArrayAsync(void *dst, size_t wOffset, size_t hOffset, const void *src, size_t spitch, size_t width, size_t height, cudaMemcpyKind kind, cudaStream_t stream)
{
    TRACE("(%p, %zu, %zu, %p, %zu, %zu, %zu, %d, %p)\n", dst, wOffset, hOffset, src, spitch, width, height, kind, stream);
    return pcudaMemcpy2DToArrayAsync(dst, wOffset, hOffset, src, spitch, width, height, kind, stream);
}

cudaError_t WINAPI wine_cudaMemcpy3D(const cudaMemcpy3DParms* p)
{
    TRACE("(%p)\n", p);
    return pcudaMemcpy3D(p);
}

cudaError_t WINAPI wine_cudaMemcpy3DAsync(const cudaMemcpy3DParms* p, cudaStream_t stream)
{
    TRACE("(%p, %p)\n", p, stream);
    return pcudaMemcpy3DAsync(p, stream);
}

cudaError_t WINAPI wine_cudaMemcpyArrayToArray(void *dst, size_t wOffsetDst, size_t hOffsetDst, void *src, size_t wOffsetSrc, size_t hOffsetSrc, size_t count, cudaMemcpyKind kind)
{
    TRACE("(%p, %zu, %zu, %p, %zu, %zu, %zu, %d)\n", dst, wOffsetDst, hOffsetDst, src, wOffsetSrc, hOffsetSrc, count, kind);
    return pcudaMemcpyArrayToArray(dst, wOffsetDst, hOffsetDst, src, wOffsetSrc, hOffsetSrc, count, kind);
}

cudaError_t WINAPI wine_cudaMemcpyAsync(void *dst, const void *src, size_t count, cudaMemcpyKind kind, cudaStream_t stream)
{
    TRACE("(%p, %p, %zu, %d, %p)\n", dst, src, count, kind, stream);
    return pcudaMemcpyAsync(dst, src, count, kind, stream);
}

cudaError_t WINAPI wine_cudaMemcpyFromArray(void *dst, void *src, size_t wOffset, size_t hOffset, size_t count, cudaMemcpyKind kind)
{
    TRACE("(%p, %p, %zu, %zu, %zu, %d)\n", dst, src, wOffset, hOffset, count, kind);
    return pcudaMemcpyFromArray(dst, src, wOffset, hOffset, count, kind);
}

cudaError_t WINAPI wine_cudaMemcpyFromArrayAsync(void *dst, void *src, size_t wOffset, size_t hOffset, size_t count, cudaMemcpyKind kind, cudaStream_t stream)
{
    TRACE("(%p, %p, %zu, %zu, %zu, %d, %p)\n", dst, src, wOffset, hOffset, count, kind, stream);
    return pcudaMemcpyFromArrayAsync(dst, src, wOffset, hOffset, count, kind, stream);
}

cudaError_t WINAPI wine_cudaMemcpyFromSymbol(void *dst, const void *symbol, size_t count, size_t offset, cudaMemcpyKind kind)
{
    TRACE("(%p, %p, %zu, %zu, %d)\n", dst, symbol, count, offset, kind);
    return pcudaMemcpyFromSymbol(dst, symbol, count, offset, kind);
}

cudaError_t WINAPI wine_cudaMemcpyFromSymbolAsync(void *dst, const void *symbol, size_t count, size_t offset, cudaMemcpyKind kind, cudaStream_t stream)
{
    TRACE("(%p, %p, %zu, %zu, %d, %p)\n", dst, symbol, count, offset, kind, stream);
    return pcudaMemcpyFromSymbolAsync(dst, symbol, count, offset, kind, stream);
}

cudaError_t WINAPI wine_cudaMemcpyToArray(void *dst, size_t wOffset, size_t hOffset, const void *src, size_t count, cudaMemcpyKind kind)
{
    TRACE("(%p, %zu, %zu, %p, %zu, %d)\n", dst, wOffset, hOffset, src, count, kind);
    return pcudaMemcpyToArray(dst, wOffset, hOffset, src, count, kind);
}

cudaError_t WINAPI wine_cudaMemcpyToArrayAsync(void *dst, size_t wOffset, size_t hOffset, const void *src, size_t count, cudaMemcpyKind kind, cudaStream_t stream)
{
    TRACE("(%p, %zu, %zu, %p, %zu, %d, %p)\n", dst, wOffset, hOffset, src, count, kind, stream);
    return pcudaMemcpyToArrayAsync(dst, wOffset, hOffset, src, count, kind, stream);
}

cudaError_t WINAPI wine_cudaMemcpyToSymbol(const void *symbol, const void *src, size_t count, size_t offset, cudaMemcpyKind kind)
{
    TRACE("(%p, %p, %zu, %zu, %d)\n", symbol, src, count, offset, kind);
    return pcudaMemcpyToSymbol(symbol, src, count, offset, kind);
}

cudaError_t WINAPI wine_cudaMemcpyToSymbolAsync(const void *symbol, const void *src, size_t count, size_t offset, cudaMemcpyKind kind, cudaStream_t stream)
{
    TRACE("(%p, %p, %zu, %zu, %d, %p)\n", symbol, src, count, offset, kind, stream);
    return pcudaMemcpyToSymbolAsync(symbol, src, count, offset, kind, stream);
}

cudaError_t WINAPI wine_cudaMemGetInfo(size_t *free, size_t *total)
{
    TRACE("(%p, %p)\n", free, total);
    return pcudaMemGetInfo(free, total);
}

cudaError_t WINAPI wine_cudaMemset(void *devPtr, int value, size_t count)
{
    TRACE("(%p, %d, %zu)\n", devPtr, value, count);
    return pcudaMemset(devPtr, value, count);
}

cudaError_t WINAPI wine_cudaMemset2D(void *devPtr, size_t pitch, int value, size_t width, size_t height)
{
    TRACE("(%p, %zu, %d, %zu, %zu)\n", devPtr, pitch, value, width, height);
    return pcudaMemset2D(devPtr, pitch, value, width, height);
}

cudaError_t WINAPI wine_cudaMemset3D(void *pitchedDevPtr, int value, cudaExtent extent)
{
    TRACE("(%p, %d, %p)\n", pitchedDevPtr, value, (void*)&extent);
    return pcudaMemset3D(pitchedDevPtr, value, extent);
}

cudaError_t WINAPI wine_cudaSetDevice(int device)
{
    TRACE("(%d)\n", device);
    return pcudaSetDevice(device);
}

cudaError_t WINAPI wine_cudaSetDeviceFlags(unsigned int flags)
{
    TRACE("(%u)\n", flags);
    return pcudaSetDeviceFlags(flags);
}

cudaError_t WINAPI wine_cudaSetDoubleForDevice(double *d)
{
    TRACE("(%p)\n", d);
    return pcudaSetDoubleForDevice(d);
}

cudaError_t WINAPI wine_cudaSetDoubleForHost(double *d)
{
    TRACE("(%p)\n", d);
    return pcudaSetDoubleForHost(d);
}

cudaError_t WINAPI wine_cudaSetupArgument(const void *arg, size_t size, size_t offset)
{
    TRACE("(%p, %zu, %zu)\n", arg, size, offset);
    return pcudaSetupArgument(arg, size, offset);
}

cudaError_t WINAPI wine_cudaSetValidDevices(int *device_arr, int len)
{
    TRACE("(%p, %d)\n", device_arr, len);
    return pcudaSetValidDevices(device_arr, len);
}

cudaError_t WINAPI wine_cudaStreamCreate(cudaStream_t *stream)
{
    TRACE("(%p)\n", stream);
    return pcudaStreamCreate(stream);
}

cudaError_t WINAPI wine_cudaStreamDestroy(cudaStream_t stream)
{
    TRACE("(%p)\n", stream);
    return pcudaStreamDestroy(stream);
}

cudaError_t WINAPI wine_cudaStreamQuery(cudaStream_t stream)
{
    TRACE("(%p)\n", stream);
    return pcudaStreamQuery(stream);
}

cudaError_t WINAPI wine_cudaStreamSynchronize(cudaStream_t stream)
{
    TRACE("(%p)\n", stream);
    return pcudaStreamSynchronize(stream);
}

cudaError_t WINAPI wine_cudaThreadExit(void)
{
    TRACE("()\n");
    return pcudaThreadExit();
}

cudaError_t WINAPI wine_cudaThreadSynchronize(void)
{
    TRACE("()\n");
    return pcudaThreadSynchronize();
}

cudaError_t WINAPI wine_cudaUnbindTexture(const void *texref)
{
    TRACE("(%p)\n", texref);
    return pcudaUnbindTexture(texref);
}

cudaChannelFormatDesc WINAPI wine_cudaCreateChannelDesc(int x, int y, int z, int w, cudaChannelFormatKind f)
{
    TRACE("(%d, %d, %d, %d, %p)\n", x, y, z, w, (void*)&f);
    return pcudaCreateChannelDesc(x, y, z, w, f);
}

cudaError_t WINAPI wine___cudaRegisterFatBinary(void *fatCubin)
{
    TRACE("(%p)\n", fatCubin);
    return p__cudaRegisterFatBinary(fatCubin);
}

cudaError_t WINAPI wine___cudaRegisterFunction(void **fatCubinHandle, const char *hostFun, char *deviceFun, const char *deviceName, int thread_limit, uint3 *tid, uint3 *bid,
                                         dim3 *bDim, dim3 *gDim, int *wSize)
{
    TRACE("(%p, %p, %s, %s, %d, %p, %p, %p, %p, %p)\n", fatCubinHandle, hostFun, deviceFun, deviceName, thread_limit, tid, bid, bDim, gDim, wSize);
    return p__cudaRegisterFunction(fatCubinHandle, hostFun, deviceFun, deviceName, thread_limit, tid, bid, bDim, gDim, wSize);
}

cudaError_t WINAPI wine___cudaUnregisterFatBinary(void *fatCubinHandle)
{
    TRACE("(%p)\n", fatCubinHandle);
    return p__cudaUnregisterFatBinary(fatCubinHandle);
}

cudaError_t WINAPI wine___cudaRegisterTexture(void **fatCubinHandle, const void *hostVar, const void **deviceAddress, const char *deviceName, int dim, int norm, int ext)
{
    TRACE("(%p, %p, %p, %s, %d, %d, %d)\n", fatCubinHandle, hostVar, deviceAddress, deviceName, dim, norm, ext);
    return p__cudaRegisterTexture(fatCubinHandle, hostVar, deviceAddress, deviceName, dim, norm, ext);
}

cudaError_t WINAPI wine___cudaRegisterSharedVar(void **fatCubinHandle, void **devicePtr, size_t size, size_t alignment, int storage)
{
    TRACE("(%p, %p, %zu, %zu, %d)\n", fatCubinHandle, devicePtr, size, alignment, storage);
    return p__cudaRegisterSharedVar(fatCubinHandle, devicePtr, size, alignment, storage);
}

cudaError_t WINAPI wine___cudaRegisterShared(void **fatCubinHandle, void **devicePtr)
{
    TRACE("(%p, %p)\n", fatCubinHandle, devicePtr);
    return p__cudaRegisterShared(fatCubinHandle, devicePtr);
}

cudaError_t WINAPI wine___cudaMutexOperation(int lock)
{
    TRACE("(%d)\n", lock);
    return p__cudaMutexOperation(lock);
}

cudaError_t WINAPI wine___cudaSynchronizeThreads(void **func, void *thread)
{
    TRACE("(%p, %p)\n", func, thread);
    return p__cudaSynchronizeThreads(func, thread);
}

cudaError_t WINAPI wine___cudaTextureFetch(const void *tex, void *index, int integer, void *val)
{
    TRACE("(%p, %p, %d, %p)\n", tex, index, integer, val);
    return p__cudaTextureFetch(tex, index, integer, val);
}

cudaError_t WINAPI wine___cudaRegisterVar(void **fatCubinHandle, char *hostVar, char *deviceAddress, const char *deviceName, int ext, int size, int constant, int global)
{
    TRACE("(%p, %s, %s, %s, %d, %d, %d, %d)\n", fatCubinHandle, hostVar, deviceAddress, deviceName, ext, size, constant, global);
    return p__cudaRegisterVar(fatCubinHandle, hostVar, deviceAddress, deviceName, ext, size, constant, global);
}

BOOL WINAPI DllMain(HINSTANCE instance, DWORD reason, LPVOID reserved)
{
    TRACE("(%p, %u, %p)\n", instance, reason, reserved);

    switch (reason)
    {
        case DLL_PROCESS_ATTACH:
            if (!load_functions()) return FALSE;
            break;
            case DLL_PROCESS_DETACH:
            if (reserved) break;
            if (cudart_handle) dlclose(cudart_handle);
            break;
        case DLL_THREAD_ATTACH:
            break;
        case DLL_THREAD_DETACH:
            break;
    }

    return TRUE;
}
