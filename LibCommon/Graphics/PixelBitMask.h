#pragma once
#include <TypeDefs.h>
#include <Protocols/Graphics/PixelBitmask.h>

namespace Common::Graphics
{
	struct PixelBitMask
	{
	public:
		PixelBitMask();
		PixelBitMask(const UINT32 red, const  UINT32 green, const  UINT32 blue, const  UINT32 alpha);
		PixelBitMask(Efi::PixelBitmask& mask);

		UINT32 RedMask;
		UINT32 GreenMask;
		UINT32 BlueMask;
		UINT32 AlphaMask;
	};
}
