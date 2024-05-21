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

#ifdef HAVE_PTHREAD_H
#include <pthread.h>
#endif

#include "windef.h"
#include "winbase.h"
#include "wine/debug.h"
#include "wine/list.h"
#include "cufft.h"

WINE_DEFAULT_DEBUG_CHANNEL(nvcuda);

static cufftResult (*pcufftCreate)(void* handle);
static cufftResult (*pcufftDestroy)(void* plan);
static cufftResult (*pcufftEstimate1d)(int nx, void* type, int batch, size_t *workSize);
static cufftResult (*pcufftEstimate2d)(int nx, int ny, void* type, size_t *workSize);
static cufftResult (*pcufftEstimate3d)(int nx, int ny, int nz, void* type, size_t *workSize);
static cufftResult (*pcufftEstimateMany)(int rank, int *n, int *inembed, int istride, int idist, int *onembed, int ostride, int odist, void* type, int batch, size_t *workSize);
static cufftResult (*pcufftExecC2C)(void* plan, void* idata, void* odata, int direction);
static cufftResult (*pcufftExecR2C)(void* plan, void* idata, void* odata);
static cufftResult (*pcufftExecC2R)(void* plan, void* idata, void* odata);
static cufftResult (*pcufftExecZ2Z)(void* plan, void* idata, void* odata, int direction);
static cufftResult (*pcufftExecD2Z)(void* plan, void* idata, void* odata);
static cufftResult (*pcufftExecZ2D)(void* plan, void* idata, void* odata);
static cufftResult (*pcufftGetPlanPropertyInt64)(void* plan, void* property, long long int* returnPtrValue);
static cufftResult (*pcufftGetProperty)(void* type, int *value);
static cufftResult (*pcufftGetSize)(void* handle, size_t *workSize);
static cufftResult (*pcufftGetSize1d)(void* handle, int nx, void* type, int batch, size_t *workSize);
static cufftResult (*pcufftGetSize2d)(void* handle, int nx, int ny, void* type, int batch, size_t *workSize);
static cufftResult (*pcufftGetSize3d)(void* handle, int nx, int ny, int nz, void* type, int batch, size_t *workSize);
static cufftResult (*pcufftGetSizeMany)(void* handle, int rank, int *n, int *inembed, int istride, int idist, int *onembed, int ostride, int odist, void* type, int batch, size_t *workArea);
static cufftResult (*pcufftGetSizeMany64)(void* plan, int rank, long long int *n, long long int *inembed, long long int istride, long long int idist,
                                        long long int *onembed, long long int ostride, long long int odist, void* type, long long int batch, size_t *workSize);
static cufftResult (*pcufftGetVersion)(int *version);
static cufftResult (*pcufftMakePlan1d)(void* plan, int nx, void* type, int batch, size_t *workSize);
static cufftResult (*pcufftMakePlan2d)(void* plan, int nx, int ny, void* type, size_t *workSize);
static cufftResult (*pcufftMakePlan3d)(void* plan, int nx, int ny, int nz, void* type, size_t *workSize);
static cufftResult (*pcufftMakePlanMany)(void* plan, int rank, int *n, int *inembed, int istride, int idist, int *onembed, int ostride, int odist, void* type, int batch, size_t *workSize);
static cufftResult (*pcufftMakePlanMany64)(void* plan, int rank, long long int *n, long long int *inembed, long long int istride, long long int idist, long long int *onembed,
                                         long long int ostride, long long int odist, void* type, long long int batch, size_t * workSize);
