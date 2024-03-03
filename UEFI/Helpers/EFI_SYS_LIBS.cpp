#include <Helpers/EFI_SYS_LIBS.h>
namespace EFI
{
	static BOOLEAN _initialized;
	static EFI_STATUS _lastStatus;
	static EFI_SYSTEM_TABLE* _systemTable;
	static EFI_HANDLE _imgHandle;

	void EFI_SYS_LIBS::InitializeLib(EFI_HANDLE imageHandle, EFI_SYSTEM_TABLE* systemTable)
	{
		if (_systemTable == nullptr)
		{
			_lastStatus = EFI_STATUS::INVALID_PARAMETER;
			_initialized = false;
			return;
		}

		_systemTable = systemTable;
		_imgHandle = imageHandle;

		_initialized = true;
		_lastStatus = EFI_STATUS::SUCCESS;
	}

	BOOLEAN EFI_SYS_LIBS::IsInitialized()
	{
		return _initialized;
	}

	EFI_STATUS EFI_SYS_LIBS::LastStatus()
	{
		return _lastStatus;
	}

	void* EFI_SYS_LIBS::AllocatePool(UINTN size)
	{
		void* buffer = nullptr;
		_lastStatus = _systemTable->BootServices->AllocatePool(EFI_MEMORY_TYPE::LoaderData, size, &buffer);
		return buffer;
	}

	void* EFI_SYS_LIBS::AllocatePlacedPool(UINTN size, EFI_PHYSICAL_ADDRESS memory)
	{
		return memory;
	}

	void* EFI_SYS_LIBS::AllocateZeroPool(UINTN size)
	{
		void* buffer = nullptr;
		_lastStatus = _systemTable->BootServices->AllocatePool(EFI_MEMORY_TYPE::LoaderData, size, &buffer);
		if (_lastStatus == EFI_STATUS::SUCCESS)
		{
			SetMem(buffer, size, (UINT8)0);
		}
		return buffer;
	}

	void* EFI_SYS_LIBS::AllocatePlacedZeroPool(UINTN size, EFI_PHYSICAL_ADDRESS memory)
	{
		SetMem(memory, size, (UINT8)0u);
		return memory;
	}

	void EFI_SYS_LIBS::FreePool(void* buffer)
	{
		_lastStatus = _systemTable->BootServices->FreePool(buffer);
	}

	void* EFI_SYS_LIBS::CopyMem(void* destination, void* source, UINTN length)
	{
		_lastStatus = _systemTable->BootServices->CopyMem(destination, source, length);
		return destination;
	}

	void* EFI_SYS_LIBS::MoveMem(void* destination, void* source, UINTN length)
	{
		_lastStatus = _systemTable->BootServices->CopyMem(destination, source, length);
		if (_lastStatus == EFI_STATUS::SUCCESS)
			return nullptr;

		_lastStatus = _systemTable->BootServices->SetMem(source, length, 0);
		return destination;
	}

	void* EFI_SYS_LIBS::SetMem(void* buffer, UINTN size, UINT8 value)
	{
		_lastStatus = _systemTable->BootServices->SetMem(buffer, size, value);
		return buffer;
	}

	void* EFI_SYS_LIBS::ZeroMem(void* buffer, UINTN size)
	{
		_lastStatus = _systemTable->BootServices->SetMem(buffer, size, 0);
		return buffer;
	}

	void* EFI_SYS_LIBS::AllocatePages(UINTN pages)
	{
		EFI_PHYSICAL_ADDRESS buffer = nullptr;
		_lastStatus = _systemTable->BootServices->AllocatePages(EFI_ALLOCATE_TYPE::AllocateAnyPages, EFI_MEMORY_TYPE::LoaderData, pages, &buffer);
		return buffer;
	}

	void EFI_SYS_LIBS::FreePages(void* buffer, UINTN pages)
	{
		_lastStatus = _systemTable->BootServices->FreePages((EFI_PHYSICAL_ADDRESS)buffer, pages);
	}
}

void* operator new(UINTN size)
{
	if (EFI::EFI_SYS_LIBS::IsInitialized())
	{
		return EFI::EFI_SYS_LIBS::AllocatePool(size);
	}
	return nullptr;
}

void* operator new[](UINTN size)
{
	if (EFI::EFI_SYS_LIBS::IsInitialized())
	{
		return EFI::EFI_SYS_LIBS::AllocatePool(size);
	}
	return nullptr;
}

void operator delete(void* ptr)
{
	if (EFI::EFI_SYS_LIBS::IsInitialized())
	{
		EFI::EFI_SYS_LIBS::FreePool(ptr);
	}
}

void operator delete[](void* ptr)
{
	if (EFI::EFI_SYS_LIBS::IsInitialized())
	{
		EFI::EFI_SYS_LIBS::FreePool(ptr);
	}
}

void operator delete  (void* ptr, void* n)
{
	if (EFI::EFI_SYS_LIBS::IsInitialized())
	{
		EFI::EFI_SYS_LIBS::FreePool(ptr);
	}
};

void operator delete[](void* ptr, void* n)
{
	if (EFI::EFI_SYS_LIBS::IsInitialized())
	{
		EFI::EFI_SYS_LIBS::FreePool(ptr);
	}
};