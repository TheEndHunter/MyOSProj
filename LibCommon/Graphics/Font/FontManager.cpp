#include <Graphics/Font/FontManager.h>
#include <Graphics/Font/PCSF/PCSF1.h>
#include <Graphics/Font/PCSF/PCSF2.h>

namespace Common::Graphics::Font
{
	PCSF::PCSF1 FontManager::LoadPSF1Font(Common::FileSystem::ESP::ESP_FS_Context* fsCtx, const CHAR16* path)
	{
		/*Get File Info and Open File, If any fail, return an Empty PCSF1 Font*/
		Common::FileSystem::FileInfo fileInfo = fsCtx->GetFileInfo(path);
		if (fileInfo == Common::FileSystem::Empty_FileInfo) return PCSF::Empty_PCSF1;

		auto handle = fsCtx->OpenFile(&fileInfo, Common::FileSystem::FileMode::Read,Common::FileSystem::FileAttribute::ReadOnly);
		if (handle == Common::FileSystem::Empty_FileHandle) return PCSF::Empty_PCSF1;

		/*Create PCSF1 Font*/
		return PCSF::PCSF1(&handle);
	}

	PCSF::PCSF2 FontManager::LoadPSF2Font(Common::FileSystem::ESP::ESP_FS_Context* fsCtx, const CHAR16* path)
	{
		/*Get File Info and Open File, If any fail, return an Empty PCSF2 Font*/
		Common::FileSystem::FileInfo fileInfo = fsCtx->GetFileInfo(path);
		if (fileInfo == Common::FileSystem::Empty_FileInfo) return PCSF::Empty_PCSF2;

		auto handle = fsCtx->OpenFile(&fileInfo, Common::FileSystem::FileMode::Read, Common::FileSystem::FileAttribute::ReadOnly);
		if (handle == Common::FileSystem::Empty_FileHandle) return PCSF::Empty_PCSF2;

		/*Create PCSF1 Font*/
		return PCSF::PCSF2(&handle);
	}
}