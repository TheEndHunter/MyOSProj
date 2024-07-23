// Kernel.cpp : This file contains the 'EfiMain' function. Program execution begins and ends there.
//
#include "TypeDefs.h"
#include <Graphics/RenderContext.h>
#include <Graphics/MonitorContext.h>
#include <FileSystem/ESP/ESP_FS_Context.h>
#include <System/Console.h>
#include <Graphics/Font/FontManager.h>

namespace kernel
{
    using namespace Common::Graphics;

    UINT64 CDECL KrnlMain(RenderContext* rendererCtx, MonitorContext* monitorCtx, Common::FileSystem::ESP::ESP_FS_Context* efiSysPart, Common::FileSystem::ESP::ESP_FS_Context* sysPart, Common::FileSystem::ESP::ESP_FS_Context* libPart)
    {
         if(!libPart->OpenVolume())
		 {
			 return 0x8000000000000001;
		 }

         rendererCtx->DrawRectangle(200, 200, 200, 200, Colours::Red);
         rendererCtx->DrawRectangle(210, 210, 180, 180, Colours::Green);
         rendererCtx->DrawRectangle(220, 220, 160, 160, Colours::Blue);
         rendererCtx->DrawRectangle(230, 230, 140, 140, Colours::White);

		 Common::Graphics::Font::PCSF::PCSF1 font1 = Common::Graphics::Font::FontManager::LoadPSF1Font(libPart, u".\\Assets\\Fonts\\ZapV24\\ZapVGA09.psf");
         rendererCtx->ClearScreen(Colours::Azure);

         if (font1 == Common::Graphics::Font::PCSF::Empty_PCSF1)
		 {
			 return 0x8000000000000002;
		 }

         if (!font1.IsValid())
         {
             return 0x8000000000000003;
         }

		 Common::System::Console console = Common::System::Console(rendererCtx,Common::System::ConsoleColour::Black,Common::System::ConsoleColour::LightCyan,&font1);
         console.ClearScreen();

		 console.WriteLine(u"Hello, World!");

        return 0x0000000000000000;
    }
}
