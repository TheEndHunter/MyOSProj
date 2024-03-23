#include "ELF.h"

namespace Common::FileTypes::ELF
{
	ELF::ELF(Common::FileSystem::ESP::FileHandle* handle)
	{
		handle->Read(sizeof(ElfHeaderCommon), &CommonHeader);

		if (CommonHeader.Identity.Magic.Char[0] != 0x7F || CommonHeader.Identity.Magic.Char[1] != 0x45 || CommonHeader.Identity.Magic.Char[2] != 0x4C || CommonHeader.Identity.Magic.Char[3] != 0x46)
		{
			_isValidElf = false;
			return;
		}

		_isValidElf = true;

		if (CommonHeader.Identity.Class == ELFClass::ELF32)
		{
			handle->Read(sizeof(ElfHeader32), &Hdr.Elf32);
		}
		else if (CommonHeader.Identity.Class == ELFClass::ELF64)
		{
			handle->Read(sizeof(ElfHeader64), &Hdr.Elf64);
		}
		else
		{
			_isValidElf = false;
			return;
		}

		//TODO: Read program headers
	}
}