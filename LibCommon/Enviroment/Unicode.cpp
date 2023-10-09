#pragma once
#include "TypeDefs.h"
#include <EFI_GUID.h>
#include <EFI_STATUS.h>
#include "Unicode.h"

namespace Common::Enviroment
{
	CHAR16 _u16_hex16String[6]{ u'\0' };
	CHAR16 _u16_hex32String[10]{ u'\0' };
	CHAR16 _u16_hex64String[18]{ u'\0' };
	CHAR16 _u16_hex8String[4]{ u'\0' };
	CHAR16 _u16_hexGUIDString[39]{ u'\0' };
	CHAR16 _u16_hexu16String[5]{ u'\0' };
	CHAR16 _u16_hexu32String[9]{ u'\0' };
	CHAR16 _u16_hexu64String[17]{ u'\0' };
	CHAR16 _u16_hexu8String[3]{ u'\0' };
	CHAR16 _u16_t16String[7]{ u'\0' };
	CHAR16 _u16_t32String[12]{ u'\0' };
	CHAR16 _u16_t64String[22]{ u'\0' };
	CHAR16 _u16_t8String[5]{ u'\0' };
	CHAR16 _u16_tu16String[6]{ u'\0' };
	CHAR16 _u16_tu32String[11]{ u'\0' };
	CHAR16 _u16_tu64String[21]{ u'\0' };
	CHAR16 _u16_tu8String[4]{ u'\0' };
	CHAR8 _hex16String[6]{ '\0' };
	CHAR8 _hex32String[10]{ '\0' };
	CHAR8 _hex64String[18]{ '\0' };
	CHAR8 _hex8String[4]{ '\0' };
	CHAR8 _hexGUIDString[39]{ '\0' };
	CHAR8 _hexu16String[5]{ '\0' };
	CHAR8 _hexu32String[9]{ '\0' };
	CHAR8 _hexu64String[17]{ '\0' };
	CHAR8 _hexu8String[3]{ '\0' };
	CHAR8 _t16String[7]{ '\0' };
	CHAR8 _t32String[12]{ '\0' };
	CHAR8 _t64String[22]{ '\0' };
	CHAR8 _t8String[5]{ '\0' };
	CHAR8 _tu16String[6]{ '\0' };
	CHAR8 _tu32String[11]{ '\0' };
	CHAR8 _tu64String[21]{ '\0' };
	CHAR8 _tu8String[4]{ '\0' };
	const CHAR16* _u16_hexChars = u"0123456789ABCDEF";
	const CHAR16* Common::Enviroment::UTF16::NewLine = u"\r\n";
	const CHAR8* _hexChars = "0123456789ABCDEF";
	const CHAR8* Common::Enviroment::UTF8::NewLine = "\r\n";
	constinit const CHAR16* _u16_ABORTED = u"ABORTED";
	constinit const CHAR16* _u16_ACCESS_DENIED = u"ACCESS_DENIED";
	constinit const CHAR16* _u16_ALREADY_STARTED = u"ALREADY_STARTED";
	constinit const CHAR16* _u16_BAD_BUFFER_SIZE = u"BAD_BUFFER_SIZE";
	constinit const CHAR16* _u16_BUFFER_TOO_SMALL = u"BUFFER_TOO_SMALL";
	constinit const CHAR16* _u16_COMPROMISED_DATA = u"COMPROMISED_DATA";
	constinit const CHAR16* _u16_CRC_ERROR = u"CRC_ERROR";
	constinit const CHAR16* _u16_DEVICE_ERROR = u"DEVICE_ERROR";
	constinit const CHAR16* _u16_END_OF_FILE = u"END_OF_FILE";
	constinit const CHAR16* _u16_END_OF_MEDIA = u"END_OF_MEDIA";
	constinit const CHAR16* _u16_HTTP_ERROR = u"HTTP_ERROR";
	constinit const CHAR16* _u16_ICMP_ERROR = u"ICMP_ERROR";
	constinit const CHAR16* _u16_INCOMPATIBLE_VERSION = u"INCOMPATIBLE_VERSION";
	constinit const CHAR16* _u16_INVALID_LANGUAGE = u"INVALID_LANGUAGE";
	constinit const CHAR16* _u16_INVALID_PARAMETER = u"INVALID_PARAMETER";
	constinit const CHAR16* _u16_IP_ADDRESS_CONFLICT = u"IP_ADDRESS_CONFLICT";
	constinit const CHAR16* _u16_LOAD_ERROR = u"LOAD_ERROR";
	constinit const CHAR16* _u16_MEDIA_CHANGED = u"MEDIA_CHANGED";
	constinit const CHAR16* _u16_NO_MAPPING = u"NO_MAPPING";
	constinit const CHAR16* _u16_NO_MEDIA = u"NO_MEDIA";
	constinit const CHAR16* _u16_NO_RESPONSE = u"NO_RESPONSE";
	constinit const CHAR16* _u16_NOT_FOUND = u"NOT_FOUND";
	constinit const CHAR16* _u16_NOT_READY = u"NOT_READY";
	constinit const CHAR16* _u16_NOT_STARTED = u"NOT_STARTED";
	constinit const CHAR16* _u16_OUT_OF_RESOURCES = u"OUT_OF_RESOURCES";
	constinit const CHAR16* _u16_PROTOCOL_ERROR = u"PROTOCOL_ERROR";
	constinit const CHAR16* _u16_SECURITY_VIOLATION = u"SECURITY_VIOLATION";
	constinit const CHAR16* _u16_SUCCESS = u"SUCCESS";
	constinit const CHAR16* _u16_TFTP_ERROR = u"TFTP_ERROR";
	constinit const CHAR16* _u16_TIMEOUT = u"TIMEOUT";
	constinit const CHAR16* _u16_UNSUPPORTED = u"UNSUPPORTED";
	constinit const CHAR16* _u16_VOLUME_CORRUPTED = u"VOLUME_CORRUPTED";
	constinit const CHAR16* _u16_VOLUME_FULL = u"VOLUME_FULL";
	constinit const CHAR16* _u16_WARN_BUFFER_TOO_SMALL = u"WARN_BUFFER_TOO_SMALL";
	constinit const CHAR16* _u16_WARN_DELETE_FAILURE = u"WARN_DELETE_FAILURE";
	constinit const CHAR16* _u16_WARN_FILE_SYSTEM = u"WARN_FILE_SYSTEM";
	constinit const CHAR16* _u16_WARN_RESET_REQUIRED = u"WARN_RESET_REQUIRED";
	constinit const CHAR16* _u16_WARN_STALE_DATA = u"WARN_STALE_DATA";
	constinit const CHAR16* _u16_WARN_UNKNOWN_GLYPH = u"WARN_UNKNOWN_GLYPH";
	constinit const CHAR16* _u16_WARN_WRITE_FAILURE = u"WARN_WRITE_FAILURE";
	constinit const CHAR16* _u16_WRITE_PROTECTED = u"WRITE_PROTECTED";
	constinit const CHAR8* _ABORTED = "ABORTED";
	constinit const CHAR8* _ACCESS_DENIED = "ACCESS_DENIED";
	constinit const CHAR8* _ALREADY_STARTED = "ALREADY_STARTED";
	constinit const CHAR8* _BAD_BUFFER_SIZE = "BAD_BUFFER_SIZE";
	constinit const CHAR8* _BUFFER_TOO_SMALL = "BUFFER_TOO_SMALL";
	constinit const CHAR8* _COMPROMISED_DATA = "COMPROMISED_DATA";
	constinit const CHAR8* _CRC_ERROR = "CRC_ERROR";
	constinit const CHAR8* _DEVICE_ERROR = "DEVICE_ERROR";
	constinit const CHAR8* _END_OF_FILE = "END_OF_FILE";
	constinit const CHAR8* _END_OF_MEDIA = "END_OF_MEDIA";
	constinit const CHAR8* _HTTP_ERROR = "HTTP_ERROR";
	constinit const CHAR8* _ICMP_ERROR = "ICMP_ERROR";
	constinit const CHAR8* _INCOMPATIBLE_VERSION = "INCOMPATIBLE_VERSION";
	constinit const CHAR8* _INVALID_LANGUAGE = "INVALID_LANGUAGE";
	constinit const CHAR8* _INVALID_PARAMETER = "INVALID_PARAMETER";
	constinit const CHAR8* _IP_ADDRESS_CONFLICT = "IP_ADDRESS_CONFLICT";
	constinit const CHAR8* _LOAD_ERROR = "LOAD_ERROR";
	constinit const CHAR8* _MEDIA_CHANGED = "MEDIA_CHANGED";
	constinit const CHAR8* _NO_MAPPING = "NO_MAPPING";
	constinit const CHAR8* _NO_MEDIA = "NO_MEDIA";
	constinit const CHAR8* _NO_RESPONSE = "NO_RESPONSE";
	constinit const CHAR8* _NOT_FOUND = "NOT_FOUND";
	constinit const CHAR8* _NOT_READY = "NOT_READY";
	constinit const CHAR8* _NOT_STARTED = "NOT_STARTED";
	constinit const CHAR8* _OUT_OF_RESOURCES = "OUT_OF_RESOURCES";
	constinit const CHAR8* _PROTOCOL_ERROR = "PROTOCOL_ERROR";
	constinit const CHAR8* _SECURITY_VIOLATION = "SECURITY_VIOLATION";
	constinit const CHAR8* _SUCCESS = "SUCCESS";
	constinit const CHAR8* _TFTP_ERROR = "TFTP_ERROR";
	constinit const CHAR8* _TIMEOUT = "TIMEOUT";
	constinit const CHAR8* _UNSUPPORTED = "UNSUPPORTED";
	constinit const CHAR8* _VOLUME_CORRUPTED = "VOLUME_CORRUPTED";
	constinit const CHAR8* _VOLUME_FULL = "VOLUME_FULL";
	constinit const CHAR8* _WARN_BUFFER_TOO_SMALL = "WARN_BUFFER_TOO_SMALL";
	constinit const CHAR8* _WARN_DELETE_FAILURE = "WARN_DELETE_FAILURE";
	constinit const CHAR8* _WARN_FILE_SYSTEM = "WARN_FILE_SYSTEM";
	constinit const CHAR8* _WARN_RESET_REQUIRED = "WARN_RESET_REQUIRED";
	constinit const CHAR8* _WARN_STALE_DATA = "WARN_STALE_DATA";
	constinit const CHAR8* _WARN_UNKNOWN_GLYPH = "WARN_UNKNOWN_GLYPH";
	constinit const CHAR8* _WARN_WRITE_FAILURE = "WARN_WRITE_FAILURE";
	constinit const CHAR8* _WRITE_PROTECTED = "WRITE_PROTECTED";

