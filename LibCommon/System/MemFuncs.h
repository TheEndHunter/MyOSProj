#pragma once
#include <TypeDefs.h>
#include <Numerics/NumberBase.h>

namespace Common::System
{
	VOID MemSet(VOID* dest, UINT8 value, UINT64 size);
	VOID MemCpy(VOID* dest, VOID* src, UINT64 size);
	VOID MemMove(VOID* dest, VOID* src, UINT64 size);
	VOID MemZero(VOID* dest, UINT64 size);
	VOID MemReverse(VOID* dest, UINT64 size);
	BOOLEAN MemCmp(VOID* cmpA, VOID* cmpB, UINT64 size);

	template<typename T>
	VOID MemSet(T* dest, T value, UINT64 size)
	{
		T* p = (T*)dest;
		for (UINT64 i = 0; i < size; i++)
		{
			p[i] = value;
		}
	}

	template<typename T>
	VOID MemCpy(T* dest, T* src, UINT64 size)
	{
		T* p = (T*)dest;
		T* q = (T*)src;

		for (UINT64 i = 0; i < size; i++)
		{
			p[i] = q[i];
		}
	}

	template<typename T>
	VOID MemMove(T* dest, T* src, UINT64 size)
	{
		T* p = (T*)dest;
		T* q = (T*)src;

		T* temp = new T[size];

		for (UINT64 i = 0; i < size; i++)
		{
			temp[i] = q[i];
		}

		for (UINT64 i = 0; i < size; i++)
		{
			p[i] = temp[i];
		}

		delete[] temp;
	}

	template<typename T>
	VOID MemZero(T* dest, UINT64 size)
	{
		T* p = (T*)dest;
		for (UINT64 i = 0; i < size; i++)
		{
			*p = 0;
			p++;
		}
	}

	template<typename T>
	VOID MemReverse(T* dest, UINT64 size)
	{
		T* p = (T*)dest;

		T* temp = new T[size];

		for (UINT64 i = 0; i < size; i++)
		{
			temp[i] = p[i];
		}

		for (UINT64 i = 0; i < size; i++)
		{
			p[i] = temp[size - i - 1];
		}

		delete[] temp;
	}

	template<typename T>
	BOOLEAN MemCmp(T* cmpA, T* cmpB, UINT64 size)
	{
		T* p = (T*)cmpA;
		T* q = (T*)cmpB;

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

inline void memcpy(void* dest, void* src, UINT64 size)
{
	Common::System::MemCpy(dest, src, size);
}

inline void memmove(void* dest, void* src, UINT64 size)
{
	Common::System::MemMove(dest, src, size);
}

inline void memset(void* dest, UINT8 value, UINT64 size)
{
	Common::System::MemSet(dest, value, size);
}

inline void memzero(void* dest, UINT64 size)
{
	Common::System::MemZero(dest, size);
}

inline void memreverse(void* dest, UINT64 size)
{
	Common::System::MemReverse(dest, size);
}

inline bool memcmp(void* cmpA, void* cmpB, UINT64 size)
{
	return Common::System::MemCmp(cmpA, cmpB, size);
}