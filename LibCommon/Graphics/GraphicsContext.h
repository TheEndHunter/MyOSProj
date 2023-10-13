#pragma once
#include "TypeDefs.h"
#include "EFI_STATUS.h"
#include "EFI_HANDLE.h"
#include "EFI_SYSTEM_TABLE.h"
#include "Protocols/Graphics/EFI_GRAPHICS_OUTPUT_PROTOCOL.h"
#include <Protocols/Graphics/EFI_GRAPHICS_OUTPUT_MODE_INFORMATION.h>
#include <Protocols/Graphics/EFI_GRAPHICS_OUTPUT_BLT_PIXEL.h>
#include "Color.h"

namespace Common::Graphics
{
    struct GraphicsContext
    { 
    protected:
       GraphicsContext(EFI::EFI_GRAPHICS_OUTPUT_PROTOCOL* g);
    public:
        static EFI::EFI_STATUS LastStatus;
        static GraphicsContext Initialize(EFI::EFI_HANDLE hnd, EFI::EFI_SYSTEM_TABLE* sysTable); 
        void Terminate(EFI::EFI_HANDLE hnd, EFI::EFI_SYSTEM_TABLE* sysTable);

        Color GetBackground() const;
        Color GetForeground() const;
        EFI::EFI_STATUS QueryMode(UINT32 modeNumber,OUT UINTN* size,OUT EFI::EFI_GRAPHICS_OUTPUT_MODE_INFORMATION* info);
        EFI::EFI_STATUS SetMode(UINT32 modeNumber);
        UINT32 GetCurrentMode();
        UINT32 GetModeCount();
        UINTN GetHeight();
        UINTN GetWidth();
        void ClearScreen();
        void ClearScreen(Color color);
        void ClearScreen(Color* color);
        void ClearScreen(EFI::EFI_GRAPHICS_OUTPUT_BLT_PIXEL* color);
        void ClearScreen(UINT32 color);
        void ClearScreen(UINT8 r, UINT8 g, UINT8 b, UINT8 a = (UINT8)0xFF);
        void DrawCircle(UINTN xPos, UINTN yPos, UINTN radius,UINTN thickness);
        void DrawCircle(UINTN xPos, UINTN yPos, UINTN radius,UINTN thickness, Color color);
        void DrawCircle(UINTN xPos, UINTN yPos, UINTN radius,UINTN thickness, Color* color);
        void DrawCircle(UINTN xPos, UINTN yPos, UINTN radius,UINTN thickness, EFI::EFI_GRAPHICS_OUTPUT_BLT_PIXEL* color);
        void DrawCircle(UINTN xPos, UINTN yPos, UINTN radius,UINTN thickness, UINT32 color);
        void DrawCircle(UINTN xPos, UINTN yPos, UINTN radius,UINTN thickness, UINT8 r, UINT8 g, UINT8 b, UINT8 a = (UINT8)0xFF);
        void DrawFilledCircle(UINTN xPos, UINTN yPos, UINTN radius);
        void DrawFilledCircle(UINTN xPos, UINTN yPos, UINTN radius, Color color);
        void DrawFilledCircle(UINTN xPos, UINTN yPos, UINTN radius, Color* color);
        void DrawFilledCircle(UINTN xPos, UINTN yPos, UINTN radius, EFI::EFI_GRAPHICS_OUTPUT_BLT_PIXEL* color);
        void DrawFilledCircle(UINTN xPos, UINTN yPos, UINTN radius, UINT32 color);
        void DrawFilledCircle(UINTN xPos, UINTN yPos, UINTN radius, UINT8 r, UINT8 g, UINT8 b, UINT8 a = (UINT8)0xFF);
        void DrawFilledRectangle(UINTN xPos, UINTN yPos, UINTN width, UINTN height);
        void DrawFilledRectangle(UINTN xPos, UINTN yPos, UINTN width, UINTN height, Color color);
        void DrawFilledRectangle(UINTN xPos, UINTN yPos, UINTN width, UINTN height, Color* color);
        void DrawFilledRectangle(UINTN xPos, UINTN yPos, UINTN width, UINTN height, EFI::EFI_GRAPHICS_OUTPUT_BLT_PIXEL* color);
        void DrawFilledRectangle(UINTN xPos, UINTN yPos, UINTN width, UINTN height, UINT32 color);
        void DrawFilledRectangle(UINTN xPos, UINTN yPos, UINTN width, UINTN height, UINT8 r, UINT8 g, UINT8 b, UINT8 a = (UINT8)0xFF);
        void DrawLine(UINTN sXPos , UINTN sYPos, UINTN eXPos, UINTN eYPos, UINTN thickness);
        void DrawLine(UINTN sXPos, UINTN sYPos, UINTN eXPos, UINTN eYPos, UINTN thickness, Color color);
        void DrawLine(UINTN sXPos, UINTN sYPos, UINTN eXPos, UINTN eYPos, UINTN thickness, Color* color);
        void DrawLine(UINTN sXPos, UINTN sYPos, UINTN eXPos, UINTN eYPos, UINTN thickness, EFI::EFI_GRAPHICS_OUTPUT_BLT_PIXEL* color);
        void DrawLine(UINTN sXPos, UINTN sYPos, UINTN eXPos, UINTN eYPos, UINTN thickness, UINT32 color);
        void DrawLine(UINTN sXPos, UINTN sYPos, UINTN eXPos, UINTN eYPos, UINTN thickness, UINT8 r, UINT8 g, UINT8 b, UINT8 a = (UINT8)0xFF);
        void DrawRectangle(UINTN xPos, UINTN yPos, UINTN width, UINTN height,UINTN thickness);
        void DrawRectangle(UINTN xPos, UINTN yPos, UINTN width, UINTN height, UINTN thickness, Color color);
        void DrawRectangle(UINTN xPos, UINTN yPos, UINTN width, UINTN height, UINTN thickness, Color* color);
        void DrawRectangle(UINTN xPos, UINTN yPos, UINTN width, UINTN height, UINTN thickness, EFI::EFI_GRAPHICS_OUTPUT_BLT_PIXEL* color);
        void DrawRectangle(UINTN xPos, UINTN yPos, UINTN width, UINTN height, UINTN thickness, UINT32 color);
        void DrawRectangle(UINTN xPos, UINTN yPos, UINTN width, UINTN height, UINTN thickness, UINT8 r, UINT8 g, UINT8 b, UINT8 a = (UINT8)0xFF);
        void SetBackground(Color color);
        void SetBackground(Color* color);
        void SetBackground(EFI::EFI_GRAPHICS_OUTPUT_BLT_PIXEL* color);
        void SetBackground(UINT32 color);
        void SetBackground(UINT8 r, UINT8 g, UINT8 b, UINT8 a = (UINT8)0xFF);
        void SetBackgroundPixel(UINTN xPos, UINTN yPos);
        void SetBackgroundPixel(UINTN xPos, UINTN yPos, Color color);
        void SetBackgroundPixel(UINTN xPos, UINTN yPos, Color* color);
        void SetBackgroundPixel(UINTN xPos, UINTN yPos, EFI::EFI_GRAPHICS_OUTPUT_BLT_PIXEL* color);
        void SetBackgroundPixel(UINTN xPos, UINTN yPos, UINT32 color);
        void SetBackgroundPixel(UINTN xPos, UINTN yPos, UINT8 r, UINT8 g, UINT8 b, UINT8 a = (UINT8)0xFF);
        void SetForeground(Color color);
        void SetForeground(Color* color);
        void SetForeground(EFI::EFI_GRAPHICS_OUTPUT_BLT_PIXEL* color);
        void SetForeground(UINT32 color);
        void SetForeground(UINT8 r, UINT8 g, UINT8 b, UINT8 a = (UINT8)0xFF);
        void SetForegroundPixel(UINTN xPos, UINTN yPos);
        void SetForegroundPixel(UINTN xPos, UINTN yPos, Color color);
        void SetForegroundPixel(UINTN xPos, UINTN yPos, Color* color);
        void SetForegroundPixel(UINTN xPos, UINTN yPos, EFI::EFI_GRAPHICS_OUTPUT_BLT_PIXEL* color);
        void SetForegroundPixel(UINTN xPos, UINTN yPos, UINT32 color);
        void SetForegroundPixel(UINTN xPos, UINTN yPos, UINT8 r, UINT8 g, UINT8 b, UINT8 a = (UINT8)0xFF);

    private:
        EFI::EFI_GRAPHICS_OUTPUT_PROTOCOL* gop;
        EFI::EFI_GRAPHICS_OUTPUT_BLT_PIXEL CurrentBackground;
        EFI::EFI_GRAPHICS_OUTPUT_BLT_PIXEL CurrentForeground;
    };
}

