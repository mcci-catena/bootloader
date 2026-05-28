/*

Module:	mcci_bootloader_board_catena5230.h

Function:
	Definitions for bootloader on MCCI Catena 5230.

Copyright and License:
	This file copyright (C) 2026 by

		MCCI Corporation
		3520 Krums Corners Road
		Ithaca, NY  14850

	See accompanying LICENSE file for copyright and license information.

Author:
	Terry Moore, MCCI Corporation	May 2026

*/

#ifndef _mcci_bootloader_board_catena5230_h_
#define _mcci_bootloader_board_catena5230_h_	/* prevent multiple includes */

#pragma once

#include "mcci_bootloader_platform.h"
#include "mcci_bootloader_board_catena_1sj.h"

MCCI_BOOTLOADER_BEGIN_DECLS

McciBootloaderPlatform_SystemInitFn_t
McciBootloaderBoard_Catena5230_systemInit;

McciBootloaderPlatform_PrepareForLaunchFn_t
McciBootloaderBoard_Catena5230_prepareForLaunch;

McciBootloaderPlatform_StorageInitFn_t
McciBootloaderBoard_Catena5230_storageInit;

MCCI_BOOTLOADER_END_DECLS

#endif /* _mcci_bootloader_board_catena5230_h_ */
