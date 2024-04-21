#include "RenderContext.h"
#include <EFI_STATUS.h>
#include <EFI_LOCATE_SEARCH_TYPE.h>
#include <EFI_GUID.h>

#include <Protocols/Graphics/EFI_GRAPHICS_OUTPUT_PROTOCOL.h>

#include <System/Allocator.h>

#include <Enviroment/Unicode.h>


namespace Common::Graphics
{
	static inline UINTN CalculatePixelOffset(UINTN x, UINTN y, UINTN ppsl)
	{
		return (y * ppsl) + x;
	}

	template<typename Pixel>
	static void SetRectangle(UINT32 x1, UINT32 y1, UINT32 width, UINT32 height, UINT32 ppsl, Pixel* fb,const Pixel* p)
	{
		UINT32 yMax = y1 + height;

		/*Draw the rectangle*/
		for (UINTN y = y1; y < yMax; y++)
		{
			UINTN row = CalculatePixelOffset(x1, y, ppsl);
			for (UINTN x = x1; x < width; x++)
			{
				fb[row + x] = *p;
			}
		}
	}

	template<typename Pixel>
	static void SetFilledRectangle(UINT32 x1, UINT32 y1, UINT32 width1, UINT32 height1,UINT32 x2,UINT32 y2,UINT32 width2,UINT32 height2, UINT32 ppsl, Pixel* fb,const Pixel* bgP,const Pixel* fgP)
	{
		/*Draw a Rectangle within a rectangle*/

		UINT32 yMax = y1 + height1;
		UINT32 xMax = x1 + width1;

		/*Draw the rectangle*/
		for (UINTN y = y1; y < yMax; y++)
		{
			UINTN row = CalculatePixelOffset(x1, y, ppsl);
			for (UINTN x = x1; x < xMax; x++)
			{
				if (y > y2 && y < height2 || x > x2 && x < width2)
				{
					fb[row + x] = *fgP;
				}
				else
				{
					fb[row + x] = *bgP;
				}
			}
		}
	}


	RenderContext::RenderContext(EFI::EFI_GRAPHICS_OUTPUT_PROTOCOL* ptr, Colour fg, Colour bg)
	{
		monitor = MonitorContext(ptr);
		defaultBg = bg;
		defaultFg = fg;
		background = bg;
		foreground = fg;
	}

	RenderContext* RenderContext::Initialize(EFI::EFI_SYSTEM_TABLE* sysTbl, EFI::EFI_HANDLE imgHndl, Colour fg, Colour bg)
	{
		EFI::EFI_GRAPHICS_OUTPUT_PROTOCOL* gop = nullptr;
		// Locate the GOP protocol and store it in the gop variable, use locate protocol first then try to locate handle Buffer if that fails, if that fails then return the error
		EFI::EFI_STATUS LastStatus = sysTbl->BootServices->LocateProtocol(&EFI::EFI_GRAPHICS_OUTPUT_PROTOCOL_GUID, nullptr, (void**)&gop);

		if (LastStatus == EFI::EFI_STATUS::SUCCESS)
		{
			return new RenderContext(gop, fg, bg);
		}

		UINTN handleCount = 0;
		EFI::EFI_HANDLE* handleBuffer;
		LastStatus = sysTbl->BootServices->LocateHandleBuffer(EFI::EFI_LOCATE_SEARCH_TYPE::ByProtocol, &EFI::EFI_GRAPHICS_OUTPUT_PROTOCOL_GUID, nullptr, &handleCount, &handleBuffer);

		sysTbl->ConOut->OutputString(sysTbl->ConOut, Enviroment::UTF16::ToString(handleCount));

		if (LastStatus != EFI::EFI_STATUS::SUCCESS)
		{
			return nullptr;
		}

		LastStatus = sysTbl->BootServices->OpenProtocol(handleBuffer[0], &EFI::EFI_GRAPHICS_OUTPUT_PROTOCOL_GUID, (void**)&gop, imgHndl, nullptr, EFI::EFI_OPEN_PROTOCOL_GET_PROTOCOL);

		sysTbl->BootServices->FreePool(handleBuffer);

		return new RenderContext(gop, fg, bg);
	}

	Colour RenderContext::GetBackground()
	{
		return background;
	}

