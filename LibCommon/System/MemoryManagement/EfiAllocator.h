#pragma once
#include <TypeDefs.h>
#include <EFI_SYSTEM_TABLE.h>
#include <System/MemoryManagement/AllocatorStatus.h>

namespace Common::System::MemoryManagement
{
	class Allocator;

	class EfiAllocator
	{
	public:
		 static EFI::EFI_SYSTEM_TABLE* _efiSystemTable;
		 static VOID_PTR Allocate(UINTN size);
		 static VOID_PTR AllocateZeroed(UINTN size);
		 static VOID_PTR AllocatePage(UINTN pageCount);
		 static VOID_PTR AllocatePageZeroed(UINTN pageCount);
		 static VOID Free(VOID_PTR ptr);
		 static VOID FreePage(VOID_PTR ptr, UINTN pageCount);
		 static AllocatorStatus _lastStatus;
	};
}
