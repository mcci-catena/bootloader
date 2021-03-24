/*

Module:	mcci_bootloader_platform_types.h

Function:
	Types for MCCI bootloader platform interface

Copyright and License:
	This file copyright (C) 2021 by

		MCCI Corporation
		3520 Krums Corners Road
		Ithaca, NY  14850

	See accompanying LICENSE file for copyright and license information.

Author:
	Terry Moore, MCCI Corporation	March 2021

*/

#ifndef _mcci_bootloader_platform_types_h_
#define _mcci_bootloader_platform_types_h_	/* prevent multiple includes */

#pragma once

#ifndef _mcci_bootloader_types_h_
# include "mcci_bootloader_types.h"
#endif

MCCI_BOOTLOADER_BEGIN_DECLS

///
/// \brief function type for platform intialization function
///
/// \details Functions of this type are called by the bootloader after
///	RAM has been initialized. The function should set the system
///	clock speed set up any "always needed" peripherals.
///
typedef	void (McciBootloaderPlatform_SystemInitFn_t)(void);

///
/// \brief function type for preparing to launch an application
///
/// \details The bootloader calls this function just before jumping
///	to the application. The function is required to return the
///	platform to a reset-like state (making the bootloader
///	maximally transparent).
///
typedef	void (McciBootloaderPlatform_PrepareForLaunchFn_t)(void);

///
/// \brief function for reporting a fatal error
///
/// \param [in] errorCode failure reason.
///
/// \details If a fatal error occurs during the boot, the bootloader
///	calls this function, which must not return. If possible, the
///	function displays the errorCode in a platform-specific way.
///
/// \note
///	Although it would be nice to decorate the type with "noreturn",
///	that's not possible in C. But we can mark a function that
///	calls this as no-return, and then use __builtin_notreached()
///	in that function.
///
typedef void
(McciBootloaderPlatform_FailFn_t)(
	McciBootloaderError_t errorCode
	);

///
/// \brief delay execution
///
/// \param [in] ms number of milliseconds to delay
///
/// \details The bootloader calls this function in order to delay
///	execution by the specified number of milliseconds. The implementation
///	may delay longer, but apart errors due to clock inaccuracies, it
///	should not return appreciably before the specified number of
///	milliseconds has elapsed.
///
typedef void
(McciBootloaderPlatform_DelayMsFn_t)(
	uint32_t ms
	);

///
/// \brief Get the "update flag"
///
/// The bootloader needs to know if an update has been requested; no
/// point in scanning storage if we have not been asked to do so.
///
/// \returns \c true if we should attempt to update flash from storage, \c false
///	otherwise.
///
typedef bool
(McciBootloaderPlatform_GetUpdateFlagFn_t)(
	void
	);

///
/// \brief Set the "update flag"
///
/// Set the value of the "update flag"
///
/// \param [in] state \c true if next boot should attempt to update flash from
///		storage, \c false otherwise.
///
/// \see McciBootloaderPlatform_getUpdateFlagFn_t
///
typedef void
(McciBootloaderPlatform_SetUpdateFlagFn_t)(
	bool
	);

///
/// \brief Initialize the storage driver.
///
/// The bootloader calls this prior to doing the first storage access.
/// Portable drivers can use the SPI APIs to do their work, and should
/// in turn initialize the SPI driver.
///
/// \see McciBootloader_SpiInitFn
///
typedef void
(McciBootloaderPlatform_StorageInitFn_t)(
	void
	);

///
/// \brief Read bytes from the storage
///
/// \param [in] startAddress	starting byte address on the storage of data
///				to be read.
/// \param [in] pBuffer		pointer to buffer to be filled.
/// \param [in] nBuffer		number of bytes to read.
///
/// This API is implemented by the storage chip drivers. Often, the storage
/// chip will have restrictions in terms of address offset and block read
/// length. The parameters fed to the boot loader and the fact that it reads
/// 4k blocks (only) should allow most constraints to be honored.
///
/// \return \c true if all data was successfully read, \c false if there was
///	an error
///
typedef bool
(McciBootloaderPlatform_StorageReadFn_t)(
	McciBootloaderStorageAddress_t startAddress,
	uint8_t *pBuffer,
	size_t nBuffer
	);

///
/// \brief get the start address of the primary image in the storage
///
typedef McciBootloaderStorageAddress_t
(McciBootloaderPlatform_GetPrimaryStorageAddressFn_t)(
	void
	);

///
/// \brief get the start address of the fallback image in the storage
///
typedef McciBootloaderStorageAddress_t
(McciBootloaderPlatform_GetFallbackStorageAddressFn_t)(
	void
	);

///
/// \brief initialize the SPI driver for storage use
///
/// \note This API is only called if a driver decides it intends to use SPI.
///
typedef void
(McciBootloaderPlatform_SpiInitFn_t)(
	void
	);

///
/// \brief send/receive data over the SPI bus
///
/// \param [out] pRx points to the receive data buffer, if not NULL.
/// \param [in] pTx points to the transmit data buffer, if not NULL.
/// \param [in] nBytes is the number of bytes to transfer.
/// \param [in] fContinue indicates whether the chip select is to be left
///		active after the operation. If \c true, then the chip
///		select is left active, otherwise it's made inactive.
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
typedef void
(McciBootloaderPlatform_SpiTransferFn_t)(
	uint8_t *pRx,
	const uint8_t *pTx,
	size_t nBytes,
	bool fContinue
	);

///
/// \brief Initialize the annuciator system
///
/// Some boot operations are quite slow. So we allow for a platform to use
/// the tick interrupt and output information to the user as to how things
/// are going. This call is made before any state declarations are made to
/// the annunciator.
///
typedef void
(McciBootloaderPlatform_AnnunciatorInitFn_t)(
	void
	);

///
/// \brief Indicate the current state
///
/// \param [in] state	the current boot state
///
/// Update the curent state for use by the annunciator.
///
typedef void
(McciBootloaderPlatform_AnnunciatorIndicateStateFn_t)(
	McciBootloaderState_t state
	);

/// \brief storage interface structure
typedef struct McciBootloaderPlatform_StorageInterface_s
McciBootloaderPlatform_StorageInterface_t;

/// \brief SPI interface structure
typedef struct McciBootloaderPlatform_SpiInterface_s
McciBootloaderPlatform_SpiInterface_t;

/// \brief annunciator interface structure
typedef struct McciBootloaderPlatform_AnnunciatorInterface_s
McciBootloaderPlatform_AnnunciatorInterface_t;


/// \brief top-level interface structure
typedef struct McciBootloaderPlatform_Interface_s
McciBootloaderPlatform_Interface_t;

MCCI_BOOTLOADER_END_DECLS
#endif /* _mcci_bootloader_platform_types_h_ */
