#pragma once
#include <UEFIDef.h>
#include <Protocols/Graphics/EFI_GRAPHICS_OUTPUT_BLT_PIXEL.h>


namespace Common::Graphics
{
	/*
	*  struct for containing a 4 8-bit color values.
	*  with functions for converting to 32-bit color values.
	* 
	*  This struct also supports the following operators:
	*  + - * / += -= *= /= == != < > <= >=
	*/

	struct Colour
	{
	public:
		const UINT8 Blue;
		const UINT8 Green;
		const UINT8 Red;
		const UINT8 Alpha;

		const UINT32 AsRGBA() const
		{
			return (UINT32)((Alpha << 24) | (Red << 16) | (Green << 8) | Blue);
		}
		
		const UINT32 AsBGRA() const
		{
			return (UINT32)((Blue << 24) | (Green << 16) | (Red << 8) | Alpha);
		}
		
		const UINT32 AsARGB() const
		{
			return (UINT32)((Alpha << 24) | (Blue << 16) | (Green << 8) | Red);
		}
		
		const UINT32 AsABGR() const
		{
			return (UINT32)((Alpha << 24) | (Green << 16) | (Blue << 8) | Red);
		}

		const EFI::EFI_GRAPHICS_OUTPUT_BLT_PIXEL AsEFI() const
		{
			return EFI::EFI_GRAPHICS_OUTPUT_BLT_PIXEL{ Blue, Green, Red, Alpha};
		}

		Colour operator+(const Colour& other) const
		{
			return Colour(Blue + other.Blue, Green + other.Green, Red + other.Red, Alpha + other.Alpha);
		}

		Colour operator-(const Colour& other) const
		{
			return Colour(Blue - other.Blue, Green - other.Green, Red - other.Red, Alpha - other.Alpha);
		}

		Colour operator*(const Colour& other) const
		{
			return Colour(Blue * other.Blue, Green * other.Green, Red * other.Red, Alpha * other.Alpha);
		}

		Colour operator/(const Colour& other) const
		{
			return Colour(Blue / other.Blue, Green / other.Green, Red / other.Red, Alpha / other.Alpha);
		}

		Colour operator =(const Colour& other) const
		{
			return Colour(other);
		}

		bool operator==(const Colour& other) const
		{
			return Blue == other.Blue && Green == other.Green && Red == other.Red && Alpha == other.Alpha;
		}

		bool operator!=(const Colour& other) const
		{
			return Blue != other.Blue || Green != other.Green || Red != other.Red || Alpha != other.Alpha;
		}

		bool operator<(const Colour& other) const
		{
			return Blue < other.Blue && Green < other.Green && Red < other.Red && Alpha < other.Alpha;
		}

		bool operator>(const Colour& other) const
		{
			return Blue > other.Blue && Green > other.Green && Red > other.Red && Alpha > other.Alpha;
		}

		bool operator<=(const Colour& other) const
		{
			return Blue <= other.Blue && Green <= other.Green && Red <= other.Red && Alpha <= other.Alpha;
		}

		bool operator>=(const Colour& other) const
		{
			return Blue >= other.Blue && Green >= other.Green && Red >= other.Red && Alpha >= other.Alpha;
		}

		constexpr Colour() : Blue(0), Green(0), Red(0), Alpha(255) {};
		constexpr Colour(const UINT32 rgba) : Blue((UINT8)((rgba & 0x0000FF00) >> 8)), Green((UINT8)((rgba & 0x00FF0000) >> 16)), Red((UINT8)((rgba & 0xFF000000) >> 24)), Alpha((UINT8)(rgba & 0x000000FF)) {}
		constexpr Colour(const UINT8 red, const UINT8 green, const UINT8 blue,const UINT8 alpha) : Blue(blue), Green(green), Red(red), Alpha(alpha) {}
		constexpr Colour(const UINT8 red, const UINT8 green, const UINT8 blue) : Blue(blue), Green(green), Red(red), Alpha(255) {}
		constexpr Colour(const Colour& color) : Blue(color.Blue), Green(color.Green), Red(color.Red), Alpha(color.Alpha) {}
		constexpr Colour(const Colour* color) : Blue(color->Blue), Green(color->Green), Red(color->Red), Alpha(color->Alpha) {}

