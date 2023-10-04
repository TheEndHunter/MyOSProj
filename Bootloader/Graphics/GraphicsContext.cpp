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
#include <Enviroment/StringHelpers.h>
#include <Console.h>


namespace Bootloader::Graphics
{
	using namespace EFI;

	EFI::EFI_STATUS GraphicsContext::Initialize(EFI::EFI_HANDLE hnd, EFI::EFI_SYSTEM_TABLE* sysTable)
	{
		if (gop != nullptr)
		{
			return EFI::EFI_STATUS::SUCCESS;
		}

		// Locate the GOP protocol and store it in the gop variable, use locate protocol first then try to locate handle Buffer if that fails, if that fails then return the error

		EFI::EFI_STATUS status = sysTable->BootServices->LocateProtocol(&EFI_GRAPHICS_OUTPUT_PROTOCOL_GUID, nullptr, (void**)&gop);

		if (status != EFI::EFI_STATUS::SUCCESS)
		{
			UINTN handleCount = 0;
			EFI::EFI_HANDLE* handleBuffer;

			status = sysTable->BootServices->LocateHandleBuffer(EFI_LOCATE_SEARCH_TYPE::ByProtocol, &EFI_GRAPHICS_OUTPUT_PROTOCOL_GUID, nullptr, &handleCount, &handleBuffer);
			
			sysTable->ConOut->OutputString(sysTable->ConOut, Enviroment::StringHelpers::ToString(handleCount) );

			if (status != EFI::EFI_STATUS::SUCCESS)
			{
				return status;
			}

			status = sysTable->BootServices->OpenProtocol(handleBuffer[0], &EFI_GRAPHICS_OUTPUT_PROTOCOL_GUID, (void**)&gop, hnd, nullptr, EFI::EFI_OPEN_PROTOCOL_GET_PROTOCOL);

			sysTable->BootServices->FreePool(handleBuffer);
		}

			return status;
	};

	EFI::EFI_STATUS GraphicsContext::Terminate(EFI::EFI_HANDLE hnd, EFI::EFI_SYSTEM_TABLE* sysTable)
	{
		if (gop == nullptr)
		{
			return EFI::EFI_STATUS::SUCCESS;
		}

		return sysTable->BootServices->CloseProtocol(sysTable->ConsoleOutHandle, &EFI_GRAPHICS_OUTPUT_PROTOCOL_GUID, hnd, nullptr);
	};

	void GraphicsContext::SetForegroundPixel(UINTN xPos, UINTN yPos)
	{
		*(EFI_GRAPHICS_OUTPUT_BLT_PIXEL*)(gop->Mode->FrameBufferBase + (yPos * (UINTN)(gop->Mode->Info->HorizontalResolution) + xPos)) = CurrentForeground;
	};

	void GraphicsContext::SetForegroundPixel(UINTN xPos, UINTN yPos, EFI::EFI_GRAPHICS_OUTPUT_BLT_PIXEL* rgba)
	{
		CurrentForeground = *rgba;
		*(EFI_GRAPHICS_OUTPUT_BLT_PIXEL*)(gop->Mode->FrameBufferBase + (yPos * (UINTN)(gop->Mode->Info->HorizontalResolution) + xPos)) = CurrentForeground;
	};

	void GraphicsContext::SetForegroundPixel(UINTN xPos, UINTN yPos, UINT8 r, UINT8 g, UINT8 b, UINT8 a)
	{
		CurrentForeground = EFI::EFI_GRAPHICS_OUTPUT_BLT_PIXEL{ b, g, r, a };
		*(EFI_GRAPHICS_OUTPUT_BLT_PIXEL*)(gop->Mode->FrameBufferBase + (yPos * (UINTN)(gop->Mode->Info->HorizontalResolution) + xPos)) = CurrentForeground;
	};

	void GraphicsContext::SetForegroundPixel(UINTN xPos, UINTN yPos, UINT32 rgba)
	{
		CurrentForeground = EFI::EFI_GRAPHICS_OUTPUT_BLT_PIXEL{ (UINT8)(rgba >> 16), (UINT8)(rgba >> 8), (UINT8)(rgba), (UINT8)(rgba >> 24) };
		*(EFI_GRAPHICS_OUTPUT_BLT_PIXEL*)(gop->Mode->FrameBufferBase + (yPos * (UINTN)(gop->Mode->Info->HorizontalResolution) + xPos)) = CurrentForeground;
	};

	void GraphicsContext::SetBackgroundPixel(UINTN xPos, UINTN yPos)
	{
		*(EFI_GRAPHICS_OUTPUT_BLT_PIXEL*)(gop->Mode->FrameBufferBase + (yPos * (UINTN)(gop->Mode->Info->HorizontalResolution) + xPos)) = CurrentBackground;
	};

