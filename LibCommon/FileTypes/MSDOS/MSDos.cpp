#include <FileTypes/MSDos/MSDos.h>

namespace Common::FileTypes::MSDOS
{
	const CHAR DosHeaderSignature[2] = { 'M', 'Z' };

	DOSHeader::DOSHeader()
	{
		Magic.Char[0] = DosHeaderSignature[0];
		Magic.Char[1] = DosHeaderSignature[1];
		BytesOnLastPage = 0;
		PagesInFile = 0;
		Relocations = 0;
		SizeOfHeaderParagraphs = 0;
		MinimumExtraParagraphs = 0;
		MaximumExtraParagraphs = 0;
		InitialSS = 0;
		InitialSP = 0;
		Checksum = 0;
		InitialIP = 0;
		InitialCS = 0;
		RelocationTableOffset = 0;
		OverlayNumber = 0;
		Reserved[0] = 0;
		Reserved[1] = 0;
		Reserved[2] = 0;
		Reserved[3] = 0;
		OEMID = 0;
		OEMInfo = 0;
		Reserved2[0] = 0;
		Reserved2[1] = 0;
		Reserved2[2] = 0;
		Reserved2[3] = 0;
		Reserved2[4] = 0;
		Reserved2[5] = 0;
		Reserved2[6] = 0;
		Reserved2[7] = 0;
		Reserved2[8] = 0;
		Reserved2[9] = 0;
		PEHeaderOffset = 0;
	}

	DOSHeader::DOSHeader(Common::FileSystem::FileHandle* handle)
	{
		handle->SetPosition(0UL);
		handle->Read<UINT16>(&Magic.Value);
		handle->Read<UINT16>(&BytesOnLastPage);
		handle->Read<UINT16>(&PagesInFile);
		handle->Read<UINT16>(&Relocations);
		handle->Read<UINT16>(&SizeOfHeaderParagraphs);
		handle->Read<UINT16>(&MinimumExtraParagraphs);
		handle->Read<UINT16>(&MaximumExtraParagraphs);
		handle->Read<UINT16>(&InitialSS);
		handle->Read<UINT16>(&InitialSP);
		handle->Read<UINT16>(&Checksum);
		handle->Read<UINT16>(&InitialIP);
		handle->Read<UINT16>(&InitialCS);
		handle->Read<UINT16>(&RelocationTableOffset);
		handle->Read<UINT16>(&OverlayNumber);
		handle->Read<UINT16>(&Reserved[0], 4);
		handle->Read<UINT16>(&OEMID);
		handle->Read<UINT16>(&OEMInfo);
		handle->Read<UINT16>(&Reserved2[0],10);
		handle->Read<UINT32>(&PEHeaderOffset);
	}

	const BOOLEAN DOSHeader::VerifySignature(const DOSHeader* header)
	{
		if (header->Magic.Char[0] != DosHeaderSignature[0])
		{
			return FALSE;
		}

		if (header->Magic.Char[1] != DosHeaderSignature[1])
		{
			return FALSE;
		}

		return TRUE;
	}
}
