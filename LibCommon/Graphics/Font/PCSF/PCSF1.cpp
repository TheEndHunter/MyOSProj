#include <Graphics/Font/PCSF/PCSF1.h>

namespace Common::Graphics::Font::PCSF
{
	PCSF1::PCSF1()
	{
		_isValid = FALSE;
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
			_isValid = FALSE;
			return;
		}

		_isValid = TRUE;
		UINT32 charSize = Header.CharSize;

		if((UINT8)Header.Mode & (UINT8)PCSF1Mode::MODE512)
		{
			CharCount = 512;
		}
		else
		{
			CharCount = 256;
		}


		Glyphs = (UINT8**)new UINT8[CharCount * charSize];
		handle->Read<UINT8>(&Glyphs[0][0], CharCount);
		
		if ((UINT8)Header.Mode & (UINT8)PCSF1Mode::MODEHASTAB)
		{
			UnicodeTable = new UnicodeSequence[CharCount];
			if (UnicodeTable == nullptr)
			{
				// Memory allocation failed, handle this case
				_isValid = FALSE;
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
						_isValid = FALSE;
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
				_isValid = FALSE;
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

	BOOLEAN PCSF1Hdr::operator==(const PCSF1Hdr& other)
	{
		if (Magic.Value != other.Magic.Value)
		{
			return FALSE;
		}

		if (Mode != other.Mode)
		{
			return FALSE;
		}

		if (CharSize != other.CharSize)
		{
			return FALSE;
		}

		return TRUE;
	}

	BOOLEAN PCSF1Hdr::operator!=(const PCSF1Hdr& other)
	{
		return !(this->operator==(other));
	}

	BOOLEAN PCSF1::IsValid()
	{
		return _isValid;
	}

	UINT8* PCSF1::GetGlyph(UINT16 index)
	{
		if (index < CharCount)
		{
			return Glyphs[index];
		}
		return nullptr;
	}
	BOOLEAN PCSF1::operator==(const PCSF1& other)
	{
		/*Check all Members of PCSF1*/

		if (Header != other.Header)
		{
			return FALSE;
		}

		if (CharCount != other.CharCount)
		{
			return FALSE;
		}

		if (UnicodeTable == nullptr && other.UnicodeTable != nullptr)
		{
			return FALSE;
		}

		if (UnicodeTable != nullptr && other.UnicodeTable == nullptr)
		{
			return FALSE;
		}

		if (UnicodeTable != nullptr && other.UnicodeTable != nullptr)
		{
			if (UnicodeTable->length != other.UnicodeTable->length)
			{
				return FALSE;
			}

			for (UINT16 i = 0; i < CharCount; i++)
			{
				if (UnicodeTable[i].length != other.UnicodeTable[i].length)
				{
					return FALSE;
				}

				for (UINT8 j = 0; j < UnicodeTable[i].length; j++)
				{
					if (UnicodeTable[i].sequence[j] != other.UnicodeTable[i].sequence[j])
					{
						return FALSE;
					}
				}
			}
		}

		/*Check Glphys to make sure they match*/

		for (UINT64 i = 0; i < CharCount; i++)
		{
			UINT8* glyph1 = Glyphs[i];
			UINT8* glyph2 = other.Glyphs[i];

			for(UINT16 j = 0; j < Header.CharSize; j++)
			{
				if (glyph1[j] != glyph2[j])
				{
					return FALSE;
				}
			}
		}
		return TRUE;
	}

	BOOLEAN PCSF1::operator!=(const PCSF1& other)
	{
		return !(this->operator==(other));
	}
}