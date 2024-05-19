#include <EFI_STATUS.h>
#include <EFI_HANDLE.h>
#include <EFI_SYSTEM_TABLE.h>
#include <Protocols/Graphics/EFI_GRAPHICS_OUTPUT_PROTOCOL.h>
#include <Protocols/Graphics/EFI_GRAPHICS_OUTPUT_BLT_PIXEL.h>
#include <EFI_LOCATE_SEARCH_TYPE.h>
#include <EFI_BOOT_SERVICES.h>
#include <Protocols/Graphics/EFI_GRAPHICS_OUTPUT_BLT_OPERATION.h>
#include <Protocols/Graphics/EFI_GRAPHICS_OUTPUT_MODE_INFORMATION.h>
#include <Environment/Unicode.h>
#include "GraphicsContext.h"
#include <Numerics/Math.h>

using namespace Common::Numerics;

namespace Common::Graphics
{
	using namespace EFI;

	/*static EFI_INPUT_KEY __WaitForKey(EFI_SYSTEM_TABLE* sysTable)
	{
		EFI_INPUT_KEY key;
		while (sysTable->ConIn->ReadKeyStroke(sysTable->ConIn, &key) == EFI_STATUS::NOT_READY)
		{
			sysTable->BootServices->Stall(1000);
		}
		sysTable->ConIn->Reset(sysTable->ConIn, false);
		return key;
	}*/

	EFI::EFI_STATUS Graphics::GraphicsContext::LastStatus = EFI::EFI_STATUS::SUCCESS;
	GraphicsContext GraphicsContext::Initialize(EFI::EFI_HANDLE hnd, EFI::EFI_SYSTEM_TABLE* sysTable)
	{
		EFI_GRAPHICS_OUTPUT_PROTOCOL* gop = nullptr;
		// Locate the GOP protocol and store it in the gop variable, use locate protocol first then try to locate handle Buffer if that fails, if that fails then return the error
		LastStatus = sysTable->BootServices->LocateProtocol(&EFI_GRAPHICS_OUTPUT_PROTOCOL_GUID, nullptr, (void**)&gop);

		if (LastStatus != EFI::EFI_STATUS::SUCCESS)
		{
			UINTN handleCount = 0;
			EFI::EFI_HANDLE* handleBuffer;
			LastStatus = sysTable->BootServices->LocateHandleBuffer(EFI_LOCATE_SEARCH_TYPE::ByProtocol, &EFI_GRAPHICS_OUTPUT_PROTOCOL_GUID, nullptr, &handleCount, &handleBuffer);

			sysTable->ConOut->OutputString(sysTable->ConOut, Environment::UTF16::ToString(handleCount));

			if (LastStatus != EFI::EFI_STATUS::SUCCESS)
			{
				return nullptr;
			}

			LastStatus = sysTable->BootServices->OpenProtocol(handleBuffer[0], &EFI_GRAPHICS_OUTPUT_PROTOCOL_GUID, (void**)&gop, hnd, nullptr, EFI::EFI_OPEN_PROTOCOL_GET_PROTOCOL);

			sysTable->BootServices->FreePool(handleBuffer);
		}

		return GraphicsContext(gop);
	};

	void GraphicsContext::Terminate(EFI::EFI_HANDLE hnd, EFI::EFI_SYSTEM_TABLE* sysTable)
	{
		LastStatus = sysTable->BootServices->CloseProtocol(sysTable->ConsoleOutHandle, &EFI_GRAPHICS_OUTPUT_PROTOCOL_GUID, hnd, nullptr);
	};

