#include "PE32DataDirectory.h"

namespace Common::FileTypes::PE
{
	PE32DataDirectory::PE32DataDirectory(Common::FileSystem::ESP::FileHandle* hndl)
	{
		hndl->Read(sizeof(UINT32), &VirtualAddress);
		hndl->Read(sizeof(UINT32), &Size);
	}
}
