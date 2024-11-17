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

#include <guiddef.h>
#include <stdint.h>

#ifndef __WINE_NVENCODEAPI_H
#define __WINE_NVENCODEAPI_H

#define NVENCAPI_MAJOR_VERSION 12
#define NVENCAPI_MINOR_VERSION 1

#define NVENCAPI_VERSION (NVENCAPI_MAJOR_VERSION | (NVENCAPI_MINOR_VERSION << 24))
#define NVENCAPI_STRUCT_VERSION(ver) ((uint32_t)NVENCAPI_VERSION | ((ver)<<16) | (0x7 << 28))

#define NVENCSTATUS int
#define NV_ENC_SUCCESS 0
#define NV_ENC_ERR_INVALID_PTR 6
#define NV_ENC_ERR_UNSUPPORTED_PARAM 12
#define NV_ENC_ERR_INVALID_VERSION 15
#define MAX_NUM_CLOCK_TS 3

typedef void *NV_ENC_INPUT_PTR;
typedef void *NV_ENC_OUTPUT_PTR;
typedef void *NV_ENC_REGISTERED_PTR;
typedef void *NV_ENC_CUSTREAM_PTR;

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
typedef struct _NV_ENC_SEI_PAYLOAD NV_ENC_SEI_PAYLOAD;
typedef struct _NV_ENC_LOCK_BITSTREAM NV_ENC_LOCK_BITSTREAM;
typedef struct _NV_ENC_LOCK_INPUT_BUFFER NV_ENC_LOCK_INPUT_BUFFER;
typedef struct _NV_ENC_MAP_INPUT_RESOURCE NV_ENC_MAP_INPUT_RESOURCE;
typedef struct _NV_ENC_REGISTER_RESOURCE NV_ENC_REGISTER_RESOURCE;
typedef struct _NV_ENC_STAT NV_ENC_STAT;
typedef struct _NV_ENC_SEQUENCE_PARAM_PAYLOAD NV_ENC_SEQUENCE_PARAM_PAYLOAD;
typedef struct _NV_ENC_EVENT_PARAMS NV_ENC_EVENT_PARAMS;
typedef struct _NV_ENC_OPEN_ENCODE_SESSIONEX_PARAMS NV_ENC_OPEN_ENCODE_SESSIONEX_PARAMS;
typedef struct _NV_ENC_OPEN_ENCODE_SESSION_EX_PARAMS NV_ENC_OPEN_ENCODE_SESSION_EX_PARAMS;
typedef struct _NV_ENC_CREATE_MV_BUFFER NV_ENC_CREATE_MV_BUFFER;
typedef struct _NV_ENC_MEONLY_PARAMS NV_ENC_MEONLY_PARAMS;
typedef struct _NV_ENC_TIME_CODE NV_ENC_TIME_CODE;
typedef struct _NVENC_EXTERNAL_ME_SB_HINT NVENC_EXTERNAL_ME_SB_HINT;
typedef struct _NV_ENC_RESTORE_ENCODER_STATE_PARAMS NV_ENC_RESTORE_ENCODER_STATE_PARAMS;
typedef struct _NV_ENC_LOOKAHEAD_PIC_PARAMS NV_ENC_LOOKAHEAD_PIC_PARAMS;

typedef enum _NV_ENC_BUFFER_FORMAT
{
    NV_ENC_BUFFER_FORMAT_UNDEFINED                       = 0x00000000,
    NV_ENC_BUFFER_FORMAT_NV12                            = 0x00000001,
    NV_ENC_BUFFER_FORMAT_YV12                            = 0x00000010,
    NV_ENC_BUFFER_FORMAT_IYUV                            = 0x00000100,
    NV_ENC_BUFFER_FORMAT_YUV444                          = 0x00001000,
    NV_ENC_BUFFER_FORMAT_YUV420_10BIT                    = 0x00010000,
    NV_ENC_BUFFER_FORMAT_YUV444_10BIT                    = 0x00100000,
    NV_ENC_BUFFER_FORMAT_ARGB                            = 0x01000000,
    NV_ENC_BUFFER_FORMAT_ARGB10                          = 0x02000000,
    NV_ENC_BUFFER_FORMAT_AYUV                            = 0x04000000,
    NV_ENC_BUFFER_FORMAT_ABGR                            = 0x10000000,
    NV_ENC_BUFFER_FORMAT_ABGR10                          = 0x20000000,
    NV_ENC_BUFFER_FORMAT_U8                              = 0x40000000,
} NV_ENC_BUFFER_FORMAT;
#define NV_ENC_BUFFER_FORMAT_NV12_PL NV_ENC_BUFFER_FORMAT_NV12
#define NV_ENC_BUFFER_FORMAT_YV12_PL NV_ENC_BUFFER_FORMAT_YV12
#define NV_ENC_BUFFER_FORMAT_IYUV_PL NV_ENC_BUFFER_FORMAT_IYUV
#define NV_ENC_BUFFER_FORMAT_YUV444_PL NV_ENC_BUFFER_FORMAT_YUV444

