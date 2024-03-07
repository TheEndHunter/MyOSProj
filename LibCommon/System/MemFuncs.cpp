#include "MemFuncs.h"

namespace Common::System
{
    VOID MemSet(VOID* dest, UINT8 value, UINTN size)
    {
        UINT8* p = (UINT8*)dest;
		for (UINTN i = 0; i < size; i++)
		{
			*p = value;
			p++;
		}
    }

	VOID MemCpy(VOID* dest, VOID* src, UINTN size)
	{
		UINT8* p = (UINT8*)dest;
		UINT8* q = (UINT8*)src;
		for (UINTN i = 0; i < size; i++)
		{
			*p = *q;
			p++;
			q++;
		}
	}

	VOID MemMove(VOID* dest, VOID* src, UINTN size)
	{
		UINT8* p = (UINT8*)dest;
		UINT8* q = (UINT8*)src;
		for (UINTN i = 0; i < size; i++)
		{
			*p = *q;
			*q = 0;
			p++;
			q++;
		}
	}

	VOID MemZero(VOID* dest, UINTN size)
	{
		UINT8* p = (UINT8*)dest;
		for (UINTN i = 0; i < size; i++)
		{
			*p = 0;
			p++;
		}
	}

	VOID MemReverse(VOID* dest, UINTN size)
	{
		UINT8* p = (UINT8*)dest;
		UINT8* q = (UINT8*)dest + size - 1;
		for (UINTN i = 0; i < size / 2; i++)
		{
			UINT8 temp = *p;
			*p = *q;
			*q = temp;
			p++;
			q--;
		}
	}

}
