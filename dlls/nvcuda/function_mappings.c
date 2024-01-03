/*
 * Copyright (C) 2023 Sveinar Søpler
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

#include "function_mappings.h"
#include <stdio.h>

extern void wine_cuGetProcAddress(void);
extern void wine_cuGetProcAddress_v2(void);
extern void wine_cuInit(void);
extern void wine_cuDeviceGet(void);
extern void wine_cuDeviceGetCount(void);
extern void wine_cuDeviceGetName(void);
extern void wine_cuDeviceTotalMem(void);
extern void wine_cuDeviceTotalMem_v2(void);
extern void wine_cuDeviceGetAttribute(void);
extern void wine_cuDeviceGetP2PAttribute(void);
extern void wine_cuDriverGetVersion(void);
extern void wine_cuDeviceGetByPCIBusId(void);
extern void wine_cuDeviceGetPCIBusId(void);
extern void wine_cuDeviceGetUuid(void);
extern void wine_cuDeviceGetUuid_v2(void);
extern void wine_cuDeviceGetTexture1DLinearMaxWidth(void);
extern void wine_cuDeviceGetDefaultMemPool(void);
extern void wine_cuDeviceSetMemPool(void);
extern void wine_cuDeviceGetMemPool(void);
extern void wine_cuFlushGPUDirectRDMAWrites(void);
extern void wine_cuDeviceGetLuid(void);
extern void wine_cuDevicePrimaryCtxRetain(void);
extern void wine_cuDevicePrimaryCtxRelease(void);
extern void wine_cuDevicePrimaryCtxRelease_v2(void);
extern void wine_cuDevicePrimaryCtxSetFlags(void);
extern void wine_cuDevicePrimaryCtxSetFlags_v2(void);
extern void wine_cuDevicePrimaryCtxGetState(void);
extern void wine_cuDevicePrimaryCtxReset(void);
extern void wine_cuDevicePrimaryCtxReset_v2(void);
extern void wine_cuCtxCreate(void);
extern void wine_cuCtxCreate_v2(void);
extern void wine_cuCtxCreate_v3(void);
extern void wine_cuCtxGetFlags(void);
extern void wine_cuCtxSetCurrent(void);
extern void wine_cuCtxGetCurrent(void);
extern void wine_cuCtxDetach(void);
extern void wine_cuCtxGetApiVersion(void);
extern void wine_cuCtxGetDevice(void);
extern void wine_cuCtxGetLimit(void);
extern void wine_cuCtxSetLimit(void);
extern void wine_cuCtxGetCacheConfig(void);
extern void wine_cuCtxSetCacheConfig(void);
extern void wine_cuCtxGetSharedMemConfig(void);
extern void wine_cuCtxGetStreamPriorityRange(void);
extern void wine_cuCtxSetSharedMemConfig(void);
extern void wine_cuCtxSynchronize(void);
extern void wine_cuCtxResetPersistingL2Cache(void);
extern void wine_cuCtxPopCurrent(void);
extern void wine_cuCtxPopCurrent_v2(void);
extern void wine_cuCtxPushCurrent(void);
extern void wine_cuCtxPushCurrent_v2(void);
extern void wine_cuModuleLoad(void);
extern void wine_cuModuleLoadData(void);
extern void wine_cuModuleLoadFatBinary(void);
extern void wine_cuModuleUnload(void);
extern void wine_cuModuleGetFunction(void);
extern void wine_cuModuleGetGlobal(void);
extern void wine_cuModuleGetGlobal_v2(void);
extern void wine_cuModuleGetTexRef(void);
extern void wine_cuModuleGetSurfRef(void);
extern void wine_cuModuleGetLoadingMode(void);
extern void wine_cuLibraryLoadData(void);
extern void wine_cuLibraryLoadFromFile(void);
extern void wine_cuLibraryUnload(void);
extern void wine_cuLibraryGetKernel(void);
extern void wine_cuLibraryGetModule(void);
extern void wine_cuKernelGetFunction(void);
extern void wine_cuLibraryGetGlobal(void);
extern void wine_cuLibraryGetManaged(void);
extern void wine_cuKernelGetAttribute(void);
extern void wine_cuKernelSetAttribute(void);
extern void wine_cuKernelSetCacheConfig(void);
extern void wine_cuLinkCreate(void);
extern void wine_cuLinkCreate_v2(void);
extern void wine_cuLinkAddData(void);
extern void wine_cuLinkAddData_v2(void);
extern void wine_cuLinkAddFile(void);
extern void wine_cuLinkComplete(void);
extern void wine_cuLinkDestroy(void);
extern void wine_cuMemGetInfo(void);
extern void wine_cuMemGetInfo_v2(void);
extern void wine_cuMemAllocManaged(void);
extern void wine_cuMemAlloc(void);
extern void wine_cuMemAlloc_v2(void);
extern void wine_cuMemAllocPitch(void);
extern void wine_cuMemAllocPitch_v2(void);
extern void wine_cuMemFree(void);
extern void wine_cuMemFree_v2(void);
extern void wine_cuMemGetAddressRange(void);
extern void wine_cuMemGetAddressRange_v2(void);
extern void wine_cuMemFreeHost(void);
extern void wine_cuMemHostAlloc(void);
extern void wine_cuMemHostGetDevicePointer(void);
extern void wine_cuMemHostGetDevicePointer_v2(void);
extern void wine_cuMemHostGetFlags(void);
extern void wine_cuMemHostRegister(void);
extern void wine_cuMemHostRegister_v2(void);
extern void wine_cuMemHostUnregister(void);
extern void wine_cuPointerGetAttribute(void);
extern void wine_cuPointerGetAttributes(void);
extern void wine_cuMemAllocAsync(void);
extern void wine_cuMemAllocAsync_ptsz(void);
extern void wine_cuMemAllocFromPoolAsync(void);
extern void wine_cuMemAllocFromPoolAsync_ptsz(void);
extern void wine_cuMemFreeAsync(void);
extern void wine_cuMemFreeAsync_ptsz(void);
extern void wine_cuMemPoolTrimTo(void);
extern void wine_cuMemPoolSetAttribute(void);
extern void wine_cuMemPoolGetAttribute(void);
extern void wine_cuMemPoolSetAccess(void);
extern void wine_cuMemPoolGetAccess(void);
extern void wine_cuMemPoolCreate(void);
extern void wine_cuMemPoolDestroy(void);
extern void wine_cuMemPoolExportToShareableHandle(void);
extern void wine_cuMemPoolImportFromShareableHandle(void);
extern void wine_cuMemPoolExportPointer(void);
extern void wine_cuMemPoolImportPointer(void);
extern void wine_cuMemcpy(void);
extern void wine_cuMemcpy_ptds(void);
extern void wine_cuMemcpyAsync(void);
extern void wine_cuMemcpyAsync_ptsz(void);
extern void wine_cuMemcpyPeer(void);
extern void wine_cuMemcpyPeer_ptds(void);
extern void wine_cuMemcpyPeerAsync(void);
extern void wine_cuMemcpyPeerAsync_ptsz(void);
extern void wine_cuMemcpyHtoD(void);
extern void wine_cuMemcpyHtoD_v2(void);
extern void wine_cuMemcpyHtoD_v2_ptds(void);
extern void wine_cuMemcpyHtoDAsync(void);
extern void wine_cuMemcpyHtoDAsync_v2(void);
extern void wine_cuMemcpyHtoDAsync_v2_ptsz(void);
extern void wine_cuMemcpyDtoH(void);
extern void wine_cuMemcpyDtoH_v2(void);
extern void wine_cuMemcpyDtoH_v2_ptds(void);
extern void wine_cuMemcpyDtoHAsync(void);
extern void wine_cuMemcpyDtoHAsync_v2(void);
extern void wine_cuMemcpyDtoHAsync_v2_ptsz(void);
extern void wine_cuMemcpyDtoD(void);
extern void wine_cuMemcpyDtoD_v2(void);
extern void wine_cuMemcpyDtoD_v2_ptds(void);
extern void wine_cuMemcpyDtoDAsync(void);
extern void wine_cuMemcpyDtoDAsync_v2(void);
extern void wine_cuMemcpyDtoDAsync_v2_ptsz(void);
extern void wine_cuMemcpy2DUnaligned(void);
extern void wine_cuMemcpy2DUnaligned_v2(void);
extern void wine_cuMemcpy2DUnaligned_v2_ptds(void);
extern void wine_cuMemcpy2DAsync(void);
extern void wine_cuMemcpy2DAsync_v2(void);
extern void wine_cuMemcpy2DAsync_v2_ptsz(void);
extern void wine_cuMemcpy3D(void);
extern void wine_cuMemcpy3D_v2(void);
extern void wine_cuMemcpy3D_v2_ptds(void);
extern void wine_cuMemcpy3DAsync(void);
extern void wine_cuMemcpy3DAsync_v2(void);
extern void wine_cuMemcpy3DAsync_v2_ptsz(void);
extern void wine_cuMemcpy3DPeer(void);
extern void wine_cuMemcpy3DPeer_ptds(void);
extern void wine_cuMemcpy3DPeerAsync(void);
extern void wine_cuMemcpy3DPeerAsync_ptsz(void);
extern void wine_cuMemsetD8(void);
extern void wine_cuMemsetD8_v2(void);
extern void wine_cuMemsetD8_v2_ptds(void);
extern void wine_cuMemsetD8Async(void);
extern void wine_cuMemsetD8Async_ptsz(void);
extern void wine_cuMemsetD2D8Async(void);
extern void wine_cuMemsetD2D8Async_ptsz(void);
extern void wine_cuMemsetD2D8(void);
extern void wine_cuMemsetD2D8_v2(void);
extern void wine_cuMemsetD2D8_v2_ptds(void);
extern void wine_cuFuncSetCacheConfig(void);
extern void wine_cuFuncSetSharedMemConfig(void);
extern void wine_cuFuncGetAttribute(void);
extern void wine_cuFuncSetAttribute(void);
extern void wine_cuArrayCreate(void);
extern void wine_cuArrayCreate_v2(void);
extern void wine_cuArrayGetDescriptor(void);
extern void wine_cuArrayGetDescriptor_v2(void);
extern void wine_cuArrayGetSparseProperties(void);
extern void wine_cuArrayGetPlane(void);
extern void wine_cuArray3DCreate(void);
extern void wine_cuArray3DCreate_v2(void);
extern void wine_cuArray3DGetDescriptor(void);
extern void wine_cuArray3DGetDescriptor_v2(void);
extern void wine_cuArrayDestroy(void);
extern void wine_cuMipmappedArrayCreate(void);
extern void wine_cuMipmappedArrayGetLevel(void);
extern void wine_cuMipmappedArrayGetSparseProperties(void);
extern void wine_cuMipmappedArrayDestroy(void);
extern void wine_cuTexRefCreate(void);
extern void wine_cuTexRefDestroy(void);
extern void wine_cuTexRefSetArray(void);
extern void wine_cuTexRefSetMipmappedArray(void);
extern void wine_cuTexRefSetAddress(void);
extern void wine_cuTexRefSetAddress_v2(void);
extern void wine_cuTexRefSetAddress(void);
extern void wine_cuTexRefSetAddress2D(void);
extern void wine_cuTexRefSetAddress2D_v2(void);
extern void wine_cuTexRefSetFormat(void);
extern void wine_cuTexRefSetAddressMode(void);
extern void wine_cuTexRefSetFilterMode(void);
extern void wine_cuTexRefSetMipmapFilterMode(void);
extern void wine_cuTexRefSetMipmapLevelBias(void);
extern void wine_cuTexRefSetMipmapLevelClamp(void);
extern void wine_cuTexRefSetMaxAnisotropy(void);
extern void wine_cuTexRefSetFlags(void);
extern void wine_cuTexRefSetBorderColor(void);
extern void wine_cuTexRefGetBorderColor(void);
extern void wine_cuSurfRefSetArray(void);
extern void wine_cuArrayGetMemoryRequirements(void);
extern void wine_cuMipmappedArrayGetMemoryRequirements(void);
extern void wine_cuTexObjectCreate(void);
extern void wine_cuTexObjectDestroy(void);
extern void wine_cuTexObjectGetResourceDesc(void);
extern void wine_cuTexObjectGetTextureDesc(void);
extern void wine_cuTexObjectGetResourceViewDesc(void);
extern void wine_cuSurfObjectCreate(void);
extern void wine_cuSurfObjectDestroy(void);
extern void wine_cuSurfObjectGetResourceDesc(void);
extern void wine_cuImportExternalMemory(void);
extern void wine_cuExternalMemoryGetMappedBuffer(void);
extern void wine_cuExternalMemoryGetMappedMipmappedArray(void);
extern void wine_cuDestroyExternalMemory(void);
extern void wine_cuImportExternalSemaphore(void);
extern void wine_cuSignalExternalSemaphoresAsync(void);
extern void wine_cuSignalExternalSemaphoresAsync_ptsz(void);
extern void wine_cuWaitExternalSemaphoresAsync(void);
extern void wine_cuWaitExternalSemaphoresAsync_ptsz(void);
extern void wine_cuDestroyExternalSemaphore(void);
extern void wine_cuLaunchKernel(void);
extern void wine_cuLaunchKernel_ptsz(void);
extern void wine_cuLaunchCooperativeKernel(void);
extern void wine_cuLaunchCooperativeKernel_ptsz(void);
extern void wine_cuLaunchCooperativeKernelMultiDevice(void);
extern void wine_cuLaunchHostFunc(void);
extern void wine_cuLaunchHostFunc_ptsz(void);
extern void wine_cuLaunchKernelEx(void);
extern void wine_cuLaunchKernelEx_ptsz(void);
extern void wine_cuEventCreate(void);
extern void wine_cuEventRecord(void);
extern void wine_cuEventRecord_ptsz(void);
extern void wine_cuEventRecordWithFlags(void);
extern void wine_cuEventRecordWithFlags_ptsz(void);
extern void wine_cuEventQuery(void);
extern void wine_cuEventSynchronize(void);
extern void wine_cuEventDestroy(void);
extern void wine_cuEventDestroy_v2(void);
extern void wine_cuEventElapsedTime(void);
extern void wine_cuStreamWaitValue32(void);
extern void wine_cuStreamWaitValue32_ptsz(void);
extern void wine_cuStreamWriteValue32(void);
extern void wine_cuStreamWriteValue32_ptsz(void);
extern void wine_cuStreamWaitValue64(void);
extern void wine_cuStreamWaitValue64_ptsz(void);
extern void wine_cuStreamWriteValue64(void);
extern void wine_cuStreamWriteValue64_ptsz(void);
extern void wine_cuStreamBatchMemOp(void);
extern void wine_cuStreamBatchMemOp_ptsz(void);
extern void wine_cuStreamCreate(void);
extern void wine_cuStreamCreateWithPriority(void);
extern void wine_cuStreamGetPriority(void);
extern void wine_cuStreamGetPriority_ptsz(void);
extern void wine_cuStreamGetFlags(void);
extern void wine_cuStreamGetCtx(void);
extern void wine_cuStreamGetFlags_ptsz(void);
extern void wine_cuStreamGetId(void);
extern void wine_cuStreamGetId_ptsz(void);
extern void wine_cuStreamDestroy(void);
extern void wine_cuStreamWaitEvent(void);
extern void wine_cuStreamWaitEvent_ptsz(void);
extern void wine_cuStreamAddCallback(void);
extern void wine_cuStreamAddCallback_ptsz(void);
extern void wine_cuStreamSynchronize(void);
extern void wine_cuStreamSynchronize_ptsz(void);
extern void wine_cuStreamQuery(void);
extern void wine_cuStreamQuery_ptsz(void);
extern void wine_cuStreamAttachMemAsync(void);
extern void wine_cuStreamAttachMemAsync_ptsz(void);
extern void wine_cuStreamCopyAttributes(void);
extern void wine_cuStreamCopyAttributes_ptsz(void);
extern void wine_cuStreamGetAttribute(void);
extern void wine_cuStreamGetAttribute_ptsz(void);
extern void wine_cuStreamSetAttribute(void);
extern void wine_cuStreamSetAttribute_ptsz(void);
extern void wine_cuDeviceCanAccessPeer(void);
extern void wine_cuCtxEnablePeerAccess(void);
extern void wine_cuCtxDisablePeerAccess(void);
extern void wine_cuIpcGetEventHandle(void);
extern void wine_cuIpcOpenEventHandle(void);
extern void wine_cuIpcGetMemHandle(void);
extern void wine_cuIpcOpenMemHandle(void);
extern void wine_cuIpcOpenMemHandle_v2(void);
extern void wine_cuIpcCloseMemHandle(void);
extern void wine_cuGLCtxCreate(void);
extern void wine_cuGLCtxCreate_v2(void);
extern void wine_cuGLInit(void);
extern void wine_cuGLGetDevices(void);
extern void wine_cuGLRegisterBufferObject(void);
extern void wine_cuGLMapBufferObject(void);
extern void wine_cuGLMapBufferObject_v2(void);
extern void wine_cuGLMapBufferObject_v2_ptds(void);
extern void wine_cuGLMapBufferObjectAsync(void);
extern void wine_cuGLMapBufferObjectAsync_v2(void);
extern void wine_cuGLMapBufferObjectAsync_v2_ptsz(void);
extern void wine_cuGLUnmapBufferObject(void);
extern void wine_cuGLUnmapBufferObjectAsync(void);
extern void wine_cuGLUnregisterBufferObject(void);
extern void wine_cuGLSetBufferObjectMapFlags(void);
extern void wine_cuGraphicsGLRegisterImage(void);
extern void wine_cuGraphicsGLRegisterBuffer(void);
extern void wine_cuWGLGetDevice(void);
extern void wine_cuGraphicsUnregisterResource(void);
extern void wine_cuGraphicsMapResources(void);
extern void wine_cuGraphicsMapResources_ptsz(void);
extern void wine_cuGraphicsUnmapResources(void);
extern void wine_cuGraphicsUnmapResources_ptsz(void);
extern void wine_cuGraphicsResourceSetMapFlags(void);
extern void wine_cuGraphicsResourceSetMapFlags_v2(void);
extern void wine_cuGraphicsSubResourceGetMappedArray(void);
extern void wine_cuGraphicsResourceGetMappedMipmappedArray(void);
extern void wine_cuGraphicsResourceGetMappedPointer(void);
extern void wine_cuGraphicsResourceGetMappedPointer_v2(void);
extern void wine_cuProfilerInitialize(void);
extern void wine_cuProfilerStart(void);
extern void wine_cuProfilerStop(void);
extern void wine_cuD3D11GetDevice(void);
extern void wine_cuGraphicsD3D11RegisterResource(void);
extern void wine_cuD3D10GetDevice(void);
extern void wine_cuGraphicsD3D10RegisterResource(void);
extern void wine_cuD3D9GetDevice(void);
extern void wine_cuGraphicsD3D9RegisterResource(void);
extern void wine_cuGetExportTable(void);
extern void wine_cuOccupancyMaxActiveBlocksPerMultiprocessorWithFlags(void);
extern void wine_cuOccupancyAvailableDynamicSMemPerBlock(void);
extern void wine_cuOccupancyMaxPotentialClusterSize(void);
extern void wine_cuOccupancyMaxActiveClusters(void);
extern void wine_cuMemAdvise(void);
extern void wine_cuMemPrefetchAsync(void);
extern void wine_cuMemPrefetchAsync_ptsz(void);
extern void wine_cuMemRangeGetAttribute(void);
extern void wine_cuMemRangeGetAttributes(void);
extern void wine_cuGetErrorString(void);
extern void wine_cuGetErrorName(void);
extern void wine_cuGraphCreate(void);
extern void wine_cuGraphAddKernelNode(void);
extern void wine_cuGraphAddKernelNode_v2(void);
extern void wine_cuGraphKernelNodeGetParams(void);
extern void wine_cuGraphKernelNodeGetParams_v2(void);
extern void wine_cuGraphKernelNodeSetParams(void);
extern void wine_cuGraphKernelNodeSetParams_v2(void);
extern void wine_cuGraphAddMemcpyNode(void);
extern void wine_cuGraphMemcpyNodeGetParams(void);
extern void wine_cuGraphMemcpyNodeSetParams(void);
extern void wine_cuGraphAddMemsetNode(void);
extern void wine_cuGraphMemsetNodeGetParams(void);
extern void wine_cuGraphMemsetNodeSetParams(void);
extern void wine_cuGraphAddHostNode(void);
extern void wine_cuGraphHostNodeGetParams(void);
extern void wine_cuGraphHostNodeSetParams(void);
extern void wine_cuGraphAddChildGraphNode(void);
extern void wine_cuGraphChildGraphNodeGetGraph(void);
extern void wine_cuGraphAddEmptyNode(void);
extern void wine_cuGraphAddEventRecordNode(void);
extern void wine_cuGraphEventRecordNodeGetEvent(void);
extern void wine_cuGraphEventRecordNodeSetEvent(void);
extern void wine_cuGraphAddEventWaitNode(void);
extern void wine_cuGraphEventWaitNodeGetEvent(void);
extern void wine_cuGraphEventWaitNodeSetEvent(void);
extern void wine_cuGraphAddExternalSemaphoresSignalNode(void);
extern void wine_cuGraphExternalSemaphoresSignalNodeGetParams(void);
extern void wine_cuGraphExternalSemaphoresSignalNodeSetParams(void);
extern void wine_cuGraphAddExternalSemaphoresWaitNode(void);
extern void wine_cuGraphExternalSemaphoresWaitNodeGetParams(void);
extern void wine_cuGraphExternalSemaphoresWaitNodeSetParams(void);
extern void wine_cuGraphExecExternalSemaphoresSignalNodeSetParams(void);
extern void wine_cuGraphExecExternalSemaphoresWaitNodeSetParams(void);
extern void wine_cuGraphAddMemAllocNode(void);
extern void wine_cuGraphMemAllocNodeGetParams(void);
extern void wine_cuGraphAddMemFreeNode(void);
extern void wine_cuGraphMemFreeNodeGetParams(void);
extern void wine_cuDeviceGraphMemTrim(void);
extern void wine_cuDeviceGetGraphMemAttribute(void);
extern void wine_cuDeviceSetGraphMemAttribute(void);
extern void wine_cuGraphClone(void);
extern void wine_cuGraphNodeFindInClone(void);
extern void wine_cuGraphNodeGetType(void);
extern void wine_cuGraphGetNodes(void);
extern void wine_cuGraphGetRootNodes(void);
extern void wine_cuGraphGetEdges(void);
extern void wine_cuGraphNodeGetDependencies(void);
extern void wine_cuGraphNodeGetDependentNodes(void);
extern void wine_cuGraphAddDependencies(void);
extern void wine_cuGraphRemoveDependencies(void);
extern void wine_cuGraphDestroyNode(void);
extern void wine_cuGraphInstantiate(void);
extern void wine_cuGraphInstantiate_v2(void);
extern void wine_cuGraphInstantiateWithFlags(void);
extern void wine_cuGraphUpload(void);
extern void wine_cuGraphUpload_ptsz(void);
extern void wine_cuGraphLaunch(void);
extern void wine_cuGraphLaunch_ptsz(void);
extern void wine_cuGraphExecDestroy(void);
extern void wine_cuGraphDestroy(void);
extern void wine_cuStreamBeginCapture(void);
extern void wine_cuStreamBeginCapture_ptsz(void);
extern void wine_cuStreamBeginCapture_v2(void);
extern void wine_cuStreamBeginCapture_v2_ptsz(void);
extern void wine_cuStreamEndCapture(void);
extern void wine_cuStreamEndCapture_ptsz(void);
extern void wine_cuStreamIsCapturing(void);
extern void wine_cuStreamIsCapturing_ptsz(void);
extern void wine_cuStreamGetCaptureInfo(void);
extern void wine_cuStreamGetCaptureInfo_ptsz(void);
extern void wine_cuStreamGetCaptureInfo_v2(void);
extern void wine_cuStreamGetCaptureInfo_v2_ptsz(void);
extern void wine_cuStreamUpdateCaptureDependencies(void);
extern void wine_cuStreamUpdateCaptureDependencies_ptsz(void);
extern void wine_cuGraphExecKernelNodeSetParams(void);
extern void wine_cuGraphExecKernelNodeSetParams_v2(void);
extern void wine_cuGraphExecMemcpyNodeSetParams(void);
extern void wine_cuGraphExecMemsetNodeSetParams(void);
extern void wine_cuGraphExecHostNodeSetParams(void);
extern void wine_cuGraphExecChildGraphNodeSetParams(void);
extern void wine_cuGraphExecEventRecordNodeSetEvent(void);
extern void wine_cuGraphExecEventWaitNodeSetEvent(void);
extern void wine_cuThreadExchangeStreamCaptureMode(void);
extern void wine_cuGraphExecUpdate(void);
extern void wine_cuGraphExecUpdate_v2(void);
extern void wine_cuGraphKernelNodeCopyAttributes(void);
extern void wine_cuGraphKernelNodeGetAttribute(void);
extern void wine_cuGraphKernelNodeSetAttribute(void);
extern void wine_cuGraphDebugDotPrint(void);
extern void wine_cuUserObjectCreate(void);
extern void wine_cuUserObjectRetain(void);
extern void wine_cuUserObjectRelease(void);
extern void wine_cuGraphRetainUserObject(void);
extern void wine_cuGraphReleaseUserObject(void);
extern void wine_cuGraphNodeSetEnabled(void);
extern void wine_cuGraphNodeGetEnabled(void);
extern void wine_cuGraphInstantiateWithParams(void);
extern void wine_cuGraphInstantiateWithParams_ptsz(void);
extern void wine_cuGraphExecGetFlags(void);
extern void wine_cuMemAdvise_v2(void);
extern void wine_cuMemPrefetchAsync_v2(void);
extern void wine_cuMemPrefetchAsync_v2_ptsz(void);
extern void wine_cuGraphAddNode(void);
extern void wine_cuGraphNodeSetParams(void);
extern void wine_cuGraphExecNodeSetParams(void);
extern void wine_cuKernelGetName(void);
extern void wine_cuFuncGetName(void);
extern void wine_cuGraphGetEdges_v2(void);
extern void wine_cuGraphNodeGetDependencies_v2(void);
extern void wine_cuGraphNodeGetDependentNodes_v2(void);
extern void wine_cuGraphAddDependencies_v2(void);
extern void wine_cuGraphRemoveDependencies_v2(void);
extern void wine_cuStreamBeginCaptureToGraph(void);
extern void wine_cuStreamBeginCaptureToGraph_ptsz(void);
extern void wine_cuStreamGetCaptureInfo_v3(void);
extern void wine_cuStreamGetCaptureInfo_v3_ptsz(void);
extern void wine_cuStreamUpdateCaptureDependencies_v2(void);
extern void wine_cuStreamUpdateCaptureDependencies_v2_ptsz(void);
extern void wine_cuGraphAddNode_v2(void);
extern void wine_cuGraphConditionalHandleCreate(void);
extern void wine_cuFuncGetModule(void);

const FunctionMapping mappings[] = {
    {"cuGetProcAddress", 11030, 0, wine_cuGetProcAddress},
    {"cuGetProcAddress", 12000, 0, wine_cuGetProcAddress_v2},
    {"cuInit", 2000, 0, wine_cuInit},
    {"cuDeviceGet", 2000, 0, wine_cuDeviceGet},
    {"cuDeviceGet", 12020, 0, wine_cuDeviceGet},
    {"cuDeviceGetCount", 2000, 0, wine_cuDeviceGetCount},
    {"cuDeviceGetName", 2000, 0, wine_cuDeviceGetName},
    {"cuDeviceGetName", 12020, 0, wine_cuDeviceGetName},
    {"cuDeviceTotalMem", 2000, 0, wine_cuDeviceTotalMem},
    {"cuDeviceTotalMem", 3020, 0, wine_cuDeviceTotalMem_v2},
    {"cuDeviceGetAttribute", 2000, 0, wine_cuDeviceGetAttribute},
    {"cuDeviceGetP2PAttribute", 8000, 0, wine_cuDeviceGetP2PAttribute},
    {"cuDriverGetVersion", 2020, 0, wine_cuDriverGetVersion},
    {"cuDeviceGetByPCIBusId", 4010, 0, wine_cuDeviceGetByPCIBusId},
    {"cuDeviceGetPCIBusId", 4010, 0, wine_cuDeviceGetPCIBusId},
    {"cuDeviceGetUuid", 9020, 0, wine_cuDeviceGetUuid},
    {"cuDeviceGetUuid", 11040, 0, wine_cuDeviceGetUuid_v2},
    {"cuDeviceGetTexture1DLinearMaxWidth", 11010, 0, wine_cuDeviceGetTexture1DLinearMaxWidth},
    {"cuDeviceGetDefaultMemPool", 11020, 0, wine_cuDeviceGetDefaultMemPool},
    {"cuDeviceSetMemPool", 11020, 0, wine_cuDeviceSetMemPool},
    {"cuDeviceGetMemPool", 11020, 0, wine_cuDeviceGetMemPool},
    {"cuFlushGPUDirectRDMAWrites", 11030, 0, wine_cuFlushGPUDirectRDMAWrites},
    {"cuDeviceGetLuid", 10000, 0, wine_cuDeviceGetLuid},
    {"cuDevicePrimaryCtxRetain", 7000, 0, wine_cuDevicePrimaryCtxRetain},
    {"cuDevicePrimaryCtxRelease", 7000, 0, wine_cuDevicePrimaryCtxRelease},
    {"cuDevicePrimaryCtxRelease", 11000, 0, wine_cuDevicePrimaryCtxRelease_v2},
    {"cuDevicePrimaryCtxSetFlags", 11000, 0, wine_cuDevicePrimaryCtxSetFlags_v2},
    {"cuDevicePrimaryCtxGetState", 7000, 0, wine_cuDevicePrimaryCtxGetState},
    {"cuDevicePrimaryCtxReset", 7000, 0, wine_cuDevicePrimaryCtxReset},
    {"cuDevicePrimaryCtxReset", 11000, 0, wine_cuDevicePrimaryCtxReset_v2},
    {"cuCtxCreate", 2000, 0, wine_cuCtxCreate},
    {"cuCtxCreate", 3020, 0, wine_cuCtxCreate_v2},
    {"cuCtxCreate", 11040, 0, wine_cuCtxCreate_v3},
    {"cuCtxGetFlags", 7000, 0, wine_cuCtxGetFlags},
    {"cuCtxSetCurrent", 4000, 0, wine_cuCtxSetCurrent},
    {"cuCtxGetCurrent", 4000, 0, wine_cuCtxGetCurrent},
    {"cuCtxDetach", 2000, 0, wine_cuCtxDetach},
    {"cuCtxGetApiVersion", 3020, 0, wine_cuCtxGetApiVersion},
    {"cuCtxGetDevice", 2000, 0, wine_cuCtxGetDevice},
    {"cuCtxGetLimit", 3010, 0, wine_cuCtxGetLimit},
    {"cuCtxSetLimit", 3010, 0, wine_cuCtxSetLimit},
    {"cuCtxGetCacheConfig", 3020, 0, wine_cuCtxGetCacheConfig},
    {"cuCtxSetCacheConfig", 3020, 0, wine_cuCtxSetCacheConfig},
    {"cuCtxGetSharedMemConfig", 4020, 0, wine_cuCtxGetSharedMemConfig},
    {"cuCtxGetStreamPriorityRange", 5050, 0, wine_cuCtxGetStreamPriorityRange},
    {"cuCtxSetSharedMemConfig", 4020, 0, wine_cuCtxSetSharedMemConfig},
    {"cuCtxSynchronize", 2000, 0, wine_cuCtxSynchronize},
    {"cuCtxResetPersistingL2Cache", 11000, 0, wine_cuCtxResetPersistingL2Cache},
    {"cuCtxPopCurrent", 2000, 0, wine_cuCtxPopCurrent},
    {"cuCtxPopCurrent", 4000, 0, wine_cuCtxPopCurrent_v2},
    {"cuCtxPushCurrent", 2000, 0, wine_cuCtxPushCurrent},
    {"cuCtxPushCurrent", 4000, 0, wine_cuCtxPushCurrent_v2},
    {"cuModuleLoad", 2000, 0, wine_cuModuleLoad},
    {"cuModuleLoadData", 2000, 0, wine_cuModuleLoadData},
    {"cuModuleLoadFatBinary", 2000, 0, wine_cuModuleLoadFatBinary},
    {"cuModuleUnload", 2000, 0, wine_cuModuleUnload},
    {"cuModuleGetFunction", 2000, 0, wine_cuModuleGetFunction},
    {"cuModuleGetGlobal", 2000, 0, wine_cuModuleGetGlobal},
    {"cuModuleGetGlobal", 3020, 0, wine_cuModuleGetGlobal_v2},
    {"cuModuleGetTexRef", 2000, 0, wine_cuModuleGetTexRef},
    {"cuModuleGetSurfRef", 3000, 0, wine_cuModuleGetSurfRef},
    {"cuModuleGetLoadingMode", 11070, 0, wine_cuModuleGetLoadingMode},
    {"cuLibraryLoadData", 12000, 0, wine_cuLibraryLoadData},
    {"cuLibraryLoadFromFile", 12000, 0, wine_cuLibraryLoadFromFile},
    {"cuLibraryUnload", 12000, 0, wine_cuLibraryUnload},
    {"cuLibraryGetKernel", 12000, 0, wine_cuLibraryGetKernel},
    {"cuLibraryGetModule", 12000, 0, wine_cuLibraryGetModule},
    {"cuKernelGetFunction", 12000, 0, wine_cuKernelGetFunction},
    {"cuLibraryGetGlobal", 12000, 0, wine_cuLibraryGetGlobal},
    {"cuLibraryGetManaged", 12000, 0, wine_cuLibraryGetManaged},
    {"cuKernelGetAttribute", 12000, 0, wine_cuKernelGetAttribute},
    {"cuKernelSetAttribute", 12000, 0, wine_cuKernelSetAttribute},
    {"cuKernelSetCacheConfig", 12000, 0, wine_cuKernelSetCacheConfig},
    {"cuLinkCreate", 5050, 0, wine_cuLinkCreate},
    {"cuLinkCreate", 6050, 0, wine_cuLinkCreate_v2},
    {"cuLinkAddData", 5050, 0, wine_cuLinkAddData},
    {"cuLinkAddData", 6050, 0, wine_cuLinkAddData_v2},
    {"cuLinkAddFile", 5050, 0, wine_cuLinkAddFile},
    {"cuLinkComplete", 5050, 0, wine_cuLinkComplete},
    {"cuLinkDestroy", 5050, 0, wine_cuLinkDestroy},
    {"cuMemGetInfo", 2000, 0, wine_cuMemGetInfo},
    {"cuMemGetInfo", 3020, 0, wine_cuMemGetInfo_v2},
    {"cuMemAllocManaged", 6000, 0, wine_cuMemAllocManaged},
    {"cuMemAlloc", 2000, 0, wine_cuMemAlloc},
    {"cuMemAlloc", 3020, 0, wine_cuMemAlloc_v2},
    {"cuMemAllocPitch", 2000, 0, wine_cuMemAllocPitch},
    {"cuMemAllocPitch", 3020, 0, wine_cuMemAllocPitch_v2},
    {"cuMemFree", 2000, 0, wine_cuMemFree},
    {"cuMemFree", 3020, 0, wine_cuMemFree_v2},
    {"cuMemGetAddressRange", 2000, 0, wine_cuMemGetAddressRange},
    {"cuMemGetAddressRange", 3020, 0, wine_cuMemGetAddressRange_v2},
    {"cuMemFreeHost", 2000, 0, wine_cuMemFreeHost},
    {"cuMemHostAlloc", 2020, 0, wine_cuMemHostAlloc},
    {"cuMemHostGetDevicePointer", 2020, 0, wine_cuMemHostGetDevicePointer},
    {"cuMemHostGetDevicePointer", 3020, 0, wine_cuMemHostGetDevicePointer_v2},
    {"cuMemHostGetFlags", 2030, 0, wine_cuMemHostGetFlags},
    {"cuMemHostRegister", 4000, 0, wine_cuMemHostRegister},
    {"cuMemHostRegister", 6050, 0, wine_cuMemHostRegister_v2},
    {"cuMemHostUnregister", 4000, 0, wine_cuMemHostUnregister},
    {"cuPointerGetAttribute", 4000, 0, wine_cuPointerGetAttribute},
    {"cuPointerGetAttributes", 7000, 0, wine_cuPointerGetAttributes},
    {"cuMemAllocAsync", 11020, 0, wine_cuMemAllocAsync},
    {"cuMemAllocAsync", 11020, 2, wine_cuMemAllocAsync_ptsz},
    {"cuMemAllocFromPoolAsync", 11020, 0, wine_cuMemAllocFromPoolAsync},
    {"cuMemAllocFromPoolAsync", 11020, 2, wine_cuMemAllocFromPoolAsync_ptsz},
    {"cuMemFreeAsync", 11020, 0, wine_cuMemFreeAsync},
    {"cuMemFreeAsync", 11020, 2, wine_cuMemFreeAsync_ptsz},
    {"cuMemPoolTrimTo", 11020, 0, wine_cuMemPoolTrimTo},
    {"cuMemPoolSetAttribute", 11020, 0, wine_cuMemPoolSetAttribute},
    {"cuMemPoolGetAttribute", 11020, 0, wine_cuMemPoolGetAttribute},
    {"cuMemPoolSetAccess", 11020, 0, wine_cuMemPoolSetAccess},
    {"cuMemPoolGetAccess", 11020, 0, wine_cuMemPoolGetAccess},
    {"cuMemPoolCreate", 11020, 0, wine_cuMemPoolCreate},
    {"cuMemPoolDestroy", 11020, 0, wine_cuMemPoolDestroy},
    {"cuMemPoolExportToShareableHandle", 11020, 0, wine_cuMemPoolExportToShareableHandle},
    {"cuMemPoolImportFromShareableHandle", 11020, 0, wine_cuMemPoolImportFromShareableHandle},
    {"cuMemPoolExportPointer", 11020, 0, wine_cuMemPoolExportPointer},
    {"cuMemPoolImportPointer", 11020, 0, wine_cuMemPoolImportPointer},
    {"cuMemcpy", 4000, 0, wine_cuMemcpy},
    {"cuMemcpy", 7000, 2, wine_cuMemcpy_ptds},
    {"cuMemcpyAsync", 4000, 0, wine_cuMemcpyAsync},
    {"cuMemcpyAsync", 7000, 2, wine_cuMemcpyAsync_ptsz},
    {"cuMemcpyPeer", 4000, 0, wine_cuMemcpyPeer},
    {"cuMemcpyPeer", 7000, 2, wine_cuMemcpyPeer_ptds},
    {"cuMemcpyPeerAsync", 4000, 0, wine_cuMemcpyPeerAsync},
    {"cuMemcpyPeerAsync", 7000, 2, wine_cuMemcpyPeerAsync_ptsz},
    {"cuMemcpyHtoD", 2000, 0, wine_cuMemcpyHtoD},
    {"cuMemcpyHtoD", 3020, 0, wine_cuMemcpyHtoD_v2},
    {"cuMemcpyHtoD", 7000, 2, wine_cuMemcpyHtoD_v2_ptds},
    {"cuMemcpyHtoDAsync", 2000, 0, wine_cuMemcpyHtoDAsync},
    {"cuMemcpyHtoDAsync", 3020, 0, wine_cuMemcpyHtoDAsync_v2},
    {"cuMemcpyHtoDAsync", 7000, 2, wine_cuMemcpyHtoDAsync_v2_ptsz},
    {"cuMemcpyDtoH", 2000, 0, wine_cuMemcpyDtoH},
    {"cuMemcpyDtoH", 3020, 0, wine_cuMemcpyDtoH_v2},
    {"cuMemcpyDtoH", 7000, 2, wine_cuMemcpyDtoH_v2_ptds},
    {"cuMemcpyDtoHAsync", 2000, 0, wine_cuMemcpyDtoHAsync},
    {"cuMemcpyDtoHAsync", 3020, 0, wine_cuMemcpyDtoHAsync_v2},
    {"cuMemcpyDtoHAsync", 7000, 2, wine_cuMemcpyDtoHAsync_v2_ptsz},
    {"cuMemcpyDtoD", 3000, 0, wine_cuMemcpyDtoD},
    {"cuMemcpyDtoD", 3020, 0, wine_cuMemcpyDtoD_v2},
    {"cuMemcpyDtoD", 7000, 2, wine_cuMemcpyDtoD_v2_ptds},
    {"cuMemcpyDtoDAsync", 3000, 0, wine_cuMemcpyDtoDAsync},
    {"cuMemcpyDtoDAsync", 3020, 0, wine_cuMemcpyDtoDAsync_v2},
    {"cuMemcpyDtoDAsync", 7000, 2, wine_cuMemcpyDtoDAsync_v2_ptsz},
    {"cuMemcpy2DUnaligned", 2000, 0, wine_cuMemcpy2DUnaligned},
    {"cuMemcpy2DUnaligned", 3020, 0, wine_cuMemcpy2DUnaligned_v2},
    {"cuMemcpy2DUnaligned", 7000, 2, wine_cuMemcpy2DUnaligned_v2_ptds},
    {"cuMemcpy2DAsync", 2000, 0, wine_cuMemcpy2DAsync},
    {"cuMemcpy2DAsync", 3020, 0, wine_cuMemcpy2DAsync_v2},
    {"cuMemcpy2DAsync", 7000, 2, wine_cuMemcpy2DAsync_v2_ptsz},
    {"cuMemcpy3D", 2000, 0, wine_cuMemcpy3D},
    {"cuMemcpy3D", 3020, 0, wine_cuMemcpy3D_v2},
    {"cuMemcpy3D", 7000, 2, wine_cuMemcpy3D_v2_ptds},
    {"cuMemcpy3DAsync", 2000, 0, wine_cuMemcpy3DAsync},
    {"cuMemcpy3DAsync", 3020, 0, wine_cuMemcpy3DAsync_v2},
    {"cuMemcpy3DAsync", 7000, 2, wine_cuMemcpy3DAsync_v2_ptsz},
    {"cuMemcpy3DPeer", 4000, 0, wine_cuMemcpy3DPeer},
    {"cuMemcpy3DPeer", 7000, 2, wine_cuMemcpy3DPeer_ptds},
    {"cuMemcpy3DPeerAsync", 4000, 0, wine_cuMemcpy3DPeerAsync},
    {"cuMemcpy3DPeerAsync", 7000, 2, wine_cuMemcpy3DPeerAsync_ptsz},
    {"cuMemsetD8", 2000, 0, wine_cuMemsetD8},
    {"cuMemsetD8", 3020, 0, wine_cuMemsetD8_v2},
    {"cuMemsetD8", 7000, 2, wine_cuMemsetD8_v2_ptds},
    {"cuMemsetD8Async", 3020, 0, wine_cuMemsetD8Async},
    {"cuMemsetD8Async", 7000, 2, wine_cuMemsetD8Async_ptsz},
    {"cuMemsetD2D8Async", 3020, 0, wine_cuMemsetD2D8Async},
    {"cuMemsetD2D8Async", 7000, 2, wine_cuMemsetD2D8Async_ptsz},
    {"cuMemsetD2D8", 2000, 0, wine_cuMemsetD2D8},
    {"cuMemsetD2D8", 3020, 0, wine_cuMemsetD2D8_v2},
    {"cuMemsetD2D8", 7000, 2, wine_cuMemsetD2D8_v2_ptds},
    {"cuFuncSetCacheConfig", 3000, 0, wine_cuFuncSetCacheConfig},
    {"cuFuncSetSharedMemConfig", 4020, 0, wine_cuFuncSetSharedMemConfig},
    {"cuFuncGetAttribute", 2020, 0, wine_cuFuncGetAttribute},
    {"cuFuncSetAttribute", 9000, 0, wine_cuFuncSetAttribute},
    {"cuArrayCreate", 2000, 0, wine_cuArrayCreate},
    {"cuArrayCreate", 3020, 0, wine_cuArrayCreate_v2},
    {"cuArrayGetDescriptor", 2000, 0, wine_cuArrayGetDescriptor},
    {"cuArrayGetDescriptor", 3020, 0, wine_cuArrayGetDescriptor_v2},
    {"cuArrayGetSparseProperties", 11010, 0, wine_cuArrayGetSparseProperties},
    {"cuArrayGetPlane", 11020, 0, wine_cuArrayGetPlane},
    {"cuArray3DCreate", 2000, 0, wine_cuArray3DCreate},
    {"cuArray3DCreate", 3020, 0, wine_cuArray3DCreate_v2},
    {"cuArray3DGetDescriptor", 2000, 0, wine_cuArray3DGetDescriptor},
    {"cuArray3DGetDescriptor", 3020, 0, wine_cuArray3DGetDescriptor_v2},
    {"cuArrayDestroy", 2000, 0, wine_cuArrayDestroy},
    {"cuMipmappedArrayCreate", 5000, 0, wine_cuMipmappedArrayCreate},
    {"cuMipmappedArrayGetLevel", 5000, 0, wine_cuMipmappedArrayGetLevel},
    {"cuMipmappedArrayGetSparseProperties", 11010, 0, wine_cuMipmappedArrayGetSparseProperties},
    {"cuMipmappedArrayDestroy", 5000, 0, wine_cuMipmappedArrayDestroy},
    {"cuTexRefCreate", 2000, 0, wine_cuTexRefCreate},
    {"cuTexRefDestroy", 2000, 0, wine_cuTexRefDestroy},
    {"cuTexRefSetArray", 2000, 0, wine_cuTexRefSetArray},
    {"cuTexRefSetMipmappedArray", 5000, 0, wine_cuTexRefSetMipmappedArray},
    {"cuTexRefSetAddress", 2000, 0, wine_cuTexRefSetAddress},
    {"cuTexRefSetAddress", 3020, 0, wine_cuTexRefSetAddress_v2},
    {"cuTexRefSetAddress2D", 2020, 0, wine_cuTexRefSetAddress2D},
    {"cuTexRefSetAddress2D", 4010, 0, wine_cuTexRefSetAddress2D_v2},
    {"cuTexRefSetFormat", 2000, 0, wine_cuTexRefSetFormat},
    {"cuTexRefSetAddressMode", 2000, 0, wine_cuTexRefSetAddressMode},
    {"cuTexRefSetFilterMode", 2000, 0, wine_cuTexRefSetFilterMode},
    {"cuTexRefSetMipmapFilterMode", 5000, 0, wine_cuTexRefSetMipmapFilterMode},
    {"cuTexRefSetMipmapLevelBias", 5000, 0, wine_cuTexRefSetMipmapLevelBias},
    {"cuTexRefSetMipmapLevelClamp", 5000, 0, wine_cuTexRefSetMipmapLevelClamp},
    {"cuTexRefSetMaxAnisotropy", 5000, 0, wine_cuTexRefSetMaxAnisotropy},
    {"cuTexRefSetFlags", 2000, 0, wine_cuTexRefSetFlags},
    {"cuTexRefSetBorderColor", 8000, 0, wine_cuTexRefSetBorderColor},
    {"cuTexRefGetBorderColor", 8000, 0, wine_cuTexRefGetBorderColor},
    {"cuSurfRefSetArray", 3000, 0, wine_cuSurfRefSetArray},
    {"cuArrayGetMemoryRequirements", 11060, 0, wine_cuArrayGetMemoryRequirements},
    {"cuMipmappedArrayGetMemoryRequirements", 11060, 0, wine_cuMipmappedArrayGetMemoryRequirements},
    {"cuTexObjectCreate", 5000, 0, wine_cuTexObjectCreate},
    {"cuTexObjectDestroy", 5000, 0, wine_cuTexObjectDestroy},
    {"cuTexObjectGetResourceDesc", 5000, 0, wine_cuTexObjectGetResourceDesc},
    {"cuTexObjectGetTextureDesc", 5000, 0, wine_cuTexObjectGetTextureDesc},
    {"cuTexObjectGetResourceViewDesc", 5000, 0, wine_cuTexObjectGetResourceViewDesc},
    {"cuSurfObjectCreate", 5000, 0, wine_cuSurfObjectCreate},
    {"cuSurfObjectDestroy", 5000, 0, wine_cuSurfObjectDestroy},
    {"cuSurfObjectGetResourceDesc", 5000, 0, wine_cuSurfObjectGetResourceDesc},
    {"cuImportExternalMemory", 10000, 0, wine_cuImportExternalMemory},
    {"cuExternalMemoryGetMappedBuffer", 10000, 0, wine_cuExternalMemoryGetMappedBuffer},
    {"cuExternalMemoryGetMappedMipmappedArray", 10000, 0, wine_cuExternalMemoryGetMappedMipmappedArray},
    {"cuDestroyExternalMemory", 10000, 0, wine_cuDestroyExternalMemory},
    {"cuImportExternalSemaphore", 10000, 0, wine_cuImportExternalSemaphore},
    {"cuSignalExternalSemaphoresAsync", 10000, 0, wine_cuSignalExternalSemaphoresAsync},
    {"cuSignalExternalSemaphoresAsync", 10000, 2, wine_cuSignalExternalSemaphoresAsync_ptsz},
    {"cuWaitExternalSemaphoresAsync", 10000, 0, wine_cuWaitExternalSemaphoresAsync},
    {"cuWaitExternalSemaphoresAsync", 10000, 2, wine_cuWaitExternalSemaphoresAsync_ptsz},
    {"cuDestroyExternalSemaphore", 10000, 0, wine_cuDestroyExternalSemaphore},
    {"cuLaunchKernel", 4000, 0, wine_cuLaunchKernel},
    {"cuLaunchKernel", 7000, 2, wine_cuLaunchKernel_ptsz},
    {"cuLaunchCooperativeKernel", 9000, 0, wine_cuLaunchCooperativeKernel},
    {"cuLaunchCooperativeKernel", 9000, 2, wine_cuLaunchCooperativeKernel_ptsz},
    {"cuLaunchCooperativeKernelMultiDevice", 9000, 0, wine_cuLaunchCooperativeKernelMultiDevice},
    {"cuLaunchHostFunc", 10000, 0, wine_cuLaunchHostFunc},
    {"cuLaunchHostFunc", 10000, 2, wine_cuLaunchHostFunc_ptsz},
    {"cuLaunchKernelEx", 11060, 0, wine_cuLaunchKernelEx},
    {"cuLaunchKernelEx", 11060, 2, wine_cuLaunchKernelEx_ptsz},
    {"cuEventCreate", 2000, 0, wine_cuEventCreate},
    {"cuEventRecord", 2000, 0, wine_cuEventRecord},
    {"cuEventRecord", 7000, 2, wine_cuEventRecord_ptsz},
    {"cuEventRecordWithFlags", 11010, 0, wine_cuEventRecordWithFlags},
    {"cuEventRecordWithFlags", 11010, 2, wine_cuEventRecordWithFlags_ptsz},
    {"cuEventQuery", 2000, 0, wine_cuEventQuery},
    {"cuEventSynchronize", 2000, 0, wine_cuEventSynchronize},
    {"cuEventDestroy", 2000, 0, wine_cuEventDestroy},
    {"cuEventDestroy", 4000, 0, wine_cuEventDestroy_v2},
    {"cuEventElapsedTime", 2000, 0, wine_cuEventElapsedTime},
    {"cuStreamWaitValue32", 8000, 0, wine_cuStreamWaitValue32},
    {"cuStreamWaitValue32", 8000, 2, wine_cuStreamWaitValue32_ptsz},
    {"cuStreamWriteValue32", 8000, 0, wine_cuStreamWriteValue32},
    {"cuStreamWriteValue32", 8000, 2, wine_cuStreamWriteValue32_ptsz},
    {"cuStreamWaitValue64", 9000, 0, wine_cuStreamWaitValue64},
    {"cuStreamWaitValue64", 9000, 2, wine_cuStreamWaitValue64_ptsz},
    {"cuStreamWriteValue64", 9000, 0, wine_cuStreamWriteValue64},
    {"cuStreamWriteValue64", 9000, 2, wine_cuStreamWriteValue64_ptsz},
    {"cuStreamBatchMemOp", 8000, 0, wine_cuStreamBatchMemOp},
    {"cuStreamBatchMemOp", 8000, 2, wine_cuStreamBatchMemOp_ptsz},
    {"cuStreamCreate", 2000, 0, wine_cuStreamCreate},
    {"cuStreamCreateWithPriority", 5050, 0, wine_cuStreamCreateWithPriority},
    {"cuStreamGetPriority", 5050, 0, wine_cuStreamGetPriority},
    {"cuStreamGetPriority", 7000, 2, wine_cuStreamGetPriority_ptsz},
    {"cuStreamGetFlags", 5050, 0, wine_cuStreamGetFlags},
    {"cuStreamGetCtx", 9020, 0, wine_cuStreamGetCtx},
    {"cuStreamGetFlags", 7000, 2, wine_cuStreamGetFlags_ptsz},
    {"cuStreamGetId", 12000, 0, wine_cuStreamGetId},
    {"cuStreamGetId", 12000, 2, wine_cuStreamGetId_ptsz},
    {"cuStreamDestroy", 4000, 0, wine_cuStreamDestroy},
    {"cuStreamWaitEvent", 3020, 0, wine_cuStreamWaitEvent},
    {"cuStreamWaitEvent", 7000, 2, wine_cuStreamWaitEvent_ptsz},
    {"cuStreamAddCallback", 5000, 0, wine_cuStreamAddCallback},
    {"cuStreamAddCallback", 7000, 2, wine_cuStreamAddCallback_ptsz},
    {"cuStreamSynchronize", 2000, 0, wine_cuStreamSynchronize},
    {"cuStreamSynchronize", 7000, 2, wine_cuStreamSynchronize_ptsz},
    {"cuStreamQuery", 2000, 0, wine_cuStreamQuery},
    {"cuStreamQuery", 7000, 2, wine_cuStreamQuery},
    {"cuStreamAttachMemAsync", 6000, 0, wine_cuStreamAttachMemAsync},
    {"cuStreamAttachMemAsync", 7000, 2, wine_cuStreamAttachMemAsync_ptsz},
    {"cuStreamCopyAttributes", 11000, 0, wine_cuStreamCopyAttributes},
    {"cuStreamCopyAttributes", 11000, 2, wine_cuStreamCopyAttributes_ptsz},
    {"cuStreamGetAttribute", 11000, 0, wine_cuStreamGetAttribute},
    {"cuStreamGetAttribute", 11000, 2, wine_cuStreamGetAttribute_ptsz},
    {"cuStreamSetAttribute", 11000, 0, wine_cuStreamSetAttribute},
    {"cuStreamSetAttribute", 11000, 2, wine_cuStreamSetAttribute_ptsz},
    {"cuDeviceCanAccessPeer", 4000, 0, wine_cuDeviceCanAccessPeer},
    {"cuCtxEnablePeerAccess", 4000, 0, wine_cuCtxEnablePeerAccess},
    {"cuCtxDisablePeerAccess", 4000, 0, wine_cuCtxDisablePeerAccess},
    {"cuIpcGetEventHandle", 4010, 0, wine_cuIpcGetEventHandle},
    {"cuIpcOpenEventHandle", 4010, 0, wine_cuIpcOpenEventHandle},
    {"cuIpcGetMemHandle", 4010, 0, wine_cuIpcGetMemHandle},
    {"cuIpcOpenMemHandle", 4010, 0, wine_cuIpcOpenMemHandle},
    {"cuIpcOpenMemHandle", 11000, 0, wine_cuIpcOpenMemHandle_v2},
    {"cuIpcCloseMemHandle", 4010, 0, wine_cuIpcCloseMemHandle},
    {"cuGLCtxCreate", 2000, 0, wine_cuGLCtxCreate},
    {"cuGLCtxCreate", 3020, 0, wine_cuGLCtxCreate_v2},
    {"cuGLInit", 2000, 0, wine_cuGLInit},
    {"cuGLGetDevices", 4010, 0, wine_cuGLGetDevices},
    {"cuGLRegisterBufferObject", 2000, 0, wine_cuGLRegisterBufferObject},
    {"cuGLMapBufferObject", 2000, 0, wine_cuGLMapBufferObject},
    {"cuGLMapBufferObject", 3020, 0, wine_cuGLMapBufferObject_v2},
    {"cuGLMapBufferObject", 7000, 2, wine_cuGLMapBufferObject_v2_ptds},
    {"cuGLMapBufferObjectAsync", 2030, 0, wine_cuGLMapBufferObjectAsync},
    {"cuGLMapBufferObjectAsync", 3020, 0, wine_cuGLMapBufferObjectAsync_v2},
    {"cuGLMapBufferObjectAsync", 7000, 2, wine_cuGLMapBufferObjectAsync_v2_ptsz},
    {"cuGLUnmapBufferObject", 2000, 0, wine_cuGLUnmapBufferObject},
    {"cuGLUnmapBufferObjectAsync", 2030, 0, wine_cuGLUnmapBufferObjectAsync},
    {"cuGLUnregisterBufferObject", 2000, 0, wine_cuGLUnregisterBufferObject},
    {"cuGLSetBufferObjectMapFlags", 2030, 0, wine_cuGLSetBufferObjectMapFlags},
    {"cuGraphicsGLRegisterImage", 3000, 0, wine_cuGraphicsGLRegisterImage},
    {"cuGraphicsGLRegisterBuffer", 3000, 0 ,wine_cuGraphicsGLRegisterBuffer},
    {"cuWGLGetDevice", 2020, 0, wine_cuWGLGetDevice},
    {"cuGraphicsUnregisterResource", 3000, 0, wine_cuGraphicsUnregisterResource},
    {"cuGraphicsMapResources", 3000, 0, wine_cuGraphicsMapResources},
    {"cuGraphicsMapResources", 7000, 2, wine_cuGraphicsMapResources_ptsz},
    {"cuGraphicsUnmapResources", 3000, 0, wine_cuGraphicsUnmapResources},
    {"cuGraphicsUnmapResources", 7000, 2, wine_cuGraphicsUnmapResources_ptsz},
    {"cuGraphicsResourceSetMapFlags", 3000, 0, wine_cuGraphicsResourceSetMapFlags},
    {"cuGraphicsResourceSetMapFlags", 6050, 0, wine_cuGraphicsResourceSetMapFlags_v2},
    {"cuGraphicsSubResourceGetMappedArray", 3000, 0, wine_cuGraphicsSubResourceGetMappedArray},
    {"cuGraphicsResourceGetMappedMipmappedArray", 5000, 0, wine_cuGraphicsResourceGetMappedMipmappedArray},
    {"cuGraphicsResourceGetMappedPointer", 3000, 0, wine_cuGraphicsResourceGetMappedPointer},
    {"cuGraphicsResourceGetMappedPointer", 3020, 0, wine_cuGraphicsResourceGetMappedPointer_v2},
    {"cuProfilerInitialize", 4000, 0, wine_cuProfilerInitialize},
    {"cuProfilerStart", 4000, 0, wine_cuProfilerStart},
    {"cuProfilerStop", 4000, 0, wine_cuProfilerStop},
    {"cuD3D11GetDevice", 3000, 0, wine_cuD3D11GetDevice},
    {"cuGraphicsD3D11RegisterResource", 3000, 0, wine_cuGraphicsD3D11RegisterResource},
    {"cuD3D10GetDevice", 2010, 0, wine_cuD3D10GetDevice},
    {"cuGraphicsD3D10RegisterResource", 3000, 0, wine_cuGraphicsD3D10RegisterResource},
    {"cuD3D9GetDevice", 2000, 0, wine_cuD3D9GetDevice},
    {"cuGraphicsD3D9RegisterResource", 3000, 0, wine_cuGraphicsD3D9RegisterResource},
    {"cuGetExportTable", 3000, 0, wine_cuGetExportTable},
    {"cuOccupancyMaxActiveBlocksPerMultiprocessorWithFlags", 7000, 0, wine_cuOccupancyMaxActiveBlocksPerMultiprocessorWithFlags},
    {"cuOccupancyAvailableDynamicSMemPerBlock", 10020, 0, wine_cuOccupancyAvailableDynamicSMemPerBlock},
    {"cuOccupancyMaxPotentialClusterSize", 11070, 0, wine_cuOccupancyMaxPotentialClusterSize},
    {"cuOccupancyMaxActiveClusters", 11070, 0, wine_cuOccupancyMaxActiveClusters},
    {"cuMemAdvise", 8000, 0, wine_cuMemAdvise},
    {"cuMemPrefetchAsync", 8000, 0, wine_cuMemPrefetchAsync},
    {"cuMemPrefetchAsync", 8000, 2, wine_cuMemPrefetchAsync_ptsz},
    {"cuMemRangeGetAttribute", 8000, 0, wine_cuMemRangeGetAttribute},
    {"cuMemRangeGetAttributes", 8000, 0, wine_cuMemRangeGetAttributes},
    {"cuGetErrorString", 6000, 0, wine_cuGetErrorString},
    {"cuGetErrorName", 6000, 0, wine_cuGetErrorName},
    {"cuGraphCreate", 10000, 0, wine_cuGraphCreate},
    {"cuGraphAddKernelNode", 10000, 0, wine_cuGraphAddKernelNode},
    {"cuGraphAddKernelNode", 12000, 0, wine_cuGraphAddKernelNode_v2},
    {"cuGraphKernelNodeGetParams", 10000, 0, wine_cuGraphKernelNodeGetParams},
    {"cuGraphKernelNodeGetParams", 12000, 0, wine_cuGraphKernelNodeGetParams_v2},
    {"cuGraphKernelNodeSetParams", 10000, 0, wine_cuGraphKernelNodeSetParams},
    {"cuGraphKernelNodeSetParams", 12000, 0, wine_cuGraphKernelNodeSetParams_v2},
    {"cuGraphAddMemcpyNode", 10000, 0, wine_cuGraphAddMemcpyNode},
    {"cuGraphMemcpyNodeGetParams", 10000, 0, wine_cuGraphMemcpyNodeGetParams},
    {"cuGraphMemcpyNodeSetParams", 10000, 0, wine_cuGraphMemcpyNodeSetParams},
    {"cuGraphAddMemsetNode", 10000, 0, wine_cuGraphAddMemsetNode},
    {"cuGraphMemsetNodeGetParams", 10000, 0, wine_cuGraphMemsetNodeGetParams},
    {"cuGraphMemsetNodeSetParams", 10000, 0, wine_cuGraphMemsetNodeSetParams},
    {"cuGraphAddHostNode", 10000, 0, wine_cuGraphAddHostNode},
    {"cuGraphHostNodeGetParams", 10000, 0, wine_cuGraphHostNodeGetParams},
    {"cuGraphHostNodeSetParams", 10000, 0, wine_cuGraphHostNodeSetParams},
    {"cuGraphAddChildGraphNode", 10000, 0, wine_cuGraphAddChildGraphNode},
    {"cuGraphChildGraphNodeGetGraph", 10000, 0, wine_cuGraphChildGraphNodeGetGraph},
    {"cuGraphAddEmptyNode", 10000, 0, wine_cuGraphAddEmptyNode},
    {"cuGraphAddEventRecordNode", 11010, 0, wine_cuGraphAddEventRecordNode},
    {"cuGraphEventRecordNodeGetEvent", 11010, 0, wine_cuGraphEventRecordNodeGetEvent},
    {"cuGraphEventRecordNodeSetEvent", 11010, 0, wine_cuGraphEventRecordNodeSetEvent},
    {"cuGraphAddEventWaitNode", 11010, 0, wine_cuGraphAddEventWaitNode},
    {"cuGraphEventWaitNodeGetEvent", 11010, 0, wine_cuGraphEventWaitNodeGetEvent},
    {"cuGraphEventWaitNodeSetEvent", 11010, 0, wine_cuGraphEventWaitNodeSetEvent},
    {"cuGraphAddExternalSemaphoresSignalNode", 11020, 0, wine_cuGraphAddExternalSemaphoresSignalNode},
    {"cuGraphExternalSemaphoresSignalNodeGetParams", 11020, 0, wine_cuGraphExternalSemaphoresSignalNodeGetParams},
    {"cuGraphExternalSemaphoresSignalNodeSetParams", 11020, 0, wine_cuGraphExternalSemaphoresSignalNodeSetParams},
    {"cuGraphAddExternalSemaphoresWaitNode", 11020, 0, wine_cuGraphAddExternalSemaphoresWaitNode},
    {"cuGraphExternalSemaphoresWaitNodeGetParams", 11020, 0, wine_cuGraphExternalSemaphoresWaitNodeGetParams},
    {"cuGraphExternalSemaphoresWaitNodeSetParams", 11020, 0, wine_cuGraphExternalSemaphoresWaitNodeSetParams},
    {"cuGraphExecExternalSemaphoresSignalNodeSetParams", 11020, 0, wine_cuGraphExecExternalSemaphoresSignalNodeSetParams},
    {"cuGraphExecExternalSemaphoresWaitNodeSetParams", 11020, 0, wine_cuGraphExecExternalSemaphoresWaitNodeSetParams},
    {"cuGraphAddMemAllocNode", 11040, 0, wine_cuGraphAddMemAllocNode},
    {"cuGraphMemAllocNodeGetParams", 11040, 0, wine_cuGraphMemAllocNodeGetParams},
    {"cuGraphAddMemFreeNode", 11040, 0, wine_cuGraphAddMemFreeNode},
    {"cuGraphMemFreeNodeGetParams", 11040, 0, wine_cuGraphMemFreeNodeGetParams},
    {"cuDeviceGraphMemTrim", 11040, 0, wine_cuDeviceGraphMemTrim},
    {"cuDeviceGetGraphMemAttribute", 11040, 0, wine_cuDeviceGetGraphMemAttribute},
    {"cuDeviceSetGraphMemAttribute", 11040, 0, wine_cuDeviceSetGraphMemAttribute},
    {"cuGraphClone", 10000, 0, wine_cuGraphClone},
    {"cuGraphNodeFindInClone", 10000, 0, wine_cuGraphNodeFindInClone},
    {"cuGraphNodeGetType", 10000, 0, wine_cuGraphNodeGetType},
    {"cuGraphGetNodes", 10000, 0, wine_cuGraphGetNodes},
    {"cuGraphGetRootNodes", 10000, 0, wine_cuGraphGetRootNodes},
    {"cuGraphGetEdges", 10000, 0, wine_cuGraphGetEdges},
    {"cuGraphGetEdges", 12030, 0, wine_cuGraphGetEdges_v2},
    {"cuGraphNodeGetDependencies", 10000, 0, wine_cuGraphNodeGetDependencies},
    {"cuGraphNodeGetDependencies", 12030, 0, wine_cuGraphNodeGetDependencies_v2},
    {"cuGraphNodeGetDependentNodes", 10000, 0, wine_cuGraphNodeGetDependentNodes},
    {"cuGraphNodeGetDependentNodes", 12030, 0, wine_cuGraphNodeGetDependentNodes_v2},
    {"cuGraphAddDependencies", 10000, 0, wine_cuGraphAddDependencies},
    {"cuGraphAddDependencies", 12030, 0, wine_cuGraphAddDependencies_v2},
    {"cuGraphRemoveDependencies", 10000, 0, wine_cuGraphRemoveDependencies},
    {"cuGraphRemoveDependencies", 12030, 0, wine_cuGraphRemoveDependencies_v2},
    {"cuGraphDestroyNode", 10000, 0, wine_cuGraphDestroyNode},
    {"cuGraphInstantiate", 10000, 0, wine_cuGraphInstantiate},
    {"cuGraphInstantiate", 11000, 0, wine_cuGraphInstantiate_v2},
    {"cuGraphInstantiateWithFlags", 11040, 0, wine_cuGraphInstantiateWithFlags},
    {"cuGraphUpload", 11010, 0, wine_cuGraphUpload},
    {"cuGraphUpload", 11010, 2, wine_cuGraphUpload_ptsz},
    {"cuGraphLaunch", 10000, 0, wine_cuGraphLaunch},
    {"cuGraphLaunch", 10000, 2, wine_cuGraphLaunch_ptsz},
    {"cuGraphExecDestroy", 10000, 0, wine_cuGraphExecDestroy},
    {"cuGraphDestroy", 10000, 0, wine_cuGraphDestroy},
    {"cuStreamBeginCapture", 10000, 0, wine_cuStreamBeginCapture},
    {"cuStreamBeginCapture", 10000, 2, wine_cuStreamBeginCapture_ptsz},
    {"cuStreamBeginCapture", 10010, 0, wine_cuStreamBeginCapture_v2},
    {"cuStreamBeginCapture", 10010, 2, wine_cuStreamBeginCapture_v2_ptsz},
    {"cuStreamEndCapture", 10000, 0, wine_cuStreamEndCapture},
    {"cuStreamEndCapture", 10000, 2, wine_cuStreamEndCapture_ptsz},
    {"cuStreamIsCapturing", 10000, 0, wine_cuStreamIsCapturing},
    {"cuStreamIsCapturing", 10000, 2, wine_cuStreamIsCapturing_ptsz},
    {"cuStreamGetCaptureInfo", 10010, 0, wine_cuStreamGetCaptureInfo},
    {"cuStreamGetCaptureInfo", 10010, 2, wine_cuStreamGetCaptureInfo_ptsz},
    {"cuStreamGetCaptureInfo", 11030, 0, wine_cuStreamGetCaptureInfo_v2},
    {"cuStreamGetCaptureInfo", 11030, 2, wine_cuStreamGetCaptureInfo_v2_ptsz},
    {"cuStreamGetCaptureInfo", 12030, 0, wine_cuStreamGetCaptureInfo_v3},
    {"cuStreamGetCaptureInfo", 12030, 2, wine_cuStreamGetCaptureInfo_v3_ptsz},
    {"cuStreamUpdateCaptureDependencies", 11030, 0, wine_cuStreamUpdateCaptureDependencies},
    {"cuStreamUpdateCaptureDependencies", 11030, 2, wine_cuStreamUpdateCaptureDependencies_ptsz},
    {"cuStreamUpdateCaptureDependencies", 12030, 0, wine_cuStreamUpdateCaptureDependencies_v2},
    {"cuStreamUpdateCaptureDependencies", 12030, 2, wine_cuStreamUpdateCaptureDependencies_v2_ptsz},
    {"cuGraphExecKernelNodeSetParams", 10010, 0, wine_cuGraphExecKernelNodeSetParams},
    {"cuGraphExecKernelNodeSetParams", 12000, 0, wine_cuGraphExecKernelNodeSetParams_v2},
    {"cuGraphExecMemcpyNodeSetParams", 10020, 0, wine_cuGraphExecMemcpyNodeSetParams},
    {"cuGraphExecMemsetNodeSetParams", 10020, 0, wine_cuGraphExecMemsetNodeSetParams},
    {"cuGraphExecHostNodeSetParams", 10020, 0, wine_cuGraphExecHostNodeSetParams},
    {"cuGraphExecChildGraphNodeSetParams", 11010, 0, wine_cuGraphExecChildGraphNodeSetParams},
    {"cuGraphExecEventRecordNodeSetEvent", 11010, 0, wine_cuGraphExecEventRecordNodeSetEvent},
    {"cuGraphExecEventWaitNodeSetEvent", 11010, 0, wine_cuGraphExecEventWaitNodeSetEvent},
    {"cuThreadExchangeStreamCaptureMode", 10010, 0, wine_cuThreadExchangeStreamCaptureMode},
    {"cuGraphExecUpdate", 10020, 0, wine_cuGraphExecUpdate},
    {"cuGraphExecUpdate", 12000, 0, wine_cuGraphExecUpdate_v2},
    {"cuGraphKernelNodeCopyAttributes", 11000, 0, wine_cuGraphKernelNodeCopyAttributes},
    {"cuGraphKernelNodeGetAttribute", 11000, 0, wine_cuGraphKernelNodeGetAttribute},
    {"cuGraphKernelNodeSetAttribute", 11000, 0, wine_cuGraphKernelNodeSetAttribute},
    {"cuGraphDebugDotPrint", 11030, 0, wine_cuGraphDebugDotPrint},
    {"cuUserObjectCreate", 11030, 0, wine_cuUserObjectCreate},
    {"cuUserObjectRetain", 11030, 0, wine_cuUserObjectRetain},
    {"cuUserObjectRelease", 11030, 0, wine_cuUserObjectRelease},
    {"cuGraphRetainUserObject", 11030, 0, wine_cuGraphRetainUserObject},
    {"cuGraphReleaseUserObject", 11030, 0, wine_cuGraphReleaseUserObject},
    {"cuGraphNodeSetEnabled", 11060, 0, wine_cuGraphNodeSetEnabled},
    {"cuGraphNodeGetEnabled", 11060, 0, wine_cuGraphNodeGetEnabled},
    {"cuGraphInstantiateWithParams", 12000, 0, wine_cuGraphInstantiateWithParams},
    {"cuGraphInstantiateWithParams", 12000, 2, wine_cuGraphInstantiateWithParams_ptsz},
    {"cuGraphInstantiateWithParams_ptsz", 12000, 2, wine_cuGraphInstantiateWithParams_ptsz},
    {"cuGraphExecGetFlags", 12000, 0, wine_cuGraphExecGetFlags},
    {"cuMemAdvise", 12020, 0, wine_cuMemAdvise_v2},
    {"cuMemPrefetchAsync", 12020, 0, wine_cuMemPrefetchAsync_v2},
    {"cuMemPrefetchAsync", 12020, 2, wine_cuMemPrefetchAsync_v2_ptsz},
    {"cuGraphAddNode", 12020, 0, wine_cuGraphAddNode},
    {"cuGraphAddNode", 12030, 0, wine_cuGraphAddNode_v2},
    {"cuGraphNodeSetParams", 12020, 0, wine_cuGraphNodeSetParams},
    {"cuGraphExecNodeSetParams", 12020, 0, wine_cuGraphExecNodeSetParams},
    {"cuKernelGetName", 12030, 0, wine_cuKernelGetName},
    {"cuFuncGetName", 12030, 0, wine_cuFuncGetName},
    {"cuStreamBeginCaptureToGraph", 12030, 0, wine_cuStreamBeginCaptureToGraph},
    {"cuStreamBeginCaptureToGraph", 12030, 2, wine_cuStreamBeginCaptureToGraph_ptsz},
    {"cuGraphConditionalHandleCreate", 12030, 0, wine_cuGraphConditionalHandleCreate},
    {"cuFuncGetModule", 11000, 0, wine_cuFuncGetModule},
};

const size_t mappings_count = sizeof(mappings) / sizeof(mappings[0]);
