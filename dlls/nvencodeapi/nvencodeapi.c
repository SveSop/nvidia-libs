/*
 * Copyright (C) 2015 Michael Müller
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

#include "windef.h"
#include "winbase.h"
#include "wine/debug.h"

#include "nvencodeapi.h"

WINE_DEFAULT_DEBUG_CHANNEL(nvencodeapi);

static void *libnvidia_encode_handle = NULL;
static LINUX_NV_ENCODE_API_FUNCTION_LIST origFunctions;

static NVENCSTATUS (*pNvEncodeAPICreateInstance)(LINUX_NV_ENCODE_API_FUNCTION_LIST *functionList);
static NVENCSTATUS (*pNvEncodeAPIGetMaxSupportedVersion)(uint32_t* version);

static NVENCSTATUS WINAPI NvEncOpenEncodeSession(void *device, uint32_t deviceType, void **encoder)
{
    TRACE("(%p, %u, %p)\n", device, deviceType, encoder);
    return origFunctions.nvEncOpenEncodeSession(device, deviceType, encoder);
}

static NVENCSTATUS WINAPI NvEncGetEncodeGUIDCount(void *encoder, uint32_t *encodeGUIDCount)
{
    TRACE("(%p, %p)\n", encoder, encodeGUIDCount);
    return origFunctions.nvEncGetEncodeGUIDCount(encoder, encodeGUIDCount);
}

static NVENCSTATUS WINAPI NvEncGetEncodeGUIDs(void *encoder, GUID *GUIDs, uint32_t guidArraySize, uint32_t *GUIDCount)
{
    TRACE("(%p, %p, %u, %p)\n", encoder, GUIDs, guidArraySize, GUIDCount);
    return origFunctions.nvEncGetEncodeGUIDs(encoder, GUIDs, guidArraySize, GUIDCount);
}

static NVENCSTATUS WINAPI NvEncGetEncodeProfileGUIDCount(void *encoder, GUID encodeGUID, uint32_t *encodeProfileGUIDCount)
{
    TRACE("(%p, %s, %p)\n", encoder, debugstr_guid(&encodeGUID), encodeProfileGUIDCount);
    return origFunctions.nvEncGetEncodeProfileGUIDCount(encoder, encodeGUID, encodeProfileGUIDCount);
}

static NVENCSTATUS WINAPI NvEncGetEncodeProfileGUIDs(void *encoder, GUID encodeGUID, GUID *profileGUIDs,
                                                     uint32_t guidArraySize, uint32_t *GUIDCount)
{
    TRACE("(%p, %s, %p, %u, %p)\n", encoder, debugstr_guid(&encodeGUID), profileGUIDs, guidArraySize, GUIDCount);
    return origFunctions.nvEncGetEncodeProfileGUIDs(encoder, encodeGUID, profileGUIDs, guidArraySize, GUIDCount);
}

static NVENCSTATUS WINAPI NvEncGetInputFormatCount(void *encoder, GUID encodeGUID, uint32_t *inputFmtCount)
{
    TRACE("(%p, %s, %p)\n", encoder, debugstr_guid(&encodeGUID), inputFmtCount);
    return origFunctions.nvEncGetInputFormatCount(encoder, encodeGUID, inputFmtCount);
}

static NVENCSTATUS WINAPI NvEncGetInputFormats(void *encoder, GUID encodeGUID, NV_ENC_BUFFER_FORMAT *inputFmts,
                                               uint32_t inputFmtArraySize, uint32_t *inputFmtCount)
{
    TRACE("(%p, %s, %p)\n", encoder, debugstr_guid(&encodeGUID), inputFmtCount);
    return origFunctions.nvEncGetInputFormatCount(encoder, encodeGUID, inputFmtCount);
}

static NVENCSTATUS WINAPI NvEncGetEncodeCaps(void *encoder, GUID encodeGUID, NV_ENC_CAPS_PARAM *capsParam, int *capsVal)
{
    TRACE("(%p, %s, %p, %p)\n", encoder, debugstr_guid(&encodeGUID), capsParam, capsVal);
    return origFunctions.nvEncGetEncodeCaps(encoder, encodeGUID, capsParam, capsVal);
}

static NVENCSTATUS WINAPI NvEncGetEncodePresetCount(void *encoder, GUID encodeGUID, uint32_t *encodePresetGUIDCount)
{
    TRACE("(%p, %s, %p)\n", encoder, debugstr_guid(&encodeGUID), encodePresetGUIDCount);
    return origFunctions.nvEncGetEncodePresetCount(encoder, encodeGUID, encodePresetGUIDCount);
}

static NVENCSTATUS WINAPI NvEncGetEncodePresetGUIDs(void *encoder, GUID encodeGUID, GUID *presetGUIDs, uint32_t guidArraySize,
                                                    uint32_t *encodePresetGUIDCount)
{
    TRACE("(%p, %s, %p, %u, %p)\n", encoder, debugstr_guid(&encodeGUID), presetGUIDs, guidArraySize, encodePresetGUIDCount);
    return origFunctions.nvEncGetEncodePresetGUIDs(encoder, encodeGUID, presetGUIDs, guidArraySize, encodePresetGUIDCount);
}

static NVENCSTATUS WINAPI NvEncGetEncodePresetConfig(void *encoder, GUID encodeGUID, GUID presetGUID, NV_ENC_PRESET_CONFIG *presetConfig)
{
    TRACE("(%p, %s, %s, %p)\n", encoder, debugstr_guid(&encodeGUID), debugstr_guid(&presetGUID), presetConfig);
    return origFunctions.nvEncGetEncodePresetConfig(encoder, encodeGUID, presetGUID, presetConfig);
}

static NVENCSTATUS WINAPI NvEncInitializeEncoder(void *encoder, NV_ENC_INITIALIZE_PARAMS *createEncodeParams)
{
    NV_ENC_INITIALIZE_PARAMS linux_encode_params;

    TRACE("(%p, %p)\n", encoder, createEncodeParams);

    if (!createEncodeParams)
        return NV_ENC_ERR_INVALID_PTR;

    if (createEncodeParams->enableEncodeAsync)
    {
        FIXME("Async encoding is not supported by the linux NVIDIA driver.\n");
        FIXME("Trying to emulate async mode, but this might not work for all applications.\n");

        /* Forward modified information to the linux library. */
        linux_encode_params = *createEncodeParams;
        createEncodeParams = &linux_encode_params;
        linux_encode_params.enableEncodeAsync = 0;
    }

    return origFunctions.nvEncInitializeEncoder(encoder, createEncodeParams);
}

