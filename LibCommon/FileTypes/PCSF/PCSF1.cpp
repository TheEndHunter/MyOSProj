#include <FileTypes/PCSF/PCSF1.h>

namespace Common::FileTypes::PCSF
{
	PSF1::PSF1()
	{
		_isValid = false;
		Header = PSF1Hdr();
	}

	PSF1::PSF1(Common::FileSystem::ESP::FileHandle* handle)
	{
		Header = PSF1Hdr(handle);
		if (Header.Magic.Char[0] != PSF1_MAGIC[0] || Header.Magic.Char[1] != PSF1_MAGIC[1])
		{
			_isValid = true;
		}
		else
		{
			_isValid = false;
			return;
		}
		UINT32 length;

		if(Header.Mode == PSF1Mode::MODE512)
		{
			length = 512;
		}
		else
		{
			length = 256;
		}

		if (Header.Mode == PSF1Mode::MODEHASTAB)
		{
			length *= 2;
		}

		Glyphs._8 = new UINT8[length];
		handle->Read<UINT8>(Glyphs._8, length);
	}

	PSF1Hdr::PSF1Hdr()
	{
		Magic.Char[0] = 0;
		Magic.Char[1] = 0;
		Mode = PSF1Mode::None;
		CharSize = 0;
	}

	PSF1Hdr::PSF1Hdr(Common::FileSystem::ESP::FileHandle* handle)
	{
		handle->SetPosition(0UL);
		handle->Read<UINT16>(&Magic.Value);
		handle->Read<PSF1Mode>(&Mode);
		handle->Read<UINT8>(&CharSize);
	}

	BOOLEAN PSF1::IsValid()
	{
		return _isValid;
	}

	UINT8 PSF1::GetGlyph(UINT8 index)
	{
		if (index < 256)
		{
			return Glyphs._8[index];
		}
		return 0;
	}

	UINT16 PSF1::GetGlyphUnicode(UINT8 index)
	{
		if (index < 256)
		{
			return Glyphs._16[index];
		}
		return 0;
	}
}