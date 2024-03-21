#pragma once
#include <TypeDefs.h>
#include <FileTypes/ELF/ELFCommon.h>
#include <FileTypes/ELF/ELF32.h>
#include <FileTypes/ELF/ELF64.h>

namespace Common::FileTypes::ELF
{
	struct ELF
	{
	public:

		ElfHeaderCommon CommonHeader;

		union
		{
			ElfHeader32* Elf32;
			ElfHeader64* Elf64;
		}Hdr;


	};
}

