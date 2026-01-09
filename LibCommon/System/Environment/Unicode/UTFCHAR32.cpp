#include <System/Environment/Unicode/UTFCHAR32.h>
#include <System/Environment/Unicode/UTFHelpers.h>

namespace Common::System::Environment
{
    const CHAR32 UTF<CHAR32>::NULL = 0;
    const CHAR32 UTF<CHAR32>::NewLine[3] = { '\r', '\n', 0 };
    const CHAR32 UTF<CHAR32>::NewLineChar[2] = { '\r', '\n' };
    const CHAR32 UTF<CHAR32>::Space = ' ';
    const CHAR32 UTF<CHAR32>::Tab = '\t';
    const CHAR32 UTF<CHAR32>::Backspace = '\b';

    UINT64 UTF<CHAR32>::Length(const CHAR32* str)
    {
        return UTFHelpers::Length<CHAR32>(str);
    }


    void UTF<CHAR32>::FreeSplit(CHAR32** arr, UINT64 count)
    {
        if (arr == nullptr) return;
        for (UINT64 i = 0; i < count; ++i) if (arr[i] != nullptr) delete[] arr[i];
        delete[] arr;
    }

    void UTF<CHAR32>::Free(CHAR32* str)
    {
        if (str != nullptr) delete[] str;
    }

    CHAR32* UTF<CHAR32>::FromCharArray(CHAR32 arr[], UINT64 Length)
    {
        if (arr == nullptr) return nullptr;
        CHAR32* result = new CHAR32[Length + 1];
        for (UINT64 i = 0; i < Length; ++i) result[i] = arr[i];
        result[Length] = 0;
        return result;
    }

    CHAR32* UTF<CHAR32>::FromCString(const CHAR* str)
    {
        if (str == nullptr) return nullptr;
        UINT64 len = UTFHelpers::Length<CHAR>(str);
        CHAR32* result = new CHAR32[len + 1];
        for (UINT64 i = 0; i < len; ++i) result[i] = (CHAR32)(unsigned char)str[i];
        result[len] = 0;
        return result;
    }

    CHAR32* UTF<CHAR32>::FromUTF8String(const CHAR8* str)
    {
        if (str == nullptr) return nullptr;
        UINT64 srcLen = UTF<CHAR8>::Length(str);
        // Count code points
        UINT64 count = 0;
        for (UINT64 i = 0; i < srcLen; )
        {
            unsigned char c = (unsigned char)str[i];
            if (c <= 0x7F) { ++count; ++i; }
            else if ((c & 0xE0) == 0xC0) { ++count; i += 2; }
            else if ((c & 0xF0) == 0xE0) { ++count; i += 3; }
            else if ((c & 0xF8) == 0xF0) { ++count; i += 4; }
            else { ++count; ++i; }
        }
        CHAR32* result = new CHAR32[count + 1];
        UINT64 out = 0;
        for (UINT64 i = 0; i < srcLen; )
        {
            unsigned char c = (unsigned char)str[i];
            UINT32 codepoint = 0;
            UINT64 remaining = srcLen - i;
            if (c <= 0x7F) { codepoint = c; i += 1; }
            else if ((c & 0xE0) == 0xC0 && remaining >= 2)
            {
                unsigned char c1 = (unsigned char)str[i+1];
                if ((c1 & 0xC0) == 0x80) codepoint = ((c & 0x1F) << 6) | (c1 & 0x3F);
                else codepoint = 0xFFFD;
                i += 2;
            }
            else if ((c & 0xF0) == 0xE0 && remaining >= 3)
            {
                unsigned char c1 = (unsigned char)str[i+1];
                unsigned char c2 = (unsigned char)str[i+2];
                if (((c1 & 0xC0) == 0x80) && ((c2 & 0xC0) == 0x80)) codepoint = ((c & 0x0F) << 12) | ((c1 & 0x3F) << 6) | (c2 & 0x3F);
                else codepoint = 0xFFFD;
                i += 3;
            }
            else if ((c & 0xF8) == 0xF0 && remaining >= 4)
            {
                unsigned char c1 = (unsigned char)str[i+1];
                unsigned char c2 = (unsigned char)str[i+2];
                unsigned char c3 = (unsigned char)str[i+3];
                if (((c1 & 0xC0) == 0x80) && ((c2 & 0xC0) == 0x80) && ((c3 & 0xC0) == 0x80)) codepoint = ((c & 0x07) << 18) | ((c1 & 0x3F) << 12) | ((c2 & 0x3F) << 6) | (c3 & 0x3F);
                else codepoint = 0xFFFD;
                i += 4;
            }
            else { codepoint = 0xFFFD; i += 1; }
            result[out++] = (CHAR32)codepoint;
        }
        result[out] = 0;
        return result;
    }

