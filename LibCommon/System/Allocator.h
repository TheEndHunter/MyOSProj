#pragma once

#include <TypeDefs.h>
#include <System/AllocatorStatus.h>

namespace Common::System
{
	typedef VOID_PTR AllocFunc(UINTN size);
	typedef VOID_PTR AllocZeroedFunc(UINTN size);
	typedef VOID_PTR AllocPageFunc(UINTN size);
	typedef VOID_PTR AllocPageZeroedFunc(UINTN size);

	typedef VOID FreeFunc(VOID_PTR ptr);
	typedef VOID FreePageFunc(VOID* ptr, UINTN size);

	typedef AllocatorStatus GetStatusFunc();
	typedef VOID SetStatusFunc(AllocatorStatus status);


	/*
	Class for Memory allocation functions that will provide access for in the EFI and eventually the kernel new, new[] new(), new[](), delete and delete[] along with functions to move, copy and set memory
	class will act as an interface
	*/
	class Allocator
	{
	public:
		static VOID_PTR	Allocate(UINTN size);
		static VOID_PTR	AllocateZeroed(UINTN size);
		static VOID		Free(VOID_PTR ptr);
		
		static VOID_PTR	AllocatePage(UINTN pageCount);
		static VOID_PTR	AllocatePageZeroed(UINTN pageCount);
		static VOID		FreePage(VOID_PTR ptr, UINTN pageCount);
		
		static void SetAllocators(AllocFunc& allocFunc, AllocZeroedFunc& allocZeroFunc, AllocPageFunc& allocPageFunc, AllocPageZeroedFunc& allocPageZeroFunc, FreeFunc& freeFunc, FreePageFunc& freePageFunc, GetStatusFunc& getStatusFunc, SetStatusFunc& setStatusFunc);
		
		static BOOLEAN IsInitalized();
		static AllocatorStatus LastStatus();
	};

	
}

VOID_PTR CDECL operator new(UINTN size);
VOID_PTR CDECL operator new[](UINTN size);
VOID	 CDECL operator delete(VOID_PTR ptr);
VOID	 CDECL operator delete[](VOID_PTR ptr);

