#include <System/Allocator.h>

namespace Common::System
{
	typedef VOID_PTR AllocFunc(UINTN size);
	typedef VOID_PTR AllocZeroedFunc(UINTN size);
	typedef VOID_PTR AllocPageFunc(UINTN size);
	typedef VOID_PTR AllocPageZeroedFunc(UINTN size);

	typedef VOID FreeFunc(VOID_PTR ptr);
	typedef VOID FreePageFunc(VOID* ptr, UINTN size);

	typedef AllocatorStatus GetStatusFunc();
	typedef VOID SetStatusFunc(AllocatorStatus status);

	AllocFunc* _allocFunc;
	AllocZeroedFunc* _allocZeroedFunc;
	AllocPageFunc* _allocPageFunc;
	AllocPageZeroedFunc* _allocPageZeroedFunc;
	FreeFunc* _freeFunc;
	FreePageFunc* _freePageFunc;
	EFI::EFI_SYSTEM_TABLE* _efiSystemTable;

#pragma region Allocator
	BOOLEAN _isInitalized;

	AllocatorStatus Allocator::_lastStatus = AllocatorStatus::Not_Initialized;

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
			_lastStatus = AllocatorStatus::Not_Initialized;
			return nullptr;
		}

		VOID_PTR p = _allocZeroedFunc(size);
		
		return p;
	}
	VOID Allocator::Free(VOID_PTR ptr)
	{
		if (!_isInitalized)
		{
			_lastStatus = AllocatorStatus::Not_Initialized;
			return;
		}
		_freeFunc(ptr);
		
	}
	VOID_PTR Allocator::AllocatePage(UINTN pageCount)
	{
		if (!_isInitalized)
		{
			_lastStatus = AllocatorStatus::Not_Initialized;
			return nullptr;
		}
		void* p = _allocPageFunc(pageCount);
		
		return p;
	}

	VOID_PTR Allocator::AllocatePageZeroed(UINTN pageCount)
	{
		if (!_isInitalized)
		{
			_lastStatus = AllocatorStatus::Not_Initialized;
			return nullptr;
		}
		void* p = _allocPageZeroedFunc(pageCount);
		
		return p;
	}

	VOID Allocator::FreePage(VOID_PTR ptr, UINTN pageCount)
	{
		if (!_isInitalized)
		{
			_lastStatus = AllocatorStatus::Not_Initialized;
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
		return _lastStatus;
	}

	AllocatorStatus Allocator::SetEfiAllocator(EFI::EFI_SYSTEM_TABLE* systemTable)
	{
		if(_isInitalized)
		{
			_lastStatus = AllocatorStatus::Success;
			return _lastStatus;
		}

		_efiSystemTable = systemTable;

		_allocFunc = EfiAllocator::Allocate;
		_allocZeroedFunc = EfiAllocator::AllocateZeroed;
		_allocPageFunc = EfiAllocator::AllocatePage;
		_allocPageZeroedFunc = EfiAllocator::AllocatePageZeroed;
		_freeFunc = EfiAllocator::Free;
		_freePageFunc = EfiAllocator::FreePage;

		_lastStatus = AllocatorStatus::Success;
		_isInitalized = TRUE;
		return _lastStatus;
	}

#pragma endregion

#pragma region EfiAllocator

	
	VOID_PTR EfiAllocator::Allocate(UINTN size)
	{
		if (_efiSystemTable == nullptr)
		{
			return nullptr;
		}

		EFI::EFI_STATUS status;
		VOID* buffer;
		status = _efiSystemTable->BootServices->AllocatePool(EFI::EFI_MEMORY_TYPE::LoaderData, size, &buffer);
		if (status != EFI::EFI_STATUS::SUCCESS)
		{
			switch (status)
			{
			case EFI::EFI_STATUS::OUT_OF_RESOURCES:
				Allocator::_lastStatus = AllocatorStatus::Not_Enough_Memory;
				break;
			case EFI::EFI_STATUS::INVALID_PARAMETER:
				Allocator::_lastStatus = AllocatorStatus::Invalid_Parameters;
				break;
			}
			return nullptr;
		}

		Allocator::_lastStatus = AllocatorStatus::Success;
		return buffer;
	}
	VOID_PTR EfiAllocator::AllocateZeroed(UINTN size)
	{
		if (_efiSystemTable == nullptr)
		{
			return nullptr;
		}

		EFI::EFI_STATUS status;
		VOID* buffer;
		status = _efiSystemTable->BootServices->AllocatePool(EFI::EFI_MEMORY_TYPE::LoaderData, size, &buffer);
		if (status != EFI::EFI_STATUS::SUCCESS)
		{
			switch (status)
			{
			case EFI::EFI_STATUS::OUT_OF_RESOURCES:
				Allocator::_lastStatus = AllocatorStatus::Not_Enough_Memory;
				break;
			case EFI::EFI_STATUS::INVALID_PARAMETER:
				Allocator::_lastStatus = AllocatorStatus::Invalid_Parameters;
				break;
			}
			return nullptr;
		}

		status = _efiSystemTable->BootServices->SetMem(buffer, size, 0);

		Allocator::_lastStatus = AllocatorStatus::Success;
		return buffer;
	}
	VOID_PTR EfiAllocator::AllocatePage(UINTN pageCount)
	{
		if (_efiSystemTable == nullptr)
		{
			return nullptr;
		}

		EFI::EFI_STATUS status;
		VOID* buffer;
		status = _efiSystemTable->BootServices->AllocatePages(EFI::EFI_ALLOCATE_TYPE::AllocateAnyPages, EFI::EFI_MEMORY_TYPE::LoaderData, pageCount, &buffer);
		if (status != EFI::EFI_STATUS::SUCCESS)
		{
			switch (status)
			{
			case EFI::EFI_STATUS::OUT_OF_RESOURCES:
				Allocator::_lastStatus = AllocatorStatus::Not_Enough_Memory;
				break;
			case EFI::EFI_STATUS::INVALID_PARAMETER:
				Allocator::_lastStatus = AllocatorStatus::Invalid_Parameters;
				break;
			}
			return nullptr;
		}

		Allocator::_lastStatus = AllocatorStatus::Success;
		return buffer;
	}
	VOID_PTR EfiAllocator::AllocatePageZeroed(UINTN pageCount)
	{
		if (_efiSystemTable == nullptr)
		{
			return nullptr;
		}

		EFI::EFI_STATUS status;
		VOID* buffer;
		status = _efiSystemTable->BootServices->AllocatePages(EFI::EFI_ALLOCATE_TYPE::AllocateAnyPages, EFI::EFI_MEMORY_TYPE::LoaderData, pageCount, &buffer);
		if (status != EFI::EFI_STATUS::SUCCESS)
		{
			switch (status)
			{
			case EFI::EFI_STATUS::OUT_OF_RESOURCES:
				Allocator::_lastStatus = AllocatorStatus::Not_Enough_Memory;
				break;
			case EFI::EFI_STATUS::INVALID_PARAMETER:
				Allocator::_lastStatus = AllocatorStatus::Invalid_Parameters;
				break;
			}
			return nullptr;
		}

		status = _efiSystemTable->BootServices->SetMem(buffer, (pageCount * 4096), 0);

		Allocator::_lastStatus = AllocatorStatus::Success;
		return buffer;
	}
	VOID EfiAllocator::Free(VOID_PTR ptr)
	{
		if (_efiSystemTable == nullptr)
		{
			return;
		}
		_efiSystemTable->BootServices->FreePool(ptr);
	}
	VOID EfiAllocator::FreePage(VOID_PTR ptr, UINTN pageCount)
	{
		if (_efiSystemTable == nullptr)
		{
			return;
		}
		_efiSystemTable->BootServices->FreePages(ptr, pageCount);
	}
#pragma endregion
}

