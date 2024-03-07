#include <System/Allocator.h>

namespace Common::System
{
	AllocFunc* _allocFunc;
	AllocZeroedFunc* _allocZeroedFunc;
	AllocPageFunc* _allocPageFunc;
	AllocPageZeroedFunc* _allocPageZeroedFunc;
	FreeFunc* _freeFunc;
	FreePageFunc* _freePageFunc;
	GetStatusFunc* _getStatusFunc;
	SetStatusFunc* _setStatusFunc;


	BOOLEAN _isInitalized;
	AllocatorStatus _lastStatus;

	VOID_PTR Allocator::Allocate(UINTN size)
	{
		if (!_isInitalized)
		{
			_lastStatus = AllocatorStatus::Not_Initialized;
			return nullptr;
		}

		VOID_PTR p = _allocFunc(size);
		_lastStatus = _getStatusFunc();
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
		_lastStatus = _getStatusFunc();
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
		_lastStatus = _getStatusFunc();
	}
	VOID_PTR Allocator::AllocatePage(UINTN pageCount)
	{
		if (!_isInitalized)
		{
			_lastStatus = AllocatorStatus::Not_Initialized;
			return nullptr;
		}
		void* p = _allocPageFunc(pageCount);
		_lastStatus = _getStatusFunc();
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
		_lastStatus = _getStatusFunc();
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
		_lastStatus = _getStatusFunc();
	}

	void Allocator::SetAllocators(AllocFunc& allocFunc,AllocZeroedFunc& allocZeroFunc, AllocPageFunc& allocPageFunc, AllocPageZeroedFunc& allocPageZeroFunc, FreeFunc& freeFunc, FreePageFunc& freePageFunc, GetStatusFunc& getStatusFunc, SetStatusFunc& setStatusFunc)
	{
		/*if any or all of the function pointers are zero, return nullptr*/
		if (setStatusFunc == nullptr)
		{
			_isInitalized = FALSE;
			_lastStatus = AllocatorStatus::Invalid_Parameters;
			return;
		};

		_lastStatus = AllocatorStatus::Success;

		if (allocFunc == nullptr)
		{
			_isInitalized = FALSE;
			setStatusFunc(AllocatorStatus::Invalid_Parameters);
			return;
		}
		if (allocZeroFunc == nullptr)
		{
			_isInitalized = FALSE;
			setStatusFunc(AllocatorStatus::Invalid_Parameters);
			return;
		}
		if (allocPageFunc == nullptr)
		{
			_isInitalized = FALSE;
			setStatusFunc(AllocatorStatus::Invalid_Parameters);
			return;
		}
		if (allocPageZeroFunc == nullptr)
		{
			_isInitalized = FALSE;
			setStatusFunc(AllocatorStatus::Invalid_Parameters);
			return;
		}
		if (freeFunc == nullptr)
		{
			_isInitalized = FALSE;
			setStatusFunc(AllocatorStatus::Invalid_Parameters);
			return;
		}
		if (freePageFunc == nullptr)
		{
			_isInitalized = FALSE;
			setStatusFunc(AllocatorStatus::Invalid_Parameters);
			return;
		}
		if (getStatusFunc == nullptr)
		{
			_isInitalized = FALSE;
			setStatusFunc(AllocatorStatus::Invalid_Parameters);
			return;
		}


		_allocFunc = allocFunc;
		_allocZeroedFunc = allocZeroFunc;
		_allocPageFunc = allocPageFunc;
		_allocPageZeroedFunc = allocPageZeroFunc;
		_freeFunc = freeFunc;
		_freePageFunc = freePageFunc;
		_getStatusFunc = getStatusFunc;

		_isInitalized = TRUE;
	}

	BOOLEAN Allocator::IsInitalized()
	{
		return _isInitalized;
	}

	AllocatorStatus Allocator::LastStatus()
	{
		if (!_isInitalized)
			return _lastStatus;
		
		if(_lastStatus != AllocatorStatus::Success)
			return _lastStatus;


		return _getStatusFunc();
	}

}

VOID_PTR __cdecl operator new(UINTN size)
{
	return Common::System::Allocator::Allocate(size);
}

VOID_PTR __cdecl operator new[](UINTN size)
{
	return Common::System::Allocator::Allocate(size);
}

VOID __cdecl operator delete(VOID_PTR ptr)
{
	return Common::System::Allocator::Free(ptr);
}

VOID __cdecl operator delete[](VOID_PTR ptr)
{
	return Common::System::Allocator::Free(ptr);
}

