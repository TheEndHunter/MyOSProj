#pragma once
#include <Typedefs.h>
#include <FileSystem/FileHandle.h>

namespace Common::Graphics::Font::PCSF
{
	const CHAR PCSF2_MAGIC[4] = { 0x72, 0xb5, 0x4a, 0x86 };

	enum class PCSF2Flags : UINT32
	{
		None = 0x00000000,
		HasUnicodeTable = 0x00000001,
	};

	const UINT16 PSF2_SEPARATOR  = 0xFFFF;
	const UINT16 PSF2_STARTSEQ = 0xFFFE;

#pragma pack(push, 1)
	struct PCSF2Hdr
	{
	public:
		PCSF2Hdr();
		PCSF2Hdr(Common::FileSystem::FileHandle* handle);

		union
		{
			CHAR Char[4];
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
		PCSF2(Common::FileSystem::FileHandle* handle);

		PCSF2Hdr Header;
		BOOLEAN IsValid();

		UINT8* GetGlyph8(UINT8 index);
		UINT16* GetGlyph16(UINT8 index);
		UINT32* GetGlyph32(UINT8 index);
		UINT64* GetGlyph64(UINT8 index);
	private:

		union
		{
			UINT8* _8;
			UINT16* _16;
			UINT32* _32;
			UINT64* _64;
		}Glyphs;
		BOOLEAN _isValid;
	};
#pragma pack(pop)

	const static PCSF2 Empty_PCSF2 = PCSF2();
}

