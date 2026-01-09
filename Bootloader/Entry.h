#pragma once
#include <TypeDefs.h>
#include <EFI_HANDLE.h>
#include <EFI_STATUS.h>
#include <EFI_SYSTEM_TABLE.h>
#include <Protocols/IO/Peripheral/EFI_INPUT_KEY.h>

namespace Bootloader
{
	using namespace EFI;
	extern "C" EFI_STATUS EFIAPI EfiMain(EFI_HANDLE imgHndl, EFI_SYSTEM_TABLE * sysTbl);
}