	void GraphicsContext::SetForegroundPixel(UINTN xPos, UINTN yPos)
	{
		*(EFI::EFI_GRAPHICS_OUTPUT_BLT_PIXEL*)(((UINTN)gop->Mode->FrameBufferBase) + (yPos * (UINTN)(gop->Mode->Info->HorizontalResolution) + xPos)) = CurrentForeground;
	};
	void GraphicsContext::SetForegroundPixel(UINTN xPos, UINTN yPos, EFI::EFI_GRAPHICS_OUTPUT_BLT_PIXEL* rgba)
	{
		CurrentForeground = *rgba;
		*(EFI::EFI_GRAPHICS_OUTPUT_BLT_PIXEL*)(((UINTN)gop->Mode->FrameBufferBase) + (yPos * (UINTN)(gop->Mode->Info->HorizontalResolution) + xPos)) = CurrentForeground;
	}
	void GraphicsContext::SetForegroundPixel(UINTN xPos, UINTN yPos, Colour* colour)
	{
		CurrentForeground = Colour::ToEFI(colour);
	}
	void GraphicsContext::SetForegroundPixel(UINTN xPos, UINTN yPos, Colour colour)
	{
		CurrentForeground = Colour::ToEFI(colour);
	};
	void GraphicsContext::SetForegroundPixel(UINTN xPos, UINTN yPos, UINT8 r, UINT8 g, UINT8 b, UINT8 a)
	{
		CurrentForeground = EFI::EFI_GRAPHICS_OUTPUT_BLT_PIXEL{ b,g,r,a };
		*(EFI::EFI_GRAPHICS_OUTPUT_BLT_PIXEL*)(((UINTN)gop->Mode->FrameBufferBase) + (yPos * (UINTN)(gop->Mode->Info->HorizontalResolution) + xPos)) = CurrentForeground;
	};
	void GraphicsContext::SetForegroundPixel(UINTN xPos, UINTN yPos, UINT32 rgba)
	{
		CurrentForeground = EFI::EFI_GRAPHICS_OUTPUT_BLT_PIXEL{ (UINT8)((rgba & 0x0000FF00) >> 8),(UINT8)((rgba & 0x00FF0000) >> 16),(UINT8)((rgba & 0xFF000000) >> 24), (UINT8)((rgba & 0x000000FF)) };
		*(EFI::EFI_GRAPHICS_OUTPUT_BLT_PIXEL*)(((UINTN)gop->Mode->FrameBufferBase) + (yPos * (UINTN)(gop->Mode->Info->HorizontalResolution) + xPos)) = CurrentForeground;
	};

	void GraphicsContext::SetBackgroundPixel(UINTN xPos, UINTN yPos)
	{
		*(EFI::EFI_GRAPHICS_OUTPUT_BLT_PIXEL*)(((UINTN)gop->Mode->FrameBufferBase) + (yPos * (UINTN)(gop->Mode->Info->HorizontalResolution) + xPos)) = CurrentBackground;
	};
	void GraphicsContext::SetBackgroundPixel(UINTN xPos, UINTN yPos, EFI::EFI_GRAPHICS_OUTPUT_BLT_PIXEL* rgba)
	{
		CurrentBackground = *rgba;
		*(EFI::EFI_GRAPHICS_OUTPUT_BLT_PIXEL*)(((UINTN)gop->Mode->FrameBufferBase) + (yPos * (UINTN)(gop->Mode->Info->HorizontalResolution) + xPos)) = CurrentBackground;
	}
	void GraphicsContext::SetBackgroundPixel(UINTN xPos, UINTN yPos, Colour* colour)
	{
		CurrentBackground = Colour::ToEFI(colour);
	}
	void GraphicsContext::SetBackgroundPixel(UINTN xPos, UINTN yPos, Colour colour)
	{
		CurrentBackground = Colour::ToEFI(colour);
	}
	void GraphicsContext::SetBackgroundPixel(UINTN xPos, UINTN yPos, UINT8 r, UINT8 g, UINT8 b, UINT8 a)
	{
		CurrentBackground = EFI_GRAPHICS_OUTPUT_BLT_PIXEL{ b,g,r,a };
		*(EFI::EFI_GRAPHICS_OUTPUT_BLT_PIXEL*)(((UINTN)((UINTN)gop->Mode->FrameBufferBase)) + (yPos * (UINTN)(gop->Mode->Info->HorizontalResolution) + xPos)) = CurrentBackground;
	};
	void GraphicsContext::SetBackgroundPixel(UINTN xPos, UINTN yPos, UINT32 rgba)
	{
		CurrentBackground = EFI::EFI_GRAPHICS_OUTPUT_BLT_PIXEL{ (UINT8)((rgba & 0x0000FF00) >> 8),(UINT8)((rgba & 0x00FF0000) >> 16),(UINT8)((rgba & 0xFF000000) >> 24), (UINT8)((rgba & 0x000000FF)) };;
		*(EFI::EFI_GRAPHICS_OUTPUT_BLT_PIXEL*)(((UINTN)((UINTN)gop->Mode->FrameBufferBase)) + (yPos * (UINTN)(gop->Mode->Info->HorizontalResolution) + xPos)) = CurrentBackground;
	};

