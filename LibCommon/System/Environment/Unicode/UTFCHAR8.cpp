#include <System/Environment/Unicode/UTFCHAR8.h>

namespace Common::System::Environment
{
	const CHAR8 UTF<CHAR8>::NewLine[3]{ u8'\r', u8'\n',u8'\0' };
	CHAR8 _UTF8_GUIDTOSTRING[43] = { u8'{',u8'\0',u8'\0',u8'\0',u8'\0',u8'\0',u8'\0',u8'\0',u8'\0',u8'-',u8'\0',u8'\0',u8'\0',u8'\0',u8'-',u8'\0',u8'\0',u8'\0',u8'\0',u8'-',u8'\0',u8'\0',u8'\0',u8'\0',u8'-',u8'\0',u8'\0',u8'\0',u8'\0',u8'\0',u8'\0',u8'\0',u8'\0',u8'\0',u8'\0',u8'\0',u8'\0',u8'}',u8'\0' };
	CHAR8 _UTF8_HEXCHARS[17] = { u8'0',u8'1',u8'2',u8'3',u8'4',u8'5',u8'6',u8'7',u8'8',u8'9',u8'A',u8'B',u8'C',u8'D',u8'E',u8'F' };
	CHAR8 _UTF8_HEXSTRING[18] = { u8'\0',u8'\0',u8'\0',u8'\0',u8'\0',u8'\0',u8'\0',u8'\0',u8'\0',u8'\0',u8'\0',u8'\0',u8'\0',u8'\0',u8'\0',u8'\0',u8'\0',u8'\0' };
	CHAR8 _UTF8_VALUETOSTRING[23] = { u8'\0',u8'\0',u8'\0',u8'\0',u8'\0',u8'\0',u8'\0',u8'\0',u8'\0',u8'\0',u8'\0',u8'\0',u8'\0',u8'\0',u8'\0',u8'\0',u8'\0',u8'\0',u8'\0',u8'\0',u8'\0',u8'\0',u8'\0' };
	CHAR8 _UTF8_WHITESPACECHARS[8] = { 0x09,0x0A,0x0B,0x0C,0x0D,0x20,0x85,0xA0 };

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
	
	CHAR8* UTF<CHAR8>::ToHex(const INT16 value)
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

	CHAR8* UTF<CHAR8>::ToHex(const INT32 value)
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

	CHAR8* UTF<CHAR8>::ToHex(const INT64 value)
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

	CHAR8* UTF<CHAR8>::ToHex(const INT8 value)
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

	CHAR8* UTF<CHAR8>::ToHex(const UINT16 value)
	{
		_UTF8_HEXSTRING[0] = _UTF8_HEXCHARS[(value >> 12) & 0xF];
		_UTF8_HEXSTRING[1] = _UTF8_HEXCHARS[(value >> 8) & 0xF];
		_UTF8_HEXSTRING[2] = _UTF8_HEXCHARS[(value >> 4) & 0xF];
		_UTF8_HEXSTRING[3] = _UTF8_HEXCHARS[value & 0xF];
		_UTF8_HEXSTRING[4] = u8'\0';
		return &_UTF8_HEXSTRING[0];
	}

	CHAR8* UTF<CHAR8>::ToHex(const UINT32 value)
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

	CHAR8* UTF<CHAR8>::ToHex(const UINT64 value)
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

	CHAR8* UTF<CHAR8>::ToHex(const UINT8 value)
	{
		_UTF8_HEXSTRING[0] = _UTF8_HEXCHARS[(value >> 4) & 0xF];
		_UTF8_HEXSTRING[1] = _UTF8_HEXCHARS[value & 0xF];
		_UTF8_HEXSTRING[2] = u8'\0';
		return &_UTF8_HEXSTRING[0];
	}

	CHAR8* UTF<CHAR8>::ToHex(const VOID_PTR ptr)
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

	CHAR8* UTF<CHAR8>::ToString(const EFI::EFI_GUID guid)
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

	CHAR8* UTF<CHAR8>::ToString(const EFI::EFI_STATUS status)
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

	CHAR8* UTF<CHAR8>::ToString(const Common::System::MemoryManagement::AllocatorStatus status)
	{
		switch (status)
		{
		case Common::System::MemoryManagement::AllocatorStatus::Success:
			return (CHAR8*)_UTF8_ALLOC_STATUS_SUCCESS;
		case Common::System::MemoryManagement::AllocatorStatus::Invalid_Parameters:
			return (CHAR8*)_UTF8_ALLOC_STATUS_INVALID_PARAMETER;
		case Common::System::MemoryManagement::AllocatorStatus::Not_Enough_Memory:
			return (CHAR8*)_UTF8_ALLOC_STATUS_NOT_ENOUGH_MEMORY;
		case Common::System::MemoryManagement::AllocatorStatus::Not_Enough_Pages:
			return (CHAR8*)_UTF8_ALLOC_STATUS_NOT_ENOUGH_PAGES;
		case Common::System::MemoryManagement::AllocatorStatus::Access_Denied:
			return (CHAR8*)_UTF8_ALLOC_STATUS_ACCESS_DENIED;
		}
	}

