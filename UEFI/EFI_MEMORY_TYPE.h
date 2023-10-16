#pragma once

namespace EFI
{
	enum class EFI_MEMORY_TYPE
	{
		ReservedMemoryType,
		LoaderCode,
		LoaderData,
		BootServicesCode,
		BootServicesData,
		RuntimeServicesCode,
		RuntimeServicesData,
		ConventionalMemory,
		UnusableMemory,
		ACPIReclaimMemory,
		ACPIMemoryNVS,
		MemoryMappedIO,
		MemoryMappedIOPortSpace,
		PalCode,
		PersistentMemory,
		UnacceptedMemoryType,
		MaxMemoryType
	};
}
