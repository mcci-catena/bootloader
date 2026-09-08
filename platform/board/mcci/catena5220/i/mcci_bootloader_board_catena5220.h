/*

Module:	mcci_bootloader_board_catena5220.h

Function:
	Definitions for bootloader on MCCI Catena 5220.

Copyright and License:
	This file copyright (C) 2026 by

		MCCI Corporation
		3520 Krums Corners Road
		Ithaca, NY  14850

	See accompanying LICENSE file for copyright and license information.

Author:
	Pranau Ravikumar, MCCI Corporation	September 2026

*/

#ifndef _mcci_bootloader_board_catena5220_h_
#define _mcci_bootloader_board_catena5220_h_	/* prevent multiple includes */

#pragma once

#include "mcci_bootloader_platform.h"
#include "mcci_bootloader_board_catena_1sj.h"

MCCI_BOOTLOADER_BEGIN_DECLS

McciBootloaderPlatform_StorageInitFn_t
McciBootloaderBoard_Catena5220_storageInit;

MCCI_BOOTLOADER_END_DECLS

#endif /* _mcci_bootloader_board_catena5220_h_ */