	Colour RenderContext::GetForeground()
	{
		return foreground;
	}

	void RenderContext::ResetToDefaultColours()
	{
		background = defaultBg;
		foreground = defaultFg;
	}

	void RenderContext::ResetBackground()
	{
		background = defaultBg;
	}


	void RenderContext::ResetForeground()
	{
		foreground = defaultFg;
	}

	void RenderContext::ClearScreen(BOOLEAN resetColours)
	{
		VOID_PTR fb = monitor.GetFrameBuffer();
		PixelFormat pf = monitor.GetPixelFormat();
		UINT32 ppsl = monitor.GetPixelsPerScanLine();
		UINT32 hRes = monitor.GetHorizontalResolution();
		UINT32 vRes = monitor.GetVerticalResolution();

		/*
		Base on monitor colour mode and bytes per pixel we grab and calculate the colour values need to be entered for the buffer
		*/

		if (resetColours)
		{
			background = defaultBg;
			foreground = defaultFg;
		}

		switch (pf)
		{
		case Common::Graphics::RedGreenBlueReserved8BitPerColor:
		{
			Pixel1Bpp bgP = Pixel1Bpp(background.Red, background.Green, background.Blue, background.Alpha);
			SetRectangle<Pixel1Bpp>(0,0,vRes,hRes,ppsl, (Pixel1Bpp*)fb, &bgP);
			return;
		}
		case Common::Graphics::BlueGreenRedReserved8BitPerColor:
		{
			Pixel1Bpp bgP = Pixel1Bpp(background.Blue, background.Green, background.Red, background.Alpha);
			SetRectangle<Pixel1Bpp>(0, 0, vRes, hRes, ppsl, (Pixel1Bpp*)fb, &bgP);
			return;
		}
		case Common::Graphics::BitMask:
			return;
		case Common::Graphics::BltOnly:
			return;
		case Common::Graphics::FormatMax:
			return;
		default:
			return;
		}


	}

	void RenderContext::ClearScreen(Colour colour)
	{
		background = colour;
		ClearScreen();
	}

	void RenderContext::ClearScreen(Colour* colour)
	{
		background = *colour;
		ClearScreen();
	}

	void RenderContext::ClearScreen(UINT32 colour)
	{
		background = Colour(colour);
		ClearScreen();
	}

	void RenderContext::ClearScreen(UINT32 r, UINT32 g, UINT32 b, UINT32 a)
	{
		background = Colour(r, g, b, a);
		ClearScreen();
	}

	void RenderContext::DrawCircle(UINT32 xPos, UINT32 yPos, UINT32 radius, UINT32 thickness)
	{
	}

	void RenderContext::DrawCircle(UINT32 xPos, UINT32 yPos, UINT32 radius, UINT32 thickness, Colour colour)
	{
	}

	void RenderContext::DrawCircle(UINT32 xPos, UINT32 yPos, UINT32 radius, UINT32 thickness, Colour* colour)
	{
	}

	void RenderContext::DrawCircle(UINT32 xPos, UINT32 yPos, UINT32 radius, UINT32 thickness, UINT32 colour)
	{
	}

	void RenderContext::DrawCircle(UINT32 xPos, UINT32 yPos, UINT32 radius, UINT32 thickness, UINT32 r, UINT32 g, UINT32 b, UINT32 a)
	{
	}

	void RenderContext::DrawFilledCircle(UINT32 xPos, UINT32 yPos, UINT32 radius)
	{
	}

	void RenderContext::DrawFilledCircle(UINT32 xPos, UINT32 yPos, UINT32 radius, Colour colour)
	{
	}

	void RenderContext::DrawFilledCircle(UINT32 xPos, UINT32 yPos, UINT32 radius, Colour* colour)
	{
	}

	void RenderContext::DrawFilledCircle(UINT32 xPos, UINT32 yPos, UINT32 radius, UINT32 colour)
	{
	}

	void RenderContext::DrawFilledCircle(UINT32 xPos, UINT32 yPos, UINT32 radius, UINT32 r, UINT32 g, UINT32 b, UINT32 a)
	{
	}

