#pragma once
#include <TypeDefs.h>
#include <EFI_SYSTEM_TABLE.h>
#include <EFI_STATUS.h>
#include "VolumeInfo.h"

namespace Common::FileSystem
{
	struct VolumeHandle
	{
	protected:
		VolumeHandle(VolumeInfo& i, void* b) : Info(i), Size(i.Size), Buffer(b) {};
	public:
		constexpr VolumeHandle() : Size(0), Buffer(nullptr) {};

		static VolumeHandle Create(VolumeInfo& i, void* b);

		VolumeInfo Info;
		UINT64 Size;
		void* Buffer;

		bool operator ==(const VolumeHandle& right);
		bool operator !=(const VolumeHandle& right);
	};

	constinit const VolumeHandle Empty_VolHandle = VolumeHandle();
}
