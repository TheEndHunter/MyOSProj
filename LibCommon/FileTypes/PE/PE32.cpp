#include "PE32.h"

namespace Common::FileTypes::PE
{
	PE32::PE32(FileSystem::FileHandle* handle)
	{
		// Read DOSHeader
		DOSHdr = DOSHeader(handle);

		if(DOSHdr.Magic.Value != 0x5A4D)
		{
			_isValid = FALSE;
			return;
		}

		handle->SetPosition(DOSHdr.PEHeaderOffset);
		// Read NTHeaders
		PE32hdr = PE32Header(handle);

		if (PE32hdr.Signature.Char[0] != 'P')
		{
			_isValid = FALSE;
			return;
		}
		if (PE32hdr.Signature.Char[1] != 'E')
		{
			_isValid = FALSE;
			return;
		}
		if (PE32hdr.Signature.Char[2] != '\0')
		{
			_isValid = FALSE;
			return;
		}
		if (PE32hdr.Signature.Char[3] != '\0')
		{
			_isValid = FALSE;
			return;
		}
		OptHdrCommon = PE32OptionHeader(handle);

		if(OptHdrCommon.Magic.Value == 0x10B)
		{
			OptHdr.X86 = new PE32OptionHeader32(handle);
		}
		else if(OptHdrCommon.Magic.Value == 0x20B)
		{
			OptHdr.X64 = new PE32OptionHeader64(handle);
		}
		else
		{
			_isValid = FALSE;
			return;
		}

		_isValid = TRUE;
	}
	BOOLEAN PE32::IsValid() const
	{
		return _isValid;
	}
}