	const CHAR16* UTF16::ToString(const EFI::EFI_GUID guid)
	{
		_u16_hexGUIDString[0] = u'{';
		_u16_hexGUIDString[1] = _u16_hexChars[(guid.Data1 >> 28) & 0x0F];
		_u16_hexGUIDString[2] = _u16_hexChars[(guid.Data1 >> 24) & 0x0F];
		_u16_hexGUIDString[3] = _u16_hexChars[(guid.Data1 >> 20) & 0x0F];
		_u16_hexGUIDString[4] = _u16_hexChars[(guid.Data1 >> 16) & 0x0F];
		_u16_hexGUIDString[5] = _u16_hexChars[(guid.Data1 >> 12) & 0x0F];
		_u16_hexGUIDString[6] = _u16_hexChars[(guid.Data1 >> 8) & 0x0F];
		_u16_hexGUIDString[7] = _u16_hexChars[(guid.Data1 >> 4) & 0x0F];
		_u16_hexGUIDString[8] = _u16_hexChars[guid.Data1 & 0x0F];
		_u16_hexGUIDString[9] = u'-';
		_u16_hexGUIDString[10] = _u16_hexChars[(guid.Data2 >> 12) & 0x0F];
		_u16_hexGUIDString[11] = _u16_hexChars[(guid.Data2 >> 8) & 0x0F];
		_u16_hexGUIDString[12] = _u16_hexChars[(guid.Data2 >> 4) & 0x0F];
		_u16_hexGUIDString[13] = _u16_hexChars[guid.Data2 & 0x0F];
		_u16_hexGUIDString[14] = u'-';
		_u16_hexGUIDString[15] = _u16_hexChars[(guid.Data3 >> 12) & 0x0F];
		_u16_hexGUIDString[16] = _u16_hexChars[(guid.Data3 >> 8) & 0x0F];
		_u16_hexGUIDString[17] = _u16_hexChars[(guid.Data3 >> 4) & 0x0F];
		_u16_hexGUIDString[18] = _u16_hexChars[guid.Data3 & 0x0F];
		_u16_hexGUIDString[19] = u'-';
		_u16_hexGUIDString[20] = _u16_hexChars[(guid.Data4[0] >> 4) & 0x0F];
		_u16_hexGUIDString[21] = _u16_hexChars[guid.Data4[0] & 0x0F];
		_u16_hexGUIDString[22] = _u16_hexChars[(guid.Data4[1] >> 4) & 0x0F];
		_u16_hexGUIDString[23] = _u16_hexChars[guid.Data4[1] & 0x0F];
		_u16_hexGUIDString[24] = u'-';
		_u16_hexGUIDString[25] = _u16_hexChars[(guid.Data4[2] >> 4) & 0x0F];
		_u16_hexGUIDString[26] = _u16_hexChars[guid.Data4[2] & 0x0F];
		_u16_hexGUIDString[27] = _u16_hexChars[(guid.Data4[3] >> 4) & 0x0F];
		_u16_hexGUIDString[28] = _u16_hexChars[guid.Data4[3] & 0x0F];
		_u16_hexGUIDString[29] = _u16_hexChars[(guid.Data4[4] >> 4) & 0x0F];
		_u16_hexGUIDString[30] = _u16_hexChars[guid.Data4[4] & 0x0F];
		_u16_hexGUIDString[31] = _u16_hexChars[(guid.Data4[5] >> 4) & 0x0F];
		_u16_hexGUIDString[32] = _u16_hexChars[guid.Data4[5] & 0x0F];
		_u16_hexGUIDString[33] = _u16_hexChars[(guid.Data4[6] >> 4) & 0x0F];
		_u16_hexGUIDString[34] = _u16_hexChars[guid.Data4[6] & 0x0F];
		_u16_hexGUIDString[35] = _u16_hexChars[(guid.Data4[7] >> 4) & 0x0F];
		_u16_hexGUIDString[36] = _u16_hexChars[guid.Data4[7] & 0x0F];
		_u16_hexGUIDString[37] = u'}';
		_u16_hexGUIDString[38] = u'\0';
		return _u16_hexGUIDString;
	}

