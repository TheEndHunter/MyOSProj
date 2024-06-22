#include "PE32SectionHeader.h"

namespace Common::FileTypes::PE
{
	PE32SectionHeader::PE32SectionHeader()
	{
		Name[0] = 0;
		Name[1] = 0;
		Name[2] = 0;
		Name[3] = 0;
		Name[4] = 0;
		Name[5] = 0;
		Name[6] = 0;
		Name[7] = 0;
		Misc.Value = 0;
		VirtualAddress = 0;
		SizeOfRawData = 0;
		PointerToRawData = 0;
		PointerToRelocations = 0;
		PointerToLinenumbers = 0;
		NumberOfRelocations = 0;
		NumberOfLinenumbers = 0;
		Characteristics = PE32SectionFlags::SectionFlagReserved1;
	}

	PE32SectionHeader::PE32SectionHeader(FileSystem::FileHandle * handle)
	{
		handle->Read<CCHAR>(&Name[0], 8);
		handle->Read<UINT32>(&Misc.Value);
		handle->Read<UINT32>(&VirtualAddress);
		handle->Read<UINT32>(&SizeOfRawData);
		handle->Read<UINT32>(&PointerToRawData);
		handle->Read<UINT32>(&PointerToRelocations);
		handle->Read<UINT32>(&PointerToLinenumbers);
		handle->Read<UINT16>(&NumberOfRelocations);
		handle->Read<UINT16>(&NumberOfLinenumbers);
		handle->Read<PE32SectionFlags>(&Characteristics);
	}
}
