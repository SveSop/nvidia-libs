/*
 * Copyright (C) 2021 Krzysztof Bogacki
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
 *
 */

#include "config.h"
#include <dlfcn.h>

#include <stdarg.h>

#include "windef.h"
#include "winbase.h"
#include "wine/debug.h"

WINE_DEFAULT_DEBUG_CHANNEL(nvml);

#pragma push_macro("__declspec")
#undef __declspec
#define __declspec(x) __cdecl

#define _WINDOWS
#define NVML_LIB_EXPORT
#define NVML_NO_UNVERSIONED_FUNC_DEFS
#include "nvml.h"

#pragma pop_macro("__declspec")

static void *libnvidia_ml_handle = NULL;

static const char* (*pnvmlErrorString)(nvmlReturn_t result) = NULL;
static nvmlReturn_t (*pnvmlInit)(void) = NULL;
static nvmlReturn_t (*pnvmlInitWithFlags)(unsigned int flags) = NULL;
static nvmlReturn_t (*pnvmlInit_v2)(void) = NULL;
static nvmlReturn_t (*pnvmlShutdown)(void) = NULL;
static nvmlReturn_t (*pnvmlSystemGetCudaDriverVersion)(int *cudaDriverVersion) = NULL;
static nvmlReturn_t (*pnvmlSystemGetCudaDriverVersion_v2)(int *cudaDriverVersion) = NULL;
static nvmlReturn_t (*pnvmlSystemGetDriverVersion)(char *version, unsigned int length) = NULL;
static nvmlReturn_t (*pnvmlSystemGetNVMLVersion)(char *version, unsigned int length) = NULL;

static nvmlReturn_t (*pnvmlDeviceGetAPIRestriction)(nvmlDevice_t device, nvmlRestrictedAPI_t apiType, nvmlEnableState_t *isRestricted) = NULL;
static nvmlReturn_t (*pnvmlDeviceGetActiveVgpus)(nvmlDevice_t device, unsigned int *vgpuCount, nvmlVgpuInstance_t *vgpuInstances) = NULL;
static nvmlReturn_t (*pnvmlDeviceGetApplicationsClock)(nvmlDevice_t device, nvmlClockType_t clockType, unsigned int *clockMHz) = NULL;
static nvmlReturn_t (*pnvmlDeviceGetArchitecture)(nvmlDevice_t device, nvmlDeviceArchitecture_t *arch) = NULL;
static nvmlReturn_t (*pnvmlDeviceGetAutoBoostedClocksEnabled)(nvmlDevice_t device, nvmlEnableState_t *isEnabled, nvmlEnableState_t *defaultIsEnabled) = NULL;
static nvmlReturn_t (*pnvmlDeviceGetBAR1MemoryInfo)(nvmlDevice_t device, nvmlBAR1Memory_t *bar1Memory) = NULL;
static nvmlReturn_t (*pnvmlDeviceGetBoardId)(nvmlDevice_t device, unsigned int *boardId) = NULL;
static nvmlReturn_t (*pnvmlDeviceGetBoardPartNumber)(nvmlDevice_t device, char *partNumber, unsigned int length) = NULL;
static nvmlReturn_t (*pnvmlDeviceGetBrand)(nvmlDevice_t device, nvmlBrandType_t *type) = NULL;
static nvmlReturn_t (*pnvmlDeviceGetBridgeChipInfo)(nvmlDevice_t device, nvmlBridgeChipHierarchy_t *bridgeHierarchy) = NULL;
static nvmlReturn_t (*pnvmlDeviceGetClock)(nvmlDevice_t device, nvmlClockType_t clockType, nvmlClockId_t clockId, unsigned int *clockMHz) = NULL;
static nvmlReturn_t (*pnvmlDeviceGetClockInfo)(nvmlDevice_t device, nvmlClockType_t type, unsigned int *clock) = NULL;
static nvmlReturn_t (*pnvmlDeviceGetComputeMode)(nvmlDevice_t device, nvmlComputeMode_t *mode) = NULL;
static nvmlReturn_t (*pnvmlDeviceGetCount)(unsigned int *deviceCount) = NULL;
static nvmlReturn_t (*pnvmlDeviceGetCount_v2)(unsigned int *deviceCount) = NULL;
static nvmlReturn_t (*pnvmlDeviceGetCreatableVgpus)(nvmlDevice_t device, unsigned int *vgpuCount, nvmlVgpuTypeId_t *vgpuTypeIds) = NULL;
static nvmlReturn_t (*pnvmlDeviceGetCudaComputeCapability)(nvmlDevice_t device, int *major, int *minor) = NULL;
static nvmlReturn_t (*pnvmlDeviceGetCurrPcieLinkGeneration)(nvmlDevice_t device, unsigned int *currLinkGen) = NULL;
static nvmlReturn_t (*pnvmlDeviceGetCurrPcieLinkWidth)(nvmlDevice_t device, unsigned int *currLinkWidth) = NULL;
static nvmlReturn_t (*pnvmlDeviceGetCurrentClocksThrottleReasons)(nvmlDevice_t device, unsigned long long *clocksThrottleReasons) = NULL;
static nvmlReturn_t (*pnvmlDeviceGetDecoderUtilization)(nvmlDevice_t device, unsigned int *utilization, unsigned int *samplingPeriodUs) = NULL;
static nvmlReturn_t (*pnvmlDeviceGetDefaultApplicationsClock)(nvmlDevice_t device, nvmlClockType_t clockType, unsigned int *clockMHz) = NULL;
static nvmlReturn_t (*pnvmlDeviceGetDetailedEccErrors)(nvmlDevice_t device, nvmlMemoryErrorType_t errorType, nvmlEccCounterType_t counterType, nvmlEccErrorCounts_t *eccCounts) = NULL;
static nvmlReturn_t (*pnvmlDeviceGetDisplayActive)(nvmlDevice_t device, nvmlEnableState_t *isActive) = NULL;
static nvmlReturn_t (*pnvmlDeviceGetDisplayMode)(nvmlDevice_t device, nvmlEnableState_t *display) = NULL;
static nvmlReturn_t (*pnvmlDeviceGetEccMode)(nvmlDevice_t device, nvmlEnableState_t *current, nvmlEnableState_t *pending) = NULL;
static nvmlReturn_t (*pnvmlDeviceGetEncoderCapacity)(nvmlDevice_t device, nvmlEncoderType_t encoderQueryType, unsigned int *encoderCapacity) = NULL;
static nvmlReturn_t (*pnvmlDeviceGetEncoderStats)(nvmlDevice_t device, unsigned int *sessionCount, unsigned int *averageFps, unsigned int *averageLatency) = NULL;
static nvmlReturn_t (*pnvmlDeviceGetEncoderUtilization)(nvmlDevice_t device, unsigned int *utilization, unsigned int *samplingPeriodUs) = NULL;
static nvmlReturn_t (*pnvmlDeviceGetEnforcedPowerLimit)(nvmlDevice_t device, unsigned int *limit) = NULL;
static nvmlReturn_t (*pnvmlDeviceGetFBCStats)(nvmlDevice_t device, nvmlFBCStats_t *fbcStats) = NULL;
static nvmlReturn_t (*pnvmlDeviceGetFanSpeed)(nvmlDevice_t device, unsigned int *speed) = NULL;
static nvmlReturn_t (*pnvmlDeviceGetFanSpeed_v2)(nvmlDevice_t device, unsigned int fan, unsigned int *speed) = NULL;
static nvmlReturn_t (*pnvmlDeviceGetFieldValues)(nvmlDevice_t device, int valuesCount, nvmlFieldValue_t *values) = NULL;
static nvmlReturn_t (*pnvmlDeviceGetGpuOperationMode)(nvmlDevice_t device, nvmlGpuOperationMode_t *current, nvmlGpuOperationMode_t *pending) = NULL;
static nvmlReturn_t (*pnvmlDeviceGetGridLicensableFeatures)(nvmlDevice_t device, nvmlGridLicensableFeatures_t *pGridLicensableFeatures) = NULL;
static nvmlReturn_t (*pnvmlDeviceGetGridLicensableFeatures_v2)(nvmlDevice_t device, nvmlGridLicensableFeatures_t *pGridLicensableFeatures) = NULL;
static nvmlReturn_t (*pnvmlDeviceGetGridLicensableFeatures_v3)(nvmlDevice_t device, nvmlGridLicensableFeatures_t *pGridLicensableFeatures) = NULL;
static nvmlReturn_t (*pnvmlDeviceGetHandleByIndex)(unsigned int index, nvmlDevice_t *device) = NULL;
static nvmlReturn_t (*pnvmlDeviceGetHandleByIndex_v2)(unsigned int index, nvmlDevice_t *device) = NULL;
static nvmlReturn_t (*pnvmlDeviceGetHandleByPciBusId)(const char *pciBusId, nvmlDevice_t *device) = NULL;
static nvmlReturn_t (*pnvmlDeviceGetHandleByPciBusId_v2)(const char *pciBusId, nvmlDevice_t *device) = NULL;
static nvmlReturn_t (*pnvmlDeviceGetHandleBySerial)(const char *serial, nvmlDevice_t *device) = NULL;
static nvmlReturn_t (*pnvmlDeviceGetHandleByUUID)(const char *uuid, nvmlDevice_t *device) = NULL;
static nvmlReturn_t (*pnvmlDeviceGetHostVgpuMode)(nvmlDevice_t device, nvmlHostVgpuMode_t *pHostVgpuMode) = NULL;
static nvmlReturn_t (*pnvmlDeviceGetIndex)(nvmlDevice_t device, unsigned int *index) = NULL;
static nvmlReturn_t (*pnvmlDeviceGetInforomConfigurationChecksum)(nvmlDevice_t device, unsigned int *checksum) = NULL;
static nvmlReturn_t (*pnvmlDeviceGetInforomImageVersion)(nvmlDevice_t device, char *version, unsigned int length) = NULL;
static nvmlReturn_t (*pnvmlDeviceGetInforomVersion)(nvmlDevice_t device, nvmlInforomObject_t object, char *version, unsigned int length) = NULL;
static nvmlReturn_t (*pnvmlDeviceGetMaxClockInfo)(nvmlDevice_t device, nvmlClockType_t type, unsigned int *clock) = NULL;
static nvmlReturn_t (*pnvmlDeviceGetMaxPcieLinkGeneration)(nvmlDevice_t device, unsigned int *maxLinkGen) = NULL;
static nvmlReturn_t (*pnvmlDeviceGetMaxPcieLinkWidth)(nvmlDevice_t device, unsigned int *maxLinkWidth) = NULL;
static nvmlReturn_t (*pnvmlDeviceGetMemoryErrorCounter)(nvmlDevice_t device, nvmlMemoryErrorType_t errorType, nvmlEccCounterType_t counterType, nvmlMemoryLocation_t locationType, unsigned long long *count) = NULL;
static nvmlReturn_t (*pnvmlDeviceGetMemoryInfo)(nvmlDevice_t device, nvmlMemory_t *memory) = NULL;
static nvmlReturn_t (*pnvmlDeviceGetMigMode)(nvmlDevice_t device, unsigned int *currentMode, unsigned int *pendingMode) = NULL;
static nvmlReturn_t (*pnvmlDeviceGetMultiGpuBoard)(nvmlDevice_t device, unsigned int *multiGpuBool) = NULL;
static nvmlReturn_t (*pnvmlDeviceGetName)(nvmlDevice_t device, char *name, unsigned int length) = NULL;
static nvmlReturn_t (*pnvmlDeviceGetNvLinkCapability)(nvmlDevice_t device, unsigned int link, nvmlNvLinkCapability_t capability, unsigned int *capResult) = NULL;
static nvmlReturn_t (*pnvmlDeviceGetNvLinkErrorCounter)(nvmlDevice_t device, unsigned int link, nvmlNvLinkErrorCounter_t counter, unsigned long long *counterValue) = NULL;
static nvmlReturn_t (*pnvmlDeviceGetNvLinkRemotePciInfo)(nvmlDevice_t device, unsigned int link, nvmlPciInfo_t *pci) = NULL;
static nvmlReturn_t (*pnvmlDeviceGetNvLinkRemotePciInfo_v2)(nvmlDevice_t device, unsigned int link, nvmlPciInfo_t *pci) = NULL;
static nvmlReturn_t (*pnvmlDeviceGetNvLinkState)(nvmlDevice_t device, unsigned int link, nvmlEnableState_t *isActive) = NULL;
static nvmlReturn_t (*pnvmlDeviceGetNvLinkUtilizationControl)(nvmlDevice_t device, unsigned int link, unsigned int counter, nvmlNvLinkUtilizationControl_t *control) = NULL;
static nvmlReturn_t (*pnvmlDeviceGetNvLinkUtilizationCounter)(nvmlDevice_t device, unsigned int link, unsigned int counter,  unsigned long long *rxcounter, unsigned long long *txcounter) = NULL;
static nvmlReturn_t (*pnvmlDeviceGetNvLinkVersion)(nvmlDevice_t device, unsigned int link, unsigned int *version) = NULL;
static nvmlReturn_t (*pnvmlDeviceGetP2PStatus)(nvmlDevice_t device1, nvmlDevice_t device2, nvmlGpuP2PCapsIndex_t p2pIndex, nvmlGpuP2PStatus_t *p2pStatus) = NULL;
static nvmlReturn_t (*pnvmlDeviceGetPciInfo)(nvmlDevice_t device, nvmlPciInfo_t *pci) = NULL;
static nvmlReturn_t (*pnvmlDeviceGetPciInfo_v2)(nvmlDevice_t device, nvmlPciInfo_t *pci) = NULL;
static nvmlReturn_t (*pnvmlDeviceGetPciInfo_v3)(nvmlDevice_t device, nvmlPciInfo_t *pci) = NULL;
static nvmlReturn_t (*pnvmlDeviceGetPcieReplayCounter)(nvmlDevice_t device, unsigned int *value) = NULL;
static nvmlReturn_t (*pnvmlDeviceGetPcieThroughput)(nvmlDevice_t device, nvmlPcieUtilCounter_t counter, unsigned int *value) = NULL;
static nvmlReturn_t (*pnvmlDeviceGetPerformanceState)(nvmlDevice_t device, nvmlPstates_t *pState) = NULL;
static nvmlReturn_t (*pnvmlDeviceGetPgpuMetadataString)(nvmlDevice_t device, char *pgpuMetadata, unsigned int *bufferSize) = NULL;
static nvmlReturn_t (*pnvmlDeviceGetPowerManagementDefaultLimit)(nvmlDevice_t device, unsigned int *defaultLimit) = NULL;
static nvmlReturn_t (*pnvmlDeviceGetPowerManagementLimit)(nvmlDevice_t device, unsigned int *limit) = NULL;
static nvmlReturn_t (*pnvmlDeviceGetPowerManagementLimitConstraints)(nvmlDevice_t device, unsigned int *minLimit, unsigned int *maxLimit) = NULL;
static nvmlReturn_t (*pnvmlDeviceGetPowerManagementMode)(nvmlDevice_t device, nvmlEnableState_t *mode) = NULL;
static nvmlReturn_t (*pnvmlDeviceGetPowerState)(nvmlDevice_t device, nvmlPstates_t *pState) = NULL;
static nvmlReturn_t (*pnvmlDeviceGetPowerUsage)(nvmlDevice_t device, unsigned int *power) = NULL;
static nvmlReturn_t (*pnvmlDeviceGetRemappedRows)(nvmlDevice_t device, unsigned int *corrRows, unsigned int *uncRows, unsigned int *isPending, unsigned int *failureOccurred) = NULL;
static nvmlReturn_t (*pnvmlDeviceGetRetiredPages)(nvmlDevice_t device, nvmlPageRetirementCause_t cause, unsigned int *pageCount, unsigned long long *addresses) = NULL;
static nvmlReturn_t (*pnvmlDeviceGetRetiredPagesPendingStatus)(nvmlDevice_t device, nvmlEnableState_t *isPending) = NULL;
static nvmlReturn_t (*pnvmlDeviceGetRetiredPages_v2)(nvmlDevice_t device, nvmlPageRetirementCause_t cause, unsigned int *pageCount, unsigned long long *addresses, unsigned long long *timestamps) = NULL;
static nvmlReturn_t (*pnvmlDeviceGetRowRemapperHistogram)(nvmlDevice_t device, nvmlRowRemapperHistogramValues_t *values) = NULL;
static nvmlReturn_t (*pnvmlDeviceGetSamples)(nvmlDevice_t device, nvmlSamplingType_t type, unsigned long long lastSeenTimeStamp, nvmlValueType_t *sampleValType, unsigned int *sampleCount, nvmlSample_t *samples) = NULL;
static nvmlReturn_t (*pnvmlDeviceGetSerial)(nvmlDevice_t device, char *serial, unsigned int length) = NULL;
static nvmlReturn_t (*pnvmlDeviceGetSupportedClocksThrottleReasons)(nvmlDevice_t device, unsigned long long *supportedClocksThrottleReasons) = NULL;
static nvmlReturn_t (*pnvmlDeviceGetSupportedEventTypes)(nvmlDevice_t device, unsigned long long *eventTypes) = NULL;
static nvmlReturn_t (*pnvmlDeviceGetSupportedGraphicsClocks)(nvmlDevice_t device, unsigned int memoryClockMHz, unsigned int *count, unsigned int *clocksMHz) = NULL;
static nvmlReturn_t (*pnvmlDeviceGetSupportedMemoryClocks)(nvmlDevice_t device, unsigned int *count, unsigned int *clocksMHz) = NULL;
static nvmlReturn_t (*pnvmlDeviceGetSupportedVgpus)(nvmlDevice_t device, unsigned int *vgpuCount, nvmlVgpuTypeId_t *vgpuTypeIds) = NULL;
static nvmlReturn_t (*pnvmlDeviceGetTemperature)(nvmlDevice_t device, nvmlTemperatureSensors_t sensorType, unsigned int *temp) = NULL;
static nvmlReturn_t (*pnvmlDeviceGetTemperatureThreshold)(nvmlDevice_t device, nvmlTemperatureThresholds_t thresholdType, unsigned int *temp) = NULL;
static nvmlReturn_t (*pnvmlDeviceGetTotalEccErrors)(nvmlDevice_t device, nvmlMemoryErrorType_t errorType, nvmlEccCounterType_t counterType, unsigned long long *eccCounts) = NULL;
static nvmlReturn_t (*pnvmlDeviceGetTotalEnergyConsumption)(nvmlDevice_t device, unsigned long long *energy) = NULL;
static nvmlReturn_t (*pnvmlDeviceGetUUID)(nvmlDevice_t device, char *uuid, unsigned int length) = NULL;
static nvmlReturn_t (*pnvmlDeviceGetUtilizationRates)(nvmlDevice_t device, nvmlUtilization_t *utilization) = NULL;
static nvmlReturn_t (*pnvmlDeviceGetVbiosVersion)(nvmlDevice_t device, char *version, unsigned int length) = NULL;
static nvmlReturn_t (*pnvmlDeviceGetVgpuUtilization)(nvmlDevice_t device, unsigned long long lastSeenTimeStamp, nvmlValueType_t *sampleValType, unsigned int *vgpuInstanceSamplesCount, nvmlVgpuInstanceUtilizationSample_t *utilizationSamples) = NULL;
static nvmlReturn_t (*pnvmlDeviceGetViolationStatus)(nvmlDevice_t device, nvmlPerfPolicyType_t perfPolicyType, nvmlViolationTime_t *violTime) = NULL;
static nvmlReturn_t (*pnvmlDeviceGetVirtualizationMode)(nvmlDevice_t device, nvmlGpuVirtualizationMode_t *pVirtualMode) = NULL;
static nvmlReturn_t (*pnvmlDeviceOnSameBoard)(nvmlDevice_t device1, nvmlDevice_t device2, int *onSameBoard) = NULL;
static nvmlReturn_t (*pnvmlDeviceRegisterEvents)(nvmlDevice_t device, unsigned long long eventTypes, nvmlEventSet_t set) = NULL;
static nvmlReturn_t (*pnvmlDeviceSetComputeMode)(nvmlDevice_t device, nvmlComputeMode_t mode) = NULL;
static nvmlReturn_t (*pnvmlEventSetCreate)(nvmlEventSet_t *set) = NULL;
static nvmlReturn_t (*pnvmlEventSetFree)(nvmlEventSet_t set) = NULL;
static nvmlReturn_t (*pnvmlEventSetWait)(nvmlEventSet_t set, nvmlEventData_t *data, unsigned int timeoutms) = NULL;
static nvmlReturn_t (*pnvmlEventSetWait_v2)(nvmlEventSet_t set, nvmlEventData_t *data, unsigned int timeoutms) = NULL;

