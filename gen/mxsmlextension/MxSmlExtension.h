/*** MXSML VERSION: 2.3.1 ***/
/**
 * Copyright © 2022 MetaX Integrated Circuits (Shanghai) Co., Ltd. All Rights Reserved.
 *
 * This software and associated documentation files (hereinafter collectively referred to as
 * "Software") is a proprietary commercial software developed by MetaX Integrated Circuits
 * (Shanghai) Co., Ltd. and/or its affiliates (hereinafter collectively referred to as “MetaX”).
 * The information presented in the Software belongs to MetaX. Without prior written permission
 * from MetaX, no entity or individual has the right to obtain a copy of the Software to deal in
 * the Software, including but not limited to use, copy, modify, merge, disclose, publish,
 * distribute, sublicense, and/or sell copies of the Software or substantial portions of the Software.
 *
 * The Software is provided for reference only, without warranty of any kind, either express or
 * implied, including but not limited to the warranty of merchantability, fitness for any purpose
 * and/or noninfringement. In no case shall MetaX be liable for any claim, damage or other liability
 * arising from, out of or in connection with the Software.
 *
 * If the Software need to be used in conjunction with any third-party software or open source
 * software, the rights to the third-party software or open source software still belong to the
 * copyright owners. For details, please refer to the respective notices or licenses. Please comply
 * with the provisions of the relevant notices or licenses. If the open source software licenses
 * additionally require the disposal of rights related to this Software, please contact MetaX
 * immediately and obtain MetaX 's written consent.
 *
 * MetaX reserves the right, at its sole discretion, to change, modify, add or remove portions of the
 * Software, at any time. MetaX reserves all the right for the final explanation.
 *
 */

#ifndef __MXSML_EXTENSION_H__
#define __MXSML_EXTENSION_H__

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @file MxSmlExtension.h
 *
 * @brief Main header file for mxsml extension apis.
 *
 */

/*
 * For Windows DLL export
 */
#ifdef DECLDIR
    #undef DECLDIR
#endif

#if defined _WIN32
    #if !defined MXSML_STATIC_IMPORT
        #if defined MXSML_LIB_EXPORT
            #define DECLDIR __declspec(dllexport)
        #else
            #define DECLDIR __declspec(dllimport)
        #endif
    #else
        #define DECLDIR
    #endif
#else
    #define DECLDIR
#endif

/**
 * @brief Return values for API calls.
 */
typedef enum MxSmlExReturn
#ifdef __cplusplus
 : unsigned int
#endif
{
    MXSMLEX_SUCCESS = 0,                          //!< The operation was successful
    MXSMLEX_ERROR_UNINITIALIZED = 1,              //!< mxsml extension was not first initialized with mxSmlExInit()
    MXSMLEX_ERROR_INVALID_ARGUMENT = 2,           //!< A supplied argument is invalid
    MXSMLEX_ERROR_NOT_SUPPORTED = 3,              //!< The requested operation is not available on target device
    MXSMLEX_ERROR_NO_PERMISSION = 4,              //!< The current user does not have permission for operation
    MXSMLEX_ERROR_ALREADY_INITIALIZED = 5,        //!< Deprecated: Multiple initializations are now allowed
    MXSMLEX_ERROR_NOT_FOUND = 6,                  //!< A query to find an object was unsuccessful
    MXSMLEX_ERROR_INSUFFICIENT_SIZE = 7,          //!< An input argument is not large enough
    MXSMLEX_ERROR_INSUFFICIENT_POWER = 8,         //!< A device's external power cables are not properly attached
    MXSMLEX_ERROR_DRIVER_NOT_LOADED = 9,          //!< Driver is not loaded
    MXSMLEX_ERROR_TIMEOUT = 10,                   //!< User provided timeout passed
    MXSMLEX_ERROR_IRQ_ISSUE = 11,                 //!< Kernel detected an interrupt issue with a GPU
    MXSMLEX_ERROR_LIBRARY_NOT_FOUND = 12,         //!< MXSML Shared Library couldn't be found or loaded
    MXSMLEX_ERROR_FUNCTION_NOT_FOUND = 13,        //!< Local version of MXSML doesn't implement this function
    MXSMLEX_ERROR_CORRUPTED_INFOROM = 14,         //!< infoROM is corrupted
    MXSMLEX_ERROR_GPU_IS_LOST = 15,               //!< The GPU has fallen off the bus or has otherwise become inaccessible
    MXSMLEX_ERROR_RESET_REQUIRED = 16,            //!< The GPU requires a reset before it can be used again
    MXSMLEX_ERROR_OPERATING_SYSTEM = 17,          //!< The GPU control device has been blocked by the operating system/cgroups
    MXSMLEX_ERROR_LIB_RM_VERSION_MISMATCH = 18,   //!< RM detects a driver/library version mismatch
    MXSMLEX_ERROR_IN_USE = 19,                    //!< An operation cannot be performed because the GPU is currently in use
    MXSMLEX_ERROR_MEMORY = 20,                    //!< Insufficient memory
    MXSMLEX_ERROR_NO_DATA = 21,                   //!< No data
    MXSMLEX_ERROR_VGPU_ECC_NOT_SUPPORTED = 22,    //!< The requested vgpu operation is not available on target device, becasue ECC is enabled
    MXSMLEX_ERROR_INSUFFICIENT_RESOURCES = 23,    //!< Ran out of critical resources, other than memory
    MXSMLEX_ERROR_FREQ_NOT_SUPPORTED = 24,        //!< Ran out of critical resources, other than memory
    MXSMLEX_ERROR_ARGUMENT_VERSION_MISMATCH = 25, //!< The provided version is invalid/unsupported
    MXSMLEX_ERROR_DEPRECATED  = 26,               //!< The requested functionality has been deprecated
    MXSMLEX_ERROR_UNKNOWN = 999                   //!< An internal driver error occurred
} mxSmlExReturn_t;

/**
 * @brief Temperature sensors.
 */
typedef enum MxSmlExTemperatureSensors
#ifdef __cplusplus
 : unsigned int
#endif
{
    MXSMLEX_TEMPERATURE_GPU = 0,
    MXSMLEX_TEMPERATURE_COUNT
} mxsmlExTemperatureSensors_t;

/**
 * @brief Queryable pcie utilization counters.
 */
typedef enum MxSmlExPcieUtilCounter
#ifdef __cplusplus
 : unsigned int
#endif
{
    MXSMLEX_PCIE_UTIL_TX_BYTES = 0,
    MXSMLEX_PCIE_UTIL_RX_BYTES = 1,
    MXSMLEX_PCIE_UTIL_COUNT
} mxsmlExPcieUtilCounter_t;

/**
 * @brief Temperature thresholds.
 */
typedef enum MxSmlExTemperatureThresholds
#ifdef __cplusplus
 : unsigned int