	void RenderContext::DrawFilledRectangle(UINT32 xPos, UINT32 yPos, UINT32 width, UINT32 height, UINT32 thickness)
	{
		VOID_PTR fb = monitor.GetFrameBuffer();
		UINT32 ppsl = monitor.GetPixelsPerScanLine();
		PixelFormat pf = monitor.GetPixelFormat();

		/*Get X and Y Pos in Buffer*/

		UINT32 x2 = xPos + thickness;
		UINT32 y2 = yPos + thickness;

		UINT32 width2 = width - (thickness * 2);
		UINT32 height2 = height - (thickness * 2);


		switch (pf)
		{
		case Common::Graphics::RedGreenBlueReserved8BitPerColor:
		{
			Pixel1Bpp bgP = Pixel1Bpp(background.Red, background.Green, background.Blue, background.Alpha);
			Pixel1Bpp fgP = Pixel1Bpp(foreground.Red, foreground.Green, foreground.Blue, foreground.Alpha);
			SetFilledRectangle<Pixel1Bpp>(xPos, yPos, width, height, x2, y2, width2, height2, ppsl, (Pixel1Bpp*)fb, &bgP, &fgP);
			return;
		}
		case Common::Graphics::BlueGreenRedReserved8BitPerColor:
		{
			Pixel1Bpp bgP = Pixel1Bpp(background.Blue, background.Green, background.Red, background.Alpha);
			Pixel1Bpp fgP = Pixel1Bpp(foreground.Blue, foreground.Green, foreground.Red, foreground.Alpha);
			SetFilledRectangle<Pixel1Bpp>(xPos, yPos, width, height, x2, y2, width2, height2, ppsl, (Pixel1Bpp*)fb, &bgP, &fgP);
			return;
		}
		case Common::Graphics::BitMask:
			return;
		case Common::Graphics::BltOnly:
			return;
		case Common::Graphics::FormatMax:
			return;
		default:
			return;
		}
	}

	

	void RenderContext::DrawFilledRectangle(UINT32 xPos, UINT32 yPos, UINT32 width, UINT32 height, UINT32 thickness, Colour fg, Colour bg)
	{
		foreground = fg;
		background = bg;
		DrawFilledRectangle(xPos, yPos, width, height, thickness);
	}

	void RenderContext::DrawFilledRectangle(UINT32 xPos, UINT32 yPos, UINT32 width, UINT32 height, UINT32 thickness, Colour* fg, Colour* bg)
	{
		foreground = *fg;
		background = *bg;
		DrawFilledRectangle(xPos, yPos, width, height, thickness);
	}

	void RenderContext::DrawFilledRectangle(UINT32 xPos, UINT32 yPos, UINT32 width, UINT32 height, UINT32 thickness, UINT32 fg, UINT32 bg)
	{
		foreground = Colour(fg);
		background = Colour(bg);
		DrawFilledRectangle(xPos, yPos, width, height, thickness);
	}

	void RenderContext::DrawFilledRectangle(UINT32 xPos, UINT32 yPos, UINT32 width, UINT32 height, UINT32 thickness, UINT8 fgR, UINT8 fgG, UINT8 fbB, UINT32 bgR, UINT32 bgG, UINT32 bgB, UINT8 fbA, UINT32 bgA)
	{
		foreground = Colour(fgR, fgG, fbB, fbA);
		background = Colour(bgR, bgG, bgB, bgA);
		DrawFilledRectangle(xPos, yPos, width, height, thickness);
	}

	void RenderContext::DrawLine(UINT32 sXPos, UINT32 sYPos, UINT32 eXPos, UINT32 eYPos, UINT32 thickness)
	{
	}

	void RenderContext::DrawLine(UINT32 sXPos, UINT32 sYPos, UINT32 eXPos, UINT32 eYPos, UINT32 thickness, Colour colour)
	{
	}

	void RenderContext::DrawLine(UINT32 sXPos, UINT32 sYPos, UINT32 eXPos, UINT32 eYPos, UINT32 thickness, Colour* colour)
	{
	}

	void RenderContext::DrawLine(UINT32 sXPos, UINT32 sYPos, UINT32 eXPos, UINT32 eYPos, UINT32 thickness, UINT32 colour)
	{
	}

