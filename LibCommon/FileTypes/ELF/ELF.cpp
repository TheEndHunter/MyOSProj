#include "ELF.h"

namespace Common::FileTypes::ELF
{
	ELF::ELF(Common::FileSystem::ESP::FileHandle* handle)
	{
		handle->SetPosition(0UL);
		handle->Read<ElfHeaderCommon>(&CommonHeader);

		if (CommonHeader.Identity.Magic.Char[0] != 0x7F || CommonHeader.Identity.Magic.Char[1] != 0x45 || CommonHeader.Identity.Magic.Char[2] != 0x4C || CommonHeader.Identity.Magic.Char[3] != 0x46)
		{
			_isValidElf = false;
			return;
		}


		if (CommonHeader.Identity.Class == ELFClass::ELF32)
		{
			Hdrs.Elf32 = new ELF32(handle);
		}
		else if (CommonHeader.Identity.Class == ELFClass::ELF64)
		{
			Hdrs.Elf64 = new ELF64(handle);
		}
		else
		{
			_isValidElf = false;
			return;
		}

		_isValidElf = true;
	}

	BOOLEAN ELF::IsValidElf()
	{
		return _isValidElf;
	}
}