typedef enum _NV_ENC_OUTPUT_STATS_LEVEL
{
    NV_ENC_OUTPUT_STATS_NONE          = 0,
    NV_ENC_OUTPUT_STATS_BLOCK_LEVEL   = 1,
    NV_ENC_OUTPUT_STATS_ROW_LEVEL     = 2,
} NV_ENC_OUTPUT_STATS_LEVEL;

typedef enum _NV_ENC_DISPLAY_PIC_STRUCT
{
    NV_ENC_PIC_STRUCT_DISPLAY_FRAME             = 0x00,
    NV_ENC_PIC_STRUCT_DISPLAY_FIELD_TOP_BOTTOM  = 0x01,
    NV_ENC_PIC_STRUCT_DISPLAY_FIELD_BOTTOM_TOP  = 0x02,
    NV_ENC_PIC_STRUCT_DISPLAY_FRAME_DOUBLING    = 0x03,
    NV_ENC_PIC_STRUCT_DISPLAY_FRAME_TRIPLING    = 0x04
} NV_ENC_DISPLAY_PIC_STRUCT;

typedef struct _NV_ENC_CLOCK_TIMESTAMP_SET
{
    uint32_t countingType            : 1;
    uint32_t discontinuityFlag       : 1;
    uint32_t cntDroppedFrames        : 1;
    uint32_t nFrames                 : 8;
    uint32_t secondsValue            : 6;
    uint32_t minutesValue            : 6;
    uint32_t hoursValue              : 5;
    uint32_t reserved2               : 4;
    uint32_t timeOffset;
} NV_ENC_CLOCK_TIMESTAMP_SET;

typedef struct _NV_ENC_TIME_CODE
{
    NV_ENC_DISPLAY_PIC_STRUCT displayPicStruct;
    NV_ENC_CLOCK_TIMESTAMP_SET clockTimestamp[MAX_NUM_CLOCK_TS];
} NV_ENC_TIME_CODE;

typedef struct _NV_ENC_CAPS_PARAM
{
    uint32_t version;
    uint32_t capsToQuery;
    uint32_t reserved[62];
} NV_ENC_CAPS_PARAM;
#define NV_ENC_CAPS_PARAM_VER NVENCAPI_STRUCT_VERSION(1)

typedef struct _NVENC_EXTERNAL_ME_HINT_COUNTS_PER_BLOCKTYPE
{
    uint32_t numCandsPerBlk16x16 : 4;
    uint32_t numCandsPerBlk16x8  : 4;
    uint32_t numCandsPerBlk8x16  : 4;
    uint32_t numCandsPerBlk8x8   : 4;
    uint32_t reserved            : 16;
    uint32_t reserved1[3];
} NVENC_EXTERNAL_ME_HINT_COUNTS_PER_BLOCKTYPE;

typedef enum NV_ENC_TUNING_INFO
{
    NV_ENC_TUNING_INFO_UNDEFINED         = 0,
    NV_ENC_TUNING_INFO_HIGH_QUALITY      = 1,
    NV_ENC_TUNING_INFO_LOW_LATENCY       = 2,
    NV_ENC_TUNING_INFO_ULTRA_LOW_LATENCY = 3,
    NV_ENC_TUNING_INFO_LOSSLESS          = 4,
    NV_ENC_TUNING_INFO_COUNT
}NV_ENC_TUNING_INFO;

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
    uint32_t reportSliceOffsets       : 1;
    uint32_t enableSubFrameWrite      : 1;
    uint32_t enableExternalMEHints    : 1;
    uint32_t enableMEOnlyMode         : 1;
    uint32_t enableWeightedPrediction : 1;
    uint32_t splitEncodeMode          : 4;
    uint32_t enableOutputInVidmem     : 1;
    uint32_t enableReconFrameOutput   : 1;
    uint32_t enableOutputStats        : 1;
    uint32_t reservedBitFields        : 20;
    uint32_t privDataSize;
    void *privData;
    void *encodeConfig;
    uint32_t maxEncodeWidth;
    uint32_t maxEncodeHeight;
    NVENC_EXTERNAL_ME_HINT_COUNTS_PER_BLOCKTYPE maxMEHintCountsPerBlock[2];
    NV_ENC_TUNING_INFO tuningInfo;
    NV_ENC_BUFFER_FORMAT bufferFormat;
    uint32_t numStateBuffers;
    NV_ENC_OUTPUT_STATS_LEVEL outputStatsLevel;
    uint32_t reserved[285];
    void *reserved2[64];
} NV_ENC_INITIALIZE_PARAMS;
#define NV_ENC_INITIALIZE_PARAMS_VER (NVENCAPI_STRUCT_VERSION(6) | ( 1<<31 ))

