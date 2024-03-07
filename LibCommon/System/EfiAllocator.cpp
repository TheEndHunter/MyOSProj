#include "EfiAllocator.h"
#include <EFI_STATUS.h>
#include <EFI_SYSTEM_TABLE.h>
#include <EFI_MEMORY_TYPE.h>
#include "MemFuncs.h"

namespace Common::System
{
	EFI::EFI_SYSTEM_TABLE* _sysTable;

	AllocatorStatus _efi_lastStatus;

	static AllocatorStatus GetStatus()
	{
		return _efi_lastStatus;
	}

	CONST static UINTN PAGE_SHIFT = 12;
	CONST static UINTN PAGE_SIZE = 1ul << PAGE_SHIFT;
	CONST static UINTN PAGES_MAX = MAX_UINTN >> PAGE_SHIFT;

	static VOID* Allocate(UINTN size)
	{
		if (_sysTable == nullptr)
		{
			_efi_lastStatus = AllocatorStatus::Not_Initialized;
			return nullptr;
		}

		EFI::EFI_STATUS status;
		VOID* buffer;
		status = _sysTable->BootServices->AllocatePool(EFI::EFI_MEMORY_TYPE::LoaderData, size, &buffer);
		if(status != EFI::EFI_STATUS::SUCCESS)
		{
			switch(status)
			{
				case EFI::EFI_STATUS::OUT_OF_RESOURCES:
					_efi_lastStatus = AllocatorStatus::Not_Enough_Memory;
					break;
				case EFI::EFI_STATUS::INVALID_PARAMETER:
					_efi_lastStatus = AllocatorStatus::Invalid_Parameters;
					break;
			}
			return nullptr;
		}

		_efi_lastStatus = AllocatorStatus::Success;
		return buffer;
	}

	static VOID* AllocateZeroed(UINTN size)
	{
		if (_sysTable == nullptr)
		{
			_efi_lastStatus = AllocatorStatus::Not_Initialized;
			return nullptr;
		}

		EFI::EFI_STATUS status;
		VOID* buffer;
		status = _sysTable->BootServices->AllocatePool(EFI::EFI_MEMORY_TYPE::LoaderData, size, &buffer);
		if (status != EFI::EFI_STATUS::SUCCESS)
		{
			switch (status)
			{
			case EFI::EFI_STATUS::OUT_OF_RESOURCES:
				_efi_lastStatus = AllocatorStatus::Not_Enough_Memory;
				break;
			case EFI::EFI_STATUS::INVALID_PARAMETER:
				_efi_lastStatus = AllocatorStatus::Invalid_Parameters;
				break;
			}
			return nullptr;
		}

		Common::System::MemZero(buffer,size);

		_efi_lastStatus = AllocatorStatus::Success;
		return buffer;
	}

	static VOID* AllocatePages(UINTN pages)
	{
		if(_sysTable == nullptr)
		{
			_efi_lastStatus = AllocatorStatus::Not_Initialized;
			return nullptr;
		}

		EFI::EFI_STATUS status;
		VOID* buffer;
		status = _sysTable->BootServices->AllocatePages(EFI::EFI_ALLOCATE_TYPE::AllocateAnyPages, EFI::EFI_MEMORY_TYPE::LoaderData, pages, &buffer);
		if(status != EFI::EFI_STATUS::SUCCESS)
		{
			switch(status)
			{
				case EFI::EFI_STATUS::OUT_OF_RESOURCES:
					_efi_lastStatus = AllocatorStatus::Not_Enough_Memory;
					break;
				case EFI::EFI_STATUS::INVALID_PARAMETER:
					_efi_lastStatus = AllocatorStatus::Invalid_Parameters;
					break;
			}
			return nullptr;
		}

		_efi_lastStatus = AllocatorStatus::Success;
		return buffer;
	}

	static VOID* AllocatePagesZeroed(UINTN pages)
	{
		if(_sysTable == nullptr)
		{
			_efi_lastStatus = AllocatorStatus::Not_Initialized;
			return nullptr;
		}

		EFI::EFI_STATUS status;
		VOID* buffer;
		status = _sysTable->BootServices->AllocatePages(EFI::EFI_ALLOCATE_TYPE::AllocateAnyPages, EFI::EFI_MEMORY_TYPE::LoaderData, pages, &buffer);
		if(status != EFI::EFI_STATUS::SUCCESS)
		{
			switch(status)
			{
				case EFI::EFI_STATUS::OUT_OF_RESOURCES:
					_efi_lastStatus = AllocatorStatus::Not_Enough_Memory;
					break;
				case EFI::EFI_STATUS::INVALID_PARAMETER:
					_efi_lastStatus = AllocatorStatus::Invalid_Parameters;
					break;
			}
			return nullptr;
		}


		Common::System::MemZero(buffer,(pages*PAGE_SIZE));

		_efi_lastStatus = AllocatorStatus::Success;
		return buffer;
	}

	static VOID Free(VOID* buffer)
	{
		if(_sysTable == nullptr)
		{
			_efi_lastStatus = AllocatorStatus::Not_Initialized;
			return;
		}
		
		_sysTable->BootServices->FreePool(buffer);
		_efi_lastStatus = AllocatorStatus::Success;
	}

	static VOID FreePage(VOID* buffer, UINTN pages)
	{
		if(_sysTable == nullptr)
		{
			_efi_lastStatus = AllocatorStatus::Not_Initialized;
			return;
		}

		_sysTable->BootServices->FreePages(buffer, pages);
		_efi_lastStatus = AllocatorStatus::Success;
	}

	static void SetStatus(AllocatorStatus status)
	{
		_efi_lastStatus = status;
	}

	VOID EFIAllocator::SetEFIAllocator(EFI::EFI_SYSTEM_TABLE* systemTable)
	{
		if (systemTable != nullptr)
		{
			_sysTable = systemTable;
			Allocator::SetAllocators(Allocate, AllocateZeroed, AllocatePages, AllocatePagesZeroed, Free, FreePage, GetStatus,SetStatus);
		}
		else
		{
			_efi_lastStatus = AllocatorStatus::Invalid_Parameters;
		}
	}
}