	void GraphicsContext::ClearScreen()
	{
		gop->Blt(gop, &CurrentBackground, EFI::EFI_GRAPHICS_OUTPUT_BLT_OPERATION::EfiBltVideoFill, 0, 0, 0, 0, gop->Mode->Info->HorizontalResolution, gop->Mode->Info->VerticalResolution, 0);
	};
	void GraphicsContext::ClearScreen(EFI::EFI_GRAPHICS_OUTPUT_BLT_PIXEL* rgba)
	{
		CurrentBackground = *rgba;
		gop->Blt(gop, &CurrentBackground, EFI::EFI_GRAPHICS_OUTPUT_BLT_OPERATION::EfiBltVideoFill, 0, 0, 0, 0, gop->Mode->Info->HorizontalResolution, gop->Mode->Info->VerticalResolution, 0);
	}
	void GraphicsContext::ClearScreen(Colour* colour)
	{
		CurrentBackground = Colour::ToEFI(colour);
		gop->Blt(gop, (EFI::EFI_GRAPHICS_OUTPUT_BLT_PIXEL*)&CurrentBackground, EFI::EFI_GRAPHICS_OUTPUT_BLT_OPERATION::EfiBltVideoFill, 0, 0, 0, 0, gop->Mode->Info->HorizontalResolution, gop->Mode->Info->VerticalResolution, 0);
	}
	void GraphicsContext::ClearScreen(Colour colour)
	{
		CurrentBackground = Colour::ToEFI(colour);
		gop->Blt(gop, (EFI::EFI_GRAPHICS_OUTPUT_BLT_PIXEL*)&CurrentBackground, EFI::EFI_GRAPHICS_OUTPUT_BLT_OPERATION::EfiBltVideoFill, 0, 0, 0, 0, gop->Mode->Info->HorizontalResolution, gop->Mode->Info->VerticalResolution, 0);
	}
	void GraphicsContext::ClearScreen(UINT8 r, UINT8 g, UINT8 b, UINT8 a)
	{
		CurrentBackground = EFI_GRAPHICS_OUTPUT_BLT_PIXEL{ b,g,r,a };
		gop->Blt(gop, (EFI::EFI_GRAPHICS_OUTPUT_BLT_PIXEL*)&CurrentBackground, EFI::EFI_GRAPHICS_OUTPUT_BLT_OPERATION::EfiBltVideoFill, 0, 0, 0, 0, gop->Mode->Info->HorizontalResolution, gop->Mode->Info->VerticalResolution, 0);
	};
	void GraphicsContext::ClearScreen(UINT32 rgba)
	{
		CurrentBackground = EFI::EFI_GRAPHICS_OUTPUT_BLT_PIXEL{ (UINT8)((rgba & 0x0000FF00) >> 8),(UINT8)((rgba & 0x00FF0000) >> 16),(UINT8)((rgba & 0xFF000000) >> 24), (UINT8)((rgba & 0x000000FF)) };
		gop->Blt(gop, (EFI::EFI_GRAPHICS_OUTPUT_BLT_PIXEL*)&CurrentBackground, EFI::EFI_GRAPHICS_OUTPUT_BLT_OPERATION::EfiBltVideoFill, 0, 0, 0, 0, gop->Mode->Info->HorizontalResolution, gop->Mode->Info->VerticalResolution, 0);
	};

