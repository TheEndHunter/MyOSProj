#include <Graphics/Font/FontManager.h>
#include <FileTypes/PCSF/PCSF1.h>
#include <FileTypes/PCSF/PCSF2.h>
#include<System/MemoryManagement/Allocator.h>

namespace Common::Graphics::Font
{
	const Debugging::Debugger* _fontDebugger = nullptr;

	void SetFontDebugLogger(Debugging::Debugger* debugger)
	{
		_fontDebugger = debugger;
	}

	PCSF::PCSF1* FontManager::LoadPSF1Font(Common::FileSystem::ESP::ESP_FS_Context* fsCtx, const CHAR16* path)
	{
		if (fsCtx == nullptr) return nullptr;

		if (System::Environment::UTF<CHAR16>::IsNullEmptyOrWhiteSpace(path)) return nullptr;

		_fontDebugger->PrintInfoLine(u"Loading PSF1 Font From Path:");
		_fontDebugger->PrintInfoLine(path);

		/*Get File Info and Open File, If any fail, return null*/
		Common::FileSystem::FileInfo fileInfo = fsCtx->GetFileInfo(path);

		if (fileInfo == Common::FileSystem::Empty_FileInfo) return nullptr;

		_fontDebugger->PrintInfo(u"Found File: ");
		_fontDebugger->PrintInfoLine(fileInfo.FileName);
		_fontDebugger->PrintInfo(u"File Size: ");
		_fontDebugger->PrintInfoLine(System::Environment::UTF<CHAR16>::ToString(fileInfo.Size));
		_fontDebugger->PrintInfo(u"File Physical Size: ");
		_fontDebugger->PrintInfoLine(System::Environment::UTF<CHAR16>::ToString(fileInfo.PhysicalSize));
		_fontDebugger->PrintInfo(u"File Attributes: ");
		_fontDebugger->PrintInfoLine(System::Environment::UTF<CHAR16>::ToHex(fileInfo.Attribute));

		auto handle = fsCtx->OpenFile(&fileInfo, Common::FileSystem::FileMode::Read,Common::FileSystem::FileAttribute::ReadOnly);

		if (fsCtx->LastStatus != EFI::EFI_STATUS::SUCCESS)
		{
			_fontDebugger->PrintError(u"Failed To Open File, Error: ");
			_fontDebugger->PrintErrorLine(Common::System::Environment::UTF<CHAR16>::ToString(fsCtx->LastStatus));
			return nullptr;
		}

		if (handle == Common::FileSystem::Empty_FileHandle)
		{
			_fontDebugger->PrintInfoLine(u"Failed To Open File, Invalid file Handle");
			fsCtx->LastStatus = EFI::EFI_STATUS::END_OF_FILE;
			return nullptr;
		}

		if (!handle.IsValid())
		{
			_fontDebugger->PrintInfoLine(u"Failed To Open File, Invalid file Pointer");
			fsCtx->LastStatus = EFI::EFI_STATUS::CRC_ERROR;
			return nullptr;
		}

		_fontDebugger->PrintInfoLine(u"Allocating File...");
		PCSF::PCSF1* font = new PCSF::PCSF1(&handle);
		
		_fontDebugger->PrintInfoLine(Common::System::Environment::UTF<CHAR16>::ToHex(font));

		handle.SetPosition(0UL);

		_fontDebugger->PrintInfoLine(u"Reading File:");
		_fontDebugger->PrintInfoLine(fileInfo.FileName);
		/*Create PCSF1 Font*/
		

		if (!font->IsValid())
		{
			_fontDebugger->PrintInfoLine(u"Invalid File:");
			_fontDebugger->PrintInfoLine(fileInfo.FileName);
			fsCtx->LastStatus = EFI::EFI_STATUS::INVALID_PARAMETER;
			return nullptr;
		}

		_fontDebugger->PrintInfoLine(u"Valid File:");
		_fontDebugger->PrintInfoLine(fileInfo.FileName);
		return font;
	}

	PCSF::PCSF2* FontManager::LoadPSF2Font(Common::FileSystem::ESP::ESP_FS_Context* fsCtx, const CHAR16* path)
	{
		if (fsCtx == nullptr) return nullptr;

		if (System::Environment::UTF<CHAR16>::IsNullEmptyOrWhiteSpace(path)) return nullptr;

		_fontDebugger->PrintInfoLine(u"Loading PSF1 Font From Path:");
		_fontDebugger->PrintInfoLine(path);

		/*Get File Info and Open File, If any fail, return null*/
		Common::FileSystem::FileInfo fileInfo = fsCtx->GetFileInfo(path);

		if (fileInfo == Common::FileSystem::Empty_FileInfo) return nullptr;

		_fontDebugger->PrintInfo(u"Found File: ");
		_fontDebugger->PrintInfoLine(fileInfo.FileName);
		_fontDebugger->PrintInfo(u"File Size: ");
		_fontDebugger->PrintInfoLine(System::Environment::UTF<CHAR16>::ToString(fileInfo.Size));
		_fontDebugger->PrintInfo(u"File Physical Size: ");
		_fontDebugger->PrintInfoLine(System::Environment::UTF<CHAR16>::ToString(fileInfo.PhysicalSize));
		_fontDebugger->PrintInfo(u"File Attributes: ");
		_fontDebugger->PrintInfoLine(System::Environment::UTF<CHAR16>::ToHex(fileInfo.Attribute));

		auto handle = fsCtx->OpenFile(&fileInfo, Common::FileSystem::FileMode::Read, Common::FileSystem::FileAttribute::ReadOnly);

		if (fsCtx->LastStatus != EFI::EFI_STATUS::SUCCESS)
		{
			_fontDebugger->PrintError(u"Failed To Open File, Error: ");
			_fontDebugger->PrintErrorLine(Common::System::Environment::UTF<CHAR16>::ToString(fsCtx->LastStatus));
			return nullptr;
		}

		if (handle == Common::FileSystem::Empty_FileHandle)
		{
			_fontDebugger->PrintInfoLine(u"Failed To Open File, Invalid file Handle");
			fsCtx->LastStatus = EFI::EFI_STATUS::END_OF_FILE;
			return nullptr;
		}

		if (!handle.IsValid())
		{
			_fontDebugger->PrintInfoLine(u"Failed To Open File, Invalid file Pointer");
			fsCtx->LastStatus = EFI::EFI_STATUS::CRC_ERROR;
			return nullptr;
		}

		_fontDebugger->PrintInfoLine(u"Allocating File...");
		PCSF::PCSF2* font = new PCSF::PCSF2(&handle);

		_fontDebugger->PrintInfoLine(Common::System::Environment::UTF<CHAR16>::ToHex(font));

		handle.SetPosition(0UL);

		_fontDebugger->PrintInfoLine(u"Reading File:");
		_fontDebugger->PrintInfoLine(fileInfo.FileName);
		/*Create PCSF1 Font*/


		if (!font->IsValid())
		{
			_fontDebugger->PrintInfoLine(u"Invalid File:");
			_fontDebugger->PrintInfoLine(fileInfo.FileName);
			fsCtx->LastStatus = EFI::EFI_STATUS::INVALID_PARAMETER;
			return nullptr;
		}

		_fontDebugger->PrintInfoLine(u"Valid File:");
		_fontDebugger->PrintInfoLine(fileInfo.FileName);
		return font;
	}
}