#include "ELF32.h"
namespace Common::FileTypes::ELF
{
	ELF32::ELF32(Common::FileSystem::ESP::FileHandle* handle)
	{
		handle->Read<ElfHeader32>(&EntryHeader);

		handle->SetPosition(EntryHeader.ProgramHdrOffset);
		ProgHeader = new ElfProgramHeader32[EntryHeader.ProgramHdrEntries];
		handle->Read<ElfProgramHeader32>(ProgHeader, EntryHeader.ProgramHdrEntries);

		handle->SetPosition(EntryHeader.SectionHdrOffset);
		SectHeader = new ElfSectionHeader32[EntryHeader.SectionHdrEntries];
		handle->Read<ElfSectionHeader32>(SectHeader, EntryHeader.SectionHdrEntries);
	}
}
