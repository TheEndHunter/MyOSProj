#pragma once
#include <UEFIDef.h>
#include <EFI_SYSTEM_TABLE.h>
#include <EFI_STATUS.h>

namespace EFI
{
	class EFI_SYS_LIBS
	{
	public:
		static void FreePages(void* buffer, UINTN pages);
		static void FreePool(void* buffer);
		static void* AllocatePages(UINTN pages);
		static void* AllocatePlacedPool(UINTN size, EFI_PHYSICAL_ADDRESS memory);
		static void* AllocatePlacedZeroPool(UINTN size, EFI_PHYSICAL_ADDRESS memory);
		static void* AllocatePool(UINTN size);
		static void* AllocateZeroPool(UINTN size);
		static void* CopyMem(void* destination, void* source, UINTN length);
		static void* MoveMem(void* destination, void* source, UINTN length);
		static void* SetMem(void* buffer, UINTN size, UINT8 value);
		static void* ZeroMem(void* buffer, UINTN size);

		static void InitializeLib(EFI_HANDLE imageHandle, EFI_SYSTEM_TABLE* systemTable);

		static BOOLEAN IsInitialized();
		static EFI_STATUS LastStatus();

	};
}

void* CDECL operator new(UINTN size);
void* CDECL operator new[](UINTN size);
void CDECL operator delete(void* ptr);
void CDECL operator delete[](void* ptr);
void CDECL operator delete  (void* ptr, void* n);
void CDECL operator delete[](void* ptr, void* n);