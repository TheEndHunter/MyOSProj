#include "PE32OptionHeader.h"

namespace Common::FileTypes::PE
{
	PE32OptionHeader::PE32OptionHeader()
	{
		Magic.Value = 0;
		MajorLinkerVersion = 0;
		MinorLinkerVersion = 0;
		SizeOfCode = 0;
		SizeOfInitializedData = 0;
		SizeOfUninitializedData = 0;
		AddressOfEntryPoint = 0;
		BaseOfCode = 0;
	}

	PE32OptionHeader::PE32OptionHeader(FileSystem::ESP::FileHandle* handle)
	{
		handle->Read(sizeof(Magic), &Magic);
		handle->Read(sizeof(MajorLinkerVersion), &MajorLinkerVersion);
		handle->Read(sizeof(MinorLinkerVersion), &MinorLinkerVersion);
		handle->Read(sizeof(SizeOfCode), &SizeOfCode);
		handle->Read(sizeof(SizeOfInitializedData), &SizeOfInitializedData);
		handle->Read(sizeof(SizeOfUninitializedData), &SizeOfUninitializedData);
		handle->Read(sizeof(AddressOfEntryPoint), &AddressOfEntryPoint);
		handle->Read(sizeof(BaseOfCode), &BaseOfCode);
	};
}