static NVENCSTATUS WINAPI NvEncCreateInputBuffer(void *encoder, NV_ENC_CREATE_INPUT_BUFFER *createInputBufferParams)
{
    TRACE("(%p, %p)\n", encoder, createInputBufferParams);
    return origFunctions.nvEncCreateInputBuffer(encoder, createInputBufferParams);
}

static NVENCSTATUS WINAPI NvEncDestroyInputBuffer(void *encoder, NV_ENC_INPUT_PTR inputBuffer)
{
    TRACE("(%p, %p)\n", encoder, inputBuffer);
    return origFunctions.nvEncDestroyInputBuffer(encoder, inputBuffer);
}

static NVENCSTATUS WINAPI NvEncCreateBitstreamBuffer(void *encoder, NV_ENC_CREATE_BITSTREAM_BUFFER *createBitstreamBufferParams)
{
    TRACE("(%p, %p)\n", encoder, createBitstreamBufferParams);
    return origFunctions.nvEncCreateBitstreamBuffer(encoder, createBitstreamBufferParams);
}

static NVENCSTATUS WINAPI NvEncDestroyBitstreamBuffer(void *encoder, NV_ENC_OUTPUT_PTR bitstreamBuffer)
{
    TRACE("(%p, %p)\n", encoder, bitstreamBuffer);
    return origFunctions.nvEncDestroyBitstreamBuffer(encoder, bitstreamBuffer);
}

static NVENCSTATUS WINAPI NvEncEncodePicture(void *encoder, NV_ENC_PIC_PARAMS *encodePicParams)
{
    NVENCSTATUS result;
    TRACE("(%p, %p)\n", encoder, encodePicParams);

    result = origFunctions.nvEncEncodePicture(encoder, encodePicParams);

    if (encodePicParams->completionEvent)
        SetEvent(encodePicParams->completionEvent);

    return result;
}

