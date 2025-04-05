#include <System/Environment/Unicode/UTFCHAR16.h>

namespace Common::System::Environment
{
	const CHAR16 UTF<CHAR16>::NewLine[3]{u'\r', u'\n',u'\0'};

	CHAR16 _UTF16_GUIDTOSTRING[43] = { u'{',u'\0',u'\0',u'\0',u'\0',u'\0',u'\0',u'\0',u'\0',u'-',u'\0',u'\0',u'\0',u'\0',u'-',u'\0',u'\0',u'\0',u'\0',u'-',u'\0',u'\0',u'\0',u'\0',u'-',u'\0',u'\0',u'\0',u'\0',u'\0',u'\0',u'\0',u'\0',u'\0',u'\0',u'\0',u'\0',u'\0',u'\0',u'\0',u'\0',u'}',u'\0' };
	CHAR16 _UTF16_HEXCHARS[17] = { u'0',u'1',u'2',u'3',u'4',u'5',u'6',u'7',u'8',u'9',u'A',u'B',u'C',u'D',u'E',u'F' };
	CHAR16 _UTF16_HEXSTRING[18] = { u'\0',u'\0',u'\0',u'\0',u'\0',u'\0',u'\0',u'\0',u'\0',u'\0',u'\0',u'\0',u'\0',u'\0',u'\0',u'\0',u'\0',u'\0' };
	CHAR16 _UTF16_VALUETOSTRING[23] = { u'\0',u'\0',u'\0',u'\0',u'\0',u'\0',u'\0',u'\0',u'\0',u'\0',u'\0',u'\0',u'\0',u'\0',u'\0',u'\0',u'\0',u'\0',u'\0',u'\0',u'\0',u'\0',u'\0' };
	CHAR16 _UTF16_WHITESPACECHARS[30] = { 0x0009,0x000A,0x000B,0x000C,0x000D,0x0020,0x0085,0x00A0,0x1680,0x2000,0x2001,0x2003,0x2004,0x2005,0x2006,0x2007,0x02008,0x2009,0x200A,0x2028,0x2029,0x202F,0x205F,0x3000,0x180E,0x200B,0x200C,0x200D,0x2060,0xFEFF };