#endif
{
    MXSMLEX_TEMPERATURE_THRESHOLD_SHUTDOWN = 0,
    MXSMLEX_TEMPERATURE_THRESHOLD_SLOWDOWN = 1,
    MXSMLEX_TEMPERATURE_THRESHOLD_MEM_MAX = 2,
    MXSMLEX_TEMPERATURE_THRESHOLD_GPU_MAX = 3,
    MXSMLEX_TEMPERATURE_THRESHOLD_ACOUSTIC_MIN = 4,
    MXSMLEX_TEMPERATURE_THRESHOLD_ACOUSTIC_CURR = 5,
    MXSMLEX_TEMPERATURE_THRESHOLD_ACOUSTIC_MAX = 6,
    MXSMLEX_TEMPERATURE_THRESHOLD_COUNT
} mxsmlExTemperatureThresholds_t;

/**
 * @brief Clock types.
 */
typedef enum MxSmlExClockType
#ifdef __cplusplus
 : unsigned int
#endif
{
    MXSMLEX_CLOCK_GRAPHICS = 0,
    MXSMLEX_CLOCK_SM = 1,
    MXSMLEX_CLOCK_MEM = 2,
    MXSMLEX_CLOCK_VIDEO = 3,
    MXSMLEX_CLOCK_COUNT
} mxsmlExClockType_t;

/**
 * @brief Clock Ids.
 */
typedef enum MxSmlExClockId
#ifdef __cplusplus
 : unsigned int
#endif
{
    MXSMLEX_CLOCK_ID_CURRENT = 0,
    MXSMLEX_CLOCK_ID_APP_CLOCK_TARGET = 1,
    MXSMLEX_CLOCK_ID_APP_CLOCK_DEFAULT = 2,
    MXSMLEX_CLOCK_ID_CUSTOMER_BOOST_MAX = 3,
    MXSMLEX_CLOCK_ID_COUNT
} mxsmlExClockId_t;

#define MXSMLEX_DBDF_ID_BUFFER_SIZE 32            //!< Guaranteed maximum possible size for BDF ID
#define MXSMLEX_DBDF_ID_BUFFER_V2_SIZE 16         //!< Guaranteed maximum possible size for BDF ID legacy

typedef struct MxSmlExPciInfo
{
    char busIdLegacy[MXSMLEX_DBDF_ID_BUFFER_V2_SIZE]; //!< The legacy tuple domain:bus:device.function PCI identifier
    unsigned int domain;                              //!< The PCI domain on which the device's bus resides, 0 to 0xffffffff
    unsigned int bus;                                 //!< The bus on which the device resides, 0 to 0xff
    unsigned int device;                              //!< The device's id on the bus, 0 to 31
    unsigned int pciDeviceId;                         //!< The combined 16-bit device id and 16-bit vendor id
    unsigned int pciSubSystemId;                      //!< The 32-bit Sub System Device ID
    char busId[MXSMLEX_DBDF_ID_BUFFER_SIZE];          //!< The tuple domain:bus:device.function PCI identifier
} mxSmlExPciInfo_t;

/**
 * @brief This structure holds the utilization rate information of device
 */
typedef struct MxSmlExUtilization
{
    unsigned int gpu;
    unsigned int memory;
} mxsmlExUtilization_t;

/**
 * @brief This structure holds the process information currently using GPU, usedGpuMemory unit: byte
 */
typedef struct MxSmlExProcessInfo
{
    unsigned int computeInstanceId;
    unsigned int gpuInstanceId;
    unsigned int pid;
    unsigned long long usedGpuMemory;
} mxsmlExProcessInfo_t;

/**
 * @brief This structure holds the memory allocation information of device, unit: byte
 */
typedef struct MxSmlExMemory
{
    unsigned long long free;
    unsigned long long total;
    unsigned long long used;
} mxsmlExMemory_t;

typedef struct MxSmlExDevice* mxsmlExDevice_t;

#define MXSMLEX_DEVICE_UUID_BUFFER_SIZE 80 //!< Guaranteed maximum possible size for device UUID

/**
 * @brief This structure holds the excluded device information
*/
typedef struct MxSmlExExcludedDeviceInfo
{
    mxSmlExPciInfo_t pciInfo;
    char uuid[MXSMLEX_DEVICE_UUID_BUFFER_SIZE];
} mxSmlExExcludedDeviceInfo_t;

/**
 * @brief This structure holds the P2P capability index status information
*/
typedef enum MxSmlExGpuP2PStatus
{
    MXSMLEX_P2P_STATUS_OK = 0,
    MXSMLEX_P2P_STATUS_CHIPSET_NOT_SUPPORTED,
    MXSMLEX_P2P_STATUS_GPU_NOT_SUPPORTED,
    MXSMLEX_P2P_STATUS_IOH_TOPOLOGY_NOT_SUPPORTED,
    MXSMLEX_P2P_STATUS_DISABLED_BY_REGKEY,
    MXSMLEX_P2P_STATUS_NOT_SUPPORTED,
    MXSMLEX_P2P_STATUS_UNKNOWN
} mxSmlExGpuP2PStatus_t;

/**
 * @brief This structure holds the P2P capability index information
*/
typedef enum MxSmlExGpuP2PCapsIndex
{
    MXSMLEX_P2P_CAPS_INDEX_READ = 0,
    MXSMLEX_P2P_CAPS_INDEX_WRITE,
    MXSMLEX_P2P_CAPS_INDEX_MXLINK,
    MXSMLEX_P2P_CAPS_INDEX_ATOMICS,
    MXSMLEX_P2P_CAPS_INDEX_PROP,
    MXSMLEX_P2P_CAPS_INDEX_UNKNOWN
} mxSmlExGpuP2PCapsIndex_t;

/**
 * @brief This structure holds the performance states
*/
typedef enum MxSmlExPstates
{
    MXSMLEX_PSTATE_0 = 0,           //!< Performance state 0 -- Maximum Performance.
    MXSMLEX_PSTATE_1 = 1,
    MXSMLEX_PSTATE_2 = 2,
    MXSMLEX_PSTATE_3 = 3,
    MXSMLEX_PSTATE_4 = 4,
    MXSMLEX_PSTATE_5 = 5,
    MXSMLEX_PSTATE_6 = 6,
    MXSMLEX_PSTATE_7 = 7,
    MXSMLEX_PSTATE_8 = 8,
    MXSMLEX_PSTATE_9 = 9,
    MXSMLEX_PSTATE_10 = 10,
    MXSMLEX_PSTATE_11 = 11,
    MXSMLEX_PSTATE_12 = 12,
    MXSMLEX_PSTATE_13 = 13,
    MXSMLEX_PSTATE_14 = 14,
    MXSMLEX_PSTATE_15 = 15,         //!< Performance state 15 -- Minimum Performance.
    MXSMLEX_PSTATE_UNKNOWN = 32     //!< Unknown performance state.
} mxSmlExPstates_t;

