#include "RenderContext.h"
#include <Status.h>
#include <LocateSearchType.h>
#include <Guid.h>

#include <Protocols/Graphics/GraphicsOutputProtocol.h>

#include <System/MemoryManagement/Allocator.h>

#include <System/Environment/Unicode.h>


namespace Common::Graphics
{
	inline UINT64 CalculatePixelOffset(const UINT64 x, const UINT64 y, const UINT64 ppsl)
	{
		/*calculate the address offset of the pixel in the buffer*/
		return (y * ppsl) + x;
	}

	template<typename Pixel>
	void _SetRectangle(const UINT64 x1, const UINT64 y1, const UINT64 width, const UINT64 height, const UINT64 ppsl, Pixel* fb, const Pixel& p)
	{
		UINT64 yMax = y1 + height;
		UINT64 xMax = x1 + width;

		/*Draw the rectangle*/
		for (UINT64 y = y1; y < yMax; y++)
		{
			UINT64 row = CalculatePixelOffset(x1, y, ppsl);
			Pixel* pRow = &fb[row];
			for (UINT64 x = x1; x < xMax; x++)
			{
				pRow[x] = p;
			}
		}
	}

	template<typename Pixel>
	void _SetFilledRectangle(const UINT64 x1, const UINT64 y1, const UINT64 width1, const UINT64 height1, const UINT64 x2, const UINT64 y2, const UINT64 width2, const UINT64 height2, const UINT64 ppsl, Pixel* fb, const Pixel& c2P, const Pixel& c1P)
	{
		UINT64 yMax1 = y1 + height1;
		UINT64 xMax1 = x1 + width1;

		UINT64 yMax2 = y2 + height2;
		UINT64 xMax2 = x2 + width2;

		/*Draw the rectangle*/
		for (UINT64 y = y1; y < yMax1; y++)
		{
			/*Find the start of the row and set a pointer before doing the loop*/
			UINT64 row = CalculatePixelOffset(0, y, ppsl);
			Pixel* pRow = &fb[row];
			for (UINT64 x = x1; x < xMax1; x++)
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

	template<typename Pixel, typename CharWidth>
	void _drawChar(const UINT64 width, const UINT64 height, const CharWidth* charPtr, const UINT64 xPos, const UINT64 yPos, const UINT64 ppsl, Pixel* fb, const Pixel& txtColor)
	{
		CharWidth* cPtr = (CharWidth*)charPtr;
		for (UINT64 y = 0; y < height; y++)
		{
			UINT64 row = CalculatePixelOffset(xPos, yPos + y, ppsl);
			Pixel* pRow = &((Pixel*)fb)[row];
			for (UINT64 x = 0; x < width; x++)
			{
				if (cPtr[y] & 1ULL << x)
				{
					pRow[x] = txtColor;
				}
			}
		}
	}

	template<typename Pixel>
	void _SetPixel(const UINT64 xPos, const UINT64 yPos, const UINT64 ppsl, Pixel* fb, const Pixel& p)
	{
		fb[CalculatePixelOffset(xPos, yPos, ppsl)] = p;
	}

	template<typename Pixel>
	void _SetPixelRow(const UINT64 xPos, const UINT64 yPos, const UINT64 width, const UINT64 ppsl, Pixel* fb, const Pixel& p)
	{
		for (UINT64 x = xPos; x < xPos + width; x++)
		{
			_SetPixel<Pixel>(x, yPos, ppsl, fb, p);
		}
	}


	RenderContext::RenderContext(Efi::GraphicsOutputProtocol* ptr, const Colour txt, const Colour bg, const Colour fg1, const Colour fg2)
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

		pcsf1 = nullptr;
		pcsf2 = nullptr;
	}

	RenderContext* RenderContext::Initialize(Efi::SystemTable* sysTbl, Efi::Handle imgHndl, const Colour txt, const Colour bg, const Colour fg1, const Colour fg2)
	{
		Efi::GraphicsOutputProtocol* gop = nullptr;
		// Locate the GOP protocol and store it in the gop variable, use locate protocol first then try to locate handle Buffer if that fails, if that fails then return the error
		Efi::Status LastStatus = sysTbl->BootServices->LocateProtocol(&Efi::GraphicsOutputProtocol_GUID, nullptr, (void**)&gop);

		if (LastStatus == Efi::Status::Success)
		{
			return new RenderContext(gop, txt, bg, fg1, fg2);
		}

		UINT64 handleCount = 0;
		Efi::Handle* handleBuffer;
		LastStatus = sysTbl->BootServices->LocateHandleBuffer(Efi::LocateSearchType::ByProtocol, &Efi::GraphicsOutputProtocol_GUID, nullptr, &handleCount, &handleBuffer);

		sysTbl->ConOut->OutputString(sysTbl->ConOut, Common::System::Environment::UTF<CHAR16>::ToString(handleCount));

		if (LastStatus != Efi::Status::Success)
		{
			return nullptr;
		}

		LastStatus = sysTbl->BootServices->OpenProtocol(handleBuffer[0], &Efi::GraphicsOutputProtocol_GUID, (void**)&gop, imgHndl, nullptr, Efi::Services::OpenProtocolGetProtocol);

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
		Pixel1Bpp* fb = (Pixel1Bpp*)monitor.GetFrameBuffer();
		const UINT64 fbSize = monitor.GetFrameBufferSize();
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

		Pixel1Bpp bg;

		switch (pf)
		{
		case Common::Graphics::RedGreenBlueReserved8BitPerColor:
		{
			bg = Pixel1Bpp(backgroundColour.Red, backgroundColour.Green, backgroundColour.Blue, backgroundColour.Alpha);
			break;
		}
		case Common::Graphics::BlueGreenRedReserved8BitPerColor:
		{
			bg = Pixel1Bpp(backgroundColour.Blue, backgroundColour.Green, backgroundColour.Red, backgroundColour.Alpha);
			break;
		}

		default:
			return;
		}

		for (UINT64 i = 0; i < fbSize; i++)
		{
			fb[i] = bg;
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

	void RenderContext::ClearScreen(const UINT8 r, const UINT8 g, const UINT8 b, const UINT8 a)
	{
		backgroundColour = Colour(r, g, b, a);
		ClearScreen();
	}

	void RenderContext::DrawCircle(const UINT64 xPos, const UINT64 yPos, const UINT64 radius, const UINT64 thickness)
	{
	}

	void RenderContext::DrawCircle(const UINT64 xPos, const UINT64 yPos, const UINT64 radius, const UINT64 thickness, const Colour colour)
	{
	}

	void RenderContext::DrawCircle(const UINT64 xPos, const UINT64 yPos, const UINT64 radius, const UINT64 thickness, const Colour* colour)
	{
	}

	void RenderContext::DrawCircle(const UINT64 xPos, const UINT64 yPos, const UINT64 radius, const UINT64 thickness, const UINT32 colour)
	{
	}

	void RenderContext::DrawCircle(const UINT64 xPos, const UINT64 yPos, const UINT64 radius, const UINT64 thickness, const UINT8 r, const UINT8 g, const UINT8 b, const UINT8 a)
	{
	}

	void RenderContext::DrawFilledCircle(const UINT64 xPos, const UINT64 yPos, const UINT64 radius)
	{
	}

	void RenderContext::DrawFilledCircle(const UINT64 xPos, const UINT64 yPos, const UINT64 radius, const Colour colour)
	{
	}

	void RenderContext::DrawFilledCircle(const UINT64 xPos, const UINT64 yPos, const UINT64 radius, const Colour* colour)
	{
	}

	void RenderContext::DrawFilledCircle(const UINT64 xPos, const UINT64 yPos, const UINT64 radius, const UINT32 colour)
	{
	}

	void RenderContext::DrawFilledCircle(const UINT64 xPos, const UINT64 yPos, const UINT64 radius, const UINT8 r, const UINT8 g, const UINT8 b, const UINT8 a)
	{
	}

	void RenderContext::DrawFilledRectangle(const UINT64 xPos, const UINT64 yPos, const UINT64 width, const UINT64 height, const UINT64 thickness)
	{
		Pixel1Bpp* fb = (Pixel1Bpp*)monitor.GetFrameBuffer();
		UINT64 ppsl = monitor.GetPixelsPerScanLine();
		PixelFormat pf = monitor.GetPixelFormat();

		/*Get X and Y Pos in Buffer*/

		UINT64 x2 = xPos + thickness;
		UINT64 y2 = yPos + thickness;

		UINT64 width2 = width - (thickness * 2);
		UINT64 height2 = height - (thickness * 2);

		Pixel1Bpp c2P;
		Pixel1Bpp c1P;

		switch (pf)
		{
		case Common::Graphics::RedGreenBlueReserved8BitPerColor:
		{
			c2P = Pixel1Bpp(foreground2Colour.Red, foreground2Colour.Green, foreground2Colour.Blue, foreground2Colour.Alpha);
			c1P = Pixel1Bpp(foreground1Colour.Red, foreground1Colour.Green, foreground1Colour.Blue, foreground1Colour.Alpha);
			break;
		}
		case Common::Graphics::BlueGreenRedReserved8BitPerColor:
		{
			c2P = Pixel1Bpp(foreground2Colour.Blue, foreground2Colour.Green, foreground2Colour.Red, foreground2Colour.Alpha);
			c1P = Pixel1Bpp(foreground1Colour.Blue, foreground1Colour.Green, foreground1Colour.Red, foreground1Colour.Alpha);
			break;
		}
		default:
			return;
		}

		_SetFilledRectangle<Pixel1Bpp>(xPos, yPos, width, height, x2, y2, width2, height2, ppsl, fb, c2P, c1P);
	}

	void RenderContext::DrawFilledRectangle(const UINT64 xPos, const UINT64 yPos, const UINT64 width, const UINT64 height, const UINT64 thickness, const Colour c1, const Colour c2)
	{
		foreground1Colour = c1;
		foreground2Colour = c2;
		DrawFilledRectangle(xPos, yPos, width, height, thickness);
	}

	void RenderContext::DrawFilledRectangle(const UINT64 xPos, const UINT64 yPos, const UINT64 width, const UINT64 height, const UINT64 thickness, const Colour* c1, const Colour* c2)
	{
		foreground1Colour = *c1;
		foreground2Colour = *c2;
		DrawFilledRectangle(xPos, yPos, width, height, thickness);
	}

	void RenderContext::DrawFilledRectangle(const UINT64 xPos, const UINT64 yPos, const UINT64 width, const UINT64 height, const UINT64 thickness, const UINT32 c1, const UINT32 c2)
	{
		foreground1Colour = Colour(c1);
		foreground2Colour = Colour(c2);
		DrawFilledRectangle(xPos, yPos, width, height, thickness);
	}

	void RenderContext::DrawFilledRectangle(const UINT64 xPos, const UINT64 yPos, const UINT64 width, const UINT64 height, const UINT64 thickness, const UINT8 c1R, const UINT8 c1G, const UINT8 c1B, const UINT8 c1A, const UINT8 c2R, const UINT8 c2G, const UINT8 c2B, const UINT8 c2A)
	{
		foreground1Colour = Colour(c1R, c1G, c1B, c1A);
		foreground2Colour = Colour(c2R, c2G, c2B, c2A);
		DrawFilledRectangle(xPos, yPos, width, height, thickness);
	}

	void RenderContext::DrawLine(const UINT64 sXPos, const UINT64 sYPos, const UINT64 eXPos, const UINT64 eYPos, const UINT64 thickness)
	{
	}

	void RenderContext::DrawLine(const UINT64 sXPos, const UINT64 sYPos, const UINT64 eXPos, const UINT64 eYPos, const UINT64 thickness, const Colour colour)
	{
	}

	void RenderContext::DrawLine(const UINT64 sXPos, const UINT64 sYPos, const UINT64 eXPos, const UINT64 eYPos, const UINT64 thickness, const Colour* colour)
	{
	}

	void RenderContext::DrawLine(const UINT64 sXPos, const UINT64 sYPos, const UINT64 eXPos, const UINT64 eYPos, const UINT64 thickness, const UINT32 colour)
	{
	}

	void RenderContext::DrawLine(const UINT64 sXPos, const UINT64 sYPos, const UINT64 eXPos, const UINT64 eYPos, const UINT64 thickness, const UINT8 r, const UINT8 g, const UINT8 b, const UINT8 a)
	{
	}

	void RenderContext::DrawRectangle(const UINT64 xPos, const UINT64 yPos, const UINT64 width, const UINT64 height)
	{
		Pixel1Bpp* fb = (Pixel1Bpp*)monitor.GetFrameBuffer();
		UINT64 ppsl = monitor.GetPixelsPerScanLine();
		PixelFormat pf = monitor.GetPixelFormat();

		Pixel1Bpp c2P;

		switch (pf)
		{
		case Common::Graphics::RedGreenBlueReserved8BitPerColor:
		{
			c2P = Pixel1Bpp(backgroundColour.Red, backgroundColour.Green, backgroundColour.Blue, backgroundColour.Alpha);
			break;
		}
		case Common::Graphics::BlueGreenRedReserved8BitPerColor:
		{
			c2P = Pixel1Bpp(backgroundColour.Blue, backgroundColour.Green, backgroundColour.Red, backgroundColour.Alpha);
			break;
		}
		default:
			return;
		}

		_SetRectangle<Pixel1Bpp>(xPos, yPos, width, height, ppsl, fb, c2P);
	}

	void RenderContext::DrawRectangle(const UINT64 xPos, const UINT64 yPos, const UINT64 width, const UINT64 height, const Colour colour)
	{
		backgroundColour = colour;
		DrawRectangle(xPos, yPos, width, height);
	}

	void RenderContext::DrawRectangle(const UINT64 xPos, const UINT64 yPos, const UINT64 width, const UINT64 height, const Colour* colour)
	{
		backgroundColour = *colour;
		DrawRectangle(xPos, yPos, width, height);
	}

	void RenderContext::DrawRectangle(const UINT64 xPos, const UINT64 yPos, const UINT64 width, const UINT64 height, const UINT32 colour)
	{
		backgroundColour = Colour(colour);
		DrawRectangle(xPos, yPos, width, height);
	}

	void RenderContext::DrawRectangle(const UINT64 xPos, const UINT64 yPos, const UINT64 width, const UINT64 height, const UINT8 r, const UINT8 g, const UINT8 b, const UINT8 a)
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

	void RenderContext::SetBackgroundColour(const UINT8 r, const UINT8 g, const UINT8 b, const UINT8 a)
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

	void RenderContext::SetForeground1Colour(const UINT8 r, const UINT8 g, const UINT8 b, const UINT8 a)
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

	void RenderContext::SetForeground2Colour(const UINT8 r, const UINT8 g, const UINT8 b, const UINT8 a)
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

	void RenderContext::SetTextColour(const UINT8 r, const UINT8 g, const UINT8 b, const UINT8 a)
	{
		textColour = Colour(r, g, b, a);
	}

	void RenderContext::SetPCSF1Font(Graphics::Font::PCSF::PCSF1* font)
	{
		pcsf1 = font;
	}

	void RenderContext::SetPCSF2Font(Graphics::Font::PCSF::PCSF2* font)
	{
		pcsf2 = font;
	}

	void RenderContext::SetFonts(Graphics::Font::PCSF::PCSF1* pcsf1, Graphics::Font::PCSF::PCSF2* pcsf2)
	{
		pcsf1 = pcsf1;
		pcsf2 = pcsf2;
	}

	void RenderContext::DrawPCSF1Char(const UINT64 xPos, const UINT64 yPos, const CHAR16 c)
	{
		if (pcsf1 == nullptr)
		{
			return;
		}

		Pixel1Bpp* fb = (Pixel1Bpp*)monitor.GetFrameBuffer();
		UINT64 ppsl = monitor.GetPixelsPerScanLine();
		PixelFormat pf = monitor.GetPixelFormat();

		switch (pf)
		{
		case Common::Graphics::RedGreenBlueReserved8BitPerColor:
		{
			Pixel1Bpp txtCol = Pixel1Bpp(textColour.Red, textColour.Green, textColour.Blue, textColour.Alpha);
			_drawChar<Pixel1Bpp, UINT8>((UINT64)pcsf1->Header.CharSize, (UINT64)pcsf1->Header.CharSize, pcsf1->GetGlyph((UINT16)c), xPos, yPos, ppsl, fb, txtCol);
			return;
		}
		case Common::Graphics::BlueGreenRedReserved8BitPerColor:
		{
			Pixel1Bpp txtCol = Pixel1Bpp(textColour.Blue, textColour.Green, textColour.Red, textColour.Alpha);
			_drawChar<Pixel1Bpp, UINT8>((UINT64)pcsf1->Header.CharSize, (UINT64)pcsf1->Header.CharSize, pcsf1->GetGlyph((UINT16)c), xPos, yPos, ppsl, fb, txtCol);
		}
		}
		return;
	}

	void RenderContext::DrawPCSF1Char(const UINT64 xPos, const UINT64 yPos, const CHAR16 c, const Colour colour)
	{
		if (pcsf1 == nullptr)
		{
			return;
		}
		textColour = colour;
		DrawPCSF1Char(xPos, yPos, c);
	}

	void RenderContext::DrawPCSF1Char(const UINT64 xPos, const UINT64 yPos, const CHAR16 c, const Colour* colour)
	{
		if (pcsf1 == nullptr)
		{
			return;
		}
		textColour = *colour;
		DrawPCSF1Char(xPos, yPos, c);

	}

	void RenderContext::DrawPCSF1Char(const UINT64 xPos, const UINT64 yPos, const CHAR16 c, const UINT32 colour)
	{
		if (pcsf1 == nullptr)
		{
			return;
		}
		textColour = Colour(colour);
		DrawPCSF1Char(xPos, yPos, c);
	}

	void RenderContext::DrawPCSF1Char(const UINT64 xPos, const UINT64 yPos, const CHAR16 c, const UINT8 r, const UINT8 g, const UINT8 b, const UINT8 a)
	{
		if (pcsf1 == nullptr)
		{
			return;
		}
		textColour = Colour(r, g, b, a);
		DrawPCSF1Char(xPos, yPos, c);
	}

	void RenderContext::DrawPCSF2Char(const UINT64 xPos, const UINT64 yPos, const CHAR16 c)
	{
		if (pcsf2 == nullptr)
		{
			return;
		}
		Pixel1Bpp* fb = (Pixel1Bpp*)monitor.GetFrameBuffer();
		UINT64 ppsl = monitor.GetPixelsPerScanLine();
		PixelFormat pf = monitor.GetPixelFormat();

		UINT64 width = pcsf2->Header.Width;
		UINT64 height = pcsf2->Header.Height;

		Pixel1Bpp txtCol;

		switch (pf)
		{
		case Common::Graphics::RedGreenBlueReserved8BitPerColor:
			txtCol = Pixel1Bpp(textColour.Red, textColour.Green, textColour.Blue, textColour.Alpha);
			break;
		case Common::Graphics::BlueGreenRedReserved8BitPerColor:
			txtCol = Pixel1Bpp(textColour.Blue, textColour.Green, textColour.Red, textColour.Alpha);
			break;
		default:
			return;
		}

		if (width >= 1 && width <= 8)
		{
			_drawChar<Pixel1Bpp, UINT8>(width, height, pcsf2->GetGlyph8((UINT16)c), xPos, yPos, ppsl, fb, txtCol);
		}
		else if (width >= 9 && width <= 16)
		{
			_drawChar<Pixel1Bpp, UINT16>(width, height, pcsf2->GetGlyph16((UINT16)c), xPos, yPos, ppsl, fb, txtCol);
		}
		else if (width >= 17 && width <= 32)
		{
			_drawChar<Pixel1Bpp, UINT32>(width, height, pcsf2->GetGlyph32((UINT16)c), xPos, yPos, ppsl, fb, txtCol);
		}
		else if (width >= 33 && width <= 64)
		{
			_drawChar<Pixel1Bpp, UINT64>(width, height, pcsf2->GetGlyph64((UINT16)c), xPos, yPos, ppsl, fb, txtCol);
		}
		else
		{
			return;
		}
	}

	void RenderContext::DrawPCSF2Char(const UINT64 xPos, const UINT64 yPos, const CHAR16 c, const Colour colour)
	{
		if (pcsf2 == nullptr)
		{
			return;
		}
		textColour = colour;
		DrawPCSF2Char(xPos, yPos, c);
	}

	void RenderContext::DrawPCSF2Char(const UINT64 xPos, const UINT64 yPos, const CHAR16 c, const Colour* colour)
	{
		if (pcsf2 == nullptr)
		{
			return;
		}
		textColour = *colour;
		DrawPCSF2Char(xPos, yPos, c);
	}

	void RenderContext::DrawPCSF2Char(const UINT64 xPos, const UINT64 yPos, const CHAR16 c, const UINT32 colour)
	{
		if (pcsf2 == nullptr)
		{
			return;
		}
		textColour = Colour(colour);
		DrawPCSF2Char(xPos, yPos, c);
	}

	void RenderContext::DrawPCSF2Char(const UINT64 xPos, const UINT64 yPos, const CHAR16 c, const UINT8 r, const UINT8 g, const UINT8 b, const UINT8 a)
	{
		if (pcsf2 == nullptr)
		{
			return;
		}
		textColour = Colour(r, g, b, a);
		DrawPCSF2Char(xPos, yPos, c);
	}

	void RenderContext::DrawPCSF1Char(const UINT64 xPos, const UINT64 yPos, const CHAR8 c)
	{
		if (pcsf1 == nullptr)
		{
			return;
		}

		DrawPCSF1Char(xPos, yPos, (CHAR16)c);
	}

	void RenderContext::DrawPCSF1Char(const UINT64 xPos, const UINT64 yPos, const CHAR8 c, const Colour colour)
	{
		if (pcsf1 == nullptr)
		{
			return;
		}

		textColour = colour;
		DrawPCSF1Char(xPos, yPos, (CHAR16)c);
	}

	void RenderContext::DrawPCSF1Char(const UINT64 xPos, const UINT64 yPos, const CHAR8 c, const Colour* colour)
	{
		if (pcsf1 == nullptr)
		{
			return;
		}

		textColour = *colour;
		DrawPCSF1Char(xPos, yPos, (CHAR16)c);
	}

	void RenderContext::DrawPCSF1Char(const UINT64 xPos, const UINT64 yPos, const CHAR8 c, const UINT32 colour)
	{
		if (pcsf1 == nullptr)
		{
			return;
		}

		textColour = Colour(colour);
		DrawPCSF1Char(xPos, yPos, (CHAR16)c);

	}

	void RenderContext::DrawPCSF1Char(const UINT64 xPos, const UINT64 yPos, const CHAR8 c, const UINT8 r, const UINT8 g, const UINT8 b, const UINT8 a)
	{
		if (pcsf1 == nullptr)
		{
			return;
		}

		textColour = Colour(r, g, b, a);
		DrawPCSF1Char(xPos, yPos, (CHAR16)c);
	}

	void RenderContext::DrawPCSF2Char(const UINT64 xPos, const UINT64 yPos, const CHAR8 c)
	{
		if (pcsf2 == nullptr)
		{
			return;
		}

		DrawPCSF2Char(xPos, yPos, (CHAR16)c);
	}

	void RenderContext::DrawPCSF2Char(const UINT64 xPos, const UINT64 yPos, const CHAR8 c, const Colour colour)
	{
		if (pcsf2 == nullptr)
		{
			return;
		}

		textColour = colour;
		DrawPCSF2Char(xPos, yPos, (CHAR16)c);
	}

	void RenderContext::DrawPCSF2Char(const UINT64 xPos, const UINT64 yPos, const CHAR8 c, const Colour* colour)
	{
		if (pcsf2 == nullptr)
		{
			return;
		}

		textColour = *colour;
		DrawPCSF2Char(xPos, yPos, (CHAR16)c);

	}

	void RenderContext::DrawPCSF2Char(const UINT64 xPos, const UINT64 yPos, const CHAR8 c, const UINT32 colour)
	{
		if (pcsf2 == nullptr)
		{
			return;
		}

		textColour = Colour(colour);
		DrawPCSF2Char(xPos, yPos, (CHAR16)c);
	}

	void RenderContext::DrawPCSF2Char(const UINT64 xPos, const UINT64 yPos, const CHAR8 c, const UINT8 r, const UINT8 g, const UINT8 b, const UINT8 a)
	{
		if (pcsf2 == nullptr)
		{
			return;
		}

		textColour = Colour(r, g, b, a);
		DrawPCSF2Char(xPos, yPos, (CHAR16)c);
	}

	void RenderContext::SetPixelBackgroundColour(const UINT64 xPos, const UINT64 yPos)
	{
		Pixel1Bpp* fb = (Pixel1Bpp*)monitor.GetFrameBuffer();
		UINT64 ppsl = monitor.GetPixelsPerScanLine();
		PixelFormat pf = monitor.GetPixelFormat();

		UINT64 pos = CalculatePixelOffset(xPos, yPos, ppsl);
		Pixel1Bpp c2P;
		switch (pf)
		{
		case Common::Graphics::RedGreenBlueReserved8BitPerColor:
		{
			c2P = Pixel1Bpp(backgroundColour.Red, backgroundColour.Green, backgroundColour.Blue, backgroundColour.Alpha);
			break;
		}
		case Common::Graphics::BlueGreenRedReserved8BitPerColor:
		{
			c2P = Pixel1Bpp(backgroundColour.Blue, backgroundColour.Green, backgroundColour.Red, backgroundColour.Alpha);
			break;
		}
		default:
			return;
		}

		_SetPixel<Pixel1Bpp>(xPos, yPos, ppsl, fb, c2P);
	}

	void RenderContext::SetPixelRowBackgroundColour(const UINT64 xPos, const UINT64 yPos, const UINT64 length)
	{
		Pixel1Bpp* fb = (Pixel1Bpp*)monitor.GetFrameBuffer();
		PixelFormat pf = monitor.GetPixelFormat();
		UINT64 ppsl = monitor.GetPixelsPerScanLine();

		UINT64 pos = CalculatePixelOffset(xPos, yPos, ppsl);
		UINT64 end = pos + length;
		Pixel1Bpp p;
		/*
		*  Calculate the pixel position in the frame buffer, and set theconst Colour of the pixel
		*/

		switch (pf)
		{
		case Common::Graphics::RedGreenBlueReserved8BitPerColor:
		{
			p = Pixel1Bpp(backgroundColour.Red, backgroundColour.Green, backgroundColour.Blue, backgroundColour.Alpha);
			break;
		}
		case Common::Graphics::BlueGreenRedReserved8BitPerColor:
		{
			Pixel1Bpp p = Pixel1Bpp(backgroundColour.Blue, backgroundColour.Green, backgroundColour.Red, backgroundColour.Alpha);
			break;
		}
		default:
			return;
		}

		_SetPixelRow<Pixel1Bpp>(xPos, yPos, length, ppsl, fb, p);
	}

	void RenderContext::SetPixelRowBackgroundColour(const UINT64 xPos, const UINT64 yPos, const UINT64 length, const Colour colour)
	{
		backgroundColour = colour;
		SetPixelRowBackgroundColour(xPos, yPos, length);
	}

	void RenderContext::SetPixelRowBackgroundColour(const UINT64 xPos, const UINT64 yPos, const UINT64 length, const Colour* colour)
	{
		backgroundColour = *colour;
		SetPixelRowBackgroundColour(xPos, yPos, length);
	}

	void RenderContext::SetPixelRowBackgroundColour(const UINT64 xPos, const UINT64 yPos, const UINT64 length, const UINT32 colour)
	{
		backgroundColour = Colour(colour);
		SetPixelRowBackgroundColour(xPos, yPos, length);
	}

	void RenderContext::SetPixelRowBackgroundColour(const UINT64 xPos, const UINT64 yPos, const UINT64 length, const UINT8 r, const UINT8 g, const UINT8 b, const UINT8 a)
	{
		backgroundColour = Colour(r, g, b, a);
		SetPixelRowBackgroundColour(xPos, yPos, length);
	}

	void RenderContext::SetPixelBackgroundColour(const UINT64 xPos, const UINT64 yPos, const Colour colour)
	{
		backgroundColour = colour;
		SetPixelBackgroundColour(xPos, yPos);
	}

	void RenderContext::SetPixelBackgroundColour(const UINT64 xPos, const UINT64 yPos, const Colour* colour)
	{
		backgroundColour = *colour;
		SetPixelBackgroundColour(xPos, yPos);
	}

	void RenderContext::SetPixelBackgroundColour(const UINT64 xPos, const UINT64 yPos, const UINT32 colour)
	{
		backgroundColour = Colour(colour);
		SetPixelBackgroundColour(xPos, yPos);
	}

	void RenderContext::SetPixelBackgroundColour(const UINT64 xPos, const UINT64 yPos, const UINT8 r, const UINT8 g, const UINT8 b, const UINT8 a)
	{
		backgroundColour = Colour(r, g, b, a);
		SetPixelBackgroundColour(xPos, yPos);
	}

	void RenderContext::SetPixelForeground1Colour(const UINT64 xPos, const UINT64 yPos)
	{
		Pixel1Bpp* fb = (Pixel1Bpp*)monitor.GetFrameBuffer();
		UINT64 ppsl = monitor.GetPixelsPerScanLine();
		PixelFormat pf = monitor.GetPixelFormat();

		UINT64 pos = CalculatePixelOffset(xPos, yPos, ppsl);
		Pixel1Bpp c2P;

		switch (pf)
		{
		case Common::Graphics::RedGreenBlueReserved8BitPerColor:
		{
			c2P = Pixel1Bpp(foreground1Colour.Red, foreground1Colour.Green, foreground1Colour.Blue, foreground1Colour.Alpha);
			break;
		}
		case Common::Graphics::BlueGreenRedReserved8BitPerColor:
		{
			c2P = Pixel1Bpp(foreground1Colour.Blue, foreground1Colour.Green, foreground1Colour.Red, foreground1Colour.Alpha);
			break;
		}
		default:
			return;
		}

		_SetPixel<Pixel1Bpp>(xPos, yPos, ppsl, fb, c2P);
	}

	void RenderContext::SetPixelRowForeground1Colour(const UINT64 xPos, const UINT64 yPos, const UINT64 length)
	{
		Pixel1Bpp* fb = (Pixel1Bpp*)monitor.GetFrameBuffer();
		PixelFormat pf = monitor.GetPixelFormat();
		UINT64 ppsl = monitor.GetPixelsPerScanLine();

		UINT64 pos = CalculatePixelOffset(xPos, yPos, ppsl);
		UINT64 end = pos + length;
		Pixel1Bpp p;
		switch (pf)
		{
		case Common::Graphics::RedGreenBlueReserved8BitPerColor:
		{
			p = Pixel1Bpp(foreground1Colour.Red, foreground1Colour.Green, foreground1Colour.Blue, foreground1Colour.Alpha);

			break;
		}
		case Common::Graphics::BlueGreenRedReserved8BitPerColor:
		{
			p = Pixel1Bpp(foreground1Colour.Blue, foreground1Colour.Green, foreground1Colour.Red, foreground1Colour.Alpha);
			break;
		}
		default:
			return;
		}

		_SetPixelRow<Pixel1Bpp>(xPos, yPos, length, ppsl, fb, p);
	}

	void RenderContext::SetPixelForeground1Colour(const UINT64 xPos, const UINT64 yPos, const Colour colour)
	{
		foreground1Colour = colour;
		SetPixelForeground1Colour(xPos, yPos);
	}

	void RenderContext::SetPixelForeground1Colour(const UINT64 xPos, const UINT64 yPos, const Colour* colour)
	{
		foreground1Colour = *colour;
		SetPixelForeground1Colour(xPos, yPos);
	}

	void RenderContext::SetPixelForeground1Colour(const UINT64 xPos, const UINT64 yPos, const UINT32 colour)
	{
		foreground1Colour = Colour(colour);
		SetPixelForeground1Colour(xPos, yPos);
	}

	void RenderContext::SetPixelForeground1Colour(const UINT64 xPos, const UINT64 yPos, const UINT8 r, const UINT8 g, const UINT8 b, const UINT8 a)
	{
		foreground1Colour = Colour(r, g, b, a);
		SetPixelForeground1Colour(xPos, yPos);
	}

	void RenderContext::Terminate(Efi::Handle hnd, Efi::SystemTable* sysTable)
	{
		monitor.Terminate();
		sysTable->BootServices->CloseProtocol(sysTable->ConsoleOutHandle, &Efi::GraphicsOutputProtocol_GUID, hnd, nullptr);
	};

	void RenderContext::SetPixelRowForeground1Colour(const UINT64 xPos, const UINT64 yPos, const UINT64 length, const Colour colour)
	{
		foreground1Colour = colour;
		SetPixelRowForeground1Colour(xPos, yPos, length);
	}
	void RenderContext::SetPixelRowForeground1Colour(const UINT64 xPos, const UINT64 yPos, const UINT64 length, const Colour* colour)
	{
		foreground1Colour = *colour;
		SetPixelRowForeground1Colour(xPos, yPos, length);
	}
	void RenderContext::SetPixelRowForeground1Colour(const UINT64 xPos, const UINT64 yPos, const UINT64 length, const UINT32 colour)
	{
		foreground1Colour = Colour(colour);
		SetPixelRowForeground1Colour(xPos, yPos, length);
	}
	void RenderContext::SetPixelRowForeground1Colour(const UINT64 xPos, const UINT64 yPos, const UINT64 length, const UINT8 r, const UINT8 g, const UINT8 b, const UINT8 a)
	{
		foreground1Colour = Colour(r, g, b, a);
		SetPixelRowForeground1Colour(xPos, yPos, length);
	}

	void RenderContext::SetPixelRowForeground2Colour(const UINT64 xPos, const UINT64 yPos, const UINT64 length, const Colour colour)
	{
		foreground2Colour = colour;
		SetPixelRowForeground2Colour(xPos, yPos, length);
	}
	void RenderContext::SetPixelRowForeground2Colour(const UINT64 xPos, const UINT64 yPos, const UINT64 length, const Colour* colour)
	{
		foreground2Colour = *colour;
		SetPixelRowForeground2Colour(xPos, yPos, length);
	}
	void RenderContext::SetPixelRowForeground2Colour(const UINT64 xPos, const UINT64 yPos, const UINT64 length, const UINT32 colour)
	{
		foreground2Colour = Colour(colour);
		SetPixelRowForeground2Colour(xPos, yPos, length);
	}
	void RenderContext::SetPixelRowForeground2Colour(const UINT64 xPos, const UINT64 yPos, const UINT64 length, const UINT8 r, const UINT8 g, const UINT8 b, const UINT8 a)
	{
		foreground2Colour = Colour(r, g, b, a);
		SetPixelRowForeground2Colour(xPos, yPos, length);
	}

	void RenderContext::SetPixelRowTextColour(const UINT64 xPos, const UINT64 yPos, const UINT64 length)
	{
		Pixel1Bpp* fb = (Pixel1Bpp*)monitor.GetFrameBuffer();
		PixelFormat pf = monitor.GetPixelFormat();
		UINT64 ppsl = monitor.GetPixelsPerScanLine();

		UINT64 pos = CalculatePixelOffset(xPos, yPos, ppsl);
		UINT64 end = pos + length;

		Pixel1Bpp p;

		switch (pf)
		{
		case Common::Graphics::RedGreenBlueReserved8BitPerColor:
		{
			p = Pixel1Bpp(textColour.Red, textColour.Green, textColour.Blue, textColour.Alpha);
			break;
		}
		case Common::Graphics::BlueGreenRedReserved8BitPerColor:
		{
			p = Pixel1Bpp(textColour.Blue, textColour.Green, textColour.Red, textColour.Alpha);
			break;
		}
		default:
			return;
		}

		_SetPixelRow<Pixel1Bpp>(xPos, yPos, length, ppsl, fb, p);
	}

	void RenderContext::SetPixelRowTextColour(const UINT64 xPos, const UINT64 yPos, const UINT64 length, const Colour colour)
	{
		textColour = colour;
		SetPixelRowTextColour(xPos, yPos, length);
	}

	void RenderContext::SetPixelRowTextColour(const UINT64 xPos, const UINT64 yPos, const UINT64 length, const Colour* colour)
	{
		textColour = *colour;
		SetPixelRowTextColour(xPos, yPos, length);
	}

	void RenderContext::SetPixelRowTextColour(const UINT64 xPos, const UINT64 yPos, const UINT64 length, const UINT32 colour)
	{
		textColour = Colour(colour);
		SetPixelRowTextColour(xPos, yPos, length);
	}

	void RenderContext::SetPixelRowTextColour(const UINT64 xPos, const UINT64 yPos, const UINT64 length, const UINT8 r, const UINT8 g, const UINT8 b, const UINT8 a)
	{
		textColour = Colour(r, g, b, a);
		SetPixelRowTextColour(xPos, yPos, length);
	}

	void RenderContext::SetPixelForeground2Colour(const UINT64 xPos, const UINT64 yPos)
	{
		Pixel1Bpp* fb = (Pixel1Bpp*)monitor.GetFrameBuffer();
		const UINT64 ppsl = monitor.GetPixelsPerScanLine();
		PixelFormat pf = monitor.GetPixelFormat();

		const UINT64 pos = CalculatePixelOffset(xPos, yPos, ppsl);
		Pixel1Bpp c2P;
		switch (pf)
		{
		case Common::Graphics::RedGreenBlueReserved8BitPerColor:
		{
			c2P = Pixel1Bpp(foreground2Colour.Red, foreground2Colour.Green, foreground2Colour.Blue, foreground2Colour.Alpha);
			break;
		}
		case Common::Graphics::BlueGreenRedReserved8BitPerColor:
		{
			c2P = Pixel1Bpp(foreground2Colour.Blue, foreground2Colour.Green, foreground2Colour.Red, foreground2Colour.Alpha);
			break;
		}
		default:
			return;
		}
		_SetPixel<Pixel1Bpp>(xPos, yPos, ppsl, fb, c2P);
	}

	void RenderContext::SetPixelRowForeground2Colour(const UINT64 xPos, const UINT64 yPos, const UINT64 length)
	{
		Pixel1Bpp* fb = (Pixel1Bpp*)monitor.GetFrameBuffer();
		PixelFormat pf = monitor.GetPixelFormat();
		UINT64 ppsl = monitor.GetPixelsPerScanLine();

		UINT64 pos = CalculatePixelOffset(xPos, yPos, ppsl);
		UINT64 end = pos + length;

		Pixel1Bpp p;
		switch (pf)
		{
		case Common::Graphics::RedGreenBlueReserved8BitPerColor:
		{
			p = Pixel1Bpp(foreground2Colour.Red, foreground2Colour.Green, foreground2Colour.Blue, foreground2Colour.Alpha);
			break;
		}
		case Common::Graphics::BlueGreenRedReserved8BitPerColor:
		{
			p = Pixel1Bpp(foreground2Colour.Blue, foreground2Colour.Green, foreground2Colour.Red, foreground2Colour.Alpha);
			break;
		}
		default:
			return;
		}

		_SetPixelRow<Pixel1Bpp>(xPos, yPos, length, ppsl, fb, p);
	}

	void RenderContext::SetPixelForeground2Colour(const UINT64 xPos, const UINT64 yPos, const Colour colour)
	{
		foreground2Colour = colour;
		SetPixelForeground2Colour(xPos, yPos);
	}

	void RenderContext::SetPixelForeground2Colour(const UINT64 xPos, const UINT64 yPos, const Colour* colour)
	{
		foreground2Colour = *colour;
		SetPixelForeground2Colour(xPos, yPos);
	}

	void RenderContext::SetPixelForeground2Colour(const UINT64 xPos, const UINT64 yPos, const UINT32 colour)
	{
		foreground2Colour = Colour(colour);
		SetPixelForeground2Colour(xPos, yPos);
	}

	void RenderContext::SetPixelForeground2Colour(const UINT64 xPos, const UINT64 yPos, const UINT8 r, const UINT8 g, const UINT8 b, const UINT8 a)
	{
		foreground2Colour = Colour(r, g, b, a);
		SetPixelForeground2Colour(xPos, yPos);
	}

	void RenderContext::SetPixelTextColour(const UINT64 xPos, const UINT64 yPos)
	{
		Pixel1Bpp* fb = (Pixel1Bpp*)monitor.GetFrameBuffer();
		const UINT64 ppsl = monitor.GetPixelsPerScanLine();
		PixelFormat pf = monitor.GetPixelFormat();

		const UINT64 pos = CalculatePixelOffset(xPos, yPos, ppsl);
		Pixel1Bpp c2P;
		switch (pf)
		{
		case Common::Graphics::RedGreenBlueReserved8BitPerColor:
		{
			c2P = Pixel1Bpp(textColour.Red, textColour.Green, textColour.Blue, textColour.Alpha);
			break;
		}
		case Common::Graphics::BlueGreenRedReserved8BitPerColor:
		{
			c2P = Pixel1Bpp(textColour.Blue, textColour.Green, textColour.Red, textColour.Alpha);
			break;
		}
		default:
			return;
		}
		_SetPixel<Pixel1Bpp>(xPos, yPos, ppsl, fb, c2P);
	}

	void RenderContext::SetPixelTextColour(const UINT64 xPos, const UINT64 yPos, const Colour colour)
	{
		textColour = colour;
		SetPixelTextColour(xPos, yPos);
	}

	void RenderContext::SetPixelTextColour(const UINT64 xPos, const UINT64 yPos, const Colour* colour)
	{
		textColour = *colour;
		SetPixelTextColour(xPos, yPos);
	}

	void RenderContext::SetPixelTextColour(const UINT64 xPos, const UINT64 yPos, const UINT32 colour)
	{
		textColour = Colour(colour);
		SetPixelTextColour(xPos, yPos);
	}

	void RenderContext::SetPixelTextColour(const UINT64 xPos, const UINT64 yPos, const UINT8 r, const UINT8 g, const UINT8 b, const UINT8 a)
	{
		textColour = Colour(r, g, b, a);
		SetPixelTextColour(xPos, yPos);
	}

	MonitorContext* RenderContext::GetMonitorContext()
	{
		return &monitor;
	}

	UINT64 RenderContext::GetWidth()
	{
		if (monitor.currentMode == nullptr)
		{
			return 0;
		}

		return monitor.currentMode->HorizontalResolution;

	}
	UINT64 RenderContext::GetHeight()
	{
		if (monitor.currentMode == nullptr)
		{
			return 0;
		}

		return monitor.currentMode->VerticalResolution;
	}
}