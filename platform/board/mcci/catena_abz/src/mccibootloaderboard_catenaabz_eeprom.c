/*

Module:	mccibootloaderboard_catenaabz_eeprom.c

Function:
	EEPROM variables and accessors for bootloader for Catenas based on ABZ
	and STM32L0.

Copyright and License:
	This file copyright (C) 2021 by

		MCCI Corporation
		3520 Krums Corners Road
		Ithaca, NY  14850

	See accompanying LICENSE file for copyright and license information.

Author:
	Terry Moore, MCCI Corporation	March 2021

*/

#include "mcci_bootloader_board_catena_abz.h"
#include "mcci_stm32l0xx.h"

/****************************************************************************\
|
|	Manifest constants & typedefs.
|
\****************************************************************************/


/****************************************************************************\
|
|	Read-only data.
|
\****************************************************************************/



/****************************************************************************\
|
|	Variables.
|
\****************************************************************************/

McciBootloaderBoard_CatenaAbz_Eeprom_t *
McciBootloaderBoard_CatenaAbz_getEepromPointer()
	{
	extern void *g_McciBootloader_BootEepromBase;

	/* convert to a pointer to the eeprom */
	return (McciBootloaderBoard_CatenaAbz_Eeprom_t *)
			&g_McciBootloader_BootEepromBase;
	}

bool
McciBootloaderBoard_CatenaAbz_getUpdate(void)
	{
	const McciBootloaderBoard_CatenaAbz_Eeprom_t * const pEeprom = McciBootloaderBoard_CatenaAbz_getEepromPointer();

	if (pEeprom->fUpdateRequest == MCCI_BOOTLOADER_CATENA_ABZ_EEPROM_UPDATE_REQUEST)
		return true;
	else
		return false;
	}

void
McciBootloaderBoard_CatenaAbz_setUpdate(bool fRequest)
	{
	const McciBootloaderBoard_CatenaAbz_Eeprom_t * const pEeprom = McciBootloaderBoard_CatenaAbz_getEepromPointer();
	uint32_t dwValue = fRequest ? MCCI_BOOTLOADER_CATENA_ABZ_EEPROM_UPDATE_REQUEST
				  : 0;

	// if it's already set to the right value, just return.
	if (pEeprom->fUpdateRequest == dwValue)
		return;

	// spin waiting for an operation
	while (McciArm_getReg(MCCI_STM32L0_REG_FLASH_SR) & MCCI_STM32L0_REG_FLASH_SR_BSY)
		/* loop */;

	// unlock
	McciArm_putReg(MCCI_STM32L0_REG_FLASH_PEKEYR, MCCI_STM32L0_REG_FLASH_PEKEYR_UNLOCK1);
	McciArm_putReg(MCCI_STM32L0_REG_FLASH_PEKEYR, MCCI_STM32L0_REG_FLASH_PEKEYR_UNLOCK2);

	// the EEPROM should erase first, if needed; select the data EEPROM.
	McciArm_putRegOr(
		MCCI_STM32L0_REG_FLASH_PECR,
		MCCI_STM32L0_REG_FLASH_PECR_DATA
		);

	// write data
	McciArm_putReg((uint32_t)&pEeprom->fUpdateRequest, dwValue);

	// wait for operation to complete
	while (McciArm_getReg(MCCI_STM32L0_REG_FLASH_SR) & MCCI_STM32L0_REG_FLASH_SR_BSY)
		/* loop */;

	// re-lock
	McciArm_putRegOr(
		MCCI_STM32L0_REG_FLASH_PECR,
		MCCI_STM32L0_REG_FLASH_PECR_PELOCK
		);
	}

/**** end of mccibootloaderboard_catenaabz_eeprom.c ****/
