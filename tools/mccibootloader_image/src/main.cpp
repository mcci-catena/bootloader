/*

Module:	main.c

Function:
	main() and main app logic for mccibootloader_image.

Copyright and License:
	This file copyright (C) 2021 by

		MCCI Corporation
		3520 Krums Corners Road
		Ithaca, NY  14850

	See accompanying LICENSE file for copyright and license information.

Author:
	Terry Moore, MCCI Corporation	March 2021

*/

#include "mccibootloader_image.h"
#include "mccibootloader_image_version.h"
#include <iomanip>
#include <sstream>

/****************************************************************************\
|
|	Manifest constants & typedefs.
|
\****************************************************************************/

static void dumpAppInfo(
	std::string const &s,
	McciBootloader_AppInfo_Wire_t const &appInfo
	);

static std::string versionToString(
	McciVersion::Version_t version
	);

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

App_t gApp;

int main(
	int argc,
	char **argv
	)
	{
	return gApp.begin(argc, argv);
	}

int App_t::begin(int argc, char **argv)
	{
	// make sure the authsize is right.
	this->authSize =
		sizeof(mcci_tweetnacl_sign_publickey_t) +
		sizeof(mcci_tweetnacl_sha512_t) +
		mcci_tweetnacl_sign_signature_size();

	this->scanArgs(argc, argv);

	// do the pre-tests
	this->testNaCl();

	// read the image
	this->readImage();

	// start processing.
	if (this->fHash)
		{
		this->keyfile.begin(this->keyfilename);

		if (! this->keyfile.read())
			this->fatal(string("can't read key file: ") + this->keyfilename);

		if (this->fVerbose)
			std::cout << "Keyfile comment: " << this->keyfile.m_comment << "\n\n";
		}

	if (this->fHash || this->fSign)
		this->addHeader();

	if (this->fHash || this->fSign)
		this->addHash();

	if (this->fSign)
		this->addSignature();

	// write image
	this->writeImage();

	return EXIT_SUCCESS;
	}

void App_t::verbose(const string &message)
	{
	if (this->fVerbose)
		std::cout << message << "\n";
	}

void App_t::scanArgs(int argc, char **argv)
	{
	this->argc = argc;
	this->argv = argv;
	this->progname = filebasename(*argv++);
	vector<string> posArgs;

	bool fOptOk = true;
	this->fAddTime = true;
	this->pComment = NULL;

	for (;;)
		{
		auto const pThisarg = *argv++;

		if (pThisarg == NULL)
			break;

		string arg = pThisarg;

		if (! fOptOk)
			{
			posArgs.push_back(arg);
			continue;
			}

		bool fBool = true;
		string boolArg = arg;

		if (arg.substr(0, 5) == "--no-")
			{
			fBool = false;
			boolArg = "--" + arg.substr(5);
			}
		else if (arg.substr(0, 2) == "-n")
			{
			fBool = false;
			boolArg = "-" + arg.substr(2);
			}

		if (arg == "--")
			{
			fOptOk = false;
			}
		else if (boolArg == "-v" || boolArg == "--verbose")
			{
			this->fVerbose = fBool;
			}
		else if (boolArg == "-D" || boolArg == "--debug")
			{
			this->fDebug = fBool;
			}
		else if (boolArg == "-h" || boolArg == "--hash")
			{
			this->fHash = fBool;
			this->fUpdate |= fBool;
			}
		else if (boolArg == "-t" || boolArg == "--add-time")
			{
			this->fAddTime = fBool;
			}
		else if (boolArg == "-s" || boolArg == "--sign")
			{
			this->fSign = fBool;
			this->fHash |= fBool;
			this->fUpdate |= fBool;
			}
		else if (boolArg == "-p" || boolArg == "--patch")
			{
			this->fPatch = fBool;
			}
		else if (boolArg == "--dry-run")
			{
			this->fDryRun = fBool;
			}
		else if (boolArg == "--force-binary")
			{
			this->fForceBinary = fBool;
			}
		else if (arg == "-k" || arg == "--keyfile")
			{
			if (*argv == nullptr)
				this->usage("missing keyfile name");

			this->keyfilename = *argv++;
			}
		else if (arg == "-c" || arg == "--comment")
			{
			if (*argv == nullptr)
				this->usage("missing comment value");
			this->pComment = *argv++;
			}
		else if (arg == "-V" || arg == "--app-version")
			{
			if (*argv == nullptr)
				this->usage("missing app-version value");

			this->setAppVersion(string(*argv));
			}
		else if (arg == "--version")
			{
			std::cout << "mccibootloader_image v"
				<< std::dec
				<< unsigned(McciVersion::getMajor(kVersion)) << "."
				<< unsigned(McciVersion::getMinor(kVersion)) << "."
				<< unsigned(McciVersion::getPatch(kVersion))
				;
			unsigned const kLocal = McciVersion::getLocal(kVersion);
			if (kLocal != 0)
				std::cout << "." << kLocal;
			std::cout << "\n";
			std::cout << kCopyright << "\n";
			exit(EXIT_SUCCESS);
			}
		else if (arg.substr(0, 1) == "-")
			{
			this->usage("unknown arg: " + arg);
			}
		else
			{
			posArgs.push_back(arg);
			}
		}

	/* check the positional args */
	if (posArgs.size() == 0)
		{
		this->usage("missing input filename");
		}
	this->infilename = posArgs[0];

	if (posArgs.size() == 1)
		{
		if (! this->fPatch && this->fUpdate)
			{
			this->usage("--patch needed for in-place update");
			}
		this->outfilename = "";
		}
	else
		this->outfilename = posArgs[1];

	if (posArgs.size() > 2)
		{
		this->usage("extra arguments");
		}

	if (this->fVerbose)
		{
		std::cout << std::boolalpha;
		std::cout << "Program settings:\n"
		          << "     --verbose: " << this->fVerbose << "\n"
		          << "       --debug: " << this->fDebug << "\n"
		          << "        --hash: " << this->fHash << "\n"
		          << "        --sign: " << this->fSign << "\n"
		          << "    --add-time: " << this->fAddTime << "\n"
		          << "     --dry-run: " << this->fDryRun << "\n"
			  << "--force-binary: " << this->fForceBinary << "\n"
			  << "       --patch: " << this->fPatch << "\n"
		          << "     --keyfile: " << this->keyfilename << "\n"
			  << "     --comment: " << (pComment == NULL ? "<<none>>": pComment) << "\n"
			  << " --app-version: " << (!this->fAppVersion ? "<<none>>": versionToString(this->appVersion)) << "\n"
			  << "\n"
		          << "input:          " << this->infilename << "\n"
		          << "output:         "
		          << (!this->fUpdate ? "none" : !this->fPatch ? this->outfilename : "{update}")
			  << "\n";
		std::cout << "\n";
		std::cout << std::flush;
		}
	}

