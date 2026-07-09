/*

Module:	mcci_bootloader_board_stm32h7b3i_dk.h

Function:
	Top-level platform interface for STM32H7B3I_DK.

Copyright and License:
	This file copyright (C) 2021 by

		MCCI Corporation
		3520 Krums Corners Road
		Ithaca, NY  14850

	See accompanying LICENSE file for copyright and license information.

Author:
	ChaeHee Won, MCCI Corporation	June 2021

*/

#ifndef _mcci_bootloader_board_stm32h7b3i_dk_h_
#define _mcci_bootloader_board_stm32h7b3i_dk_h_	/* prevent multiple includes */

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

#ifndef _mcci_bootloader_board_stm32h7b3i_dk_request_h_
# include "mcci_bootloader_board_stm32h7b3i_dk_request.h"
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
#define	MCCI_BOOTLOADER_BOARD_STM32H7B3I_DK_STORAGE_IMAGE_SIZE	\
	(UINT32_C(1024) * 1024)

///
/// \brief base address of the update image in flash bank 2.
///
/// \details Defined by the linker script.
///
extern const uint8_t gk_McciBootloaderBoard_Stm32h7b3iDk_UpdateImageBase[];

///
/// \brief base address of the fallback image (bank 2, 512k to 1024k).
///
/// \details Defined by the linker script.
///
extern const uint8_t gk_McciBootloaderBoard_Stm32h7b3iDk_FallbackImageBase[];


/****************************************************************************\
|
|	API functions.
|
\****************************************************************************/

McciBootloaderPlatform_SystemInitFn_t
McciBootloaderBoard_Stm32h7b3iDk_systemInit;

McciBootloaderPlatform_PrepareForLaunchFn_t
McciBootloaderBoard_Stm32h7b3iDk_prepareForLaunch;

McciBootloaderPlatform_FailFn_t MCCI_BOOTLOADER_NORETURN_PFX
McciBootloaderBoard_Stm32h7b3iDk_fail
MCCI_BOOTLOADER_NORETURN_SFX;

McciBootloaderPlatform_DelayMsFn_t
McciBootloaderBoard_Stm32h7b3iDk_delayMs;

McciBootloaderPlatform_GetMillisecondsFn_t
McciBootloaderBoard_Stm32h7b3iDk_getMilliseconds;

McciBootloaderPlatform_GetUpdateFlagFn_t
McciBootloaderBoard_Stm32h7b3iDk_getUpdate;

McciBootloaderPlatform_SetUpdateFlagFn_t
McciBootloaderBoard_Stm32h7b3iDk_setUpdate;

McciBootloaderPlatform_StorageInitFn_t
McciBootloaderBoard_Stm32h7b3iDk_storageInit;

McciBootloaderPlatform_StorageReadFn_t
McciBootloaderBoard_Stm32h7b3iDk_storageRead;

McciBootloaderPlatform_GetPrimaryStorageAddressFn_t
McciBootloaderBoard_Stm32h7b3iDk_getPrimaryStorageAddress;

McciBootloaderPlatform_GetFallbackStorageAddressFn_t
McciBootloaderBoard_Stm32h7b3iDk_getFallbackStorageAddress;

McciBootloaderPlatform_AnnunciatorInitFn_t
McciBootloaderBoard_Stm32h7b3iDk_annunciatorInit;

McciBootloaderPlatform_AnnunciatorIndicateStateFn_t
McciBootloaderBoard_Stm32h7b3iDk_annunciatorIndicateState;

void McciBootloaderBoard_Stm32h7b3iDk_annunciatorHandleSysTick(void);
void McciBootloaderBoard_Stm32h7b3iDk_clearLed(void);
void McciBootloaderBoard_Stm32h7b3iDk_handleSysTick(void);
void McciBootloaderBoard_Stm32h7b3iDk_setLed(void);

McciBootloaderBoard_Stm32h7b3iDk_Request_t *
McciBootloaderBoard_Stm32h7b3iDk_getRequestPointer(void);

MCCI_BOOTLOADER_END_DECLS

#endif /* _mcci_bootloader_board_stm32h7b3i_dk_h_ */
