
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
		handle->Read(sizeof(Signature), &Signature);
		handle->Read(sizeof(Machine), &Machine);
		handle->Read(sizeof(NumberOfSections), &NumberOfSections);
		handle->Read(sizeof(TimeDateStamp), &TimeDateStamp);
		handle->Read(sizeof(PointerToSymbolTable), &PointerToSymbolTable);
		handle->Read(sizeof(NumberOfSymbols), &NumberOfSymbols);
		handle->Read(sizeof(SizeOfOptionalHeader), &SizeOfOptionalHeader);
		handle->Read(sizeof(Characteristics), &Characteristics);
	}
}