	void GraphicsContext::SetBackgroundPixel(UINTN xPos, UINTN yPos, EFI::EFI_GRAPHICS_OUTPUT_BLT_PIXEL* rgba)
	{
		CurrentBackground = *rgba;
		*(EFI_GRAPHICS_OUTPUT_BLT_PIXEL*)(gop->Mode->FrameBufferBase + (yPos * (UINTN)(gop->Mode->Info->HorizontalResolution) + xPos)) = CurrentBackground;
	};

	void GraphicsContext::SetBackgroundPixel(UINTN xPos, UINTN yPos, UINT8 r, UINT8 g, UINT8 b, UINT8 a)
	{
		CurrentBackground = EFI::EFI_GRAPHICS_OUTPUT_BLT_PIXEL{ b, g, r, a };
		*(EFI_GRAPHICS_OUTPUT_BLT_PIXEL*)(gop->Mode->FrameBufferBase + (yPos * (UINTN)(gop->Mode->Info->HorizontalResolution) + xPos)) = CurrentBackground;
	};

	void GraphicsContext::SetBackgroundPixel(UINTN xPos, UINTN yPos, UINT32 rgba)
	{
		CurrentBackground = EFI::EFI_GRAPHICS_OUTPUT_BLT_PIXEL{ (UINT8)(rgba >> 16), (UINT8)(rgba >> 8), (UINT8)(rgba), (UINT8)(rgba >> 24) };
		*(EFI_GRAPHICS_OUTPUT_BLT_PIXEL*)(gop->Mode->FrameBufferBase + (yPos * (UINTN)(gop->Mode->Info->HorizontalResolution) + xPos)) = CurrentBackground;
	};

	void GraphicsContext::ClearScreen()
	{
		gop->Blt(gop, &CurrentBackground, EFI::EFI_GRAPHICS_OUTPUT_BLT_OPERATION::EfiBltVideoFill, 0, 0, 0, 0, gop->Mode->Info->HorizontalResolution, gop->Mode->Info->VerticalResolution, 0);
	};

	void GraphicsContext::ClearScreen(EFI::EFI_GRAPHICS_OUTPUT_BLT_PIXEL* rgba)
	{
		CurrentBackground = *rgba;
		gop->Blt(gop, rgba, EFI::EFI_GRAPHICS_OUTPUT_BLT_OPERATION::EfiBltVideoFill, 0, 0, 0, 0, gop->Mode->Info->HorizontalResolution, gop->Mode->Info->VerticalResolution, 0);
	};

	void GraphicsContext::ClearScreen(UINT8 r, UINT8 g, UINT8 b, UINT8 a)
	{
		CurrentBackground = EFI::EFI_GRAPHICS_OUTPUT_BLT_PIXEL{ b, g, r, a };
		gop->Blt(gop, &CurrentBackground, EFI::EFI_GRAPHICS_OUTPUT_BLT_OPERATION::EfiBltVideoFill, 0, 0, 0, 0, gop->Mode->Info->HorizontalResolution, gop->Mode->Info->VerticalResolution, 0);
	};

	void GraphicsContext::ClearScreen(UINT32 rgba)
	{
		CurrentBackground = EFI::EFI_GRAPHICS_OUTPUT_BLT_PIXEL{ (UINT8)(rgba >> 16), (UINT8)(rgba >> 8), (UINT8)(rgba), (UINT8)(rgba >> 24) };
		gop->Blt(gop, &CurrentBackground, EFI::EFI_GRAPHICS_OUTPUT_BLT_OPERATION::EfiBltVideoFill, 0, 0, 0, 0, gop->Mode->Info->HorizontalResolution, gop->Mode->Info->VerticalResolution, 0);
	};

	void GraphicsContext::DrawRectangle(UINTN xPos, UINTN yPos, UINTN width, UINTN height)
	{
		gop->Blt(gop, &CurrentForeground, EFI::EFI_GRAPHICS_OUTPUT_BLT_OPERATION::EfiBltVideoFill, 0, 0, xPos, yPos, width, height, 0);
	};

	void GraphicsContext::DrawRectangle(UINTN xPos, UINTN yPos, UINTN width, UINTN height, EFI::EFI_GRAPHICS_OUTPUT_BLT_PIXEL* rgba)
	{
		CurrentForeground = *rgba;
		gop->Blt(gop, rgba, EFI::EFI_GRAPHICS_OUTPUT_BLT_OPERATION::EfiBltVideoFill, 0, 0, xPos, yPos, width, height, 0);
	};

