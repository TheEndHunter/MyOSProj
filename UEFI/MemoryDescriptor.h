#pragma once
#include "UEFIDef.h"
#include "MemoryAddress.h"

namespace Efi
{
	constexpr UINTN MemoryDescriptorVersion = 1;

	enum class MemoryAttributes : UINT64
	{		
		/// <summary>
		/// Memory cache-ability attribute: The memory region supports being configured as not cacheable.
		/// </summary>
		UC = 0x0000000000000001,		
		/// <summary>
		/// Memory cache-ability attribute: The memory region supports being configured as not cacheable.
		/// </summary>
		WC = 0x0000000000000002,		
		/// <summary>
		/// Memory cache-ability attribute: The memory region supports being configured as cacheable with a “write through” policy.
		///  Writes that hit in the cache will also be written to main memory.
		/// </summary>
		WT = 0x0000000000000004,		
		/// <summary>
		/// Memory cache-ability attribute: The memory region supports being configured as cacheable with a “write back” policy. 
		/// Reads and writes that hit in the cache do not propagate to main memory. 
		/// Dirty data is written back to main memory when a new cache line is allocated.
		/// </summary>
		WB = 0x0000000000000008,		
		/// <summary>
		/// Memory cache-ability attribute: The memory region supports being configured as cacheable with a “write back” policy. 
		/// Reads and writes that hit in the cache do not propagate to main memory. 
		/// Dirty data is written back to main memory when a new cache line is allocated.
		/// </summary>
		UCE = 0x0000000000000010,		
		/// <summary>
		/// Physical memory protection attribute: The memory region supports being configured as write-protected by system hardware.
		/// This is typically used as a cache-ability attribute today. The memory region supports being configured as cacheable with a “write protected” policy.
		/// Reads come from cache lines when possible, and read misses cause cache fills.
		/// Writes are propagated to the system bus and cause corresponding cache lines on all processors on the bus to be invalidated.
		/// </summary>
		WP = 0x0000000000001000,		
		/// <summary>
		/// Physical memory protection attribute: The memory region supports being configured as read-protected by system hardware.
		/// </summary>
		RP = 0x0000000000002000,		
		/// <summary>
		/// Physical memory protection attribute: The memory region supports being configured so it is protected by system hardware from executing code.
		/// </summary>
		XP = 0x0000000000004000,		
		/// <summary>
		/// Runtime memory attribute: The memory region refers to persistent memory
		/// </summary>
		NV = 0x0000000000008000,		
		/// <summary>
		/// The memory region provides higher reliability relative to other memory in the system. 
		/// If all memory has the same reliability, then this bit is not used.
		/// </summary>
		MoreReliable = 0x0000000000010000,		
		/// <summary>
		/// Physical memory protection attribute: The memory region supports making this memory range read-only by system hardware.
		/// </summary>
		RO = 0x0000000000020000,		
		/// <summary>
		/// Specific-purpose memory (SPM).
		/// The memory is earmarked for specific purposes such as for specific device drivers or applications.
		/// The SPM attribute serves as a hint to the OS to avoid allocating this memory for core OS data or code that can not be relocated.
		/// Prolonged use of this memory for purposes other than the intended purpose may result in suboptimal platform performance.
		/// </summary>
		SP = 0x0000000000040000,				
		/// <summary>
		/// If this flag is set, the memory region is capable of being protected with the CPU’s memory cryptographic capabilities.
		/// If this flag is clear, the memory region is not capable of being protected with the CPU’s memory cryptographic capabilities or the CPU does not support CPU memory cryptographic capabilities.
		/// </summary>
		CpuCrypto = 0x0000000000080000,		
		/// <summary>
		/// Runtime memory attribute: The memory region needs to be given a virtual mapping by the operating system when SetVirtualAddressMap() is called (described in Virtual Memory Services).
		/// </summary>
		Runtime = 0x8000000000000000,		
		/// <summary>
		/// If this flag is set, the memory region is described with additional ISA-specific memory attributes as specified in EFI_MEMORY_ISA_MASK .
		/// </summary>
		IsaValid = 0x4000000000000000,		
		/// <summary>
		/// Defines the bits reserved for describing optional ISA-specific cache-ability attributes that are not covered by the standard UEFI Memory Attributes cache-ability bits
		/// (MemoryAttributes::UC, MemoryAttributes::WC, MemoryAttributes::WT, MemoryAttributes::WB and MemoryAttributes::UCE).
		/// See Calling Conventions for further ISA-specific enum classeration of these bits.
		/// </summary>
		IsaMask = 0x0FFFF00000000000,
	};

	struct MemoryDescriptor
	{
  public:
      UINT32 Type;																																																																																																						
  private:
      UINT32 Padding;
  public:
      PhysicalAddress PhysicalStart;
      VirtualAddress VirtualStart;
      UINT64 NumberOfPages;
      MemoryAttributes Attribute;
  };
}
