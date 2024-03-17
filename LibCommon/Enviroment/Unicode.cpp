#pragma once
#include "TypeDefs.h"
#include <EFI_GUID.h>
#include <EFI_STATUS.h>
#include "Unicode.h"

namespace Common::Enviroment
{
#pragma region UTF16
	CHAR16 _UTF16_GUIDTOSTRING[43] = { u'{',u'\0',u'\0',u'\0',u'\0',u'\0',u'\0',u'\0',u'\0',u'-',u'\0',u'\0',u'\0',u'\0',u'-',u'\0',u'\0',u'\0',u'\0',u'-',u'\0',u'\0',u'\0',u'\0',u'-',u'\0',u'\0',u'\0',u'\0',u'\0',u'\0',u'\0',u'\0',u'\0',u'\0',u'\0',u'\0',u'\0',u'\0',u'\0',u'\0',u'}',u'\0' };
	CHAR16 _UTF16_HEXCHARS[17] = { u'0',u'1',u'2',u'3',u'4',u'5',u'6',u'7',u'8',u'9',u'A',u'B',u'C',u'D',u'E',u'F' };
	CHAR16 _UTF16_HEXSTRING[18] = { u'\0',u'\0',u'\0',u'\0',u'\0',u'\0',u'\0',u'\0',u'\0',u'\0',u'\0',u'\0',u'\0',u'\0',u'\0',u'\0',u'\0',u'\0' };
	CHAR16 _UTF16_VALUETOSTRING[23] = { u'\0',u'\0',u'\0',u'\0',u'\0',u'\0',u'\0',u'\0',u'\0',u'\0',u'\0',u'\0',u'\0',u'\0',u'\0',u'\0',u'\0',u'\0',u'\0',u'\0',u'\0',u'\0',u'\0' };
	CHAR16 _UTF16_WHITESPACECHARS[30] = { 0x0009,0x000A,0x000B,0x000C,0x000D,0x0020,0x0085,0x00A0,0x1680,0x2000,0x2001,0x2003,0x2004,0x2005,0x2006,0x2007,0x02008,0x2009,0x200A,0x2028,0x2029,0x202F,0x205F,0x3000,0x180E,0x200B,0x200C,0x200D,0x2060,0xFEFF };
	const CHAR16* Common::Enviroment::UTF16::NewLine = u"\r\n";
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

	
	CHAR16* UTF16::ToHex(const INT16 value)
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

	CHAR16* UTF16::ToHex(const INT32 value)
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

	CHAR16* UTF16::ToHex(const INT64 value)
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

	CHAR16* UTF16::ToHex(const INT8 value)
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

	CHAR16* UTF16::ToHex(const UINT16 value)
	{
		_UTF16_HEXSTRING[0] = _UTF16_HEXCHARS[(value >> 12) & 0xF];
		_UTF16_HEXSTRING[1] = _UTF16_HEXCHARS[(value >> 8) & 0xF];
		_UTF16_HEXSTRING[2] = _UTF16_HEXCHARS[(value >> 4) & 0xF];
		_UTF16_HEXSTRING[3] = _UTF16_HEXCHARS[value & 0xF];
		_UTF16_HEXSTRING[4] = u'\0';
		return &_UTF16_HEXSTRING[0];
	}

	CHAR16* UTF16::ToHex(const UINT32 value)
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

