/*

Module:	mcci_bootloader_cm0plus.h

Function:
	Definitions for MCCI Bootloader on ARM CM0plus systems

Copyright and License:
	This file copyright (C) 2021 by

		MCCI Corporation
		3520 Krums Corners Road
		Ithaca, NY  14850

	See accompanying LICENSE file for copyright and license information.

Author:
	Terry Moore, MCCI Corporation	March 2021

*/

#ifndef _mcci_bootloader_cm0plus_h_
#define _mcci_bootloader_cm0plus_h_	/* prevent multiple includes */

#pragma once

#include "mcci_arm_cm0plus.h"
#include "mcci_bootloader_cm0plus_appimage.h"

#ifdef __cplusplus
extern "C" {
#endif

/****************************************************************************\
|
|	Globals
|
\****************************************************************************/

///
/// \brief the CortexM0 vectors for the boot loader.
///
/// \details
///	The vectors are put in section \c .McciBootloader_Vectors -- be
///	sure to research the link script when making changes here.
///
/// \see mccibootloader.ld
///
extern const McciBootloader_CortexPageZero_t
gk_McciBootloader_CortexVectors
__attribute__((__section__(".McciBootloader_Vectors")));

/****************************************************************************\
|
|	End of file
|
\****************************************************************************/


#ifdef __cplusplus
}
#endif

#endif /* _mcci_bootloader_cm0plus_h_ */