		constexpr Colour(const EFI::EFI_GRAPHICS_OUTPUT_BLT_PIXEL& color) : Blue(color.Blue), Green(color.Green), Red(color.Red), Alpha(color.Alpha) {}
		constexpr Colour(const EFI::EFI_GRAPHICS_OUTPUT_BLT_PIXEL* color) : Blue(color->Blue), Green(color->Green), Red(color->Red), Alpha(color->Alpha) {}

		static const Colour FromRGBA(const UINT32 rgba) 
		{
			return Colour(rgba);
		}

		static const Colour FromBGRA(const UINT32 bgra) 
		{
			return Colour((UINT8)((bgra & 0x0000FF00) >> 8), (UINT8)((bgra & 0x00FF0000) >> 16), (UINT8)((bgra & 0xFF000000) >> 24), (UINT8)((bgra & 0x000000FF)));
		}

		static const Colour FromARGB(const UINT32 argb) 
		{
			return Colour((UINT8)((argb & 0x00FF0000) >> 16), (UINT8)((argb & 0x0000FF00) >> 8), (UINT8)(argb & 0x000000FF), (UINT8)((argb & 0xFF000000) >> 24));
		} 

		static const Colour FromABGR(const UINT32 abgr) 
		{
			return Colour((UINT8)((abgr & 0x000000FF)), (UINT8)((abgr & 0x0000FF00) >> 8), (UINT8)((abgr & 0x00FF0000) >> 16), (UINT8)((abgr & 0xFF000000) >> 24));
		}

		static const Colour FromRGBA(const UINT8 r, const UINT8 g, const UINT8 b, const UINT8 a = 255)  
		{
			return Colour(r,g,b,a);
		}

		static const Colour FromBGRA(const UINT8 b, const UINT8 g, const UINT8 r, const UINT8 a = 255) 
		{
			return Colour(r,g,b,a);
		}

		static const Colour FromARGB(const UINT8 a, const UINT8 r, const UINT8 g, const UINT8 b) 
		{
			return Colour(r,g,b,a);
		} 

		static const Colour FromABGR(const UINT8 a, const UINT8 b, const UINT8 g, const UINT8 r) 
		{
			return Colour(r,g,b,a);
		}

		static const Colour FromRGB(const UINT8 r, const UINT8 g, const UINT8 b)
		{
			return Colour(r,g,b);
		}
		static const Colour FromBGR(const UINT8 b, const UINT8 g, const UINT8 r)
		{
			return Colour(r, g, b);
		}

		static const Colour FromEFI(const EFI::EFI_GRAPHICS_OUTPUT_BLT_PIXEL color)
		{
			return Colour(color);
		}

		static const EFI::EFI_GRAPHICS_OUTPUT_BLT_PIXEL ToEFI(const Colour color)
		{
			return EFI::EFI_GRAPHICS_OUTPUT_BLT_PIXEL{ color.Blue, color.Green, color.Red, color.Alpha };
		}
		static const EFI::EFI_GRAPHICS_OUTPUT_BLT_PIXEL ToEFI(const Colour* color)
		{
			return EFI::EFI_GRAPHICS_OUTPUT_BLT_PIXEL{ color->Blue, color->Green, color->Red, color->Alpha };
		}
	};
	