	const CHAR16* UTF16::ToString(EFI::EFI_STATUS status)
	{
		switch (status)
		{
		case EFI::EFI_STATUS::SUCCESS:
			return _u16_SUCCESS;
		case EFI::EFI_STATUS::LOAD_ERROR:
			return _u16_LOAD_ERROR;
		case EFI::EFI_STATUS::INVALID_PARAMETER:
			return _u16_INVALID_PARAMETER;
		case EFI::EFI_STATUS::UNSUPPORTED:
			return _u16_UNSUPPORTED;
		case EFI::EFI_STATUS::BAD_BUFFER_SIZE:
			return _u16_BAD_BUFFER_SIZE;
		case EFI::EFI_STATUS::BUFFER_TOO_SMALL:
			return _u16_BUFFER_TOO_SMALL;
		case EFI::EFI_STATUS::NOT_READY:
			return _u16_NOT_READY;
		case EFI::EFI_STATUS::DEVICE_ERROR:
			return _u16_DEVICE_ERROR;
		case EFI::EFI_STATUS::WRITE_PROTECTED:
			return _u16_WRITE_PROTECTED;
		case EFI::EFI_STATUS::OUT_OF_RESOURCES:
			return _u16_OUT_OF_RESOURCES;
		case EFI::EFI_STATUS::VOLUME_CORRUPTED:
			return _u16_VOLUME_CORRUPTED;
		case EFI::EFI_STATUS::VOLUME_FULL:
			return _u16_VOLUME_FULL;
		case EFI::EFI_STATUS::NO_MEDIA:
			return _u16_NO_MEDIA;
		case EFI::EFI_STATUS::MEDIA_CHANGED:
			return _u16_MEDIA_CHANGED;
		case EFI::EFI_STATUS::NOT_FOUND:
			return _u16_NOT_FOUND;
		case EFI::EFI_STATUS::ACCESS_DENIED:
			return _u16_ACCESS_DENIED;
		case EFI::EFI_STATUS::NO_RESPONSE:
			return _u16_NO_RESPONSE;
		case EFI::EFI_STATUS::NO_MAPPING:
			return _u16_NO_MAPPING;
		case EFI::EFI_STATUS::TIMEOUT:
			return _u16_TIMEOUT;
		case EFI::EFI_STATUS::NOT_STARTED:
			return _u16_NOT_STARTED;
		case EFI::EFI_STATUS::ALREADY_STARTED:
			return _u16_ALREADY_STARTED;
		case EFI::EFI_STATUS::ABORTED:
			return _u16_ABORTED;
		case EFI::EFI_STATUS::ICMP_ERROR:
			return _u16_ICMP_ERROR;
		case EFI::EFI_STATUS::TFTP_ERROR:
			return _u16_TFTP_ERROR;
		case EFI::EFI_STATUS::PROTOCOL_ERROR:
			return _u16_PROTOCOL_ERROR;
		case EFI::EFI_STATUS::INCOMPATIBLE_VERSION:
			return _u16_INCOMPATIBLE_VERSION;
		case EFI::EFI_STATUS::SECURITY_VIOLATION:
			return _u16_SECURITY_VIOLATION;
		case EFI::EFI_STATUS::CRC_ERROR:
			return _u16_CRC_ERROR;
		case EFI::EFI_STATUS::END_OF_MEDIA:
			return _u16_END_OF_MEDIA;
		case EFI::EFI_STATUS::END_OF_FILE:
			return _u16_END_OF_FILE;
		case EFI::EFI_STATUS::INVALID_LANGUAGE:
			return _u16_INVALID_LANGUAGE;
		case EFI::EFI_STATUS::COMPROMISED_DATA:
			return _u16_COMPROMISED_DATA;
		case EFI::EFI_STATUS::IP_ADDRESS_CONFLICT:
			return _u16_IP_ADDRESS_CONFLICT;
		case EFI::EFI_STATUS::HTTP_ERROR:
			return _u16_HTTP_ERROR;

		case EFI::EFI_STATUS::WARN_UNKNOWN_GLYPH:
			return _u16_WARN_UNKNOWN_GLYPH;
		case EFI::EFI_STATUS::WARN_DELETE_FAILURE:
			return _u16_WARN_DELETE_FAILURE;
		case EFI::EFI_STATUS::WARN_WRITE_FAILURE:
			return _u16_WARN_WRITE_FAILURE;
		case EFI::EFI_STATUS::WARN_BUFFER_TOO_SMALL:
			return _u16_WARN_BUFFER_TOO_SMALL;
		case EFI::EFI_STATUS::WARN_STALE_DATA:
			return _u16_WARN_STALE_DATA;
		case EFI::EFI_STATUS::WARN_FILE_SYSTEM:
			return _u16_WARN_FILE_SYSTEM;
		case EFI::EFI_STATUS::WARN_RESET_REQUIRED:
			return _u16_WARN_RESET_REQUIRED;
		default: return nullptr;
		}
	}

