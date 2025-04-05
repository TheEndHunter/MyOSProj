#include <System/MemoryManagement/Allocator.h>
#include <System/MemoryManagement/AllocatorStatus.h>
#include <System/Environment/Unicode.h>

namespace Common::System::MemoryManagement
{
#pragma region Allocator
	BOOLEAN _init = FALSE;
	Allocator* _allocatorInstance;

	Allocator::Allocator(AllocatorStatus* allocStatus, AllocFunc allocFunc, AllocZeroedFunc allocZeroedFunc, AllocPageFunc allocPageFunc, AllocPageZeroedFunc allocPageZeroedFunc, FreeFunc freeFunc, FreePageFunc freePageFunc)
	{
		_lastStatus = allocStatus;
		_allocFunc = allocFunc;
		_allocZeroedFunc = allocZeroedFunc;
		_allocPageFunc = allocPageFunc;
		_allocPageZeroedFunc = allocPageZeroedFunc;
		_freeFunc = freeFunc;
		_freePageFunc = freePageFunc;
	}

	Debugging::Debugger* _debug;
	void Allocator::SetDebugger(Debugging::Debugger* debugger)
	{
		_debug = debugger;
	}

	Allocator::Allocator()
	{
	}

	Allocator* Allocator::GetInstance()
	{
		if (_init == FALSE)
		{
			return nullptr;
		}
		return _allocatorInstance;
	}

	AllocatorStatus Allocator::SetWithExistingAllocator(Allocator* allocator)
	{
		if (allocator == nullptr)
		{
			if (!_allocatorInstance->IsInitalized())
			{
				return AllocatorStatus::Invalid_Parameters;
			}
			else
			{
				return AllocatorStatus::Not_Initialized;
			}
		}

		_allocatorInstance = allocator;
		_init = TRUE;

		*_allocatorInstance->_lastStatus = AllocatorStatus::Success;
		return *_allocatorInstance->_lastStatus;
	}

	VOID_PTR Allocator::Allocate(UINTN length)
	{
		if (!_initialized)
		{
			return nullptr;
		}

		if (_debug != nullptr)
		{
			_debug->PrintInfo(u"Allocating: ");
			_debug->PrintInfo(Common::System::Environment::UTF<CHAR16>::ToString(length));
			_debug->PrintInfoLine(u" bytes");
		}

		VOID_PTR p = _allocFunc(length);
		return p;
	}
	VOID_PTR Allocator::AllocateZeroed(UINTN length)
	{
		if (!_initialized)
		{
			*_lastStatus = AllocatorStatus::Not_Initialized;
			return nullptr;
		}
		if (_debug != nullptr)
		{
			_debug->PrintInfo(u"Allocating Zeroed: ");
			_debug->PrintInfo(Common::System::Environment::UTF<CHAR16>::ToString(length));
			_debug->PrintInfoLine(u" bytes");
		}
		VOID_PTR p = _allocZeroedFunc(length);
		
		return p;
	}
	VOID Allocator::Free(VOID_PTR ptr)
	{
		if (!_initialized)
		{
			*_lastStatus = AllocatorStatus::Not_Initialized;
			return;
		}

		if (_debug != nullptr)
		{
			_debug->PrintInfo(u"Freeing Address: ");
			_debug->PrintInfoLine(Common::System::Environment::UTF<CHAR16>::ToHex(ptr));
		}

		_freeFunc(ptr);
		
	}
	VOID_PTR Allocator::AllocatePage(UINTN pageCount)
	{
		if (!_initialized)
		{
			*_lastStatus = AllocatorStatus::Not_Initialized;
			return nullptr;
		}

		if (_debug != nullptr)
		{
			_debug->PrintInfo(u"Allocating: ");
			_debug->PrintInfo(Common::System::Environment::UTF<CHAR16>::ToString(pageCount));
			_debug->PrintInfoLine(u" pages");
		}

		VOID_PTR p = _allocPageFunc(pageCount);
		
		return p;
	}

	VOID_PTR Allocator::AllocatePageZeroed(UINTN pageCount)
	{
		if (!_initialized)
		{
			*_lastStatus = AllocatorStatus::Not_Initialized;
			return nullptr;
		}

		if (_debug != nullptr)
		{
			_debug->PrintInfo(u"Allocating Zeroed: ");
			_debug->PrintInfo(Common::System::Environment::UTF<CHAR16>::ToString(pageCount));
			_debug->PrintInfoLine(u" pages");
		}

		VOID_PTR p = _allocPageZeroedFunc(pageCount);
		
		return p;
	}