	CHAR8* UTF<CHAR8>::ToString(const INT16 value)
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
		BOOLEAN isNegative = false;
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

	CHAR8* UTF<CHAR8>::ToString(const INT32 value)
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
		BOOLEAN isNegative = false;
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

	CHAR8* UTF<CHAR8>::ToString(const INT64 value)
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
		BOOLEAN isNegative = false;
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

	CHAR8* UTF<CHAR8>::ToString(const INT8 value)
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
		BOOLEAN isNegative = false;
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

	CHAR8* UTF<CHAR8>::ToString(const UINT16 value)
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

	CHAR8* UTF<CHAR8>::ToString(const UINT32 value)
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

	CHAR8* UTF<CHAR8>::ToString(const UINT64 value)
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

	CHAR8* UTF<CHAR8>::ToString(const UINT8 value)
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

	CHAR8* UTF<CHAR8>::ToString(const VOID_PTR ptr)
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

	CHAR8* UTF<CHAR8>::ToString(const BOOLEAN boolean)
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

	UINT64 UTF<CHAR8>::Length(const CHAR8* str)
	{
		if (str == nullptr)
		{
			return 0;
		}

		if (str[0] == u8'\0')
		{
			return 1;
		}

		UINT64 index = 0;
		UINT64 len = 1;
		while (str[index] != u8'\0')
		{
			len++;
			index++;
		}
		return len;
	}

	BOOLEAN UTF<CHAR8>::Compare(const CHAR8* l, const CHAR8* r, StringCulture culture)
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

	BOOLEAN UTF<CHAR8>::StartsWith(const CHAR8* str, const CHAR8* value, StringCulture culture)
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

	BOOLEAN UTF<CHAR8>::EndsWith(const CHAR8* str, const CHAR8* value, StringCulture culture)
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

	BOOLEAN UTF<CHAR8>::Contains(const CHAR8* str, const CHAR8* value, StringCulture culture)
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
					for (UINT64 i = 0; i < valueLength; i++)
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

	BOOLEAN UTF<CHAR8>::IsNullOrEmpty(const CHAR8* str)
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

	BOOLEAN UTF<CHAR8>::IsNullOrWhiteSpace(const CHAR8* str)
	{
		if (str == nullptr)
		{
			return TRUE;
		};

		if (str[0] == u8'\0')
		{
			return TRUE;
		}

		UINT64 index = 0;
		INT64 charindex = -1;
		while (str[index] != u'\0')
		{
			UINT64 i = 0;
			for (UINT64 i = 0; i < 30; i++)
			{
				if (str[index] != _UTF8_WHITESPACECHARS[i])
				{
					charindex = index;
				}
			}
			index++;
		}

		return charindex == -1;
	}
	BOOLEAN UTF<CHAR8>::IsNullEmptyOrWhiteSpace(const CHAR8* str)
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
		INT64 charindex = -1;
		while (str[index] != u'\0')
		{
			UINT64 i = 0;
			for (UINT64 i = 0; i < 30; i++)
			{
				if (str[index] != _UTF8_WHITESPACECHARS[i])
				{
					charindex = index;
				}
			}
			index++;
		}

		return charindex == -1;
	}
	CHAR8* UTF<CHAR8>::FromCharArray(CHAR8 arr[], UINT64 Length)
	{
		/*Convert from CHAR8 Array to UTF<CHAR8> String*/

		if (arr == nullptr)
		{
			return nullptr;
		}
		CHAR8* result = new CHAR8[Length + 1];

		for (UINT64 i = 0; i < Length; i++)
		{
			result[i] = arr[i];
		}
		result[Length] = u8'\0';

		return result;
	}
	CHAR8* UTF<CHAR8>::FromUTF16String(const CHAR16* str)
	{
		/*Convert from UTF16 String to UTF<CHAR8> String*/

		if (str == nullptr)
		{
			return nullptr;
		}

		UINT64 len = UTF<CHAR16>::Length(str);

		CHAR8* result = new CHAR8[len];

		for (UINT64 i = 0; i < len; i++)
		{
			result[i] = (CHAR8)str[i];
		}

		return result;
	}
	CHAR8* UTF<CHAR8>::FromCString(const CHAR* str)
	{
		/*Convert from Ascii UTF<CHAR> to UTF<CHAR8>*/

		if (str == nullptr)
		{
			return nullptr;
		}

		UINT64 len = UTF<CHAR>::Length(str);

		CHAR8* result = new CHAR8[len];

		for (UINT64 i = 0; i < len; i++)
		{
			result[i] = (CHAR8)str[i];
		}
		result[len - 1] = u8'\0';

		return result;
	}
}