	const CHAR16* UTF16::ToString(const UINT8 b)
	{
		if (b == 0)
		{
			_u16_tu8String[0] = u'0';
			_u16_tu8String[1] = u'\0';
			return &_u16_tu8String[0];
		}

		UINT8 i = b;
		_u16_tu8String[3] = u'\0';
		UINT8 len = 3;
		for (; i > 0; i /= 10)
		{
			_u16_tu8String[--len] = (i % 10) + u'0';
		}
		return &_u16_tu8String[len];
	}
	const CHAR16* UTF16::ToString(const UINT16 b)
	{
		if (b == 0)
		{
			_u16_tu16String[0] = u'0';
			_u16_tu16String[1] = u'\0';
			return &_u16_tu16String[0];
		}

		UINT16 i = b;
		_u16_tu16String[5] = u'\0';
		UINT8 len = 5;
		for (; i > 0; i /= 10)
		{
			_u16_tu16String[--len] = (i % 10) + u'0';
		}

		return &_u16_tu16String[len];
	}
	const CHAR16* UTF16::ToString(const UINT32 b)
	{
		if (b == 0)
		{
			_u16_tu32String[0] = u'0';
			_u16_tu32String[1] = u'\0';
			return &_u16_tu32String[0];
		}

		UINT32 i = b;
		_u16_tu32String[10] = u'\0';
		UINT8 len = 10;
		for (; i > 0; i /= 10)
		{
			_u16_tu32String[--len] = (i % 10) + u'0';
		}

		return &_u16_tu32String[len];
	}
	const CHAR16* UTF16::ToString(const UINT64 b)
	{
		if (b == 0)
		{
			_u16_tu64String[0] = u'0';
			_u16_tu64String[1] = u'\0';
			return &_u16_tu64String[0];
		}

		UINT64 i = b;
		_u16_tu64String[20] = u'\0';
		UINT8 len = 20;
		for (; i > 0; i /= 10)
		{
			_u16_tu64String[--len] = (i % 10) + u'0';
		}

		return &_u16_tu64String[len];
	}

	const CHAR16* UTF16::ToHex(const UINT8 b)
	{
		_u16_hexu8String[0] = _u16_hexChars[(b >> 4) & 0x0F];
		_u16_hexu8String[1] = _u16_hexChars[b & 0x0F];
		_u16_hexu8String[2] = u'\0';
		return &_u16_hexu8String[0];
	}
	const CHAR16* UTF16::ToHex(const UINT16 b)
	{
		_u16_hexu16String[0] = _u16_hexChars[(b >> 12) & 0x0F];
		_u16_hexu16String[1] = _u16_hexChars[(b >> 8) & 0x0F];
		_u16_hexu16String[2] = _u16_hexChars[(b >> 4) & 0x0F];
		_u16_hexu16String[3] = _u16_hexChars[b & 0x0F];
		_u16_hexu16String[4] = u'\0';
		return &_u16_hexu16String[0];
	}
	const CHAR16* UTF16::ToHex(const UINT32 b)
	{
		_u16_hexu32String[0] = _u16_hexChars[(b >> 28) & 0x0F];
		_u16_hexu32String[1] = _u16_hexChars[(b >> 24) & 0x0F];
		_u16_hexu32String[2] = _u16_hexChars[(b >> 20) & 0x0F];
		_u16_hexu32String[3] = _u16_hexChars[(b >> 16) & 0x0F];
		_u16_hexu32String[4] = _u16_hexChars[(b >> 12) & 0x0F];
		_u16_hexu32String[5] = _u16_hexChars[(b >> 8) & 0x0F];
		_u16_hexu32String[6] = _u16_hexChars[(b >> 4) & 0x0F];
		_u16_hexu32String[7] = _u16_hexChars[b & 0x0F];
		_u16_hexu32String[8] = u'\0';
		return &_u16_hexu32String[0];
	}
	const CHAR16* UTF16::ToHex(const UINT64 b)
	{
		_u16_hexu64String[0] = _u16_hexChars[(b >> 60) & 0x0F];
		_u16_hexu64String[1] = _u16_hexChars[(b >> 56) & 0x0F];
		_u16_hexu64String[2] = _u16_hexChars[(b >> 52) & 0x0F];
		_u16_hexu64String[3] = _u16_hexChars[(b >> 48) & 0x0F];
		_u16_hexu64String[4] = _u16_hexChars[(b >> 44) & 0x0F];
		_u16_hexu64String[5] = _u16_hexChars[(b >> 40) & 0x0F];
		_u16_hexu64String[6] = _u16_hexChars[(b >> 36) & 0x0F];
		_u16_hexu64String[7] = _u16_hexChars[(b >> 32) & 0x0F];
		_u16_hexu64String[8] = _u16_hexChars[(b >> 28) & 0x0F];
		_u16_hexu64String[9] = _u16_hexChars[(b >> 24) & 0x0F];
		_u16_hexu64String[10] = _u16_hexChars[(b >> 20) & 0x0F];
		_u16_hexu64String[11] = _u16_hexChars[(b >> 16) & 0x0F];
		_u16_hexu64String[12] = _u16_hexChars[(b >> 12) & 0x0F];
		_u16_hexu64String[13] = _u16_hexChars[(b >> 8) & 0x0F];
		_u16_hexu64String[14] = _u16_hexChars[(b >> 4) & 0x0F];
		_u16_hexu64String[15] = _u16_hexChars[b & 0x0F];
		_u16_hexu64String[16] = u'\0';
		return &_u16_hexu64String[0];
	}