VOID_PTR operator new(UINTN size)
{
	if (!Common::System::Allocator::IsInitalized())
	{
		return nullptr;
	}
	return Common::System::Allocator::Allocate(size);
}

VOID_PTR operator new[](UINTN size)
{
	if (!Common::System::Allocator::IsInitalized())
	{
		return nullptr;
	}
	return Common::System::Allocator::Allocate(size);
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
	if (!Common::System::Allocator::IsInitalized())
	{
		return;
	}

	Common::System::Allocator::Free(ptr);
}

void operator delete[](VOID_PTR ptr)
{
	if (!Common::System::Allocator::IsInitalized())
	{
		return;
	}
	Common::System::Allocator::Free(ptr);
}

void operator delete(VOID_PTR ptr, UINTN size)
{
	if (!Common::System::Allocator::IsInitalized())
	{
		return;
	}
	Common::System::Allocator::Free(ptr);
}

void operator delete[](VOID_PTR ptr, UINTN size)
{
	if (!Common::System::Allocator::IsInitalized())
	{
		return;
	}
	Common::System::Allocator::Free(ptr);
}

void operator delete(VOID_PTR ptr, VOID_PTR place)
{
	if (!Common::System::Allocator::IsInitalized())
	{
		return;
	}
	Common::System::Allocator::Free(ptr);
}

void operator delete[](VOID_PTR ptr, VOID_PTR place)
{
	if (!Common::System::Allocator::IsInitalized())
	{
		return;
	}
	Common::System::Allocator::Free(ptr);
}

