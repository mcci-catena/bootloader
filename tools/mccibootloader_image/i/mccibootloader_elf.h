/*

Module:	mccibootloader_elf.h

Function:
	Simple definion of ELF format for bootloader tools

Copyright and License:
	This file copyright (C) 2021 by

		MCCI Corporation
		3520 Krums Corners Road
		Ithaca, NY  14850

	See accompanying LICENSE file for copyright and license information.

Author:
	Terry Moore, MCCI Corporation	April 2021

*/

#ifndef _mccibootloader_elf_h_
#define _mccibootloader_elf_h_	/* prevent multiple includes */

#pragma once

#include <cstdint>

namespace McciBootloader_Elf {

///< Base class for ELF header blocks (32 and 64-bit)
class ElfIdentBase_t
	{
public:
	/// \brief the magic number for ELF headers
	static constexpr std::uint8_t kElfMagic[4] = { 0x7F, 'E', 'L', 'F' };

protected:
	constexpr std::uint16_t get16(const std::uint8_t (&va)[2]) const
		{
		return this->isLittleEndian()
			? (std::uint16_t(va[1]) << 8) | std::uint16_t((va[0]) << 0)
			: (std::uint16_t(va[0]) << 8) | std::uint16_t((va[1]) << 0)
			;
		}
	constexpr std::uint32_t get32(const std::uint8_t (&va)[4]) const
		{
		return this->isLittleEndian()
			? (std::uint32_t(va[3]) << 24) | (std::uint32_t(va[2]) << 16) | (std::uint32_t(va[1]) << 8) | va[0]
			: (std::uint32_t(va[0]) << 24) | (std::uint32_t(va[1]) << 16) | (std::uint32_t(va[2]) << 8) | va[3]
			;
		}
	constexpr std::uint64_t get64(const std::uint8_t (&va)[8]) const
		{
		return this->isLittleEndian()
			? (std::uint64_t(va[7]) << 56) | (std::uint64_t(va[6]) << 48) | (std::uint64_t(va[5]) << 40) | (std::uint64_t(va[4]) << 32) |
			  (std::uint64_t(va[3]) << 24) | (std::uint64_t(va[2]) << 16) | (std::uint64_t(va[1]) <<  8) | (std::uint64_t(va[0]) <<  0)
			: (std::uint64_t(va[0]) << 56) | (std::uint64_t(va[1]) << 48) | (std::uint64_t(va[2]) << 40) | (std::uint64_t(va[3]) << 32) |
			  (std::uint64_t(va[4]) << 24) | (std::uint64_t(va[5]) << 16) | (std::uint64_t(va[6]) <<  8) | (std::uint64_t(va[7]) <<  0)
			;
		}

public:
	/// \brief default constructor
	ElfIdentBase_t() {};

	std::uint8_t ei_magic[4];	///< the magic value to identify the header
	constexpr bool magicIsValid() const
		{
		return 	this->ei_magic[0] == kElfMagic[0] &&
			this->ei_magic[1] == kElfMagic[1] &&
			this->ei_magic[2] == kElfMagic[2] &&
			this->ei_magic[3] == kElfMagic[3];
		}

	std::uint8_t ei_class;		///< the class (32 or 64 bit header)
	/// \brief valid values of \c ei_class
	enum class ei_class_t : std::uint8_t
		{
		k32bit = 1,		///< this is a 32-bit header
		k64bit = 2,		///< this is a 64-bit header
		};
	/// \brief check whether image class (32/64 bit) indicator is valid
	constexpr bool classIsValid() const
		{
		return  1 <= this->ei_class &&
			this->ei_class <= 2; 
		}
	/// \brief return the class of the image
	constexpr ei_class_t getClass() const
		{
		return ei_class_t(this->ei_class);
		}
	