	void GraphicsContext::DrawRectangle(UINTN xPos, UINTN yPos, UINTN width, UINTN height, UINT8 r, UINT8 g, UINT8 b, UINT8 a)
	{
		CurrentForeground = EFI::EFI_GRAPHICS_OUTPUT_BLT_PIXEL{ b, g, r, a };
		gop->Blt(gop, &CurrentForeground, EFI::EFI_GRAPHICS_OUTPUT_BLT_OPERATION::EfiBltVideoFill, 0, 0, xPos, yPos, width, height, 0);
	};

	void GraphicsContext::DrawRectangle(UINTN xPos, UINTN yPos, UINTN width, UINTN height, UINT32 rgba)
	{
		CurrentForeground = EFI::EFI_GRAPHICS_OUTPUT_BLT_PIXEL{ (UINT8)(rgba >> 16), (UINT8)(rgba >> 8), (UINT8)(rgba), (UINT8)(rgba >> 24) };
		gop->Blt(gop, &CurrentForeground, EFI::EFI_GRAPHICS_OUTPUT_BLT_OPERATION::EfiBltVideoFill, 0, 0, xPos, yPos, width, height, 0);
	};

	void GraphicsContext::SetBackground(EFI::EFI_GRAPHICS_OUTPUT_BLT_PIXEL* rgba)
	{
		CurrentBackground = *rgba;
	};

	void GraphicsContext::SetBackground(UINT8 r, UINT8 g, UINT8 b, UINT8 a)
	{
		CurrentBackground = EFI::EFI_GRAPHICS_OUTPUT_BLT_PIXEL{ b, g, r, a };
	};

	void GraphicsContext::SetBackground(UINT32 rgba)
	{
		CurrentBackground = EFI::EFI_GRAPHICS_OUTPUT_BLT_PIXEL{ (UINT8)(rgba >> 16), (UINT8)(rgba >> 8), (UINT8)(rgba), (UINT8)(rgba >> 24) };
	};

	void GraphicsContext::SetForeground(EFI::EFI_GRAPHICS_OUTPUT_BLT_PIXEL* rgba)
	{
		CurrentForeground = *rgba;
	};

	void GraphicsContext::SetForeground(UINT8 r, UINT8 g, UINT8 b, UINT8 a)
	{
		CurrentForeground = EFI::EFI_GRAPHICS_OUTPUT_BLT_PIXEL{ b, g, r, a };
	};

	void GraphicsContext::SetForeground(UINT32 rgba)
	{
		CurrentForeground = EFI::EFI_GRAPHICS_OUTPUT_BLT_PIXEL{ (UINT8)(rgba >> 16), (UINT8)(rgba >> 8), (UINT8)(rgba), (UINT8)(rgba >> 24) };
	};

	EFI::EFI_GRAPHICS_OUTPUT_BLT_PIXEL GraphicsContext::GetBackground() const
	{
		return CurrentBackground;
	};

	EFI::EFI_GRAPHICS_OUTPUT_BLT_PIXEL GraphicsContext::GetForeground() const
	{
		return CurrentForeground;
	};

	EFI::EFI_STATUS GraphicsContext::SetMode(UINT32 modeNumber)
	{
		if (modeNumber >= gop->Mode->MaxMode)
		{
			return EFI::EFI_STATUS::UNSUPPORTED;
		}

		return gop->SetMode(gop, modeNumber);
	};

	EFI::EFI_STATUS GraphicsContext::QueryMode(UINT32 modeNumber, OUT UINTN* size, OUT EFI::EFI_GRAPHICS_OUTPUT_MODE_INFORMATION* info)
	{
		if (modeNumber >= gop->Mode->MaxMode)
		{
			return EFI::EFI_STATUS::UNSUPPORTED;
		}

		return gop->QueryMode(gop, modeNumber, size, (EFI_GRAPHICS_OUTPUT_MODE_INFORMATION**)info);
	};

	UINT32 GraphicsContext::GetModeCount()
	{
		return gop->Mode->MaxMode;
	};

	UINT32 GraphicsContext::GetCurrentMode()
	{
		return gop->Mode->Mode;
	};

	UINTN GraphicsContext::GetWidth()
	{
		return gop->Mode->Info->HorizontalResolution;
	};

	UINTN GraphicsContext::GetHeight()
	{
		return gop->Mode->Info->VerticalResolution;
	};

	GraphicsContext::GraphicsContext()
	{
		gop = nullptr;
		CurrentBackground = EFI::EFI_GRAPHICS_OUTPUT_BLT_PIXEL{0x00, 0x00, 0x00, 0xFF};
		CurrentForeground = EFI::EFI_GRAPHICS_OUTPUT_BLT_PIXEL(0xFF, 0xFF, 0xFF, 0xFF);
	};

};