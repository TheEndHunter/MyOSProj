#include "PE32.h"

namespace Common::FileTypes::PE
{
	PE32::PE32(FileSystem::ESP::FileHandle* handle)
	{
		_dosHdrValid = FALSE;
		_peHdrValid = FALSE;
		_optHdrValid = FALSE;
		_sectionHdrValid = FALSE;
		_dataBufferValid = FALSE;

		// Read DOSHeader
		DOSHdr = DOSHeader(handle);

		if(DOSHdr.Magic.Value != 0x5A4D)
		{
			return;
		}

		_dosHdrValid = TRUE;

		handle->SetPosition(DOSHdr.PEHeaderOffset);
		// Read NTHeaders
		PE32hdr = PE32Header(handle);

		if (PE32hdr.Signature.Char[0] != 'P')
		{
			return;
		}
		if (PE32hdr.Signature.Char[1] != 'E')
		{
			return;
		}
		if (PE32hdr.Signature.Char[2] != '\0')
		{
			return;
		}
		if (PE32hdr.Signature.Char[3] != '\0')
		{
			return;
		}
		_peHdrValid = TRUE;

		OptHdrCommon = PE32OptionHeader(handle);
		
		if(OptHdrCommon.Magic.Value == 0x010b)
		{
			OptHdr.PE32 = new PE32OptionHeader32(handle);

			if(OptHdr.PE32 == nullptr)
			{
				return;
			}
			SizeOfDataBuffer = OptHdr.PE32->SizeOfImage;
		}
		else if(OptHdrCommon.Magic.Value == 0x020b)
		{
			OptHdr.PE32PLUS = new PE32OptionHeader64(handle);

			if(OptHdr.PE32PLUS == nullptr)
			{
				return;
			}

			SizeOfDataBuffer = OptHdr.PE32PLUS->SizeOfImage;
		}
		else
		{
			return;
		}

		_optHdrValid = TRUE;

		SectionHeaders = System::Allocator::AllocateArray<PE32SectionHeader>(PE32hdr.NumberOfSections);
		
		if (SectionHeaders == nullptr)
		{
			return;
		}

		for (UINTN i = 0; i < PE32hdr.NumberOfSections; i++)
		{
			SectionHeaders[i] = PE32SectionHeader(handle);
		}

		_sectionHdrValid = TRUE;


		DataBuffer = new UINT8[SizeOfDataBuffer];
				
		if(DataBuffer == nullptr)
		{
			delete SectionHeaders;
			return;
		}


		handle->SetPosition(SectionHeaders[0].PointerToRawData);
		for (UINT16 i = 0; i < PE32hdr.NumberOfSections; i++)
		{
			handle->Read(SectionHeaders[i].SizeOfRawData, &DataBuffer[SectionHeaders[i].VirtualAddress]);
		}

		_dataBufferValid = TRUE;

		_EntryPointOffset = OptHdrCommon.AddressOfEntryPoint;
		_EntryPoint = &DataBuffer[OptHdrCommon.AddressOfEntryPoint];
	}

	BOOLEAN PE32::IsDosHdrValid() const
	{
		return _dosHdrValid;
	}
	BOOLEAN PE32::IsPEHdrValid() const
	{
		return _peHdrValid;
	}

	BOOLEAN PE32::IsOptHdrValid() const
	{
		return _optHdrValid;
	}

	BOOLEAN PE32::IsSectionHdrValid() const
	{
		return _sectionHdrValid;
	}

	BOOLEAN PE32::IsDataBufferValid() const
	{
		return _dataBufferValid;
	}

	const UINTN PE32::GetEntryPointOffset() const
	{
		return _EntryPointOffset;
	}

	const VOID_PTR PE32::GetEntryPoint() const
	{
		return _EntryPoint;
	}
}
