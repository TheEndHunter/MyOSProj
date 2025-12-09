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

		delete[length] temp;
	}

	VOID MemZero(VOID* dest, UINT64 length)
	{
		UINT8* p = (UINT8*)dest;
		for (UINT64 i = 0; i < length; i++)
		{
			*p = 0;
			p++;
		}
	}

	VOID MemReverse(VOID* dest, UINT64 length)
	{
		UINT8* p = (UINT8*)dest;

		UINT8* temp = new UINT8[length];

		for (UINT64 i = 0; i < length; i++)
		{
			temp[i] = p[i];
		}

		UINT64 s;
		for (UINT64 i = length - 1; i > 0; i--)
		{
			p[s] = temp[i];
			s++;
		}

		delete[length] temp;
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
