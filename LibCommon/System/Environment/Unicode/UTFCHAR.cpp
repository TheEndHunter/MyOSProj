#pragma once
#include <System/Environment/Unicode/UTFCHAR.h>


namespace Common::System::Environment
{

	const CHAR UTF<CHAR>::NewLine[3]{ '\r', '\n','\0' };
	CHAR _CSTR_GUIDTOSTRING[43] = { '{','\0','\0','\0','\0','\0','\0','\0','\0','-','\0','\0','\0','\0','-','\0','\0','\0','\0','-','\0','\0','\0','\0','-','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','}','\0' };
	CHAR _CSTR_HEXCHARS[17] = { '0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F' };
	CHAR _CSTR_HEXSTRING[18] = { '\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0' };
	CHAR _CSTR_VALUETOSTRING[23] = { '\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0' };
	CHAR _CSTR_WHITESPACECHARS[6] = { 0x09,0x0A,0x0B,0x0C,0x0D,0x20 };

	constinit const CHAR* _CSTR_ABORTED = "ABORTED";
	constinit const CHAR* _CSTR_ACCESS_DENIED = "ACCESS_DENIED";
	constinit const CHAR* _CSTR_ALREADY_STARTED = "ALREADY_STARTED";
	constinit const CHAR* _CSTR_BAD_BUFFER_SIZE = "BAD_BUFFER_SIZE";
	constinit const CHAR* _CSTR_BOOLEAN_FALSE = "False";
	constinit const CHAR* _CSTR_BOOLEAN_TRUE = "True";
	constinit const CHAR* _CSTR_BUFFER_TOO_SMALL = "BUFFER_TOO_SMALL";
	constinit const CHAR* _CSTR_COMPROMISED_DATA = "COMPROMISED_DATA";
	constinit const CHAR* _CSTR_CRC_ERROR = "CRC_ERROR";
	constinit const CHAR* _CSTR_DEVICE_ERROR = "DEVICE_ERROR";
	constinit const CHAR* _CSTR_END_OF_FILE = "END_OF_FILE";
	constinit const CHAR* _CSTR_END_OF_MEDIA = "END_OF_MEDIA";
	constinit const CHAR* _CSTR_HTTP_ERROR = "HTTP_ERROR";
	constinit const CHAR* _CSTR_ICMP_ERROR = "ICMP_ERROR";
	constinit const CHAR* _CSTR_INCOMPATIBLE_VERSION = "INCOMPATIBLE_VERSION";
	constinit const CHAR* _CSTR_INVALID_LANGUAGE = "INVALID_LANGUAGE";
	constinit const CHAR* _CSTR_INVALID_PARAMETER = "INVALID_PARAMETER";
	constinit const CHAR* _CSTR_IP_ADDRESS_CONFLICT = "IP_ADDRESS_CONFLICT";
	constinit const CHAR* _CSTR_LOAD_ERROR = "LOAD_ERROR";
	constinit const CHAR* _CSTR_MEDIA_CHANGED = "MEDIA_CHANGED";
	constinit const CHAR* _CSTR_NO_MAPPING = "NO_MAPPING";
	constinit const CHAR* _CSTR_NO_MEDIA = "NO_MEDIA";
	constinit const CHAR* _CSTR_NO_RESPONSE = "NO_RESPONSE";
	constinit const CHAR* _CSTR_NOT_FOUND = "NOT_FOUND";
	constinit const CHAR* _CSTR_NOT_READY = "NOT_READY";
	constinit const CHAR* _CSTR_NOT_STARTED = "NOT_STARTED";
	constinit const CHAR* _CSTR_OUT_OF_RESOURCES = "OUT_OF_RESOURCES";
	constinit const CHAR* _CSTR_PROTOCOL_ERROR = "PROTOCOL_ERROR";
	constinit const CHAR* _CSTR_SECURITY_VIOLATION = "SECURITY_VIOLATION";
	constinit const CHAR* _CSTR_SUCCESS = "SUCCESS";
	constinit const CHAR* _CSTR_TFTP_ERROR = "TFTP_ERROR";
	constinit const CHAR* _CSTR_TIMEOUT = "TIMEOUT";
	constinit const CHAR* _CSTR_UNSUPPORTED = "UNSUPPORTED";
	constinit const CHAR* _CSTR_VOLUME_CORRUPTED = "VOLUME_CORRUPTED";
	constinit const CHAR* _CSTR_VOLUME_FULL = "VOLUME_FULL";
	constinit const CHAR* _CSTR_WARN_BUFFER_TOO_SMALL = "WARN_BUFFER_TOO_SMALL";
	constinit const CHAR* _CSTR_WARN_DELETE_FAILURE = "WARN_DELETE_FAILURE";
	constinit const CHAR* _CSTR_WARN_FILE_SYSTEM = "WARN_FILE_SYSTEM";
	constinit const CHAR* _CSTR_WARN_RESET_REQUIRED = "WARN_RESET_REQUIRED";
	constinit const CHAR* _CSTR_WARN_STALE_DATA = "WARN_STALE_DATA";
	constinit const CHAR* _CSTR_WARN_UNKNOWN_GLYPH = "WARN_UNKNOWN_GLYPH";
	constinit const CHAR* _CSTR_WARN_WRITE_FAILURE = "WARN_WRITE_FAILURE";
	constinit const CHAR* _CSTR_WRITE_PROTECTED = "WRITE_PROTECTED";