	void GraphicsContext::DrawFilledRectangle(UINTN xPos, UINTN yPos, UINTN width, UINTN height)
	{
		gop->Blt(gop, (EFI::EFI_GRAPHICS_OUTPUT_BLT_PIXEL*)&CurrentForeground, EFI::EFI_GRAPHICS_OUTPUT_BLT_OPERATION::EfiBltVideoFill, 0, 0, xPos, yPos, width, height, 0);
	};
	void GraphicsContext::DrawFilledRectangle(UINTN xPos, UINTN yPos, UINTN width, UINTN height, EFI::EFI_GRAPHICS_OUTPUT_BLT_PIXEL* rgba)
	{
		CurrentForeground = *rgba;
		gop->Blt(gop, (EFI::EFI_GRAPHICS_OUTPUT_BLT_PIXEL*)&CurrentForeground, EFI::EFI_GRAPHICS_OUTPUT_BLT_OPERATION::EfiBltVideoFill, 0, 0, xPos, yPos, width, height, 0);
	}
	void GraphicsContext::DrawFilledRectangle(UINTN xPos, UINTN yPos, UINTN width, UINTN height, Colour* colour)
	{
		CurrentForeground = Colour::ToEFI(colour);
		gop->Blt(gop, (EFI::EFI_GRAPHICS_OUTPUT_BLT_PIXEL*)&CurrentForeground, EFI::EFI_GRAPHICS_OUTPUT_BLT_OPERATION::EfiBltVideoFill, 0, 0, xPos, yPos, width, height, 0);
	}
	void GraphicsContext::DrawFilledRectangle(UINTN xPos, UINTN yPos, UINTN width, UINTN height, Colour colour)
	{
		CurrentForeground = Colour::ToEFI(colour);
		gop->Blt(gop, (EFI::EFI_GRAPHICS_OUTPUT_BLT_PIXEL*)&CurrentForeground, EFI::EFI_GRAPHICS_OUTPUT_BLT_OPERATION::EfiBltVideoFill, 0, 0, xPos, yPos, width, height, 0);
	}
	void GraphicsContext::DrawFilledRectangle(UINTN xPos, UINTN yPos, UINTN width, UINTN height, UINT8 r, UINT8 g, UINT8 b, UINT8 a)
	{
		CurrentForeground = EFI_GRAPHICS_OUTPUT_BLT_PIXEL{ b,g,r,a };
		gop->Blt(gop, (EFI::EFI_GRAPHICS_OUTPUT_BLT_PIXEL*)&CurrentForeground, EFI::EFI_GRAPHICS_OUTPUT_BLT_OPERATION::EfiBltVideoFill, 0, 0, xPos, yPos, width, height, 0);
	};
	void GraphicsContext::DrawFilledRectangle(UINTN xPos, UINTN yPos, UINTN width, UINTN height, UINT32 rgba)
	{
		CurrentForeground = EFI::EFI_GRAPHICS_OUTPUT_BLT_PIXEL{ (UINT8)((rgba & 0x0000FF00) >> 8),(UINT8)((rgba & 0x00FF0000) >> 16),(UINT8)((rgba & 0xFF000000) >> 24), (UINT8)((rgba & 0x000000FF)) };
		gop->Blt(gop, (EFI::EFI_GRAPHICS_OUTPUT_BLT_PIXEL*)&CurrentForeground, EFI::EFI_GRAPHICS_OUTPUT_BLT_OPERATION::EfiBltVideoFill, 0, 0, xPos, yPos, width, height, 0);
	}

	void GraphicsContext::DrawLine(UINTN sXPos, UINTN sYPos, UINTN eXPos, UINTN eYPos, UINTN thickness)
	{
		INTN dx = Math::AbsDiff((INTN)(sXPos), (INTN)(eXPos));
		INTN dy = Math::AbsDiff((INTN)(sYPos), (INTN)(eYPos));
		INTN sx = Math::Sign((INTN)(eXPos - sXPos));
		INTN sy = Math::Sign((INTN)(eYPos - sYPos));
		INTN err = dx - dy;
		INTN e2;
		INTN x = sXPos;
		INTN y = sYPos;

		for (UINTN i = 0; i < thickness; i++)
		{
			SetForegroundPixel(x, y);
		}

		while (x != eXPos || y != eYPos)
		{
			e2 = 2 * err;
			if (e2 > -dy)
			{
				err -= dy;
				x += sx;
				for (UINTN i = 0; i < thickness; i++)
				{
					SetForegroundPixel(x, y);
				}
			}
			if (e2 < dx)
			{
				err += dx;
				y += sy;
				for (UINTN i = 0; i < thickness; i++)
				{
					SetForegroundPixel(x, y);
				}
			}
		}
	}
	void GraphicsContext::DrawLine(UINTN sXPos, UINTN sYPos, UINTN eXPos, UINTN eYPos, UINTN thickness, EFI::EFI_GRAPHICS_OUTPUT_BLT_PIXEL* colour)
	{
		CurrentForeground = *colour;
		DrawLine(sXPos, sYPos, eXPos, eYPos, thickness);
	}
	void GraphicsContext::DrawLine(UINTN sXPos, UINTN sYPos, UINTN eXPos, UINTN eYPos, UINTN thickness, Colour* colour)
	{
		CurrentForeground = Colour::ToEFI(colour);
		DrawLine(sXPos, sYPos, eXPos, eYPos, thickness);
	}
	void GraphicsContext::DrawLine(UINTN sXPos, UINTN sYPos, UINTN eXPos, UINTN eYPos, UINTN thickness, Colour colour)
	{
		CurrentForeground = Colour::ToEFI(colour);
		DrawLine(sXPos, sYPos, eXPos, eYPos, thickness);
	}
	void GraphicsContext::DrawLine(UINTN sXPos, UINTN sYPos, UINTN eXPos, UINTN eYPos, UINTN thickness, UINT8 r, UINT8 g, UINT8 b, UINT8 a)
	{
		CurrentForeground = EFI_GRAPHICS_OUTPUT_BLT_PIXEL{ b,g,r,a };
		DrawLine(sXPos, sYPos, eXPos, eYPos, thickness);
	}
	void GraphicsContext::DrawLine(UINTN sXPos, UINTN sYPos, UINTN eXPos, UINTN eYPos, UINTN thickness, UINT32 colour)
	{
		CurrentForeground = EFI::EFI_GRAPHICS_OUTPUT_BLT_PIXEL{ (UINT8)((colour & 0x0000FF00) >> 8),(UINT8)((colour & 0x00FF0000) >> 16),(UINT8)((colour & 0xFF000000) >> 24), (UINT8)((colour & 0x000000FF)) };
		DrawLine(sXPos, sYPos, eXPos, eYPos, thickness);
	}
	void GraphicsContext::DrawRectangle(UINTN xPos, UINTN yPos, UINTN width, UINTN height, UINTN thickness)
	{
		/*Draw to filled rectangles to mimic an outlined rectangle tacking the thickness off of the inner rectangles size*/
		UINTN x2 = xPos + thickness;
		UINTN y2 = yPos + thickness;
		UINTN w2 = width - (thickness * 2);
		UINTN h2 = height - (thickness * 2);
		DrawFilledRectangle(xPos, yPos, width, height,CurrentForeground);
		DrawFilledRectangle(x2, y2, w2, h2, CurrentBackground);
	}

