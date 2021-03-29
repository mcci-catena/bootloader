/*

Module:	keyfile_ed25519.cpp

Function:
	Methods for Keyfile_ed25519_t

Copyright and License:
	This file copyright (C) 2021 by

		MCCI Corporation
		3520 Krums Corners Road
		Ithaca, NY  14850

	See accompanying LICENSE file for copyright and license information.

Author:
	Terry Moore, MCCI Corporation	March 2021

*/

#include "keyfile_ed25519.h"

#include <string>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <sstream>

using namespace std;

/****************************************************************************\
|
|	Manifest constants & typedefs.
|
\****************************************************************************/

static std::string base64decode(const std::string &input);
static uint32_t getInt(std::istringstream &s);
static std::string getByteString(std::istringstream &s);

/****************************************************************************\
|
|	Read-only data.
|
\****************************************************************************/



/****************************************************************************\
|
|	Variables.
|
\****************************************************************************/

bool
Keyfile_ed25519_t::begin(
	string filename
	)
	{
	this->m_filename = filename;
	this->clear();
	return true;
	}

void
Keyfile_ed25519_t::clear()
	{
	memset(&this->m_public, 0, sizeof(this->m_public));
	memset(&this->m_private, 0, sizeof(this->m_private));
	}

bool
Keyfile_ed25519_t::read()
	{
	std::ifstream infile(this->m_filename, std::ios::in);

	if (! infile.is_open())
		return false;

	string s;
	std::getline(infile, s);
	if (s != "-----BEGIN OPENSSH PRIVATE KEY-----")
		return false;

	string m;
	do	{
		string body;
		while (true)
			{
			std::getline(infile, s);
			if (s == "-----END OPENSSH PRIVATE KEY-----")
				{
				break;
				}
			body.append(s);
			}

		m = base64decode(body);
		} while (0);

	std::istringstream dm (m, std::ios::binary);
	std::getline(dm, s, '\0');
	if (s != "openssh-key-v1")
		return false;

	/* skip two strings */
	(void) getByteString(dm);
	(void) getByteString(dm);
	(void) getByteString(dm);
	if (getInt(dm) != 1)
		// wrong number of keys
		return false;

	auto pubm_string = getByteString(dm);
	std::istringstream pubm (pubm_string, std::ios::binary);
	if (getByteString(pubm) != "ssh-ed25519")
		return false;
	auto pubkey_string = getByteString(pubm);
	if (pubkey_string.size() != sizeof(this->m_public.bytes))
		return false;
	for (unsigned i = 0; i < sizeof(this->m_public.bytes); ++i)
		this->m_public.bytes[i] = uint8_t(pubkey_string[i]);

	auto privm_string = getByteString(dm);
	std::istringstream privm (privm_string, std::ios::binary);
	/* skip two dwords */
	(void) getInt(privm);
	(void) getInt(privm);
	/* match */
	if (getByteString(privm) != "ssh-ed25519")
		return false;
	// the public key is repeated
	if (getByteString(privm) != pubkey_string)
		return false;
	// then the private key
	auto privkey_string = getByteString(privm);
	if (privkey_string.size() != sizeof(this->m_private.bytes))
		return false;

	for (unsigned i = 0; i < sizeof(this->m_private.bytes); ++i)
		this->m_private.bytes[i] = uint8_t(privkey_string[i]);

	// wipe out everything else
	//memset(privkey_string.data(), 0, privkey_string.size());
	//memset(privm_string.data(), 0, privm_string.size());

	// finally the comment
	this->m_comment = getByteString(privm);
	return true;
	}

static uint32_t getInt(std::istringstream &s)
	{
	uint8_t buf[4];
	s.read((char *)&buf, 4);
	return (uint32_t(buf[0]) << 24) |
	       (uint32_t(buf[1]) << 16) |
	       (uint32_t(buf[2]) <<  8) |
	       (uint32_t(buf[3]) <<  0);
	}

static std::string getByteString(std::istringstream &s)
	{
	auto n = getInt(s);

	std::string result;
	for (uint32_t i = 0; i < n; ++i)
		{
		result.push_back(s.get());
		}
	return result;
	}

constexpr int find64(char c)
	{
	return 	('A' <= c && c <= 'Z')  ? (c - 'A') :
		('a' <= c && c <= 'z') 	? (c - 'a' + 26) :
		('0' <= c && c <= '9')	? (c - '0' + 52) :
		(c == '+') 		? 62 :
		(c == '/')		? 63 :
		(c == '=')		? -1 :
					-2;
	}

static std::string base64decode(const std::string &input)
	{
	string result;
	uint32_t accum;
	unsigned n64, nPad;

	n64 = 0;
	nPad = 0;
	accum = 0;
	for (auto c : input)
		{
		if (c == '\n' || c == '\r' || c == ' ')
			continue;

		auto v = find64(c);
		if (v == -2)
			/* error */
			return "";

		// may be padding or real
		accum <<= 6;
		if (v >= 0)
			{
			if (nPad > 0)
				return "";
			accum += v;
			}
		else
			{
			++nPad;
			}

		++n64;
		if (n64 == 4)
			{
			unsigned nc;
			// deal with number of pad chars
			nc = (nPad == 0) ? 3 :
			     (nPad <= 2) ? 2 :
			     (nPad <= 3) ? 1 :
			     	0;
			// extract the characters.
			for (unsigned i = 0; i < nc; ++i)
				{
				result.push_back(char(accum >> (16 - 8 * i)));
				}

			// reset scanner
			accum = n64 = nPad = 0;
			}
		}

	return result;
	}
