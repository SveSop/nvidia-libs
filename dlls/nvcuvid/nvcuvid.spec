@ stub CreateEncoderInterface
@ stdcall cuvidMapVideoFrame64(ptr long ptr ptr ptr) wine_cuvidMapVideoFrame64
@ stdcall cuvidUnmapVideoFrame64(ptr int64) wine_cuvidUnmapVideoFrame64
@ stdcall cuvidCreateDecoder(ptr ptr) wine_cuvidCreateDecoder
@ stdcall cuvidCreateVideoParser(ptr ptr) wine_cuvidCreateVideoParser
@ stdcall cuvidCreateVideoSource(ptr str ptr) wine_cuvidCreateVideoSource
@ stub cuvidCreateVideoSourceW
@ stdcall cuvidCtxLock(ptr long) wine_cuvidCtxLock
@ stdcall cuvidCtxLockCreate(ptr ptr) wine_cuvidCtxLockCreate
@ stdcall cuvidCtxLockDestroy(ptr) wine_cuvidCtxLockDestroy
@ stdcall cuvidCtxUnlock(ptr long) wine_cuvidCtxUnlock
@ stdcall cuvidDecodePicture(ptr ptr) wine_cuvidDecodePicture
@ stdcall cuvidDestroyDecoder(ptr) wine_cuvidDestroyDecoder
@ stdcall cuvidDestroyVideoParser(ptr) wine_cuvidDestroyVideoParser
@ stdcall cuvidDestroyVideoSource(ptr) wine_cuvidDestroyVideoSource
@ stdcall cuvidGetSourceAudioFormat(ptr ptr long) wine_cuvidGetSourceAudioFormat
@ stdcall cuvidGetSourceVideoFormat(ptr ptr long) wine_cuvidGetSourceVideoFormat
@ stub cuvidGetVideoFrameSurface
#@ stdcall cuvidGetVideoFrameSurface(ptr long ptr) wine_cuvidGetVideoFrameSurface
@ stdcall cuvidGetVideoSourceState(ptr) wine_cuvidGetVideoSourceState
@ stdcall cuvidMapVideoFrame(ptr long ptr ptr ptr) wine_cuvidMapVideoFrame
@ stdcall cuvidParseVideoData(ptr ptr) wine_cuvidParseVideoData
@ stdcall cuvidSetVideoSourceState(ptr long) wine_cuvidSetVideoSourceState
@ stdcall cuvidUnmapVideoFrame(ptr long) wine_cuvidUnmapVideoFrame
