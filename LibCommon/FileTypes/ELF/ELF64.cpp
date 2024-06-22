#include "ELF64.h"

namespace Common::FileTypes::ELF
{
	ELF64::ELF64(Common::FileSystem::FileHandle* handle)
	{
		handle->Read<ElfHeader64>(&EntryHeader);

		handle->SetPosition(EntryHeader.ProgramHdrOffset);
		ProgHeader = new ElfProgramHeader64[EntryHeader.ProgramHdrEntries];
		handle->Read<ElfProgramHeader64>(ProgHeader, EntryHeader.ProgramHdrEntries);

		handle->SetPosition(EntryHeader.SectionHdrOffset);
		SectHeader = new ElfSectionHeader64[EntryHeader.SectionHdrEntries];
		handle->Read<ElfSectionHeader64>(SectHeader,EntryHeader.SectionHdrEntries);
	}
}
