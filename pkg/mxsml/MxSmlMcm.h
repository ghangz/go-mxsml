/*** MXSML VERSION: 2.3.1 ***/
/**
 * Copyright © 2024 MetaX Integrated Circuits (Shanghai) Co., Ltd. All Rights Reserved.
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

#ifndef __MX_SML_MCM_H__
#define  __MX_SML_MCM_H__

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @file MxSmlMcm.h
 *
 * @brief Main header file for mxsml.
 * All required function, structure, enum, etc. definitions should be defined in this file.
 *
 */

#include "MxSml.h"

#define MAX_DIE_NUM 2      //!< Guaranteed maximum die count on one device

/**
 * @brief Get number of dies in device
 *
 * @param[in]  deviceId : the device index
 * @param[out] dieCount : the number of device dies
 *
 * @retval MXSML_Success            call was successful
 * @retval MXSML_InvalidDeviceId    deviceId is out of range
 */
mxSmlReturn_t DECLDIR mxSmlGetDeviceDieCount(unsigned int deviceId, unsigned int* dieCount);

/**
 * @brief Get device memory usage information
 *
 * @param[in]  deviceId : the device index
 * @param[in]  dieId : the die index
 * @param[out] memoryInfo : return memory information (KB)
 *
 * @retval MXSML_Success            call was successful
 * @retval MXSML_InvalidDeviceId    deviceId is out of range
 * @retval MXSML_InvalidDieId       dieId is out of range
 * @retval MXSML_InvalidInput       memoryInfo is null
 * @retval MXSML_SysfsError         read sysfs file failure
 */
mxSmlReturn_t DECLDIR mxSmlGetDieMemoryInfo(unsigned int deviceId, unsigned int dieId, mxSmlMemoryInfo_t* memoryInfo);

/**
 * @brief Get the current temperature readings for the device, in degress C
 *
 * @param[in]  deviceId : the device index
 * @param[in]  dieId : the die index
 * @param[in]  temperatureType : flag that indicates which temperature reading to get
 * @param[out] temperature : reference in which to return the temperature reading
 *
 * @retval MXSML_Success                call was successful
 * @retval MXSML_InvalidDeviceId        deviceId is out of range
 * @retval MXSML_InvalidDieId           dieId is out of range
 * @retval MXSML_InvalidInput           temperature is null
 * @retval MXSML_OperationNotSupport    the operation is not support on target device
 * @retval MXSML_SysfsError             read sysfs file failure
 */
mxSmlReturn_t DECLDIR mxSmlGetDieTemperatureInfo(unsigned int deviceId, unsigned int dieId, mxSmlTemperatureSensors_t temperatureType,
    int* temperature);

/**
 * @brief Get pmbus info for specified pmbus unit
 *
 * @param[in]  deviceId : the device index
 * @param[in]  dieId : the die index
 * @param[in]  pmbusUnit : the pmbus unit
 * @param[out] pmbusInfo : return the pmbus info
 *
 * @retval MXSML_Success                call was successful
 * @retval MXSML_InvalidDeviceId        deviceId is out of range
 * @retval MXSML_InvalidDieId           dieId is out of range
 * @retval MXSML_InvalidInput           pmbusInfo is null
 * @retval MXSML_OperationNotSupport    the operation is not support on target device
 * @retval MXSML_SysfsError             read sysfs file failure
 */
mxSmlReturn_t DECLDIR mxSmlGetDiePmbusInfo(unsigned int deviceId, unsigned int dieId, mxSmlPmbusUnit_t pmbusUnit, mxSmlPmbusInfo_t* pmbusInfo);

/**
 * @brief Get device version
 *
 * @param[in]  deviceId : the device index
 * @param[in]  dieId : the die index
 * @param[in]  versionUnit : unit
 * @param[out] version : version of unit
 * @param[in,out] size : length of version
 *
 * @details the guaranteed maximum possible size is 64
 *
 * @retval MXSML_Success                call was successful
 * @retval MXSML_InvalidDeviceId        deviceId is out of range
 * @retval MXSML_InvalidDieId           dieId is out of range
 * @retval MXSML_InvalidInput           versionUnit in invalid, or version or size is null
 * @retval MXSML_InsufficientSize       size is not large enough but size return the minimal version size
 * @retval MXSML_SysfsError             read sysfs file failure
 */
mxSmlReturn_t DECLDIR mxSmlGetDeviceDieVersion(unsigned int deviceId, unsigned int dieId, mxSmlVersionUnit_t versionUnit, char* version,
    unsigned int* size);

