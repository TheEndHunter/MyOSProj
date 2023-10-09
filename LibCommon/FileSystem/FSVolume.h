#pragma once
#include "TypeDefs.h"
#include "EFI_SYSTEM_TABLE.h"

namespace Common::FileSystem
{
	class FSVolume
	{
	public:
		FSVolume(EFI::EFI_SYSTEM_TABLE* sysTable);
	};
}