	const CHAR16* UTF16::ToString(const INT8 b)
	{
		if (b == 0)
		{
			_u16_t8String[0] = u'0';
			_u16_t8String[1] = u'\0';
			return &_u16_t8String[0];
		}

		INT8 i = b;
		_u16_t8String[4] = u'\0';
		INT8 len = 4;
		for (; i > 0; i /= 10)
		{
			_u16_t8String[--len] = (i % 10) + u'0';
		}
		if (i < 0)
		{
			_u16_t8String[--len] = u'-';
		}
		return &_u16_t8String[len];
	}
	const CHAR16* UTF16::ToString(const INT16 b)
	{
		if (b == 0)
		{
			_u16_t16String[0] = u'0';
			_u16_t16String[1] = u'\0';
			return &_u16_t16String[0];
		}

		INT16 i = b;
		_u16_t16String[6] = u'\0';
		INT8 len = 6;
		for (; i > 0; i /= 10)
		{
			_u16_t16String[--len] = (i % 10) + u'0';
		}
		if (i < 0)
		{
			_u16_t16String[--len] = u'-';
		}
		return &_u16_t16String[len];
	}
	const CHAR16* UTF16::ToString(const INT32 b)
	{
		if (b == 0)
		{
			_u16_t32String[0] = u'0';
			_u16_t32String[1] = u'\0';
			return &_u16_t32String[0];
		}

		INT32 i = b;
		_u16_t32String[11] = u'\0';
		INT8 len = 11;
		for (; i > 0; i /= 10)
		{
			_u16_t32String[--len] = (i % 10) + u'0';
		}
		if (i < 0)
		{
			_u16_t32String[--len] = u'-';
		}
		return &_u16_t32String[len];
	}
	const CHAR16* UTF16::ToString(const INT64 b)
	{
		if (b == 0)
		{
			_u16_t64String[0] = u'0';
			_u16_t64String[1] = u'\0';
			return &_u16_t64String[0];
		}

		INT64 i = b;
		_u16_t64String[21] = u'\0';
		INT8 len = 21;
		for (; i > 0; i /= 10)
		{
			_u16_t64String[--len] = (i % 10) + u'0';
		}
		if (i < 0)
		{
			_u16_t64String[--len] = u'-';
		}
		return &_u16_t64String[len];
	}

	const CHAR16* UTF16::ToHex(const INT8 b)
	{
		_u16_hex8String[1] = _u16_hexChars[(b >> 4) & 0x0F];
		_u16_hex8String[2] = _u16_hexChars[b & 0x0F];
		_u16_hex8String[3] = u'\0';

		if (b < 0)
		{
			_u16_hex8String[0] = u'-';
			return &_u16_hex8String[0];
		}
		else
		{
			return &_u16_hex8String[1];
		}

		return _u16_hex8String;
	}
	const CHAR16* UTF16::ToHex(const INT16 b)
	{
		_u16_hex16String[1] = _u16_hexChars[(b >> 12) & 0x0F];
		_u16_hex16String[2] = _u16_hexChars[(b >> 8) & 0x0F];
		_u16_hex16String[3] = _u16_hexChars[(b >> 4) & 0x0F];
		_u16_hex16String[4] = _u16_hexChars[b & 0x0F];
		_u16_hex16String[5] = u'\0';
		if (b < 0)
		{
			_u16_hex16String[0] = u'-';
			return &_u16_hex16String[0];
		}
		else
		{
			return &_u16_hex16String[1];
		}
	}
	const CHAR16* UTF16::ToHex(const INT32 b)
	{
		_u16_hex32String[1] = _u16_hexChars[(b >> 28) & 0x0F];
		_u16_hex32String[2] = _u16_hexChars[(b >> 24) & 0x0F];
		_u16_hex32String[3] = _u16_hexChars[(b >> 20) & 0x0F];
		_u16_hex32String[4] = _u16_hexChars[(b >> 16) & 0x0F];
		_u16_hex32String[5] = _u16_hexChars[(b >> 12) & 0x0F];
		_u16_hex32String[6] = _u16_hexChars[(b >> 8) & 0x0F];
		_u16_hex32String[7] = _u16_hexChars[(b >> 4) & 0x0F];
		_u16_hex32String[8] = _u16_hexChars[b & 0x0F];
		_u16_hex32String[9] = u'\0';
		if (b < 0)
		{
			_u16_hex32String[0] = u'-';
			return &_u16_hex32String[0];
		}
		else
		{
			return &_u16_hex32String[1];
		}
	}
	const CHAR16* UTF16::ToHex(const INT64 b)
	{
		_u16_hex64String[1] = _u16_hexChars[(b >> 60) & 0x0F];
		_u16_hex64String[2] = _u16_hexChars[(b >> 56) & 0x0F];
		_u16_hex64String[3] = _u16_hexChars[(b >> 52) & 0x0F];
		_u16_hex64String[4] = _u16_hexChars[(b >> 48) & 0x0F];
		_u16_hex64String[5] = _u16_hexChars[(b >> 44) & 0x0F];
		_u16_hex64String[6] = _u16_hexChars[(b >> 40) & 0x0F];
		_u16_hex64String[7] = _u16_hexChars[(b >> 36) & 0x0F];
		_u16_hex64String[8] = _u16_hexChars[(b >> 32) & 0x0F];
		_u16_hex64String[9] = _u16_hexChars[(b >> 28) & 0x0F];
		_u16_hex64String[10] = _u16_hexChars[(b >> 24) & 0x0F];
		_u16_hex64String[11] = _u16_hexChars[(b >> 20) & 0x0F];
		_u16_hex64String[12] = _u16_hexChars[(b >> 16) & 0x0F];
		_u16_hex64String[13] = _u16_hexChars[(b >> 12) & 0x0F];
		_u16_hex64String[14] = _u16_hexChars[(b >> 8) & 0x0F];
		_u16_hex64String[15] = _u16_hexChars[(b >> 4) & 0x0F];
		_u16_hex64String[16] = _u16_hexChars[b & 0x0F];
		_u16_hex64String[17] = u'\0';
		if (b < 0)
		{
			_u16_hex64String[0] = u'-';
			return &_u16_hex64String[0];
		}
		else
		{
			return &_u16_hex64String[1];
		}
	}

