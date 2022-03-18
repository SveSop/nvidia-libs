@ stdcall cuArray3DCreate(ptr ptr) wine_cuArray3DCreate
@ stdcall cuArray3DCreate_v2(ptr ptr) wine_cuArray3DCreate_v2
@ stdcall cuArray3DGetDescriptor(ptr ptr) wine_cuArray3DGetDescriptor
@ stdcall cuArray3DGetDescriptor_v2(ptr ptr) wine_cuArray3DGetDescriptor_v2
@ stdcall cuArrayCreate(ptr ptr) wine_cuArrayCreate
@ stdcall cuArrayCreate_v2(ptr ptr) wine_cuArrayCreate_v2
@ stdcall cuArrayDestroy(ptr) wine_cuArrayDestroy
@ stdcall cuArrayGetDescriptor(ptr ptr) wine_cuArrayGetDescriptor
@ stdcall cuArrayGetDescriptor_v2(ptr ptr) wine_cuArrayGetDescriptor_v2
@ stdcall cuCtxAttach(ptr long) wine_cuCtxAttach
@ stdcall cuCtxCreate(ptr long long) wine_cuCtxCreate
@ stdcall cuCtxCreate_v2(ptr long long) wine_cuCtxCreate_v2
@ stdcall cuCtxDestroy(ptr) wine_cuCtxDestroy
@ stdcall cuCtxDestroy_v2(ptr) wine_cuCtxDestroy_v2
@ stdcall cuCtxDetach(ptr) wine_cuCtxDetach
@ stdcall cuCtxDisablePeerAccess(ptr) wine_cuCtxDisablePeerAccess
@ stdcall cuCtxEnablePeerAccess(ptr long) wine_cuCtxEnablePeerAccess
@ stdcall cuCtxGetApiVersion(ptr ptr) wine_cuCtxGetApiVersion
@ stdcall cuCtxGetCacheConfig(ptr) wine_cuCtxGetCacheConfig
@ stdcall cuCtxGetCurrent(ptr) wine_cuCtxGetCurrent
@ stdcall cuCtxGetDevice(ptr) wine_cuCtxGetDevice
@ stdcall cuCtxGetFlags(ptr) wine_cuCtxGetFlags
@ stdcall cuCtxGetLimit(ptr long) wine_cuCtxGetLimit
@ stdcall cuCtxGetSharedMemConfig(ptr) wine_cuCtxGetSharedMemConfig
@ stdcall cuCtxGetStreamPriorityRange(ptr ptr) wine_cuCtxGetStreamPriorityRange
@ stdcall cuCtxPopCurrent(ptr) wine_cuCtxPopCurrent
@ stdcall cuCtxPopCurrent_v2(ptr) wine_cuCtxPopCurrent_v2
@ stdcall cuCtxPushCurrent(ptr) wine_cuCtxPushCurrent
@ stdcall cuCtxPushCurrent_v2(ptr) wine_cuCtxPushCurrent_v2
@ stdcall cuCtxSetCacheConfig(long) wine_cuCtxSetCacheConfig
@ stdcall cuCtxSetCurrent(ptr) wine_cuCtxSetCurrent
@ stdcall cuCtxSetLimit(long long) wine_cuCtxSetLimit
@ stdcall cuCtxSetSharedMemConfig(long) wine_cuCtxSetSharedMemConfig
@ stdcall cuCtxSynchronize() wine_cuCtxSynchronize
@ stub cuD3D10CtxCreate
@ stub cuD3D10CtxCreateOnDevice
@ stub cuD3D10CtxCreate_v2
@ stdcall cuD3D10GetDevice(ptr ptr) wine_cuD3D10GetDevice
@ stub cuD3D10GetDevices
@ stub cuD3D10GetDirect3DDevice
@ stub cuD3D10MapResources
@ stub cuD3D10RegisterResource
@ stub cuD3D10ResourceGetMappedArray
@ stub cuD3D10ResourceGetMappedPitch
@ stub cuD3D10ResourceGetMappedPitch_v2
@ stub cuD3D10ResourceGetMappedPointer
@ stub cuD3D10ResourceGetMappedPointer_v2
@ stub cuD3D10ResourceGetMappedSize
@ stub cuD3D10ResourceGetMappedSize_v2
@ stub cuD3D10ResourceGetSurfaceDimensions
@ stub cuD3D10ResourceGetSurfaceDimensions_v2
@ stub cuD3D10ResourceSetMapFlags
@ stub cuD3D10UnmapResources
@ stub cuD3D10UnregisterResource
@ stub cuD3D11CtxCreate
@ stub cuD3D11CtxCreateOnDevice
@ stub cuD3D11CtxCreate_v2
@ stdcall cuD3D11GetDevice(ptr ptr) wine_cuD3D11GetDevice
@ stub cuD3D11GetDevices
@ stub cuD3D11GetDirect3DDevice
@ stub cuD3D9Begin
@ stdcall cuD3D9CtxCreate(ptr ptr long ptr) wine_cuD3D9CtxCreate
@ stub cuD3D9CtxCreateOnDevice
@ stub cuD3D9CtxCreate_v2
@ stub cuD3D9End
@ stdcall cuD3D9GetDevice(ptr str) wine_cuD3D9GetDevice
@ stub cuD3D9GetDevices
@ stub cuD3D9GetDirect3DDevice
@ stub cuD3D9MapResources
@ stub cuD3D9MapVertexBuffer
@ stub cuD3D9MapVertexBuffer_v2
@ stub cuD3D9RegisterResource
@ stub cuD3D9RegisterVertexBuffer
@ stub cuD3D9ResourceGetMappedArray
@ stub cuD3D9ResourceGetMappedPitch
@ stub cuD3D9ResourceGetMappedPitch_v2
@ stub cuD3D9ResourceGetMappedPointer
@ stub cuD3D9ResourceGetMappedPointer_v2
@ stub cuD3D9ResourceGetMappedSize
@ stub cuD3D9ResourceGetMappedSize_v2
@ stub cuD3D9ResourceGetSurfaceDimensions
@ stub cuD3D9ResourceGetSurfaceDimensions_v2
@ stub cuD3D9ResourceSetMapFlags
@ stub cuD3D9UnmapResources
@ stub cuD3D9UnmapVertexBuffer
@ stub cuD3D9UnregisterResource
@ stub cuD3D9UnregisterVertexBuffer
@ stub cuDestroyExternalMemory
@ stub cuDestroyExternalSemaphore
@ stdcall cuDeviceCanAccessPeer(ptr long long) wine_cuDeviceCanAccessPeer
@ stdcall cuDeviceComputeCapability(ptr ptr long) wine_cuDeviceComputeCapability
@ stdcall cuDeviceGet(ptr long) wine_cuDeviceGet
@ stdcall cuDeviceGetAttribute(ptr long long) wine_cuDeviceGetAttribute
@ stdcall cuDeviceGetByPCIBusId(ptr str) wine_cuDeviceGetByPCIBusId
@ stdcall cuDeviceGetCount(ptr) wine_cuDeviceGetCount
@ stdcall cuDeviceGetDefaultMemPool(ptr long) wine_cuDeviceGetDefaultMemPool
@ stdcall cuDeviceGetGraphMemAttribute(long long ptr) wine_cuDeviceGetGraphMemAttribute
@ stdcall cuDeviceGetLuid(ptr ptr long) wine_cuDeviceGetLuid
@ stdcall cuDeviceGetName(ptr long long) wine_cuDeviceGetName
@ stub cuDeviceGetP2PAttribute
@ stdcall cuDeviceGetPCIBusId(ptr long long) wine_cuDeviceGetPCIBusId
@ stdcall cuDeviceGetProperties(ptr long) wine_cuDeviceGetProperties
@ stdcall cuDeviceGetUuid(ptr long) wine_cuDeviceGetUuid
@ stdcall cuDeviceGraphMemTrim(long) wine_cuDeviceGraphMemTrim
@ stdcall cuDevicePrimaryCtxGetState(long ptr ptr) wine_cuDevicePrimaryCtxGetState
@ stdcall cuDevicePrimaryCtxRelease(long) wine_cuDevicePrimaryCtxRelease
@ stdcall cuDevicePrimaryCtxReset(long) wine_cuDevicePrimaryCtxReset
@ stdcall cuDevicePrimaryCtxRetain(ptr long) wine_cuDevicePrimaryCtxRetain
@ stdcall cuDevicePrimaryCtxSetFlags(long long) wine_cuDevicePrimaryCtxSetFlags
@ stdcall cuDeviceTotalMem(ptr long) wine_cuDeviceTotalMem
@ stdcall cuDeviceTotalMem_v2(ptr long) wine_cuDeviceTotalMem_v2
@ stdcall cuDriverGetVersion(ptr) wine_cuDriverGetVersion
@ stdcall cuEventCreate(ptr long) wine_cuEventCreate
@ stdcall cuEventDestroy(ptr) wine_cuEventDestroy
@ stdcall cuEventDestroy_v2(ptr) wine_cuEventDestroy_v2
@ stdcall cuEventElapsedTime(ptr ptr ptr) wine_cuEventElapsedTime
@ stdcall cuEventQuery(ptr) wine_cuEventQuery
@ stdcall cuEventRecord(ptr ptr) wine_cuEventRecord
@ stdcall cuEventRecord_ptsz(ptr ptr) wine_cuEventRecord_ptsz
@ stdcall cuEventSynchronize(ptr) wine_cuEventSynchronize
@ stub cuExternalMemoryGetMappedBuffer
@ stub cuExternalMemoryGetMappedMipmappedArray
@ stdcall cuFuncGetAttribute(ptr long ptr) wine_cuFuncGetAttribute
@ stub cuFuncSetAttribute
@ stdcall cuFuncSetBlockShape(ptr long long long) wine_cuFuncSetBlockShape
@ stdcall cuFuncSetCacheConfig(ptr long) wine_cuFuncSetCacheConfig
@ stdcall cuFuncSetSharedMemConfig(ptr long) wine_cuFuncSetSharedMemConfig
@ stdcall cuFuncSetSharedSize(ptr long) wine_cuFuncSetSharedSize
@ stdcall cuGLCtxCreate(ptr long long) wine_cuGLCtxCreate
@ stdcall cuGLCtxCreate_v2(ptr long long) wine_cuGLCtxCreate_v2
@ stdcall cuGLGetDevices(ptr ptr long long) wine_cuGLGetDevices
@ stdcall cuGLGetDevices_v2(ptr ptr long long) wine_cuGLGetDevices_v2
@ stdcall cuGLInit() wine_cuGLInit
@ stdcall cuGLMapBufferObject(ptr ptr long) wine_cuGLMapBufferObject
@ stdcall cuGLMapBufferObjectAsync(ptr ptr long ptr) wine_cuGLMapBufferObjectAsync
@ stdcall cuGLMapBufferObjectAsync_v2(ptr ptr long ptr) wine_cuGLMapBufferObjectAsync_v2
@ stdcall cuGLMapBufferObjectAsync_v2_ptsz(ptr ptr long ptr) wine_cuGLMapBufferObjectAsync_v2_ptsz
@ stdcall cuGLMapBufferObject_v2(ptr ptr long) wine_cuGLMapBufferObject_v2
@ stdcall cuGLMapBufferObject_v2_ptds(ptr ptr long) wine_cuGLMapBufferObject_v2_ptds
@ stdcall cuGLRegisterBufferObject(long) wine_cuGLRegisterBufferObject
@ stdcall cuGLSetBufferObjectMapFlags(long long) wine_cuGLSetBufferObjectMapFlags
@ stdcall cuGLUnmapBufferObject(long) wine_cuGLUnmapBufferObject
@ stdcall cuGLUnmapBufferObjectAsync(long ptr) wine_cuGLUnmapBufferObjectAsync
@ stdcall cuGLUnregisterBufferObject(long) wine_cuGLUnregisterBufferObject
@ stdcall cuGetErrorName(long ptr) wine_cuGetErrorName
@ stdcall cuGetErrorString(long ptr) wine_cuGetErrorString
@ stdcall cuGetExportTable(ptr ptr) wine_cuGetExportTable
@ stub cuGraphAddChildGraphNode
@ stub cuGraphAddDependencies
@ stub cuGraphAddEmptyNode
@ stdcall cuGraphAddHostNode(ptr ptr ptr long ptr) wine_cuGraphAddHostNode
@ stdcall cuGraphAddKernelNode(ptr ptr ptr long ptr) wine_cuGraphAddKernelNode
@ stdcall cuGraphAddMemAllocNode(ptr ptr ptr long ptr) wine_cuGraphAddMemAllocNode
@ stdcall cuGraphAddMemFreeNode(ptr ptr ptr long long) wine_cuGraphAddMemFreeNode
@ stdcall cuGraphAddMemcpyNode(ptr ptr ptr long ptr ptr) wine_cuGraphAddMemcpyNode
@ stdcall cuGraphAddMemsetNode(ptr ptr ptr long ptr ptr) wine_cuGraphAddMemsetNode
@ stub cuGraphChildGraphNodeGetGraph
@ stdcall cuGraphClone(ptr ptr) wine_cuGraphClone
@ stdcall cuGraphCreate(ptr long) wine_cuGraphCreate
@ stdcall cuGraphDestroy(ptr) wine_cuGraphDestroy
@ stdcall cuGraphDestroyNode(ptr) wine_cuGraphDestroyNode
@ stdcall cuGraphExecDestroy(ptr) wine_cuGraphExecDestroy
@ stdcall cuGraphExecKernelNodeSetParams(ptr ptr ptr) wine_cuGraphExecKernelNodeSetParams
@ stub cuGraphGetEdges
@ stdcall cuGraphGetNodes(ptr ptr long) wine_cuGraphGetNodes
@ stub cuGraphGetRootNodes
@ stub cuGraphHostNodeGetParams
@ stub cuGraphHostNodeSetParams
@ stdcall cuGraphInstantiate(ptr ptr ptr ptr long) wine_cuGraphInstantiate_v2
@ stdcall cuGraphInstantiate_v2(ptr ptr ptr ptr long) wine_cuGraphInstantiate_v2
@ stub cuGraphKernelNodeGetParams
@ stub cuGraphKernelNodeSetParams
@ stdcall cuGraphLaunch(ptr ptr) wine_cuGraphLaunch
@ stub cuGraphLaunch_ptsz
@ stub cuGraphMemcpyNodeGetParams
@ stub cuGraphMemcpyNodeSetParams
@ stub cuGraphMemsetNodeGetParams
@ stub cuGraphMemsetNodeSetParams
@ stub cuGraphNodeFindInClone
@ stub cuGraphNodeGetDependencies
@ stub cuGraphNodeGetDependentNodes
@ stub cuGraphNodeGetType
@ stub cuGraphRemoveDependencies
@ stub cuGraphicsD3D10RegisterResource
@ stdcall cuGraphicsD3D11RegisterResource(ptr ptr long) wine_cuGraphicsD3D11RegisterResource
@ stub cuGraphicsD3D9RegisterResource
@ stdcall cuGraphicsGLRegisterBuffer(ptr long long) wine_cuGraphicsGLRegisterBuffer
@ stdcall cuGraphicsGLRegisterImage(ptr long long long) wine_cuGraphicsGLRegisterImage
@ stdcall cuGraphicsMapResources(long ptr ptr) wine_cuGraphicsMapResources
@ stdcall cuGraphicsMapResources_ptsz(long ptr ptr) wine_cuGraphicsMapResources_ptsz
@ stdcall cuGraphicsResourceGetMappedMipmappedArray(ptr ptr) wine_cuGraphicsResourceGetMappedMipmappedArray
@ stdcall cuGraphicsResourceGetMappedPointer(ptr ptr ptr) wine_cuGraphicsResourceGetMappedPointer
@ stdcall cuGraphicsResourceGetMappedPointer_v2(ptr ptr ptr) wine_cuGraphicsResourceGetMappedPointer_v2
@ stdcall cuGraphicsResourceSetMapFlags(ptr long) wine_cuGraphicsResourceSetMapFlags
@ stdcall cuGraphicsResourceSetMapFlags_v2(ptr long) wine_cuGraphicsResourceSetMapFlags_v2
@ stdcall cuGraphicsSubResourceGetMappedArray(ptr ptr long long) wine_cuGraphicsSubResourceGetMappedArray
@ stdcall cuGraphicsUnmapResources(long ptr ptr) wine_cuGraphicsUnmapResources
@ stdcall cuGraphicsUnmapResources_ptsz(long ptr ptr) wine_cuGraphicsUnmapResources_ptsz
@ stdcall cuGraphicsUnregisterResource(ptr) wine_cuGraphicsUnregisterResource
@ stub cuImportExternalMemory
@ stub cuImportExternalSemaphore
@ stdcall cuInit(long) wine_cuInit
@ stdcall cuIpcCloseMemHandle(long) wine_cuIpcCloseMemHandle
@ stdcall cuIpcGetEventHandle(ptr ptr) wine_cuIpcGetEventHandle
@ stdcall cuIpcGetMemHandle(ptr long) wine_cuIpcGetMemHandle
@ stdcall cuIpcOpenEventHandle(ptr ptr) wine_cuIpcOpenEventHandle
@ stdcall cuIpcOpenMemHandle(ptr ptr long) wine_cuIpcOpenMemHandle
@ stdcall cuLaunch(ptr) wine_cuLaunch
@ stub cuLaunchCooperativeKernel
@ stub cuLaunchCooperativeKernelMultiDevice
@ stub cuLaunchCooperativeKernel_ptsz
@ stdcall cuLaunchGrid(ptr long long) wine_cuLaunchGrid
@ stdcall cuLaunchGridAsync(ptr long long ptr) wine_cuLaunchGridAsync
@ stub cuLaunchHostFunc
@ stub cuLaunchHostFunc_ptsz
@ stdcall cuLaunchKernel(ptr long long long long long long long ptr ptr ptr) wine_cuLaunchKernel
@ stdcall cuLaunchKernel_ptsz(ptr long long long long long long long ptr ptr ptr) wine_cuLaunchKernel_ptsz
@ stdcall cuLinkAddData(ptr long ptr long str long ptr ptr) wine_cuLinkAddData
@ stdcall cuLinkAddData_v2(ptr long ptr long str long ptr ptr) wine_cuLinkAddData_v2
@ stub cuLinkAddFile
@ stub cuLinkAddFile_v2
@ stdcall cuLinkComplete(ptr ptr ptr) wine_cuLinkComplete
@ stdcall cuLinkCreate(long ptr ptr ptr) wine_cuLinkCreate
@ stdcall cuLinkCreate_v2(long ptr ptr ptr) wine_cuLinkCreate_v2
@ stdcall cuLinkDestroy(ptr) wine_cuLinkDestroy
@ stub cuMemAdvise
@ stdcall cuMemAlloc(ptr long) wine_cuMemAlloc
@ stdcall cuMemAllocAsync(ptr long ptr) wine_cuMemAllocAsync
@ stdcall cuMemAllocHost(ptr long) wine_cuMemAllocHost
@ stdcall cuMemAllocHost_v2(ptr long) wine_cuMemAllocHost_v2
@ stdcall cuMemAllocManaged(ptr long long) wine_cuMemAllocManaged
@ stdcall cuMemAllocPitch(ptr ptr long long long) wine_cuMemAllocPitch
@ stdcall cuMemAllocPitch_v2(ptr ptr long long long) wine_cuMemAllocPitch_v2
@ stdcall cuMemAlloc_v2(ptr long) wine_cuMemAlloc_v2
@ stdcall cuMemFree(long) wine_cuMemFree
@ stdcall cuMemFreeAsync(ptr ptr) wine_cuMemFreeAsync
@ stdcall cuMemFreeHost(ptr) wine_cuMemFreeHost
@ stdcall cuMemFree_v2(long) wine_cuMemFree_v2
@ stdcall cuMemGetAddressRange(ptr ptr long) wine_cuMemGetAddressRange
@ stdcall cuMemGetAddressRange_v2(ptr ptr long) wine_cuMemGetAddressRange_v2
@ stdcall cuMemGetInfo(ptr ptr) wine_cuMemGetInfo
@ stdcall cuMemGetInfo_v2(ptr ptr) wine_cuMemGetInfo_v2
@ stdcall cuMemHostAlloc(ptr long long) wine_cuMemHostAlloc
@ stdcall cuMemHostGetDevicePointer(ptr ptr long) wine_cuMemHostGetDevicePointer
@ stdcall cuMemHostGetDevicePointer_v2(ptr ptr long) wine_cuMemHostGetDevicePointer_v2
@ stdcall cuMemHostGetFlags(ptr ptr) wine_cuMemHostGetFlags
@ stdcall cuMemHostRegister(ptr long long) wine_cuMemHostRegister
@ stdcall cuMemHostRegister_v2(ptr long long) wine_cuMemHostRegister_v2
@ stdcall cuMemHostUnregister(ptr) wine_cuMemHostUnregister
@ stdcall cuMemPoolSetAttribute(ptr long ptr) wine_cuMemPoolSetAttribute
@ stub cuMemPrefetchAsync
@ stub cuMemPrefetchAsync_ptsz
@ stub cuMemRangeGetAttribute
@ stub cuMemRangeGetAttributes
@ stdcall cuMemcpy(long long long) wine_cuMemcpy
@ stdcall cuMemcpy2D(ptr) wine_cuMemcpy2D
@ stdcall cuMemcpy2DAsync(ptr ptr) wine_cuMemcpy2DAsync
@ stdcall cuMemcpy2DAsync_v2(ptr ptr) wine_cuMemcpy2DAsync_v2
@ stdcall cuMemcpy2DAsync_v2_ptsz(ptr ptr) wine_cuMemcpy2DAsync_v2_ptsz
@ stdcall cuMemcpy2DUnaligned(ptr) wine_cuMemcpy2DUnaligned
@ stdcall cuMemcpy2DUnaligned_v2(ptr) wine_cuMemcpy2DUnaligned_v2
@ stdcall cuMemcpy2DUnaligned_v2_ptds(ptr) wine_cuMemcpy2DUnaligned_v2_ptds
@ stdcall cuMemcpy2D_v2(ptr) wine_cuMemcpy2D_v2
@ stdcall cuMemcpy2D_v2_ptds(ptr) wine_cuMemcpy2D_v2_ptds
@ stdcall cuMemcpy3D(ptr) wine_cuMemcpy3D
@ stdcall cuMemcpy3DAsync(ptr ptr) wine_cuMemcpy3DAsync
@ stdcall cuMemcpy3DAsync_v2(ptr ptr) wine_cuMemcpy3DAsync_v2
@ stdcall cuMemcpy3DAsync_v2_ptsz(ptr ptr) wine_cuMemcpy3DAsync_v2_ptsz
@ stdcall cuMemcpy3DPeer(ptr) wine_cuMemcpy3DPeer
@ stdcall cuMemcpy3DPeerAsync(ptr ptr) wine_cuMemcpy3DPeerAsync
@ stdcall cuMemcpy3DPeerAsync_ptsz(ptr ptr) wine_cuMemcpy3DPeerAsync_ptsz
@ stdcall cuMemcpy3DPeer_ptds(ptr) wine_cuMemcpy3DPeer_ptds
@ stdcall cuMemcpy3D_v2(ptr) wine_cuMemcpy3D_v2
@ stdcall cuMemcpy3D_v2_ptds(ptr) wine_cuMemcpy3D_v2_ptds
@ stdcall cuMemcpyAsync(long long long ptr) wine_cuMemcpyAsync
@ stdcall cuMemcpyAsync_ptsz(long long long ptr) wine_cuMemcpyAsync_ptsz
@ stdcall cuMemcpyAtoA(ptr long ptr long long) wine_cuMemcpyAtoA
@ stdcall cuMemcpyAtoA_v2(ptr long ptr long long) wine_cuMemcpyAtoA_v2
@ stdcall cuMemcpyAtoA_v2_ptds(ptr long ptr long long) wine_cuMemcpyAtoA_v2_ptds
@ stdcall cuMemcpyAtoD(long ptr long long) wine_cuMemcpyAtoD
@ stdcall cuMemcpyAtoD_v2(long ptr long long) wine_cuMemcpyAtoD_v2
@ stdcall cuMemcpyAtoD_v2_ptds(long ptr long long) wine_cuMemcpyAtoD_v2_ptds
@ stdcall cuMemcpyAtoH(ptr ptr long long) wine_cuMemcpyAtoH
@ stdcall cuMemcpyAtoHAsync(ptr ptr long long ptr) wine_cuMemcpyAtoHAsync
@ stdcall cuMemcpyAtoHAsync_v2(ptr ptr long long ptr) wine_cuMemcpyAtoHAsync_v2
@ stdcall cuMemcpyAtoHAsync_v2_ptsz(ptr ptr long long ptr) wine_cuMemcpyAtoHAsync_v2_ptsz
@ stdcall cuMemcpyAtoH_v2(ptr ptr long long) wine_cuMemcpyAtoH_v2
@ stdcall cuMemcpyAtoH_v2_ptds(ptr ptr long long) wine_cuMemcpyAtoH_v2_ptds
@ stdcall cuMemcpyDtoA(ptr long long long) wine_cuMemcpyDtoA
@ stdcall cuMemcpyDtoA_v2(ptr long long long) wine_cuMemcpyDtoA_v2
@ stdcall cuMemcpyDtoA_v2_ptds(ptr long long long) wine_cuMemcpyDtoA_v2_ptds
@ stdcall cuMemcpyDtoD(long long long) wine_cuMemcpyDtoD
@ stdcall cuMemcpyDtoDAsync(long long long ptr) wine_cuMemcpyDtoDAsync
@ stdcall cuMemcpyDtoDAsync_v2(long long long ptr) wine_cuMemcpyDtoDAsync_v2
@ stdcall cuMemcpyDtoDAsync_v2_ptsz(long long long ptr) wine_cuMemcpyDtoDAsync_v2_ptsz
@ stdcall cuMemcpyDtoD_v2(long long long) wine_cuMemcpyDtoD_v2
@ stdcall cuMemcpyDtoD_v2_ptds(long long long) wine_cuMemcpyDtoD_v2_ptds
@ stdcall cuMemcpyDtoH(ptr long long) wine_cuMemcpyDtoH
@ stdcall cuMemcpyDtoHAsync(ptr long long ptr) wine_cuMemcpyDtoHAsync
@ stdcall cuMemcpyDtoHAsync_v2(ptr long long ptr) wine_cuMemcpyDtoHAsync_v2
@ stdcall cuMemcpyDtoHAsync_v2_ptsz(ptr long long ptr) wine_cuMemcpyDtoHAsync_v2_ptsz
@ stdcall cuMemcpyDtoH_v2(ptr long long) wine_cuMemcpyDtoH_v2
@ stdcall cuMemcpyDtoH_v2_ptds(ptr long long) wine_cuMemcpyDtoH_v2_ptds
@ stdcall cuMemcpyHtoA(ptr long ptr long) wine_cuMemcpyHtoA
@ stdcall cuMemcpyHtoAAsync(ptr long ptr long ptr) wine_cuMemcpyHtoAAsync
@ stdcall cuMemcpyHtoAAsync_v2(ptr long ptr long ptr) wine_cuMemcpyHtoAAsync_v2
@ stdcall cuMemcpyHtoAAsync_v2_ptsz(ptr long ptr long ptr) wine_cuMemcpyHtoAAsync_v2_ptsz
@ stdcall cuMemcpyHtoA_v2(ptr long ptr long) wine_cuMemcpyHtoA_v2
@ stdcall cuMemcpyHtoA_v2_ptds(ptr long ptr long) wine_cuMemcpyHtoA_v2_ptds
@ stdcall cuMemcpyHtoD(long ptr long) wine_cuMemcpyHtoD
@ stdcall cuMemcpyHtoDAsync(long ptr long ptr) wine_cuMemcpyHtoDAsync
@ stdcall cuMemcpyHtoDAsync_v2(long ptr long ptr) wine_cuMemcpyHtoDAsync_v2
@ stdcall cuMemcpyHtoDAsync_v2_ptsz(long ptr long ptr) wine_cuMemcpyHtoDAsync_v2_ptsz
@ stdcall cuMemcpyHtoD_v2(long ptr long) wine_cuMemcpyHtoD_v2
@ stdcall cuMemcpyHtoD_v2_ptds(long ptr long) wine_cuMemcpyHtoD_v2_ptds
@ stdcall cuMemcpyPeer(long ptr long ptr long) wine_cuMemcpyPeer
@ stdcall cuMemcpyPeerAsync(long ptr long ptr long ptr) wine_cuMemcpyPeerAsync
@ stdcall cuMemcpyPeerAsync_ptsz(long ptr long ptr long ptr) wine_cuMemcpyPeerAsync_ptsz
@ stdcall cuMemcpyPeer_ptds(long ptr long ptr long) wine_cuMemcpyPeer_ptds
@ stdcall cuMemcpy_ptds(long long long) wine_cuMemcpy_ptds
@ stdcall cuMemsetD16(long long long) wine_cuMemsetD16
@ stdcall cuMemsetD16Async(long long long ptr) wine_cuMemsetD16Async
@ stdcall cuMemsetD16Async_ptsz(long long long ptr) wine_cuMemsetD16Async_ptsz
@ stdcall cuMemsetD16_v2(long long long) wine_cuMemsetD16_v2
@ stdcall cuMemsetD16_v2_ptds(long long long) wine_cuMemsetD16_v2_ptds
@ stdcall cuMemsetD2D16(long long long long long) wine_cuMemsetD2D16
@ stdcall cuMemsetD2D16Async(long long long long long ptr) wine_cuMemsetD2D16Async
@ stdcall cuMemsetD2D16Async_ptsz(long long long long long ptr) wine_cuMemsetD2D16Async_ptsz
@ stdcall cuMemsetD2D16_v2(long long long long long) wine_cuMemsetD2D16_v2
@ stdcall cuMemsetD2D16_v2_ptds(long long long long long) wine_cuMemsetD2D16_v2_ptds
@ stdcall cuMemsetD2D32(long long long long long) wine_cuMemsetD2D32
@ stdcall cuMemsetD2D32Async(long long long long long ptr) wine_cuMemsetD2D32Async
@ stdcall cuMemsetD2D32Async_ptsz(long long long long long ptr) wine_cuMemsetD2D32Async_ptsz
@ stdcall cuMemsetD2D32_v2(long long long long long) wine_cuMemsetD2D32_v2
@ stdcall cuMemsetD2D32_v2_ptds(long long long long long) wine_cuMemsetD2D32_v2_ptds
@ stdcall cuMemsetD2D8(long long long long long) wine_cuMemsetD2D8
@ stdcall cuMemsetD2D8Async(long long long long long ptr) wine_cuMemsetD2D8Async
@ stdcall cuMemsetD2D8Async_ptsz(long long long long long ptr) wine_cuMemsetD2D8Async_ptsz
@ stdcall cuMemsetD2D8_v2(long long long long long) wine_cuMemsetD2D8_v2
@ stdcall cuMemsetD2D8_v2_ptds(long long long long long) wine_cuMemsetD2D8_v2_ptds
@ stdcall cuMemsetD32(long long long) wine_cuMemsetD32
@ stdcall cuMemsetD32Async(long long long ptr) wine_cuMemsetD32Async
@ stdcall cuMemsetD32Async_ptsz(long long long ptr) wine_cuMemsetD32Async_ptsz
@ stdcall cuMemsetD32_v2(long long long) wine_cuMemsetD32_v2
@ stdcall cuMemsetD32_v2_ptds(long long long) wine_cuMemsetD32_v2_ptds
@ stdcall cuMemsetD8(long long long) wine_cuMemsetD8
@ stdcall cuMemsetD8Async(long long long ptr) wine_cuMemsetD8Async
@ stdcall cuMemsetD8Async_ptsz(long long long ptr) wine_cuMemsetD8Async_ptsz
@ stdcall cuMemsetD8_v2(long long long) wine_cuMemsetD8_v2
@ stdcall cuMemsetD8_v2_ptds(long long long) wine_cuMemsetD8_v2_ptds
@ stdcall cuMipmappedArrayCreate(ptr ptr long) wine_cuMipmappedArrayCreate
@ stdcall cuMipmappedArrayDestroy(ptr) wine_cuMipmappedArrayDestroy
@ stdcall cuMipmappedArrayGetLevel(ptr ptr long) wine_cuMipmappedArrayGetLevel
@ stdcall cuModuleGetFunction(ptr ptr str) wine_cuModuleGetFunction
@ stdcall cuModuleGetGlobal(ptr ptr ptr str) wine_cuModuleGetGlobal
@ stdcall cuModuleGetGlobal_v2(ptr ptr ptr str) wine_cuModuleGetGlobal_v2
@ stdcall cuModuleGetSurfRef(ptr ptr str) wine_cuModuleGetSurfRef
@ stdcall cuModuleGetTexRef(ptr ptr str) wine_cuModuleGetTexRef
@ stdcall cuModuleLoad(ptr str) wine_cuModuleLoad
@ stdcall cuModuleLoadData(ptr ptr) wine_cuModuleLoadData
@ stdcall cuModuleLoadDataEx(ptr ptr long ptr ptr) wine_cuModuleLoadDataEx
@ stdcall cuModuleLoadFatBinary(ptr ptr) wine_cuModuleLoadFatBinary
@ stdcall cuModuleUnload(ptr) wine_cuModuleUnload
@ stdcall cuOccupancyMaxActiveBlocksPerMultiprocessor(ptr ptr long long) wine_cuOccupancyMaxActiveBlocksPerMultiprocessor
@ stdcall cuOccupancyMaxActiveBlocksPerMultiprocessorWithFlags(ptr ptr long long long) wine_cuOccupancyMaxActiveBlocksPerMultiprocessorWithFlags
#@ stdcall cuOccupancyMaxPotentialBlockSize(ptr ptr ptr ptr long long) wine_cuOccupancyMaxPotentialBlockSize
#@ stdcall cuOccupancyMaxPotentialBlockSizeWithFlags(ptr ptr ptr ptr long long long) wine_cuOccupancyMaxPotentialBlockSizeWithFlags
@ stdcall cuParamSetSize(ptr long) wine_cuParamSetSize
@ stdcall cuParamSetTexRef(ptr long ptr) wine_cuParamSetTexRef
@ stdcall cuParamSetf(ptr long float) wine_cuParamSetf
@ stdcall cuParamSeti(ptr long long) wine_cuParamSeti
@ stdcall cuParamSetv(ptr long ptr long) wine_cuParamSetv
@ stdcall cuPointerGetAttribute(ptr long long) wine_cuPointerGetAttribute
@ stdcall cuPointerGetAttributes(long ptr ptr long) wine_cuPointerGetAttributes
@ stdcall cuPointerSetAttribute(ptr long long) wine_cuPointerSetAttribute
@ stub cuProfilerInitialize
@ stub cuProfilerStart
@ stdcall cuProfilerStop(ptr) wine_cuProfilerStop
@ stub cuSignalExternalSemaphoresAsync
@ stub cuSignalExternalSemaphoresAsync_ptsz
@ stdcall cuStreamAddCallback(ptr ptr ptr long) wine_cuStreamAddCallback
@ stdcall cuStreamAddCallback_ptsz(ptr ptr ptr long) wine_cuStreamAddCallback_ptsz
@ stdcall cuStreamAttachMemAsync(ptr long long long) wine_cuStreamAttachMemAsync
@ stdcall cuStreamAttachMemAsync_ptsz(ptr long long long) wine_cuStreamAttachMemAsync_ptsz
@ stub cuStreamBatchMemOp
@ stub cuStreamBatchMemOp_ptsz
@ stub cuStreamBeginCapture
@ stub cuStreamBeginCapture_ptsz
@ stdcall cuStreamBeginCapture_v2(ptr long) wine_cuStreamBeginCapture_v2
@ stub cuStreamBeginCapture_v2_ptsz
@ stdcall cuStreamCreate(ptr long) wine_cuStreamCreate
@ stdcall cuStreamCreateWithPriority(ptr long long) wine_cuStreamCreateWithPriority
@ stdcall cuStreamDestroy(ptr) wine_cuStreamDestroy
@ stdcall cuStreamDestroy_v2(ptr) wine_cuStreamDestroy
@ stdcall cuStreamEndCapture(ptr ptr) wine_cuStreamEndCapture
@ stub cuStreamEndCapture_ptsz
@ stub cuStreamGetCaptureInfo
@ stub cuStreamGetCaptureInfo_ptsz
@ stub cuStreamGetCtx
@ stub cuStreamGetCtx_ptsz
@ stdcall cuStreamGetFlags(ptr ptr) wine_cuStreamGetFlags
@ stdcall cuStreamGetFlags_ptsz(ptr ptr) wine_cuStreamGetFlags_ptsz
@ stdcall cuStreamGetPriority(ptr ptr) wine_cuStreamGetPriority
@ stdcall cuStreamGetPriority_ptsz(ptr ptr) wine_cuStreamGetPriority_ptsz
@ stdcall cuStreamIsCapturing(ptr ptr) wine_cuStreamIsCapturing
@ stub cuStreamIsCapturing_ptsz
@ stdcall cuStreamQuery(ptr) wine_cuStreamQuery
@ stdcall cuStreamQuery_ptsz(ptr) wine_cuStreamQuery_ptsz
@ stdcall cuStreamSynchronize(ptr) wine_cuStreamSynchronize
@ stdcall cuStreamSynchronize_ptsz(ptr) wine_cuStreamSynchronize_ptsz
@ stdcall cuStreamWaitEvent(ptr ptr long) wine_cuStreamWaitEvent
@ stdcall cuStreamWaitEvent_ptsz(ptr ptr long) wine_cuStreamWaitEvent_ptsz
@ stub cuStreamWaitValue32
@ stub cuStreamWaitValue32_ptsz
@ stub cuStreamWaitValue64
@ stub cuStreamWaitValue64_ptsz
@ stub cuStreamWriteValue32
@ stub cuStreamWriteValue32_ptsz
@ stub cuStreamWriteValue64
@ stub cuStreamWriteValue64_ptsz
@ stdcall cuSurfObjectCreate(ptr ptr) wine_cuSurfObjectCreate
@ stdcall cuSurfObjectDestroy(int64) wine_cuSurfObjectDestroy
@ stdcall cuSurfObjectGetResourceDesc(ptr int64) wine_cuSurfObjectGetResourceDesc
@ stdcall cuSurfRefGetArray(ptr ptr) wine_cuSurfRefGetArray
@ stdcall cuSurfRefSetArray(ptr ptr long) wine_cuSurfRefSetArray
@ stdcall cuTexObjectCreate(ptr ptr ptr ptr) wine_cuTexObjectCreate
@ stdcall cuTexObjectDestroy(int64) wine_cuTexObjectDestroy
@ stdcall cuTexObjectGetResourceDesc(ptr int64) wine_cuTexObjectGetResourceDesc
@ stdcall cuTexObjectGetResourceViewDesc(ptr int64) wine_cuTexObjectGetResourceViewDesc
@ stdcall cuTexObjectGetTextureDesc(ptr int64) wine_cuTexObjectGetTextureDesc
@ stdcall cuTexRefCreate(ptr) wine_cuTexRefCreate
@ stdcall cuTexRefDestroy(ptr) wine_cuTexRefDestroy
@ stdcall cuTexRefGetAddress(ptr ptr) wine_cuTexRefGetAddress
@ stdcall cuTexRefGetAddressMode(ptr ptr long) wine_cuTexRefGetAddressMode
@ stdcall cuTexRefGetAddress_v2(ptr ptr) wine_cuTexRefGetAddress_v2
@ stdcall cuTexRefGetArray(ptr ptr) wine_cuTexRefGetArray
@ stub cuTexRefGetBorderColor
@ stdcall cuTexRefGetFilterMode(ptr ptr) wine_cuTexRefGetFilterMode
@ stdcall cuTexRefGetFlags(ptr ptr) wine_cuTexRefGetFlags
@ stdcall cuTexRefGetFormat(ptr ptr ptr) wine_cuTexRefGetFormat
@ stdcall cuTexRefGetMaxAnisotropy(ptr ptr) wine_cuTexRefGetMaxAnisotropy
@ stdcall cuTexRefGetMipmapFilterMode(ptr ptr) wine_cuTexRefGetMipmapFilterMode
@ stdcall cuTexRefGetMipmapLevelBias(ptr ptr) wine_cuTexRefGetMipmapLevelBias
@ stdcall cuTexRefGetMipmapLevelClamp(ptr ptr ptr) wine_cuTexRefGetMipmapLevelClamp
@ stdcall cuTexRefGetMipmappedArray(ptr ptr) wine_cuTexRefGetMipmappedArray
@ stdcall cuTexRefSetAddress(ptr ptr long long) wine_cuTexRefSetAddress
@ stdcall cuTexRefSetAddress2D(ptr ptr long long) wine_cuTexRefSetAddress2D
@ stdcall cuTexRefSetAddress2D_v2(ptr ptr long long) wine_cuTexRefSetAddress2D_v2
@ stdcall cuTexRefSetAddress2D_v3(ptr ptr long long) wine_cuTexRefSetAddress2D_v3
@ stdcall cuTexRefSetAddressMode(ptr long long) wine_cuTexRefSetAddressMode
@ stdcall cuTexRefSetAddress_v2(ptr ptr long long) wine_cuTexRefSetAddress_v2
@ stdcall cuTexRefSetArray(ptr ptr long) wine_cuTexRefSetArray
@ stub cuTexRefSetBorderColor
@ stdcall cuTexRefSetFilterMode(ptr long) wine_cuTexRefSetFilterMode
@ stdcall cuTexRefSetFlags(ptr long) wine_cuTexRefSetFlags
@ stdcall cuTexRefSetFormat(ptr long long) wine_cuTexRefSetFormat
@ stdcall cuTexRefSetMaxAnisotropy(ptr long) wine_cuTexRefSetMaxAnisotropy
@ stdcall cuTexRefSetMipmapFilterMode(ptr long) wine_cuTexRefSetMipmapFilterMode
@ stdcall cuTexRefSetMipmapLevelBias(ptr float) wine_cuTexRefSetMipmapLevelBias
@ stdcall cuTexRefSetMipmapLevelClamp(ptr float float) wine_cuTexRefSetMipmapLevelClamp
@ stdcall cuTexRefSetMipmappedArray(ptr ptr long) wine_cuTexRefSetMipmappedArray
@ stub cuThreadExchangeStreamCaptureMode
@ stub cuWGLGetDevice
@ stub cuWaitExternalSemaphoresAsync
@ stub cuWaitExternalSemaphoresAsync_ptsz
