#pragma once
#include "TypeDefs.h"
#include <EFI_GUID.h>
#include <EFI_STATUS.h>
#include <Environment/StringCulture.h>
#include <System/MemoryManagement/AllocatorStatus.h>

namespace Common::Environment
{
	class UTF16
	{
	public:
		const static CHAR16  NULL = u'\0';
		const static CHAR16* NewLine;
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
		static BOOLEAN Compare(const CHAR16* l,const CHAR16* r, StringCulture culture = InvariantCulture);
		static BOOLEAN StartsWith(const CHAR16* str, const CHAR16* value, StringCulture culture = InvariantCulture);
		static BOOLEAN EndsWith(const CHAR16* str, const CHAR16* value, StringCulture culture = InvariantCulture);
		static BOOLEAN Contains(const CHAR16* str, const CHAR16* value, StringCulture culture = InvariantCulture);
		static BOOLEAN IsNullOrEmpty(const CHAR16* str);
		static BOOLEAN IsNullOrWhiteSpace(const CHAR16* str);
		static BOOLEAN IsNullEmptyOrWhiteSpace(const CHAR16* str);

		static CHAR16* FromCharArray(CHAR16 arr[], UINT64 Length);
		static CHAR16* FromUTF8String(const CHAR8* str);
		static CHAR16* FromCString(const CCHAR* str);
	};

	class UTF8
	{
	public:
		const static CHAR8  NULL = u8'\0';
		const static CHAR8* NewLine;
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
		static CHAR8* FromCString(const CCHAR* str);
	};

	struct CString
	{
	public:
		const static CCHAR  NULL = '\0';
		const static CCHAR* NewLine;
		const static CCHAR  Space = ' ';
		const static CCHAR  Tab = '\t';
		const static CCHAR  Backspace = '\b';

		static CCHAR* ToHex(const INT16 value);
		static CCHAR* ToHex(const INT32 value);
		static CCHAR* ToHex(const INT64 value);
		static CCHAR* ToHex(const INT8 valueC);

		static CCHAR* ToHex(const UINT16 value);
		static CCHAR* ToHex(const UINT32 value);
		static CCHAR* ToHex(const UINT64 value);
		static CCHAR* ToHex(const UINT8 value);
		static CCHAR* ToHex(const VOID_PTR ptrC);

		static CCHAR* ToString(const EFI::EFI_GUID guid);
		static CCHAR* ToString(const EFI::EFI_STATUS status);
		static CCHAR* ToString(const Common::System::MemoryManagement::AllocatorStatus status);
		static CCHAR* ToString(const INT16 value);
		static CCHAR* ToString(const INT32 value);
		static CCHAR* ToString(const INT64 value);
		static CCHAR* ToString(const INT8 valueC);

		static CCHAR* ToString(const UINT16 value);
		static CCHAR* ToString(const UINT32 value);
		static CCHAR* ToString(const UINT64 value);
		static CCHAR* ToString(const UINT8 value);
		static CCHAR* ToString(const VOID_PTR ptr);
		static CCHAR* ToString(const BOOLEAN boolean);

		static UINT64 Length(const CCHAR* str);
		static BOOLEAN Compare(const CCHAR* l, const CCHAR* r, StringCulture culture = InvariantCulture);
		static BOOLEAN StartsWith(const CCHAR* str, const CCHAR* value, StringCulture culture = InvariantCulture);
		static BOOLEAN EndsWith(const CCHAR* str, const CCHAR* value, StringCulture culture = InvariantCulture);
		static BOOLEAN Contains(const CCHAR* str, const CCHAR* value, StringCulture culture = InvariantCulture);
		static BOOLEAN IsNullOrEmpty(const CCHAR* str);
		static BOOLEAN IsNullOrWhiteSpace(const CCHAR* str);

		static CCHAR* FromCharArray(CCHAR arr[], UINT64 Length);
		static CCHAR* FromUTF16String(const CHAR16* str);
		static CCHAR* FromUTF8String(const CHAR8* str);
	};
}