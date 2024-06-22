#include <Graphics/Font/PCSF/PCSF1.h>

namespace Common::Graphics::Font::PCSF
{
	PCSF1::PCSF1()
	{
		_isValid = false;
		Header = PCSF1Hdr();
		CharCount = 0;
		Glyphs = nullptr;
		UnicodeTable = nullptr;
	}

	PCSF1::PCSF1(Common::FileSystem::FileHandle* handle)
	{
		Header = PCSF1Hdr(handle);
		if (Header.Magic.Char[0] != PSF1_MAGIC[0] || Header.Magic.Char[1] != PSF1_MAGIC[1])
		{
			_isValid = false;
			return;
		}

		_isValid = true;
		UINT32 length;

		if((UINT8)Header.Mode & (UINT8)PCSF1Mode::MODE512)
		{
			length = 512;
		}
		else
		{
			length = 256;
		}

		CharCount = length;
		length *= Header.CharSize;

		Glyphs = new UINT8[length];
		handle->Read<UINT8>(Glyphs, length);
		
		

		if ((UINT8)Header.Mode & (UINT8)PCSF1Mode::MODEHASTAB)
		{
			UnicodeTable = new UnicodeSequence[CharCount];
			if (UnicodeTable == nullptr)
			{
				// Memory allocation failed, handle this case
				_isValid = false;
				delete[] Glyphs;
				Glyphs = nullptr;
				return;
			}

			UINT16 i;
			for (i = 0; i < CharCount; i++)
			{
				UINT8 seqLength;
				handle->Read<UINT8>(&seqLength);

				if (seqLength == 0xFF)
				{
					// End of sequence for this glyph
					UnicodeTable[i].sequence = nullptr;
					UnicodeTable[i].length = 0;
				}
				else if (seqLength == 0x00)
				{
					// End of table
					break;
				}
				else
				{
					// Allocate memory for the sequence
					UnicodeTable[i].sequence = new UINT8[seqLength];
					if (UnicodeTable[i].sequence == nullptr)
					{
						// Memory allocation failed, handle this case
						_isValid = false;
						for (UINT16 j = 0; j < i; j++)
						{
							delete[] UnicodeTable[j].sequence;
						}
						delete[] UnicodeTable;
						UnicodeTable = nullptr;
						delete[] Glyphs;
						Glyphs = nullptr;
						return;
					}
					UnicodeTable[i].length = seqLength;

					// Read the sequence directly into the UnicodeSequence
					handle->Read<UINT8>(UnicodeTable[i].sequence, seqLength);
				}
			}

			// Check if the Unicode table is shorter than expected
			if (i < CharCount)
			{
				for (UINT16 j = 0; j < i; j++)
				{
					delete[] UnicodeTable[j].sequence;
				}
				delete[] UnicodeTable;
				UnicodeTable = nullptr;
				delete[] Glyphs;
				Glyphs = nullptr;

				// The Unicode table is shorter than expected, handle this case
				_isValid = false;
				return;
			}
		}
		else
		{
			UnicodeTable = nullptr;
		}

	}

	PCSF1Hdr::PCSF1Hdr()
	{
		Magic.Char[0] = 0;
		Magic.Char[1] = 0;
		Mode = PCSF1Mode::None;
		CharSize = 0;
	}

	PCSF1Hdr::PCSF1Hdr(Common::FileSystem::FileHandle* handle)
	{
		handle->SetPosition(0UL);
		handle->Read<UINT16>(&Magic.Value);
		handle->Read<PCSF1Mode>(&Mode);
		handle->Read<UINT8>(&CharSize);
	}

	BOOLEAN PCSF1::IsValid()
	{
		return _isValid;
	}

	UINT8* PCSF1::GetGlyph(UINT16 index)
	{
		if (index < CharCount)
		{
			return &Glyphs[index];
		}
		return nullptr;
	}

	UINT64 PCSF1::GetCharWidth()
	{
		return Header.CharSize;
	}

	UINT64 PCSF1::GetCharHeight()
	{
		return Header.CharSize;
	}

	BOOLEAN PCSF1::SupportsUnicode()
	{
		return (UINT8)Header.Mode & (UINT8)PCSF1Mode::MODEHASTAB;
	}

	VOID_PTR PCSF1::GetGlyph(UINT64 codePoint)
	{
		if (UnicodeTable == nullptr)
		{
			return nullptr;
		}

		for (UINT32 i = 0; i < CharCount; i++)
		{
			if (UnicodeTable[i].sequence != nullptr)
			{
				if (UnicodeTable[i].length == 1)
				{
					if (UnicodeTable[i].sequence[0] == codePoint)
					{
						return (VOID_PTR)&Glyphs[i];
					}
				}
				else
				{
					if (UnicodeTable[i].sequence[0] == PSF1_STARTSEQ)
					{
						if (UnicodeTable[i].sequence[1] == codePoint)
						{
							return (VOID_PTR)&Glyphs[i];
						}
					}
				}
			}
		}

		return nullptr;
	}

	PCSF1::~PCSF1()
	{
		delete[] Glyphs;
		Glyphs = nullptr;

		if (UnicodeTable != nullptr)
		{
			for (UINT32 i = 0; i < CharCount; i++)
			{
				delete[] UnicodeTable[i].sequence;
			}
			delete[] UnicodeTable;
			UnicodeTable = nullptr;
		}
	}
}