/**
 * @brief Get clock frequencies specified by the clock type
 *
 * @param[in]  deviceId : the device index
 * @param[in]  dieId : the die index
 * @param[in]  clockIp : identify which clock domain to query
 * @param[in,out]  clocksSize : the size of the clocksMhz array that is safe to access
 * @param[out] clocksMhz : return the clock frequency information in MHz
 *
 * @details clocksSize:
 *          csc[4], xcore[1], mc0[3], mc1[3], vpue[1], vpud[4], soc[1], dnoc[1], ccx[1]
 *
 * @retval MXSML_Success                call was successful
 * @retval MXSML_InvalidDeviceId        deviceId is out of range
 * @retval MXSML_InvalidDieId           dieId is out of range
 * @retval MXSML_OperationNotSupport    the operation is not support on target device
 * @retval MXSML_InvalidInput           clocksSize or clocksMhz is nullptr or clockIp is not valid for target device
 * @retval MXSML_InsufficientSize       clocksSize is not large enough but infoSize return the minimal array size
 * @retval MXSML_SysfsError             read sysfs file failure
 */
mxSmlReturn_t DECLDIR mxSmlGetDieClocks(
        unsigned int deviceId, unsigned int dieId, mxSmlClockIp_t clockIp, unsigned int* clocksSize, unsigned int* clocksMhz);

/**
 * @brief Get die chip serial
 *
 * @param[in]  deviceId : the device indexs
 * @param[in]  dieId : the die index
 * @param[out] chipSerial : chip serial
 * @param[in,out] size : length of chip serial
 *
 * @details the guaranteed maximum possible size is 32
 *
 * @retval MXSML_Success            call was successful
 * @retval MXSML_InvalidDeviceId    deviceId is out of range
 * @retval MXSML_InvalidInput       chipSerial or size is null
 * @retval MXSML_InsufficientSize   size is not large enough but size return the minimal required size
 * @retval MXSML_SysfsError         read sysfs file failure
 * @retval MXSML_InvalidDieId       dieId is out of range
 */
mxSmlReturn_t DECLDIR mxSmlGetDieChipSerial(unsigned int deviceId, unsigned int dieId, char* chipSerial, unsigned int* size);

/**
 * @brief Get die IP usage
 *
 * @param[in] deviceId : the device index
 * @param[in] dieId : the die index
 * @param[in] ip : device ip
 * @param[out] usage : return device usage
 *
 * @retval MXSML_Success            call was successful
 * @retval MXSML_InvalidDeviceId    deviceId is out of range
 * @retval MXSML_SysfsError         read sysfs file failure
 * @retval MXSML_InvalidDieId       dieId is out of range
 */
mxSmlReturn_t DECLDIR mxSmlGetDieIpUsage(unsigned int deviceId, unsigned int dieId, mxSmlUsageIp_t ip, int* usage);

/**
 * @brief Get die xcore ap usage toggle
 *
 * @param[in] deviceId : the device index
 * @param[in] dieId : the die index
 * @param[out] apUsageToggle : the xcore ap usage toggle: 0(disable) 1(enable)
 *
 * @retval MXSML_Success                call was successful
 * @retval MXSML_InvalidDeviceId        deviceId is out of range
 * @retval MXSML_InvalidInput           apUsageToggle is null
 * @retval MXSML_OperationNotSupport    the operation is not support on target device
 * @retval MXSML_SysfsError             open sysfs file failure
 * @retval MXSML_InvalidDieId           dieId is out of range
 */
mxSmlReturn_t DECLDIR mxSmlGetDieApUsageToggle(unsigned int deviceId, unsigned int dieId, unsigned int* apUsageToggle);

/**
 * @brief Get die current DPM ip perf level
 *
 * @param[in] deviceId : the device index
 * @param[in] dieId : the die index
 * @param[in] dpmIp : the dpm ip
 * @param[out] dpmIpPerfLevel : dpm ip perf level
 *
 * @retval MXSML_Success            call was successful
 * @retval MXSML_InvalidDeviceId    deviceId is out of range
 * @retval MXSML_SysfsError         read sysfs file failure
 * @retval MXSML_InvalidInput       dpmIpPerfLevel is null
 * @retval MXSML_InvalidDieId       dieId is out of range
 */
mxSmlReturn_t DECLDIR mxSmlGetCurrentDieDpmIpPerfLevel(unsigned int deviceId, unsigned int dieId, mxSmlDpmIp_t dpmIp, unsigned int* dpmIpPerfLevel);

