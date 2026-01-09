#include "ELF64.h"

namespace Common::FileTypes::ELF
{
	ELF64::ELF64(Common::FileSystem::FileHandle* handle)
	{
        handle->Read<ElfHeader64>(&EntryHeader);

        // Validate ELF identity and supported features
        if (!ValidateMagic(EntryHeader.Common.Identity) ||
            !ValidateClass(EntryHeader.Common.Identity) ||
            !ValidateDataType(EntryHeader.Common.Identity) ||
            !ValidateVersion(EntryHeader.Common.Identity))
        {
            Valid = false;
            return;
        }

        if (!IsSupportedOSABI(EntryHeader.Common.Identity.OSABI))
        {
            Valid = false;
            return;
        }

        handle->SetPosition(EntryHeader.ProgramHdrOffset);
        ProgHeader = reinterpret_cast<ElfProgramHeader64*>(new ElfProgramHeader64[EntryHeader.ProgramHdrEntries]);
        if (ProgHeader == nullptr)
        {
            Valid = false;
            return;
        }
        handle->Read<ElfProgramHeader64>(ProgHeader, EntryHeader.ProgramHdrEntries);

        handle->SetPosition(EntryHeader.SectionHdrOffset);
        SectHeader = reinterpret_cast<ElfSectionHeader64*>(new ElfSectionHeader64[EntryHeader.SectionHdrEntries]);
        if (SectHeader == nullptr)
        {
            delete[] ProgHeader;
            ProgHeader = nullptr;
            Valid = false;
            return;
        }
        handle->Read<ElfSectionHeader64>(SectHeader,EntryHeader.SectionHdrEntries);

        Valid = true;
	}

    ELF64::~ELF64()
    {
        delete[] ProgHeader;
        delete[] SectHeader;
        ProgHeader = nullptr;
        SectHeader = nullptr;
    }
}
