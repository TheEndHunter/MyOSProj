#pragma once
#include "UEFIDef.h"
#include "EFI_STATUS.h"
#include "EFI_HANDLE.h"
#include "EFI_SYSTEM_TABLE.h"
#include "Protocols/Graphics/EFI_GRAPHICS_OUTPUT_PROTOCOL.h"
#include <Protocols/Graphics/EFI_GRAPHICS_OUTPUT_MODE_INFORMATION.h>
#include <Protocols/Graphics/EFI_GRAPHICS_OUTPUT_BLT_PIXEL.h>

namespace Bootloader::Graphics
{
    struct GraphicsContext
    {
    public:
       GraphicsContext();
       EFI::EFI_STATUS Initialize(EFI::EFI_HANDLE hnd, EFI::EFI_SYSTEM_TABLE* sysTable);
       
       EFI::EFI_STATUS Terminate(EFI::EFI_HANDLE hnd, EFI::EFI_SYSTEM_TABLE* sysTable);

       void SetForegroundPixel(UINTN xPos, UINTN yPos);
       void SetForegroundPixel(UINTN xPos, UINTN yPos, EFI::EFI_GRAPHICS_OUTPUT_BLT_PIXEL* color);
       void SetForegroundPixel(UINTN xPos, UINTN yPos, UINT8 r, UINT8 g, UINT8 b, UINT8 a = (UINT8)0xFF);
       void SetForegroundPixel(UINTN xPos, UINTN yPos, UINT32 color);

       void SetBackgroundPixel(UINTN xPos, UINTN yPos);
       void SetBackgroundPixel(UINTN xPos, UINTN yPos, EFI::EFI_GRAPHICS_OUTPUT_BLT_PIXEL* color);
       void SetBackgroundPixel(UINTN xPos, UINTN yPos, UINT8 r, UINT8 g, UINT8 b, UINT8 a = (UINT8)0xFF);
       void SetBackgroundPixel(UINTN xPos, UINTN yPos, UINT32 color);

       void ClearScreen();
       void ClearScreen(EFI::EFI_GRAPHICS_OUTPUT_BLT_PIXEL* color);
       void ClearScreen(UINT8 r, UINT8 g, UINT8 b, UINT8 a = (UINT8)0xFF);
       void ClearScreen(UINT32 color);

       void DrawRectangle(UINTN xPos, UINTN yPos, UINTN width, UINTN height);
       void DrawRectangle(UINTN xPos, UINTN yPos, UINTN width, UINTN height, EFI::EFI_GRAPHICS_OUTPUT_BLT_PIXEL* color);
       void DrawRectangle(UINTN xPos, UINTN yPos, UINTN width, UINTN height, UINT8 r, UINT8 g, UINT8 b, UINT8 a = (UINT8)0xFF);
       void DrawRectangle(UINTN xPos, UINTN yPos, UINTN width, UINTN height, UINT32 color);

       //void DrawFilledRectangle(UINTN xPos, UINTN yPos, UINTN width, UINTN height);
       //void DrawFilledRectangle(UINTN xPos, UINTN yPos, UINTN width, UINTN height, EFI::EFI_GRAPHICS_OUTPUT_BLT_PIXEL* color);
       //void DrawFilledRectangle(UINTN xPos, UINTN yPos, UINTN width, UINTN height, UINT8 r, UINT8 g, UINT8 b, UINT8 a = (UINT8)0xFF);
       //void DrawFilledRectangle(UINTN xPos, UINTN yPos, UINTN width, UINTN height, UINT32 color);

       //void DrawLine(UINTN xPos, UINTN yPos, UINTN x2Pos, UINTN y2Pos);
       //void DrawLine(UINTN xPos, UINTN yPos, UINTN x2Pos, UINTN y2Pos, EFI::EFI_GRAPHICS_OUTPUT_BLT_PIXEL* color);
       //void DrawLine(UINTN xPos, UINTN yPos, UINTN x2Pos, UINTN y2Pos, UINT8 r, UINT8 g, UINT8 b, UINT8 a = (UINT8)0xFF);
       //void DrawLine(UINTN xPos, UINTN yPos, UINTN x2Pos, UINTN y2Pos, UINT32 color);

       //void DrawCircle(UINTN xPos, UINTN yPos, UINTN radius);
       //void DrawCircle(UINTN xPos, UINTN yPos, UINTN radius, EFI::EFI_GRAPHICS_OUTPUT_BLT_PIXEL* color);
       //void DrawCircle(UINTN xPos, UINTN yPos, UINTN radius, UINT8 r, UINT8 g, UINT8 b, UINT8 a = (UINT8)0xFF);
       //void DrawCircle(UINTN xPos, UINTN yPos, UINTN radius, UINT32 color);

       //void DrawFilledCircle(UINTN xPos, UINTN yPos, UINTN radius);
       //void DrawFilledCircle(UINTN xPos, UINTN yPos, UINTN radius, EFI::EFI_GRAPHICS_OUTPUT_BLT_PIXEL* color);
       //void DrawFilledCircle(UINTN xPos, UINTN yPos, UINTN radius, UINT8 r, UINT8 g, UINT8 b, UINT8 a = (UINT8)0xFF);
       //void DrawFilledCircle(UINTN xPos, UINTN yPos, UINTN radius, UINT32 color);

       void SetBackground(EFI::EFI_GRAPHICS_OUTPUT_BLT_PIXEL* color);
       void SetBackground(UINT8 r, UINT8 g, UINT8 b, UINT8 a = (UINT8)0xFF);
       void SetBackground(UINT32 color);

       void SetForeground(EFI::EFI_GRAPHICS_OUTPUT_BLT_PIXEL* color);
       void SetForeground(UINT8 r, UINT8 g, UINT8 b, UINT8 a = (UINT8)0xFF);
       void SetForeground(UINT32 color);

       EFI::EFI_GRAPHICS_OUTPUT_BLT_PIXEL GetBackground() const;
       EFI::EFI_GRAPHICS_OUTPUT_BLT_PIXEL GetForeground() const;

        /*
        * Graphics output protocol mode selection with auto adjustment of pixel format to match selected mode's settings
        */

       EFI::EFI_STATUS SetMode(UINT32 modeNumber);
       EFI::EFI_STATUS QueryMode(UINT32 modeNumber,OUT UINTN* size,OUT EFI::EFI_GRAPHICS_OUTPUT_MODE_INFORMATION* info);
       UINT32 GetModeCount();
       UINT32 GetCurrentMode();

       UINTN GetWidth();
       UINTN GetHeight();


    private:
        EFI::EFI_GRAPHICS_OUTPUT_PROTOCOL* gop;

        EFI::EFI_GRAPHICS_OUTPUT_BLT_PIXEL CurrentBackground;
        EFI::EFI_GRAPHICS_OUTPUT_BLT_PIXEL CurrentForeground;
    };
}

