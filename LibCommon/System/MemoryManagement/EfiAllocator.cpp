#include <System\MemoryManagement\EfiAllocator.h>
#include <System\MemoryManagement\AllocatorStatus.h>

#include <SystemTable.h>


namespace Common::System::MemoryManagement
{
#pragma region EfiAllocator

	Efi::SystemTable* EfiAllocator::_efiSystemTable = nullptr; // Definition for the SystemTable pointer
	AllocatorStatus EfiAllocator::_lastStatus = AllocatorStatus::NotInitialized; // Definition for the AllocatorStatus

	VOID_PTR EfiAllocator::Allocate(UINTN length)
	{
		if (EfiAllocator::_efiSystemTable == nullptr)
		{
			return nullptr;
		}

		Efi::Status status;
		VOID* buffer;
		status = EfiAllocator::_efiSystemTable->BootServices->AllocatePool(Efi::MemoryType::LoaderData, length, &buffer);
		if (status != Efi::Status::Success)
		{
			switch (status)
			{
			case Efi::Status::OutOfResources:
				_lastStatus = AllocatorStatus::NotEnoughMemory;
				break;
			case Efi::Status::InvalidParameter:
				_lastStatus = AllocatorStatus::InvalidParameters;
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

		Efi::Status status;
		VOID* buffer;
		status = EfiAllocator::_efiSystemTable->BootServices->AllocatePool(Efi::MemoryType::LoaderData, length, &buffer);
		if (status != Efi::Status::Success)
		{
			switch (status)
			{
			case Efi::Status::OutOfResources:
				_lastStatus = AllocatorStatus::NotEnoughMemory;
				break;
			case Efi::Status::InvalidParameter:
				_lastStatus = AllocatorStatus::InvalidParameters;
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

		Efi::Status status;
		VOID* buffer;
		status = EfiAllocator::_efiSystemTable->BootServices->AllocatePages(Efi::AllocateType::AllocateAnyPages, Efi::MemoryType::LoaderData, pageCount, &buffer);
		if (status != Efi::Status::Success)
		{
			switch (status)
			{
			case Efi::Status::OutOfResources:
				_lastStatus = AllocatorStatus::NotEnoughMemory;
				break;
			case Efi::Status::InvalidParameter:
				_lastStatus = AllocatorStatus::InvalidParameters;
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

		Efi::Status status;
		VOID* buffer;
		status = EfiAllocator::_efiSystemTable->BootServices->AllocatePages(Efi::AllocateType::AllocateAnyPages, Efi::MemoryType::LoaderData, pageCount, &buffer);
		if (status != Efi::Status::Success)
		{
			switch (status)
			{
			case Efi::Status::OutOfResources:
				_lastStatus = AllocatorStatus::NotEnoughMemory;
				break;
			case Efi::Status::InvalidParameter:
				_lastStatus = AllocatorStatus::InvalidParameters;
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