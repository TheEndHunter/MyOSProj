#include "MemFuncs.h"

namespace Common::System
{
    VOID MemSet(VOID* dest, UINT8 value, UINT64 length)
    {
        UINT8* p = (UINT8*)dest;
		for (UINT64 i = 0; i < length; i++)
		{
			p[i] = value;
		}
    }

	VOID MemCpy(VOID* dest, VOID* src, UINT64 length)
	{
		UINT8* p = (UINT8*)dest;
		UINT8* q = (UINT8*)src;

		for (UINT64 i = 0; i < length; i++)
		{
			p[i] = q[i];
		}
	}

	VOID MemMove(VOID* dest, VOID* src, UINT64 length)
	{
		UINT8* p = (UINT8*)dest;
		UINT8* q = (UINT8*)src;

		UINT8* temp = new UINT8[length];

		for (UINT64 i = 0; i < length; i++)
		{
			temp[i] = q[i];
		}

		for (UINT64 i = 0; i < length; i++)
		{
			p[i] = temp[i];
		}

		delete[] temp;
	}

	VOID MemZero(VOID* dest, UINT64 length)
	{
		UINT8* p = (UINT8*)dest;
		for (UINT64 i = 0; i < length; i++)
		{
			p[i] = 0;
		}
	}

	VOID MemReverse(VOID* dest, UINT64 length)
	{
		UINT8* p = (UINT8*)dest;

		if (length == 0) return;

		UINT8* temp = new UINT8[length];

		for (UINT64 i = 0; i < length; i++)
		{
			temp[i] = p[i];
		}

		UINT64 s = 0;
		for (UINT64 i = length; i-- > 0; )
		{
			p[s] = temp[i];
			s++;
		}

		delete[] temp;
	}

	BOOLEAN MemCmp(VOID* cmpA, VOID* cmpB, UINT64 length)
	{
		UINT8* p = (UINT8*)cmpA;
		UINT8* q = (UINT8*)cmpB;

		for (UINT64 i = 0; i < length; i++)
		{
			if (p[i] != q[i])
			{
				return FALSE;
			}
		}

		return TRUE;
	}

}
