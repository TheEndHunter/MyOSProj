#pragma once
#include <UEFIDef.h>
#include <EFI_GUID.h>

namespace Bootloader::Enviroment
{
	using namespace EFI;

	class StringHelpers
	{
	public:

		static const CHAR16* ToString(const EFI_GUID guid);

		static const CHAR16* ToString(const UINT8 b);
		static const CHAR16* ToString(const UINT16 b);
		static const CHAR16* ToString(const UINT32 b);
		static const CHAR16* ToString(const UINT64 b);

		static const CHAR16* ToHex(const UINT8 b);
		static const CHAR16* ToHex(const UINT16 b);
		static const CHAR16* ToHex(const UINT32 b);
		static const CHAR16* ToHex(const UINT64 b);

		static const CHAR16* ToString(const INT8 b);
		static const CHAR16* ToString(const INT16 b);
		static const CHAR16* ToString(const INT32 b);
		static const CHAR16* ToString(const INT64 b);

		static const CHAR16* ToHex(const INT8 b);
		static const CHAR16* ToHex(const INT16 b);
		static const CHAR16* ToHex(const INT32 b);
		static const CHAR16* ToHex(const INT64 b);
	};
}
