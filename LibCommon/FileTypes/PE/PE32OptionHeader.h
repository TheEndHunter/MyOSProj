#pragma once
#include <TypeDefs.h>
#include <FileSystem/FileHandle.h>

namespace Common::FileTypes::PE
{
#pragma pack(push, 1)
	struct PE32OptionHeader
	{
	public:
		PE32OptionHeader();

		PE32OptionHeader(FileSystem::ESP::FileHandle* handle);
		/*
		*  Standard Fields
		*/
		union
		{
			CCHAR Char[2];
			UINT16 Value;
		}Magic;
		UINT8 MajorLinkerVersion;
		UINT8 MinorLinkerVersion;
		UINT32 SizeOfCode;
		UINT32 SizeOfInitializedData;
		UINT32 SizeOfUninitializedData;
		UINT32 AddressOfEntryPoint;
		UINT32 BaseOfCode;
	};
#pragma pack(pop)
}
