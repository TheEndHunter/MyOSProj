#include <System/Environment/Unicode/UTFCHAR16.h>

namespace Common::System::Environment
{
	constexpr const CHAR16 UTF<CHAR16>::NewLine[3]{u'\r', u'\n',u'\0'};
	constexpr const CHAR16 UTF<CHAR16>::NewLineChar[2]{ u'\r', u'\n' };

	CHAR16 _UTF16_GUIDTOSTRING[43] = { u'{',u'\0',u'\0',u'\0',u'\0',u'\0',u'\0',u'\0',u'\0',u'-',u'\0',u'\0',u'\0',u'\0',u'-',u'\0',u'\0',u'\0',u'\0',u'-',u'\0',u'\0',u'\0',u'\0',u'-',u'\0',u'\0',u'\0',u'\0',u'\0',u'\0',u'\0',u'\0',u'\0',u'\0',u'\0',u'\0',u'\0',u'\0',u'\0',u'\0',u'}',u'\0' };
	constexpr const UINT64 _UTF16_GUIDTOSTRING_LEN = sizeof(_UTF16_GUIDTOSTRING) / sizeof(CHAR16);

	CHAR16 _UTF16_HEXCHARS[17] = { u'0',u'1',u'2',u'3',u'4',u'5',u'6',u'7',u'8',u'9',u'A',u'B',u'C',u'D',u'E',u'F' };
	constexpr const UINT64 _UTF16_HEXCHARS_LEN = sizeof(_UTF16_HEXCHARS) / sizeof(CHAR16);

	CHAR16 _UTF16_HEXSTRING[18] = { u'\0',u'\0',u'\0',u'\0',u'\0',u'\0',u'\0',u'\0',u'\0',u'\0',u'\0',u'\0',u'\0',u'\0',u'\0',u'\0',u'\0',u'\0' };
	constexpr const UINT64 _UTF16_HEXSTRING_LEN = sizeof(_UTF16_HEXSTRING) / sizeof(CHAR16);

	 CHAR16 _UTF16_VALUETOSTRING[23] = { u'\0',u'\0',u'\0',u'\0',u'\0',u'\0',u'\0',u'\0',u'\0',u'\0',u'\0',u'\0',u'\0',u'\0',u'\0',u'\0',u'\0',u'\0',u'\0',u'\0',u'\0',u'\0',u'\0' };
	constexpr const UINT64 _UTF16_VALUETOSTRINGSTRING_LEN = sizeof(_UTF16_VALUETOSTRING) / sizeof(CHAR16);

	constexpr CHAR16 _UTF16_WHITESPACECHARS[30] = { 0x0009,0x000A,0x000B,0x000C,0x000D,0x0020,0x0085,0x00A0,0x1680,0x2000,0x2001,0x2003,0x2004,0x2005,0x2006,0x2007,0x02008,0x2009,0x200A,0x2028,0x2029,0x202F,0x205F,0x3000,0x180E,0x200B,0x200C,0x200D,0x2060,0xFEFF };
	constexpr const UINT64 _UTF16_WHITESPACECHARS_LEN = sizeof(_UTF16_WHITESPACECHARS) / sizeof(CHAR16);
	
	constexpr const CHAR16* _UTF16_ABORTED = u"ABORTED";
	constexpr const CHAR16* _UTF16_ACCESS_DENIED = u"ACCESS_DENIED";
	constexpr const CHAR16* _UTF16_ALREADY_STARTED = u"ALREADY_STARTED";
	constexpr const CHAR16* _UTF16_BAD_BUFFER_SIZE = u"BadBufferSize";
	constexpr const CHAR16* _UTF16_BOOLEAN_FALSE = u"False";
	constexpr const CHAR16* _UTF16_BOOLEAN_TRUE = u"True";
	constexpr const CHAR16* _UTF16_BUFFER_TOO_SMALL = u"BufferTooSmall";
	constexpr const CHAR16* _UTF16_COMPROMISED_DATA = u"COMPROMISED_DATA";
	constexpr const CHAR16* _UTF16_CRC_ERROR = u"CRC_ERROR";
	constexpr const CHAR16* _UTF16_DEVICE_ERROR = u"DEVICE_ERROR";
	constexpr const CHAR16* _UTF16_END_OF_FILE = u"END_OF_FILE";
	constexpr const CHAR16* _UTF16_END_OF_MEDIA = u"END_OF_MEDIA";
	constexpr const CHAR16* _UTF16_HTTP_ERROR = u"HTTP_ERROR";
	constexpr const CHAR16* _UTF16_ICMP_ERROR = u"ICMP_ERROR";
	constexpr const CHAR16* _UTF16_INCOMPATIBLE_VERSION = u"INCOMPATIBLE_VERSION";
	constexpr const CHAR16* _UTF16_INVALID_LANGUAGE = u"INVALID_LANGUAGE";
	constexpr const CHAR16* _UTF16_INVALID_PARAMETER = u"InvalidParameter";
	constexpr const CHAR16* _UTF16_IP_ADDRESS_CONFLICT = u"IP_ADDRESS_CONFLICT";
	constexpr const CHAR16* _UTF16_LOAD_ERROR = u"LoadError";
	constexpr const CHAR16* _UTF16_MEDIA_CHANGED = u"MEDIA_CHANGED";
	constexpr const CHAR16* _UTF16_NO_MAPPING = u"NO_MAPPING";
	constexpr const CHAR16* _UTF16_NO_MEDIA = u"NO_MEDIA";
	constexpr const CHAR16* _UTF16_NO_RESPONSE = u"NO_RESPONSE";
	constexpr const CHAR16* _UTF16_NOT_FOUND = u"NOT_FOUND";
	constexpr const CHAR16* _UTF16_NOT_READY = u"NotReady";
	constexpr const CHAR16* _UTF16_NOT_STARTED = u"NOT_STARTED";
	constexpr const CHAR16* _UTF16_OutOfResources = u"OutOfResources";
	constexpr const CHAR16* _UTF16_PROTOCOL_ERROR = u"PROTOCOL_ERROR";
	constexpr const CHAR16* _UTF16_SECURITY_VIOLATION = u"SECURITY_VIOLATION";
	constexpr const CHAR16* _UTF16_SUCCESS = u"Success";
	constexpr const CHAR16* _UTF16_TFTP_ERROR = u"TFTP_ERROR";
	constexpr const CHAR16* _UTF16_TIMEOUT = u"TIMEOUT";
	constexpr const CHAR16* _UTF16_UNSUPPORTED = u"Unsupported";
	constexpr const CHAR16* _UTF16_VOLUME_CORRUPTED = u"VOLUME_CORRUPTED";
	constexpr const CHAR16* _UTF16_VOLUME_FULL = u"VOLUME_FULL";
	constexpr const CHAR16* _UTF16_WARN_BUFFER_TOO_SMALL = u"WARN_BUFFER_TOO_SMALL";
	constexpr const CHAR16* _UTF16_WARN_DELETE_FAILURE = u"WARN_DELETE_FAILURE";
	constexpr const CHAR16* _UTF16_WARN_FILE_SYSTEM = u"WARN_FILE_SYSTEM";
	constexpr const CHAR16* _UTF16_WARN_RESET_REQUIRED = u"WARN_RESET_REQUIRED";
	constexpr const CHAR16* _UTF16_WARN_STALE_DATA = u"WARN_STALE_DATA";
	constexpr const CHAR16* _UTF16_WARN_UNKNOWN_GLYPH = u"WARN_UNKNOWN_GLYPH";
	constexpr const CHAR16* _UTF16_WARN_WRITE_FAILURE = u"WARN_WRITE_FAILURE";
	constexpr const CHAR16* _UTF16_WRITE_PROTECTED = u"WRITE_PROTECTED";

	constexpr const CHAR16* _UTF16_ALLOC_STATUS_SUCCESS = u"Success";
	constexpr const CHAR16* _UTF16_ALLOC_STATUS_INVALID_PARAMETER = u"InvalidParameter";
	constexpr const CHAR16* _UTF16_ALLOC_STATUS_NOT_ENOUGH_MEMORY = u"NOT_ENOUGH_MEMORY";
	constexpr const CHAR16* _UTF16_ALLOC_STATUS_NOT_ENOUGH_PAGES = u"NOT_ENOUGH_PAGES";
	constexpr const CHAR16* _UTF16_ALLOC_STATUS_ACCESS_DENIED = u"ACCESS_DENIED";
	constexpr const CHAR16* _UTF16_ALLOC_STATUS_UNKNOWN = u"UNKNOWN";

