#pragma once
#include <TypeDefs.h>
#include <Graphics/Colour.h>
#include <Graphics/MonitorContext.h>
#include <FileTypes/PCSF/PCSF1.h>
#include <FileTypes/PCSF/PCSF2.h>

#include <Protocols/Graphics/EFI_GRAPHICS_OUTPUT_PROTOCOL.h>
#include <EFI_SYSTEM_TABLE.h>
#include <EFI_HANDLE.h>

namespace Common::Graphics
{
	struct RenderContext
	{
    private:
		RenderContext(EFI::EFI_GRAPHICS_OUTPUT_PROTOCOL* ptr, Colour txt, Colour bg, Colour fg1, Colour fg2);
	public:
        static RenderContext* Initialize(EFI::EFI_SYSTEM_TABLE* sysTbl,EFI::EFI_HANDLE imgHndl, Colour txt = Colours::White, Colour bg = Colours::Black, Colour fg1 = Colours::WhiteSmoke, Colour fg2 = Colours::AliceBlue);

		Colour GetBackgroundColour();
		Colour GetForeground1Colour();
        Colour GetForeground2Colour();
        Colour GetTextColour();

        void ClearScreen(BOOLEAN resetColours = FALSE);
        void ClearScreen(const Colour colour);
        void ClearScreen(const Colour* colour);
        void ClearScreen(const UINT32 colour);
        void ClearScreen(const UINT32 r, const UINT32 g, const UINT32 b, const UINT32 a = 0xFFFFFFFFu);

        void DrawCircle(const UINT32 xPos, const UINT32 yPos, const UINT32 radius, const UINT32 thickness);
        void DrawCircle(const UINT32 xPos, const UINT32 yPos, const UINT32 radius, const UINT32 thickness, const Colour colour);
        void DrawCircle(const UINT32 xPos, const UINT32 yPos, const UINT32 radius, const UINT32 thickness, const Colour* colour);
        void DrawCircle(const UINT32 xPos, const UINT32 yPos, const UINT32 radius, const UINT32 thickness, const UINT32 colour);
        void DrawCircle(const UINT32 xPos, const UINT32 yPos, const UINT32 radius, const UINT32 thickness, const UINT32 r, const UINT32 g, const UINT32 b, const UINT32 a = 0xFFFFFFFFu);

        void DrawFilledCircle(const UINT32 xPos, const UINT32 yPos, const UINT32 radius);
        void DrawFilledCircle(const UINT32 xPos, const UINT32 yPos, const UINT32 radius, const Colour colour);
        void DrawFilledCircle(const UINT32 xPos, const UINT32 yPos, const UINT32 radius, const Colour* colour);
        void DrawFilledCircle(const UINT32 xPos, const UINT32 yPos, const UINT32 radius, const UINT32 colour);
        void DrawFilledCircle(const UINT32 xPos, const UINT32 yPos, const UINT32 radius, const UINT32 r, const UINT32 g, const UINT32 b, const UINT32 a = 0xFFFFFFFFu);

        void DrawFilledRectangle(const UINT32 xPos, const UINT32 yPos, const UINT32 width, const UINT32 height,const UINT32 thickness);
        void DrawFilledRectangle(const UINT32 xPos, const UINT32 yPos, const UINT32 width, const UINT32 height,const UINT32 thickness, const Colour c1, const Colour c2);
        void DrawFilledRectangle(const UINT32 xPos, const UINT32 yPos, const UINT32 width, const UINT32 height,const UINT32 thickness, const Colour* c1, const Colour* c2);
        void DrawFilledRectangle(const UINT32 xPos, const UINT32 yPos, const UINT32 width, const UINT32 height,const UINT32 thickness, const UINT32 c1,const UINT32 c2);
        void DrawFilledRectangle(const UINT32 xPos, const UINT32 yPos, const UINT32 width, const UINT32 height,const UINT32 thickness, const UINT32 c1R, const UINT32 c1G, const UINT32 c1B, const UINT32 c1A, const UINT32 c2R, const UINT32 c2G, const UINT32 c2B, const UINT32 c2A);

