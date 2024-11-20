/*
 * Copyright (C) 2015 Michael Müller
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

#include <guiddef.h>
#include <stdint.h>

#ifndef __WINE_NVENCODEAPI_H
#define __WINE_NVENCODEAPI_H

#define NVENCAPI_MAJOR_VERSION 5
#define NVENCAPI_MINOR_VERSION 0
#define NVENCAPI_VERSION ((NVENCAPI_MAJOR_VERSION << 4) | (NVENCAPI_MINOR_VERSION))
#define NVENCAPI_STRUCT_VERSION(type, version) (uint32_t)(sizeof(type) | ((version)<<16) | (NVENCAPI_VERSION << 24))

/* the version scheme changed between 5.0 and 6.0 */
#define NVENCAPI_MAJOR_VERSION_6 6
#define NVENCAPI_MINOR_VERSION_0 0
#define NVENCAPI_VERSION_6_0 (NVENCAPI_MAJOR_VERSION_6 | (NVENCAPI_MINOR_VERSION_0 << 24))
#define NVENCAPI_STRUCT_VERSION_6_0(ver) ((uint32_t)NVENCAPI_VERSION_6_0 | ((ver)<<16) | (0x7 << 28))

#define NVENCSTATUS int
#define NV_ENC_SUCCESS 0
#define NV_ENC_ERR_INVALID_PTR 6
#define NV_ENC_ERR_UNSUPPORTED_PARAM 12
#define NV_ENC_ERR_INVALID_VERSION 15

typedef void *NV_ENC_INPUT_PTR;
typedef void *NV_ENC_OUTPUT_PTR;
typedef void *NV_ENC_REGISTERED_PTR;

typedef struct _NV_ENC_CAPS_PARAM NV_ENC_CAPS_PARAM;
typedef struct _NV_ENC_CREATE_INPUT_BUFFER NV_ENC_CREATE_INPUT_BUFFER;
typedef struct _NV_ENC_CREATE_BITSTREAM_BUFFER NV_ENC_CREATE_BITSTREAM_BUFFER;
typedef struct _NV_ENC_QP NV_ENC_QP;
typedef struct _NV_ENC_RC_PARAMS NV_ENC_RC_PARAMS;
typedef struct _NV_ENC_CONFIG_H264_VUI_PARAMETERS NV_ENC_CONFIG_H264_VUI_PARAMETERS;
typedef struct _NV_ENC_CONFIG_H264 NV_ENC_CONFIG_H264;
typedef struct _NV_ENC_CONFIG_HEVC NV_ENC_CONFIG_HEVC;
typedef struct _NV_ENC_CONFIG NV_ENC_CONFIG;
typedef struct _NV_ENC_RECONFIGURE_PARAMS NV_ENC_RECONFIGURE_PARAMS;
typedef struct _NV_ENC_PRESET_CONFIG NV_ENC_PRESET_CONFIG;
typedef struct _NV_ENC_H264_SEI_PAYLOAD NV_ENC_H264_SEI_PAYLOAD;
typedef struct _NV_ENC_LOCK_BITSTREAM NV_ENC_LOCK_BITSTREAM;
typedef struct _NV_ENC_LOCK_INPUT_BUFFER NV_ENC_LOCK_INPUT_BUFFER;
typedef struct _NV_ENC_MAP_INPUT_RESOURCE NV_ENC_MAP_INPUT_RESOURCE;
typedef struct _NV_ENC_REGISTER_RESOURCE NV_ENC_REGISTER_RESOURCE;
typedef struct _NV_ENC_STAT NV_ENC_STAT;
typedef struct _NV_ENC_SEQUENCE_PARAM_PAYLOAD NV_ENC_SEQUENCE_PARAM_PAYLOAD;
typedef struct _NV_ENC_EVENT_PARAMS NV_ENC_EVENT_PARAMS;
typedef struct _NV_ENC_OPEN_ENCODE_SESSIONEX_PARAMS NV_ENC_OPEN_ENCODE_SESSIONEX_PARAMS;
typedef struct _NV_ENC_BUFFER_FORMAT NV_ENC_BUFFER_FORMAT;
typedef struct _NV_ENC_OPEN_ENCODE_SESSION_EX_PARAMS NV_ENC_OPEN_ENCODE_SESSION_EX_PARAMS;
typedef struct _NV_ENC_CREATE_MV_BUFFER NV_ENC_CREATE_MV_BUFFER;
typedef struct _NV_ENC_MEONLY_PARAMS NV_ENC_MEONLY_PARAMS;