	constinit const CHAR* _CSTR_ALLOC_STATUS_SUCCESS = "SUCCESS";
	constinit const CHAR* _CSTR_ALLOC_STATUS_INVALID_PARAMETER = "INVALID_PARAMETER";
	constinit const CHAR* _CSTR_ALLOC_STATUS_NOT_ENOUGH_MEMORY = "NOT_ENOUGH_MEMORY";
	constinit const CHAR* _CSTR_ALLOC_STATUS_NOT_ENOUGH_PAGES = "NOT_ENOUGH_PAGES";
	constinit const CHAR* _CSTR_ALLOC_STATUS_ACCESS_DENIED = "ACCESS_DENIED";
	constinit const CHAR* _CSTR_ALLOC_STATUS_UNKNOWN = "UNKNOWN";

	CHAR* UTF<CHAR>::ToHex(const INT16 value)
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

	CHAR* UTF<CHAR>::ToHex(const INT32 value)
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

	CHAR* UTF<CHAR>::ToHex(const INT64 value)
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

	CHAR* UTF<CHAR>::ToHex(const INT8 value)
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

	CHAR* UTF<CHAR>::ToHex(const UINT16 value)
	{
		_CSTR_HEXSTRING[0] = _CSTR_HEXCHARS[(value >> 12) & 0xF];
		_CSTR_HEXSTRING[1] = _CSTR_HEXCHARS[(value >> 8) & 0xF];
		_CSTR_HEXSTRING[2] = _CSTR_HEXCHARS[(value >> 4) & 0xF];
		_CSTR_HEXSTRING[3] = _CSTR_HEXCHARS[value & 0xF];
		_CSTR_HEXSTRING[4] = '\0';
		return &_CSTR_HEXSTRING[0];
	}

	CHAR* UTF<CHAR>::ToHex(const UINT32 value)
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

	CHAR* UTF<CHAR>::ToHex(const UINT64 value)
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

	CHAR* UTF<CHAR>::ToHex(const UINT8 value)
	{
		_CSTR_HEXSTRING[0] = _CSTR_HEXCHARS[(value >> 4) & 0xF];
		_CSTR_HEXSTRING[1] = _CSTR_HEXCHARS[value & 0xF];
		_CSTR_HEXSTRING[2] = '\0';
		return &_CSTR_HEXSTRING[0];
	}

	CHAR* UTF<CHAR>::ToHex(const VOID_PTR ptr)
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

	CHAR* UTF<CHAR>::ToString(const EFI::EFI_GUID guid)
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

