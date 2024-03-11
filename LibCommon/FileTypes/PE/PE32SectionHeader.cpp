#include "PE32SectionHeader.h"

namespace Common::FileTypes::PE
{
	PE32SectionHeader::PE32SectionHeader(FileSystem::FileHandle * handle)
	{
		handle->Read(sizeof(Name), &Name);
		handle->Read(sizeof(Misc), &Misc.value);
		handle->Read(sizeof(VirtualAddress), &VirtualAddress);
		handle->Read(sizeof(SizeOfRawData), &SizeOfRawData);
		handle->Read(sizeof(PointerToRawData), &PointerToRawData);
		handle->Read(sizeof(PointerToRelocations), &PointerToRelocations);
		handle->Read(sizeof(PointerToLinenumbers), &PointerToLinenumbers);
		handle->Read(sizeof(NumberOfRelocations), &NumberOfRelocations);
		handle->Read(sizeof(NumberOfLinenumbers), &NumberOfLinenumbers);
		handle->Read(sizeof(Characteristics), &Characteristics);
	}
}
