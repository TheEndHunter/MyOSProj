#pragma once

#include "UEFIDef.h"
#include <Status.h>
#include <Guid.h>
#include "GraphicsOutputModeInformation.h"
#include "GraphicsOutputBLTPixel.h"
#include "GraphicsOutputBLTOperation.h"
#include "GraphicsOutputProtocolMode.h"

namespace Efi
{
	struct GraphicsOutputProtocol;

	constinit  const ALIGN(8) Efi::Guid GraphicsOutputProtocol_GUID = { 0x9042a9de, 0x23dc,0x4a38, { 0x96, 0xfb, 0x7a, 0xde, 0xd0, 0x80, 0x51, 0x6a }};

	typedef Status (EFIAPI* GraphicsOutputProtocolQueryMode) (IN GraphicsOutputProtocol* This,IN UINT32 Modenumber,OUT UINTN* SizeOfInfo, OUT GraphicsOutputModeInformation** Info);
	typedef Status (EFIAPI* GraphicsOutputProtocolSetMode) (IN GraphicsOutputProtocol* This, IN UINT32 Modenumber);

	typedef Status (EFIAPI* GraphicsOutputProtocolBlt) ( IN GraphicsOutputProtocol* This, IN OUT GraphicsOutputBLTPixel* BltBuffer,
		OPTIONAL IN GraphicsOutputBLTOperation BltOperation,IN UINTN SourceX,IN UINTN SourceY,IN UINTN DestinationX,IN UINTN DestinationY,IN UINTN Width,IN UINTN Height,
		IN UINTN Delta OPTIONAL);

	struct GraphicsOutputProtocol
	{
	public:
		GraphicsOutputProtocolQueryMode QueryMode;
		GraphicsOutputProtocolSetMode SetMode;
		GraphicsOutputProtocolBlt Blt;
		GraphicsOutputProtocolMode* Mode;
	};
}