	VOID Allocator::FreePage(VOID_PTR ptr, UINTN pageCount)
	{
		if (!_initialized)
		{
			*_lastStatus = AllocatorStatus::Not_Initialized;
			return;
		}

		if (_debug != nullptr)
		{
			_debug->PrintInfo(u"Freeing Pages From Address: ");
			_debug->PrintInfo(Common::System::Environment::UTF<CHAR16>::ToHex(ptr));
			_debug->PrintInfo(u" Page Count: ");
			_debug->PrintInfoLine(Common::System::Environment::UTF<CHAR16>::ToString(pageCount));

		}

		_freePageFunc(ptr, pageCount);
		
	}

	BOOLEAN Allocator::IsInitalized()
	{
		return _initialized;
	}

	AllocatorStatus Allocator::LastStatus()
	{
		return *_lastStatus;
	}

	AllocatorStatus Allocator::SetEfiAllocator(EFI::EFI_SYSTEM_TABLE* systemTable)
	{
		if (_init)
		{
				*_allocatorInstance->_lastStatus = AllocatorStatus::Success;
				return *_allocatorInstance->_lastStatus;
		}

		EfiAllocator::_efiSystemTable = systemTable;

		_allocatorInstance  = (Allocator*)EfiAllocator::Allocate(sizeof(Allocator));
		_allocatorInstance = new(_allocatorInstance) Allocator(&EfiAllocator::_lastStatus, EfiAllocator::Allocate, EfiAllocator::AllocateZeroed, EfiAllocator::AllocatePage, EfiAllocator::AllocatePageZeroed, EfiAllocator::Free, EfiAllocator::FreePage);

		*_allocatorInstance->_lastStatus = AllocatorStatus::Success;
		_init = TRUE;
		return *_allocatorInstance->_lastStatus;
	}


	AllocatorStatus Allocator::SetKernelAllocator(EFI::EFI_SYSTEM_TABLE* systemTable)
	{
		return AllocatorStatus::Unknown;
	}

#pragma endregion
}

extern VOID_PTR operator new(UINTN length)
{
	auto* allocator = Common::System::MemoryManagement::Allocator::GetInstance();
	if (allocator == nullptr)
	{
		return nullptr;
	}
	if (!allocator->IsInitalized())
	{
		return nullptr;
	}
	return allocator->Allocate(length);
}

extern VOID_PTR operator new[](UINTN length)
{
	auto* allocator = Common::System::MemoryManagement::Allocator::GetInstance();
	if (allocator == nullptr)
	{
		return nullptr;
	}
	if (!allocator->IsInitalized())
	{
		return nullptr;
	}
	return allocator->Allocate(length);
}

extern VOID_PTR operator new(UINTN length, VOID_PTR ptr)
{
	return ptr;
}

extern VOID_PTR operator new[](UINTN length, VOID_PTR ptr)
{
	return ptr;
}

extern void operator delete(VOID_PTR ptr)
{
	auto* allocator = Common::System::MemoryManagement::Allocator::GetInstance();
	if (allocator == nullptr)
	{
		return;
	}
	if (!allocator->IsInitalized())
	{
		return;
	}
	return allocator->Free(ptr);
}

extern void operator delete[](VOID_PTR ptr)
{
	auto* allocator = Common::System::MemoryManagement::Allocator::GetInstance();
	if (allocator == nullptr)
	{
		return;
	}
	if (!allocator->IsInitalized())
	{
		return;
	}
	return allocator->Free(ptr);
}

extern void operator delete(VOID_PTR ptr, UINTN length)
{
	auto* allocator = Common::System::MemoryManagement::Allocator::GetInstance();
	if (allocator == nullptr)
	{
		return;
	}
	if (!allocator->IsInitalized())
	{
		return;
	}
	return allocator->Free(ptr);
}

extern void operator delete[](VOID_PTR ptr, UINTN length)
{
	auto* allocator = Common::System::MemoryManagement::Allocator::GetInstance();
	if (allocator == nullptr)
	{
		return;
	}
	if (!allocator->IsInitalized())
	{
		return;
	}
	return allocator->Free(ptr);
}

extern void operator delete(VOID_PTR ptr, VOID_PTR place)
{
	auto* allocator = Common::System::MemoryManagement::Allocator::GetInstance();
	if (allocator == nullptr)
	{
		return;
	}
	if (!allocator->IsInitalized())
	{
		return;
	}
	return allocator->Free(ptr);
}

extern void operator delete[](VOID_PTR ptr, VOID_PTR place)
{
	auto* allocator = Common::System::MemoryManagement::Allocator::GetInstance();
	if (allocator == nullptr)
	{
		return;
	}
	if (!allocator->IsInitalized())
	{
		return;
	}
	return allocator->Free(ptr);
}