static cufftResult (*pcufftPlan1d)(void* plan, int nx, void* type, int batch);
static cufftResult (*pcufftPlan2d)(void* plan, int nx, int ny, void* type);
static cufftResult (*pcufftPlan3d)(void* plan, int nx, int ny, int nz, void* type);
static cufftResult (*pcufftPlanMany)(void* plan, int rank, int *n, int *inembed, int istride, int idist, int *onembed, int ostride, int odist, void* type, int batch);
static cufftResult (*pcufftResetPlanProperty)(void* plan, void* property);
static cufftResult (*pcufftSetAutoAllocation)(void* plan, int autoAllocate);
static cufftResult (*pcufftSetPlanPropertyInt64)(void* plan, void* property, const long long int inputValueInt);
static cufftResult (*pcufftSetStream)(void* plan, void* stream);
static cufftResult (*pcufftSetWorkArea)(void* plan, void *workArea);
static cufftResult (*pcufftXtClearCallback)(void* plan, void* cbType);
static cufftResult (*pcufftXtExec)(void* plan, void *input, void *output, int direction);
static cufftResult (*pcufftXtExecDescriptor)(void* plan, void* input, void* output, int direction);
static cufftResult (*pcufftXtExecDescriptorC2C)(void* plan, void* input, void* output, int direction);
static cufftResult (*pcufftXtExecDescriptorC2R)(void* plan, void* input, void* output);
static cufftResult (*pcufftXtExecDescriptorD2Z)(void* plan, void* input, void* output);
static cufftResult (*pcufftXtExecDescriptorR2C)(void* plan, void* input, void* output);
static cufftResult (*pcufftXtExecDescriptorZ2D)(void* plan, void* input, void* output);
static cufftResult (*pcufftXtExecDescriptorZ2Z)(void* plan, void* input, void* output, int direction);
static cufftResult (*pcufftXtFree)(void* descriptor);
static cufftResult (*pcufftXtGetSizeMany)(void* plan, int rank, long long int *n, long long int *inembed, long long int istride, long long int idist, void* inputtype,
                                        long long int *onembed, long long int ostride, long long int odist, void* outputtype, long long int batch, size_t *workSize, void* executiontype);
static cufftResult (*pcufftXtMakePlanMany)(void* plan, int rank, long long int *n, long long int *inembed, long long int istride, long long int idist, void* inputtype, long long int *onembed,
                                         long long int ostride, long long int odist, void* outputtype, long long int batch, size_t *workSize, void* executiontype);
static cufftResult (*pcufftXtMalloc)(void* plan, void** descriptor, void* format);
static cufftResult (*pcufftXtMemcpy)(void* plan, void *dstPointer, void *srcPointer, void* type);
static cufftResult (*pcufftXtQueryPlan)(void* plan, void *queryStruct, void* queryType);
static cufftResult (*pcufftXtSetCallback)(void* plan, void **callback_routine, void* cbType, void **caller_info);
static cufftResult (*pcufftXtSetCallbackSharedSize)(void* plan, void* cbType, size_t sharedSize);
static cufftResult (*pcufftXtSetGPUs)(void* handle, int nGPUs, int *whichGPUs);
static cufftResult (*pcufftXtSetWorkArea)(void* plan, void **workArea);
static cufftResult (*pcufftXtSetWorkAreaPolicy)(void* plan, void* policy, size_t *workSize);

static void *cufft_handle = NULL;

