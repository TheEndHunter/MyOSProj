#pragma once
#include "TypeDefs.h"
#include <System/Environment/Unicode/UTFTemplate.h>

namespace Common::System::Environment
{
	template<>
	struct UTF<CHAR>
	{
	public:
		const static CHAR  NULL = '\0';
		const static CHAR NewLine[3];
		const static CHAR  Space = ' ';
		const static CHAR  Tab = '\t';
		const static CHAR  Backspace = '\b';

		static CHAR* ToHex(const INT16 value);
		static CHAR* ToHex(const INT32 value);
		static CHAR* ToHex(const INT64 value);
		static CHAR* ToHex(const INT8 valueC);

		static CHAR* ToHex(const UINT16 value);
		static CHAR* ToHex(const UINT32 value);
		static CHAR* ToHex(const UINT64 value);
		static CHAR* ToHex(const UINT8 value);
		static CHAR* ToHex(const VOID_PTR ptrC);

		static CHAR* ToString(const EFI::EFI_GUID guid);
		static CHAR* ToString(const EFI::EFI_STATUS status);
		static CHAR* ToString(const Common::System::MemoryManagement::AllocatorStatus status);
		static CHAR* ToString(const INT16 value);
		static CHAR* ToString(const INT32 value);
		static CHAR* ToString(const INT64 value);
		static CHAR* ToString(const INT8 valueC);

		static CHAR* ToString(const UINT16 value);
		static CHAR* ToString(const UINT32 value);
		static CHAR* ToString(const UINT64 value);
		static CHAR* ToString(const UINT8 value);
		static CHAR* ToString(const VOID_PTR ptr);
		static CHAR* ToString(const BOOLEAN boolean);

		static UINT64 Length(const CHAR* str);
		static BOOLEAN Compare(const CHAR* l, const CHAR* r, StringCulture culture = InvariantCulture);
		static BOOLEAN StartsWith(const CHAR* str, const CHAR* value, StringCulture culture = InvariantCulture);
		static BOOLEAN EndsWith(const CHAR* str, const CHAR* value, StringCulture culture = InvariantCulture);
		static BOOLEAN Contains(const CHAR* str, const CHAR* value, StringCulture culture = InvariantCulture);
		static BOOLEAN IsNullOrEmpty(const CHAR* str);
		static BOOLEAN IsNullOrWhiteSpace(const CHAR* str);

		static CHAR* FromCharArray(CHAR arr[], UINT64 Length);
		static CHAR* FromUTF16String(const CHAR16* str);
		static CHAR* FromUTF8String(const CHAR8* str);
	};
}