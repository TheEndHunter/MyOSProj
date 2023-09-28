#include "StringHelpers.h"
#include <EFI_SYSTEM_TABLE.h>

namespace Bootloader
{
	const CHAR16* hexChars = u"0123456789ABCDEF";

	const CHAR16* StringHelpers::ToString(EFI_SYSTEM_TABLE* sysTable, EFI_GUID guid)
	{
		CHAR16* guidString = nullptr;
		EFI_STATUS s = sysTable->BootServices->AllocatePool(EFI_MEMORY_TYPE::EfiLoaderData , sizeof(CHAR16) * 39, (void**)&guidString);

		if (s != EFI_STATUS::SUCCESS)
		{
			return nullptr;
		}

		guidString[0] = u'{';
		guidString[1] = hexChars[(guid.Data1 >> 28) & 0x0F];
		guidString[2] = hexChars[(guid.Data1 >> 24) & 0x0F];
		guidString[3] = hexChars[(guid.Data1 >> 20) & 0x0F];
		guidString[4] = hexChars[(guid.Data1 >> 16) & 0x0F];
		guidString[5] = hexChars[(guid.Data1 >> 12) & 0x0F];
		guidString[6] = hexChars[(guid.Data1 >> 8) & 0x0F];
		guidString[7] = hexChars[(guid.Data1 >> 4) & 0x0F];
		guidString[8] = hexChars[guid.Data1 & 0x0F];
		guidString[9] = u'-';
		guidString[10] = hexChars[(guid.Data2 >> 12) & 0x0F];
		guidString[11] = hexChars[(guid.Data2 >> 8) & 0x0F];
		guidString[12] = hexChars[(guid.Data2 >> 4) & 0x0F];
		guidString[13] = hexChars[guid.Data2 & 0x0F];
		guidString[14] = u'-';
		guidString[15] = hexChars[(guid.Data3 >> 12) & 0x0F];
		guidString[16] = hexChars[(guid.Data3 >> 8) & 0x0F];
		guidString[17] = hexChars[(guid.Data3 >> 4) & 0x0F];
		guidString[18] = hexChars[guid.Data3 & 0x0F];
		guidString[19] = u'-';
		guidString[20] = hexChars[(guid.Data4[0] >> 4) & 0x0F];
		guidString[21] = hexChars[guid.Data4[0] & 0x0F];
		guidString[22] = hexChars[(guid.Data4[1] >> 4) & 0x0F];
		guidString[23] = hexChars[guid.Data4[1] & 0x0F];
		guidString[24] = u'-';
		guidString[25] = hexChars[(guid.Data4[2] >> 4) & 0x0F];
		guidString[26] = hexChars[guid.Data4[2] & 0x0F];
		guidString[27] = hexChars[(guid.Data4[3] >> 4) & 0x0F];
		guidString[28] = hexChars[guid.Data4[3] & 0x0F];
		guidString[29] = hexChars[(guid.Data4[4] >> 4) & 0x0F];
		guidString[30] = hexChars[guid.Data4[4] & 0x0F];
		guidString[31] = hexChars[(guid.Data4[5] >> 4) & 0x0F];
		guidString[32] = hexChars[guid.Data4[5] & 0x0F];
		guidString[33] = hexChars[(guid.Data4[6] >> 4) & 0x0F];
		guidString[34] = hexChars[guid.Data4[6] & 0x0F];
		guidString[35] = hexChars[(guid.Data4[7] >> 4) & 0x0F];
		guidString[36] = hexChars[guid.Data4[7] & 0x0F];
		guidString[37] = u'}';
		guidString[38] = u'\0';
		return guidString;
	}

	const CHAR16* StringHelpers::ToHex(EFI_SYSTEM_TABLE* sysTable, UINT8 b)
	{
		CHAR16* hexString = nullptr;
		sysTable->BootServices->AllocatePool(EFI_MEMORY_TYPE::EfiLoaderData, sizeof(CHAR16) * 3, (void**)&hexString);
		hexString[0] = hexChars[(b >> 4) & 0x0F];
		hexString[1] = hexChars[b & 0x0F];
		hexString[2] = u'\0';
		return hexString;
	}

	const CHAR16* StringHelpers::ToHex(EFI_SYSTEM_TABLE* sysTable, UINT16 b)
	{
		CHAR16* hexString = nullptr;
		sysTable->BootServices->AllocatePool(EFI_MEMORY_TYPE::EfiLoaderData, sizeof(CHAR16) * 5, (void**)&hexString);
		hexString[0] = hexChars[(b >> 12) & 0x0F];
		hexString[1] = hexChars[(b >> 8) & 0x0F];
		hexString[2] = hexChars[(b >> 4) & 0x0F];
		hexString[3] = hexChars[b & 0x0F];
		hexString[4] = u'\0';
		return hexString;
	}

	const CHAR16* StringHelpers::ToHex(EFI_SYSTEM_TABLE* sysTable, UINT32 b)
	{
		CHAR16* hexString = nullptr;
		sysTable->BootServices->AllocatePool(EFI_MEMORY_TYPE::EfiLoaderData, sizeof(CHAR16) * 9, (void**)&hexString);
		hexString[0] = hexChars[(b >> 28) & 0x0F];
		hexString[1] = hexChars[(b >> 24) & 0x0F];
		hexString[2] = hexChars[(b >> 20) & 0x0F];
		hexString[3] = hexChars[(b >> 16) & 0x0F];
		hexString[4] = hexChars[(b >> 12) & 0x0F];
		hexString[5] = hexChars[(b >> 8) & 0x0F];
		hexString[6] = hexChars[(b >> 4) & 0x0F];
		hexString[7] = hexChars[b & 0x0F];
		hexString[8] = u'\0';
		return hexString;
	}

	const CHAR16* StringHelpers::ToHex(EFI_SYSTEM_TABLE* sysTable, UINT64 b)
	{
		CHAR16* hexString = nullptr;
		sysTable->BootServices->AllocatePool(EFI_MEMORY_TYPE::EfiLoaderData, sizeof(CHAR16) * 17, (void**)&hexString);
		hexString[0] = hexChars[(b >> 60) & 0x0F];
		hexString[1] = hexChars[(b >> 56) & 0x0F];
		hexString[2] = hexChars[(b >> 52) & 0x0F];
		hexString[3] = hexChars[(b >> 48) & 0x0F];
		hexString[4] = hexChars[(b >> 44) & 0x0F];
		hexString[5] = hexChars[(b >> 40) & 0x0F];
		hexString[6] = hexChars[(b >> 36) & 0x0F];
		hexString[7] = hexChars[(b >> 32) & 0x0F];
		hexString[8] = hexChars[(b >> 28) & 0x0F];
		hexString[9] = hexChars[(b >> 24) & 0x0F];
		hexString[10] = hexChars[(b >> 20) & 0x0F];
		hexString[11] = hexChars[(b >> 16) & 0x0F];
		hexString[12] = hexChars[(b >> 12) & 0x0F];
		hexString[13] = hexChars[(b >> 8) & 0x0F];
		hexString[14] = hexChars[(b >> 4) & 0x0F];
		hexString[15] = hexChars[b & 0x0F];
		hexString[16] = u'\0';
		return hexString;
	}
}