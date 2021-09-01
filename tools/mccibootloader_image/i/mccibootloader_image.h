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
#include <algorithm>
#include "mcci_tweetnacl_hash.h"
#include "mcci_tweetnacl_sign.h"
#include <chrono>
#include <ctime>
#include <cstring>
#include <ios>
#include <iostream>
#include <fstream>

#include "mccibootloader_elf.h"
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

/* versions */
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


// a forward reference
struct McciBootloader_AppInfo_Wire_t;

// the application structure
struct App_t
	{
	bool		fVerbose;
	bool		fDebug;
	bool		fSign;
	bool		fHash;
	bool		fPatch;
	bool		fUpdate;
	bool		fAddTime;
	bool		fDryRun;
	bool		fForceBinary;
	char 		*pComment;
	std::string	infilename;
	std::string	outfilename;
	std::string	progname;
	std::string	keyfilename;
	std::vector<uint8_t>	fileimage;
	McciVersion::Version_t	appVersion;
	bool		fAppVersion;

	struct AppElf_t
		{
		std::vector<uint8_t>	image;
		const McciBootloader_Elf::ElfIdent32_t *pIdent32;
		std::vector<McciBootloader_Elf::ElfIdent32_t::ProgramHeader_t> vHeaders;
		std::uint32_t	targetAddress;
		} elf;

	int		argc;
	char		**argv;
	size_t		fSize;
	size_t		authSize;
	mcci_tweetnacl_sha512_t fileHash;
	const McciBootloader_AppInfo_Wire_t *pFileAppInfo;

	int begin(int argc, char **argv);
	bool isUsingElf() const
		{ return this->elf.image.size() != 0; }

private:
	void scanArgs(int argc, char **argv);
	[[noreturn]] void usage(const string &message);
	[[noreturn]] void fatal(const string &message);
	void verbose(const string &message);
	bool probeHeader(size_t appInfoOffset, McciBootloader_AppInfo_Wire_t &fileAppInfo, uint8_t * &pFileAppInfo);
	void addHeader();
	void addHash();
	void addSignature();
	void testNaCl();
	void dump(const string &message, const uint8_t *pBegin, const uint8_t *pEnd);
	void readImage();
	void writeImage();
	void elfImagePrep();
	void setAppVersion(const string &versionString);

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
			(uint32_t(this->m_v[0]) << 0) |
			(uint32_t(this->m_v[1]) << 8) |
			(uint32_t(this->m_v[2]) << 16) |
			(uint32_t(this->m_v[3]) << 24) |
			0;
		}
private:
	uint8_t m_v[4];
	};

// the layout of the image
class uint64_le_t
	{
public:
	uint64_le_t(uint64_t v = 0)
		: m_v 	{
			std::uint8_t(v & 0xFF),
		        std::uint8_t((v >> 8) & 0xFF),
			std::uint8_t((v >> 16) & 0xFF),
			std::uint8_t((v >> 24) & 0xFF),
			std::uint8_t((v >> 32) & 0xFF),
			std::uint8_t((v >> 40) & 0xFF),
			std::uint8_t((v >> 48) & 0xFF),
			std::uint8_t((v >> 56) & 0xFF),
			}
		{}
	void put(uint64_t v)
		{
		this->m_v[0] = std::uint8_t(v >>  0);
		this->m_v[1] = std::uint8_t(v >>  8);
		this->m_v[2] = std::uint8_t(v >> 16);
		this->m_v[3] = std::uint8_t(v >> 24);
		this->m_v[4] = std::uint8_t(v >> 32);
		this->m_v[5] = std::uint8_t(v >> 40);
		this->m_v[6] = std::uint8_t(v >> 48);
		this->m_v[7] = std::uint8_t(v >> 56);
		}
	uint64_t get(void) const
		{
		return
			(uint64_t(this->m_v[0]) << 0) |
			(uint64_t(this->m_v[1]) << 8) |
			(uint64_t(this->m_v[2]) << 16) |
			(uint64_t(this->m_v[3]) << 24) |
			(uint64_t(this->m_v[4]) << 32) |
			(uint64_t(this->m_v[5]) << 40) |
			(uint64_t(this->m_v[6]) << 48) |
			(uint64_t(this->m_v[7]) << 56) |
			0
			;
		}
private:
	std::uint8_t m_v[8];
	};