typedef struct _NVENC_EXTERNAL_ME_HINT_COUNTS_PER_BLOCKTYPE
{
    uint32_t numCandsPerBlk16x16 : 4;
    uint32_t numCandsPerBlk16x8  : 4;
    uint32_t numCandsPerBlk8x16  : 4;
    uint32_t numCandsPerBlk8x8   : 4;
    uint32_t reserved            : 16;
    uint32_t reserved1[3];
} NVENC_EXTERNAL_ME_HINT_COUNTS_PER_BLOCKTYPE;

typedef struct _NV_ENC_INITIALIZE_PARAMS
{
    uint32_t version;
    GUID encodeGUID;
    GUID presetGUID;
    uint32_t encodeWidth;
    uint32_t encodeHeight;
    uint32_t darWidth;
    uint32_t darHeight;
    uint32_t frameRateNum;
    uint32_t frameRateDen;
    uint32_t enableEncodeAsync;
    uint32_t enablePTD;
    uint32_t reportSliceOffsets    : 1;
    uint32_t enableSubFrameWrite   : 1;
    uint32_t enableExternalMEHints : 1;
    uint32_t reservedBitFields     : 29;
    uint32_t privDataSize;
    void *privData;
    void *encodeConfig;
    uint32_t maxEncodeWidth;
    uint32_t maxEncodeHeight;
    NVENC_EXTERNAL_ME_HINT_COUNTS_PER_BLOCKTYPE maxMEHintCountsPerBlock[2];
    uint32_t reserved[289];
    void *reserved2[64];
} NV_ENC_INITIALIZE_PARAMS;

typedef struct _NV_ENC_PIC_PARAMS_H264
{
    uint32_t displayPOCSyntax;
    uint32_t reserved3;
    uint32_t refPicFlag;
    uint32_t colourPlaneId;
    uint32_t forceIntraRefreshWithFrameCnt;
    uint32_t constrainedFrame    : 1;
    uint32_t sliceModeDataUpdate : 1;
    uint32_t ltrMarkFrame        : 1;
    uint32_t ltrUseFrames        : 1;
    uint32_t reservedBitFields   : 28;
    uint8_t *sliceTypeData;
    uint32_t sliceTypeArrayCnt;
    uint32_t seiPayloadArrayCnt;
    NV_ENC_H264_SEI_PAYLOAD *seiPayloadArray;
    uint32_t sliceMode;
    uint32_t sliceModeData;
    uint32_t ltrMarkFrameIdx;
    uint32_t ltrUseFrameBitmap;
    uint32_t ltrUsageMode;
    uint32_t reserved[243];
    void *reserved2[62];
} NV_ENC_PIC_PARAMS_H264;

typedef struct _NV_ENC_PIC_PARAMS_HEVC
{
    uint32_t displayPOCSyntax;
    uint32_t refPicFlag;
    uint32_t temporalId;
    uint32_t forceIntraRefreshWithFrameCnt;
    uint32_t constrainedFrame    : 1;
    uint32_t sliceModeDataUpdate : 1;
    uint32_t ltrMarkFrame        : 1;
    uint32_t ltrUseFrames        : 1;
    uint32_t reservedBitFields   : 28;
    uint8_t *sliceTypeData;
    uint32_t sliceTypeArrayCnt;
    uint32_t sliceMode;
    uint32_t sliceModeData;
    uint32_t ltrMarkFrameIdx;
    uint32_t ltrUseFrameBitmap;
    uint32_t ltrUsageMode;
    uint32_t reserved[246];
    void *reserved2[62];
} NV_ENC_PIC_PARAMS_HEVC;

typedef union _NV_ENC_CODEC_PIC_PARAMS
{
    NV_ENC_PIC_PARAMS_H264 h264PicParams;
    NV_ENC_PIC_PARAMS_HEVC hevcPicParams;
    uint32_t reserved[256];
} NV_ENC_CODEC_PIC_PARAMS;

struct _NVENC_EXTERNAL_ME_HINT
{
    int32_t mvx        : 12;
    int32_t mvy        : 10;
    int32_t refidx     : 5;
    int32_t dir        : 1;
    int32_t partType   : 2;
    int32_t lastofPart : 1;
    int32_t lastOfMB   : 1;
};

