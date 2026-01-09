#pragma once
#include <TypeDefs.h>
#include <System/Environment/StringCulture.h>
#include <System/Optional.h>
#include "UnicodeCaseFolding.h"

namespace Common::System::Environment::UTFHelpers
{
    template<typename CharT>
    inline UINT64 Length(const CharT* str)
    {
        if (str == nullptr) return 0;
        UINT64 i = 0;
        while (str[i] != (CharT)0) ++i;
        return i;
    }

    template<typename CharT>
    inline BOOLEAN IsNullOrEmpty(const CharT* str)
    {
        return (str == nullptr) || (str[0] == (CharT)0);
    }

    template<typename CharT>
    inline BOOLEAN IsWhiteSpaceChar(CharT c, const CharT* table, UINT64 tableLen)
    {
        for (UINT64 i = 0; i < tableLen; ++i) if (c == table[i]) return TRUE;
        return FALSE;
    }

    // Case folding helper. Uses ASCII fast-path and a data-driven mapping for full Unicode folding.
    template<typename CharT>
    inline CharT CaseFold(CharT c)
    {
        // Use numeric codepoint operations so this works for CHAR, CHAR16, CHAR32.
        UINT32 cp = (UINT32)c;
        // ASCII A-Z -> a-z
        if (cp >= 0x41 && cp <= 0x5A) return (CharT)(cp + 0x20);
        // ASCII / Latin-1 / common BMP ranges handled by simple offsets for speed
        if ((cp >= 0x00C0 && cp <= 0x00D6) || (cp >= 0x00D8 && cp <= 0x00DE)) return (CharT)(cp + 0x20);
        if (cp >= 0x0391 && cp <= 0x03A9) return (CharT)(cp + 0x20);
        if (cp >= 0x0410 && cp <= 0x042F) return (CharT)(cp + 0x20);
        // Otherwise consult the data-driven folding table (placeholder)
        UINT32 folded = Common::System::Environment::Unicode::FoldCodePoint(cp);
        return (CharT)folded;
    }

    template<typename CharT>
    inline BOOLEAN Compare(const CharT* l, const CharT* r, StringCulture culture)
    {
        UINT64 lLen = Length(l);
        UINT64 rLen = Length(r);
        if (lLen != rLen) return FALSE;
        if (IsNullOrEmpty(l) && IsNullOrEmpty(r)) return TRUE;
        if (IsNullOrEmpty(l) || IsNullOrEmpty(r)) return FALSE;

        switch (culture)
        {
        case Common::System::Environment::InvariantCulture:
        case Common::System::Environment::CurrentCulture:
        case Common::System::Environment::Ordinal:
            for (UINT64 i = 0; i < lLen; ++i) if (l[i] != r[i]) return FALSE;
            return TRUE;
        case Common::System::Environment::InvariantCultureIgnoreCase:
        case Common::System::Environment::CurrentCultureIgnoreCase:
        case Common::System::Environment::OrdinalIgnoreCase:
            for (UINT64 i = 0; i < lLen; ++i)
            {
                // Use case folding helper for canonical comparison. Currently implements ASCII fold; extend for full Unicode.
                CharT a = l[i]; CharT b = r[i];
                auto aFold = CaseFold<CharT>(a);
                auto bFold = CaseFold<CharT>(b);
                if (aFold != bFold) return FALSE;
            }
            return TRUE;
        default:
            return FALSE;
        }
    }

    template<typename CharT>
    inline BOOLEAN StartsWith(const CharT* str, const CharT* value, StringCulture culture)
    {
        if (IsNullOrEmpty(str) && IsNullOrEmpty(value)) return TRUE;
        if (IsNullOrEmpty(str) || IsNullOrEmpty(value)) return FALSE;
        UINT64 sLen = Length(str); UINT64 vLen = Length(value);
        if (sLen < vLen) return FALSE;
        switch (culture)
        {
        case Common::System::Environment::InvariantCulture:
        case Common::System::Environment::CurrentCulture:
        case Common::System::Environment::Ordinal:
            for (UINT64 i = 0; i < vLen; ++i) if (str[i] != value[i]) return FALSE;
            return TRUE;
        case Common::System::Environment::InvariantCultureIgnoreCase:
        case Common::System::Environment::CurrentCultureIgnoreCase:
        case Common::System::Environment::OrdinalIgnoreCase:
            for (UINT64 i = 0; i < vLen; ++i)
            {
                CharT a = CaseFold<CharT>(str[i]); CharT b = CaseFold<CharT>(value[i]);
                if (a != b) return FALSE;
            }
            return TRUE;
        default:
            return FALSE;
        }
    }