[[noreturn]]
void App_t::usage(const string &message)
	{
	string usage = message;
	if (usage != "" && usage[usage.length() - 1] != '\n')
		{
		usage.append(": ");
		}
	usage.append("usage: ");
	usage.append(this->progname);
	usage.append(" -[vsh k{keyfile} c{comment} -V{app-version}] --[version sign hash app-version {version} comment {comment} dry-run add-time force-binary verbose debug] infile [outfile]\n");
	fprintf(stderr, "%s\n", usage.c_str());
	exit(EXIT_FAILURE);
	}

static std::string versionToString(McciVersion::Version_t version)
	{
	ostringstream sVersion;
	sVersion << unsigned(McciVersion::getMajor(version))
		 << "."
		 << unsigned(McciVersion::getMinor(version))
		 << "."
		 << unsigned(McciVersion::getPatch(version))
		 ;
	if (McciVersion::getLocal(version) != 0)
		{
		sVersion << "-"
			 << unsigned(McciVersion::getLocal(version));
		}

	return sVersion.str();
	}

void App_t::setAppVersion(
	const string &versionString
	)
	{
	unsigned i = 0;

	auto const failstring = [&versionString, &i](const string &message) -> string
		{
		string result;
		result = message + ": ";
		result += versionString.substr(0, i);
		result += "[";
		result += versionString.substr(i);
		result += "]\n";
		return result;
		};

	auto const getn = [this, &versionString, &i, &failstring]() -> std::uint8_t
		{
		std::uint32_t result;
		auto const n = versionString.length();
		bool err;
		bool gotDigit;

		err = false;
		gotDigit = false;
		result = 0;

		while (i < n && !err)
			{
			auto c = versionString[i];
			if (! ('0' <= c && c <= '9'))
				break;

			gotDigit = true;
			result = result * 10 + (c - '0');
			if (result >= 256)
				err = true;
			else
				++i;
			}

		if (! gotDigit)
			err = true;

		if (err)
			this->usage(failstring("illegal app-version syntax"));

		return result;
		};
	auto const checkpunct = [&versionString, &i](char c) -> bool
		{
		auto const n = versionString.length();

		if (i < n && versionString[i] == c)
			{
			++i;
			return true;
			}
		return false;
		};

	auto const major = getn();
	std::uint8_t minor, patch, prerelease;
	minor = patch = prerelease = 0;

	if (checkpunct('.'))
		{
		minor = getn();
		if (checkpunct('.'))
			patch = getn();
		}
	if (checkpunct('-'))
		{
		prerelease = getn();
		}

	if (i < versionString.length())
		this->usage(failstring("illegal value for app-version"));

	this->appVersion = McciVersion::makeVersion(major, minor, patch, prerelease);
	this->fAppVersion = true;
	}

