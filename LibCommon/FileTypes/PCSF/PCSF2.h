#pragma once
#include <Typedefs.h>
#include <FileSystem/ESP/FileHandle.h>

namespace Common::FileTypes::PCSF
{
	const CCHAR PCSF2_MAGIC[4] = { 0x72,0xb5,0x4a,0x86 };

	enum PCSF2Flags : UINT32
	{
		None = 0x00000000,
		HasUnicodeTable = 0x00000001,
	};

	const UINT16 PSF1_SEPARATOR  = 0xFFFF;
	const UINT16 PSF1_STARTSEQ = 0xFFFE;

#pragma pack(push, 1)
	struct PCSF2Hdr
	{
	public:
		PCSF2Hdr();
		PCSF2Hdr(Common::FileSystem::ESP::FileHandle* handle);

		union
		{
			CCHAR Char[4];
			UINT32 Value;
		}Magic;
		UINT32 Version;
		UINT32 HeaderSize;
		PCSF2Flags Flags;
		UINT32 Length;
		UINT32 GlyphSize;
		UINT32 Height;
		UINT32 Width;
	};
#pragma pack(pop)

#pragma pack(push, 1)
	struct PCSF2
	{
	public:
		PCSF2();
		PCSF2(Common::FileSystem::ESP::FileHandle* handle);

		PCSF2Hdr Header;
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