    template<typename CharT>
    inline BOOLEAN EndsWith(const CharT* str, const CharT* value, StringCulture culture)
    {
        if (IsNullOrEmpty(str) && IsNullOrEmpty(value)) return TRUE;
        if (IsNullOrEmpty(str) || IsNullOrEmpty(value)) return FALSE;
        UINT64 sLen = Length(str); UINT64 vLen = Length(value);
        if (sLen < vLen) return FALSE;
        switch (culture)
        {
        case Common::System::Environment::InvariantCulture:
        case Common::System::Environment::CurrentCulture:
        case Common::System::Environment::Ordinal:
            for (UINT64 i = 0; i < vLen; ++i) if (str[sLen - vLen + i] != value[i]) return FALSE;
            return TRUE;
        case Common::System::Environment::InvariantCultureIgnoreCase:
        case Common::System::Environment::CurrentCultureIgnoreCase:
        case Common::System::Environment::OrdinalIgnoreCase:
            for (UINT64 i = 0; i < vLen; ++i)
            {
                CharT a = CaseFold<CharT>(str[sLen - vLen + i]); CharT b = CaseFold<CharT>(value[i]);
                if (a != b) return FALSE;
            }
            return TRUE;
        default:
            return FALSE;
        }
    }

    template<typename CharT>
    inline BOOLEAN Contains(const CharT* str, const CharT* value, StringCulture culture)
    {
        if (IsNullOrEmpty(str) && IsNullOrEmpty(value)) return TRUE;
        if (IsNullOrEmpty(str) || IsNullOrEmpty(value)) return FALSE;
        UINT64 sLen = Length(str); UINT64 vLen = Length(value);
        if (sLen < vLen) return FALSE;
        switch (culture)
        {
        case Common::System::Environment::InvariantCulture:
        case Common::System::Environment::CurrentCulture:
        case Common::System::Environment::Ordinal:
            for (UINT64 i = 0; i <= sLen - vLen; ++i)
            {
                if (str[i] == value[0])
                {
                    BOOLEAN match = TRUE;
                    for (UINT64 j = 0; j < vLen; ++j) if (str[i+j] != value[j]) { match = FALSE; break; }
                    if (match) return TRUE;
                }
            }
            return FALSE;
        case Common::System::Environment::InvariantCultureIgnoreCase:
        case Common::System::Environment::CurrentCultureIgnoreCase:
        case Common::System::Environment::OrdinalIgnoreCase:
            for (UINT64 i = 0; i <= sLen - vLen; ++i)
            {
                CharT a = CaseFold<CharT>(str[i]); CharT b = CaseFold<CharT>(value[0]);
                if (a == b)
                {
                    BOOLEAN match = TRUE;
                    for (UINT64 j = 0; j < vLen; ++j)
                    {
                        CharT aa = CaseFold<CharT>(str[i+j]); CharT bb = CaseFold<CharT>(value[j]);
                        if (aa != bb) { match = FALSE; break; }
                    }
                    if (match) return TRUE;
                }
            }
            return FALSE;
        default:
            return FALSE;
        }
    }

    template<typename CharT>
    inline BOOLEAN IsNullOrWhiteSpace(const CharT* str, const CharT* whitespaceTable, UINT64 tableLen)
    {
        if (str == nullptr) return TRUE;
        for (UINT64 i = 0; ; ++i)
        {
            CharT c = str[i]; if (c == (CharT)0) break;
            if (!IsWhiteSpaceChar<CharT>(c, whitespaceTable, tableLen)) return FALSE;
        }
        return TRUE;
    }