	const CHAR8* UTF8::ToString(const EFI::EFI_GUID guid)
	{
		_hexGUIDString[0] = '{';
		_hexGUIDString[1] = _hexChars[(guid.Data1 >> 28) & 0x0F];
		_hexGUIDString[2] = _hexChars[(guid.Data1 >> 24) & 0x0F];
		_hexGUIDString[3] = _hexChars[(guid.Data1 >> 20) & 0x0F];
		_hexGUIDString[4] = _hexChars[(guid.Data1 >> 16) & 0x0F];
		_hexGUIDString[5] = _hexChars[(guid.Data1 >> 12) & 0x0F];
		_hexGUIDString[6] = _hexChars[(guid.Data1 >> 8) & 0x0F];
		_hexGUIDString[7] = _hexChars[(guid.Data1 >> 4) & 0x0F];
		_hexGUIDString[8] = _hexChars[guid.Data1 & 0x0F];
		_hexGUIDString[9] = '-';
		_hexGUIDString[10] = _hexChars[(guid.Data2 >> 12) & 0x0F];
		_hexGUIDString[11] = _hexChars[(guid.Data2 >> 8) & 0x0F];
		_hexGUIDString[12] = _hexChars[(guid.Data2 >> 4) & 0x0F];
		_hexGUIDString[13] = _hexChars[guid.Data2 & 0x0F];
		_hexGUIDString[14] = '-';
		_hexGUIDString[15] = _hexChars[(guid.Data3 >> 12) & 0x0F];
		_hexGUIDString[16] = _hexChars[(guid.Data3 >> 8) & 0x0F];
		_hexGUIDString[17] = _hexChars[(guid.Data3 >> 4) & 0x0F];
		_hexGUIDString[18] = _hexChars[guid.Data3 & 0x0F];
		_hexGUIDString[19] = '-';
		_hexGUIDString[20] = _hexChars[(guid.Data4[0] >> 4) & 0x0F];
		_hexGUIDString[21] = _hexChars[guid.Data4[0] & 0x0F];
		_hexGUIDString[22] = _hexChars[(guid.Data4[1] >> 4) & 0x0F];
		_hexGUIDString[23] = _hexChars[guid.Data4[1] & 0x0F];
		_hexGUIDString[24] = '-';
		_hexGUIDString[25] = _hexChars[(guid.Data4[2] >> 4) & 0x0F];
		_hexGUIDString[26] = _hexChars[guid.Data4[2] & 0x0F];
		_hexGUIDString[27] = _hexChars[(guid.Data4[3] >> 4) & 0x0F];
		_hexGUIDString[28] = _hexChars[guid.Data4[3] & 0x0F];
		_hexGUIDString[29] = _hexChars[(guid.Data4[4] >> 4) & 0x0F];
		_hexGUIDString[30] = _hexChars[guid.Data4[4] & 0x0F];
		_hexGUIDString[31] = _hexChars[(guid.Data4[5] >> 4) & 0x0F];
		_hexGUIDString[32] = _hexChars[guid.Data4[5] & 0x0F];
		_hexGUIDString[33] = _hexChars[(guid.Data4[6] >> 4) & 0x0F];
		_hexGUIDString[34] = _hexChars[guid.Data4[6] & 0x0F];
		_hexGUIDString[35] = _hexChars[(guid.Data4[7] >> 4) & 0x0F];
		_hexGUIDString[36] = _hexChars[guid.Data4[7] & 0x0F];
		_hexGUIDString[37] = '}';
		_hexGUIDString[38] = '\0';
		return _hexGUIDString;
	}

