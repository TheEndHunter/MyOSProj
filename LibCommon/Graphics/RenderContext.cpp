#include "RenderContext.h"
#include <EFI_STATUS.h>
#include <EFI_LOCATE_SEARCH_TYPE.h>
#include <EFI_GUID.h>

#include <Protocols/Graphics/EFI_GRAPHICS_OUTPUT_PROTOCOL.h>

#include <System/Allocator.h>

#include <Environment/Unicode.h>


namespace Common::Graphics
{
	inline UINTN CalculatePixelOffset(const UINTN x, const UINTN y, const UINTN ppsl)
	{
		/*calculate the address offset of the pixel in the buffer*/
		return (y * ppsl) + x;
	}

	template<typename Pixel>
	void SetRectangle(const UINT32 x1, const UINT32 y1, const UINT32 width, const UINT32 height, const UINT32 ppsl, Pixel* fb, const Pixel& p)
	{
		UINT32 yMax = y1 + height;
		UINT32 xMax = x1 + width;

		/*Draw the rectangle*/
		for (UINTN y = y1; y < yMax; y++)
		{
			UINTN row = CalculatePixelOffset(x1, y, ppsl);
			Pixel* pRow = &fb[row];
			for (UINTN x = x1; x < xMax; x++)
			{
				pRow[x] = p;
			}
		}
	}

	template<typename Pixel>
	void SetFilledRectangle(const UINT32 x1, const UINT32 y1, const UINT32 width1, const UINT32 height1, const UINT32 x2, const UINT32 y2, const UINT32 width2, const UINT32 height2, const UINT32 ppsl, Pixel* fb, const Pixel& c2P, const Pixel& c1P)
	{
		UINT32 yMax1 = y1 + height1;
		UINT32 xMax1 = x1 + width1;

		UINT32 yMax2 = y2 + height2;
		UINT32 xMax2 = x2 + width2;

		/*Draw the rectangle*/
		for (UINTN y = y1; y < yMax1; y++)
		{
			/*Find the start of the row and set a pointer before doing the loop*/
			UINTN row = CalculatePixelOffset(0, y, ppsl);
			Pixel* pRow = &fb[row];
			for (UINTN x = x1; x < xMax1; x++)
			{
				if ((y > y2 && y < yMax2) && (x > x2 && x < xMax2))
				{
					pRow[x] = c1P;
				}
				else
				{
					pRow[x] = c2P;
				}
			}
		}
	}


	RenderContext::RenderContext(EFI::EFI_GRAPHICS_OUTPUT_PROTOCOL* ptr,const Colour txt,const Colour bg,const Colour fg1,const Colour fg2)
	{
		monitor = MonitorContext(ptr);
		defaultBackgroundColour = bg;
		defaultForeground1Colour = fg1;
		defaultForeground2Colour = fg2;
		defaultText = txt;

		backgroundColour = bg;
		foreground1Colour = fg1;
		foreground2Colour = fg2;
		textColour = txt;
	}

	RenderContext* RenderContext::Initialize(EFI::EFI_SYSTEM_TABLE* sysTbl, EFI::EFI_HANDLE imgHndl,const Colour txt,const Colour bg,const Colour fg1,const Colour fg2)
	{
		EFI::EFI_GRAPHICS_OUTPUT_PROTOCOL* gop = nullptr;
		// Locate the GOP protocol and store it in the gop variable, use locate protocol first then try to locate handle Buffer if that fails, if that fails then return the error
		EFI::EFI_STATUS LastStatus = sysTbl->BootServices->LocateProtocol(&EFI::EFI_GRAPHICS_OUTPUT_PROTOCOL_GUID, nullptr, (void**)&gop);

		if (LastStatus == EFI::EFI_STATUS::SUCCESS)
		{
			return new RenderContext(gop, txt, bg, fg1, fg2);
		}

		UINTN handleCount = 0;
		EFI::EFI_HANDLE* handleBuffer;
		LastStatus = sysTbl->BootServices->LocateHandleBuffer(EFI::EFI_LOCATE_SEARCH_TYPE::ByProtocol, &EFI::EFI_GRAPHICS_OUTPUT_PROTOCOL_GUID, nullptr, &handleCount, &handleBuffer);

		sysTbl->ConOut->OutputString(sysTbl->ConOut, Environment::UTF16::ToString(handleCount));

		if (LastStatus != EFI::EFI_STATUS::SUCCESS)
		{
			return nullptr;
		}

		LastStatus = sysTbl->BootServices->OpenProtocol(handleBuffer[0], &EFI::EFI_GRAPHICS_OUTPUT_PROTOCOL_GUID, (void**)&gop, imgHndl, nullptr, EFI::EFI_OPEN_PROTOCOL_GET_PROTOCOL);

		sysTbl->BootServices->FreePool(handleBuffer);

		return new RenderContext(gop, txt, bg, fg1, fg2);
	}

