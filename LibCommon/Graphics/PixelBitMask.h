#pragma once
#include <TypeDefs.h>
#include <Protocols/Graphics/EFI_PIXEL_BITMASK.h>

namespace Common::Graphics
{
	struct PixelBitMask
	{
	public:
		const PixelBitMask();
		const PixelBitMask(UINT32 red, UINT32 green, UINT32 blue, UINT32 alpha);
		PixelBitMask(EFI::EFI_PIXEL_BITMASK& mask);

		UINT32 RedMask;
		UINT32 GreenMask;
		UINT32 BlueMask;
		UINT32 AlphaMask;
	};
}