static BOOL load_functions(void)
{
    if (!(cufft_handle = dlopen("libcufft.so.11", RTLD_NOW)))
    {
        FIXME("Wine cannot find the cuda FFT library\n");
        return FALSE;
    }

    #define LOAD_FUNCPTR(f) if((*(void **)(&p##f) = dlsym(cufft_handle, #f)) == NULL){ERR("Can't find symbol %s\n", #f); return FALSE;}

    LOAD_FUNCPTR(cufftCreate);
    LOAD_FUNCPTR(cufftDestroy);
    LOAD_FUNCPTR(cufftEstimate1d);
    LOAD_FUNCPTR(cufftEstimate2d);
    LOAD_FUNCPTR(cufftEstimate3d);
    LOAD_FUNCPTR(cufftEstimateMany);
    LOAD_FUNCPTR(cufftExecC2C);
    LOAD_FUNCPTR(cufftExecR2C);
    LOAD_FUNCPTR(cufftExecC2R);
    LOAD_FUNCPTR(cufftExecZ2Z);
    LOAD_FUNCPTR(cufftExecD2Z);
    LOAD_FUNCPTR(cufftExecZ2D);
    LOAD_FUNCPTR(cufftGetPlanPropertyInt64);
    LOAD_FUNCPTR(cufftGetProperty);
    LOAD_FUNCPTR(cufftGetSize);
    LOAD_FUNCPTR(cufftGetSize1d);
    LOAD_FUNCPTR(cufftGetSize2d);
    LOAD_FUNCPTR(cufftGetSize3d);
    LOAD_FUNCPTR(cufftGetSizeMany);
    LOAD_FUNCPTR(cufftGetSizeMany64);
    LOAD_FUNCPTR(cufftGetVersion);
    LOAD_FUNCPTR(cufftMakePlan1d);
    LOAD_FUNCPTR(cufftMakePlan2d);
    LOAD_FUNCPTR(cufftMakePlan3d);
    LOAD_FUNCPTR(cufftMakePlanMany);
    LOAD_FUNCPTR(cufftMakePlanMany64);
    LOAD_FUNCPTR(cufftPlan1d);
    LOAD_FUNCPTR(cufftPlan2d);
    LOAD_FUNCPTR(cufftPlan3d);
    LOAD_FUNCPTR(cufftPlanMany);
    LOAD_FUNCPTR(cufftResetPlanProperty);
    LOAD_FUNCPTR(cufftSetAutoAllocation);
    LOAD_FUNCPTR(cufftSetPlanPropertyInt64);
    LOAD_FUNCPTR(cufftSetStream);
    LOAD_FUNCPTR(cufftSetWorkArea);
    LOAD_FUNCPTR(cufftXtClearCallback);
    LOAD_FUNCPTR(cufftXtExec);
    LOAD_FUNCPTR(cufftXtExecDescriptor);
    LOAD_FUNCPTR(cufftXtExecDescriptorC2C);
    LOAD_FUNCPTR(cufftXtExecDescriptorC2R);
    LOAD_FUNCPTR(cufftXtExecDescriptorD2Z);
    LOAD_FUNCPTR(cufftXtExecDescriptorR2C);
    LOAD_FUNCPTR(cufftXtExecDescriptorZ2D);
    LOAD_FUNCPTR(cufftXtExecDescriptorZ2Z);
    LOAD_FUNCPTR(cufftXtFree);
    LOAD_FUNCPTR(cufftXtGetSizeMany);
    LOAD_FUNCPTR(cufftXtMakePlanMany);
    LOAD_FUNCPTR(cufftXtMalloc);
    LOAD_FUNCPTR(cufftXtMemcpy);
    LOAD_FUNCPTR(cufftXtQueryPlan);
    LOAD_FUNCPTR(cufftXtSetCallback);
    LOAD_FUNCPTR(cufftXtSetCallbackSharedSize);
    LOAD_FUNCPTR(cufftXtSetGPUs);
    LOAD_FUNCPTR(cufftXtSetWorkArea);
    LOAD_FUNCPTR(cufftXtSetWorkAreaPolicy);

    #undef LOAD_FUNCPTR
    return TRUE;
}

cufftResult WINAPI wine_cufftCreate(void* handle)
{
    TRACE("(%p)\n", handle);
    return pcufftCreate(handle);
}

cufftResult WINAPI wine_cufftDestroy(void* plan)
{
    TRACE("(%p)\n", plan);
    return pcufftDestroy(plan);
}

cufftResult WINAPI wine_cufftEstimate1d(int nx, void* type, int batch, size_t *workSize)
{
    TRACE("(%d, %p, %d, %p)\n", nx, type, batch, workSize);
    return pcufftEstimate1d(nx, type, batch, workSize);
}

cufftResult WINAPI wine_cufftEstimate2d(int nx, int ny, void* type, size_t *workSize)
{
    TRACE("(%d, %d, %p, %p)\n", nx, ny, type, workSize);
    return pcufftEstimate2d(nx, ny, type, workSize);
}

cufftResult WINAPI wine_cufftEstimate3d(int nx, int ny, int nz, void* type, size_t *workSize)
{
    TRACE("(%d, %d, %d, %p, %p)\n", nx, ny, nz, type, workSize);
    return pcufftEstimate3d(nx, ny, nz, type, workSize);
}

