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

/****************************************************************************\
|
|	Manifest constants & typedefs.
|
\****************************************************************************/



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
	if (this->fHash || this->fSign)
		this->hFile = fopen(this->filename.c_str(), "r+b");
	else
		this->hFile = fopen(this->filename.c_str(), "rb");
	
	if (this->hFile == nullptr)
		{
		string msg = "can't open " + this->filename;
		std::perror(msg.c_str());
		std::exit(EXIT_FAILURE);
		}

	if (this->fHash || this->fSign)
		this->addHeader();

	if (this->fHash || this->fSign)
		this->addHash();

	if (this->fSign)
		this->addSignature();

	fclose(this->hFile);

	return EXIT_SUCCESS;
	}

void App_t::scanArgs(int argc, char **argv)
	{
	this->argc = argc;
	this->argv = argv;
	this->progname = filebasename(argv[0]);
	vector<string> posArgs;

	bool fOptOk = true;
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
		this->usage("missing filename");
		}
	if (posArgs.size() > 1)
		{
		this->usage("extra arguments");
		}

	this->filename = posArgs[0];
	}

void App_t::addHeader()
	{
	// get size
	if (fseek(this->hFile, 0, SEEK_END) != 0)
		{
		std::perror("can't seek to end");
		std::exit(EXIT_FAILURE);
		}
	auto const fSize = ftell(this->hFile);
	if (fSize == -1L)
		{
		std::perror("can't get size");
		std::exit(EXIT_FAILURE);
		}
	this->fSize = (unsigned long) fSize;

	if (fseek(this->hFile, offsetof(McciBootloader_CortexPageZero_Wire_t, PageZero.AppInfo), SEEK_SET) != 0)
		{
		std::perror("can't seek to header");
		std::exit(EXIT_FAILURE);
		}

	McciBootloader_AppInfo_Wire_t fileAppInfo;
	if (fread(&fileAppInfo, sizeof(fileAppInfo), 1, this->hFile) != 1)
		{
		std::perror("can't seek to header");
		std::exit(EXIT_FAILURE);
		}
	
	if (fseek(this->hFile, offsetof(McciBootloader_CortexPageZero_Wire_t, PageZero.AppInfo), SEEK_SET) != 0)
		{
		std::perror("can't seek to header");
		std::exit(EXIT_FAILURE);
		}

	McciBootloader_AppInfo_Wire_t appInfo;

	if (fileAppInfo.magic.get() == fileAppInfo.kMagic &&
	    fileAppInfo.size.get() == sizeof(fileAppInfo) &&
	    fileAppInfo.imagesize.get() != 0)
	    	{
		appInfo = fileAppInfo;
		this->fSize = appInfo.imagesize.get();
		if (appInfo.targetAddress.get() == 0)
			appInfo.targetAddress.put(appInfo.kBootloaderAddress);
		}
	else
		{
		appInfo.targetAddress.put(appInfo.kBootloaderAddress);
		appInfo.imagesize.put(this->fSize);
		}

	appInfo.authsize.put(
		sizeof(mcci_tweetnacl_sha512_t) +
		mcci_tweetnacl_sign_signature_size()
		);
	uint32_t now = (uint32_t) time(nullptr);
	appInfo.gpsTimestamp.put(now + 18);

	if (fwrite(&appInfo, sizeof(appInfo), 1, this->hFile) != 1)
		{
		std::perror("can't write header");
		std::exit(EXIT_FAILURE);
		}
	}

void
App_t::addHash()
	{
	uint8_t *pBuffer = (uint8_t *)malloc(this->fSize);
	if (pBuffer == nullptr)
		{
		this->fatal("can't allocate memory");
		}

	if (fseek(this->hFile, 0, SEEK_SET) != 0)
		{
		std::perror("can't seek to front");
		std::exit(EXIT_FAILURE);
		}

	if (fread(pBuffer, this->fSize, 1, this->hFile) != 1)
		{
		std::perror("can't read file");
		std::exit(EXIT_FAILURE);
		}

	mcci_tweetnacl_hash_sha512(
		&this->fileHash,
		pBuffer,
		this->fSize
		);

	/* file is positioned at the place for the hash */
	if (fwrite(&this->fileHash.bytes, sizeof(this->fileHash.bytes), 1, this->hFile) != 1)
		{
		std::perror("can't read hash");
		std::exit(EXIT_FAILURE);
		}
	}


/**** end of main.c ****/
