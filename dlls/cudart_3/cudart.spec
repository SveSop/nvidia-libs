@ stdcall cudaBindTexture(ptr ptr ptr ptr long) wine_cudaBindTexture
@ stdcall cudaBindTexture2D(ptr ptr ptr ptr long long long) wine_cudaBindTexture2D
@ stdcall cudaBindTextureToArray(ptr ptr ptr) wine_cudaBindTextureToArray
@ stdcall cudaChooseDevice(ptr ptr) wine_cudaChooseDevice
@ stdcall cudaConfigureCall(ptr ptr long ptr) wine_cudaConfigureCall
@ stdcall cudaGetChannelDesc(ptr ptr) wine_cudaGetChannelDesc
@ stdcall cudaDriverGetVersion(ptr) wine_cudaDriverGetVersion
@ stdcall cudaGetDeviceCount(ptr) wine_cudaGetDeviceCount
@ stdcall cudaGetDeviceProperties(ptr long) wine_cudaGetDeviceProperties
@ stdcall cudaRuntimeGetVersion(ptr) wine_cudaRuntimeGetVersion
@ stdcall cudaEventCreate(ptr) wine_cudaEventCreate
@ stdcall cudaEventCreateWithFlags(ptr long) wine_cudaEventCreateWithFlags
@ stdcall cudaEventDestroy(ptr) wine_cudaEventDestroy
@ stdcall cudaEventElapsedTime(ptr ptr ptr) wine_cudaEventElapsedTime
@ stdcall cudaEventQuery(ptr) wine_cudaEventQuery
@ stdcall cudaEventRecord(ptr ptr) wine_cudaEventRecord
@ stdcall cudaEventSynchronize(ptr) wine_cudaEventSynchronize
@ stdcall cudaFree(ptr) wine_cudaFree
@ stdcall cudaFreeArray(ptr) wine_cudaFreeArray
@ stdcall cudaFreeHost(ptr) wine_cudaFreeHost
@ stdcall cudaFuncGetAttributes(ptr ptr) wine_cudaFuncGetAttributes
@ stdcall cudaFuncSetCacheConfig(ptr ptr) wine_cudaFuncSetCacheConfig
@ stdcall cudaGetDevice(ptr) wine_cudaGetDevice
@ stdcall cudaGetErrorString(ptr) wine_cudaGetErrorString
@ stdcall cudaGetLastError() wine_cudaGetLastError
@ stdcall cudaGetSymbolAddress(ptr str) wine_cudaGetSymbolAddress
@ stdcall cudaGetSymbolSize(ptr str) wine_cudaGetSymbolSize
@ stdcall cudaGetTextureAlignmentOffset(ptr ptr) wine_cudaGetTextureAlignmentOffset
@ stdcall cudaGetTextureReference(ptr str) wine_cudaGetTextureReference
@ stdcall cudaGLMapBufferObject(ptr long) wine_cudaGLMapBufferObject
@ stdcall cudaGLRegisterBufferObject(long) wine_cudaGLRegisterBufferObject
@ stdcall cudaGLSetBufferObjectMapFlags(long long) wine_cudaGLSetBufferObjectMapFlags
@ stdcall cudaGLSetGLDevice(long) wine_cudaGLSetGLDevice
@ stdcall cudaGLUnmapBufferObject(long) wine_cudaGLUnmapBufferObject
@ stdcall cudaGLUnmapBufferObjectAsync(long ptr) wine_cudaGLUnmapBufferObjectAsync
@ stdcall cudaGLUnregisterBufferObject(long) wine_cudaGLUnregisterBufferObject
@ stdcall cudaGraphicsGLRegisterBuffer(ptr long long) wine_cudaGraphicsGLRegisterBuffer
@ stdcall cudaGraphicsGLRegisterImage(ptr long long long) wine_cudaGraphicsGLRegisterImage
@ stdcall cudaGraphicsMapResources(long ptr ptr) wine_cudaGraphicsMapResources
@ stdcall cudaGraphicsResourceGetMappedPointer(ptr ptr ptr) wine_cudaGraphicsResourceGetMappedPointer
@ stdcall cudaGraphicsResourceSetMapFlags(ptr long) wine_cudaGraphicsResourceSetMapFlags
@ stdcall cudaGraphicsSubResourceGetMappedArray(ptr ptr long long) wine_cudaGraphicsSubResourceGetMappedArray
@ stdcall cudaGraphicsUnmapResources(long ptr ptr) wine_cudaGraphicsUnmapResources
@ stdcall cudaGraphicsUnregisterResource(ptr) wine_cudaGraphicsUnregisterResource
@ stdcall cudaHostAlloc(ptr long long) wine_cudaHostAlloc
@ stdcall cudaHostGetDevicePointer(ptr ptr long) wine_cudaHostGetDevicePointer
@ stdcall cudaHostGetFlags(ptr ptr) wine_cudaHostGetFlags
@ stdcall cudaLaunch(str) wine_cudaLaunch
@ stdcall cudaMalloc(ptr long) wine_cudaMalloc
@ stdcall cudaMalloc3D(ptr ptr) wine_cudaMalloc3D
@ stdcall cudaMalloc3DArray(ptr ptr ptr long) wine_cudaMalloc3DArray
@ stdcall cudaMallocArray(ptr ptr long long long) wine_cudaMallocArray
@ stdcall cudaMallocHost(ptr long) wine_cudaMallocHost
@ stdcall cudaMallocPitch(ptr ptr long long) wine_cudaMallocPitch
@ stdcall cudaMemcpy(ptr ptr long ptr) wine_cudaMemcpy
@ stdcall cudaMemcpy2D(ptr long ptr long long long long ptr) wine_cudaMemcpy2D
@ stdcall cudaMemcpy2DArrayToArray(ptr long long long ptr long long long long ptr) wine_cudaMemcpy2DArrayToArray
@ stdcall cudaMemcpy2DAsync(ptr long ptr long long long ptr ptr) wine_cudaMemcpy2DAsync
@ stdcall cudaMemcpy2DFromArray(ptr long ptr long long long long long ptr) wine_cudaMemcpy2DFromArray
@ stdcall cudaMemcpy2DFromArrayAsync(ptr long ptr long long long long long ptr ptr) wine_cudaMemcpy2DFromArrayAsync
@ stdcall cudaMemcpy2DToArray(ptr long long long ptr long long long long ptr) wine_cudaMemcpy2DToArray
@ stdcall cudaMemcpy2DToArrayAsync(ptr long long long ptr long long long long ptr ptr) wine_cudaMemcpy2DToArrayAsync
@ stdcall cudaMemcpy3D(ptr) wine_cudaMemcpy3D
@ stdcall cudaMemcpy3DAsync(ptr ptr) wine_cudaMemcpy3DAsync
@ stdcall cudaMemcpyArrayToArray(ptr long long ptr long long long long ptr) wine_cudaMemcpyArrayToArray
@ stdcall cudaMemcpyAsync(ptr ptr long ptr ptr) wine_cudaMemcpyAsync
@ stdcall cudaMemcpyFromArray(ptr ptr ptr long long long ptr) wine_cudaMemcpyFromArray
@ stdcall cudaMemcpyFromArrayAsync(ptr ptr ptr long long long long ptr) wine_cudaMemcpyFromArrayAsync
@ stdcall cudaMemcpyFromSymbol(ptr ptr long long ptr) wine_cudaMemcpyFromSymbol
@ stdcall cudaMemcpyFromSymbolAsync(ptr ptr long long ptr ptr) wine_cudaMemcpyFromSymbolAsync
@ stdcall cudaMemcpyToArray(ptr long long ptr long ptr) wine_cudaMemcpyToArray
@ stdcall cudaMemcpyToArrayAsync(ptr long long long ptr long ptr) wine_cudaMemcpyToArrayAsync
@ stdcall cudaMemcpyToSymbol(ptr ptr long long ptr) wine_cudaMemcpyToSymbol
@ stdcall cudaMemcpyToSymbolAsync(ptr ptr long long ptr ptr) wine_cudaMemcpyToSymbolAsync
@ stdcall cudaMemGetInfo(ptr ptr) wine_cudaMemGetInfo
@ stdcall cudaMemset(ptr long long) wine_cudaMemset
@ stdcall cudaMemset2D(ptr long long long long long) wine_cudaMemset2D
@ stdcall cudaMemset3D(ptr long ptr) wine_cudaMemset3D
@ stdcall cudaSetDevice(long) wine_cudaSetDevice
@ stdcall cudaSetDeviceFlags(long) wine_cudaSetDeviceFlags
@ stdcall cudaSetDoubleForDevice(ptr) wine_cudaSetDoubleForDevice
@ stdcall cudaSetDoubleForHost(ptr) wine_cudaSetDoubleForHost
@ stdcall cudaSetupArgument(ptr long long) wine_cudaSetupArgument
@ stdcall cudaSetValidDevices(ptr long) wine_cudaSetValidDevices
@ stdcall cudaStreamCreate(ptr) wine_cudaStreamCreate
@ stdcall cudaStreamDestroy(ptr) wine_cudaStreamDestroy
@ stdcall cudaStreamQuery(ptr) wine_cudaStreamQuery
@ stdcall cudaStreamSynchronize(ptr) wine_cudaStreamSynchronize
@ stdcall cudaThreadExit() wine_cudaThreadExit
@ stdcall cudaThreadSynchronize() wine_cudaThreadSynchronize
@ stdcall cudaUnbindTexture(ptr) wine_cudaUnbindTexture
@ stdcall __cudaMutexOperation(long) wine___cudaMutexOperation
@ stdcall __cudaRegisterFatBinary(ptr) wine___cudaRegisterFatBinary
@ stdcall __cudaRegisterFunction(ptr str str str long ptr ptr ptr ptr ptr) wine___cudaRegisterFunction
@ stdcall __cudaRegisterShared(ptr ptr) wine___cudaRegisterShared
@ stdcall __cudaRegisterSharedVar(ptr ptr long long long long) wine___cudaRegisterSharedVar
@ stdcall __cudaRegisterTexture(ptr ptr ptr str long long long) wine___cudaRegisterTexture
@ stdcall __cudaRegisterVar(ptr str str str long long long long) wine___cudaRegisterVar
@ stdcall __cudaSynchronizeThreads(ptr ptr) wine___cudaSynchronizeThreads
@ stdcall __cudaTextureFetch(ptr ptr long ptr) wine___cudaTextureFetch
@ stdcall __cudaUnregisterFatBinary(ptr) wine___cudaUnregisterFatBinary
@ stdcall cudaCreateChannelDesc(long long long long ptr) wine_cudaCreateChannelDesc