	CHAR* UTF<CHAR>::ToString(const EFI::EFI_STATUS status)
	{
		switch (status)
		{
		case EFI::EFI_STATUS::ABORTED:
			return (CHAR*)_CSTR_ABORTED;
		case EFI::EFI_STATUS::ACCESS_DENIED:
			return (CHAR*)_CSTR_ACCESS_DENIED;
		case EFI::EFI_STATUS::ALREADY_STARTED:
			return (CHAR*)_CSTR_ALREADY_STARTED;
		case EFI::EFI_STATUS::BAD_BUFFER_SIZE:
			return (CHAR*)_CSTR_BAD_BUFFER_SIZE;
		case EFI::EFI_STATUS::BUFFER_TOO_SMALL:
			return (CHAR*)_CSTR_BUFFER_TOO_SMALL;
		case EFI::EFI_STATUS::COMPROMISED_DATA:
			return (CHAR*)_CSTR_COMPROMISED_DATA;
		case EFI::EFI_STATUS::CRC_ERROR:
			return (CHAR*)_CSTR_CRC_ERROR;
		case EFI::EFI_STATUS::DEVICE_ERROR:
			return (CHAR*)_CSTR_DEVICE_ERROR;
		case EFI::EFI_STATUS::END_OF_FILE:
			return (CHAR*)_CSTR_END_OF_FILE;
		case EFI::EFI_STATUS::END_OF_MEDIA:
			return (CHAR*)_CSTR_END_OF_MEDIA;
		case EFI::EFI_STATUS::HTTP_ERROR:
			return (CHAR*)_CSTR_HTTP_ERROR;
		case EFI::EFI_STATUS::ICMP_ERROR:
			return (CHAR*)_CSTR_ICMP_ERROR;
		case EFI::EFI_STATUS::INCOMPATIBLE_VERSION:
			return (CHAR*)_CSTR_INCOMPATIBLE_VERSION;
		case EFI::EFI_STATUS::INVALID_LANGUAGE:
			return (CHAR*)_CSTR_INVALID_LANGUAGE;
		case EFI::EFI_STATUS::INVALID_PARAMETER:
			return (CHAR*)_CSTR_INVALID_PARAMETER;
		case EFI::EFI_STATUS::IP_ADDRESS_CONFLICT:
			return (CHAR*)_CSTR_IP_ADDRESS_CONFLICT;
		case EFI::EFI_STATUS::LOAD_ERROR:
			return (CHAR*)_CSTR_LOAD_ERROR;
		case EFI::EFI_STATUS::MEDIA_CHANGED:
			return (CHAR*)_CSTR_MEDIA_CHANGED;
		case EFI::EFI_STATUS::NO_MAPPING:
			return (CHAR*)_CSTR_NO_MAPPING;
		case EFI::EFI_STATUS::NO_MEDIA:
			return (CHAR*)_CSTR_NO_MEDIA;
		case EFI::EFI_STATUS::NO_RESPONSE:
			return (CHAR*)_CSTR_NO_RESPONSE;
		case EFI::EFI_STATUS::NOT_FOUND:
			return (CHAR*)_CSTR_NOT_FOUND;
		case EFI::EFI_STATUS::NOT_READY:
			return (CHAR*)_CSTR_NOT_READY;
		case EFI::EFI_STATUS::NOT_STARTED:
			return (CHAR*)_CSTR_NOT_STARTED;
		case EFI::EFI_STATUS::OUT_OF_RESOURCES:
			return (CHAR*)_CSTR_OUT_OF_RESOURCES;
		case EFI::EFI_STATUS::PROTOCOL_ERROR:
			return (CHAR*)_CSTR_PROTOCOL_ERROR;
		case EFI::EFI_STATUS::SECURITY_VIOLATION:
			return (CHAR*)_CSTR_SECURITY_VIOLATION;
		case EFI::EFI_STATUS::SUCCESS:
			return (CHAR*)_CSTR_SUCCESS;
		case EFI::EFI_STATUS::TFTP_ERROR:
			return (CHAR*)_CSTR_TFTP_ERROR;
		case EFI::EFI_STATUS::TIMEOUT:
			return (CHAR*)_CSTR_TIMEOUT;
		case EFI::EFI_STATUS::UNSUPPORTED:
			return (CHAR*)_CSTR_UNSUPPORTED;
		case EFI::EFI_STATUS::VOLUME_CORRUPTED:
			return (CHAR*)_CSTR_VOLUME_CORRUPTED;
		case EFI::EFI_STATUS::VOLUME_FULL:
			return (CHAR*)_CSTR_VOLUME_FULL;
		case EFI::EFI_STATUS::WARN_BUFFER_TOO_SMALL:
			return (CHAR*)_CSTR_WARN_BUFFER_TOO_SMALL;
		case EFI::EFI_STATUS::WARN_DELETE_FAILURE:
			return (CHAR*)_CSTR_WARN_DELETE_FAILURE;
		case EFI::EFI_STATUS::WARN_FILE_SYSTEM:
			return (CHAR*)_CSTR_WARN_FILE_SYSTEM;
		case EFI::EFI_STATUS::WARN_RESET_REQUIRED:
			return (CHAR*)_CSTR_WARN_RESET_REQUIRED;
		case EFI::EFI_STATUS::WARN_STALE_DATA:
			return (CHAR*)_CSTR_WARN_STALE_DATA;
		case EFI::EFI_STATUS::WARN_UNKNOWN_GLYPH:
			return (CHAR*)_CSTR_WARN_UNKNOWN_GLYPH;
		case EFI::EFI_STATUS::WARN_WRITE_FAILURE:
			return (CHAR*)_CSTR_WARN_WRITE_FAILURE;
		case EFI::EFI_STATUS::WRITE_PROTECTED:
			return (CHAR*)_CSTR_WRITE_PROTECTED;
		default:
			return nullptr;
		}
	}

