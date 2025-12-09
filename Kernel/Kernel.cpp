// Kernel.cpp : This file contains the 'EfiMain' function. Program execution begins and ends there.
//
#include "TypeDefs.h"
#include <Graphics/RenderContext.h>
#include <Graphics/MonitorContext.h>
#include <FileSystem/ESP/ESP_FS_Context.h>
#include <System/Console.h>
#include <Graphics/Font/FontManager.h>
#include <System/MemoryManagement/Allocator.h>
#include <System/MemoryManagement/KernelAllocator.h>

#include <System/Environment/KernelErrors.h>


namespace kernel
{
	using namespace Common::Graphics;

	const CHAR16* fontFile = u"\\Assets\\Fonts\\ZapV24\\ZapVGA09.psf";

	Common::System::Environment::KernelError CDECL KrnlMain(Common::System::MemoryManagement::Allocator* efiAlloc, Common::Debugging::Debugger* debugger, RenderContext* rendererCtx, MonitorContext* monitorCtx, Common::FileSystem::ESP::ESP_FS_Context* efiSysPart, Common::FileSystem::ESP::ESP_FS_Context* sysPart, Common::FileSystem::ESP::ESP_FS_Context* libPart)
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
		new int(0); // Force the allocator to be initalized

		Common::FileSystem::SetFileSystemDebugger(debugger);
		Common::FileSystem::ESP::SetESPDebugger(debugger);
		Common::Graphics::Font::SetFontDebugLogger(debugger);
		Common::Graphics::Font::PCSF::PCSF1::LoadDebugger(debugger);
		debugger->PrintInfoLine(u"Allocator Set");

		if (!libPart->OpenVolume())
		{
			return Common::System::Environment::KernelError::VolumeOpenFailed;
		}

		rendererCtx->DrawRectangle(200, 200, 200, 200, Colours::Red);
		rendererCtx->DrawRectangle(210, 210, 180, 180, Colours::Green);
		rendererCtx->DrawRectangle(220, 220, 160, 160, Colours::Blue);
		rendererCtx->DrawRectangle(230, 230, 140, 140, Colours::White);
		
		rendererCtx->ClearScreen(Colours::Bisque);

		BOOLEAN b = Common::System::Environment::UTF<CHAR16>::IsNullEmptyOrWhiteSpace(u"ss");
		debugger->PrintDebug(u"ss is NullEmptyOrWhiteSpace: ");
		debugger->PrintDebugLine(Common::System::Environment::UTF<CHAR16>::ToString(b));

		BOOLEAN b1 = Common::System::Environment::UTF<CHAR16>::IsNullEmptyOrWhiteSpace(u"  \\");
		debugger->PrintDebug(u"'  \\' is NullEmptyOrWhiteSpace: ");
		debugger->PrintDebugLine(Common::System::Environment::UTF<CHAR16>::ToString(b1));



		if (!libPart->FileExists(fontFile))
		{
			debugger->PrintCritical(u"Font file does not exist");
			debugger->PrintCriticalLine(fontFile);
			debugger->WaitForKey();
			return Common::System::Environment::KernelError::FontInvalid;
		}
		
		Common::Graphics::Font::PCSF::PCSF1* font1 = Common::Graphics::Font::FontManager::LoadPSF1Font(libPart, fontFile);

		if (font1 == nullptr)
		{
			debugger->PrintCritical(u"Font unable to load: ");
			debugger->PrintCriticalLine(Common::System::Environment::UTF<CHAR16>::ToString(libPart->LastStatus));
			debugger->WaitForKey();
			return Common::System::Environment::KernelError::FontPtrNull;
		}

		if (!font1->IsValid())
		{
			return Common::System::Environment::KernelError::FontInvalid;
		}

		Common::System::Console console = Common::System::Console(rendererCtx, Common::System::ConsoleColour::LightCyan, Common::System::ConsoleColour::Black , font1);
		console.ClearScreen();

		console.WriteLine(u"Hello, World!");

		return Common::System::Environment::KernelError::Success;
	}
}

