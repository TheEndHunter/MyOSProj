
#include <FileTypes/PE/PE32Header.h>
#include <System/Allocator.h>

namespace Common::FileTypes::PE
{
	PE32Header::PE32Header()
	{
		Signature.Value = 0;
		Machine = MachineTypes::Unknown;
		NumberOfSections = 0;
		TimeDateStamp = 0;
		PointerToSymbolTable = 0;
		NumberOfSymbols = 0;
		SizeOfOptionalHeader = 0;
		Characteristics = PECharacteristics::System;
	}

	PE32Header::PE32Header(FileSystem::FileHandle * handle)
	{
		handle->Read<UINT32>(&Signature.Value);
		handle->Read<MachineTypes>(&Machine);
		handle->Read<UINT16>(&NumberOfSections);
		handle->Read<UINT32>(&TimeDateStamp);
		handle->Read<UINT32>(&PointerToSymbolTable);
		handle->Read<UINT32>(&NumberOfSymbols);
		handle->Read<UINT16>(&SizeOfOptionalHeader);
		handle->Read<PECharacteristics>(&Characteristics);
	}
}