/**
 * @brief Get dpm IP's max performance level
 *
 * @param[in] deviceId : the device index
 * @param[in] dieId : the die index
 * @param[in] dpmIp : the target IP
 * @param[out] dpmMaxLevel : return the max dpm performance level
 *
 * @retval MXSML_Success                call was successful
 * @retval MXSML_InvalidDeviceId        deviceId is out of range
 * @retval MXSML_InvalidDieId           dieId is out of range
 * @retval MXSML_InvalidInput           dpmIp is invalid or dpmMaxLevel is null
 * @retval MXSML_OperationNotSupport    the operation is not support on target device
 * @retval MXSML_SysfsError             read sysfs file failure
 */
mxSmlReturn_t DECLDIR mxSmlGetDieDpmIpMaxPerfLevel(unsigned int deviceId, unsigned int dieId, mxSmlDpmIp_t dpmIp, unsigned int* dpmMaxLevel);

/**
 * @brief Get die current encoder and decoder codec status
 *
 * @param[in]  deviceId : the device index
 * @param[in]  dieId : the die index
 * @param[out] codecStatus : return codec status
 *
 * @retval MXSML_Success            call was successful
 * @retval MXSML_InvalidDeviceId    deviceId is out of range
 * @retval MXSML_SysfsError         read sysfs file failure
 * @retval MXSML_InvalidInput       codecStatus is nulls
 * @retval MXSML_InvalidDieId       dieId is out of range
 */
mxSmlReturn_t DECLDIR mxSmlGetDieCodecStatus(unsigned int deviceId, unsigned int dieId, mxSmlCodecStatus_t* codecStatus);

/**
 * @brief Get device die xcore ap usage
 *
 * @param[in] deviceId : the device index
 * @param[in] dieId : the die index
 * @param[out] apUsage : return each AP's usage
 * @param[in,out] size : size of apUsage array, return the actual num of AP usage
 * @param[in,out] dpcNum : size of dpc
 *
 * @retval MXSML_Success              call was successful
 * @retval MXSML_InvalidDeviceId      deviceId is out of range
 * @retval MXSML_InvalidDieId         dieId is out of range
 * @retval MXMSL_InvalidInput         apUsage or size or dpcNum is null
 * @retval MXSML_InsufficientSize     size or dpcNum is not large enough but size or dpcNum return the minimal size
 * @retval MXSML_OperationNotSupport  the operation is not support on target device
 * @retval MXSML_SysfsError           read sysfs file failure
*/
mxSmlReturn_t DECLDIR mxSmlGetDieXcoreApUsage(unsigned int deviceId, unsigned int dieId, unsigned int* apUsage, unsigned int* size,
    unsigned int* dpcNum);

/**
 * @brief Get die Eeprom information
 *
 * @param[in]  deviceId :   the device index
 * @param[in]  dieId :      the die index
 * @param[out] eepromInfo : return Eeprom information
 *
 * @retval MXSML_Success            call was successful
 * @retval MXSML_InvalidDeviceId    deviceId is out of range
 * @retval MXSML_SysfsError         read sysfs file failure
 * @retval MXSML_InvalidInput       eepromInfo is invalid
 * @retval MXSML_InvalidDieId       dieId is out of range
 */
mxSmlReturn_t DECLDIR mxSmlGetDieEepromInfo(unsigned int deviceId, unsigned int dieId, mxSmlEepromInfo_t* eepromInfo);

/**
 * @brief Get die ecc state
 *
 * @param[in] deviceId : the device index
 * @param[in] dieId : the die index
 * @param[out] eccState : the ecc state: 0(disable) 1(enable)
 *
 * @retval MXSML_Success                call was successful
 * @retval MXSML_InvalidDeviceId        deviceId is out of range
 * @retval MXSML_InvalidDieId           dieId is out of range
 * @retval MXSML_InvalidInput           eccState is null
 * @retval MXSML_OperationNotSupport    the operation is not support on target device
 * @retval MXSML_SysfsError             open sysfs file failure
 */
mxSmlReturn_t DECLDIR mxSmlGetDieEccState(unsigned int deviceId, unsigned int dieId, unsigned int* eccState);

/**
 * @brief Get die power state for target IP
 *
 * @param[in] deviceId : the device index
 * @param[in] dieId : the die index
 * @param[in] dpmIp : the target IP
 * @param[out] powerState : power state for the target IP
 * @param[in,out] size : size of power state array that is safe to access
 *
 * @details the power state array size set as 8 is large enough
 *
 * @retval MXSML_Success            call was successful
 * @retval MXSML_InvalidDeviceId    deviceId is out of range
 * @retval MXSML_InvalidDieId       dieId is out of range
 * @retval MXSML_SysfsError         read sysfs file failure
 * @retval MXSML_InvalidInput       powerState or size is null or dpmIp is invalid in target device
 * @retval MXSML_InsufficientSize   size is not large enough but size return the minimal power state array size
 */
