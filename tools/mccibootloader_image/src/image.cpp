/*

Module:	image.cpp

Function:
	image.cpp

Copyright and License:
	This file copyright (C) 2021 by

		MCCI Corporation
		3520 Krums Corners Road
		Ithaca, NY  14850

	See accompanying LICENSE file for copyright and license information.

Author:
	Terry Moore, MCCI Corporation	April 2021

*/

#include "mccibootloader_image.h"

#include "mccibootloader_elf.h"
#include <sstream>

using namespace McciBootloader_Elf;

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

void App_t::readImage()
	{
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

	// see if it's an elf file
	const ElfIdentBase_t * const pElfBase = (ElfIdentBase_t *)(&this->fileimage[0]);

	if (this->fForceBinary || ! pElfBase->magicIsValid())
		// treat as binary
		return;

	this->verbose(string("Treating ") + this->infilename + " as ELF file");

	if (! pElfBase->isValid(ElfIdentBase_t::e_machine_t::kArm))
		{
		// ELF, but not grokked
		this->fatal("Can't handle this ELF file");
		}

	if (! pElfBase->isLittleEndian())
		{
		this->fatal("big-endian ELF file not supported");
		}
	if (pElfBase->getType() != decltype(pElfBase->getType())::kExec)
		{
		this->fatal("only executable ELF images supported");
		}
	if (pElfBase->getClass() != decltype(pElfBase->getClass())::k32bit)
		{
		this->fatal("only 32-bit ELF images supported");
		}

	const ElfIdent32_t * const pElfIdent32 = (const ElfIdent32_t *)pElfBase;

	if (! pElfIdent32->phentsizeIsValid())
		{
		this->fatal("e_phentsize must be 0x20 for 32-bit images");
		}
	if (pElfIdent32->getPhoff() != sizeof(*pElfIdent32))
		{
		this->fatal("unexpected e_phoff value");
		}
	if (pElfIdent32->getPhnum() > 4)
		{
		ostringstream msg;
		msg << "ELF e_phnum > 4: " << pElfIdent32->getPhnum();
		this->fatal(msg.str());
		}

	// empty the file image and set up the elf image
	this->elf.image = std::move(this->fileimage);
	this->fileimage.clear();

	// record the header
	this->elf.pIdent32 = pElfIdent32;

	// scan the program header entries
	for (unsigned i = 0; i < pElfIdent32->getPhnum(); ++i)
		{
		const ElfIdent32_t::ProgramHeader_t ph { *pElfIdent32, i };

		if (ph.getType() != decltype(ph.getType())::kLoad)
			this->fatal("section type is not loadable");

		// dump the section
		if (this->fVerbose)
			{
			std::ostringstream msg;

			msg << "ELF: section " << i << ": "
			    << "vaddr(" << std::hex << ph.getVaddr() << ") "
			    << "paddr(" << std::hex << ph.getPaddr() << ") "
			    << "size(" << std::hex << ph.getMemsz() << ") "
			    << "vend(" << std::hex << ph.getVaddr() + ph.getMemsz() << ") "
			    << "offset(" << std::hex << ph.getOffset() << ") "
			    << "fsize(" << std::hex << ph.getFilesz() << ") "
			    << "flags(" << std::hex << ph.getFlags() << ")"
			    ;
			this->verbose(msg.str());
			}

		// we used to try skipping writable sections, but ...
		// that requires PHDRS in the link script. Instead, use
		// a heuristic to discard non-contiguous sections
		if ((ph.getFlags() & ph.getFlagW()) != 0)
			{
			if (this->elf.vHeaders.size() != 0 &&
			    this->fileimage.size() != ph.getPaddr() - this->elf.targetAddress)
			    	{
				if (this->fVerbose)
					{
					std::ostringstream msg;
					msg << "Elf: skipping non-contiguous writable section " << i;
					this->verbose(msg.str());
					}
				continue;
				}
			}
	
		// if it's the first, record the elf base address
		if (this->elf.vHeaders.size() == 0)
			{
			this->elf.targetAddress = ph.getPaddr();
			}

		// is the section contiguous with the first?
		if (this->fileimage.size() != ph.getPaddr() - this->elf.targetAddress)
			{
			this->fatal("ELF sections not contiguous");
			}

		// save the header
		this->elf.vHeaders.push_back(ph);

		// extract the section. We do this in two steps in case
		// the file size is shorter than the memsize.
		std::vector<std::uint8_t> section;
		const auto memsz = ph.getMemsz();
		const uint32_t nCopy = std::min(memsz, ph.getFilesz());
		section.reserve(memsz);
		section.insert(
			section.end(),
			this->elf.image.begin() + ph.getOffset(),
			this->elf.image.begin() + ph.getOffset() + nCopy
			);
		section.resize(memsz, 0);

		// append section to the file image
		this->fileimage.insert(
			this->fileimage.end(),
			section.begin(),
			section.end()
			);
		}

	this->fSize = this->fileimage.size();
	}

void App_t::writeImage()
	{
	std::ofstream outfile;
	std::string successMessage;

	if (this->isUsingElf())
		{
		this->elfImagePrep();
		this->fileimage = std::move(this->elf.image);
		}

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
	}

/// \brief transfer data from this->fileimage back to this->elf.image
void App_t::elfImagePrep()
	{
	// walk through each of the headers, and copy the section.
	for (auto & h : this->elf.vHeaders)
		{
		auto const elfbase = h.getOffset();
		auto const pbase = h.getPaddr() - this->elf.targetAddress;
		auto const memsz = h.getMemsz();
		auto const filesz = h.getFilesz();
	
		// if memsz is > filesz, look for non-zero values
		if (memsz > filesz)
			{
			for (auto i = memsz; i < filesz; ++i)
				{
				auto j = pbase + i;
				if (this->fileimage[j] != 0)
					this->fatal("elf section in file too small and non-zero data written");
				}
			} 

		// merge
		memcpy(
			&this->elf.image[elfbase],
			&this->fileimage[pbase],
			memsz
			);
		}
	}
