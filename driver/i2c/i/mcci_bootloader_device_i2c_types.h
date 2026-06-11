/*

Module:	mcci_bootloader_device_i2c_types.h

Function:
	Common types for I2C work.

Copyright and License:
	This file copyright (C) 2026 by

		MCCI Corporation
		3520 Krums Corners Road
		Ithaca, NY  14850

	See accompanying LICENSE file for copyright and license information.

Author:
	Terry Moore, MCCI Corporation	June 2026

*/

#ifndef _mcci_bootloader_device_i2c_types_h_
#define _mcci_bootloader_device_i2c_types_h_	/* prevent multiple includes */

#pragma once

#ifndef _mcci_bootloader_device_types_h_
# include "mcci_bootloader_device_types.h"
#endif


#ifdef __cplusplus
extern "C" {
#endif

/// I2C bus address. Could be 10 bits someday, so we use a uint16_t.
typedef	uint16_t McciBootloaderDeviceI2cAddress_t;

#ifdef __cplusplus
}
#endif

#endif /* _mcci_bootloader_device_i2c_types_h_ */