const char* __cdecl nvmlErrorString(nvmlReturn_t result)
{
    TRACE("(%u)\n", result);
    return pnvmlErrorString(result);
}

nvmlReturn_t __cdecl nvmlInit(void)
{
    TRACE("()\n");
    return pnvmlInit();
}

nvmlReturn_t __cdecl nvmlInitWithFlags(unsigned int flags)
{
    TRACE("(%u)\n", flags);
    return pnvmlInitWithFlags(flags);
}

nvmlReturn_t __cdecl nvmlInit_v2(void)
{
    TRACE("()\n");
    return pnvmlInit_v2();
}

nvmlReturn_t __cdecl nvmlInternalGetExportTable(size_t *exportTable, GUID *guid)
{
    FIXME("(%p, %s): stub\n", exportTable, debugstr_guid(guid));
    return NVML_ERROR_INVALID_ARGUMENT;
}

nvmlReturn_t __cdecl nvmlShutdown(void)
{
    TRACE("()\n");
    return pnvmlShutdown();
}

nvmlReturn_t __cdecl nvmlSystemGetCudaDriverVersion(int *cudaDriverVersion)
{
    TRACE("(%p)\n", cudaDriverVersion);
    return pnvmlSystemGetCudaDriverVersion(cudaDriverVersion);
}

nvmlReturn_t __cdecl nvmlSystemGetCudaDriverVersion_v2(int *cudaDriverVersion)
{
    TRACE("(%p)\n", cudaDriverVersion);
    return pnvmlSystemGetCudaDriverVersion_v2(cudaDriverVersion);
}

nvmlReturn_t __cdecl nvmlSystemGetDriverVersion(char *version, unsigned int length)
{
    TRACE("(%p, %u)\n", version, length);
    return pnvmlSystemGetDriverVersion(version, length);
}

nvmlReturn_t __cdecl nvmlSystemGetNVMLVersion(char *version, unsigned int length)
{
    TRACE("(%p, %u)\n", version, length);
    return pnvmlSystemGetNVMLVersion(version, length);
}

nvmlReturn_t __cdecl nvmlDeviceClearCpuAffinity(nvmlDevice_t device)
{
    TRACE("(%p)\n", device);

    unsigned int index;
    nvmlReturn_t ret = nvmlDeviceGetIndex(device, &index);

    return ret == NVML_SUCCESS ? NVML_ERROR_NOT_SUPPORTED : ret;
}

nvmlReturn_t __cdecl nvmlDeviceDiscoverGpus(nvmlPciInfo_t *pciInfo)
{
    TRACE("(%p)\n", pciInfo);

    if (!pciInfo) return NVML_ERROR_INVALID_ARGUMENT;

    unsigned int deviceCount;
    nvmlReturn_t ret = nvmlDeviceGetCount_v2(&deviceCount);

    return ret == NVML_SUCCESS ? NVML_ERROR_NOT_SUPPORTED : ret;
}

