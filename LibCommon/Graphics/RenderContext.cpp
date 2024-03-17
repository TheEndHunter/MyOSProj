#include "RenderContext.h"

namespace Common::Graphics
{
    RenderContext::RenderContext(EFI::EFI_GRAPHICS_OUTPUT_PROTOCOL* ptr, Colour fg, Colour bg)
    {
        monitor = MonitorContext(ptr);
        background = bg;
        foreground = fg;
    }
    Colour RenderContext::GetBackground() const
    {
        return background;
    }

    Colour RenderContext::GetForeground() const
    {
        return foreground;
    }

    void RenderContext::ClearScreen()
    {
        Pixel* fb = monitor.GetFrameBuffer();
        UINTN size = monitor.GetFrameBufferSize();
        
        Pixel bg = Pixel(background.Red,background.Green,background.Blue,background.Alpha);
        for (UINTN i = 0; i < size; i++)
        {
			fb[i] = bg;
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

    void RenderContext::ClearScreen(UINT8 r, UINT8 g, UINT8 b, UINT8 a)
    {
        background = Colour(r,g,b,a);
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

    void RenderContext::DrawCircle(UINT32 xPos, UINT32 yPos, UINT32 radius, UINT32 thickness, UINT8 r, UINT8 g, UINT8 b, UINT8 a)
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

    void RenderContext::DrawFilledCircle(UINT32 xPos, UINT32 yPos, UINT32 radius, UINT8 r, UINT8 g, UINT8 b, UINT8 a)
    {
    }

    void RenderContext::DrawFilledRectangle(UINT32 xPos, UINT32 yPos, UINT32 width, UINT32 height)
    {
    }

    void RenderContext::DrawFilledRectangle(UINT32 xPos, UINT32 yPos, UINT32 width, UINT32 height, Colour colour)
    {
    }

    void RenderContext::DrawFilledRectangle(UINT32 xPos, UINT32 yPos, UINT32 width, UINT32 height, Colour* colour)
    {
    }

    void RenderContext::DrawFilledRectangle(UINT32 xPos, UINT32 yPos, UINT32 width, UINT32 height, UINT32 colour)
    {
    }

    void RenderContext::DrawFilledRectangle(UINT32 xPos, UINT32 yPos, UINT32 width, UINT32 height, UINT8 r, UINT8 g, UINT8 b, UINT8 a)
    {
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

    void RenderContext::DrawLine(UINT32 sXPos, UINT32 sYPos, UINT32 eXPos, UINT32 eYPos, UINT32 thickness, UINT8 r, UINT8 g, UINT8 b, UINT8 a)
    {
    }

    void RenderContext::DrawRectangle(UINT32 xPos, UINT32 yPos, UINT32 width, UINT32 height, UINT32 thickness)
    {
    }

    void RenderContext::DrawRectangle(UINT32 xPos, UINT32 yPos, UINT32 width, UINT32 height, UINT32 thickness, Colour colour)
    {
    }

    void RenderContext::DrawRectangle(UINT32 xPos, UINT32 yPos, UINT32 width, UINT32 height, UINT32 thickness, Colour* colour)
    {
    }

    void RenderContext::DrawRectangle(UINT32 xPos, UINT32 yPos, UINT32 width, UINT32 height, UINT32 thickness, UINT32 colour)
    {
    }

    void RenderContext::DrawRectangle(UINT32 xPos, UINT32 yPos, UINT32 width, UINT32 height, UINT32 thickness, UINT8 r, UINT8 g, UINT8 b, UINT8 a)
    {

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

    void RenderContext::SetBackground(UINT8 r, UINT8 g, UINT8 b, UINT8 a)
    {
        background = Colour(r,g,b,a);
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

    void RenderContext::SetForeground(UINT8 r, UINT8 g, UINT8 b, UINT8 a)
    {
        foreground = Colour(r,g,b,a);
    }

    void RenderContext::SetPixelBackground(UINT32 xPos, UINT32 yPos)
    {
        Pixel* fb = monitor.GetFrameBuffer();
        UINTN size = monitor.GetFrameBufferSize();
        UINT32 ppsl = monitor.GetPixelsPerScanLine();
        UINT32 hRes = monitor.GetHorizontalResolution();
        UINT32 vRes = monitor.GetVerticalResolution();

        /*
        *  Calculate the pixel position in the frame buffer, and set the colour of the pixel
        */

        UINTN pos = (yPos * ppsl) + xPos;
        Pixel p = Pixel(background.Red,background.Green,background.Blue,background.Alpha);
        if (pos < size)
        {
			fb[pos] = p;
		}
    }

    void RenderContext::SetPixelBackground(UINT32 xPos, UINT32 yPos, Colour colour)
    {
        background = colour;
        SetPixelBackground(xPos,yPos);
    }

    void RenderContext::SetPixelBackground(UINT32 xPos, UINT32 yPos, Colour* colour)
    {
        background = *colour;
		SetPixelBackground(xPos,yPos);
    }

    void RenderContext::SetPixelBackground(UINT32 xPos, UINT32 yPos, UINT32 colour)
    {
        background = Colour(colour);
		SetPixelBackground(xPos,yPos);
    }

    void RenderContext::SetPixelBackground(UINT32 xPos, UINT32 yPos, UINT8 r, UINT8 g, UINT8 b, UINT8 a)
    {
        background = Colour(r,g,b,a);
        SetPixelBackground(xPos,yPos);
    }

    void RenderContext::SetPixelForeground(UINT32 xPos, UINT32 yPos)
    {
        Pixel* fb = monitor.GetFrameBuffer();
        UINTN size = monitor.GetFrameBufferSize();
        UINT32 ppsl = monitor.GetPixelsPerScanLine();
        UINT32 hRes = monitor.GetHorizontalResolution();
        UINT32 vRes = monitor.GetVerticalResolution();

        /*
        *  Calculate the pixel position in the frame buffer, and set the colour of the pixel
        */

        UINTN pos = (yPos * ppsl) + xPos;
        Pixel p = Pixel(foreground.Red, foreground.Green, foreground.Blue, foreground.Alpha);
        if (pos < size)
        {
            fb[pos] = p;
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

    void RenderContext::SetPixelForeground(UINT32 xPos, UINT32 yPos, UINT8 r, UINT8 g, UINT8 b, UINT8 a)
    {
        foreground = Colour(r,g,b,a);
        SetPixelForeground(xPos, yPos);
    }
}