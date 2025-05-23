// Kernel.cpp : This file contains the 'EfiMain' function. Program execution begins and ends there.
//
#include "TypeDefs.h"
#include <Graphics/RenderContext.h>
#include <Graphics/MonitorContext.h>
#include <FileSystem/ESP/ESP_FS_Context.h>
#include <System/Console.h>
#include <Graphics/Font/FontManager.h>
#include <System/MemoryManagement/Allocator.h>
#include <System/Environment/KernelErrors.h>

extern VOID_PTR  operator new(UINTN length);
extern VOID_PTR operator new[](UINTN length);
extern VOID_PTR operator new(UINTN length, VOID_PTR ptr);
extern VOID_PTR operator new[](UINTN length, VOID_PTR ptr);

extern void operator delete(VOID_PTR ptr);
extern void operator delete[](VOID_PTR ptr);
extern void operator delete(VOID_PTR ptr, UINTN length);
extern void operator delete[](VOID_PTR ptr, UINTN length);
extern void operator delete(VOID_PTR ptr, VOID_PTR ptr2);
extern void operator delete[](VOID_PTR ptr, VOID_PTR ptr2);

namespace kernel
{
    using namespace Common::Graphics;

    Common::System::Environment::KernelError CDECL KrnlMain(Common::System::MemoryManagement::Allocator* efiAlloc,Common::Debugging::Debugger* debugger, RenderContext* rendererCtx, MonitorContext* monitorCtx, Common::FileSystem::ESP::ESP_FS_Context* efiSysPart, Common::FileSystem::ESP::ESP_FS_Context* sysPart, Common::FileSystem::ESP::ESP_FS_Context* libPart)
    {
        if (Common::System::MemoryManagement::Allocator::SetWithExistingAllocator(efiAlloc) != Common::System::MemoryManagement::AllocatorStatus::Success)
        {
            debugger->PrintCriticalLine(u"Unable to use existing Allocator");
            return Common::System::Environment::KernelError::AllocatorNotSet;
        }

		auto alloc = Common::System::MemoryManagement::Allocator::GetInstance();

        if (alloc != efiAlloc)
        {
            debugger->PrintCriticalLine(u"allocator does not match!");
            return Common::System::Environment::KernelError::AllocatorNotMatched;
        }

        if (!alloc->IsInitalized())
        {
			debugger->PrintCriticalLine(u"Allocator is not initalized!");
			return Common::System::Environment::KernelError::AllocatorNotInitialized;
        }

        Common::System::Environment::UTF<CHAR>();
        Common::System::Environment::UTF<CHAR8>();
        Common::System::Environment::UTF<CHAR16>();

         if(!libPart->OpenVolume())
		 {
			 return Common::System::Environment::KernelError::VolumeOpenFailed;
		 }

         rendererCtx->DrawRectangle(200, 200, 200, 200, Colours::Red);
         rendererCtx->DrawRectangle(210, 210, 180, 180, Colours::Green);
         rendererCtx->DrawRectangle(220, 220, 160, 160, Colours::Blue);
         rendererCtx->DrawRectangle(230, 230, 140, 140, Colours::White);

		 Common::Graphics::Font::FontManager::SetDebugLogger(debugger);
		 Common::Graphics::Font::PCSF::PCSF1::LoadDebugger(debugger);


		 Common::Graphics::Font::PCSF::PCSF1* font1 = Common::Graphics::Font::FontManager::LoadPSF1Font(libPart, u"\\Assets\\Fonts\\ZapV24\\ZapVGA09.psf");
         rendererCtx->ClearScreen(Colours::Azure);

         if (font1 == nullptr)
		 {
			 return Common::System::Environment::KernelError::FontPtrNull;
		 }

         if (!font1->IsValid())
         {
             return Common::System::Environment::KernelError::FontInvalid;
         }

		 Common::System::Console console = Common::System::Console(rendererCtx,Common::System::ConsoleColour::Black,Common::System::ConsoleColour::LightCyan,font1);
         console.ClearScreen();

		 console.WriteLine(u"Hello, World!");

        return Common::System::Environment::KernelError::Success;
    }
}
