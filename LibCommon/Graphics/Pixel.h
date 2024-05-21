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
		Pixel4Bpp();

		Pixel4Bpp(Colour& c);

		Pixel4Bpp(Pixel3Bpp& p);

		Pixel4Bpp(Pixel2Bpp& p);

		Pixel4Bpp(Pixel1Bpp& p);

		Pixel4Bpp(const UINT32 b1, const UINT32 b2, const UINT32 b3, const UINT32 b4);

		UINT32 B1;
		UINT32 B2;
		UINT32 B3;
		UINT32 B4;
	};

	struct Pixel3Bpp
	{
	public:
		Pixel3Bpp();

		Pixel3Bpp(Colour& c);

		Pixel3Bpp(Pixel4Bpp& p);

		Pixel3Bpp(Pixel2Bpp& p);

		Pixel3Bpp(Pixel1Bpp& p);

		Pixel3Bpp(const UINT32 b1, const UINT32 b2, const UINT32 b3, const UINT32 b4);

		UINT8 B1[3];
		UINT8 B2[3];
		UINT8 B3[3];
		UINT8 B4[3];
	};

	struct Pixel2Bpp
	{
	public:
		Pixel2Bpp();

		Pixel2Bpp(Pixel4Bpp& p);

		Pixel2Bpp(Pixel3Bpp& p);

		Pixel2Bpp(Pixel1Bpp& p);

		Pixel2Bpp(const UINT16 b1, const UINT16 b2, const UINT16 b3, const UINT16 b4);

		UINT16 B1;
		UINT16 B2;
		UINT16 B3;
		UINT16 B4;
	};

	struct Pixel1Bpp
	{
	public:
		Pixel1Bpp();

		Pixel1Bpp(Pixel4Bpp& p);

		Pixel1Bpp(Pixel3Bpp& p);

		Pixel1Bpp(Pixel2Bpp& p);

		Pixel1Bpp(const UINT8 b1, const UINT8 b2, const UINT8 b3, const UINT8 b4);

		UINT8 B1;
		UINT8 B2;
		UINT8 B3;
		UINT8 B4;
	};

}
