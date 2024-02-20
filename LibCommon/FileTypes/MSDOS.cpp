#include <FileTypes/MSDOS.h>
#include <EFI_STATUS.h>

namespace Common::FileTypes
{
    DOS_HDR DOS_HDR::ReadHdr(Common::FileSystem::FileHandle* file)
    {
		DOS_HDR hdr;
		UINT64 size = sizeof(DOS_HDR);

		EFI::EFI_STATUS status = file->Read(&size,&hdr);

		if (status != EFI::EFI_STATUS::SUCCESS)
		{
			return DOS_HDR_EMPTY;
		}
		return hdr;
    }
}
