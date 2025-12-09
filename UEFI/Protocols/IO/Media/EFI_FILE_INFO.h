#pragma once
#include "UEFIDef.h"
#include "EFI_STATUS.h"
#include "EFI_GUID.h"
#include <Protocols/Time/EFI_TIME.h>
#include "EFI_FILE_ATTRIBUTES.h"
#include <Helper Funcs/StringHelpers.h>

namespace EFI
{
	constinit const ALIGN(8) EFI::EFI_GUID EFI_FILE_INFO_ID { 0x09576e92ui32,0x6d3fui16,0x11d2ui16,0x8e,0x39,0x00,0xa0,0xc9,0x69,0x72,0x3b};

	

	struct EFI_FILE_INFO 
	{
	public:
		/// <summary>
		/// Size of the EFI_FILE_INFO structure, including the Null-terminated FileName string.
		/// </summary>
		UINT64 Size;
		/// <summary>
		/// The size of the file in bytes.
		/// </summary>
		UINT64 FileSize;
		/// <summary>
		/// The amount of physical space the file consumes on the file system volume.
		/// </summary>
		UINT64 PhysicalSize;
		/// <summary>
		/// The time the file was created.
		/// </summary>
		EFI::EFI_TIME CreateTime;
		/// <summary>
		/// The time when the file was last accessed.
		/// </summary>
		EFI::EFI_TIME LastAccessTime;
		/// <summary>
		/// The time when the file’s contents were last modified.
		/// </summary>
		EFI::EFI_TIME ModificationTime;
		/// <summary>
		/// Represents file attributes in the EFI (Extensible Firmware Interface) system.
		/// </summary>
		EFI::EFI_FILE_ATTRIBUTES Attribute;
		CONST CHAR16* FileName;

		BOOLEAN operator ==(const EFI_FILE_INFO& right)
		{
			/*Compare all members for equality, if one fails return FALSE, otherwise return TRUE*/

			if (Size != right.Size)
				return FALSE;

			if (FileSize != right.FileSize)
				return FALSE;

			if (PhysicalSize != right.PhysicalSize)
				return FALSE;

			if (CreateTime != right.CreateTime)
				return FALSE;

			if (LastAccessTime != right.LastAccessTime)
				return FALSE;

			if (ModificationTime != right.ModificationTime)
				return FALSE;

			if (Attribute != right.Attribute)
				return FALSE;

			if(CompareStrings(FileName, right.FileName) == FALSE)
				return FALSE;

			return TRUE;
		};

		BOOLEAN operator !=(const EFI_FILE_INFO& right)
		{
			return !(*this == right);
		};
	};
}