	void RenderContext::DrawLine(UINT32 sXPos, UINT32 sYPos, UINT32 eXPos, UINT32 eYPos, UINT32 thickness, UINT32 r, UINT32 g, UINT32 b, UINT32 a)
	{
	}

	
	void RenderContext::DrawRectangle(UINT32 xPos, UINT32 yPos, UINT32 width, UINT32 height)
	{
		VOID_PTR fb = monitor.GetFrameBuffer();
		UINT32 ppsl = monitor.GetPixelsPerScanLine();
		PixelFormat pf = monitor.GetPixelFormat();

		switch (pf)
		{
		case Common::Graphics::RedGreenBlueReserved8BitPerColor:
		{
			/*Get X and Y Pos in Buffer*/

			Pixel1Bpp bgP = Pixel1Bpp(background.Red, background.Green, background.Blue, background.Alpha);

			SetRectangle<Pixel1Bpp>(xPos,yPos,width,height,ppsl,(Pixel1Bpp*)fb, &bgP);
			return;
		}
		case Common::Graphics::BlueGreenRedReserved8BitPerColor:
		{
			Pixel1Bpp bgP = Pixel1Bpp(background.Blue, background.Green, background.Red, background.Alpha);
			SetRectangle<Pixel1Bpp>(xPos, yPos, width, height, ppsl, (Pixel1Bpp*)fb, &bgP);
			return;
		}
		case Common::Graphics::BitMask:
			return;
		case Common::Graphics::BltOnly:
			return;
		case Common::Graphics::FormatMax:
			return;
		default:
			return;
		}
	}

	void RenderContext::DrawRectangle(UINT32 xPos, UINT32 yPos, UINT32 width, UINT32 height, Colour colour)
	{
		background = colour;
		DrawRectangle(xPos, yPos, width, height);
	}

	void RenderContext::DrawRectangle(UINT32 xPos, UINT32 yPos, UINT32 width, UINT32 height, Colour* colour)
	{
		background = *colour;
		DrawRectangle(xPos, yPos, width, height);
	}

	void RenderContext::DrawRectangle(UINT32 xPos, UINT32 yPos, UINT32 width, UINT32 height, UINT32 colour)
	{
		background = Colour(colour);
		DrawRectangle(xPos, yPos, width, height);
	}

	void RenderContext::DrawRectangle(UINT32 xPos, UINT32 yPos, UINT32 width, UINT32 height, UINT32 r, UINT32 g, UINT32 b, UINT32 a)
	{
		background = Colour(r, g, b, a);
		DrawRectangle(xPos, yPos, width, height);
	}

	void RenderContext::SetBackground(Colour colour)
	{
		background = colour;
	}

	void RenderContext::SetBackground(Colour* colour)
	{
		background = *colour;
	}

	void RenderContext::SetBackground(UINT32 colour)
	{
		background = Colour(colour);
	}

	void RenderContext::SetBackground(UINT32 r, UINT32 g, UINT32 b, UINT32 a)
	{
		background = Colour(r, g, b, a);
	}

	void RenderContext::SetForeground(Colour colour)
	{
		foreground = colour;
	}

	void RenderContext::SetForeground(Colour* colour)
	{
		foreground = *colour;
	}

	void RenderContext::SetForeground(UINT32 colour)
	{
		foreground = Colour(colour);
	}

	void RenderContext::SetForeground(UINT32 r, UINT32 g, UINT32 b, UINT32 a)
	{
		foreground = Colour(r, g, b, a);
	}

	void RenderContext::SetPixelBackground(UINT32 xPos, UINT32 yPos)
	{
		VOID_PTR fb = monitor.GetFrameBuffer();
		UINTN ppsl = monitor.GetPixelsPerScanLine();
		PixelFormat pf = monitor.GetPixelFormat();

		UINTN pos = CalculatePixelOffset(xPos,yPos,ppsl);

		switch (pf)
		{
		case Common::Graphics::RedGreenBlueReserved8BitPerColor:
		{
			Pixel1Bpp bgP = Pixel1Bpp(background.Red, background.Green, background.Blue, background.Alpha);
			((Pixel1Bpp*)fb)[pos] = bgP;
			return;
		}
		case Common::Graphics::BlueGreenRedReserved8BitPerColor:
		{
			Pixel1Bpp bgP = Pixel1Bpp(background.Blue, background.Green, background.Red, background.Alpha);
			((Pixel1Bpp*)fb)[pos] = bgP;
			return;
		}
		case Common::Graphics::BitMask:
			return;
		case Common::Graphics::BltOnly:
			return;
		case Common::Graphics::FormatMax:
			return;
		default:
			return;
		}
	}

