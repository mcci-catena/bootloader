/*

Module:	mccibootloader_image.h

Function:
	Header for common things for mccibootloader_image tool.

Copyright and License:
	This file copyright (C) 2021 by

		MCCI Corporation
		3520 Krums Corners Road
		Ithaca, NY  14850

	See accompanying LICENSE file for copyright and license information.

Author:
	Terry Moore, MCCI Corporation	March 2021

*/

#ifndef _mccibootloader_image_h_
#define _mccibootloader_image_h_	/* prevent multiple includes */

#pragma once

#include <cstdint>
#include <string>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include "mcci_tweetnacl_hash.h"
#include "mcci_tweetnacl_sign.h"
#include <chrono>
#include <ctime>
#include <cstring>
#include <ios>
#include <iostream>
#include <fstream>

#include "keyfile_ed25519.h"

using namespace std;

// guids
struct GuidWire_t
	{
	uint8_t		time_low[4];
	uint8_t		time_mid[2];
	uint8_t		time_hi_and_version[2];
	uint8_t		clock_seq_hi_and_reserved;
	uint8_t		clock_seq_low;
	uint8_t		node[6];
	};

constexpr size_t GuidWire_t_SIZE = 16;

/* validate the layout */
static_assert(offsetof(GuidWire_t, time_mid) == 4, "GUID layout mismatch");
static_assert(offsetof(GuidWire_t, time_hi_and_version) == 6, "GUID layout mismatch");
static_assert(offsetof(GuidWire_t, clock_seq_hi_and_reserved) == 8, "GUID layout mismatch");
static_assert(offsetof(GuidWire_t, clock_seq_low) == 9, "GUID layout mismatch");
static_assert(offsetof(GuidWire_t, node) == 10, "GUID layout mismatch");
static_assert(sizeof(GuidWire_t) == GuidWire_t_SIZE, "GUID layout mismatch");

// the application structure
struct App_t
	{
	bool		fVerbose;
	bool		fSign;
	bool		fHash;
	bool		fPatch;
	bool		fUpdate;
	bool		fAddGps;
	bool		fDryRun;
	std::string	infilename;
	std::string	outfilename;
	std::string	progname;
	std::string	keyfilename;
	std::vector<uint8_t>	fileimage;
	int		argc;
	char		**argv;
	size_t		fSize;
	size_t		authSize;
	mcci_tweetnacl_sha512_t fileHash;

	int begin(int argc, char **argv);

private:
	void scanArgs(int argc, char **argv);
	[[noreturn]] void usage(const string &message);
	[[noreturn]] void fatal(const string &message);
	void verbose(const string &message);
	void addHeader();
	void addHash();
	void addSignature();
	void testNaCl();
	void dump(const string &message, const uint8_t *pBegin, const uint8_t *pEnd);

	Keyfile_ed25519_t keyfile;
	};

static constexpr const char *filebasename(const char *s)
    {
    const char *pName = s;

    for (auto p = s; *p != '\0'; ++p)
        {
        if (*p == '/' || *p == '\\')
            pName = p + 1;
        }
    return pName;
    }

namespace McciVersion {
	typedef std::uint32_t Version_t;

	// create a version number for comparison
	constexpr std::uint32_t
	makeVersion(
		std::uint8_t major, std::uint8_t minor, std::uint8_t patch, std::uint8_t local = 0
		)
		{
		return ((std::uint32_t)major << 24u) | ((std::uint32_t)minor << 16u) | ((std::uint32_t)patch << 8u) | (std::uint32_t)local;
		}

	// extract major number from version
	constexpr std::uint8_t
	getMajor(std::uint32_t v)
		{
		return std::uint8_t(v >> 24u);
		}

	// extract minor number from version
	constexpr std::uint8_t
	getMinor(std::uint32_t v)
		{
		return std::uint8_t(v >> 16u);
		}

	// extract patch number from version
	constexpr std::uint8_t
		getPatch(std::uint32_t v)
		{
		return std::uint8_t(v >> 8u);
		}

	// extract local number from version
	constexpr std::uint8_t
	getLocal(std::uint32_t v)
		{
		return std::uint8_t(v);
		}
} // namespace McciVersion

// the layout of the image
class uint32_le_t
	{
public:
	uint32_le_t(uint32_t v = 0)
		: m_v 	{
			std::uint8_t(v & 0xFF),
		        std::uint8_t((v >> 8) & 0xFF),
			std::uint8_t((v >> 16) & 0xFF),
			std::uint8_t(v >> 24)
			}
		{}
	void put(uint32_t v)
		{
		this->m_v[0] = std::uint8_t(v >>  0);
		this->m_v[1] = std::uint8_t(v >>  8);
		this->m_v[2] = std::uint8_t(v >> 16);
		this->m_v[3] = std::uint8_t(v >> 24);
		}
	uint32_t get(void) const
		{
		return
			(this->m_v[0] << 0) |
			(this->m_v[1] << 8) |
			(this->m_v[2] << 16) |
			(this->m_v[3] << 24);
		}
private:
	uint8_t m_v[4];
	};

struct CortexAppEntryContents_t
	{
	uint32_le_t	stack;
	uint32_le_t	entry;
	};

union CortexAppEntry_t
	{
	CortexAppEntryContents_t	AppEntry;
	};

struct CortexVectorsContents_t
	{
	uint32_le_t	v[192/4];
	};

union CortexVectors_t
	{
	CortexAppEntryContents_t	AppEntry;
	CortexAppEntry_t		AppEntryCast;
	CortexVectorsContents_t		Vectors;
	};

struct McciBootloader_AppInfo_Wire_t
	{
	static constexpr uint32_t kMagic = (('M' << 0) | ('A' << 8) | ('P' << 16) | ('0' << 24));
	static constexpr uint32_t kBootloaderAddress = 0x08000000;
	static constexpr uint32_t kAppAddress = kBootloaderAddress + 20 * 1024;

	uint32_le_t	magic = kMagic;		//< the format identifier.
	uint32_le_t	size = sizeof(*this);	//< size of this stucture, in bytes
	uint32_le_t	targetAddress { 0 };	//< the target load address
	uint32_le_t	imagesize { 0 };	//< size of the app, in bytes.
					//   Must be multiple of 4.
	uint32_le_t	authsize { 0 };	//< size of authentication data.
					// Overall image size is imagesize
					//   + authsize
	uint32_le_t	gpsTimestamp { 0 };	//< GPS timestamp of image
	GuidWire_t	appGuid {{ 0  }};	//< application ID
	uint32_le_t	version { 0 };	//< version of the image (semantic version)
	};

struct McciBootloader_CortexPageZeroContents_t
	{
	CortexVectorsContents_t		Hdr;
	McciBootloader_AppInfo_Wire_t	AppInfo;
	};

union McciBootloader_CortexPageZero_Wire_t
	{
	CortexAppEntryContents_t		CortexAppEntry;		//< View instance as a CortexM0 AppEntry.
	CortexAppEntry_t			CortexAppEntryCast;	//< Downcast to an AppEntry without explicit casting
	CortexVectorsContents_t		 	CortexVectors;		//< View instance as vectors.
	CortexVectors_t	 			CortexVectorsCast;	//< Downcast to a CortexVectors_t without explicit casting
	McciBootloader_CortexPageZeroContents_t PageZero;		//< View instance as a PageZero.
	uint8_t					Bytes[256];		//< padding to force size
	};

static_assert(sizeof(McciBootloader_CortexPageZero_Wire_t) == 256, "Page zero size wrong");

#endif /* _mccibootloader_image_h_ */
