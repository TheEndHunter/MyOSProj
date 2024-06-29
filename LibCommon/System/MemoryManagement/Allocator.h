#pragma once
#include <TypeDefs.h>
#include <System/MemoryManagement/EfiAllocator.h>
#include <System/MemoryManagement/KernelAllocator.h>
#include <System//MemoryManagement/AllocatorStatus.h>
#include <EFI_SYSTEM_TABLE.h>

namespace Common::System::MemoryManagement
{
	typedef VOID_PTR (*AllocFunc) (UINTN size);
	typedef VOID_PTR (*AllocZeroedFunc) (UINTN size);
	typedef VOID_PTR (*AllocPageFunc) (UINTN size);
	typedef VOID_PTR (*AllocPageZeroedFunc) (UINTN size);

	typedef VOID (*FreeFunc) (VOID_PTR ptr);
	typedef VOID (*FreePageFunc)(VOID* ptr, UINTN size);

	typedef AllocatorStatus GetStatusFunc();
	typedef VOID SetStatusFunc(AllocatorStatus status);

	/*
	Class for Memory allocation functions that will provide access for in the EFI and eventually the kernel new, new[] new(), new[](), delete and delete[] along with functions to move, copy and set memory
	class will act as an interface
	*/
	
	class Allocator
	{
		friend class EfiAllocator;
		friend class KernelAllocator;

	public:
		static VOID_PTR	Allocate(UINTN size);
		static VOID_PTR	AllocateZeroed(UINTN size);
		static VOID		Free(VOID_PTR ptr);
		static VOID_PTR	AllocatePage(UINTN pageCount);
		static VOID_PTR	AllocatePageZeroed(UINTN pageCount);
		static VOID		FreePage(VOID_PTR ptr, UINTN pageCount);
		
		static AllocatorStatus SetEfiAllocator(EFI::EFI_SYSTEM_TABLE* systemTable);
		static AllocatorStatus SetKernelAllocator(EFI::EFI_SYSTEM_TABLE* systemTable);
		
		template<typename Type>
		static Type* Allocate()
		{
			return (Type*)Allocate(sizeof(Type));
		}
		
		template<typename Type>
		static Type* AllocateArray(UINTN length)
		{

			return (Type*)Allocate(sizeof(Type) * length);
		}

		template<typename Type>
		static Type* AllocateZeroedArray(UINTN length)
		{
			return (Type*)AllocateZeroed(sizeof(Type)*length);
		}
		
		template<typename Type>
		static VOID Free(Type* ptr)
		{
			Free((VOID_PTR)ptr);
		}

		static BOOLEAN IsInitalized();
		static AllocatorStatus LastStatus();

	private:
		static AllocatorStatus* _lastStatus;
		
		static AllocFunc _allocFunc;
		static AllocZeroedFunc _allocZeroedFunc;
		static AllocPageFunc _allocPageFunc;
		static AllocPageZeroedFunc _allocPageZeroedFunc;
		static FreeFunc _freeFunc;
		static FreePageFunc _freePageFunc;
	};
}

/*Declare all overridable new and delete operator variants*/
VOID_PTR operator new(UINTN size);
VOID_PTR operator new[](UINTN size);
VOID_PTR operator new(UINTN size, VOID_PTR ptr);
VOID_PTR operator new[](UINTN size, VOID_PTR ptr);

void operator delete(VOID_PTR ptr);
void operator delete[](VOID_PTR ptr);
void operator delete(VOID_PTR ptr, UINTN size);
void operator delete[](VOID_PTR ptr, UINTN size);
void operator delete(VOID_PTR ptr, VOID_PTR ptr2);
void operator delete[](VOID_PTR ptr, VOID_PTR ptr2);
