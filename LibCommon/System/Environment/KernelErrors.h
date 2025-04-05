#pragma once
#include <TypeDefs.h>

namespace Common::System::Environment
{
	enum class KernelError : UINT64
	{
		Success = 0x0000000000000000,
		AllocatorNotSet = 0x8000000000000001,
		AllocatorNotMatched = 0x8000000000000002,
		AllocatorNotInitialized = 0x8000000000000003,
		VolumeOpenFailed = 0x8000000000000004,
		FontPtrNull = 0x8000000000000005,
		FontInvalid = 0x8000000000000006,
	};
}