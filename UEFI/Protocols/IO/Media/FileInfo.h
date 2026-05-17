#pragma once
#include "UEFIDef.h"
#include <Status.h>
#include <Guid.h>
#include <Protocols/Time/Time.h>
#include "FileAttributes.h"
#include <HelperFuncs/StringHelpers.h>

namespace Efi
{
    constinit const ALIGN(8) Efi::Guid FileInfoId { 0x09576e92ui32,0x6d3fui16,0x11d2ui16,0x8e,0x39,0x00,0xa0,0xc9,0x69,0x72,0x3b};

	

    struct FileInfo 
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
		Efi::Time CreateTime;
		/// <summary>
		/// The time when the file was last accessed.
		/// </summary>
		Efi::Time LastAccessTime;
		/// <summary>
		/// The time when the file’s contents were last modified.
		/// </summary>
		Efi::Time ModificationTime;
		/// <summary>
		/// Represents file attributes in the EFI (Extensible Firmware Interface) system.
		/// </summary>
        Efi::FileAttributes Attribute;
		CONST CHAR16* FileName;

        BOOLEAN operator ==(const FileInfo& right)
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

        BOOLEAN operator !=(const FileInfo& right)
		{
			return !(*this == right);
		};
	};
}