nvmlReturn_t __cdecl nvmlDeviceGetAPIRestriction(nvmlDevice_t device, nvmlRestrictedAPI_t apiType, nvmlEnableState_t *isRestricted)
{
    TRACE("(%p, %u, %p)\n", device, apiType, isRestricted);
    return pnvmlDeviceGetAPIRestriction
        ? pnvmlDeviceGetAPIRestriction(device, apiType, isRestricted)
        : NVML_ERROR_FUNCTION_NOT_FOUND;
}

nvmlReturn_t __cdecl nvmlDeviceGetActiveVgpus(nvmlDevice_t device, unsigned int *vgpuCount, nvmlVgpuInstance_t *vgpuInstances)
{
    TRACE("(%p, %p, %p)\n", device, vgpuCount, vgpuInstances);
    return pnvmlDeviceGetActiveVgpus
        ? pnvmlDeviceGetActiveVgpus(device, vgpuCount, vgpuInstances)
        : NVML_ERROR_FUNCTION_NOT_FOUND;
}

nvmlReturn_t __cdecl nvmlDeviceGetApplicationsClock(nvmlDevice_t device, nvmlClockType_t clockType, unsigned int *clockMHz)
{
    TRACE("(%p, %u, %p)\n", device, clockType, clockMHz);
    return pnvmlDeviceGetApplicationsClock
        ? pnvmlDeviceGetApplicationsClock(device, clockType, clockMHz)
        : NVML_ERROR_FUNCTION_NOT_FOUND;
}

nvmlReturn_t __cdecl nvmlDeviceGetArchitecture(nvmlDevice_t device, nvmlDeviceArchitecture_t *arch)
{
    TRACE("(%p, %p)\n", device, arch);
    return pnvmlDeviceGetArchitecture
        ? pnvmlDeviceGetArchitecture(device, arch)
        : NVML_ERROR_FUNCTION_NOT_FOUND;
}

nvmlReturn_t __cdecl nvmlDeviceGetAutoBoostedClocksEnabled(nvmlDevice_t device, nvmlEnableState_t *isEnabled, nvmlEnableState_t *defaultIsEnabled)
{
    TRACE("(%p, %p, %p)\n", device, isEnabled, defaultIsEnabled);
    return pnvmlDeviceGetAutoBoostedClocksEnabled
        ? pnvmlDeviceGetAutoBoostedClocksEnabled(device, isEnabled, defaultIsEnabled)
        : NVML_ERROR_FUNCTION_NOT_FOUND;
}

nvmlReturn_t __cdecl nvmlDeviceGetBAR1MemoryInfo(nvmlDevice_t device, nvmlBAR1Memory_t *bar1Memory)
{
    TRACE("(%p, %p)\n", device, bar1Memory);
    return pnvmlDeviceGetBAR1MemoryInfo
        ? pnvmlDeviceGetBAR1MemoryInfo(device, bar1Memory)
        : NVML_ERROR_FUNCTION_NOT_FOUND;
}

nvmlReturn_t __cdecl nvmlDeviceGetBoardId(nvmlDevice_t device, unsigned int *boardId)
{
    TRACE("(%p, %p)\n", device, boardId);
    return pnvmlDeviceGetBoardId
        ? pnvmlDeviceGetBoardId(device, boardId)
        : NVML_ERROR_FUNCTION_NOT_FOUND;
}

nvmlReturn_t __cdecl nvmlDeviceGetBoardPartNumber(nvmlDevice_t device, char *partNumber, unsigned int length)
{
    TRACE("(%p, %p, %u)\n", device, partNumber, length);
    return pnvmlDeviceGetBoardPartNumber
        ? pnvmlDeviceGetBoardPartNumber(device, partNumber, length)
        : NVML_ERROR_FUNCTION_NOT_FOUND;
}

nvmlReturn_t __cdecl nvmlDeviceGetBrand(nvmlDevice_t device, nvmlBrandType_t *type)
{
    TRACE("(%p, %p)\n", device, type);
    return pnvmlDeviceGetBrand
        ? pnvmlDeviceGetBrand(device, type)
        : NVML_ERROR_FUNCTION_NOT_FOUND;
}

nvmlReturn_t __cdecl nvmlDeviceGetBridgeChipInfo(nvmlDevice_t device, nvmlBridgeChipHierarchy_t *bridgeHierarchy)
{
    TRACE("(%p, %p)\n", device, bridgeHierarchy);
    return pnvmlDeviceGetBridgeChipInfo
        ? pnvmlDeviceGetBridgeChipInfo(device, bridgeHierarchy)
        : NVML_ERROR_FUNCTION_NOT_FOUND;
}

nvmlReturn_t __cdecl nvmlDeviceGetClock(nvmlDevice_t device, nvmlClockType_t clockType, nvmlClockId_t clockId, unsigned int *clockMHz)
{
    TRACE("(%p, %u, %u, %p)\n", device, clockType, clockId, clockMHz);
    return pnvmlDeviceGetClock
        ? pnvmlDeviceGetClock(device, clockType, clockId, clockMHz)
        : NVML_ERROR_FUNCTION_NOT_FOUND;
}

nvmlReturn_t __cdecl nvmlDeviceGetClockInfo(nvmlDevice_t device, nvmlClockType_t type, unsigned int *clock)
{
    TRACE("(%p, %u, %p)\n", device, type, clock);
    return pnvmlDeviceGetClockInfo
        ? pnvmlDeviceGetClockInfo(device, type, clock)
        : NVML_ERROR_FUNCTION_NOT_FOUND;
}

nvmlReturn_t __cdecl nvmlDeviceGetComputeMode(nvmlDevice_t device, nvmlComputeMode_t *mode)
{
    TRACE("(%p, %p)\n", device, mode);
    return pnvmlDeviceGetComputeMode
        ? pnvmlDeviceGetComputeMode(device, mode)
        : NVML_ERROR_FUNCTION_NOT_FOUND;
}

nvmlReturn_t __cdecl nvmlDeviceGetCount(unsigned int *deviceCount)
{
    TRACE("(%p)\n", deviceCount);
    return pnvmlDeviceGetCount
        ? pnvmlDeviceGetCount(deviceCount)
        : NVML_ERROR_FUNCTION_NOT_FOUND;
}

nvmlReturn_t __cdecl nvmlDeviceGetCount_v2(unsigned int *deviceCount)
{
    TRACE("(%p)\n", deviceCount);
    return pnvmlDeviceGetCount_v2
        ? pnvmlDeviceGetCount_v2(deviceCount)
        : NVML_ERROR_FUNCTION_NOT_FOUND;
}

nvmlReturn_t __cdecl nvmlDeviceGetCpuAffinity(nvmlDevice_t device, unsigned int cpuSetSize, unsigned long *cpuSet)
{
    TRACE("(%p, %u, %p)\n", device, cpuSetSize, cpuSet);

    if (!cpuSetSize || !cpuSet) return NVML_ERROR_INVALID_ARGUMENT;

    unsigned int index;
    nvmlReturn_t ret = nvmlDeviceGetIndex(device, &index);

    return ret == NVML_SUCCESS ? NVML_ERROR_NOT_SUPPORTED : ret;
}

nvmlReturn_t __cdecl nvmlDeviceGetCpuAffinityWithinScope(nvmlDevice_t device, unsigned int cpuSetSize, unsigned long *cpuSet, nvmlAffinityScope_t scope)
{
    TRACE("(%p, %u, %p, %u)\n", device, cpuSetSize, cpuSet, scope);

    if (!cpuSetSize || !cpuSet || (scope != NVML_AFFINITY_SCOPE_NODE && scope != NVML_AFFINITY_SCOPE_SOCKET)) return NVML_ERROR_INVALID_ARGUMENT;

    unsigned int index;
    nvmlReturn_t ret = nvmlDeviceGetIndex(device, &index);

    return ret == NVML_SUCCESS ? NVML_ERROR_NOT_SUPPORTED : ret;
}

nvmlReturn_t __cdecl nvmlDeviceGetCreatableVgpus(nvmlDevice_t device, unsigned int *vgpuCount, nvmlVgpuTypeId_t *vgpuTypeIds)
{
    TRACE("(%p, %p, %p)\n", device, vgpuCount, vgpuTypeIds);
    return pnvmlDeviceGetCreatableVgpus
        ? pnvmlDeviceGetCreatableVgpus(device, vgpuCount, vgpuTypeIds)
        : NVML_ERROR_FUNCTION_NOT_FOUND;
}

nvmlReturn_t __cdecl nvmlDeviceGetCudaComputeCapability(nvmlDevice_t device, int *major, int *minor)
{
    TRACE("(%p, %p, %p)\n", device, major, minor);
    return pnvmlDeviceGetCudaComputeCapability
        ? pnvmlDeviceGetCudaComputeCapability(device, major, minor)
        : NVML_ERROR_FUNCTION_NOT_FOUND;
}

nvmlReturn_t __cdecl nvmlDeviceGetCurrPcieLinkGeneration(nvmlDevice_t device, unsigned int *currLinkGen)
{
    TRACE("(%p, %p)\n", device, currLinkGen);
    return pnvmlDeviceGetCurrPcieLinkGeneration
        ? pnvmlDeviceGetCurrPcieLinkGeneration(device, currLinkGen)
        : NVML_ERROR_FUNCTION_NOT_FOUND;
}

nvmlReturn_t __cdecl nvmlDeviceGetCurrPcieLinkWidth(nvmlDevice_t device, unsigned int *currLinkWidth)
{
    TRACE("(%p, %p)\n", device, currLinkWidth);
    return pnvmlDeviceGetCurrPcieLinkWidth
        ? pnvmlDeviceGetCurrPcieLinkWidth(device, currLinkWidth)
        : NVML_ERROR_FUNCTION_NOT_FOUND;
}

nvmlReturn_t __cdecl nvmlDeviceGetCurrentClocksThrottleReasons(nvmlDevice_t device, unsigned long long *clocksThrottleReasons)
{
    TRACE("(%p, %p)\n", device, clocksThrottleReasons);
    return pnvmlDeviceGetCurrentClocksThrottleReasons
        ? pnvmlDeviceGetCurrentClocksThrottleReasons(device, clocksThrottleReasons)
        : NVML_ERROR_FUNCTION_NOT_FOUND;
}

nvmlReturn_t __cdecl nvmlDeviceGetDecoderUtilization(nvmlDevice_t device, unsigned int *utilization, unsigned int *samplingPeriodUs)
{
    TRACE("(%p, %p, %p)\n", device, utilization, samplingPeriodUs);
    return pnvmlDeviceGetDecoderUtilization
        ? pnvmlDeviceGetDecoderUtilization(device, utilization, samplingPeriodUs)
        : NVML_ERROR_FUNCTION_NOT_FOUND;
}

nvmlReturn_t __cdecl nvmlDeviceGetDefaultApplicationsClock(nvmlDevice_t device, nvmlClockType_t clockType, unsigned int *clockMHz)
{
    TRACE("(%p, %u, %p)\n", device, clockType, clockMHz);
    return pnvmlDeviceGetDefaultApplicationsClock
        ? pnvmlDeviceGetDefaultApplicationsClock(device, clockType, clockMHz)
        : NVML_ERROR_FUNCTION_NOT_FOUND;
}

nvmlReturn_t __cdecl nvmlDeviceGetDetailedEccErrors(nvmlDevice_t device, nvmlMemoryErrorType_t errorType, nvmlEccCounterType_t counterType, nvmlEccErrorCounts_t *eccCounts)
{
    TRACE("(%p, %u, %u, %p)\n", device, errorType, counterType, eccCounts);
    return pnvmlDeviceGetDetailedEccErrors
        ? pnvmlDeviceGetDetailedEccErrors(device, errorType, counterType, eccCounts)
        : NVML_ERROR_FUNCTION_NOT_FOUND;
}

