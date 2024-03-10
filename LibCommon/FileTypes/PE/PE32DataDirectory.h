#pragma once
#include <TypeDefs.h>

namespace Common::FileTypes::PE
{
	const static UINTN MAX_PE32_DATA_DIRECTORIES = 16;

	//Export Directory
	const static UINTN PE32_DATA_DIRECTORY_EXPORT = 0;
	//Import Directory
	const static UINTN PE32_DATA_DIRECTORY_IMPORT = 1;
	//Resource Directory
	const static UINTN PE32_DATA_DIRECTORY_RESOURCE = 2;
	//Exception Directory
	const static UINTN PE32_DATA_DIRECTORY_EXCEPTION = 3;
	//Security Directory
	const static UINTN PE32_DATA_DIRECTORY_SECURITY = 4;
	//Base Relocation Table
	const static UINTN PE32_DATA_DIRECTORY_BASERELOC = 5;
	//Debug Directory
	const static UINTN PE32_DATA_DIRECTORY_DEBUG = 6;
	//Architecture Specific Data
	const static UINTN PE32_DATA_DIRECTORY_ARCHITECTURE = 7;
	// RVA of Global Pointer
	const static UINTN PE32_DATA_DIRECTORY_GLOBALPTR = 8;
	// Thread Local Storage Directory
	const static UINTN PE32_DATA_DIRECTORY_TLS = 9;
	// Load Configuration Directory
	const static UINTN PE32_DATA_DIRECTORY_LOAD_CONFIG = 10;
	// Bound Import Directory
	const static UINTN PE32_DATA_DIRECTORY_BOUND_IMPORT = 11;
	// Import Address Table
	const static UINTN PE32_DATA_DIRECTORY_IAT = 12;
	// Delay Import Descriptor
	const static UINTN PE32_DATA_DIRECTORY_DELAY_IMPORT = 13;
	// COM Runtime Descriptor
	const static UINTN PE32_DATA_DIRECTORY_COM_DESCRIPTOR = 14;
	/*Marked Reserved On MSDocs Site*/
	const static UINTN PE32_DATA_DIRECTORY_RESERVED = 15;

#pragma pack(push,1)
	struct PE32DataDirectory
	{
		UINT32 VirtualAddress;
		UINT32 Size;
	};
#pragma pack(pop)
}
