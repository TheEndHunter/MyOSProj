#pragma once
#include "TypeDefs.h"
#include <EFI_GUID.h>
#include <EFI_STATUS.h>

namespace Common::Enviroment
{
	enum StringComparison
	{
		//Compare strings using culture - sensitive sort rules and the current culture.
		CurrentCulture = 0,
		//Compare strings using culture - sensitive sort rules, the current culture, and ignoring the case of the strings being compared.
		CurrentCultureIgnoreCase = 1,
		//Compare strings using culture - sensitive sort rules and the invariant culture.
		InvariantCulture = 2,
		//Compare strings using culture - sensitive sort rules, the invariant culture, and ignoring the case of the strings being compared.
		InvariantCultureIgnoreCase = 3,
		//Compare strings using ordinal(binary) sort rules.
		Ordinal = 4,
		//Compare strings using ordinal(binary) sort rules and ignoring the case of the strings being compared.
		OrdinalIgnoreCase = 5, 
	};

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
		static const CHAR16* ToHex(const VOID_PTR ptr);
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
		static const CHAR16* ToString(const VOID_PTR ptr);

		static const UINT64 Length(const CHAR16* str);
		static const BOOLEAN Compare(const CHAR16* l,const CHAR16* r, StringComparison mode = InvariantCulture);
		static const BOOLEAN StartsWith(const CHAR16* str, const CHAR16* value, StringComparison mode = InvariantCulture);
		static const BOOLEAN EndsWith(const CHAR16* str, const CHAR16* value, StringComparison mode = InvariantCulture);
		static const BOOLEAN Contains(const CHAR16* str, const CHAR16* value, StringComparison mode = InvariantCulture);
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

		static const CHAR8* ToHex(const INT16 b);
		static const CHAR8* ToHex(const INT32 b);
		static const CHAR8* ToHex(const INT64 b);
		static const CHAR8* ToHex(const INT8 b);
		static const CHAR8* ToHex(const UINT16 b);
		static const CHAR8* ToHex(const UINT32 b);
		static const CHAR8* ToHex(const UINT64 b);
		static const CHAR8* ToHex(const UINT8 b);
		static const CHAR8* ToHex(const VOID_PTR ptr);
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
		static const CHAR8* ToString(const VOID_PTR ptr);

		static const UINT64 Length(const CHAR8* str);
		static const BOOLEAN Compare(const CHAR8* l, const CHAR8* r, StringComparison mode = InvariantCulture);
		static const BOOLEAN StartsWith(const CHAR8* str, const CHAR8* value, StringComparison mode = InvariantCulture);
		static const BOOLEAN EndsWith(const CHAR8* str, const CHAR8* value, StringComparison mode = InvariantCulture);
		static const BOOLEAN Contains(const CHAR8* str, const CHAR8* value, StringComparison mode = InvariantCulture);
		static const BOOLEAN IsNullOrEmpty(const CHAR8* str);
		static const BOOLEAN IsNullOrWhiteSpace(const CHAR8* str);
	};
}