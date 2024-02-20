#pragma once
#include <TypeDefs.h>

namespace Commmon::FileTypes
{
	struct  PE_HDR
	{
	public:
		union
		{
			UINT8 Char[4]; // PE\0\0 or 0x00004550
			UINT32 Value; // PE\0\0 or 0x00004550
		} Magic;
		UINT16 Machine;
		UINT16 NumberOfSections;
		UINT32 TimeDateStamp;
		UINT32 PointerToSymbolTable;
		UINT32 NumberOfSymbols;
		UINT16 SizeOfOptionalHeader;
		UINT16 Characteristics;
	};

	struct PE_OPT_HDR
	{
	public:
		union
		{
			UINT8 Char[2];
			UINT16 Value;
		}Magic;// 0x010b - PE32, 0x020b - PE32+ (64 bit)
		UINT8  MajorLinkerVersion;
		UINT8  MinorLinkerVersion;
		UINT32 SizeOfCode;
		UINT32 SizeOfInitializedData;
		UINT32 SizeOfUninitializedData;
		UINT32 AddressOfEntryPoint;
		UINT32 BaseOfCode;
		union
		{
			struct
			{
				UINT32 BaseOfData;
				UINT32 ImageBase;
			};
			UINT64 ImageBase64;
		};
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
		UINT16 DllCharacteristics;
		UINT32 SizeOfStackReserve;
		UINT32 SizeOfStackCommit;
		UINT32 SizeOfHeapReserve;
		UINT32 SizeOfHeapCommit;
		UINT32 LoaderFlags;
		UINT32 NumberOfRvaAndSizes;
	};

	struct PE_IMG_SECTION_HDR
	{ // size 40 bytes
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

	struct PE_ATTR_CERT_TABLE
	{
	public:
		UINT32 DWLength;
		UINT16 WRevision;
		UINT16 WCertificateType;
		VOID_PTR BCertificate;
	};
};