    Common::System::Optional<UINT64> UTF<CHAR32>::FromUTF16String(const CHAR16* src, CHAR32* outBuffer, UINT64 outBufferSize)
    {
        if (src == nullptr || outBuffer == nullptr) return Common::System::Optional<UINT64>();
        UINT64 srcLen = UTF<CHAR16>::Length(src);
        UINT64 needed = 0;
        for (UINT64 i = 0; i < srcLen; ++i)
        {
            UINT16 w = (UINT16)src[i];
            if (w >= 0xD800 && w <= 0xDBFF)
            {
                if (i + 1 < srcLen)
                {
                    UINT16 w2 = (UINT16)src[i+1];
                    if (w2 >= 0xDC00 && w2 <= 0xDFFF) { ++needed; ++i; continue; }
                }
                ++needed; // replacement
            }
            else ++needed;
        }
        if (outBufferSize < needed + 1) return Common::System::Optional<UINT64>();
        UINT64 out = 0;
        for (UINT64 i = 0; i < srcLen; ++i)
        {
            UINT16 w = (UINT16)src[i];
            if (w >= 0xD800 && w <= 0xDBFF)
            {
                if (i + 1 < srcLen)
                {
                    UINT16 w2 = (UINT16)src[i+1];
                    if (w2 >= 0xDC00 && w2 <= 0xDFFF)
                    {
                        UINT32 codepoint = 0x10000 + (((UINT32)w - 0xD800) << 10) + ((UINT32)w2 - 0xDC00);
                        outBuffer[out++] = (CHAR32)codepoint; ++i; continue;
                    }
                }
                outBuffer[out++] = 0xFFFD;
            }
            else outBuffer[out++] = (CHAR32)w;
        }
        outBuffer[out] = 0;
        return Common::System::Optional<UINT64>(out);
    }