	CHAR16* UTF<CHAR16>::ToHex(const INT16 value)
	{
		if (value < 0)
		{
			INT16 abs = -value;
			_UTF16_HEXSTRING[0] = u'-';
			_UTF16_HEXSTRING[1] = _UTF16_HEXCHARS[(abs >> 12) & 0xF];
			_UTF16_HEXSTRING[2] = _UTF16_HEXCHARS[(abs >> 8) & 0xF];
			_UTF16_HEXSTRING[3] = _UTF16_HEXCHARS[(abs >> 4) & 0xF];
            _UTF16_HEXSTRING[4] = _UTF16_HEXCHARS[abs & 0xF];
            _UTF16_HEXSTRING[5] = u'\0';
        }
        else
        {
            _UTF16_HEXSTRING[0] = _UTF16_HEXCHARS[(value >> 12) & 0xF];
            _UTF16_HEXSTRING[1] = _UTF16_HEXCHARS[(value >> 8) & 0xF];
            _UTF16_HEXSTRING[2] = _UTF16_HEXCHARS[(value >> 4) & 0xF];
            _UTF16_HEXSTRING[3] = _UTF16_HEXCHARS[value & 0xF];
            _UTF16_HEXSTRING[4] = u'\0';
        }
        return &_UTF16_HEXSTRING[0];
    }

CHAR16* UTF<CHAR16>::SanitizeToUcs2(const CHAR16* src)
{
    if (src == nullptr) return nullptr;
    UINT64 len = Length(src);
    CHAR16* out = new CHAR16[len + 1];
    UINT64 outIdx = 0;
    for (UINT64 i = 0; i < len; ++i)
    {
        UINT16 w = (UINT16)src[i];
        if (w >= 0xD800 && w <= 0xDBFF)
        {
            // high surrogate - not representable in UCS-2 => replace
            out[outIdx++] = (CHAR16)0xFFFD;
            // skip potential low surrogate if present
            if (i + 1 < len)
            {
                UINT16 w2 = (UINT16)src[i+1];
                if (w2 >= 0xDC00 && w2 <= 0xDFFF) i++; // consume but replace
            }
        }
        else if (w >= 0xDC00 && w <= 0xDFFF)
        {
            // unpaired low surrogate -> replacement
            out[outIdx++] = (CHAR16)0xFFFD;
        }
        else
        {
            // BMP codepoint, keep as-is
            out[outIdx++] = (CHAR16)w;
        }
    }
    out[outIdx] = u'\0';
    return out;
}

CHAR8* UTF<CHAR16>::ToUTF8String(const CHAR16* str)
{
    if (str == nullptr) return nullptr;
    UINT64 srcLen = UTF<CHAR16>::Length(str);
    // Use existing UTF<CHAR8>::FromUTF16String by creating a buffer via buffer overload
    // First compute required size
    UINT64 needed = 0;
    for (UINT64 i = 0; i < srcLen; ++i)
    {
        UINT16 w1 = (UINT16)str[i];
        if (w1 >= 0xD800 && w1 <= 0xDBFF)
        {
            if (i + 1 < srcLen)
            {
                UINT16 w2 = (UINT16)str[i+1];
                if (w2 >= 0xDC00 && w2 <= 0xDFFF) { needed += 4; i++; continue; }
            }
            needed += 3; // replacement U+FFFD
        }
        else if (w1 >= 0xDC00 && w1 <= 0xDFFF)
        {
            needed += 3; // replacement
        }
        else if (w1 < 0x80) needed += 1;
        else if (w1 < 0x800) needed += 2;
        else needed += 3;
    }

    CHAR8* out = new CHAR8[needed + 1];
    UINT64 outIdx = 0;
    for (UINT64 i = 0; i < srcLen; ++i)
    {
        UINT32 codepoint = 0;
        UINT16 w1 = (UINT16)str[i];
        if (w1 >= 0xD800 && w1 <= 0xDBFF)
        {
            if (i + 1 < srcLen)
            {
                UINT16 w2 = (UINT16)str[i+1];
                if (w2 >= 0xDC00 && w2 <= 0xDFFF)
                {
                    codepoint = 0x10000 + (((w1 - 0xD800) << 10) | (w2 - 0xDC00));
                    i++; // consumed
                }
                else codepoint = 0xFFFD;
            }
            else codepoint = 0xFFFD;
        }
        else if (w1 >= 0xDC00 && w1 <= 0xDFFF) codepoint = 0xFFFD;
        else codepoint = w1;

        if (codepoint <= 0x7F)
        {
            out[outIdx++] = (CHAR8)codepoint;
        }
        else if (codepoint <= 0x7FF)
        {
            out[outIdx++] = (CHAR8)(0xC0 | ((codepoint >> 6) & 0x1F));
            out[outIdx++] = (CHAR8)(0x80 | (codepoint & 0x3F));
        }
        else if (codepoint <= 0xFFFF)
        {
            out[outIdx++] = (CHAR8)(0xE0 | ((codepoint >> 12) & 0x0F));
            out[outIdx++] = (CHAR8)(0x80 | ((codepoint >> 6) & 0x3F));
            out[outIdx++] = (CHAR8)(0x80 | (codepoint & 0x3F));
        }
        else
        {
            out[outIdx++] = (CHAR8)(0xF0 | ((codepoint >> 18) & 0x07));
            out[outIdx++] = (CHAR8)(0x80 | ((codepoint >> 12) & 0x3F));
            out[outIdx++] = (CHAR8)(0x80 | ((codepoint >> 6) & 0x3F));
            out[outIdx++] = (CHAR8)(0x80 | (codepoint & 0x3F));
        }
    }
    out[outIdx] = u8'\0';
    return out;
}

Common::System::Optional<UINT64> UTF<CHAR16>::ToUTF8String(const CHAR16* src, CHAR8* outBuffer, UINT64 outBufferSize)
{
    if (src == nullptr || outBuffer == nullptr) return Common::System::Optional<UINT64>();
    UINT64 srcLen = UTF<CHAR16>::Length(src);
    // compute needed bytes
    UINT64 needed = 0;
    for (UINT64 i = 0; i < srcLen; ++i)
    {
        UINT16 w1 = (UINT16)src[i];
        if (w1 >= 0xD800 && w1 <= 0xDBFF)
        {
            if (i + 1 < srcLen)
            {
                UINT16 w2 = (UINT16)src[i+1];
                if (w2 >= 0xDC00 && w2 <= 0xDFFF) { needed += 4; i++; continue; }
            }
            needed += 3;
        }
        else if (w1 >= 0xDC00 && w1 <= 0xDFFF) needed += 3;
        else if (w1 < 0x80) needed += 1;
        else if (w1 < 0x800) needed += 2;
        else needed += 3;
    }
    if (outBufferSize < needed + 1) return Common::System::Optional<UINT64>();

    UINT64 outIdx = 0;
    for (UINT64 i = 0; i < srcLen; ++i)
    {
        UINT32 codepoint = 0;
        UINT16 w1 = (UINT16)src[i];
        if (w1 >= 0xD800 && w1 <= 0xDBFF)
        {
            if (i + 1 < srcLen)
            {
                UINT16 w2 = (UINT16)src[i+1];
                if (w2 >= 0xDC00 && w2 <= 0xDFFF)
                {
                    codepoint = 0x10000 + (((w1 - 0xD800) << 10) | (w2 - 0xDC00));
                    i++;
                }
                else codepoint = 0xFFFD;
            }
            else codepoint = 0xFFFD;
        }
        else if (w1 >= 0xDC00 && w1 <= 0xDFFF) codepoint = 0xFFFD;
        else codepoint = w1;

        if (codepoint <= 0x7F)
        {
            outBuffer[outIdx++] = (CHAR8)codepoint;
        }
        else if (codepoint <= 0x7FF)
        {
            outBuffer[outIdx++] = (CHAR8)(0xC0 | ((codepoint >> 6) & 0x1F));
            outBuffer[outIdx++] = (CHAR8)(0x80 | (codepoint & 0x3F));
        }
        else if (codepoint <= 0xFFFF)
        {
            outBuffer[outIdx++] = (CHAR8)(0xE0 | ((codepoint >> 12) & 0x0F));
            outBuffer[outIdx++] = (CHAR8)(0x80 | ((codepoint >> 6) & 0x3F));
            outBuffer[outIdx++] = (CHAR8)(0x80 | (codepoint & 0x3F));
        }
        else
        {
            outBuffer[outIdx++] = (CHAR8)(0xF0 | ((codepoint >> 18) & 0x07));
            outBuffer[outIdx++] = (CHAR8)(0x80 | ((codepoint >> 12) & 0x3F));
            outBuffer[outIdx++] = (CHAR8)(0x80 | ((codepoint >> 6) & 0x3F));
            outBuffer[outIdx++] = (CHAR8)(0x80 | (codepoint & 0x3F));
        }
    }
    outBuffer[outIdx] = u8'\0';
    return Common::System::Optional<UINT64>(outIdx);
}

CHAR* UTF<CHAR16>::ToCString(const CHAR16* str)
{
    if (str == nullptr) return nullptr;
    UINT64 len = UTF<CHAR16>::Length(str);
    CHAR* out = new CHAR[len + 1];
    for (UINT64 i = 0; i < len; ++i)
    {
        CHAR16 c = str[i];
        if (c <= 0xFF) out[i] = (CHAR)(c & 0xFF);
        else out[i] = '?';
    }
    out[len] = '\0';
    return out;
}

Common::System::Optional<UINT64> UTF<CHAR16>::ToCString(const CHAR16* src, CHAR* outBuffer, UINT64 outBufferSize)
{
    if (src == nullptr || outBuffer == nullptr) return Common::System::Optional<UINT64>();
    UINT64 len = UTF<CHAR16>::Length(src);
    if (outBufferSize < len + 1) return Common::System::Optional<UINT64>();
    for (UINT64 i = 0; i < len; ++i)
    {
        CHAR16 c = src[i];
        outBuffer[i] = (c <= 0xFF) ? (CHAR)(c & 0xFF) : '?';
    }
    outBuffer[len] = '\0';
    return Common::System::Optional<UINT64>(len);
}

void UTF<CHAR16>::FreeSplit(CHAR16** arr, UINT64 count)
{
    if (arr == nullptr) return;
    for (UINT64 i = 0; i < count; ++i) if (arr[i] != nullptr) delete[] arr[i];
    delete[] arr;
}

void UTF<CHAR16>::Free(CHAR16* str)
{
    if (str != nullptr) delete[] str;
}