/**
 * @brief Initialize mxsml
 *
 * @details When called, the devices are discovered and initialized.
 * This function shall be called once before invoking any other methods in this library.
 *
 * @retval MXSMLEX_SUCCESS                 Initialization was successful
 * @retval MXSMLEX_ERROR_UNKNOWN           Any unexpected error
 */
mxSmlExReturn_t DECLDIR mxSmlExInit(void);

/**
 * @brief Get the handle for a particular device, based on its index
 *
 * @param[in]  deviceId : the device index, start from 0
 * @param[out] deviceHandle : return the device handle
 *
 * @retval MXSMLEX_SUCCESS                   call was successful
 * @retval MXSMLEX_ERROR_INVALID_ARGUMENT    deviceId is invalid or deviceHandle is null
 */
mxSmlExReturn_t DECLDIR mxSmlExGetDeviceHandleByIndex(unsigned int deviceId, mxsmlExDevice_t* deviceHandle);

/**
 * @brief Get the handle for a particular device, based on its PCI bus id
 *
 * @param[in]  pciBusId : the PCI bus id of the target GPU
 * @param[out] deviceHandle : return the device handle
 *
 * @retval MXSMLEX_SUCCESS                   call was successful
 * @retval MXSMLEX_ERROR_INVALID_ARGUMENT    pciBusId is invalid or deviceHandle is null
 */
mxSmlExReturn_t DECLDIR mxSmlExGetDeviceHandleByPciBusId(const char* pciBusId, mxsmlExDevice_t* deviceHandle);

/**
 * @brief Get the PCI attributes of this device
 *
 * @param[in]  deviceHandle : the device handle
 * @param[out] pci : reference in which to return the PCI info
 *
 * @retval MXSMLEX_SUCCESS                   call was successful
 * @retval MXSMLEX_ERROR_INVALID_ARGUMENT    deviceHandle is invalid or pci is null
 */
mxSmlExReturn_t DECLDIR mxSmlExDeviceGetPciInfo(mxsmlExDevice_t deviceHandle, mxSmlExPciInfo_t* pci);

/**
 * @brief Get the fan's speed of this device
 *
 * @param[in]  deviceHandle : the device handle
 * @param[out] speed : reference in which to return the fan speed
 *
 * @retval MXSMLEX_SUCCESS                   call was successful
 * @retval MXSMLEX_ERROR_NOT_SUPPORTED       the device does not have a fan
 * @retval MXSMLEX_ERROR_INVALID_ARGUMENT    deviceHandle is invalid or speed is null
 */
mxSmlExReturn_t DECLDIR mxSmlExDeviceGetFanSpeed(mxsmlExDevice_t deviceHandle, unsigned int* speed);

/**
 * @brief Get the specified fan's speed of this device
 *
 * @param[in]  deviceHandle : the device handle
 * @param[in]  fan : the index of fan
 * @param[out] speed : reference in which to return the fan speed
 *
 * @retval MXSMLEX_SUCCESS                   call was successful
 * @retval MXSMLEX_ERROR_NOT_SUPPORTED       the device does not have a fan
 * @retval MXSMLEX_ERROR_INVALID_ARGUMENT    deviceHandle is invalid or speed is null
 */
mxSmlExReturn_t DECLDIR mxSmlExDeviceGetFanSpeed_v2(mxsmlExDevice_t deviceHandle, unsigned int fan, unsigned int* speed);

/**
 * @brief Get the current utilization rates of this device
 *
 * @param[in]  deviceHandle : the device handle
 * @param[out] utilizaition : reference in which to return the utilization info
 *
 * @retval MXSMLEX_SUCCESS                   call was successful
 * @retval MXSMLEX_ERROR_INVALID_ARGUMENT    deviceHandle is invalid or utilization is null
 */
mxSmlExReturn_t DECLDIR mxSmlExDeviceGetUtilization(mxsmlExDevice_t deviceHandle, mxsmlExUtilization_t* utilizaition);

#define MXSMLEX_NAME_V2_BUFFER_SIZE 96            //!< Guaranteed maximum possible size for device name
/**
 * @brief Get the name of this device
 *
 * @param[in]  deviceHandle : the device handle
 * @param[out] name : reference in which to return the product name
 * @param[in]  length : the maximum allowed length of the string returned in name, not exceed 96 characters
 *
 * @retval MXSMLEX_SUCCESS                     call was successful
 * @retval MXSMLEX_ERROR_INVALID_ARGUMENT      deviceHandle is invalid or name is null
 * @retval MXSMLEX_ERROR_INSUFFICIENT_SIZE     length is too small
 */
mxSmlExReturn_t DECLDIR mxSmlExDeviceGetName(mxsmlExDevice_t deviceHandle, char* name, unsigned int length);

#define MXSMLEX_DRIVER_VERSION_BUFFER_SIZE 80     //!< Guaranteed maximum possible size for driver version
/**
 * @brief Get the version of the system driver
 *
 * @param[out] version : reference in which to return the version
 * @param[in]  length : the maximum allowed length of the string returned in version, not exceed 80 characters
 *
 * @retval MXSMLEX_SUCCESS                     call was successful
 * @retval MXSMLEX_ERROR_UNKNOWN               unexpected error
 * @retval MXSMLEX_ERROR_INVALID_ARGUMENT      version is null
 * @retval MXSMLEX_ERROR_INSUFFICIENT_SIZE     length is too small
 */
mxSmlExReturn_t DECLDIR mxSmlExSystemGetDriverVersion(char* version, unsigned int length);

/**
 * @brief Get the version of the mxsml library
 *
 * @param[out] version : reference in which to return the mxsml version
 * @param[in]  length : the maximum allowed length of the string returned in version, not exceed 80 characters
 *
 * @retval MXSMLEX_SUCCESS                     call was successful
 * @retval MXSMLEX_ERROR_UNKNOWN               unexpected error
 * @retval MXSMLEX_ERROR_INVALID_ARGUMENT      version is null
 * @retval MXSMLEX_ERROR_INSUFFICIENT_SIZE     length is too small
 */
mxSmlExReturn_t DECLDIR mxSmlExSystemGetMxsmlVersion(char* version, unsigned int length);

/**
 * @brief Get minor number for the device
 *
 * @param[in] deviceHandle : the device handle
 * @param[out]  minorNumber : reference in which to return the minor number for the device
 *
 * @retval MXSMLEX_SUCCESS                     call was successful
 * @retval MXSMLEX_ERROR_UNKNOWN               unexpected error
 * @retval MXSMLEX_ERROR_INVALID_ARGUMENT      deviceHandle is invalid or minorNumber is null
 * @retval MXSMLEX_ERROR_NOT_SUPPORTED         the query is not supported on target device
 */