        void DrawLine(const UINT32 sXPos, const UINT32 sYPos, const UINT32 eXPos, const UINT32 eYPos, const UINT32 thickness);
        void DrawLine(const UINT32 sXPos, const UINT32 sYPos, const UINT32 eXPos, const UINT32 eYPos, const UINT32 thickness, const Colour colour);
        void DrawLine(const UINT32 sXPos, const UINT32 sYPos, const UINT32 eXPos, const UINT32 eYPos, const UINT32 thickness, const Colour* colour);
        void DrawLine(const UINT32 sXPos, const UINT32 sYPos, const UINT32 eXPos, const UINT32 eYPos, const UINT32 thickness, const UINT32 colour);
        void DrawLine(const UINT32 sXPos, const UINT32 sYPos, const UINT32 eXPos, const UINT32 eYPos, const UINT32 thickness, const UINT32 r, const UINT32 g, const UINT32 b, const UINT32 a = 0xFFFFFFFFu);

        void DrawRectangle(const UINT32 xPos, const UINT32 yPos, const UINT32 width, const UINT32 height);
        void DrawRectangle(const UINT32 xPos, const UINT32 yPos, const UINT32 width, const UINT32 height,const Colour colour);
        void DrawRectangle(const UINT32 xPos, const UINT32 yPos, const UINT32 width, const UINT32 height,const Colour* colour);
        void DrawRectangle(const UINT32 xPos, const UINT32 yPos, const UINT32 width, const UINT32 height,const UINT32 colour);
        void DrawRectangle(const UINT32 xPos, const UINT32 yPos, const UINT32 width, const UINT32 height,const UINT32 r, const UINT32 g, const UINT32 b, const UINT32 a = 0xFFFFFFFFu);

        void ResetBackgroundColour();
        void ResetForeground1Colour();
        void ResetForeground2Colour();
        void ResetTextColour();
        void ResetToDefaultColours();

        void SetBackgroundColour(const Colour colour);
        void SetBackgroundColour(const Colour* colour);
        void SetBackgroundColour(const UINT32 colour);
        void SetBackgroundColour(const UINT32 r, const UINT32 g, const UINT32 b, const UINT32 a = 0xFFFFFFFFu);

        void SetForeground1Colour(const Colour colour);
        void SetForeground1Colour(const Colour* colour);
        void SetForeground1Colour(const UINT32 colour);
        void SetForeground1Colour(const UINT32 r, const UINT32 g, const UINT32 b, const UINT32 a = 0xFFFFFFFFu);

        void SetForeground2Colour(const Colour colour);
        void SetForeground2Colour(const Colour* colour);
        void SetForeground2Colour(const UINT32 colour);
        void SetForeground2Colour(const UINT32 r, const UINT32 g, const UINT32 b, const UINT32 a = 0xFFFFFFFFu);

        void SetPixelBackgroundColour(const UINT32 xPos, const UINT32 yPos);
        void SetPixelBackgroundColour(const UINT32 xPos, const UINT32 yPos, const Colour colour);
        void SetPixelBackgroundColour(const UINT32 xPos, const UINT32 yPos, const Colour* colour);
        void SetPixelBackgroundColour(const UINT32 xPos, const UINT32 yPos, const UINT32 colour);
        void SetPixelBackgroundColour(const UINT32 xPos, const UINT32 yPos, const UINT32 r, const UINT32 g, const UINT32 b, const UINT32 a = 0xFFFFFFFFu);

        void SetPixelForeground1Colour(const UINT32 xPos, const UINT32 yPos);
        void SetPixelForeground1Colour(const UINT32 xPos, const UINT32 yPos, const Colour colour);
        void SetPixelForeground1Colour(const UINT32 xPos, const UINT32 yPos, const Colour* colour);
        void SetPixelForeground1Colour(const UINT32 xPos, const UINT32 yPos, const UINT32 colour);
        void SetPixelForeground1Colour(const UINT32 xPos, const UINT32 yPos, const UINT32 r, const UINT32 g, const UINT32 b, const UINT32 a = 0xFFFFFFFFu);

