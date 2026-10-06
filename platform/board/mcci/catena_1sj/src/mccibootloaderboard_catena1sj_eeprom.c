/*

Module:	mccibootloaderboard_catena1sj_eeprom.c

Function:
	EEPROM variables and accessors for bootloader for Catenas based on 1SJ
	and STM32L0.

Copyright and License:
	This file copyright (C) 2026 by

		MCCI Corporation
		3520 Krums Corners Road
		Ithaca, NY  14850

	See accompanying LICENSE file for copyright and license information.

Author:
	Terry Moore, MCCI Corporation	March 2026

*/

#include "mcci_bootloader_board_catena_1sj.h"
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

McciBootloaderBoard_Catena1sj_Eeprom_t *
McciBootloaderBoard_Catena1sj_getEepromPointer()
	{
	///
	/// \brief base address of the bootloader EEPROM region (linker-defined).
	///
	/// \details
	///	This is hidden in this function because linker-defined symbols
	///	are not really type-safe; so we use an accessor.
	///
	extern volatile uint8_t g_McciBootloaderBoard_Catena1sj_EepromBase[];

	/* convert to a pointer to the eeprom */
	return (McciBootloaderBoard_Catena1sj_Eeprom_t *)
			&g_McciBootloaderBoard_Catena1sj_EepromBase[0];
	}

bool
McciBootloaderBoard_Catena1sj_getUpdate(void)
	{
	const McciBootloaderBoard_Catena1sj_Eeprom_t * const pEeprom = McciBootloaderBoard_Catena1sj_getEepromPointer();

	if (pEeprom->fUpdateRequest == MCCI_BOOTLOADER_CATENA_1SJ_EEPROM_UPDATE_REQUEST)
		return true;
	else
		return false;
	}

void
McciBootloaderBoard_Catena1sj_setUpdate(bool fRequest)
	{
	const McciBootloaderBoard_Catena1sj_Eeprom_t * const pEeprom = McciBootloaderBoard_Catena1sj_getEepromPointer();
	uint32_t dwValue = fRequest ? MCCI_BOOTLOADER_CATENA_1SJ_EEPROM_UPDATE_REQUEST
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

	// the EEPROM should erase first, if needed.
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

/**** end of mccibootloaderboard_catena1sj_eeprom.c ****/