nvmlReturn_t __cdecl nvmlDeviceGetDisplayActive(nvmlDevice_t device, nvmlEnableState_t *isActive)
{
    TRACE("(%p, %p)\n", device, isActive);
    return pnvmlDeviceGetDisplayActive
        ? pnvmlDeviceGetDisplayActive(device, isActive)
        : NVML_ERROR_FUNCTION_NOT_FOUND;
}

nvmlReturn_t __cdecl nvmlDeviceGetDisplayMode(nvmlDevice_t device, nvmlEnableState_t *display)
{
    TRACE("(%p, %p)\n", device, display);
    return pnvmlDeviceGetDisplayMode
        ? pnvmlDeviceGetDisplayMode(device, display)
        : NVML_ERROR_FUNCTION_NOT_FOUND;
}

nvmlReturn_t __cdecl nvmlDeviceGetDriverModel(nvmlDevice_t device, nvmlDriverModel_t *current, nvmlDriverModel_t *pending)
{
    TRACE("(%p, %p, %p)\n", device, current, pending);

    if (!current && !pending) return NVML_ERROR_INVALID_ARGUMENT;

    unsigned int index;
    nvmlReturn_t ret = nvmlDeviceGetIndex(device, &index);

    if (ret == NVML_SUCCESS)
    {
        if (current) *current = NVML_DRIVER_WDDM;
        if (pending) *pending = NVML_DRIVER_WDDM;
    }

    return ret;
}

nvmlReturn_t __cdecl nvmlDeviceGetEccMode(nvmlDevice_t device, nvmlEnableState_t *current, nvmlEnableState_t *pending)
{
    TRACE("(%p, %p, %p)\n", device, current, pending);
    return pnvmlDeviceGetEccMode
        ? pnvmlDeviceGetEccMode(device, current, pending)
        : NVML_ERROR_FUNCTION_NOT_FOUND;
}

nvmlReturn_t __cdecl nvmlDeviceGetEncoderCapacity(nvmlDevice_t device, nvmlEncoderType_t encoderQueryType, unsigned int *encoderCapacity)
{
    TRACE("(%p, %u, %p)\n", device, encoderQueryType, encoderCapacity);
    return pnvmlDeviceGetEncoderCapacity
        ? pnvmlDeviceGetEncoderCapacity(device, encoderQueryType, encoderCapacity)
        : NVML_ERROR_FUNCTION_NOT_FOUND;
}

nvmlReturn_t __cdecl nvmlDeviceGetEncoderStats(nvmlDevice_t device, unsigned int *sessionCount, unsigned int *averageFps, unsigned int *averageLatency)
{
    TRACE("(%p, %p, %p, %p)\n", device, sessionCount, averageFps, averageLatency);
    return pnvmlDeviceGetEncoderStats
        ? pnvmlDeviceGetEncoderStats(device, sessionCount, averageFps, averageLatency)
        : NVML_ERROR_FUNCTION_NOT_FOUND;
}

nvmlReturn_t __cdecl nvmlDeviceGetEncoderUtilization(nvmlDevice_t device, unsigned int *utilization, unsigned int *samplingPeriodUs)
{
    TRACE("(%p, %p, %p)\n", device, utilization, samplingPeriodUs);
    return pnvmlDeviceGetEncoderUtilization
        ? pnvmlDeviceGetEncoderUtilization(device, utilization, samplingPeriodUs)
        : NVML_ERROR_FUNCTION_NOT_FOUND;
}

nvmlReturn_t __cdecl nvmlDeviceGetEnforcedPowerLimit(nvmlDevice_t device, unsigned int *limit)
{
    TRACE("(%p, %p)\n", device, limit);
    return pnvmlDeviceGetEnforcedPowerLimit
        ? pnvmlDeviceGetEnforcedPowerLimit(device, limit)
        : NVML_ERROR_FUNCTION_NOT_FOUND;
}

nvmlReturn_t __cdecl nvmlDeviceGetFBCStats(nvmlDevice_t device, nvmlFBCStats_t *fbcStats)
{
    TRACE("(%p, %p)\n", device, fbcStats);
    return pnvmlDeviceGetFBCStats
        ? pnvmlDeviceGetFBCStats(device, fbcStats)
        : NVML_ERROR_FUNCTION_NOT_FOUND;
}

nvmlReturn_t __cdecl nvmlDeviceGetFanSpeed(nvmlDevice_t device, unsigned int *speed)
{
    TRACE("(%p, %p)\n", device, speed);
    return pnvmlDeviceGetFanSpeed
        ? pnvmlDeviceGetFanSpeed(device, speed)
        : NVML_ERROR_FUNCTION_NOT_FOUND;
}

nvmlReturn_t __cdecl nvmlDeviceGetFanSpeed_v2(nvmlDevice_t device, unsigned int fan, unsigned int *speed)
{
    TRACE("(%p, %u, %p)\n", device, fan, speed);
    return pnvmlDeviceGetFanSpeed_v2
        ? pnvmlDeviceGetFanSpeed_v2(device, fan, speed)
        : NVML_ERROR_FUNCTION_NOT_FOUND;
}

nvmlReturn_t __cdecl nvmlDeviceGetFieldValues(nvmlDevice_t device, int valuesCount, nvmlFieldValue_t *values)
{
    TRACE("(%p, %u, %p)\n", device, valuesCount, values);
    return pnvmlDeviceGetFieldValues
        ? pnvmlDeviceGetFieldValues(device, valuesCount, values)
        : NVML_ERROR_FUNCTION_NOT_FOUND;
}

nvmlReturn_t __cdecl nvmlDeviceGetGpuOperationMode(nvmlDevice_t device, nvmlGpuOperationMode_t *current, nvmlGpuOperationMode_t *pending)
{
    TRACE("(%p, %p, %p)\n", device, current, pending);
    return pnvmlDeviceGetGpuOperationMode
        ? pnvmlDeviceGetGpuOperationMode(device, current, pending)
        : NVML_ERROR_FUNCTION_NOT_FOUND;
}

nvmlReturn_t __cdecl nvmlDeviceGetGridLicensableFeatures(nvmlDevice_t device, nvmlGridLicensableFeatures_t *pGridLicensableFeatures)
{
    TRACE("(%p, %p)\n", device, pGridLicensableFeatures);
    return pnvmlDeviceGetGridLicensableFeatures
        ? pnvmlDeviceGetGridLicensableFeatures(device, pGridLicensableFeatures)
        : NVML_ERROR_FUNCTION_NOT_FOUND;
}

nvmlReturn_t __cdecl nvmlDeviceGetGridLicensableFeatures_v2(nvmlDevice_t device, nvmlGridLicensableFeatures_t *pGridLicensableFeatures)
{
    TRACE("(%p, %p)\n", device, pGridLicensableFeatures);
    return pnvmlDeviceGetGridLicensableFeatures_v2
        ? pnvmlDeviceGetGridLicensableFeatures_v2(device, pGridLicensableFeatures)
        : NVML_ERROR_FUNCTION_NOT_FOUND;
}

nvmlReturn_t __cdecl nvmlDeviceGetGridLicensableFeatures_v3(nvmlDevice_t device, nvmlGridLicensableFeatures_t *pGridLicensableFeatures)
{
    TRACE("(%p, %p)\n", device, pGridLicensableFeatures);
    return pnvmlDeviceGetGridLicensableFeatures_v3
        ? pnvmlDeviceGetGridLicensableFeatures_v3(device, pGridLicensableFeatures)
        : NVML_ERROR_FUNCTION_NOT_FOUND;
}

nvmlReturn_t __cdecl nvmlDeviceGetHandleByIndex(unsigned int index, nvmlDevice_t *device)
{
    TRACE("(%u, %p)\n", index, device);
    return pnvmlDeviceGetHandleByIndex
        ? pnvmlDeviceGetHandleByIndex(index, device)
        : NVML_ERROR_FUNCTION_NOT_FOUND;
}

nvmlReturn_t __cdecl nvmlDeviceGetHandleByIndex_v2(unsigned int index, nvmlDevice_t *device)
{
    TRACE("(%u, %p)\n", index, device);
    return pnvmlDeviceGetHandleByIndex_v2
        ? pnvmlDeviceGetHandleByIndex_v2(index, device)
        : NVML_ERROR_FUNCTION_NOT_FOUND;
}

nvmlReturn_t __cdecl nvmlDeviceGetHandleByPciBusId(const char *pciBusId, nvmlDevice_t *device)
{
    TRACE("(%s, %p)\n", pciBusId, device);
    return pnvmlDeviceGetHandleByPciBusId
        ? pnvmlDeviceGetHandleByPciBusId(pciBusId, device)
        : NVML_ERROR_FUNCTION_NOT_FOUND;
}

nvmlReturn_t __cdecl nvmlDeviceGetHandleByPciBusId_v2(const char *pciBusId, nvmlDevice_t *device)
{
    TRACE("(%s, %p)\n", pciBusId, device);
    return pnvmlDeviceGetHandleByPciBusId_v2
        ? pnvmlDeviceGetHandleByPciBusId_v2(pciBusId, device)
        : NVML_ERROR_FUNCTION_NOT_FOUND;
}

nvmlReturn_t __cdecl nvmlDeviceGetHandleBySerial(const char *serial, nvmlDevice_t *device)
{
    TRACE("(%s, %p)\n", serial, device);
    return pnvmlDeviceGetHandleBySerial
        ? pnvmlDeviceGetHandleBySerial(serial, device)
        : NVML_ERROR_FUNCTION_NOT_FOUND;
}

nvmlReturn_t __cdecl nvmlDeviceGetHandleByUUID(const char *uuid, nvmlDevice_t *device)
{
    TRACE("(%s, %p)\n", uuid, device);
    return pnvmlDeviceGetHandleByUUID
        ? pnvmlDeviceGetHandleByUUID(uuid, device)
        : NVML_ERROR_FUNCTION_NOT_FOUND;
}

nvmlReturn_t __cdecl nvmlDeviceGetHostVgpuMode(nvmlDevice_t device, nvmlHostVgpuMode_t *pHostVgpuMode)
{
    TRACE("(%p, %p)\n", device, pHostVgpuMode);
    return pnvmlDeviceGetHostVgpuMode
        ? pnvmlDeviceGetHostVgpuMode(device, pHostVgpuMode)
        : NVML_ERROR_FUNCTION_NOT_FOUND;
}

nvmlReturn_t __cdecl nvmlDeviceGetIndex(nvmlDevice_t device, unsigned int *index)
{
    TRACE("(%p, %p)\n", device, index);
    return pnvmlDeviceGetIndex
        ? pnvmlDeviceGetIndex(device, index)
        : NVML_ERROR_FUNCTION_NOT_FOUND;
}

nvmlReturn_t __cdecl nvmlDeviceGetInforomConfigurationChecksum(nvmlDevice_t device, unsigned int *checksum)
{
    TRACE("(%p, %p)\n", device, checksum);
    return pnvmlDeviceGetInforomConfigurationChecksum
        ? pnvmlDeviceGetInforomConfigurationChecksum(device, checksum)
        : NVML_ERROR_FUNCTION_NOT_FOUND;
}

nvmlReturn_t __cdecl nvmlDeviceGetInforomImageVersion(nvmlDevice_t device, char *version, unsigned int length)
{
    TRACE("(%p, %p, %u)\n", device, version, length);
    return pnvmlDeviceGetInforomImageVersion
        ? pnvmlDeviceGetInforomImageVersion(device, version, length)
        : NVML_ERROR_FUNCTION_NOT_FOUND;
}

nvmlReturn_t __cdecl nvmlDeviceGetInforomVersion(nvmlDevice_t device, nvmlInforomObject_t object, char *version, unsigned int length)
{
    TRACE("(%p, %u, %p, %u)\n", device, object, version, length);
    return pnvmlDeviceGetInforomVersion
        ? pnvmlDeviceGetInforomVersion(device, object, version, length)
        : NVML_ERROR_FUNCTION_NOT_FOUND;
}