mxSmlExReturn_t DECLDIR mxSmlExDeviceGetMinorNumber(mxsmlExDevice_t deviceHandle, unsigned int* minorNumber);

/**
 * @brief Generic enable/disable enum.
 */
typedef enum MxSmlExEnableState
#ifdef __cplusplus
 : unsigned int
#endif
{
    MXSMLEX_FEATURE_DISABLED = 0,
    MXSMLEX_FEATURE_ENABLED = 1
} mxSmlExEnableState_t;

/**
 * @brief Get the state of the device's MetaXLink for the link specified
 *
 * @param[in]  deviceHandle : the device handle
 * @param[in]  link : specifies the MetaXLink to be queried
 * @param[out] isActive : indicates the link is active or inactive
 *
 * @retval MXSMLEX_SUCCESS                     call was successful
 * @retval MXSMLEX_ERROR_UNKNOWN               unexpected error
 * @retval MXSMLEX_ERROR_INVALID_ARGUMENT      deviceHandle is invalid or isActive is null
 * @retval MXSMLEX_ERROR_NOT_SUPPORTED         the device does not support this feature
 */
mxSmlExReturn_t DECLDIR mxSmlExDeviceGetMetaXLinkState(mxsmlExDevice_t deviceHandle, unsigned int link, mxSmlExEnableState_t* isActive);

/**
 * @brief Get the pci information for the remote node on a MetaXLink
 *
 * @param[in]  deviceHandle : the device handle
 * @param[in]  link : specifies the MetaXLink to be queried
 * @param[out] pci : mxSmlExPciInfo_t of the remote node for the specified link, pciSubSystemId is indeterminate
 *
 * @retval MXSMLEX_SUCCESS                     call was successful
 * @retval MXSMLEX_ERROR_UNKNOWN               unexpected error
 * @retval MXSMLEX_ERROR_INVALID_ARGUMENT      deviceHandle is invalid or pci is null
 * @retval MXSMLEX_ERROR_NOT_SUPPORTED         the device does not support this feature
 */
mxSmlExReturn_t DECLDIR mxSmlExDeviceGetMetaXLinkRemotePciInfo_v2(mxsmlExDevice_t deviceHandle, unsigned int link, mxSmlExPciInfo_t *pci);

/**
 * @brief convert mxsml error code into readable strings
 *
 * @param[in] result : mxsml error code to convert
 *
 * @retval String representation of the error
 */
DECLDIR const char* mxSmlExErrorString(mxSmlExReturn_t result);

/**
 * @brief Shut down mxsml
 *
 * @details This method should be called after mxsml work is done.
 * Shut down mxsml by releasing all gpu resources previously allocated with mxSmlExInit().
 *
 * @retval MXSMLEX_SUCCESS                 if mxsml has been properly shut down
 * @retval MXSMLEX_ERROR_UNKNOWN           unexpected error
 */
mxSmlExReturn_t DECLDIR mxSmlExShutdown(void);

/**
 * @brief Get the current temperature readings for the device, in degress C
 *
 * @param[in]  deviceHandle : the device handle
 * @param[in]  sensorType : flag that indicates which sensor reading to get
 * @param[out] temperature : reference in which to return the temperature reading
 *
 * @retval MXSMLEX_SUCCESS                     call was successful
 * @retval MXSMLEX_ERROR_UNKNOWN               unexpected error
 * @retval MXSMLEX_ERROR_INVALID_ARGUMENT      deviceHandle is invalid, sensorType is invalid or temperature is null
 */
mxSmlExReturn_t DECLDIR mxSmlExDeviceGetTemperature(mxsmlExDevice_t deviceHandle, mxsmlExTemperatureSensors_t sensorType, unsigned int* temperature);

/**
 * @brief Get the number of compute devices in the system
 *
 * @param[out] deviceCount : reference in which to return the number of accessible devices
 *
 * @retval MXSMLEX_SUCCESS                     call was successful
 * @retval MXSMLEX_ERROR_UNKNOWN               unexpected error
 * @retval MXSMLEX_ERROR_INVALID_ARGUMENT      deviceCount is null
 */
mxSmlExReturn_t DECLDIR mxSmlExDeviceGetCount(unsigned int* deviceCount);

/**
 * @brief Get the number of maca compute devices in the system
 *
 * @param[out] deviceCount : reference in which to return the number of accessible devices
 *
 * @retval MXSMLEX_SUCCESS                     call was successful
 * @retval MXSMLEX_ERROR_UNKNOWN               unexpected error
 * @retval MXSMLEX_ERROR_INVALID_ARGUMENT      deviceCount is null
 */
mxSmlExReturn_t DECLDIR mxSmlExMacaDeviceGetCount(unsigned int* deviceCount);

/**
 * @brief Get the current pcie link width for the device
 *
 * @param[in]  deviceHandle : the device handle
 * @param[out] currLinkWidth : reference in which to return the current pcie link width
 *
 * @retval MXSMLEX_SUCCESS                     call was successful
 * @retval MXSMLEX_ERROR_UNKNOWN               unexpected error
 * @retval MXSMLEX_ERROR_INVALID_ARGUMENT      deviceHandle is invalid or currLinkWidth is null
 */
mxSmlExReturn_t DECLDIR mxSmlExDeviceGetCurrPcieLinkWidth(mxsmlExDevice_t deviceHandle, unsigned int* currLinkWidth);

/**
 * @brief Get process information currently running on GPU
 *
 * @param[in] deviceHandle : the device handle
 * @param[out] infoCount : reference in which to provide the infos array size and to return the number of returned elements
 * @param[out] infos : reference in which to return the process information
 *
 * @retval MXSMLEX_SUCCESS                     call was successful
 * @retval MXSMLEX_ERROR_UNKNOWN               unexpected error
 * @retval MXSMLEX_ERROR_INSUFFICIENT_SIZE     infos array is too small but infoCount return the minimal infos array size
 * @retval MXSMLEX_ERROR_INVALID_ARGUMENT      deviceHandle is invalid or infoCount or infos is null
 */
mxSmlExReturn_t DECLDIR mxSmlExDeviceGetComputeRunningProcesses(mxsmlExDevice_t deviceHandle, unsigned int* infoCount, mxsmlExProcessInfo_t* infos);

/**
 * @brief Get the memory information for the device, in bytes
 *
 * @param[in]  deviceHandle : the device handle
 * @param[out] memory : reference in which to return the memory information
 *
 * @retval MXSMLEX_SUCCESS                     call was successful
 * @retval MXSMLEX_ERROR_UNKNOWN               unexpected error
 * @retval MXSMLEX_ERROR_INVALID_ARGUMENT      deviceHandle or memory is null
 * @retval MXSMLEX_ERROR_NOT_SUPPORTED         The operation is unsupported on target device
 */
