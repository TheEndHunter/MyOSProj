#include "GraphicsContext.h"
#include <UEFIDef.h>
#include <EFI_STATUS.h>
#include <EFI_HANDLE.h>
#include <EFI_SYSTEM_TABLE.h>
#include <Protocols/Graphics/EFI_GRAPHICS_OUTPUT_PROTOCOL.h>
#include <Protocols/Graphics/EFI_GRAPHICS_OUTPUT_BLT_PIXEL.h>
#include <EFI_LOCATE_SEARCH_TYPE.h>
#include <EFI_BOOT_SERVICES.h>
#include <Protocols/Graphics/EFI_GRAPHICS_OUTPUT_BLT_OPERATION.h>
#include <Protocols/Graphics/EFI_GRAPHICS_OUTPUT_MODE_INFORMATION.h>
#include <EFI_MEMORY_TYPE.h>

namespace Bootloader::Graphics
{
	using namespace EFI;

	EFI::EFI_STATUS GraphicsContext::Initialize(EFI::EFI_HANDLE hnd, EFI::EFI_SYSTEM_TABLE* sysTable)
	{
		if (gop != nullptr)
		{
			return EFI::EFI_STATUS::SUCCESS;
		}

		return sysTable->BootServices->OpenProtocol(sysTable->ConsoleOutHandle, &EFI_GRAPHICS_OUTPUT_PROTOCOL_GUID, (void**)&gop, hnd, nullptr, EFI_OPEN_PROTOCOL_BY_HANDLE_PROTOCOL);
	}

	EFI::EFI_STATUS GraphicsContext::Terminate(EFI::EFI_HANDLE hnd, EFI::EFI_SYSTEM_TABLE* sysTable)
	{
		if (gop == nullptr)
		{
			return EFI::EFI_STATUS::SUCCESS;
		}

		return sysTable->BootServices->CloseProtocol(sysTable->ConsoleOutHandle, &EFI_GRAPHICS_OUTPUT_PROTOCOL_GUID, hnd, nullptr);
	}

	void GraphicsContext::SetForegroundPixel(UINTN xPos, UINTN yPos)
	{
		*(EFI_GRAPHICS_OUTPUT_BLT_PIXEL*)(gop->Mode->FrameBufferBase + (yPos * (UINTN)(gop->Mode->Info->HorizontalResolution) + xPos)) = CurrentForeground;
	}

	void GraphicsContext::SetForegroundPixel(UINTN xPos, UINTN yPos, EFI::EFI_GRAPHICS_OUTPUT_BLT_PIXEL* color)
	{
		CurrentForeground = *color;
		*(EFI_GRAPHICS_OUTPUT_BLT_PIXEL*)(gop->Mode->FrameBufferBase + (yPos * (UINTN)(gop->Mode->Info->HorizontalResolution) + xPos)) = CurrentForeground;
	}

	void GraphicsContext::SetForegroundPixel(UINTN xPos, UINTN yPos, UINT8 r, UINT8 g, UINT8 b, UINT8 a)
	{
		CurrentForeground = EFI::EFI_GRAPHICS_OUTPUT_BLT_PIXEL{ b, g, r, a };
		*(EFI_GRAPHICS_OUTPUT_BLT_PIXEL*)(gop->Mode->FrameBufferBase + (yPos * (UINTN)(gop->Mode->Info->HorizontalResolution) + xPos)) = CurrentForeground;
	}

	void GraphicsContext::SetForegroundPixel(UINTN xPos, UINTN yPos, UINT32 color)
	{
		CurrentForeground = EFI::EFI_GRAPHICS_OUTPUT_BLT_PIXEL{ (UINT8)(color >> 16), (UINT8)(color >> 8), (UINT8)(color), (UINT8)(color >> 24) };
		*(EFI_GRAPHICS_OUTPUT_BLT_PIXEL*)(gop->Mode->FrameBufferBase + (yPos * (UINTN)(gop->Mode->Info->HorizontalResolution) + xPos)) = CurrentForeground;
	}

	void GraphicsContext::SetBackgroundPixel(UINTN xPos, UINTN yPos)
	{
		*(EFI_GRAPHICS_OUTPUT_BLT_PIXEL*)(gop->Mode->FrameBufferBase + (yPos * (UINTN)(gop->Mode->Info->HorizontalResolution) + xPos)) = CurrentBackground;
	}