nvmlReturn_t __cdecl nvmlDeviceGetMaxClockInfo(nvmlDevice_t device, nvmlClockType_t type, unsigned int *clock)
{
    TRACE("(%p, %u, %p)\n", device, type, clock);
    return pnvmlDeviceGetMaxClockInfo
        ? pnvmlDeviceGetMaxClockInfo(device, type, clock)
        : NVML_ERROR_FUNCTION_NOT_FOUND;
}

nvmlReturn_t __cdecl nvmlDeviceGetMaxPcieLinkGeneration(nvmlDevice_t device, unsigned int *maxLinkGen)
{
    TRACE("(%p, %p)\n", device, maxLinkGen);
    return pnvmlDeviceGetMaxPcieLinkGeneration
        ? pnvmlDeviceGetMaxPcieLinkGeneration(device, maxLinkGen)
        : NVML_ERROR_FUNCTION_NOT_FOUND;
}

nvmlReturn_t __cdecl nvmlDeviceGetMaxPcieLinkWidth(nvmlDevice_t device, unsigned int *maxLinkWidth)
{
    TRACE("(%p, %p)\n", device, maxLinkWidth);
    return pnvmlDeviceGetMaxPcieLinkWidth
        ? pnvmlDeviceGetMaxPcieLinkWidth(device, maxLinkWidth)
        : NVML_ERROR_FUNCTION_NOT_FOUND;
}

nvmlReturn_t __cdecl nvmlDeviceGetMemoryAffinity(nvmlDevice_t device, unsigned int nodeSetSize, unsigned long *nodeSet, nvmlAffinityScope_t scope)
{
    TRACE("(%p, %u, %p, %u)\n", device, nodeSetSize, nodeSet, scope);

    if (!nodeSetSize || !nodeSet || (scope != NVML_AFFINITY_SCOPE_NODE && scope != NVML_AFFINITY_SCOPE_SOCKET)) return NVML_ERROR_INVALID_ARGUMENT;

    unsigned int index;
    nvmlReturn_t ret = nvmlDeviceGetIndex(device, &index);

    return ret == NVML_SUCCESS ? NVML_ERROR_NOT_SUPPORTED : ret;
}

nvmlReturn_t __cdecl nvmlDeviceGetMemoryErrorCounter(nvmlDevice_t device, nvmlMemoryErrorType_t errorType, nvmlEccCounterType_t counterType, nvmlMemoryLocation_t locationType, unsigned long long *count)
{
    TRACE("(%p, %u, %u, %u, %p)\n", device, errorType, counterType, locationType, count);
    return pnvmlDeviceGetMemoryErrorCounter
        ? pnvmlDeviceGetMemoryErrorCounter(device, errorType, counterType, locationType, count)
        : NVML_ERROR_FUNCTION_NOT_FOUND;
}

nvmlReturn_t __cdecl nvmlDeviceGetMemoryInfo(nvmlDevice_t device, nvmlMemory_t *memory)
{
    TRACE("(%p, %p)\n", device, memory);
    return pnvmlDeviceGetMemoryInfo
        ? pnvmlDeviceGetMemoryInfo(device, memory)
        : NVML_ERROR_FUNCTION_NOT_FOUND;
}

nvmlReturn_t __cdecl nvmlDeviceGetMigMode(nvmlDevice_t device, unsigned int *currentMode, unsigned int *pendingMode)
{
    TRACE("(%p, %p, %p)\n", device, currentMode, pendingMode);
    return pnvmlDeviceGetMigMode
        ? pnvmlDeviceGetMigMode(device, currentMode, pendingMode)
        : NVML_ERROR_FUNCTION_NOT_FOUND;
}

nvmlReturn_t __cdecl nvmlDeviceGetMinorNumber(nvmlDevice_t device, unsigned int *minorNumber)
{
    TRACE("(%p, %p)\n", device, minorNumber);

    if (!minorNumber) return NVML_ERROR_INVALID_ARGUMENT;

    unsigned int index;
    nvmlReturn_t ret = nvmlDeviceGetIndex(device, &index);

    return ret == NVML_SUCCESS ? NVML_ERROR_NOT_SUPPORTED : ret;
}

nvmlReturn_t __cdecl nvmlDeviceGetMultiGpuBoard(nvmlDevice_t device, unsigned int *multiGpuBool)
{
    TRACE("(%p, %p)\n", device, multiGpuBool);
    return pnvmlDeviceGetMultiGpuBoard
        ? pnvmlDeviceGetMultiGpuBoard(device, multiGpuBool)
        : NVML_ERROR_FUNCTION_NOT_FOUND;
}

nvmlReturn_t __cdecl nvmlDeviceGetName(nvmlDevice_t device, char *name, unsigned int length)
{
    TRACE("(%p, %p, %u)\n", device, name, length);
    return pnvmlDeviceGetName
        ? pnvmlDeviceGetName(device, name, length)
        : NVML_ERROR_FUNCTION_NOT_FOUND;
}

nvmlReturn_t __cdecl nvmlDeviceGetNvLinkCapability(nvmlDevice_t device, unsigned int link, nvmlNvLinkCapability_t capability, unsigned int *capResult)
{
    TRACE("(%p, %u, %u, %p)\n", device, link, capability, capResult);
    return pnvmlDeviceGetNvLinkCapability
        ? pnvmlDeviceGetNvLinkCapability(device, link, capability, capResult)
        : NVML_ERROR_FUNCTION_NOT_FOUND;
}

nvmlReturn_t __cdecl nvmlDeviceGetNvLinkErrorCounter(nvmlDevice_t device, unsigned int link, nvmlNvLinkErrorCounter_t counter, unsigned long long *counterValue)
{
    TRACE("(%p, %u, %u, %p)\n", device, link, counter, counterValue);
    return pnvmlDeviceGetNvLinkErrorCounter
        ? pnvmlDeviceGetNvLinkErrorCounter(device, link, counter, counterValue)
        : NVML_ERROR_FUNCTION_NOT_FOUND;
}

nvmlReturn_t __cdecl nvmlDeviceGetNvLinkRemotePciInfo(nvmlDevice_t device, unsigned int link, nvmlPciInfo_t *pci)
{
    TRACE("(%p, %u, %p)\n", device, link, pci);
    return pnvmlDeviceGetNvLinkRemotePciInfo
        ? pnvmlDeviceGetNvLinkRemotePciInfo(device, link, pci)
        : NVML_ERROR_FUNCTION_NOT_FOUND;
}

nvmlReturn_t __cdecl nvmlDeviceGetNvLinkRemotePciInfo_v2(nvmlDevice_t device, unsigned int link, nvmlPciInfo_t *pci)
{
    TRACE("(%p, %u, %p)\n", device, link, pci);
    return pnvmlDeviceGetNvLinkRemotePciInfo_v2
        ? pnvmlDeviceGetNvLinkRemotePciInfo_v2(device, link, pci)
        : NVML_ERROR_FUNCTION_NOT_FOUND;
}

nvmlReturn_t __cdecl nvmlDeviceGetNvLinkState(nvmlDevice_t device, unsigned int link, nvmlEnableState_t *isActive)
{
    TRACE("(%p, %u, %p)\n", device, link, isActive);
    return pnvmlDeviceGetNvLinkState
        ? pnvmlDeviceGetNvLinkState(device, link, isActive)
        : NVML_ERROR_FUNCTION_NOT_FOUND;
}

nvmlReturn_t __cdecl nvmlDeviceGetNvLinkUtilizationControl(nvmlDevice_t device, unsigned int link, unsigned int counter, nvmlNvLinkUtilizationControl_t *control)
{
    TRACE("(%p, %u, %u, %p)\n", device, link, counter, control);
    return pnvmlDeviceGetNvLinkUtilizationControl
        ? pnvmlDeviceGetNvLinkUtilizationControl(device, link, counter, control)
        : NVML_ERROR_FUNCTION_NOT_FOUND;
}

nvmlReturn_t __cdecl nvmlDeviceGetNvLinkUtilizationCounter(nvmlDevice_t device, unsigned int link, unsigned int counter,  unsigned long long *rxcounter, unsigned long long *txcounter)
{
    TRACE("(%p, %u, %u, %p, %p)\n", device, link, counter, rxcounter, txcounter);
    return pnvmlDeviceGetNvLinkUtilizationCounter
        ? pnvmlDeviceGetNvLinkUtilizationCounter(device, link, counter, rxcounter, txcounter)
        : NVML_ERROR_FUNCTION_NOT_FOUND;
}

nvmlReturn_t __cdecl nvmlDeviceGetNvLinkVersion(nvmlDevice_t device, unsigned int link, unsigned int *version)
{
    TRACE("(%p, %u, %p)\n", device, link, version);
    return pnvmlDeviceGetNvLinkVersion
        ? pnvmlDeviceGetNvLinkVersion(device, link, version)
        : NVML_ERROR_FUNCTION_NOT_FOUND;
}

nvmlReturn_t __cdecl nvmlDeviceGetP2PStatus(nvmlDevice_t device1, nvmlDevice_t device2, nvmlGpuP2PCapsIndex_t p2pIndex, nvmlGpuP2PStatus_t *p2pStatus)
{
    TRACE("(%p, %p, %u, %p)\n", device1, device2, p2pIndex, p2pStatus);
    return pnvmlDeviceGetP2PStatus
        ? pnvmlDeviceGetP2PStatus(device1, device2, p2pIndex, p2pStatus)
        : NVML_ERROR_FUNCTION_NOT_FOUND;
}

nvmlReturn_t __cdecl nvmlDeviceGetPciInfo(nvmlDevice_t device, nvmlPciInfo_t *pci)
{
    TRACE("(%p, %p)\n", device, pci);
    return pnvmlDeviceGetPciInfo
        ? pnvmlDeviceGetPciInfo(device, pci)
        : NVML_ERROR_FUNCTION_NOT_FOUND;
}

nvmlReturn_t __cdecl nvmlDeviceGetPciInfo_v2(nvmlDevice_t device, nvmlPciInfo_t *pci)
{
    TRACE("(%p, %p)\n", device, pci);
    return pnvmlDeviceGetPciInfo_v2
        ? pnvmlDeviceGetPciInfo_v2(device, pci)
        : NVML_ERROR_FUNCTION_NOT_FOUND;
}

nvmlReturn_t __cdecl nvmlDeviceGetPciInfo_v3(nvmlDevice_t device, nvmlPciInfo_t *pci)
{
    TRACE("(%p, %p)\n", device, pci);
    return pnvmlDeviceGetPciInfo_v3
        ? pnvmlDeviceGetPciInfo_v3(device, pci)
        : NVML_ERROR_FUNCTION_NOT_FOUND;
}

nvmlReturn_t __cdecl nvmlDeviceGetPcieReplayCounter(nvmlDevice_t device, unsigned int *value)
{
    TRACE("(%p, %p)\n", device, value);
    return pnvmlDeviceGetPcieReplayCounter
        ? pnvmlDeviceGetPcieReplayCounter(device, value)
        : NVML_ERROR_FUNCTION_NOT_FOUND;
}

nvmlReturn_t __cdecl nvmlDeviceGetPcieThroughput(nvmlDevice_t device, nvmlPcieUtilCounter_t counter, unsigned int *value)
{
    TRACE("(%p, %u, %p)\n", device, counter, value);
    return pnvmlDeviceGetPcieThroughput
        ? pnvmlDeviceGetPcieThroughput(device, counter, value)
        : NVML_ERROR_FUNCTION_NOT_FOUND;
}

nvmlReturn_t __cdecl nvmlDeviceGetPerformanceState(nvmlDevice_t device, nvmlPstates_t *pState)
{
    TRACE("(%p, %p)\n", device, pState);
    return pnvmlDeviceGetPerformanceState
        ? pnvmlDeviceGetPerformanceState(device, pState)
        : NVML_ERROR_FUNCTION_NOT_FOUND;
}

