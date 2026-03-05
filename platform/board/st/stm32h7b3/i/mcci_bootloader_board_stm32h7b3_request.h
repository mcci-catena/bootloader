/*

Module:	mcci_bootloader_board_stm32h7b3_request.h

Function:
	Layout of Bootloader update request image on STM32H7B3.

Copyright and License:
	This file copyright (C) 2021 by

		MCCI Corporation
		3520 Krums Corners Road
		Ithaca, NY  14850

	See accompanying LICENSE file for copyright and license information.

Author:
	ChaeHee Won, MCCI Corporation	June 2021

*/

#ifndef _mcci_bootloader_board_stm32h7b3_request_h_
#define _mcci_bootloader_board_stm32h7b3_request_h_	/* prevent multiple includes */

#pragma once

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

///
/// \brief symbolic type for STM32H7B3 update request image.
///
typedef struct McciBootloaderBoard_Stm32h7b3_Request_s
McciBootloaderBoard_Stm32h7b3_Request_t;

///
/// \brief layout of STM32H7B3 update request image
///
/// We place an image of this at the end of the application image.
///
extern void *gk_McciBootloader_RequestBase;

struct McciBootloaderBoard_Stm32h7b3_Request_s
	{
	uint32_t	MagicBegin;
	uint32_t	fUpdateRequest;	///< the update request.
	uint32_t	Reserved;
	uint32_t	MagicEnd;
	};

// we don't want to use any external headers other than stdint.h, so
// provide a compile assert macro
#define MCCI_BOOTLOADER_REQUEST_STATIC_ASSERT(e) \
 void  MCCI_BOOTLOADER_REQUEST_STATIC_ASSERT__(int MCCI_BOOTLOADER_REQUEST_STATIC_ASSERT_x[(e) ? 1: -1])

// make sure the structure is the right size
MCCI_BOOTLOADER_REQUEST_STATIC_ASSERT(
	sizeof(McciBootloaderBoard_Stm32h7b3_Request_t) == 16
	);

/// \brief mark the beginning of a bootloader REQUEST section
#define	MCCI_BOOTLOADER_STM32H7B3_REQUEST_MAGIC_BEGIN	(('T' << 24) | ('O' << 16) | ('O' << 8) | 'B')

/// \brief mark the end of a bootloader REQUEST section
#define	MCCI_BOOTLOADER_STM32H7B3_REQUEST_MAGIC_END	(('t' << 24) | ('o' << 16) | ('p' << 8) | 'b')

/// \brief the distinguished "update request" value
#define	MCCI_BOOTLOADER_STM32H7B3_REQUEST_UPDATE_REQUEST	UINT32_C(0xFFFFFFFF)

#ifdef __cplusplus
}
#endif

#endif /* _mcci_bootloader_board_stm32h7b3_request_h_ */
