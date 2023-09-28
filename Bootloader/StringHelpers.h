#pragma once
#include <UEFIDef.h>
#include <EFI_GUID.h>

namespace Bootloader
{
	using namespace EFI;

	static class StringHelpers
	{
	public:

		static const CHAR16* ToString(const EFI_GUID guid);
		static const CHAR16* ToHex(const UINT8 b);
		static const CHAR16* ToHex(const UINT16 b);
		static const CHAR16* ToHex(const UINT32 b);
		static const CHAR16* ToHex(const UINT64 b);
	};
}