mxSmlExReturn_t DECLDIR mxSmlExDeviceGetMemoryInfo(mxsmlExDevice_t deviceHandle, mxsmlExMemory_t* memory);

/**
 * @brief Get the compute capability for the device
 *
 * @param[in]  deviceHandle : the device handle
 * @param[out] major : reference in which to return the major compute capability
 * @param[out] minor : reference in which to return the minor compute capability
 *
 * @retval MXSMLEX_SUCCESS                     call was successful
 * @retval MXSMLEX_ERROR_UNKNOWN               unexpected error
 * @retval MXSMLEX_ERROR_INVALID_ARGUMENT      deviceHandle is invalid or major of minor is null
 */
mxSmlExReturn_t DECLDIR mxSmlExDeviceGetComputeCapability(mxsmlExDevice_t deviceHandle, int* major, int* minor);

/**
 * @brief Get the power usage for the device in milliwatts
 *
 * @param[in]  deviceHandle : the device handle
 * @param[out] powerUsage : reference in which to return the power usage information
 *
 * @retval MXSMLEX_SUCCESS                     call was successful
 * @retval MXSMLEX_ERROR_UNKNOWN               unexpected error
 * @retval MXSMLEX_ERROR_INVALID_ARGUMENT      deviceHandle is invalid or powerUsage is null
 */
mxSmlExReturn_t DECLDIR mxSmlExGetPowerUsage(mxsmlExDevice_t deviceHandle, unsigned int* powerUsage);

/**
 * @brief Get the power management limit associated with the device
 *
 * @param[in]  deviceHandle : the device handle
 * @param[out] limit : reference in which to return the power management limit in milliwatts
 *
 * @retval MXSMLEX_SUCCESS                     call was successful
 * @retval MXSMLEX_ERROR_UNKNOWN               unexpected error
 * @retval MXSMLEX_ERROR_INVALID_ARGUMENT      deviceHandle is invalid or limit is null
 */
mxSmlExReturn_t DECLDIR mxSmlExGetPowerManagementLimit(mxsmlExDevice_t deviceHandle, unsigned int* limit);

/**
 * @brief Get the maximum pcie link width for the device in system
 *
 * @param[in]  deviceHandle : the device handle
 * @param[out] maxLinkWidth : reference in which to return the max pcie link width
 *
 * @retval MXSMLEX_SUCCESS                     call was successful
 * @retval MXSMLEX_ERROR_UNKNOWN               unexpected error
 * @retval MXSMLEX_ERROR_INVALID_ARGUMENT      deviceHandle is invalid or maxLinkWidth is null
 */
mxSmlExReturn_t DECLDIR mxSmlExGetMaxPcieLinkWidth(mxsmlExDevice_t deviceHandle, unsigned int* maxLinkWidth);

/**
 * @brief Get the pcie utilization information
 *
 * @param[in]  deviceHandle : the device handle
 * @param[in]  counter : the specific counter
 * @param[out] value : reference in which to return throughput in KBytes/s
 *
 * @retval MXSMLEX_SUCCESS                     call was successful
 * @retval MXSMLEX_ERROR_UNKNOWN               unexpected error
 * @retval MXSMLEX_ERROR_NOT_SUPPORTED         the device does not support this feature
 * @retval MXSMLEX_ERROR_INVALID_ARGUMENT      deviceHandle or counter is invalid or value is null
 */
mxSmlExReturn_t DECLDIR mxSmlExGetPcieThroughput(mxsmlExDevice_t deviceHandle, mxsmlExPcieUtilCounter_t counter, unsigned int* value);

/**
 * @brief Get the temperature threshold for the device
 *
 * @param[in]  deviceHandle : the device handle
 * @param[in]  thresholdType : the type of threshold value queried
 * @param[out] temperature : reference in which to return the temperature reading
 *
 * @retval MXSMLEX_SUCCESS                     call was successful
 * @retval MXSMLEX_ERROR_UNKNOWN               unexpected error
 * @retval MXSMLEX_ERROR_NOT_SUPPORTED         the threshold type is unsupported
 * @retval MXSMLEX_ERROR_INVALID_ARGUMENT      deviceHandle is invalid or temp is null
 */
mxSmlExReturn_t DECLDIR mxSmlExDeviceGetTemperatureThreshold(mxsmlExDevice_t deviceHandle, mxsmlExTemperatureThresholds_t thresholdType, unsigned int* temperature);

/**
 * @brief Get the current clock speeds for the device
 *
 * @param[in]  deviceHandle : the device handle
 * @param[in]  clockType : identify which clock domain to query
 * @param[out] clock : reference in which to return the clock speed in MHz
 *
 * @retval MXSMLEX_SUCCESS                     call was successful
 * @retval MXSMLEX_ERROR_UNKNOWN               unexpected error
 * @retval MXSMLEX_ERROR_NOT_SUPPORTED         the clock type is unsupported
 * @retval MXSMLEX_ERROR_INVALID_ARGUMENT      deviceHandle is invalid or clock is null
 */
mxSmlExReturn_t DECLDIR mxSmlExDeviceGetClockInfo(mxsmlExDevice_t deviceHandle, mxsmlExClockType_t clockType, unsigned int* clock);

/**
 * @brief Get the current clock speeds specified by the clock type and clock ID
 *
 * @param[in]  deviceHandle : the device handle
 * @param[in]  clockType : identify which clock domain to query
 * @param[in]  clockId : identify which clock domain to query
 * @param[out] clock : reference in which to return the clock speed in MHz
 *
 * @retval MXSMLEX_SUCCESS                     call was successful
 * @retval MXSMLEX_ERROR_UNKNOWN               unexpected error
 * @retval MXSMLEX_ERROR_NOT_SUPPORTED         the clock type is unsupported
 * @retval MXSMLEX_ERROR_INVALID_ARGUMENT      deviceHandle is invalid or clock is null
 */
mxSmlExReturn_t DECLDIR mxSmlExDeviceGetClock(mxsmlExDevice_t deviceHandle, mxsmlExClockType_t clockType, mxsmlExClockId_t clockId, unsigned int* clock);

/**
 * @brief Get the device power limit
 *
 * @param[in]  deviceHandle : the device handle
 * @param[out] limit : return the power management limit in milliwatts
 *
 * @retval MXSMLEX_SUCCESS                     call was successful
 * @retval MXSMLEX_ERROR_UNKNOWN               unexpected error
 * @retval MXSMLEX_ERROR_NOT_SUPPORTED         the device does not support this feature
 * @retval MXSMLEX_ERROR_INVALID_ARGUMENT      deviceHandle is invalid or limit is null
 */
mxSmlExReturn_t DECLDIR mxSmlExDeviceGetEnforcedPowerLimit(mxsmlExDevice_t deviceHandle, unsigned int* limit);