typedef struct _NV_ENC_PIC_PARAMS
{
    uint32_t version;
    uint32_t inputWidth;
    uint32_t inputHeight;
    uint32_t inputPitch;
    uint32_t encodePicFlags;
    uint32_t frameIdx;
    uint64_t inputTimeStamp;
    uint64_t inputDuration;
    void *inputBuffer;
    void *outputBitstream;
    void *completionEvent;
    int bufferFmt;
    int pictureStruct;
    int pictureType;
    NV_ENC_CODEC_PIC_PARAMS codecPicParams;
    struct _NVENC_EXTERNAL_ME_HINT_COUNTS_PER_BLOCKTYPE meHintCountsPerBlock[2];
    struct _NVENC_EXTERNAL_ME_HINT *meExternalHints;
    uint32_t reserved1[6];
    void *reserved2[2];
    int8_t *qpDeltaMap;
    uint32_t qpDeltaMapSize;
    uint32_t reservedBitFields;
    uint32_t reserved3[287];
    void *reserved4[60];
} NV_ENC_PIC_PARAMS;

typedef struct __NV_ENCODE_API_FUNCTION_LIST
{
    uint32_t version;
    uint32_t reserved;
    NVENCSTATUS (WINAPI *nvEncOpenEncodeSession)(void *device, uint32_t deviceType, void **encoder);
    NVENCSTATUS (WINAPI *nvEncGetEncodeGUIDCount)(void *encoder, uint32_t *encodeGUIDCount);
    NVENCSTATUS (WINAPI *nvEncGetEncodeProfileGUIDCount)(void *encoder, GUID encodeGUID, uint32_t *encodePresetGUIDCount);
    NVENCSTATUS (WINAPI *nvEncGetEncodeProfileGUIDs)(void *encoder, GUID encodeGUID, GUID *presetGUIDs, uint32_t guidArraySize,
                                                     uint32_t *encodePresetGUIDCount);
    NVENCSTATUS (WINAPI *nvEncGetEncodeGUIDs)(void *encoder, GUID *GUIDs, uint32_t guidArraySize, uint32_t *GUIDCount);
    NVENCSTATUS (WINAPI *nvEncGetInputFormatCount)(void *encoder, GUID encodeGUID, uint32_t *inputFmtCount);
    NVENCSTATUS (WINAPI *nvEncGetInputFormats)(void *encoder, GUID encodeGUID, NV_ENC_BUFFER_FORMAT *inputFmts,
                                               uint32_t inputFmtArraySize, uint32_t *inputFmtCount);
    NVENCSTATUS (WINAPI *nvEncGetEncodeCaps)(void *encoder, GUID encodeGUID, NV_ENC_CAPS_PARAM *capsParam, int *capsVal);
    NVENCSTATUS (WINAPI *nvEncGetEncodePresetCount)(void *encoder, GUID encodeGUID, uint32_t *encodePresetGUIDCount);
    NVENCSTATUS (WINAPI *nvEncGetEncodePresetGUIDs)(void *encoder, GUID encodeGUID, GUID *presetGUIDs, uint32_t guidArraySize,
                                                    uint32_t *encodePresetGUIDCount);
    NVENCSTATUS (WINAPI *nvEncGetEncodePresetConfig)(void *encoder, GUID encodeGUID, GUID presetGUID, NV_ENC_PRESET_CONFIG *presetConfig);
    NVENCSTATUS (WINAPI *nvEncInitializeEncoder)(void *encoder, NV_ENC_INITIALIZE_PARAMS *createEncodeParams);
    NVENCSTATUS (WINAPI *nvEncCreateInputBuffer)(void *encoder, NV_ENC_CREATE_INPUT_BUFFER *createInputBufferParams);
    NVENCSTATUS (WINAPI *nvEncDestroyInputBuffer)(void *encoder, NV_ENC_INPUT_PTR inputBuffer);
    NVENCSTATUS (WINAPI *nvEncCreateBitstreamBuffer)(void *encoder, NV_ENC_CREATE_BITSTREAM_BUFFER *createBitstreamBufferParams);
    NVENCSTATUS (WINAPI *nvEncDestroyBitstreamBuffer)(void *encoder, NV_ENC_OUTPUT_PTR bitstreamBuffer);
    NVENCSTATUS (WINAPI *nvEncEncodePicture)(void *encoder, NV_ENC_PIC_PARAMS *encodePicParams);
    NVENCSTATUS (WINAPI *nvEncLockBitstream)(void *encoder, NV_ENC_LOCK_BITSTREAM *lockBitstreamBufferParams);
    NVENCSTATUS (WINAPI *nvEncUnlockBitstream)(void *encoder, NV_ENC_OUTPUT_PTR bitstreamBuffer);
    NVENCSTATUS (WINAPI *nvEncLockInputBuffer)(void *encoder, NV_ENC_LOCK_INPUT_BUFFER *lockInputBufferParams);
    NVENCSTATUS (WINAPI *nvEncUnlockInputBuffer)(void *encoder, NV_ENC_INPUT_PTR inputBuffer);
    NVENCSTATUS (WINAPI *nvEncGetEncodeStats)(void *encoder, NV_ENC_STAT *encodeStats);
    NVENCSTATUS (WINAPI *nvEncGetSequenceParams)(void *encoder, NV_ENC_SEQUENCE_PARAM_PAYLOAD *hsequenceParamPayload);
    NVENCSTATUS (WINAPI *nvEncRegisterAsyncEvent)(void *encoder, NV_ENC_EVENT_PARAMS *eventParams);
    NVENCSTATUS (WINAPI *nvEncUnregisterAsyncEvent)(void *encoder, NV_ENC_EVENT_PARAMS *eventParams);
    NVENCSTATUS (WINAPI *nvEncMapInputResource)(void *encoder, NV_ENC_MAP_INPUT_RESOURCE *mapInputResParams);
    NVENCSTATUS (WINAPI *nvEncUnmapInputResource)(void *encoder, NV_ENC_INPUT_PTR mappedInputBuffer);
    NVENCSTATUS (WINAPI *nvEncDestroyEncoder)(void *encoder);
    NVENCSTATUS (WINAPI *nvEncInvalidateRefFrames)(void *encoder, uint64_t invalidRefFrameTimeStamp);
    NVENCSTATUS (WINAPI *nvEncOpenEncodeSessionEx)(NV_ENC_OPEN_ENCODE_SESSION_EX_PARAMS *openSessionExParams, void **encoder);
    NVENCSTATUS (WINAPI *nvEncRegisterResource)(void *encoder, NV_ENC_REGISTER_RESOURCE *registerResParams);
    NVENCSTATUS (WINAPI *nvEncUnregisterResource)(void *encoder, NV_ENC_REGISTERED_PTR registeredRes);
    NVENCSTATUS (WINAPI *nvEncReconfigureEncoder)(void *encoder, NV_ENC_RECONFIGURE_PARAMS *reInitEncodeParams);
    void *reserved1;
    NVENCSTATUS (WINAPI *nvEncCreateMVBuffer)(void *encoder, NV_ENC_CREATE_MV_BUFFER *createMVBufferParams);
    NVENCSTATUS (WINAPI *nvEncDestroyMVBuffer)(void *encoder, NV_ENC_OUTPUT_PTR MVBuffer);
    NVENCSTATUS (WINAPI *nvEncRunMotionEstimationOnly)(void *encoder, NV_ENC_MEONLY_PARAMS *MEOnlyParams);
    void *reserved2[281];
} NV_ENCODE_API_FUNCTION_LIST;

