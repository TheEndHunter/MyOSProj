#pragma once
#include <UEFIDef.h>
#include <Protocols/Debug/DebugImageInfoNormal.h>

namespace Efi
{
    union DebugImageInfo
	{
		UINT32* ImageInfoType;
        DebugImageInfoNormal* NormalImage;
	};
}
