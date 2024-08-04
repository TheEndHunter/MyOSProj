
#include "DirectoryInfo.h"
#include <System/Environment/Unicode.h>

namespace Common::FileSystem
{
	DirectoryInfo::DirectoryInfo(EFI::EFI_FILE_INFO* info)
		: Size(info->Size), FileSize(info->FileSize), PhysicalSize(info->PhysicalSize),
		CreateTime(info->CreateTime), LastAccessTime(info->LastAccessTime),
		ModificationTime(info->ModificationTime), Attribute(info->Attribute), DirectoryName(info->FileName)
	{
	}

	DirectoryInfo DirectoryInfo::Create(EFI::EFI_FILE_INFO* info)
	{
		if (info == nullptr)
			return Empty_DirectoryInfo;

		return DirectoryInfo(info);
	}
	bool DirectoryInfo::operator==(const DirectoryInfo& right)
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

		if (System::Environment::UTF16::Compare(DirectoryName,right.DirectoryName) == FALSE)
			return false;

		return true;
	}
	bool DirectoryInfo::operator!=(const DirectoryInfo& right)
	{
		return !(*this == right);
	}
}