	CHAR16* UTF<CHAR16>::ToHex(const INT32 value)
	{
		if (value < 0)
		{
			INT32 abs = -value;
			_UTF16_HEXSTRING[0] = u'-';
			_UTF16_HEXSTRING[1] = _UTF16_HEXCHARS[(abs >> 28) & 0xF];
			_UTF16_HEXSTRING[2] = _UTF16_HEXCHARS[(abs >> 24) & 0xF];
			_UTF16_HEXSTRING[3] = _UTF16_HEXCHARS[(abs >> 20) & 0xF];
			_UTF16_HEXSTRING[4] = _UTF16_HEXCHARS[(abs >> 16) & 0xF];
			_UTF16_HEXSTRING[5] = _UTF16_HEXCHARS[(abs >> 12) & 0xF];
			_UTF16_HEXSTRING[6] = _UTF16_HEXCHARS[(abs >> 8) & 0xF];
			_UTF16_HEXSTRING[7] = _UTF16_HEXCHARS[(abs >> 4) & 0xF];
			_UTF16_HEXSTRING[8] = _UTF16_HEXCHARS[abs & 0xF];
			_UTF16_HEXSTRING[9] = u'\0';
		}
		else
		{
			_UTF16_HEXSTRING[0] = _UTF16_HEXCHARS[(value >> 28) & 0xF];
			_UTF16_HEXSTRING[1] = _UTF16_HEXCHARS[(value >> 24) & 0xF];
			_UTF16_HEXSTRING[2] = _UTF16_HEXCHARS[(value >> 20) & 0xF];
			_UTF16_HEXSTRING[3] = _UTF16_HEXCHARS[(value >> 16) & 0xF];
			_UTF16_HEXSTRING[4] = _UTF16_HEXCHARS[(value >> 12) & 0xF];
			_UTF16_HEXSTRING[5] = _UTF16_HEXCHARS[(value >> 8) & 0xF];
			_UTF16_HEXSTRING[6] = _UTF16_HEXCHARS[(value >> 4) & 0xF];
			_UTF16_HEXSTRING[7] = _UTF16_HEXCHARS[value & 0xF];
			_UTF16_HEXSTRING[8] = u'\0';
		}
		return &_UTF16_HEXSTRING[0];
	}

	CHAR16* UTF<CHAR16>::ToHex(const INT64 value)
	{
		if (value < 0)
		{
			INT64 abs = -value;
			_UTF16_HEXSTRING[0] = u'-';
			_UTF16_HEXSTRING[1] = _UTF16_HEXCHARS[(abs >> 60) & 0xF];
			_UTF16_HEXSTRING[2] = _UTF16_HEXCHARS[(abs >> 56) & 0xF];
			_UTF16_HEXSTRING[3] = _UTF16_HEXCHARS[(abs >> 52) & 0xF];
			_UTF16_HEXSTRING[4] = _UTF16_HEXCHARS[(abs >> 48) & 0xF];
			_UTF16_HEXSTRING[5] = _UTF16_HEXCHARS[(abs >> 44) & 0xF];
			_UTF16_HEXSTRING[6] = _UTF16_HEXCHARS[(abs >> 40) & 0xF];
			_UTF16_HEXSTRING[7] = _UTF16_HEXCHARS[(abs >> 36) & 0xF];
			_UTF16_HEXSTRING[8] = _UTF16_HEXCHARS[(abs >> 32) & 0xF];
			_UTF16_HEXSTRING[9] = _UTF16_HEXCHARS[(abs >> 28) & 0xF];
			_UTF16_HEXSTRING[10] = _UTF16_HEXCHARS[(abs >> 24) & 0xF];
			_UTF16_HEXSTRING[11] = _UTF16_HEXCHARS[(abs >> 20) & 0xF];
			_UTF16_HEXSTRING[12] = _UTF16_HEXCHARS[(abs >> 16) & 0xF];
			_UTF16_HEXSTRING[13] = _UTF16_HEXCHARS[(abs >> 12) & 0xF];
			_UTF16_HEXSTRING[14] = _UTF16_HEXCHARS[(abs >> 8) & 0xF];
			_UTF16_HEXSTRING[15] = _UTF16_HEXCHARS[(abs >> 4) & 0xF];
			_UTF16_HEXSTRING[16] = _UTF16_HEXCHARS[abs & 0xF];
			_UTF16_HEXSTRING[17] = u'\0';
		}
		else
		{
			_UTF16_HEXSTRING[0] = _UTF16_HEXCHARS[(value >> 60) & 0xF];
			_UTF16_HEXSTRING[1] = _UTF16_HEXCHARS[(value >> 56) & 0xF];
			_UTF16_HEXSTRING[2] = _UTF16_HEXCHARS[(value >> 52) & 0xF];
			_UTF16_HEXSTRING[3] = _UTF16_HEXCHARS[(value >> 48) & 0xF];
			_UTF16_HEXSTRING[4] = _UTF16_HEXCHARS[(value >> 44) & 0xF];
			_UTF16_HEXSTRING[5] = _UTF16_HEXCHARS[(value >> 40) & 0xF];
			_UTF16_HEXSTRING[6] = _UTF16_HEXCHARS[(value >> 36) & 0xF];
			_UTF16_HEXSTRING[7] = _UTF16_HEXCHARS[(value >> 32) & 0xF];
			_UTF16_HEXSTRING[8] = _UTF16_HEXCHARS[(value >> 28) & 0xF];
			_UTF16_HEXSTRING[9] = _UTF16_HEXCHARS[(value >> 24) & 0xF];
			_UTF16_HEXSTRING[10] = _UTF16_HEXCHARS[(value >> 20) & 0xF];
			_UTF16_HEXSTRING[11] = _UTF16_HEXCHARS[(value >> 16) & 0xF];
			_UTF16_HEXSTRING[12] = _UTF16_HEXCHARS[(value >> 12) & 0xF];
			_UTF16_HEXSTRING[13] = _UTF16_HEXCHARS[(value >> 8) & 0xF];
			_UTF16_HEXSTRING[14] = _UTF16_HEXCHARS[(value >> 4) & 0xF];
			_UTF16_HEXSTRING[15] = _UTF16_HEXCHARS[value & 0xF];
			_UTF16_HEXSTRING[16] = u'\0';
		}
		return &_UTF16_HEXSTRING[0];
	}

	CHAR16* UTF<CHAR16>::ToHex(const INT8 value)
	{
		if (value < 0)
		{
			INT8 abs = -value;
			_UTF16_HEXSTRING[0] = u'-';
			_UTF16_HEXSTRING[1] = _UTF16_HEXCHARS[(abs >> 4) & 0xF];
			_UTF16_HEXSTRING[2] = _UTF16_HEXCHARS[abs & 0xF];
			_UTF16_HEXSTRING[3] = u'\0';
		}
		else
		{
			_UTF16_HEXSTRING[0] = _UTF16_HEXCHARS[(value >> 4) & 0xF];
			_UTF16_HEXSTRING[1] = _UTF16_HEXCHARS[value & 0xF];
			_UTF16_HEXSTRING[2] = u'\0';
		}
		return &_UTF16_HEXSTRING[0];
	}

	CHAR16* UTF<CHAR16>::ToHex(const UINT16 value)
	{
		_UTF16_HEXSTRING[0] = _UTF16_HEXCHARS[(value >> 12) & 0xF];
		_UTF16_HEXSTRING[1] = _UTF16_HEXCHARS[(value >> 8) & 0xF];
		_UTF16_HEXSTRING[2] = _UTF16_HEXCHARS[(value >> 4) & 0xF];
		_UTF16_HEXSTRING[3] = _UTF16_HEXCHARS[value & 0xF];
		_UTF16_HEXSTRING[4] = u'\0';
		return &_UTF16_HEXSTRING[0];
	}

	CHAR16* UTF<CHAR16>::ToHex(const UINT32 value)
	{
		_UTF16_HEXSTRING[0] = _UTF16_HEXCHARS[(value >> 28) & 0xF];
		_UTF16_HEXSTRING[1] = _UTF16_HEXCHARS[(value >> 24) & 0xF];
		_UTF16_HEXSTRING[2] = _UTF16_HEXCHARS[(value >> 20) & 0xF];
		_UTF16_HEXSTRING[3] = _UTF16_HEXCHARS[(value >> 16) & 0xF];
		_UTF16_HEXSTRING[4] = _UTF16_HEXCHARS[(value >> 12) & 0xF];
		_UTF16_HEXSTRING[5] = _UTF16_HEXCHARS[(value >> 8) & 0xF];
		_UTF16_HEXSTRING[6] = _UTF16_HEXCHARS[(value >> 4) & 0xF];
		_UTF16_HEXSTRING[7] = _UTF16_HEXCHARS[value & 0xF];
		_UTF16_HEXSTRING[8] = u'\0';
		return &_UTF16_HEXSTRING[0];
	}

	CHAR16* UTF<CHAR16>::ToHex(const UINT64 value)
	{
		UINT64 i = value;
		_UTF16_HEXSTRING[0] = _UTF16_HEXCHARS[(value >> 60) & 0xF];
		_UTF16_HEXSTRING[1] = _UTF16_HEXCHARS[(value >> 56) & 0xF];
		_UTF16_HEXSTRING[2] = _UTF16_HEXCHARS[(value >> 52) & 0xF];
		_UTF16_HEXSTRING[3] = _UTF16_HEXCHARS[(value >> 48) & 0xF];
		_UTF16_HEXSTRING[4] = _UTF16_HEXCHARS[(value >> 44) & 0xF];
		_UTF16_HEXSTRING[5] = _UTF16_HEXCHARS[(value >> 40) & 0xF];
		_UTF16_HEXSTRING[6] = _UTF16_HEXCHARS[(value >> 36) & 0xF];
		_UTF16_HEXSTRING[7] = _UTF16_HEXCHARS[(value >> 32) & 0xF];
		_UTF16_HEXSTRING[8] = _UTF16_HEXCHARS[(value >> 28) & 0xF];
		_UTF16_HEXSTRING[9] = _UTF16_HEXCHARS[(value >> 24) & 0xF];
		_UTF16_HEXSTRING[10] = _UTF16_HEXCHARS[(value >> 20) & 0xF];
		_UTF16_HEXSTRING[11] = _UTF16_HEXCHARS[(value >> 16) & 0xF];
		_UTF16_HEXSTRING[12] = _UTF16_HEXCHARS[(value >> 12) & 0xF];
		_UTF16_HEXSTRING[13] = _UTF16_HEXCHARS[(value >> 8) & 0xF];
		_UTF16_HEXSTRING[14] = _UTF16_HEXCHARS[(value >> 4) & 0xF];
		_UTF16_HEXSTRING[15] = _UTF16_HEXCHARS[value & 0xF];
		_UTF16_HEXSTRING[16] = u'\0';
		return &_UTF16_HEXSTRING[0];
	}