nvmlReturn_t __cdecl nvmlDeviceGetPersistenceMode(nvmlDevice_t device, nvmlEnableState_t *mode)
{
    TRACE("(%p, %p)\n", device, mode);

    if (!mode) return NVML_ERROR_INVALID_ARGUMENT;

    unsigned int index;
    nvmlReturn_t ret = nvmlDeviceGetIndex(device, &index);

    return ret == NVML_SUCCESS ? NVML_ERROR_NOT_SUPPORTED : ret;
}

nvmlReturn_t __cdecl nvmlDeviceGetPgpuMetadataString(nvmlDevice_t device, char *pgpuMetadata, unsigned int *bufferSize)
{
    TRACE("(%p, %p, %p)\n", device, pgpuMetadata, bufferSize);
    return pnvmlDeviceGetPgpuMetadataString
        ? pnvmlDeviceGetPgpuMetadataString(device, pgpuMetadata, bufferSize)
        : NVML_ERROR_FUNCTION_NOT_FOUND;
}

nvmlReturn_t __cdecl nvmlDeviceGetPowerManagementDefaultLimit(nvmlDevice_t device, unsigned int *defaultLimit)
{
    TRACE("(%p, %p)\n", device, defaultLimit);
    return pnvmlDeviceGetPowerManagementDefaultLimit
        ? pnvmlDeviceGetPowerManagementDefaultLimit(device, defaultLimit)
        : NVML_ERROR_FUNCTION_NOT_FOUND;
}

nvmlReturn_t __cdecl nvmlDeviceGetPowerManagementLimit(nvmlDevice_t device, unsigned int *limit)
{
    TRACE("(%p, %p)\n", device, limit);
    return pnvmlDeviceGetPowerManagementLimit
        ? pnvmlDeviceGetPowerManagementLimit(device, limit)
        : NVML_ERROR_FUNCTION_NOT_FOUND;
}

nvmlReturn_t __cdecl nvmlDeviceGetPowerManagementLimitConstraints(nvmlDevice_t device, unsigned int *minLimit, unsigned int *maxLimit)
{
    TRACE("(%p, %p, %p)\n", device, minLimit, maxLimit);
    return pnvmlDeviceGetPowerManagementLimitConstraints
        ? pnvmlDeviceGetPowerManagementLimitConstraints(device, minLimit, maxLimit)
        : NVML_ERROR_FUNCTION_NOT_FOUND;
}

nvmlReturn_t __cdecl nvmlDeviceGetPowerManagementMode(nvmlDevice_t device, nvmlEnableState_t *mode)
{
    TRACE("(%p, %p)\n", device, mode);
    return pnvmlDeviceGetPowerManagementMode
        ? pnvmlDeviceGetPowerManagementMode(device, mode)
        : NVML_ERROR_FUNCTION_NOT_FOUND;
}

nvmlReturn_t __cdecl nvmlDeviceGetPowerState(nvmlDevice_t device, nvmlPstates_t *pState)
{
    TRACE("(%p, %p)\n", device, pState);
    return pnvmlDeviceGetPowerState
        ? pnvmlDeviceGetPowerState(device, pState)
        : NVML_ERROR_FUNCTION_NOT_FOUND;
}

nvmlReturn_t __cdecl nvmlDeviceGetPowerUsage(nvmlDevice_t device, unsigned int *power)
{
    TRACE("(%p, %p)\n", device, power);
    return pnvmlDeviceGetPowerUsage
        ? pnvmlDeviceGetPowerUsage(device, power)
        : NVML_ERROR_FUNCTION_NOT_FOUND;
}

nvmlReturn_t __cdecl nvmlDeviceGetRemappedRows(nvmlDevice_t device, unsigned int *corrRows, unsigned int *uncRows, unsigned int *isPending, unsigned int *failureOccurred)
{
    TRACE("(%p, %p, %p, %p, %p)\n", device, corrRows, uncRows, isPending, failureOccurred);
    return pnvmlDeviceGetRemappedRows
        ? pnvmlDeviceGetRemappedRows(device, corrRows, uncRows, isPending, failureOccurred)
        : NVML_ERROR_FUNCTION_NOT_FOUND;
}

nvmlReturn_t __cdecl nvmlDeviceGetRetiredPages(nvmlDevice_t device, nvmlPageRetirementCause_t cause, unsigned int *pageCount, unsigned long long *addresses)
{
    TRACE("(%p, %u, %p, %p)\n", device, cause, pageCount, addresses);
    return pnvmlDeviceGetRetiredPages
        ? pnvmlDeviceGetRetiredPages(device, cause, pageCount, addresses)
        : NVML_ERROR_FUNCTION_NOT_FOUND;
}

nvmlReturn_t __cdecl nvmlDeviceGetRetiredPagesPendingStatus(nvmlDevice_t device, nvmlEnableState_t *isPending)
{
    TRACE("(%p, %p)\n", device, isPending);
    return pnvmlDeviceGetRetiredPagesPendingStatus
        ? pnvmlDeviceGetRetiredPagesPendingStatus(device, isPending)
        : NVML_ERROR_FUNCTION_NOT_FOUND;
}

nvmlReturn_t __cdecl nvmlDeviceGetRetiredPages_v2(nvmlDevice_t device, nvmlPageRetirementCause_t cause, unsigned int *pageCount, unsigned long long *addresses, unsigned long long *timestamps)
{
    TRACE("(%p, %u, %p, %p, %p)\n", device, cause, pageCount, addresses, timestamps);
    return pnvmlDeviceGetRetiredPages_v2
        ? pnvmlDeviceGetRetiredPages_v2(device, cause, pageCount, addresses, timestamps)
        : NVML_ERROR_FUNCTION_NOT_FOUND;
}

nvmlReturn_t __cdecl nvmlDeviceGetRowRemapperHistogram(nvmlDevice_t device, nvmlRowRemapperHistogramValues_t *values)
{
    TRACE("(%p, %p)\n", device, values);
    return pnvmlDeviceGetRowRemapperHistogram
        ? pnvmlDeviceGetRowRemapperHistogram(device, values)
        : NVML_ERROR_FUNCTION_NOT_FOUND;
}

nvmlReturn_t __cdecl nvmlDeviceGetSamples(nvmlDevice_t device, nvmlSamplingType_t type, unsigned long long lastSeenTimeStamp, nvmlValueType_t *sampleValType, unsigned int *sampleCount, nvmlSample_t *samples)
{
    TRACE("(%p, %u, %llu, %p, %p, %p)\n", device, type, lastSeenTimeStamp, sampleValType, sampleCount, samples);
    return pnvmlDeviceGetSamples
        ? pnvmlDeviceGetSamples(device, type, lastSeenTimeStamp, sampleValType, sampleCount, samples)
        : NVML_ERROR_FUNCTION_NOT_FOUND;
}

nvmlReturn_t __cdecl nvmlDeviceGetSerial(nvmlDevice_t device, char *serial, unsigned int length)
{
    TRACE("(%p, %p, %u)\n", device, serial, length);
    return pnvmlDeviceGetSerial
        ? pnvmlDeviceGetSerial(device, serial, length)
        : NVML_ERROR_FUNCTION_NOT_FOUND;
}

nvmlReturn_t __cdecl nvmlDeviceGetSupportedClocksThrottleReasons(nvmlDevice_t device, unsigned long long *supportedClocksThrottleReasons)
{
    TRACE("(%p, %p)\n", device, supportedClocksThrottleReasons);
    return pnvmlDeviceGetSupportedClocksThrottleReasons
        ? pnvmlDeviceGetSupportedClocksThrottleReasons(device, supportedClocksThrottleReasons)
        : NVML_ERROR_FUNCTION_NOT_FOUND;
}

nvmlReturn_t __cdecl nvmlDeviceGetSupportedEventTypes(nvmlDevice_t device, unsigned long long *eventTypes)
{
    WARN("(%p, %p): using Linux behavior\n", device, eventTypes);
    return pnvmlDeviceGetSupportedEventTypes
        ? pnvmlDeviceGetSupportedEventTypes(device, eventTypes)
        : NVML_ERROR_FUNCTION_NOT_FOUND;
}

nvmlReturn_t __cdecl nvmlDeviceGetSupportedGraphicsClocks(nvmlDevice_t device, unsigned int memoryClockMHz, unsigned int *count, unsigned int *clocksMHz)
{
    TRACE("(%p, %u, %p, %p)\n", device, memoryClockMHz, count, clocksMHz);
    return pnvmlDeviceGetSupportedGraphicsClocks
        ? pnvmlDeviceGetSupportedGraphicsClocks(device, memoryClockMHz, count, clocksMHz)
        : NVML_ERROR_FUNCTION_NOT_FOUND;
}

nvmlReturn_t __cdecl nvmlDeviceGetSupportedMemoryClocks(nvmlDevice_t device, unsigned int *count, unsigned int *clocksMHz)
{
    TRACE("(%p, %p, %p)\n", device, count, clocksMHz);
    return pnvmlDeviceGetSupportedMemoryClocks
        ? pnvmlDeviceGetSupportedMemoryClocks(device, count, clocksMHz)
        : NVML_ERROR_FUNCTION_NOT_FOUND;
}

nvmlReturn_t __cdecl nvmlDeviceGetSupportedVgpus(nvmlDevice_t device, unsigned int *vgpuCount, nvmlVgpuTypeId_t *vgpuTypeIds)
{
    TRACE("(%p, %p, %p)\n", device, vgpuCount, vgpuTypeIds);
    return pnvmlDeviceGetSupportedVgpus
        ? pnvmlDeviceGetSupportedVgpus(device, vgpuCount, vgpuTypeIds)
        : NVML_ERROR_FUNCTION_NOT_FOUND;
}

nvmlReturn_t __cdecl nvmlDeviceGetTemperature(nvmlDevice_t device, nvmlTemperatureSensors_t sensorType, unsigned int *temp)
{
    TRACE("(%p, %u, %p)\n", device, sensorType, temp);
    return pnvmlDeviceGetTemperature
        ? pnvmlDeviceGetTemperature(device, sensorType, temp)
        : NVML_ERROR_FUNCTION_NOT_FOUND;
}

nvmlReturn_t __cdecl nvmlDeviceGetTemperatureThreshold(nvmlDevice_t device, nvmlTemperatureThresholds_t thresholdType, unsigned int *temp)
{
    TRACE("(%p, %u, %p)\n", device, thresholdType, temp);
    return pnvmlDeviceGetTemperatureThreshold
        ? pnvmlDeviceGetTemperatureThreshold(device, thresholdType, temp)
        : NVML_ERROR_FUNCTION_NOT_FOUND;
}

nvmlReturn_t __cdecl nvmlDeviceGetTopologyCommonAncestor(nvmlDevice_t device1, nvmlDevice_t device2, nvmlGpuTopologyLevel_t *pathInfo)
{
    TRACE("(%p, %p, %p)\n", device1, device2, pathInfo);
    return NVML_ERROR_NOT_SUPPORTED;
}

nvmlReturn_t __cdecl nvmlDeviceGetTopologyNearestGpus(nvmlDevice_t device, nvmlGpuTopologyLevel_t level, unsigned int *count, nvmlDevice_t *deviceArray)
{
    TRACE("(%p, %u, %p, %p)\n", device, level, count, deviceArray);

    if (level != NVML_TOPOLOGY_INTERNAL &&
        level != NVML_TOPOLOGY_SINGLE &&
        level != NVML_TOPOLOGY_MULTIPLE &&
        level != NVML_TOPOLOGY_HOSTBRIDGE &&
        level != NVML_TOPOLOGY_NODE &&
        level != NVML_TOPOLOGY_SYSTEM)
    {
        return NVML_ERROR_INVALID_ARGUMENT;
    }

    if (!count || (*count && !deviceArray)) return NVML_ERROR_INVALID_ARGUMENT;

    unsigned int index;
    nvmlReturn_t ret = nvmlDeviceGetIndex(device, &index);

    return ret == NVML_SUCCESS ? NVML_ERROR_NOT_SUPPORTED : ret;
}

