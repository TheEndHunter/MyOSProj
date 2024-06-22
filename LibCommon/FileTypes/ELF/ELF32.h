#pragma once
#include <TypeDefs.h>
#include <FileTypes/ELF/ELFCommon.h>
#include <FileSystem/FileHandle.h>

namespace Common::FileTypes::ELF
{
#define ELF32_ST_BIND(i)   ((i)>>4)
#define ELF32_ST_TYPE(i)   ((i)&0xf)
#define ELF32_ST_INFO(b,t) (((b)<<4)+((t)&0xf))
#define ELF32_ST_VISIBILITY(o) ((o)&0x3)
#define ELF32_R_SYM(i)	((i)>>8)
#define ELF32_R_TYPE(i)   ((unsigned char)(i))
#define ELF32_R_INFO(s,t) (((s)<<8)+(unsigned char)(t))

	enum class ElfSectionFlags32 : UINT32
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
#pragma pack (push,1)
	struct ElfProgramHeader32
	{
	public:
		ElfProgramType Type;
		UINT32	ProgramOffset;
		UINT32	ProgramVirtAddr;
		UINT32	ProgramPhysAddr;
		UINT32	ProgramFileSize;
		UINT32	ProgramMemSize;
		ElfProgramFlags	ProgramFlags;
		UINT32	ProgramAlign;
	};
#pragma pack(pop)

#pragma pack (push,1)
	struct ELF32
	{
	public:
		ELF32(Common::FileSystem::FileHandle* handle);
		ElfHeader32 EntryHeader;
		ElfProgramHeader32* ProgHeader;
		ElfSectionHeader32* SectHeader;
	};
#pragma pack(pop)
}
