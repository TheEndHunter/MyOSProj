#pragma once

#include "UEFIDef.h"
#include <Status.h>
#include <Guid.h>
#include "StopBitsType.h"
#include "ParityType.h"
#include "SerialControlBits.h"
#include "SerialIOMode.h"

namespace Efi
{
    struct SerialIOProtocol;

    constinit  const ALIGN(8) Efi::Guid SerialIOProtocolGuid =          { 0xBB25CF6F, 0xF1D4, 0x11D2, {0x9a, 0x0c, 0x00, 0x90, 0x27, 0x3f, 0xc1, 0xfd}};
    constinit  const ALIGN(8) Efi::Guid SerialTerminalDeviceTypeGuid = { 0x6ad9a60f, 0x5815, 0x4c7c, {0x8a, 0x10, 0x50, 0x53, 0xd2, 0xbf, 0x7a, 0x1b} };

    const UINT32 SerialIOProtocolRevision = 0x00010000;
    const UINT32 SerialIOProtocolRevision1p1 = 0x00010001;

     typedef Status (EFIAPI* SerialResetFunc)(SerialIOProtocol* This);

     typedef Status (EFIAPI* SerialSetAttributesFunc)(SerialIOProtocol* This,
         UINT64 BaudRate, UINT32 ReceiveFifoDepth, UINT32 Timeout,
         ParityType Parity, UINT8 DataBits, StopBitsType StopBits);

     typedef Status (EFIAPI* SerialSetControlBitsFunc)(SerialIOProtocol* This,
         SerialControlBits Control);

     typedef Status (EFIAPI* SerialGetControlBitsFunc)(SerialIOProtocol* This,
         SerialControlBits* Control);

     typedef Status (EFIAPI* SerialWriteFunc)(SerialIOProtocol* This,
         UINTN* BufferSize, VOID* Buffer);

     typedef Status (EFIAPI* SerialReadFunc)(SerialIOProtocol* This,
         UINTN* BufferSize, VOID* Buffer);

     struct SerialIOProtocol
	 {
	 public:
		 UINT32 Revision;
         SerialResetFunc Reset;
         SerialSetAttributesFunc SetAttributes;
         SerialSetControlBitsFunc SetControl;
         SerialGetControlBitsFunc GetControl;
         SerialWriteFunc Write;
         SerialReadFunc Read;
         SerialIOMode* Mode;
		 CONST Guid* DeviceTypeGuid; // Revision 1.1
	 };
}
