#pragma once
#include <TypeDefs.h>
#include <FileSystem/FileHandle.h>
#include <FileTypes/ELF/ELFCommon.h>
#include <FileTypes/ELF/ELF32.h>
#include <FileTypes/ELF/ELF64.h>

namespace Common::FileTypes::ELF
{
#pragma pack(push, 1)
	struct ELF
	{
	public:
		ELF(Common::FileSystem::FileHandle* handle);

		BOOLEAN IsValidElf();

		ElfHeaderCommon CommonHeader;
		union
		{
			ELF32* Elf32;
			ELF64* Elf64;
		}Hdrs;

	private:
		BOOLEAN _isValidElf;

	};
#pragma pack(pop)

	
}

