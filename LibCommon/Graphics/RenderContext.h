#pragma once
#include <TypeDefs.h>
#include <Graphics/Colour.h>
#include <Graphics/MonitorContext.h>
#include <Protocols/Graphics/EFI_GRAPHICS_OUTPUT_PROTOCOL.h>

namespace Common::Graphics
{
	struct RenderContext
	{
	public:
		RenderContext(EFI::EFI_GRAPHICS_OUTPUT_PROTOCOL* ptr, Colour fg = Colours::White, Colour bg = Colours::Black);

		Colour GetBackground() const;
		Colour GetForeground() const;

        void ClearScreen();
        void ClearScreen(Colour colour);
        void ClearScreen(Colour* colour);
        void ClearScreen(UINT32 colour);
        void ClearScreen(UINT8 r, UINT8 g, UINT8 b, UINT8 a = (UINT8)0xFF);
        void DrawCircle(UINT32 xPos, UINT32 yPos, UINT32 radius, UINT32 thickness);
        void DrawCircle(UINT32 xPos, UINT32 yPos, UINT32 radius, UINT32 thickness, Colour colour);
        void DrawCircle(UINT32 xPos, UINT32 yPos, UINT32 radius, UINT32 thickness, Colour* colour);
        void DrawCircle(UINT32 xPos, UINT32 yPos, UINT32 radius, UINT32 thickness, UINT32 colour);
        void DrawCircle(UINT32 xPos, UINT32 yPos, UINT32 radius, UINT32 thickness, UINT8 r, UINT8 g, UINT8 b, UINT8 a = (UINT8)0xFF);
        void DrawFilledCircle(UINT32 xPos, UINT32 yPos, UINT32 radius);
        void DrawFilledCircle(UINT32 xPos, UINT32 yPos, UINT32 radius, Colour colour);
        void DrawFilledCircle(UINT32 xPos, UINT32 yPos, UINT32 radius, Colour* colour);
        void DrawFilledCircle(UINT32 xPos, UINT32 yPos, UINT32 radius, UINT32 colour);
        void DrawFilledCircle(UINT32 xPos, UINT32 yPos, UINT32 radius, UINT8 r, UINT8 g, UINT8 b, UINT8 a = (UINT8)0xFF);
        void DrawFilledRectangle(UINT32 xPos, UINT32 yPos, UINT32 width, UINT32 height);
        void DrawFilledRectangle(UINT32 xPos, UINT32 yPos, UINT32 width, UINT32 height, Colour colour);
        void DrawFilledRectangle(UINT32 xPos, UINT32 yPos, UINT32 width, UINT32 height, Colour* colour);
        void DrawFilledRectangle(UINT32 xPos, UINT32 yPos, UINT32 width, UINT32 height, UINT32 colour);
        void DrawFilledRectangle(UINT32 xPos, UINT32 yPos, UINT32 width, UINT32 height, UINT8 r, UINT8 g, UINT8 b, UINT8 a = (UINT8)0xFF);
        void DrawLine(UINT32 sXPos, UINT32 sYPos, UINT32 eXPos, UINT32 eYPos, UINT32 thickness);
        void DrawLine(UINT32 sXPos, UINT32 sYPos, UINT32 eXPos, UINT32 eYPos, UINT32 thickness, Colour colour);
        void DrawLine(UINT32 sXPos, UINT32 sYPos, UINT32 eXPos, UINT32 eYPos, UINT32 thickness, Colour* colour);
        void DrawLine(UINT32 sXPos, UINT32 sYPos, UINT32 eXPos, UINT32 eYPos, UINT32 thickness, UINT32 colour);
        void DrawLine(UINT32 sXPos, UINT32 sYPos, UINT32 eXPos, UINT32 eYPos, UINT32 thickness, UINT8 r, UINT8 g, UINT8 b, UINT8 a = (UINT8)0xFF);
        void DrawRectangle(UINT32 xPos, UINT32 yPos, UINT32 width, UINT32 height, UINT32 thickness);
        void DrawRectangle(UINT32 xPos, UINT32 yPos, UINT32 width, UINT32 height, UINT32 thickness, Colour colour);
        void DrawRectangle(UINT32 xPos, UINT32 yPos, UINT32 width, UINT32 height, UINT32 thickness, Colour* colour);
        void DrawRectangle(UINT32 xPos, UINT32 yPos, UINT32 width, UINT32 height, UINT32 thickness, UINT32 colour);
        void DrawRectangle(UINT32 xPos, UINT32 yPos, UINT32 width, UINT32 height, UINT32 thickness, UINT8 r, UINT8 g, UINT8 b, UINT8 a = (UINT8)0xFF);
        void SetBackground(Colour colour);
        void SetBackground(Colour* colour);
        void SetBackground(UINT32 colour);
        void SetBackground(UINT8 r, UINT8 g, UINT8 b, UINT8 a = (UINT8)0xFF);
        void SetForeground(Colour colour);
        void SetForeground(Colour* colour);
        void SetForeground(UINT32 colour);
        void SetForeground(UINT8 r, UINT8 g, UINT8 b, UINT8 a = (UINT8)0xFF);
        void SetPixelBackground(UINT32 xPos, UINT32 yPos);
        void SetPixelBackground(UINT32 xPos, UINT32 yPos, Colour colour);
        void SetPixelBackground(UINT32 xPos, UINT32 yPos, Colour* colour);
        void SetPixelBackground(UINT32 xPos, UINT32 yPos, UINT32 colour);
        void SetPixelBackground(UINT32 xPos, UINT32 yPos, UINT8 r, UINT8 g, UINT8 b, UINT8 a = (UINT8)0xFF);
        void SetPixelForeground(UINT32 xPos, UINT32 yPos);
        void SetPixelForeground(UINT32 xPos, UINT32 yPos, Colour colour);
        void SetPixelForeground(UINT32 xPos, UINT32 yPos, Colour* colour);
        void SetPixelForeground(UINT32 xPos, UINT32 yPos, UINT32 colour);
        void SetPixelForeground(UINT32 xPos, UINT32 yPos, UINT8 r, UINT8 g, UINT8 b, UINT8 a = (UINT8)0xFF);

	private:
        MonitorContext monitor;
		Colour background;
		Colour foreground;
	};
}
