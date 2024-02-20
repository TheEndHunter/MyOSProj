#pragma once
#include <TypeDefs.h>

namespace Common::FileTypes
{
	struct COFF_HDR
	{
	public:
		UINT16 Machine;
		UINT16 NumberOfSections;
		UINT32 TimeDateStamp;
		UINT32 PointerToSymbolTable;
		UINT32 NumberOfSymbols;
		UINT16 SizeOfOptionalHeader;
		UINT16 Characteristics;
	};

	struct COFF_SECTION_HDR
	{
	public:
		UINT8 Name[8];
		UINT32 VirtualSize;
		UINT32 VirtualAddress;
		UINT32 SizeOfRawData;
		UINT32 PointerToRawData;
		UINT32 PointerToRelocations;
		UINT32 PointerToLinenumbers;
		UINT16 NumberOfRelocations;
		UINT16 NumberOfLinenumbers;
		UINT32 Characteristics;
	};
};


