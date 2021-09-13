/*

Module:	mcci_bootloader_board_stm32h7b3.h

Function:
	Top-level platform interface for STM32H7B3.

Copyright and License:
	This file copyright (C) 2021 by

		MCCI Corporation
		3520 Krums Corners Road
		Ithaca, NY  14850

	See accompanying LICENSE file for copyright and license information.

Author:
	ChaeHee Won, MCCI Corporation	June 2021

*/

#ifndef _mcci_bootloader_board_stm32h7b3_h_
#define _mcci_bootloader_board_stm32h7b3_h_	/* prevent multiple includes */

#pragma once

#ifndef _mcci_bootloader_types_h_
# include "mcci_bootloader_types.h"
#endif

#ifndef _mcci_bootloader_platform_h_
# include "mcci_bootloader_platform.h"
#endif

#ifndef _mcci_bootloader_stm32h7_h_
# include "mcci_bootloader_stm32h7.h"
#endif

#ifndef _mcci_stm32h7xx_h_
# include "mcci_stm32h7xx.h"
#endif

#ifndef _mcci_bootloader_board_stm32h7b3_request_h_
# include "mcci_bootloader_board_stm32h7b3_request.h"
#endif

MCCI_BOOTLOADER_BEGIN_DECLS

/****************************************************************************\
|
|	Flash layout
|
\****************************************************************************/

///
/// \brief the maximum image size is 1024k bytes at the bank2 flash
///
#define	MCCI_BOOTLOADER_BOARD_STM32H7B3_STORAGE_IMAGE_SIZE	\
	(UINT32_C(1024) * 1024)

///
/// \brief base address of the update image
///
/// \details The update block begins at the bank2.
///
#define	MCCI_BOOTLOADER_BOARD_STM32H7B3_STORAGE_UPDATE_BASE	\
	MCCI_STM32H7_MEMORY_FLASH2

///
/// \brief we put the fallback image at the bank2 512k to 1024k, in case anyone
///	needs special things in page zero.
///
#define	MCCI_BOOTLOADER_BOARD_STM32H7B3_STORAGE_FALLBACK_BASE	\
	(MCCI_STM32H7_MEMORY_FLASH2 + (UINT32_C(512) * 1024))


/****************************************************************************\
|
|	API functions.
|
\****************************************************************************/

McciBootloaderPlatform_SystemInitFn_t
McciBootloaderBoard_Stm32h7b3_systemInit;

McciBootloaderPlatform_PrepareForLaunchFn_t
McciBootloaderBoard_Stm32h7b3_prepareForLaunch;

McciBootloaderPlatform_FailFn_t MCCI_BOOTLOADER_NORETURN_PFX
McciBootloaderBoard_Stm32h7b3_fail
MCCI_BOOTLOADER_NORETURN_SFX;

McciBootloaderPlatform_DelayMsFn_t
McciBootloaderBoard_Stm32h7b3_delayMs;

McciBootloaderPlatform_GetUpdateFlagFn_t
McciBootloaderBoard_Stm32h7b3_getUpdate;

McciBootloaderPlatform_SetUpdateFlagFn_t
McciBootloaderBoard_Stm32h7b3_setUpdate;

McciBootloaderPlatform_StorageInitFn_t
McciBootloaderBoard_Stm32h7b3_storageInit;

McciBootloaderPlatform_StorageReadFn_t
McciBootloaderBoard_Stm32h7b3_storageRead;

McciBootloaderPlatform_GetPrimaryStorageAddressFn_t
McciBootloaderBoard_Stm32h7b3_getPrimaryStorageAddress;

McciBootloaderPlatform_GetFallbackStorageAddressFn_t
McciBootloaderBoard_Stm32h7b3_getFallbackStorageAddress;

McciBootloaderPlatform_AnnunciatorInitFn_t
McciBootloaderBoard_Stm32h7b3_annunciatorInit;

McciBootloaderPlatform_AnnunciatorIndicateStateFn_t
McciBootloaderBoard_Stm32h7b3_annunciatorIndicateState;

void McciBootloaderBoard_Stm32h7b3_clearLed(void);
void McciBootloaderBoard_Stm32h7b3_handleSysTick(void);
void McciBootloaderBoard_Stm32h7b3_setLed(void);

McciBootloaderBoard_Stm32h7b3_Request_t *
McciBootloaderBoard_Stm32h7b3_getRequestPointer(void);

MCCI_BOOTLOADER_END_DECLS

#endif /* _mcci_bootloader_board_stm32h7b3_h_ */
