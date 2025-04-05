
#include "FileInfo.h"
#include <System/Environment/Unicode.h>

namespace Common::FileSystem
{
	FileInfo::FileInfo(EFI::EFI_FILE_INFO* info)
		: Size(info->Size), FileSize(info->FileSize), PhysicalSize(info->PhysicalSize),
		CreateTime(info->CreateTime), LastAccessTime(info->LastAccessTime),
		ModificationTime(info->ModificationTime), Attribute(info->Attribute), FileName(info->FileName)
	{
	}

	FileInfo FileInfo::Create(EFI::EFI_FILE_INFO* info)
	{
		if (info == nullptr)
			return Empty_FileInfo;

		return FileInfo(info);
	}
	BOOLEAN FileInfo::operator==(const FileInfo& right)
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

		if (System::Environment::UTF<CHAR16>::Compare(FileName,right.FileName) == FALSE)
			return false;

		return true;
	}
	BOOLEAN FileInfo::operator!=(const FileInfo& right)
	{
		return !(*this == right);
	}
}
