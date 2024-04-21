#include <Graphics/Pixel.h>

namespace Common::Graphics
{
	Pixel1Bpp::Pixel1Bpp()
	{
		B1 = 0;
		B2 = 0;
		B3 = 0;
		B4 = 0;
	}
	Pixel1Bpp::Pixel1Bpp(Pixel4Bpp& p)
	{
		B1 = (UINT8)p.B1;
		B2 = (UINT8)p.B2;
		B3 = (UINT8)p.B3;
		B4 = (UINT8)p.B4;
	}
	Pixel1Bpp::Pixel1Bpp(Pixel3Bpp& p)
	{
		B1 = p.B1[2];
		B2 = p.B2[2];
		B3 = p.B3[2];
		B4 = p.B4[2];
	}
	Pixel1Bpp::Pixel1Bpp(Pixel2Bpp& p)
	{
		B1 = (UINT8)p.B1;
		B2 = (UINT8)p.B2;
		B3 = (UINT8)p.B3;
		B4 = (UINT8)p.B4;
	}
	Pixel1Bpp::Pixel1Bpp(UINT8 b1, UINT8 b2, UINT8 b3, UINT8 b4)
	{
		B1 = b1;
		B2 = b2;
		B3 = b3;
		B4 = b4;
	}
	Pixel2Bpp::Pixel2Bpp()
	{
		B1 = 0;
		B2 = 0;
		B3 = 0;
		B4 = 0;
	}
	Pixel2Bpp::Pixel2Bpp(Pixel4Bpp& p)
	{
		B1 = (UINT16)p.B1;
		B2 = (UINT16)p.B2;
		B3 = (UINT16)p.B3;
		B4 = (UINT16)p.B4;
	}
	Pixel2Bpp::Pixel2Bpp(Pixel3Bpp& p)
	{
		B1 = (UINT16)((p.B1[0] << 8) | p.B1[1]);
		B2 = (UINT16)((p.B2[0] << 8) | p.B2[1]);
		B3 = (UINT16)((p.B3[0] << 8) | p.B3[1]);
		B4 = (UINT16)((p.B4[0] << 8) | p.B4[1]);
	}
	Pixel2Bpp::Pixel2Bpp(Pixel1Bpp& p)
	{
		B1 = p.B1;
		B2 = p.B2;
		B3 = p.B3;
		B4 = p.B4;
	}
	Pixel2Bpp::Pixel2Bpp(UINT16 b1, UINT16 b2, UINT16 b3, UINT16 b4)
	{
		B1 = b1;
		B2 = b2;
		B3 = b3;
		B4 = b4;
	}
	Pixel3Bpp::Pixel3Bpp()
	{
		B1[0] = 0;
		B1[1] = 0;
		B1[2] = 0;
		B2[0] = 0;
		B2[1] = 0;
		B2[2] = 0;
		B3[0] = 0;
		B3[1] = 0;
		B3[2] = 0;
		B4[0] = 0;
		B4[1] = 0;
		B4[2] = 0;
	}
	Pixel3Bpp::Pixel3Bpp(Colour& c)
	{
		B1[0] = 0;
		B1[1] = 0;
		B1[2] = c.Red;
		B2[0] = 0;
		B2[1] = 0;
		B2[2] = c.Green;
		B3[0] = 0;
		B3[1] = 0;
		B3[2] = c.Blue;
		B4[0] = 0;
		B4[1] = 0;
		B4[2] = c.Alpha;
	}
	Pixel3Bpp::Pixel3Bpp(Pixel4Bpp& p)
	{
		B1[0] = (UINT8)((p.B1 & 0x0F00) >> 16);
		B1[1] = (UINT8)((p.B1 & 0x00F0) >> 8);
		B1[2] = (UINT8)(p.B1 & 0x000F);
		B2[0] = (UINT8)((p.B2 & 0x0F00) >> 16);
		B2[1] = (UINT8)((p.B2 & 0x00F0) >> 8);
		B2[2] = (UINT8)(p.B2 & 0x000F);
		B3[0] = (UINT8)((p.B3 & 0x0F00) >> 16);
		B3[1] = (UINT8)((p.B3 & 0x00F0) >> 8);
		B3[2] = (UINT8)(p.B3 & 0x000F);
		B4[0] = (UINT8)((p.B4 & 0x0F00) >> 16);
		B4[1] = (UINT8)((p.B4 & 0x00F0) >> 8);
		B4[2] = (UINT8)(p.B4 & 0x000F);
	}
	Pixel3Bpp::Pixel3Bpp(Pixel2Bpp& p)
	{
		B1[0] = 0;
		B1[1] = ((p.B1 & (0xFF00)) >> 8);
		B1[2] = (p.B1 & 0x00FF);
		B2[0] = 0;
		B2[1] = ((p.B2 & (0xFF00)) >> 8);
		B2[2] = (p.B2 & 0x00FF);
		B3[0] = 0;
		B3[1] = ((p.B3 & (0xFF00)) >> 8);
		B3[2] = (p.B3 & 0x00FF);
		B4[0] = 0;
		B4[1] = ((p.B4 & (0xFF00)) >> 8);
		B4[2] = (p.B4 & 0x00FF);
	}
	Pixel3Bpp::Pixel3Bpp(Pixel1Bpp& p)
	{
		B1[0] = 0;
		B1[1] = 0;
		B1[2] = p.B1;
		B2[0] = 0;
		B2[1] = 0;
		B2[2] = p.B2;
		B3[0] = 0;
		B3[1] = 0;
		B3[2] = p.B3;
		B4[0] = 0;
		B4[1] = 0;
		B4[2] = p.B4;
	}
	Pixel3Bpp::Pixel3Bpp(UINT32 b1, UINT32 b2, UINT32 b3, UINT32 b4)
	{
		B1[0] = (UINT8)((b1 & 0x0F00) >> 16);
		B1[1] = (UINT8)((b1 & 0x00F0) >> 8);
		B1[2] = (UINT8)(b1 & 0x000F);
		B2[0] = (UINT8)((b2 & 0x0F00) >> 16);
		B2[1] = (UINT8)((b2 & 0x00F0) >> 8);
		B2[2] = (UINT8)(b2 & 0x000F);
		B3[0] = (UINT8)((b3 & 0x0F00) >> 16);
		B3[1] = (UINT8)((b3 & 0x00F0) >> 8);
		B3[2] = (UINT8)(b3 & 0x000F);
		B4[0] = (UINT8)((b4 & 0x0F00) >> 16);
		B4[1] = (UINT8)((b4 & 0x00F0) >> 8);
		B4[2] = (UINT8)(b4 & 0x000F);
	}
	Pixel4Bpp::Pixel4Bpp()
	{
		B1 = 0;
		B2 = 0;
		B3 = 0;
		B4 = 0;
	}
	Pixel4Bpp::Pixel4Bpp(Colour& c)
	{
		B1 = c.Red;
		B2 = c.Green;
		B3 = c.Blue;
		B4 = c.Alpha;
	}
	Pixel4Bpp::Pixel4Bpp(Pixel3Bpp& p)
	{
		B1 = (UINT32)((UINT32)p.B1[0] << 16) | ((UINT32)p.B1[1] << 8) | (UINT32)p.B1[2];
		B2 = (UINT32)((UINT32)p.B2[0] << 16) | ((UINT32)p.B2[1] << 8) | (UINT32)p.B2[2];
		B3 = (UINT32)((UINT32)p.B3[0] << 16) | ((UINT32)p.B3[1] << 8) | (UINT32)p.B3[2];
		B4 = (UINT32)((UINT32)p.B4[0] << 16) | ((UINT32)p.B4[1] << 8) | (UINT32)p.B4[2];
	}
	Pixel4Bpp::Pixel4Bpp(Pixel2Bpp& p)
	{
		B1 = p.B1;
		B2 = p.B2;
		B3 = p.B3;
		B4 = p.B4;
	}
	Pixel4Bpp::Pixel4Bpp(Pixel1Bpp& p)
	{
		B1 = p.B1;
		B2 = p.B2;
		B3 = p.B3;
		B4 = p.B4;
	}
	Pixel4Bpp::Pixel4Bpp(UINT32 b1, UINT32 b2, UINT32 b3, UINT32 b4)
	{
		B1 = b1;
		B2 = b2;
		B3 = b3;
		B4 = b4;
	}
}