nvmlReturn_t __cdecl nvmlDeviceGetTotalEccErrors(nvmlDevice_t device, nvmlMemoryErrorType_t errorType, nvmlEccCounterType_t counterType, unsigned long long *eccCounts)
{
    TRACE("(%p, %u, %u, %p)\n", device, errorType, counterType, eccCounts);
    return pnvmlDeviceGetTotalEccErrors
        ? pnvmlDeviceGetTotalEccErrors(device, errorType, counterType, eccCounts)
        : NVML_ERROR_FUNCTION_NOT_FOUND;
}

nvmlReturn_t __cdecl nvmlDeviceGetTotalEnergyConsumption(nvmlDevice_t device, unsigned long long *energy)
{
    TRACE("(%p, %p)\n", device, energy);
    return pnvmlDeviceGetTotalEnergyConsumption
        ? pnvmlDeviceGetTotalEnergyConsumption(device, energy)
        : NVML_ERROR_FUNCTION_NOT_FOUND;
}

nvmlReturn_t __cdecl nvmlDeviceGetUUID(nvmlDevice_t device, char *uuid, unsigned int length)
{
    TRACE("(%p, %p, %u)\n", device, uuid, length);
    return pnvmlDeviceGetUUID
        ? pnvmlDeviceGetUUID(device, uuid, length)
        : NVML_ERROR_FUNCTION_NOT_FOUND;
}

nvmlReturn_t __cdecl nvmlDeviceGetUtilizationRates(nvmlDevice_t device, nvmlUtilization_t *utilization)
{
    TRACE("(%p, %p)\n", device, utilization);
    return pnvmlDeviceGetUtilizationRates
        ? pnvmlDeviceGetUtilizationRates(device, utilization)
        : NVML_ERROR_FUNCTION_NOT_FOUND;
}

nvmlReturn_t __cdecl nvmlDeviceGetVbiosVersion(nvmlDevice_t device, char *version, unsigned int length)
{
    TRACE("(%p, %p, %u)\n", device, version, length);
    return pnvmlDeviceGetVbiosVersion
        ? pnvmlDeviceGetVbiosVersion(device, version, length)
        : NVML_ERROR_FUNCTION_NOT_FOUND;
}

nvmlReturn_t __cdecl nvmlDeviceGetVgpuUtilization(nvmlDevice_t device, unsigned long long lastSeenTimeStamp, nvmlValueType_t *sampleValType, unsigned int *vgpuInstanceSamplesCount, nvmlVgpuInstanceUtilizationSample_t *utilizationSamples)
{
    TRACE("(%p, %llu, %p, %p, %p)\n", device, lastSeenTimeStamp, sampleValType, vgpuInstanceSamplesCount, utilizationSamples);
    return pnvmlDeviceGetVgpuUtilization
        ? pnvmlDeviceGetVgpuUtilization(device, lastSeenTimeStamp, sampleValType, vgpuInstanceSamplesCount, utilizationSamples)
        : NVML_ERROR_FUNCTION_NOT_FOUND;
}

nvmlReturn_t __cdecl nvmlDeviceGetViolationStatus(nvmlDevice_t device, nvmlPerfPolicyType_t perfPolicyType, nvmlViolationTime_t *violTime)
{
    TRACE("(%p, %u, %p)\n", device, perfPolicyType, violTime);
    return pnvmlDeviceGetViolationStatus
        ? pnvmlDeviceGetViolationStatus(device, perfPolicyType, violTime)
        : NVML_ERROR_FUNCTION_NOT_FOUND;
}

nvmlReturn_t __cdecl nvmlDeviceGetVirtualizationMode(nvmlDevice_t device, nvmlGpuVirtualizationMode_t *pVirtualMode)
{
    TRACE("(%p, %p)\n", device, pVirtualMode);
    return pnvmlDeviceGetVirtualizationMode
        ? pnvmlDeviceGetVirtualizationMode(device, pVirtualMode)
        : NVML_ERROR_FUNCTION_NOT_FOUND;
}

nvmlReturn_t __cdecl nvmlDeviceModifyDrainState(nvmlPciInfo_t *pciInfo, nvmlEnableState_t newState)
{
    TRACE("(%p, %u)\n", pciInfo, newState);

    if (!pciInfo || (newState != NVML_FEATURE_ENABLED && newState != NVML_FEATURE_DISABLED)) return NVML_ERROR_INVALID_ARGUMENT;

    unsigned int deviceCount;
    nvmlReturn_t ret = nvmlDeviceGetCount_v2(&deviceCount);

    return ret == NVML_SUCCESS ? NVML_ERROR_NOT_SUPPORTED : ret;
}

nvmlReturn_t __cdecl nvmlDeviceOnSameBoard(nvmlDevice_t device1, nvmlDevice_t device2, int *onSameBoard)
{
    TRACE("(%p, %p, %p)\n", device1, device2, onSameBoard);
    return pnvmlDeviceOnSameBoard
        ? pnvmlDeviceOnSameBoard(device1, device2, onSameBoard)
        : NVML_ERROR_FUNCTION_NOT_FOUND;
}

nvmlReturn_t __cdecl nvmlDeviceQueryDrainState(nvmlPciInfo_t *pciInfo, nvmlEnableState_t *currentState)
{
    TRACE("(%p, %p)\n", pciInfo, currentState);

    if (!pciInfo || !currentState) return NVML_ERROR_INVALID_ARGUMENT;

    unsigned int deviceCount;
    nvmlReturn_t ret = nvmlDeviceGetCount_v2(&deviceCount);

    return ret == NVML_SUCCESS ? NVML_ERROR_NOT_SUPPORTED : ret;
}

nvmlReturn_t __cdecl nvmlDeviceRegisterEvents(nvmlDevice_t device, unsigned long long eventTypes, nvmlEventSet_t set)
{
    WARN("(%p, %llu, %p): using Linux behavior\n", device, eventTypes, set);
    return pnvmlDeviceRegisterEvents
        ? pnvmlDeviceRegisterEvents(device, eventTypes, set)
        : NVML_ERROR_FUNCTION_NOT_FOUND;
}

nvmlReturn_t __cdecl nvmlDeviceRemoveGpu(nvmlPciInfo_t *pciInfo)
{
    TRACE("(%p)\n", pciInfo);

    if (!pciInfo) return NVML_ERROR_INVALID_ARGUMENT;

    unsigned int deviceCount;
    nvmlReturn_t ret = nvmlDeviceGetCount_v2(&deviceCount);

    return ret == NVML_SUCCESS ? NVML_ERROR_NOT_SUPPORTED : ret;
}

nvmlReturn_t __cdecl nvmlDeviceRemoveGpu_v2(nvmlPciInfo_t *pciInfo, nvmlDetachGpuState_t gpuState, nvmlPcieLinkState_t linkState)
{
    TRACE("(%p, %u, %u)\n", pciInfo, gpuState, linkState);

    if (!pciInfo || (gpuState != NVML_DETACH_GPU_KEEP && gpuState != NVML_DETACH_GPU_REMOVE) || (linkState != NVML_PCIE_LINK_KEEP && linkState != NVML_PCIE_LINK_SHUT_DOWN)) return NVML_ERROR_INVALID_ARGUMENT;

    unsigned int deviceCount;
    nvmlReturn_t ret = nvmlDeviceGetCount_v2(&deviceCount);

    return ret == NVML_SUCCESS ? NVML_ERROR_NOT_SUPPORTED : ret;
}

nvmlReturn_t __cdecl nvmlDeviceSetComputeMode(nvmlDevice_t device, nvmlComputeMode_t mode)
{
    TRACE("(%p, %u)\n", device, mode);
    return pnvmlDeviceSetComputeMode
        ? pnvmlDeviceSetComputeMode(device, mode)
        : NVML_ERROR_FUNCTION_NOT_FOUND;
}

nvmlReturn_t __cdecl nvmlDeviceSetCpuAffinity(nvmlDevice_t device)
{
    TRACE("(%p)\n", device);

    unsigned int index;
    nvmlReturn_t ret = nvmlDeviceGetIndex(device, &index);

    return ret == NVML_SUCCESS ? NVML_ERROR_NOT_SUPPORTED : ret;
}

nvmlReturn_t __cdecl nvmlDeviceSetDriverModel(nvmlDevice_t device, nvmlDriverModel_t driverModel, unsigned int flags)
{
    TRACE("(%p, %u, %u)\n", device, driverModel, flags);

    if (driverModel != NVML_DRIVER_WDDM && driverModel != NVML_DRIVER_WDM) return NVML_ERROR_INVALID_ARGUMENT;

    unsigned int index;
    nvmlReturn_t ret = nvmlDeviceGetIndex(device, &index);

    return ret == NVML_SUCCESS ? NVML_ERROR_NOT_SUPPORTED : ret;
}

nvmlReturn_t __cdecl nvmlDeviceSetPersistenceMode(nvmlDevice_t device, nvmlEnableState_t mode)
{
    TRACE("(%p, %u)\n", device, mode);

    if (!mode) return NVML_ERROR_INVALID_ARGUMENT;

    unsigned int index;
    nvmlReturn_t ret = nvmlDeviceGetIndex(device, &index);

    return ret == NVML_SUCCESS ? NVML_ERROR_NOT_SUPPORTED : ret;
}

nvmlReturn_t __cdecl nvmlEventSetCreate(nvmlEventSet_t *set)
{
    TRACE("(%p)\n", set);
    return pnvmlEventSetCreate
        ? pnvmlEventSetCreate(set)
        : NVML_ERROR_FUNCTION_NOT_FOUND;
}

nvmlReturn_t __cdecl nvmlEventSetFree(nvmlEventSet_t set)
{
    TRACE("(%p)\n", set);
    return pnvmlEventSetFree
        ? pnvmlEventSetFree(set)
        : NVML_ERROR_FUNCTION_NOT_FOUND;
}

nvmlReturn_t __cdecl nvmlEventSetWait(nvmlEventSet_t set, nvmlEventData_t *data, unsigned int timeoutms)
{
    WARN("(%p, %p, %u): using Linux behavior\n", set, data, timeoutms);
    return pnvmlEventSetWait
        ? pnvmlEventSetWait(set, data, timeoutms)
        : NVML_ERROR_FUNCTION_NOT_FOUND;
}

nvmlReturn_t __cdecl nvmlEventSetWait_v2(nvmlEventSet_t set, nvmlEventData_t *data, unsigned int timeoutms)
{
    WARN("(%p, %p, %u): using Linux behavior\n", set, data, timeoutms);
    return pnvmlEventSetWait_v2
        ? pnvmlEventSetWait_v2(set, data, timeoutms)
        : NVML_ERROR_FUNCTION_NOT_FOUND;
}

nvmlReturn_t __cdecl nvmlSystemGetTopologyGpuSet(unsigned int cpuNumber, unsigned int *count, nvmlDevice_t *deviceArray)
{
    TRACE("(%u, %p, %p)\n", cpuNumber, count, deviceArray);

    if (!count || (*count && !deviceArray)) return NVML_ERROR_INVALID_ARGUMENT;

    unsigned int deviceCount;
    nvmlReturn_t ret = nvmlDeviceGetCount_v2(&deviceCount);

    return ret == NVML_SUCCESS ? NVML_ERROR_NOT_SUPPORTED : ret;
}

