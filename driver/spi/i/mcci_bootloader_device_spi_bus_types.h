/*

Module:	mcci_bootloader_device_spi_bus_types.h

Function:
	Types for SPI bus driver

Copyright and License:
	This file copyright (C) 2026 by

		MCCI Corporation
		3520 Krums Corners Road
		Ithaca, NY  14850

	See accompanying LICENSE file for copyright and license information.

Author:
	Terry Moore, MCCI Corporation	May 2026

*/

#ifndef _mcci_bootloader_device_spi_bus_types_h_
#define _mcci_bootloader_device_spi_bus_types_h_	/* prevent multiple includes */

#pragma once

#ifndef _mcci_bootloader_device_types_h_
# include "mcci_bootloader_device_types.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

typedef struct McciBootloaderDeviceSpiBusMethods_s McciBootloaderDeviceSpiBusMethods_t;
typedef union McciBootloaderDeviceSpiBus_u McciBootloaderDeviceSpiBus_t;
typedef struct McciBootloaderDeviceSpiBus_Contents_s McciBootloaderDeviceSpiBus_Contents_t;

///
/// \brief send/receive data over the SPI bus
///
/// \param [in] pBus points to the constrol object.
/// \param [out] pRx points to the receive data buffer, if not NULL.
/// \param [in] pTx points to the transmit data buffer, if not NULL.
/// \param [in] nBytes is the number of bytes to transfer.
/// \param [in] fContinue indicates whether the chip select is to be left
///		active after the operation. If \c true, then the chip
///		select is left active, otherwise it's made inactive.
///
/// \return \c true for success, \c false for failure.
///
/// \details
///	This API writes and reads data from the SPI bus, optionally leaving the
///	target device selected.
///
///	\p nBytes bytes of data are transferred from the buffer at \p pTx to
///	the SPI bus, and at the same time are received from the SPI bus to
///	the buffer at \p pRx.
///
///	The parameters \p pRx and \p pTx are optional. If \c NULL, bytes are
///	discarded or zeroes inserted, respectively.
///
///	This API is provided so we can write portable storage chip drivers
///	that use the SPI bus. It's not used directly by the outer logic
///	of the bootloader.
///
typedef bool (McciBootloaderDeviceSpiBus_TransferFn_t)(McciBootloaderDeviceSpiBus_t *pBus, uint8_t *pRx, const uint8_t *pTx, size_t nBytes, bool fContinue);

#ifdef __cplusplus
}
#endif

#endif /* _mcci_bootloader_device_spi_bus_types_h_ */
