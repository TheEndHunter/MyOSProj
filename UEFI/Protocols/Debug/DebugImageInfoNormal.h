#pragma once
#include <UEFIDef.h>
#include <Handle.h>
#include <Protocols/LoadedImageProtocol.h>

namespace Efi
{
    struct DebugImageInfoNormal
	{
	public:
		UINT32 ImageInfoType;
        LoadedImageProtocol* LoadedImageProtocolInstance;
        Handle ImageHandle;
	};
}