/// \brief a string type for comments
template<std::size_t a_nch> 
class utf8_z_t
	{
public:
	utf8_z_t() {};

	std::string get() const
		{
		size_t n = (this->m_v[a_nch - 1] == '\0') 
				? a_nch 
				: std::strlen(this->m_v)
				;

		return std::string(this->m_v, n);
		}
	void put(const char *v)
		{
		this->put(std::string(v));
		}
	void put(const std::string &s)
		{
		size_t n = std::min(s.size(), a_nch);
		std::memcpy(this->m_v, s.c_str(), n);
		std::memset(this->m_v + n, 0, a_nch - n);
		}

private:
	char m_v[a_nch] { 0 };
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

///
/// \brief the template for creating the architecture-specific vectors
///
/// \param a_nVec number of vectors to be reserved.
///
/// \details
/// 	ARM Cortex architectures allow different numbers of
///	entries in the vector table. We use this template to represent
///	the vectors in a consistent way.
///
template <uint32_t a_nVec>
struct CortexAbstractVectorsContents_t
	{
	static constexpr uint32_t nVec = a_nVec;	//< the number of vectors
	uint32_le_t		v[nVec];		//< the array of vector pointers
	};

template <uint32_t a_nVec>
union CortexAbstractVectors_t
	{
	CortexAppEntryContents_t			AppEntry;
	CortexAppEntry_t				AppEntryCast;
	CortexAbstractVectorsContents_t<a_nVec>		Vectors;
	};

struct McciBootloader_AppInfo_Wire_t
	{
	static constexpr uint32_t kMagic = (('M' << 0) | ('A' << 8) | ('P' << 16) | ('0' << 24));
	static constexpr uint32_t kBootloaderAddress = 0x08000000;
	static constexpr uint32_t kAppAddress = kBootloaderAddress + 20 * 1024;

	uint32_le_t	magic = kMagic;		///< the format identifier.
	uint32_le_t	size = sizeof(*this);	///< size of this stucture, in bytes
	uint32_le_t	targetAddress { 0 };	///< the target load address
	uint32_le_t	imagesize { 0 };	///< size of the app, in bytes.
						///   Must be multiple of 4.
	uint32_le_t	authsize { 0 };		///< size of authentication data.
						/// Overall image size is imagesize
						///   + authsize
	uint32_le_t	version { 0 };		///< version of the image (semantic version)
	uint64_le_t	posixTimestamp { 0 };	///< Posix timestamp of image
	utf8_z_t<16>	comment; 		///< the comment
	std::uint8_t	reserved56[16] { 0 };	///< reserved, zero.
	};

static_assert(
	sizeof(McciBootloader_AppInfo_Wire_t) == 64,
	"wrong size for AppInfo_Wire_t"
	);

/// \brief The portable form of the signature block.
struct McciBootloader_SignatureBlock_Wire_t
	{
	uint8_t	publicKey[32] = {0};		///< public key
	uint8_t	hash[64] = {0};			///< sha512 hash
	uint8_t	signature[64] = {0};		///< signature
	};

static_assert(
	sizeof(McciBootloader_SignatureBlock_Wire_t) == 160,
	"wrong size for McciBootloader_SignatureBlock_Wire_t"
	);

template <uint32_t a_nVec>
struct McciBootloader_CortexAbstract_PageZeroContents_t
	{
	CortexAbstractVectorsContents_t<a_nVec>	Hdr;
	McciBootloader_AppInfo_Wire_t		AppInfo;
	};

template <uint32_t a_nVec>
union McciBootloader_CortexAbstract_PageZero_Wire_t
	{
	CortexAppEntryContents_t		CortexAppEntry;		//< View instance as a CortexM0 AppEntry.
	CortexAppEntry_t			CortexAppEntryCast;	//< Downcast to an AppEntry without explicit casting
	CortexAbstractVectorsContents_t<a_nVec>	CortexVectors;		//< View instance as vectors.
	CortexAbstractVectors_t<a_nVec> 	CortexVectorsCast;	//< Downcast to a CortexVectors_t without explicit casting
	McciBootloader_CortexAbstract_PageZeroContents_t<a_nVec>
						PageZero;		//< View instance as a PageZero.
	uint8_t					Bytes[a_nVec * 4 + 64];	//< padding to force size
	};

///
/// \brief concrete page-zero type for Cortex m0/m0plus CPUs.
///
/// \details The CM0/CM0+ architectures have 48 vectors, and 256 bytes in page zero.
///	This structure is the concrete representation.
///
typedef McciBootloader_CortexAbstract_PageZero_Wire_t<48>
	McciBootloader_CortexM0_PageZero_Wire_t;

static_assert(
	sizeof(McciBootloader_CortexM0_PageZero_Wire_t) == 256,
	"Page zero size wrong"
	);

///
/// \brief concrete page-zero type for Cortex m7 CPUs.
///
/// \details The CM7 architectures have up to 240 vectors, and 1024 bytes in page zero.
///	This structure is the concrete representation.
///
typedef McciBootloader_CortexAbstract_PageZero_Wire_t<256>
	McciBootloader_CortexM7_PageZero_Wire_t;

static_assert(
	sizeof(McciBootloader_CortexM7_PageZero_Wire_t) == 1024 + 64,
	"Page zero size wrong"
	);

///
/// \brief concrete page-zero type for STM32H7 SOCs.
///
/// \details The STM32H7 SOCs have hundress of vectors, but less than 240.
///	This structure is the concrete representation.  Rather than trying to crunch things
///	as tightly as possible, we act as if there are 240 vectors (which leaves 64
///	bytes free at the end, but wastes (240-170)*4 = 280 bytes between the end of
///	the vectors and the start of the AppInfo block.
///
typedef McciBootloader_CortexAbstract_PageZero_Wire_t<240>
	McciBootloader_Stm32h7_PageZero_Wire_t;

static_assert(
	sizeof(McciBootloader_Stm32h7_PageZero_Wire_t) == 1024,
	"Page zero size wrong"
	);

///
/// \brief represent the supported positions for AppInfo_Wire_t structures
///
struct McciBootloader_AppInfoOffset_t
	{
	const char *pModelName;		//> the name of the architecture or model used for this table
	size_t appInfoOffset;		//> the byte offset of the appinfo in the file image
	};

#endif /* _mccibootloader_image_h_ */