    template<typename CharT>
    inline Common::System::Optional<UINT64> IndexOf(const CharT* str, const CharT* value, UINT64 startIndex, StringCulture culture)
    {
        if (str == nullptr || value == nullptr) return Common::System::Optional<UINT64>();
        UINT64 sLen = Length(str); UINT64 vLen = Length(value);
        if (startIndex >= sLen) return Common::System::Optional<UINT64>();
        if (vLen == 0) return Common::System::Optional<UINT64>(startIndex);
        switch (culture)
        {
        case Common::System::Environment::InvariantCulture:
        case Common::System::Environment::CurrentCulture:
        case Common::System::Environment::Ordinal:
            for (UINT64 i = startIndex; i <= sLen - vLen; ++i)
            {
                if (str[i] == value[0])
                {
                    BOOLEAN match = TRUE;
                    for (UINT64 j = 0; j < vLen; ++j) if (str[i+j] != value[j]) { match = FALSE; break; }
                    if (match) return Common::System::Optional<UINT64>(i);
                }
            }
            return Common::System::Optional<UINT64>();
        case Common::System::Environment::InvariantCultureIgnoreCase:
        case Common::System::Environment::CurrentCultureIgnoreCase:
        case Common::System::Environment::OrdinalIgnoreCase:
            for (UINT64 i = startIndex; i <= sLen - vLen; ++i)
            {
                CharT a = CaseFold<CharT>(str[i]); CharT b = CaseFold<CharT>(value[0]);
                if (a == b)
                {
                    BOOLEAN match = TRUE;
                    for (UINT64 j = 0; j < vLen; ++j)
                    {
                        CharT aa = CaseFold<CharT>(str[i+j]); CharT bb = CaseFold<CharT>(value[j]);
                        if (aa != bb) { match = FALSE; break; }
                    }
                    if (match) return Common::System::Optional<UINT64>(i);
                }
            }
            return Common::System::Optional<UINT64>();
        default:
            return Common::System::Optional<UINT64>();
        }
    }

    template<typename CharT>
    inline Common::System::Optional<UINT64> IndexOf(const CharT* str, const CharT value, UINT64 startIndex, StringCulture culture)
    {
        if (str == nullptr) return Common::System::Optional<UINT64>();
        UINT64 sLen = Length(str);
        if (startIndex >= sLen) return Common::System::Optional<UINT64>();
        switch (culture)
        {
        case Common::System::Environment::InvariantCulture:
        case Common::System::Environment::CurrentCulture:
        case Common::System::Environment::Ordinal:
            for (UINT64 i = startIndex; i < sLen; ++i) if (str[i] == value) return Common::System::Optional<UINT64>(i);
            return Common::System::Optional<UINT64>();
        case Common::System::Environment::InvariantCultureIgnoreCase:
        case Common::System::Environment::CurrentCultureIgnoreCase:
        case Common::System::Environment::OrdinalIgnoreCase:
            {
                CharT rb = value; if (rb >= (CharT)'a' && rb <= (CharT)'z') rb = (CharT)(rb - 32);
                for (UINT64 i = startIndex; i < sLen; ++i)
                {
                    CharT a = str[i]; if (a >= (CharT)'a' && a <= (CharT)'z') a = (CharT)(a - 32);
                    if (a == rb) return Common::System::Optional<UINT64>(i);
                }
                return Common::System::Optional<UINT64>();
            }
        default:
            return Common::System::Optional<UINT64>();
        }
    }