#define mxsmlExClocksThrottleReasonAll mxsmlClocksThrottleReasonAll
#define mxsmlExClocksThrottleReasonApplicationsClocksSetting mxsmlClocksThrottleReasonApplicationsLimit
#define mxsmlExClocksThrottleReasonDisplayClockSetting mxsmlClocksThrottleReasonOther
#define mxsmlExClocksThrottleReasonGpuIdle mxsmlClocksThrottleReasonIdle
#define mxsmlExClocksThrottleReasonHwPowerBrakeSlowdown mxsmlClocksThrottleReasonPowerBrake
#define mxsmlExClocksThrottleReasonHwSlowdown mxsmlClocksThrottleReasonOther
#define mxsmlExClocksThrottleReasonHwThermalSlowdown mxsmlClocksThrottleReasonOther
#define mxsmlExClocksThrottleReasonNone mxsmlClocksThrottleReasonNone
#define mxsmlExClocksThrottleReasonSwPowerCap mxsmlClocksThrottleReasonOverPower
#define mxsmlExClocksThrottleReasonSwThermalSlowdown mxsmlClocksThrottleReasonThermalOverTemperature
#define mxsmlExClocksThrottleReasonSyncBoost mxsmlClocksThrottleReasonOther
/**
 * @brief Get the current clocks throttling reasons
 *
 * @param[in]  deviceHandle : the device handle
 * @param[out] clocksThrottleReasons : reference in which to return bitmask of active clocks throttle reasons
 *
 * @retval MXSMLEX_SUCCESS                     call was successful
 * @retval MXSMLEX_ERROR_UNKNOWN               unexpected error
 * @retval MXSMLEX_ERROR_NOT_SUPPORTED         the device does not support this feature
 * @retval MXSMLEX_ERROR_INVALID_ARGUMENT      deviceHandle is invalid or clocksThrottleReasons is null
 */
mxSmlExReturn_t DECLDIR mxSmlExDeviceGetCurrentClocksThrottleReasons(mxsmlExDevice_t deviceHandle, unsigned long long* clocksThrottleReasons);

/**
 * @brief Get the supported clocks throttling reasons
 *
 * @param[in]  deviceHandle : the device handle
 * @param[out] supportedClocksThrottleReasons : reference in which to return bitmask of supported clocks throttle reasons
 *
 * @retval MXSMLEX_SUCCESS                     call was successful
 * @retval MXSMLEX_ERROR_UNKNOWN               unexpected error
 * @retval MXSMLEX_ERROR_NOT_SUPPORTED         the device does not support this feature
 * @retval MXSMLEX_ERROR_INVALID_ARGUMENT      deviceHandle is invalid or supportedClocksThrottleReasons is null
 */
mxSmlExReturn_t DECLDIR mxSmlExDeviceGetSupportedClocksThrottleReasons(mxsmlExDevice_t deviceHandle, unsigned long long* supportedClocksThrottleReasons);

/**
 * @brief Get an array of bitmasks with the ideal CPU affinity for the device
 *
 * @param[in]  deviceHandle : the device handle
 * @param[in]  cpuSetSize: the size of the cpuSet array that is safe to access
 * @param[out] cpuSet: array reference in which to return a bitmask of CPUs, 64 CPUs per unsigned long on 64-bit machines, 32 on 32-bit machines
 *
 * @retval MXSMLEX_SUCCESS                     call was successful
 * @retval MXSMLEX_ERROR_UNKNOWN               unexpected error
 * @retval MXSMLEX_ERROR_NOT_SUPPORTED         the device does not support this feature
 * @retval MXSMLEX_ERROR_INVALID_ARGUMENT      deviceHandle is invalid or cpuSetSize == 0 or cpuSet is null
 */
mxSmlExReturn_t DECLDIR mxSmlExDeviceGetCpuAffinity(mxsmlExDevice_t deviceHandle, unsigned int cpuSetSize, unsigned long* cpuSet);

/**
 * @brief Get the memory clocks that can be used as an argument for mxSmlExDeviceSetApplicationsClocks
 *
 * @param[in]  deviceHandle : the device handle
 * @param[in]  count : reference in which to provide the clocksMHz array size, and to return the number of elements
 * @param[out] clocksMHz : reference in which to return the clock in MHz
 *
 * @retval MXSMLEX_SUCCESS                     call was successful
 * @retval MXSMLEX_ERROR_UNKNOWN               unexpected error
 * @retval MXSMLEX_ERROR_NOT_SUPPORTED         the device does not support this feature
 * @retval MXSMLEX_ERROR_INSUFFICIENT_SIZE     the count is too small and count is set to the required number
 * @retval MXSMLEX_ERROR_INVALID_ARGUMENT      deviceHandle is invalid or count or clocksMHz is null
 */
mxSmlExReturn_t DECLDIR mxSmlExDeviceGetSupportedMemoryClocks(mxsmlExDevice_t deviceHandle, unsigned int* count, unsigned int* clocksMHz);

/**
 * @brief Get the graphics clocks that can be used as an argument for mxSmlExDeviceSetApplicationsClocks
 *
 * @param[in]  deviceHandle : the device handle
 * @param[in]  count : reference in which to provide the clocksMHz array size, and to return the number of elements
 * @param[out] clocksMHz : reference in which to return the clock in MHz
 *
 * @retval MXSMLEX_SUCCESS                     call was successful
 * @retval MXSMLEX_ERROR_UNKNOWN               unexpected error
 * @retval MXSMLEX_ERROR_NOT_SUPPORTED         the device does not support this feature
 * @retval MXSMLEX_ERROR_INSUFFICIENT_SIZE     the count is too small and count is set to the required number
 * @retval MXSMLEX_ERROR_INVALID_ARGUMENT      deviceHandle is invalid or count or clocksMHz is null
 */
mxSmlExReturn_t DECLDIR mxSmlExDeviceGetSupportedGraphicsClocks(mxsmlExDevice_t deviceHandle, unsigned int* count, unsigned int* clocksMHz);

/**
 * @brief Get the graphics clocks that can be used as an argument for mxSmlExDeviceSetApplicationsClocks
 *
 * @param[in]  deviceHandle : the device handle
 * @param[in]  memoryClockMHz : memory clock for which to return possible graphics clocks
 * @param[in]  count : reference in which to provide the clocksMHz array size, and to return the number of elements
 * @param[out] clocksMHz : reference in which to return the clock in MHz
 *
 * @retval MXSMLEX_SUCCESS                     call was successful
 * @retval MXSMLEX_ERROR_UNKNOWN               unexpected error
 * @retval MXSMLEX_ERROR_NOT_SUPPORTED         the device does not support this feature
 * @retval MXSMLEX_ERROR_NOT_FOUND             if the specified memoryClockMHz is not a supported frequency
 * @retval MXSMLEX_ERROR_INSUFFICIENT_SIZE     the count is too small and count is set to the required number
 * @retval MXSMLEX_ERROR_INVALID_ARGUMENT      deviceHandle is invalid or count or clocksMHz is null
 */
