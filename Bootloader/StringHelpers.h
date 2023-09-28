#pragma once
#include <UEFIDef.h>
#include <EFI_GUID.h>
#include <EFI_SYSTEM_TABLE.h>
#include <EFI_MEMORY_TYPE.h>

namespace Bootloader
{
	using namespace EFI;

	static class StringHelpers
	{
	public:

		static const CHAR16* ToString(EFI_SYSTEM_TABLE* sysTable, EFI_GUID guid);

		static const CHAR16* ToHex(EFI_SYSTEM_TABLE* sysTable, UINT8 b);
		static const CHAR16* ToHex(EFI_SYSTEM_TABLE* sysTable, UINT16 b);
		static const CHAR16* ToHex(EFI_SYSTEM_TABLE* sysTable, UINT32 b);
		static const CHAR16* ToHex(EFI_SYSTEM_TABLE* sysTable, UINT64 b);
	};
}