static BOOL load_nvml(void)
{
    if (!(libnvidia_ml_handle = dlopen("libnvidia-ml.so.1", RTLD_NOW)))
    {
        ERR("Wine cannot find the libnvidia-ml.so library, NVIDIA Management Library support disabled.\n");
        return FALSE;
    }

    #define LOAD_FUNCPTR(f) if (!(*(void **)(&p##f) = dlsym(libnvidia_ml_handle, #f))) { ERR("Can't find symbol %s.\n", #f); goto fail; }

    LOAD_FUNCPTR(nvmlErrorString);
    LOAD_FUNCPTR(nvmlInit);
    LOAD_FUNCPTR(nvmlInitWithFlags);
    LOAD_FUNCPTR(nvmlInit_v2);
    LOAD_FUNCPTR(nvmlShutdown);
    LOAD_FUNCPTR(nvmlSystemGetCudaDriverVersion);
    LOAD_FUNCPTR(nvmlSystemGetCudaDriverVersion_v2);
    LOAD_FUNCPTR(nvmlSystemGetDriverVersion);
    LOAD_FUNCPTR(nvmlSystemGetNVMLVersion);

    #undef LOAD_FUNCPTR

    #define TRY_LOAD_FUNCPTR(f) if (!(*(void **)(&p##f) = dlsym(libnvidia_ml_handle, #f))) { WARN("Can't find symbol %s.\n", #f); }

    TRY_LOAD_FUNCPTR(nvmlDeviceGetAPIRestriction);
    TRY_LOAD_FUNCPTR(nvmlDeviceGetActiveVgpus);
    TRY_LOAD_FUNCPTR(nvmlDeviceGetApplicationsClock);
    TRY_LOAD_FUNCPTR(nvmlDeviceGetArchitecture);
    TRY_LOAD_FUNCPTR(nvmlDeviceGetAutoBoostedClocksEnabled);
    TRY_LOAD_FUNCPTR(nvmlDeviceGetBAR1MemoryInfo);
    TRY_LOAD_FUNCPTR(nvmlDeviceGetBoardId);
    TRY_LOAD_FUNCPTR(nvmlDeviceGetBoardPartNumber);
    TRY_LOAD_FUNCPTR(nvmlDeviceGetBrand);
    TRY_LOAD_FUNCPTR(nvmlDeviceGetBridgeChipInfo);
    TRY_LOAD_FUNCPTR(nvmlDeviceGetClock);
    TRY_LOAD_FUNCPTR(nvmlDeviceGetClockInfo);
    TRY_LOAD_FUNCPTR(nvmlDeviceGetComputeMode);
    TRY_LOAD_FUNCPTR(nvmlDeviceGetCount);
    TRY_LOAD_FUNCPTR(nvmlDeviceGetCount_v2);
    TRY_LOAD_FUNCPTR(nvmlDeviceGetCreatableVgpus);
    TRY_LOAD_FUNCPTR(nvmlDeviceGetCudaComputeCapability);
    TRY_LOAD_FUNCPTR(nvmlDeviceGetCurrPcieLinkGeneration);
    TRY_LOAD_FUNCPTR(nvmlDeviceGetCurrPcieLinkWidth);
    TRY_LOAD_FUNCPTR(nvmlDeviceGetCurrentClocksThrottleReasons);
    TRY_LOAD_FUNCPTR(nvmlDeviceGetDecoderUtilization);
    TRY_LOAD_FUNCPTR(nvmlDeviceGetDefaultApplicationsClock);
    TRY_LOAD_FUNCPTR(nvmlDeviceGetDetailedEccErrors);
    TRY_LOAD_FUNCPTR(nvmlDeviceGetDisplayActive);
    TRY_LOAD_FUNCPTR(nvmlDeviceGetDisplayMode);
    TRY_LOAD_FUNCPTR(nvmlDeviceGetEccMode);
    TRY_LOAD_FUNCPTR(nvmlDeviceGetEncoderCapacity);
    TRY_LOAD_FUNCPTR(nvmlDeviceGetEncoderStats);
    TRY_LOAD_FUNCPTR(nvmlDeviceGetEncoderUtilization);
    TRY_LOAD_FUNCPTR(nvmlDeviceGetEnforcedPowerLimit);
    TRY_LOAD_FUNCPTR(nvmlDeviceGetFanSpeed);
    TRY_LOAD_FUNCPTR(nvmlDeviceGetFanSpeed_v2);
    TRY_LOAD_FUNCPTR(nvmlDeviceGetFBCStats);
    TRY_LOAD_FUNCPTR(nvmlDeviceGetFieldValues);
    TRY_LOAD_FUNCPTR(nvmlDeviceGetGpuOperationMode);
    TRY_LOAD_FUNCPTR(nvmlDeviceGetGridLicensableFeatures);
    TRY_LOAD_FUNCPTR(nvmlDeviceGetGridLicensableFeatures_v2);
    TRY_LOAD_FUNCPTR(nvmlDeviceGetGridLicensableFeatures_v3);
    TRY_LOAD_FUNCPTR(nvmlDeviceGetHandleByIndex);
    TRY_LOAD_FUNCPTR(nvmlDeviceGetHandleByIndex_v2);
    TRY_LOAD_FUNCPTR(nvmlDeviceGetHandleByPciBusId);
    TRY_LOAD_FUNCPTR(nvmlDeviceGetHandleByPciBusId_v2);
    TRY_LOAD_FUNCPTR(nvmlDeviceGetHandleBySerial);
    TRY_LOAD_FUNCPTR(nvmlDeviceGetHandleByUUID);
    TRY_LOAD_FUNCPTR(nvmlDeviceGetHostVgpuMode);
    TRY_LOAD_FUNCPTR(nvmlDeviceGetIndex);
    TRY_LOAD_FUNCPTR(nvmlDeviceGetInforomConfigurationChecksum);
    TRY_LOAD_FUNCPTR(nvmlDeviceGetInforomImageVersion);
    TRY_LOAD_FUNCPTR(nvmlDeviceGetInforomVersion);
    TRY_LOAD_FUNCPTR(nvmlDeviceGetMaxClockInfo);
    TRY_LOAD_FUNCPTR(nvmlDeviceGetMaxPcieLinkGeneration);
    TRY_LOAD_FUNCPTR(nvmlDeviceGetMaxPcieLinkWidth);
    TRY_LOAD_FUNCPTR(nvmlDeviceGetMemoryErrorCounter);
    TRY_LOAD_FUNCPTR(nvmlDeviceGetMemoryInfo);
    TRY_LOAD_FUNCPTR(nvmlDeviceGetMigMode);
    TRY_LOAD_FUNCPTR(nvmlDeviceGetMultiGpuBoard);
    TRY_LOAD_FUNCPTR(nvmlDeviceGetName);
    TRY_LOAD_FUNCPTR(nvmlDeviceGetNvLinkCapability);
    TRY_LOAD_FUNCPTR(nvmlDeviceGetNvLinkErrorCounter);
    TRY_LOAD_FUNCPTR(nvmlDeviceGetNvLinkRemotePciInfo);
    TRY_LOAD_FUNCPTR(nvmlDeviceGetNvLinkRemotePciInfo_v2);
    TRY_LOAD_FUNCPTR(nvmlDeviceGetNvLinkState);
    TRY_LOAD_FUNCPTR(nvmlDeviceGetNvLinkUtilizationControl);
    TRY_LOAD_FUNCPTR(nvmlDeviceGetNvLinkUtilizationCounter);
    TRY_LOAD_FUNCPTR(nvmlDeviceGetNvLinkVersion);
    TRY_LOAD_FUNCPTR(nvmlDeviceGetP2PStatus);
    TRY_LOAD_FUNCPTR(nvmlDeviceGetPciInfo);
    TRY_LOAD_FUNCPTR(nvmlDeviceGetPciInfo_v2);
    TRY_LOAD_FUNCPTR(nvmlDeviceGetPciInfo_v3);
    TRY_LOAD_FUNCPTR(nvmlDeviceGetPcieReplayCounter);
    TRY_LOAD_FUNCPTR(nvmlDeviceGetPcieThroughput);
    TRY_LOAD_FUNCPTR(nvmlDeviceGetPerformanceState);
    TRY_LOAD_FUNCPTR(nvmlDeviceGetPgpuMetadataString);
    TRY_LOAD_FUNCPTR(nvmlDeviceGetPowerManagementDefaultLimit);
    TRY_LOAD_FUNCPTR(nvmlDeviceGetPowerManagementLimit);
    TRY_LOAD_FUNCPTR(nvmlDeviceGetPowerManagementLimitConstraints);
    TRY_LOAD_FUNCPTR(nvmlDeviceGetPowerManagementMode);
    TRY_LOAD_FUNCPTR(nvmlDeviceGetPowerState);
    TRY_LOAD_FUNCPTR(nvmlDeviceGetPowerUsage);
    TRY_LOAD_FUNCPTR(nvmlDeviceGetRemappedRows);
    TRY_LOAD_FUNCPTR(nvmlDeviceGetRetiredPages);
    TRY_LOAD_FUNCPTR(nvmlDeviceGetRetiredPagesPendingStatus);
    TRY_LOAD_FUNCPTR(nvmlDeviceGetRetiredPages_v2);
    TRY_LOAD_FUNCPTR(nvmlDeviceGetRowRemapperHistogram);
    TRY_LOAD_FUNCPTR(nvmlDeviceGetSamples);
    TRY_LOAD_FUNCPTR(nvmlDeviceGetSerial);
    TRY_LOAD_FUNCPTR(nvmlDeviceGetSupportedClocksThrottleReasons);
    TRY_LOAD_FUNCPTR(nvmlDeviceGetSupportedEventTypes);
    TRY_LOAD_FUNCPTR(nvmlDeviceGetSupportedGraphicsClocks);
    TRY_LOAD_FUNCPTR(nvmlDeviceGetSupportedMemoryClocks);
    TRY_LOAD_FUNCPTR(nvmlDeviceGetSupportedVgpus);
    TRY_LOAD_FUNCPTR(nvmlDeviceGetTemperature);
    TRY_LOAD_FUNCPTR(nvmlDeviceGetTemperatureThreshold);
    TRY_LOAD_FUNCPTR(nvmlDeviceGetTotalEccErrors);
    TRY_LOAD_FUNCPTR(nvmlDeviceGetTotalEnergyConsumption);
    TRY_LOAD_FUNCPTR(nvmlDeviceGetUUID);
    TRY_LOAD_FUNCPTR(nvmlDeviceGetUtilizationRates);
    TRY_LOAD_FUNCPTR(nvmlDeviceGetVbiosVersion);
    TRY_LOAD_FUNCPTR(nvmlDeviceGetVgpuUtilization);
    TRY_LOAD_FUNCPTR(nvmlDeviceGetViolationStatus);
    TRY_LOAD_FUNCPTR(nvmlDeviceGetVirtualizationMode);
    TRY_LOAD_FUNCPTR(nvmlDeviceOnSameBoard);
    TRY_LOAD_FUNCPTR(nvmlDeviceRegisterEvents);
    TRY_LOAD_FUNCPTR(nvmlDeviceSetComputeMode);
    TRY_LOAD_FUNCPTR(nvmlEventSetCreate);
    TRY_LOAD_FUNCPTR(nvmlEventSetFree);
    TRY_LOAD_FUNCPTR(nvmlEventSetWait);
    TRY_LOAD_FUNCPTR(nvmlEventSetWait_v2);

    #undef TRY_LOAD_FUNCPTR

    return TRUE;

fail:
    dlclose(libnvidia_ml_handle);
    return FALSE;
}

BOOL WINAPI DllMain(HINSTANCE instance, DWORD reason, LPVOID reserved)
{
    TRACE("(%p, %u, %p)\n", instance, reason, reserved);

    switch (reason)
    {
        case DLL_PROCESS_ATTACH:
            DisableThreadLibraryCalls(instance);
            if (!load_nvml()) return FALSE;
            break;
        case DLL_PROCESS_DETACH:
            if (reserved) break;
            if (libnvidia_ml_handle) dlclose(libnvidia_ml_handle);
            break;
    }

    return TRUE;
}