	constinit const CHAR16* _UTF16_ABORTED = u"ABORTED";
	constinit const CHAR16* _UTF16_ACCESS_DENIED = u"ACCESS_DENIED";
	constinit const CHAR16* _UTF16_ALREADY_STARTED = u"ALREADY_STARTED";
	constinit const CHAR16* _UTF16_BAD_BUFFER_SIZE = u"BAD_BUFFER_SIZE";
	constinit const CHAR16* _UTF16_BOOLEAN_FALSE = u"False";
	constinit const CHAR16* _UTF16_BOOLEAN_TRUE = u"True";
	constinit const CHAR16* _UTF16_BUFFER_TOO_SMALL = u"BUFFER_TOO_SMALL";
	constinit const CHAR16* _UTF16_COMPROMISED_DATA = u"COMPROMISED_DATA";
	constinit const CHAR16* _UTF16_CRC_ERROR = u"CRC_ERROR";
	constinit const CHAR16* _UTF16_DEVICE_ERROR = u"DEVICE_ERROR";
	constinit const CHAR16* _UTF16_END_OF_FILE = u"END_OF_FILE";
	constinit const CHAR16* _UTF16_END_OF_MEDIA = u"END_OF_MEDIA";
	constinit const CHAR16* _UTF16_HTTP_ERROR = u"HTTP_ERROR";
	constinit const CHAR16* _UTF16_ICMP_ERROR = u"ICMP_ERROR";
	constinit const CHAR16* _UTF16_INCOMPATIBLE_VERSION = u"INCOMPATIBLE_VERSION";
	constinit const CHAR16* _UTF16_INVALID_LANGUAGE = u"INVALID_LANGUAGE";
	constinit const CHAR16* _UTF16_INVALID_PARAMETER = u"INVALID_PARAMETER";
	constinit const CHAR16* _UTF16_IP_ADDRESS_CONFLICT = u"IP_ADDRESS_CONFLICT";
	constinit const CHAR16* _UTF16_LOAD_ERROR = u"LOAD_ERROR";
	constinit const CHAR16* _UTF16_MEDIA_CHANGED = u"MEDIA_CHANGED";
	constinit const CHAR16* _UTF16_NO_MAPPING = u"NO_MAPPING";
	constinit const CHAR16* _UTF16_NO_MEDIA = u"NO_MEDIA";
	constinit const CHAR16* _UTF16_NO_RESPONSE = u"NO_RESPONSE";
	constinit const CHAR16* _UTF16_NOT_FOUND = u"NOT_FOUND";
	constinit const CHAR16* _UTF16_NOT_READY = u"NOT_READY";
	constinit const CHAR16* _UTF16_NOT_STARTED = u"NOT_STARTED";
	constinit const CHAR16* _UTF16_OUT_OF_RESOURCES = u"OUT_OF_RESOURCES";
	constinit const CHAR16* _UTF16_PROTOCOL_ERROR = u"PROTOCOL_ERROR";
	constinit const CHAR16* _UTF16_SECURITY_VIOLATION = u"SECURITY_VIOLATION";
	constinit const CHAR16* _UTF16_SUCCESS = u"SUCCESS";
	constinit const CHAR16* _UTF16_TFTP_ERROR = u"TFTP_ERROR";
	constinit const CHAR16* _UTF16_TIMEOUT = u"TIMEOUT";
	constinit const CHAR16* _UTF16_UNSUPPORTED = u"UNSUPPORTED";
	constinit const CHAR16* _UTF16_VOLUME_CORRUPTED = u"VOLUME_CORRUPTED";
	constinit const CHAR16* _UTF16_VOLUME_FULL = u"VOLUME_FULL";
	constinit const CHAR16* _UTF16_WARN_BUFFER_TOO_SMALL = u"WARN_BUFFER_TOO_SMALL";
	constinit const CHAR16* _UTF16_WARN_DELETE_FAILURE = u"WARN_DELETE_FAILURE";
	constinit const CHAR16* _UTF16_WARN_FILE_SYSTEM = u"WARN_FILE_SYSTEM";
	constinit const CHAR16* _UTF16_WARN_RESET_REQUIRED = u"WARN_RESET_REQUIRED";
	constinit const CHAR16* _UTF16_WARN_STALE_DATA = u"WARN_STALE_DATA";
	constinit const CHAR16* _UTF16_WARN_UNKNOWN_GLYPH = u"WARN_UNKNOWN_GLYPH";
	constinit const CHAR16* _UTF16_WARN_WRITE_FAILURE = u"WARN_WRITE_FAILURE";
	constinit const CHAR16* _UTF16_WRITE_PROTECTED = u"WRITE_PROTECTED";

	constinit const CHAR16* _UTF16_ALLOC_STATUS_SUCCESS = u"SUCCESS";
	constinit const CHAR16* _UTF16_ALLOC_STATUS_INVALID_PARAMETER = u"INVALID_PARAMETER";
	constinit const CHAR16* _UTF16_ALLOC_STATUS_NOT_ENOUGH_MEMORY = u"NOT_ENOUGH_MEMORY";
	constinit const CHAR16* _UTF16_ALLOC_STATUS_NOT_ENOUGH_PAGES = u"NOT_ENOUGH_PAGES";
	constinit const CHAR16* _UTF16_ALLOC_STATUS_ACCESS_DENIED = u"ACCESS_DENIED";
	constinit const CHAR16* _UTF16_ALLOC_STATUS_UNKNOWN = u"UNKNOWN";

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
		for (; i > 0; i >>= 4)
		{
			_UTF16_HEXSTRING[i] = _UTF16_HEXCHARS[i & 0xF];
		}
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

	CHAR16* UTF<CHAR16>::ToString(const EFI::EFI_GUID guid)
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

