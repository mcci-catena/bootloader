/*

Module:	mcci_bootloader_board_model491x.h

Function:
	Definitions for bootloader on MCCI Catena 491x boards.

Copyright and License:
	This file copyright (C) 2023 by

		MCCI Corporation
		3520 Krums Corners Road
		Ithaca, NY  14850

	See accompanying LICENSE file for copyright and license information.

Author:
	Dhinesh Kumar Pitchai, MCCI Corporation	September 2023

*/

#ifndef _mcci_bootloader_board_model491x_h_
#define _mcci_bootloader_board_model491x_h_	/* prevent multiple includes */

#pragma once

#include "mcci_bootloader_platform.h"
#include "mcci_bootloader_board_catena_abz.h"

MCCI_BOOTLOADER_BEGIN_DECLS

McciBootloaderPlatform_StorageInitFn_t
McciBootloaderBoard_Model491x_storageInit;

MCCI_BOOTLOADER_END_DECLS

#endif /* _mcci_bootloader_board_model491x_h_ */
