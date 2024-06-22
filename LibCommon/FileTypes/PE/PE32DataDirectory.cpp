#include "PE32DataDirectory.h"

namespace Common::FileTypes::PE
{
	PE32DataDirectory::PE32DataDirectory()
	{
		VirtualAddress = 0;
		Size = 0;
	}
	PE32DataDirectory::PE32DataDirectory(Common::FileSystem::FileHandle* hndl)
	{
		hndl->Read<UINT32>(&VirtualAddress);
		hndl->Read<UINT32>(&Size);
	}
}
