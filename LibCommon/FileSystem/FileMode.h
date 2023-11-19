#pragma once

#include "TypeDefs.h"

namespace Common::FileSystem
{
	enum FileMode : UINT8
	{
		Create = 1,
		Read = 2,
		Write = 4,
	};
}
