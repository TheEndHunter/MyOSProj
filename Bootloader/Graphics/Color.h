#pragma once
#include <UEFIDef.h>


namespace Bootloader::Graphics
{
	/*
	*  struct for containing a 4 8-bit color values.
	*  with functions for converting to 32-bit color values.
	* 
	*  This struct also supports the following operators:
	*  + - * / += -= *= /= == != < > <= >=
	*/

	typedef struct Color
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

		Color operator+(const Color& other) const
		{
			return Color(Blue + other.Blue, Green + other.Green, Red + other.Red, Alpha + other.Alpha);
		}

		Color operator-(const Color& other) const
		{
			return Color(Blue - other.Blue, Green - other.Green, Red - other.Red, Alpha - other.Alpha);
		}

		Color operator*(const Color& other) const
		{
			return Color(Blue * other.Blue, Green * other.Green, Red * other.Red, Alpha * other.Alpha);
		}

		Color operator/(const Color& other) const
		{
			return Color(Blue / other.Blue, Green / other.Green, Red / other.Red, Alpha / other.Alpha);
		}

		bool operator==(const Color& other) const
		{
			return Blue == other.Blue && Green == other.Green && Red == other.Red && Alpha == other.Alpha;
		}

		bool operator!=(const Color& other) const
		{
			return Blue != other.Blue || Green != other.Green || Red != other.Red || Alpha != other.Alpha;
		}

		bool operator<(const Color& other) const
		{
			return Blue < other.Blue && Green < other.Green && Red < other.Red && Alpha < other.Alpha;
		}

		bool operator>(const Color& other) const
		{
			return Blue > other.Blue && Green > other.Green && Red > other.Red && Alpha > other.Alpha;
		}

		bool operator<=(const Color& other) const
		{
			return Blue <= other.Blue && Green <= other.Green && Red <= other.Red && Alpha <= other.Alpha;
		}

		bool operator>=(const Color& other) const
		{
			return Blue >= other.Blue && Green >= other.Green && Red >= other.Red && Alpha >= other.Alpha;
		}

		constexpr Color() : Blue(0), Green(0), Red(0), Alpha(255) {};
		constexpr Color(const UINT8 red, const UINT8 green, const UINT8 blue,const UINT8 alpha) : Blue(blue), Green(green), Red(red), Alpha(alpha) {}
		constexpr Color(const UINT8 red, const UINT8 green, const UINT8 blue) : Blue(blue), Green(green), Red(red), Alpha(255) {}

		const Color FromRGBA(const UINT32 rgba) const 
		{
			return Color((UINT8)((rgba & 0x0000FF00) >> 8), (UINT8)((rgba & 0x00FF0000) >> 16), (UINT8)((rgba & 0xFF000000) >> 24), (UINT8)(rgba & 0x000000FF));
		}

		const Color FromBGRA(const UINT32 bgra) const 
		{
			return Color((UINT8)((bgra & 0xFF000000) >> 24), (UINT8)((bgra & 0x00FF0000) >> 16), (UINT8)((bgra & 0x0000FF00) >> 8), (UINT8)(bgra & 0x000000FF));
		}

		const Color FromARGB(const UINT32 argb) const 
		{
			return Color((UINT8)((argb & 0x000000FF)), (UINT8)((argb & 0x0000FF00) >> 8), (UINT8)((argb & 0x00FF0000) >> 16), (UINT8)((argb & 0xFF000000)>>24));
		} 

		const Color FromABGR(const UINT32 abgr) const 
		{
			return Color((UINT8)((abgr & 0x00FF0000) >> 16), (UINT8)((abgr & 0x0000FF00) >> 8), (UINT8)(abgr & 0x000000FF), (UINT8)((abgr & 0xFF000000)>>24));
		}

		const Color FromRGBA(const UINT8 r, const UINT8 g, const UINT8 b, const UINT8 a = 255) const 
		{
			return Color(b, g, r, a);
		}

		const Color FromBGRA(const UINT8 b, const UINT8 g, const UINT8 r, const UINT8 a = 255) const 
		{
			return Color(b, g, r, a);
		}

		const Color FromARGB(const UINT8 a, const UINT8 r, const UINT8 g, const UINT8 b) const 
		{
			return Color(b, g, r, a);
		} 

