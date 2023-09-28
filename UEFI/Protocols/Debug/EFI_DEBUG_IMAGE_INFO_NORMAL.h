#pragma once
#include <UEFIDef.h>
#include <EFI_HANDLE.h>
#include <Protocols/EFI_LOADED_IMAGE_PROTOCOL.h>

namespace EFI
{
	struct EFI_DEBUG_IMAGE_INFO_NORMAL
	{
	public:
		UINT32 ImageInfoType;
		EFI_LOADED_IMAGE_PROTOCOL* LoadedImageProtocolInstance;
		EFI_HANDLE ImageHandle;
	};
}