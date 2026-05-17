#pragma once

#include "UEFIDef.h"

namespace Efi
{
	BOOLEAN CompareStringLengths(CONST CHAR* left, CONST CHAR* right, OUT UINT64* lLen, OUT UINT64* rLen);
	BOOLEAN CompareStringLengths(CONST CHAR8* left, CONST CHAR8* right, OUT UINT64* lLen, OUT UINT64* rLen);
	BOOLEAN CompareStringLengths(CONST CHAR16* left, CONST CHAR16* right, OUT UINT64* lLen, OUT UINT64* rLen);

	BOOLEAN CompareStrings(CONST CHAR* left, CONST CHAR* right);
	BOOLEAN CompareStrings(CONST CHAR8* left, CONST CHAR8* right);
	BOOLEAN CompareStrings(CONST CHAR16* left, CONST CHAR16* right);


}