		const Color FromABGR(const UINT8 a, const UINT8 b, const UINT8 g, const UINT8 r) const 
		{
			return Color(b, g, r, a);
		}
	};
	
	/// <summary>
	///  Selection of colours for use in the bootloader for the GraphicsContext.
	///  base on colors from https://en.wikipedia.org/wiki/Web_colors
	/// </summary>
	namespace Colors
	{
		/* Pink colors */
		constinit const Color DeepPink =Color(255, 20, 147);
		constinit const Color HotPink = Color(255, 105, 180);
		constinit const Color LightPink = Color(255, 182, 193);
		constinit const Color MediumVioletRed = Color((UINT8)199, (UINT8)21, (UINT8)133);
		constinit const Color PaleVioletRed	=Color(219, 112, 147);
		constinit const Color Pink = Color(255, 192, 203);
		/* Red colors */
		constinit const Color Crimson = Color(220, 20, 60);
		constinit const Color DarkRed = Color(139, 0, 0);
		constinit const Color DarkSalmon = Color(233, 150, 122);
		constinit const Color Firebrick = Color(178, 34, 34);
		constinit const Color IndianRed = Color(205, 92, 92);
		constinit const Color LightCoral = Color(240, 128, 128);
		constinit const Color LightSalmon = Color(255, 160, 122);
		constinit const Color Red = Color(255, 0, 0);
		constinit const Color Salmon = Color(250, 128, 114);
		 /* Orange colors */
		constinit const Color Coral = Color(255, 127, 80);
		constinit const Color DarkOrange = Color(255, 140, 0);
		constinit const Color Orange = Color(255, 165, 0);
		constinit const Color OrangeRed = Color(255, 69, 0);
		constinit const Color Tomato = Color(255, 99, 71);
		/* Yellow colors */
		constinit const Color DarkKhaki = Color(189, 183, 107);
		constinit const Color Gold = Color(255, 215, 0);
		constinit const Color Khaki = Color(240, 230, 140);
		constinit const Color LemonChiffon = Color(255, 250, 205);
		constinit const Color LightGoldenrodYellow = Color(250, 250, 210);
		constinit const Color LightYellow = Color(255, 255, 224);
		constinit const Color Moccasin = Color(255, 228, 181);
		constinit const Color PaleGoldenrod = Color(238, 232, 170);
		constinit const Color PapayaWhip = Color(255, 239, 213);
		constinit const Color PeachPuff = Color(255, 218, 185);
		constinit const Color Yellow = Color(255, 255, 0);
		/* Brown colors */
		constinit const Color Bisque = Color(255, 228, 196);
		constinit const Color BlanchedAlmond = Color(255, 235, 205);
		constinit const Color Brown = Color(165, 42, 42);
		constinit const Color Burlywood = Color(222, 184, 135);
		constinit const Color Chocolate = Color(210, 105, 30);
		constinit const Color Cornsilk = Color(255, 248, 220);
		constinit const Color DarkGoldenrod = Color(184, 134, 11);
		constinit const Color Goldenrod = Color(218, 165, 32);
		constinit const Color Maroon = Color(128, 0, 0);
		constinit const Color NavajoWhite = Color(255, 222, 173);
		constinit const Color Peru = Color(205, 133, 63);
		constinit const Color RosyBrown = Color(188, 143, 143);
		constinit const Color SaddleBrown = Color(139, 69, 19);
		constinit const Color SandyBrown = Color(244, 164, 96);
		constinit const Color Sienna = Color(160, 82, 45);
		constinit const Color Tan = Color(210, 180, 140);
		constinit const Color Wheat = Color(245, 222, 179);
		/* Purple, violet, and magenta colors */
		constinit const Color BlueViolet = Color(138, 43, 226);
		constinit const Color DarkMagenta = Color(139, 0, 139);
		constinit const Color DarkOrchid = Color(153, 50, 204);
		constinit const Color DarkSlateBlue = Color(72, 61, 139);
		constinit const Color DarkViolet = Color(148, 0, 211);
		constinit const Color Fuchsia = Color(255, 0, 255);
		constinit const Color Indigo = Color(75, 0, 130);
		constinit const Color Lavender = Color(230, 230, 250);
		constinit const Color Magenta = Color(255, 0, 255);
		constinit const Color MediumOrchid = Color(186, 85, 211);
		constinit const Color MediumPurple = Color(147, 112, 219);
		constinit const Color MediumSlateBlue = Color(123, 104, 238);
		constinit const Color Orchid = Color(218, 112, 214);
		constinit const Color Plum = Color(221, 160, 221);
		constinit const Color Purple = Color(128, 0, 128);
		constinit const Color SlateBlue = Color(106, 90, 205);
		constinit const Color Thistle = Color(216, 191, 216);
		constinit const Color Violet = Color(238, 130, 238);
		/* Blue colors */
		constinit const Color Blue	 = Color(0, 0, 255);
		constinit const Color CornflowerBlue = Color(100, 149, 237);
		constinit const Color DarkBlue	= Color(0, 0, 139);
		constinit const Color DeepSkyBlue = Color(0, 191, 255);
		constinit const Color DodgerBlue = Color(30, 144, 255);
		constinit const Color LightBlue = Color(173, 216, 230);
		constinit const Color LightSkyBlue = Color(135, 206, 250);
		constinit const Color LightSteelBlue = Color(176, 196, 222);
		constinit const Color MediumBlue	 = Color(0, 0, 205);
		constinit const Color MidnightBlue = Color(25, 25, 112);
		constinit const Color Navy = Color(0, 0, 128);
		constinit const Color PowderBlue = Color(176, 224, 230);
		constinit const Color RoyalBlue	 = Color(65, 105, 225);
		constinit const Color SkyBlue = Color(135, 206, 235);
		constinit const Color SteelBlue = Color(70, 130, 180);
		/*Cyan colors*/
		constinit const Color Aqua = Color(00, 255, 255);
		constinit const Color Aquamarine = Color(127, 255, 212);
		constinit const Color CadetBlue = Color(95, 158, 160);
		constinit const Color Cyan = Color(0, 255, 255);
		constinit const Color DarkCyan = Color(0, 139, 139);
		constinit const Color DarkTurquoise = Color(0, 206, 209);
		constinit const Color LightCyan = Color(224, 255, 255);
		constinit const Color LightSeaGreen = Color(32, 178, 170);
		constinit const Color MediumTurquoise = Color(72, 209, 204);
		constinit const Color PaleTurquoise = Color(175, 238, 238);
		constinit const Color Teal = Color(0, 128, 128);
		constinit const Color Turquoise = Color(64, 224, 208);
		/* Green colors */
		constinit const Color Chartreuse = Color(127, 255, 0);
		constinit const Color DarkGreen = Color(0, 100, 0);
		constinit const Color DarkOliveGreen = Color(85, 107, 47);
		constinit const Color DarkSeaGreen = Color(143, 188, 143);
		constinit const Color ForestGreen = Color(34, 139, 34);
		constinit const Color Green = Color(0, 128, 0);
		constinit const Color GreenYellow = Color(173, 255, 47);
		constinit const Color LawnGreen = Color(124, 252, 0);
		constinit const Color LightGreen	 = Color(144, 238, 144);
		constinit const Color Lime = Color(0, 255, 0);
		constinit const Color LimeGreen = Color(50, 205, 50);
		constinit const Color MediumAquamarine = Color(102, 205, 170);
		constinit const Color MediumSeaGreen = Color(60, 179, 113);
		constinit const Color MediumSpringGreen = Color(0, 250, 154);
		constinit const Color Olive = Color(128, 128, 0);
		constinit const Color OliveDrab = Color(107, 142, 35);
		constinit const Color PaleGreen = Color(152, 251, 152);
		constinit const Color SeaGreen = Color(46, 139, 87);
		constinit const Color SpringGreen = Color(0, 255, 127);
		constinit const Color YellowGreen = Color(154, 205, 50);
		/* White colors */
		constinit const Color AliceBlue = Color(240, 248, 255);
		constinit const Color AntiqueWhite = Color(250, 235, 215);
		constinit const Color Azure = Color(240, 255, 255);
		constinit const Color Beige = Color(245, 245, 220);
		constinit const Color FloralWhite = Color(255, 250, 240);
		constinit const Color GhostWhite = Color(248, 248, 255);
		constinit const Color Honeydew = Color(240, 255, 240);
		constinit const Color Ivory = Color(255, 255, 240);
		constinit const Color LavenderBlush = Color(255, 240, 245);
		constinit const Color Linen = Color(250, 240, 230);
		constinit const Color MintCream = Color(245, 255, 250);
		constinit const Color MistyRose = Color(255, 228, 225);
		constinit const Color OldLace	 = Color(253, 245, 230);
		constinit const Color Seashell	 = Color(255, 245, 238);
		constinit const Color Snow	 = Color(255, 250, 250);
		constinit const Color White = Color(255, 255, 255);
		constinit const Color WhiteSmoke = Color(245, 245, 245);
		/* Gray and black colors */
		constinit const Color Black = Color(0, 0, 0);
		constinit const Color DarkGray = Color(169, 169, 169);
		constinit const Color DarkSlateGray = Color(47, 79, 79);
		constinit const Color DimGray = Color(105, 105, 105);
		constinit const Color Gainsboro = Color(220, 220, 220);
		constinit const Color Gray = Color(128, 128, 128);
		constinit const Color LightGray = Color(211, 211, 211);
		constinit const Color LightSlateGray = Color(119, 136, 153);
		constinit const Color Silver = Color(192, 192, 192);
		constinit const Color SlateGray = Color(112, 128, 144);
	}
}