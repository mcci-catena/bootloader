/*

Module:	mcci_bootloader_cm7.h

Function:
	Definitions for MCCI Bootloader on ARM CM7 systems

Copyright and License:
	This file copyright (C) 2021 by

		MCCI Corporation
		3520 Krums Corners Road
		Ithaca, NY  14850

	See accompanying LICENSE file for copyright and license information.

Author:
	ChaeHee Won, MCCI Corporation	June 2021

*/

#ifndef _mcci_bootloader_cm7_h_
#define _mcci_bootloader_cm7_h_	/* prevent multiple includes */

#pragma once

#include "mcci_arm_cm7.h"
#include "mcci_bootloader_cm7_appimage.h"

#ifdef __cplusplus
extern "C" {
#endif

/****************************************************************************\
|
|	Globals
|
\****************************************************************************/

///
/// \brief the CortexM7 vectors for the boot loader.
///
/// \details
///	The vectors are put in section \c .McciBootloader_Vectors -- be
///	sure to research the link script when making changes here.
///
/// \see mccibootloader.ld
///
extern const McciBootloader_CortexM7PageZero_t
gk_McciBootloader_CortexVectors
__attribute__((__section__(".McciBootloader_Vectors")));

///
/// \brief the application signature block
///
/// \details
///	The signature block is put in section \c .McciBootloader_Signature -- be
///	sure to research the link script when making changes here.
///
/// \see mccibootloader.ld
///
extern const McciBootloader_SignatureBlock_t
gk_McciBootloader_SignatureBlock
__attribute__((__section__(".McciBootloader_Signature")));

/****************************************************************************\
|
|	End of file
|
\****************************************************************************/


#ifdef __cplusplus
}
#endif

#endif /* _mcci_bootloader_cm7_h_ */