cufftResult WINAPI wine_cufftEstimateMany(int rank, int *n, int *inembed, int istride, int idist, int *onembed, int ostride, int odist, void* type, int batch, size_t *workSize)
{
    TRACE("(%d, %p, %p, %d, %d, %p, %d, %d, %p, %d, %p)", rank, n, inembed, istride, idist, onembed, ostride, odist, type, batch, workSize);
    return pcufftEstimateMany(rank, n, inembed, istride, idist, onembed, ostride, odist, type, batch, workSize);
}

cufftResult WINAPI wine_cufftExecC2C(void* plan, void* idata, void* odata, int direction)
{
    TRACE("(%p, %p, %p, %d)\n", plan, idata, odata, direction);
    return pcufftExecC2C(plan, idata, odata, direction);
}

cufftResult WINAPI wine_cufftExecR2C(void* plan, void* idata, void* odata)
{
    TRACE("(%p, %p, %p)\n", plan, idata, odata);
    return pcufftExecR2C(plan, idata, odata);
}

cufftResult WINAPI wine_cufftExecC2R(void* plan, void* idata, void* odata)
{
    TRACE("(%p, %p, %p)\n", plan, idata, odata);
    return pcufftExecC2R(plan, idata, odata);
}

cufftResult WINAPI wine_cufftExecZ2Z(void* plan, void* idata, void* odata, int direction)
{
    TRACE("(%p, %p, %p, %d)\n", plan, idata, odata, direction);
    return pcufftExecZ2Z(plan, idata, odata, direction);
}

cufftResult WINAPI wine_cufftExecD2Z(void* plan, void* idata, void* odata)
{
    TRACE("(%p, %p, %p)\n", plan, idata, odata);
    return pcufftExecD2Z(plan, idata, odata);
}

cufftResult WINAPI wine_cufftExecZ2D(void* plan, void* idata, void* odata)
{
    TRACE("(%p, %p, %p)\n", plan, idata, odata);
    return pcufftExecZ2D(plan, idata, odata);
}

cufftResult WINAPI wine_cufftGetPlanPropertyInt64(void* plan, void* property, long long int* returnPtrValue)
{
    TRACE("(%p, %p, %p)\n", plan, property, returnPtrValue);
    return pcufftGetPlanPropertyInt64(plan, property, returnPtrValue);
}

cufftResult WINAPI wine_cufftGetProperty(void* type, int *value)
{
    TRACE("(%p, %p)\n", type, value);
    return pcufftGetProperty(type, value);
}

cufftResult WINAPI wine_cufftGetSize(void* handle, size_t *workSize)
{
    TRACE("(%p, %p)\n", handle, workSize);
    return pcufftGetSize(handle, workSize);
}

cufftResult WINAPI wine_cufftGetSize1d(void* handle, int nx, void* type, int batch, size_t *workSize)
{
    TRACE("(%p, %d, %p, %d, %p)\n", handle, nx, type, batch, workSize);
    return pcufftGetSize1d(handle, nx, type, batch, workSize);
}

cufftResult WINAPI wine_cufftGetSize2d(void* handle, int nx, int ny, void* type, int batch, size_t *workSize)
{
    TRACE("(%p, %d, %d, %p, %d, %p)\n", handle, nx, ny, type, batch, workSize);
    return pcufftGetSize2d(handle, nx, ny, type, batch, workSize);
}

cufftResult WINAPI wine_cufftGetSize3d(void* handle, int nx, int ny, int nz, void* type, int batch, size_t *workSize)
{
    TRACE("(%p, %d, %d, %d, %p, %d, %p)\n", handle, nx, ny, nz, type, batch, workSize);
    return pcufftGetSize3d(handle, nx, ny, nz, type, batch, workSize);
}

cufftResult WINAPI wine_cufftGetSizeMany(void* handle, int rank, int *n, int *inembed, int istride, int idist, int *onembed, int ostride, int odist, void* type, int batch, size_t *workArea)
{
    TRACE("(%p, %d, %p, %p, %d, %d, %p, %d, %d, %p, %d, %p)\n", handle, rank, n, inembed, istride, idist, onembed, ostride, odist, type, batch, workArea);
    return pcufftGetSizeMany(handle, rank, n, inembed, istride, idist, onembed, ostride, odist, type, batch, workArea);
}

