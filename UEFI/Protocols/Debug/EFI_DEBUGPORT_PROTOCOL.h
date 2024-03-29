#pragma once
#include "UEFIDef.h"
#include <EFI_GUID.h>
#include <EFI_STATUS.h>

namespace EFI
{
	struct EFI_DEBUGPORT_PROTOCOL;

	constinit  const ALIGN(8) EFI::EFI_GUID EFI_DEBUGPORT_PROTOCOL_GUID = { 0xEBA4E8D2,0x3858,0x41EC, {0xA2,0x81,0x26,0x47,0xBA,0x96,0x60,0xD0} };
	const EFI_GUID DEVICE_PATH_MESSAGING_DEBUGPORT = EFI_DEBUGPORT_PROTOCOL_GUID;
	const EFI_GUID EFI_DEBUGPORT_VARIABLE_GUID = EFI_DEBUGPORT_PROTOCOL_GUID;
	const CHAR16* EFI_DEBUGPORT_VARIABLE_NAME = u"DEBUGPORT";

	typedef EFI_STATUS (EFIAPI* EFI_DEBUGPORT_RESET) (IN EFI_DEBUGPORT_PROTOCOL* This);

	typedef EFI_STATUS(EFIAPI* EFI_DEBUGPORT_WRITE) (IN EFI_DEBUGPORT_PROTOCOL* This,
		IN UINT32 Timeout, IN OUT UINTN* BufferSize,IN VOID* Buffer);
	
	typedef EFI_STATUS (EFIAPI* EFI_DEBUGPORT_READ) (IN EFI_DEBUGPORT_PROTOCOL* This,
		IN UINT32 Timeout, IN OUT UINTN* BufferSize, OUT VOID* Buffer);

	typedef EFI_STATUS(EFIAPI* EFI_DEBUGPORT_POLL) (IN EFI_DEBUGPORT_PROTOCOL* This);

	struct EFI_DEBUGPORT_PROTOCOL
	{
	public:
		EFI_DEBUGPORT_RESET Reset;
		EFI_DEBUGPORT_WRITE Write;
		EFI_DEBUGPORT_READ Read;
		EFI_DEBUGPORT_POLL Poll;
	} ;
}