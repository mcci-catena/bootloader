/*

Module:	mcci_bootloader_stm32l0.h

Function:
	MCCI Bootloader STM32L0 functions

Copyright and License:
	This file copyright (C) 2021 by

		MCCI Corporation
		3520 Krums Corners Road
		Ithaca, NY  14850

	See accompanying LICENSE file for copyright and license information.

Author:
	fullname, MCCI Corporation	March 2021

*/

#ifndef _mcci_bootloader_stm32l0_h_
#define _mcci_bootloader_stm32l0_h_	/* prevent multiple includes */

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

/****************************************************************************\
|
|	API functions
|
\****************************************************************************/

void McciBootloader_Stm32L0_systemInit(void);

#ifdef __cplusplus
}
#endif

#endif /* _mcci_bootloader_stm32l0_h_ */