	std::uint8_t ei_data;		///< the endianness
	enum class ei_data_t : std::uint8_t
		{
		kLittleEndian = 1,	///< this is a little-endian file
		kBigEndian = 2,		///< this is a big-endian file 
		};
	constexpr bool dataIsValid() const
		{
		return	1 <= this->ei_data && this->ei_data <= 2;
		}
	constexpr ei_data_t getData() const { return ei_data_t(this->ei_data); }
	constexpr bool isLittleEndian() const
		{
		return this->getData() == ei_data_t::kLittleEndian;
		}

	std::uint8_t ei_version;	///< the version
	enum class ei_version_t : std::uint8_t
		{
		kVersion1 = 1,		///< this is version 1
		};
	constexpr bool eiVersionIsValid() const
		{
		return this->ei_version == 1;
		}
	
	/// \brief the OS ABI
	///
	/// \note details taken from Wikipedia 2021-04-03
	///
	std::uint8_t ei_osabi;
	enum class ei_osabi_t : std::uint8_t
		{
		kNone = 0,	///< the value we care about.
		};
	constexpr bool osabiIsValid() const
		{
		return this->ei_osabi == 0;
		}
	
	/// \brief the ABI
	///
	/// \note we require this to be zero.
	///
	std::uint8_t ei_abi;
	enum class ei_abi_t : std::uint8_t
		{
		kNone = 0,	///< there's no ABI for us.
		};
	/// \brief return \c true if the ABI value is valid in this header.
	constexpr bool abiIsValid() const
		{
		return this->ei_abi == 0;
		}

	/// \brief padding, should be zero.
	std::uint8_t ei_padding[7];
	/// \brief return true if padding is valid
	constexpr bool paddingIsValid() const
		{
		return ! (ei_padding[0] || ei_padding[1] || ei_padding[2] ||
			  ei_padding[3] || ei_padding[4] || ei_padding[5] ||
			  ei_padding[6]);
		}
	
	/// \brief image type
	std::uint8_t e_type[2];
	/// \brief type values for ELF header
	enum class e_type_t : std::uint16_t
		{
		kNone = 0,
		kRel = 1,
		kExec = 2,	///< executable image.
		kDyn = 3,
		kCore = 4,
		kLoOS = 0xFE00,
		kHiOS = 0xFEFF,
		kLoProc = 0xFF00,
		kHiProc = 0xFFFF,
		};
	/// \brief return type value from this header
	constexpr e_type_t getType() const
		{
		return this->isLittleEndian() ? e_type_t((this->e_type[1] << 8) | this->e_type[0])
					      : e_type_t((this->e_type[0] << 8) | this->e_type[1])
					      ;
		}

	/// \brief target machine architecture; we only declare a subset.
	std::uint8_t e_machine[2];
	enum class e_machine_t : std::uint16_t
		{
		kNone = 0,
		kArm = 0x28,	///< ARMv7/Aarch32
		kRISCV = 243,	///< RISC-V
		};
	/// \brief return the target machine
	constexpr e_machine_t getMachine() const
		{
		return this->isLittleEndian() ? e_machine_t((this->e_machine[1] << 8) | this->e_machine[0])
					      : e_machine_t((this->e_machine[0] << 8) | this->e_machine[1])
					      ;
		}
	/// \brief check whether the target machine is the desired
	constexpr bool machineIsValid(e_machine_t desiredMachine) const
		{
		return this->getMachine() == desiredMachine;
		}
	
	/// \brief version number
	std::uint8_t e_version[4];
	enum class e_version_t : std::uint32_t
		{
		kVersion1 = 1,
		};
	/// \brief return version from this header.
	constexpr e_version_t getElfVersion() const
		{
		return e_version_t(this->get32(this->e_version));
		}
	/// \brief return \c true if header version is valid.
	constexpr bool elfVersionIsValid() const
		{
		return this->getElfVersion() == e_version_t::kVersion1;
		}

