#pragma once
#include <TypeDefs.h>
#include <System/Environment/Unicode/UTFTemplate.h>

namespace Common::System::Environment
{
    template<>
    class UTF<CHAR32>
    {
    public:
        const static CHAR32  NULL;
        const static CHAR32 NewLine[3];
        const static CHAR32 NewLineChar[2];
        const static CHAR32  Space;
        const static CHAR32  Tab;
        const static CHAR32  Backspace;

        static CHAR32* FromCharArray(CHAR32 arr[], UINT64 Length);
        static CHAR32* FromUTF8String(const CHAR8* str);
        static CHAR32* FromUTF16String(const CHAR16* str);
        static CHAR32* FromCString(const CHAR* str);

        static Common::System::Optional<UINT64> FromUTF8String(const CHAR8* src, CHAR32* outBuffer, UINT64 outBufferSize);
        static Common::System::Optional<UINT64> FromUTF16String(const CHAR16* src, CHAR32* outBuffer, UINT64 outBufferSize);
        static Common::System::Optional<UINT64> FromCString(const CHAR* src, CHAR32* outBuffer, UINT64 outBufferSize);

        static UINT64 Length(const CHAR32* str);
        static BOOLEAN Compare(const CHAR32* l, const CHAR32* r, StringCulture culture);
        static BOOLEAN StartsWith(const CHAR32* str, const CHAR32* value, StringCulture culture);
        static BOOLEAN EndsWith(const CHAR32* str, const CHAR32* value, StringCulture culture);
        static BOOLEAN Contains(const CHAR32* str, const CHAR32* value, StringCulture culture);
        static BOOLEAN IsNullOrEmpty(const CHAR32* str);
        static BOOLEAN IsNullOrWhiteSpace(const CHAR32* str);
        static BOOLEAN IsNullEmptyOrWhiteSpace(const CHAR32* str);

        static Common::System::Optional<UINT64> IndexOf(const CHAR32* str, const CHAR32* value, UINT64 startIndex, StringCulture culture);
        static Common::System::Optional<UINT64> IndexOf(const CHAR32* str, const CHAR32 value, UINT64 startIndex, StringCulture culture);
        static Common::System::Optional<UINT64> LastIndexOf(const CHAR32* str, const CHAR32* value, UINT64 startIndex, StringCulture culture);
        static Common::System::Optional<UINT64> LastIndexOf(const CHAR32* str, const CHAR32 value, UINT64 startIndex, StringCulture culture);

        static CHAR32** Split(const CHAR32* str, const CHAR32* separator, OUT UINT64* count);
        static CHAR32** Split(const CHAR32* str, const CHAR32 separator, OUT UINT64* count);
        static CHAR32* Join(const CHAR32** str, const CHAR32* separator, UINT64 count);
        static CHAR32* Join(const CHAR32** str, const CHAR32 separator, UINT64 count);

	static void FreeSplit(CHAR32** arr, UINT64 count);
	static void Free(CHAR32* str);
    };
}
