/*

Module:	mcci_bootloader_board_catena_abz.h

Function:
	Top-level platform interface for MCCI Catenas based on the
	Murata type-ABZ module with the STM32L0.

Copyright and License:
	This file copyright (C) 2021 by

		MCCI Corporation
		3520 Krums Corners Road
		Ithaca, NY  14850

	See accompanying LICENSE file for copyright and license information.

Author:
	Terry Moore, MCCI Corporation	March 2021

*/

#ifndef _mcci_bootloader_board_catena_abz_h_
#define _mcci_bootloader_board_catena_abz_h_	/* prevent multiple includes */

#pragma once

#ifndef _mcci_bootloader_types_h_
# include "mcci_bootloader_types.h"
#endif

#ifndef _mcci_bootloader_platform_h_
# include "mcci_bootloader_platform.h"
#endif

#ifndef _mcci_bootloader_stm32l0_h_
# include "mcci_bootloader_stm32l0.h"
#endif

#ifndef _mcci_bootloader_board_catena_abz_eeprom_h_
# include "mcci_bootloader_board_catena_abz_eeprom.h"
#endif

MCCI_BOOTLOADER_BEGIN_DECLS

/****************************************************************************\
|
|	SPI Flash layout
|
\****************************************************************************/

/// \brief the maximum image size is 168k bytes (192k - 20k for the bootloader
///	and 4k for the mfg page).
#define	MCCI_BOOTLOADER_BOARD_CATENA_ABZ_STORAGE_IMAGE_SIZE	\
		(UINT32_C(168) * 1024)

/// \brief we put the fallback image at 64k to 232k, in case anyone needs
///	special things in page zero. This also lets you set the WP bit,
///	clear the TP bit, and set BP bits to 0x03; this will protect the
///	first 256k against accidental change.
#define	MCCI_BOOTLOADER_BOARD_CATENA_ABZ_STORAGE_FALLBACK_BASE	\
		(UINT32_C(65536))

///
/// \brief base address of the update image
///
/// \details The update block begins at a multiple of 64k to allow use
///	of 64k erase if desired. We put it at 256k so we can easily 
///	write-protect the fallback image if needed.
///
#define	MCCI_BOOTLOADER_BOARD_CATENA_ABZ_STORAGE_UPDATE_BASE	\
		(UINT32_C(256) * 1024)

/****************************************************************************\
|
|	API functions.
|
\****************************************************************************/

McciBootloaderPlatform_SystemInitFn_t 
McciBootloaderBoard_CatenaAbz_systemInit;

McciBootloaderPlatform_PrepareForLaunchFn_t
McciBootloaderBoard_CatenaAbz_prepareForLaunch;

McciBootloaderPlatform_FailFn_t MCCI_BOOTLOADER_NORETURN_PFX
McciBootloaderBoard_CatenaAbz_fail 
MCCI_BOOTLOADER_NORETURN_SFX;

McciBootloaderPlatform_DelayMsFn_t
McciBootloaderBoard_CatenaAbz_delayMs;

McciBootloaderPlatform_GetUpdateFlagFn_t
McciBootloaderBoard_CatenaAbz_getUpdate;

McciBootloaderPlatform_SetUpdateFlagFn_t
McciBootloaderBoard_CatenaAbz_setUpdate;

McciBootloaderPlatform_StorageReadFn_t
McciBootloaderBoard_CatenaAbz_storageRead;

McciBootloaderPlatform_GetPrimaryStorageAddressFn_t
McciBootloaderBoard_CatenaAbz_getPrimaryStorageAddress;

McciBootloaderPlatform_GetFallbackStorageAddressFn_t
McciBootloaderBoard_CatenaAbz_getFallbackStorageAddress;

McciBootloaderPlatform_SpiInitFn_t
McciBootloaderBoard_CatenaAbz_spiInit;

McciBootloaderPlatform_SpiTransferFn_t
McciBootloaderBoard_CatenaAbz_spiTransfer;

McciBootloaderPlatform_AnnunciatorInitFn_t
McciBootloaderBoard_CatenaAbz_annunciatorInit;

McciBootloaderPlatform_AnnunciatorIndicateStateFn_t
McciBootloaderBoard_CatenaAbz_annunciatorIndicateState;

void McciBootloaderBoard_CatenaAbz_clearLed(void);
void McciBootloaderBoard_CatenaAbz_handleSysTick(void);
void McciBootloaderBoard_CatenaAbz_setLed(void);

MCCI_BOOTLOADER_END_DECLS

#endif /* _mcci_bootloader_board_catena_abz_h_ */
