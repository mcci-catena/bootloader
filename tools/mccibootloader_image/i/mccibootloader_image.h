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
#include "mcciadk_guid.h"
#include "mcci_tweetnacl_hash.h"
#include "mcci_tweetnacl_sign.h"
#include <chrono>
#include <ctime>
#include <cstring>

using namespace std;

// the application structure
struct App_t
	{
	bool		fVerbose;
	bool		fSign;
	bool		fHash;
	std::string	filename;
	std::string	progname;
	int		argc;
	char		**argv;
	FILE		*hFile;
	size_t		fSize;
	mcci_tweetnacl_sha512_t fileHash;

	int begin(int argc, char **argv);
	void scanArgs(int argc, char **argv);
	[[noreturn]] void usage(const string &message);
	[[noreturn]] void fatal(const string &message);
	void addHeader();
	void addHash();
	void addSignature();
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
		this->m_v[0] = v & 0xFF;
		this->m_v[1] = (v & 0xFF) >> 8;
		this->m_v[2] = (v & 0xFF) >> 16;
		this->m_v[3] = (v & 0xFF) >> 24;
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
	uint32_le_t	targetAddress;	//< the target load address
	uint32_le_t	imagesize;	//< size of the app, in bytes.
					//   Must be multiple of 4.
	uint32_le_t	authsize;	//< size of authentication data.
					// Overall image size is imagesize
					//   + authsize
	uint32_le_t	gpsTimestamp;	//< GPS timestamp of image
	MCCIADK_GUID	appGuid;	//< application ID
	uint32_le_t	version;	//< version of the image (semantic version)
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