	CHAR16* UTF<CHAR16>::ToHex(const UINT8 value)
	{
		_UTF16_HEXSTRING[0] = _UTF16_HEXCHARS[(value >> 4) & 0xF];
		_UTF16_HEXSTRING[1] = _UTF16_HEXCHARS[value & 0xF];
		_UTF16_HEXSTRING[2] = u'\0';
		return &_UTF16_HEXSTRING[0];
	}

	CHAR16* UTF<CHAR16>::ToHex(const VOID_PTR ptr)
	{
		UINT64 value = (UINT64)ptr;
		_UTF16_HEXSTRING[0] = _UTF16_HEXCHARS[(value >> 60) & 0xF];
		_UTF16_HEXSTRING[1] = _UTF16_HEXCHARS[(value >> 56) & 0xF];
		_UTF16_HEXSTRING[2] = _UTF16_HEXCHARS[(value >> 52) & 0xF];
		_UTF16_HEXSTRING[3] = _UTF16_HEXCHARS[(value >> 48) & 0xF];
		_UTF16_HEXSTRING[4] = _UTF16_HEXCHARS[(value >> 44) & 0xF];
		_UTF16_HEXSTRING[5] = _UTF16_HEXCHARS[(value >> 40) & 0xF];
		_UTF16_HEXSTRING[6] = _UTF16_HEXCHARS[(value >> 36) & 0xF];
		_UTF16_HEXSTRING[7] = _UTF16_HEXCHARS[(value >> 32) & 0xF];
		_UTF16_HEXSTRING[8] = _UTF16_HEXCHARS[(value >> 28) & 0xF];
		_UTF16_HEXSTRING[9] = _UTF16_HEXCHARS[(value >> 24) & 0xF];
		_UTF16_HEXSTRING[10] = _UTF16_HEXCHARS[(value >> 20) & 0xF];
		_UTF16_HEXSTRING[11] = _UTF16_HEXCHARS[(value >> 16) & 0xF];
		_UTF16_HEXSTRING[12] = _UTF16_HEXCHARS[(value >> 12) & 0xF];
		_UTF16_HEXSTRING[13] = _UTF16_HEXCHARS[(value >> 8) & 0xF];
		_UTF16_HEXSTRING[14] = _UTF16_HEXCHARS[(value >> 4) & 0xF];
		_UTF16_HEXSTRING[15] = _UTF16_HEXCHARS[value & 0xF];
		_UTF16_HEXSTRING[16] = u'\0';
		return &_UTF16_HEXSTRING[0];
	}

	CHAR16* UTF<CHAR16>::ToString(const Efi::Guid guid)
	{
		_UTF16_GUIDTOSTRING[1] = _UTF16_HEXCHARS[(guid.Data1 >> 28) & 0xF];
		_UTF16_GUIDTOSTRING[2] = _UTF16_HEXCHARS[(guid.Data1 >> 24) & 0xF];
		_UTF16_GUIDTOSTRING[3] = _UTF16_HEXCHARS[(guid.Data1 >> 20) & 0xF];
		_UTF16_GUIDTOSTRING[4] = _UTF16_HEXCHARS[(guid.Data1 >> 16) & 0xF];
		_UTF16_GUIDTOSTRING[5] = _UTF16_HEXCHARS[(guid.Data1 >> 12) & 0xF];
		_UTF16_GUIDTOSTRING[6] = _UTF16_HEXCHARS[(guid.Data1 >> 8) & 0xF];
		_UTF16_GUIDTOSTRING[7] = _UTF16_HEXCHARS[(guid.Data1 >> 4) & 0xF];
		_UTF16_GUIDTOSTRING[8] = _UTF16_HEXCHARS[guid.Data1 & 0xF];
		_UTF16_GUIDTOSTRING[10] = _UTF16_HEXCHARS[(guid.Data2 >> 12) & 0xF];
		_UTF16_GUIDTOSTRING[11] = _UTF16_HEXCHARS[(guid.Data2 >> 8) & 0xF];
		_UTF16_GUIDTOSTRING[12] = _UTF16_HEXCHARS[(guid.Data2 >> 4) & 0xF];
		_UTF16_GUIDTOSTRING[13] = _UTF16_HEXCHARS[guid.Data2 & 0xF];
		_UTF16_GUIDTOSTRING[15] = _UTF16_HEXCHARS[(guid.Data3 >> 12) & 0xF];
		_UTF16_GUIDTOSTRING[16] = _UTF16_HEXCHARS[(guid.Data3 >> 8) & 0xF];
		_UTF16_GUIDTOSTRING[17] = _UTF16_HEXCHARS[(guid.Data3 >> 4) & 0xF];
		_UTF16_GUIDTOSTRING[18] = _UTF16_HEXCHARS[guid.Data3 & 0xF];
		_UTF16_GUIDTOSTRING[20] = _UTF16_HEXCHARS[(guid.Data4[0] >> 4) & 0xF];
		_UTF16_GUIDTOSTRING[21] = _UTF16_HEXCHARS[guid.Data4[0] & 0xF];
		_UTF16_GUIDTOSTRING[23] = _UTF16_HEXCHARS[(guid.Data4[1] >> 4) & 0xF];
		_UTF16_GUIDTOSTRING[24] = _UTF16_HEXCHARS[guid.Data4[1] & 0xF];
		_UTF16_GUIDTOSTRING[26] = _UTF16_HEXCHARS[(guid.Data4[2] >> 4) & 0xF];
		_UTF16_GUIDTOSTRING[27] = _UTF16_HEXCHARS[guid.Data4[2] & 0xF];
		_UTF16_GUIDTOSTRING[28] = _UTF16_HEXCHARS[(guid.Data4[3] >> 4) & 0xF];
		_UTF16_GUIDTOSTRING[29] = _UTF16_HEXCHARS[guid.Data4[3] & 0xF];
		_UTF16_GUIDTOSTRING[31] = _UTF16_HEXCHARS[(guid.Data4[4] >> 4) & 0xF];
		_UTF16_GUIDTOSTRING[32] = _UTF16_HEXCHARS[guid.Data4[4] & 0xF];
		_UTF16_GUIDTOSTRING[34] = _UTF16_HEXCHARS[(guid.Data4[5] >> 4) & 0xF];
		_UTF16_GUIDTOSTRING[35] = _UTF16_HEXCHARS[guid.Data4[5] & 0xF];
		_UTF16_GUIDTOSTRING[37] = _UTF16_HEXCHARS[(guid.Data4[6] >> 4) & 0xF];
		_UTF16_GUIDTOSTRING[38] = _UTF16_HEXCHARS[guid.Data4[6] & 0xF];
		_UTF16_GUIDTOSTRING[40] = _UTF16_HEXCHARS[(guid.Data4[7] >> 4) & 0xF];
		_UTF16_GUIDTOSTRING[41] = _UTF16_HEXCHARS[guid.Data4[7] & 0xF];
		return &_UTF16_GUIDTOSTRING[0];
	}

	const CHAR16* UTF<CHAR16>::ToString(const Efi::Status status)
	{
		switch (status)
		{
		case Efi::Status::Aborted:
			return _UTF16_ABORTED;
		case Efi::Status::AccessDenied:
			return _UTF16_ACCESS_DENIED;
		case Efi::Status::AlreadyStarted:
			return _UTF16_ALREADY_STARTED;
		case Efi::Status::BadBufferSize:
			return _UTF16_BAD_BUFFER_SIZE;
		case Efi::Status::BufferTooSmall:
			return _UTF16_BUFFER_TOO_SMALL;
		case Efi::Status::CompromisedData:
			return _UTF16_COMPROMISED_DATA;
		case Efi::Status::CrcError:
			return _UTF16_CRC_ERROR;
		case Efi::Status::DeviceError:
			return _UTF16_DEVICE_ERROR;
		case Efi::Status::EndOfFile:
			return _UTF16_END_OF_FILE;
		case Efi::Status::EndOfMedia:
			return _UTF16_END_OF_MEDIA;
		case Efi::Status::HttpError:
			return _UTF16_HTTP_ERROR;
		case Efi::Status::IcmpError:
			return _UTF16_ICMP_ERROR;
		case Efi::Status::IncompatibleVersion:
			return _UTF16_INCOMPATIBLE_VERSION;
		case Efi::Status::InvalidLanguage:
			return _UTF16_INVALID_LANGUAGE;
		case Efi::Status::InvalidParameter:
			return _UTF16_INVALID_PARAMETER;
		case Efi::Status::IpAddressConflict:
			return _UTF16_IP_ADDRESS_CONFLICT;
		case Efi::Status::LoadError:
			return _UTF16_LOAD_ERROR;
		case Efi::Status::MediaChanged:
			return _UTF16_MEDIA_CHANGED;
		case Efi::Status::NoMapping:
			return _UTF16_NO_MAPPING;
		case Efi::Status::NoMedia:
			return _UTF16_NO_MEDIA;
		case Efi::Status::NoResponse:
			return _UTF16_NO_RESPONSE;
		case Efi::Status::NotFound:
			return _UTF16_NOT_FOUND;
		case Efi::Status::NotReady:
			return _UTF16_NOT_READY;
		case Efi::Status::NotStarted:
			return _UTF16_NOT_STARTED;
		case Efi::Status::OutOfResources:
			return _UTF16_OutOfResources;
		case Efi::Status::ProtocolError:
			return _UTF16_PROTOCOL_ERROR;
		case Efi::Status::SecurityViolation:
			return _UTF16_SECURITY_VIOLATION;
		case Efi::Status::Success:
			return _UTF16_SUCCESS;
		case Efi::Status::TftpError:
			return _UTF16_TFTP_ERROR;
		case Efi::Status::Timeout:
			return _UTF16_TIMEOUT;
		case Efi::Status::Unsupported:
			return _UTF16_UNSUPPORTED;
		case Efi::Status::VolumeCorrupted:
			return _UTF16_VOLUME_CORRUPTED;
		case Efi::Status::VolumeFull:
			return _UTF16_VOLUME_FULL;
		case Efi::Status::WarnBufferTooSmall:
			return _UTF16_WARN_BUFFER_TOO_SMALL;
		case Efi::Status::WarnDeleteFailure:
			return _UTF16_WARN_DELETE_FAILURE;
		case Efi::Status::WarnFileSystem:
			return _UTF16_WARN_FILE_SYSTEM;
		case Efi::Status::WarnResetRequired:
			return _UTF16_WARN_RESET_REQUIRED;
		case Efi::Status::WarnStaleData:
			return _UTF16_WARN_STALE_DATA;
		case Efi::Status::WarnUnknownGlyph:
			return _UTF16_WARN_UNKNOWN_GLYPH;
		case Efi::Status::WarnWriteFailure:
			return _UTF16_WARN_WRITE_FAILURE;
		case Efi::Status::WriteProtected:
			return _UTF16_WRITE_PROTECTED;
		default:
			return nullptr;
		}
	}