    template<typename CharT>
    inline Common::System::Optional<UINT64> LastIndexOf(const CharT* str, const CharT* value, UINT64 startIndex, StringCulture culture)
    {
        if (str == nullptr || value == nullptr) return Common::System::Optional<UINT64>();
        UINT64 sLen = Length(str); UINT64 vLen = Length(value);
        if (sLen < vLen) return Common::System::Optional<UINT64>();
        if (startIndex >= sLen) return Common::System::Optional<UINT64>();
        switch (culture)
        {
        case Common::System::Environment::InvariantCulture:
        case Common::System::Environment::CurrentCulture:
        case Common::System::Environment::Ordinal:
            for (UINT64 i = startIndex; i <= sLen - vLen; ++i)
            {
                if (str[i] == value[0])
                {
                    BOOLEAN match = TRUE;
                    for (UINT64 j = 0; j < vLen; ++j) if (str[i+j] != value[j]) { match = FALSE; break; }
                    if (match) return Common::System::Optional<UINT64>(i);
                }
            }
            return Common::System::Optional<UINT64>();
        case Common::System::Environment::InvariantCultureIgnoreCase:
        case Common::System::Environment::CurrentCultureIgnoreCase:
        case Common::System::Environment::OrdinalIgnoreCase:
            for (UINT64 i = startIndex; i <= sLen - vLen; ++i)
            {
                CharT a = CaseFold<CharT>(str[i]); CharT b = CaseFold<CharT>(value[0]);
                if (a == b)
                {
                    BOOLEAN match = TRUE;
                    for (UINT64 j = 0; j < vLen; ++j)
                    {
                        CharT aa = CaseFold<CharT>(str[i+j]); CharT bb = CaseFold<CharT>(value[j]);
                        if (aa != bb) { match = FALSE; break; }
                    }
                    if (match) return Common::System::Optional<UINT64>(i);
                }
            }
            return Common::System::Optional<UINT64>();
        default:
            return Common::System::Optional<UINT64>();
        }
    }

    template<typename CharT>
    inline Common::System::Optional<UINT64> LastIndexOf(const CharT* str, const CharT value, UINT64 startIndex, StringCulture culture)
    {
        if (str == nullptr) return Common::System::Optional<UINT64>();
        UINT64 sLen = Length(str);
        if (startIndex >= sLen) return Common::System::Optional<UINT64>();
        switch (culture)
        {
        case Common::System::Environment::InvariantCulture:
        case Common::System::Environment::CurrentCulture:
        case Common::System::Environment::Ordinal:
            for (UINT64 i = startIndex; i < sLen; ++i) if (str[i] == value) return Common::System::Optional<UINT64>(i);
            return Common::System::Optional<UINT64>();
        case Common::System::Environment::InvariantCultureIgnoreCase:
        case Common::System::Environment::CurrentCultureIgnoreCase:
        case Common::System::Environment::OrdinalIgnoreCase:
            {
                CharT rb = value; if (rb >= (CharT)'a' && rb <= (CharT)'z') rb = (CharT)(rb - 32);
                for (UINT64 i = startIndex; i < sLen; ++i)
                {
                    CharT a = str[i]; if (a >= (CharT)'a' && a <= (CharT)'z') a = (CharT)(a - 32);
                    if (a == rb) return Common::System::Optional<UINT64>(i);
                }
                return Common::System::Optional<UINT64>();
            }
        default:
            return Common::System::Optional<UINT64>();
        }
    }

    template<typename CharT>
    inline CharT** Split(const CharT* str, const CharT* separator, OUT UINT64* count)
    {
        if (IsNullOrEmpty<CharT>(str)) return nullptr;
        if (IsNullOrEmpty<CharT>(separator)) return nullptr;
        UINT64 sLen = Length<CharT>(str); UINT64 sepLen = Length<CharT>(separator);
        if (sLen == 0 || sepLen == 0) return nullptr;
        if (sLen <= sepLen) return nullptr;
        UINT64 cnt = 1;
        for (UINT64 i = 0; i <= sLen - sepLen; ++i)
        {
            BOOLEAN match = TRUE;
            for (UINT64 j = 0; j < sepLen; ++j) if (str[i+j] != separator[j]) { match = FALSE; break; }
            if (match) ++cnt;
        }
        *count = cnt;
        CharT** substrings = new CharT*[cnt];
        const CharT* start = str; UINT64 idx = 0;
        for (UINT64 i = 0; i < sLen; ++i)
        {
            BOOLEAN match = FALSE;
            if (i <= sLen - sepLen) { match = TRUE; for (UINT64 j = 0; j < sepLen; ++j) if (str[i+j] != separator[j]) { match = FALSE; break; } }
            if (match) {
                UINT64 len = (UINT64)(str + i - start);
                CharT* sub = new CharT[len + 1]; for (UINT64 k = 0; k < len; ++k) sub[k] = start[k]; sub[len] = 0; substrings[idx++] = sub;
                start = str + i + sepLen; i += sepLen - 1;
            }
        }
        UINT64 lastLen = (UINT64)((str + sLen) - start);
        CharT* last = new CharT[lastLen + 1]; for (UINT64 k = 0; k < lastLen; ++k) last[k] = start[k]; last[lastLen] = 0; substrings[idx++] = last;
        return substrings;
    }

