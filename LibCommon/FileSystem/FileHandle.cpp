#include "FileHandle.h"

namespace Common::FileSystem
{
	FileHandle FileHandle::Create(EFI::EFI_FILE_PROTOCOL* file, FileInfo& i)
	{
		return FileHandle(file, i);
	}
	bool FileHandle::operator==(const FileHandle& right)
	{
		/*Compare all members for equality, if one fails return false, otherwise return true*/
		if (Info != right.Info)
			return false;

		if (Size != right.Size)
			return false;

		if (_File != right._File)
			return false;

		return true;
	}
	bool FileHandle::operator!=(const FileHandle& right)
	{
		return !(*this == right);
	};
}
