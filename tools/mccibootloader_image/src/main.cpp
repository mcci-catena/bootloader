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

/****************************************************************************\
|
|	Manifest constants & typedefs.
|
\****************************************************************************/

static void dumpAppInfo(
	std::string const &s,
	McciBootloader_AppInfo_Wire_t const &appInfo
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
		sizeof(mcci_tweetnacl_sha512_t) +
		mcci_tweetnacl_sign_signature_size();

	this->scanArgs(argc, argv);

	// do the pre-tests
	this->testNaCl();

	// do the work.
	std::ifstream infile {this->infilename, ios::binary | ios::ate};

	if (! infile.is_open())
		{
		string msg = "can't read " + this->infilename;
		std::perror(msg.c_str());
		std::exit(EXIT_FAILURE);
		}

	// get length
	infile.exceptions(std::ifstream::failbit);
	this->fSize = size_t(infile.tellg());
	infile.seekg(0);

	// get file
	this->fileimage.resize(this->fSize);
	infile.read((char *)&this->fileimage[0], this->fSize);
	infile.close();

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
	std::ofstream outfile;
	std::string successMessage;
	if (this->fDryRun)
		this->verbose("dry run, skipping write");
	else if (this->fPatch)
		{
		outfile.open(this->infilename, ios::binary);
		if (! outfile.is_open())
			{
			string msg = "can't write: " + this->infilename;
			std::perror(msg.c_str());
			std::exit(EXIT_FAILURE);
			}
		successMessage = string("successfully patched: ") + this->infilename;
		}
	else if (this->outfilename != "")
		{
		outfile.open(this->outfilename, ios::binary | ios::trunc);
		if (! outfile.is_open())
			{
			string msg = "can't create: " + this->outfilename;
			std::perror(msg.c_str());
			std::exit(EXIT_FAILURE);
			}
		successMessage = string("output file successfully written: ") + this->outfilename;
		}
	else
		{
		/* nothing to do */
		this->verbose("read-only mode, nothing written");
		}

	if (outfile.is_open())
		{
		outfile.exceptions(ios::badbit | ios::failbit);
		outfile.write((char *)&this->fileimage.at(0), this->fileimage.size());
		outfile.close();
		this->verbose(successMessage);
		}

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
	this->fAddGps = true;
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
		else if (boolArg == "-h" || boolArg == "--hash")
			{
			this->fHash = fBool;
			this->fUpdate |= fBool;
			}
		else if (boolArg == "-g" || boolArg == "--add-gps")
			{
			this->fAddGps = fBool;
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
		else if (arg == "-k" || arg == "--keyfile")
			{
			if (*argv == nullptr)
				this->usage("missing keyfile name");

			this->keyfilename = *argv++;
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
		          << "    --verbose: " << this->fVerbose << "\n"
		          << "       --hash: " << this->fHash << "\n"
		          << "       --sign: " << this->fSign << "\n"
		          << "    --add-gps: " << this->fAddGps << "\n"
		          << "    --dry-run: " << this->fDryRun << "\n"
		          << "    --keyfile: " << this->keyfilename << "\n"
			  << "\n"
		          << "input:     " << this->infilename << "\n"
		          << "output:    "
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
	if (usage != "")
		{
		usage.append(": ");
		}
	usage.append("usage: ");
	usage.append(this->progname);
	usage.append(" -[vsh k{keyfile}] --[version sign hash] infile [outfile]\n");
	fprintf(stderr, "%s\n", usage.c_str());
	exit(EXIT_FAILURE);
	}

void dumpAppInfo(
	std::string const &s,
	McciBootloader_AppInfo_Wire_t const &appInfo
	)
	{
	std::cout << s << ":\n" << std::hex
	          << "        magic: " << std::setw(8) << std::setfill('0') << appInfo.magic.get() << "\n"
	          << "         size: " << std::setw(8) << std::setfill('0') << appInfo.size.get() << "\n"
	          << "targetAddress: " << std::setw(8) << std::setfill('0') << appInfo.targetAddress.get() << "\n"
	          << "    imageSize: " << std::setw(8) << std::setfill('0') << appInfo.imagesize.get() << "\n"
	          << "     authSize: " << std::setw(8) << std::setfill('0') << appInfo.authsize.get() << "\n"
	          << " gpsTimestamp: " << std::setw(8) << std::setfill('0') << appInfo.gpsTimestamp.get() << "\n"
		  ;
	auto version = appInfo.version.get();
	std::cout << "      version: " << std::dec
				<< unsigned(McciVersion::getMajor(version)) << "."
				<< unsigned(McciVersion::getMinor(version)) << "."
				<< unsigned(McciVersion::getPatch(version));
	if (McciVersion::getLocal(version) != 0)
		std::cout       << "."
				<< unsigned(McciVersion::getLocal(version));
	std::cout << "\n";
	std::cout << "\n";
	}

void App_t::addHeader()
	{
	McciBootloader_AppInfo_Wire_t fileAppInfo;
	static const uint8_t zeros[sizeof(fileAppInfo)] = { 0 };
	auto const pFileAppInfo = &this->fileimage.at(offsetof(McciBootloader_CortexPageZero_Wire_t, PageZero.AppInfo));
	memcpy(&fileAppInfo, pFileAppInfo, sizeof(fileAppInfo));

	// dump header if verbose
	if (this->fVerbose)
		dumpAppInfo("AppInfo from input", fileAppInfo);

	// an appinfo with defaults.
	McciBootloader_AppInfo_Wire_t appInfo;

	// if the file's appinfo looks good, use it
	if (fileAppInfo.magic.get() == fileAppInfo.kMagic &&
	    fileAppInfo.size.get() == sizeof(fileAppInfo) &&
	    fileAppInfo.targetAddress.get() != 0)
	    	{
		appInfo = fileAppInfo;
		if (appInfo.imagesize.get() == 0)
			{
			this->verbose("AppInfo.imagesize == 0, change to file size");
			appInfo.imagesize.put(this->fSize);
			}
		else
			{
			this->fSize = appInfo.imagesize.get();
			}
		}
	// otherwise make a new one
	else if (memcmp(pFileAppInfo, zeros, sizeof(zeros)) == 0)
		{
		this->verbose("AppInfo is zero, creating new one");
		appInfo.targetAddress.put(appInfo.kBootloaderAddress);
		appInfo.imagesize.put(this->fSize);
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

	// add GPS
	if (this->fAddGps)
		{
		uint32_t now = (uint32_t) time(nullptr);
		if (this->fVerbose)
			std::cout << "Posix time: " << now << "\n";
		appInfo.gpsTimestamp.put(now - 315964800 + 18);
		}

	// add key
	if (this->fSign)
		{
		appInfo.publicKey = keyfile.m_public;
		}

	if (this->fVerbose)
		dumpAppInfo("AppInfo after update", appInfo);

	// update the application image
	memcpy(pFileAppInfo, &appInfo, sizeof(appInfo));
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
		std::cout << std::setw(2) << unsigned(b[0]);
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

	mcci_tweetnacl_hash_sha512(
		&this->fileHash,
		&this->fileimage[0],
		this->fSize
		);

	/* truncate the image prior to appending the hash */
	this->fileimage.resize(this->fSize);

	/* append the hash */
	this->fileimage.insert(
		this->fileimage.end(),
		&this->fileHash.bytes[0],
		this->fileHash.bytes + sizeof(this->fileHash.bytes)
		);

	/* display the hash */
	if (this->fVerbose)
		this->dump(
			"Appended Hash",
			&this->fileimage.at(this->fSize),
			this->fileimage.data() + this->fileimage.size()
			);
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
	this->fileimage.resize(this->fSize + sizeof(mcci_tweetnacl_sha512_t::bytes));
	this->fileimage.insert(
		this->fileimage.end(),
		buffer,
		buffer + sizeOut
		);

	if (this->fVerbose)
		{
		this->dump(
			"signature",
			buffer,
			buffer + sizeOut
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
