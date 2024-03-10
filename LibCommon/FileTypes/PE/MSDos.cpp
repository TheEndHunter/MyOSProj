#include <FileTypes/PE/MSDos.h>

namespace Common::FileTypes::PE
{
	const CCHAR DosHeaderSignature[2] = { 'M', 'Z' };

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
		handle->Read(sizeof(Magic), &Magic);
		handle->Read(sizeof(BytesOnLastPage), &BytesOnLastPage);
		handle->Read(sizeof(PagesInFile), &PagesInFile);
		handle->Read(sizeof(Relocations), &Relocations);
		handle->Read(sizeof(SizeOfHeaderParagraphs), &SizeOfHeaderParagraphs);
		handle->Read(sizeof(MinimumExtraParagraphs), &MinimumExtraParagraphs);
		handle->Read(sizeof(MaximumExtraParagraphs), &MaximumExtraParagraphs);
		handle->Read(sizeof(InitialSS), &InitialSS);
		handle->Read(sizeof(InitialSP), &InitialSP);
		handle->Read(sizeof(Checksum), &Checksum);
		handle->Read(sizeof(InitialIP), &InitialIP);
		handle->Read(sizeof(InitialCS), &InitialCS);
		handle->Read(sizeof(RelocationTableOffset), &RelocationTableOffset);
		handle->Read(sizeof(OverlayNumber), &OverlayNumber);
		handle->Read(sizeof(Reserved), &Reserved);
		handle->Read(sizeof(OEMID), &OEMID);
		handle->Read(sizeof(OEMInfo), &OEMInfo);
		handle->Read(sizeof(Reserved2), &Reserved2);
		handle->Read(sizeof(PEHeaderOffset), &PEHeaderOffset);
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