mxSmlExReturn_t DECLDIR mxSmlExDeviceGetSupportedGraphicsClocks_v2(mxsmlExDevice_t deviceHandle, unsigned int memoryClockMHz,
                                                                        unsigned int* count, unsigned int* clocksMHz);

/**
 * @brief set clocks that applications will lock to
 *
 * @param[in]  deviceHandle : the device handle
 * @param[in]  memoryClockMHz : requested memory clock in MHz
 * @param[in]  graphicsClockMHz : requested graphics clock in MHz
 *
 * @retval MXSMLEX_SUCCESS                     call was successful
 * @retval MXSMLEX_ERROR_UNKNOWN               unexpected error
 * @retval MXSMLEX_ERROR_NOT_SUPPORTED         the device does not support this feature
 * @retval MXSMLEX_ERROR_INVALID_ARGUMENT      deviceHandle is invalid or memoryClockMHz and graphicsClockMHz is not a valid clock combination
 */
mxSmlExReturn_t DECLDIR mxSmlExDeviceSetApplicationsClocks(mxsmlExDevice_t deviceHandle, unsigned int memoryClockMHz, unsigned int graphicsClockMHz);

/**
 * @brief reset the application clock to the default value
 *
 * @param[in]  deviceHandle : the device handle
 *
 * @retval MXSMLEX_SUCCESS                     call was successful
 * @retval MXSMLEX_ERROR_UNKNOWN               unexpected error
 * @retval MXSMLEX_ERROR_NOT_SUPPORTED         the device does not support this feature
 * @retval MXSMLEX_ERROR_INVALID_ARGUMENT      deviceHandle is invalid
 */
mxSmlExReturn_t DECLDIR mxSmlExDeviceResetApplicationsClocks(mxsmlExDevice_t deviceHandle);

/**
 * @brief get the current setting of a clock that applications will use
 *
 * @param[in]   deviceHandle : the device handle
 * @param[in]   clockType : identify which clock domain to query
 * @param[out]  clockMHz : reference in which to return the clock in MHz
 *
 * @retval MXSMLEX_SUCCESS                     call was successful
 * @retval MXSMLEX_ERROR_UNKNOWN               unexpected error
 * @retval MXSMLEX_ERROR_NOT_SUPPORTED         the device does not support this feature
 * @retval MXSMLEX_ERROR_INVALID_ARGUMENT      deviceHandle is invalid or clockType is invalid or clocksMHz is null
 */
mxSmlExReturn_t DECLDIR mxSmlExDeviceGetApplicationsClock(mxsmlExDevice_t deviceHandle, mxsmlExClockType_t clockType, unsigned int* clockMHz);

/**
 * @brief get the status for a given p2p capability index between a given pair of devices
 *
 * @param[in]  deviceHandle1 : the first device handle
 * @param[in]  deviceHandle2 : the second device handle
 * @param[in]  p2pIndex : the p2p Capability Index being looked for between device1 and device2
 * @param[out] p2pStatus : reference in which to return the status of p2pIndex
 *
 * @retval MXSMLEX_SUCCESS                     call was successful
 * @retval MXSMLEX_ERROR_INVALID_ARGUMENT      deviceHandle1 is invalid or deviceHandle2 is invalid or p2pIndex is invalid or p2pStatus is null
*/
mxSmlExReturn_t DECLDIR mxSmlExDeviceGetP2PStatus(mxsmlExDevice_t deviceHandle1, mxsmlExDevice_t deviceHandle2, mxSmlExGpuP2PCapsIndex_t p2pIndex, mxSmlExGpuP2PStatus_t *p2pStatus);

/**
 * @brief get uuid which is the globally unique immutable number associated with this device
 *
 * @param[in]  deviceHandle : the device handle
 * @param[out] uuid : reference in which to return the uuid
 * @param[in]  length : the maximum allowed length of uuid
 *
 * @retval MXSMLEX_SUCCESS                     call was successful
 * @retval MXSMLEX_ERROR_INVALID_ARGUMENT      deviceHandle is invalid or uuid is null or length is invalid
*/
mxSmlExReturn_t DECLDIR mxSmlExDeviceGetUUID(mxsmlExDevice_t deviceHandle, char* uuid, unsigned int length);

/**
 * @brief get device by uuid
 *
 * @param[in]  uuid : the uuid
 * @param[out] deviceHandle : reference in which to return the device handle
 *
 * @retval MXSMLEX_SUCCESS                     call was successful
 * @retval MXSMLEX_ERROR_INVALID_ARGUMENT      deviceHandle is invalid or uuid is null or length is invalid
*/
mxSmlExReturn_t DECLDIR mxSmlExDeviceGetHandleByUUID(char* uuid, mxsmlExDevice_t* deviceHandle);

/**
 * @brief get the current performance state for the device
 *
 * @param[in]  deviceHandle : the device handle
 * @param[out] pState : reference in which to return the performance state reading
 *
 * @retval MXSMLEX_SUCCESS                     call was successful
 * @retval MXSMLEX_ERROR_INVALID_ARGUMENT      deviceHandle is invalid or pState is null
 * @retval MXSMLEX_ERROR_UNKNOWN               unexpected error
 * @retval MXSMLEX_ERROR_NOT_SUPPORTED         the device does not support this feature
*/
mxSmlExReturn_t DECLDIR mxSmlExDeviceGetPerformanceState(mxsmlExDevice_t deviceHandle, mxSmlExPstates_t* pState);

/**
 * @brief set the current state of Auto Boosted clocks on a device
 *
 * @param[in]  deviceHandle : the device handle
 * @param[in] enabled : what state to try to set Auto Boosted clocks of the target device to
 *
 * @retval MXSMLEX_SUCCESS                     call was successful
 * @retval MXSMLEX_ERROR_INVALID_ARGUMENT      deviceHandle is invalid
 * @retval MXSMLEX_ERROR_UNKNOWN               unexpected error
 * @retval MXSMLEX_ERROR_NOT_SUPPORTED         the device does not support this feature
*/
mxSmlExReturn_t DECLDIR mxSmlExDeviceSetAutoBoostedClocksEnabled(mxsmlExDevice_t deviceHandle, mxSmlExEnableState_t enabled);