    Common::System::Optional<UINT64> UTF<CHAR32>::FromUTF8String(const CHAR8* src, CHAR32* outBuffer, UINT64 outBufferSize)
    {
        if (src == nullptr || outBuffer == nullptr) return Common::System::Optional<UINT64>();
        UINT64 srcLen = UTF<CHAR8>::Length(src);
        UINT64 needed = 0;
        for (UINT64 i = 0; i < srcLen; )
        {
            unsigned char c = (unsigned char)src[i];
            if (c <= 0x7F) { ++needed; ++i; }
            else if ((c & 0xE0) == 0xC0) { ++needed; i += 2; }
            else if ((c & 0xF0) == 0xE0) { ++needed; i += 3; }
            else if ((c & 0xF8) == 0xF0) { ++needed; i += 4; }
            else { ++needed; ++i; }
        }
        if (outBufferSize < needed + 1) return Common::System::Optional<UINT64>();
        UINT64 out = 0;
        for (UINT64 i = 0; i < srcLen; )
        {
            unsigned char c = (unsigned char)src[i];
            UINT32 codepoint = 0;
            UINT64 remaining = srcLen - i;
            if (c <= 0x7F) { codepoint = c; i += 1; }
            else if ((c & 0xE0) == 0xC0 && remaining >= 2)
            {
                unsigned char c1 = (unsigned char)src[i+1];
                if ((c1 & 0xC0) == 0x80) codepoint = ((c & 0x1F) << 6) | (c1 & 0x3F);
                else codepoint = 0xFFFD;
                i += 2;
            }
            else if ((c & 0xF0) == 0xE0 && remaining >= 3)
            {
                unsigned char c1 = (unsigned char)src[i+1];
                unsigned char c2 = (unsigned char)src[i+2];
                if (((c1 & 0xC0) == 0x80) && ((c2 & 0xC0) == 0x80)) codepoint = ((c & 0x0F) << 12) | ((c1 & 0x3F) << 6) | (c2 & 0x3F);
                else codepoint = 0xFFFD;
                i += 3;
            }
            else if ((c & 0xF8) == 0xF0 && remaining >= 4)
            {
                unsigned char c1 = (unsigned char)src[i+1];
                unsigned char c2 = (unsigned char)src[i+2];
                unsigned char c3 = (unsigned char)src[i+3];
                if (((c1 & 0xC0) == 0x80) && ((c2 & 0xC0) == 0x80) && ((c3 & 0xC0) == 0x80)) codepoint = ((c & 0x07) << 18) | ((c1 & 0x3F) << 12) | ((c2 & 0x3F) << 6) | (c3 & 0x3F);
                else codepoint = 0xFFFD;
                i += 4;
            }
            else { codepoint = 0xFFFD; i += 1; }
            outBuffer[out++] = (CHAR32)codepoint;
        }
        outBuffer[out] = 0;
        return Common::System::Optional<UINT64>(out);
    }

    constexpr const CHAR32 _UTF32_WHITESPACECHARS[] = { 0x0009,0x000A,0x000B,0x000C,0x000D,0x0020,0x0085,0x00A0,0x1680,0x2000,0x2001,0x2003,0x2004,0x2005,0x2006,0x2007,0x2008,0x2009,0x200A,0x2028,0x2029,0x202F,0x205F,0x3000,0x180E,0x200B,0x200C,0x200D,0x2060,0xFEFF };
    constexpr const UINT64 _UTF32_WHITESPACECHARS_LEN = sizeof(_UTF32_WHITESPACECHARS) / sizeof(CHAR32);

    BOOLEAN UTF<CHAR32>::Compare(const CHAR32* l, const CHAR32* r, StringCulture culture)
    {
        UINT64 lLength = Length(l);
        UINT64 rLength = Length(r);

        if (lLength != rLength)
        {
            return FALSE;
        }

        BOOLEAN lBool = IsNullOrEmpty(l);
        BOOLEAN rBool = IsNullOrEmpty(r);

        if (lBool == rBool)
        {
            return TRUE;
        }

        switch (culture)
        {
        case Common::System::Environment::InvariantCulture:
        case Common::System::Environment::CurrentCulture:
        case Common::System::Environment::Ordinal:
        {
            for (UINT64 index = 0; index < lLength; index++)
            {
                if (l[index] != r[index])
                {
                    return FALSE;
                }
            }
            return TRUE;
        }
        case Common::System::Environment::InvariantCultureIgnoreCase:
        case Common::System::Environment::CurrentCultureIgnoreCase:
        case Common::System::Environment::OrdinalIgnoreCase:
        {
            for (UINT64 index = 0; index < lLength; index++)
            {
                CHAR32 lChar = l[index];
                CHAR32 rChar = r[index];
                if (lChar >= 'a' && lChar <= 'z') lChar -= 32;
                if (rChar >= 'a' && rChar <= 'z') rChar -= 32;
                if (lChar != rChar) return FALSE;
            }
            return TRUE;
        }
        default:
            return FALSE;
        }
    }

