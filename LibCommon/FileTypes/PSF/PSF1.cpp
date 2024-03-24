#include <FileTypes/PSF/PSF1.h>

namespace Common::FileTypes::PSF
{
    PSF1::PSF1()
    {
        _isValid = false;
        Header = PSF1Hdr();
        Chars._1 = 0;
    }
    PSF1::PSF1(Common::FileSystem::ESP::FileHandle* handle)
    {
        Header = PSF1Hdr(handle);
        if (Header.Magic.Char[0] != PSF1_MAGIC[0] || Header.Magic.Char[1] != PSF1_MAGIC[1])
		{
			_isValid = true;
            if(Header.CharSize <= 8)
            {
				Chars._1 = new UINT8[256];
				handle->Read<UINT8>(Chars._1, 256);
			}
            else if (Header.CharSize <= 16)
            {
                Chars._2 = new UINT16[256];
                handle->Read<UINT16>(Chars._2, 256);
            }
            else if (Header.CharSize <= 32)
			{
				Chars._3 = new UINT32[256];
				handle->Read<UINT32>(Chars._3, 256);
			}
			else if (Header.CharSize <= 64)
			{
				Chars._4 = new UINT64[256];
				handle->Read<UINT64>(Chars._4, 256);
			}
			else
			{
				_isValid = false;
            }
		}
		else
		{
			_isValid = false;
		}
    }

    PSF1Hdr::PSF1Hdr()
    {
        Magic.Char[0] = 0;
        Magic.Char[1] = 0;
        Mode = PSF1_Mode::MAXMODE;
        CharSize = 0;
    }

    PSF1Hdr::PSF1Hdr(Common::FileSystem::ESP::FileHandle* handle)
    {
        handle->SetPosition(0UL);
        handle->Read<UINT16>(&Magic.Value);
        handle->Read<PSF1_Mode>(&Mode);
        handle->Read<UINT8>(&CharSize);
    }

    BOOLEAN PSF1::IsValid()
    {
        return _isValid;
    }
}