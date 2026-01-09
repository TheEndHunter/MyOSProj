#pragma once
#include <System/Environment/Unicode/UTFCHAR.h>


namespace Common::System::Environment
{
	const CHAR UTF<CHAR>::NewLine[3]{ '\r', '\n','\0'};
	const CHAR UTF<CHAR>::NewLineChar[2]{ '\r', '\n'};

	CHAR _CSTR_GUIDTOSTRING[43] = { '{','\0','\0','\0','\0','\0','\0','\0','\0','-','\0','\0','\0','\0','-','\0','\0','\0','\0','-','\0','\0','\0','\0','-','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','}','\0' };
	constexpr const UINT64 _CSTR_GUIDTOSTRING_LEN = sizeof(_CSTR_GUIDTOSTRING) / sizeof(CHAR);

	CHAR _CSTR_HEXCHARS[17] = { '0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F' };
	constexpr const UINT64 _CSTR_HEXCHARS_LEN = sizeof(_CSTR_GUIDTOSTRING) / sizeof(CHAR);

	CHAR _CSTR_HEXSTRING[18] = { '\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0' };
	constexpr const UINT64 _CSTR_HEXSTRING_LEN = sizeof(_CSTR_GUIDTOSTRING) / sizeof(CHAR);

	CHAR _CSTR_VALUETOSTRING[23] = { '\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0' };
	constexpr const UINT64 _CSTR_VALUETOSTRING_LEN = sizeof(_CSTR_GUIDTOSTRING) / sizeof(CHAR);