	Colour RenderContext::GetBackgroundColour()
	{
		return backgroundColour;
	}

	Colour RenderContext::GetForeground1Colour()
	{
		return foreground1Colour;
	}
	Colour RenderContext::GetForeground2Colour()
	{
		return foreground2Colour;
	}
	Colour RenderContext::GetTextColour()
	{
		return textColour;
	}

	void RenderContext::ResetToDefaultColours()
	{
		backgroundColour = defaultBackgroundColour;
		foreground1Colour = defaultForeground1Colour;
		foreground2Colour = defaultForeground2Colour;
		textColour = defaultText;
	}

	void RenderContext::ResetBackgroundColour()
	{
		backgroundColour = defaultBackgroundColour;
	}

	void RenderContext::ResetForeground1Colour()
	{
		foreground1Colour = defaultForeground1Colour;
	}
	void RenderContext::ResetForeground2Colour()
	{
		foreground2Colour = defaultForeground2Colour;
	}
	void RenderContext::ResetTextColour()
	{
		textColour = defaultText;
	}

	void RenderContext::ClearScreen(BOOLEAN resetColours)
	{
		VOID_PTR fb = monitor.GetFrameBuffer();
		const UINTN fbSize = monitor.GetFrameBufferSize();
		PixelFormat pf = monitor.GetPixelFormat();

		/*
		Base on monitorconst Colour mode and bytes per pixel we grab and calculate theconst Colour values need to be entered for the buffer
		*/

		if (resetColours == TRUE)
		{
			backgroundColour = defaultBackgroundColour;
			foreground1Colour = defaultForeground1Colour;
			foreground2Colour = defaultForeground2Colour;
			textColour = defaultText;
		}
		
		switch (pf)
		{
		case Common::Graphics::RedGreenBlueReserved8BitPerColor:
		{
			Pixel1Bpp bg = Pixel1Bpp(backgroundColour.Red, backgroundColour.Green, backgroundColour.Blue, backgroundColour.Alpha);
			Pixel1Bpp* fbptr = (Pixel1Bpp*)fb;
			for (UINTN i = 0; i < fbSize; i++)
			{
				fbptr[i] = bg;
			}
			break;
		}
		case Common::Graphics::BlueGreenRedReserved8BitPerColor:
		{
			Pixel1Bpp bg = Pixel1Bpp(backgroundColour.Blue, backgroundColour.Green, backgroundColour.Red, backgroundColour.Alpha);
			Pixel1Bpp* fbptr = (Pixel1Bpp*)fb;
			for (UINTN i = 0; i < fbSize; i++)
			{
				fbptr[i] = bg;
			}
			break;
		}
		case Common::Graphics::BitMask:
			break;
		case Common::Graphics::BltOnly:
			break;
		case Common::Graphics::FormatMax:
			break;
		}
	}

	void RenderContext::ClearScreen(const Colour colour)
	{
		backgroundColour = colour;
		ClearScreen();
	}

	void RenderContext::ClearScreen(const Colour* colour)
	{
		backgroundColour = *colour;
		ClearScreen();
	}

	void RenderContext::ClearScreen(const UINT32 colour)
	{
		backgroundColour = Colour(colour);
		ClearScreen();
	}

	void RenderContext::ClearScreen(const UINT32 r, const UINT32 g, const UINT32 b, const UINT32 a)
	{
		backgroundColour = Colour(r, g, b, a);
		ClearScreen();
	}

	void RenderContext::DrawCircle(const UINT32 xPos, const UINT32 yPos, const UINT32 radius, const UINT32 thickness)
	{
	}

	void RenderContext::DrawCircle(const UINT32 xPos, const UINT32 yPos, const UINT32 radius, const UINT32 thickness,const Colour colour)
	{
	}

	void RenderContext::DrawCircle(const UINT32 xPos, const UINT32 yPos, const UINT32 radius, const UINT32 thickness, const Colour* colour)
	{
	}

	void RenderContext::DrawCircle(const UINT32 xPos, const UINT32 yPos, const UINT32 radius, const UINT32 thickness, const UINT32 colour)
	{
	}

	void RenderContext::DrawCircle(const UINT32 xPos, const UINT32 yPos, const UINT32 radius, const UINT32 thickness, const UINT32 r, const UINT32 g, const UINT32 b, const UINT32 a)
	{
	}

