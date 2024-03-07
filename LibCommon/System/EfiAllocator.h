#pragma once
#include <TypeDefs.h>
#include <EFI_SYSTEM_TABLE.h>
#include <System/AllocatorStatus.h>
#include <System/Allocator.h>

namespace Common::System
{
	class EFIAllocator
	{
	public:
		static VOID SetEFIAllocator(EFI::EFI_SYSTEM_TABLE* systemTable);
	};
}
