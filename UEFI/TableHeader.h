#pragma once
#include "UEFIDef.h"

namespace Efi
{
	constexpr UINT64 EFI_SYSTEM_TABLE_SIGNATURE = 0x5453595320494249ull;
	constexpr UINT64 EFI_2_100_SYSTEM_TABLE_REVISION = ((2<<16) | (100));
	constexpr UINT64 EFI_2_90_SYSTEM_TABLE_REVISION  = ((2<<16) | (90));
	constexpr UINT64 EFI_2_80_SYSTEM_TABLE_REVISION  = ((2<<16) | (80));
	constexpr UINT64 EFI_2_70_SYSTEM_TABLE_REVISION  = ((2<<16) | (70));
	constexpr UINT64 EFI_2_60_SYSTEM_TABLE_REVISION  = ((2<<16) | (60));
	constexpr UINT64 EFI_2_50_SYSTEM_TABLE_REVISION  = ((2<<16) | (50));
	constexpr UINT64 EFI_2_40_SYSTEM_TABLE_REVISION  = ((2<<16) | (40));
	constexpr UINT64 EFI_2_31_SYSTEM_TABLE_REVISION  = ((2<<16) | (31));
	constexpr UINT64 EFI_2_30_SYSTEM_TABLE_REVISION  = ((2<<16) | (30));
	constexpr UINT64 EFI_2_20_SYSTEM_TABLE_REVISION  = ((2<<16) | (20));
	constexpr UINT64 EFI_2_10_SYSTEM_TABLE_REVISION  = ((2<<16) | (10));
	constexpr UINT64 EFI_2_00_SYSTEM_TABLE_REVISION  = ((2<<16) | (00));
	constexpr UINT64 EFI_1_10_SYSTEM_TABLE_REVISION  = ((1<<16) | (10));
	constexpr UINT64 EFI_1_02_SYSTEM_TABLE_REVISION  = ((1<<16) | (02));
	constexpr UINT64 EFI_SYSTEM_TABLE_REVISION = EFI_2_100_SYSTEM_TABLE_REVISION;
	constexpr UINT64 SpecificationVersion = EFI_SYSTEM_TABLE_REVISION;

	struct TableHeader
	{
	public:
		UINT64 Signature;
		UINT32 Revision;
		UINT32 HeaderSize;
		UINT32 CRC32;
		UINT32 Reserved;
	};
}