	void GraphicsContext::DrawRectangle(UINTN xPos, UINTN yPos, UINTN width, UINTN height, UINTN thickness, EFI::EFI_GRAPHICS_OUTPUT_BLT_PIXEL* colour)
	{
		CurrentForeground = *colour;
		DrawRectangle(xPos, yPos, width, height, thickness);
	}
	void GraphicsContext::DrawRectangle(UINTN xPos, UINTN yPos, UINTN width, UINTN height, UINTN thickness, Colour* colour)
	{
		CurrentForeground = Colour::ToEFI(colour);
		DrawRectangle(xPos, yPos, width, height, thickness);
	}
	void GraphicsContext::DrawRectangle(UINTN xPos, UINTN yPos, UINTN width, UINTN height, UINTN thickness, Colour colour)
	{
		CurrentForeground = Colour::ToEFI(colour);
		DrawRectangle(xPos, yPos, width, height, thickness);
	}
	void GraphicsContext::DrawRectangle(UINTN xPos, UINTN yPos, UINTN width, UINTN height, UINTN thickness, UINT8 r, UINT8 g, UINT8 b, UINT8 a)
	{
		CurrentForeground = EFI_GRAPHICS_OUTPUT_BLT_PIXEL{ b,g,r,a };
		DrawRectangle(xPos, yPos, width, height, thickness);
	}
	void GraphicsContext::DrawRectangle(UINTN xPos, UINTN yPos, UINTN width, UINTN height, UINTN thickness, UINT32 colour)
	{
		CurrentForeground = EFI::EFI_GRAPHICS_OUTPUT_BLT_PIXEL{ (UINT8)((colour & 0x0000FF00) >> 8),(UINT8)((colour & 0x00FF0000) >> 16),(UINT8)((colour & 0xFF000000) >> 24), (UINT8)((colour & 0x000000FF)) };
		DrawRectangle(xPos, yPos, width, height, thickness);
	}

	void GraphicsContext::DrawCircle(UINTN xPos, UINTN yPos, UINTN radius,UINTN thickness)
	{
	}

	void GraphicsContext::DrawCircle(UINTN xPos, UINTN yPos, UINTN radius, UINTN thickness,EFI::EFI_GRAPHICS_OUTPUT_BLT_PIXEL* colour)
	{
	}
	void GraphicsContext::DrawCircle(UINTN xPos, UINTN yPos, UINTN radius, UINTN thickness, Colour* colour)
	{
	}
	void GraphicsContext::DrawCircle(UINTN xPos, UINTN yPos, UINTN radius, UINTN thickness, Colour colour)
	{
	}
	void GraphicsContext::DrawCircle(UINTN xPos, UINTN yPos, UINTN radius, UINTN thickness, UINT8 r, UINT8 g, UINT8 b, UINT8 a)
	{
	}
	void GraphicsContext::DrawCircle(UINTN xPos, UINTN yPos, UINTN radius, UINTN thickness, UINT32 colour)
	{
	}