	void RenderContext::SetPixelRowBackground(UINT32 xPos, UINT32 yPos, UINT32 length)
	{
		VOID_PTR fb = monitor.GetFrameBuffer();
		PixelFormat pf = monitor.GetPixelFormat();
		UINTN ppsl = monitor.GetPixelsPerScanLine();

		UINTN pos = CalculatePixelOffset(xPos, yPos, ppsl);
		UINTN end = pos + length;

		/*
		*  Calculate the pixel position in the frame buffer, and set the colour of the pixel
		*/

		switch (pf)
		{
		case Common::Graphics::RedGreenBlueReserved8BitPerColor:
		{
			Pixel1Bpp p = Pixel1Bpp(background.Red, background.Green, background.Blue, background.Alpha);
			for (UINTN i = pos; i < end; i++)
			{
				((Pixel1Bpp*)fb)[i] = p;
			}
			return;
		}
		case Common::Graphics::BlueGreenRedReserved8BitPerColor:
		{
			Pixel1Bpp p = Pixel1Bpp(background.Blue, background.Green, background.Red, background.Alpha);
			for (UINTN i = pos; i < end; i++)
			{
				((Pixel1Bpp*)fb)[i] = p;
			}
			return;
		}
		case Common::Graphics::BitMask:
			return;
		case Common::Graphics::BltOnly:
			return;
		case Common::Graphics::FormatMax:
			return;
		default:
			return;
		}
	}

	void RenderContext::SetPixelRowBackground(UINT32 xPos, UINT32 yPos, UINT32 length, Colour colour)
	{
		background = colour;
		SetPixelRowBackground(xPos, yPos, length);
	}

	void RenderContext::SetPixelRowBackground(UINT32 xPos, UINT32 yPos, UINT32 length, Colour* colour)
	{
		background = *colour;
		SetPixelRowBackground(xPos, yPos, length);
	}

	void RenderContext::SetPixelRowBackground(UINT32 xPos, UINT32 yPos, UINT32 length, UINT32 colour)
	{
		background = Colour(colour);
		SetPixelRowBackground(xPos, yPos, length);
	}

	void RenderContext::SetPixelRowBackground(UINT32 xPos, UINT32 yPos, UINT32 length, UINT32 r, UINT32 g, UINT32 b, UINT32 a)
	{
		background = Colour(r, g, b, a);
		SetPixelRowBackground(xPos, yPos, length);
	}

	void RenderContext::SetPixelBackground(UINT32 xPos, UINT32 yPos, Colour colour)
	{
		background = colour;
		SetPixelBackground(xPos, yPos);
	}

	void RenderContext::SetPixelBackground(UINT32 xPos, UINT32 yPos, Colour* colour)
	{
		background = *colour;
		SetPixelBackground(xPos, yPos);
	}

	void RenderContext::SetPixelBackground(UINT32 xPos, UINT32 yPos, UINT32 colour)
	{
		background = Colour(colour);
		SetPixelBackground(xPos, yPos);
	}

	void RenderContext::SetPixelBackground(UINT32 xPos, UINT32 yPos, UINT32 r, UINT32 g, UINT32 b, UINT32 a)
	{
		background = Colour(r, g, b, a);
		SetPixelBackground(xPos, yPos);
	}

	void RenderContext::SetPixelForeground(UINT32 xPos, UINT32 yPos)
	{
		VOID_PTR fb = monitor.GetFrameBuffer();
		UINTN ppsl = monitor.GetPixelsPerScanLine();
		PixelFormat pf = monitor.GetPixelFormat();

		UINTN pos = CalculatePixelOffset(xPos,yPos,ppsl);

		switch (pf)
		{
		case Common::Graphics::RedGreenBlueReserved8BitPerColor:
		{
			Pixel1Bpp bgP = Pixel1Bpp(foreground.Red, foreground.Green, foreground.Blue, foreground.Alpha);
			((Pixel1Bpp*)fb)[pos] = bgP;
			return;
		}
		case Common::Graphics::BlueGreenRedReserved8BitPerColor:
		{
			Pixel1Bpp bgP = Pixel1Bpp(foreground.Blue, foreground.Green, foreground.Red, foreground.Alpha);
			((Pixel1Bpp*)fb)[pos] = bgP;
			return;
		}
		case Common::Graphics::BitMask:
			return;
		case Common::Graphics::BltOnly:
			return;
		case Common::Graphics::FormatMax:
			return;
		default:
			return;
		}
	}

