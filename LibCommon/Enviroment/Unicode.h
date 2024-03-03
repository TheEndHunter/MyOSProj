#pragma once
#include "TypeDefs.h"
#include <EFI_GUID.h>
#include <EFI_STATUS.h>
#include <Enviroment/StringCulture.h>

namespace Common::Enviroment
{
	class UTF16
	{
	public:
		static const CHAR16  NULL = u'\0';
		static const CHAR16* NewLine;
		static const CHAR16  Space = u' ';
		static const CHAR16  Tab = u'\t';
		static const CHAR16  Backspace = u'\b';

		static const CHAR16* ToHex(const INT16 value);
		static const CHAR16* ToHex(const INT32 value);
		static const CHAR16* ToHex(const INT64 value);
		static const CHAR16* ToHex(const INT8 value);

		static const CHAR16* ToHex(const UINT16 value);
		static const CHAR16* ToHex(const UINT32 value);
		static const CHAR16* ToHex(const UINT64 value);
		static const CHAR16* ToHex(const UINT8 value);
		static const CHAR16* ToHex(const VOID_PTR ptr);

		static const CHAR16* ToString(const EFI::EFI_GUID guid);
		static const CHAR16* ToString(const EFI::EFI_STATUS status);
		static const CHAR16* ToString(const INT16 value);
		static const CHAR16* ToString(const INT32 value);
		static const CHAR16* ToString(const INT64 value);
		static const CHAR16* ToString(const INT8 value);

		static const CHAR16* ToString(const UINT16 value);
		static const CHAR16* ToString(const UINT32 value);
		static const CHAR16* ToString(const UINT64 value);
		static const CHAR16* ToString(const UINT8 value);
		static const CHAR16* ToString(const VOID_PTR ptr);
		static const CHAR16* ToString(const BOOLEAN boolean);

		static const UINTN Length(const CHAR16* str);
		static const BOOLEAN Compare(const CHAR16* l,const CHAR16* r, StringCulture culture = InvariantCulture);
		static const BOOLEAN StartsWith(const CHAR16* str, const CHAR16* value, StringCulture culture = InvariantCulture);
		static const BOOLEAN EndsWith(const CHAR16* str, const CHAR16* value, StringCulture culture = InvariantCulture);
		static const BOOLEAN Contains(const CHAR16* str, const CHAR16* value, StringCulture culture = InvariantCulture);
		static const BOOLEAN IsNullOrEmpty(const CHAR16* str);
		static const BOOLEAN IsNullOrWhiteSpace(const CHAR16* str);
	};

	class UTF8
	{
	public:
		static const CHAR8  NULL = '\0';
		static const CHAR8* NewLine;
		static const CHAR8  Space = ' ';
		static const CHAR8  Tab = '\t';
		static const CHAR8  Backspace = '\b';

		static const CHAR8* ToHex(const INT16 value);
		static const CHAR8* ToHex(const INT32 value);
		static const CHAR8* ToHex(const INT64 value);
		static const CHAR8* ToHex(const INT8 value);
		static const CHAR8* ToHex(const UINT16 value);
		static const CHAR8* ToHex(const UINT32 value);
		static const CHAR8* ToHex(const UINT64 value);
		static const CHAR8* ToHex(const UINT8 value);
		static const CHAR8* ToHex(const VOID_PTR ptr);

		static const CHAR8* ToString(const EFI::EFI_GUID guid);
		static const CHAR8* ToString(const EFI::EFI_STATUS status);
		static const CHAR8* ToString(const INT16 value);
		static const CHAR8* ToString(const INT32 value);
		static const CHAR8* ToString(const INT64 value);
		static const CHAR8* ToString(const INT8 value);
		static const CHAR8* ToString(const UINT16 value);
		static const CHAR8* ToString(const UINT32 value);
		static const CHAR8* ToString(const UINT64 value);
		static const CHAR8* ToString(const UINT8 value);
		static const CHAR8* ToString(const VOID_PTR ptr);
		static const CHAR8* ToString(const BOOLEAN boolean);

		static const UINTN Length(const CHAR8* str);
		static const BOOLEAN Compare(const CHAR8* l, const CHAR8* r, StringCulture culture = InvariantCulture);
		static const BOOLEAN StartsWith(const CHAR8* str, const CHAR8* value, StringCulture culture = InvariantCulture);
		static const BOOLEAN EndsWith(const CHAR8* str, const CHAR8* value, StringCulture culture = InvariantCulture);
		static const BOOLEAN Contains(const CHAR8* str, const CHAR8* value, StringCulture culture = InvariantCulture);
		static const BOOLEAN IsNullOrEmpty(const CHAR8* str);
		static const BOOLEAN IsNullOrWhiteSpace(const CHAR8* str);
	};
}