static NVENCSTATUS WINAPI NvEncLockBitstream(void *encoder, NV_ENC_LOCK_BITSTREAM *lockBitstreamBufferParams)
{
    TRACE("(%p, %p)\n", encoder, lockBitstreamBufferParams);
    return origFunctions.nvEncLockBitstream(encoder, lockBitstreamBufferParams);
}

static NVENCSTATUS WINAPI NvEncUnlockBitstream(void *encoder, NV_ENC_OUTPUT_PTR bitstreamBuffer)
{
    TRACE("(%p, %p)\n", encoder, bitstreamBuffer);
    return origFunctions.nvEncUnlockBitstream(encoder, bitstreamBuffer);
}

static NVENCSTATUS WINAPI NvEncLockInputBuffer(void *encoder, NV_ENC_LOCK_INPUT_BUFFER *lockInputBufferParams)
{
    TRACE("(%p, %p)\n", encoder, lockInputBufferParams);
    return origFunctions.nvEncLockInputBuffer(encoder, lockInputBufferParams);
}

static NVENCSTATUS WINAPI NvEncUnlockInputBuffer(void *encoder, NV_ENC_INPUT_PTR inputBuffer)
{
    TRACE("(%p, %p)\n", encoder, inputBuffer);
    return origFunctions.nvEncUnlockInputBuffer(encoder, inputBuffer);
}

static NVENCSTATUS WINAPI NvEncGetEncodeStats(void *encoder, NV_ENC_STAT *encodeStats)
{
    TRACE("(%p, %p)\n", encoder, encodeStats);
    return origFunctions.nvEncGetEncodeStats(encoder, encodeStats);
}

static NVENCSTATUS WINAPI NvEncGetSequenceParams(void *encoder, NV_ENC_SEQUENCE_PARAM_PAYLOAD *sequenceParamPayload)
{
    TRACE("(%p, %p)\n", encoder, sequenceParamPayload);
    return origFunctions.nvEncGetSequenceParams(encoder, sequenceParamPayload);
}

static NVENCSTATUS WINAPI NvEncRegisterAsyncEvent(void *encoder, NV_ENC_EVENT_PARAMS *eventParams)
{
    TRACE("(%p, %p)\n", encoder, eventParams);
    /* This function will always fail as the linux NVIDIA driver doesn't support async mode */
    /* return origFunctions.nvEncRegisterAsyncEvent(encoder, eventParams); */
    return NV_ENC_SUCCESS;
}

static NVENCSTATUS WINAPI NvEncUnregisterAsyncEvent(void *encoder, NV_ENC_EVENT_PARAMS *eventParams)
{
    TRACE("(%p, %p)\n", encoder, eventParams);
    /* This function will always fail as the linux NVIDIA driver doesn't support async mode */
    /* return origFunctions.nvEncUnregisterAsyncEvent(encoder, eventParams); */
    return NV_ENC_SUCCESS;
}

static NVENCSTATUS WINAPI NvEncMapInputResource(void *encoder, NV_ENC_MAP_INPUT_RESOURCE *mapInputResParams)
{
    TRACE("(%p, %p)\n", encoder, mapInputResParams);
    return origFunctions.nvEncMapInputResource(encoder, mapInputResParams);
}

static NVENCSTATUS WINAPI NvEncUnmapInputResource(void *encoder, NV_ENC_INPUT_PTR mappedInputBuffer)
{
    TRACE("(%p, %p)\n", encoder, mappedInputBuffer);
    return origFunctions.nvEncUnmapInputResource(encoder, mappedInputBuffer);
}

static NVENCSTATUS WINAPI NvEncDestroyEncoder(void *encoder)
{
    TRACE("(%p)\n", encoder);
    return origFunctions.nvEncDestroyEncoder(encoder);
}

static NVENCSTATUS WINAPI NvEncInvalidateRefFrames(void *encoder, uint64_t invalidRefFrameTimeStamp)
{
    TRACE("(%p, %s)\n", encoder, wine_dbgstr_longlong(invalidRefFrameTimeStamp));
    return origFunctions.nvEncInvalidateRefFrames(encoder, invalidRefFrameTimeStamp);
}