	void GraphicsContext::SetBackgroundPixel(UINTN xPos, UINTN yPos, EFI::EFI_GRAPHICS_OUTPUT_BLT_PIXEL* color)
	{
		CurrentBackground = *color;
		*(EFI_GRAPHICS_OUTPUT_BLT_PIXEL*)(gop->Mode->FrameBufferBase + (yPos * (UINTN)(gop->Mode->Info->HorizontalResolution) + xPos)) = CurrentBackground;
	}

	void GraphicsContext::SetBackgroundPixel(UINTN xPos, UINTN yPos, UINT8 r, UINT8 g, UINT8 b, UINT8 a)
	{
		CurrentBackground = EFI::EFI_GRAPHICS_OUTPUT_BLT_PIXEL{ b, g, r, a };
		*(EFI_GRAPHICS_OUTPUT_BLT_PIXEL*)(gop->Mode->FrameBufferBase + (yPos * (UINTN)(gop->Mode->Info->HorizontalResolution) + xPos)) = CurrentBackground;
	}

	void GraphicsContext::SetBackgroundPixel(UINTN xPos, UINTN yPos, UINT32 color)
	{
		CurrentBackground = EFI::EFI_GRAPHICS_OUTPUT_BLT_PIXEL{ (UINT8)(color >> 16), (UINT8)(color >> 8), (UINT8)(color), (UINT8)(color >> 24) };
		*(EFI_GRAPHICS_OUTPUT_BLT_PIXEL*)(gop->Mode->FrameBufferBase + (yPos * (UINTN)(gop->Mode->Info->HorizontalResolution) + xPos)) = CurrentBackground;
	}

	void GraphicsContext::ClearScreen()
	{
		gop->Blt(gop, &CurrentBackground, EFI::EFI_GRAPHICS_OUTPUT_BLT_OPERATION::EfiBltVideoFill, 0, 0, 0, 0, gop->Mode->Info->HorizontalResolution, gop->Mode->Info->VerticalResolution, 0);
	}

	void GraphicsContext::ClearScreen(EFI::EFI_GRAPHICS_OUTPUT_BLT_PIXEL* color)
	{
		CurrentBackground = *color;
		gop->Blt(gop, color, EFI::EFI_GRAPHICS_OUTPUT_BLT_OPERATION::EfiBltVideoFill, 0, 0, 0, 0, gop->Mode->Info->HorizontalResolution, gop->Mode->Info->VerticalResolution, 0);
	}

	void GraphicsContext::ClearScreen(UINT8 r, UINT8 g, UINT8 b, UINT8 a)
	{
		CurrentBackground = EFI::EFI_GRAPHICS_OUTPUT_BLT_PIXEL{ b, g, r, a };
		gop->Blt(gop, &CurrentBackground, EFI::EFI_GRAPHICS_OUTPUT_BLT_OPERATION::EfiBltVideoFill, 0, 0, 0, 0, gop->Mode->Info->HorizontalResolution, gop->Mode->Info->VerticalResolution, 0);
	}

	void GraphicsContext::ClearScreen(UINT32 color)
	{
		CurrentBackground = EFI::EFI_GRAPHICS_OUTPUT_BLT_PIXEL{ (UINT8)(color >> 16), (UINT8)(color >> 8), (UINT8)(color), (UINT8)(color >> 24) };
		gop->Blt(gop, &CurrentBackground, EFI::EFI_GRAPHICS_OUTPUT_BLT_OPERATION::EfiBltVideoFill, 0, 0, 0, 0, gop->Mode->Info->HorizontalResolution, gop->Mode->Info->VerticalResolution, 0);
	}

	void GraphicsContext::DrawRectangle(UINTN xPos, UINTN yPos, UINTN width, UINTN height)
	{
		gop->Blt(gop, &CurrentForeground, EFI::EFI_GRAPHICS_OUTPUT_BLT_OPERATION::EfiBltVideoFill, 0, 0, xPos, yPos, width, height, 0);
	}

	void GraphicsContext::DrawRectangle(UINTN xPos, UINTN yPos, UINTN width, UINTN height, EFI::EFI_GRAPHICS_OUTPUT_BLT_PIXEL* color)
	{
		CurrentForeground = *color;
		gop->Blt(gop, color, EFI::EFI_GRAPHICS_OUTPUT_BLT_OPERATION::EfiBltVideoFill, 0, 0, xPos, yPos, width, height, 0);
	}

