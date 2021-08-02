# @ stub nvmlComputeInstanceDestroy
# @ stub nvmlComputeInstanceGetInfo
# @ stub nvmlComputeInstanceGetInfo_v2
# @ stub nvmlDeviceClearAccountingPids
@ cdecl nvmlDeviceClearCpuAffinity(ptr)
# @ stub nvmlDeviceClearEccErrorCounts
# @ stub nvmlDeviceCreateGpuInstance
# @ stub nvmlDeviceCreateGpuInstanceWithPlacement
@ cdecl nvmlDeviceDiscoverGpus(ptr)
# @ stub nvmlDeviceFreezeNvLinkUtilizationCounter
@ cdecl nvmlDeviceGetAPIRestriction(ptr long ptr)
# @ stub nvmlDeviceGetAccountingBufferSize
# @ stub nvmlDeviceGetAccountingMode
# @ stub nvmlDeviceGetAccountingPids
# @ stub nvmlDeviceGetAccountingStats
@ cdecl nvmlDeviceGetActiveVgpus(ptr ptr ptr)
@ cdecl nvmlDeviceGetApplicationsClock(ptr long ptr)
@ cdecl nvmlDeviceGetArchitecture(ptr ptr)
# @ stub nvmlDeviceGetAttributes
# @ stub nvmlDeviceGetAttributes_v2
@ cdecl nvmlDeviceGetAutoBoostedClocksEnabled(ptr ptr ptr)
@ cdecl nvmlDeviceGetBAR1MemoryInfo(ptr ptr)
@ cdecl nvmlDeviceGetBoardId(ptr ptr)
@ cdecl nvmlDeviceGetBoardPartNumber(ptr ptr long)
@ cdecl nvmlDeviceGetBrand(ptr ptr)
@ cdecl nvmlDeviceGetBridgeChipInfo(ptr ptr)
@ cdecl nvmlDeviceGetClock(ptr long long ptr)
@ cdecl nvmlDeviceGetClockInfo(ptr long ptr)
# @ stub nvmlDeviceGetComputeInstanceId
@ cdecl nvmlDeviceGetComputeMode(ptr ptr)
# @ stub nvmlDeviceGetComputeRunningProcesses
# @ stub nvmlDeviceGetComputeRunningProcesses_v2
@ cdecl nvmlDeviceGetCount(ptr)
@ cdecl nvmlDeviceGetCount_v2(ptr)
@ cdecl nvmlDeviceGetCpuAffinity(ptr long ptr)
@ cdecl nvmlDeviceGetCpuAffinityWithinScope(ptr long ptr long)
@ cdecl nvmlDeviceGetCreatableVgpus(ptr ptr ptr)
@ cdecl nvmlDeviceGetCudaComputeCapability(ptr ptr ptr)
@ cdecl nvmlDeviceGetCurrPcieLinkGeneration(ptr ptr)
@ cdecl nvmlDeviceGetCurrPcieLinkWidth(ptr ptr)
@ cdecl nvmlDeviceGetCurrentClocksThrottleReasons(ptr ptr)
@ cdecl nvmlDeviceGetDecoderUtilization(ptr ptr ptr)
@ cdecl nvmlDeviceGetDefaultApplicationsClock(ptr long ptr)
@ cdecl nvmlDeviceGetDetailedEccErrors(ptr long long ptr)
# @ stub nvmlDeviceGetDeviceHandleFromMigDeviceHandle
@ cdecl nvmlDeviceGetDisplayActive(ptr ptr)
@ cdecl nvmlDeviceGetDisplayMode(ptr ptr)
@ cdecl nvmlDeviceGetDriverModel(ptr ptr ptr)
@ cdecl nvmlDeviceGetEccMode(ptr ptr ptr)
@ cdecl nvmlDeviceGetEncoderCapacity(ptr long ptr)
# @ stub nvmlDeviceGetEncoderSessions
@ cdecl nvmlDeviceGetEncoderStats(ptr ptr ptr ptr)
@ cdecl nvmlDeviceGetEncoderUtilization(ptr ptr ptr)
@ cdecl nvmlDeviceGetEnforcedPowerLimit(ptr ptr)
# @ stub nvmlDeviceGetFBCSessions
@ cdecl nvmlDeviceGetFBCStats(ptr ptr)
@ cdecl nvmlDeviceGetFanSpeed(ptr ptr)
@ cdecl nvmlDeviceGetFanSpeed_v2(ptr long ptr)
@ cdecl nvmlDeviceGetFieldValues(ptr long ptr)
# @ stub nvmlDeviceGetGpuInstanceById
# @ stub nvmlDeviceGetGpuInstanceId
# @ stub nvmlDeviceGetGpuInstancePossiblePlacements
# @ stub nvmlDeviceGetGpuInstanceProfileInfo
# @ stub nvmlDeviceGetGpuInstanceRemainingCapacity
# @ stub nvmlDeviceGetGpuInstances
@ cdecl nvmlDeviceGetGpuOperationMode(ptr ptr ptr)
# @ stub nvmlDeviceGetGraphicsRunningProcesses
# @ stub nvmlDeviceGetGraphicsRunningProcesses_v2
@ cdecl nvmlDeviceGetGridLicensableFeatures(ptr ptr)
@ cdecl nvmlDeviceGetGridLicensableFeatures_v2(ptr ptr)
@ cdecl nvmlDeviceGetGridLicensableFeatures_v3(ptr ptr)
@ cdecl nvmlDeviceGetHandleByIndex(long ptr)
@ cdecl nvmlDeviceGetHandleByIndex_v2(long ptr)
@ cdecl nvmlDeviceGetHandleByPciBusId(str ptr)
@ cdecl nvmlDeviceGetHandleByPciBusId_v2(str ptr)
@ cdecl nvmlDeviceGetHandleBySerial(str ptr)
@ cdecl nvmlDeviceGetHandleByUUID(str ptr)
@ cdecl nvmlDeviceGetHostVgpuMode(ptr ptr)
@ cdecl nvmlDeviceGetIndex(ptr ptr)
@ cdecl nvmlDeviceGetInforomConfigurationChecksum(ptr ptr)
@ cdecl nvmlDeviceGetInforomImageVersion(ptr ptr long)
@ cdecl nvmlDeviceGetInforomVersion(ptr long ptr long)
# @ stub nvmlDeviceGetMPSComputeRunningProcesses
@ cdecl nvmlDeviceGetMaxClockInfo(ptr long ptr)
# @ stub nvmlDeviceGetMaxCustomerBoostClock
# @ stub nvmlDeviceGetMaxMigDeviceCount
@ cdecl nvmlDeviceGetMaxPcieLinkGeneration(ptr ptr)
@ cdecl nvmlDeviceGetMaxPcieLinkWidth(ptr ptr)
@ cdecl nvmlDeviceGetMemoryAffinity(ptr long ptr long)
@ cdecl nvmlDeviceGetMemoryErrorCounter(ptr long long long ptr)
@ cdecl nvmlDeviceGetMemoryInfo(ptr ptr)
# @ stub nvmlDeviceGetMigDeviceHandleByIndex
@ cdecl nvmlDeviceGetMigMode(ptr ptr ptr)
@ cdecl nvmlDeviceGetMinorNumber(ptr ptr)
@ cdecl nvmlDeviceGetMultiGpuBoard(ptr ptr)
@ cdecl nvmlDeviceGetName(ptr ptr long)
@ cdecl nvmlDeviceGetNvLinkCapability(ptr long long ptr)
@ cdecl nvmlDeviceGetNvLinkErrorCounter(ptr long long ptr)
# @ stub nvmlDeviceGetNvLinkRemotePciInfo
@ cdecl nvmlDeviceGetNvLinkRemotePciInfo_v2(ptr long ptr)
@ cdecl nvmlDeviceGetNvLinkState(ptr long ptr)
@ cdecl nvmlDeviceGetNvLinkUtilizationControl(ptr long long ptr)
@ cdecl nvmlDeviceGetNvLinkUtilizationCounter(ptr long long ptr ptr)
@ cdecl nvmlDeviceGetNvLinkVersion(ptr long ptr)
@ cdecl nvmlDeviceGetP2PStatus(ptr ptr long ptr)
@ cdecl nvmlDeviceGetPciInfo(ptr ptr)
@ cdecl nvmlDeviceGetPciInfo_v2(ptr ptr)
@ cdecl nvmlDeviceGetPciInfo_v3(ptr ptr)
@ cdecl nvmlDeviceGetPcieReplayCounter(ptr ptr)
@ cdecl nvmlDeviceGetPcieThroughput(ptr long ptr)
@ cdecl nvmlDeviceGetPerformanceState(ptr ptr)
@ cdecl nvmlDeviceGetPersistenceMode(ptr ptr)
@ cdecl nvmlDeviceGetPgpuMetadataString(ptr ptr ptr)
@ cdecl nvmlDeviceGetPowerManagementDefaultLimit(ptr ptr)
@ cdecl nvmlDeviceGetPowerManagementLimit(ptr ptr)
@ cdecl nvmlDeviceGetPowerManagementLimitConstraints(ptr ptr ptr)
@ cdecl nvmlDeviceGetPowerManagementMode(ptr ptr)
@ cdecl nvmlDeviceGetPowerState(ptr ptr)
@ cdecl nvmlDeviceGetPowerUsage(ptr ptr)
# @ stub nvmlDeviceGetProcessUtilization
@ cdecl nvmlDeviceGetRemappedRows(ptr ptr ptr ptr ptr)
@ cdecl nvmlDeviceGetRetiredPages(ptr long ptr ptr)
@ cdecl nvmlDeviceGetRetiredPagesPendingStatus(ptr ptr)
@ cdecl nvmlDeviceGetRetiredPages_v2(ptr long ptr ptr ptr)
@ cdecl nvmlDeviceGetRowRemapperHistogram(ptr ptr)
@ cdecl nvmlDeviceGetSamples(ptr long int64 ptr ptr ptr)
@ cdecl nvmlDeviceGetSerial(ptr ptr long)
@ cdecl nvmlDeviceGetSupportedClocksThrottleReasons(ptr ptr)
@ cdecl nvmlDeviceGetSupportedEventTypes(ptr ptr)
@ cdecl nvmlDeviceGetSupportedGraphicsClocks(ptr long ptr ptr)
@ cdecl nvmlDeviceGetSupportedMemoryClocks(ptr ptr ptr)
@ cdecl nvmlDeviceGetSupportedVgpus(ptr ptr ptr)
@ cdecl nvmlDeviceGetTemperature(ptr long ptr)
@ cdecl nvmlDeviceGetTemperatureThreshold(ptr long ptr)
@ cdecl nvmlDeviceGetTopologyCommonAncestor(ptr ptr ptr)
@ cdecl nvmlDeviceGetTopologyNearestGpus(ptr long ptr ptr)
@ cdecl nvmlDeviceGetTotalEccErrors(ptr long long ptr)
@ cdecl nvmlDeviceGetTotalEnergyConsumption(ptr ptr)
@ cdecl nvmlDeviceGetUUID(ptr ptr long)
@ cdecl nvmlDeviceGetUtilizationRates(ptr ptr)
@ cdecl nvmlDeviceGetVbiosVersion(ptr ptr long)
# @ stub nvmlDeviceGetVgpuMetadata
# @ stub nvmlDeviceGetVgpuProcessUtilization
@ cdecl nvmlDeviceGetVgpuUtilization(ptr int64 ptr ptr ptr)
@ cdecl nvmlDeviceGetViolationStatus(ptr long ptr)
@ cdecl nvmlDeviceGetVirtualizationMode(ptr ptr)
# @ stub nvmlDeviceIsMigDeviceHandle
@ cdecl nvmlDeviceModifyDrainState(ptr long)
@ cdecl nvmlDeviceOnSameBoard(ptr ptr ptr)
@ cdecl nvmlDeviceQueryDrainState(ptr ptr)
@ cdecl nvmlDeviceRegisterEvents(ptr int64 ptr)
@ cdecl nvmlDeviceRemoveGpu(ptr)
@ cdecl nvmlDeviceRemoveGpu_v2(ptr long long)
# @ stub nvmlDeviceResetApplicationsClocks
# @ stub nvmlDeviceResetGpuLockedClocks
# @ stub nvmlDeviceResetMemoryLockedClocks
# @ stub nvmlDeviceResetNvLinkErrorCounters
# @ stub nvmlDeviceResetNvLinkUtilizationCounter
# @ stub nvmlDeviceSetAPIRestriction
# @ stub nvmlDeviceSetAccountingMode
# @ stub nvmlDeviceSetApplicationsClocks
# @ stub nvmlDeviceSetAutoBoostedClocksEnabled
@ cdecl nvmlDeviceSetComputeMode(ptr long)
@ cdecl nvmlDeviceSetCpuAffinity(ptr)
# @ stub nvmlDeviceSetDefaultAutoBoostedClocksEnabled
@ cdecl nvmlDeviceSetDriverModel(ptr long long)
# @ stub nvmlDeviceSetEccMode
# @ stub nvmlDeviceSetGpuLockedClocks
# @ stub nvmlDeviceSetGpuOperationMode
# @ stub nvmlDeviceSetMemoryLockedClocks
# @ stub nvmlDeviceSetMigMode
# @ stub nvmlDeviceSetNvLinkUtilizationControl
@ cdecl nvmlDeviceSetPersistenceMode(ptr long)
# @ stub nvmlDeviceSetPowerManagementLimit
# @ stub nvmlDeviceSetTemperatureThreshold
# @ stub nvmlDeviceSetVirtualizationMode
# @ stub nvmlDeviceValidateInforom
@ cdecl nvmlErrorString(long)
@ cdecl nvmlEventSetCreate(ptr)
@ cdecl nvmlEventSetFree(ptr)
@ cdecl nvmlEventSetWait(ptr long long)
@ cdecl nvmlEventSetWait_v2(ptr ptr long)
# @ stub nvmlGetBlacklistDeviceCount
# @ stub nvmlGetBlacklistDeviceInfoByIndex
# @ stub nvmlGetExcludedDeviceCount
# @ stub nvmlGetExcludedDeviceInfoByIndex
# @ stub nvmlGetVgpuCompatibility
# @ stub nvmlGetVgpuVersion
# @ stub nvmlGpuInstanceCreateComputeInstance
# @ stub nvmlGpuInstanceDestroy
# @ stub nvmlGpuInstanceGetComputeInstanceById
# @ stub nvmlGpuInstanceGetComputeInstanceProfileInfo
# @ stub nvmlGpuInstanceGetComputeInstanceRemainingCapacity
# @ stub nvmlGpuInstanceGetComputeInstances
# @ stub nvmlGpuInstanceGetInfo
@ cdecl nvmlInit()
@ cdecl nvmlInitWithFlags(long)
@ cdecl nvmlInit_v2()
@ cdecl nvmlInternalGetExportTable(ptr ptr)
# @ stub nvmlSetVgpuVersion
@ cdecl nvmlShutdown()
@ cdecl nvmlSystemGetCudaDriverVersion(ptr)
@ cdecl nvmlSystemGetCudaDriverVersion_v2(ptr)
@ cdecl nvmlSystemGetDriverVersion(ptr long)
# @ stub nvmlSystemGetHicVersion
@ cdecl nvmlSystemGetNVMLVersion(ptr long)
# @ stub nvmlSystemGetProcessName
@ cdecl nvmlSystemGetTopologyGpuSet(long ptr ptr)
# @ stub nvmlUnitGetCount
# @ stub nvmlUnitGetDevices
# @ stub nvmlUnitGetFanSpeedInfo
# @ stub nvmlUnitGetHandleByIndex
# @ stub nvmlUnitGetLedState
# @ stub nvmlUnitGetPsuInfo
# @ stub nvmlUnitGetTemperature
# @ stub nvmlUnitGetUnitInfo
# @ stub nvmlUnitSetLedState
# @ stub nvmlVgpuInstanceClearAccountingPids
# @ stub nvmlVgpuInstanceGetAccountingMode
# @ stub nvmlVgpuInstanceGetAccountingPids
# @ stub nvmlVgpuInstanceGetAccountingStats
# @ stub nvmlVgpuInstanceGetEccMode
# @ stub nvmlVgpuInstanceGetEncoderCapacity
# @ stub nvmlVgpuInstanceGetEncoderSessions
# @ stub nvmlVgpuInstanceGetEncoderStats
# @ stub nvmlVgpuInstanceGetFBCSessions
# @ stub nvmlVgpuInstanceGetFBCStats
# @ stub nvmlVgpuInstanceGetFbUsage
# @ stub nvmlVgpuInstanceGetFrameRateLimit
# @ stub nvmlVgpuInstanceGetGpuInstanceId
# @ stub nvmlVgpuInstanceGetLicenseStatus
# @ stub nvmlVgpuInstanceGetMdevUUID
# @ stub nvmlVgpuInstanceGetMetadata
# @ stub nvmlVgpuInstanceGetType
# @ stub nvmlVgpuInstanceGetUUID
# @ stub nvmlVgpuInstanceGetVmDriverVersion
# @ stub nvmlVgpuInstanceGetVmID
# @ stub nvmlVgpuInstanceSetEncoderCapacity
# @ stub nvmlVgpuTypeGetClass
# @ stub nvmlVgpuTypeGetDeviceID
# @ stub nvmlVgpuTypeGetFrameRateLimit
# @ stub nvmlVgpuTypeGetFramebufferSize
# @ stub nvmlVgpuTypeGetGpuInstanceProfileId
# @ stub nvmlVgpuTypeGetLicense
# @ stub nvmlVgpuTypeGetMaxInstances
# @ stub nvmlVgpuTypeGetMaxInstancesPerVm
# @ stub nvmlVgpuTypeGetName
# @ stub nvmlVgpuTypeGetNumDisplayHeads
# @ stub nvmlVgpuTypeGetResolution