    BOOLEAN UTF<CHAR32>::StartsWith(const CHAR32* str, const CHAR32* value, StringCulture culture)
    {
        if (IsNullOrEmpty(str) && IsNullOrEmpty(value)) return TRUE;
        if (IsNullOrEmpty(str) || IsNullOrEmpty(value)) return FALSE;

        UINT64 strLength = Length(str);
        UINT64 valueLength = Length(value);
        if (strLength < valueLength) return FALSE;

        switch (culture)
        {
        case Common::System::Environment::InvariantCulture:
        case Common::System::Environment::CurrentCulture:
        case Common::System::Environment::Ordinal:
            for (UINT64 index = 0; index < valueLength; index++) if (str[index] != value[index]) return FALSE;
            return TRUE;
        case Common::System::Environment::InvariantCultureIgnoreCase:
        case Common::System::Environment::CurrentCultureIgnoreCase:
        case Common::System::Environment::OrdinalIgnoreCase:
            for (UINT64 index = 0; index < valueLength; index++) {
                CHAR32 lChar = str[index]; CHAR32 rChar = value[index];
                if (lChar >= 'a' && lChar <= 'z') lChar -= 32;
                if (rChar >= 'a' && rChar <= 'z') rChar -= 32;
                if (lChar != rChar) return FALSE;
            }
            return TRUE;
        default:
            return FALSE;
        }
    }

    BOOLEAN UTF<CHAR32>::EndsWith(const CHAR32* str, const CHAR32* value, StringCulture culture)
    {
        if (IsNullOrEmpty(str) && IsNullOrEmpty(value)) return TRUE;
        if (IsNullOrEmpty(str) || IsNullOrEmpty(value)) return FALSE;

        UINT64 strLength = Length(str);
        UINT64 valueLength = Length(value);
        if (strLength < valueLength) return FALSE;

        switch (culture)
        {
        case Common::System::Environment::InvariantCulture:
        case Common::System::Environment::CurrentCulture:
        case Common::System::Environment::Ordinal:
            for (UINT64 index = 0; index < valueLength; index++) if (str[strLength - valueLength + index] != value[index]) return FALSE;
            return TRUE;
        case Common::System::Environment::InvariantCultureIgnoreCase:
        case Common::System::Environment::CurrentCultureIgnoreCase:
        case Common::System::Environment::OrdinalIgnoreCase:
            for (UINT64 index = 0; index < valueLength; index++) {
                CHAR32 lChar = str[strLength - valueLength + index]; CHAR32 rChar = value[index];
                if (lChar >= 'a' && lChar <= 'z') lChar -= 32;
                if (rChar >= 'a' && rChar <= 'z') rChar -= 32;
                if (lChar != rChar) return FALSE;
            }
            return TRUE;
        default:
            return FALSE;
        }
    }

    BOOLEAN UTF<CHAR32>::Contains(const CHAR32* str, const CHAR32* value, StringCulture culture)
    {
        if (IsNullOrEmpty(str) && IsNullOrEmpty(value)) return TRUE;
        if (IsNullOrEmpty(str) || IsNullOrEmpty(value)) return FALSE;

        UINT64 strLength = Length(str);
        UINT64 valueLength = Length(value);
        if (strLength < valueLength) return FALSE;

        switch (culture)
        {
        case Common::System::Environment::InvariantCulture:
        case Common::System::Environment::CurrentCulture:
        case Common::System::Environment::Ordinal:
            for (UINT64 index = 0; index <= strLength - valueLength; index++) {
                if (str[index] == value[0]) {
                    BOOLEAN match = TRUE;
                    for (UINT64 i = 0; i < valueLength; i++) if (str[index + i] != value[i]) { match = FALSE; break; }
                    if (match) return TRUE;
                }
            }
            return FALSE;
        case Common::System::Environment::InvariantCultureIgnoreCase:
        case Common::System::Environment::CurrentCultureIgnoreCase:
        case Common::System::Environment::OrdinalIgnoreCase:
            for (UINT64 index = 0; index <= strLength - valueLength; index++) {
                CHAR32 lChar = str[index]; CHAR32 rChar = value[0];
                if (lChar >= 'a' && lChar <= 'z') lChar -= 32;
                if (rChar >= 'a' && rChar <= 'z') rChar -= 32;
                if (lChar == rChar) {
                    BOOLEAN match = TRUE;
                    for (UINT64 i = 0; i < valueLength; i++) {
                        CHAR32 lChar2 = str[index + i]; CHAR32 rChar2 = value[i];
                        if (lChar2 >= 'a' && lChar2 <= 'z') lChar2 -= 32;
                        if (rChar2 >= 'a' && rChar2 <= 'z') rChar2 -= 32;
                        if (lChar2 != rChar2) { match = FALSE; break; }
                    }
                    if (match) return TRUE;
                }
            }
            return FALSE;
        default:
            return FALSE;
        }
    }