/**
 * @brief get the current state of Auto Boosted clocks on a device
 *
 * @param[in]  deviceHandle : the device handle
 * @param[out] isEnabled : where to store the current state of Auto Boosted clocks of the target device
 * @param[out] defaultIsEnabled : where to store the default Auto Boosted clocks behavior
 *
 * @retval MXSMLEX_SUCCESS                     call was successful
 * @retval MXSMLEX_ERROR_INVALID_ARGUMENT      deviceHandle is invalid or isEnabled or defaultIsEnabled is null
 * @retval MXSMLEX_ERROR_UNKNOWN               unexpected error
 * @retval MXSMLEX_ERROR_NOT_SUPPORTED         the device does not support this feature
*/
mxSmlExReturn_t DECLDIR mxSmlExDeviceGetAutoBoostedClocksEnabled(mxsmlExDevice_t deviceHandle, mxSmlExEnableState_t* isEnabled, mxSmlExEnableState_t* defaultIsEnabled);

/**
 * @brief Represents level relationships within a system between two GPUs.
 */
typedef enum MxSmlExGpuTopologyLevel
#ifdef __cplusplus
 : unsigned int
#endif
{
    MXSMLEX_TOPOLOGY_INTERNAL = 0,
    MXSMLEX_TOPOLOGY_SINGLE = 10,
    MXSMLEX_TOPOLOGY_MULTIPLE = 20,
    MXSMLEX_TOPOLOGY_HOSTBRIDGE = 30,
    MXSMLEX_TOPOLOGY_NODE = 40,
    MXSMLEX_TOPOLOGY_SYSTEM = 50
} mxSmlExGpuTopologyLevel_t;

/**
 * @brief get the common ancestor for two devices
 *
 * @param[in]  deviceHandle1 : the first device handle
 * @param[in]  deviceHandle2 : the second device handle
 * @param[out] pathInfo : return the path type
 *
 * @retval MXSMLEX_SUCCESS                     call was successful
 * @retval MXSMLEX_ERROR_INVALID_ARGUMENT      deviceHandle1 or deviceHandle2 is invalid or pathInfo is null
 * @retval MXSMLEX_ERROR_UNKNOWN               unexpected error
 * @retval MXSMLEX_ERROR_NOT_SUPPORTED         metaXlink or unknown link type does not support this feature
*/
mxSmlExReturn_t DECLDIR mxSmlExDeviceGetTopologyCommonAncestor(mxsmlExDevice_t deviceHandle1, mxsmlExDevice_t deviceHandle2, mxSmlExGpuTopologyLevel_t* pathInfo);

/**
 * @brief Represents MetaXLink's remote device type
 */
typedef enum MxSmlExMetaXLinkDeviceType
#ifdef __cplusplus
 : unsigned int
#endif
{
    MXSMLEX_METAXLINK_DEVICE_TYPE_GPU = 0x00,
    MXSMLEX_METAXLINK_DEVICE_TYPE_NPU = 0x01,
    MXSMLEX_METAXLINK_DEVICE_TYPE_SWITCH = 0x02,
    MXSMLEX_METAXLINK_DEVICE_TYPE_UNKNOWN = 0xFF
} mxSmlExMetaXLinkDeviceType_t;

/**
 * @brief get the MetaXLink device type of the remote device connected over the given link
 *
 * @param[in]  deviceHandle : the device handle
 * @param[in]  link : the MetaXLink link index
 * @param[out] type : return the remote device type
 *
 * @retval MXSMLEX_SUCCESS                     call was successful
 * @retval MXSMLEX_ERROR_INVALID_ARGUMENT      deviceHandle or link is invalid or type is null
 * @retval MXSMLEX_ERROR_NOT_SUPPORTED         MetaXlink is not supported
 * @retval MXSMLEX_ERROR_UNKNOWN               unexpected error
*/
mxSmlExReturn_t DECLDIR mxSmlExDeviceGetMetaXLinkRemoteDeviceType(mxsmlExDevice_t deviceHandle, unsigned int link, mxSmlExMetaXLinkDeviceType_t* type);

#define MXSMLEX_FI_DEV_METAXLINK_LINK_COUNT 91             //!< Field value enums used to query MetaXLink number

typedef union MxSmlExValue {
    double dVal;
    int siVal;
    signed long long sllVal;
    unsigned int uiVal;
    unsigned long ulVal;
    unsigned long long ullVal;
} mxSmlExValue_t;

/**
 * @brief Represents MetaXLink's remote device type
 */
typedef enum MxSmlExValueType
#ifdef __cplusplus
 : unsigned int
#endif
{
    MXSMLEX_VALUE_TYPE_DOUBLE = 0,
    MXSMLEX_VALUE_TYPE_UNSIGNED_INT = 1,
    MXSMLEX_VALUE_TYPE_UNSIGNED_LONG = 2,
    MXSMLEX_VALUE_TYPE_UNSIGNED_LONG_LONG = 3,
    MXSMLEX_VALUE_TYPE_SIGNED_LONG_LONG = 4,
    MXSMLEX_VALUE_TYPE_SIGNED_INT = 5,
    MXSMLEX_VALUE_TYPE_COUNT
} mxSmlExValueType_t;

/**
 * @brief Information for a field value sample
 */
typedef struct MxSmlExFieldValue
{
    unsigned int fieldId;
    long long latencyUsec;
    mxSmlExReturn_t mxSmlExReturn;
    unsigned int scopeId;
    long long timestamp;
    mxSmlExValue_t value;
    mxSmlExValueType_t valueType;
} mxSmlExFieldValue_t;

/**
 * @brief request values for a list of fields for a device
 *
 * @param[in] deviceHandle : the device handle
 * @param[in] valuesCount : number of entries in values that should be retrieved
 * @param[in] values : array of valuesCount structures to hold field values
 *
 * @details Each value's fieldId must be populated prior to this call
 *
 * @retval MXSMLEX_SUCCESS                     call was successful
 * @retval MXSMLEX_ERROR_INVALID_ARGUMENT      deviceHandle is invalid or values is null
 * @retval MXSMLEX_ERROR_UNKNOWN               unexpected error
*/
mxSmlExReturn_t DECLDIR mxSmlExDeviceGetFieldValues(mxsmlExDevice_t deviceHandle, int valuesCount, mxSmlExFieldValue_t* values);

/**
 * @brief Sets the ideal affinity for the calling thread and device
 *
 * @param[in] deviceHandle : the device handle
 *
 * @retval MXSMLEX_SUCCESS                      call was successful
 * @retval MXSMLEX_ERROR_INVALID_ARGUMENT       deviceHandle is invalid
 * @retval MXSMLEX_ERROR_UNKNOWN                unexpected error
 */
mxSmlExReturn_t DECLDIR mxSmlExDeviceSetCpuAffinity(mxsmlExDevice_t deviceHandle);

/**
 * Information for Sample
 */
typedef struct MxSmlExSample
{
    unsigned long long timeStamp;       //!< CPU Timestamp in microseconds
    mxSmlExValue_t sampleValue;         //!< Sample Value
}mxSmlExSample_t;

#ifdef __cplusplus
}
#endif

#endif // __MXSML_EXTENSION_H__