	void RenderContext::SetPixelRowForeground(UINT32 xPos, UINT32 yPos, UINT32 length)
	{
		VOID_PTR fb = monitor.GetFrameBuffer();
		PixelFormat pf = monitor.GetPixelFormat();
		UINTN ppsl = monitor.GetPixelsPerScanLine();

		UINTN pos = CalculatePixelOffset(xPos,yPos,ppsl);
		UINTN end = pos + length;

		switch (pf)
		{
		case Common::Graphics::RedGreenBlueReserved8BitPerColor:
		{
			Pixel1Bpp p = Pixel1Bpp(foreground.Red, foreground.Green, foreground.Blue, foreground.Alpha);
			for (UINTN i = pos; i < end; i++)
			{
				((Pixel1Bpp*)fb)[i] = p;
			}
			return;
		}
		case Common::Graphics::BlueGreenRedReserved8BitPerColor:
		{
			Pixel1Bpp p = Pixel1Bpp(foreground.Blue, foreground.Green, foreground.Red, foreground.Alpha);
			for (UINTN i = pos; i < end; i++)
			{
				((Pixel1Bpp*)fb)[i] = p;
			}
			return;
		}
		case Common::Graphics::BitMask:
			return;
		case Common::Graphics::BltOnly:
			return;
		case Common::Graphics::FormatMax:
			return;
		default:
			return;
		}
	}

	void RenderContext::SetPixelForeground(UINT32 xPos, UINT32 yPos, Colour colour)
	{
		foreground = colour;
		SetPixelForeground(xPos, yPos);
	}

	void RenderContext::SetPixelForeground(UINT32 xPos, UINT32 yPos, Colour* colour)
	{
		foreground = *colour;
		SetPixelForeground(xPos, yPos);
	}

	void RenderContext::SetPixelForeground(UINT32 xPos, UINT32 yPos, UINT32 colour)
	{
		foreground = Colour(colour);
		SetPixelForeground(xPos, yPos);
	}

	void RenderContext::SetPixelForeground(UINT32 xPos, UINT32 yPos, UINT32 r, UINT32 g, UINT32 b, UINT32 a)
	{
		foreground = Colour(r, g, b, a);
		SetPixelForeground(xPos, yPos);
	}

	void RenderContext::Terminate(EFI::EFI_HANDLE hnd, EFI::EFI_SYSTEM_TABLE* sysTable)
	{
		monitor.Terminate();
		sysTable->BootServices->CloseProtocol(sysTable->ConsoleOutHandle, &EFI::EFI_GRAPHICS_OUTPUT_PROTOCOL_GUID, hnd, nullptr);
	};

	void RenderContext::SetPixelRowForeground(UINT32 xPos, UINT32 yPos, UINT32 length, Colour colour)
	{
		foreground = colour;
		SetPixelRowForeground(xPos, yPos, length);
	}
	void RenderContext::SetPixelRowForeground(UINT32 xPos, UINT32 yPos, UINT32 length, Colour* colour)
	{
		foreground = *colour;
		SetPixelRowForeground(xPos, yPos, length);
	}
	void RenderContext::SetPixelRowForeground(UINT32 xPos, UINT32 yPos, UINT32 length, UINT32 colour)
	{
		foreground = Colour(colour);
		SetPixelRowForeground(xPos, yPos, length);
	}
	void RenderContext::SetPixelRowForeground(UINT32 xPos, UINT32 yPos, UINT32 length, UINT32 r, UINT32 g, UINT32 b, UINT32 a)
	{
		foreground = Colour(r, g, b, a);
		SetPixelRowForeground(xPos, yPos, length);
	}
	MonitorContext* RenderContext::GetMonitorContext()
	{
		return &monitor;
	}
}