	CHAR _CSTR_WHITESPACECHARS[6] = { 0x09,0x0A,0x0B,0x0C,0x0D,0x20 };
	constexpr const UINT64 _CSTR_WHITESPACECHARS_LEN = sizeof(_CSTR_GUIDTOSTRING) / sizeof(CHAR);

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

void UTF<CHAR>::FreeSplit(CHAR** arr, UINT64 count)
{
    if (arr == nullptr) return;
    for (UINT64 i = 0; i < count; ++i) if (arr[i] != nullptr) delete[] arr[i];
    delete[] arr;
}

void UTF<CHAR>::Free(CHAR* str)
{
    if (str != nullptr) delete[] str;
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

	const CHAR* UTF<CHAR>::ToString(const EFI::EFI_STATUS status)
	{
		switch (status)
		{
		case EFI::EFI_STATUS::ABORTED:
			return _CSTR_ABORTED;
		case EFI::EFI_STATUS::ACCESS_DENIED:
			return _CSTR_ACCESS_DENIED;
		case EFI::EFI_STATUS::ALREADY_STARTED:
			return _CSTR_ALREADY_STARTED;
		case EFI::EFI_STATUS::BAD_BUFFER_SIZE:
			return _CSTR_BAD_BUFFER_SIZE;
		case EFI::EFI_STATUS::BUFFER_TOO_SMALL:
			return _CSTR_BUFFER_TOO_SMALL;
		case EFI::EFI_STATUS::COMPROMISED_DATA:
			return _CSTR_COMPROMISED_DATA;
		case EFI::EFI_STATUS::CRC_ERROR:
			return _CSTR_CRC_ERROR;
		case EFI::EFI_STATUS::DEVICE_ERROR:
			return _CSTR_DEVICE_ERROR;
		case EFI::EFI_STATUS::END_OF_FILE:
			return _CSTR_END_OF_FILE;
		case EFI::EFI_STATUS::END_OF_MEDIA:
			return _CSTR_END_OF_MEDIA;
		case EFI::EFI_STATUS::HTTP_ERROR:
			return _CSTR_HTTP_ERROR;
		case EFI::EFI_STATUS::ICMP_ERROR:
			return _CSTR_ICMP_ERROR;
		case EFI::EFI_STATUS::INCOMPATIBLE_VERSION:
			return _CSTR_INCOMPATIBLE_VERSION;
		case EFI::EFI_STATUS::INVALID_LANGUAGE:
			return _CSTR_INVALID_LANGUAGE;
		case EFI::EFI_STATUS::INVALID_PARAMETER:
			return _CSTR_INVALID_PARAMETER;
		case EFI::EFI_STATUS::IP_ADDRESS_CONFLICT:
			return _CSTR_IP_ADDRESS_CONFLICT;
		case EFI::EFI_STATUS::LOAD_ERROR:
			return _CSTR_LOAD_ERROR;
		case EFI::EFI_STATUS::MEDIA_CHANGED:
			return _CSTR_MEDIA_CHANGED;
		case EFI::EFI_STATUS::NO_MAPPING:
			return _CSTR_NO_MAPPING;
		case EFI::EFI_STATUS::NO_MEDIA:
			return _CSTR_NO_MEDIA;
		case EFI::EFI_STATUS::NO_RESPONSE:
			return _CSTR_NO_RESPONSE;
		case EFI::EFI_STATUS::NOT_FOUND:
			return _CSTR_NOT_FOUND;
		case EFI::EFI_STATUS::NOT_READY:
			return _CSTR_NOT_READY;
		case EFI::EFI_STATUS::NOT_STARTED:
			return _CSTR_NOT_STARTED;
		case EFI::EFI_STATUS::OUT_OF_RESOURCES:
			return _CSTR_OUT_OF_RESOURCES;
		case EFI::EFI_STATUS::PROTOCOL_ERROR:
			return _CSTR_PROTOCOL_ERROR;
		case EFI::EFI_STATUS::SECURITY_VIOLATION:
			return _CSTR_SECURITY_VIOLATION;
		case EFI::EFI_STATUS::SUCCESS:
			return _CSTR_SUCCESS;
		case EFI::EFI_STATUS::TFTP_ERROR:
			return _CSTR_TFTP_ERROR;
		case EFI::EFI_STATUS::TIMEOUT:
			return _CSTR_TIMEOUT;
		case EFI::EFI_STATUS::UNSUPPORTED:
			return _CSTR_UNSUPPORTED;
		case EFI::EFI_STATUS::VOLUME_CORRUPTED:
			return _CSTR_VOLUME_CORRUPTED;
		case EFI::EFI_STATUS::VOLUME_FULL:
			return _CSTR_VOLUME_FULL;
		case EFI::EFI_STATUS::WARN_BUFFER_TOO_SMALL:
			return _CSTR_WARN_BUFFER_TOO_SMALL;
		case EFI::EFI_STATUS::WARN_DELETE_FAILURE:
			return _CSTR_WARN_DELETE_FAILURE;
		case EFI::EFI_STATUS::WARN_FILE_SYSTEM:
			return _CSTR_WARN_FILE_SYSTEM;
		case EFI::EFI_STATUS::WARN_RESET_REQUIRED:
			return _CSTR_WARN_RESET_REQUIRED;
		case EFI::EFI_STATUS::WARN_STALE_DATA:
			return _CSTR_WARN_STALE_DATA;
		case EFI::EFI_STATUS::WARN_UNKNOWN_GLYPH:
			return _CSTR_WARN_UNKNOWN_GLYPH;
		case EFI::EFI_STATUS::WARN_WRITE_FAILURE:
			return _CSTR_WARN_WRITE_FAILURE;
		case EFI::EFI_STATUS::WRITE_PROTECTED:
			return _CSTR_WRITE_PROTECTED;
        default:
            return _CSTR_ABORTED; // fallback string for unknown status
        }
        }
	const CHAR* UTF<CHAR>::ToString(const Common::System::MemoryManagement::AllocatorStatus status)
	{
		switch (status)
		{
		case Common::System::MemoryManagement::AllocatorStatus::Success:
			return _CSTR_ALLOC_STATUS_SUCCESS;
		case Common::System::MemoryManagement::AllocatorStatus::Invalid_Parameters:
			return _CSTR_ALLOC_STATUS_INVALID_PARAMETER;
		case Common::System::MemoryManagement::AllocatorStatus::Not_Enough_Memory:
			return _CSTR_ALLOC_STATUS_NOT_ENOUGH_MEMORY;
		case Common::System::MemoryManagement::AllocatorStatus::Not_Enough_Pages:
			return _CSTR_ALLOC_STATUS_NOT_ENOUGH_PAGES;
		case Common::System::MemoryManagement::AllocatorStatus::Access_Denied:
			return _CSTR_ALLOC_STATUS_ACCESS_DENIED;
		default:
			return _CSTR_ALLOC_STATUS_UNKNOWN;
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

	const CHAR* UTF<CHAR>::ToString(const BOOLEAN boolean)
	{
		if (boolean)
		{
			return _CSTR_BOOLEAN_TRUE;
		}
		else
		{
			return _CSTR_BOOLEAN_FALSE;
		}
	}

	UINT64 UTF<CHAR>::Length(const CHAR* str)
	{
		if (str == nullptr)
		{
			return 0;
		}

		UINT64 len = 0;
		while (str[len] != '\0')
		{
			len++;
		}
		return len;
	}

	Common::System::Optional<UINT64> UTF<CHAR>::IndexOf(const CHAR* str, const CHAR* value, UINT64 startIndex, StringCulture culture)
	{
		if (str == nullptr || value == nullptr)
		{
			return Common::System::Optional<UINT64>();
		}

		UINT64 strLength = Length(str);
		UINT64 valueLength = Length(value);

		if (startIndex >= strLength || valueLength == 0 || strLength < valueLength)
		{
			return Common::System::Optional<UINT64>();
		}

		for (UINT64 idx = startIndex; idx <= strLength - valueLength; ++idx)
		{
			BOOLEAN match = FALSE;
			for (UINT64 j = 0; j < valueLength; ++j)
			{
				if (str[idx + j] != value[j])
				{
					break;
				}

				match = TRUE;
			}
			if (match)
			{
				return Common::System::Optional<UINT64>(idx);
			}
		}
		return Common::System::Optional<UINT64>();
	}

	Common::System::Optional<UINT64> UTF<CHAR>::IndexOf(const CHAR* str, const CHAR value, UINT64 startIndex, StringCulture culture)
	{
		CHAR tmp[2] = { value, '\0' };
		return IndexOf(str, &tmp[0], startIndex, culture);
	}

	Common::System::Optional<UINT64> UTF<CHAR>::LastIndexOf(const CHAR* str, const CHAR* value, UINT64 startIndex, StringCulture culture)
	{
		if (str == nullptr || value == nullptr)
		{
			return Common::System::Optional<UINT64>();
		}

		UINT64 strLength = Length(str);
		UINT64 valueLength = Length(value);

		if (valueLength == 0 || strLength < valueLength)
		{
			return Common::System::Optional<UINT64>();
		}

		UINT64 start = (startIndex == 0 || startIndex > strLength - valueLength) ? (strLength - valueLength) : startIndex;
		for (INT64 idx = (INT64)start; idx >= 0; --idx)
		{
			BOOLEAN match = TRUE;
			for (UINT64 j = 0; j < valueLength; ++j)
			{
				if (str[idx + j] != value[j])
				{
					match = FALSE;
					break;
				}
			}
			if (match)
			{
				return Common::System::Optional<UINT64>((UINT64)idx);
			}
		}
		return Common::System::Optional<UINT64>();
	}

	BOOLEAN UTF<CHAR>::Compare(const CHAR* l, const CHAR* r, StringCulture culture)
	{		
		/*Check for isNullOrEmpty and Lengths, if they don't match, return FALSE*/

		Common::System::Optional<UINT64> lLenOpt = Length(l);
		Common::System::Optional<UINT64> rLenOpt = Length(r);
		UINT64 lLength = lLenOpt.HasValue() ? lLenOpt.GetValue() : 0;
		UINT64 rLength = rLenOpt.HasValue() ? rLenOpt.GetValue() : 0;

		if (lLength != rLength)
		{
			return FALSE;
		}
		
		BOOLEAN lBool = IsNullOrEmpty(l);
		BOOLEAN rBool = IsNullOrEmpty(r);
		
		if (lBool && rBool)
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
			CHAR lChar = l[index];
			CHAR rChar = r[index];
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

		// For StartsWith we only require valueLength <= strLength
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
		for (UINT64 index = 0; index <= strLength - valueLength; index++)
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
		for (UINT64 index = 0; index <= strLength - valueLength; index++)
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
					CHAR lChar2 = str[index + i];
					CHAR rChar2 = value[i];
						/*If the character is a lower case letter, switch it to upper for comparison*/
					if (lChar2 >= 'a' && lChar2 <= 'z')
					{
						lChar2 -= 32;
					}
					if (rChar2 >= 'a' && rChar2 <= 'z')
					{
						rChar2 -= 32;
					}

					if (lChar2 != rChar2)
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
		}

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
		}

		if (str[0] == '\0')
		{
			return TRUE;
		}

		UINT64 index = 0;
		while (str[index] != '\0')
		{
			BOOLEAN isWhite = FALSE;
			for (UINT64 i = 0; i < _CSTR_WHITESPACECHARS_LEN; i++)
			{
				if ((unsigned char)str[index] == (unsigned char)_CSTR_WHITESPACECHARS[i])
				{
					isWhite = TRUE;
					break;
				}
			}
			if (!isWhite)
			{
				return FALSE;
			}
			index++;
		}
		return TRUE;
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
		/* Encode UTF-16 to UTF-8 into CHAR* (bytes). Replaces invalid sequences with U+FFFD. */

		if (str == nullptr)
		{
			return nullptr;
		}

		UINT64 srcLen = UTF<CHAR16>::Length(str);

		// First pass: compute needed bytes
		UINT64 needed = 0;
		for (UINT64 i = 0; i < srcLen; ++i)
		{
			UINT16 w1 = (UINT16)str[i];
			if (w1 >= 0xD800 && w1 <= 0xDBFF)
			{
				if (i + 1 < srcLen)
				{
					UINT16 w2 = (UINT16)str[i + 1];
					if (w2 >= 0xDC00 && w2 <= 0xDFFF)
					{
						needed += 4;
						i++;
						continue;
					}
				}
				needed += 3; // replacement
			}
			else if (w1 >= 0xDC00 && w1 <= 0xDFFF)
			{
				needed += 3; // replacement
			}
			else if (w1 < 0x80)
			{
				needed += 1;
			}
			else if (w1 < 0x800)
			{
				needed += 2;
			}
			else
			{
				needed += 3;
			}
		}

		CHAR* result = new CHAR[needed + 1];
		UINT64 out = 0;

		for (UINT64 i = 0; i < srcLen; ++i)
		{
			UINT32 codepoint;
			UINT16 w1 = (UINT16)str[i];
			if (w1 >= 0xD800 && w1 <= 0xDBFF)
			{
				if (i + 1 < srcLen)
				{
					UINT16 w2 = (UINT16)str[i + 1];
					if (w2 >= 0xDC00 && w2 <= 0xDFFF)
					{
						codepoint = 0x10000 + (((UINT32)w1 - 0xD800) << 10) + ((UINT32)w2 - 0xDC00);
						i++;
					}
					else
					{
						codepoint = 0xFFFD;
					}
				}
				else
				{
					codepoint = 0xFFFD;
				}
			}
			else if (w1 >= 0xDC00 && w1 <= 0xDFFF)
			{
				codepoint = 0xFFFD;
			}
			else
			{
				codepoint = w1;
			}

			if (codepoint <= 0x7F)
			{
				result[out++] = (CHAR)(unsigned char)codepoint;
			}
			else if (codepoint <= 0x7FF)
			{
				result[out++] = (CHAR)(unsigned char)(0xC0 | ((codepoint >> 6) & 0x1F));
				result[out++] = (CHAR)(unsigned char)(0x80 | (codepoint & 0x3F));
			}
			else if (codepoint <= 0xFFFF)
			{
				result[out++] = (CHAR)(unsigned char)(0xE0 | ((codepoint >> 12) & 0x0F));
				result[out++] = (CHAR)(unsigned char)(0x80 | ((codepoint >> 6) & 0x3F));
				result[out++] = (CHAR)(unsigned char)(0x80 | (codepoint & 0x3F));
			}
			else
			{
				result[out++] = (CHAR)(unsigned char)(0xF0 | ((codepoint >> 18) & 0x07));
				result[out++] = (CHAR)(unsigned char)(0x80 | ((codepoint >> 12) & 0x3F));
				result[out++] = (CHAR)(unsigned char)(0x80 | ((codepoint >> 6) & 0x3F));
				result[out++] = (CHAR)(unsigned char)(0x80 | (codepoint & 0x3F));
			}
		}

		result[out] = '\0';
		return result;
	}

    Common::System::Optional<UINT64> UTF<CHAR>::FromUTF16String(const CHAR16* src, CHAR* outBuffer, UINT64 outBufferSize)
    {
        if (src == nullptr || outBuffer == nullptr) return Common::System::Optional<UINT64>();
        UINT64 srcLen = UTF<CHAR16>::Length(src);
        UINT64 needed = 0;
        for (UINT64 i = 0; i < srcLen; ++i)
        {
            UINT16 w1 = (UINT16)src[i];
            if (w1 >= 0xD800 && w1 <= 0xDBFF)
            {
                if (i + 1 < srcLen)
                {
                    UINT16 w2 = (UINT16)src[i+1];
                    if (w2 >= 0xDC00 && w2 <= 0xDFFF) { needed += 4; ++i; continue; }
                }
                needed += 3;
            }
            else if (w1 >= 0xDC00 && w1 <= 0xDFFF) needed += 3;
            else if (w1 < 0x80) needed += 1;
            else if (w1 < 0x800) needed += 2;
            else needed += 3;
        }
        if (outBufferSize < needed + 1) return Common::System::Optional<UINT64>();
        UINT64 out = 0;
        for (UINT64 i = 0; i < srcLen; ++i)
        {
            UINT32 codepoint;
            UINT16 w1 = (UINT16)src[i];
            if (w1 >= 0xD800 && w1 <= 0xDBFF)
            {
                if (i + 1 < srcLen)
                {
                    UINT16 w2 = (UINT16)src[i + 1];
                    if (w2 >= 0xDC00 && w2 <= 0xDFFF)
                    {
                        codepoint = 0x10000 + (((UINT32)w1 - 0xD800) << 10) + ((UINT32)w2 - 0xDC00);
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
                outBuffer[out++] = (CHAR)(unsigned char)codepoint;
            }
            else if (codepoint <= 0x7FF)
            {
                outBuffer[out++] = (CHAR)(unsigned char)(0xC0 | ((codepoint >> 6) & 0x1F));
                outBuffer[out++] = (CHAR)(unsigned char)(0x80 | (codepoint & 0x3F));
            }
            else if (codepoint <= 0xFFFF)
            {
                outBuffer[out++] = (CHAR)(unsigned char)(0xE0 | ((codepoint >> 12) & 0x0F));
                outBuffer[out++] = (CHAR)(unsigned char)(0x80 | ((codepoint >> 6) & 0x3F));
                outBuffer[out++] = (CHAR)(unsigned char)(0x80 | (codepoint & 0x3F));
            }
            else
            {
                outBuffer[out++] = (CHAR)(unsigned char)(0xF0 | ((codepoint >> 18) & 0x07));
                outBuffer[out++] = (CHAR)(unsigned char)(0x80 | ((codepoint >> 12) & 0x3F));
                outBuffer[out++] = (CHAR)(unsigned char)(0x80 | ((codepoint >> 6) & 0x3F));
                outBuffer[out++] = (CHAR)(unsigned char)(0x80 | (codepoint & 0x3F));
            }
        }
        outBuffer[out] = '\0';
        return Common::System::Optional<UINT64>(out);
    }

    Common::System::Optional<UINT64> UTF<CHAR>::FromUTF8String(const CHAR8* src, CHAR* outBuffer, UINT64 outBufferSize)
    {
        if (src == nullptr || outBuffer == nullptr) return Common::System::Optional<UINT64>();
        UINT64 srcLen = UTF<CHAR8>::Length(src);
        UINT64 needed = 0;
        for (UINT64 i = 0; i < srcLen; )
        {
            unsigned char c = (unsigned char)src[i];
            if (c <= 0x7F) { needed += 1; i += 1; }
            else if ((c & 0xE0) == 0xC0 && i + 1 < srcLen) { needed += 2; i += 2; }
            else if ((c & 0xF0) == 0xE0 && i + 2 < srcLen) { needed += 3; i += 3; }
            else if ((c & 0xF8) == 0xF0 && i + 3 < srcLen) { needed += 4; i += 4; }
            else { needed += 3; i += 1; }
        }
        if (outBufferSize < needed + 1) return Common::System::Optional<UINT64>();
        UINT64 out = 0;
        for (UINT64 i = 0; i < srcLen; )
        {
            unsigned char c = (unsigned char)src[i];
            if (c <= 0x7F) { outBuffer[out++] = (CHAR)c; i += 1; continue; }
            else if ((c & 0xE0) == 0xC0 && i + 1 < srcLen) { unsigned char c1 = (unsigned char)src[i+1]; if ((c1 & 0xC0) == 0x80) { outBuffer[out++] = (CHAR)c; outBuffer[out++] = (CHAR)c1; i += 2; continue; } }
            else if ((c & 0xF0) == 0xE0 && i + 2 < srcLen) { unsigned char c1 = (unsigned char)src[i+1]; unsigned char c2 = (unsigned char)src[i+2]; if (((c1 & 0xC0) == 0x80) && ((c2 & 0xC0) == 0x80)) { outBuffer[out++] = (CHAR)c; outBuffer[out++] = (CHAR)c1; outBuffer[out++] = (CHAR)c2; i += 3; continue; } }
            else if ((c & 0xF8) == 0xF0 && i + 3 < srcLen) { unsigned char c1 = (unsigned char)src[i+1]; unsigned char c2 = (unsigned char)src[i+2]; unsigned char c3 = (unsigned char)src[i+3]; if (((c1 & 0xC0) == 0x80) && ((c2 & 0xC0) == 0x80) && ((c3 & 0xC0) == 0x80)) { outBuffer[out++] = (CHAR)c; outBuffer[out++] = (CHAR)c1; outBuffer[out++] = (CHAR)c2; outBuffer[out++] = (CHAR)c3; i += 4; continue; } }
            outBuffer[out++] = (CHAR)0xEF; outBuffer[out++] = (CHAR)0xBF; outBuffer[out++] = (CHAR)0xBD; i += 1;
        }
        outBuffer[out] = '\0';
        return Common::System::Optional<UINT64>(out);
    }
	CHAR* UTF<CHAR>::FromUTF8String(const CHAR8* str)
	{
		/* Validate UTF-8 and copy bytes into CHAR*; invalid sequences replaced by U+FFFD (EF BF BD). */

		if (str == nullptr)
		{
			return nullptr;
		}

		UINT64 srcLen = UTF<CHAR8>::Length(str);

		// First pass: estimate needed bytes (invalid sequences become 3 bytes U+FFFD)
		UINT64 needed = 0;
		for (UINT64 i = 0; i < srcLen; )
		{
			unsigned char c = (unsigned char)str[i];
			if (c <= 0x7F)
			{
				needed += 1; i += 1;
			}
			else if ((c & 0xE0) == 0xC0 && i + 1 < srcLen)
			{
				unsigned char c1 = (unsigned char)str[i+1];
				if ((c1 & 0xC0) == 0x80)
				{
					needed += 2; i += 2;
				}
				else { needed += 3; i += 1; }
			}
			else if ((c & 0xF0) == 0xE0 && i + 2 < srcLen)
			{
				unsigned char c1 = (unsigned char)str[i+1];
				unsigned char c2 = (unsigned char)str[i+2];
				if (((c1 & 0xC0) == 0x80) && ((c2 & 0xC0) == 0x80)) { needed += 3; i += 3; }
				else { needed += 3; i += 1; }
			}
			else if ((c & 0xF8) == 0xF0 && i + 3 < srcLen)
			{
				unsigned char c1 = (unsigned char)str[i+1];
				unsigned char c2 = (unsigned char)str[i+2];
				unsigned char c3 = (unsigned char)str[i+3];
				if (((c1 & 0xC0) == 0x80) && ((c2 & 0xC0) == 0x80) && ((c3 & 0xC0) == 0x80)) { needed += 4; i += 4; }
				else { needed += 3; i += 1; }
			}
			else { needed += 3; i += 1; }
		}

		CHAR* result = new CHAR[needed + 1];
		UINT64 out = 0;

		for (UINT64 i = 0; i < srcLen; )
		{
			unsigned char c = (unsigned char)str[i];
			if (c <= 0x7F)
			{
				result[out++] = (CHAR)c; i += 1; continue;
			}
			else if ((c & 0xE0) == 0xC0 && i + 1 < srcLen)
			{
				unsigned char c1 = (unsigned char)str[i+1];
				if ((c1 & 0xC0) == 0x80)
				{
					// copy two bytes
					result[out++] = (CHAR)c;
					result[out++] = (CHAR)c1;
					i += 2; continue;
				}
			}
			else if ((c & 0xF0) == 0xE0 && i + 2 < srcLen)
			{
				unsigned char c1 = (unsigned char)str[i+1];
				unsigned char c2 = (unsigned char)str[i+2];
				if (((c1 & 0xC0) == 0x80) && ((c2 & 0xC0) == 0x80))
				{
					result[out++] = (CHAR)c; result[out++] = (CHAR)c1; result[out++] = (CHAR)c2;
					i += 3; continue;
				}
			}
			else if ((c & 0xF8) == 0xF0 && i + 3 < srcLen)
			{
				unsigned char c1 = (unsigned char)str[i+1];
				unsigned char c2 = (unsigned char)str[i+2];
				unsigned char c3 = (unsigned char)str[i+3];
				if (((c1 & 0xC0) == 0x80) && ((c2 & 0xC0) == 0x80) && ((c3 & 0xC0) == 0x80))
				{
					result[out++] = (CHAR)c; result[out++] = (CHAR)c1; result[out++] = (CHAR)c2; result[out++] = (CHAR)c3;
					i += 4; continue;
				}
			}
			// invalid sequence -> insert UTF-8 replacement U+FFFD (EF BF BD)
			result[out++] = (CHAR)0xEF; result[out++] = (CHAR)0xBF; result[out++] = (CHAR)0xBD;
			i += 1;
		}

		result[out] = '\0';
		return result;
	}
}