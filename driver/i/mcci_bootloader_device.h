/*

Module:	mcci_bootloader_device.h

Function:
	Driver interface object for all portable drivers

Copyright and License:
	This file copyright (C) 2026 by

		MCCI Corporation
		3520 Krums Corners Road
		Ithaca, NY  14850

	See accompanying LICENSE file for copyright and license information.

Author:
	Terry Moore, MCCI Corporation	May 2026

*/

#ifndef _mcci_bootloader_device_h_
#define _mcci_bootloader_device_h_	/* prevent multiple includes */

#pragma once

#ifndef _mcci_bootloader_types_h_
# include "mcci_bootloader_types.h"
#endif

#ifndef _mcci_bootloader_device_types_h_
# include "mcci_bootloader_device_types.h"
#endif

MCCI_BOOTLOADER_BEGIN_DECLS

struct McciBootloaderDeviceStatusFlags_s
	{
	uint32_t	fStarted: 1;	///< set \c true between ::begin and ::end.
	};

union McciBootloaderDeviceStatus_u
	{
	uint32_t			raw;	///< flag bits as a uint32 for easy zeroing.
	McciBootloaderDeviceStatusFlags_t flags; ///< individual flags.
	};

struct McciBootloaderDevice_Contents_s
	{
	/// pointer to device-level method table.
	const McciBootloaderDeviceMethods_t *pMethods;

	/// device status flags
	McciBootloaderDeviceStatus_t	status;
	};

union McciBootloaderDevice_u
	{
	McciBootloaderDevice_Contents_t	Device;
	};

#define McciBootloaderDevice_CONTENTS	\
	McciBootloaderDevice_Contents_t	Device

#define	McciBootloaderDevice_UNION			\
	McciBootloaderDevice_Contents_t	Device;		\
	McciBootloaderDevice_t		DeviceCast

///
/// @brief start operation of a given device
///
/// @param pDevice [in] device to be started, viewed generically.
///
/// @return \c true for success, \c false for failure.
///
/// @details
///	Although there is a \c McciBootloaderDeviceMethods_t::pBegin
///	function in the method table, this method is not intended
///	to be called by clients directly. Additional work is done by
///	the framework to maintain the started flag and check for
///	initialization.
///
///	Instead, clients call this function to start a device. If the
///	device has not been initialized, this function returns
///	fails. If the device has already been started, this function
///	succeeds without doing anything else. Otherwise, the device's
///	begin method is called (via the private table); if the method
///	succeeds, the device is marked started, and the function
///	returns success.
///
bool McciBootloaderDevice_begin(
	McciBootloaderDevice_t *pDevice
	);

///
/// @brief finish operation of a given device
///
/// @param pDevice [in] device to be stopped, viewed generically.
///
/// @return \c true for success, \c false for failure.
///
/// @details
///	Although there is a \c McciBootloaderDeviceMethods_t::pEnd
///	function in the method table, that method is not intended
///	to be called by clients directly. Additional work is done by
///	the framework to maintain the started flag and check for
///	initialization.
///
///	Instead, clients call this function to stp[] a device. If the
///	device has not been initialized, this function returns
///	fails. If the device has already been stopped, this function
///	succeeds without doing anything else. Otherwise, the device's
///	end method is called (via the private table); if the method
///	succeeds, the device is marked stopped, and the function
///	returns success. If the end method fails, the device is
///	left in an operational state.
///
bool McciBootloaderDevice_end(
	McciBootloaderDevice_t *pDevice
	);

MCCI_BOOTLOADER_END_DECLS

#endif /* _mcci_bootloader_device_h_ */
