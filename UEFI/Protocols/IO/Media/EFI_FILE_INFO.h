#pragma once
#include "UEFIDef.h"
#include "EFI_STATUS.h"
#include "EFI_GUID.h"
#include <Protocols/Time/EFI_TIME.h>
#include "EFI_FILE_ATTRIBUTES.h"

namespace EFI
{
	constinit const ALIGN(8) EFI::EFI_GUID EFI_FILE_INFO_ID { 0x09576e92ui32,0x6d3fui16,0x11d2ui16,0x8e,0x39,0x00,0xa0,0xc9,0x69,0x72,0x3b};

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
		CHAR16* FileName;

		bool operator ==(const EFI_FILE_INFO& right)
		{
			/*Compare all members for equality, if one fails return false, otherwise return true*/

			if (Size != right.Size)
				return false;

			if (FileSize != right.FileSize)
				return false;

			if (PhysicalSize != right.PhysicalSize)
				return false;

			if (CreateTime != right.CreateTime)
				return false;

			if (LastAccessTime != right.LastAccessTime)
				return false;

			if (ModificationTime != right.ModificationTime)
				return false;

			if (Attribute != right.Attribute)
				return false;

			if (FileName != right.FileName)
				return false;

			return true;
		};

		bool operator !=(const EFI_FILE_INFO& right)
		{
			return !(*this == right);
		};
	};
}

