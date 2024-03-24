#pragma once
#include <TypeDefs.h>
#include <FileTypes/ELF/ELFCommon.h>
#include <FileSystem/ESP/FileHandle.h>

namespace Common::FileTypes::ELF
{

	/* Symbol Binding
		STB_LOCAL	0
		STB_GLOBAL	1
		STB_WEAK	2
		STB_LOOS	10
		STB_HIOS	12
		STB_LOPROC	13
		STB_HIPROC	15
	*/

	/* Symbol Type
		STT_NOTYPE	0
		STT_OBJECT	1
		STT_FUNC	2
		STT_SECTION	3
		STT_FILE	4
		STT_COMMON	5
		STT_TLS	6
		STT_LOOS	10
		STT_HIOS	12
		STT_LOPROC	13
		STT_HIPROC	15
	*/

	/*  Symbol Visibility
		STV_DEFAULT	0
		STV_INTERNAL	1
		STV_HIDDEN	2
		STV_PROTECTED	3
	*/

	/* Section Index 0
		st_name	0	No name
		st_value	0	Zero value
		st_size	0	No size
		st_info	0	No type, local binding
		st_other	0	Default visibility
		st_shndx	SHN_UNDEF	No section
	*/

#define ELF64_ST_BIND(i)   ((i)>>4)
#define ELF64_ST_TYPE(i)   ((i)&0xf)
#define ELF64_ST_INFO(b,t) (((b)<<4)+((t)&0xf))
#define ELF64_ST_VISIBILITY(o) ((o)&0x3)
#define ELF64_R_SYM(i)    ((i)>>32)
#define ELF64_R_TYPE(i)   ((i)&0xffffffffL)
#define ELF64_R_INFO(s,t) (((s)<<32)+((t)&0xffffffffL))

	enum class ElfSectionFlags64 : UINT64
	{
		WRITE = 0x1,
		ALLOC = 0x2,
		EXECINSTR = 0x4,
		MERGE = 0x10,
		STRINGS = 0x20,
		INFO_LINK = 0x40,
		LINK_ORDER = 0x80,
		OS_NONCONFORMING = 0x100,
		GROUP = 0x200,
		TLS = 0x400,
		MASKOS = 0x0ff00000,
		MASKPROC = 0xf0000000,
	};

	

#pragma pack(push, 1)
	struct ElfHeader64
	{
	public:
		
		UINT32 Version;
		UINT64 EntryPoint;
		UINT64 ProgramHdrOffset;
		UINT64 SectionHdrOffset;
		UINT32 Flags;
		UINT16 HdrSize;
		UINT16 ProgramHdrSize;
		UINT16 ProgramHdrEntries;
		UINT16 SectionHdrSize;
		UINT16 SectionHdrEntries;
		UINT16 SectionHdrStringTblIndex;
	};
#pragma pack(pop)

#pragma pack(push, 1)
	struct ElfSectionHeader64
	{
	public:
		UINT32 Name;
		ElfSectionType Type;
		ElfSectionFlags64 Flags;
		UINT64 Addr;
		UINT64 Offset;
		UINT64 Size;
		UINT32 Link;
		UINT32 Info;
		UINT64 Addralign;
		UINT64 Entsize;
	};
#pragma pack(pop)

#pragma pack(push, 1)
	struct ElfSymbol64
	{
	public:
		UINT32 Name;
		UINT8 Info;
		UINT8 Other;
		UINT16 SectionIndex;
		UINT64 Value;
		UINT64 Size;
	};
#pragma pack(pop)

#pragma pack (push,1)
	struct ElfRel63
	{
	public:
		UINT64 Offset;
		UINT64 Info;
	};
#pragma pack(pop)
#pragma pack (push,1)
	struct ElfRela64
	{
	public:
		UINT64 Offset;
		UINT64 Info;
		INT64 Addend;
	};
#pragma pack(pop)
#pragma pack (push,1)
	struct ElfProgramHeader64
	{
	public:
		ElfProgramType Type;
		ElfProgramFlags	ProgramFlags;
		UINT64	ProgramOffset;
		UINT64	ProgramVirtAddr;
		UINT64	ProgramPhysAddr;
		UINT64	ProgramFileSize;
		UINT64	ProgramMemSixe;
		UINT64	ProgramAlign;
	};
#pragma pack(pop)
#pragma pack (push,1)
	struct ELF64
	{
	public:
		ELF64(Common::FileSystem::ESP::FileHandle* handle);
		ElfHeader64 EntryHeader;
		ElfProgramHeader64* ProgHeader;
		ElfSectionHeader64* SectHeader;
	};
#pragma pack(pop)
}