        void SetPixelForeground2Colour(const UINT32 xPos, const UINT32 yPos);
        void SetPixelForeground2Colour(const UINT32 xPos, const UINT32 yPos, const Colour colour);
        void SetPixelForeground2Colour(const UINT32 xPos, const UINT32 yPos, const Colour* colour);
        void SetPixelForeground2Colour(const UINT32 xPos, const UINT32 yPos, const UINT32 colour);
        void SetPixelForeground2Colour(const UINT32 xPos, const UINT32 yPos, const UINT32 r, const UINT32 g, const UINT32 b, const UINT32 a = 0xFFFFFFFFu);

        void SetPixelTextColour(const UINT32 xPos, const UINT32 yPos);
        void SetPixelTextColour(const UINT32 xPos, const UINT32 yPos, const Colour colour);
        void SetPixelTextColour(const UINT32 xPos, const UINT32 yPos, const Colour* colour);
        void SetPixelTextColour(const UINT32 xPos, const UINT32 yPos, const UINT32 colour);
        void SetPixelTextColour(const UINT32 xPos, const UINT32 yPos, const UINT32 r, const UINT32 g, const UINT32 b, const UINT32 a = 0xFFFFFFFFu);

        void SetPixelRowBackgroundColour(const UINT32 xPos, const UINT32 yPos,const UINT32 length);
        void SetPixelRowBackgroundColour(const UINT32 xPos, const UINT32 yPos,const UINT32 length, const Colour colour);
        void SetPixelRowBackgroundColour(const UINT32 xPos, const UINT32 yPos,const UINT32 length, const Colour* colour);
        void SetPixelRowBackgroundColour(const UINT32 xPos, const UINT32 yPos,const UINT32 length, const UINT32 colour);
        void SetPixelRowBackgroundColour(const UINT32 xPos, const UINT32 yPos,const UINT32 length, const UINT32 r, const UINT32 g, const UINT32 b, const UINT32 a = 0xFFFFFFFFu);

        void SetPixelRowForeground1Colour(const UINT32 xPos, const UINT32 yPos, const UINT32 length);
        void SetPixelRowForeground1Colour(const UINT32 xPos, const UINT32 yPos, const UINT32 length, const Colour colour);
        void SetPixelRowForeground1Colour(const UINT32 xPos, const UINT32 yPos, const UINT32 length, const Colour* colour);
        void SetPixelRowForeground1Colour(const UINT32 xPos, const UINT32 yPos, const UINT32 length, const UINT32 colour);
        void SetPixelRowForeground1Colour(const UINT32 xPos, const UINT32 yPos, const UINT32 length, const UINT32 r, const UINT32 g, const UINT32 b, const UINT32 a = 0xFFFFFFFFu);

        void SetPixelRowForeground2Colour(const UINT32 xPos, const UINT32 yPos, const UINT32 length);
        void SetPixelRowForeground2Colour(const UINT32 xPos, const UINT32 yPos, const UINT32 length, const Colour colour);
        void SetPixelRowForeground2Colour(const UINT32 xPos, const UINT32 yPos, const UINT32 length, const Colour* colour);
        void SetPixelRowForeground2Colour(const UINT32 xPos, const UINT32 yPos, const UINT32 length, const UINT32 colour);
        void SetPixelRowForeground2Colour(const UINT32 xPos, const UINT32 yPos, const UINT32 length, const UINT32 r, const UINT32 g, const UINT32 b, const UINT32 a = 0xFFFFFFFFu);

		void SetPixelRowTextColour(const UINT32 xPos, const UINT32 yPos, const UINT32 length);
		void SetPixelRowTextColour(const UINT32 xPos, const UINT32 yPos, const UINT32 length, const Colour colour);
		void SetPixelRowTextColour(const UINT32 xPos, const UINT32 yPos, const UINT32 length, const Colour* colour);
		void SetPixelRowTextColour(const UINT32 xPos, const UINT32 yPos, const UINT32 length, const UINT32 colour);
		void SetPixelRowTextColour(const UINT32 xPos, const UINT32 yPos, const UINT32 length, const UINT32 r, const UINT32 g, const UINT32 b, const UINT32 a = 0xFFFFFFFFu);