    BOOLEAN UTF<CHAR32>::IsNullOrEmpty(const CHAR32* str)
    {
        if (str == nullptr) return TRUE;
        if (str[0] == 0) return TRUE;
        return FALSE;
    }

    BOOLEAN UTF<CHAR32>::IsNullOrWhiteSpace(const CHAR32* str)
    {
        if (str == nullptr) return TRUE;
        for (UINT64 i = 0;; i++) {
            CHAR32 c = str[i];
            if (c == 0) break;
            BOOLEAN found = FALSE;
            for (UINT64 l = 0; l < _UTF32_WHITESPACECHARS_LEN; l++) {
                if (c == _UTF32_WHITESPACECHARS[l]) { found = TRUE; break; }
            }
            if (!found) return FALSE;
        }
        return TRUE;
    }

    BOOLEAN UTF<CHAR32>::IsNullEmptyOrWhiteSpace(const CHAR32* str)
    {
        if (str == nullptr) return TRUE;
        if (str[0] == 0) return TRUE;
        for (UINT64 i = 0;; i++) {
            CHAR32 c = str[i]; if (c == 0) break;
            BOOLEAN found = FALSE;
            for (UINT64 l = 0; l < _UTF32_WHITESPACECHARS_LEN; l++) { if (c == _UTF32_WHITESPACECHARS[l]) { found = TRUE; break; } }
            if (!found) return FALSE;
        }
        return TRUE;
    }

    Common::System::Optional<UINT64> UTF<CHAR32>::IndexOf(const CHAR32* str, const CHAR32* value, UINT64 startIndex, StringCulture culture)
    {
        if (str == nullptr || value == nullptr) return Common::System::Optional<UINT64>();
        UINT64 strLength = Length(str);
        UINT64 valueLength = Length(value);
        if (startIndex >= strLength) return Common::System::Optional<UINT64>();
        if (valueLength == 0) return Common::System::Optional<UINT64>(startIndex);

        switch (culture) {
        case Common::System::Environment::InvariantCulture:
        case Common::System::Environment::CurrentCulture:
        case Common::System::Environment::Ordinal:
            for (UINT64 index = startIndex; index <= strLength - valueLength; index++) {
                if (str[index] == value[0]) {
                    BOOLEAN match = TRUE;
                    for (UINT64 i = 0; i < valueLength; i++) if (str[index + i] != value[i]) { match = FALSE; break; }
                    if (match) return Common::System::Optional<UINT64>(index);
                }
            }
            return Common::System::Optional<UINT64>();
        case Common::System::Environment::InvariantCultureIgnoreCase:
        case Common::System::Environment::CurrentCultureIgnoreCase:
        case Common::System::Environment::OrdinalIgnoreCase:
            for (UINT64 index = startIndex; index <= strLength - valueLength; index++) {
                CHAR32 lChar = str[index]; CHAR32 rChar = value[0];
                if (lChar >= 'a' && lChar <= 'z') lChar -= 32;
                if (rChar >= 'a' && rChar <= 'z') rChar -= 32;
                if (lChar == rChar) {
                    BOOLEAN match = TRUE;
                    for (UINT64 i = 0; i < valueLength; i++) {
                        CHAR32 lChar2 = str[index + i]; CHAR32 rChar2 = value[i];
                        if (lChar2 >= 'a' && lChar2 <= 'z') lChar2 -= 32;
                        if (rChar2 >= 'a' && rChar2 <= 'z') rChar2 -= 32;
                        if (lChar2 != rChar2) { match = FALSE; break; }
                    }
                    if (match) return Common::System::Optional<UINT64>(index);
                }
            }
            return Common::System::Optional<UINT64>();
        default:
            return Common::System::Optional<UINT64>();
        }
    }

