#pragma once
#include <TypeDefs.h>
#include <System/MemoryManagement/EfiAllocator.h>
#include <System/MemoryManagement/KernelAllocator.h>
#include <System//MemoryManagement/AllocatorStatus.h>
#include <EFI_SYSTEM_TABLE.h>
#include <Debugging/Debugger.h>

namespace Common::System::MemoryManagement
{
	typedef VOID_PTR (*AllocFunc) (UINTN length);
	typedef VOID_PTR (*AllocZeroedFunc) (UINTN length);
	typedef VOID_PTR (*AllocPageFunc) (UINTN length);
	typedef VOID_PTR (*AllocPageZeroedFunc) (UINTN length);

	typedef VOID (*FreeFunc) (VOID_PTR ptr);
	typedef VOID (*FreePageFunc)(VOID* ptr, UINTN length);

	typedef AllocatorStatus GetStatusFunc();
	typedef VOID SetStatusFunc(AllocatorStatus status);

	/*
	Class for Memory allocation functions that will provide access for in the EFI and eventually the kernel new, new[] new(), new[](), delete and delete[] along with functions to move, copy and set memory
	class will act as an interface
	*/
	
	class Allocator
	{
		friend class Allocator;
		friend class EfiAllocator;
		friend class KernelAllocator;
	private:
		Allocator(AllocatorStatus* allocStatus,AllocFunc allocFunc, AllocZeroedFunc allocZeroedFunc, AllocPageFunc allocPageFunc, AllocPageZeroedFunc allocPageZeroedFunc, FreeFunc freeFunc,FreePageFunc freePageFunc);
	public:
		static void SetDebugger(Debugging::Debugger* debugger);
		Allocator();
		static  Allocator* GetInstance();
		static AllocatorStatus SetWithExistingAllocator(Allocator* allocator);
		static AllocatorStatus SetEfiAllocator(EFI::EFI_SYSTEM_TABLE* systemTable);
		static AllocatorStatus SetKernelAllocator(EFI::EFI_SYSTEM_TABLE* systemTable);

		VOID_PTR	Allocate(UINTN length);
		VOID_PTR	AllocateZeroed(UINTN length);
		VOID		Free(VOID_PTR ptr);
		VOID_PTR	AllocatePage(UINTN pageCount);
		VOID_PTR	AllocatePageZeroed(UINTN pageCount);
		VOID		FreePage(VOID_PTR ptr, UINTN pageCount);
		template<typename Type>
		Type* Allocate()
		{
			return (Type*)Allocate(sizeof(Type));
		}
		
		template<typename Type>
		Type* AllocateArray(UINTN length)
		{

			return (Type*)Allocate(sizeof(Type) * length);
		}

		template<typename Type>
		Type* AllocateZeroedArray(UINTN length)
		{
			return (Type*)AllocateZeroed(sizeof(Type)*length);
		}
		
		template<typename Type>
		VOID Free(Type* ptr)
		{
			Free((VOID_PTR)ptr);
		}

		BOOLEAN IsInitalized();
		AllocatorStatus LastStatus();

	protected:
		BOOLEAN _initialized;
		AllocatorStatus* _lastStatus;
		
		AllocFunc _allocFunc;
		AllocZeroedFunc _allocZeroedFunc;
		AllocPageFunc _allocPageFunc;
		AllocPageZeroedFunc _allocPageZeroedFunc;
		FreeFunc _freeFunc;
		FreePageFunc _freePageFunc;
	};
}

/*Declare all overridable new and delete operator variants*/
API_DLL VOID_PTR  operator new(UINTN length);
API_DLL VOID_PTR operator new[](UINTN length);
API_DLL VOID_PTR operator new(UINTN length, VOID_PTR ptr);
API_DLL VOID_PTR operator new[](UINTN length, VOID_PTR ptr);

API_DLL void operator delete(VOID_PTR ptr);
API_DLL void operator delete[](VOID_PTR ptr);
API_DLL void operator delete(VOID_PTR ptr, UINTN length);
API_DLL void operator delete[](VOID_PTR ptr, UINTN length);
API_DLL void operator delete(VOID_PTR ptr, VOID_PTR ptr2);
API_DLL void operator delete[](VOID_PTR ptr, VOID_PTR ptr2);
