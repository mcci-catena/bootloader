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

#include <stdint.h>

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
/// \brief Erase a region of internal flash
///
/// \param [in] targetAddress	base address of region to erase
/// \param [in] targetSize	number of bytes to erase
///
/// \p targetAddress and \b targetSize must match the alignment
/// restritctons of the platform hardware.
///
/// \return \c true if region was successfully erased.
///
typedef bool
(McciBootloaderPlatform_SystemFlashEraseFn_t)(
	volatile const void *targetAddress,
	size_t targetSize
	);

///
/// \brief Program a chunk of internal flash
///
/// \param [in] pDestination	base address of region to program
/// \param [in] pSource		base address of data to write (in RAM,
///				for maximum portability)
/// \param [in] nBytes		number of bytes to copy
///
/// \p pDestination and \b nBytes must match the alignment
/// restritctons of the platform hardware. 4k is normally a good
/// block size.
///
/// \return \c true if region was successfully programmed.
///
typedef bool
(McciBootloaderPlatform_SystemFlashWriteFn_t)(
	volatile const void *pDestination,
	const void *pSource,
	size_t nBytes
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

/// \brief error codes from SVC handler on ARMv6-M systems & such like
typedef enum McciBootloaderPlatform_ARMv6M_SvcError_e
	{
	/// successful processing
	McciBootloaderPlatform_SvcError_OK = 0,

	/// error: verify failure
	McciBootloaderPlatform_SvcError_VerifyFailure = UINT32_C(-3),
	/// error: invalid parameter to SVC
	McciBootloaderPlatform_SvcError_InvalidParameter = UINT32_C(-2),
	/// error: SVC isn't just unimplemented, it's unkown to the bootloader
	McciBootloaderPlatform_SvcError_Unclaimed = UINT32_C(-1),
	} McciBootloaderPlatform_ARMv6M_SvcError_t;

MCCIADK_C_ASSERT(sizeof(McciBootloaderPlatform_ARMv6M_SvcError_t) == sizeof(uint32_t));

/// \brief SVC request codes for boot loader on ARMv6-M systems & such like
typedef enum McciBootloaderPlatform_ARMv6M_SvcRq_e
	{
	/// Fetch pointer to \c uint32_t "update" flag in EEPROM. \c arg1 is pointer to cell to
	/// receive pointer.
	McciBootloaderPlatform_ARMv6M_SvcRq_GetUpdatePointer = UINT32_C(0x01000000),
	/// Call \ref mcci_tweetnacl_hashblocks_sha512_init. \c arg1 is pointer to hash block.
	McciBootloaderPlatform_ARMv6M_SvcRq_HashInit  /* = UINT32_C(0x01000001) */,

	/// Call \ref mcci_tweetnacl_hashblocks_sha512. \c arg1 points to argument.
	/// \see McciBootloaderPlatform_ARMv6M_SvcRq_HashBlocks_Arg_t
	McciBootloaderPlatform_ARMv6M_SvcRq_HashBlocks  /* = UINT32_C(0x01000002) */,

	/// Call \ref mcci_tweetnacl_hashblocks_finish. \c arg1 points to
	/// argument.
	/// \see McciBootloaderPlatform_ARMv6M_SvcRq_HashFinish_Arg_t
	McciBootloaderPlatform_ARMv6M_SvcRq_HashFinish  /* = UINT32_C(0x01000003) */,

	/// Call \ref mcci_tweetnacl_verify64. \c arg1 and \c arg2 are the pointers
	/// result is set to verifyFailure for failure.
	McciBootloaderPlatform_ARMv6M_SvcRq_Verify64  /* = UINT32_C(0x01000004) */,
	} McciBootloaderPlatform_ARMv6M_SvcRq_t;

MCCIADK_C_ASSERT(sizeof(McciBootloaderPlatform_ARMv6M_SvcRq_t) == sizeof(uint32_t));

/// \brief argument to \ref McciBootloaderPlatform_ARMv6M_SvcRq_HashBlocks
typedef struct McciBootloaderPlatform_ARMv6M_SvcRq_HashBlocks_Arg_s
	{
	void *pHash;
	const uint8_t *pMessage;
	size_t nMessage;
	} McciBootloaderPlatform_ARMv6M_SvcRq_HashBlocks_Arg_t;

/// \brief argument to \ref McciBootloaderPlatform_ARMv6M_SvcRq_HashFinish
typedef struct McciBootloaderPlatform_ARMv6M_SvcRq_HashFinish_Arg_s
	{
	void *pHash;
	const uint8_t *pMessage;
	size_t nMessage;
	size_t nOverall;
	} McciBootloaderPlatform_ARMv6M_SvcRq_HashFinish_Arg_t;

///
/// \brief SVC function interface
///
/// \param [in] svcRequest is the request code.
/// \param [in] pErrorCode points to a cell to be filled with the error code
///		(According to the value of \p svcRequest, there may additional
///		OUT parameters)
/// \param [in] arg1 is an extra argument, interpreted according to \p svcRequest
/// \param [in] arg2 is an extra argument, interpreted according to \p svcRequest
///
/// \details
///	This definition lets us take advantage of the ARMv6-M and related
///	implementations; exception handlers are just like regular subroutines
///	(except that results have to be passed back by modifying the saved
///	registers on the stack). We work around this by passing results back
///	in memory.
///
typedef void
(McciBootloaderPlatform_ARMv6M_SvcHandlerFn_t)(
	McciBootloaderPlatform_ARMv6M_SvcRq_t svcRequest,
	McciBootloaderPlatform_ARMv6M_SvcError_t *pErrorCode,
	uint32_t arg1,
	uint32_t arg2
	);

MCCI_BOOTLOADER_END_DECLS
#endif /* _mcci_bootloader_platform_types_h_ */
