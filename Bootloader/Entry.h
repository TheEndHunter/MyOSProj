#pragma once
#include <TypeDefs.h>
#include <EFI_HANDLE.h>
#include <EFI_STATUS.h>
#include <EFI_SYSTEM_TABLE.h>
#include <Protocols/IO/Peripheral/EFI_INPUT_KEY.h>

namespace Bootloader
{
	using namespace EFI;

	static void PrintInfo(EFI_SYSTEM_TABLE* sysTbl, UINT8 color, const CHAR16* errorMessage, EFI_STATUS status = EFI_STATUS::SUCCESS);
	static void PrintDebug(EFI_SYSTEM_TABLE* sysTbl, const CHAR16* errorMessage, EFI_STATUS status = EFI_STATUS::SUCCESS);
	static void PrintError(EFI_SYSTEM_TABLE* sysTbl, const CHAR16* errorMessage, EFI_STATUS status = EFI_STATUS::SUCCESS);
	static NORETURN void ThrowException(EFI_SYSTEM_TABLE* sysTbl, EFI_HANDLE imgHndl, const CHAR16* errorMessage, EFI_STATUS status);

	static NORETURN void Exit(EFI_SYSTEM_TABLE* sysTable, EFI_HANDLE imgHndl, EFI_STATUS Status = EFI_STATUS::SUCCESS, UINTN exitDataSize = 0, CHAR16* exitData = nullptr);
	
	static EFI_INPUT_KEY WaitForKey(EFI_SYSTEM_TABLE* sysTable);

	EFI_STATUS EfiMain(EFI_HANDLE imgHndl, EFI_SYSTEM_TABLE* sysTbl);
}
