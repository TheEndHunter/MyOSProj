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
		handle->Read<UINT16>(&Magic.Value);
		handle->Read<UINT8>(&MajorLinkerVersion);
		handle->Read<UINT8>(&MinorLinkerVersion);
		handle->Read<UINT32>(&SizeOfCode);
		handle->Read<UINT32>(&SizeOfInitializedData);
		handle->Read<UINT32>(&SizeOfUninitializedData);
		handle->Read<UINT32>(&AddressOfEntryPoint);
		handle->Read<UINT32>(&BaseOfCode);
	};
}
