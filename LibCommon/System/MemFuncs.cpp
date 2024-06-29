#include "MemFuncs.h"

namespace Common::System
{
    VOID MemSet(VOID* dest, UINT8 value, UINT64 size)
    {
        UINT8* p = (UINT8*)dest;
		for (UINT64 i = 0; i < size; i++)
		{
			p[i] = value;
		}
    }

	VOID MemCpy(VOID* dest, VOID* src, UINT64 size)
	{
		UINT8* p = (UINT8*)dest;
		UINT8* q = (UINT8*)src;

		for (UINT64 i = 0; i < size; i++)
		{
			p[i] = q[i];
		}
	}

	VOID MemMove(VOID* dest, VOID* src, UINT64 size)
	{
		UINT8* p = (UINT8*)dest;
		UINT8* q = (UINT8*)src;

		UINT8* temp = new UINT8[size];

		for (UINT64 i = 0; i < size; i++)
		{
			temp[i] = q[i];	
		}

		for (UINT64 i = 0; i < size; i++)
		{
			p[i] = temp[i];
		}

		delete[size] temp;
	}

	VOID MemZero(VOID* dest, UINT64 size)
	{
		UINT8* p = (UINT8*)dest;
		for (UINT64 i = 0; i < size; i++)
		{
			*p = 0;
			p++;
		}
	}

	VOID MemReverse(VOID* dest, UINT64 size)
	{
		UINT8* p = (UINT8*)dest;

		UINT8* temp = new UINT8[size];

		for (UINT64 i = 0; i < size; i++)
		{
			temp[i] = p[i];
		}

		UINT64 s;
		for (UINT64 i = size - 1; i > 0; i--)
		{
			p[s] = temp[i];
			s++;
		}

		delete[size] temp;
	}

	BOOLEAN MemCmp(VOID* cmpA, VOID* cmpB, UINT64 size)
	{
		UINT8* p = (UINT8*)cmpA;
		UINT8* q = (UINT8*)cmpB;

		for (UINT64 i = 0; i < size; i++)
		{
			if (p[i] != q[i])
			{
				return FALSE;
			}
		}

		return TRUE;
	}

}
