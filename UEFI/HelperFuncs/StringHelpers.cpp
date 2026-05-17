#include "StringHelpers.h"

namespace Efi
{
	BOOLEAN CompareStringLengths(const CHAR* left, const CHAR* right, OUT UINT64* lLen, OUT UINT64* rLen)
	{
		if (lLen == nullptr || rLen == nullptr)
			return FALSE;

		if (left == nullptr || right == nullptr)
			return FALSE;

		UINT64 leftLength = 0;
		UINT64 rightLength = 0;

		while (*left++ != u'\0')
			leftLength++;

		while (*right++ != u'\0')
			rightLength++;

		*lLen = leftLength;
		*rLen = rightLength;

		return leftLength == rightLength;
	}
	BOOLEAN CompareStringLengths(const CHAR8* left, const CHAR8* right, OUT UINT64* lLen, OUT UINT64* rLen)
	{
		if (lLen == nullptr || rLen == nullptr)
			return FALSE;

		if (left == nullptr || right == nullptr)
			return FALSE;

		UINT64 leftLength = 0;
		UINT64 rightLength = 0;

		while (*left++ != u'\0')
			leftLength++;

		while (*right++ != u'\0')
			rightLength++;

		*lLen = leftLength;
		*rLen = rightLength;

		return leftLength == rightLength;
	}
	BOOLEAN CompareStringLengths(const CHAR16* left, const CHAR16* right, OUT UINT64* lLen, OUT UINT64* rLen)
	{
		if (lLen == nullptr || rLen == nullptr)
			return FALSE;

		if (left == nullptr || right == nullptr)
			return FALSE;

		UINT64 leftLength = 0;
		UINT64 rightLength = 0;

		while (*left++ != u'\0')
			leftLength++;

		while (*right++ != u'\0')
			rightLength++;

		*lLen = leftLength;
		*rLen = rightLength;

		return leftLength == rightLength;
	}

	BOOLEAN CompareStrings(const CHAR* left, const CHAR* right)
	{
		if (left == nullptr || right == nullptr)
			return FALSE;

		UINT64 lLen;
		UINT64 rLen;

		if (CompareStringLengths(left, right, &lLen, &rLen))
		{
			for (UINT64 i = 0; i <= lLen; i++)
			{
				if (left[i] != right[i])
					return FALSE;
			}
			return TRUE;
		}
		return FALSE; // If lengths are not equal, strings cannot be equal
	}

	BOOLEAN CompareStrings(const CHAR8* left, const CHAR8* right)
	{
		if (left == nullptr || right == nullptr)
			return FALSE;

		UINT64 lLen;
		UINT64 rLen;

		if (CompareStringLengths(left, right, &lLen, &rLen))
		{
			for (UINT64 i = 0; i <= lLen; i++)
			{
				if (left[i] != right[i])
					return FALSE;
			}
			return TRUE;
		}
		return FALSE; // If lengths are not equal, strings cannot be equal
	}

	BOOLEAN CompareStrings(const CHAR16* left, const CHAR16* right)
	{
		if (left == nullptr || right == nullptr)
			return FALSE;

		UINT64 lLen;
		UINT64 rLen;

		if (CompareStringLengths(left, right, &lLen, &rLen))
		{
			for (UINT64 i = 0; i <= lLen; i++)
			{
				if (left[i] != right[i])
					return FALSE;
			}
			return TRUE;
		}
		return FALSE; // If lengths are not equal, strings cannot be equal
	}		
}