	/// \brief return \c true if base header is valid
	constexpr bool isValid(e_machine_t desiredMachine = e_machine_t::kArm) const
		{
		return 	this->magicIsValid() &&
			this->classIsValid() &&
			this->dataIsValid() &&
			this->eiVersionIsValid() &&
			this->abiIsValid() &&
			this->paddingIsValid() &&
			this->machineIsValid(desiredMachine) &&
			this->elfVersionIsValid();
		}

	// now things get tricky because of the variations due to size.
	};

///< 32-bit ElfIdent header
class ElfIdent32_t : public ElfIdentBase_t
	{
public:
	/// \brief expected size of header in bytes
	static constexpr unsigned kExpectedSize = 52;

	/// \brief default constructor
	ElfIdent32_t() {}

	std::uint8_t	e_entry[4];	///< memory address of entry point
	/// \brief return entry point.
	constexpr std::uint32_t getEntry() const
		{ return this->get32(this->e_entry); }

	std::uint8_t	e_phoff[4];	///< offset to program header table
	/// \brief return program header offset.
	constexpr std::uint32_t getPhoff() const
		{ return this->get32(this->e_phoff); }

	std::uint8_t	e_shoff[4];	///< offset to segment header table
	/// \brief return segment header offset.
	constexpr std::uint32_t getShoff() const
		{ return this->get32(this->e_shoff); }

	std::uint8_t	e_flags[4];	///< executable flags
	/// \brief return segment header offset.
	constexpr std::uint32_t getFlags() const
		{ return this->get32(this->e_flags); }

	std::uint8_t	e_ehsize[2]; 	///< size of this in bytes
	/// \brief return header size
	constexpr std::uint16_t getEhsize() const
		{ return this->get16(this->e_ehsize); }

	std::uint8_t	e_phentsize[2];	///< size of program header entry in bytes
	/// \brief return program header entry size
	constexpr std::uint16_t getPhentsize() const
		{ return this->get16(this->e_phentsize); }
	/// \brief check program header entry size
	constexpr bool phentsizeIsValid() const
		{ return this->get16(this->e_phentsize) == 0x20; }

	std::uint8_t	e_phnum[2];	///< count of program header entries
	/// \brief return number of program header entries
	constexpr std::uint16_t getPhnum() const
		{ return this->get16(this->e_phnum); }

	std::uint8_t	e_shentsize[2];	///< size of segment header entry in bytes
	/// \brief return size of segment header entries in bytes
	constexpr std::uint16_t getShentsize() const
		{ return this->get16(this->e_shentsize); }

	std::uint8_t	e_shnum[2];	///< count of segment header entries
	/// \brief return number of segment header entries
	constexpr std::uint16_t getShnum() const
		{ return this->get16(this->e_shnum); }

	std::uint8_t	e_shstrndx[2];	///< index of segment table header for section names
	/// \brief return index of segment table header containing segment names.
	constexpr std::uint16_t getShstrndx() const
		{ return this->get16(this->e_shstrndx); }

	/// \brief the raw structure of a program header
	struct ProgramHeaderImage_t
		{
		uint8_t	p_type[4];	///< segment type
		uint8_t p_offset[4];	///< offset of image in file image
		uint8_t p_vaddr[4];	///< offset of image in memory
		uint8_t p_paddr[4];	///< physical address of image
		uint8_t p_filesz[4];	///< size of section in file (bytes)
		uint8_t p_memsz[4];	///< size of section in memory (bytes)
		uint8_t	p_flags[4];	///< section flags
		uint8_t p_align[4];	///< alignment (power of 2)
		};

	static_assert(sizeof(ProgramHeaderImage_t) == 0x20, "Wrong size for 32-bit ProgramHeaderImage_t");

	/// \brief check whether a ElfIdent32_t looks valid
	bool isValid() const
		{
		return this->ElfIdentBase_t::isValid() && this->phentsizeIsValid();
		}