static NVENCSTATUS WINAPI NvEncOpenEncodeSessionEx(NV_ENC_OPEN_ENCODE_SESSION_EX_PARAMS *openSessionExParams, void **encoder)
{
    TRACE("(%p, %p)\n", openSessionExParams, encoder);
    return origFunctions.nvEncOpenEncodeSessionEx(openSessionExParams, encoder);
}

static NVENCSTATUS WINAPI NvEncRegisterResource(void *encoder, NV_ENC_REGISTER_RESOURCE *registerResParams)
{
    TRACE("(%p, %p)\n", encoder, registerResParams);
    return origFunctions.nvEncRegisterResource(encoder, registerResParams);
}

static NVENCSTATUS WINAPI NvEncUnregisterResource(void *encoder, NV_ENC_REGISTERED_PTR registeredResource)
{
    TRACE("(%p, %p)\n", encoder, registeredResource);
    return origFunctions.nvEncUnregisterResource(encoder, registeredResource);
}

static NVENCSTATUS WINAPI NvEncReconfigureEncoder(void *encoder, NV_ENC_RECONFIGURE_PARAMS *reInitEncodeParams)
{
    TRACE("(%p, %p)\n", encoder, reInitEncodeParams);
    return origFunctions.nvEncReconfigureEncoder(encoder, reInitEncodeParams);
}

static NVENCSTATUS WINAPI NvEncCreateMVBuffer(void *encoder, NV_ENC_CREATE_MV_BUFFER *createMVBufferParams)
{
    TRACE("(%p, %p)\n", encoder, createMVBufferParams);
    return origFunctions.nvEncCreateMVBuffer(encoder, createMVBufferParams);
}

static NVENCSTATUS WINAPI NvEncDestroyMVBuffer(void *encoder, NV_ENC_OUTPUT_PTR MVBuffer)
{
    TRACE("(%p, %p)\n", encoder, MVBuffer);
    return origFunctions.nvEncDestroyMVBuffer(encoder, MVBuffer);
}

static NVENCSTATUS WINAPI NvEncRunMotionEstimationOnly(void *encoder, NV_ENC_MEONLY_PARAMS *MEOnlyParams)
{
    TRACE("(%p, %p)\n", encoder, MEOnlyParams);
    return origFunctions.nvEncRunMotionEstimationOnly(encoder, MEOnlyParams);
}

NVENCSTATUS WINAPI NvEncodeAPIGetMaxSupportedVersion(uint32_t* version)
{
    TRACE("(%p)\n", version);
    return pNvEncodeAPIGetMaxSupportedVersion(version);
}

