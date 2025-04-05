#pragma once

#include <TypeDefs.h>
#include <FileSystem/ESP/ESP_FS_Context.h>

#include <FileTypes/PCSF/PCSF1.h>
#include <FileTypes/PCSF/PCSF2.h>
#include <Debugging/Debugger.h>

namespace Common::Graphics::Font
{
	class FontManager
	{
	public:
		static void SetDebugLogger(Debugging::Debugger* debugger);
		static PCSF::PCSF1* LoadPSF1Font(Common::FileSystem::ESP::ESP_FS_Context* fsCtx, const CHAR16* path);
		static PCSF::PCSF2* LoadPSF2Font(Common::FileSystem::ESP::ESP_FS_Context* fsCtx, const CHAR16* path);
	private:
		static Debugging::Debugger* _Debugger;
	};
}
