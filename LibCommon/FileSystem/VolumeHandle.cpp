#include "FileHandle.h"
#include "VolumeHandle.h"

namespace Common::FileSystem
{
    VolumeHandle Common::FileSystem::VolumeHandle::Create(VolumeInfo& i, void* b)
	{
		return VolumeHandle(i, b);
	}
	bool VolumeHandle::operator==(const VolumeHandle& right)
	{
		/*Compare all members for equality, if one fails return false, otherwise return true*/
		if (Info != right.Info)
			return false;

		if (Size != right.Size)
			return false;

		if (Buffer != right.Buffer)
			return false;


		return true;
	}
	bool VolumeHandle::operator!=(const VolumeHandle& right)
	{
		return !(*this == right);
	};

}