	const CHAR16* UTF<CHAR16>::ToString(const Common::System::MemoryManagement::AllocatorStatus status)
	{
		switch (status)
		{
		case Common::System::MemoryManagement::AllocatorStatus::Success:
			return _UTF16_ALLOC_STATUS_SUCCESS;
		case Common::System::MemoryManagement::AllocatorStatus::InvalidParameters:
			return _UTF16_ALLOC_STATUS_INVALID_PARAMETER;
		case Common::System::MemoryManagement::AllocatorStatus::NotEnoughMemory:
			return _UTF16_ALLOC_STATUS_NOT_ENOUGH_MEMORY;
		case Common::System::MemoryManagement::AllocatorStatus::NotEnoughPages:
			return _UTF16_ALLOC_STATUS_NOT_ENOUGH_PAGES;
		case Common::System::MemoryManagement::AllocatorStatus::AccessDenied:
			return _UTF16_ALLOC_STATUS_ACCESS_DENIED;
		}
	}

	CHAR16* UTF<CHAR16>::ToString(const INT16 value)
	{
		if (value == 0)
		{
			_UTF16_VALUETOSTRING[0] = u'0';
			_UTF16_VALUETOSTRING[1] = u'\0';
			return &_UTF16_VALUETOSTRING[0];
		}

		INT16 i = value;
		INT8 len = 6;
		_UTF16_VALUETOSTRING[len] = u'\0';
		BOOLEAN isNegative = false;
		if (i < 0)
		{
			isNegative = true;
			i = -i; // make it positive
		}
		for (; i > 0; i /= 10)
		{
			_UTF16_VALUETOSTRING[--len] = (i % 10) + u'0';
		}
		if (isNegative)
		{
			_UTF16_VALUETOSTRING[--len] = u'-';
		}
		return &_UTF16_VALUETOSTRING[len];
	}

	CHAR16* UTF<CHAR16>::ToString(const INT32 value)
	{
		if (value == 0)
		{
			_UTF16_VALUETOSTRING[0] = u'0';
			_UTF16_VALUETOSTRING[1] = u'\0';
			return &_UTF16_VALUETOSTRING[0];
		}

		INT32 i = value;
		INT8 len = 11;
		_UTF16_VALUETOSTRING[len] = u'\0';
		BOOLEAN isNegative = false;
		if (i < 0)
		{
			isNegative = true;
			i = -i; // make it positive
		}
		for (; i > 0; i /= 10)
		{
			_UTF16_VALUETOSTRING[--len] = (i % 10) + u'0';
		}
		if (isNegative)
		{
			_UTF16_VALUETOSTRING[--len] = u'-';
		}
		return &_UTF16_VALUETOSTRING[len];
	}

	CHAR16* UTF<CHAR16>::ToString(const INT64 value)
	{
		if (value == 0)
		{
			_UTF16_VALUETOSTRING[0] = u'0';
			_UTF16_VALUETOSTRING[1] = u'\0';
			return &_UTF16_VALUETOSTRING[0];
		}

		INT64 i = value;
		INT8 len = 21;
		_UTF16_VALUETOSTRING[len] = u'\0';
		BOOLEAN isNegative = false;
		if (i < 0)
		{
			isNegative = true;
			i = -i; // make it positive
		}
		for (; i > 0; i /= 10)
		{
			_UTF16_VALUETOSTRING[--len] = (i % 10) + u'0';
		}
		if (isNegative)
		{
			_UTF16_VALUETOSTRING[--len] = u'-';
		}
		return &_UTF16_VALUETOSTRING[len];
	}

	CHAR16* UTF<CHAR16>::ToString(const INT8 value)
	{
		if (value == 0)
		{
			_UTF16_VALUETOSTRING[0] = u'0';
			_UTF16_VALUETOSTRING[1] = u'\0';
			return &_UTF16_VALUETOSTRING[0];
		}

		INT8 i = value;
		INT8 len = 4;
		_UTF16_VALUETOSTRING[len] = u'\0';
		BOOLEAN isNegative = false;
		if (i < 0)
		{
			isNegative = true;
			i = -i; // make it positive
		}
		for (; i > 0; i /= 10)
		{
			_UTF16_VALUETOSTRING[--len] = (i % 10) + u'0';
		}
		if (isNegative)
		{
			_UTF16_VALUETOSTRING[--len] = u8'-';
		}
		return &_UTF16_VALUETOSTRING[len];
	}

	CHAR16* UTF<CHAR16>::ToString(const UINT16 value)
	{
		if (value == 0)
		{
			_UTF16_VALUETOSTRING[0] = u'0';
			_UTF16_VALUETOSTRING[1] = u'\0';
			return &_UTF16_VALUETOSTRING[0];
		}

		UINT16 i = value;
		INT8 len = 5;
		_UTF16_VALUETOSTRING[len] = u'\0';
		for (; i > 0; i /= 10)
		{
			_UTF16_VALUETOSTRING[--len] = (i % 10) + u'0';
		}
		return &_UTF16_VALUETOSTRING[len];
	}

	CHAR16* UTF<CHAR16>::ToString(const UINT32 value)
	{
		if (value == 0)
		{
			_UTF16_VALUETOSTRING[0] = u'0';
			_UTF16_VALUETOSTRING[1] = u'\0';
			return &_UTF16_VALUETOSTRING[0];
		}

		UINT32 i = value;
		INT8 len = 10;
		_UTF16_VALUETOSTRING[len] = u'\0';
		for (; i > 0; i /= 10)
		{
			_UTF16_VALUETOSTRING[--len] = (i % 10) + u'0';
		}
		return &_UTF16_VALUETOSTRING[len];
	}

	CHAR16* UTF<CHAR16>::ToString(const UINT64 value)
	{
		if (value == 0)
		{
			_UTF16_VALUETOSTRING[0] = u'0';
			_UTF16_VALUETOSTRING[1] = u'\0';
			return &_UTF16_VALUETOSTRING[0];
		}

		UINT64 i = value;
		INT8 len = 20;
		_UTF16_VALUETOSTRING[len] = u'\0';
		for (; i > 0; i /= 10)
		{
			_UTF16_VALUETOSTRING[--len] = (i % 10) + u'0';
		}
		return &_UTF16_VALUETOSTRING[len];
	}

	CHAR16* UTF<CHAR16>::ToString(const UINT8 value)
	{
		if (value == 0)
		{
			_UTF16_VALUETOSTRING[0] = u'0';
			_UTF16_VALUETOSTRING[1] = u'\0';
			return &_UTF16_VALUETOSTRING[0];
		}

		UINT8 i = value;
		INT8 len = 3;
		_UTF16_VALUETOSTRING[len] = u'\0';
		for (; i > 0; i /= 10)
		{
			_UTF16_VALUETOSTRING[--len] = (i % 10) + u'0';
		}
		return &_UTF16_VALUETOSTRING[len];
	}

	CHAR16* UTF<CHAR16>::ToString(const VOID_PTR ptr)
	{
		UINT64 value = (UINT64)ptr;
		if (value == 0)
		{
			_UTF16_VALUETOSTRING[0] = u'0';
			_UTF16_VALUETOSTRING[1] = u'\0';
			return &_UTF16_VALUETOSTRING[0];
		}

		UINT64 i = value;
		INT8 len = 20;
		_UTF16_VALUETOSTRING[len] = u'\0';
		for (; i > 0; i /= 10)
		{
			_UTF16_VALUETOSTRING[--len] = (i % 10) + u'0';
		}
		return &_UTF16_VALUETOSTRING[len];
	}
	const CHAR16* UTF<CHAR16>::ToString(const BOOLEAN boolean)
	{
		if (boolean)
		{
			return _UTF16_BOOLEAN_TRUE;
		}
		else
		{
			return _UTF16_BOOLEAN_FALSE;
		}
	}
		
	UINT64 UTF<CHAR16>::Length(const CHAR16* str)
	{
		if (str == nullptr)
		{
			return 0;
		}

		if (str[0] == u'\0')
		{
			return 1;
		}

		UINT64 index = 0;
		UINT64 len = 1;
		while (str[index] != u'\0')
		{
			len++;
			index++;
		}
		return len;
	}

