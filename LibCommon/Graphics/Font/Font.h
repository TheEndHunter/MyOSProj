#pragma once

#include "TypeDefs.h"
#include "FileSystem/FileSystemContext.h"

namespace Common::Graphics::Font
{
	class Font
	{
	protected:
			Font(void* data);
	public:
		static Font LoadFont(Common::FileSystem::ESP::ESP_FS_Context* fsCtx, const CHAR16* path);
	};
}
