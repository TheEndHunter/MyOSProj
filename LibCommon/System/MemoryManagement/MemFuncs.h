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
		T* p = dest;
		for (UINT64 i = 0; i < length; i++)
		{
			p[i] = value;
		}
	}
	template<typename T>
	VOID MemCpy(T* dest, T* src, UINT64 length)
	{
		T* p = dest;
		T* q = src;

		for (UINT64 i = 0; i < length; i++)
		{
			p[i] = q[i];
		}
	}
	template<typename T>
	VOID MemMove(T* dest, T* src, UINT64 length)
	{
		T* p = dest;
		T* q = src;

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
		T* p = dest;
		for (UINT64 i = 0; i < length; i++)
		{
			*p = 0;
			p++;
		}
	}
	template<typename T>
	VOID MemReverse(T* dest, UINT64 length)
	{
		T* p = dest;

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
		T* p = cmpA;
		T* q = cmpB;

		for (UINT64 i = 0; i < length; i++)
		{
			if (p[i] != q[i])
			{
				return FALSE;
			}
		}

		return TRUE;
	}


	template<CHAR16>
	VOID MemSet(CHAR16* dest, CHAR16 value, UINT64 length)
	{
		CHAR16* p = dest;
		for (UINT64 i = 0; i < length; i++)
		{
			p[i] = value;
		}
	}
	template<CHAR16>
	VOID MemCpy(CHAR16* dest, CHAR16* src, UINT64 length)
	{
		CHAR16* p = dest;
		CHAR16* q = src;

		for (UINT64 i = 0; i < length; i++)
		{
			p[i] = q[i];
		}
	}
	template<CHAR16>
	VOID MemMove(CHAR16* dest, CHAR16* src, UINT64 length)
	{
		CHAR16* p = dest;
		CHAR16* q = src;

		CHAR16* temp = new CHAR16[length];

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
	template<CHAR16>
	VOID MemZero(CHAR16* dest, UINT64 length)
	{
		CHAR16* p = dest;
		for (UINT64 i = 0; i < length; i++)
		{
			*p = 0;
			p++;
		}
	}
	template<CHAR16>
	VOID MemReverse(CHAR16* dest, UINT64 length)
	{
		CHAR16* p = dest;

		CHAR16* temp = new CHAR16[length];

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
	template<CHAR16>
	BOOLEAN MemCmp(CHAR16* cmpA, CHAR16* cmpB, UINT64 length)
	{
		CHAR16* p = cmpA;
		CHAR16* q = cmpB;

		for (UINT64 i = 0; i < length; i++)
		{
			if (p[i] != q[i])
			{
				return FALSE;
			}
		}

		return TRUE;
	}

	template<CHAR32>
	VOID MemSet(CHAR32* dest, CHAR32 value, UINT64 length)
	{
		CHAR32* p = dest;
		for (UINT64 i = 0; i < length; i++)
		{
			p[i] = value;
		}
	}
	template<CHAR32>
	VOID MemCpy(CHAR32* dest, CHAR32* src, UINT64 length)
	{
		CHAR32* p = dest;
		CHAR32* q = src;

		for (UINT64 i = 0; i < length; i++)
		{
			p[i] = q[i];
		}
	}
	template<CHAR32>
	VOID MemMove(CHAR32* dest, CHAR32* src, UINT64 length)
	{
		CHAR32* p = dest;
		CHAR32* q = src;

		CHAR32* temp = new CHAR32[length];

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
	template<CHAR32>
	VOID MemZero(CHAR32* dest, UINT64 length)
	{
		CHAR32* p = dest;
		for (UINT64 i = 0; i < length; i++)
		{
			*p = 0;
			p++;
		}
	}
	template<CHAR32>
	VOID MemReverse(CHAR32* dest, UINT64 length)
	{
		CHAR32* p = dest;

		CHAR32* temp = new CHAR32[length];

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
	template<CHAR32>
	BOOLEAN MemCmp(CHAR32* cmpA, CHAR32* cmpB, UINT64 length)
	{
		CHAR32* p = cmpA;
		CHAR32* q = cmpB;

		for (UINT64 i = 0; i < length; i++)
		{
			if (p[i] != q[i])
			{
				return FALSE;
			}
		}

		return TRUE;
	}

	template<CHAR8>
	VOID MemSet(CHAR8* dest, CHAR8 value, UINT64 length)
	{
		CHAR8* p = dest;
		for (UINT64 i = 0; i < length; i++)
		{
			p[i] = value;
		}
	}
	template<CHAR8>
	VOID MemCpy(CHAR8* dest, CHAR8* src, UINT64 length)
	{
		CHAR8* p = dest;
		CHAR8* q = src;

		for (UINT64 i = 0; i < length; i++)
		{
			p[i] = q[i];
		}
	}
	template<CHAR8>
	VOID MemMove(CHAR8* dest, CHAR8* src, UINT64 length)
	{
		CHAR8* p = dest;
		CHAR8* q = src;

		CHAR8* temp = new CHAR8[length];

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
	template<CHAR8>
	VOID MemZero(CHAR8* dest, UINT64 length)
	{
		CHAR8* p = dest;
		for (UINT64 i = 0; i < length; i++)
		{
			*p = 0;
			p++;
		}
	}
	template<CHAR8>
	VOID MemReverse(CHAR8* dest, UINT64 length)
	{
		CHAR8* p = dest;

		CHAR8* temp = new CHAR8[length];

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
	template<CHAR8>
	BOOLEAN MemCmp(CHAR8* cmpA, CHAR8* cmpB, UINT64 length)
	{
		CHAR8* p = cmpA;
		CHAR8* q = cmpB;

		for (UINT64 i = 0; i < length; i++)
		{
			if (p[i] != q[i])
			{
				return FALSE;
			}
		}

		return TRUE;
	}

	template<CHAR>
	VOID MemSet(CHAR* dest, CHAR value, UINT64 length)
	{
		CHAR* p = dest;
		for (UINT64 i = 0; i < length; i++)
		{
			p[i] = value;
		}
	}
	template<CHAR>
	VOID MemCpy(CHAR* dest, CHAR* src, UINT64 length)
	{
		CHAR* p = dest;
		CHAR* q = src;

		for (UINT64 i = 0; i < length; i++)
		{
			p[i] = q[i];
		}
	}
	template<CHAR>
	VOID MemMove(CHAR* dest, CHAR* src, UINT64 length)
	{
		CHAR* p = dest;
		CHAR* q = src;

		CHAR* temp = new CHAR[length];

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
	template<CHAR>
	VOID MemZero(CHAR* dest, UINT64 length)
	{
		CHAR* p = dest;
		for (UINT64 i = 0; i < length; i++)
		{
			*p = 0;
			p++;
		}
	}
	template<CHAR>
	VOID MemReverse(CHAR* dest, UINT64 length)
	{
		CHAR* p = dest;

		CHAR* temp = new CHAR[length];

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
	template<CHAR>
	BOOLEAN MemCmp(CHAR* cmpA, CHAR* cmpB, UINT64 length)
	{
		CHAR* p = cmpA;
		CHAR* q = cmpB;

		for (UINT64 i = 0; i < length; i++)
		{
			if (p[i] != q[i])
			{
				return FALSE;
			}
		}

		return TRUE;
	}

	template<INT16>
	VOID MemSet(INT16* dest, INT16 value, UINT64 length)
	{
		INT16* p = dest;
		for (UINT64 i = 0; i < length; i++)
		{
			p[i] = value;
		}
	}
	template<INT16>
	VOID MemCpy(INT16* dest, INT16* src, UINT64 length)
	{
		INT16* p = dest;
		INT16* q = src;

		for (UINT64 i = 0; i < length; i++)
		{
			p[i] = q[i];
		}
	}
	template<INT16>
	VOID MemMove(INT16* dest, INT16* src, UINT64 length)
	{
		INT16* p = dest;
		INT16* q = src;

		INT16* temp = new INT16[length];

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
	template<INT16>
	VOID MemZero(INT16* dest, UINT64 length)
	{
		INT16* p = dest;
		for (UINT64 i = 0; i < length; i++)
		{
			*p = 0;
			p++;
		}
	}
	template<INT16>
	VOID MemReverse(INT16* dest, UINT64 length)
	{
		INT16* p = dest;

		INT16* temp = new INT16[length];

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
	template<INT16>
	BOOLEAN MemCmp(INT16* cmpA, INT16* cmpB, UINT64 length)
	{
		INT16* p = cmpA;
		INT16* q = cmpB;

		for (UINT64 i = 0; i < length; i++)
		{
			if (p[i] != q[i])
			{
				return FALSE;
			}
		}

		return TRUE;
	}

	template<INT32>
	VOID MemSet(INT32* dest, INT32 value, UINT64 length)
	{
		INT32* p = dest;
		for (UINT64 i = 0; i < length; i++)
		{
			p[i] = value;
		}
	}
	template<INT32>
	VOID MemCpy(INT32* dest, INT32* src, UINT64 length)
	{
		INT32* p = dest;
		INT32* q = src;

		for (UINT64 i = 0; i < length; i++)
		{
			p[i] = q[i];
		}
	}
	template<INT32>
	VOID MemMove(INT32* dest, INT32* src, UINT64 length)
	{
		INT32* p = dest;
		INT32* q = src;

		INT32* temp = new INT32[length];

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
	template<INT32>
	VOID MemZero(INT32* dest, UINT64 length)
	{
		INT32* p = dest;
		for (UINT64 i = 0; i < length; i++)
		{
			*p = 0;
			p++;
		}
	}
	template<INT32>
	VOID MemReverse(INT32* dest, UINT64 length)
	{
		INT32* p = dest;

		INT32* temp = new INT32[length];

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
	template<INT32>
	BOOLEAN MemCmp(INT32* cmpA, INT32* cmpB, UINT64 length)
	{
		INT32* p = cmpA;
		INT32* q = cmpB;

		for (UINT64 i = 0; i < length; i++)
		{
			if (p[i] != q[i])
			{
				return FALSE;
			}
		}

		return TRUE;
	}

	template<INT8>
	VOID MemSet(INT8* dest, INT8 value, UINT64 length)
	{
		INT8* p = dest;
		for (UINT64 i = 0; i < length; i++)
		{
			p[i] = value;
		}
	}
	template<INT8>
	VOID MemCpy(INT8* dest, INT8* src, UINT64 length)
	{
		INT8* p = dest;
		INT8* q = src;

		for (UINT64 i = 0; i < length; i++)
		{
			p[i] = q[i];
		}
	}
	template<INT8>
	VOID MemMove(INT8* dest, INT8* src, UINT64 length)
	{
		INT8* p = dest;
		INT8* q = src;

		INT8* temp = new INT8[length];

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
	template<INT8>
	VOID MemZero(INT8* dest, UINT64 length)
	{
		INT8* p = dest;
		for (UINT64 i = 0; i < length; i++)
		{
			*p = 0;
			p++;
		}
	}
	template<INT8>
	VOID MemReverse(INT8* dest, UINT64 length)
	{
		INT8* p = dest;

		INT8* temp = new INT8[length];

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
	template<INT8>
	BOOLEAN MemCmp(INT8* cmpA, INT8* cmpB, UINT64 length)
	{
		INT8* p = cmpA;
		INT8* q = cmpB;

		for (UINT64 i = 0; i < length; i++)
		{
			if (p[i] != q[i])
			{
				return FALSE;
			}
		}

		return TRUE;
	}

	template<UINT16>
	VOID MemSet(UINT16* dest, UINT16 value, UINT64 length)
	{
		UINT16* p = dest;
		for (UINT64 i = 0; i < length; i++)
		{
			p[i] = value;
		}
	}
	template<UINT16>
	VOID MemCpy(UINT16* dest, UINT16* src, UINT64 length)
	{
		UINT16* p = dest;
		UINT16* q = src;

		for (UINT64 i = 0; i < length; i++)
		{
			p[i] = q[i];
		}
	}
	template<UINT16>
	VOID MemMove(UINT16* dest, UINT16* src, UINT64 length)
	{
		UINT16* p = dest;
		UINT16* q = src;

		UINT16* temp = new UINT16[length];

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
	template<UINT16>
	VOID MemZero(UINT16* dest, UINT64 length)
	{
		UINT16* p = dest;
		for (UINT64 i = 0; i < length; i++)
		{
			*p = 0;
			p++;
		}
	}
	template<UINT16>
	VOID MemReverse(UINT16* dest, UINT64 length)
	{
		UINT16* p = dest;

		UINT16* temp = new UINT16[length];

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
	template<UINT16>
	BOOLEAN MemCmp(UINT16* cmpA, UINT16* cmpB, UINT64 length)
	{
		UINT16* p = cmpA;
		UINT16* q = cmpB;

		for (UINT64 i = 0; i < length; i++)
		{
			if (p[i] != q[i])
			{
				return FALSE;
			}
		}

		return TRUE;
	}

	template<UINT32>
	VOID MemSet(UINT32* dest, UINT32 value, UINT64 length)
	{
		UINT32* p = dest;
		for (UINT64 i = 0; i < length; i++)
		{
			p[i] = value;
		}
	}
	template<UINT32>
	VOID MemCpy(UINT32* dest, UINT32* src, UINT64 length)
	{
		UINT32* p = dest;
		UINT32* q = src;

		for (UINT64 i = 0; i < length; i++)
		{
			p[i] = q[i];
		}
	}
	template<UINT32>
	VOID MemMove(UINT32* dest, UINT32* src, UINT64 length)
	{
		UINT32* p = dest;
		UINT32* q = src;

		UINT32* temp = new UINT32[length];

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
	template<UINT32>
	VOID MemZero(UINT32* dest, UINT64 length)
	{
		UINT32* p = dest;
		for (UINT64 i = 0; i < length; i++)
		{
			*p = 0;
			p++;
		}
	}
	template<UINT32>
	VOID MemReverse(UINT32* dest, UINT64 length)
	{
		UINT32* p = dest;

		UINT32* temp = new UINT32[length];

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
	template<UINT32>
	BOOLEAN MemCmp(UINT32* cmpA, UINT32* cmpB, UINT64 length)
	{
		UINT32* p = cmpA;
		UINT32* q = cmpB;

		for (UINT64 i = 0; i < length; i++)
		{
			if (p[i] != q[i])
			{
				return FALSE;
			}
		}

		return TRUE;
	}

	template<UINT8>
	VOID MemSet(UINT8* dest, UINT8 value, UINT64 length)
	{
		UINT8* p = dest;
		for (UINT64 i = 0; i < length; i++)
		{
			p[i] = value;
		}
	}
	template<UINT8>
	VOID MemCpy(UINT8* dest, UINT8* src, UINT64 length)
	{
		UINT8* p = dest;
		UINT8* q = src;

		for (UINT64 i = 0; i < length; i++)
		{
			p[i] = q[i];
		}
	}
	template<UINT8>
	VOID MemMove(UINT8* dest, UINT8* src, UINT64 length)
	{
		UINT8* p = dest;
		UINT8* q = src;

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
	template<UINT8>
	VOID MemZero(UINT8* dest, UINT64 length)
	{
		UINT8* p = dest;
		for (UINT64 i = 0; i < length; i++)
		{
			*p = 0;
			p++;
		}
	}
	template<UINT8>
	VOID MemReverse(UINT8* dest, UINT64 length)
	{
		UINT8* p = dest;

		UINT8* temp = new UINT8[length];

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
	template<UINT8>
	BOOLEAN MemCmp(UINT8* cmpA, UINT8* cmpB, UINT64 length)
	{
		UINT8* p = cmpA;
		UINT8* q = cmpB;

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

inline BOOLEAN memcmp(void* cmpA, void* cmpB, UINT64 length)
{
	return Common::System::MemCmp(cmpA, cmpB, length);
}