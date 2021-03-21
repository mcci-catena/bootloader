/* mcci_bootloader_types.h	Mon Jun 29 2020 10:14:36 tmm */

/*

Module:  mcci_bootloader_types.h

Function:
	Format of on-media data for the MCCI bootloader.

Version:
	V0.1.0	Mon Jun 29 2020 10:14:36 tmm	Edit level 1

Copyright notice:
	This file copyright (C) 2020 by

		MCCI Corporation
		3520 Krums Corners Road
		Ithaca, NY  14850

	An unpublished work.  All rights reserved.

	This file is proprietary information, and may not be disclosed or
	copied without the prior permission of MCCI Corporation.

Author:
	Terry Moore, MCCI Corporation	June 2020

Revision history:
   0.1.0  Mon Jun 29 2020 10:14:36  tmm
	Module created.

*/

#ifndef _MCCI_BOOTLOADER_TYPES_H_		/* prevent multiple includes */
#define _MCCI_BOOTLOADER_TYPES_H_

#include "mcciadk_env.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdarg.h>

/****************************************************************************\
|
|	Environmental basics
|
\****************************************************************************/

#ifdef __cplusplus
# define	MCCI_BOOTLOADER_BEGIN_DECLS	extern "C" {
# define	MCCI_BOOTLOADER_END_DECLS	}
#else
# define	MCCI_BOOTLOADER_BEGIN_DECLS	/* nothing */
# define	MCCI_BOOTLOADER_END_DECLS	/* nothing */
#endif

#ifdef _MSC_VER
# define MCCI_BOOTLOADER_NORETURN_PFX	__declspec(noreturn)
# define MCCI_BOOTLOADER_NORETURN_SFX	/* nothing */
#else
# define MCCI_BOOTLOADER_NORETURN_PFX	/* nothing */
# define MCCI_BOOTLOADER_NORETURN_SFX	__attribute__((__noreturn__))
#endif

#define	MCCI_BOOTLOADER_NOT_REACHED()	__builtin_unreachable()

/****************************************************************************\
|
|	Scalar types and type handles.
|
\****************************************************************************/

MCCI_BOOTLOADER_BEGIN_DECLS

///
/// \brief error codes for the bootloader
///
/// \see McciBootloaderError_e
///
typedef uint32_t McciBootloaderError_t;

MCCI_BOOTLOADER_END_DECLS
#endif /* _MCCI_BOOTLOADER_TYPES_H_ */