	CHAR* UTF<CHAR>::ToString(const Common::System::MemoryManagement::AllocatorStatus status)
	{
		switch (status)
		{
		case Common::System::MemoryManagement::AllocatorStatus::Success:
			return (CHAR*)_CSTR_ALLOC_STATUS_SUCCESS;
		case Common::System::MemoryManagement::AllocatorStatus::Invalid_Parameters:
			return (CHAR*)_CSTR_ALLOC_STATUS_INVALID_PARAMETER;
		case Common::System::MemoryManagement::AllocatorStatus::Not_Enough_Memory:
			return (CHAR*)_CSTR_ALLOC_STATUS_NOT_ENOUGH_MEMORY;
		case Common::System::MemoryManagement::AllocatorStatus::Not_Enough_Pages:
			return (CHAR*)_CSTR_ALLOC_STATUS_NOT_ENOUGH_PAGES;
		case Common::System::MemoryManagement::AllocatorStatus::Access_Denied:
			return (CHAR*)_CSTR_ALLOC_STATUS_ACCESS_DENIED;
		}
	}

	CHAR* UTF<CHAR>::ToString(const INT16 value)
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
		BOOLEAN isNegative = false;
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

	CHAR* UTF<CHAR>::ToString(const INT32 value)
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
		BOOLEAN isNegative = false;
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

	CHAR* UTF<CHAR>::ToString(const INT64 value)
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
		BOOLEAN isNegative = false;
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

	CHAR* UTF<CHAR>::ToString(const INT8 value)
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
		BOOLEAN isNegative = false;
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

	CHAR* UTF<CHAR>::ToString(const UINT16 value)
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

	CHAR* UTF<CHAR>::ToString(const UINT32 value)
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

	CHAR* UTF<CHAR>::ToString(const UINT64 value)
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

	CHAR* UTF<CHAR>::ToString(const UINT8 value)
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

	CHAR* UTF<CHAR>::ToString(const VOID_PTR ptr)
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

	CHAR* UTF<CHAR>::ToString(const BOOLEAN boolean)
	{
		if (boolean)
		{
			return (CHAR*)_CSTR_BOOLEAN_TRUE;
		}
		else
		{
			return (CHAR*)_CSTR_BOOLEAN_FALSE;
		}
	}

	UINT64 UTF<CHAR>::Length(const CHAR* str)
	{
		if (str == nullptr)
		{
			return 0;
		}

		if (str[0] == '\0')
		{
			return 1;
		}

		UINT64 index = 0;
		UINT64 len = 1;
		while (str[index] != '\0')
		{
			len++;
			index++;
		}
		return len;
	}

	BOOLEAN UTF<CHAR>::Compare(const CHAR* l, const CHAR* r, StringCulture culture)
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

		UINT64 lLength = Length(l);
		UINT64 rLength = Length(r);

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

	BOOLEAN UTF<CHAR>::StartsWith(const CHAR* str, const CHAR* value, StringCulture culture)
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

	BOOLEAN UTF<CHAR>::EndsWith(const CHAR* str, const CHAR* value, StringCulture culture)
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

	BOOLEAN UTF<CHAR>::Contains(const CHAR* str, const CHAR* value, StringCulture culture)
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
					for (UINT64 i = 0; i < valueLength; i++)
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

	BOOLEAN UTF<CHAR>::IsNullOrEmpty(const CHAR* str)
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

	BOOLEAN UTF<CHAR>::IsNullOrWhiteSpace(const CHAR* str)
	{
		if (str == nullptr)
		{
			return TRUE;
		};

		if (str[0] == '\0')
		{
			return TRUE;
		}

		UINT64 index = 0;
		while (str[index] != '\0')
		{
			UINT64 i = 0;
			for (UINT64 i = 0; i < 30; i++)
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
	CHAR* UTF<CHAR>::FromCharArray(CHAR arr[], UINT64 Length)
	{
		if (arr == nullptr)
		{
			return nullptr;
		}

		CHAR* result = new CHAR[Length + 1];

		for (UINT64 i = 0; i < Length; i++)
		{
			result[i] = arr[i];
		}
		result[Length] = '\0';

		return result;
	}
	CHAR* UTF<CHAR>::FromUTF16String(const CHAR16* str)
	{
		if (str == nullptr)
		{
			return nullptr;
		}

		if (str[0] == '\0')
		{
			return (CHAR*)"\0";
		}

		UINT64 len = UTF<CHAR16>::Length(str);
		CHAR* result = new CHAR[len];
		for (UINT64 i = 0; i < len; i++)
		{
			result[i] = (CHAR)(str[i] & 0x00FF);
		}
		return result;
	}
	CHAR* UTF<CHAR>::FromUTF8String(const CHAR8* str)
	{
		if (str == nullptr)
		{
			return nullptr;
		}

		if (str[0] == '\0')
		{
			return (CHAR*)"\0";
		}

		UINT64 len = UTF<CHAR8>::Length(str);
		CHAR* result = new CHAR[len];
		for (UINT64 i = 0; i < len; i++)
		{
			result[i] = str[i];
		}
		return result;
	}
}