	void GraphicsContext::DrawRectangle(UINTN xPos, UINTN yPos, UINTN width, UINTN height, UINT8 r, UINT8 g, UINT8 b, UINT8 a)
	{
		CurrentForeground = EFI::EFI_GRAPHICS_OUTPUT_BLT_PIXEL{ b, g, r, a };
		gop->Blt(gop, &CurrentForeground, EFI::EFI_GRAPHICS_OUTPUT_BLT_OPERATION::EfiBltVideoFill, 0, 0, xPos, yPos, width, height, 0);
	}

	void GraphicsContext::DrawRectangle(UINTN xPos, UINTN yPos, UINTN width, UINTN height, UINT32 color)
	{
		CurrentForeground = EFI::EFI_GRAPHICS_OUTPUT_BLT_PIXEL{ (UINT8)(color >> 16), (UINT8)(color >> 8), (UINT8)(color), (UINT8)(color >> 24) };
		gop->Blt(gop, &CurrentForeground, EFI::EFI_GRAPHICS_OUTPUT_BLT_OPERATION::EfiBltVideoFill, 0, 0, xPos, yPos, width, height, 0);
	}

	void GraphicsContext::SetBackground(EFI::EFI_GRAPHICS_OUTPUT_BLT_PIXEL* color)
	{
		CurrentBackground = *color;
	}

	void GraphicsContext::SetBackground(UINT8 r, UINT8 g, UINT8 b, UINT8 a)
	{
		CurrentBackground = EFI::EFI_GRAPHICS_OUTPUT_BLT_PIXEL{ b, g, r, a };
	}

	void GraphicsContext::SetBackground(UINT32 color)
	{
		CurrentBackground = EFI::EFI_GRAPHICS_OUTPUT_BLT_PIXEL{ (UINT8)(color >> 16), (UINT8)(color >> 8), (UINT8)(color), (UINT8)(color >> 24) };
	}

	void GraphicsContext::SetForeground(EFI::EFI_GRAPHICS_OUTPUT_BLT_PIXEL* color)
	{
		CurrentForeground = *color;
	}

	void GraphicsContext::SetForeground(UINT8 r, UINT8 g, UINT8 b, UINT8 a)
	{
		CurrentForeground = EFI::EFI_GRAPHICS_OUTPUT_BLT_PIXEL{ b, g, r, a };
	}

	void GraphicsContext::SetForeground(UINT32 color)
	{
		CurrentForeground = EFI::EFI_GRAPHICS_OUTPUT_BLT_PIXEL{ (UINT8)(color >> 16), (UINT8)(color >> 8), (UINT8)(color), (UINT8)(color >> 24) };
	}

	EFI::EFI_GRAPHICS_OUTPUT_BLT_PIXEL GraphicsContext::GetBackground() const
	{
		return CurrentBackground;
	}

	EFI::EFI_GRAPHICS_OUTPUT_BLT_PIXEL GraphicsContext::GetForeground() const
	{
		return CurrentForeground;
	}

	EFI::EFI_STATUS GraphicsContext::SetMode(UINT32 modeNumber)
	{
		if (modeNumber >= gop->Mode->MaxMode)
		{
			return EFI::EFI_STATUS::UNSUPPORTED;
		}

		return gop->SetMode(gop, modeNumber);
	}

	EFI::EFI_STATUS GraphicsContext::QueryMode(UINT32 modeNumber, OUT UINTN* size, OUT EFI::EFI_GRAPHICS_OUTPUT_MODE_INFORMATION* info)
	{
		if (modeNumber >= gop->Mode->MaxMode)
		{
			return EFI::EFI_STATUS::UNSUPPORTED;
		}

		return gop->QueryMode(gop, modeNumber, size, (EFI_GRAPHICS_OUTPUT_MODE_INFORMATION**)info);
	}

	UINT32 GraphicsContext::GetModeCount()
	{
		return gop->Mode->MaxMode;
	}

	UINT32 GraphicsContext::GetCurrentMode()
	{
		return gop->Mode->Mode;
	}

	UINTN GraphicsContext::GetWidth()
	{
		return gop->Mode->Info->HorizontalResolution;
	}

	UINTN GraphicsContext::GetHeight()
	{
		return gop->Mode->Info->VerticalResolution;
	}

	GraphicsContext::GraphicsContext()
	{
		gop = nullptr;
		CurrentBackground = EFI::EFI_GRAPHICS_OUTPUT_BLT_PIXEL{0x00, 0x00, 0x00, 0xFF};
		CurrentForeground = EFI::EFI_GRAPHICS_OUTPUT_BLT_PIXEL(0xFF, 0xFF, 0xFF, 0xFF);
	};
}