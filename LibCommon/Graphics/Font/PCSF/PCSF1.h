#pragma once
#include <Typedefs.h>
#include <FileSystem/FileHandle.h>
#include <Graphics/Font/IFont.h>



namespace Common::Graphics::Font::PCSF
{
	const CCHAR PSF1_MAGIC[2] = { 0x36, 0x04 };

	struct UnicodeSequence
	{
		UINT8 length;
		UINT8* sequence;
	};

	enum class PCSF1Mode : UINT8
	{
		None = 0,
		// If this bit is set, the font face will have 512 glyphs.If it is unset, then the font face will have just 256 glyphs.
		MODE512 = 1,
		//If this bit is set, the font face will have a unicode table.
		MODEHASTAB = 2,
		//Equivalent to PSF1_MODEHASTAB
		MODESEQ = 4

	};	

	const UINT16 PSF1_SEPARATOR  = 0xFFFF;
	const UINT16 PSF1_STARTSEQ = 0xFFFE;

#pragma pack(push, 1)
	struct PCSF1Hdr
	{
	public:
		PCSF1Hdr();
		PCSF1Hdr(Common::FileSystem::FileHandle* handle);

		union
		{
			CCHAR Char[2];
			UINT16 Value;
		}Magic;

		PCSF1Mode Mode;
		UINT8 CharSize;
	};
#pragma pack(pop)

#pragma pack(push, 1)
	struct PCSF1 : IFont
	{
	public:
		PCSF1();
		PCSF1(Common::FileSystem::FileHandle* handle);
		~PCSF1();

		PCSF1Hdr Header;
		UINT16 CharCount;
		BOOLEAN IsValid();
		UINT8* GetGlyph(UINT16 index);

	private:
		UINT8* Glyphs;
		UnicodeSequence* UnicodeTable;
		BOOLEAN _isValid;

		// Inherited via Font
		UINT64 GetCharWidth() override;
		UINT64 GetCharHeight() override;
		BOOLEAN SupportsUnicode() override;
		VOID_PTR GetGlyph(UINT64 codePoint) override;
	};
#pragma pack(pop)
}

