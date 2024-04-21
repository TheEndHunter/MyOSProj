#pragma once
#include <TypeDefs.h>
#include <Graphics/Colour.h>
#include <Graphics/MonitorContext.h>
#include <Protocols/Graphics/EFI_GRAPHICS_OUTPUT_PROTOCOL.h>
#include <EFI_SYSTEM_TABLE.h>
#include <EFI_HANDLE.h>

namespace Common::Graphics
{
	struct RenderContext
	{
    private:
		RenderContext(EFI::EFI_GRAPHICS_OUTPUT_PROTOCOL* ptr, Colour fg, Colour bg);
	public:
        static RenderContext* Initialize(EFI::EFI_SYSTEM_TABLE* sysTbl,EFI::EFI_HANDLE imgHndl, Colour fg = Colours::White, Colour bg = Colours::Black);

		Colour GetBackground();
		Colour GetForeground();

        void ResetToDefaultColours();
        void ResetBackground();
        void ResetForeground();

        void ClearScreen(BOOLEAN resetColours = FALSE);
        void ClearScreen(Colour colour);
        void ClearScreen(Colour* colour);
        void ClearScreen(UINT32 colour);
        void ClearScreen(UINT32 r, UINT32 g, UINT32 b, UINT32 a = (UINT8)0xFF);

        void DrawCircle(UINT32 xPos, UINT32 yPos, UINT32 radius, UINT32 thickness);
        void DrawCircle(UINT32 xPos, UINT32 yPos, UINT32 radius, UINT32 thickness, Colour colour);
        void DrawCircle(UINT32 xPos, UINT32 yPos, UINT32 radius, UINT32 thickness, Colour* colour);
        void DrawCircle(UINT32 xPos, UINT32 yPos, UINT32 radius, UINT32 thickness, UINT32 colour);
        void DrawCircle(UINT32 xPos, UINT32 yPos, UINT32 radius, UINT32 thickness, UINT32 r, UINT32 g, UINT32 b, UINT32 a = (UINT8)0xFF);

        void DrawFilledCircle(UINT32 xPos, UINT32 yPos, UINT32 radius);
        void DrawFilledCircle(UINT32 xPos, UINT32 yPos, UINT32 radius, Colour colour);
        void DrawFilledCircle(UINT32 xPos, UINT32 yPos, UINT32 radius, Colour* colour);
        void DrawFilledCircle(UINT32 xPos, UINT32 yPos, UINT32 radius, UINT32 colour);
        void DrawFilledCircle(UINT32 xPos, UINT32 yPos, UINT32 radius, UINT32 r, UINT32 g, UINT32 b, UINT32 a = (UINT8)0xFF);

        /*uses foregound and background colours*/
        void DrawFilledRectangle(UINT32 xPos, UINT32 yPos, UINT32 width, UINT32 height,UINT32 thickness);
        void DrawFilledRectangle(UINT32 xPos, UINT32 yPos, UINT32 width, UINT32 height,UINT32 thickness, Colour fg, Colour bg);
        void DrawFilledRectangle(UINT32 xPos, UINT32 yPos, UINT32 width, UINT32 height,UINT32 thickness, Colour* fg, Colour* bg);
        void DrawFilledRectangle(UINT32 xPos, UINT32 yPos, UINT32 width, UINT32 height,UINT32 thickness, UINT32 fg,UINT32 bg);
        void DrawFilledRectangle(UINT32 xPos, UINT32 yPos, UINT32 width, UINT32 height,UINT32 thickness, UINT8 fgR, UINT8 fgG, UINT8 fbB, UINT32 bgR, UINT32 bgG, UINT32 bgB, UINT8 fbA = (UINT8)0xFF, UINT32 bgA = (UINT8)0xFF);

        void DrawLine(UINT32 sXPos, UINT32 sYPos, UINT32 eXPos, UINT32 eYPos, UINT32 thickness);
        void DrawLine(UINT32 sXPos, UINT32 sYPos, UINT32 eXPos, UINT32 eYPos, UINT32 thickness, Colour colour);
        void DrawLine(UINT32 sXPos, UINT32 sYPos, UINT32 eXPos, UINT32 eYPos, UINT32 thickness, Colour* colour);
        void DrawLine(UINT32 sXPos, UINT32 sYPos, UINT32 eXPos, UINT32 eYPos, UINT32 thickness, UINT32 colour);
        void DrawLine(UINT32 sXPos, UINT32 sYPos, UINT32 eXPos, UINT32 eYPos, UINT32 thickness, UINT32 r, UINT32 g, UINT32 b, UINT32 a = (UINT8)0xFF);