	/// \brief 
	class ProgramHeader_t
		{
	public:
		ProgramHeader_t(const ElfIdent32_t &Ident, unsigned iHdr)
			: m_ident(Ident)
			, m_hdr(
				*(ProgramHeaderImage_t *)
					((const std::uint8_t *)&Ident
						+ Ident.getPhoff()
						+ Ident.getPhentsize() * iHdr
					)
				)
			{}

	protected:
		constexpr std::uint32_t get(const std::uint8_t (&va)[4]) const
			{
			return m_ident.isLittleEndian()
				? (std::uint32_t(va[3]) << 24) | (std::uint32_t(va[2]) << 16) | (std::uint32_t(va[1]) << 8) | va[0]
				: (std::uint32_t(va[0]) << 24) | (std::uint32_t(va[1]) << 16) | (std::uint32_t(va[2]) << 8) | va[3]
				;
			}

	public:
//		uint8_t	p_type[4];	///< segment type
		/// \brief program header types
		enum class p_type_t : std::uint32_t
			{
			kNull = 0,		///< unused entry
			kLoad = 1,		///< loadable segment
			kDynamic = 2,		///< dynamic linking info
			kInterp = 3,		///< information for interpreter
			kNote = 4,		///< Auxiliary info
			kPhdr = 6,		///< segment containging phdr
			kTls = 7,		///< thread-local storage template
			kLoOS = 0x60000000,	///< first OS-specific item
			kHiOS = 0x6FFFFFFF,	///< last OS-specific item
			kLoProc = 0x7000000,	///< first processor-specific item
			kHiProc = 0x7FFFFFFF,	///< last procssor-specific item
			};

		/// \brief return the header type
		p_type_t getType() const
			{ return p_type_t(this->get(this->m_hdr.p_type)); }

//		uint8_t p_offset[4];	///< offset of image in file image
		/// \brief return offset of segment in file image
		std::uint32_t getOffset() const
			{ return this->get(this->m_hdr.p_offset); }

//		uint8_t p_vaddr[4];	///< offset of image in memory
		/// \brief return offset of segment in memory
		std::uint32_t getVaddr() const
			{ return this->get(this->m_hdr.p_vaddr); }

//		uint8_t p_paddr[4];	///< physical address of image
		/// \brief return physical address of segment.
		std::uint32_t getPaddr() const
			{ return this->get(this->m_hdr.p_paddr); }

//		uint8_t p_filesz[4];	///< size of section in file (bytes)
		/// \brief return size of section in file.
		std::uint32_t getFilesz() const
			{ return this->get(this->m_hdr.p_filesz); }

//		uint8_t p_memsz[4];	///< size of section in memory (bytes)
		/// \brief return size of section in memory.
		std::uint32_t getMemsz() const
			{ return this->get(this->m_hdr.p_memsz); }

//		uint8_t	p_flags[4];	///< section flags
		/// \brief return section flags.
		std::uint32_t getFlags() const
			{ return this->get(this->m_hdr.p_flags); }
		static constexpr std::uint32_t getFlagX()
			{ return 0x1; }
		static constexpr std::uint32_t getFlagW()
			{ return 0x2; }
		static constexpr std::uint32_t getFlagR()
			{ return 0x4; }

//		uint8_t p_align[4];	///< alignment (power of 2)
		/// \brief return section alignment.
		///
		/// \return 0 or 1 if section is not aligned; otherwise 
		///	alignment value, which must be a value of two.
		std::uint32_t getAlign() const
			{ return this->get(this->m_hdr.p_align); }
		
	private:
		///< reference to Elf identifier governing this header
		const ElfIdent32_t &m_ident;
		///< reference to physical image of header
		const ProgramHeaderImage_t &m_hdr;
		};
	};

static_assert(sizeof(ElfIdent32_t) == ElfIdent32_t::kExpectedSize, "ElfIdent32_t size is wrong");

} // namespace McciBootloader_Elf

#endif /* _mccibootloader_elf_h_ */