	CHAR16* UTF<CHAR16>::ToString(const EFI::EFI_STATUS status)
	{
		switch (status)
		{
		case EFI::EFI_STATUS::ABORTED:
			return (CHAR16*)_UTF16_ABORTED;
		case EFI::EFI_STATUS::ACCESS_DENIED:
			return (CHAR16*)_UTF16_ACCESS_DENIED;
		case EFI::EFI_STATUS::ALREADY_STARTED:
			return (CHAR16*)_UTF16_ALREADY_STARTED;
		case EFI::EFI_STATUS::BAD_BUFFER_SIZE:
			return (CHAR16*)_UTF16_BAD_BUFFER_SIZE;
		case EFI::EFI_STATUS::BUFFER_TOO_SMALL:
			return (CHAR16*)_UTF16_BUFFER_TOO_SMALL;
		case EFI::EFI_STATUS::COMPROMISED_DATA:
			return (CHAR16*)_UTF16_COMPROMISED_DATA;
		case EFI::EFI_STATUS::CRC_ERROR:
			return (CHAR16*)_UTF16_CRC_ERROR;
		case EFI::EFI_STATUS::DEVICE_ERROR:
			return (CHAR16*)_UTF16_DEVICE_ERROR;
		case EFI::EFI_STATUS::END_OF_FILE:
			return (CHAR16*)_UTF16_END_OF_FILE;
		case EFI::EFI_STATUS::END_OF_MEDIA:
			return (CHAR16*)_UTF16_END_OF_MEDIA;
		case EFI::EFI_STATUS::HTTP_ERROR:
			return (CHAR16*)_UTF16_HTTP_ERROR;
		case EFI::EFI_STATUS::ICMP_ERROR:
			return (CHAR16*)_UTF16_ICMP_ERROR;
		case EFI::EFI_STATUS::INCOMPATIBLE_VERSION:
			return (CHAR16*)_UTF16_INCOMPATIBLE_VERSION;
		case EFI::EFI_STATUS::INVALID_LANGUAGE:
			return (CHAR16*)_UTF16_INVALID_LANGUAGE;
		case EFI::EFI_STATUS::INVALID_PARAMETER:
			return (CHAR16*)_UTF16_INVALID_PARAMETER;
		case EFI::EFI_STATUS::IP_ADDRESS_CONFLICT:
			return (CHAR16*)_UTF16_IP_ADDRESS_CONFLICT;
		case EFI::EFI_STATUS::LOAD_ERROR:
			return (CHAR16*)_UTF16_LOAD_ERROR;
		case EFI::EFI_STATUS::MEDIA_CHANGED:
			return (CHAR16*)_UTF16_MEDIA_CHANGED;
		case EFI::EFI_STATUS::NO_MAPPING:
			return (CHAR16*)_UTF16_NO_MAPPING;
		case EFI::EFI_STATUS::NO_MEDIA:
			return (CHAR16*)_UTF16_NO_MEDIA;
		case EFI::EFI_STATUS::NO_RESPONSE:
			return (CHAR16*)_UTF16_NO_RESPONSE;
		case EFI::EFI_STATUS::NOT_FOUND:
			return (CHAR16*)_UTF16_NOT_FOUND;
		case EFI::EFI_STATUS::NOT_READY:
			return (CHAR16*)_UTF16_NOT_READY;
		case EFI::EFI_STATUS::NOT_STARTED:
			return (CHAR16*)_UTF16_NOT_STARTED;
		case EFI::EFI_STATUS::OUT_OF_RESOURCES:
			return (CHAR16*)_UTF16_OUT_OF_RESOURCES;
		case EFI::EFI_STATUS::PROTOCOL_ERROR:
			return (CHAR16*)_UTF16_PROTOCOL_ERROR;
		case EFI::EFI_STATUS::SECURITY_VIOLATION:
			return (CHAR16*)_UTF16_SECURITY_VIOLATION;
		case EFI::EFI_STATUS::SUCCESS:
			return (CHAR16*)_UTF16_SUCCESS;
		case EFI::EFI_STATUS::TFTP_ERROR:
			return (CHAR16*)_UTF16_TFTP_ERROR;
		case EFI::EFI_STATUS::TIMEOUT:
			return (CHAR16*)_UTF16_TIMEOUT;
		case EFI::EFI_STATUS::UNSUPPORTED:
			return (CHAR16*)_UTF16_UNSUPPORTED;
		case EFI::EFI_STATUS::VOLUME_CORRUPTED:
			return (CHAR16*)_UTF16_VOLUME_CORRUPTED;
		case EFI::EFI_STATUS::VOLUME_FULL:
			return (CHAR16*)_UTF16_VOLUME_FULL;
		case EFI::EFI_STATUS::WARN_BUFFER_TOO_SMALL:
			return (CHAR16*)_UTF16_WARN_BUFFER_TOO_SMALL;
		case EFI::EFI_STATUS::WARN_DELETE_FAILURE:
			return (CHAR16*)_UTF16_WARN_DELETE_FAILURE;
		case EFI::EFI_STATUS::WARN_FILE_SYSTEM:
			return (CHAR16*)_UTF16_WARN_FILE_SYSTEM;
		case EFI::EFI_STATUS::WARN_RESET_REQUIRED:
			return (CHAR16*)_UTF16_WARN_RESET_REQUIRED;
		case EFI::EFI_STATUS::WARN_STALE_DATA:
			return (CHAR16*)_UTF16_WARN_STALE_DATA;
		case EFI::EFI_STATUS::WARN_UNKNOWN_GLYPH:
			return (CHAR16*)_UTF16_WARN_UNKNOWN_GLYPH;
		case EFI::EFI_STATUS::WARN_WRITE_FAILURE:
			return (CHAR16*)_UTF16_WARN_WRITE_FAILURE;
		case EFI::EFI_STATUS::WRITE_PROTECTED:
			return (CHAR16*)_UTF16_WRITE_PROTECTED;
		default:
			return nullptr;
		}
	}