        void DrawRectangle(UINT32 xPos, UINT32 yPos, UINT32 width, UINT32 height);
        void DrawRectangle(UINT32 xPos, UINT32 yPos, UINT32 width, UINT32 height,Colour colour);
        void DrawRectangle(UINT32 xPos, UINT32 yPos, UINT32 width, UINT32 height,Colour* colour);
        void DrawRectangle(UINT32 xPos, UINT32 yPos, UINT32 width, UINT32 height,UINT32 colour);
        void DrawRectangle(UINT32 xPos, UINT32 yPos, UINT32 width, UINT32 height,UINT32 r, UINT32 g, UINT32 b, UINT32 a = (UINT8)0xFF);

        void SetBackground(Colour colour);
        void SetBackground(Colour* colour);
        void SetBackground(UINT32 colour);
        void SetBackground(UINT32 r, UINT32 g, UINT32 b, UINT32 a = (UINT8)0xFF);

        void SetForeground(Colour colour);
        void SetForeground(Colour* colour);
        void SetForeground(UINT32 colour);
        void SetForeground(UINT32 r, UINT32 g, UINT32 b, UINT32 a = (UINT8)0xFF);

        void SetPixelBackground(UINT32 xPos, UINT32 yPos);
        void SetPixelBackground(UINT32 xPos, UINT32 yPos, Colour colour);
        void SetPixelBackground(UINT32 xPos, UINT32 yPos, Colour* colour);
        void SetPixelBackground(UINT32 xPos, UINT32 yPos, UINT32 colour);
        void SetPixelBackground(UINT32 xPos, UINT32 yPos, UINT32 r, UINT32 g, UINT32 b, UINT32 a = (UINT8)0xFF);

        void SetPixelRowBackground(UINT32 xPos, UINT32 yPos,UINT32 length);
        void SetPixelRowBackground(UINT32 xPos, UINT32 yPos,UINT32 length, Colour colour);
        void SetPixelRowBackground(UINT32 xPos, UINT32 yPos,UINT32 length, Colour* colour);
        void SetPixelRowBackground(UINT32 xPos, UINT32 yPos,UINT32 length, UINT32 colour);
        void SetPixelRowBackground(UINT32 xPos, UINT32 yPos,UINT32 length, UINT32 r, UINT32 g, UINT32 b, UINT32 a = (UINT8)0xFF);

        void SetPixelForeground(UINT32 xPos, UINT32 yPos);
        void SetPixelForeground(UINT32 xPos, UINT32 yPos, Colour colour);
        void SetPixelForeground(UINT32 xPos, UINT32 yPos, Colour* colour);
        void SetPixelForeground(UINT32 xPos, UINT32 yPos, UINT32 colour);
        void SetPixelForeground(UINT32 xPos, UINT32 yPos, UINT32 r, UINT32 g, UINT32 b, UINT32 a = (UINT8)0xFF);

        void SetPixelRowForeground(UINT32 xPos, UINT32 yPos, UINT32 length);
        void SetPixelRowForeground(UINT32 xPos, UINT32 yPos, UINT32 length, Colour colour);
        void SetPixelRowForeground(UINT32 xPos, UINT32 yPos, UINT32 length, Colour* colour);
        void SetPixelRowForeground(UINT32 xPos, UINT32 yPos, UINT32 length, UINT32 colour);
        void SetPixelRowForeground(UINT32 xPos, UINT32 yPos, UINT32 length, UINT32 r, UINT32 g, UINT32 b, UINT32 a = (UINT8)0xFF);

        void Terminate(EFI::EFI_HANDLE hnd, EFI::EFI_SYSTEM_TABLE* sysTable);


        MonitorContext* GetMonitorContext();

	private:
        MonitorContext monitor;
        Colour defaultBg;
        Colour defaultFg;
		Colour background;
		Colour foreground;
	};
    void SetPixel1Bpp(unsigned long long vRes, unsigned long long ppsl, unsigned long long hRes, void* fb, const Common::Graphics::Pixel1Bpp& bgP);
    void SetRectangle1Bpp(unsigned long long finalY, unsigned long long size, unsigned long long finalX, unsigned int yPos, unsigned long long ppsl, unsigned int xPos, void* fb, const Common::Graphics::Pixel1Bpp& bgP);
}
