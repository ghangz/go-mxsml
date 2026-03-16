// "Copyright (c) 2026 MetaX Integrated Circuits (Shanghai) Co., Ltd. All rights reserved."
package mxsmlextension

var (
	Init                                     = extensionWrapper.Init
	ShutDown                                 = extensionWrapper.ShutDown
	ErrorString                              = extensionWrapper.ErrorString
	DeviceGetCount                           = extensionWrapper.DeviceGetCount
	SystemGetDriverVersion                   = extensionWrapper.SystemGetDriverVersion
	SystemGetNVMLVersion                     = extensionWrapper.SystemGetNVMLVersion
	DeviceGetHandleByIndex                   = extensionWrapper.DeviceGetHandleByIndex
	DeviceGetHandleByUUID                    = extensionWrapper.DeviceGetHandleByUUID
	DeviceGetHandleByPciBusId                = extensionWrapper.DeviceGetHandleByPciBusId
	DeviceGetName                            = extensionWrapper.DeviceGetName
	DeviceGetUUID                            = extensionWrapper.DeviceGetUUID
	DeviceGetPciInfo                         = extensionWrapper.DeviceGetPciInfo
	DeviceGetMemoryInfo                      = extensionWrapper.DeviceGetMemoryInfo
	DeviceGetFanSpeed                        = extensionWrapper.DeviceGetFanSpeed
	DeviceGetFanSpeed_v2                     = extensionWrapper.DeviceGetFanSpeed_v2
	DeviceGetUtilizationRates                = extensionWrapper.DeviceGetUtilizationRates
	DeviceGetMinorNumber                     = extensionWrapper.DeviceGetMinorNumber
	DeviceGetNvLinkState                     = extensionWrapper.DeviceGetNvLinkState
	DeviceGetNvLinkRemotePciInfo             = extensionWrapper.DeviceGetNvLinkRemotePciInfo
	DeviceGetTemperature                     = extensionWrapper.DeviceGetTemperature
	DeviceGetCurrPcieLinkWidth               = extensionWrapper.DeviceGetCurrPcieLinkWidth
	DeviceGetComputeRunningProcesses         = extensionWrapper.DeviceGetComputeRunningProcesses
	DeviceGetCudaComputeCapability           = extensionWrapper.DeviceGetCudaComputeCapability
	DeviceGetPowerUsage                      = extensionWrapper.DeviceGetPowerUsage
	DeviceGetPowerManagementLimit            = extensionWrapper.DeviceGetPowerManagementLimit
	DeviceGetMaxPcieLinkWidth                = extensionWrapper.DeviceGetMaxPcieLinkWidth
	DeviceGetPcieThroughput                  = extensionWrapper.DeviceGetPcieThroughput
	DeviceGetTemperatureThreshold            = extensionWrapper.DeviceGetTemperatureThreshold
	DeviceGetClockInfo                       = extensionWrapper.DeviceGetClockInfo
	DeviceGetCurrentClocksThrottleReasons    = extensionWrapper.DeviceGetCurrentClocksThrottleReasons
	DeviceGetSupportedClocksThrottleReasons  = extensionWrapper.DeviceGetSupportedClocksThrottleReasons
	DeviceGetCpuAffinity                     = extensionWrapper.DeviceGetCpuAffinity
	DeviceGetSupportedMemoryClocks           = extensionWrapper.DeviceGetSupportedMemoryClocks
	DeviceGetSupportedGraphicsClocks         = extensionWrapper.DeviceGetSupportedGraphicsClocks
	DeviceSetApplicationsClocks              = extensionWrapper.DeviceSetApplicationsClocks
	DeviceResetApplicationsClocks            = extensionWrapper.DeviceResetApplicationsClocks
	DeviceGetApplicationsClock               = extensionWrapper.DeviceGetApplicationsClock
	DeviceGetP2PStatus                       = extensionWrapper.DeviceGetP2PStatus
	DeviceGetPerformanceState                = extensionWrapper.DeviceGetPerformanceState
	DeviceSetAutoBoostedClocksEnabled        = extensionWrapper.DeviceSetAutoBoostedClocksEnabled
	DeviceGetAutoBoostedClocksEnabled        = extensionWrapper.DeviceGetAutoBoostedClocksEnabled
	DeviceGetTopologyCommonAncestor          = extensionWrapper.DeviceGetTopologyCommonAncestor
	DeviceGetNvLinkRemoteDeviceType          = extensionWrapper.DeviceGetNvLinkRemoteDeviceType
	DeviceGetFieldValues                     = extensionWrapper.DeviceGetFieldValues
)

type Device interface {
	GetUUID() (string, Return)
	GetName() (string, Return)
	GetPciInfo() (PciInfo, Return)
	GetMemoryInfo() (Memory, Return)
	GetFanSpeed() (uint32, Return)
	GetFanSpeed_v2(int) (uint32, Return)
	GetUtilizationRates() (Utilization, Return)
	GetMinorNumber()(int, Return)
	GetNvLinkState(int) (EnableState, Return)
	GetNvLinkRemotePciInfo(int) (PciInfo, Return)
	GetTemperature(TemperatureSensors) (uint32, Return)
	GetCurrPcieLinkWidth() (int, Return)
	GetComputeRunningProcesses() ([]ProcessInfo, Return)
	GetCudaComputeCapability() (int, int, Return)
	GetPowerUsage() (uint32, Return)
	GetPowerManagementLimit() (uint32, Return)
	GetMaxPcieLinkWidth() (int, Return)
	GetPcieThroughput(PcieUtilCounter) (uint32, Return)
	GetTemperatureThreshold(TemperatureThresholds) (uint32, Return)
	GetClockInfo(ClockType) (uint32, Return)
	GetCurrentClocksThrottleReasons() (uint64, Return)
	GetSupportedClocksThrottleReasons() (uint64, Return)
	GetCpuAffinity(int) ([]uint, Return)
	GetSupportedMemoryClocks() (int, []uint32, Return)
	GetSupportedGraphicsClocks(int) (int, []uint32, Return)
	SetApplicationsClocks(uint32, uint32) Return
	ResetApplicationsClocks() Return
	GetApplicationsClock(ClockType) (uint32, Return)
	GetP2PStatus(Device, GpuP2PCapsIndex) (GpuP2PStatus, Return)
	GetPerformanceState() (Pstates, Return)
	SetAutoBoostedClocksEnabled(EnableState) Return
	GetAutoBoostedClocksEnabled() (EnableState, EnableState, Return)
	GetTopologyCommonAncestor(Device) (GpuTopologyLevel, Return)
	GetNvLinkRemoteDeviceType(int) (IntNvLinkDeviceType, Return)
	GetFieldValues([]FieldValue) Return
}
