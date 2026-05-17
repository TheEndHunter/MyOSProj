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
		const static CHAR16 NewLineChar[2];
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

		static CHAR16* ToString(const Efi::Guid guid);
		static const CHAR16* ToString(const Efi::Status status);
		static const CHAR16* ToString(const Common::System::MemoryManagement::AllocatorStatus status);
		static CHAR16* ToString(const INT16 value);
		static CHAR16* ToString(const INT32 value);
		static CHAR16* ToString(const INT64 value);
		static CHAR16* ToString(const INT8 value);

		static CHAR16* ToString(const UINT16 value);
		static CHAR16* ToString(const UINT32 value);
		static CHAR16* ToString(const UINT64 value);
		static CHAR16* ToString(const UINT8 value);
		static CHAR16* ToString(const VOID_PTR ptr);
		static const CHAR16* ToString(const BOOLEAN boolean);

		/// <summary>
		/// Length of string(Including the null terminator!) so a  length of 1 is returned for a non nullptr, Empty('\0') string.
		/// </summary>
		/// <param name="str"></param>
		/// <returns></returns>
		static UINT64 Length(const CHAR16* str);
		static BOOLEAN Compare(const CHAR16* l, const CHAR16* r, StringCulture culture = InvariantCulture);
		static BOOLEAN StartsWith(const CHAR16* str, const CHAR16* value, StringCulture culture = InvariantCulture);
		static BOOLEAN EndsWith(const CHAR16* str, const CHAR16* value, StringCulture culture = InvariantCulture);
		static BOOLEAN Contains(const CHAR16* str, const CHAR16* value, StringCulture culture = InvariantCulture);
		static BOOLEAN IsNullOrEmpty(const CHAR16* str);
		static BOOLEAN IsNullOrWhiteSpace(const CHAR16* str);
		static BOOLEAN IsNullEmptyOrWhiteSpace(const CHAR16* str);

	/// Returns heap-allocated UTF-16 string. Caller must free with delete[].
	static CHAR16* FromCharArray(CHAR16 arr[], UINT64 Length);

	/// Convert UTF-8 bytes to UTF-16. Returns heap-allocated buffer (caller must delete[]).
	/// Use the buffer overload to avoid allocation: it writes into caller-provided buffer and returns written units.
	static CHAR16* FromUTF8String(const CHAR8* str);

	/// Buffer overload: writes UTF-16 code units into outBuffer. Returns Optional<writtenUnits> or empty Optional when buffer too small or input null.
	static Common::System::Optional<UINT64> FromUTF8String(const CHAR8* src, CHAR16* outBuffer, UINT64 outBufferSize);

	/// Convert C string (ASCII) to UTF-16. Returns heap-allocated buffer (caller must delete[]).
	static CHAR16* FromCString(const CHAR* str);

	/// Buffer overload for FromCString: writes UTF-16 to outBuffer and returns written length or empty Optional if buffer too small.
	static Common::System::Optional<UINT64> FromCString(const CHAR* src, CHAR16* outBuffer, UINT64 outBufferSize);

		/// Returns a heap-allocated UCS-2-safe CHAR16 buffer where any surrogate pairs or non-BMP
		/// code points are replaced by U+FFFD. Caller must delete[] the returned buffer.
		static CHAR16* SanitizeToUcs2(const CHAR16* src);

		/// Convert UTF-16 to UTF-8. Returns heap-allocated CHAR8* (caller must delete[]).
		static CHAR8* ToUTF8String(const CHAR16* str);

		/// Buffer overload: writes UTF-8 bytes into outBuffer. Returns Optional<writtenBytes> or empty Optional when buffer too small or input null.
		static Common::System::Optional<UINT64> ToUTF8String(const CHAR16* src, CHAR8* outBuffer, UINT64 outBufferSize);

		/// Narrow UTF-16 to C string (CHAR) lossy: characters > 0xFF replaced with '?'. Returns heap-allocated CHAR* (caller must delete[]).
		static CHAR* ToCString(const CHAR16* str);

		/// Buffer overload for ToCString: writes narrow bytes to outBuffer and returns written length or empty Optional if buffer too small.
		static Common::System::Optional<UINT64> ToCString(const CHAR16* src, CHAR* outBuffer, UINT64 outBufferSize);

	static void FreeSplit(CHAR16** arr, UINT64 count);
	static void Free(CHAR16* str);

        static Common::System::Optional<UINT64> IndexOf(const CHAR16* str, const CHAR16* value, UINT64 startIndex = 0, StringCulture culture = InvariantCulture);
        static Common::System::Optional<UINT64> IndexOf(const CHAR16* str, const CHAR16 value, UINT64 startIndex = 0, StringCulture culture = InvariantCulture);
        static Common::System::Optional<UINT64> LastIndexOf(const CHAR16* str, const CHAR16* value, UINT64 startIndex = 0, StringCulture culture = InvariantCulture);
        static Common::System::Optional<UINT64> LastIndexOf(const CHAR16* str, const CHAR16 value, UINT64 startIndex = 0, StringCulture culture = InvariantCulture);

		static CHAR16** Split(const CHAR16* str, const CHAR16* separator, OUT UINT64* count);
		static CHAR16** Split(const CHAR16* str, const CHAR16 separator, OUT UINT64* count);
		static CHAR16* Join(const CHAR16** str, const CHAR16* separator, UINT64 count);
		static CHAR16* Join(const CHAR16** str, const CHAR16 separator, UINT64 count);
	};
}


