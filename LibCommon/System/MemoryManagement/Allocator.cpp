#include <System/MemoryManagement/Allocator.h>
#include <System/MemoryManagement/AllocatorStatus.h>

namespace Common::System::MemoryManagement
{
#pragma region Allocator
	BOOLEAN _isInitalized;

	AllocatorStatus _defaultStatus = AllocatorStatus::Not_Initialized;
	AllocatorStatus* Allocator::_lastStatus = &_defaultStatus;

	// Definitions for the function pointers in Allocator
	VOID_PTR (*Allocator::_allocFunc)(UINT64) = nullptr;
	VOID_PTR (*Allocator::_allocZeroedFunc)(UINT64) = nullptr;
	VOID_PTR (*Allocator::_allocPageFunc)(UINT64) = nullptr;
	VOID_PTR (*Allocator::_allocPageZeroedFunc)(UINT64) = nullptr;
	void  (*Allocator::_freeFunc)(VOID_PTR) = nullptr;
	void  (*Allocator::_freePageFunc)(VOID_PTR, UINT64) = nullptr;

	VOID_PTR Allocator::Allocate(UINTN size)
	{
		if (!_isInitalized)
		{
			return nullptr;
		}

		VOID_PTR p = _allocFunc(size);
		return p;
	}
	VOID_PTR Allocator::AllocateZeroed(UINTN size)
	{
		if (!_isInitalized)
		{
			*_lastStatus = AllocatorStatus::Not_Initialized;
			return nullptr;
		}

		VOID_PTR p = _allocZeroedFunc(size);
		
		return p;
	}
	VOID Allocator::Free(VOID_PTR ptr)
	{
		if (!_isInitalized)
		{
			*_lastStatus = AllocatorStatus::Not_Initialized;
			return;
		}
		_freeFunc(ptr);
		
	}
	VOID_PTR Allocator::AllocatePage(UINTN pageCount)
	{
		if (!_isInitalized)
		{
			*_lastStatus = AllocatorStatus::Not_Initialized;
			return nullptr;
		}
		VOID_PTR p = _allocPageFunc(pageCount);
		
		return p;
	}

	VOID_PTR Allocator::AllocatePageZeroed(UINTN pageCount)
	{
		if (!_isInitalized)
		{
			*_lastStatus = AllocatorStatus::Not_Initialized;
			return nullptr;
		}
		VOID_PTR p = _allocPageZeroedFunc(pageCount);
		
		return p;
	}

	VOID Allocator::FreePage(VOID_PTR ptr, UINTN pageCount)
	{
		if (!_isInitalized)
		{
			*_lastStatus = AllocatorStatus::Not_Initialized;
			return;
		}
		_freePageFunc(ptr, pageCount);
		
	}

	BOOLEAN Allocator::IsInitalized()
	{
		return _isInitalized;
	}

	AllocatorStatus Allocator::LastStatus()
	{
		return *_lastStatus;
	}

	AllocatorStatus Allocator::SetEfiAllocator(EFI::EFI_SYSTEM_TABLE* systemTable)
	{
		if(_isInitalized)
		{
			*_lastStatus = AllocatorStatus::Success;
			return *_lastStatus;
		}
		EfiAllocator::_efiSystemTable = systemTable;

		_lastStatus = &EfiAllocator::_lastStatus;
		_allocFunc = EfiAllocator::Allocate;
		_allocZeroedFunc = EfiAllocator::AllocateZeroed;
		_allocPageFunc = EfiAllocator::AllocatePage;
		_allocPageZeroedFunc = EfiAllocator::AllocatePageZeroed;
		_freeFunc = EfiAllocator::Free;
		_freePageFunc = EfiAllocator::FreePage;

		*_lastStatus = AllocatorStatus::Success;
		_isInitalized = TRUE;
		return *_lastStatus;
	}


	AllocatorStatus Allocator::SetKernelAllocator(EFI::EFI_SYSTEM_TABLE* systemTable)
	{
		return AllocatorStatus::Unknown;
	}

#pragma endregion


}

VOID_PTR operator new(UINTN size)
{
	if (!Common::System::MemoryManagement::Allocator::IsInitalized())
	{
		return nullptr;
	}
	return Common::System::MemoryManagement::Allocator::Allocate(size);
}

VOID_PTR operator new[](UINTN size)
{
	if (!Common::System::MemoryManagement::Allocator::IsInitalized())
	{
		return nullptr;
	}
	return Common::System::MemoryManagement::Allocator::Allocate(size);
}

VOID_PTR operator new(UINTN size, VOID_PTR ptr)
{
	return ptr;
}

VOID_PTR operator new[](UINTN size, VOID_PTR ptr)
{
	return ptr;
}

void operator delete(VOID_PTR ptr)
{
	if (!Common::System::MemoryManagement::Allocator::IsInitalized())
	{
		return;
	}

	Common::System::MemoryManagement::Allocator::Free(ptr);
}

void operator delete[](VOID_PTR ptr)
{
	if (!Common::System::MemoryManagement::Allocator::IsInitalized())
	{
		return;
	}
	Common::System::MemoryManagement::Allocator::Free(ptr);
}

void operator delete(VOID_PTR ptr, UINTN size)
{
	if (!Common::System::MemoryManagement::Allocator::IsInitalized())
	{
		return;
	}
	Common::System::MemoryManagement::Allocator::Free(ptr);
}

void operator delete[](VOID_PTR ptr, UINTN size)
{
	if (!Common::System::MemoryManagement::Allocator::IsInitalized())
	{
		return;
	}
	Common::System::MemoryManagement::Allocator::Free(ptr);
}

void operator delete(VOID_PTR ptr, VOID_PTR place)
{
	if (!Common::System::MemoryManagement::Allocator::IsInitalized())
	{
		return;
	}
	Common::System::MemoryManagement::Allocator::Free(ptr);
}

void operator delete[](VOID_PTR ptr, VOID_PTR place)
{
	if (!Common::System::MemoryManagement::Allocator::IsInitalized())
	{
		return;
	}
	Common::System::MemoryManagement::Allocator::Free(ptr);
}

