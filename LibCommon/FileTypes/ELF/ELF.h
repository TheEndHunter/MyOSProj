#pragma once
#include <TypeDefs.h>
#include <FileTypes/ELF/ELFCommon.h>
#include <FileTypes/ELF/ELF32.h>
#include <FileTypes/ELF/ELF64.h>
#include <FileSystem/ESP/FileHandle.h>

namespace Common::FileTypes::ELF
{
	struct ELF
	{
	public:
		ELF(Common::FileSystem::ESP::FileHandle* handle);

		BOOLEAN IsValidElf();

		ElfHeaderCommon CommonHeader;

		union
		{
			ElfHeader32* Elf32;
			ElfHeader64* Elf64;
		}Hdr;
	private:
		BOOLEAN _isValidElf;

	};
}