    Common::System::Optional<UINT64> UTF<CHAR32>::IndexOf(const CHAR32* str, const CHAR32 value, UINT64 startIndex, StringCulture culture)
    {
        if (str == nullptr) return Common::System::Optional<UINT64>();
        UINT64 strLength = Length(str);
        if (startIndex >= strLength) return Common::System::Optional<UINT64>();

        switch (culture) {
        case Common::System::Environment::InvariantCulture:
        case Common::System::Environment::CurrentCulture:
        case Common::System::Environment::Ordinal:
            for (UINT64 index = startIndex; index < strLength; index++) if (str[index] == value) return Common::System::Optional<UINT64>(index);
            return Common::System::Optional<UINT64>();
        case Common::System::Environment::InvariantCultureIgnoreCase:
        case Common::System::Environment::CurrentCultureIgnoreCase:
        case Common::System::Environment::OrdinalIgnoreCase:
            {
                CHAR32 rChar = value; if (rChar >= 'a' && rChar <= 'z') rChar -= 32;
                for (UINT64 index = startIndex; index < strLength; index++) {
                    CHAR32 lChar = str[index]; if (lChar >= 'a' && lChar <= 'z') lChar -= 32;
                    if (lChar == rChar) return Common::System::Optional<UINT64>(index);
                }
                return Common::System::Optional<UINT64>();
            }
        default:
            return Common::System::Optional<UINT64>();
        }
    }

    Common::System::Optional<UINT64> UTF<CHAR32>::LastIndexOf(const CHAR32* str, const CHAR32* value, UINT64 startIndex, StringCulture culture)
    {
        if (str == nullptr || value == nullptr) return Common::System::Optional<UINT64>();
        UINT64 strLength = Length(str);
        UINT64 valueLength = Length(value);
        if (strLength < valueLength) return Common::System::Optional<UINT64>();
        if (startIndex >= strLength) return Common::System::Optional<UINT64>();

        switch (culture) {
        case Common::System::Environment::InvariantCulture:
        case Common::System::Environment::CurrentCulture:
        case Common::System::Environment::Ordinal:
            for (UINT64 index = startIndex; index <= strLength - valueLength; index++) {
                if (str[index] == value[0]) {
                    BOOLEAN match = TRUE;
                    for (UINT64 i = 0; i < valueLength; i++) if (str[index + i] != value[i]) { match = FALSE; break; }
                    if (match) return Common::System::Optional<UINT64>(index);
                }
            }
            return Common::System::Optional<UINT64>();
        case Common::System::Environment::InvariantCultureIgnoreCase:
        case Common::System::Environment::CurrentCultureIgnoreCase:
        case Common::System::Environment::OrdinalIgnoreCase:
            for (UINT64 index = startIndex; index <= strLength - valueLength; index++) {
                CHAR32 lChar = str[index]; CHAR32 rChar = value[0];
                if (lChar >= 'a' && lChar <= 'z') lChar -= 32;
                if (rChar >= 'a' && rChar <= 'z') rChar -= 32;
                if (lChar == rChar) {
                    BOOLEAN match = TRUE;
                    for (UINT64 i = 0; i < valueLength; i++) {
                        CHAR32 lChar2 = str[index + i]; CHAR32 rChar2 = value[i];
                        if (lChar2 >= 'a' && lChar2 <= 'z') lChar2 -= 32;
                        if (rChar2 >= 'a' && rChar2 <= 'z') rChar2 -= 32;
                        if (lChar2 != rChar2) { match = FALSE; break; }
                    }
                    if (match) return Common::System::Optional<UINT64>(index);
                }
            }
            return Common::System::Optional<UINT64>();
        default:
            return Common::System::Optional<UINT64>();
        }
    }

