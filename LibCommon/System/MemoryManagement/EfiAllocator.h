#pragma once
#include <TypeDefs.h>
#include <SystemTable.h>
#include <System/MemoryManagement/AllocatorStatus.h>

namespace Common::System::MemoryManagement
{
	class Allocator;

	class EfiAllocator
	{
	public:
		 static Efi::SystemTable* _efiSystemTable;
		 static VOID_PTR Allocate(UINTN length);
		 static VOID_PTR AllocateZeroed(UINTN length);
		 static VOID_PTR AllocatePage(UINTN pageCount);
		 static VOID_PTR AllocatePageZeroed(UINTN pageCount);
		 static VOID Free(VOID_PTR ptr);
		 static VOID FreePage(VOID_PTR ptr, UINTN pageCount);
		 static AllocatorStatus _lastStatus;
	};
}
