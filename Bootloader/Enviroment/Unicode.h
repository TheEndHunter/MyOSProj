#pragma once
#include <UEFIDef.h>
#include <EFI_GUID.h>
#include <EFI_STATUS.h>

namespace Bootloader::Enviroment
{
	class UTF16
	{
	public:
		static const CHAR16  NULL = u'\0';
		static const CHAR16* NewLine;
		static const CHAR16  Space = u' ';
		static const CHAR16  Tab = u'\t';
		static const CHAR16  Backspace = u'\b';

		static const CHAR16* ToHex(const INT16 b);
		static const CHAR16* ToHex(const INT32 b);
		static const CHAR16* ToHex(const INT64 b);
		static const CHAR16* ToHex(const INT8 b);
		static const CHAR16* ToHex(const UINT16 b);
		static const CHAR16* ToHex(const UINT32 b);
		static const CHAR16* ToHex(const UINT64 b);
		static const CHAR16* ToHex(const UINT8 b);
		static const CHAR16* ToString(const EFI::EFI_GUID guid);
		static const CHAR16* ToString(const EFI::EFI_STATUS status);
		static const CHAR16* ToString(const INT16 b);
		static const CHAR16* ToString(const INT32 b);
		static const CHAR16* ToString(const INT64 b);
		static const CHAR16* ToString(const INT8 b);
		static const CHAR16* ToString(const UINT16 b);
		static const CHAR16* ToString(const UINT32 b);
		static const CHAR16* ToString(const UINT64 b);
		static const CHAR16* ToString(const UINT8 b);
	};

	class UTF8
	{
	public:
		static const CHAR8  NULL = '\0';
		static const CHAR8* NewLine;
		static const CHAR8  Space = ' ';
		static const CHAR8  Tab = '\t';
		static const CHAR8  Backspace = '\b';

		static const CHAR8* ToHex(const INT16 b);
		static const CHAR8* ToHex(const INT32 b);
		static const CHAR8* ToHex(const INT64 b);
		static const CHAR8* ToHex(const INT8 b);
		static const CHAR8* ToHex(const UINT16 b);
		static const CHAR8* ToHex(const UINT32 b);
		static const CHAR8* ToHex(const UINT64 b);
		static const CHAR8* ToHex(const UINT8 b);
		static const CHAR8* ToString(const EFI::EFI_GUID guid);
		static const CHAR8* ToString(const EFI::EFI_STATUS status);
		static const CHAR8* ToString(const INT16 b);
		static const CHAR8* ToString(const INT32 b);
		static const CHAR8* ToString(const INT64 b);
		static const CHAR8* ToString(const INT8 b);
		static const CHAR8* ToString(const UINT16 b);
		static const CHAR8* ToString(const UINT32 b);
		static const CHAR8* ToString(const UINT64 b);
		static const CHAR8* ToString(const UINT8 b);
	};
}