	void GraphicsContext::DrawFilledCircle(UINTN xPos, UINTN yPos, UINTN radius)
	{
	}
	void GraphicsContext::DrawFilledCircle(UINTN xPos, UINTN yPos, UINTN radius, EFI::EFI_GRAPHICS_OUTPUT_BLT_PIXEL* colour)
	{
	}
	void GraphicsContext::DrawFilledCircle(UINTN xPos, UINTN yPos, UINTN radius, Colour* colour)
	{
	}
	void GraphicsContext::DrawFilledCircle(UINTN xPos, UINTN yPos, UINTN radius, Colour colour)
	{
	}
	void GraphicsContext::DrawFilledCircle(UINTN xPos, UINTN yPos, UINTN radius, UINT8 r, UINT8 g, UINT8 b, UINT8 a)
	{
	}
	void GraphicsContext::DrawFilledCircle(UINTN xPos, UINTN yPos, UINTN radius, UINT32 colour)
	{
	}

	void GraphicsContext::SetBackground(EFI::EFI_GRAPHICS_OUTPUT_BLT_PIXEL* rgba)
	{
		CurrentBackground = *rgba;
	}
	void GraphicsContext::SetBackground(Colour* colour)
	{
		CurrentBackground = Colour::ToEFI(colour);
	}
	void GraphicsContext::SetBackground(Colour colour)
	{
		CurrentBackground = Colour::ToEFI(colour);
	}
	void GraphicsContext::SetBackground(UINT8 r, UINT8 g, UINT8 b, UINT8 a)
	{
		CurrentBackground = EFI::EFI_GRAPHICS_OUTPUT_BLT_PIXEL{ b,g,r,a };
	};
	void GraphicsContext::SetBackground(UINT32 rgba)
	{
		CurrentBackground = EFI::EFI_GRAPHICS_OUTPUT_BLT_PIXEL{ (UINT8)((rgba & 0x0000FF00) >> 8),(UINT8)((rgba & 0x00FF0000) >> 16),(UINT8)((rgba & 0xFF000000) >> 24), (UINT8)((rgba & 0x000000FF)) };
	};

	void GraphicsContext::SetForeground(EFI::EFI_GRAPHICS_OUTPUT_BLT_PIXEL* rgba)
	{
		CurrentForeground = *rgba;
	}
	void GraphicsContext::SetForeground(Colour* colour)
	{
		CurrentForeground = Colour::ToEFI(colour);
	}
	void GraphicsContext::SetForeground(Colour colour)
	{
		CurrentForeground = Colour::ToEFI(colour);
	}
	void GraphicsContext::SetForeground(UINT8 r, UINT8 g, UINT8 b, UINT8 a)
	{
		CurrentForeground = EFI::EFI_GRAPHICS_OUTPUT_BLT_PIXEL{ b,g,r,a };
	};
	void GraphicsContext::SetForeground(UINT32 rgba)
	{
		CurrentForeground = EFI::EFI_GRAPHICS_OUTPUT_BLT_PIXEL{ (UINT8)((rgba & 0x0000FF00) >> 8),(UINT8)((rgba & 0x00FF0000) >> 16),(UINT8)((rgba & 0xFF000000) >> 24), (UINT8)((rgba & 0x000000FF)) };
	};

	Colour GraphicsContext::GetBackground() const
	{
		return CurrentBackground;
	};
	Colour GraphicsContext::GetForeground() const
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
	};
	EFI::EFI_STATUS GraphicsContext::QueryMode(UINT32 modeNumber, OUT UINTN* size, OUT EFI::EFI_GRAPHICS_OUTPUT_MODE_INFORMATION** info)
	{
		if (modeNumber >= gop->Mode->MaxMode)
		{
			return EFI::EFI_STATUS::UNSUPPORTED;
		}

		return gop->QueryMode(gop, modeNumber, size, info);
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

	GraphicsContext::GraphicsContext(EFI_GRAPHICS_OUTPUT_PROTOCOL* g)
	{
		gop = g;
		CurrentBackground = Colour::ToEFI(Colours::Black);
		CurrentForeground = Colour::ToEFI(Colours::White);
	};
};