/*

Module:	mcci_bootloader_platform.h

Function:
	Definitions for the platform API

Copyright and License:
	This file copyright (C) 2021 by

		MCCI Corporation
		3520 Krums Corners Road
		Ithaca, NY  14850

	See accompanying LICENSE file for copyright and license information.

Author:
	fullname, MCCI Corporation	March 2021

*/

#ifndef _mcci_bootloader_platform_h_
#define _mcci_bootloader_platform_h_	/* prevent multiple includes */

#pragma once

#ifndef _mcci_bootloader_platform_types_h_
# include "mcci_bootloader_platform_types.h"
#endif

MCCI_BOOTLOADER_BEGIN_DECLS

/// \brief interface for storage
struct McciBootloaderPlatform_StorageInterface_s
	{
	McciBootloaderPlatform_StorageInitFn_t		*pInit;				///< Initialize storage.
	McciBootloaderPlatform_StorageReadFn_t		*pRead;				///< Read from storage.
	McciBootloaderPlatform_GetPrimaryStorageAddressFn_t *pGetPrimaryAddress;		///< Get address of primary firmware region
	McciBootloaderPlatform_GetFallbackStorageAddressFn_t *pGetFallbackAddress;	///< Get address of fall-back firmware region.
	};

struct McciBootloaderPlatform_SpiInterface_s
	{
	McciBootloaderPlatform_SpiInitFn_t		*pInit;		///< Initialize SPI
	McciBootloaderPlatform_SpiTransferFn_t		*pTransfer;	///< do a SPI write/read.
	};

struct McciBootloaderPlatform_AnnunciatorInterface_s
	{
	McciBootloaderPlatform_AnnunciatorInitFn_t	*pInit;			///< initialize the annunciator system
	McciBootloaderPlatform_AnnunciatorIndicateStateFn_t *pIndicateState;	///< record the current state
	};

/// \brief interface structure to platform functions
struct McciBootloaderPlatform_Interface_s
	{
	McciBootloaderPlatform_SystemInitFn_t		*pSystemInit;		///< System init provider function
	McciBootloaderPlatform_PrepareForLaunchFn_t	*pPrepareForLaunch;	///< Prepare to launch application
	McciBootloaderPlatform_FailFn_t			*pFail;			///< Stop the boot, due to a failure
	McciBootloaderPlatform_DelayMsFn_t		*pDelayMs;		///< Delay execution some number of milliseconds
	McciBootloaderPlatform_GetUpdateFlagFn_t	*pGetUpdate;		///< Find out whether firmware update was requested
	McciBootloaderPlatform_SetUpdateFlagFn_t	*pSetUpdate;		///< Set value of firmware-update flag
	McciBootloaderPlatform_SystemFlashEraseFn_t	*pSystemFlashErase;	///< Erase flash
	McciBootloaderPlatform_SystemFlashWriteFn_t	*pSystemFlashWrite;	///< Write block to flash
	McciBootloaderPlatform_StorageInterface_t	Storage;
	McciBootloaderPlatform_SpiInterface_t		Spi;
	McciBootloaderPlatform_AnnunciatorInterface_t	Annunciator;
	};

extern const McciBootloaderPlatform_Interface_t
gk_McciBootloaderPlatformInterface;

static inline void
McciBootloaderPlatform_systemInit(void)
	{
	(*gk_McciBootloaderPlatformInterface.pSystemInit)();
	}

static inline void
McciBootloaderPlatform_prepareForLaunch(void)
	{
	(*gk_McciBootloaderPlatformInterface.pPrepareForLaunch)();
	}

static inline bool
McciBootloaderPlatform_getUpdateFlag(void)
	{
	return (*gk_McciBootloaderPlatformInterface.pGetUpdate)();
	}

static inline void
McciBootloaderPlatform_setUpdateFlag(bool fUpdate)
	{
	(*gk_McciBootloaderPlatformInterface.pSetUpdate)(fUpdate);
	}

static inline bool
McciBootloaderPlatform_systemFlashErase(
	volatile const void *targetAddress,
	size_t targetSize
	)
	{
	return (*gk_McciBootloaderPlatformInterface.pSystemFlashErase)(
		targetAddress, 
		targetSize
		);
	}

static inline bool
McciBootloaderPlatform_systemFlashWrite(
	volatile const void *pDestination,
	const void *pSource,
	size_t nBytes
	)
	{
	return (*gk_McciBootloaderPlatformInterface.pSystemFlashWrite)(
		pDestination,
		pSource,
		nBytes
		);
	}

void
MCCI_BOOTLOADER_NORETURN_PFX
McciBootloaderPlatform_fail(
	McciBootloaderError_t errorCode
	) MCCI_BOOTLOADER_NORETURN_SFX;

static inline void
McciBootloaderPlatform_delayMs(
	uint32_t ms
	)
	{
	(*gk_McciBootloaderPlatformInterface.pDelayMs)(ms);
	}

static inline void
McciBootloaderPlatform_storageInit(void)
	{
	(*gk_McciBootloaderPlatformInterface.Storage.pInit)();
	}

static inline bool
McciBootloaderPlatform_storageRead(
	McciBootloaderStorageAddress_t hAddress,
	uint8_t *pBuffer,
	size_t nBuffer
	)
	{
	return (*gk_McciBootloaderPlatformInterface.Storage.pRead)(
		hAddress,
		pBuffer,
		nBuffer
		);
	}

static inline McciBootloaderStorageAddress_t
McciBootloaderPlatform_getPrimaryStorageAddress(void)
	{
	return (*gk_McciBootloaderPlatformInterface.Storage.pGetPrimaryAddress)();
	}

static inline McciBootloaderStorageAddress_t
McciBootloaderPlatform_getFallbackStorageAddress(void)
	{
	return (*gk_McciBootloaderPlatformInterface.Storage.pGetFallbackAddress)();
	}

static inline void
McciBootloaderPlatform_spiInit(void)
	{
	(*gk_McciBootloaderPlatformInterface.Spi.pInit)();
	}

static inline void
McciBootloaderPlatform_spiTransfer(
	uint8_t *pRx,
	const uint8_t *pTx,
	size_t nBytes,
	bool fContinue
	)
	{
	(*gk_McciBootloaderPlatformInterface.Spi.pTransfer)(
		pRx, pTx, nBytes, fContinue
		);
	}

static inline void
McciBootloaderPlatform_annunciatorInit(void)
	{
	(*gk_McciBootloaderPlatformInterface.Annunciator.pInit)();
	}

static inline void
McciBootloaderPlatform_annunciatorIndicateState(
	McciBootloaderState_t state
	)
	{
	(*gk_McciBootloaderPlatformInterface.Annunciator.pIndicateState)(state);
	}

void
McciBootloaderPlatform_entry(void);

MCCI_BOOTLOADER_NORETURN_PFX
void
McciBootloaderPlatform_startApp(
	const void *pAppBase
	) MCCI_BOOTLOADER_NORETURN_SFX;

bool
McciBootloaderPlatform_checkImageValid(
	const void *pHeader,
	size_t nHeader,
	uintptr_t targetAddress,
	size_t targetSize
	);

const McciBootloader_AppInfo_t *
McciBootloaderPlatform_getAppInfo(
	const void *pHeader,
	size_t nHeader
	);

MCCI_BOOTLOADER_END_DECLS

#endif /* _mcci_bootloader_platform_h_ */
