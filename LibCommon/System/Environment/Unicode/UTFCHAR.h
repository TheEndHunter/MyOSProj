#pragma once
#include "TypeDefs.h"
#include <System/Optional.h>
#include <System/Environment/Unicode/UTFTemplate.h>

namespace Common::System::Environment
{
	template<>
	struct UTF<CHAR>
	{
	public:
		const static CHAR  NULL = '\0';
		const static CHAR NewLine[3];
		const static CHAR NewLineChar[2];
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

		static CHAR* ToString(const Efi::Guid guid);
		static const CHAR* ToString(const Efi::Status status);
		static const CHAR* ToString(const Common::System::MemoryManagement::AllocatorStatus status);
		static CHAR* ToString(const INT16 value);
		static CHAR* ToString(const INT32 value);
		static CHAR* ToString(const INT64 value);
		static CHAR* ToString(const INT8 valueC);

		static CHAR* ToString(const UINT16 value);
		static CHAR* ToString(const UINT32 value);
		static CHAR* ToString(const UINT64 value);
		static CHAR* ToString(const UINT8 value);
		static CHAR* ToString(const VOID_PTR ptr);
		static const CHAR* ToString(const BOOLEAN boolean);

        static UINT64 Length(const CHAR* str);
		static Common::System::Optional<UINT64> IndexOf(const CHAR* str, const CHAR* value, UINT64 startIndex = 0, StringCulture culture = InvariantCulture);
		static Common::System::Optional<UINT64> IndexOf(const CHAR* str, const CHAR value, UINT64 startIndex = 0, StringCulture culture = InvariantCulture);
		static Common::System::Optional<UINT64> LastIndexOf(const CHAR* str, const CHAR* value, UINT64 startIndex = 0, StringCulture culture = InvariantCulture);
		static Common::System::Optional<UINT64> LastIndexOf(const CHAR* str, const CHAR value, UINT64 startIndex = 0, StringCulture culture = InvariantCulture);
		static BOOLEAN Compare(const CHAR* l, const CHAR* r, StringCulture culture = InvariantCulture);
		static BOOLEAN StartsWith(const CHAR* str, const CHAR* value, StringCulture culture = InvariantCulture);
		static BOOLEAN EndsWith(const CHAR* str, const CHAR* value, StringCulture culture = InvariantCulture);
		static BOOLEAN Contains(const CHAR* str, const CHAR* value, StringCulture culture = InvariantCulture);
		static BOOLEAN IsNullOrEmpty(const CHAR* str);
		static BOOLEAN IsNullOrWhiteSpace(const CHAR* str);

		static CHAR* FromCharArray(CHAR arr[], UINT64 Length);
	/// Convert UTF-16 string to UTF-8 bytes. Returns heap-allocated buffer (caller must delete[]).
	/// Use the buffer overload to avoid allocation.
	static CHAR* FromUTF16String(const CHAR16* str);
	/// Validate and normalize UTF-8 into CHAR*; returns heap-allocated buffer (caller must delete[]).
	/// Buffer overload returns Optional(length) and writes to caller-provided buffer.
	static CHAR* FromUTF8String(const CHAR8* str);

	static Common::System::Optional<UINT64> FromUTF16String(const CHAR16* src, CHAR* outBuffer, UINT64 outBufferSize);
	static Common::System::Optional<UINT64> FromUTF8String(const CHAR8* src, CHAR* outBuffer, UINT64 outBufferSize);

	static void FreeSplit(CHAR** arr, UINT64 count);
	static void Free(CHAR* str);
	};
}