	const CHAR8* UTF8::ToString(EFI::EFI_STATUS status)
	{
		switch (status)
		{
		case EFI::EFI_STATUS::SUCCESS:
			return _SUCCESS;
		case EFI::EFI_STATUS::LOAD_ERROR:
			return _LOAD_ERROR;
		case EFI::EFI_STATUS::INVALID_PARAMETER:
			return _INVALID_PARAMETER;
		case EFI::EFI_STATUS::UNSUPPORTED:
			return _UNSUPPORTED;
		case EFI::EFI_STATUS::BAD_BUFFER_SIZE:
			return _BAD_BUFFER_SIZE;
		case EFI::EFI_STATUS::BUFFER_TOO_SMALL:
			return _BUFFER_TOO_SMALL;
		case EFI::EFI_STATUS::NOT_READY:
			return _NOT_READY;
		case EFI::EFI_STATUS::DEVICE_ERROR:
			return _DEVICE_ERROR;
		case EFI::EFI_STATUS::WRITE_PROTECTED:
			return _WRITE_PROTECTED;
		case EFI::EFI_STATUS::OUT_OF_RESOURCES:
			return _OUT_OF_RESOURCES;
		case EFI::EFI_STATUS::VOLUME_CORRUPTED:
			return _VOLUME_CORRUPTED;
		case EFI::EFI_STATUS::VOLUME_FULL:
			return _VOLUME_FULL;
		case EFI::EFI_STATUS::NO_MEDIA:
			return _NO_MEDIA;
		case EFI::EFI_STATUS::MEDIA_CHANGED:
			return _MEDIA_CHANGED;
		case EFI::EFI_STATUS::NOT_FOUND:
			return _NOT_FOUND;
		case EFI::EFI_STATUS::ACCESS_DENIED:
			return _ACCESS_DENIED;
		case EFI::EFI_STATUS::NO_RESPONSE:
			return _NO_RESPONSE;
		case EFI::EFI_STATUS::NO_MAPPING:
			return _NO_MAPPING;
		case EFI::EFI_STATUS::TIMEOUT:
			return _TIMEOUT;
		case EFI::EFI_STATUS::NOT_STARTED:
			return _NOT_STARTED;
		case EFI::EFI_STATUS::ALREADY_STARTED:
			return _ALREADY_STARTED;
		case EFI::EFI_STATUS::ABORTED:
			return _ABORTED;
		case EFI::EFI_STATUS::ICMP_ERROR:
			return _ICMP_ERROR;
		case EFI::EFI_STATUS::TFTP_ERROR:
			return _TFTP_ERROR;
		case EFI::EFI_STATUS::PROTOCOL_ERROR:
			return _PROTOCOL_ERROR;
		case EFI::EFI_STATUS::INCOMPATIBLE_VERSION:
			return _INCOMPATIBLE_VERSION;
		case EFI::EFI_STATUS::SECURITY_VIOLATION:
			return _SECURITY_VIOLATION;
		case EFI::EFI_STATUS::CRC_ERROR:
			return _CRC_ERROR;
		case EFI::EFI_STATUS::END_OF_MEDIA:
			return _END_OF_MEDIA;
		case EFI::EFI_STATUS::END_OF_FILE:
			return _END_OF_FILE;
		case EFI::EFI_STATUS::INVALID_LANGUAGE:
			return _INVALID_LANGUAGE;
		case EFI::EFI_STATUS::COMPROMISED_DATA:
			return _COMPROMISED_DATA;
		case EFI::EFI_STATUS::IP_ADDRESS_CONFLICT:
			return _IP_ADDRESS_CONFLICT;
		case EFI::EFI_STATUS::HTTP_ERROR:
			return _HTTP_ERROR;

		case EFI::EFI_STATUS::WARN_UNKNOWN_GLYPH:
			return _WARN_UNKNOWN_GLYPH;
		case EFI::EFI_STATUS::WARN_DELETE_FAILURE:
			return _WARN_DELETE_FAILURE;
		case EFI::EFI_STATUS::WARN_WRITE_FAILURE:
			return _WARN_WRITE_FAILURE;
		case EFI::EFI_STATUS::WARN_BUFFER_TOO_SMALL:
			return _WARN_BUFFER_TOO_SMALL;
		case EFI::EFI_STATUS::WARN_STALE_DATA:
			return _WARN_STALE_DATA;
		case EFI::EFI_STATUS::WARN_FILE_SYSTEM:
			return _WARN_FILE_SYSTEM;
		case EFI::EFI_STATUS::WARN_RESET_REQUIRED:
			return _WARN_RESET_REQUIRED;
		default: return nullptr;
		};
	};

	const CHAR8* UTF8::ToString(const UINT8 b)
	{
		if (b == 0)
		{
			_tu8String[0] = '0';
			_tu8String[1] = '\0';
			return &_tu8String[0];
		}

		UINT8 i = b;
		_tu8String[3] = '\0';
		UINT8 len = 3;
		for (; i > 0; i /= 10)
		{
			_tu8String[--len] = (i % 10) + '0';
		}
		return &_tu8String[len];
	}
	const CHAR8* UTF8::ToString(const UINT16 b)
	{
		if (b == 0)
		{
			_tu16String[0] = '0';
			_tu16String[1] = '\0';
			return &_tu16String[0];
		}

		UINT16 i = b;
		_tu16String[5] = '\0';
		UINT8 len = 5;
		for (; i > 0; i /= 10)
		{
			_tu16String[--len] = (i % 10) + '0';
		}

		return &_tu16String[len];
	}
	const CHAR8* UTF8::ToString(const UINT32 b)
	{
		if (b == 0)
		{
			_tu32String[0] = '0';
			_tu32String[1] = '\0';
			return &_tu32String[0];
		}

		UINT32 i = b;
		_tu32String[10] = '\0';
		UINT8 len = 10;
		for (; i > 0; i /= 10)
		{
			_tu32String[--len] = (i % 10) + '0';
		}

		return &_tu32String[len];
	}
	const CHAR8* UTF8::ToString(const UINT64 b)
	{
		if (b == 0)
		{
			_tu64String[0] = '0';
			_tu64String[1] = '\0';
			return &_tu64String[0];
		}

		UINT64 i = b;
		_tu64String[20] = '\0';
		UINT8 len = 20;
		for (; i > 0; i /= 10)
		{
			_tu64String[--len] = (i % 10) + '0';
		}

		return &_tu64String[len];
	}

	const CHAR8* UTF8::ToHex(const UINT8 b)
	{
		_hexu8String[0] = _hexChars[(b >> 4) & 0x0F];
		_hexu8String[1] = _hexChars[b & 0x0F];
		_hexu8String[2] = '\0';
		return &_hexu8String[0];
	}
	const CHAR8* UTF8::ToHex(const UINT16 b)
	{
		_hexu16String[0] = _hexChars[(b >> 12) & 0x0F];
		_hexu16String[1] = _hexChars[(b >> 8) & 0x0F];
		_hexu16String[2] = _hexChars[(b >> 4) & 0x0F];
		_hexu16String[3] = _hexChars[b & 0x0F];
		_hexu16String[4] = '\0';
		return &_hexu16String[0];
	}
	const CHAR8* UTF8::ToHex(const UINT32 b)
	{
		_hexu32String[0] = _hexChars[(b >> 28) & 0x0F];
		_hexu32String[1] = _hexChars[(b >> 24) & 0x0F];
		_hexu32String[2] = _hexChars[(b >> 20) & 0x0F];
		_hexu32String[3] = _hexChars[(b >> 16) & 0x0F];
		_hexu32String[4] = _hexChars[(b >> 12) & 0x0F];
		_hexu32String[5] = _hexChars[(b >> 8) & 0x0F];
		_hexu32String[6] = _hexChars[(b >> 4) & 0x0F];
		_hexu32String[7] = _hexChars[b & 0x0F];
		_hexu32String[8] = '\0';
		return &_hexu32String[0];
	}
	const CHAR8* UTF8::ToHex(const UINT64 b)
	{
		_hexu64String[0] = _hexChars[(b >> 60) & 0x0F];
		_hexu64String[1] = _hexChars[(b >> 56) & 0x0F];
		_hexu64String[2] = _hexChars[(b >> 52) & 0x0F];
		_hexu64String[3] = _hexChars[(b >> 48) & 0x0F];
		_hexu64String[4] = _hexChars[(b >> 44) & 0x0F];
		_hexu64String[5] = _hexChars[(b >> 40) & 0x0F];
		_hexu64String[6] = _hexChars[(b >> 36) & 0x0F];
		_hexu64String[7] = _hexChars[(b >> 32) & 0x0F];
		_hexu64String[8] = _hexChars[(b >> 28) & 0x0F];
		_hexu64String[9] = _hexChars[(b >> 24) & 0x0F];
		_hexu64String[10] = _hexChars[(b >> 20) & 0x0F];
		_hexu64String[11] = _hexChars[(b >> 16) & 0x0F];
		_hexu64String[12] = _hexChars[(b >> 12) & 0x0F];
		_hexu64String[13] = _hexChars[(b >> 8) & 0x0F];
		_hexu64String[14] = _hexChars[(b >> 4) & 0x0F];
		_hexu64String[15] = _hexChars[b & 0x0F];
		_hexu64String[16] = '\0';
		return &_hexu64String[0];
	}