cufftResult WINAPI wine_cufftGetSizeMany64(void* plan, int rank, long long int *n, long long int *inembed, long long int istride, long long int idist,
                                        long long int *onembed, long long int ostride, long long int odist, void* type, long long int batch, size_t *workSize)
{
    TRACE("(%p, %d, %p, %p, %lld, %lld, %p, %lld, %lld, %p, %lld, %p)\n", plan, rank, n, inembed, istride, idist, onembed, ostride, odist, type, batch, workSize);
    return pcufftGetSizeMany64(plan, rank, n, inembed, istride, idist, onembed, ostride, odist, type, batch, workSize);
}

cufftResult WINAPI wine_cufftGetVersion(int *version)
{
    TRACE("(%p)\n", version);
    return pcufftGetVersion(version);
}

cufftResult WINAPI wine_cufftMakePlan1d(void* plan, int nx, void* type, int batch, size_t *workSize)
{
    TRACE("(%p, %d, %p, %d, %p)\n", plan, nx, type, batch, workSize);
    return pcufftMakePlan1d(plan, nx, type, batch, workSize);
}

cufftResult WINAPI wine_cufftMakePlan2d(void* plan, int nx, int ny, void* type, size_t *workSize)
{
    TRACE("(%p, %d, %d, %p, %p)\n", plan, nx, ny, type, workSize);
    return pcufftMakePlan2d(plan, nx, ny, type, workSize);
}

cufftResult WINAPI wine_cufftMakePlan3d(void* plan, int nx, int ny, int nz, void* type, size_t *workSize)
{
    TRACE("(%p, %d, %d, %d, %p, %p)\n", plan, nx, ny, nz, type, workSize);
    return pcufftMakePlan3d(plan, nx, ny, nz, type, workSize);
}

cufftResult WINAPI wine_cufftMakePlanMany(void* plan, int rank, int *n, int *inembed, int istride, int idist, int *onembed, int ostride, int odist, void* type, int batch, size_t *workSize)
{
    TRACE("(%p, %d, %p, %p, %d, %d, %p, %d, %d, %p, %d, %p)\n", plan, rank, n, inembed, istride, idist, onembed, ostride, odist, type, batch, workSize);
    return pcufftMakePlanMany(plan, rank, n, inembed, istride, idist, onembed, ostride, odist, type, batch, workSize);
}

cufftResult WINAPI wine_cufftMakePlanMany64(void* plan, int rank, long long int *n, long long int *inembed, long long int istride, long long int idist, long long int *onembed,
                                         long long int ostride, long long int odist, void* type, long long int batch, size_t * workSize)
{
    TRACE("(%p, %d, %p, %p, %lld, %lld, %p, %lld, %lld, %p, %lld, %p)\n", plan, rank, n, inembed, istride, idist, onembed, ostride, odist, type, batch, workSize);
    return pcufftMakePlanMany64(plan, rank, n, inembed, istride, idist, onembed, ostride, odist, type, batch, workSize);
}

cufftResult WINAPI wine_cufftPlan1d(void* plan, int nx, void* type, int batch)
{
    TRACE("(%p, %d, %p, %d)\n", plan, nx, type, batch);
    return pcufftPlan1d(plan, nx, type, batch);
}

cufftResult WINAPI wine_cufftPlan2d(void* plan, int nx, int ny, void* type)
{
    TRACE("(%p, %d, %d, %p)\n", plan, nx, ny, type);
    return pcufftPlan2d(plan, nx, ny, type);
}

cufftResult WINAPI wine_cufftPlan3d(void* plan, int nx, int ny, int nz, void* type)
{
    TRACE("(%p, %d, %d, %d, %p)\n", plan, nx, ny, nz, type);
    return pcufftPlan3d(plan, nx, ny, nz, type);
}