	CHAR16* UTF<CHAR16>::ToString(const Common::System::MemoryManagement::AllocatorStatus status)
	{
		switch (status)
		{
		case Common::System::MemoryManagement::AllocatorStatus::Success:
			return (CHAR16*)_UTF16_ALLOC_STATUS_SUCCESS;
		case Common::System::MemoryManagement::AllocatorStatus::Invalid_Parameters:
			return (CHAR16*)_UTF16_ALLOC_STATUS_INVALID_PARAMETER;
		case Common::System::MemoryManagement::AllocatorStatus::Not_Enough_Memory:
			return (CHAR16*)_UTF16_ALLOC_STATUS_NOT_ENOUGH_MEMORY;
		case Common::System::MemoryManagement::AllocatorStatus::Not_Enough_Pages:
			return (CHAR16*)_UTF16_ALLOC_STATUS_NOT_ENOUGH_PAGES;
		case Common::System::MemoryManagement::AllocatorStatus::Access_Denied:
			return (CHAR16*)_UTF16_ALLOC_STATUS_ACCESS_DENIED;
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

	CHAR16* UTF<CHAR16>::ToString(const BOOLEAN boolean)
	{
		if (boolean)
		{
			return (CHAR16*)_UTF16_BOOLEAN_TRUE;
		}
		else
		{
			return (CHAR16*)_UTF16_BOOLEAN_FALSE;
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
		BOOLEAN lBool = IsNullOrEmpty(l);
		BOOLEAN rBool = IsNullOrEmpty(r);

		if (lBool || rBool)
		{
			return FALSE;
		}

		if (lBool && rBool)
		{
			return TRUE;
		}

		UINT64 lLength = UTF<CHAR16>::Length(l);
		UINT64 rLength = UTF<CHAR16>::Length(r);

		if (lLength != rLength)
		{
			return FALSE;
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

		if (l || r)
		{
			return FALSE;
		}

		if (l && r)
		{
			return TRUE;
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

		if (l || r)
		{
			return FALSE;
		}

		if (l && r)
		{
			return TRUE;
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

		if (l || r)
		{
			return FALSE;
		}

		if (l && r)
		{
			return TRUE;
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
		};

		if (str[0] == u'\0')
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
		};

		UINT64 index = 0;
		INT64 charindex = -1;
		while (str[index] != u'\0')
		{
			UINT64 i = 0;
			for (UINT64 i = 0; i < 30; i++)
			{
				if (str[index] != _UTF16_WHITESPACECHARS[i])
				{
					charindex = index;
				}
			}
			index++;
		}

		return charindex == -1;
	}

	BOOLEAN UTF<CHAR16>::IsNullEmptyOrWhiteSpace(const CHAR16* str)
	{
		if (str == nullptr)
		{
			return TRUE;
		};

		if (str[0] == u'\0')
		{
			return TRUE;
		}

		/*Check Entire string, if any of that characters are non whitespace characters, return false otherwise return true*/

		UINT64 index = 0;
		INT64 charindex = -1;

		while (str[index] != u'\0')
		{
			UINT64 i = 0;
			for (UINT64 i = 0; i < 30; i++)
			{
				if (str[index] != _UTF16_WHITESPACECHARS[i])
				{
					charindex = index;
				}
			}
			index++;
		}

		return charindex == -1;
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
		if (str == nullptr)
		{
			return nullptr;
		}

		if (str[0] == '\0')
		{
			return (CHAR16*)u"\0";
		}

		UINT64 len = UTF<CHAR8>::Length(str);

		CHAR16* result = new CHAR16[len];

		for (UINT64 i = 0; i < len; i++)
		{
			result[i] = (CHAR16)str[i];
		}
		return result;
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

	INT64 UTF<CHAR16>::IndexOf(const CHAR16* str, const CHAR16* value, UINT64 startIndex, StringCulture culture)
	{
		// Get the first occurance of the 'value' in thr 'str' and return it's index
		BOOLEAN l = IsNullOrEmpty(str);
		BOOLEAN r = IsNullOrEmpty(value);

		if (l || r)
		{
			return -1;
		}

		if (l && r)
		{
			return 0;
		}

		UINT64 strLength = Length(str);

		if (startIndex >= strLength)
		{
			return -1;
		}

		UINT64 valueLength = Length(value);

		if (strLength < valueLength)
		{
			return -1;
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
						return index;
					}
				}
			}
			return -1;
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
						return index;
					}
				}
			}
			return -1;
		}

		default:
			return -1;
		}
	}

	INT64 UTF<CHAR16>::IndexOf(const CHAR16* str, const CHAR16 value, UINT64 startIndex, StringCulture culture)
	{
		// Get the first occurance of the 'value' in thr 'str' and return it's index
		BOOLEAN l = IsNullOrEmpty(str);

		if (l)
		{
			return -1;
		}

		UINT64 strLength = Length(str);

		if (startIndex >= strLength)
		{
			return -1;
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
					return index;
				}
			}
			return -1;
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

	INT64 UTF<CHAR16>::LastIndexOf(const CHAR16* str, const CHAR16* value, UINT64 startIndex, StringCulture culture)
	{
		// Get the first occurance of the 'value' in thr 'str' and return it's index
		BOOLEAN l = IsNullOrEmpty(str);
		BOOLEAN r = IsNullOrEmpty(value);

		if (l || r)
		{
			return -1;
		}

		if (l && r)
		{
			return 0;
		}

		UINT64 strLength = Length(str);

		if (startIndex >= strLength)
		{
			return -1;
		}

		UINT64 valueLength = Length(value);

		if (strLength < valueLength)
		{
			return -1;
		}

		switch (culture)
		{

		case Common::System::Environment::InvariantCulture:
		case Common::System::Environment::CurrentCulture:
		case Common::System::Environment::Ordinal:
		{
			int lastIndex = -1;
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
			return lastIndex;
		}

		case Common::System::Environment::InvariantCultureIgnoreCase:
		case Common::System::Environment::CurrentCultureIgnoreCase:
		case Common::System::Environment::OrdinalIgnoreCase:
		{
			INT64 lastIndex = -1;
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
			return lastIndex;
		}

		default:
			return -1;
		}
	}


	INT64 UTF<CHAR16>::LastIndexOf(const CHAR16* str, const CHAR16 value, UINT64 startIndex, StringCulture culture)
	{
		// Get the first occurance of the 'value' in thr 'str' and return it's index
		BOOLEAN l = IsNullOrEmpty(str);

		if (l)
		{
			return -1;
		}

		UINT64 strLength = Length(str);

		if (startIndex >= strLength)
		{
			return -1;
		}

		switch (culture)
		{

		case Common::System::Environment::InvariantCulture:
		case Common::System::Environment::CurrentCulture:
		case Common::System::Environment::Ordinal:
		{
			INT64 lastIndex = -1;
			for (UINT64 index = startIndex; index < strLength; index++)
			{
				if (str[index] == value)
				{
					lastIndex = index;
				}
			}
			return lastIndex;
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

			INT64 lastIndex = -1;
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
			return lastIndex;
		}

		default:
			return -1;
		}
	}

	CHAR16** UTF<CHAR16>::Split(const CHAR16* str, const CHAR16* separator, OUT UINT64* count)
	{
		if (IsNullOrEmpty(str)) return nullptr;
		if (IsNullOrEmpty(separator)) return nullptr;

		UINT64 strLen = Length(str);
		UINT64 sepLen = Length(separator);

		if (strLen <= sepLen) return nullptr;


	}

	CHAR16** UTF<CHAR16>::Split(const CHAR16* str, const CHAR16 separator, OUT UINT64* count)
	{
		if (IsNullOrEmpty(str)) return nullptr;
		UINT64 strLen = Length(str);

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
		UINT64 sepLen = Length(separator);

		for (UINT64 i = 0; i < count; i++)
		{
			if (!IsNullOrEmpty(str[i]))
			{
				len += Length(str[i]) + sepLen;
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
				len += Length(str[i]) + 1;
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