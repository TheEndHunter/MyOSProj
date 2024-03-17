#pragma once
#include "TypeDefs.h"
#include "EFI_STATUS.h"
#include "EFI_HANDLE.h"
#include "EFI_SYSTEM_TABLE.h"
#include "Protocols/Graphics/EFI_GRAPHICS_OUTPUT_PROTOCOL.h"
#include <Protocols/Graphics/EFI_GRAPHICS_OUTPUT_MODE_INFORMATION.h>
#include <Protocols/Graphics/EFI_GRAPHICS_OUTPUT_BLT_PIXEL.h>
#include <Graphics/Colour.h>

namespace Common::Graphics
{
    using namespace EFI;
    struct GraphicsContext
    { 
    protected:
       GraphicsContext(EFI::EFI_GRAPHICS_OUTPUT_PROTOCOL* g);
    public:
        static EFI::EFI_STATUS LastStatus;
        static GraphicsContext Initialize(EFI::EFI_HANDLE hnd, EFI::EFI_SYSTEM_TABLE* sysTable); 
        void Terminate(EFI::EFI_HANDLE hnd, EFI::EFI_SYSTEM_TABLE* sysTable);

        Colour GetBackground() const;
        Colour GetForeground() const;
        EFI::EFI_STATUS QueryMode(UINT32 modeNumber,OUT UINTN* size,OUT EFI_GRAPHICS_OUTPUT_MODE_INFORMATION** info);
        EFI::EFI_STATUS SetMode(UINT32 modeNumber);
        UINT32 GetCurrentMode();
        UINT32 GetModeCount();
        UINTN GetHeight();
        UINTN GetWidth();
        void ClearScreen();
        void ClearScreen(Colour colour);
        void ClearScreen(Colour* colour);
        void ClearScreen(EFI::EFI_GRAPHICS_OUTPUT_BLT_PIXEL* colour);
        void ClearScreen(UINT32 colour);
        void ClearScreen(UINT8 r, UINT8 g, UINT8 b, UINT8 a = (UINT8)0xFF);
        void DrawCircle(UINTN xPos, UINTN yPos, UINTN radius,UINTN thickness);
        void DrawCircle(UINTN xPos, UINTN yPos, UINTN radius,UINTN thickness, Colour colour);
        void DrawCircle(UINTN xPos, UINTN yPos, UINTN radius,UINTN thickness, Colour* colour);
        void DrawCircle(UINTN xPos, UINTN yPos, UINTN radius,UINTN thickness, EFI::EFI_GRAPHICS_OUTPUT_BLT_PIXEL* colour);
        void DrawCircle(UINTN xPos, UINTN yPos, UINTN radius,UINTN thickness, UINT32 colour);
        void DrawCircle(UINTN xPos, UINTN yPos, UINTN radius,UINTN thickness, UINT8 r, UINT8 g, UINT8 b, UINT8 a = (UINT8)0xFF);
        void DrawFilledCircle(UINTN xPos, UINTN yPos, UINTN radius);
        void DrawFilledCircle(UINTN xPos, UINTN yPos, UINTN radius, Colour colour);
        void DrawFilledCircle(UINTN xPos, UINTN yPos, UINTN radius, Colour* colour);
        void DrawFilledCircle(UINTN xPos, UINTN yPos, UINTN radius, EFI::EFI_GRAPHICS_OUTPUT_BLT_PIXEL* colour);
        void DrawFilledCircle(UINTN xPos, UINTN yPos, UINTN radius, UINT32 colour);
        void DrawFilledCircle(UINTN xPos, UINTN yPos, UINTN radius, UINT8 r, UINT8 g, UINT8 b, UINT8 a = (UINT8)0xFF);
        void DrawFilledRectangle(UINTN xPos, UINTN yPos, UINTN width, UINTN height);
        void DrawFilledRectangle(UINTN xPos, UINTN yPos, UINTN width, UINTN height, Colour colour);
        void DrawFilledRectangle(UINTN xPos, UINTN yPos, UINTN width, UINTN height, Colour* colour);
        void DrawFilledRectangle(UINTN xPos, UINTN yPos, UINTN width, UINTN height, EFI::EFI_GRAPHICS_OUTPUT_BLT_PIXEL* colour);
        void DrawFilledRectangle(UINTN xPos, UINTN yPos, UINTN width, UINTN height, UINT32 colour);
        void DrawFilledRectangle(UINTN xPos, UINTN yPos, UINTN width, UINTN height, UINT8 r, UINT8 g, UINT8 b, UINT8 a = (UINT8)0xFF);
        void DrawLine(UINTN sXPos , UINTN sYPos, UINTN eXPos, UINTN eYPos, UINTN thickness);
        void DrawLine(UINTN sXPos, UINTN sYPos, UINTN eXPos, UINTN eYPos, UINTN thickness, Colour colour);
        void DrawLine(UINTN sXPos, UINTN sYPos, UINTN eXPos, UINTN eYPos, UINTN thickness, Colour* colour);
        void DrawLine(UINTN sXPos, UINTN sYPos, UINTN eXPos, UINTN eYPos, UINTN thickness, EFI::EFI_GRAPHICS_OUTPUT_BLT_PIXEL* colour);
        void DrawLine(UINTN sXPos, UINTN sYPos, UINTN eXPos, UINTN eYPos, UINTN thickness, UINT32 colour);
        void DrawLine(UINTN sXPos, UINTN sYPos, UINTN eXPos, UINTN eYPos, UINTN thickness, UINT8 r, UINT8 g, UINT8 b, UINT8 a = (UINT8)0xFF);
        void DrawRectangle(UINTN xPos, UINTN yPos, UINTN width, UINTN height,UINTN thickness);
        void DrawRectangle(UINTN xPos, UINTN yPos, UINTN width, UINTN height, UINTN thickness, Colour colour);
        void DrawRectangle(UINTN xPos, UINTN yPos, UINTN width, UINTN height, UINTN thickness, Colour* colour);
        void DrawRectangle(UINTN xPos, UINTN yPos, UINTN width, UINTN height, UINTN thickness, EFI::EFI_GRAPHICS_OUTPUT_BLT_PIXEL* colour);
        void DrawRectangle(UINTN xPos, UINTN yPos, UINTN width, UINTN height, UINTN thickness, UINT32 colour);
        void DrawRectangle(UINTN xPos, UINTN yPos, UINTN width, UINTN height, UINTN thickness, UINT8 r, UINT8 g, UINT8 b, UINT8 a = (UINT8)0xFF);
        void SetBackground(Colour colour);
        void SetBackground(Colour* colour);
        void SetBackground(EFI::EFI_GRAPHICS_OUTPUT_BLT_PIXEL* colour);
        void SetBackground(UINT32 colour);
        void SetBackground(UINT8 r, UINT8 g, UINT8 b, UINT8 a = (UINT8)0xFF);
        void SetBackgroundPixel(UINTN xPos, UINTN yPos);
        void SetBackgroundPixel(UINTN xPos, UINTN yPos, Colour colour);
        void SetBackgroundPixel(UINTN xPos, UINTN yPos, Colour* colour);
        void SetBackgroundPixel(UINTN xPos, UINTN yPos, EFI::EFI_GRAPHICS_OUTPUT_BLT_PIXEL* colour);
        void SetBackgroundPixel(UINTN xPos, UINTN yPos, UINT32 colour);
        void SetBackgroundPixel(UINTN xPos, UINTN yPos, UINT8 r, UINT8 g, UINT8 b, UINT8 a = (UINT8)0xFF);
        void SetForeground(Colour colour);
        void SetForeground(Colour* colour);
        void SetForeground(EFI::EFI_GRAPHICS_OUTPUT_BLT_PIXEL* colour);
        void SetForeground(UINT32 colour);
        void SetForeground(UINT8 r, UINT8 g, UINT8 b, UINT8 a = (UINT8)0xFF);
        void SetForegroundPixel(UINTN xPos, UINTN yPos);
        void SetForegroundPixel(UINTN xPos, UINTN yPos, Colour colour);
        void SetForegroundPixel(UINTN xPos, UINTN yPos, Colour* colour);
        void SetForegroundPixel(UINTN xPos, UINTN yPos, EFI::EFI_GRAPHICS_OUTPUT_BLT_PIXEL* colour);
        void SetForegroundPixel(UINTN xPos, UINTN yPos, UINT32 colour);
        void SetForegroundPixel(UINTN xPos, UINTN yPos, UINT8 r, UINT8 g, UINT8 b, UINT8 a = (UINT8)0xFF);

    private:
        EFI::EFI_GRAPHICS_OUTPUT_PROTOCOL* gop;
        EFI::EFI_GRAPHICS_OUTPUT_BLT_PIXEL CurrentBackground;
        EFI::EFI_GRAPHICS_OUTPUT_BLT_PIXEL CurrentForeground;
    };
}

