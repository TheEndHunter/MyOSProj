#pragma once
#include <TypeDefs.h>
#include <Numerics/NumberBase.h>

namespace Common::System
{
	VOID MemSet(VOID* dest, UINT8 value, UINT64 length);
	VOID MemCpy(VOID* dest, VOID* src, UINT64 length);
	VOID MemMove(VOID* dest, VOID* src, UINT64 length);
	VOID MemZero(VOID* dest, UINT64 length);
	VOID MemReverse(VOID* dest, UINT64 length);
	BOOLEAN MemCmp(VOID* cmpA, VOID* cmpB, UINT64 length);

	template<typename T>
	VOID MemSet(T* dest, T value, UINT64 length)
	{
		T* p = (T*)dest;
		for (UINT64 i = 0; i < length; i++)
		{
			p[i] = value;
		}
	}

	template<typename T>
	VOID MemCpy(T* dest, T* src, UINT64 length)
	{
		T* p = (T*)dest;
		T* q = (T*)src;

		for (UINT64 i = 0; i < length; i++)
		{
			p[i] = q[i];
		}
	}

	template<typename T>
	VOID MemMove(T* dest, T* src, UINT64 length)
	{
		T* p = (T*)dest;
		T* q = (T*)src;

		T* temp = new T[length];

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

	template<typename T>
	VOID MemZero(T* dest, UINT64 length)
	{
		T* p = (T*)dest;
		for (UINT64 i = 0; i < length; i++)
		{
			*p = 0;
			p++;
		}
	}

	template<typename T>
	VOID MemReverse(T* dest, UINT64 length)
	{
		T* p = (T*)dest;

		T* temp = new T[length];

		for (UINT64 i = 0; i < length; i++)
		{
			temp[i] = p[i];
		}

		for (UINT64 i = 0; i < length; i++)
		{
			p[i] = temp[length - i - 1];
		}

		delete[] temp;
	}

	template<typename T>
	BOOLEAN MemCmp(T* cmpA, T* cmpB, UINT64 length)
	{
		T* p = (T*)cmpA;
		T* q = (T*)cmpB;

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

inline void memcpy(void* dest, void* src, UINT64 length)
{
	Common::System::MemCpy(dest, src, length);
}

inline void memmove(void* dest, void* src, UINT64 length)
{
	Common::System::MemMove(dest, src, length);
}

inline void memset(void* dest, UINT8 value, UINT64 length)
{
	Common::System::MemSet(dest, value, length);
}

inline void memzero(void* dest, UINT64 length)
{
	Common::System::MemZero(dest, length);
}

inline void memreverse(void* dest, UINT64 length)
{
	Common::System::MemReverse(dest, length);
}

inline bool memcmp(void* cmpA, void* cmpB, UINT64 length)
{
	return Common::System::MemCmp(cmpA, cmpB, length);
}