	/// <summary>
	///  Selection of colours for use in the bootloader for the GraphicsContext.
	///  base on colors from https://en.wikipedia.org/wiki/Web_colors
	/// </summary>
	namespace Colours
	{
		/* Pink colors */
		constinit const Colour DeepPink = Colour(255, 20, 147);
		constinit const Colour HotPink = Colour(255, 105, 180);
		constinit const Colour LightPink = Colour(255, 182, 193);
		constinit const Colour MediumVioletRed = Colour((UINT8)199, (UINT8)21, (UINT8)133);
		constinit const Colour PaleVioletRed	=Colour(219, 112, 147);
		constinit const Colour Pink = Colour(255, 192, 203);
		/* Red colors */
		constinit const Colour Crimson = Colour(220, 20, 60);
		constinit const Colour DarkRed = Colour(139, 0, 0);
		constinit const Colour DarkSalmon = Colour(233, 150, 122);
		constinit const Colour Firebrick = Colour(178, 34, 34);
		constinit const Colour IndianRed = Colour(205, 92, 92);
		constinit const Colour LightCoral = Colour(240, 128, 128);
		constinit const Colour LightSalmon = Colour(255, 160, 122);
		constinit const Colour Red = Colour(255, 0, 0);
		constinit const Colour Salmon = Colour(250, 128, 114);
		 /* Orange colors */
		constinit const Colour Coral = Colour(255, 127, 80);
		constinit const Colour DarkOrange = Colour(255, 140, 0);
		constinit const Colour Orange = Colour(255, 165, 0);
		constinit const Colour OrangeRed = Colour(255, 69, 0);
		constinit const Colour Tomato = Colour(255, 99, 71);
		/* Yellow colors */
		constinit const Colour DarkKhaki = Colour(189, 183, 107);
		constinit const Colour Gold = Colour(255, 215, 0);
		constinit const Colour Khaki = Colour(240, 230, 140);
		constinit const Colour LemonChiffon = Colour(255, 250, 205);
		constinit const Colour LightGoldenrodYellow = Colour(250, 250, 210);
		constinit const Colour LightYellow = Colour(255, 255, 224);
		constinit const Colour Moccasin = Colour(255, 228, 181);
		constinit const Colour PaleGoldenrod = Colour(238, 232, 170);
		constinit const Colour PapayaWhip = Colour(255, 239, 213);
		constinit const Colour PeachPuff = Colour(255, 218, 185);
		constinit const Colour Yellow = Colour(255, 255, 0);
		/* Brown colors */
		constinit const Colour Bisque = Colour(255, 228, 196);
		constinit const Colour BlanchedAlmond = Colour(255, 235, 205);
		constinit const Colour Brown = Colour(165, 42, 42);
		constinit const Colour Burlywood = Colour(222, 184, 135);
		constinit const Colour Chocolate = Colour(210, 105, 30);
		constinit const Colour Cornsilk = Colour(255, 248, 220);
		constinit const Colour DarkGoldenrod = Colour(184, 134, 11);
		constinit const Colour Goldenrod = Colour(218, 165, 32);
		constinit const Colour Maroon = Colour(128, 0, 0);
		constinit const Colour NavajoWhite = Colour(255, 222, 173);
		constinit const Colour Peru = Colour(205, 133, 63);
		constinit const Colour RosyBrown = Colour(188, 143, 143);
		constinit const Colour SaddleBrown = Colour(139, 69, 19);
		constinit const Colour SandyBrown = Colour(244, 164, 96);
		constinit const Colour Sienna = Colour(160, 82, 45);
		constinit const Colour Tan = Colour(210, 180, 140);
		constinit const Colour Wheat = Colour(245, 222, 179);
		/* Purple, violet, and magenta colors */
		constinit const Colour BlueViolet = Colour(138, 43, 226);
		constinit const Colour DarkMagenta = Colour(139, 0, 139);
		constinit const Colour DarkOrchid = Colour(153, 50, 204);
		constinit const Colour DarkSlateBlue = Colour(72, 61, 139);
		constinit const Colour DarkViolet = Colour(148, 0, 211);
		constinit const Colour Fuchsia = Colour(255, 0, 255);
		constinit const Colour Indigo = Colour(75, 0, 130);
		constinit const Colour Lavender = Colour(230, 230, 250);
		constinit const Colour Magenta = Colour(255, 0, 255);
		constinit const Colour MediumOrchid = Colour(186, 85, 211);
		constinit const Colour MediumPurple = Colour(147, 112, 219);
		constinit const Colour MediumSlateBlue = Colour(123, 104, 238);
		constinit const Colour Orchid = Colour(218, 112, 214);
		constinit const Colour Plum = Colour(221, 160, 221);
		constinit const Colour Purple = Colour(128, 0, 128);
		constinit const Colour SlateBlue = Colour(106, 90, 205);
		constinit const Colour Thistle = Colour(216, 191, 216);
		constinit const Colour Violet = Colour(238, 130, 238);
		/* Blue colors */
		constinit const Colour Blue	 = Colour(0, 0, 255);
		constinit const Colour CornflowerBlue = Colour(100, 149, 237);
		constinit const Colour DarkBlue	= Colour(0, 0, 139);
		constinit const Colour DeepSkyBlue = Colour(0, 191, 255);
		constinit const Colour DodgerBlue = Colour(30, 144, 255);
		constinit const Colour LightBlue = Colour(173, 216, 230);
		constinit const Colour LightSkyBlue = Colour(135, 206, 250);
		constinit const Colour LightSteelBlue = Colour(176, 196, 222);
		constinit const Colour MediumBlue	 = Colour(0, 0, 205);
		constinit const Colour MidnightBlue = Colour(25, 25, 112);
		constinit const Colour Navy = Colour(0, 0, 128);
		constinit const Colour PowderBlue = Colour(176, 224, 230);
		constinit const Colour RoyalBlue	 = Colour(65, 105, 225);
		constinit const Colour SkyBlue = Colour(135, 206, 235);
		constinit const Colour SteelBlue = Colour(70, 130, 180);
		/*Cyan colors*/
		constinit const Colour Aqua = Colour(00, 255, 255);
		constinit const Colour Aquamarine = Colour(127, 255, 212);
		constinit const Colour CadetBlue = Colour(95, 158, 160);
		constinit const Colour Cyan = Colour(0, 255, 255);
		constinit const Colour DarkCyan = Colour(0, 139, 139);
		constinit const Colour DarkTurquoise = Colour(0, 206, 209);
		constinit const Colour LightCyan = Colour(224, 255, 255);
		constinit const Colour LightSeaGreen = Colour(32, 178, 170);
		constinit const Colour MediumTurquoise = Colour(72, 209, 204);
		constinit const Colour PaleTurquoise = Colour(175, 238, 238);
		constinit const Colour Teal = Colour(0, 128, 128);
		constinit const Colour Turquoise = Colour(64, 224, 208);
		/* Green colors */
		constinit const Colour Chartreuse = Colour(127, 255, 0);
		constinit const Colour DarkGreen = Colour(0, 100, 0);
		constinit const Colour DarkOliveGreen = Colour(85, 107, 47);
		constinit const Colour DarkSeaGreen = Colour(143, 188, 143);
		constinit const Colour ForestGreen = Colour(34, 139, 34);
		constinit const Colour Green = Colour(0, 128, 0);
		constinit const Colour GreenYellow = Colour(173, 255, 47);
		constinit const Colour LawnGreen = Colour(124, 252, 0);
		constinit const Colour LightGreen	 = Colour(144, 238, 144);
		constinit const Colour Lime = Colour(0, 255, 0);
		constinit const Colour LimeGreen = Colour(50, 205, 50);
		constinit const Colour MediumAquamarine = Colour(102, 205, 170);
		constinit const Colour MediumSeaGreen = Colour(60, 179, 113);
		constinit const Colour MediumSpringGreen = Colour(0, 250, 154);
		constinit const Colour Olive = Colour(128, 128, 0);
		constinit const Colour OliveDrab = Colour(107, 142, 35);
		constinit const Colour PaleGreen = Colour(152, 251, 152);
		constinit const Colour SeaGreen = Colour(46, 139, 87);
		constinit const Colour SpringGreen = Colour(0, 255, 127);
		constinit const Colour YellowGreen = Colour(154, 205, 50);
		/* White colors */
		constinit const Colour AliceBlue = Colour(240, 248, 255);
		constinit const Colour AntiqueWhite = Colour(250, 235, 215);
		constinit const Colour Azure = Colour(240, 255, 255);
		constinit const Colour Beige = Colour(245, 245, 220);
		constinit const Colour FloralWhite = Colour(255, 250, 240);
		constinit const Colour GhostWhite = Colour(248, 248, 255);
		constinit const Colour Honeydew = Colour(240, 255, 240);
		constinit const Colour Ivory = Colour(255, 255, 240);
		constinit const Colour LavenderBlush = Colour(255, 240, 245);
		constinit const Colour Linen = Colour(250, 240, 230);
		constinit const Colour MintCream = Colour(245, 255, 250);
		constinit const Colour MistyRose = Colour(255, 228, 225);
		constinit const Colour OldLace	 = Colour(253, 245, 230);
		constinit const Colour Seashell	 = Colour(255, 245, 238);
		constinit const Colour Snow	 = Colour(255, 250, 250);
		constinit const Colour White = Colour(255, 255, 255);
		constinit const Colour WhiteSmoke = Colour(245, 245, 245);
		/* Gray and black colors */
		constinit const Colour Black = Colour(0, 0, 0);
		constinit const Colour DarkGray = Colour(169, 169, 169);
		constinit const Colour DarkSlateGray = Colour(47, 79, 79);
		constinit const Colour DimGray = Colour(105, 105, 105);
		constinit const Colour Gainsboro = Colour(220, 220, 220);
		constinit const Colour Gray = Colour(128, 128, 128);
		constinit const Colour LightGray = Colour(211, 211, 211);
		constinit const Colour LightSlateGray = Colour(119, 136, 153);
		constinit const Colour Silver = Colour(192, 192, 192);
		constinit const Colour SlateGray = Colour(112, 128, 144);
	}
}