cufftResult WINAPI wine_cufftPlanMany(void* plan, int rank, int *n, int *inembed, int istride, int idist, int *onembed, int ostride, int odist, void* type, int batch)
{
    TRACE("(%p, %d, %p, %p, %d, %d, %p, %d, %d, %p, %d)\n", plan, rank, n, inembed, istride, idist, onembed, ostride, odist, type, batch);
    return pcufftPlanMany(plan, rank, n, inembed, istride, idist, onembed, ostride, odist, type, batch);
}

cufftResult WINAPI wine_cufftResetPlanProperty(void* plan, void* property)
{
    TRACE("(%p, %p)\n", plan, property);
    return pcufftResetPlanProperty(plan, property);
}

cufftResult WINAPI wine_cufftSetAutoAllocation(void* plan, int autoAllocate)
{
    TRACE("(%p, %d)\n", plan, autoAllocate);
    return pcufftSetAutoAllocation(plan, autoAllocate);
}

cufftResult WINAPI wine_cufftSetPlanPropertyInt64(void* plan, void* property, const long long int inputValueInt)
{
    TRACE("(%p, %p, %lld)\n", plan, property, inputValueInt);
    return pcufftSetPlanPropertyInt64(plan, property, inputValueInt);
}

cufftResult WINAPI wine_cufftSetStream(void* plan, void* stream)
{
    TRACE("(%p, %p)\n", plan, stream);
    return pcufftSetStream(plan, stream);
}

cufftResult WINAPI wine_cufftSetWorkArea(void* plan, void *workArea)
{
    TRACE("(%p, %p)\n", plan, workArea);
    return pcufftSetWorkArea(plan, workArea);
}

cufftResult WINAPI wine_cufftXtClearCallback(void* plan, void* cbType)
{
    TRACE("(%p, %p)\n", plan, cbType);
    return pcufftXtClearCallback(plan, cbType);
}

cufftResult WINAPI wine_cufftXtExec(void* plan, void *input, void *output, int direction)
{
    TRACE("(%p, %p, %p, %d)\n", plan, input, output, direction);
    return pcufftXtExec(plan, input, output, direction);
}

cufftResult WINAPI wine_cufftXtExecDescriptor(void* plan, void* input, void* output, int direction)
{
    TRACE("(%p, %p, %p, %d)\n", plan, input, output, direction);
    return pcufftXtExecDescriptor(plan, input, output, direction);
}

cufftResult WINAPI wine_cufftXtExecDescriptorC2C(void* plan, void* input, void* output, int direction)
{
    TRACE("(%p, %p, %p, %d)\n", plan, input, output, direction);
    return pcufftXtExecDescriptorC2C(plan, input, output, direction);
}

cufftResult WINAPI wine_cufftXtExecDescriptorC2R(void* plan, void* input, void* output)
{
    TRACE("(%p, %p, %p)\n", plan, input, output);
    return pcufftXtExecDescriptorC2R(plan, input, output);
}

cufftResult WINAPI wine_cufftXtExecDescriptorD2Z(void* plan, void* input, void* output)
{
    TRACE("(%p, %p, %p)\n", plan, input, output);
    return pcufftXtExecDescriptorD2Z(plan, input, output);
}

cufftResult WINAPI wine_cufftXtExecDescriptorR2C(void* plan, void* input, void* output)
{
    TRACE("(%p, %p, %p)\n", plan, input, output);
    return pcufftXtExecDescriptorR2C(plan, input, output);
}

cufftResult WINAPI wine_cufftXtExecDescriptorZ2D(void* plan, void* input, void* output)
{
    TRACE("(%p, %p, %p)\n", plan, input, output);
    return pcufftXtExecDescriptorZ2D(plan, input, output);
}

cufftResult WINAPI wine_cufftXtExecDescriptorZ2Z(void* plan, void* input, void* output, int direction)
{
    TRACE("(%p, %p, %p, %d)\n", plan, input, output, direction);
    return pcufftXtExecDescriptorZ2Z(plan, input, output, direction);
}

cufftResult WINAPI wine_cufftXtFree(void* descriptor)
{
    TRACE("(%p)\n", descriptor);
    return pcufftXtFree(descriptor);
}

