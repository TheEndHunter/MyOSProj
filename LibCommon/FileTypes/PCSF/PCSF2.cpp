#include <FileTypes/PCSF/PCSF2.h>

namespace Common::FileTypes::PCSF
{
	PCSF2::PCSF2()
	{
		_isValid = false;
		Header = PCSF2Hdr();
	}

	PCSF2::PCSF2(Common::FileSystem::ESP::FileHandle* handle)
	{
		Header = PCSF2Hdr(handle);
		if (Header.Magic.Char[0] != PCSF2_MAGIC[0] || Header.Magic.Char[1] != PCSF2_MAGIC[1]
			|| Header.Magic.Char[2] != PCSF2_MAGIC[2] || Header.Magic.Char[3] != PCSF2_MAGIC[3])
		{
			_isValid = true;
		}
		else
		{
			_isValid = false;
			return;
		}
	}

	PCSF2Hdr::PCSF2Hdr()
	{
		Magic.Char[0] = 0;
		Magic.Char[1] = 0;
		Magic.Char[2] = 0;
		Magic.Char[3] = 0;
		Version = 0;
		HeaderSize = 0;
		Flags = PCSF2Flags::None;
		Length = 0;
		GlyphSize = 0;
		Height = 0;
		Width = 0;
	}

	PCSF2Hdr::PCSF2Hdr(Common::FileSystem::ESP::FileHandle* handle)
	{
		handle->SetPosition(0UL);
		handle->Read<UINT32>(&Magic.Value);
		handle->Read<UINT32>(&Version);
		handle->Read<UINT32>(&HeaderSize);
		handle->Read<PCSF2Flags>(&Flags);
		handle->Read<UINT32>(&Length);
		handle->Read<UINT32>(&GlyphSize);
		handle->Read<UINT32>(&Height);
		handle->Read<UINT32>(&Width);
	}

	BOOLEAN PCSF2::IsValid()
	{
		return _isValid;
	}

	UINT8 PCSF2::GetGlyph(UINT8 index)
	{
		if (index < 256)
		{
			return Glyphs._8[index];
		}
		return 0;
	}

	UINT16 PCSF2::GetGlyphUnicode(UINT8 index)
	{
		if (index < 256)
		{
			return Glyphs._16[index];
		}
		return 0;
	}
}