    Common::System::Optional<UINT64> UTF<CHAR32>::LastIndexOf(const CHAR32* str, const CHAR32 value, UINT64 startIndex, StringCulture culture)
    {
        if (str == nullptr) return Common::System::Optional<UINT64>();
        UINT64 strLength = Length(str);
        if (startIndex >= strLength) return Common::System::Optional<UINT64>();

        switch (culture) {
        case Common::System::Environment::InvariantCulture:
        case Common::System::Environment::CurrentCulture:
        case Common::System::Environment::Ordinal:
            for (UINT64 index = startIndex; index < strLength; index++) if (str[index] == value) return Common::System::Optional<UINT64>(index);
            return Common::System::Optional<UINT64>();
        case Common::System::Environment::InvariantCultureIgnoreCase:
        case Common::System::Environment::CurrentCultureIgnoreCase:
        case Common::System::Environment::OrdinalIgnoreCase:
            {
                CHAR32 rChar = value; if (rChar >= 'a' && rChar <= 'z') rChar -= 32;
                for (UINT64 index = startIndex; index < strLength; index++) {
                    CHAR32 lChar = str[index]; if (lChar >= 'a' && lChar <= 'z') lChar -= 32;
                    if (lChar == rChar) return Common::System::Optional<UINT64>(index);
                }
                return Common::System::Optional<UINT64>();
            }
        default:
            return Common::System::Optional<UINT64>();
        }
    }

    CHAR32** UTF<CHAR32>::Split(const CHAR32* str, const CHAR32* separator, OUT UINT64* count)
    {
        if (IsNullOrEmpty(str)) return nullptr;
        if (IsNullOrEmpty(separator)) return nullptr;
        UINT64 strLen = Length(str);
        UINT64 sepLen = Length(separator);
        if (strLen == 0 || sepLen == 0) return nullptr;
        if (strLen <= sepLen) return nullptr;
        // Count occurrences
        UINT64 cnt = 1;
        for (UINT64 i = 0; i <= strLen - sepLen; i++) {
            BOOLEAN match = TRUE;
            for (UINT64 j = 0; j < sepLen; j++) if (str[i + j] != separator[j]) { match = FALSE; break; }
            if (match) cnt++;
        }
        *count = cnt;
        CHAR32** substrings = new CHAR32*[cnt];
        const CHAR32* start = str;
        UINT64 substringIndex = 0;
        for (UINT64 i = 0; i < strLen; i++) {
            // check if separator starts at this position
            BOOLEAN match = FALSE;
            if (i <= strLen - sepLen) {
                match = TRUE;
                for (UINT64 j = 0; j < sepLen; j++) if (str[i + j] != separator[j]) { match = FALSE; break; }
            }
            if (match) {
                UINT64 length = (UINT64)(str + i - start);
                CHAR32* substring = new CHAR32[length + 1];
                for (UINT64 k = 0; k < length; ++k) substring[k] = start[k];
                substring[length] = 0;
                substrings[substringIndex++] = substring;
                start = str + i + sepLen;
                i += sepLen - 1;
            }
        }
        // last segment
        UINT64 length = (UINT64)((str + strLen) - start);
        CHAR32* substring = new CHAR32[length + 1];
        for (UINT64 k = 0; k < length; ++k) substring[k] = start[k];
        substring[length] = 0;
        substrings[substringIndex++] = substring;
        return substrings;
    }

    CHAR32** UTF<CHAR32>::Split(const CHAR32* str, const CHAR32 separator, OUT UINT64* count)
    {
        if (IsNullOrEmpty(str)) return nullptr;
        UINT64 strLen = Length(str);
        if (strLen == 0) return nullptr;
        UINT64 cnt = 1;
        for (UINT64 i = 0; i < strLen; i++) if (str[i] == separator) cnt++;
        *count = cnt;
        CHAR32** substrings = new CHAR32*[cnt];
        const CHAR32* start = str;
        UINT64 substringIndex = 0;
        for (UINT64 i = 0; i < strLen; i++) {
            if (str[i] == separator) {
                UINT64 length = (UINT64)(str + i - start);
                CHAR32* substring = new CHAR32[length + 1];
                for (UINT64 k = 0; k < length; ++k) substring[k] = start[k];
                substring[length] = 0;
                substrings[substringIndex++] = substring;
                start = str + i + 1;
            }
        }
        // last segment
        UINT64 lengthLast = (UINT64)((str + strLen) - start);
        CHAR32* substringLast = new CHAR32[lengthLast + 1];
        for (UINT64 k = 0; k < lengthLast; ++k) substringLast[k] = start[k];
        substringLast[lengthLast] = 0;
        substrings[substringIndex++] = substringLast;
        return substrings;
    }

