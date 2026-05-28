/*

Module:	mcci_bootloader_board_catena_1sj_eeprom.h

Function:
	Layout of Bootloader EEPROM for Catenas based on Murata 1SJ modules with STM32L0.

Copyright and License:
	This file copyright (C) 2026 by

		MCCI Corporation
		3520 Krums Corners Road
		Ithaca, NY  14850

	See accompanying LICENSE file for copyright and license information.

Author:
	Terry Moore, MCCI Corporation	May 2026

*/

#ifndef _mcci_bootloader_board_catena_1sj_eeprom_h_
#define _mcci_bootloader_board_catena_1sj_eeprom_h_	/* prevent multiple includes */

#pragma once

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

///
/// \brief symbolic type for Catena EEPROM image.
///
typedef struct McciBootloaderBoard_Catena1sj_Eeprom_s
McciBootloaderBoard_Catena1sj_Eeprom_t;

///
/// \brief layout of Catena EEPROM image
///
/// We place an image of this at the end of the data EEPROM section for
/// the SoC.
///
struct McciBootloaderBoard_Catena1sj_Eeprom_s
	{
	uint32_t	fUpdateRequest;	///< the update request.
	};

// we don't want to use any external headers other than stdint.h, so
// provide a compile assert macro
#define MCCI_BOOTLOADER_EEPROM_STATIC_ASSERT(e) \
 void  MCCI_BOOTLOADER_EEPROM_STATIC_ASSERT__(int MCCI_BOOTLOADER_EEPROM_STATIC_ASSERT_x[(e) ? 1: -1])

// make sure the structure is the right size
MCCI_BOOTLOADER_EEPROM_STATIC_ASSERT(
	sizeof(McciBootloaderBoard_Catena1sj_Eeprom_t) == 4
	);

/// \brief mark the beginning of a bootloader EEPROM section
#define	MCCI_BOOTLOADER_CATENA_1SJ_EEPROM_MAGIC_BEGIN	(('T' << 24) | ('O' << 16) | ('O' << 8) | 'B')

/// \brief mark the end of a bootloader EEPROM section
#define	MCCI_BOOTLOADER_CATENA_1SJ_EEPROM_MAGIC_END	(('t' << 24) | ('o' << 16) | ('p' << 8) | 'b')

/// \brief the distinguished "update request" value
#define	MCCI_BOOTLOADER_CATENA_1SJ_EEPROM_UPDATE_REQUEST	UINT32_C(0xFFFFFFFF)

#ifdef __cplusplus
}
#endif

#endif /* _mcci_bootloader_board_catena_1sj_eeprom_h_ */