	BOOLEAN UTF<CHAR16>::Compare(const CHAR16* l, const CHAR16* r, StringCulture culture)
	{
		/*Check for isNullOrEmpty and Lengths, if they don't match, return FALSE*/

		UINT64 lLength = Length(l);;
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
			/*Binary Comparison of string*/

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
			/*Binary Comparison, Ignoring Case of string*/

			UINT64 index = 0;

			for (UINT64 index = 0; index < lLength; index++)
			{
				CHAR16 lChar = l[index];
				CHAR16 rChar = r[index];
				/*If the character is a lower case letter, switch it to upper for comparison*/
				if (lChar >= u'a' && lChar <= u'z')
				{
					lChar -= 32;
				}
				if (rChar >= u'a' && rChar <= u'z')
				{
					rChar -= 32;
				}

				if (lChar != rChar)
				{
					return FALSE;
				}
			}
			return TRUE;
		}
		default:
			return FALSE;
		}

	}

	BOOLEAN UTF<CHAR16>::StartsWith(const CHAR16* str, const CHAR16* value, StringCulture culture)
	{
		BOOLEAN l = IsNullOrEmpty(str);
		BOOLEAN r = IsNullOrEmpty(value);
		if (l == r)
		{
			return TRUE;
		}

		if (l || r)
		{
			return FALSE;
		}


		UINT64 strLength = Length(str);
		UINT64 valueLength = Length(value);

		if (strLength < valueLength)
		{
			return FALSE;
		}

		switch (culture)
		{
		case Common::System::Environment::InvariantCulture:
		case Common::System::Environment::CurrentCulture:
		case Common::System::Environment::Ordinal:
		{
			for (UINT64 index = 0; index < valueLength; index++)
			{
				if (str[index] != value[index])
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
			for (UINT64 index = 0; index < valueLength; index++)
			{
				CHAR16 lChar = str[index];
				CHAR16 rChar = value[index];
				/*If the character is a lower case letter, switch it to upper for comparison*/
				if (lChar >= u'a' && lChar <= u'z')
				{
					lChar -= 32;
				}
				if (rChar >= u'a' && rChar <= u'z')
				{
					rChar -= 32;
				}

				if (lChar != rChar)
				{
					return FALSE;
				}
			}
			return TRUE;
		}
		default:
			return FALSE;
		}
	}

	BOOLEAN UTF<CHAR16>::EndsWith(const CHAR16* str, const CHAR16* value, StringCulture culture)
	{
		BOOLEAN l = IsNullOrEmpty(str);
		BOOLEAN r = IsNullOrEmpty(value);
		if (l == r)
		{
			return TRUE;
		}

		if (l || r)
		{
			return FALSE;
		}

		UINT64 strLength = Length(str);
		UINT64 valueLength = Length(value);

		if (strLength < valueLength)
		{
			return FALSE;
		}

		switch (culture)
		{
		case Common::System::Environment::InvariantCulture:
		case Common::System::Environment::CurrentCulture:
		case Common::System::Environment::Ordinal:
		{
			UINT64 index = 0;
			for (UINT64 index = 0; index < valueLength; index++)
			{
				if (str[strLength - valueLength + index] != value[index])
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
			UINT64 index = 0;
			for (UINT64 index = 0; index < valueLength; index++)
			{
				CHAR16 lChar = str[strLength - valueLength + index];
				CHAR16 rChar = value[index];
				/*If the character is a lower case letter, switch it to upper for comparison*/
				if (lChar >= u'a' && lChar <= u'z')
				{
					lChar -= 32;
				}
				if (rChar >= u'a' && rChar <= u'z')
				{
					rChar -= 32;
				}

				if (lChar != rChar)
				{
					return FALSE;
				}
			}
			return TRUE;
		}
		default:
			return FALSE;
		}

	}

	BOOLEAN UTF<CHAR16>::Contains(const CHAR16* str, const CHAR16* value, StringCulture culture)
	{
		BOOLEAN l = IsNullOrEmpty(str);
		BOOLEAN r = IsNullOrEmpty(value);

		if (l == r)
		{
			return TRUE;
		}

		if (l || r)
		{
			return FALSE;
		}


		UINT64 strLength = Length(str);
		UINT64 valueLength = Length(value);

		if (strLength < valueLength)
		{
			return FALSE;
		}

		switch (culture)
		{
		case Common::System::Environment::InvariantCulture:
		case Common::System::Environment::CurrentCulture:
		case Common::System::Environment::Ordinal:
		{
			UINT64 index = 0;
			for (UINT64 index = 0; index < strLength - valueLength; index++)
			{
				if (str[index] == value[0])
				{
					BOOLEAN match = TRUE;
					for (UINT64 i = 0; i < valueLength; i++)
					{
						if (str[index + i] != value[i])
						{
							match = FALSE;
							break;
						}
					}

					if (match)
					{
						return TRUE;
					}
				}
			}
			return FALSE;
		}
		case Common::System::Environment::InvariantCultureIgnoreCase:
		case Common::System::Environment::CurrentCultureIgnoreCase:
		case Common::System::Environment::OrdinalIgnoreCase:
		{
			UINT64 index = 0;
			for (UINT64 index = 0; index < strLength - valueLength; index++)
			{
				CHAR16 lChar = str[index];
				CHAR16 rChar = value[0];

				/*If the character is a lower case letter, switch it to upper for comparison*/

				if (lChar >= u'a' && lChar <= u'z')
				{
					lChar -= 32;
				}
				if (rChar >= u'a' && rChar <= u'z')
				{
					rChar -= 32;
				}

				if (lChar == rChar)
				{
					BOOLEAN match = TRUE;
					for (UINT64 i = 0; i < valueLength; i++)
					{
						CHAR16 lChar2 = str[index + i];
						CHAR16 rChar2 = value[i];
						/*If the character is a lower case letter, switch it to upper for comparison*/
						if (lChar2 >= u'a' && lChar2 <= u'z')
						{
							lChar2 -= 32;
						}
						if (rChar2 >= u'a' && rChar2 <= u'z')
						{
							rChar2 -= 32;
						}

						if (lChar != rChar)
						{
							match = FALSE;
							break;
						}
					}

					if (match)
					{
						return TRUE;
					}
				}
			}
			return FALSE;
		}
		default:
			return FALSE;
		}
	}

	BOOLEAN UTF<CHAR16>::IsNullOrEmpty(const CHAR16* str)
	{
		if (str == nullptr)
		{
			return TRUE;
		}

		if (str[0] == '\0')
		{
			return TRUE;
		}
		return FALSE;
	}

	BOOLEAN UTF<CHAR16>::IsNullOrWhiteSpace(const CHAR16* str)
	{
		if (str == nullptr)
		{
			return TRUE;
		}

		for (UINT64 i = 0;; i++)
		{
			CHAR16 c = str[i];
			if (c == 0)
			{
				break;
			}

			for (UINT64 l = 0; l < _UTF16_WHITESPACECHARS_LEN; l++)
			{
				CHAR16 c1 = _UTF16_WHITESPACECHARS[l];

				if (c != c1)
				{
					return FALSE;
				}

			}
		}
	}

	BOOLEAN UTF<CHAR16>::IsNullEmptyOrWhiteSpace(const CHAR16* str)
	{
		if (str == nullptr)
		{
			return TRUE;
		}

		if (str[0] == u'\0')
		{
			return TRUE;
		}

		/*Check Entire string, if any of that characters are non whitespace characters, return false otherwise return true*/

		for (UINT64 i = 0;; i++)
		{
			CHAR16 c = str[i];
			if (c == 0)
			{
				break;
			}

			for (UINT64 l = 0; l < _UTF16_WHITESPACECHARS_LEN; l++)
			{
				CHAR16 c1 = _UTF16_WHITESPACECHARS[l];

				if (c != c1)
				{
					return FALSE;
				}
			}
		}
	}

	CHAR16* UTF<CHAR16>::FromCharArray(CHAR16 arr[], UINT64 Length)
	{
		if (arr == nullptr)
		{
			return nullptr;
		}

		if (arr[0] == u'\0')
		{
			return (CHAR16*)u"\0";
		}

		CHAR16* result = new CHAR16[Length + 1];

		for (UINT64 i = 0; i < Length; i++)
		{
			result[i] = arr[i];
		}
		result[Length] = u'\0';
		return result;
	}

	CHAR16* UTF<CHAR16>::FromUTF8String(const CHAR8* str)
	{
		/* Decode UTF-8 to UTF-16, handling multi-byte sequences and invalid sequences.
		   Invalid sequences produce U+FFFD. */

		if (str == nullptr)
		{
			return nullptr;
		}

		UINT64 srcLen = UTF<CHAR8>::Length(str);

		// First pass: determine required number of UTF-16 code units
		UINT64 needed = 0;
		for (UINT64 i = 0; i < srcLen; )
		{
			unsigned char c = (unsigned char)str[i];
			if (c <= 0x7F)
			{
				needed += 1;
				i++;
			}
			else if ((c & 0xE0) == 0xC0)
			{
				needed += 1;
				i += 2;
			}
			else if ((c & 0xF0) == 0xE0)
			{
				needed += 1;
				i += 3;
			}
			else if ((c & 0xF8) == 0xF0)
			{
				needed += 2; // will become surrogate pair
				i += 4;
			}
			else
			{
				// invalid leading byte, consume one and produce replacement
				needed += 1;
				i++;
			}
		}

		CHAR16* result = new CHAR16[needed + 1];
		UINT64 out = 0;

		for (UINT64 i = 0; i < srcLen; )
		{
			unsigned char c = (unsigned char)str[i];
			UINT32 codepoint = 0;
			UINT64 remaining = srcLen - i;

			if (c <= 0x7F)
			{
				codepoint = c;
				i++;
			}
			else if ((c & 0xE0) == 0xC0 && remaining >= 2)
			{
				unsigned char c1 = (unsigned char)str[i+1];
				if ((c1 & 0xC0) == 0x80)
				{
					codepoint = ((c & 0x1F) << 6) | (c1 & 0x3F);
					if (codepoint < 0x80) // overlong
						codepoint = 0xFFFD;
				}
				else
				{
					codepoint = 0xFFFD;
				}
				i += 2;
			}
			else if ((c & 0xF0) == 0xE0 && remaining >= 3)
			{
				unsigned char c1 = (unsigned char)str[i+1];
				unsigned char c2 = (unsigned char)str[i+2];
				if (((c1 & 0xC0) == 0x80) && ((c2 & 0xC0) == 0x80))
				{
					codepoint = ((c & 0x0F) << 12) | ((c1 & 0x3F) << 6) | (c2 & 0x3F);
					if (codepoint < 0x800) // overlong
						codepoint = 0xFFFD;
					// UTF-8 encodings of surrogates are invalid
					if (codepoint >= 0xD800 && codepoint <= 0xDFFF)
						codepoint = 0xFFFD;
				}
				else
				{
					codepoint = 0xFFFD;
				}
				i += 3;
			}
			else if ((c & 0xF8) == 0xF0 && remaining >= 4)
			{
				unsigned char c1 = (unsigned char)str[i+1];
				unsigned char c2 = (unsigned char)str[i+2];
				unsigned char c3 = (unsigned char)str[i+3];
				if (((c1 & 0xC0) == 0x80) && ((c2 & 0xC0) == 0x80) && ((c3 & 0xC0) == 0x80))
				{
					codepoint = ((c & 0x07) << 18) | ((c1 & 0x3F) << 12) | ((c2 & 0x3F) << 6) | (c3 & 0x3F);
					if (codepoint < 0x10000 || codepoint > 0x10FFFF)
						codepoint = 0xFFFD;
				}
				else
				{
					codepoint = 0xFFFD;
				}
				i += 4;
			}
			else
			{
				// invalid byte or insufficient continuation bytes
				codepoint = 0xFFFD;
				i++;
			}

			if (codepoint <= 0xFFFF)
			{
				result[out++] = (CHAR16)codepoint;
			}
			else
			{
				// encode as surrogate pair
				UINT32 cp = codepoint - 0x10000;
				result[out++] = (CHAR16)(0xD800 + ((cp >> 10) & 0x3FF));
				result[out++] = (CHAR16)(0xDC00 + (cp & 0x3FF));
			}
		}

		result[out] = u'\0';
		return result;
	}

    Common::System::Optional<UINT64> UTF<CHAR16>::FromUTF8String(const CHAR8* src, CHAR16* outBuffer, UINT64 outBufferSize)
    {
        if (src == nullptr || outBuffer == nullptr) return Common::System::Optional<UINT64>();
        UINT64 srcLen = UTF<CHAR8>::Length(src);

        // First pass: determine required number of UTF-16 code units
        UINT64 needed = 0;
        for (UINT64 i = 0; i < srcLen; )
        {
            unsigned char c = (unsigned char)src[i];
            if (c <= 0x7F)
            {
                needed += 1; i += 1;
            }
            else if ((c & 0xE0) == 0xC0)
            {
                // 2-byte sequence -> 1 code unit
                needed += 1; i += 2;
            }
            else if ((c & 0xF0) == 0xE0)
            {
                // 3-byte sequence -> 1 code unit
                needed += 1; i += 3;
            }
            else if ((c & 0xF8) == 0xF0)
            {
                // 4-byte sequence -> surrogate pair -> 2 code units
                needed += 2; i += 4;
            }
            else
            {
                // invalid leading byte -> replacement U+FFFD (1 code unit)
                needed += 1; i += 1;
            }
        }

        if (outBufferSize < needed + 1) return Common::System::Optional<UINT64>();

        UINT64 out = 0;
        for (UINT64 i = 0; i < srcLen; )
        {
            unsigned char c = (unsigned char)src[i];
            UINT32 codepoint = 0;
            UINT64 remaining = srcLen - i;

            if (c <= 0x7F)
            {
                codepoint = c; i++;
            }
            else if ((c & 0xE0) == 0xC0 && remaining >= 2)
            {
                unsigned char c1 = (unsigned char)src[i+1];
                if ((c1 & 0xC0) == 0x80)
                {
                    codepoint = ((c & 0x1F) << 6) | (c1 & 0x3F);
                    if (codepoint < 0x80) codepoint = 0xFFFD; // overlong
                }
                else codepoint = 0xFFFD;
                i += 2;
            }
            else if ((c & 0xF0) == 0xE0 && remaining >= 3)
            {
                unsigned char c1 = (unsigned char)src[i+1];
                unsigned char c2 = (unsigned char)src[i+2];
                if (((c1 & 0xC0) == 0x80) && ((c2 & 0xC0) == 0x80))
                {
                    codepoint = ((c & 0x0F) << 12) | ((c1 & 0x3F) << 6) | (c2 & 0x3F);
                    if (codepoint < 0x800) codepoint = 0xFFFD; // overlong
                    if (codepoint >= 0xD800 && codepoint <= 0xDFFF) codepoint = 0xFFFD; // surrogates invalid
                }
                else codepoint = 0xFFFD;
                i += 3;
            }
            else if ((c & 0xF8) == 0xF0 && remaining >= 4)
            {
                unsigned char c1 = (unsigned char)src[i+1];
                unsigned char c2 = (unsigned char)src[i+2];
                unsigned char c3 = (unsigned char)src[i+3];
                if (((c1 & 0xC0) == 0x80) && ((c2 & 0xC0) == 0x80) && ((c3 & 0xC0) == 0x80))
                {
                    codepoint = ((c & 0x07) << 18) | ((c1 & 0x3F) << 12) | ((c2 & 0x3F) << 6) | (c3 & 0x3F);
                    if (codepoint < 0x10000 || codepoint > 0x10FFFF) codepoint = 0xFFFD;
                }
                else codepoint = 0xFFFD;
                i += 4;
            }
            else
            {
                codepoint = 0xFFFD; i += 1;
            }

            if (codepoint <= 0xFFFF)
            {
                outBuffer[out++] = (CHAR16)codepoint;
            }
            else
            {
                UINT32 cp = codepoint - 0x10000;
                outBuffer[out++] = (CHAR16)(0xD800 + ((cp >> 10) & 0x3FF));
                outBuffer[out++] = (CHAR16)(0xDC00 + (cp & 0x3FF));
            }
        }

        outBuffer[out] = u'\0';
        return Common::System::Optional<UINT64>(out);
    }

    Common::System::Optional<UINT64> UTF<CHAR16>::FromCString(const CHAR* src, CHAR16* outBuffer, UINT64 outBufferSize)
    {
        if (src == nullptr || outBuffer == nullptr) return Common::System::Optional<UINT64>();
        UINT64 len = UTF<CHAR>::Length(src);
        if (outBufferSize < len + 1) return Common::System::Optional<UINT64>();
        for (UINT64 i = 0; i < len; ++i) outBuffer[i] = (CHAR16)(unsigned char)src[i];
        outBuffer[len] = u'\0';
        return Common::System::Optional<UINT64>(len);
    }

	CHAR16* UTF<CHAR16>::FromCString(const CHAR* str)
	{
		/*Convert from ascii cstr to proper UTF16-2 byte string*/
		if (str == nullptr)
		{
			return nullptr;
		}

		if (str[0] == '\0')
		{
			return (CHAR16*)u"\0";
		}

		UINT64 len = UTF<CHAR>::Length(str);

		CHAR16* result = new CHAR16[len];

		for (UINT64 i = 0; i < len; i++)
		{
			result[i] = (CHAR16)(INT16)(str[i]);
		}
		return result;
	}

	Common::System::Optional<UINT64> UTF<CHAR16>::IndexOf(const CHAR16* str, const CHAR16* value, UINT64 startIndex, StringCulture culture)
	{
		// Get the first occurance of the 'value' in thr 'str' and return it's index
		BOOLEAN l = IsNullOrEmpty(str);
		BOOLEAN r = IsNullOrEmpty(value);

        if (l || r)
        {
            return Common::System::Optional<UINT64>();
        }

        if (l == r)
        {
            return Common::System::Optional<UINT64>(0);
        }

        UINT64 strLength = Length(str);
        UINT64 valueLength = Length(value);
        if (strLength != valueLength)
        {
            return Common::System::Optional<UINT64>();
        }

		switch (culture)
		{

		case Common::System::Environment::InvariantCulture:
		case Common::System::Environment::CurrentCulture:
		case Common::System::Environment::Ordinal:
		{
			for (UINT64 index = startIndex; index < strLength - valueLength; index++)
			{
				if (str[index] == value[0])
				{
					BOOLEAN match = TRUE;
					for (UINT64 i = 0; i < valueLength; i++)
					{
						if (str[index + i] != value[i])
						{
							match = FALSE;
							break;
						}
					}

            if (match)
            {
                return Common::System::Optional<UINT64>(index);
            }
				}
			}
            return Common::System::Optional<UINT64>();
		}

		case Common::System::Environment::InvariantCultureIgnoreCase:
		case Common::System::Environment::CurrentCultureIgnoreCase:
		case Common::System::Environment::OrdinalIgnoreCase:
		{
			for (UINT64 index = startIndex; index < strLength - valueLength; index++)
			{
				CHAR16 lChar = str[index];
				CHAR16 rChar = value[0];

				/*If the character is a lower case letter, switch it to upper for comparison*/

				if (lChar >= u'a' && lChar <= u'z')
				{
					lChar -= 32;
				}
				if (rChar >= u'a' && rChar <= u'z')
				{
					rChar -= 32;
				}

				if (lChar == rChar)
				{
					BOOLEAN match = TRUE;
					for (UINT64 i = 0; i < valueLength; i++)
					{
						CHAR16 lChar2 = str[index + i];
						CHAR16 rChar2 = value[i];
						/*If the character is a lower case letter, switch it to upper for comparison*/
						if (lChar2 >= u'a' && lChar2 <= u'z')
						{
							lChar2 -= 32;
						}
						if (rChar2 >= u'a' && rChar2 <= u'z')
						{
							rChar2 -= 32;
						}

						if (lChar != rChar)
						{
							match = FALSE;
							break;
						}
					}

            if (match)
            {
                return Common::System::Optional<UINT64>(index);
            }
				}
			}
            return Common::System::Optional<UINT64>();
		}

		default:
            return Common::System::Optional<UINT64>();
		}
	}

    Common::System::Optional<UINT64> UTF<CHAR16>::IndexOf(const CHAR16* str, const CHAR16 value, UINT64 startIndex, StringCulture culture)
	{
		// Get the first occurance of the 'value' in thr 'str' and return it's index
		BOOLEAN l = IsNullOrEmpty(str);

        if (l)
        {
            return Common::System::Optional<UINT64>();
        }

        UINT64 strLength = Length(str);
		if (strLength == 0)
		{
			return Common::System::Optional<UINT64>();
		}

		switch (culture)
		{

		case Common::System::Environment::InvariantCulture:
		case Common::System::Environment::CurrentCulture:
		case Common::System::Environment::Ordinal:
		{
			for (UINT64 index = startIndex; index < strLength; index++)
			{
                if (str[index] == value)
                {
                    return Common::System::Optional<UINT64>(index);
                }
			}
            return Common::System::Optional<UINT64>();
		}

		case Common::System::Environment::InvariantCultureIgnoreCase:
		case Common::System::Environment::CurrentCultureIgnoreCase:
		case Common::System::Environment::OrdinalIgnoreCase:
		{
			CHAR16 rChar = value;

			/*If the character is a lower case letter, switch it to upper for comparison*/

			if (rChar >= u'a' && rChar <= u'z')
			{
				rChar -= 32;
			}

			for (UINT64 index = startIndex; index < strLength; index++)
			{
				CHAR16 lChar = str[index];

				/*If the character is a lower case letter, switch it to upper for comparison*/

				if (lChar >= u'a' && lChar <= u'z')
				{
					lChar -= 32;
				}

				if (lChar == rChar)
				{
					return index;
				}
			}
			return -1;
		}

		default:
			return -1;
		}
	}

    Common::System::Optional<UINT64> UTF<CHAR16>::LastIndexOf(const CHAR16* str, const CHAR16* value, UINT64 startIndex, StringCulture culture)
	{
		// Get the first occurance of the 'value' in thr 'str' and return it's index
		BOOLEAN l = IsNullOrEmpty(str);
		BOOLEAN r = IsNullOrEmpty(value);

        if (l || r)
        {
            return Common::System::Optional<UINT64>();
        }

        if (l == r)
        {
            return Common::System::Optional<UINT64>(0);
        }

        UINT64 strLength = Length(str);
        UINT64 valueLength = Length(value);
        if (strLength < valueLength)
        {
            return Common::System::Optional<UINT64>();
        }

        if (startIndex >= strLength)
        {
            return Common::System::Optional<UINT64>();
        }

		switch (culture)
		{

		case Common::System::Environment::InvariantCulture:
		case Common::System::Environment::CurrentCulture:
		case Common::System::Environment::Ordinal:
		{
			UINT64 lastIndex;
			for (UINT64 index = startIndex; index < strLength - valueLength; index++)
			{
				if (str[index] == value[0])
				{
					BOOLEAN match = TRUE;
					for (UINT64 i = 0; i < valueLength; i++)
					{
						if (str[index + i] != value[i])
						{
							match = FALSE;
							break;
						}
					}

					if (match)
					{
						lastIndex = index;
					}
				}
			}
            return Common::System::Optional<UINT64>(lastIndex);
		}

		case Common::System::Environment::InvariantCultureIgnoreCase:
		case Common::System::Environment::CurrentCultureIgnoreCase:
		case Common::System::Environment::OrdinalIgnoreCase:
		{
			UINT64 lastIndex = 0;
			for (UINT64 index = startIndex; index < strLength - valueLength; index++)
			{
				CHAR16 lChar = str[index];
				CHAR16 rChar = value[0];

				/*If the character is a lower case letter, switch it to upper for comparison*/

				if (lChar >= u'a' && lChar <= u'z')
				{
					lChar -= 32;
				}
				if (rChar >= u'a' && rChar <= u'z')
				{
					rChar -= 32;
				}

				if (lChar == rChar)
				{
					BOOLEAN match = TRUE;
					for (UINT64 i = 0; i < valueLength; i++)
					{
						CHAR16 lChar2 = str[index + i];
						CHAR16 rChar2 = value[i];
						/*If the character is a lower case letter, switch it to upper for comparison*/
						if (lChar2 >= u'a' && lChar2 <= u'z')
						{
							lChar2 -= 32;
						}
						if (rChar2 >= u'a' && rChar2 <= u'z')
						{
							rChar2 -= 32;
						}

						if (lChar != rChar)
						{
							match = FALSE;
							break;
						}
					}

					if (match)
					{
						lastIndex = index;
					}
				}
			}
            return Common::System::Optional<UINT64>(lastIndex);
		}

		default:
            return Common::System::Optional<UINT64>();
		}
	}


    Common::System::Optional<UINT64> UTF<CHAR16>::LastIndexOf(const CHAR16* str, const CHAR16 value, UINT64 startIndex, StringCulture culture)
    {
        // Get the first occurance of the 'value' in thr 'str' and return it's index
        BOOLEAN l = IsNullOrEmpty(str);

        if (l)
        {
            return Common::System::Optional<UINT64>();
        }

        UINT64 strLength = Length(str);
        if (strLength == 0)
        {
            return Common::System::Optional<UINT64>();
        }

        if (startIndex >= strLength)
        {
            return Common::System::Optional<UINT64>();
        }

        switch (culture)
        {

        case Common::System::Environment::InvariantCulture:
        case Common::System::Environment::CurrentCulture:
        case Common::System::Environment::Ordinal:
        {
            UINT64 lastIndex =0;
            for (UINT64 index = startIndex; index < strLength; index++)
            {
                if (str[index] == value)
                {
                    lastIndex = index;
                }
            }
            return Common::System::Optional<UINT64>(lastIndex);
        }

        case Common::System::Environment::InvariantCultureIgnoreCase:
        case Common::System::Environment::CurrentCultureIgnoreCase:
        case Common::System::Environment::OrdinalIgnoreCase:
        {
            CHAR16 rChar = value;

            /*If the character is a lower case letter, switch it to upper for comparison*/

            if (rChar >= u'a' && rChar <= u'z')
            {
                rChar -= 32;
            }

            UINT64 lastIndex = 0;
            for (UINT64 index = startIndex; index < strLength; index++)
            {
                CHAR16 lChar = str[index];

                /*If the character is a lower case letter, switch it to upper for comparison*/

                if (lChar >= u'a' && lChar <= u'z')
                {
                    lChar -= 32;
                }

                if (lChar == rChar)
                {
                    lastIndex = index;
                }
            }
            return Common::System::Optional<UINT64>(lastIndex);
        }

        default:
            return Common::System::Optional<UINT64>();
        }
    }

	CHAR16** UTF<CHAR16>::Split(const CHAR16* str, const CHAR16* separator, OUT UINT64* count)
	{
		if (IsNullOrEmpty(str)) return nullptr;
		if (IsNullOrEmpty(separator)) return nullptr;

        UINT64 strLen = Length(str);
        UINT64 sepLen = Length(separator);
        if (strLen == 0 || sepLen == 0) return nullptr;

        if (strLen <= sepLen) return nullptr;


	}

	CHAR16** UTF<CHAR16>::Split(const CHAR16* str, const CHAR16 separator, OUT UINT64* count)
	{
		if (IsNullOrEmpty(str)) return nullptr;
        UINT64 strLen = Length(str);
        if (strLen == 0) return nullptr;

		// First, count the number of substrings
		UINT64 cnt = 1; // At least one substring

		for (UINT64 i = 0; i < strLen; i++)
		{
			if (str[i] == separator)
			{
				cnt++;
			}
		}

		*count = cnt;
		// Allocate memory for the array of substrings
		CHAR16** substrings = new CHAR16 * [cnt];
		// Extract substrings
		const CHAR16* start = str;
		size_t substringIndex = 0;

		const CHAR16* ptr = str;
		for (UINT64 i = 0; i < strLen; i++)
		{
			if (*ptr == separator)
			{
				// Calculate the length of the substring
				size_t length = ptr - start;
				// Allocate memory for the substring
				CHAR16* substring = new CHAR16[length + 1];
				// Copy the substring
				for (size_t i = 0; i < length; ++i)
				{
					substring[i] = start[i];
				}

				substring[length] = u'\0';
				// Add the substring to the array
				substrings[substringIndex++] = substring;
				// Move the start pointer to the next character
				start = ptr + 1;
			}
			if (*ptr == u'\0')
			{
				break;
			}
		}

		return substrings;
	}

	CHAR16* UTF<CHAR16>::Join(const CHAR16** str, const CHAR16* separator, UINT64 count)
	{
		if (count == 0) return nullptr;
		if (separator == nullptr) return nullptr;
		if (str == nullptr) return nullptr;

		UINT64 len = 0;
        Common::System::Optional<UINT64> sepLenOpt2 = Length(separator);
        if (!sepLenOpt2.HasValue()) return nullptr;
        UINT64 sepLen = sepLenOpt2.GetValue();

		for (UINT64 i = 0; i < count; i++)
		{
			if (!IsNullOrEmpty(str[i]))
			{
                Common::System::Optional<UINT64> tmpLenOpt = Length(str[i]);
                if (!tmpLenOpt.HasValue()) return nullptr;
                len += tmpLenOpt.GetValue() + sepLen;
			}
		}

		CHAR16* result = new CHAR16[len];

		UINT64 index = 0;
		for (UINT64 i = 0; i < count; i++)
		{
			if (!IsNullOrEmpty(str[i]))
			{
				const CHAR16* ptr = str[i];
				UINT64 c = 0;
				while (*ptr != u'\0')
				{
					result[index++] = *ptr;
					ptr++;
				}
				for (UINT64 j = 0; j < sepLen; j++)
				{
					result[index++] = separator[j];
				}
			}
		}

		result[len - 1] = '\0';
		return result;
	}

	CHAR16* UTF<CHAR16>::Join(const CHAR16** str, const CHAR16 separator, UINT64 count)
	{
		if (count == 0) return nullptr;
		if (str == nullptr) return nullptr;

		UINT64 len = 0;

        for (UINT64 i = 0; i < count; i++)
        {
            if (!IsNullOrEmpty(str[i]))
            {
                Common::System::Optional<UINT64> tmpLenOpt = Length(str[i]);
                if (!tmpLenOpt.HasValue()) return nullptr;
                len += tmpLenOpt.GetValue() + 1;
            }
        }

		CHAR16* result = new CHAR16[len];

		UINT64 index = 0;
		for (UINT64 i = 0; i < count; i++)
		{
			if (!IsNullOrEmpty(str[i]))
			{
				const CHAR16* ptr = str[i];
				UINT64 c = 0;
				while (*ptr != u'\0')
				{
					result[index++] = *ptr;
					ptr++;
				}
				result[index++] = separator;
			}
		}
		result[len - 1] = '\0';
		return result;
	}
}