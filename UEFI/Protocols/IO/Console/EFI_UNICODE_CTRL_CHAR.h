#pragma once
#include <UEFIDef.h>

namespace EFI
{
	struct EFI_UNICODE_CTRL_CHAR
	{
	public:
		static constexpr CHAR16 NUL = 0x0000;
		static constexpr CHAR16 BACKSPACE = 0x0008;
		static constexpr CHAR16 TAB = 0x0009;
		static constexpr CHAR16 LF = 0x000A;
		static constexpr CHAR16 CR = 0x000D;
		static constexpr CHAR16 ESC = 0x001B;
	};

	//******************************************************
	// UNICODE DRAWING CHARACTERS
	//******************************************************
	struct EFI_UNICODE_DRAWING_CHAR
	{
	public:

		static const CHAR16 BOXDRAW_HORIZONTAL = 0x2500;
		static const CHAR16 BOXDRAW_VERTICAL = 0x2502;
		static const CHAR16 BOXDRAW_DOWN_RIGHT = 0x250c;
		static const CHAR16 BOXDRAW_DOWN_LEFT = 0x2510;
		static const CHAR16 BOXDRAW_UP_RIGHT = 0x2514;
		static const CHAR16 BOXDRAW_UP_LEFT = 0x2518;
		static const CHAR16 BOXDRAW_VERTICAL_RIGHT = 0x251c;
		static const CHAR16 BOXDRAW_VERTICAL_LEFT = 0x2524;
		static const CHAR16 BOXDRAW_DOWN_HORIZONTAL = 0x252c;
		static const CHAR16 BOXDRAW_UP_HORIZONTAL = 0x2534;
		static const CHAR16 BOXDRAW_VERTICAL_HORIZONTAL = 0x253c;

		static const CHAR16 BOXDRAW_DOUBLE_HORIZONTAL = 0x2550;
		static const CHAR16 BOXDRAW_DOUBLE_VERTICAL = 0x2551;
		static const CHAR16 BOXDRAW_DOWN_RIGHT_DOUBLE = 0x2552;
		static const CHAR16 BOXDRAW_DOWN_DOUBLE_RIGHT = 0x2553;
		static const CHAR16 BOXDRAW_DOUBLE_DOWN_RIGHT = 0x2554;
		static const CHAR16 BOXDRAW_DOWN_LEFT_DOUBLE = 0x2555;
		static const CHAR16 BOXDRAW_DOWN_DOUBLE_LEFT = 0x2556;
		static const CHAR16 BOXDRAW_DOUBLE_DOWN_LEFT = 0x2557;
		
		static const CHAR16 BOXDRAW_UP_RIGHT_DOUBLE = 0x2558;
		static const CHAR16 BOXDRAW_UP_DOUBLE_RIGHT = 0x2559;
		static const CHAR16 BOXDRAW_DOUBLE_UP_RIGHT = 0x255a;
		static const CHAR16 BOXDRAW_UP_LEFT_DOUBLE = 0x255b;
		static const CHAR16 BOXDRAW_UP_DOUBLE_LEFT = 0x255c;
		static const CHAR16 BOXDRAW_DOUBLE_UP_LEFT = 0x255d;
		
		static const CHAR16 BOXDRAW_VERTICAL_RIGHT_DOUBLE = 0x255e;
		static const CHAR16 BOXDRAW_VERTICAL_DOUBLE_RIGHT = 0x255f;
		static const CHAR16 BOXDRAW_DOUBLE_VERTICAL_RIGHT = 0x2560;
		
		static const CHAR16 BOXDRAW_VERTICAL_LEFT_DOUBLE = 0x2561;
		static const CHAR16 BOXDRAW_VERTICAL_DOUBLE_LEFT = 0x2562;
		static const CHAR16 BOXDRAW_DOUBLE_VERTICAL_LEFT = 0x2563;
		
		static const CHAR16 BOXDRAW_DOWN_HORIZONTAL_DOUBLE = 0x2564;
		static const CHAR16 BOXDRAW_DOWN_DOUBLE_HORIZONTAL = 0x2565;
		static const CHAR16 BOXDRAW_DOUBLE_DOWN_HORIZONTAL = 0x2566;
		
		static const CHAR16 BOXDRAW_UP_HORIZONTAL_DOUBLE = 0x2567;
		static const CHAR16 BOXDRAW_UP_DOUBLE_HORIZONTAL = 0x2568;
		static const CHAR16 BOXDRAW_DOUBLE_UP_HORIZONTAL = 0x2569;
		
		static const CHAR16 BOXDRAW_VERTICAL_HORIZONTAL_DOUBLE = 0x256a;
		static const CHAR16 BOXDRAW_VERTICAL_DOUBLE_HORIZONTAL = 0x256b;
		static const CHAR16 BOXDRAW_DOUBLE_VERTICAL_HORIZONTAL = 0x256c;
		
		//******************************************************
		// EFI Required Block Elements Code Chart
		//******************************************************
		
		static const CHAR16 BLOCKELEMENT_FULL_BLOCK = 0x2588;
		static const CHAR16 BLOCKELEMENT_LIGHT_SHADE = 0x2591;
		
		//******************************************************
		// EFI Required Geometric Shapes Code Chart
		//******************************************************
		
		static const CHAR16 GEOMETRICSHAPE_UP_TRIANGLE = 0x25b2;
		static const CHAR16 GEOMETRICSHAPE_RIGHT_TRIANGLE = 0x25ba;
		static const CHAR16 GEOMETRICSHAPE_DOWN_TRIANGLE = 0x25bc;
		static const CHAR16 GEOMETRICSHAPE_LEFT_TRIANGLE = 0x25c4;
		
		//******************************************************
		// EFI Required Arrow shapes
		//******************************************************
		
		static const CHAR16 ARROW_UP = 0x2191;
		static const CHAR16 ARROW_DOWN = 0x2193;
	};
}