        void SetTextColour(Colour colour);
        void SetTextColour(const Colour* colour);
        void SetTextColour(UINT32 colour);
        void SetTextColour(UINT32 r, UINT32 g, UINT32 b, UINT32 a = 0xFFFFFFFFu);

		void SetPCSF1Font(Graphics::Font::PCSF::PCSF1* font);
        void SetPCSF2Font(Graphics::Font::PCSF::PCSF2* font);
		void SetFonts(Graphics::Font::PCSF::PCSF1* pcsf1, Graphics::Font::PCSF::PCSF2* pcsf2);

        void DrawPCSF1Char(const UINT32 xPos, const UINT32 yPos, const CHAR16 c);
		void DrawPCSF1Char(const UINT32 xPos, const UINT32 yPos, const CHAR16 c, const Colour colour);
		void DrawPCSF1Char(const UINT32 xPos, const UINT32 yPos, const CHAR16 c, const Colour* colour);
		void DrawPCSF1Char(const UINT32 xPos, const UINT32 yPos, const CHAR16 c, const UINT32 colour);
		void DrawPCSF1Char(const UINT32 xPos, const UINT32 yPos, const CHAR16 c, const UINT32 r, const UINT32 g, const UINT32 b, const UINT32 a = 0xFFFFFFFFu);
        
        void DrawPCSF1Char(const UINT32 xPos, const UINT32 yPos, const CHAR8 c);
        void DrawPCSF1Char(const UINT32 xPos, const UINT32 yPos, const CHAR8 c, const Colour colour);
        void DrawPCSF1Char(const UINT32 xPos, const UINT32 yPos, const CHAR8 c, const Colour* colour);
        void DrawPCSF1Char(const UINT32 xPos, const UINT32 yPos, const CHAR8 c, const UINT32 colour);
        void DrawPCSF1Char(const UINT32 xPos, const UINT32 yPos, const CHAR8 c, const UINT32 r, const UINT32 g, const UINT32 b, const UINT32 a = 0xFFFFFFFFu);

        void DrawPCSF2Char(const UINT32 xPos, const UINT32 yPos, const CHAR16 c);
        void DrawPCSF2Char(const UINT32 xPos, const UINT32 yPos, const CHAR16 c, const Colour colour);
        void DrawPCSF2Char(const UINT32 xPos, const UINT32 yPos, const CHAR16 c, const Colour* colour);
        void DrawPCSF2Char(const UINT32 xPos, const UINT32 yPos, const CHAR16 c, const UINT32 colour);
        void DrawPCSF2Char(const UINT32 xPos, const UINT32 yPos, const CHAR16 c, const UINT32 r, const UINT32 g, const UINT32 b, const UINT32 a = 0xFFFFFFFFu);

        void DrawPCSF2Char(const UINT32 xPos, const UINT32 yPos, const CHAR8 c);
        void DrawPCSF2Char(const UINT32 xPos, const UINT32 yPos, const CHAR8 c, const Colour colour);
        void DrawPCSF2Char(const UINT32 xPos, const UINT32 yPos, const CHAR8 c, const Colour* colour);
        void DrawPCSF2Char(const UINT32 xPos, const UINT32 yPos, const CHAR8 c, const UINT32 colour);
        void DrawPCSF2Char(const UINT32 xPos, const UINT32 yPos, const CHAR8 c, const UINT32 r, const UINT32 g, const UINT32 b, const UINT32 a = 0xFFFFFFFFu);

        void Terminate(EFI::EFI_HANDLE hnd, EFI::EFI_SYSTEM_TABLE* sysTable);

        MonitorContext* GetMonitorContext();

		UINT64 GetWidth();
		UINT64 GetHeight();

	private:
		Colour backgroundColour;
        Colour defaultBackgroundColour;
        Colour defaultForeground1Colour;
        Colour defaultForeground2Colour;
        Colour defaultText;
		Colour foreground1Colour;
        Colour foreground2Colour;
        Colour textColour;
        MonitorContext monitor;

		Font::PCSF::PCSF1* pcsf1;
		Font::PCSF::PCSF2* pcsf2;
	};
}
