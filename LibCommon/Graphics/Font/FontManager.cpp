#include <Graphics/Font/FontManager.h>
#include <Graphics/Font/PCSF/PCSF1.h>
#include <Graphics/Font/PCSF/PCSF2.h>

namespace Common::Graphics::Font
{
	PCSF::PCSF1 FontManager::LoadPSF1Font(Common::FileSystem::ESP::ESP_FS_Context* fsCtx, const CHAR16* path)
	{
		return PCSF::PCSF1();
	}

	PCSF::PCSF2 FontManager::LoadPSF2Font(Common::FileSystem::ESP::ESP_FS_Context* fsCtx, const CHAR16* path)
	{
		return PCSF::PCSF2();
	}
}