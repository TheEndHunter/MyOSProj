// Kernel.cpp : This file contains the 'EfiMain' function. Program execution begins and ends there.
//
#include "TypeDefs.h"
#include <Graphics/RenderContext.h>
#include <Graphics/MonitorContext.h>
#include <FileSystem/ESP/ESP_FS_Context.h>



namespace kernel
{
    using namespace Common::Graphics;

     UINTN CDECL KrnlMain(RenderContext* rendererCtx, MonitorContext* monitorCtx, Common::FileSystem::ESP::ESP_FS_Context* efiSysPart, Common::FileSystem::ESP::ESP_FS_Context* sysPart, Common::FileSystem::ESP::ESP_FS_Context* libPart)
    {
         rendererCtx->DrawRectangle(200, 200, 200, 200, Colours::Red);
         rendererCtx->DrawRectangle(210, 210, 180, 180, Colours::Green);
         rendererCtx->DrawRectangle(220, 220, 160, 160, Colours::Blue);
         rendererCtx->DrawRectangle(230, 230, 140, 140, Colours::White);

        return 123;
    }
}
