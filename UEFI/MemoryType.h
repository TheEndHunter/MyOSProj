#pragma once

namespace Efi
{
	enum class MemoryType
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