#define NV_ENCODE_API_FUNCTION_LIST_VER NVENCAPI_STRUCT_VERSION(NV_ENCODE_API_FUNCTION_LIST, 2)
#define NV_ENCODE_API_FUNCTION_LIST_VER_6_0 NVENCAPI_STRUCT_VERSION_6_0(2)

typedef struct __LINUX_NV_ENCODE_API_FUNCTION_LIST
{
    uint32_t version;
    uint32_t reserved;
    NVENCSTATUS (*nvEncOpenEncodeSession)(void *device, uint32_t deviceType, void **encoder);
    NVENCSTATUS (*nvEncGetEncodeGUIDCount)(void *encoder, uint32_t *encodeGUIDCount);
    NVENCSTATUS (*nvEncGetEncodeProfileGUIDCount)(void *encoder, GUID encodeGUID, uint32_t *encodePresetGUIDCount);
    NVENCSTATUS (*nvEncGetEncodeProfileGUIDs)(void *encoder, GUID encodeGUID, GUID *presetGUIDs, uint32_t guidArraySize,
                                              uint32_t *encodePresetGUIDCount);
    NVENCSTATUS (*nvEncGetEncodeGUIDs)(void *encoder, GUID *GUIDs, uint32_t guidArraySize, uint32_t *GUIDCount);
    NVENCSTATUS (*nvEncGetInputFormatCount)(void *encoder, GUID encodeGUID, uint32_t *inputFmtCount);
    NVENCSTATUS (*nvEncGetInputFormats)(void *encoder, GUID encodeGUID, NV_ENC_BUFFER_FORMAT *inputFmts,
                                        uint32_t inputFmtArraySize, uint32_t *inputFmtCount);
    NVENCSTATUS (*nvEncGetEncodeCaps)(void *encoder, GUID encodeGUID, NV_ENC_CAPS_PARAM *capsParam, int *capsVal);
    NVENCSTATUS (*nvEncGetEncodePresetCount)(void *encoder, GUID encodeGUID, uint32_t *encodePresetGUIDCount);
    NVENCSTATUS (*nvEncGetEncodePresetGUIDs)(void *encoder, GUID encodeGUID, GUID *presetGUIDs, uint32_t guidArraySize,
                                             uint32_t *encodePresetGUIDCount);
    NVENCSTATUS (*nvEncGetEncodePresetConfig)(void *encoder, GUID encodeGUID, GUID presetGUID, NV_ENC_PRESET_CONFIG *presetConfig);
    NVENCSTATUS (*nvEncInitializeEncoder)(void *encoder, NV_ENC_INITIALIZE_PARAMS *createEncodeParams);
    NVENCSTATUS (*nvEncCreateInputBuffer)(void *encoder, NV_ENC_CREATE_INPUT_BUFFER *createInputBufferParams);
    NVENCSTATUS (*nvEncDestroyInputBuffer)(void *encoder, NV_ENC_INPUT_PTR inputBuffer);
    NVENCSTATUS (*nvEncCreateBitstreamBuffer)(void *encoder, NV_ENC_CREATE_BITSTREAM_BUFFER *createBitstreamBufferParams);
    NVENCSTATUS (*nvEncDestroyBitstreamBuffer)(void *encoder, NV_ENC_OUTPUT_PTR bitstreamBuffer);
    NVENCSTATUS (*nvEncEncodePicture)(void *encoder, NV_ENC_PIC_PARAMS *encodePicParams);
    NVENCSTATUS (*nvEncLockBitstream)(void *encoder, NV_ENC_LOCK_BITSTREAM *lockBitstreamBufferParams);
    NVENCSTATUS (*nvEncUnlockBitstream)(void *encoder, NV_ENC_OUTPUT_PTR bitstreamBuffer);
    NVENCSTATUS (*nvEncLockInputBuffer)(void *encoder, NV_ENC_LOCK_INPUT_BUFFER *lockInputBufferParams);
    NVENCSTATUS (*nvEncUnlockInputBuffer)(void *encoder, NV_ENC_INPUT_PTR inputBuffer);
    NVENCSTATUS (*nvEncGetEncodeStats)(void *encoder, NV_ENC_STAT *encodeStats);
    NVENCSTATUS (*nvEncGetSequenceParams)(void *encoder, NV_ENC_SEQUENCE_PARAM_PAYLOAD *hsequenceParamPayload);
    NVENCSTATUS (*nvEncRegisterAsyncEvent)(void *encoder, NV_ENC_EVENT_PARAMS *eventParams);
    NVENCSTATUS (*nvEncUnregisterAsyncEvent)(void *encoder, NV_ENC_EVENT_PARAMS *eventParams);
    NVENCSTATUS (*nvEncMapInputResource)(void *encoder, NV_ENC_MAP_INPUT_RESOURCE *mapInputResParams);
    NVENCSTATUS (*nvEncUnmapInputResource)(void *encoder, NV_ENC_INPUT_PTR mappedInputBuffer);
    NVENCSTATUS (*nvEncDestroyEncoder)(void *encoder);
    NVENCSTATUS (*nvEncInvalidateRefFrames)(void *encoder, uint64_t invalidRefFrameTimeStamp);
    NVENCSTATUS (*nvEncOpenEncodeSessionEx)(NV_ENC_OPEN_ENCODE_SESSION_EX_PARAMS *openSessionExParams, void **encoder);
    NVENCSTATUS (*nvEncRegisterResource)(void *encoder, NV_ENC_REGISTER_RESOURCE *registerResParams);
    NVENCSTATUS (*nvEncUnregisterResource)(void *encoder, NV_ENC_REGISTERED_PTR registeredRes);
    NVENCSTATUS (*nvEncReconfigureEncoder)(void *encoder, NV_ENC_RECONFIGURE_PARAMS *reInitEncodeParams);
    void *reserved1;
    NVENCSTATUS (*nvEncCreateMVBuffer)(void *encoder, NV_ENC_CREATE_MV_BUFFER *createMVBufferParams);
    NVENCSTATUS (*nvEncDestroyMVBuffer)(void *encoder, NV_ENC_OUTPUT_PTR MVBuffer);
    NVENCSTATUS (*nvEncRunMotionEstimationOnly)(void *encoder, NV_ENC_MEONLY_PARAMS *MEOnlyParams);
    void *reserved2[281];
} LINUX_NV_ENCODE_API_FUNCTION_LIST;

#endif /* __WINE_NVENCODEAPI_H */