	const CHAR8* UTF8::ToString(const INT8 b)
	{
		if (b == 0)
		{
			_t8String[0] = '0';
			_t8String[1] = '\0';
			return &_t8String[0];
		}

		INT8 i = b;
		_t8String[4] = '\0';
		INT8 len = 4;
		for (; i > 0; i /= 10)
		{
			_t8String[--len] = (i % 10) + '0';
		}
		if (i < 0)
		{
			_t8String[--len] = '-';
		}
		return &_t8String[len];
	}
	const CHAR8* UTF8::ToString(const INT16 b)
	{
		if (b == 0)
		{
			_t16String[0] = '0';
			_t16String[1] = '\0';
			return &_t16String[0];
		}

		INT16 i = b;
		_t16String[6] = '\0';
		INT8 len = 6;
		for (; i > 0; i /= 10)
		{
			_t16String[--len] = (i % 10) + '0';
		}
		if (i < 0)
		{
			_t16String[--len] = '-';
		}
		return &_t16String[len];
	}
	const CHAR8* UTF8::ToString(const INT32 b)
	{
		if (b == 0)
		{
			_t32String[0] = '0';
			_t32String[1] = '\0';
			return &_t32String[0];
		}

		INT32 i = b;
		_t32String[11] = '\0';
		INT8 len = 11;
		for (; i > 0; i /= 10)
		{
			_t32String[--len] = (i % 10) + '0';
		}
		if (i < 0)
		{
			_t32String[--len] = '-';
		}
		return &_t32String[len];
	}
	const CHAR8* UTF8::ToString(const INT64 b)
	{
		if (b == 0)
		{
			_t64String[0] = '0';
			_t64String[1] = '\0';
			return &_t64String[0];
		}

		INT64 i = b;
		_t64String[21] = '\0';
		INT8 len = 21;
		for (; i > 0; i /= 10)
		{
			_t64String[--len] = (i % 10) + '0';
		}
		if (i < 0)
		{
			_t64String[--len] = '-';
		}
		return &_t64String[len];
	}

	const CHAR8* UTF8::ToHex(const INT8 b)
	{
		_hex8String[1] = _hexChars[(b >> 4) & 0x0F];
		_hex8String[2] = _hexChars[b & 0x0F];
		_hex8String[3] = '\0';

		if (b < 0)
		{
			_hex8String[0] = '-';
			return &_hex8String[0];
		}
		else
		{
			return &_hex8String[1];
		}

		return _hex8String;
	}
	const CHAR8* UTF8::ToHex(const INT16 b)
	{
		_hex16String[1] = _hexChars[(b >> 12) & 0x0F];
		_hex16String[2] = _hexChars[(b >> 8) & 0x0F];
		_hex16String[3] = _hexChars[(b >> 4) & 0x0F];
		_hex16String[4] = _hexChars[b & 0x0F];
		_hex16String[5] = '\0';
		if (b < 0)
		{
			_hex16String[0] = '-';
			return &_hex16String[0];
		}
		else
		{
			return &_hex16String[1];
		}
	}
	const CHAR8* UTF8::ToHex(const INT32 b)
	{
		_hex32String[1] = _hexChars[(b >> 28) & 0x0F];
		_hex32String[2] = _hexChars[(b >> 24) & 0x0F];
		_hex32String[3] = _hexChars[(b >> 20) & 0x0F];
		_hex32String[4] = _hexChars[(b >> 16) & 0x0F];
		_hex32String[5] = _hexChars[(b >> 12) & 0x0F];
		_hex32String[6] = _hexChars[(b >> 8) & 0x0F];
		_hex32String[7] = _hexChars[(b >> 4) & 0x0F];
		_hex32String[8] = _hexChars[b & 0x0F];
		_hex32String[9] = '\0';
		if (b < 0)
		{
			_hex32String[0] = '-';
			return &_hex32String[0];
		}
		else
		{
			return &_hex32String[1];
		}
	}
	const CHAR8* UTF8::ToHex(const INT64 b)
	{
		_hex64String[1] = _hexChars[(b >> 60) & 0x0F];
		_hex64String[2] = _hexChars[(b >> 56) & 0x0F];
		_hex64String[3] = _hexChars[(b >> 52) & 0x0F];
		_hex64String[4] = _hexChars[(b >> 48) & 0x0F];
		_hex64String[5] = _hexChars[(b >> 44) & 0x0F];
		_hex64String[6] = _hexChars[(b >> 40) & 0x0F];
		_hex64String[7] = _hexChars[(b >> 36) & 0x0F];
		_hex64String[8] = _hexChars[(b >> 32) & 0x0F];
		_hex64String[9] = _hexChars[(b >> 28) & 0x0F];
		_hex64String[10] = _hexChars[(b >> 24) & 0x0F];
		_hex64String[11] = _hexChars[(b >> 20) & 0x0F];
		_hex64String[12] = _hexChars[(b >> 16) & 0x0F];
		_hex64String[13] = _hexChars[(b >> 12) & 0x0F];
		_hex64String[14] = _hexChars[(b >> 8) & 0x0F];
		_hex64String[15] = _hexChars[(b >> 4) & 0x0F];
		_hex64String[16] = _hexChars[b & 0x0F];
		_hex64String[17] = '\0';
		if (b < 0)
		{
			_hex64String[0] = '-';
			return &_hex64String[0];
		}
		else
		{
			return &_hex64String[1];
		}
	}
}