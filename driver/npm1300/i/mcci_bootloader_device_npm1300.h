/*

Module:	mcci_bootloader_device_npm1300.h

Function:
	Data structures for driver for NPM1300 PMIC.

Copyright and License:
	This file copyright (C) 2026 by

		MCCI Corporation
		3520 Krums Corners Road
		Ithaca, NY  14850

	See accompanying LICENSE file for copyright and license information.

Author:
	Terry Moore, MCCI Corporation	June 2026

*/

#ifndef _mcci_bootloader_device_npm1300_h_
#define _mcci_bootloader_device_npm1300_h_	/* prevent multiple includes */

#pragma once

#ifndef _mcci_bootloader_device_h_
# include "mcci_bootloader_device.h"
#endif

#ifndef _mcci_bootloader_device_i2c_bus_types_h_
# include "mcci_bootloader_device_i2c_bus_types.h"
#endif

#ifndef _mcci_bootloader_device_i2c_device_types_h_
# include "mcci_bootloader_device_i2c_device_types.h"
#endif

#ifndef _mcci_bootloader_device_npm1300_types_h_
# include "mcci_bootloader_device_npm1300_types.h"
#endif

struct McciBootloaderDeviceNpm1300_Contents_s
	{
	McciBootloaderDevice_CONTENTS;

	/// @brief the underlying I2C device for the PMIC.
	McciBootloaderDeviceI2cDevice_t *pI2cDevice;
	};

#define	McciBootloaderDeviceNpm1300_CONTENTS	\
	McciBootloaderDeviceNpm1300_Contents_t	Npm1300

union McciBootloaderDeviceNpm1300_u
	{
	McciBootloaderDevice_UNION;
	McciBootloaderDeviceNpm1300_Contents_t	Npm1300;
	};

#define	McciBootloaderDeviceNpm1300_UNION			\
	McciBootloaderDevice_UNION;				\
	McciBootloaderDeviceNpm1300_Contents_t	Npm1300;	\
	McciBootloaderDeviceNpm1300_t		Npm1300Cast

/// structure for initializeing the PMIC1300.
struct McciBootloaderDriver_NPM1300_Init_s
	{
	uint16_t	address;	//< internal address of the register
	uint8_t		value;		//< value to be written to the register
	};


// methods are all non-virtual

///
/// @brief static method: create and attach an NPM1300 device object, returning its address
///
/// @param pI2cBus [in] the bus to be used to connect
/// @param pI2cDeviceForPmic [out] a pointer to an uninitialized i2c device object to be initialized and used for the attachment
/// @param sizeI2cDeviceForPmic [in] size in bytes of the objectc at \c pI2cDeviceForPmic
///
/// @return pointer to (statically allocated) NPM1300 device object, or NULL in case of errors.
///
/// @note This routine has only one device object allocated. If it ever returns non-NULL, subsequent calls will fail
///	(because the routine won't reuse the existing block). The device address is fixed at 0x6b, as that's the only
///	address supported by the NPM1300.
///
McciBootloaderDeviceNpm1300_t *
McciBootloaderDriver_NPM1300_createAndAttach(
	McciBootloaderDeviceI2cBus_t		*pI2cBus,
	McciBootloaderDeviceI2cDevice_t		*pI2cDeviceForPmic,
	size_t					sizeI2cDeviceForPmic
	);

///
/// @brief initialize NPM1300 registers according to table.
///
/// @param pPmic [in]		points to the PMIC device object
/// @param pvInitValues 	points to an array of address/value pairs
/// @param nInitValues 		count of entries in the array of ninit values.
///
/// @return \c true for success, \c false for any I2C error.
///
bool
McciBootloaderDevice_NPM1300_initializeRegisters(
	McciBootloaderDeviceNpm1300_t *pPmic,
	const McciBootloaderDriver_NPM1300_Init_t *pvInitValues,
	size_t nInitValues
	);

#ifdef __cplusplus
}
#endif

#endif /* _mcci_bootloader_device_npm1300_h_ */
