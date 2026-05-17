
#include "FileInfo.h"
#include <System/Environment/Unicode.h>

namespace Common::FileSystem
{
    FileInfo::FileInfo(Efi::FileInfo* info)
		: Size(info->Size), FileSize(info->FileSize), PhysicalSize(info->PhysicalSize),
		CreateTime(info->CreateTime), LastAccessTime(info->LastAccessTime),
		ModificationTime(info->ModificationTime), Attribute(info->Attribute), FileName(info->FileName)
	{
	}

    FileInfo FileInfo::Create(Efi::FileInfo* info)
	{
		if (info == nullptr)
			return Empty_FileInfo;

		return FileInfo(info);
	}
}
