/*

Module:	mccibootloader_image_version.h

Function:
	Version info for mccibootloader_image.

Copyright and License:
	This file copyright (C) 2021 by

		MCCI Corporation
		3520 Krums Corners Road
		Ithaca, NY  14850

	See accompanying LICENSE file for copyright and license information.

Author:
	fullname, MCCI Corporation	March 2021

*/

#ifndef _mccibootloader_image_version_h_
#define _mccibootloader_image_version_h_	/* prevent multiple includes */

#pragma once

#include "mccibootloader_image.h"

constexpr McciVersion::Version_t kVersion =
	McciVersion::makeVersion(0, 4, 0, 0);
constexpr char kCopyright[] = "Copyright (C) 2021, MCCI Corporation";

#endif /* _mccibootloader_image_version_h_ */
