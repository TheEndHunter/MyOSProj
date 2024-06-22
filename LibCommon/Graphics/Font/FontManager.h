#pragma once

#include <TypeDefs.h>
#include <FileSystem/ESP/ESP_FS_Context.h>

#include <Graphics/Font/PCSF/PCSF1.h>
#include <Graphics/Font/PCSF/PCSF2.h>

namespace Common::Graphics::Font
{
	class FontManager
	{
	public:
		static PCSF::PCSF1 LoadPSF1Font(Common::FileSystem::ESP::ESP_FS_Context* fsCtx, const CHAR16* path);
		static PCSF::PCSF2 LoadPSF2Font(Common::FileSystem::ESP::ESP_FS_Context* fsCtx, const CHAR16* path);
	};
}
