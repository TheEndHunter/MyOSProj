#pragma once
#include <TypeDefs.h>
#include <Status.h>

namespace Common::System::MemoryManagement
{
	enum class AllocatorStatus : UINT64
	{
		Success = 0,
		InvalidParameters = 1,
		NotInitialized = 2,
		NotEnoughMemory = 3,
		NotEnoughPages = 4,
		AccessDenied = 5,
		Unknown = 6
	};

	static const Efi::Status ToEfiStatus(const AllocatorStatus status)
	{
		if(status == AllocatorStatus::Success)
			return Efi::Status::Success;

		if(status == AllocatorStatus::InvalidParameters)
			return Efi::Status::InvalidParameter;

		if(status == AllocatorStatus::NotInitialized)
			return Efi::Status::NotReady;

		if(status == AllocatorStatus::NotEnoughMemory)
			return Efi::Status::OutOfResources;

		if(status == AllocatorStatus::NotEnoughPages)
			return Efi::Status::OutOfResources;

		if(status == AllocatorStatus::AccessDenied)
			return Efi::Status::AccessDenied;

		if(status == AllocatorStatus::Unknown)
			return Efi::Status::Unsupported;
		
		return Efi::Status::Unsupported;
	}

	static const AllocatorStatus FromEfiStatus(const Efi::Status status)
	{
		if(status == Efi::Status::Success)
			return AllocatorStatus::Success;

		if(status == Efi::Status::InvalidParameter)
			return AllocatorStatus::InvalidParameters;

		if(status == Efi::Status::NotReady)
			return AllocatorStatus::NotInitialized;

		if(status == Efi::Status::OutOfResources)
			return AllocatorStatus::NotEnoughMemory;

		if(status == Efi::Status::OutOfResources)
			return AllocatorStatus::NotEnoughMemory;

		if(status == Efi::Status::AccessDenied)
			return AllocatorStatus::AccessDenied;

		return AllocatorStatus::Unknown;
	}
}