typedef struct _NV_ENC_PIC_PARAMS_MVC
{
    uint32_t version;
    uint32_t viewID;
    uint32_t temporalID;
    uint32_t priorityID;
    uint32_t reserved1[12];
    void*    reserved2[8];
}NV_ENC_PIC_PARAMS_MVC;
#define NV_ENC_PIC_PARAMS_MVC_VER NVENCAPI_STRUCT_VERSION(1)

typedef union _NV_ENC_PIC_PARAMS_H264_EXT
{
    NV_ENC_PIC_PARAMS_MVC mvcPicParams;
    uint32_t reserved1[32];
}NV_ENC_PIC_PARAMS_H264_EXT;

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
    uint32_t forceIntraSliceCount;
    uint32_t *forceIntraSliceIdx;
    NV_ENC_PIC_PARAMS_H264_EXT h264ExtPicParams;
    NV_ENC_TIME_CODE timeCode;
    uint32_t reserved[203];
    void *reserved2[61];
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
    uint32_t reserved;
    NV_ENC_SEI_PAYLOAD *seiPayloadArray;
    NV_ENC_TIME_CODE timeCode;
    uint32_t reserved2[237];
    void *reserved3[61];
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
    uint16_t meHintRefPicDist[2];
    NV_ENC_INPUT_PTR alphaBuffer;
    NVENC_EXTERNAL_ME_SB_HINT *meExternalSbHints;
    uint32_t meSbHintsCount;
    uint32_t stateBufferIdx;
    NV_ENC_OUTPUT_PTR outputReconBuffer;
    uint32_t reserved3[284];
    void *reserved4[57];
} NV_ENC_PIC_PARAMS;
#define NV_ENC_PIC_PARAMS_VER (NVENCAPI_STRUCT_VERSION(6) | ( 1<<31 ))

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
    const char *(WINAPI *nvEncGetLastErrorString)(void* encoder);
    NVENCSTATUS (WINAPI *nvEncSetIOCudaStreams)(void* encoder, NV_ENC_CUSTREAM_PTR inputStream, NV_ENC_CUSTREAM_PTR outputStream);
    NVENCSTATUS (WINAPI *nvEncGetEncodePresetConfigEx)(void* encoder, GUID encodeGUID, GUID  presetGUID, NV_ENC_TUNING_INFO tuningInfo, NV_ENC_PRESET_CONFIG* presetConfig);
    NVENCSTATUS (WINAPI *nvEncGetSequenceParamEx)(void* encoder, NV_ENC_INITIALIZE_PARAMS* encInitParams, NV_ENC_SEQUENCE_PARAM_PAYLOAD* sequenceParamPayload);
    NVENCSTATUS (WINAPI *nvEncRestoreEncoderState)(void* encoder, NV_ENC_RESTORE_ENCODER_STATE_PARAMS* restoreState);
    NVENCSTATUS (WINAPI *nvEncLookaheadPicture)(void* encoder, NV_ENC_LOOKAHEAD_PIC_PARAMS *lookaheadParams);
    void *reserved2[275];
} NV_ENCODE_API_FUNCTION_LIST;
#define NV_ENCODE_API_FUNCTION_LIST_VER NVENCAPI_STRUCT_VERSION(2)

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
    const char *(*nvEncGetLastErrorString)(void* encoder);
    NVENCSTATUS (*nvEncSetIOCudaStreams)(void* encoder, NV_ENC_CUSTREAM_PTR inputStream, NV_ENC_CUSTREAM_PTR outputStream);
    NVENCSTATUS (*nvEncGetEncodePresetConfigEx)(void* encoder, GUID encodeGUID, GUID  presetGUID, NV_ENC_TUNING_INFO tuningInfo, NV_ENC_PRESET_CONFIG* presetConfig);
    NVENCSTATUS (*nvEncGetSequenceParamEx)(void* encoder, NV_ENC_INITIALIZE_PARAMS* encInitParams, NV_ENC_SEQUENCE_PARAM_PAYLOAD* sequenceParamPayload);
    NVENCSTATUS (*nvEncRestoreEncoderState)(void* encoder, NV_ENC_RESTORE_ENCODER_STATE_PARAMS* restoreState);
    NVENCSTATUS (*nvEncLookaheadPicture)(void* encoder, NV_ENC_LOOKAHEAD_PIC_PARAMS *lookaheadParams);
    void *reserved2[275];
} LINUX_NV_ENCODE_API_FUNCTION_LIST;

#endif /* __WINE_NVENCODEAPI_H */
