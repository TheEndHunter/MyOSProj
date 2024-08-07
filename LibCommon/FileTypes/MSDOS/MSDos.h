#pragma once
#include <TypeDefs.h>
#include <FileSystem/FileHandle.h>

namespace Common::FileTypes::MSDOS
{
#pragma pack(push, 1)
	struct DOSHeader
	{
	public:
		DOSHeader();
		DOSHeader(Common::FileSystem::FileHandle* handle);

		union
		{
			CHAR Char[2];
			UINT16 Value;
		} Magic;

		UINT16 BytesOnLastPage;
		UINT16 PagesInFile;
		UINT16 Relocations;
		UINT16 SizeOfHeaderParagraphs;
		UINT16 MinimumExtraParagraphs;
		UINT16 MaximumExtraParagraphs;
		UINT16 InitialSS;
		UINT16 InitialSP;
		UINT16 Checksum;
		UINT16 InitialIP;
		UINT16 InitialCS;
		UINT16 RelocationTableOffset;
		UINT16 OverlayNumber;
		UINT16 Reserved[4];
		UINT16 OEMID;
		UINT16 OEMInfo;
		UINT16 Reserved2[10];
		UINT32 PEHeaderOffset;

		static const BOOLEAN VerifySignature(const DOSHeader* header);

	};
#pragma pack(pop)
}
