#pragma once
#include <TypeDefs.h>
#include <System/Environment/Unicode/UTFTemplate.h>

namespace Common::System::Environment
{
	template<>
	class UTF<CHAR16>
	{
	public:
		const static CHAR16  NULL = u'\0';
		const static CHAR16 NewLine[3];
		const static CHAR16  Space = u' ';
		const static CHAR16  Tab = u'\t';
		const static CHAR16  Backspace = u'\b';

		static CHAR16* ToHex(const INT16 value);
		static CHAR16* ToHex(const INT32 value);
		static CHAR16* ToHex(const INT64 value);
		static CHAR16* ToHex(const INT8 value);

		static CHAR16* ToHex(const UINT16 value);
		static CHAR16* ToHex(const UINT32 value);
		static CHAR16* ToHex(const UINT64 value);
		static CHAR16* ToHex(const UINT8 value);
		static CHAR16* ToHex(const VOID_PTR ptr);

		static CHAR16* ToString(const EFI::EFI_GUID guid);
		static CHAR16* ToString(const EFI::EFI_STATUS status);
		static CHAR16* ToString(const Common::System::MemoryManagement::AllocatorStatus status);
		static CHAR16* ToString(const INT16 value);
		static CHAR16* ToString(const INT32 value);
		static CHAR16* ToString(const INT64 value);
		static CHAR16* ToString(const INT8 value);

		static CHAR16* ToString(const UINT16 value);
		static CHAR16* ToString(const UINT32 value);
		static CHAR16* ToString(const UINT64 value);
		static CHAR16* ToString(const UINT8 value);
		static CHAR16* ToString(const VOID_PTR ptr);
		static CHAR16* ToString(const BOOLEAN boolean);

		static UINT64 Length(const CHAR16* str);
		static BOOLEAN Compare(const CHAR16* l, const CHAR16* r, StringCulture culture = InvariantCulture);
		static BOOLEAN StartsWith(const CHAR16* str, const CHAR16* value, StringCulture culture = InvariantCulture);
		static BOOLEAN EndsWith(const CHAR16* str, const CHAR16* value, StringCulture culture = InvariantCulture);
		static BOOLEAN Contains(const CHAR16* str, const CHAR16* value, StringCulture culture = InvariantCulture);
		static BOOLEAN IsNullOrEmpty(const CHAR16* str);
		static BOOLEAN IsNullOrWhiteSpace(const CHAR16* str);
		static BOOLEAN IsNullEmptyOrWhiteSpace(const CHAR16* str);

		static CHAR16* FromCharArray(CHAR16 arr[], UINT64 Length);
		static CHAR16* FromUTF8String(const CHAR8* str);
		static CHAR16* FromCString(const CHAR* str);

		static INT64 IndexOf(const CHAR16* str, const CHAR16* value, UINT64 startIndex = 0, StringCulture culture = InvariantCulture);
		static INT64 IndexOf(const CHAR16* str, const CHAR16 value, UINT64 startIndex = 0, StringCulture culture = InvariantCulture);
		static INT64 LastIndexOf(const CHAR16* str, const CHAR16* value, UINT64 startIndex = 0, StringCulture culture = InvariantCulture);
		static INT64 LastIndexOf(const CHAR16* str, const CHAR16 value, UINT64 startIndex = 0, StringCulture culture = InvariantCulture);

		static CHAR16** Split(const CHAR16* str, const CHAR16* separator, OUT UINT64* count);
		static CHAR16** Split(const CHAR16* str, const CHAR16 separator, OUT UINT64* count);
		static CHAR16* Join(const CHAR16** str, const CHAR16* separator, UINT64 count);
		static CHAR16* Join(const CHAR16** str, const CHAR16 separator, UINT64 count);
	};
}