void dumpAppInfo(
	std::string const &s,
	McciBootloader_AppInfo_Wire_t const &appInfo
	)
	{
	std::cout << s << ":\n" << std::hex
	          << "          magic:         " << std::setw(8) << std::setfill('0') << appInfo.magic.get() << "\n"
	          << "           size:         " << std::setw(8) << std::setfill(' ') << appInfo.size.get() << "\n"
	          << "  targetAddress:         " << std::setw(8) << std::setfill(' ') << appInfo.targetAddress.get() << "\n"
	          << "      imageSize:         " << std::setw(8) << std::setfill(' ') << appInfo.imagesize.get() << "\n"
	          << "       authSize:         " << std::setw(8) << std::setfill(' ') << appInfo.authsize.get() << "\n"
	          << " posixTimestamp: " << std::setw(16) << std::setfill(' ') << appInfo.posixTimestamp.get() << "\n"
		  << "        comment:         " << appInfo.comment.get() << "\n";
		  ;
  
	std::cout << "        version: " << std::setw(16) << std::setfill(' ') << versionToString(appInfo.version.get());
	std::cout << "\n";
	std::cout << "\n";
	}

bool App_t::probeHeader(
	size_t appInfoOffset,
	McciBootloader_AppInfo_Wire_t &fileAppInfo,
	uint8_t * &pFileAppInfoOut
	)
	{
	// set pFileAppInfo to a pointer to the appinfo in the memory-mapped image of the file.
	auto const pFileAppInfo = &this->fileimage.at(appInfoOffset);

	// copy the data to a convenient place so we can work on it.
	memcpy(&fileAppInfo, pFileAppInfo, sizeof(fileAppInfo));

	// dump header if verbose
	if (this->fDebug)
		dumpAppInfo("App_t::probeHeader(): AppInfo from input", fileAppInfo);	// if the file's appinfo looks good, use it

	// Check the minimum information. NB: this check effectively requires that a valid heder contain:
	// a good magic number and a good size. Once we see that, the outer loop will stop looking.
	if (fileAppInfo.magic.get() == fileAppInfo.kMagic &&
	    fileAppInfo.size.get() == sizeof(fileAppInfo))
		{
		pFileAppInfoOut = pFileAppInfo;
		return true;
		}
	else
		{
		return false;
		}
	}

const McciBootloader_AppInfoOffset_t vAppInfoOffsets[] =
	{
	{ "cm0+", 	offsetof(McciBootloader_CortexM0_PageZero_Wire_t, PageZero.AppInfo) },
	{ "cm7(240)",	offsetof(McciBootloader_CortexM7Compact_PageZero_Wire_t, PageZero.AppInfo) },
	{ "cm7",	offsetof(McciBootloader_CortexM7_PageZero_Wire_t, PageZero.AppInfo) },
	};

void App_t::addHeader()
	{
	McciBootloader_AppInfo_Wire_t fileAppInfo;
	const McciBootloader_AppInfoOffset_t * pEntry;
	uint8_t *pFileAppInfo;

	// search for an AppInfo_Wire_t object.
	pEntry = nullptr;
	for (auto const &Entry : vAppInfoOffsets)
		{
		if (this->probeHeader(Entry.appInfoOffset, fileAppInfo, pFileAppInfo))
			{
			pEntry = &Entry;
			break;
			}
		}

	if (pEntry == nullptr)
		{
		this->fatal("could not find valid AppInfo structure");
		}

	// dump header if verbose
	if (this->fVerbose)
		{
		std::ostringstream msg;
		msg	<< "AppInfo for architecture "
			<< pEntry->pModelName
			<< " found at offset 0x"
			<< std::hex
			<< pEntry->appInfoOffset
			;

		dumpAppInfo(
			msg.str(),
			fileAppInfo
			);
		}

	// appInfo starts as an instance of an appinfo with defaults.
	McciBootloader_AppInfo_Wire_t appInfo;

	// if the file's appinfo looks good, use it
	if (fileAppInfo.targetAddress.get() != 0)
	    	{
		appInfo = fileAppInfo;

		if (this->isUsingElf() && this->elf.targetAddress != appInfo.targetAddress.get())
			this->fatal("ELF address doesn't match AppInfo");

		if (appInfo.authsize.get() != this->authSize)
			{
			this->fatal("Image authsize incorrect");
			}

		if (this->isUsingElf())
			{
			if (appInfo.imagesize.get() + appInfo.authsize.get() > this->fileimage.size())
				{
				std::ostringstream msg;
				msg << "ELF imagesize (0x" << std::hex << this->fileimage.size()
				    << ") smaller than appinfo imagesize + authinfo (0x"
				    << std::hex << appInfo.imagesize.get() + appInfo.authsize.get()
				    << ")";
				this->fatal(msg.str());
				}
			}
		else if (appInfo.imagesize.get() == 0)
			{
			this->verbose("AppInfo.imagesize == 0, set AppInfo.imagesize to file size");
			appInfo.imagesize.put(this->fSize);
			}
		else
			{
			this->fSize = appInfo.imagesize.get();
			}
		}
	// looks fishy: refuse to operate on the file
	else
		{
		this->fatal("AppInfo in input file is improperly formatted");
		}

	// set the authsize field according to how we work.
	appInfo.authsize.put(
		this->authSize
		);

	// set the version if one was provided
	if (this->fAppVersion)
		appInfo.version.put(
			this->appVersion
			);

	// add posix time
	if (this->fAddTime)
		{
		uint32_t now = (uint32_t) time(nullptr);
		if (this->fVerbose)
			std::cout << "Posix time: " << now << "\n";
		appInfo.posixTimestamp.put(now);
		}

	// add comment
	if (this->pComment != NULL)
		{
		appInfo.comment.put(this->pComment);
		}

	if (this->fVerbose)
		dumpAppInfo("AppInfo after update", appInfo);

	// update the application image
	memcpy(pFileAppInfo, &appInfo, sizeof(appInfo));

	// set the app's idea too.
	this->pFileAppInfo = (McciBootloader_AppInfo_Wire_t *)pFileAppInfo;
	}

