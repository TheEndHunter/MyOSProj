#include <FileTypes/PE32.h>
#include <System/Allocator.h>

namespace Common::FileTypes
{
	const static CHAR8 DosHeaderSignature[] = { 'M', 'Z' };
	const static CHAR8 PE32Signature[] = { 'P', 'E', 0, 0 };

	PE32File::PE32File(Common::FileSystem::FileHandle* handle)
	{
		lastHeaderPosition = 0;
		DosHeader = PE32File::ReadDOSHeader(handle, lastHeaderPosition);
		if(DosHeader == nullptr)
			return;

		lastHeaderPosition += DosHeader->PEHeaderOffset;

		PEHeader = PE32File::ReadPE32Header(handle, lastHeaderPosition);
		lastHeaderPosition += sizeof(PE32Header);
		if (PEHeader == nullptr)
		{
			if (DosHeader != nullptr)
				delete DosHeader;
			return;
		}
		PEOptionHeader = PE32File::ReadPE32OptionHeader(handle, lastHeaderPosition);
		lastHeaderPosition += sizeof(PE32OptionHeader);
		if (PEOptionHeader->Magic.Value == 0x10b)
		{
			Footer.PE32 = PE32File::ReadPE32OptionFooter(handle, lastHeaderPosition);
			lastHeaderPosition += sizeof(PE32OptionFooter);
		}
		else if (PEOptionHeader->Magic.Value == 0x20b)
		{
			Footer.PE32P = PE32File::ReadPE32POptionFooter(handle, lastHeaderPosition);
			lastHeaderPosition += sizeof(PE32POptionFooter);
		}
		else
		{
			Footer._Ptr = nullptr;
		}
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
	const BOOLEAN PE32Header::VerifySignature(const PE32Header* header)
	{
		if (header->Signature.Char[0] != PE32Signature[0])
		{
			return FALSE;
		}
		if (header->Signature.Char[1] != PE32Signature[1])
		{
			return FALSE;
		}
		if (header->Signature.Char[2] != PE32Signature[2])
		{
			return FALSE;
		}
		if (header->Signature.Char[3] != PE32Signature[3])
		{
			return FALSE;
		}
		return TRUE;
	}

	DOSHeader* PE32File::ReadDOSHeader(Common::FileSystem::FileHandle* handle, UINTN offset)
	{
		DOSHeader* header = new DOSHeader();
		UINTN DosHeaderSize = sizeof(DOSHeader);
		handle->SetPosition(offset);
		handle->Read((UINTN*)&DosHeaderSize, header);

		if (!DOSHeader::VerifySignature(header))
		{
			delete(sizeof(DOSHeader), header);

			return nullptr;
		}
		return header;
	}

	PE32Header* PE32File::ReadPE32Header(Common::FileSystem::FileHandle* handle, UINTN offset)
	{
		PE32Header* header = new PE32Header();
		UINTN PEHeaderSize = sizeof(PE32Header);
		handle->SetPosition(offset);
		handle->Read((UINTN*)&PEHeaderSize, header);

		if (!PE32Header::VerifySignature(header))
		{
			delete(sizeof(PE32Header), header);
			return nullptr;
		}
		return header;
	}

	PE32OptionHeader* PE32File::ReadPE32OptionHeader(Common::FileSystem::FileHandle* handle, UINTN offset)
	{
		PE32OptionHeader* header = new PE32OptionHeader();
		UINTN PEOptionHeaderSize = sizeof(PE32OptionHeader);
		handle->SetPosition(offset);
		handle->Read((UINTN*)&PEOptionHeaderSize, header);
		return header;
	}

	PE32OptionFooter* PE32File::ReadPE32OptionFooter(Common::FileSystem::FileHandle* handle, UINTN offset)
	{
		PE32OptionFooter* footer = new PE32OptionFooter();
		UINTN PEOptionFooterSize = sizeof(PE32OptionFooter);
		handle->SetPosition(offset);
		handle->Read((UINTN*)&PEOptionFooterSize, footer);
		return footer;
	}

	PE32POptionFooter* PE32File::ReadPE32POptionFooter(Common::FileSystem::FileHandle* handle, UINTN offset)
	{
		PE32POptionFooter* footer = new PE32POptionFooter();
		UINTN PEPOptionFooterSize = sizeof(PE32POptionFooter);
		handle->SetPosition(offset);
		handle->Read((UINTN*)&PEPOptionFooterSize, footer);
		return footer;
	}

	PE32SectionHeader* PE32File::ReadPE32SectionHeader(Common::FileSystem::FileHandle* handle, UINTN offset)
	{
		PE32SectionHeader* header = new PE32SectionHeader();
		UINTN PESectionHeaderSize = sizeof(PE32SectionHeader);
		handle->SetPosition(offset);
		handle->Read((UINTN*)&PESectionHeaderSize, header);
		return header;
	}

	PE32File* PE32File::Read(Common::FileSystem::FileHandle* handle)
	{
		PE32File* file = new PE32File(handle);
		return file;
	}
}
