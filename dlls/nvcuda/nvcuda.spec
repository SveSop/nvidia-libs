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
@ stdcall cuCtxCreate_v3(ptr ptr long long long) wine_cuCtxCreate_v3
@ stdcall cuCtxCreate_v4(ptr ptr long long) wine_cuCtxCreate_v4
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
@ stdcall cuDestroyExternalMemory(ptr) wine_cuDestroyExternalMemory
@ stdcall cuDestroyExternalSemaphore(ptr) wine_cuDestroyExternalSemaphore
@ stdcall cuDeviceCanAccessPeer(ptr long long) wine_cuDeviceCanAccessPeer
@ stdcall cuDeviceComputeCapability(ptr ptr long) wine_cuDeviceComputeCapability
@ stdcall cuDeviceGet(ptr long) wine_cuDeviceGet
@ stdcall cuDeviceGetAttribute(ptr long long) wine_cuDeviceGetAttribute
@ stdcall cuDeviceGetByPCIBusId(ptr str) wine_cuDeviceGetByPCIBusId
@ stdcall cuDeviceGetCount(ptr) wine_cuDeviceGetCount
@ stdcall cuDeviceGetDefaultMemPool(ptr long) wine_cuDeviceGetDefaultMemPool
@ stdcall cuDeviceGetGraphMemAttribute(long long ptr) wine_cuDeviceGetGraphMemAttribute
@ stdcall cuDeviceGetLuid(ptr ptr long) wine_cuDeviceGetLuid
@ stdcall cuDeviceGetName(str long long) wine_cuDeviceGetName
@ stdcall cuDeviceGetP2PAttribute(ptr ptr long long) wine_cuDeviceGetP2PAttribute
@ stdcall cuDeviceGetPCIBusId(str long long) wine_cuDeviceGetPCIBusId
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
@ stdcall cuExternalMemoryGetMappedBuffer(ptr ptr ptr) wine_cuExternalMemoryGetMappedBuffer
@ stdcall cuExternalMemoryGetMappedMipmappedArray(ptr ptr ptr) wine_cuExternalMemoryGetMappedMipmappedArray
@ stdcall cuFuncGetAttribute(ptr long ptr) wine_cuFuncGetAttribute
@ stdcall cuFuncSetAttribute(ptr long long) wine_cuFuncSetAttribute
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
@ stdcall cuGraphAddChildGraphNode(ptr ptr ptr long ptr) wine_cuGraphAddChildGraphNode
@ stdcall cuGraphAddDependencies(ptr ptr ptr long) wine_cuGraphAddDependencies
@ stdcall cuGraphAddEmptyNode(ptr ptr ptr long) wine_cuGraphAddEmptyNode
@ stdcall cuGraphAddHostNode(ptr ptr ptr long ptr) wine_cuGraphAddHostNode
@ stdcall cuGraphAddKernelNode(ptr ptr ptr long ptr) wine_cuGraphAddKernelNode
@ stdcall cuGraphAddMemAllocNode(ptr ptr ptr long ptr) wine_cuGraphAddMemAllocNode
@ stdcall cuGraphAddMemFreeNode(ptr ptr ptr long double) wine_cuGraphAddMemFreeNode
@ stdcall cuGraphAddMemcpyNode(ptr ptr ptr long ptr ptr) wine_cuGraphAddMemcpyNode
@ stdcall cuGraphAddMemsetNode(ptr ptr ptr long ptr ptr) wine_cuGraphAddMemsetNode
@ stdcall cuGraphChildGraphNodeGetGraph(ptr ptr) wine_cuGraphChildGraphNodeGetGraph
@ stdcall cuGraphClone(ptr ptr) wine_cuGraphClone
@ stdcall cuGraphCreate(ptr long) wine_cuGraphCreate
@ stdcall cuGraphDestroy(ptr) wine_cuGraphDestroy
@ stdcall cuGraphDestroyNode(ptr) wine_cuGraphDestroyNode
@ stdcall cuGraphExecDestroy(ptr) wine_cuGraphExecDestroy
@ stdcall cuGraphExecKernelNodeSetParams(ptr ptr ptr) wine_cuGraphExecKernelNodeSetParams
@ stdcall cuGraphGetEdges(ptr ptr ptr ptr) wine_cuGraphGetEdges
@ stdcall cuGraphGetNodes(ptr ptr ptr) wine_cuGraphGetNodes
@ stdcall cuGraphGetRootNodes(ptr ptr ptr) wine_cuGraphGetRootNodes
@ stdcall cuGraphHostNodeGetParams(ptr ptr) wine_cuGraphHostNodeGetParams
@ stdcall cuGraphHostNodeSetParams(ptr ptr) wine_cuGraphHostNodeSetParams
@ stdcall cuGraphInstantiate(ptr ptr ptr ptr long) wine_cuGraphInstantiate
@ stdcall cuGraphInstantiate_v2(ptr ptr ptr ptr long) wine_cuGraphInstantiate_v2
@ stdcall cuGraphKernelNodeGetParams(ptr ptr) wine_cuGraphKernelNodeGetParams
@ stdcall cuGraphKernelNodeSetParams(ptr ptr) wine_cuGraphKernelNodeSetParams
@ stdcall cuGraphLaunch(ptr ptr) wine_cuGraphLaunch
@ stdcall cuGraphLaunch_ptsz(ptr ptr) wine_cuGraphLaunch_ptsz
@ stdcall cuGraphMemcpyNodeGetParams(ptr ptr) wine_cuGraphMemcpyNodeGetParams
@ stdcall cuGraphMemcpyNodeSetParams(ptr ptr) wine_cuGraphMemcpyNodeSetParams
@ stdcall cuGraphMemsetNodeGetParams(ptr ptr) wine_cuGraphMemsetNodeGetParams
@ stdcall cuGraphMemsetNodeSetParams(ptr ptr) wine_cuGraphMemsetNodeSetParams
@ stdcall cuGraphNodeFindInClone(ptr ptr ptr) wine_cuGraphNodeFindInClone
@ stdcall cuGraphNodeGetDependencies(ptr ptr ptr) wine_cuGraphNodeGetDependencies
@ stdcall cuGraphNodeGetDependentNodes(ptr ptr ptr) wine_cuGraphNodeGetDependentNodes
@ stdcall cuGraphNodeGetType(ptr ptr) wine_cuGraphNodeGetType
@ stdcall cuGraphRemoveDependencies(ptr ptr ptr long) wine_cuGraphRemoveDependencies
@ stdcall cuGraphicsD3D9RegisterResource(ptr ptr long) wine_cuGraphicsD3D9RegisterResource
@ stdcall cuGraphicsD3D10RegisterResource(ptr ptr long) wine_cuGraphicsD3D10RegisterResource
@ stdcall cuGraphicsD3D11RegisterResource(ptr ptr long) wine_cuGraphicsD3D11RegisterResource
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
@ stdcall cuImportExternalMemory(ptr ptr) wine_cuImportExternalMemory
@ stdcall cuImportExternalSemaphore(ptr ptr) wine_cuImportExternalSemaphore
@ stdcall cuInit(long) wine_cuInit
@ stdcall cuIpcCloseMemHandle(double) wine_cuIpcCloseMemHandle
@ stdcall cuIpcGetEventHandle(ptr ptr) wine_cuIpcGetEventHandle
@ stdcall cuIpcGetMemHandle(ptr double) wine_cuIpcGetMemHandle
@ stdcall cuIpcOpenEventHandle(ptr ptr) wine_cuIpcOpenEventHandle
@ stdcall cuIpcOpenMemHandle(ptr ptr long) wine_cuIpcOpenMemHandle
@ stdcall cuIpcOpenMemHandle_v2(ptr ptr long) wine_cuIpcOpenMemHandle_v2
@ stdcall cuLaunch(ptr) wine_cuLaunch
@ stdcall cuLaunchCooperativeKernel(ptr long long long long long long long ptr ptr) wine_cuLaunchCooperativeKernel
@ stdcall cuLaunchCooperativeKernelMultiDevice(ptr long long) wine_cuLaunchCooperativeKernelMultiDevice
@ stub cuLaunchCooperativeKernel_ptsz
@ stdcall cuLaunchGrid(ptr long long) wine_cuLaunchGrid
@ stdcall cuLaunchGridAsync(ptr long long ptr) wine_cuLaunchGridAsync
@ stdcall cuLaunchHostFunc(ptr ptr ptr) wine_cuLaunchHostFunc
@ stdcall cuLaunchHostFunc_ptsz(ptr ptr ptr) wine_cuLaunchHostFunc_ptsz
@ stdcall cuLaunchKernel(ptr long long long long long long long ptr ptr ptr) wine_cuLaunchKernel
@ stdcall cuLaunchKernel_ptsz(ptr long long long long long long long ptr ptr ptr) wine_cuLaunchKernel_ptsz
@ stdcall cuLaunchKernelEx(ptr ptr ptr ptr) wine_cuLaunchKernelEx
@ stdcall cuLaunchKernelEx_ptsz(ptr ptr ptr ptr) wine_cuLaunchKernelEx_ptsz
@ stdcall cuLinkAddData(ptr long ptr long str long ptr ptr) wine_cuLinkAddData
@ stdcall cuLinkAddData_v2(ptr long ptr long str long ptr ptr) wine_cuLinkAddData_v2
@ stdcall cuLinkAddFile(ptr ptr str long ptr ptr) wine_cuLinkAddFile
@ stdcall cuLinkAddFile_v2(ptr ptr str long ptr ptr) wine_cuLinkAddFile_v2
@ stdcall cuLinkComplete(ptr ptr ptr) wine_cuLinkComplete
@ stdcall cuLinkCreate(long ptr ptr ptr) wine_cuLinkCreate
@ stdcall cuLinkCreate_v2(long ptr ptr ptr) wine_cuLinkCreate_v2
@ stdcall cuLinkDestroy(ptr) wine_cuLinkDestroy
@ stdcall cuMemAdvise(double long ptr long) wine_cuMemAdvise
@ stdcall cuMemAlloc(ptr long) wine_cuMemAlloc
@ stdcall cuMemAllocAsync(ptr long ptr) wine_cuMemAllocAsync
@ stdcall cuMemAllocAsync_ptsz(ptr long ptr) wine_cuMemAllocAsync_ptsz
@ stdcall cuMemAllocHost(ptr long) wine_cuMemAllocHost
@ stdcall cuMemAllocHost_v2(ptr long) wine_cuMemAllocHost_v2
@ stdcall cuMemAllocManaged(ptr long long) wine_cuMemAllocManaged
@ stdcall cuMemAllocPitch(ptr ptr long long long) wine_cuMemAllocPitch
@ stdcall cuMemAllocPitch_v2(ptr ptr long long long) wine_cuMemAllocPitch_v2
@ stdcall cuMemAlloc_v2(ptr long) wine_cuMemAlloc_v2
@ stdcall cuMemFree(long) wine_cuMemFree
@ stdcall cuMemGetAllocationGranularity(ptr ptr long) wine_cuMemGetAllocationGranularity
@ stdcall cuMemFreeAsync(double ptr) wine_cuMemFreeAsync
@ stdcall cuMemFreeAsync_ptsz(double ptr) wine_cuMemFreeAsync_ptsz
@ stdcall cuMemFreeHost(ptr) wine_cuMemFreeHost
@ stdcall cuMemFree_v2(double) wine_cuMemFree_v2
@ stdcall cuMemGetAddressRange(ptr ptr long) wine_cuMemGetAddressRange
@ stdcall cuMemGetAddressRange_v2(ptr ptr double) wine_cuMemGetAddressRange_v2
@ stdcall cuMemGetHandleForAddressRange(ptr double long long long) wine_cuMemGetHandleForAddressRange
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
@ stdcall cuMemPrefetchAsync(double long long ptr) wine_cuMemPrefetchAsync
@ stdcall cuMemPrefetchAsync_ptsz(double long long ptr) wine_cuMemPrefetchAsync_ptsz
@ stdcall cuMemRangeGetAttribute(ptr long ptr double long) wine_cuMemRangeGetAttribute
@ stdcall cuMemRangeGetAttributes(ptr ptr ptr long double long) wine_cuMemRangeGetAttributes
@ stdcall cuMemcpy(double double long) wine_cuMemcpy
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
@ stdcall cuMemcpyAsync(double double long ptr) wine_cuMemcpyAsync
@ stdcall cuMemcpyAsync_ptsz(double double long ptr) wine_cuMemcpyAsync_ptsz
@ stdcall cuMemcpyAtoA(ptr long ptr long long) wine_cuMemcpyAtoA
@ stdcall cuMemcpyAtoA_v2(ptr long ptr long long) wine_cuMemcpyAtoA_v2
@ stdcall cuMemcpyAtoA_v2_ptds(ptr long ptr long long) wine_cuMemcpyAtoA_v2_ptds
@ stdcall cuMemcpyAtoD(long ptr long long) wine_cuMemcpyAtoD
@ stdcall cuMemcpyAtoD_v2(double ptr long long) wine_cuMemcpyAtoD_v2
@ stdcall cuMemcpyAtoD_v2_ptds(double ptr long long) wine_cuMemcpyAtoD_v2_ptds
@ stdcall cuMemcpyAtoH(ptr ptr long long) wine_cuMemcpyAtoH
@ stdcall cuMemcpyAtoHAsync(ptr ptr long long ptr) wine_cuMemcpyAtoHAsync
@ stdcall cuMemcpyAtoHAsync_v2(ptr ptr long long ptr) wine_cuMemcpyAtoHAsync_v2
@ stdcall cuMemcpyAtoHAsync_v2_ptsz(ptr ptr long long ptr) wine_cuMemcpyAtoHAsync_v2_ptsz
@ stdcall cuMemcpyAtoH_v2(ptr ptr long long) wine_cuMemcpyAtoH_v2
@ stdcall cuMemcpyAtoH_v2_ptds(ptr ptr long long) wine_cuMemcpyAtoH_v2_ptds
@ stdcall cuMemcpyDtoA(ptr long long long) wine_cuMemcpyDtoA
@ stdcall cuMemcpyDtoA_v2(ptr long double long) wine_cuMemcpyDtoA_v2
@ stdcall cuMemcpyDtoA_v2_ptds(ptr long double long) wine_cuMemcpyDtoA_v2_ptds
@ stdcall cuMemcpyDtoD(long long long) wine_cuMemcpyDtoD
@ stdcall cuMemcpyDtoDAsync(long long long ptr) wine_cuMemcpyDtoDAsync
@ stdcall cuMemcpyDtoDAsync_v2(double double long ptr) wine_cuMemcpyDtoDAsync_v2
@ stdcall cuMemcpyDtoDAsync_v2_ptsz(double double long ptr) wine_cuMemcpyDtoDAsync_v2_ptsz
@ stdcall cuMemcpyDtoD_v2(double double long) wine_cuMemcpyDtoD_v2
@ stdcall cuMemcpyDtoD_v2_ptds(double double long) wine_cuMemcpyDtoD_v2_ptds
@ stdcall cuMemcpyDtoH(ptr long long) wine_cuMemcpyDtoH
@ stdcall cuMemcpyDtoHAsync(ptr long long ptr) wine_cuMemcpyDtoHAsync
@ stdcall cuMemcpyDtoHAsync_v2(ptr double long ptr) wine_cuMemcpyDtoHAsync_v2
@ stdcall cuMemcpyDtoHAsync_v2_ptsz(ptr double long ptr) wine_cuMemcpyDtoHAsync_v2_ptsz
@ stdcall cuMemcpyDtoH_v2(ptr double long) wine_cuMemcpyDtoH_v2
@ stdcall cuMemcpyDtoH_v2_ptds(ptr double long) wine_cuMemcpyDtoH_v2_ptds
@ stdcall cuMemcpyHtoA(ptr long ptr long) wine_cuMemcpyHtoA
@ stdcall cuMemcpyHtoAAsync(ptr long ptr long ptr) wine_cuMemcpyHtoAAsync
@ stdcall cuMemcpyHtoAAsync_v2(ptr long ptr long ptr) wine_cuMemcpyHtoAAsync_v2
@ stdcall cuMemcpyHtoAAsync_v2_ptsz(ptr long ptr long ptr) wine_cuMemcpyHtoAAsync_v2_ptsz
@ stdcall cuMemcpyHtoA_v2(ptr long ptr long) wine_cuMemcpyHtoA_v2
@ stdcall cuMemcpyHtoA_v2_ptds(ptr long ptr long) wine_cuMemcpyHtoA_v2_ptds
@ stdcall cuMemcpyHtoD(long ptr long) wine_cuMemcpyHtoD
@ stdcall cuMemcpyHtoDAsync(long ptr long ptr) wine_cuMemcpyHtoDAsync
@ stdcall cuMemcpyHtoDAsync_v2(double ptr long ptr) wine_cuMemcpyHtoDAsync_v2
@ stdcall cuMemcpyHtoDAsync_v2_ptsz(double ptr long ptr) wine_cuMemcpyHtoDAsync_v2_ptsz
@ stdcall cuMemcpyHtoD_v2(double ptr long) wine_cuMemcpyHtoD_v2
@ stdcall cuMemcpyHtoD_v2_ptds(double ptr long) wine_cuMemcpyHtoD_v2_ptds
@ stdcall cuMemcpyPeer(long ptr long ptr long) wine_cuMemcpyPeer
@ stdcall cuMemcpyPeerAsync(long ptr long ptr long ptr) wine_cuMemcpyPeerAsync
@ stdcall cuMemcpyPeerAsync_ptsz(long ptr long ptr long ptr) wine_cuMemcpyPeerAsync_ptsz
@ stdcall cuMemcpyPeer_ptds(long ptr long ptr long) wine_cuMemcpyPeer_ptds
@ stdcall cuMemcpy_ptds(double double long) wine_cuMemcpy_ptds
@ stdcall cuMemsetD16(long long long) wine_cuMemsetD16
@ stdcall cuMemsetD16Async(double long long ptr) wine_cuMemsetD16Async
@ stdcall cuMemsetD16Async_ptsz(double long long ptr) wine_cuMemsetD16Async_ptsz
@ stdcall cuMemsetD16_v2(double long long) wine_cuMemsetD16_v2
@ stdcall cuMemsetD16_v2_ptds(double long long) wine_cuMemsetD16_v2_ptds
@ stdcall cuMemsetD2D16(long long long long long) wine_cuMemsetD2D16
@ stdcall cuMemsetD2D16Async(long long long long long ptr) wine_cuMemsetD2D16Async
@ stdcall cuMemsetD2D16Async_ptsz(long long long long long ptr) wine_cuMemsetD2D16Async_ptsz
@ stdcall cuMemsetD2D16_v2(double long long long long) wine_cuMemsetD2D16_v2
@ stdcall cuMemsetD2D16_v2_ptds(double long long long long) wine_cuMemsetD2D16_v2_ptds
@ stdcall cuMemsetD2D32(long long long long long) wine_cuMemsetD2D32
@ stdcall cuMemsetD2D32Async(long long long long long ptr) wine_cuMemsetD2D32Async
@ stdcall cuMemsetD2D32Async_ptsz(long long long long long ptr) wine_cuMemsetD2D32Async_ptsz
@ stdcall cuMemsetD2D32_v2(double long long long long) wine_cuMemsetD2D32_v2
@ stdcall cuMemsetD2D32_v2_ptds(double long long long long) wine_cuMemsetD2D32_v2_ptds
@ stdcall cuMemsetD2D8(long long long long long) wine_cuMemsetD2D8
@ stdcall cuMemsetD2D8Async(long long long long long ptr) wine_cuMemsetD2D8Async
@ stdcall cuMemsetD2D8Async_ptsz(long long long long long ptr) wine_cuMemsetD2D8Async_ptsz
@ stdcall cuMemsetD2D8_v2(double long long long long) wine_cuMemsetD2D8_v2
@ stdcall cuMemsetD2D8_v2_ptds(double long long long long) wine_cuMemsetD2D8_v2_ptds
@ stdcall cuMemsetD32(long long long) wine_cuMemsetD32
@ stdcall cuMemsetD32Async(double long long ptr) wine_cuMemsetD32Async
@ stdcall cuMemsetD32Async_ptsz(double long long ptr) wine_cuMemsetD32Async_ptsz
@ stdcall cuMemsetD32_v2(double long long) wine_cuMemsetD32_v2
@ stdcall cuMemsetD32_v2_ptds(double long long) wine_cuMemsetD32_v2_ptds
@ stdcall cuMemsetD8(long long long) wine_cuMemsetD8
@ stdcall cuMemsetD8Async(double long long ptr) wine_cuMemsetD8Async
@ stdcall cuMemsetD8Async_ptsz(double long long ptr) wine_cuMemsetD8Async_ptsz
@ stdcall cuMemsetD8_v2(double long long) wine_cuMemsetD8_v2
@ stdcall cuMemsetD8_v2_ptds(double long long) wine_cuMemsetD8_v2_ptds
@ stdcall cuMipmappedArrayCreate(ptr ptr long) wine_cuMipmappedArrayCreate
@ stdcall cuMipmappedArrayDestroy(ptr) wine_cuMipmappedArrayDestroy
@ stdcall cuMipmappedArrayGetLevel(ptr ptr long) wine_cuMipmappedArrayGetLevel
@ stdcall cuModuleGetFunction(ptr ptr str) wine_cuModuleGetFunction
@ stdcall cuModuleGetGlobal(ptr ptr ptr str) wine_cuModuleGetGlobal
@ stdcall cuModuleGetGlobal_v2(ptr ptr ptr str) wine_cuModuleGetGlobal_v2
@ stdcall cuModuleGetLoadingMode(ptr) wine_cuModuleGetLoadingMode
@ stdcall cuModuleGetSurfRef(ptr ptr str) wine_cuModuleGetSurfRef
@ stdcall cuModuleGetTexRef(ptr ptr str) wine_cuModuleGetTexRef
@ stdcall cuModuleLoad(ptr str) wine_cuModuleLoad
@ stdcall cuModuleLoadData(ptr ptr) wine_cuModuleLoadData
@ stdcall cuModuleLoadDataEx(ptr ptr long ptr ptr) wine_cuModuleLoadDataEx
@ stdcall cuModuleLoadFatBinary(ptr ptr) wine_cuModuleLoadFatBinary
@ stdcall cuModuleUnload(ptr) wine_cuModuleUnload
@ stdcall cuOccupancyMaxActiveBlocksPerMultiprocessor(ptr ptr long long) wine_cuOccupancyMaxActiveBlocksPerMultiprocessor
@ stdcall cuOccupancyMaxActiveBlocksPerMultiprocessorWithFlags(ptr ptr long long long) wine_cuOccupancyMaxActiveBlocksPerMultiprocessorWithFlags
@ stdcall cuOccupancyMaxActiveClusters(ptr ptr ptr) wine_cuOccupancyMaxActiveClusters
@ stdcall cuOccupancyMaxPotentialBlockSize(ptr ptr ptr ptr long long) wine_cuOccupancyMaxPotentialBlockSize
@ stdcall cuOccupancyMaxPotentialBlockSizeWithFlags(ptr ptr ptr ptr long long long) wine_cuOccupancyMaxPotentialBlockSizeWithFlags
@ stdcall cuOccupancyMaxPotentialClusterSize(ptr ptr ptr) wine_cuOccupancyMaxPotentialClusterSize
@ stdcall cuParamSetSize(ptr long) wine_cuParamSetSize
@ stdcall cuParamSetTexRef(ptr long ptr) wine_cuParamSetTexRef
@ stdcall cuParamSetf(ptr long float) wine_cuParamSetf
@ stdcall cuParamSeti(ptr long long) wine_cuParamSeti
@ stdcall cuParamSetv(ptr long ptr long) wine_cuParamSetv
@ stdcall cuPointerGetAttribute(ptr long double) wine_cuPointerGetAttribute
@ stdcall cuPointerGetAttributes(long ptr ptr double) wine_cuPointerGetAttributes
@ stdcall cuPointerSetAttribute(ptr long double) wine_cuPointerSetAttribute
@ stdcall cuProfilerInitialize(str str ptr) wine_cuProfilerInitialize
@ stdcall cuProfilerStart() wine_cuProfilerStart
@ stdcall cuProfilerStop() wine_cuProfilerStop
@ stdcall cuSignalExternalSemaphoresAsync(ptr ptr long ptr) wine_cuSignalExternalSemaphoresAsync
@ stdcall cuSignalExternalSemaphoresAsync_ptsz(ptr ptr long ptr) wine_cuSignalExternalSemaphoresAsync_ptsz
@ stdcall cuStreamAddCallback(ptr ptr ptr long) wine_cuStreamAddCallback
@ stdcall cuStreamAddCallback_ptsz(ptr ptr ptr long) wine_cuStreamAddCallback_ptsz
@ stdcall cuStreamAttachMemAsync(ptr double long long) wine_cuStreamAttachMemAsync
@ stdcall cuStreamAttachMemAsync_ptsz(ptr double long long) wine_cuStreamAttachMemAsync_ptsz
@ stdcall cuStreamBatchMemOp(ptr long ptr long) wine_cuStreamBatchMemOp
@ stdcall cuStreamBatchMemOp_ptsz(ptr long ptr long) wine_cuStreamBatchMemOp_ptsz
@ stdcall cuStreamBeginCapture(ptr) wine_cuStreamBeginCapture
@ stdcall cuStreamBeginCapture_ptsz(ptr) wine_cuStreamBeginCapture_ptsz
@ stdcall cuStreamBeginCapture_v2(ptr long) wine_cuStreamBeginCapture_v2
@ stdcall cuStreamBeginCapture_v2_ptsz(ptr long) wine_cuStreamBeginCapture_v2_ptsz
@ stdcall cuStreamCreate(ptr long) wine_cuStreamCreate
@ stdcall cuStreamCreateWithPriority(ptr long long) wine_cuStreamCreateWithPriority
@ stdcall cuStreamDestroy(ptr) wine_cuStreamDestroy
@ stdcall cuStreamDestroy_v2(ptr) wine_cuStreamDestroy_v2
@ stdcall cuStreamEndCapture(ptr ptr) wine_cuStreamEndCapture
@ stub cuStreamEndCapture_ptsz
@ stdcall cuStreamGetCaptureInfo(ptr ptr ptr) wine_cuStreamGetCaptureInfo
@ stdcall cuStreamGetCaptureInfo_ptsz(ptr ptr ptr) wine_cuStreamGetCaptureInfo_ptsz
@ stdcall cuStreamGetCaptureInfo_v2(ptr ptr ptr ptr ptr ptr) wine_cuStreamGetCaptureInfo_v2
@ stdcall cuStreamGetCaptureInfo_v2_ptsz(ptr ptr ptr ptr ptr ptr) wine_cuStreamGetCaptureInfo_v2_ptsz
@ stdcall cuStreamGetCtx(ptr ptr) wine_cuStreamGetCtx
@ stdcall cuStreamGetCtx_ptsz(ptr ptr) wine_cuStreamGetCtx_ptsz
@ stdcall cuStreamGetCtx_v2(ptr ptr ptr) wine_cuStreamGetCtx_v2
@ stdcall cuStreamGetCtx_v2_ptsz(ptr ptr ptr) wine_cuStreamGetCtx_v2_ptsz
@ stdcall cuStreamGetFlags(ptr ptr) wine_cuStreamGetFlags
@ stdcall cuStreamGetFlags_ptsz(ptr ptr) wine_cuStreamGetFlags_ptsz
@ stdcall cuStreamGetPriority(ptr ptr) wine_cuStreamGetPriority
@ stdcall cuStreamGetPriority_ptsz(ptr ptr) wine_cuStreamGetPriority_ptsz
@ stdcall cuStreamIsCapturing(ptr ptr) wine_cuStreamIsCapturing
@ stdcall cuStreamIsCapturing_ptsz(ptr ptr) wine_cuStreamIsCapturing_ptsz
@ stdcall cuStreamQuery(ptr) wine_cuStreamQuery
@ stdcall cuStreamQuery_ptsz(ptr) wine_cuStreamQuery_ptsz
@ stdcall cuStreamSynchronize(ptr) wine_cuStreamSynchronize
@ stdcall cuStreamSynchronize_ptsz(ptr) wine_cuStreamSynchronize_ptsz
@ stdcall cuStreamWaitEvent(ptr ptr long) wine_cuStreamWaitEvent
@ stdcall cuStreamWaitEvent_ptsz(ptr ptr long) wine_cuStreamWaitEvent_ptsz
@ stdcall cuStreamWaitValue32(ptr double long long) wine_cuStreamWaitValue32
@ stdcall cuStreamWaitValue32_ptsz(ptr double long long) wine_cuStreamWaitValue32_ptsz
@ stdcall cuStreamWaitValue64(ptr double int64 long) wine_cuStreamWaitValue64
@ stdcall cuStreamWaitValue64_ptsz(ptr double int64 long) wine_cuStreamWaitValue64_ptsz
@ stdcall cuStreamWriteValue32(ptr double long long) wine_cuStreamWriteValue32
@ stdcall cuStreamWriteValue32_ptsz(ptr double long long) wine_cuStreamWriteValue32_ptsz
@ stdcall cuStreamWriteValue64(ptr double int64 long) wine_cuStreamWriteValue64
@ stdcall cuStreamWriteValue64_ptsz(ptr double int64 long) wine_cuStreamWriteValue64_ptsz
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
@ stdcall cuTexRefGetBorderColor(ptr ptr) wine_cuTexRefGetBorderColor
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
@ stdcall cuTexRefSetAddress_v2(ptr ptr double long) wine_cuTexRefSetAddress_v2
@ stdcall cuTexRefSetArray(ptr ptr long) wine_cuTexRefSetArray
@ stdcall cuTexRefSetBorderColor(ptr float) wine_cuTexRefSetBorderColor
@ stdcall cuTexRefSetFilterMode(ptr long) wine_cuTexRefSetFilterMode
@ stdcall cuTexRefSetFlags(ptr long) wine_cuTexRefSetFlags
@ stdcall cuTexRefSetFormat(ptr long long) wine_cuTexRefSetFormat
@ stdcall cuTexRefSetMaxAnisotropy(ptr long) wine_cuTexRefSetMaxAnisotropy
@ stdcall cuTexRefSetMipmapFilterMode(ptr long) wine_cuTexRefSetMipmapFilterMode
@ stdcall cuTexRefSetMipmapLevelBias(ptr float) wine_cuTexRefSetMipmapLevelBias
@ stdcall cuTexRefSetMipmapLevelClamp(ptr float float) wine_cuTexRefSetMipmapLevelClamp
@ stdcall cuTexRefSetMipmappedArray(ptr ptr long) wine_cuTexRefSetMipmappedArray
@ stdcall cuThreadExchangeStreamCaptureMode(ptr) wine_cuThreadExchangeStreamCaptureMode
@ stdcall cuWGLGetDevice(ptr ptr) wine_cuWGLGetDevice
@ stdcall cuWaitExternalSemaphoresAsync(ptr ptr long ptr) wine_cuWaitExternalSemaphoresAsync
@ stdcall cuWaitExternalSemaphoresAsync_ptsz(ptr ptr long ptr) wine_cuWaitExternalSemaphoresAsync_ptsz
@ stdcall cuArrayGetPlane(ptr ptr long) wine_cuArrayGetPlane
@ stdcall cuArrayGetSparseProperties(ptr ptr) wine_cuArrayGetSparseProperties
@ stdcall cuCtxGetExecAffinity(ptr ptr) wine_cuCtxGetExecAffinity
@ stdcall cuCtxResetPersistingL2Cache() wine_cuCtxResetPersistingL2Cache
@ stdcall cuDeviceGetExecAffinitySupport(ptr ptr long) wine_cuDeviceGetExecAffinitySupport
@ stdcall cuDeviceGetMemPool(ptr long) wine_cuDeviceGetMemPool
@ stdcall cuDeviceGetTexture1DLinearMaxWidth(ptr long long long) wine_cuDeviceGetTexture1DLinearMaxWidth
@ stdcall cuDeviceGetUuid_v2(ptr long) wine_cuDeviceGetUuid_v2
@ stdcall cuDevicePrimaryCtxRelease_v2(long) wine_cuDevicePrimaryCtxRelease_v2
@ stdcall cuDevicePrimaryCtxReset_v2(long) wine_cuDevicePrimaryCtxReset_v2
@ stdcall cuDevicePrimaryCtxSetFlags_v2(long long) wine_cuDevicePrimaryCtxSetFlags_v2
@ stdcall cuDeviceSetGraphMemAttribute(long long ptr) wine_cuDeviceSetGraphMemAttribute
@ stdcall cuDeviceSetMemPool(long ptr) wine_cuDeviceSetMemPool
@ stdcall cuEventRecordWithFlags(ptr ptr long) wine_cuEventRecordWithFlags
@ stdcall cuEventRecordWithFlags_ptsz(ptr ptr long) wine_cuEventRecordWithFlags_ptsz
@ stdcall cuFlushGPUDirectRDMAWrites(ptr ptr) wine_cuFlushGPUDirectRDMAWrites
@ stdcall cuFuncGetModule(ptr ptr) wine_cuFuncGetModule
@ stdcall cuGraphAddEventRecordNode(ptr ptr ptr long ptr) wine_cuGraphAddEventRecordNode
@ stdcall cuGraphAddEventWaitNode(ptr ptr ptr long ptr) wine_cuGraphAddEventWaitNode
@ stdcall cuGraphAddExternalSemaphoresSignalNode(ptr ptr ptr long ptr) wine_cuGraphAddExternalSemaphoresSignalNode
@ stdcall cuGraphAddExternalSemaphoresWaitNode(ptr ptr ptr long ptr) wine_cuGraphAddExternalSemaphoresWaitNode
@ stdcall cuGraphDebugDotPrint(ptr str long) wine_cuGraphDebugDotPrint
@ stdcall cuGraphEventRecordNodeGetEvent(ptr ptr) wine_cuGraphEventRecordNodeGetEvent
@ stdcall cuGraphEventRecordNodeSetEvent(ptr ptr) wine_cuGraphEventRecordNodeSetEvent
@ stdcall cuGraphEventWaitNodeGetEvent(ptr ptr) wine_cuGraphEventWaitNodeGetEvent
@ stdcall cuGraphEventWaitNodeSetEvent(ptr ptr) wine_cuGraphEventWaitNodeSetEvent
@ stdcall cuGraphExecChildGraphNodeSetParams(ptr ptr ptr) wine_cuGraphExecChildGraphNodeSetParams
@ stdcall cuGraphExecEventRecordNodeSetEvent(ptr ptr ptr) wine_cuGraphExecEventRecordNodeSetEvent
@ stdcall cuGraphExecEventWaitNodeSetEvent(ptr ptr ptr) wine_cuGraphExecEventWaitNodeSetEvent
@ stdcall cuGraphExecExternalSemaphoresSignalNodeSetParams(ptr ptr ptr) wine_cuGraphExecExternalSemaphoresSignalNodeSetParams
@ stdcall cuGraphExecExternalSemaphoresWaitNodeSetParams(ptr ptr ptr) wine_cuGraphExecExternalSemaphoresWaitNodeSetParams
@ stdcall cuGraphExecHostNodeSetParams(ptr ptr ptr) wine_cuGraphExecHostNodeSetParams
@ stdcall cuGraphExecMemcpyNodeSetParams(ptr ptr ptr ptr) wine_cuGraphExecMemcpyNodeSetParams
@ stdcall cuGraphExecMemsetNodeSetParams(ptr ptr ptr ptr) wine_cuGraphExecMemsetNodeSetParams
@ stdcall cuGraphExecUpdate(ptr ptr ptr ptr) wine_cuGraphExecUpdate
@ stdcall cuGraphExternalSemaphoresSignalNodeGetParams(ptr ptr) wine_cuGraphExternalSemaphoresSignalNodeGetParams
@ stdcall cuGraphExternalSemaphoresSignalNodeSetParams(ptr ptr) wine_cuGraphExternalSemaphoresSignalNodeSetParams
@ stdcall cuGraphExternalSemaphoresWaitNodeGetParams(ptr ptr) wine_cuGraphExternalSemaphoresWaitNodeGetParams
@ stdcall cuGraphExternalSemaphoresWaitNodeSetParams(ptr ptr) wine_cuGraphExternalSemaphoresWaitNodeSetParams
@ stdcall cuGraphInstantiateWithFlags(ptr ptr long) wine_cuGraphInstantiateWithFlags
@ stdcall cuGraphKernelNodeCopyAttributes(ptr ptr) wine_cuGraphKernelNodeCopyAttributes
@ stdcall cuGraphKernelNodeGetAttribute(ptr ptr ptr) wine_cuGraphKernelNodeGetAttribute
@ stdcall cuGraphKernelNodeSetAttribute(ptr ptr ptr) wine_cuGraphKernelNodeSetAttribute
@ stdcall cuGraphMemAllocNodeGetParams(ptr ptr) wine_cuGraphMemAllocNodeGetParams
@ stdcall cuGraphMemFreeNodeGetParams(ptr ptr) wine_cuGraphMemFreeNodeGetParams
@ stdcall cuGraphReleaseUserObject(ptr ptr long) wine_cuGraphReleaseUserObject
@ stdcall cuGraphRetainUserObject(ptr ptr long long) wine_cuGraphRetainUserObject
@ stdcall cuGraphUpload(ptr ptr) wine_cuGraphUpload
@ stdcall cuGraphUpload_ptsz(ptr ptr) wine_cuGraphUpload_ptsz
@ stdcall cuMemAddressFree(double long) wine_cuMemAddressFree
@ stdcall cuMemAddressReserve(ptr long long double long) wine_cuMemAddressReserve
@ stdcall cuMemAllocFromPoolAsync(ptr long ptr ptr) wine_cuMemAllocFromPoolAsync
@ stdcall cuMemAllocFromPoolAsync_ptsz(ptr long ptr ptr) wine_cuMemAllocFromPoolAsync_ptsz
@ stdcall cuMemCreate(ptr long ptr long) wine_cuMemCreate
@ stub cuMemExportToShareableHandle
@ stdcall cuMemGetAccess(ptr ptr double) wine_cuMemGetAccess
@ stub cuMemGetAllocationPropertiesFromHandle
@ stub cuMemImportFromShareableHandle
@ stdcall cuMemMap(double long long double double) wine_cuMemMap
@ stub cuMemMapArrayAsync
@ stub cuMemMapArrayAsync_ptsz
@ stdcall cuMemPoolCreate(ptr ptr) wine_cuMemPoolCreate
@ stdcall cuMemPoolDestroy(ptr) wine_cuMemPoolDestroy
@ stdcall cuMemPoolExportPointer(ptr double) wine_cuMemPoolExportPointer
@ stdcall cuMemPoolExportToShareableHandle(ptr ptr ptr long) wine_cuMemPoolExportToShareableHandle
@ stdcall cuMemPoolGetAccess(ptr ptr ptr) wine_cuMemPoolGetAccess
@ stdcall cuMemPoolGetAttribute(ptr long ptr) wine_cuMemPoolGetAttribute
@ stdcall cuMemPoolImportFromShareableHandle(ptr ptr ptr long) wine_cuMemPoolImportFromShareableHandle
@ stdcall cuMemPoolImportPointer(ptr ptr ptr) wine_cuMemPoolImportPointer
@ stdcall cuMemPoolSetAccess(ptr ptr long) wine_cuMemPoolSetAccess
@ stdcall cuMemPoolTrimTo(ptr long) wine_cuMemPoolTrimTo
@ stdcall cuMemRelease(double) wine_cuMemRelease
@ stub cuMemRetainAllocationHandle
@ stdcall cuMemSetAccess(double long ptr long) wine_cuMemSetAccess
@ stdcall cuMemUnmap(double long) wine_cuMemUnmap
@ stdcall cuMipmappedArrayGetSparseProperties(ptr ptr) wine_cuMipmappedArrayGetSparseProperties
@ stdcall cuOccupancyAvailableDynamicSMemPerBlock(ptr ptr long long) wine_cuOccupancyAvailableDynamicSMemPerBlock
@ stdcall cuStreamCopyAttributes(ptr ptr) wine_cuStreamCopyAttributes
@ stdcall cuStreamCopyAttributes_ptsz(ptr ptr) wine_cuStreamCopyAttributes_ptsz
@ stdcall cuStreamGetAttribute(ptr ptr ptr) wine_cuStreamGetAttribute
@ stdcall cuStreamGetAttribute_ptsz(ptr ptr ptr) wine_cuStreamGetAttribute_ptsz
@ stdcall cuStreamSetAttribute(ptr ptr ptr) wine_cuStreamSetAttribute
@ stdcall cuStreamSetAttribute_ptsz(ptr ptr ptr) wine_cuStreamSetAttribute_ptsz
@ stdcall cuStreamUpdateCaptureDependencies(ptr ptr long long) wine_cuStreamUpdateCaptureDependencies
@ stdcall cuStreamUpdateCaptureDependencies_ptsz(ptr ptr long long) wine_cuStreamUpdateCaptureDependencies_ptsz
@ stdcall cuUserObjectCreate(ptr ptr ptr long long) wine_cuUserObjectCreate
@ stdcall cuUserObjectRelease(ptr long) wine_cuUserObjectRelease
@ stdcall cuUserObjectRetain(ptr long) wine_cuUserObjectRetain
@ stub cuDeviceGetNvSciSyncAttributes
@ stub cuEGLStreamConsumerAcquireFrame
@ stub cuEGLStreamConsumerConnect
@ stub cuEGLStreamConsumerConnectWithFlags
@ stub cuEGLStreamConsumerDisconnect
@ stub cuEGLStreamConsumerReleaseFrame
@ stub cuEGLStreamProducerConnect
@ stub cuEGLStreamProducerDisconnect
@ stub cuEGLStreamProducerPresentFrame
@ stub cuEGLStreamProducerReturnFrame
@ stub cuEventCreateFromEGLSync
@ stub cuGraphicsEGLRegisterImage
@ stub cuGraphicsResourceGetMappedEglFrame
@ stub cuGraphicsVDPAURegisterOutputSurface
@ stub cuGraphicsVDPAURegisterVideoSurface
@ stub cuVDPAUCtxCreate
@ stub cuVDPAUCtxCreate_v2
@ stub cuVDPAUGetDevice
@ stdcall cuArrayGetMemoryRequirements(ptr ptr long) wine_cuArrayGetMemoryRequirements
@ stdcall cuMipmappedArrayGetMemoryRequirements(ptr ptr long) wine_cuMipmappedArrayGetMemoryRequirements
@ stdcall cuGraphNodeSetEnabled(ptr ptr long) wine_cuGraphNodeSetEnabled
@ stdcall cuGraphNodeGetEnabled(ptr ptr ptr) wine_cuGraphNodeGetEnabled
@ stub cudbgApiAttach
@ stub cudbgApiClientPid
@ stub cudbgApiClientRevision
@ stub cudbgApiDetach
@ stub cudbgApiInit
@ stub cudbgAttachHandlerAvailable
@ stub cudbgDebuggerCapabilities
@ stub cudbgDebuggerInitialized
@ stub cudbgDetachSuspendedDevicesMask
@ stub cudbgEnableIntegratedMemcheck
@ stub cudbgEnableLaunchBlocking
@ stub cudbgEnablePreemptionDebugging
@ stub cudbgGetAPI
@ stub cudbgGetAPIVersion
@ stub cudbgInjectionPath
@ stub cudbgIpcFlag
@ stub cudbgMain
@ stub cudbgReportDriverApiError
@ stub cudbgReportDriverApiErrorFlags
@ stub cudbgReportDriverInternalError
@ stub cudbgReportedDriverApiErrorCode
@ stub cudbgReportedDriverApiErrorFuncNameAddr
@ stub cudbgReportedDriverApiErrorFuncNameSize
@ stub cudbgReportedDriverInternalErrorCode
@ stub cudbgResumeForAttachDetach
@ stub cudbgRpcEnabled
@ stub cudbgSessionId
@ stub cudbgUseExternalDebugger
@ stdcall cuGraphAddBatchMemOpNode(ptr ptr ptr long ptr) wine_cuGraphAddBatchMemOpNode
@ stdcall cuGraphBatchMemOpNodeGetParams(ptr ptr) wine_cuGraphBatchMemOpNodeGetParams
@ stdcall cuGraphBatchMemOpNodeSetParams(ptr ptr) wine_cuGraphBatchMemOpNodeSetParams
@ stdcall cuGraphExecBatchMemOpNodeSetParams(ptr ptr ptr) wine_cuGraphExecBatchMemOpNodeSetParams
@ stdcall cuStreamBatchMemOp_v2(ptr long ptr long) wine_cuStreamBatchMemOp_v2
@ stdcall cuStreamBatchMemOp_v2_ptsz(ptr long ptr long) wine_cuStreamBatchMemOp_v2_ptsz
@ stdcall cuStreamWaitValue32_v2(ptr double long long) wine_cuStreamWaitValue32_v2
@ stdcall cuStreamWaitValue64_v2(ptr double int64 long) wine_cuStreamWaitValue64_v2
@ stdcall cuStreamWaitValue64_v2_ptsz(ptr double int64 long) wine_cuStreamWaitValue64_v2_ptsz
@ stdcall cuStreamWriteValue32_v2(ptr double long long) wine_cuStreamWriteValue32_v2
@ stdcall cuStreamWriteValue32_v2_ptsz(ptr double long long) wine_cuStreamWriteValue32_v2_ptsz
@ stdcall cuStreamWriteValue64_v2(ptr double int64 long) wine_cuStreamWriteValue64_v2
@ stdcall cuStreamWaitValue32_v2_ptsz(ptr double long long) wine_cuStreamWaitValue32_v2_ptsz
@ stdcall cuCtxGetId(ptr ptr) wine_cuCtxGetId
@ stdcall cuStreamGetId(ptr ptr) wine_cuStreamGetId
@ stdcall cuStreamGetId_ptsz(ptr ptr) wine_cuStreamGetId_ptsz
@ stub cuGraphAddKernelnNode
@ stdcall cuGraphExecGetFlags(ptr ptr) wine_cuGraphExecGetFlags
@ stub cuTensorMapEncodeTiled
@ stub cuTensorMapEncodeIm2col
@ stub cuTensorMapReplaceAddress
@ stdcall cuLibraryLoadData(ptr ptr ptr ptr long ptr ptr long) wine_cuLibraryLoadData
@ stdcall cuLibraryLoadFromFile(ptr ptr ptr ptr long ptr ptr long) wine_cuLibraryLoadFromFile
@ stdcall cuLibraryUnload(ptr) wine_cuLibraryUnload
@ stdcall cuLibraryGetKernel(ptr ptr str) wine_cuLibraryGetKernel
@ stdcall cuLibraryGetModule(ptr ptr) wine_cuLibraryGetModule
@ stdcall cuKernelGetFunction(ptr ptr) wine_cuKernelGetFunction
@ stdcall cuLibraryGetGlobal(ptr ptr ptr str) wine_cuLibraryGetGlobal
@ stdcall cuLibraryGetManaged(ptr ptr ptr str) wine_cuLibraryGetManaged
@ stdcall cuKernelGetAttribute(ptr long ptr long) wine_cuKernelGetAttribute
@ stdcall cuKernelSetAttribute(long long ptr long) wine_cuKernelSetAttribute
@ stdcall cuKernelSetCacheConfig(ptr ptr long) wine_cuKernelSetCacheConfig
@ stdcall cuLibraryGetUnifiedFunction(ptr ptr str) wine_cuLibraryGetUnifiedFunction
@ stdcall cuGraphInstantiateWithParams(ptr ptr ptr) wine_cuGraphInstantiateWithParams
@ stdcall cuGraphInstantiateWithParams_ptsz(ptr ptr ptr) wine_cuGraphInstantiateWithParams_ptsz
@ stdcall cuCtxSetFlags(long) wine_cuCtxSetFlags
@ stub cuCoredumpGetAttribute
@ stub cuCoredumpGetAttributeGlobal
@ stub cuCoredumpSetAttribute
@ stub cuCoredumpSetAttributeGlobal
@ stub cuEGLApiInit
@ stdcall cuGraphAddKernelNode_v2(ptr ptr ptr long ptr) wine_cuGraphAddKernelNode_v2
@ stdcall cuGraphAddNode(ptr ptr ptr long ptr) wine_cuGraphAddNode
@ stdcall cuGraphExecKernelNodeSetParams_v2(ptr ptr ptr) wine_cuGraphExecKernelNodeSetParams_v2
@ stdcall cuGraphExecNodeSetParams(ptr ptr ptr) wine_cuGraphExecNodeSetParams
@ stdcall cuGraphExecUpdate_v2(ptr ptr ptr) wine_cuGraphExecUpdate_v2
@ stdcall cuGraphKernelNodeGetParams_v2(ptr ptr) wine_cuGraphKernelNodeGetParams_v2
@ stdcall cuGraphKernelNodeSetParams_v2(ptr ptr) wine_cuGraphKernelNodeSetParams_v2
@ stdcall cuGraphNodeSetParams(ptr ptr) wine_cuGraphNodeSetParams
@ stdcall cuMemAdvise_v2(double long ptr ptr) wine_cuMemAdvise_v2
@ stub cuMemGetAttribute
@ stub cuMemGetAttribute_v2
@ stdcall cuMemPrefetchAsync_v2(double long ptr long ptr) wine_cuMemPrefetchAsync_v2
@ stdcall cuMemPrefetchAsync_v2_ptsz(double long ptr long ptr) wine_cuMemPrefetchAsync_v2_ptsz
@ stdcall cuMulticastAddDevice(double long) wine_cuMulticastAddDevice
@ stdcall cuMulticastBindAddr(double long double long double) wine_cuMulticastBindAddr
@ stdcall cuMulticastBindMem(double long double long long double) wine_cuMulticastBindMem
@ stdcall cuMulticastCreate(ptr ptr) wine_cuMulticastCreate
@ stdcall cuMulticastGetGranularity(ptr ptr ptr) wine_cuMulticastGetGranularity
@ stdcall cuMulticastUnbind(double long long long) wine_cuMulticastUnbind
@ stdcall cuGetProcAddress(ptr ptr long int64) wine_cuGetProcAddress
@ stdcall cuGetProcAddress_v2(ptr ptr long int64 ptr) wine_cuGetProcAddress_v2
@ stdcall cuKernelGetName(ptr ptr) wine_cuKernelGetName
@ stdcall cuFuncGetName(ptr ptr) wine_cuFuncGetName
@ stdcall cuGraphGetEdges_v2(ptr ptr ptr ptr ptr) wine_cuGraphGetEdges_v2
@ stdcall cuGraphNodeGetDependencies_v2(ptr ptr ptr ptr) wine_cuGraphNodeGetDependencies_v2
@ stdcall cuGraphNodeGetDependentNodes_v2(ptr ptr ptr ptr) wine_cuGraphNodeGetDependentNodes_v2
@ stdcall cuGraphAddDependencies_v2(ptr ptr ptr ptr long) wine_cuGraphAddDependencies_v2
@ stdcall cuGraphRemoveDependencies_v2(ptr ptr ptr ptr long) wine_cuGraphRemoveDependencies_v2
@ stdcall cuStreamBeginCaptureToGraph(ptr ptr ptr ptr long long) wine_cuStreamBeginCaptureToGraph
@ stdcall cuStreamBeginCaptureToGraph_ptsz(ptr ptr ptr ptr long long) wine_cuStreamBeginCaptureToGraph_ptsz
@ stdcall cuStreamGetCaptureInfo_v3(ptr ptr ptr ptr ptr ptr ptr) wine_cuStreamGetCaptureInfo_v3
@ stdcall cuStreamGetCaptureInfo_v3_ptsz(ptr ptr ptr ptr ptr ptr ptr) wine_cuStreamGetCaptureInfo_v3_ptsz
@ stdcall cuStreamUpdateCaptureDependencies_v2(ptr ptr ptr long long) wine_cuStreamUpdateCaptureDependencies_v2
@ stdcall cuStreamUpdateCaptureDependencies_v2_ptsz(ptr ptr ptr long long) wine_cuStreamUpdateCaptureDependencies_v2_ptsz
@ stdcall cuGraphAddNode_v2(ptr ptr ptr ptr long ptr) wine_cuGraphAddNode_v2
@ stdcall cuGraphConditionalHandleCreate(ptr ptr ptr long long) wine_cuGraphConditionalHandleCreate
@ stdcall cuFuncGetParamInfo(ptr long ptr ptr) wine_cuFuncGetParamInfo
@ stdcall cuFuncIsLoaded(ptr ptr) wine_cuFuncIsLoaded
@ stdcall cuFuncLoad(ptr) wine_cuFuncLoad
@ stdcall cuModuleGetFunctionCount(ptr ptr) wine_cuModuleGetFunctionCount
@ stdcall cuModuleEnumerateFunctions(ptr long ptr) wine_cuModuleEnumerateFunctions
@ stdcall cuLibraryGetKernelCount(ptr ptr) wine_cuLibraryGetKernelCount
@ stdcall cuLibraryEnumerateKernels(ptr long ptr) wine_cuLibraryEnumerateKernels
@ stdcall cuKernelGetParamInfo(ptr long ptr ptr) wine_cuKernelGetParamInfo
@ stdcall cuDeviceRegisterAsyncNotification(long ptr ptr ptr) wine_cuDeviceRegisterAsyncNotification
@ stdcall cuDeviceUnregisterAsyncNotification(long ptr) wine_cuDeviceUnregisterAsyncNotification
@ stdcall cuGreenCtxCreate(ptr ptr long long) wine_cuGreenCtxCreate
@ stdcall cuGreenCtxDestroy(ptr) wine_cuGreenCtxDestroy
@ stdcall cuDeviceGetDevResource(long ptr ptr) wine_cuDeviceGetDevResource
@ stdcall cuCtxGetDevResource(ptr ptr ptr) wine_cuCtxGetDevResource
@ stdcall cuGreenCtxGetDevResource(ptr ptr ptr) wine_cuGreenCtxGetDevResource
@ stdcall cuGreenCtxRecordEvent(ptr ptr) wine_cuGreenCtxRecordEvent
@ stdcall cuGreenCtxWaitEvent(ptr ptr) wine_cuGreenCtxWaitEvent
@ stdcall cuDevResourceGenerateDesc(ptr ptr long) wine_cuDevResourceGenerateDesc
@ stdcall cuDevSmResourceSplitByCount(ptr ptr ptr ptr long long) wine_cuDevSmResourceSplitByCount
@ stdcall cuStreamGetGreenCtx(ptr ptr) wine_cuStreamGetGreenCtx
@ stdcall cuCtxFromGreenCtx(ptr ptr) wine_cuCtxFromGreenCtx
@ stdcall cuKernelGetLibrary(ptr ptr) wine_cuKernelGetLibrary
@ stdcall cuCtxRecordEvent(ptr ptr) wine_cuCtxRecordEvent
@ stdcall cuCtxWaitEvent(ptr ptr) wine_cuCtxWaitEvent
@ stdcall cuGreenCtxStreamCreate(ptr ptr long long) wine_cuGreenCtxStreamCreate
