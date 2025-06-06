#pragma once
#include <Typedefs.h>
#include <FileSystem/FileHandle.h>
#include <Debugging/Debugger.h>


namespace Common::Graphics::Font::PCSF
{
	const CHAR PSF1_MAGIC[2] = { 0x36, 0x04 };

	

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
			CHAR Char[2];
			UINT16 Value;
		}Magic;

		PCSF1Mode Mode;
		UINT8 CharSize;

		BOOLEAN operator==(const PCSF1Hdr& other);

		BOOLEAN operator!=(const PCSF1Hdr& other);
	};
#pragma pack(pop)

#pragma pack(push, 1)
	struct PCSF1
	{
		static void LoadDebugger(Debugging::Debugger* debugger);
	public:
		PCSF1();
		PCSF1(Common::FileSystem::FileHandle* handle);

		PCSF1Hdr Header;
		UINT16 CharCount;
		BOOLEAN IsValid();
		UINT8* GetGlyph(UINT32 index);

		BOOLEAN operator==(const PCSF1& other);

		BOOLEAN operator!=(const PCSF1& other);

	private:
		UINT8** Glyphs;
		UnicodeSequence* UnicodeTable;
		BOOLEAN _isValid;
	};
#pragma pack(pop)

	const static PCSF1 Empty_PCSF1 = PCSF1();
}

