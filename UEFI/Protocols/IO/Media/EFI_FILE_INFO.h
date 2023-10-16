#pragma once
#include "UEFIDef.h"
#include "EFI_STATUS.h"
#include "EFI_GUID.h"
#include <Protocols/Time/EFI_TIME.h>
#include "EFI_FILE_ATTRIBUTES.h"

namespace EFI
{
	constinit const EFI::EFI_GUID EFI_FILE_INFO_ID{ 0x09576e92,0x6d3f,0x11d2,{0x8e39,0x00,0xa0,0xc9,0x69,0x72,0x3b} };

	struct EFI_FILE_INFO 
	{
	public:
		UINT64 Size;
		UINT64 FileSize;
		UINT64 PhysicalSize;
		EFI::EFI_TIME CreateTime;
		EFI::EFI_TIME LastAccessTime;
		EFI::EFI_TIME ModificationTime;
		EFI::EFI_FILE_ATTRIBUTES Attribute;
		CHAR16 FileName[];
	};
}

