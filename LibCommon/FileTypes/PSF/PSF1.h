#pragma once
#include <Typedefs.h>
#include <FileSystem/ESP/FileHandle.h>

namespace Common::FileTypes::PSF
{
	const CCHAR PSF1_MAGIC[2] = { 0x36, 0x04 };

	enum PSF1_Mode : UINT8
	{
		MODE512    = 0x01,
		MODEHASTAB = 0x02,
		MODEHASSEQ = 0x04,
		MAXMODE    = 0x05,
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

		PSF1_Mode Mode;
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

		union
		{
			UINT8*  _1;
			UINT16* _2;
			UINT32* _3;
			UINT64* _4;

		}Chars;

		BOOLEAN IsValid();
	private:
		BOOLEAN _isValid;
	};
#pragma pack(pop)
}