    template<typename CharT>
    inline void FreeSplit(CharT** arr, UINT64 count)
    {
        if (arr == nullptr) return;
        for (UINT64 i = 0; i < count; ++i)
        {
            if (arr[i] != nullptr) delete[] arr[i];
        }
        delete[] arr;
    }

    template<typename CharT>
    inline CharT** Split(const CharT* str, const CharT separator, OUT UINT64* count)
    {
        if (IsNullOrEmpty<CharT>(str)) return nullptr;
        UINT64 sLen = Length<CharT>(str);
        if (sLen == 0) return nullptr;
        UINT64 cnt = 1; for (UINT64 i = 0; i < sLen; ++i) if (str[i] == separator) ++cnt;
        *count = cnt;
        CharT** substrings = new CharT*[cnt]; const CharT* start = str; UINT64 idx = 0;
        for (UINT64 i = 0; i < sLen; ++i) {
            if (str[i] == separator) {
                UINT64 len = (UINT64)(str + i - start);
                CharT* sub = new CharT[len + 1]; for (UINT64 k = 0; k < len; ++k) sub[k] = start[k]; sub[len] = 0; substrings[idx++] = sub;
                start = str + i + 1;
            }
        }
        UINT64 lastLen = (UINT64)((str + sLen) - start);
        CharT* last = new CharT[lastLen + 1]; for (UINT64 k = 0; k < lastLen; ++k) last[k] = start[k]; last[lastLen] = 0; substrings[idx++] = last;
        return substrings;
    }

    template<typename CharT>
    inline CharT* Join(const CharT** arr, const CharT* separator, UINT64 count)
    {
        if (count == 0) return nullptr;
        if (separator == nullptr) return nullptr;
        if (arr == nullptr) return nullptr;
        UINT64 sepLen = Length<CharT>(separator);
        UINT64 total = 0;
        for (UINT64 i = 0; i < count; ++i) if (!IsNullOrEmpty<CharT>(arr[i])) total += Length<CharT>(arr[i]) + sepLen;
        if (total == 0) return nullptr;
        CharT* result = new CharT[total + 1]; UINT64 idx = 0;
        for (UINT64 i = 0; i < count; ++i) {
            if (!IsNullOrEmpty<CharT>(arr[i])) { const CharT* p = arr[i]; while (*p != (CharT)0) result[idx++] = *p++; for (UINT64 j = 0; j < sepLen; ++j) result[idx++] = separator[j]; }
        }
        if (idx == 0) { result[0] = 0; return result; }
        result[idx - 1] = 0; return result;
    }

    template<typename CharT>
    inline CharT* Join(const CharT** arr, const CharT separator, UINT64 count)
    {
        if (count == 0) return nullptr;
        if (arr == nullptr) return nullptr;
        UINT64 total = 0; for (UINT64 i = 0; i < count; ++i) if (!IsNullOrEmpty<CharT>(arr[i])) total += Length<CharT>(arr[i]) + 1;
        if (total == 0) return nullptr;
        CharT* result = new CharT[total + 1]; UINT64 idx = 0;
        for (UINT64 i = 0; i < count; ++i) {
            if (!IsNullOrEmpty<CharT>(arr[i])) { const CharT* p = arr[i]; while (*p != (CharT)0) result[idx++] = *p++; result[idx++] = separator; }
        }
        result[idx - 1] = 0; return result;
    }
}
