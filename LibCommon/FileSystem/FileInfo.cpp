
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
}