cufftResult WINAPI wine_cufftXtGetSizeMany(void* plan, int rank, long long int *n, long long int *inembed, long long int istride, long long int idist, void* inputtype,
                                        long long int *onembed, long long int ostride, long long int odist, void* outputtype, long long int batch, size_t *workSize, void* executiontype)
{
    TRACE("(%p, %d, %p, %p, %lld, %lld, %p, %p, %lld, %lld, %p, %lld, %p, %p)\n", plan, rank, n, inembed, istride, idist, inputtype, onembed, ostride, odist, outputtype, batch, workSize, executiontype);
    return pcufftXtGetSizeMany(plan, rank, n, inembed, istride, idist, inputtype, onembed, ostride, odist, outputtype, batch, workSize, executiontype);
}

cufftResult WINAPI wine_cufftXtMakePlanMany(void* plan, int rank, long long int *n, long long int *inembed, long long int istride, long long int idist, void* inputtype, long long int *onembed,
                                         long long int ostride, long long int odist, void* outputtype, long long int batch, size_t *workSize, void* executiontype)
{
    TRACE("(%p, %d, %p, %p, %lld, %lld, %p, %p, %lld, %lld, %p, %lld, %p, %p)\n", plan, rank, n, inembed, istride, idist, inputtype, onembed, ostride, odist, outputtype, batch, workSize, executiontype);
    return pcufftXtMakePlanMany(plan, rank, n, inembed, istride, idist, inputtype, onembed, ostride, odist, outputtype, batch, workSize, executiontype);
}

cufftResult WINAPI wine_cufftXtMalloc(void* plan, void** descriptor, void* format)
{
    TRACE("(%p, %p, %p)\n", plan, descriptor, format);
    return pcufftXtMalloc(plan, descriptor, format);
}

cufftResult WINAPI wine_cufftXtMemcpy(void* plan, void *dstPointer, void *srcPointer, void* type)
{
    TRACE("(%p, %p, %p, %p)\n", plan, dstPointer, srcPointer, type);
    return pcufftXtMemcpy(plan, dstPointer, srcPointer, type);
}

cufftResult WINAPI wine_cufftXtQueryPlan(void* plan, void *queryStruct, void* queryType)
{
    TRACE("(%p, %p, %p)\n", plan, queryStruct, queryType);
    return pcufftXtQueryPlan(plan, queryStruct, queryType);
}

cufftResult WINAPI wine_cufftXtSetCallback(void* plan, void **callback_routine, void* cbType, void **caller_info)
{
    TRACE("(%p, %p, %p, %p)\n", plan, callback_routine, cbType, caller_info);
    return pcufftXtSetCallback(plan, callback_routine, cbType, caller_info);
}

cufftResult WINAPI wine_cufftXtSetCallbackSharedSize(void* plan, void* cbType, size_t sharedSize)
{
    TRACE("(%p, %p, %zu)\n", plan, cbType, sharedSize);
    return pcufftXtSetCallbackSharedSize(plan, cbType, sharedSize);
}

cufftResult WINAPI wine_cufftXtSetGPUs(void* handle, int nGPUs, int *whichGPUs)
{
    TRACE("(%p, %d, %p)\n", handle, nGPUs, whichGPUs);
    return pcufftXtSetGPUs(handle, nGPUs, whichGPUs);
}

cufftResult WINAPI wine_cufftXtSetWorkArea(void* plan, void **workArea)
{
    TRACE("(%p, %p)\n", plan, workArea);
    return pcufftXtSetWorkArea(plan, workArea);
}

cufftResult WINAPI wine_cufftXtSetWorkAreaPolicy(void* plan, void* policy, size_t *workSize)
{
    TRACE("(%p, %p, %p)\n", plan, policy, workSize);
    return pcufftXtSetWorkAreaPolicy(plan, policy, workSize);
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
            if (cufft_handle) dlclose(cufft_handle);
            break;
        case DLL_THREAD_ATTACH:
            break;
        case DLL_THREAD_DETACH:
            break;
    }

    return TRUE;
}
