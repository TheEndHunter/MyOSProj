#pragma once
#include <TypeDefs.h>
#include <FileTypes/PE/PE32DLLCharacteristics.h>
#include <FileSystem/FileHandle.h>
#include <FileTypes/PE/PE32DataDirectory.h>

namespace Common::FileTypes::PE
{
#pragma pack(push, 1)
	struct PE32OptionHeader32
	{
    public:
        PE32OptionHeader32(FileSystem::ESP::FileHandle* handle);
		UINT32 BaseOfData;
        /*
        *  NT additional fields
        */
        UINT32 ImageBase;
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
        UINT32 SizeOfStackReserve;
        UINT32 SizeOfStackCommit;
        UINT32 SizeOfHeapReserve;
        UINT32 SizeOfHeapCommit;
        UINT32 LoaderFlags;
        UINT32 NumberOfRvaAndSizes;
        PE32DataDirectory* DataDirectories;
	};
#pragma pack(pop)
}