	void RenderContext::DrawFilledCircle(const UINT32 xPos, const UINT32 yPos, const UINT32 radius)
	{
	}

	void RenderContext::DrawFilledCircle(const UINT32 xPos, const UINT32 yPos, const UINT32 radius,const Colour colour)
	{
	}

	void RenderContext::DrawFilledCircle(const UINT32 xPos, const UINT32 yPos, const UINT32 radius, const Colour* colour)
	{
	}

	void RenderContext::DrawFilledCircle(const UINT32 xPos, const UINT32 yPos, const UINT32 radius, const UINT32 colour)
	{
	}

	void RenderContext::DrawFilledCircle(const UINT32 xPos, const UINT32 yPos, const UINT32 radius, const UINT32 r, const UINT32 g, const UINT32 b, const UINT32 a)
	{
	}

	void RenderContext::DrawFilledRectangle(const UINT32 xPos, const UINT32 yPos, const UINT32 width, const UINT32 height, const UINT32 thickness)
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
			Pixel1Bpp c2P = Pixel1Bpp(foreground2Colour.Red, foreground2Colour.Green, foreground2Colour.Blue, foreground2Colour.Alpha);
			Pixel1Bpp c1P = Pixel1Bpp(foreground1Colour.Red, foreground1Colour.Green, foreground1Colour.Blue, foreground1Colour.Alpha);
			SetFilledRectangle<Pixel1Bpp>(xPos, yPos, width, height, x2, y2, width2, height2, ppsl, (Pixel1Bpp*)fb, c2P, c1P);
			return;
		}
		case Common::Graphics::BlueGreenRedReserved8BitPerColor:
		{
			Pixel1Bpp c2P = Pixel1Bpp(foreground2Colour.Blue, foreground2Colour.Green, foreground2Colour.Red, foreground2Colour.Alpha);
			Pixel1Bpp c1P = Pixel1Bpp(foreground1Colour.Blue, foreground1Colour.Green, foreground1Colour.Red, foreground1Colour.Alpha);
			SetFilledRectangle<Pixel1Bpp>(xPos, yPos, width, height, x2, y2, width2, height2, ppsl, (Pixel1Bpp*)fb, c2P, c1P);
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

	void RenderContext::DrawFilledRectangle(const UINT32 xPos, const UINT32 yPos, const UINT32 width, const UINT32 height, const UINT32 thickness,const Colour c1,const Colour c2)
	{
		foreground1Colour = c1;
		foreground2Colour = c2;
		DrawFilledRectangle(xPos, yPos, width, height, thickness);
	}

	void RenderContext::DrawFilledRectangle(const UINT32 xPos, const UINT32 yPos, const UINT32 width, const UINT32 height, const UINT32 thickness, const Colour* c1, const Colour* c2)
	{
		foreground1Colour = *c1;
		foreground2Colour = *c2;
		DrawFilledRectangle(xPos, yPos, width, height, thickness);
	}

	void RenderContext::DrawFilledRectangle(const UINT32 xPos, const UINT32 yPos, const UINT32 width, const UINT32 height, const UINT32 thickness, const UINT32 c1, const UINT32 c2)
	{
		foreground1Colour = Colour(c1);
		foreground2Colour = Colour(c2);
		DrawFilledRectangle(xPos, yPos, width, height, thickness);
	}

	void RenderContext::DrawFilledRectangle(const UINT32 xPos, const UINT32 yPos, const UINT32 width, const UINT32 height, const UINT32 thickness, const UINT32 c1R, const UINT32 c1G, const UINT32 c1B, const UINT32 c1A, const UINT32 c2R, const UINT32 c2G, const UINT32 c2B, const UINT32 c2A)
	{
		foreground1Colour = Colour(c1R, c1G, c1B, c1A);
		foreground2Colour = Colour(c2R, c2G, c2B, c2A);
		DrawFilledRectangle(xPos, yPos, width, height, thickness);
	}

	void RenderContext::DrawLine(const UINT32 sXPos, const UINT32 sYPos, const UINT32 eXPos, const UINT32 eYPos, const UINT32 thickness)
	{
	}

	void RenderContext::DrawLine(const UINT32 sXPos, const UINT32 sYPos, const UINT32 eXPos, const UINT32 eYPos, const UINT32 thickness,const Colour colour)
	{
	}

	void RenderContext::DrawLine(const UINT32 sXPos, const UINT32 sYPos, const UINT32 eXPos, const UINT32 eYPos, const UINT32 thickness, const Colour* colour)
	{
	}

	void RenderContext::DrawLine(const UINT32 sXPos, const UINT32 sYPos, const UINT32 eXPos, const UINT32 eYPos, const UINT32 thickness, const UINT32 colour)
	{
	}

	void RenderContext::DrawLine(const UINT32 sXPos, const UINT32 sYPos, const UINT32 eXPos, const UINT32 eYPos, const UINT32 thickness, const UINT32 r, const UINT32 g, const UINT32 b, const UINT32 a)
	{
	}

	void RenderContext::DrawRectangle(const UINT32 xPos, const UINT32 yPos, const UINT32 width, const UINT32 height)
	{
		VOID_PTR fb = monitor.GetFrameBuffer();
		UINT32 ppsl = monitor.GetPixelsPerScanLine();
		PixelFormat pf = monitor.GetPixelFormat();

		switch (pf)
		{
		case Common::Graphics::RedGreenBlueReserved8BitPerColor:
		{
			/*Get X and Y Pos in Buffer*/
			Pixel1Bpp c2P = Pixel1Bpp(backgroundColour.Red, backgroundColour.Green, backgroundColour.Blue, backgroundColour.Alpha);

			SetRectangle<Pixel1Bpp>(xPos, yPos, width, height, ppsl, (Pixel1Bpp*)fb, c2P);
			return;
		}
		case Common::Graphics::BlueGreenRedReserved8BitPerColor:
		{
			Pixel1Bpp c2P = Pixel1Bpp(backgroundColour.Blue, backgroundColour.Green, backgroundColour.Red, backgroundColour.Alpha);
			SetRectangle<Pixel1Bpp>(xPos, yPos, width, height, ppsl, (Pixel1Bpp*)fb, c2P);
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

	void RenderContext::DrawRectangle(const UINT32 xPos, const UINT32 yPos, const UINT32 width, const UINT32 height,const Colour colour)
	{
		backgroundColour = colour;
		DrawRectangle(xPos, yPos, width, height);
	}

	void RenderContext::DrawRectangle(const UINT32 xPos, const UINT32 yPos, const UINT32 width, const UINT32 height, const Colour* colour)
	{
		backgroundColour = *colour;
		DrawRectangle(xPos, yPos, width, height);
	}

	void RenderContext::DrawRectangle(const UINT32 xPos, const UINT32 yPos, const UINT32 width, const UINT32 height, const UINT32 colour)
	{
		backgroundColour = Colour(colour);
		DrawRectangle(xPos, yPos, width, height);
	}

	void RenderContext::DrawRectangle(const UINT32 xPos, const UINT32 yPos, const UINT32 width, const UINT32 height, const UINT32 r, const UINT32 g, const UINT32 b, const UINT32 a)
	{
		backgroundColour = Colour(r, g, b, a);
		DrawRectangle(xPos, yPos, width, height);
	}

	void RenderContext::SetBackgroundColour(Colour colour)
	{
		backgroundColour = colour;
	}

	void RenderContext::SetBackgroundColour(const Colour* colour)
	{
		backgroundColour = *colour;
	}

	void RenderContext::SetBackgroundColour(const UINT32 colour)
	{
		backgroundColour = Colour(colour);
	}

	void RenderContext::SetBackgroundColour(const UINT32 r, const UINT32 g, const UINT32 b, const UINT32 a)
	{
		backgroundColour = Colour(r, g, b, a);
	}

	void RenderContext::SetForeground1Colour(Colour colour)
	{
		foreground1Colour = colour;
	}

	void RenderContext::SetForeground1Colour(const Colour* colour)
	{
		foreground1Colour = *colour;
	}

	void RenderContext::SetForeground1Colour(const UINT32 colour)
	{
		foreground1Colour = Colour(colour);
	}

	void RenderContext::SetForeground1Colour(const UINT32 r, const UINT32 g, const UINT32 b, const UINT32 a)
	{
		foreground1Colour = Colour(r, g, b, a);
	}

	void RenderContext::SetForeground2Colour(Colour colour)
	{
		foreground2Colour = colour;
	}

	void RenderContext::SetForeground2Colour(const Colour* colour)
	{
		foreground2Colour = *colour;
	}

	void RenderContext::SetForeground2Colour(const UINT32 colour)
	{
		foreground2Colour = Colour(colour);
	}

	void RenderContext::SetForeground2Colour(const UINT32 r, const UINT32 g, const UINT32 b, const UINT32 a)
	{
		foreground2Colour = Colour(r, g, b, a);
	}

	void RenderContext::SetTextColour(Colour colour)
	{
		textColour = colour;
	}

	void RenderContext::SetTextColour(const Colour* colour)
	{
		textColour = *colour;
	}

	void RenderContext::SetTextColour(const UINT32 colour)
	{
		textColour = Colour(colour);
	}

	void RenderContext::SetTextColour(const UINT32 r, const UINT32 g, const UINT32 b, const UINT32 a)
	{
		textColour = Colour(r, g, b, a);
	}

	void RenderContext::SetPixelBackgroundColour(const UINT32 xPos, const UINT32 yPos)
	{
		VOID_PTR fb = monitor.GetFrameBuffer();
		UINTN ppsl = monitor.GetPixelsPerScanLine();
		PixelFormat pf = monitor.GetPixelFormat();

		UINTN pos = CalculatePixelOffset(xPos, yPos, ppsl);

		switch (pf)
		{
		case Common::Graphics::RedGreenBlueReserved8BitPerColor:
		{
			Pixel1Bpp c2P = Pixel1Bpp(backgroundColour.Red, backgroundColour.Green, backgroundColour.Blue, backgroundColour.Alpha);
			((Pixel1Bpp*)fb)[pos] = c2P;
			return;
		}
		case Common::Graphics::BlueGreenRedReserved8BitPerColor:
		{
			Pixel1Bpp c2P = Pixel1Bpp(backgroundColour.Blue, backgroundColour.Green, backgroundColour.Red, backgroundColour.Alpha);
			((Pixel1Bpp*)fb)[pos] = c2P;
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

	void RenderContext::SetPixelRowBackgroundColour(const UINT32 xPos, const UINT32 yPos, const UINT32 length)
	{
		VOID_PTR fb = monitor.GetFrameBuffer();
		PixelFormat pf = monitor.GetPixelFormat();
		UINTN ppsl = monitor.GetPixelsPerScanLine();

		UINTN pos = CalculatePixelOffset(xPos, yPos, ppsl);
		UINTN end = pos + length;

		/*
		*  Calculate the pixel position in the frame buffer, and set theconst Colour of the pixel
		*/

		switch (pf)
		{
		case Common::Graphics::RedGreenBlueReserved8BitPerColor:
		{
			Pixel1Bpp p = Pixel1Bpp(backgroundColour.Red, backgroundColour.Green, backgroundColour.Blue, backgroundColour.Alpha);
			for (UINTN i = pos; i < end; i++)
			{
				((Pixel1Bpp*)fb)[i] = p;
			}
			return;
		}
		case Common::Graphics::BlueGreenRedReserved8BitPerColor:
		{
			Pixel1Bpp p = Pixel1Bpp(backgroundColour.Blue, backgroundColour.Green, backgroundColour.Red, backgroundColour.Alpha);
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

	void RenderContext::SetPixelRowBackgroundColour(const UINT32 xPos, const UINT32 yPos, const UINT32 length,const Colour colour)
	{
		backgroundColour = colour;
		SetPixelRowBackgroundColour(xPos, yPos, length);
	}

	void RenderContext::SetPixelRowBackgroundColour(const UINT32 xPos, const UINT32 yPos, const UINT32 length, const Colour* colour)
	{
		backgroundColour = *colour;
		SetPixelRowBackgroundColour(xPos, yPos, length);
	}

	void RenderContext::SetPixelRowBackgroundColour(const UINT32 xPos, const UINT32 yPos, const UINT32 length, const UINT32 colour)
	{
		backgroundColour = Colour(colour);
		SetPixelRowBackgroundColour(xPos, yPos, length);
	}

	void RenderContext::SetPixelRowBackgroundColour(const UINT32 xPos, const UINT32 yPos, const UINT32 length, const UINT32 r, const UINT32 g, const UINT32 b, const UINT32 a)
	{
		backgroundColour = Colour(r, g, b, a);
		SetPixelRowBackgroundColour(xPos, yPos, length);
	}

	void RenderContext::SetPixelBackgroundColour(const UINT32 xPos, const UINT32 yPos,const Colour colour)
	{
		backgroundColour = colour;
		SetPixelBackgroundColour(xPos, yPos);
	}

	void RenderContext::SetPixelBackgroundColour(const UINT32 xPos, const UINT32 yPos, const Colour* colour)
	{
		backgroundColour = *colour;
		SetPixelBackgroundColour(xPos, yPos);
	}

	void RenderContext::SetPixelBackgroundColour(const UINT32 xPos, const UINT32 yPos, const UINT32 colour)
	{
		backgroundColour = Colour(colour);
		SetPixelBackgroundColour(xPos, yPos);
	}

	void RenderContext::SetPixelBackgroundColour(const UINT32 xPos, const UINT32 yPos, const UINT32 r, const UINT32 g, const UINT32 b, const UINT32 a)
	{
		backgroundColour = Colour(r, g, b, a);
		SetPixelBackgroundColour(xPos, yPos);
	}

	void RenderContext::SetPixelForeground1Colour(const UINT32 xPos, const UINT32 yPos)
	{
		VOID_PTR fb = monitor.GetFrameBuffer();
		UINTN ppsl = monitor.GetPixelsPerScanLine();
		PixelFormat pf = monitor.GetPixelFormat();

		UINTN pos = CalculatePixelOffset(xPos, yPos, ppsl);

		switch (pf)
		{
		case Common::Graphics::RedGreenBlueReserved8BitPerColor:
		{
			Pixel1Bpp c2P = Pixel1Bpp(foreground1Colour.Red, foreground1Colour.Green, foreground1Colour.Blue, foreground1Colour.Alpha);
			((Pixel1Bpp*)fb)[pos] = c2P;
			return;
		}
		case Common::Graphics::BlueGreenRedReserved8BitPerColor:
		{
			Pixel1Bpp c2P = Pixel1Bpp(foreground1Colour.Blue, foreground1Colour.Green, foreground1Colour.Red, foreground1Colour.Alpha);
			((Pixel1Bpp*)fb)[pos] = c2P;
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

	void RenderContext::SetPixelRowForeground1Colour(const UINT32 xPos, const UINT32 yPos, const UINT32 length)
	{
		VOID_PTR fb = monitor.GetFrameBuffer();
		PixelFormat pf = monitor.GetPixelFormat();
		UINTN ppsl = monitor.GetPixelsPerScanLine();

		UINTN pos = CalculatePixelOffset(xPos, yPos, ppsl);
		UINTN end = pos + length;

		switch (pf)
		{
		case Common::Graphics::RedGreenBlueReserved8BitPerColor:
		{
			Pixel1Bpp p = Pixel1Bpp(foreground1Colour.Red, foreground1Colour.Green, foreground1Colour.Blue, foreground1Colour.Alpha);
			for (UINTN i = pos; i < end; i++)
			{
				((Pixel1Bpp*)fb)[i] = p;
			}
			return;
		}
		case Common::Graphics::BlueGreenRedReserved8BitPerColor:
		{
			Pixel1Bpp p = Pixel1Bpp(foreground1Colour.Blue, foreground1Colour.Green, foreground1Colour.Red, foreground1Colour.Alpha);
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

	void RenderContext::SetPixelForeground1Colour(const UINT32 xPos, const UINT32 yPos,const Colour colour)
	{
		foreground1Colour = colour;
		SetPixelForeground1Colour(xPos, yPos);
	}

	void RenderContext::SetPixelForeground1Colour(const UINT32 xPos, const UINT32 yPos, const Colour* colour)
	{
		foreground1Colour = *colour;
		SetPixelForeground1Colour(xPos, yPos);
	}

	void RenderContext::SetPixelForeground1Colour(const UINT32 xPos, const UINT32 yPos, const UINT32 colour)
	{
		foreground1Colour = Colour(colour);
		SetPixelForeground1Colour(xPos, yPos);
	}

	void RenderContext::SetPixelForeground1Colour(const UINT32 xPos, const UINT32 yPos, const UINT32 r, const UINT32 g, const UINT32 b, const UINT32 a)
	{
		foreground1Colour = Colour(r, g, b, a);
		SetPixelForeground1Colour(xPos, yPos);
	}

	void RenderContext::Terminate(EFI::EFI_HANDLE hnd, EFI::EFI_SYSTEM_TABLE* sysTable)
	{
		monitor.Terminate();
		sysTable->BootServices->CloseProtocol(sysTable->ConsoleOutHandle, &EFI::EFI_GRAPHICS_OUTPUT_PROTOCOL_GUID, hnd, nullptr);
	};

	void RenderContext::SetPixelRowForeground1Colour(const UINT32 xPos, const UINT32 yPos, const UINT32 length,const Colour colour)
	{
		foreground1Colour = colour;
		SetPixelRowForeground1Colour(xPos, yPos, length);
	}
	void RenderContext::SetPixelRowForeground1Colour(const UINT32 xPos, const UINT32 yPos, const UINT32 length, const Colour* colour)
	{
		foreground1Colour = *colour;
		SetPixelRowForeground1Colour(xPos, yPos, length);
	}
	void RenderContext::SetPixelRowForeground1Colour(const UINT32 xPos, const UINT32 yPos, const UINT32 length, const UINT32 colour)
	{
		foreground1Colour = Colour(colour);
		SetPixelRowForeground1Colour(xPos, yPos, length);
	}
	void RenderContext::SetPixelRowForeground1Colour(const UINT32 xPos, const UINT32 yPos, const UINT32 length, const UINT32 r, const UINT32 g, const UINT32 b, const UINT32 a)
	{
		foreground1Colour = Colour(r, g, b, a);
		SetPixelRowForeground1Colour(xPos, yPos, length);
	}

	void RenderContext::SetPixelRowForeground2Colour(const UINT32 xPos, const UINT32 yPos, const UINT32 length,const Colour colour)
	{
		foreground2Colour = colour;
		SetPixelRowForeground2Colour(xPos, yPos, length);
	}
	void RenderContext::SetPixelRowForeground2Colour(const UINT32 xPos, const UINT32 yPos, const UINT32 length, const Colour* colour)
	{
		foreground2Colour = *colour;
		SetPixelRowForeground2Colour(xPos, yPos, length);
	}
	void RenderContext::SetPixelRowForeground2Colour(const UINT32 xPos, const UINT32 yPos, const UINT32 length, const UINT32 colour)
	{
		foreground2Colour = Colour(colour);
		SetPixelRowForeground2Colour(xPos, yPos, length);
	}
	void RenderContext::SetPixelRowForeground2Colour(const UINT32 xPos, const UINT32 yPos, const UINT32 length, const UINT32 r, const UINT32 g, const UINT32 b, const UINT32 a)
	{
		foreground2Colour = Colour(r, g, b, a);
		SetPixelRowForeground2Colour(xPos, yPos, length);
	}

	void RenderContext::SetPixelRowTextColour(const UINT32 xPos, const UINT32 yPos, const UINT32 length)
	{
		VOID_PTR fb = monitor.GetFrameBuffer();
		PixelFormat pf = monitor.GetPixelFormat();
		UINTN ppsl = monitor.GetPixelsPerScanLine();

		UINTN pos = CalculatePixelOffset(xPos, yPos, ppsl);
		UINTN end = pos + length;

		switch (pf)
		{
		case Common::Graphics::RedGreenBlueReserved8BitPerColor:
		{
			Pixel1Bpp p = Pixel1Bpp(textColour.Red, textColour.Green, textColour.Blue, textColour.Alpha);
			for (UINTN i = pos; i < end; i++)
			{
				((Pixel1Bpp*)fb)[i] = p;
			}
			return;
		}
		case Common::Graphics::BlueGreenRedReserved8BitPerColor:
		{
			Pixel1Bpp p = Pixel1Bpp(textColour.Blue, textColour.Green, textColour.Red, textColour.Alpha);
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

	void RenderContext::SetPixelRowTextColour(const UINT32 xPos, const UINT32 yPos, const UINT32 length, const Colour colour)
	{
		textColour = colour;
		SetPixelRowTextColour(xPos, yPos, length);
	}

	void RenderContext::SetPixelRowTextColour(const UINT32 xPos, const UINT32 yPos, const UINT32 length, const Colour* colour)
	{
		textColour = *colour;
		SetPixelRowTextColour(xPos, yPos, length);
	}

	void RenderContext::SetPixelRowTextColour(const UINT32 xPos, const UINT32 yPos, const UINT32 length, const UINT32 colour)
	{
		textColour = Colour(colour);
		SetPixelRowTextColour(xPos, yPos, length);
	}

	void RenderContext::SetPixelRowTextColour(const UINT32 xPos, const UINT32 yPos, const UINT32 length, const UINT32 r, const UINT32 g, const UINT32 b, const UINT32 a)
	{
		textColour = Colour(r, g, b, a);
		SetPixelRowTextColour(xPos, yPos, length);
	}

	void RenderContext::SetPixelForeground2Colour(const UINT32 xPos, const UINT32 yPos)
	{
		VOID_PTR fb = monitor.GetFrameBuffer();
		const UINTN ppsl = monitor.GetPixelsPerScanLine();
		PixelFormat pf = monitor.GetPixelFormat();

		const UINTN pos = CalculatePixelOffset(xPos, yPos, ppsl);

		switch (pf)
		{
		case Common::Graphics::RedGreenBlueReserved8BitPerColor:
		{
			Pixel1Bpp c2P = Pixel1Bpp(foreground2Colour.Red, foreground2Colour.Green, foreground2Colour.Blue, foreground2Colour.Alpha);
			((Pixel1Bpp*)fb)[pos] = c2P;
			return;
		}
		case Common::Graphics::BlueGreenRedReserved8BitPerColor:
		{
			Pixel1Bpp c2P = Pixel1Bpp(foreground2Colour.Blue, foreground2Colour.Green, foreground2Colour.Red, foreground2Colour.Alpha);
			((Pixel1Bpp*)fb)[pos] = c2P;
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

	void RenderContext::SetPixelRowForeground2Colour(const UINT32 xPos, const UINT32 yPos, const UINT32 length)
	{
		VOID_PTR fb = monitor.GetFrameBuffer();
		PixelFormat pf = monitor.GetPixelFormat();
		UINTN ppsl = monitor.GetPixelsPerScanLine();

		UINTN pos = CalculatePixelOffset(xPos, yPos, ppsl);
		UINTN end = pos + length;

		switch (pf)
		{
		case Common::Graphics::RedGreenBlueReserved8BitPerColor:
		{
			Pixel1Bpp p = Pixel1Bpp(foreground2Colour.Red, foreground2Colour.Green, foreground2Colour.Blue, foreground2Colour.Alpha);
			for (UINTN i = pos; i < end; i++)
			{
				((Pixel1Bpp*)fb)[i] = p;
			}
			return;
		}
		case Common::Graphics::BlueGreenRedReserved8BitPerColor:
		{
			Pixel1Bpp p = Pixel1Bpp(foreground2Colour.Blue, foreground2Colour.Green, foreground2Colour.Red, foreground2Colour.Alpha);
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

	void RenderContext::SetPixelForeground2Colour(const UINT32 xPos, const UINT32 yPos,const Colour colour)
	{
		foreground2Colour = colour;
		SetPixelForeground2Colour(xPos, yPos);
	}

	void RenderContext::SetPixelForeground2Colour(const UINT32 xPos, const UINT32 yPos, const Colour* colour)
	{
		foreground2Colour = *colour;
		SetPixelForeground2Colour(xPos, yPos);
	}

	void RenderContext::SetPixelForeground2Colour(const UINT32 xPos, const UINT32 yPos, const UINT32 colour)
	{
		foreground2Colour = Colour(colour);
		SetPixelForeground2Colour(xPos, yPos);
	}

	void RenderContext::SetPixelForeground2Colour(const UINT32 xPos, const UINT32 yPos, const UINT32 r, const UINT32 g, const UINT32 b, const UINT32 a)
	{
		foreground2Colour = Colour(r, g, b, a);
		SetPixelForeground2Colour(xPos, yPos);
	}

	void RenderContext::SetPixelTextColour(const UINT32 xPos, const UINT32 yPos)
	{
		VOID_PTR fb = monitor.GetFrameBuffer();
		const UINTN ppsl = monitor.GetPixelsPerScanLine();
		PixelFormat pf = monitor.GetPixelFormat();

		const UINTN pos = CalculatePixelOffset(xPos, yPos, ppsl);

		switch (pf)
		{
		case Common::Graphics::RedGreenBlueReserved8BitPerColor:
		{
			Pixel1Bpp c2P = Pixel1Bpp(textColour.Red, textColour.Green, textColour.Blue, textColour.Alpha);
			((Pixel1Bpp*)fb)[pos] = c2P;
			return;
		}
		case Common::Graphics::BlueGreenRedReserved8BitPerColor:
		{
			Pixel1Bpp c2P = Pixel1Bpp(textColour.Blue, textColour.Green, textColour.Red, textColour.Alpha);
			((Pixel1Bpp*)fb)[pos] = c2P;
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

	void RenderContext::SetPixelTextColour(const UINT32 xPos, const UINT32 yPos, const Colour colour)
	{
		textColour = colour;
		SetPixelTextColour(xPos, yPos);
	}

	void RenderContext::SetPixelTextColour(const UINT32 xPos, const UINT32 yPos, const Colour* colour)
	{
		textColour = *colour;
		SetPixelTextColour(xPos, yPos);
	}

	void RenderContext::SetPixelTextColour(const UINT32 xPos, const UINT32 yPos, const UINT32 colour)
	{
		textColour = Colour(colour);
		SetPixelTextColour(xPos, yPos);
	}

	void RenderContext::SetPixelTextColour(const UINT32 xPos, const UINT32 yPos, const UINT32 r, const UINT32 g, const UINT32 b, const UINT32 a)
	{
		textColour = Colour(r, g, b, a);
		SetPixelTextColour(xPos, yPos);
	}

	MonitorContext* RenderContext::GetMonitorContext()
	{
		return &monitor;
	}
}