mxSmlReturn_t DECLDIR mxSmlGetDiePowerStateInfo(unsigned int deviceId, unsigned int dieId, mxSmlDpmIp_t dpmIp, int* powerState, unsigned int* size);

/**
 * @brief Get die hbm bandwidth
 *
 * @param[in] deviceId : the device index
 * @param[in] dieId : the die index
 * @param[out] hbmBandWidth : return Hbm bandwidth(MBytes/s)
 *
 * @retval MXSML_Success                call was successful
 * @retval MXSML_InvalidDeviceId        deviceId is out of range
 * @retval MXSML_InvalidDieId           dieId is out of range
 * @retval MXSML_OperationNotSupport    the operation is not support on target device
 * @retval MXSML_InvalidInput           hbmBandWidth is null
 * @retval MXSML_SysfsError             read sysfs file failure
 */
mxSmlReturn_t DECLDIR mxSmlGetDieHbmBandWidth(unsigned int deviceId, unsigned int dieId, mxSmlHbmBandWidth_t* hbmBandWidth);

/**
 * @brief Get die pptable version
 *
 * @param[in] deviceId : the device index
 * @param[in] dieId : the die index
 * @param[in] size : the size of version that is safe to access
 * @param[out] version : return device version
 *
 * @details the recommended size is 5, the fomat of version is like 0001
 *
 * @retval MXSML_Success            call was successful
 * @retval MXSML_InvalidDeviceId    deviceId is out of range
 * @retval MXSML_InvalidDieId       dieId is out of range
 * @retval MXSML_InvalidInput       version is null or size is 0
 * @retval MXSML_InsufficientSize   size is not large enough
 * @retval MXSML_SysfsError         read sysfs file failure
 * @retval MXSML_SysfsWriteError    write sysfs file failure
 */
mxSmlReturn_t DECLDIR mxSmlGetDiePptableVersion(unsigned int deviceId, unsigned int dieId, unsigned int size, char* version);

/**
 * @brief Get die data from RAS status register
 *
 * @param[in]   deviceId : the device index
 * @param[in]   dieId : the die index
 * @param[out]  rasStatusData : RAS status register data
 *
 * @retval MXSML_Success            call was successful
 * @retval MXSML_InvalidDeviceId    deviceId is out of range
 * @retval MXSML_InvalidDieId       dieId is out of range
 * @retval MXSML_SysfsError         open/read sysfs file failure
 */
mxSmlReturn_t DECLDIR mxSmlGetDieRasStatusData(unsigned int deviceId, unsigned int dieId, mxSmlRasStatusData_t* rasStatusData);

/**
 * @brief Get die data from RAS error counter
 *
 * @param[in]   deviceId : the device index
 * @param[in]   dieId : the die index
 * @param[out]  rasErrorData : RAS error register data
 *
 * @retval MXSML_Success            call was successful
 * @retval MXSML_InvalidDeviceId    deviceId is out of range
 * @retval MXSML_InvalidDieId       dieId is out of range
 * @retval MXSML_SysfsError         open/read sysfs file failure
 */
mxSmlReturn_t DECLDIR mxSmlGetDieRasErrorData(unsigned int deviceId, unsigned int dieId, mxSmlRasErrorData_t* rasErrorData);

/**
 * @brief This structure holds the info of a remote device connected to MetaXLink for MCM
*/
typedef struct MxSmlMcmMetaXLinkRemoteInfo {
    int deviceId;
    char bdfId[DEVICE_BDF_ID_SIZE];
    unsigned int dieId;
} mxSmlMcmMetaXLinkRemoteInfo_t;
/*
 * @brief Get die MetaXLink remote device info
 *
 * @param[in] deviceId : the device index
 * @param[in] dieId : the die index
 * @param[in] linkId : the link index
 * @param[out] remote : return the info of a remote device connected to target MetaXLink
 *
 * @retval MXSML_Success                call was successful
 * @retval MXSML_InvalidDeviceId        deviceId is out of range
 * @retval MXSML_InvalidDieId           dieId is out of range
 * @retval MXSML_NoDevice               No device was discovered for target link id
 * @retval MXSML_OperationNotSupport    the operation is not support on target device
 * @retval MXSML_InvalidInput           remote is null
 * @retval MXSML_SysfsError             open sysfs file failure
 * @retval MXSML_Failure                any unexpected failure
*/
mxSmlReturn_t DECLDIR mxSmlGetDieMetaXLinkRemoteInfo(unsigned int deviceId, unsigned int dieId, unsigned int linkId,
    mxSmlMcmMetaXLinkRemoteInfo_t* remote);

