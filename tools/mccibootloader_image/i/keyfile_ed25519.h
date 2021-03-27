/*

Module:	keyfile_ed25519.h

Function:
	Process ed25519 keyfiles

Copyright and License:
	This file copyright (C) 2021 by

		MCCI Corporation
		3520 Krums Corners Road
		Ithaca, NY  14850

	See accompanying LICENSE file for copyright and license information.

Author:
	Terry Moore, MCCI Corporation	March 2021

*/

#ifndef _keyfile_ed25519_h_
#define _keyfile_ed25519_h_	/* prevent multiple includes */

#pragma once

#include <string>
#include "mcci_tweetnacl_sign.h"

class Keyfile_ed25519_t
	{
public:
	Keyfile_ed25519_t() {}

	bool begin(std::string filename);
	void end();
	void clear();
	bool read();

	static constexpr char kName[] = "ssh-ed25519";
	std::string m_filename;
	std::string m_comment;

	mcci_tweetnacl_sign_publickey_t m_public;
	mcci_tweetnacl_sign_privatekey_t m_private;
	};

#endif /* _keyfile_ed25519_h_ */
