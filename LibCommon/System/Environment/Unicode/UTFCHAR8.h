#pragma once
#include <TypeDefs.h>
#include <System/Environment/Unicode/UTFTemplate.h>


namespace Common::System::Environment
{
	template<>
	class UTF<CHAR8>
	{
	public:
		const static CHAR8  NULL = u8'\0';
		const static CHAR8 NewLine[3];
		const static CHAR8  Space = u8' ';
		const static CHAR8  Tab = u8'\t';
		const static CHAR8  Backspace = u8'\b';

		static CHAR8* ToHex(const INT16 value);
		static CHAR8* ToHex(const INT32 value);
		static CHAR8* ToHex(const INT64 value);
		static CHAR8* ToHex(const INT8 value);
		static CHAR8* ToHex(const UINT16 value);
		static CHAR8* ToHex(const UINT32 value);
		static CHAR8* ToHex(const UINT64 value);
		static CHAR8* ToHex(const UINT8 value);
		static CHAR8* ToHex(const VOID_PTR ptr);

		static CHAR8* ToString(const EFI::EFI_GUID guid);
		static CHAR8* ToString(const EFI::EFI_STATUS status);
		static CHAR8* ToString(const Common::System::MemoryManagement::AllocatorStatus status);
		static CHAR8* ToString(const INT16 value);
		static CHAR8* ToString(const INT32 value);
		static CHAR8* ToString(const INT64 value);
		static CHAR8* ToString(const INT8 value);
		static CHAR8* ToString(const UINT16 value);
		static CHAR8* ToString(const UINT32 value);
		static CHAR8* ToString(const UINT64 value);
		static CHAR8* ToString(const UINT8 value);
		static CHAR8* ToString(const VOID_PTR ptr);
		static CHAR8* ToString(const BOOLEAN boolean);

		static UINT64 Length(const CHAR8* str);
		static BOOLEAN Compare(const CHAR8* l, const CHAR8* r, StringCulture culture = InvariantCulture);
		static BOOLEAN StartsWith(const CHAR8* str, const CHAR8* value, StringCulture culture = InvariantCulture);
		static BOOLEAN EndsWith(const CHAR8* str, const CHAR8* value, StringCulture culture = InvariantCulture);
		static BOOLEAN Contains(const CHAR8* str, const CHAR8* value, StringCulture culture = InvariantCulture);
		static BOOLEAN IsNullOrEmpty(const CHAR8* str);
		static BOOLEAN IsNullOrWhiteSpace(const CHAR8* str);
		static BOOLEAN IsNullEmptyOrWhiteSpace(const CHAR8* str);

		static CHAR8* FromCharArray(CHAR8 arr[], UINT64 Length);
		static CHAR8* FromUTF16String(const CHAR16* str);
		static CHAR8* FromCString(const CHAR* str);
	};
}


