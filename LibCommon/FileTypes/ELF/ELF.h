#pragma once
#include <TypeDefs.h>

namespace Common::FileTypes::ELF
{
	const UINTN MAX_IDENT_LEN = 16ull;

	enum class ELFClass : UINT8
	{
		None  = 0,
		ELF32 = 1,
		ELF64 = 2
	};

	enum class ELFData : UINT8
	{
		None = 0,
		LSB  = 1,
		MSB  = 2
	};

	typedef UINT32 Elf32_Addr;
	typedef UINT32 Elf32_Off;
	typedef UINT16 Elf32_Half;
	typedef UINT32 Elf32_Word;
	typedef INT32  Elf32_Sword;

	typedef UINT64 Elf64_Addr;
	typedef UINT32 Elf64_Off;
	typedef UINT16 Elf64_Half;
	typedef UINT32 Elf64_Word;
	typedef INT32  Elf64_Sword;
	typedef UINT64 Elf64_Xword;
	typedef INT64  Elf64_Sxword;

    typedef struct ELFHeader32
    {
        UINT8           Ident[MAX_IDENT_LEN];
        Elf32_Half      Type;
        Elf32_Half      Machine;
        Elf32_Word      Version;
        Elf32_Addr      Entry;
        Elf32_Off       Phoff;
        Elf32_Off       Shoff;
        Elf32_Word      Flags;
        Elf32_Half      Ehsize;
        Elf32_Half      Phentsize;
        Elf32_Half      Phnum;
        Elf32_Half      Shentsize;
        Elf32_Half      Shnum;
        Elf32_Half      Shstrndx;
    };

    typedef struct ElfHeader64 
    {
        UINT8           Ident[MAX_IDENT_LEN];
        Elf64_Half      Type;
        Elf64_Half      Machine;
        Elf64_Word      Version;
        Elf64_Addr      Entry;
        Elf64_Off       Phoff;
        Elf64_Off       Shoff;
        Elf64_Word      Flags;
        Elf64_Half      Ehsize;
        Elf64_Half      Phentsize;
        Elf64_Half      Phnum;
        Elf64_Half      Shentsize;
        Elf64_Half      Shnum;
        Elf64_Half      Shstrndx;
    };

}