    CHAR32* UTF<CHAR32>::Join(const CHAR32** str, const CHAR32* separator, UINT64 count)
    {
        if (count == 0) return nullptr;
        if (separator == nullptr) return nullptr;
        if (str == nullptr) return nullptr;
        UINT64 len = 0;
        UINT64 sepLen = Length(separator);
        for (UINT64 i = 0; i < count; i++) if (!IsNullOrEmpty(str[i])) len += Length(str[i]) + sepLen;
        if (len == 0) return nullptr;
        CHAR32* result = new CHAR32[len + 1];
        UINT64 index = 0;
        for (UINT64 i = 0; i < count; i++) {
            if (!IsNullOrEmpty(str[i])) {
                const CHAR32* ptr = str[i]; while (*ptr != 0) result[index++] = *ptr++;
                for (UINT64 j = 0; j < sepLen; j++) result[index++] = separator[j];
            }
        }
        if (index == 0) { result[0] = 0; return result; }
        result[index - 1] = 0;
        return result;
    }

    CHAR32* UTF<CHAR32>::Join(const CHAR32** str, const CHAR32 separator, UINT64 count)
    {
        if (count == 0) return nullptr;
        if (str == nullptr) return nullptr;
        UINT64 len = 0;
        for (UINT64 i = 0; i < count; i++) if (!IsNullOrEmpty(str[i])) len += Length(str[i]) + 1;
        if (len == 0) return nullptr;
        CHAR32* result = new CHAR32[len + 1];
        UINT64 index = 0;
        for (UINT64 i = 0; i < count; i++) {
            if (!IsNullOrEmpty(str[i])) {
                const CHAR32* ptr = str[i]; while (*ptr != 0) result[index++] = *ptr++;
                result[index++] = separator;
            }
        }
        result[index - 1] = 0;
        return result;
    }

    CHAR32* UTF<CHAR32>::FromUTF16String(const CHAR16* str)
    {
        if (str == nullptr) return nullptr;
        UINT64 srcLen = UTF<CHAR16>::Length(str);
        // Count code points
        UINT64 count = 0;
        for (UINT64 i = 0; i < srcLen; ++i)
        {
            UINT16 w = (UINT16)str[i];
            if (w >= 0xD800 && w <= 0xDBFF)
            {
                if (i + 1 < srcLen)
                {
                    UINT16 w2 = (UINT16)str[i+1];
                    if (w2 >= 0xDC00 && w2 <= 0xDFFF) { ++count; ++i; continue; }
                }
                ++count; // replacement
            }
            else ++count;
        }
        CHAR32* result = new CHAR32[count + 1];
        UINT64 out = 0;
        for (UINT64 i = 0; i < srcLen; ++i)
        {
            UINT16 w = (UINT16)str[i];
            if (w >= 0xD800 && w <= 0xDBFF)
            {
                if (i + 1 < srcLen)
                {
                    UINT16 w2 = (UINT16)str[i+1];
                    if (w2 >= 0xDC00 && w2 <= 0xDFFF)
                    {
                        UINT32 codepoint = 0x10000 + (((UINT32)w - 0xD800) << 10) + ((UINT32)w2 - 0xDC00);
                        result[out++] = (CHAR32)codepoint; ++i; continue;
                    }
                }
                result[out++] = 0xFFFD;
            }
            else result[out++] = (CHAR32)w;
        }
        result[out] = 0;
        return result;
    }
}
