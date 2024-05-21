@ stdcall cufftCreate(ptr) wine_cufftCreate
@ stub cufftDebug
@ stdcall cufftDestroy(ptr) wine_cufftDestroy
@ stdcall cufftEstimate1d(long ptr long ptr) wine_cufftEstimate1d
@ stdcall cufftEstimate2d(long long ptr ptr) wine_cufftEstimate2d
@ stdcall cufftEstimate3d(long long long ptr ptr) wine_cufftEstimate3d
@ stdcall cufftEstimateMany(long ptr ptr long long ptr long long ptr long ptr) wine_cufftEstimateMany
@ stdcall cufftExecC2C(ptr ptr ptr long) wine_cufftExecC2C
@ stdcall cufftExecR2C(ptr ptr ptr) wine_cufftExecR2C
@ stdcall cufftExecC2R(ptr ptr ptr) wine_cufftExecC2R
@ stdcall cufftExecZ2Z(ptr ptr ptr long) wine_cufftExecZ2Z
@ stdcall cufftExecD2Z(ptr ptr ptr) wine_cufftExecD2Z
@ stdcall cufftExecZ2D(ptr ptr ptr) wine_cufftExecZ2D
@ stdcall cufftGetPlanPropertyInt64(ptr ptr ptr) wine_cufftGetPlanPropertyInt64
@ stdcall cufftGetProperty(ptr ptr) wine_cufftGetProperty
@ stdcall cufftGetSize(ptr ptr) wine_cufftGetSize
@ stdcall cufftGetSize1d(ptr long ptr long ptr) wine_cufftGetSize1d
@ stdcall cufftGetSize2d(ptr long long ptr long ptr) wine_cufftGetSize2d
@ stdcall cufftGetSize3d(ptr long long long ptr long ptr) wine_cufftGetSize3d
@ stdcall cufftGetSizeMany(ptr long ptr ptr long long ptr ptr long ptr long ptr) wine_cufftGetSizeMany
@ stdcall cufftGetSizeMany64(ptr long long ptr ptr long long ptr long long ptr ptr long long ptr) wine_cufftGetSizeMany64
@ stdcall cufftGetVersion(ptr) wine_cufftGetVersion
@ stdcall cufftMakePlan1d(ptr long ptr long ptr) wine_cufftMakePlan1d
@ stdcall cufftMakePlan2d(ptr long long ptr ptr) wine_cufftMakePlan2d
@ stdcall cufftMakePlan3d(ptr long long long ptr ptr) wine_cufftMakePlan3d
@ stdcall cufftMakePlanMany(ptr long ptr ptr long long ptr ptr long ptr long ptr) wine_cufftMakePlanMany
@ stdcall cufftMakePlanMany64(ptr long ptr ptr long long ptr ptr long long ptr long long ptr) wine_cufftMakePlanMany64
@ stdcall cufftPlan1d(ptr long ptr long) wine_cufftPlan1d
@ stdcall cufftPlan2d(ptr long long ptr) wine_cufftPlan2d
@ stdcall cufftPlan3d(ptr long long long ptr) wine_cufftPlan3d
@ stdcall cufftPlanMany(ptr long ptr ptr long long ptr ptr long ptr long ptr) wine_cufftPlanMany
@ stdcall cufftResetPlanProperty(ptr ptr) wine_cufftResetPlanProperty
@ stdcall cufftSetAutoAllocation(ptr long) wine_cufftSetAutoAllocation
@ stdcall cufftSetPlanPropertyInt64(ptr ptr long long) wine_cufftSetPlanPropertyInt64
@ stdcall cufftSetStream(ptr ptr) wine_cufftSetStream
@ stdcall cufftSetWorkArea(ptr ptr) wine_cufftSetWorkArea
@ stdcall cufftXtClearCallback(ptr ptr) wine_cufftXtClearCallback
@ stdcall cufftXtExec(ptr ptr ptr long) wine_cufftXtExec
@ stdcall cufftXtExecDescriptor(ptr ptr ptr long) wine_cufftXtExecDescriptor
@ stdcall cufftXtExecDescriptorC2C(ptr ptr ptr long) wine_cufftXtExecDescriptorC2C
@ stdcall cufftXtExecDescriptorC2R(ptr ptr ptr) wine_cufftXtExecDescriptorC2R
@ stdcall cufftXtExecDescriptorD2Z(ptr ptr ptr) wine_cufftXtExecDescriptorD2Z
@ stdcall cufftXtExecDescriptorR2C(ptr ptr ptr) wine_cufftXtExecDescriptorR2C
@ stdcall cufftXtExecDescriptorZ2D(ptr ptr ptr) wine_cufftXtExecDescriptorZ2D
@ stdcall cufftXtExecDescriptorZ2Z(ptr ptr ptr long) wine_cufftXtExecDescriptorZ2Z
@ stdcall cufftXtFree(ptr) wine_cufftXtFree
@ stub cufftXtMakePlanGuru64
@ stdcall cufftXtGetSizeMany(ptr long long ptr ptr long long long ptr long long long ptr long long ptr ptr) wine_cufftXtGetSizeMany
@ stdcall cufftXtMakePlanMany(ptr long long ptr ptr long long long ptr ptr long long long ptr long long ptr ptr) wine_cufftXtMakePlanMany
@ stdcall cufftXtMalloc(ptr ptr ptr) wine_cufftXtMalloc
@ stdcall cufftXtMemcpy(ptr ptr ptr ptr) wine_cufftXtMemcpy
@ stdcall cufftXtQueryPlan(ptr ptr ptr) wine_cufftXtQueryPlan
@ stdcall cufftXtSetCallback(ptr ptr ptr ptr) wine_cufftXtSetCallback
@ stdcall cufftXtSetCallbackSharedSize(ptr ptr ptr) wine_cufftXtSetCallbackSharedSize
@ stdcall cufftXtSetGPUs(ptr long ptr) wine_cufftXtSetGPUs
@ stdcall cufftXtSetWorkArea(ptr ptr) wine_cufftXtSetWorkArea
@ stdcall cufftXtSetWorkAreaPolicy(ptr ptr ptr) wine_cufftXtSetWorkAreaPolicy
