#pragma once

#include "TypeDefs.h"

namespace Common::FileSystem
{
	enum FileMode : UINT64
	{
		Read = 0x0000000000000001,
		Write = 0x0000000000000002,
		Create = 0x8000000000000000,
		ReadWrite = Read | Write,
	};
}
