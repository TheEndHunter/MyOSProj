#pragma once

#include <TypeDefs.h>

namespace Common::Graphics::Font
{
	struct IFont
	{
	public:
		virtual UINT64 GetCharWidth() = 0;
		virtual UINT64 GetCharHeight() = 0;
		virtual BOOLEAN SupportsUnicode() = 0;
		virtual VOID_PTR GetGlyph(UINT64 codePoint) = 0;
		virtual ~IFont() = 0;
	};
}