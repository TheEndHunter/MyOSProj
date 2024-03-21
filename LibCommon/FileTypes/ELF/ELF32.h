#pragma once
#include <TypeDefs.h>

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

#define ELF32_ST_BIND(i)   ((i)>>4)
#define ELF32_ST_TYPE(i)   ((i)&0xf)
#define ELF32_ST_INFO(b,t) (((b)<<4)+((t)&0xf))
#define ELF32_ST_VISIBILITY(o) ((o)&0x3)
#define ELF32_R_SYM(i)	((i)>>8)
#define ELF32_R_TYPE(i)   ((unsigned char)(i))
#define ELF32_R_INFO(s,t) (((s)<<8)+(unsigned char)(t))

	enum ElfSectionFlags32 : UINT32
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
	struct ElfHeader32
	{
	public:
		UINT32 Version;
		UINT32 EntryPoint;
		UINT32 ProgramHdrOffset;
		UINT32 SectionHdrOffset;
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
	struct ElfSectionHeader32
	{
	public:
		UINT32 Name;
		ElfSectionType Type;
		ElfSectionFlags32 Flags;
		UINT32 Addr;
		UINT32 Offset;
		UINT32 Size;
		UINT32 Link;
		UINT32 Info;
		UINT32 Addralign;
		UINT32 Entsize;
	};
#pragma pack(pop)

#pragma pack(push, 1)
	struct ElfSymbol32
	{
	public:
		UINT32 Name;
		UINT32 Value;
		UINT32 Size;
		UINT8 Info;
		UINT8 Other;
		UINT16 SectionIndex;
	};
#pragma pack(pop)

#pragma pack (push,1)
	struct ElfRel32
	{
	public:
		UINT32 Offset;
		UINT32 Info;
	};
#pragma pack(pop)
#pragma pack (push,1)
	struct ElfRela32
	{
	public:
		UINT32 Offset;
		UINT32 Info;
		INT32 Addend;
	};
#pragma pack(pop)
}