/**
 * @brief Get die dma bandwidth(MBytes/s)
 *
 * @param[in] deviceId : the device index
 * @param[in] dieId : the die index
 * @param[out] dmaBandwidth : the dma bandwidth(MBytes/s)
 * @param[in,out] size : the num of dma bandwidth
 *
 * @details the num of dma bandwidth is 4 for N-class device, and is 5 for C-class device
 *
 * @retval MXSML_Success                call was successful
 * @retval MXSML_InvalidDeviceId        deviceId is out of range
 * @retval MXSML_InvalidDieId           dieId is out of range
 * @retval MXSML_InvalidInput           dmaBandwidth is null or size is 0
 * @retval MXSML_OperationNotSupport    the operation is not support on target device
 * @retval MXSML_SysfsError             open sysfs file failure
 */
mxSmlReturn_t DECLDIR mxSmlGetDieDmaBandwidth(unsigned int deviceId, unsigned int dieId, mxSmlDmaEngineBandwidth_t* dmaBandwidth,
    unsigned int* size);

/**
 * @brief Set die xcore ap usage toggle for MXC device
 *
 * @param[in] deviceId : the device index
 * @param[in] dieId : the die index
 * @param[in] toggle : the state to be set: 0(disable) 1(enable)
 *
 * @retval MXSML_Success                call was successful
 * @retval MXSML_InvalidDeviceId        deviceId is out of range
 * @retval MXSML_InvalidDieId           dieId is out of range
 * @retval MXSML_OperationNotSupport    the operation is not support on target device
 * @retval MXSML_SysfsError             open sysfs file failure
 * @retval MXSML_SysfsWriteError        write sysfs file failure
 */
mxSmlReturn_t DECLDIR mxSmlSetDieApUsageToggle(unsigned int deviceId, unsigned int dieId, int toggle);

/**
 * @brief Get die unavailable reason
 *
 * @param[in] deviceId : the device index
 * @param[in] dieId : the die index
 * @param[in,out] reason : the die unavailable reason
 *
 * @details the guaranteed maximum possible size is 64
 *
 * @retval MXSML_Success                call was successful
 * @retval MXSML_InvalidDeviceId        deviceId is out of range
 * @retval MXSML_InvalidDieId           dieId is out of range
 * @retval MXSML_InvalidInput           reason is null
 * @retval MXSML_SysfsError             open sysfs file failure
 * @retval MXSML_OperationNotSupport    the operation is not support on target device
*/
mxSmlReturn_t DECLDIR mxSmlGetDieUnavailableReason(unsigned int deviceId, unsigned int dieId, mxSmlDeviceUnavailableReasonInfo_t* reason);

/**
 * @brief Get die total ECC error counts
 *
 * @param[in] deviceId : the device index
 * @param[in] dieId : the die index
 * @param[out] eccCounts : the Ecc errors
 *
 * @retval MXSML_Success                call was successful
 * @retval MXSML_InvalidDeviceId        deviceId is out of range
 * @retval MXSML_InvalidDieId           dieId is out of range
 * @retval MXSML_InvalidInput           eccCounts is null
 * @retval MXSML_SysfsError             open sysfs file failure
 * @retval MXSML_OperationNotSupport    the operation is not support on target device
*/
mxSmlReturn_t DECLDIR mxSmlGetDieTotalEccErrors(unsigned int deviceId, unsigned int dieId, mxSmlEccErrorCount_t* eccCounts);

/**
 * @brief Get die current clocks throttling reasons
 *
 * @note More than one bit can be enabled at the same time. Multiple reasons can be affecting clocks at once.
 *
 * @param[in] deviceId : the device index
 * @param[in] dieId : the die index
 * @param[out] clocksThrottleReasons: Reference in which to return bitmask of active clocks throttle reasons
 *
 * @retval MXSML_Success                call was successful
 * @retval MXSML_InvalidDeviceId        deviceId is out of range
 * @retval MXSML_InvalidDieId           dieId is out of range
 * @retval MXSML_InvalidInput           clocksThrottleReasons is null
 * @retval MXSML_OperationNotSupport    the operation is not support on target device
 * @retval MXSML_SysfsError             open sysfs file failure
 *
 * @see mxsmlClocksThrottleReasons
 */
mxSmlReturn_t DECLDIR mxSmlGetDieCurrentClocksThrottleReason(unsigned int deviceId, unsigned int dieId, unsigned long long* clocksThrottleReasons);

#ifdef __cplusplus
}
#endif

#endif // __MX_SML_MCM_H__
