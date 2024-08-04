#include <System\MemoryManagement\EfiAllocator.h>
#include <System\MemoryManagement\AllocatorStatus.h>

#include <EFI_SYSTEM_TABLE.h>


namespace Common::System::MemoryManagement
{
#pragma region EfiAllocator

	EFI::EFI_SYSTEM_TABLE* EfiAllocator::_efiSystemTable = nullptr; // Definition for the EFI_SYSTEM_TABLE pointer
	AllocatorStatus EfiAllocator::_lastStatus = AllocatorStatus::Not_Initialized; // Definition for the AllocatorStatus

	VOID_PTR EfiAllocator::Allocate(UINTN length)
	{
		if (EfiAllocator::_efiSystemTable == nullptr)
		{
			return nullptr;
		}

		EFI::EFI_STATUS status;
		VOID* buffer;
		status = EfiAllocator::_efiSystemTable->BootServices->AllocatePool(EFI::EFI_MEMORY_TYPE::LoaderData, length, &buffer);
		if (status != EFI::EFI_STATUS::SUCCESS)
		{
			switch (status)
			{
			case EFI::EFI_STATUS::OUT_OF_RESOURCES:
				_lastStatus = AllocatorStatus::Not_Enough_Memory;
				break;
			case EFI::EFI_STATUS::INVALID_PARAMETER:
				_lastStatus = AllocatorStatus::Invalid_Parameters;
				break;
			}
			return nullptr;
		}

		_lastStatus = AllocatorStatus::Success;
		return buffer;
	}
	VOID_PTR EfiAllocator::AllocateZeroed(UINTN length)
	{
		if (EfiAllocator::_efiSystemTable == nullptr)
		{
			return nullptr;
		}

		EFI::EFI_STATUS status;
		VOID* buffer;
		status = EfiAllocator::_efiSystemTable->BootServices->AllocatePool(EFI::EFI_MEMORY_TYPE::LoaderData, length, &buffer);
		if (status != EFI::EFI_STATUS::SUCCESS)
		{
			switch (status)
			{
			case EFI::EFI_STATUS::OUT_OF_RESOURCES:
				_lastStatus = AllocatorStatus::Not_Enough_Memory;
				break;
			case EFI::EFI_STATUS::INVALID_PARAMETER:
				_lastStatus = AllocatorStatus::Invalid_Parameters;
				break;
			}
			return nullptr;
		}

		status = EfiAllocator::_efiSystemTable->BootServices->SetMem(buffer, length, 0);

		_lastStatus = AllocatorStatus::Success;
		return buffer;
	}
	VOID_PTR EfiAllocator::AllocatePage(UINTN pageCount)
	{
		if (EfiAllocator::_efiSystemTable == nullptr)
		{
			return nullptr;
		}

		EFI::EFI_STATUS status;
		VOID* buffer;
		status = EfiAllocator::_efiSystemTable->BootServices->AllocatePages(EFI::EFI_ALLOCATE_TYPE::AllocateAnyPages, EFI::EFI_MEMORY_TYPE::LoaderData, pageCount, &buffer);
		if (status != EFI::EFI_STATUS::SUCCESS)
		{
			switch (status)
			{
			case EFI::EFI_STATUS::OUT_OF_RESOURCES:
				_lastStatus = AllocatorStatus::Not_Enough_Memory;
				break;
			case EFI::EFI_STATUS::INVALID_PARAMETER:
				_lastStatus = AllocatorStatus::Invalid_Parameters;
				break;
			}
			return nullptr;
		}

		_lastStatus = AllocatorStatus::Success;
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
		status = EfiAllocator::_efiSystemTable->BootServices->AllocatePages(EFI::EFI_ALLOCATE_TYPE::AllocateAnyPages, EFI::EFI_MEMORY_TYPE::LoaderData, pageCount, &buffer);
		if (status != EFI::EFI_STATUS::SUCCESS)
		{
			switch (status)
			{
			case EFI::EFI_STATUS::OUT_OF_RESOURCES:
				_lastStatus = AllocatorStatus::Not_Enough_Memory;
				break;
			case EFI::EFI_STATUS::INVALID_PARAMETER:
				_lastStatus = AllocatorStatus::Invalid_Parameters;
				break;
			}
			return nullptr;
		}

		status = EfiAllocator::_efiSystemTable->BootServices->SetMem(buffer, (pageCount * 4096), 0);

		_lastStatus = AllocatorStatus::Success;
		return buffer;
	}
	VOID EfiAllocator::Free(VOID_PTR ptr)
	{
		if (EfiAllocator::_efiSystemTable == nullptr)
		{
			return;
		}
		EfiAllocator::_efiSystemTable->BootServices->FreePool(ptr);
	}
	VOID EfiAllocator::FreePage(VOID_PTR ptr, UINTN pageCount)
	{
		if (EfiAllocator::_efiSystemTable == nullptr)
		{
			return;
		}
		EfiAllocator::_efiSystemTable->BootServices->FreePages(ptr, pageCount);
	}
#pragma endregion
}