	CHAR16* UTF16::ToHex(const UINT64 value)
	{
		UINTN i = value;
		for (;i > 0; i >>= 4)
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

	CHAR16* UTF16::ToHex(const UINT8 value)
	{
		_UTF16_HEXSTRING[0] = _UTF16_HEXCHARS[(value >> 4) & 0xF];
		_UTF16_HEXSTRING[1] = _UTF16_HEXCHARS[value & 0xF];
		_UTF16_HEXSTRING[2] = u'\0';
		return &_UTF16_HEXSTRING[0];
	}

	CHAR16* UTF16::ToHex(const VOID_PTR ptr)
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

	CHAR16* UTF16::ToString(const EFI::EFI_GUID guid)
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

	CHAR16* UTF16::ToString(const EFI::EFI_STATUS status)
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

	CHAR16* UTF16::ToString(const Common::System::AllocatorStatus status)
	{
		switch (status)
		{
		case Common::System::AllocatorStatus::Success:
			return (CHAR16*)_UTF16_ALLOC_STATUS_SUCCESS;
		case Common::System::AllocatorStatus::Invalid_Parameters:
			return (CHAR16*)_UTF16_ALLOC_STATUS_INVALID_PARAMETER;
		case Common::System::AllocatorStatus::Not_Enough_Memory:
			return (CHAR16*)_UTF16_ALLOC_STATUS_NOT_ENOUGH_MEMORY;
		case Common::System::AllocatorStatus::Not_Enough_Pages:
			return (CHAR16*)_UTF16_ALLOC_STATUS_NOT_ENOUGH_PAGES;
		case Common::System::AllocatorStatus::Access_Denied:
			return (CHAR16*)_UTF16_ALLOC_STATUS_ACCESS_DENIED;
		}
	}

	CHAR16* UTF16::ToString(const INT16 value)
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
		bool isNegative = false;
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

	CHAR16* UTF16::ToString(const INT32 value)
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
		bool isNegative = false;
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

	CHAR16* UTF16::ToString(const INT64 value)
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
		bool isNegative = false;
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

	CHAR16* UTF16::ToString(const INT8 value)
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
		bool isNegative = false;
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

	CHAR16* UTF16::ToString(const UINT16 value)
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

	CHAR16* UTF16::ToString(const UINT32 value)
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

	CHAR16* UTF16::ToString(const UINT64 value)
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

	CHAR16* UTF16::ToString(const UINT8 value)
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

	CHAR16* UTF16::ToString(const VOID_PTR ptr)
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

	CHAR16* UTF16::ToString(const BOOLEAN boolean)
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

	UINTN UTF16::Length(const CHAR16* str)
	{
		if (str == nullptr)
		{
			return 0;
		}

		if (str[0] == u'\0')
		{
			return 1;
		}

		UINTN index = 0;
		UINTN len = 1;
		while (str[index] != u'\0')
		{
			len++;
			index++;
		}
		return len;
	}

	BOOLEAN UTF16::Compare(const CHAR16* l, const CHAR16* r, StringCulture culture)
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

		UINTN lLength = Length(l);
		UINTN rLength = Length(r);

		if (lLength != rLength)
		{
			return FALSE;
		}

		switch (culture)
		{
		case Common::Enviroment::InvariantCulture:
		case Common::Enviroment::CurrentCulture:
		case Common::Enviroment::Ordinal:
		{
			/*Binary Comparison of string*/

			for (UINTN index = 0; index < lLength; index++)
			{
				if (l[index] != r[index])
				{
					return FALSE;
				}
			}
			return TRUE;
		}
		case Common::Enviroment::InvariantCultureIgnoreCase:
		case Common::Enviroment::CurrentCultureIgnoreCase:
		case Common::Enviroment::OrdinalIgnoreCase:
		{
			/*Binary Comparison, Ignoring Case of string*/

			UINTN index = 0;

			for (UINTN index = 0; index < lLength; index++)
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

	BOOLEAN UTF16::StartsWith(const CHAR16* str, const CHAR16* value, StringCulture culture)
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

		UINTN strLength = Length(str);
		UINTN valueLength = Length(value);

		if (strLength < valueLength)
		{
			return FALSE;
		}

		switch (culture)
		{
		case Common::Enviroment::InvariantCulture:
		case Common::Enviroment::CurrentCulture:
		case Common::Enviroment::Ordinal:
		{
			for (UINTN index = 0; index < valueLength; index++)
			{
				if (str[index] != value[index])
				{
					return FALSE;
				}
			}
			return TRUE;
		}
		case Common::Enviroment::InvariantCultureIgnoreCase:
		case Common::Enviroment::CurrentCultureIgnoreCase:
		case Common::Enviroment::OrdinalIgnoreCase:
		{
			for (UINTN index = 0; index < valueLength; index++)
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

	BOOLEAN UTF16::EndsWith(const CHAR16* str, const CHAR16* value, StringCulture culture)
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

		UINTN strLength = Length(str);
		UINTN valueLength = Length(value);

		if (strLength < valueLength)
		{
			return FALSE;
		}

		switch (culture)
		{
		case Common::Enviroment::InvariantCulture:
		case Common::Enviroment::CurrentCulture:
		case Common::Enviroment::Ordinal:
		{
			UINTN index = 0;
			for (UINTN index = 0; index < valueLength; index++)
			{
				if (str[strLength - valueLength + index] != value[index])
				{
					return FALSE;
				}
			}
			return TRUE;
		}
		case Common::Enviroment::InvariantCultureIgnoreCase:
		case Common::Enviroment::CurrentCultureIgnoreCase:
		case Common::Enviroment::OrdinalIgnoreCase:
		{
			UINTN index = 0;
			for (UINTN index = 0; index < valueLength; index++)
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

	BOOLEAN UTF16::Contains(const CHAR16* str, const CHAR16* value, StringCulture culture)
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

		UINTN strLength = Length(str);
		UINTN valueLength = Length(value);

		if (strLength < valueLength)
		{
			return FALSE;
		}

		switch (culture)
		{
		case Common::Enviroment::InvariantCulture:
		case Common::Enviroment::CurrentCulture:
		case Common::Enviroment::Ordinal:
		{
			UINTN index = 0;
			for (UINTN index = 0; index < strLength - valueLength; index++)
			{
				if (str[index] == value[0])
				{
					BOOLEAN match = TRUE;
					for (UINTN i = 0; i < valueLength; i++)
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
		case Common::Enviroment::InvariantCultureIgnoreCase:
		case Common::Enviroment::CurrentCultureIgnoreCase:
		case Common::Enviroment::OrdinalIgnoreCase:
		{
			UINTN index = 0;
			for (UINTN index = 0; index < strLength - valueLength; index++)
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
					for (UINTN i = 0; i < valueLength; i++)
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

	BOOLEAN UTF16::IsNullOrEmpty(const CHAR16* str)
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

	BOOLEAN UTF16::IsNullOrWhiteSpace(const CHAR16* str)
	{
		if (str == nullptr)
		{
			return TRUE;
		};

		if (str[0] == u'\0')
		{
			return TRUE;
		}

		UINTN index = 0;
		while (str[index] != u'\0')
		{
			UINTN i = 0;
			for (UINTN i = 0; i < 30; i++)
			{
				if (str[index] == _UTF16_WHITESPACECHARS[i])
				{
					return TRUE;
				}
			}
			index++;
		}
		return FALSE;
	}

	CHAR16* UTF16::FromCharArray(CHAR16 arr[], UINTN Length)
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

		for (UINTN i = 0; i < Length; i++)
		{
			result[i] = arr[i];
		}
		result[Length] = u'\0';
		return result;
	}

	CHAR16* UTF16::FromUTF8String(const CHAR8* str)
	{
		if (str == nullptr)
		{
			return nullptr;
		}

		if (str[0] == '\0')
		{
			return (CHAR16*)u"\0";
		}

		UINTN len = UTF8::Length(str);

		CHAR16* result = new CHAR16[len];

		for (UINTN i = 0; i < len; i++)
		{
			result[i] = (CHAR16)str[i];
		}
		return result;
	}

	CHAR16* UTF16::FromCString(const CCHAR* str)
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

		UINTN len = CString::Length(str);

		CHAR16* result = new CHAR16[len];

		for (UINTN i = 0; i < len; i++)
		{
			result[i] = (CHAR16)(INT16)(str[i]);
		}
		return result;

	}

#pragma endregion
#pragma region UTF8
	CHAR8 _UTF8_GUIDTOSTRING[43] = { u8'{',u8'\0',u8'\0',u8'\0',u8'\0',u8'\0',u8'\0',u8'\0',u8'\0',u8'-',u8'\0',u8'\0',u8'\0',u8'\0',u8'-',u8'\0',u8'\0',u8'\0',u8'\0',u8'-',u8'\0',u8'\0',u8'\0',u8'\0',u8'-',u8'\0',u8'\0',u8'\0',u8'\0',u8'\0',u8'\0',u8'\0',u8'\0',u8'\0',u8'\0',u8'\0',u8'\0',u8'}',u8'\0' };
	CHAR8 _UTF8_HEXCHARS[17] = { u8'0',u8'1',u8'2',u8'3',u8'4',u8'5',u8'6',u8'7',u8'8',u8'9',u8'A',u8'B',u8'C',u8'D',u8'E',u8'F' };
	CHAR8 _UTF8_HEXSTRING[18] = { u8'\0',u8'\0',u8'\0',u8'\0',u8'\0',u8'\0',u8'\0',u8'\0',u8'\0',u8'\0',u8'\0',u8'\0',u8'\0',u8'\0',u8'\0',u8'\0',u8'\0',u8'\0' };
	CHAR8 _UTF8_VALUETOSTRING[23] = { u8'\0',u8'\0',u8'\0',u8'\0',u8'\0',u8'\0',u8'\0',u8'\0',u8'\0',u8'\0',u8'\0',u8'\0',u8'\0',u8'\0',u8'\0',u8'\0',u8'\0',u8'\0',u8'\0',u8'\0',u8'\0',u8'\0',u8'\0' };
	CHAR8 _UTF8_WHITESPACECHARS[8] = { 0x09,0x0A,0x0B,0x0C,0x0D,0x20,0x85,0xA0 };
	const CHAR8* Common::Enviroment::UTF8::NewLine = u8"\r\n";
	constinit const CHAR8* _UTF8_ABORTED = u8"ABORTED";
	constinit const CHAR8* _UTF8_ACCESS_DENIED = u8"ACCESS_DENIED";
	constinit const CHAR8* _UTF8_ALREADY_STARTED = u8"ALREADY_STARTED";
	constinit const CHAR8* _UTF8_BAD_BUFFER_SIZE = u8"BAD_BUFFER_SIZE";
	constinit const CHAR8* _UTF8_BOOLEAN_FALSE = u8"False";
	constinit const CHAR8* _UTF8_BOOLEAN_TRUE = u8"True";
	constinit const CHAR8* _UTF8_BUFFER_TOO_SMALL = u8"BUFFER_TOO_SMALL";
	constinit const CHAR8* _UTF8_COMPROMISED_DATA = u8"COMPROMISED_DATA";
	constinit const CHAR8* _UTF8_CRC_ERROR = u8"CRC_ERROR";
	constinit const CHAR8* _UTF8_DEVICE_ERROR = u8"DEVICE_ERROR";
	constinit const CHAR8* _UTF8_END_OF_FILE = u8"END_OF_FILE";
	constinit const CHAR8* _UTF8_END_OF_MEDIA = u8"END_OF_MEDIA";
	constinit const CHAR8* _UTF8_HTTP_ERROR = u8"HTTP_ERROR";
	constinit const CHAR8* _UTF8_ICMP_ERROR = u8"ICMP_ERROR";
	constinit const CHAR8* _UTF8_INCOMPATIBLE_VERSION = u8"INCOMPATIBLE_VERSION";
	constinit const CHAR8* _UTF8_INVALID_LANGUAGE = u8"INVALID_LANGUAGE";
	constinit const CHAR8* _UTF8_INVALID_PARAMETER = u8"INVALID_PARAMETER";
	constinit const CHAR8* _UTF8_IP_ADDRESS_CONFLICT = u8"IP_ADDRESS_CONFLICT";
	constinit const CHAR8* _UTF8_LOAD_ERROR = u8"LOAD_ERROR";
	constinit const CHAR8* _UTF8_MEDIA_CHANGED = u8"MEDIA_CHANGED";
	constinit const CHAR8* _UTF8_NO_MAPPING = u8"NO_MAPPING";
	constinit const CHAR8* _UTF8_NO_MEDIA = u8"NO_MEDIA";
	constinit const CHAR8* _UTF8_NO_RESPONSE = u8"NO_RESPONSE";
	constinit const CHAR8* _UTF8_NOT_FOUND = u8"NOT_FOUND";
	constinit const CHAR8* _UTF8_NOT_READY = u8"NOT_READY";
	constinit const CHAR8* _UTF8_NOT_STARTED = u8"NOT_STARTED";
	constinit const CHAR8* _UTF8_OUT_OF_RESOURCES = u8"OUT_OF_RESOURCES";
	constinit const CHAR8* _UTF8_PROTOCOL_ERROR = u8"PROTOCOL_ERROR";
	constinit const CHAR8* _UTF8_SECURITY_VIOLATION = u8"SECURITY_VIOLATION";
	constinit const CHAR8* _UTF8_SUCCESS = u8"SUCCESS";
	constinit const CHAR8* _UTF8_TFTP_ERROR = u8"TFTP_ERROR";
	constinit const CHAR8* _UTF8_TIMEOUT = u8"TIMEOUT";
	constinit const CHAR8* _UTF8_UNSUPPORTED = u8"UNSUPPORTED";
	constinit const CHAR8* _UTF8_VOLUME_CORRUPTED = u8"VOLUME_CORRUPTED";
	constinit const CHAR8* _UTF8_VOLUME_FULL = u8"VOLUME_FULL";
	constinit const CHAR8* _UTF8_WARN_BUFFER_TOO_SMALL = u8"WARN_BUFFER_TOO_SMALL";
	constinit const CHAR8* _UTF8_WARN_DELETE_FAILURE = u8"WARN_DELETE_FAILURE";
	constinit const CHAR8* _UTF8_WARN_FILE_SYSTEM = u8"WARN_FILE_SYSTEM";
	constinit const CHAR8* _UTF8_WARN_RESET_REQUIRED = u8"WARN_RESET_REQUIRED";
	constinit const CHAR8* _UTF8_WARN_STALE_DATA = u8"WARN_STALE_DATA";
	constinit const CHAR8* _UTF8_WARN_UNKNOWN_GLYPH = u8"WARN_UNKNOWN_GLYPH";
	constinit const CHAR8* _UTF8_WARN_WRITE_FAILURE = u8"WARN_WRITE_FAILURE";
	constinit const CHAR8* _UTF8_WRITE_PROTECTED = u8"WRITE_PROTECTED";

	constinit const CHAR8* _UTF8_ALLOC_STATUS_SUCCESS = u8"SUCCESS";
	constinit const CHAR8* _UTF8_ALLOC_STATUS_INVALID_PARAMETER = u8"INVALID_PARAMETER";
	constinit const CHAR8* _UTF8_ALLOC_STATUS_NOT_ENOUGH_MEMORY = u8"NOT_ENOUGH_MEMORY";
	constinit const CHAR8* _UTF8_ALLOC_STATUS_NOT_ENOUGH_PAGES = u8"NOT_ENOUGH_PAGES";
	constinit const CHAR8* _UTF8_ALLOC_STATUS_ACCESS_DENIED = u8"ACCESS_DENIED";
	constinit const CHAR8* _UTF8_ALLOC_STATUS_UNKNOWN = u8"UNKNOWN";

	CHAR8* UTF8::ToHex(const INT16 value)
	{
		if (value < 0)
		{
			INT16 abs = -value;
			_UTF8_HEXSTRING[0] = u8'-';
			_UTF8_HEXSTRING[1] = _UTF8_HEXCHARS[(abs >> 12) & 0xF];
			_UTF8_HEXSTRING[2] = _UTF8_HEXCHARS[(abs >> 8) & 0xF];
			_UTF8_HEXSTRING[3] = _UTF8_HEXCHARS[(abs >> 4) & 0xF];
			_UTF8_HEXSTRING[4] = _UTF8_HEXCHARS[abs & 0xF];
			_UTF8_HEXSTRING[5] = u8'\0';
		}
		else
		{
			_UTF8_HEXSTRING[0] = _UTF8_HEXCHARS[(value >> 12) & 0xF];
			_UTF8_HEXSTRING[1] = _UTF8_HEXCHARS[(value >> 8) & 0xF];
			_UTF8_HEXSTRING[2] = _UTF8_HEXCHARS[(value >> 4) & 0xF];
			_UTF8_HEXSTRING[3] = _UTF8_HEXCHARS[value & 0xF];
			_UTF8_HEXSTRING[4] = u8'\0';
		}
		return &_UTF8_HEXSTRING[0];
	}

	CHAR8* UTF8::ToHex(const INT32 value)
	{
		if (value < 0)
		{
			INT32 abs = -value;
			_UTF8_HEXSTRING[0] = u'-';
			_UTF8_HEXSTRING[1] = _UTF8_HEXCHARS[(abs >> 28) & 0xF];
			_UTF8_HEXSTRING[2] = _UTF8_HEXCHARS[(abs >> 24) & 0xF];
			_UTF8_HEXSTRING[3] = _UTF8_HEXCHARS[(abs >> 20) & 0xF];
			_UTF8_HEXSTRING[4] = _UTF8_HEXCHARS[(abs >> 16) & 0xF];
			_UTF8_HEXSTRING[5] = _UTF8_HEXCHARS[(abs >> 12) & 0xF];
			_UTF8_HEXSTRING[6] = _UTF8_HEXCHARS[(abs >> 8) & 0xF];
			_UTF8_HEXSTRING[7] = _UTF8_HEXCHARS[(abs >> 4) & 0xF];
			_UTF8_HEXSTRING[8] = _UTF8_HEXCHARS[abs & 0xF];
			_UTF8_HEXSTRING[9] = u8'\0';
		}
		else
		{
			_UTF8_HEXSTRING[0] = _UTF8_HEXCHARS[(value >> 28) & 0xF];
			_UTF8_HEXSTRING[1] = _UTF8_HEXCHARS[(value >> 24) & 0xF];
			_UTF8_HEXSTRING[2] = _UTF8_HEXCHARS[(value >> 20) & 0xF];
			_UTF8_HEXSTRING[3] = _UTF8_HEXCHARS[(value >> 16) & 0xF];
			_UTF8_HEXSTRING[4] = _UTF8_HEXCHARS[(value >> 12) & 0xF];
			_UTF8_HEXSTRING[5] = _UTF8_HEXCHARS[(value >> 8) & 0xF];
			_UTF8_HEXSTRING[6] = _UTF8_HEXCHARS[(value >> 4) & 0xF];
			_UTF8_HEXSTRING[7] = _UTF8_HEXCHARS[value & 0xF];
			_UTF8_HEXSTRING[8] = u8'\0';
		}
		return &_UTF8_HEXSTRING[0];
	}

	CHAR8* UTF8::ToHex(const INT64 value)
	{
		if (value < 0)
		{
			INT64 abs = -value;
			_UTF8_HEXSTRING[0] = u8'-';
			_UTF8_HEXSTRING[1] = _UTF8_HEXCHARS[(abs >> 60) & 0xF];
			_UTF8_HEXSTRING[2] = _UTF8_HEXCHARS[(abs >> 56) & 0xF];
			_UTF8_HEXSTRING[3] = _UTF8_HEXCHARS[(abs >> 52) & 0xF];
			_UTF8_HEXSTRING[4] = _UTF8_HEXCHARS[(abs >> 48) & 0xF];
			_UTF8_HEXSTRING[5] = _UTF8_HEXCHARS[(abs >> 44) & 0xF];
			_UTF8_HEXSTRING[6] = _UTF8_HEXCHARS[(abs >> 40) & 0xF];
			_UTF8_HEXSTRING[7] = _UTF8_HEXCHARS[(abs >> 36) & 0xF];
			_UTF8_HEXSTRING[8] = _UTF8_HEXCHARS[(abs >> 32) & 0xF];
			_UTF8_HEXSTRING[9] = _UTF8_HEXCHARS[(abs >> 28) & 0xF];
			_UTF8_HEXSTRING[10] = _UTF8_HEXCHARS[(abs >> 24) & 0xF];
			_UTF8_HEXSTRING[11] = _UTF8_HEXCHARS[(abs >> 20) & 0xF];
			_UTF8_HEXSTRING[12] = _UTF8_HEXCHARS[(abs >> 16) & 0xF];
			_UTF8_HEXSTRING[13] = _UTF8_HEXCHARS[(abs >> 12) & 0xF];
			_UTF8_HEXSTRING[14] = _UTF8_HEXCHARS[(abs >> 8) & 0xF];
			_UTF8_HEXSTRING[15] = _UTF8_HEXCHARS[(abs >> 4) & 0xF];
			_UTF8_HEXSTRING[16] = _UTF8_HEXCHARS[abs & 0xF];
			_UTF8_HEXSTRING[17] = u8'\0';
		}
		else
		{
			_UTF8_HEXSTRING[0] = _UTF8_HEXCHARS[(value >> 60) & 0xF];
			_UTF8_HEXSTRING[1] = _UTF8_HEXCHARS[(value >> 56) & 0xF];
			_UTF8_HEXSTRING[2] = _UTF8_HEXCHARS[(value >> 52) & 0xF];
			_UTF8_HEXSTRING[3] = _UTF8_HEXCHARS[(value >> 48) & 0xF];
			_UTF8_HEXSTRING[4] = _UTF8_HEXCHARS[(value >> 44) & 0xF];
			_UTF8_HEXSTRING[5] = _UTF8_HEXCHARS[(value >> 40) & 0xF];
			_UTF8_HEXSTRING[6] = _UTF8_HEXCHARS[(value >> 36) & 0xF];
			_UTF8_HEXSTRING[7] = _UTF8_HEXCHARS[(value >> 32) & 0xF];
			_UTF8_HEXSTRING[8] = _UTF8_HEXCHARS[(value >> 28) & 0xF];
			_UTF8_HEXSTRING[9] = _UTF8_HEXCHARS[(value >> 24) & 0xF];
			_UTF8_HEXSTRING[10] = _UTF8_HEXCHARS[(value >> 20) & 0xF];
			_UTF8_HEXSTRING[11] = _UTF8_HEXCHARS[(value >> 16) & 0xF];
			_UTF8_HEXSTRING[12] = _UTF8_HEXCHARS[(value >> 12) & 0xF];
			_UTF8_HEXSTRING[13] = _UTF8_HEXCHARS[(value >> 8) & 0xF];
			_UTF8_HEXSTRING[14] = _UTF8_HEXCHARS[(value >> 4) & 0xF];
			_UTF8_HEXSTRING[15] = _UTF8_HEXCHARS[value & 0xF];
			_UTF8_HEXSTRING[16] = u8'\0';
		}
		return &_UTF8_HEXSTRING[0];
	}

	CHAR8* UTF8::ToHex(const INT8 value)
	{
		if (value < 0)
		{
			INT8 abs = -value;
			_UTF8_HEXSTRING[0] = u8'-';
			_UTF8_HEXSTRING[1] = _UTF8_HEXCHARS[(abs >> 4) & 0xF];
			_UTF8_HEXSTRING[2] = _UTF8_HEXCHARS[abs & 0xF];
			_UTF8_HEXSTRING[3] = u8'\0';
		}
		else
		{
			_UTF8_HEXSTRING[0] = _UTF8_HEXCHARS[(value >> 4) & 0xF];
			_UTF8_HEXSTRING[1] = _UTF8_HEXCHARS[value & 0xF];
			_UTF8_HEXSTRING[2] = u8'\0';
		}
		return &_UTF8_HEXSTRING[0];
	}

	CHAR8* UTF8::ToHex(const UINT16 value)
	{
		_UTF8_HEXSTRING[0] = _UTF8_HEXCHARS[(value >> 12) & 0xF];
		_UTF8_HEXSTRING[1] = _UTF8_HEXCHARS[(value >> 8) & 0xF];
		_UTF8_HEXSTRING[2] = _UTF8_HEXCHARS[(value >> 4) & 0xF];
		_UTF8_HEXSTRING[3] = _UTF8_HEXCHARS[value & 0xF];
		_UTF8_HEXSTRING[4] = u8'\0';
		return &_UTF8_HEXSTRING[0];
	}

	CHAR8* UTF8::ToHex(const UINT32 value)
	{
		_UTF8_HEXSTRING[0] = _UTF8_HEXCHARS[(value >> 28) & 0xF];
		_UTF8_HEXSTRING[1] = _UTF8_HEXCHARS[(value >> 24) & 0xF];
		_UTF8_HEXSTRING[2] = _UTF8_HEXCHARS[(value >> 20) & 0xF];
		_UTF8_HEXSTRING[3] = _UTF8_HEXCHARS[(value >> 16) & 0xF];
		_UTF8_HEXSTRING[4] = _UTF8_HEXCHARS[(value >> 12) & 0xF];
		_UTF8_HEXSTRING[5] = _UTF8_HEXCHARS[(value >> 8) & 0xF];
		_UTF8_HEXSTRING[6] = _UTF8_HEXCHARS[(value >> 4) & 0xF];
		_UTF8_HEXSTRING[7] = _UTF8_HEXCHARS[value & 0xF];
		_UTF8_HEXSTRING[8] = u8'\0';
		return &_UTF8_HEXSTRING[0];
	}

	CHAR8* UTF8::ToHex(const UINT64 value)
	{
		_UTF8_HEXSTRING[0] = _UTF8_HEXCHARS[(value >> 60) & 0xF];
		_UTF8_HEXSTRING[1] = _UTF8_HEXCHARS[(value >> 56) & 0xF];
		_UTF8_HEXSTRING[2] = _UTF8_HEXCHARS[(value >> 52) & 0xF];
		_UTF8_HEXSTRING[3] = _UTF8_HEXCHARS[(value >> 48) & 0xF];
		_UTF8_HEXSTRING[4] = _UTF8_HEXCHARS[(value >> 44) & 0xF];
		_UTF8_HEXSTRING[5] = _UTF8_HEXCHARS[(value >> 40) & 0xF];
		_UTF8_HEXSTRING[6] = _UTF8_HEXCHARS[(value >> 36) & 0xF];
		_UTF8_HEXSTRING[7] = _UTF8_HEXCHARS[(value >> 32) & 0xF];
		_UTF8_HEXSTRING[8] = _UTF8_HEXCHARS[(value >> 28) & 0xF];
		_UTF8_HEXSTRING[9] = _UTF8_HEXCHARS[(value >> 24) & 0xF];
		_UTF8_HEXSTRING[10] = _UTF8_HEXCHARS[(value >> 20) & 0xF];
		_UTF8_HEXSTRING[11] = _UTF8_HEXCHARS[(value >> 16) & 0xF];
		_UTF8_HEXSTRING[12] = _UTF8_HEXCHARS[(value >> 12) & 0xF];
		_UTF8_HEXSTRING[13] = _UTF8_HEXCHARS[(value >> 8) & 0xF];
		_UTF8_HEXSTRING[14] = _UTF8_HEXCHARS[(value >> 4) & 0xF];
		_UTF8_HEXSTRING[15] = _UTF8_HEXCHARS[value & 0xF];
		_UTF8_HEXSTRING[16] = u8'\0';
		return &_UTF8_HEXSTRING[0];
	}

	CHAR8* UTF8::ToHex(const UINT8 value)
	{
		_UTF8_HEXSTRING[0] = _UTF8_HEXCHARS[(value >> 4) & 0xF];
		_UTF8_HEXSTRING[1] = _UTF8_HEXCHARS[value & 0xF];
		_UTF8_HEXSTRING[2] = u8'\0';
		return &_UTF8_HEXSTRING[0];
	}

	CHAR8* UTF8::ToHex(const VOID_PTR ptr)
	{
		UINT64 value = (UINT64)ptr;
		_UTF8_HEXSTRING[0] = _UTF8_HEXCHARS[(value >> 60) & 0xF];
		_UTF8_HEXSTRING[1] = _UTF8_HEXCHARS[(value >> 56) & 0xF];
		_UTF8_HEXSTRING[2] = _UTF8_HEXCHARS[(value >> 52) & 0xF];
		_UTF8_HEXSTRING[3] = _UTF8_HEXCHARS[(value >> 48) & 0xF];
		_UTF8_HEXSTRING[4] = _UTF8_HEXCHARS[(value >> 44) & 0xF];
		_UTF8_HEXSTRING[5] = _UTF8_HEXCHARS[(value >> 40) & 0xF];
		_UTF8_HEXSTRING[6] = _UTF8_HEXCHARS[(value >> 36) & 0xF];
		_UTF8_HEXSTRING[7] = _UTF8_HEXCHARS[(value >> 32) & 0xF];
		_UTF8_HEXSTRING[8] = _UTF8_HEXCHARS[(value >> 28) & 0xF];
		_UTF8_HEXSTRING[9] = _UTF8_HEXCHARS[(value >> 24) & 0xF];
		_UTF8_HEXSTRING[10] = _UTF8_HEXCHARS[(value >> 20) & 0xF];
		_UTF8_HEXSTRING[11] = _UTF8_HEXCHARS[(value >> 16) & 0xF];
		_UTF8_HEXSTRING[12] = _UTF8_HEXCHARS[(value >> 12) & 0xF];
		_UTF8_HEXSTRING[13] = _UTF8_HEXCHARS[(value >> 8) & 0xF];
		_UTF8_HEXSTRING[14] = _UTF8_HEXCHARS[(value >> 4) & 0xF];
		_UTF8_HEXSTRING[15] = _UTF8_HEXCHARS[value & 0xF];
		_UTF8_HEXSTRING[16] = u8'\0';
		return &_UTF8_HEXSTRING[0];
	}

	CHAR8* UTF8::ToString(const EFI::EFI_GUID guid)
	{
		_UTF8_GUIDTOSTRING[1] = _UTF8_HEXCHARS[(guid.Data1 >> 28) & 0xF];
		_UTF8_GUIDTOSTRING[2] = _UTF8_HEXCHARS[(guid.Data1 >> 24) & 0xF];
		_UTF8_GUIDTOSTRING[3] = _UTF8_HEXCHARS[(guid.Data1 >> 20) & 0xF];
		_UTF8_GUIDTOSTRING[4] = _UTF8_HEXCHARS[(guid.Data1 >> 16) & 0xF];
		_UTF8_GUIDTOSTRING[5] = _UTF8_HEXCHARS[(guid.Data1 >> 12) & 0xF];
		_UTF8_GUIDTOSTRING[6] = _UTF8_HEXCHARS[(guid.Data1 >> 8) & 0xF];
		_UTF8_GUIDTOSTRING[7] = _UTF8_HEXCHARS[(guid.Data1 >> 4) & 0xF];
		_UTF8_GUIDTOSTRING[8] = _UTF8_HEXCHARS[guid.Data1 & 0xF];
		_UTF8_GUIDTOSTRING[10] = _UTF8_HEXCHARS[(guid.Data2 >> 12) & 0xF];
		_UTF8_GUIDTOSTRING[11] = _UTF8_HEXCHARS[(guid.Data2 >> 8) & 0xF];
		_UTF8_GUIDTOSTRING[12] = _UTF8_HEXCHARS[(guid.Data2 >> 4) & 0xF];
		_UTF8_GUIDTOSTRING[13] = _UTF8_HEXCHARS[guid.Data2 & 0xF];
		_UTF8_GUIDTOSTRING[15] = _UTF8_HEXCHARS[(guid.Data3 >> 12) & 0xF];
		_UTF8_GUIDTOSTRING[16] = _UTF8_HEXCHARS[(guid.Data3 >> 8) & 0xF];
		_UTF8_GUIDTOSTRING[17] = _UTF8_HEXCHARS[(guid.Data3 >> 4) & 0xF];
		_UTF8_GUIDTOSTRING[18] = _UTF8_HEXCHARS[guid.Data3 & 0xF];
		_UTF8_GUIDTOSTRING[20] = _UTF8_HEXCHARS[(guid.Data4[0] >> 4) & 0xF];
		_UTF8_GUIDTOSTRING[21] = _UTF8_HEXCHARS[guid.Data4[0] & 0xF];
		_UTF8_GUIDTOSTRING[23] = _UTF8_HEXCHARS[(guid.Data4[1] >> 4) & 0xF];
		_UTF8_GUIDTOSTRING[24] = _UTF8_HEXCHARS[guid.Data4[1] & 0xF];
		_UTF8_GUIDTOSTRING[26] = _UTF8_HEXCHARS[(guid.Data4[2] >> 4) & 0xF];
		_UTF8_GUIDTOSTRING[27] = _UTF8_HEXCHARS[guid.Data4[2] & 0xF];
		_UTF8_GUIDTOSTRING[28] = _UTF8_HEXCHARS[(guid.Data4[3] >> 4) & 0xF];
		_UTF8_GUIDTOSTRING[29] = _UTF8_HEXCHARS[guid.Data4[3] & 0xF];
		_UTF8_GUIDTOSTRING[31] = _UTF8_HEXCHARS[(guid.Data4[4] >> 4) & 0xF];
		_UTF8_GUIDTOSTRING[32] = _UTF8_HEXCHARS[guid.Data4[4] & 0xF];
		_UTF8_GUIDTOSTRING[34] = _UTF8_HEXCHARS[(guid.Data4[5] >> 4) & 0xF];
		_UTF8_GUIDTOSTRING[35] = _UTF8_HEXCHARS[guid.Data4[5] & 0xF];
		_UTF8_GUIDTOSTRING[37] = _UTF8_HEXCHARS[(guid.Data4[6] >> 4) & 0xF];
		_UTF8_GUIDTOSTRING[38] = _UTF8_HEXCHARS[guid.Data4[6] & 0xF];
		_UTF8_GUIDTOSTRING[40] = _UTF8_HEXCHARS[(guid.Data4[7] >> 4) & 0xF];
		_UTF8_GUIDTOSTRING[41] = _UTF8_HEXCHARS[guid.Data4[7] & 0xF];
		return &_UTF8_GUIDTOSTRING[0];
	}

	CHAR8* UTF8::ToString(const EFI::EFI_STATUS status)
	{
		switch (status)
		{
		case EFI::EFI_STATUS::ABORTED:
			return (CHAR8*)_UTF8_ABORTED;
		case EFI::EFI_STATUS::ACCESS_DENIED:
			return (CHAR8*)_UTF8_ACCESS_DENIED;
		case EFI::EFI_STATUS::ALREADY_STARTED:
			return (CHAR8*)_UTF8_ALREADY_STARTED;
		case EFI::EFI_STATUS::BAD_BUFFER_SIZE:
			return (CHAR8*)_UTF8_BAD_BUFFER_SIZE;
		case EFI::EFI_STATUS::BUFFER_TOO_SMALL:
			return (CHAR8*)_UTF8_BUFFER_TOO_SMALL;
		case EFI::EFI_STATUS::COMPROMISED_DATA:
			return (CHAR8*)_UTF8_COMPROMISED_DATA;
		case EFI::EFI_STATUS::CRC_ERROR:
			return (CHAR8*)_UTF8_CRC_ERROR;
		case EFI::EFI_STATUS::DEVICE_ERROR:
			return (CHAR8*)_UTF8_DEVICE_ERROR;
		case EFI::EFI_STATUS::END_OF_FILE:
			return (CHAR8*)_UTF8_END_OF_FILE;
		case EFI::EFI_STATUS::END_OF_MEDIA:
			return (CHAR8*)_UTF8_END_OF_MEDIA;
		case EFI::EFI_STATUS::HTTP_ERROR:
			return (CHAR8*)_UTF8_HTTP_ERROR;
		case EFI::EFI_STATUS::ICMP_ERROR:
			return (CHAR8*)_UTF8_ICMP_ERROR;
		case EFI::EFI_STATUS::INCOMPATIBLE_VERSION:
			return (CHAR8*)_UTF8_INCOMPATIBLE_VERSION;
		case EFI::EFI_STATUS::INVALID_LANGUAGE:
			return (CHAR8*)_UTF8_INVALID_LANGUAGE;
		case EFI::EFI_STATUS::INVALID_PARAMETER:
			return (CHAR8*)_UTF8_INVALID_PARAMETER;
		case EFI::EFI_STATUS::IP_ADDRESS_CONFLICT:
			return (CHAR8*)_UTF8_IP_ADDRESS_CONFLICT;
		case EFI::EFI_STATUS::LOAD_ERROR:
			return (CHAR8*)_UTF8_LOAD_ERROR;
		case EFI::EFI_STATUS::MEDIA_CHANGED:
			return (CHAR8*)_UTF8_MEDIA_CHANGED;
		case EFI::EFI_STATUS::NO_MAPPING:
			return (CHAR8*)_UTF8_NO_MAPPING;
		case EFI::EFI_STATUS::NO_MEDIA:
			return (CHAR8*)_UTF8_NO_MEDIA;
		case EFI::EFI_STATUS::NO_RESPONSE:
			return (CHAR8*)_UTF8_NO_RESPONSE;
		case EFI::EFI_STATUS::NOT_FOUND:
			return (CHAR8*)_UTF8_NOT_FOUND;
		case EFI::EFI_STATUS::NOT_READY:
			return (CHAR8*)_UTF8_NOT_READY;
		case EFI::EFI_STATUS::NOT_STARTED:
			return (CHAR8*)_UTF8_NOT_STARTED;
		case EFI::EFI_STATUS::OUT_OF_RESOURCES:
			return (CHAR8*)_UTF8_OUT_OF_RESOURCES;
		case EFI::EFI_STATUS::PROTOCOL_ERROR:
			return (CHAR8*)_UTF8_PROTOCOL_ERROR;
		case EFI::EFI_STATUS::SECURITY_VIOLATION:
			return (CHAR8*)_UTF8_SECURITY_VIOLATION;
		case EFI::EFI_STATUS::SUCCESS:
			return (CHAR8*)_UTF8_SUCCESS;
		case EFI::EFI_STATUS::TFTP_ERROR:
			return (CHAR8*)_UTF8_TFTP_ERROR;
		case EFI::EFI_STATUS::TIMEOUT:
			return (CHAR8*)_UTF8_TIMEOUT;
		case EFI::EFI_STATUS::UNSUPPORTED:
			return (CHAR8*)_UTF8_UNSUPPORTED;
		case EFI::EFI_STATUS::VOLUME_CORRUPTED:
			return (CHAR8*)_UTF8_VOLUME_CORRUPTED;
		case EFI::EFI_STATUS::VOLUME_FULL:
			return (CHAR8*)_UTF8_VOLUME_FULL;
		case EFI::EFI_STATUS::WARN_BUFFER_TOO_SMALL:
			return (CHAR8*)_UTF8_WARN_BUFFER_TOO_SMALL;
		case EFI::EFI_STATUS::WARN_DELETE_FAILURE:
			return (CHAR8*)_UTF8_WARN_DELETE_FAILURE;
		case EFI::EFI_STATUS::WARN_FILE_SYSTEM:
			return (CHAR8*)_UTF8_WARN_FILE_SYSTEM;
		case EFI::EFI_STATUS::WARN_RESET_REQUIRED:
			return (CHAR8*)_UTF8_WARN_RESET_REQUIRED;
		case EFI::EFI_STATUS::WARN_STALE_DATA:
			return (CHAR8*)_UTF8_WARN_STALE_DATA;
		case EFI::EFI_STATUS::WARN_UNKNOWN_GLYPH:
			return (CHAR8*)_UTF8_WARN_UNKNOWN_GLYPH;
		case EFI::EFI_STATUS::WARN_WRITE_FAILURE:
			return (CHAR8*)_UTF8_WARN_WRITE_FAILURE;
		case EFI::EFI_STATUS::WRITE_PROTECTED:
			return (CHAR8*)_UTF8_WRITE_PROTECTED;
		default:
			return nullptr;
		}
	}

	CHAR8* UTF8::ToString(const Common::System::AllocatorStatus status)
	{
		switch (status)
		{
		case Common::System::AllocatorStatus::Success:
			return (CHAR8*)_UTF8_ALLOC_STATUS_SUCCESS;
		case Common::System::AllocatorStatus::Invalid_Parameters:
			return (CHAR8*)_UTF8_ALLOC_STATUS_INVALID_PARAMETER;
		case Common::System::AllocatorStatus::Not_Enough_Memory:
			return (CHAR8*)_UTF8_ALLOC_STATUS_NOT_ENOUGH_MEMORY;
		case Common::System::AllocatorStatus::Not_Enough_Pages:
			return (CHAR8*)_UTF8_ALLOC_STATUS_NOT_ENOUGH_PAGES;
		case Common::System::AllocatorStatus::Access_Denied:
			return (CHAR8*)_UTF8_ALLOC_STATUS_ACCESS_DENIED;
		}
	}

	CHAR8* UTF8::ToString(const INT16 value)
	{
		if (value == 0)
		{
			_UTF8_VALUETOSTRING[0] = u8'0';
			_UTF8_VALUETOSTRING[1] = u8'\0';
			return &_UTF8_VALUETOSTRING[0];
		}

		INT16 i = value;
		INT8 len = 6;
		_UTF8_VALUETOSTRING[len] = u8'\0';
		bool isNegative = false;
		if (i < 0)
		{
			isNegative = true;
			i = -i; // make it positive
		}
		for (; i > 0; i /= 10)
		{
			_UTF8_VALUETOSTRING[--len] = (i % 10) + u8'0';
		}
		if (isNegative)
		{
			_UTF8_VALUETOSTRING[--len] = u8'-';
		}
		return &_UTF8_VALUETOSTRING[len];
	}

	CHAR8* UTF8::ToString(const INT32 value)
	{
		if (value == 0)
		{
			_UTF8_VALUETOSTRING[0] = u8'0';
			_UTF8_VALUETOSTRING[1] = u8'\0';
			return &_UTF8_VALUETOSTRING[0];
		}

		INT32 i = value;
		INT8 len = 11;
		_UTF8_VALUETOSTRING[len] = u8'\0';
		bool isNegative = false;
		if (i < 0)
		{
			isNegative = true;
			i = -i; // make it positive
		}
		for (; i > 0; i /= 10)
		{
			_UTF8_VALUETOSTRING[--len] = (i % 10) + u8'0';
		}
		if (isNegative)
		{
			_UTF8_VALUETOSTRING[--len] = u8'-';
		}
		return &_UTF8_VALUETOSTRING[len];
	}

	CHAR8* UTF8::ToString(const INT64 value)
	{
		if (value == 0)
		{
			_UTF8_VALUETOSTRING[0] = u8'0';
			_UTF8_VALUETOSTRING[1] = u8'\0';
			return &_UTF8_VALUETOSTRING[0];
		}

		INT64 i = value;
		INT8 len = 21;
		_UTF8_VALUETOSTRING[len] = u8'\0';
		bool isNegative = false;
		if (i < 0)
		{
			isNegative = true;
			i = -i; // make it positive
		}
		for (; i > 0; i /= 10)
		{
			_UTF8_VALUETOSTRING[--len] = (i % 10) + u8'0';
		}
		if (isNegative)
		{
			_UTF8_VALUETOSTRING[--len] = u8'-';
		}
		return &_UTF8_VALUETOSTRING[len];
	}

	CHAR8* UTF8::ToString(const INT8 value)
	{
		if (value == 0)
		{
			_UTF8_VALUETOSTRING[0] = u8'0';
			_UTF8_VALUETOSTRING[1] = u8'\0';
			return &_UTF8_VALUETOSTRING[0];
		}

		INT8 i = value;
		INT8 len = 4;
		_UTF8_VALUETOSTRING[len] = u8'\0';
		bool isNegative = false;
		if (i < 0)
		{
			isNegative = true;
			i = -i; // make it positive
		}
		for (; i > 0; i /= 10)
		{
			_UTF8_VALUETOSTRING[--len] = (i % 10) + u8'0';
		}
		if (isNegative)
		{
			_UTF8_VALUETOSTRING[--len] = u8'-';
		}
		return &_UTF8_VALUETOSTRING[len];
	}

	CHAR8* UTF8::ToString(const UINT16 value)
	{
		if (value == 0)
		{
			_UTF8_VALUETOSTRING[0] = u8'0';
			_UTF8_VALUETOSTRING[1] = u8'\0';
			return &_UTF8_VALUETOSTRING[0];
		}

		UINT16 i = value;
		INT8 len = 5;
		_UTF8_VALUETOSTRING[len] = u8'\0';
		for (; i > 0; i /= 10)
		{
			_UTF8_VALUETOSTRING[--len] = (i % 10) + u8'0';
		}
		return &_UTF8_VALUETOSTRING[len];
	}

	CHAR8* UTF8::ToString(const UINT32 value)
	{
		if (value == 0)
		{
			_UTF8_VALUETOSTRING[0] = u8'0';
			_UTF8_VALUETOSTRING[1] = u8'\0';
			return &_UTF8_VALUETOSTRING[0];
		}

		UINT32 i = value;
		INT8 len = 10;
		_UTF8_VALUETOSTRING[len] = u8'\0';
		for (; i > 0; i /= 10)
		{
			_UTF8_VALUETOSTRING[--len] = (i % 10) + u8'0';
		}
		return &_UTF8_VALUETOSTRING[len];
	}

	CHAR8* UTF8::ToString(const UINT64 value)
	{
		if (value == 0)
		{
			_UTF8_VALUETOSTRING[0] = u8'0';
			_UTF8_VALUETOSTRING[1] = u8'\0';
			return &_UTF8_VALUETOSTRING[0];
		}

		UINT64 i = value;
		INT8 len = 20;
		_UTF8_VALUETOSTRING[len] = u8'\0';
		for (; i > 0; i /= 10)
		{
			_UTF8_VALUETOSTRING[--len] = (i % 10) + u8'0';
		}
		return &_UTF8_VALUETOSTRING[len];
	}

	CHAR8* UTF8::ToString(const UINT8 value)
	{
		if (value == 0)
		{
			_UTF8_VALUETOSTRING[0] = u8'0';
			_UTF8_VALUETOSTRING[1] = u8'\0';
			return &_UTF8_VALUETOSTRING[0];
		}

		UINT8 i = value;
		INT8 len = 3;
		_UTF8_VALUETOSTRING[len] = u8'\0';
		for (; i > 0; i /= 10)
		{
			_UTF8_VALUETOSTRING[--len] = (i % 10) + u8'0';
		}
		return &_UTF8_VALUETOSTRING[len];
	}

	CHAR8* UTF8::ToString(const VOID_PTR ptr)
	{
		UINT64 value = (UINT64)ptr;
		if (value == 0)
		{
			_UTF8_VALUETOSTRING[0] = u8'0';
			_UTF8_VALUETOSTRING[1] = u8'\0';
			return &_UTF8_VALUETOSTRING[0];
		}

		UINT64 i = value;
		INT8 len = 20;
		_UTF8_VALUETOSTRING[len] = u8'\0';
		for (; i > 0; i /= 10)
		{
			_UTF8_VALUETOSTRING[--len] = (i % 10) + u8'0';
		}
		return &_UTF8_VALUETOSTRING[len];
	}

	CHAR8* UTF8::ToString(const BOOLEAN boolean)
	{
		if (boolean)
		{
			return (CHAR8*)_UTF8_BOOLEAN_TRUE;
		}
		else
		{
			return (CHAR8*)_UTF8_BOOLEAN_FALSE;
		}
	}

	UINTN UTF8::Length(const CHAR8* str)
	{
		if (str == nullptr)
		{
			return 0;
		}

		if (str[0] == u8'\0')
		{
			return 1;
		}

		UINTN index = 0;
		UINTN len = 1;
		while (str[index] != u8'\0')
		{
			len++;
			index++;
		}
		return len;
	}

	BOOLEAN UTF8::Compare(const CHAR8* l, const CHAR8* r, StringCulture culture)
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

		UINTN lLength = Length(l);
		UINTN rLength = Length(r);

		if (lLength != rLength)
		{
			return FALSE;
		}

		switch (culture)
		{
		case Common::Enviroment::InvariantCulture:
		case Common::Enviroment::CurrentCulture:
		case Common::Enviroment::Ordinal:
		{
			/*Binary Comparison of string*/

			for (UINTN index = 0; index < lLength; index++)
			{
				if (l[index] != r[index])
				{
					return FALSE;
				}
			}
			return TRUE;
		}
		case Common::Enviroment::InvariantCultureIgnoreCase:
		case Common::Enviroment::CurrentCultureIgnoreCase:
		case Common::Enviroment::OrdinalIgnoreCase:
		{
			/*Binary Comparison, Ignoring Case of string*/

			UINTN index = 0;

			for (UINTN index = 0; index < lLength; index++)
			{
				CHAR8 lChar = l[index];
				CHAR8 rChar = r[index];
				/*If the character is a lower case letter, switch it to upper for comparison*/
				if (lChar >= u8'a' && lChar <= u8'z')
				{
					lChar -= 32;
				}
				if (rChar >= u8'a' && rChar <= u8'z')
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

	BOOLEAN UTF8::StartsWith(const CHAR8* str, const CHAR8* value, StringCulture culture)
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

		UINTN strLength = Length(str);
		UINTN valueLength = Length(value);

		if (strLength < valueLength)
		{
			return FALSE;
		}

		switch (culture)
		{
		case Common::Enviroment::InvariantCulture:
		case Common::Enviroment::CurrentCulture:
		case Common::Enviroment::Ordinal:
		{
			for (UINTN index = 0; index < valueLength; index++)
			{
				if (str[index] != value[index])
				{
					return FALSE;
				}
			}
			return TRUE;
		}
		case Common::Enviroment::InvariantCultureIgnoreCase:
		case Common::Enviroment::CurrentCultureIgnoreCase:
		case Common::Enviroment::OrdinalIgnoreCase:
		{
			for (UINTN index = 0; index < valueLength; index++)
			{
				CHAR8 lChar = str[index];
				CHAR8 rChar = value[index];
				/*If the character is a lower case letter, switch it to upper for comparison*/
				if (lChar >= u8'a' && lChar <= u8'z')
				{
					lChar -= 32;
				}
				if (rChar >= u8'a' && rChar <= u8'z')
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

	BOOLEAN UTF8::EndsWith(const CHAR8* str, const CHAR8* value, StringCulture culture)
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

		UINTN strLength = Length(str);
		UINTN valueLength = Length(value);

		if (strLength < valueLength)
		{
			return FALSE;
		}

		switch (culture)
		{
		case Common::Enviroment::InvariantCulture:
		case Common::Enviroment::CurrentCulture:
		case Common::Enviroment::Ordinal:
		{
			UINTN index = 0;
			for (UINTN index = 0; index < valueLength; index++)
			{
				if (str[strLength - valueLength + index] != value[index])
				{
					return FALSE;
				}
			}
			return TRUE;
		}
		case Common::Enviroment::InvariantCultureIgnoreCase:
		case Common::Enviroment::CurrentCultureIgnoreCase:
		case Common::Enviroment::OrdinalIgnoreCase:
		{
			UINTN index = 0;
			for (UINTN index = 0; index < valueLength; index++)
			{
				CHAR8 lChar = str[strLength - valueLength + index];
				CHAR8 rChar = value[index];
				/*If the character is a lower case letter, switch it to upper for comparison*/
				if (lChar >= u8'a' && lChar <= u8'z')
				{
					lChar -= 32;
				}
				if (rChar >= u8'a' && rChar <= u8'z')
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

	BOOLEAN UTF8::Contains(const CHAR8* str, const CHAR8* value, StringCulture culture)
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

		UINTN strLength = Length(str);
		UINTN valueLength = Length(value);

		if (strLength < valueLength)
		{
			return FALSE;
		}

		switch (culture)
		{
		case Common::Enviroment::InvariantCulture:
		case Common::Enviroment::CurrentCulture:
		case Common::Enviroment::Ordinal:
		{
			UINTN index = 0;
			for (UINTN index = 0; index < strLength - valueLength; index++)
			{
				if (str[index] == value[0])
				{
					BOOLEAN match = TRUE;
					for (UINTN i = 0; i < valueLength; i++)
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
		case Common::Enviroment::InvariantCultureIgnoreCase:
		case Common::Enviroment::CurrentCultureIgnoreCase:
		case Common::Enviroment::OrdinalIgnoreCase:
		{
			UINTN index = 0;
			for (UINTN index = 0; index < strLength - valueLength; index++)
			{
				CHAR8 lChar = str[index];
				CHAR8 rChar = value[0];

				/*If the character is a lower case letter, switch it to upper for comparison*/

				if (lChar >= u8'a' && lChar <= u8'z')
				{
					lChar -= 32;
				}
				if (rChar >= u8'a' && rChar <= u8'z')
				{
					rChar -= 32;
				}

				if (lChar == rChar)
				{
					BOOLEAN match = TRUE;
					for (UINTN i = 0; i < valueLength; i++)
					{
						CHAR8 lChar2 = str[index + i];
						CHAR8 rChar2 = value[i];
						/*If the character is a lower case letter, switch it to upper for comparison*/
						if (lChar2 >= u8'a' && lChar2 <= u8'z')
						{
							lChar2 -= 32;
						}
						if (rChar2 >= u8'a' && rChar2 <= u8'z')
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

	BOOLEAN UTF8::IsNullOrEmpty(const CHAR8* str)
	{
		if (str == nullptr)
		{
			return TRUE;
		};

		if (str[0] == u8'\0')
		{
			return TRUE;
		}

		return FALSE;
	}

	BOOLEAN UTF8::IsNullOrWhiteSpace(const CHAR8* str)
	{
		if (str == nullptr)
		{
			return TRUE;
		};

		if (str[0] == u8'\0')
		{
			return TRUE;
		}

		UINTN index = 0;
		while (str[index] != u8'\0')
		{
			UINTN i = 0;
			for (UINTN i = 0; i < 30; i++)
			{
				if (str[index] == _UTF8_WHITESPACECHARS[i])
				{
					return TRUE;
				}
			}
			index++;
		}
		return FALSE;
	}
	CHAR8* UTF8::FromCharArray(CHAR8 arr[], UINTN Length)
	{
		/*Convert from CHAR8 Array to UTF8 String*/

		if (arr == nullptr)
		{
			return nullptr;
		}
		CHAR8* result = new CHAR8[Length + 1];

		for (UINTN i = 0; i < Length; i++)
		{
			result[i] = arr[i];
		}
		result[Length] = u8'\0';

		return result;
	}
	CHAR8* UTF8::FromUTF16String(const CHAR16* str)
	{
		/*Convert from UTF16 String to UTF8 String*/

		if (str == nullptr)
		{
			return nullptr;
		}

		UINTN len = UTF16::Length(str);

		CHAR8* result = new CHAR8[len];

		for (UINTN i = 0; i < len; i++)
		{
			result[i] = (CHAR8)str[i];
		}

		return result;
	}
	CHAR8* UTF8::FromCString(const CCHAR* str)
	{
		/*Convert from Ascii CString to UTF8*/

		if (str == nullptr)
		{
			return nullptr;
		}

		UINTN len = CString::Length(str);

		CHAR8* result = new CHAR8[len];

		for (UINTN i = 0; i < len; i++)
		{
			result[i] = (CHAR8)str[i];
		}
		result[len - 1] = u8'\0';

		return result;
	}

#pragma endregion
#pragma region CString
	CCHAR _CSTR_GUIDTOSTRING[43] = { '{','\0','\0','\0','\0','\0','\0','\0','\0','-','\0','\0','\0','\0','-','\0','\0','\0','\0','-','\0','\0','\0','\0','-','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','}','\0' };
	CCHAR _CSTR_HEXCHARS[17] = { '0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F' };
	CCHAR _CSTR_HEXSTRING[18] = { '\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0' };
	CCHAR _CSTR_VALUETOSTRING[23] = { '\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0' };
	CCHAR _CSTR_WHITESPACECHARS[6] = { 0x09,0x0A,0x0B,0x0C,0x0D,0x20 };
	const CCHAR* Common::Enviroment::CString::NewLine = "\r\n";

	constinit const CCHAR* _CSTR_ABORTED = "ABORTED";
	constinit const CCHAR* _CSTR_ACCESS_DENIED = "ACCESS_DENIED";
	constinit const CCHAR* _CSTR_ALREADY_STARTED = "ALREADY_STARTED";
	constinit const CCHAR* _CSTR_BAD_BUFFER_SIZE = "BAD_BUFFER_SIZE";
	constinit const CCHAR* _CSTR_BOOLEAN_FALSE = "False";
	constinit const CCHAR* _CSTR_BOOLEAN_TRUE = "True";
	constinit const CCHAR* _CSTR_BUFFER_TOO_SMALL = "BUFFER_TOO_SMALL";
	constinit const CCHAR* _CSTR_COMPROMISED_DATA = "COMPROMISED_DATA";
	constinit const CCHAR* _CSTR_CRC_ERROR = "CRC_ERROR";
	constinit const CCHAR* _CSTR_DEVICE_ERROR = "DEVICE_ERROR";
	constinit const CCHAR* _CSTR_END_OF_FILE = "END_OF_FILE";
	constinit const CCHAR* _CSTR_END_OF_MEDIA = "END_OF_MEDIA";
	constinit const CCHAR* _CSTR_HTTP_ERROR = "HTTP_ERROR";
	constinit const CCHAR* _CSTR_ICMP_ERROR = "ICMP_ERROR";
	constinit const CCHAR* _CSTR_INCOMPATIBLE_VERSION = "INCOMPATIBLE_VERSION";
	constinit const CCHAR* _CSTR_INVALID_LANGUAGE = "INVALID_LANGUAGE";
	constinit const CCHAR* _CSTR_INVALID_PARAMETER = "INVALID_PARAMETER";
	constinit const CCHAR* _CSTR_IP_ADDRESS_CONFLICT = "IP_ADDRESS_CONFLICT";
	constinit const CCHAR* _CSTR_LOAD_ERROR = "LOAD_ERROR";
	constinit const CCHAR* _CSTR_MEDIA_CHANGED = "MEDIA_CHANGED";
	constinit const CCHAR* _CSTR_NO_MAPPING = "NO_MAPPING";
	constinit const CCHAR* _CSTR_NO_MEDIA = "NO_MEDIA";
	constinit const CCHAR* _CSTR_NO_RESPONSE = "NO_RESPONSE";
	constinit const CCHAR* _CSTR_NOT_FOUND = "NOT_FOUND";
	constinit const CCHAR* _CSTR_NOT_READY = "NOT_READY";
	constinit const CCHAR* _CSTR_NOT_STARTED = "NOT_STARTED";
	constinit const CCHAR* _CSTR_OUT_OF_RESOURCES = "OUT_OF_RESOURCES";
	constinit const CCHAR* _CSTR_PROTOCOL_ERROR = "PROTOCOL_ERROR";
	constinit const CCHAR* _CSTR_SECURITY_VIOLATION = "SECURITY_VIOLATION";
	constinit const CCHAR* _CSTR_SUCCESS = "SUCCESS";
	constinit const CCHAR* _CSTR_TFTP_ERROR = "TFTP_ERROR";
	constinit const CCHAR* _CSTR_TIMEOUT = "TIMEOUT";
	constinit const CCHAR* _CSTR_UNSUPPORTED = "UNSUPPORTED";
	constinit const CCHAR* _CSTR_VOLUME_CORRUPTED = "VOLUME_CORRUPTED";
	constinit const CCHAR* _CSTR_VOLUME_FULL = "VOLUME_FULL";
	constinit const CCHAR* _CSTR_WARN_BUFFER_TOO_SMALL = "WARN_BUFFER_TOO_SMALL";
	constinit const CCHAR* _CSTR_WARN_DELETE_FAILURE = "WARN_DELETE_FAILURE";
	constinit const CCHAR* _CSTR_WARN_FILE_SYSTEM = "WARN_FILE_SYSTEM";
	constinit const CCHAR* _CSTR_WARN_RESET_REQUIRED = "WARN_RESET_REQUIRED";
	constinit const CCHAR* _CSTR_WARN_STALE_DATA = "WARN_STALE_DATA";
	constinit const CCHAR* _CSTR_WARN_UNKNOWN_GLYPH = "WARN_UNKNOWN_GLYPH";
	constinit const CCHAR* _CSTR_WARN_WRITE_FAILURE = "WARN_WRITE_FAILURE";
	constinit const CCHAR* _CSTR_WRITE_PROTECTED = "WRITE_PROTECTED";

	constinit const CCHAR* _CSTR_ALLOC_STATUS_SUCCESS = "SUCCESS";
	constinit const CCHAR* _CSTR_ALLOC_STATUS_INVALID_PARAMETER = "INVALID_PARAMETER";
	constinit const CCHAR* _CSTR_ALLOC_STATUS_NOT_ENOUGH_MEMORY = "NOT_ENOUGH_MEMORY";
	constinit const CCHAR* _CSTR_ALLOC_STATUS_NOT_ENOUGH_PAGES = "NOT_ENOUGH_PAGES";
	constinit const CCHAR* _CSTR_ALLOC_STATUS_ACCESS_DENIED = "ACCESS_DENIED";
	constinit const CCHAR* _CSTR_ALLOC_STATUS_UNKNOWN = "UNKNOWN";

	CCHAR* CString::ToHex(const INT16 value)
	{
		if (value < 0)
		{
			INT16 abs = -value;
			_CSTR_HEXSTRING[0] = '-';
			_CSTR_HEXSTRING[1] = _CSTR_HEXCHARS[(abs >> 12) & 0xF];
			_CSTR_HEXSTRING[2] = _CSTR_HEXCHARS[(abs >> 8) & 0xF];
			_CSTR_HEXSTRING[3] = _CSTR_HEXCHARS[(abs >> 4) & 0xF];
			_CSTR_HEXSTRING[4] = _CSTR_HEXCHARS[abs & 0xF];
			_CSTR_HEXSTRING[5] = '\0';
		}
		else
		{
			_CSTR_HEXSTRING[0] = _CSTR_HEXCHARS[(value >> 12) & 0xF];
			_CSTR_HEXSTRING[1] = _CSTR_HEXCHARS[(value >> 8) & 0xF];
			_CSTR_HEXSTRING[2] = _CSTR_HEXCHARS[(value >> 4) & 0xF];
			_CSTR_HEXSTRING[3] = _CSTR_HEXCHARS[value & 0xF];
			_CSTR_HEXSTRING[4] = '\0';
		}
		return &_CSTR_HEXSTRING[0];
	}

	CCHAR* CString::ToHex(const INT32 value)
	{
		if (value < 0)
		{
			INT32 abs = -value;
			_CSTR_HEXSTRING[0] = u'-';
			_CSTR_HEXSTRING[1] = _CSTR_HEXCHARS[(abs >> 28) & 0xF];
			_CSTR_HEXSTRING[2] = _CSTR_HEXCHARS[(abs >> 24) & 0xF];
			_CSTR_HEXSTRING[3] = _CSTR_HEXCHARS[(abs >> 20) & 0xF];
			_CSTR_HEXSTRING[4] = _CSTR_HEXCHARS[(abs >> 16) & 0xF];
			_CSTR_HEXSTRING[5] = _CSTR_HEXCHARS[(abs >> 12) & 0xF];
			_CSTR_HEXSTRING[6] = _CSTR_HEXCHARS[(abs >> 8) & 0xF];
			_CSTR_HEXSTRING[7] = _CSTR_HEXCHARS[(abs >> 4) & 0xF];
			_CSTR_HEXSTRING[8] = _CSTR_HEXCHARS[abs & 0xF];
			_CSTR_HEXSTRING[9] = '\0';
		}
		else
		{
			_CSTR_HEXSTRING[0] = _CSTR_HEXCHARS[(value >> 28) & 0xF];
			_CSTR_HEXSTRING[1] = _CSTR_HEXCHARS[(value >> 24) & 0xF];
			_CSTR_HEXSTRING[2] = _CSTR_HEXCHARS[(value >> 20) & 0xF];
			_CSTR_HEXSTRING[3] = _CSTR_HEXCHARS[(value >> 16) & 0xF];
			_CSTR_HEXSTRING[4] = _CSTR_HEXCHARS[(value >> 12) & 0xF];
			_CSTR_HEXSTRING[5] = _CSTR_HEXCHARS[(value >> 8) & 0xF];
			_CSTR_HEXSTRING[6] = _CSTR_HEXCHARS[(value >> 4) & 0xF];
			_CSTR_HEXSTRING[7] = _CSTR_HEXCHARS[value & 0xF];
			_CSTR_HEXSTRING[8] = '\0';
		}
		return &_CSTR_HEXSTRING[0];
	}

	CCHAR* CString::ToHex(const INT64 value)
	{
		if (value < 0)
		{
			INT64 abs = -value;
			_CSTR_HEXSTRING[0] = '-';
			_CSTR_HEXSTRING[1] = _CSTR_HEXCHARS[(abs >> 60) & 0xF];
			_CSTR_HEXSTRING[2] = _CSTR_HEXCHARS[(abs >> 56) & 0xF];
			_CSTR_HEXSTRING[3] = _CSTR_HEXCHARS[(abs >> 52) & 0xF];
			_CSTR_HEXSTRING[4] = _CSTR_HEXCHARS[(abs >> 48) & 0xF];
			_CSTR_HEXSTRING[5] = _CSTR_HEXCHARS[(abs >> 44) & 0xF];
			_CSTR_HEXSTRING[6] = _CSTR_HEXCHARS[(abs >> 40) & 0xF];
			_CSTR_HEXSTRING[7] = _CSTR_HEXCHARS[(abs >> 36) & 0xF];
			_CSTR_HEXSTRING[8] = _CSTR_HEXCHARS[(abs >> 32) & 0xF];
			_CSTR_HEXSTRING[9] = _CSTR_HEXCHARS[(abs >> 28) & 0xF];
			_CSTR_HEXSTRING[10] = _CSTR_HEXCHARS[(abs >> 24) & 0xF];
			_CSTR_HEXSTRING[11] = _CSTR_HEXCHARS[(abs >> 20) & 0xF];
			_CSTR_HEXSTRING[12] = _CSTR_HEXCHARS[(abs >> 16) & 0xF];
			_CSTR_HEXSTRING[13] = _CSTR_HEXCHARS[(abs >> 12) & 0xF];
			_CSTR_HEXSTRING[14] = _CSTR_HEXCHARS[(abs >> 8) & 0xF];
			_CSTR_HEXSTRING[15] = _CSTR_HEXCHARS[(abs >> 4) & 0xF];
			_CSTR_HEXSTRING[16] = _CSTR_HEXCHARS[abs & 0xF];
			_CSTR_HEXSTRING[17] = '\0';
		}
		else
		{
			_CSTR_HEXSTRING[0] = _CSTR_HEXCHARS[(value >> 60) & 0xF];
			_CSTR_HEXSTRING[1] = _CSTR_HEXCHARS[(value >> 56) & 0xF];
			_CSTR_HEXSTRING[2] = _CSTR_HEXCHARS[(value >> 52) & 0xF];
			_CSTR_HEXSTRING[3] = _CSTR_HEXCHARS[(value >> 48) & 0xF];
			_CSTR_HEXSTRING[4] = _CSTR_HEXCHARS[(value >> 44) & 0xF];
			_CSTR_HEXSTRING[5] = _CSTR_HEXCHARS[(value >> 40) & 0xF];
			_CSTR_HEXSTRING[6] = _CSTR_HEXCHARS[(value >> 36) & 0xF];
			_CSTR_HEXSTRING[7] = _CSTR_HEXCHARS[(value >> 32) & 0xF];
			_CSTR_HEXSTRING[8] = _CSTR_HEXCHARS[(value >> 28) & 0xF];
			_CSTR_HEXSTRING[9] = _CSTR_HEXCHARS[(value >> 24) & 0xF];
			_CSTR_HEXSTRING[10] = _CSTR_HEXCHARS[(value >> 20) & 0xF];
			_CSTR_HEXSTRING[11] = _CSTR_HEXCHARS[(value >> 16) & 0xF];
			_CSTR_HEXSTRING[12] = _CSTR_HEXCHARS[(value >> 12) & 0xF];
			_CSTR_HEXSTRING[13] = _CSTR_HEXCHARS[(value >> 8) & 0xF];
			_CSTR_HEXSTRING[14] = _CSTR_HEXCHARS[(value >> 4) & 0xF];
			_CSTR_HEXSTRING[15] = _CSTR_HEXCHARS[value & 0xF];
			_CSTR_HEXSTRING[16] = '\0';
		}
		return &_CSTR_HEXSTRING[0];
	}

	CCHAR* CString::ToHex(const INT8 value)
	{
		if (value < 0)
		{
			INT8 abs = -value;
			_CSTR_HEXSTRING[0] = '-';
			_CSTR_HEXSTRING[1] = _CSTR_HEXCHARS[(abs >> 4) & 0xF];
			_CSTR_HEXSTRING[2] = _CSTR_HEXCHARS[abs & 0xF];
			_CSTR_HEXSTRING[3] = '\0';
		}
		else
		{
			_CSTR_HEXSTRING[0] = _CSTR_HEXCHARS[(value >> 4) & 0xF];
			_CSTR_HEXSTRING[1] = _CSTR_HEXCHARS[value & 0xF];
			_CSTR_HEXSTRING[2] = '\0';
		}
		return &_CSTR_HEXSTRING[0];
	}

	CCHAR* CString::ToHex(const UINT16 value)
	{
		_CSTR_HEXSTRING[0] = _CSTR_HEXCHARS[(value >> 12) & 0xF];
		_CSTR_HEXSTRING[1] = _CSTR_HEXCHARS[(value >> 8) & 0xF];
		_CSTR_HEXSTRING[2] = _CSTR_HEXCHARS[(value >> 4) & 0xF];
		_CSTR_HEXSTRING[3] = _CSTR_HEXCHARS[value & 0xF];
		_CSTR_HEXSTRING[4] = '\0';
		return &_CSTR_HEXSTRING[0];
	}

	CCHAR* CString::ToHex(const UINT32 value)
	{
		_CSTR_HEXSTRING[0] = _CSTR_HEXCHARS[(value >> 28) & 0xF];
		_CSTR_HEXSTRING[1] = _CSTR_HEXCHARS[(value >> 24) & 0xF];
		_CSTR_HEXSTRING[2] = _CSTR_HEXCHARS[(value >> 20) & 0xF];
		_CSTR_HEXSTRING[3] = _CSTR_HEXCHARS[(value >> 16) & 0xF];
		_CSTR_HEXSTRING[4] = _CSTR_HEXCHARS[(value >> 12) & 0xF];
		_CSTR_HEXSTRING[5] = _CSTR_HEXCHARS[(value >> 8) & 0xF];
		_CSTR_HEXSTRING[6] = _CSTR_HEXCHARS[(value >> 4) & 0xF];
		_CSTR_HEXSTRING[7] = _CSTR_HEXCHARS[value & 0xF];
		_CSTR_HEXSTRING[8] = '\0';
		return &_CSTR_HEXSTRING[0];
	}

	CCHAR* CString::ToHex(const UINT64 value)
	{
		_CSTR_HEXSTRING[0] = _CSTR_HEXCHARS[(value >> 60) & 0xF];
		_CSTR_HEXSTRING[1] = _CSTR_HEXCHARS[(value >> 56) & 0xF];
		_CSTR_HEXSTRING[2] = _CSTR_HEXCHARS[(value >> 52) & 0xF];
		_CSTR_HEXSTRING[3] = _CSTR_HEXCHARS[(value >> 48) & 0xF];
		_CSTR_HEXSTRING[4] = _CSTR_HEXCHARS[(value >> 44) & 0xF];
		_CSTR_HEXSTRING[5] = _CSTR_HEXCHARS[(value >> 40) & 0xF];
		_CSTR_HEXSTRING[6] = _CSTR_HEXCHARS[(value >> 36) & 0xF];
		_CSTR_HEXSTRING[7] = _CSTR_HEXCHARS[(value >> 32) & 0xF];
		_CSTR_HEXSTRING[8] = _CSTR_HEXCHARS[(value >> 28) & 0xF];
		_CSTR_HEXSTRING[9] = _CSTR_HEXCHARS[(value >> 24) & 0xF];
		_CSTR_HEXSTRING[10] = _CSTR_HEXCHARS[(value >> 20) & 0xF];
		_CSTR_HEXSTRING[11] = _CSTR_HEXCHARS[(value >> 16) & 0xF];
		_CSTR_HEXSTRING[12] = _CSTR_HEXCHARS[(value >> 12) & 0xF];
		_CSTR_HEXSTRING[13] = _CSTR_HEXCHARS[(value >> 8) & 0xF];
		_CSTR_HEXSTRING[14] = _CSTR_HEXCHARS[(value >> 4) & 0xF];
		_CSTR_HEXSTRING[15] = _CSTR_HEXCHARS[value & 0xF];
		_CSTR_HEXSTRING[16] = '\0';
		return &_CSTR_HEXSTRING[0];
	}

	CCHAR* CString::ToHex(const UINT8 value)
	{
		_CSTR_HEXSTRING[0] = _CSTR_HEXCHARS[(value >> 4) & 0xF];
		_CSTR_HEXSTRING[1] = _CSTR_HEXCHARS[value & 0xF];
		_CSTR_HEXSTRING[2] = '\0';
		return &_CSTR_HEXSTRING[0];
	}

	CCHAR* CString::ToHex(const VOID_PTR ptr)
	{
		UINT64 value = (UINT64)ptr;
		_CSTR_HEXSTRING[0] = _CSTR_HEXCHARS[(value >> 60) & 0xF];
		_CSTR_HEXSTRING[1] = _CSTR_HEXCHARS[(value >> 56) & 0xF];
		_CSTR_HEXSTRING[2] = _CSTR_HEXCHARS[(value >> 52) & 0xF];
		_CSTR_HEXSTRING[3] = _CSTR_HEXCHARS[(value >> 48) & 0xF];
		_CSTR_HEXSTRING[4] = _CSTR_HEXCHARS[(value >> 44) & 0xF];
		_CSTR_HEXSTRING[5] = _CSTR_HEXCHARS[(value >> 40) & 0xF];
		_CSTR_HEXSTRING[6] = _CSTR_HEXCHARS[(value >> 36) & 0xF];
		_CSTR_HEXSTRING[7] = _CSTR_HEXCHARS[(value >> 32) & 0xF];
		_CSTR_HEXSTRING[8] = _CSTR_HEXCHARS[(value >> 28) & 0xF];
		_CSTR_HEXSTRING[9] = _CSTR_HEXCHARS[(value >> 24) & 0xF];
		_CSTR_HEXSTRING[10] = _CSTR_HEXCHARS[(value >> 20) & 0xF];
		_CSTR_HEXSTRING[11] = _CSTR_HEXCHARS[(value >> 16) & 0xF];
		_CSTR_HEXSTRING[12] = _CSTR_HEXCHARS[(value >> 12) & 0xF];
		_CSTR_HEXSTRING[13] = _CSTR_HEXCHARS[(value >> 8) & 0xF];
		_CSTR_HEXSTRING[14] = _CSTR_HEXCHARS[(value >> 4) & 0xF];
		_CSTR_HEXSTRING[15] = _CSTR_HEXCHARS[value & 0xF];
		_CSTR_HEXSTRING[16] = '\0';
		return &_CSTR_HEXSTRING[0];
	}

	CCHAR* CString::ToString(const EFI::EFI_GUID guid)
	{
		_CSTR_GUIDTOSTRING[1] = _CSTR_HEXCHARS[(guid.Data1 >> 28) & 0xF];
		_CSTR_GUIDTOSTRING[2] = _CSTR_HEXCHARS[(guid.Data1 >> 24) & 0xF];
		_CSTR_GUIDTOSTRING[3] = _CSTR_HEXCHARS[(guid.Data1 >> 20) & 0xF];
		_CSTR_GUIDTOSTRING[4] = _CSTR_HEXCHARS[(guid.Data1 >> 16) & 0xF];
		_CSTR_GUIDTOSTRING[5] = _CSTR_HEXCHARS[(guid.Data1 >> 12) & 0xF];
		_CSTR_GUIDTOSTRING[6] = _CSTR_HEXCHARS[(guid.Data1 >> 8) & 0xF];
		_CSTR_GUIDTOSTRING[7] = _CSTR_HEXCHARS[(guid.Data1 >> 4) & 0xF];
		_CSTR_GUIDTOSTRING[8] = _CSTR_HEXCHARS[guid.Data1 & 0xF];
		_CSTR_GUIDTOSTRING[10] = _CSTR_HEXCHARS[(guid.Data2 >> 12) & 0xF];
		_CSTR_GUIDTOSTRING[11] = _CSTR_HEXCHARS[(guid.Data2 >> 8) & 0xF];
		_CSTR_GUIDTOSTRING[12] = _CSTR_HEXCHARS[(guid.Data2 >> 4) & 0xF];
		_CSTR_GUIDTOSTRING[13] = _CSTR_HEXCHARS[guid.Data2 & 0xF];
		_CSTR_GUIDTOSTRING[15] = _CSTR_HEXCHARS[(guid.Data3 >> 12) & 0xF];
		_CSTR_GUIDTOSTRING[16] = _CSTR_HEXCHARS[(guid.Data3 >> 8) & 0xF];
		_CSTR_GUIDTOSTRING[17] = _CSTR_HEXCHARS[(guid.Data3 >> 4) & 0xF];
		_CSTR_GUIDTOSTRING[18] = _CSTR_HEXCHARS[guid.Data3 & 0xF];
		_CSTR_GUIDTOSTRING[20] = _CSTR_HEXCHARS[(guid.Data4[0] >> 4) & 0xF];
		_CSTR_GUIDTOSTRING[21] = _CSTR_HEXCHARS[guid.Data4[0] & 0xF];
		_CSTR_GUIDTOSTRING[23] = _CSTR_HEXCHARS[(guid.Data4[1] >> 4) & 0xF];
		_CSTR_GUIDTOSTRING[24] = _CSTR_HEXCHARS[guid.Data4[1] & 0xF];
		_CSTR_GUIDTOSTRING[26] = _CSTR_HEXCHARS[(guid.Data4[2] >> 4) & 0xF];
		_CSTR_GUIDTOSTRING[27] = _CSTR_HEXCHARS[guid.Data4[2] & 0xF];
		_CSTR_GUIDTOSTRING[28] = _CSTR_HEXCHARS[(guid.Data4[3] >> 4) & 0xF];
		_CSTR_GUIDTOSTRING[29] = _CSTR_HEXCHARS[guid.Data4[3] & 0xF];
		_CSTR_GUIDTOSTRING[31] = _CSTR_HEXCHARS[(guid.Data4[4] >> 4) & 0xF];
		_CSTR_GUIDTOSTRING[32] = _CSTR_HEXCHARS[guid.Data4[4] & 0xF];
		_CSTR_GUIDTOSTRING[34] = _CSTR_HEXCHARS[(guid.Data4[5] >> 4) & 0xF];
		_CSTR_GUIDTOSTRING[35] = _CSTR_HEXCHARS[guid.Data4[5] & 0xF];
		_CSTR_GUIDTOSTRING[37] = _CSTR_HEXCHARS[(guid.Data4[6] >> 4) & 0xF];
		_CSTR_GUIDTOSTRING[38] = _CSTR_HEXCHARS[guid.Data4[6] & 0xF];
		_CSTR_GUIDTOSTRING[40] = _CSTR_HEXCHARS[(guid.Data4[7] >> 4) & 0xF];
		_CSTR_GUIDTOSTRING[41] = _CSTR_HEXCHARS[guid.Data4[7] & 0xF];
		return &_CSTR_GUIDTOSTRING[0];
	}

	CCHAR* CString::ToString(const EFI::EFI_STATUS status)
	{
		switch (status)
		{
		case EFI::EFI_STATUS::ABORTED:
			return (CCHAR*)_CSTR_ABORTED;
		case EFI::EFI_STATUS::ACCESS_DENIED:
			return (CCHAR*)_CSTR_ACCESS_DENIED;
		case EFI::EFI_STATUS::ALREADY_STARTED:
			return (CCHAR*)_CSTR_ALREADY_STARTED;
		case EFI::EFI_STATUS::BAD_BUFFER_SIZE:
			return (CCHAR*)_CSTR_BAD_BUFFER_SIZE;
		case EFI::EFI_STATUS::BUFFER_TOO_SMALL:
			return (CCHAR*)_CSTR_BUFFER_TOO_SMALL;
		case EFI::EFI_STATUS::COMPROMISED_DATA:
			return (CCHAR*)_CSTR_COMPROMISED_DATA;
		case EFI::EFI_STATUS::CRC_ERROR:
			return (CCHAR*)_CSTR_CRC_ERROR;
		case EFI::EFI_STATUS::DEVICE_ERROR:
			return (CCHAR*)_CSTR_DEVICE_ERROR;
		case EFI::EFI_STATUS::END_OF_FILE:
			return (CCHAR*)_CSTR_END_OF_FILE;
		case EFI::EFI_STATUS::END_OF_MEDIA:
			return (CCHAR*)_CSTR_END_OF_MEDIA;
		case EFI::EFI_STATUS::HTTP_ERROR:
			return (CCHAR*)_CSTR_HTTP_ERROR;
		case EFI::EFI_STATUS::ICMP_ERROR:
			return (CCHAR*)_CSTR_ICMP_ERROR;
		case EFI::EFI_STATUS::INCOMPATIBLE_VERSION:
			return (CCHAR*)_CSTR_INCOMPATIBLE_VERSION;
		case EFI::EFI_STATUS::INVALID_LANGUAGE:
			return (CCHAR*)_CSTR_INVALID_LANGUAGE;
		case EFI::EFI_STATUS::INVALID_PARAMETER:
			return (CCHAR*)_CSTR_INVALID_PARAMETER;
		case EFI::EFI_STATUS::IP_ADDRESS_CONFLICT:
			return (CCHAR*)_CSTR_IP_ADDRESS_CONFLICT;
		case EFI::EFI_STATUS::LOAD_ERROR:
			return (CCHAR*)_CSTR_LOAD_ERROR;
		case EFI::EFI_STATUS::MEDIA_CHANGED:
			return (CCHAR*)_CSTR_MEDIA_CHANGED;
		case EFI::EFI_STATUS::NO_MAPPING:
			return (CCHAR*)_CSTR_NO_MAPPING;
		case EFI::EFI_STATUS::NO_MEDIA:
			return (CCHAR*)_CSTR_NO_MEDIA;
		case EFI::EFI_STATUS::NO_RESPONSE:
			return (CCHAR*)_CSTR_NO_RESPONSE;
		case EFI::EFI_STATUS::NOT_FOUND:
			return (CCHAR*)_CSTR_NOT_FOUND;
		case EFI::EFI_STATUS::NOT_READY:
			return (CCHAR*)_CSTR_NOT_READY;
		case EFI::EFI_STATUS::NOT_STARTED:
			return (CCHAR*)_CSTR_NOT_STARTED;
		case EFI::EFI_STATUS::OUT_OF_RESOURCES:
			return (CCHAR*)_CSTR_OUT_OF_RESOURCES;
		case EFI::EFI_STATUS::PROTOCOL_ERROR:
			return (CCHAR*)_CSTR_PROTOCOL_ERROR;
		case EFI::EFI_STATUS::SECURITY_VIOLATION:
			return (CCHAR*)_CSTR_SECURITY_VIOLATION;
		case EFI::EFI_STATUS::SUCCESS:
			return (CCHAR*)_CSTR_SUCCESS;
		case EFI::EFI_STATUS::TFTP_ERROR:
			return (CCHAR*)_CSTR_TFTP_ERROR;
		case EFI::EFI_STATUS::TIMEOUT:
			return (CCHAR*)_CSTR_TIMEOUT;
		case EFI::EFI_STATUS::UNSUPPORTED:
			return (CCHAR*)_CSTR_UNSUPPORTED;
		case EFI::EFI_STATUS::VOLUME_CORRUPTED:
			return (CCHAR*)_CSTR_VOLUME_CORRUPTED;
		case EFI::EFI_STATUS::VOLUME_FULL:
			return (CCHAR*)_CSTR_VOLUME_FULL;
		case EFI::EFI_STATUS::WARN_BUFFER_TOO_SMALL:
			return (CCHAR*)_CSTR_WARN_BUFFER_TOO_SMALL;
		case EFI::EFI_STATUS::WARN_DELETE_FAILURE:
			return (CCHAR*)_CSTR_WARN_DELETE_FAILURE;
		case EFI::EFI_STATUS::WARN_FILE_SYSTEM:
			return (CCHAR*)_CSTR_WARN_FILE_SYSTEM;
		case EFI::EFI_STATUS::WARN_RESET_REQUIRED:
			return (CCHAR*)_CSTR_WARN_RESET_REQUIRED;
		case EFI::EFI_STATUS::WARN_STALE_DATA:
			return (CCHAR*)_CSTR_WARN_STALE_DATA;
		case EFI::EFI_STATUS::WARN_UNKNOWN_GLYPH:
			return (CCHAR*)_CSTR_WARN_UNKNOWN_GLYPH;
		case EFI::EFI_STATUS::WARN_WRITE_FAILURE:
			return (CCHAR*)_CSTR_WARN_WRITE_FAILURE;
		case EFI::EFI_STATUS::WRITE_PROTECTED:
			return (CCHAR*)_CSTR_WRITE_PROTECTED;
		default:
			return nullptr;
		}
	}

	CCHAR* CString::ToString(const Common::System::AllocatorStatus status)
	{
		switch (status)
		{
		case Common::System::AllocatorStatus::Success:
			return (CCHAR*)_CSTR_ALLOC_STATUS_SUCCESS;
		case Common::System::AllocatorStatus::Invalid_Parameters:
			return (CCHAR*)_CSTR_ALLOC_STATUS_INVALID_PARAMETER;
		case Common::System::AllocatorStatus::Not_Enough_Memory:
			return (CCHAR*)_CSTR_ALLOC_STATUS_NOT_ENOUGH_MEMORY;
		case Common::System::AllocatorStatus::Not_Enough_Pages:
			return (CCHAR*)_CSTR_ALLOC_STATUS_NOT_ENOUGH_PAGES;
		case Common::System::AllocatorStatus::Access_Denied:
			return (CCHAR*)_CSTR_ALLOC_STATUS_ACCESS_DENIED;
		}
	}

	CCHAR* CString::ToString(const INT16 value)
	{
		if (value == 0)
		{
			_CSTR_VALUETOSTRING[0] = '0';
			_CSTR_VALUETOSTRING[1] = '\0';
			return &_CSTR_VALUETOSTRING[0];
		}

		INT16 i = value;
		INT8 len = 6;
		_CSTR_VALUETOSTRING[len] = '\0';
		bool isNegative = false;
		if (i < 0)
		{
			isNegative = true;
			i = -i; // make it positive
		}
		for (; i > 0; i /= 10)
		{
			_CSTR_VALUETOSTRING[--len] = (i % 10) + '0';
		}
		if (isNegative)
		{
			_CSTR_VALUETOSTRING[--len] = '-';
		}
		return &_CSTR_VALUETOSTRING[len];
	}

	CCHAR* CString::ToString(const INT32 value)
	{
		if (value == 0)
		{
			_CSTR_VALUETOSTRING[0] = '0';
			_CSTR_VALUETOSTRING[1] = '\0';
			return &_CSTR_VALUETOSTRING[0];
		}

		INT32 i = value;
		INT8 len = 11;
		_CSTR_VALUETOSTRING[len] = '\0';
		bool isNegative = false;
		if (i < 0)
		{
			isNegative = true;
			i = -i; // make it positive
		}
		for (; i > 0; i /= 10)
		{
			_CSTR_VALUETOSTRING[--len] = (i % 10) + '0';
		}
		if (isNegative)
		{
			_CSTR_VALUETOSTRING[--len] = '-';
		}
		return &_CSTR_VALUETOSTRING[len];
	}

	CCHAR* CString::ToString(const INT64 value)
	{
		if (value == 0)
		{
			_CSTR_VALUETOSTRING[0] = '0';
			_CSTR_VALUETOSTRING[1] = '\0';
			return &_CSTR_VALUETOSTRING[0];
		}

		INT64 i = value;
		INT8 len = 21;
		_CSTR_VALUETOSTRING[len] = '\0';
		bool isNegative = false;
		if (i < 0)
		{
			isNegative = true;
			i = -i; // make it positive
		}
		for (; i > 0; i /= 10)
		{
			_CSTR_VALUETOSTRING[--len] = (i % 10) + '0';
		}
		if (isNegative)
		{
			_CSTR_VALUETOSTRING[--len] = '-';
		}
		return &_CSTR_VALUETOSTRING[len];
	}

	CCHAR* CString::ToString(const INT8 value)
	{
		if (value == 0)
		{
			_CSTR_VALUETOSTRING[0] = '0';
			_CSTR_VALUETOSTRING[1] = '\0';
			return &_CSTR_VALUETOSTRING[0];
		}

		INT8 i = value;
		INT8 len = 4;
		_CSTR_VALUETOSTRING[len] = '\0';
		bool isNegative = false;
		if (i < 0)
		{
			isNegative = true;
			i = -i; // make it positive
		}
		for (; i > 0; i /= 10)
		{
			_CSTR_VALUETOSTRING[--len] = (i % 10) + '0';
		}
		if (isNegative)
		{
			_CSTR_VALUETOSTRING[--len] = '-';
		}
		return &_CSTR_VALUETOSTRING[len];
	}

	CCHAR* CString::ToString(const UINT16 value)
	{
		if (value == 0)
		{
			_CSTR_VALUETOSTRING[0] = '0';
			_CSTR_VALUETOSTRING[1] = '\0';
			return &_CSTR_VALUETOSTRING[0];
		}

		UINT16 i = value;
		INT8 len = 5;
		_CSTR_VALUETOSTRING[len] = '\0';
		for (; i > 0; i /= 10)
		{
			_CSTR_VALUETOSTRING[--len] = (i % 10) + '0';
		}
		return &_CSTR_VALUETOSTRING[len];
	}

	CCHAR* CString::ToString(const UINT32 value)
	{
		if (value == 0)
		{
			_CSTR_VALUETOSTRING[0] = '0';
			_CSTR_VALUETOSTRING[1] = '\0';
			return &_CSTR_VALUETOSTRING[0];
		}

		UINT32 i = value;
		INT8 len = 10;
		_CSTR_VALUETOSTRING[len] = '\0';
		for (; i > 0; i /= 10)
		{
			_CSTR_VALUETOSTRING[--len] = (i % 10) + '0';
		}
		return &_CSTR_VALUETOSTRING[len];
	}

	CCHAR* CString::ToString(const UINT64 value)
	{
		if (value == 0)
		{
			_CSTR_VALUETOSTRING[0] = '0';
			_CSTR_VALUETOSTRING[1] = '\0';
			return &_CSTR_VALUETOSTRING[0];
		}

		UINT64 i = value;
		INT8 len = 20;
		_CSTR_VALUETOSTRING[len] = '\0';
		for (; i > 0; i /= 10)
		{
			_CSTR_VALUETOSTRING[--len] = (i % 10) + '0';
		}
		return &_CSTR_VALUETOSTRING[len];
	}

	CCHAR* CString::ToString(const UINT8 value)
	{
		if (value == 0)
		{
			_CSTR_VALUETOSTRING[0] = '0';
			_CSTR_VALUETOSTRING[1] = '\0';
			return &_CSTR_VALUETOSTRING[0];
		}

		UINT8 i = value;
		INT8 len = 3;
		_CSTR_VALUETOSTRING[len] = '\0';
		for (; i > 0; i /= 10)
		{
			_CSTR_VALUETOSTRING[--len] = (i % 10) + '0';
		}
		return &_CSTR_VALUETOSTRING[len];
	}

	CCHAR* CString::ToString(const VOID_PTR ptr)
	{
		UINT64 value = (UINT64)ptr;
		if (value == 0)
		{
			_CSTR_VALUETOSTRING[0] = '0';
			_CSTR_VALUETOSTRING[1] = '\0';
			return &_CSTR_VALUETOSTRING[0];
		}

		UINT64 i = value;
		INT8 len = 20;
		_CSTR_VALUETOSTRING[len] = '\0';
		for (; i > 0; i /= 10)
		{
			_CSTR_VALUETOSTRING[--len] = (i % 10) + '0';
		}
		return &_CSTR_VALUETOSTRING[len];
	}

	CCHAR* CString::ToString(const BOOLEAN boolean)
	{
		if (boolean)
		{
			return (CCHAR*)_CSTR_BOOLEAN_TRUE;
		}
		else
		{
			return (CCHAR*)_CSTR_BOOLEAN_FALSE;
		}
	}

	UINTN CString::Length(const CCHAR* str)
	{
		if (str == nullptr)
		{
			return 0;
		}

		if (str[0] == '\0')
		{
			return 1;
		}

		UINTN index = 0;
		UINTN len = 1;
		while (str[index] != '\0')
		{
			len++;
			index++;
		}
		return len;
	}

	BOOLEAN CString::Compare(const CCHAR* l, const CCHAR* r, StringCulture culture)
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

		UINTN lLength = Length(l);
		UINTN rLength = Length(r);

		if (lLength != rLength)
		{
			return FALSE;
		}



		switch (culture)
		{
		case Common::Enviroment::InvariantCulture:
		case Common::Enviroment::CurrentCulture:
		case Common::Enviroment::Ordinal:
		{
			/*Binary Comparison of string*/

			for (UINTN index = 0; index < lLength; index++)
			{
				if (l[index] != r[index])
				{
					return FALSE;
				}
			}
			return TRUE;
		}
		case Common::Enviroment::InvariantCultureIgnoreCase:
		case Common::Enviroment::CurrentCultureIgnoreCase:
		case Common::Enviroment::OrdinalIgnoreCase:
		{
			/*Binary Comparison, Ignoring Case of string*/

			UINTN index = 0;

			for (UINTN index = 0; index < lLength; index++)
			{
				CHAR8 lChar = l[index];
				CHAR8 rChar = r[index];
				/*If the character is a lower case letter, switch it to upper for comparison*/
				if (lChar >= 'a' && lChar <= 'z')
				{
					lChar -= 32;
				}
				if (rChar >= 'a' && rChar <= 'z')
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

	BOOLEAN CString::StartsWith(const CCHAR* str, const CCHAR* value, StringCulture culture)
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

		UINTN strLength = Length(str);
		UINTN valueLength = Length(value);

		if (strLength < valueLength)
		{
			return FALSE;
		}

		switch (culture)
		{
		case Common::Enviroment::InvariantCulture:
		case Common::Enviroment::CurrentCulture:
		case Common::Enviroment::Ordinal:
		{
			for (UINTN index = 0; index < valueLength; index++)
			{
				if (str[index] != value[index])
				{
					return FALSE;
				}
			}
			return TRUE;
		}
		case Common::Enviroment::InvariantCultureIgnoreCase:
		case Common::Enviroment::CurrentCultureIgnoreCase:
		case Common::Enviroment::OrdinalIgnoreCase:
		{
			for (UINTN index = 0; index < valueLength; index++)
			{
				CHAR8 lChar = str[index];
				CHAR8 rChar = value[index];
				/*If the character is a lower case letter, switch it to upper for comparison*/
				if (lChar >= 'a' && lChar <= 'z')
				{
					lChar -= 32;
				}
				if (rChar >= 'a' && rChar <= 'z')
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

	BOOLEAN CString::EndsWith(const CCHAR* str, const CCHAR* value, StringCulture culture)
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

		UINTN strLength = Length(str);
		UINTN valueLength = Length(value);

		if (strLength < valueLength)
		{
			return FALSE;
		}

		switch (culture)
		{
		case Common::Enviroment::InvariantCulture:
		case Common::Enviroment::CurrentCulture:
		case Common::Enviroment::Ordinal:
		{
			UINTN index = 0;
			for (UINTN index = 0; index < valueLength; index++)
			{
				if (str[strLength - valueLength + index] != value[index])
				{
					return FALSE;
				}
			}
			return TRUE;
		}
		case Common::Enviroment::InvariantCultureIgnoreCase:
		case Common::Enviroment::CurrentCultureIgnoreCase:
		case Common::Enviroment::OrdinalIgnoreCase:
		{
			UINTN index = 0;
			for (UINTN index = 0; index < valueLength; index++)
			{
				CHAR8 lChar = str[strLength - valueLength + index];
				CHAR8 rChar = value[index];
				/*If the character is a lower case letter, switch it to upper for comparison*/
				if (lChar >= 'a' && lChar <= 'z')
				{
					lChar -= 32;
				}
				if (rChar >= 'a' && rChar <= 'z')
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

	BOOLEAN CString::Contains(const CCHAR* str, const CCHAR* value, StringCulture culture)
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

		UINTN strLength = Length(str);
		UINTN valueLength = Length(value);

		if (strLength < valueLength)
		{
			return FALSE;
		}

		switch (culture)
		{
		case Common::Enviroment::InvariantCulture:
		case Common::Enviroment::CurrentCulture:
		case Common::Enviroment::Ordinal:
		{
			UINTN index = 0;
			for (UINTN index = 0; index < strLength - valueLength; index++)
			{
				if (str[index] == value[0])
				{
					BOOLEAN match = TRUE;
					for (UINTN i = 0; i < valueLength; i++)
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
		case Common::Enviroment::InvariantCultureIgnoreCase:
		case Common::Enviroment::CurrentCultureIgnoreCase:
		case Common::Enviroment::OrdinalIgnoreCase:
		{
			UINTN index = 0;
			for (UINTN index = 0; index < strLength - valueLength; index++)
			{
				CHAR8 lChar = str[index];
				CHAR8 rChar = value[0];

				/*If the character is a lower case letter, switch it to upper for comparison*/

				if (lChar >= 'a' && lChar <= 'z')
				{
					lChar -= 32;
				}
				if (rChar >= 'a' && rChar <= 'z')
				{
					rChar -= 32;
				}

				if (lChar == rChar)
				{
					BOOLEAN match = TRUE;
					for (UINTN i = 0; i < valueLength; i++)
					{
						CHAR8 lChar2 = str[index + i];
						CHAR8 rChar2 = value[i];
						/*If the character is a lower case letter, switch it to upper for comparison*/
						if (lChar2 >= 'a' && lChar2 <= 'z')
						{
							lChar2 -= 32;
						}
						if (rChar2 >= 'a' && rChar2 <= 'z')
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

	BOOLEAN CString::IsNullOrEmpty(const CCHAR* str)
	{
		if (str == nullptr)
		{
			return TRUE;
		};

		if (str[0] == '\0')
		{
			return TRUE;
		}

		return FALSE;
	}

	BOOLEAN CString::IsNullOrWhiteSpace(const CCHAR* str)
	{
		if (str == nullptr)
		{
			return TRUE;
		};

		if (str[0] == '\0')
		{
			return TRUE;
		}

		UINTN index = 0;
		while (str[index] != '\0')
		{
			UINTN i = 0;
			for (UINTN i = 0; i < 30; i++)
			{
				if (str[index] == _CSTR_WHITESPACECHARS[i])
				{
					return TRUE;
				}
			}
			index++;
		}
		return FALSE;
	}
	CCHAR* CString::FromCharArray(CCHAR arr[], UINTN Length)
	{
		if (arr == nullptr)
		{
			return nullptr;
		}

		CCHAR* result = new CCHAR[Length + 1];

		for (UINTN i = 0; i < Length; i++)
		{
			result[i] = arr[i];
		}
		result[Length] = '\0';

		return result;
	}
	CCHAR* CString::FromUTF16String(const CHAR16* str)
	{
		if (str == nullptr)
		{
			return nullptr;
		}

		if (str[0] == '\0')
		{
			return (CCHAR*)"\0";
		}

		UINTN len = UTF16::Length(str);
		CCHAR* result = new CCHAR[len];
		for (UINTN i = 0; i < len; i++)
		{
			result[i] = (CCHAR)(str[i] & 0x00FF);
		}
		return result;
	}
	CCHAR* CString::FromUTF8String(const CHAR8* str)
	{
		if (str == nullptr)
		{
			return nullptr;
		}

		if (str[0] == '\0')
		{
			return (CCHAR*)"\0";
		}

		UINTN len = UTF8::Length(str);
		CCHAR* result = new CCHAR[len];
		for (UINTN i = 0; i < len; i++)
		{
			result[i] = str[i];
		}
		return result;
	}
#pragma endregion
}