#pragma once
#include <TypeDefs.h>

namespace Common::System
{
	VOID MemSet(VOID* dest, UINT8 value, UINTN size);
	VOID MemCpy(VOID* dest, VOID* src, UINTN size);
	VOID MemMove(VOID* dest, VOID* src, UINTN size);
	VOID MemZero(VOID* dest, UINTN size);
	VOID MemReverse(VOID* dest, UINTN size);


}