NVENCSTATUS WINAPI NvEncodeAPICreateInstance(NV_ENCODE_API_FUNCTION_LIST *functionList)
{
    NVENCSTATUS status;

    TRACE("(%p)\n", functionList);

    if (!functionList)
        return NV_ENC_ERR_INVALID_PTR;

    /* we currently support 5.0 and 6.0 */
    if (functionList->version != NV_ENCODE_API_FUNCTION_LIST_VER &&
        functionList->version != NV_ENCODE_API_FUNCTION_LIST_VER_6_0)
    {
        FIXME("Application requested nvencodeapi version %x which is not supported yet\n",
              functionList->version);
        return NV_ENC_ERR_INVALID_VERSION;
    }

    memset(&origFunctions, 0, sizeof(origFunctions));
    origFunctions.version = functionList->version;
    status = pNvEncodeAPICreateInstance(&origFunctions);
    if (status)
    {
        FIXME("Failed to create native encoder for version %x\n", functionList->version);
        return status;
    }

    /* set all function points and reserved values to zero */
    memset(functionList, 0, sizeof(*functionList));
    functionList->version = origFunctions.version;

    #define SET_FUNCPTR(f) if (origFunctions.nv##f) functionList->nv##f = &Nv##f

    SET_FUNCPTR(EncOpenEncodeSession);
    SET_FUNCPTR(EncGetEncodeGUIDCount);
    SET_FUNCPTR(EncGetEncodeProfileGUIDCount);
    SET_FUNCPTR(EncGetEncodeProfileGUIDs);
    SET_FUNCPTR(EncGetEncodeGUIDs);
    SET_FUNCPTR(EncGetInputFormatCount);
    SET_FUNCPTR(EncGetInputFormats);
    SET_FUNCPTR(EncGetEncodeCaps);
    SET_FUNCPTR(EncGetEncodePresetCount);
    SET_FUNCPTR(EncGetEncodePresetGUIDs);
    SET_FUNCPTR(EncGetEncodePresetConfig);
    SET_FUNCPTR(EncInitializeEncoder);
    SET_FUNCPTR(EncCreateInputBuffer);
    SET_FUNCPTR(EncDestroyInputBuffer);
    SET_FUNCPTR(EncCreateBitstreamBuffer);
    SET_FUNCPTR(EncDestroyBitstreamBuffer);
    SET_FUNCPTR(EncEncodePicture);
    SET_FUNCPTR(EncLockBitstream);
    SET_FUNCPTR(EncUnlockBitstream);
    SET_FUNCPTR(EncLockInputBuffer);
    SET_FUNCPTR(EncUnlockInputBuffer);
    SET_FUNCPTR(EncGetEncodeStats);
    SET_FUNCPTR(EncGetSequenceParams);
    SET_FUNCPTR(EncRegisterAsyncEvent);
    SET_FUNCPTR(EncUnregisterAsyncEvent);
    SET_FUNCPTR(EncMapInputResource);
    SET_FUNCPTR(EncUnmapInputResource);
    SET_FUNCPTR(EncDestroyEncoder);
    SET_FUNCPTR(EncInvalidateRefFrames);
    SET_FUNCPTR(EncOpenEncodeSessionEx);
    SET_FUNCPTR(EncRegisterResource);
    SET_FUNCPTR(EncUnregisterResource);
    SET_FUNCPTR(EncReconfigureEncoder);
    SET_FUNCPTR(EncCreateMVBuffer);             /* available since 6.0 */
    SET_FUNCPTR(EncDestroyMVBuffer);            /* available since 6.0 */
    SET_FUNCPTR(EncRunMotionEstimationOnly);    /* available since 6.0 */

    #undef SET_FUNCPTR

    return NV_ENC_SUCCESS;
}

static BOOL load_nvencode(void)
{
    static const char *libname[] =
    {
        "libnvidia-encode.so",
        #ifdef __i386__
        "/usr/lib/i386-linux-gnu/nvidia/current/libnvidia-encode.so",
        #elif defined __x86_64__
        "/usr/lib/x86_64-linux-gnu/nvidia/current/libnvidia-encode.so",
        #endif
    };
    int i;

    for (i = 0; i < sizeof(libname)/sizeof(libname[0]); i++)
    {
        libnvidia_encode_handle = dlopen(libname[i], RTLD_NOW);
        if (libnvidia_encode_handle) break;
    }

    if (!libnvidia_encode_handle)
    {
        FIXME("Wine cannot find the libnvidia-encode.so library, NVIDIA video encoding support disabled.\n");
        return FALSE;
    }

    pNvEncodeAPICreateInstance = dlsym(libnvidia_encode_handle, "NvEncodeAPICreateInstance");
    if (!pNvEncodeAPICreateInstance)
    {
        FIXME("Can't find symbol NvEncodeAPICreateInstance.\n");
        return FALSE;
    }

    pNvEncodeAPIGetMaxSupportedVersion = dlsym(libnvidia_encode_handle, "NvEncodeAPIGetMaxSupportedVersion");
    if (!pNvEncodeAPIGetMaxSupportedVersion)
    {
        FIXME("Can't find symbol NvEncodeAPIGetMaxSupportedVersion.\n");
        return FALSE;
    }

    return TRUE;
}

BOOL WINAPI DllMain(HINSTANCE instance, DWORD reason, LPVOID reserved)
{
    TRACE("(%p, %u, %p)\n", instance, reason, reserved);

    switch (reason)
    {
        case DLL_PROCESS_ATTACH:
            DisableThreadLibraryCalls(instance);
            if (!load_nvencode()) return FALSE;
            break;
        case DLL_PROCESS_DETACH:
            if (reserved) break;
            if (libnvidia_encode_handle)
                dlclose(libnvidia_encode_handle);
            break;
    }

    return TRUE;
}
