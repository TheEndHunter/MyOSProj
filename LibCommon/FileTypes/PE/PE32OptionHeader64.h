#pragma once
#include <TypeDefs.h>
#include <FileTypes/PE/PE32DLLCharacteristics.h>
#include <FileSystem/FileHandle.h>
#include <FileTypes/PE/PE32DataDirectory.h>

namespace Common::FileTypes::PE
{   
#pragma pack(push, 1)
	struct PE32OptionHeader64
	{
    public:
        PE32OptionHeader64(FileSystem::FileHandle* handle);
        /*
        *  NT additional fields
        */
        UINT64 ImageBase;
        UINT32 SectionAlignment;
        UINT32 FileAlignment;
        UINT16 MajorOperatingSystemVersion;
        UINT16 MinorOperatingSystemVersion;
        UINT16 MajorImageVersion;
        UINT16 MinorImageVersion;
        UINT16 MajorSubsystemVersion;
        UINT16 MinorSubsystemVersion;
        UINT32 Win32VersionValue;
        UINT32 SizeOfImage;
        UINT32 SizeOfHeaders;
        UINT32 CheckSum;
        UINT16 Subsystem;
        PE32DLLCharacteristics DllCharacteristics;
        UINT64 SizeOfStackReserve;
        UINT64 SizeOfStackCommit;
        UINT64 SizeOfHeapReserve;
        UINT64 SizeOfHeapCommit;
        UINT32 LoaderFlags;
        UINT32 NumberOfRvaAndSizes;
        PE32DataDirectory* DataDirectories;
	};
#pragma pack(pop)
}
