#include "ELF32.h"
namespace Common::FileTypes::ELF
{
	ELF32::ELF32(Common::FileSystem::FileHandle* handle)
	{
        handle->Read<ElfHeader32>(&EntryHeader);

        // Validate ELF identity and supported features
        if (!ValidateMagic(EntryHeader.Common.Identity) ||
            !ValidateClass(EntryHeader.Common.Identity) ||
            !ValidateDataType(EntryHeader.Common.Identity) ||
            !ValidateVersion(EntryHeader.Common.Identity))
        {
            // Invalid ELF header
            Valid = false;
            return;
        }

        // Optional: enforce known OS ABI if desired
        if (!IsSupportedOSABI(EntryHeader.Common.Identity.OSABI))
        {
            Valid = false;
            return;
        }

        handle->SetPosition(EntryHeader.ProgramHdrOffset);
        ProgHeader = new ElfProgramHeader32[EntryHeader.ProgramHdrEntries];
        if (ProgHeader == nullptr)
        {
            Valid = false;
            return;
        }
        handle->Read<ElfProgramHeader32>(ProgHeader, EntryHeader.ProgramHdrEntries);

        handle->SetPosition(EntryHeader.SectionHdrOffset);
        SectHeader = new ElfSectionHeader32[EntryHeader.SectionHdrEntries];
        if (SectHeader == nullptr)
        {
            delete[] ProgHeader;
            ProgHeader = nullptr;
            Valid = false;
            return;
        }
        handle->Read<ElfSectionHeader32>(SectHeader, EntryHeader.SectionHdrEntries);

        Valid = true;
	}

    ELF32::~ELF32()
    {
        delete[] ProgHeader;
        delete[] SectHeader;
        ProgHeader = nullptr;
        SectHeader = nullptr;
    }
}