void App_t::dump(
	const string &label,
	std::uint8_t const *begin,
	std::uint8_t const *end
	)
	{
	unsigned n;
	n = 0;
	std::cout << label << ":\n" << std::hex;
	for (auto b = begin; b != end; ++b)
		{
		std::cout << std::setw(2) << setfill('0') << unsigned(b[0]);
		++n;
		if (n < 16)
			std::cout << " ";
		else
			{
			std::cout << "\n";
			n = 0;
			}
		}
	if (n != 0)
		std::cout << "\n";

	std::cout << "\n";
	}

void
App_t::addHash()
	{
	if (this->fVerbose)
		{
		this->dump("App page 0", &this->fileimage[0], &this->fileimage[256]);
		}

	/* put the public key */
	memcpy(
		&this->fileimage[0] + this->pFileAppInfo->imagesize.get(),
		this->keyfile.m_public.bytes,
		sizeof(this->keyfile.m_public.bytes)
		);

	if (this->fVerbose)
		{
		auto pKey = &this->fileimage[this->pFileAppInfo->imagesize.get()];

		this->dump(
			"Public key", pKey, pKey + sizeof(this->keyfile.m_public.bytes)
			);
		}
	size_t const hashpos = this->pFileAppInfo->imagesize.get() + sizeof(this->keyfile.m_public.bytes);

	mcci_tweetnacl_hash_sha512(
		&this->fileHash,
		&this->fileimage[0],
		hashpos
		);

	/* place the hash in the image */
	memcpy(
		&this->fileimage[hashpos],
		&this->fileHash.bytes[0],
		sizeof(this->fileHash.bytes)
		);

	/* display the hash */
	if (this->fVerbose)
		{
		ostringstream msg;

		msg << "Appended Hash @ 0x"
		    << std::hex << hashpos
		    ;
		this->dump(
			msg.str(),
			&this->fileimage.at(hashpos),
			&this->fileimage.at(hashpos + sizeof(this->fileHash.bytes))
			);
		}
	}

void
App_t::addSignature()
	{
	// here's our buffer:
	uint8_t buffer[sizeof(this->fileHash.bytes) + mcci_tweetnacl_sign_signature_size()];
	size_t sizeOut;

	mcci_tweetnacl_sign(
		buffer,
		&sizeOut,
		this->fileHash.bytes,
		sizeof(this->fileHash.bytes),
		&this->keyfile.m_private
		);

	// write the signature to the file
	const auto signaturepos = this->pFileAppInfo->imagesize.get() + offsetof(McciBootloader_SignatureBlock_Wire_t, signature);

	memcpy(
		&this->fileimage[signaturepos],
		buffer,
		mcci_tweetnacl_sign_signature_size()
		);

	if (this->fVerbose)
		{
		this->dump(
			"signature",
			buffer,
			buffer + mcci_tweetnacl_sign_signature_size()
			);
		}
	}

[[noreturn]]
void App_t::fatal(const string &message)
	{
	fprintf(stderr, "?%s: %s\n", this->progname.c_str(), message.c_str());
	exit(EXIT_FAILURE);
	}

/**** end of main.c ****/
