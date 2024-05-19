#pragma once

#include <TypeDefs.h>
#include <Graphics/Colour.h>

namespace Common::Graphics
{
	struct Pixel3Bpp;
	struct Pixel2Bpp;
	struct Pixel1Bpp;

	struct Pixel4Bpp
	{
	public:
		const Pixel4Bpp();

		const Pixel4Bpp(Colour& c);

		const Pixel4Bpp(Pixel3Bpp& p);

		const Pixel4Bpp(Pixel2Bpp& p);

		const Pixel4Bpp(Pixel1Bpp& p);

		const Pixel4Bpp(const UINT32 b1, const UINT32 b2, const UINT32 b3, const UINT32 b4);

		UINT32 B1;
		UINT32 B2;
		UINT32 B3;
		UINT32 B4;
	};

	struct Pixel3Bpp
	{
	public:
		const Pixel3Bpp();

		const Pixel3Bpp(Colour& c);

		const Pixel3Bpp(Pixel4Bpp& p);

		const Pixel3Bpp(Pixel2Bpp& p);

		const Pixel3Bpp(Pixel1Bpp& p);

		const Pixel3Bpp(const UINT32 b1, const UINT32 b2, const UINT32 b3, const UINT32 b4);

		UINT8 B1[3];
		UINT8 B2[3];
		UINT8 B3[3];
		UINT8 B4[3];
	};

	struct Pixel2Bpp
	{
	public:
		const Pixel2Bpp();

		const Pixel2Bpp(Pixel4Bpp& p);

		const Pixel2Bpp(Pixel3Bpp& p);

		const Pixel2Bpp(Pixel1Bpp& p);

		const Pixel2Bpp(const UINT16 b1, const UINT16 b2, const UINT16 b3, const UINT16 b4);

		UINT16 B1;
		UINT16 B2;
		UINT16 B3;
		UINT16 B4;
	};

	struct Pixel1Bpp
	{
	public:
		const Pixel1Bpp();

		const Pixel1Bpp(Pixel4Bpp& p);

		const Pixel1Bpp(Pixel3Bpp& p);

		const Pixel1Bpp(Pixel2Bpp& p);

		const Pixel1Bpp(const UINT8 b1, const UINT8 b2, const UINT8 b3, const UINT8 b4);

		UINT8 B1;
		UINT8 B2;
		UINT8 B3;
		UINT8 B4;
	};

}
