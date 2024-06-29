#pragma once
#include <TypeDefs.h>
#include <EFI_STATUS.h>

namespace Common::System::MemoryManagement
{
	enum class AllocatorStatus : UINT64
	{
		Success = 0,
		Invalid_Parameters = 1,
		Not_Initialized = 2,
		Not_Enough_Memory = 3,
		Not_Enough_Pages = 4,
		Access_Denied = 5,
		Unknown = 6
	};

	static const EFI::EFI_STATUS ToEfiStatus(const AllocatorStatus status)
	{
		if(status == AllocatorStatus::Success)
			return EFI::EFI_STATUS::SUCCESS;

		if(status == AllocatorStatus::Invalid_Parameters)
			return EFI::EFI_STATUS::INVALID_PARAMETER;

		if(status == AllocatorStatus::Not_Initialized)
			return EFI::EFI_STATUS::NOT_READY;

		if(status == AllocatorStatus::Not_Enough_Memory)
			return EFI::EFI_STATUS::OUT_OF_RESOURCES;

		if(status == AllocatorStatus::Not_Enough_Pages)
			return EFI::EFI_STATUS::OUT_OF_RESOURCES;

		if(status == AllocatorStatus::Access_Denied)
			return EFI::EFI_STATUS::ACCESS_DENIED;

		if(status == AllocatorStatus::Unknown)
			return EFI::EFI_STATUS::UNSUPPORTED;
		
		return EFI::EFI_STATUS::UNSUPPORTED;
	}

	static const AllocatorStatus FromEfiStatus(const EFI::EFI_STATUS status)
	{
		if(status == EFI::EFI_STATUS::SUCCESS)
			return AllocatorStatus::Success;

		if(status == EFI::EFI_STATUS::INVALID_PARAMETER)
			return AllocatorStatus::Invalid_Parameters;

		if(status == EFI::EFI_STATUS::NOT_READY)
			return AllocatorStatus::Not_Initialized;

		if(status == EFI::EFI_STATUS::OUT_OF_RESOURCES)
			return AllocatorStatus::Not_Enough_Memory;

		if(status == EFI::EFI_STATUS::OUT_OF_RESOURCES)
			return AllocatorStatus::Not_Enough_Memory;

		if(status == EFI::EFI_STATUS::ACCESS_DENIED)
			return AllocatorStatus::Access_Denied;

		return AllocatorStatus::Unknown;
	}
}
