#pragma once
#include <Typedefs.h>
#include <FileSystem/ESP/FileHandle.h>

namespace Common::FileTypes::PCSF
{
	const CCHAR PSF1_MAGIC[2] = { 0x36, 0x04 };

	enum PSF1Mode : UINT8
	{
		None = 0,
		Length512 = 1,
		HasUnicode = 2,
		HasSeq = 2,
	};

	const UINT16 PSF1_SEPARATOR  = 0xFFFF;
	const UINT16 PSF1_STARTSEQ = 0xFFFE;

#pragma pack(push, 1)
	struct PSF1Hdr
	{
	public:
		PSF1Hdr();
		PSF1Hdr(Common::FileSystem::ESP::FileHandle* handle);

		union
		{
			CCHAR Char[2];
			UINT16 Value;
		}Magic;

		PSF1Mode Mode;
		UINT8 CharSize;

	};
#pragma pack(pop)

#pragma pack(push, 1)
	struct PSF1
	{
	public:
		PSF1();
		PSF1(Common::FileSystem::ESP::FileHandle* handle);

		PSF1Hdr Header;
		BOOLEAN IsValid();
		UINT8 GetGlyph(UINT8 index);
		UINT16 GetGlyphUnicode(UINT8 index);
	private:

		union
		{
			UINT8* _8;
			UINT16* _16;

		}Glyphs;
		BOOLEAN _isValid;
	};
#pragma pack(pop)
}

