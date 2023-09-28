#include "StringHelpers.h"
#include "UEFIDef.h"

namespace Bootloader
{
	const CHAR16* hexChars = u"0123456789ABCDEF";

	CHAR16 _hexGUIDString[39] {'\0'};
	const CHAR16* StringHelpers::ToString(const EFI_GUID guid)
	{
		_hexGUIDString[0] = u'{';
		_hexGUIDString[1] = hexChars[(guid.Data1 >> 28) & 0x0F];
		_hexGUIDString[2] = hexChars[(guid.Data1 >> 24) & 0x0F];
		_hexGUIDString[3] = hexChars[(guid.Data1 >> 20) & 0x0F];
		_hexGUIDString[4] = hexChars[(guid.Data1 >> 16) & 0x0F];
		_hexGUIDString[5] = hexChars[(guid.Data1 >> 12) & 0x0F];
		_hexGUIDString[6] = hexChars[(guid.Data1 >> 8) & 0x0F];
		_hexGUIDString[7] = hexChars[(guid.Data1 >> 4) & 0x0F];
		_hexGUIDString[8] = hexChars[guid.Data1 & 0x0F];
		_hexGUIDString[9] = u'-';
		_hexGUIDString[10] = hexChars[(guid.Data2 >> 12) & 0x0F];
		_hexGUIDString[11] = hexChars[(guid.Data2 >> 8) & 0x0F];
		_hexGUIDString[12] = hexChars[(guid.Data2 >> 4) & 0x0F];
		_hexGUIDString[13] = hexChars[guid.Data2 & 0x0F];
		_hexGUIDString[14] = u'-';
		_hexGUIDString[15] = hexChars[(guid.Data3 >> 12) & 0x0F];
		_hexGUIDString[16] = hexChars[(guid.Data3 >> 8) & 0x0F];
		_hexGUIDString[17] = hexChars[(guid.Data3 >> 4) & 0x0F];
		_hexGUIDString[18] = hexChars[guid.Data3 & 0x0F];
		_hexGUIDString[19] = u'-';
		_hexGUIDString[20] = hexChars[(guid.Data4[0] >> 4) & 0x0F];
		_hexGUIDString[21] = hexChars[guid.Data4[0] & 0x0F];
		_hexGUIDString[22] = hexChars[(guid.Data4[1] >> 4) & 0x0F];
		_hexGUIDString[23] = hexChars[guid.Data4[1] & 0x0F];
		_hexGUIDString[24] = u'-';
		_hexGUIDString[25] = hexChars[(guid.Data4[2] >> 4) & 0x0F];
		_hexGUIDString[26] = hexChars[guid.Data4[2] & 0x0F];
		_hexGUIDString[27] = hexChars[(guid.Data4[3] >> 4) & 0x0F];
		_hexGUIDString[28] = hexChars[guid.Data4[3] & 0x0F];
		_hexGUIDString[29] = hexChars[(guid.Data4[4] >> 4) & 0x0F];
		_hexGUIDString[30] = hexChars[guid.Data4[4] & 0x0F];
		_hexGUIDString[31] = hexChars[(guid.Data4[5] >> 4) & 0x0F];
		_hexGUIDString[32] = hexChars[guid.Data4[5] & 0x0F];
		_hexGUIDString[33] = hexChars[(guid.Data4[6] >> 4) & 0x0F];
		_hexGUIDString[34] = hexChars[guid.Data4[6] & 0x0F];
		_hexGUIDString[35] = hexChars[(guid.Data4[7] >> 4) & 0x0F];
		_hexGUIDString[36] = hexChars[guid.Data4[7] & 0x0F];
		_hexGUIDString[37] = u'}';
		_hexGUIDString[38] = u'\0';
		return _hexGUIDString;
	}

	CHAR16 _hex8String[3] {'\0'};
	const CHAR16* StringHelpers::ToHex(const UINT8 b)
	{
		_hex8String[0] = hexChars[(b >> 4) & 0x0F];
		_hex8String[1] = hexChars[b & 0x0F];
		_hex8String[2] = u'\0';
		return _hex8String;
	}

	CHAR16 _hex16String[5] {'\0'};
	const CHAR16* StringHelpers::ToHex(const UINT16 b)
	{
		_hex16String[0] = hexChars[(b >> 12) & 0x0F];
		_hex16String[1] = hexChars[(b >> 8) & 0x0F];
		_hex16String[2] = hexChars[(b >> 4) & 0x0F];
		_hex16String[3] = hexChars[b & 0x0F];
		_hex16String[4] = u'\0';
		return _hex16String;
	}

	CHAR16 _hex32String[9] {'\0'};
	const CHAR16* StringHelpers::ToHex(const UINT32 b)
	{
		_hex32String[0] = hexChars[(b >> 28) & 0x0F];
		_hex32String[1] = hexChars[(b >> 24) & 0x0F];
		_hex32String[2] = hexChars[(b >> 20) & 0x0F];
		_hex32String[3] = hexChars[(b >> 16) & 0x0F];
		_hex32String[4] = hexChars[(b >> 12) & 0x0F];
		_hex32String[5] = hexChars[(b >> 8) & 0x0F];
		_hex32String[6] = hexChars[(b >> 4) & 0x0F];
		_hex32String[7] = hexChars[b & 0x0F];
		_hex32String[8] = u'\0';
		return _hex32String;
	}

	CHAR16 _hex64String[17] {'\0'};
	const CHAR16* StringHelpers::ToHex(const UINT64 b)
	{
		_hex64String[0] = hexChars[(b >> 60) & 0x0F];
		_hex64String[1] = hexChars[(b >> 56) & 0x0F];
		_hex64String[2] = hexChars[(b >> 52) & 0x0F];
		_hex64String[3] = hexChars[(b >> 48) & 0x0F];
		_hex64String[4] = hexChars[(b >> 44) & 0x0F];
		_hex64String[5] = hexChars[(b >> 40) & 0x0F];
		_hex64String[6] = hexChars[(b >> 36) & 0x0F];
		_hex64String[7] = hexChars[(b >> 32) & 0x0F];
		_hex64String[8] = hexChars[(b >> 28) & 0x0F];
		_hex64String[9] = hexChars[(b >> 24) & 0x0F];
		_hex64String[10] = hexChars[(b >> 20) & 0x0F];
		_hex64String[11] = hexChars[(b >> 16) & 0x0F];
		_hex64String[12] = hexChars[(b >> 12) & 0x0F];
		_hex64String[13] = hexChars[(b >> 8) & 0x0F];
		_hex64String[14] = hexChars[(b >> 4) & 0x0F];
		_hex64String[15] = hexChars[b & 0x0F];
		_hex64String[16] = u'\0';
		return _hex64String;
	}
}