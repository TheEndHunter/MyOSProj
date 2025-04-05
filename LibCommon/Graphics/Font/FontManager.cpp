#include <Graphics/Font/FontManager.h>
#include <FileTypes/PCSF/PCSF1.h>
#include <FileTypes/PCSF/PCSF2.h>
#include<System/MemoryManagement/Allocator.h>

namespace Common::Graphics::Font
{
	Debugging::Debugger* FontManager::_Debugger = nullptr;

	void FontManager::SetDebugLogger(Debugging::Debugger* debugger)
	{
		FontManager::_Debugger = debugger;
	}

	PCSF::PCSF1* FontManager::LoadPSF1Font(Common::FileSystem::ESP::ESP_FS_Context* fsCtx, const CHAR16* path)
	{
		if (fsCtx == nullptr) return nullptr;

		if (System::Environment::UTF<CHAR16>::IsNullEmptyOrWhiteSpace(path)) return nullptr;

		FontManager::_Debugger->PrintInfoLine(u"Loading PSF1 Font From Path:");
		FontManager::_Debugger->PrintInfoLine(path);

		/*Get File Info and Open File, If any fail, return null*/
		Common::FileSystem::FileInfo fileInfo = fsCtx->GetFileInfo(path);

		if (fileInfo == Common::FileSystem::Empty_FileInfo) return nullptr;

		FontManager::_Debugger->PrintInfoLine(u"Found File:");
		FontManager::_Debugger->PrintInfoLine(fileInfo.FileName);

		auto handle = fsCtx->OpenFile(&fileInfo, Common::FileSystem::FileMode::Read,Common::FileSystem::FileAttribute::ReadOnly);
		if (handle == Common::FileSystem::Empty_FileHandle) return nullptr;

		if (!handle.IsValid())
		{
			FontManager::_Debugger->PrintInfoLine(u"Failed To Open File, Invalid file Pointer");
			return nullptr;
		}

		FontManager::_Debugger->PrintInfoLine(u"Allocating File...");
		PCSF::PCSF1* font = (PCSF::PCSF1*)new UINT8[](handle.Info.PhysicalSize);
		handle.SetPosition(0UL);

		FontManager::_Debugger->PrintInfoLine(u"Reading File:");
		FontManager::_Debugger->PrintInfoLine(fileInfo.FileName);
		/*Create PCSF1 Font*/
		new(font) PCSF::PCSF1(&handle);

		if (!font->IsValid())
		{
			FontManager::_Debugger->PrintInfoLine(u"Invalid File:");
			FontManager::_Debugger->PrintInfoLine(fileInfo.FileName);
			return nullptr;
		}

		FontManager::_Debugger->PrintInfoLine(u"Valid File:");
		FontManager::_Debugger->PrintInfoLine(fileInfo.FileName);
		return font;
	}

	PCSF::PCSF2* FontManager::LoadPSF2Font(Common::FileSystem::ESP::ESP_FS_Context* fsCtx, const CHAR16* path)
	{
		if (fsCtx == nullptr) return nullptr;

		if (System::Environment::UTF<CHAR16>::IsNullEmptyOrWhiteSpace(path)) return nullptr;

		FontManager::_Debugger->PrintInfoLine(u"Loading PSF2 Font From Path:");
		FontManager::_Debugger->PrintInfoLine(path);

		/*Get File Info and Open File, If any fail, return null*/
		Common::FileSystem::FileInfo fileInfo = fsCtx->GetFileInfo(path);

		if (fileInfo == Common::FileSystem::Empty_FileInfo) return nullptr;

		FontManager::_Debugger->PrintInfoLine(u"Found File:");
		FontManager::_Debugger->PrintInfoLine(fileInfo.FileName);

		auto handle = fsCtx->OpenFile(&fileInfo, Common::FileSystem::FileMode::Read, Common::FileSystem::FileAttribute::ReadOnly);
		if (handle == Common::FileSystem::Empty_FileHandle) return nullptr;

		FontManager::_Debugger->PrintInfoLine(u"Reading File:");
		FontManager::_Debugger->PrintInfoLine(fileInfo.FileName);

		/*Create PCSF2 Font*/
		PCSF::PCSF2* font = new PCSF::PCSF2(&handle);

		if (!font->IsValid())
		{
			FontManager::_Debugger->PrintInfoLine(u"Invalid File:");
			FontManager::_Debugger->PrintInfoLine(fileInfo.FileName);
			return nullptr;
		}

		FontManager::_Debugger->PrintInfoLine(u"Valid File:");
		FontManager::_Debugger->PrintInfoLine(fileInfo.FileName);
		return font;
	}
}