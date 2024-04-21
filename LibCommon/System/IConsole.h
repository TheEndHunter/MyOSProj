#pragma once
#include <TypeDefs.h>
#include <Graphics/Colour.h>
#include <Numerics/Vectors.h>

namespace Common::System
{
	using namespace Common::Graphics;
	using namespace Common::Numerics;

	class IConsole
	{
	public:

		virtual void Write(const CCHAR* message) = 0;
		virtual void WriteLine(const CCHAR* message) = 0;
		virtual void Write(const CHAR8* message) = 0;
		virtual void WriteLine(const CHAR8* message) = 0;
		virtual void Write(const CHAR16* message) = 0;
		virtual void WriteLine(const CHAR16* message) = 0;

		virtual void FWrite(const CCHAR* format, ...) = 0;
		virtual void FWriteLine(const CCHAR* format, ...) = 0;
		virtual void FWrite(const CHAR8* format, ...) = 0;
		virtual void FWriteLine(const CHAR8* format, ...) = 0;
		virtual void FWrite(const CHAR16* format, ...) = 0;
		virtual void FWriteLine(const CHAR16* format, ...) = 0;

		virtual CCHAR ReadASCIIChar() = 0;
		virtual CHAR8 ReadUTF8Char() = 0;
		virtual CHAR16 ReadUTF16Char() = 0;

		virtual CCHAR* ReadASCIILine(OUT UINTN* len) = 0;
		virtual CHAR8* ReadUTF8Line(OUT UINTN* len) = 0;
		virtual CHAR16* ReadUTF16Line(OUT UINTN* len) = 0;

		virtual void SetPosition(UINT32 x, UINT32 y) = 0;
		virtual void SetForegroundColor(UINT32 color) = 0;
		virtual void SetForegroundColor(Colour colour) = 0;
		virtual void SetForegroundColor(UINT8 r, UINT8 g, UINT8 b, UINT8 a = 255) = 0;
		virtual void SetBackgroundColor(UINT32 color) = 0;
		virtual void SetBackgroundColor(Colour colour) = 0;
		virtual void SetBackgroundColor(UINT8 r, UINT8 g, UINT8 b, UINT8 a = 255) = 0;

		virtual Vect2D<UINT32> GetCursorPosition() = 0;
		virtual Colour GetForegroundColor() = 0;
		virtual Colour GetBackgroundColor() = 0;

		virtual void Clear(BOOLEAN resetColors = FALSE) = 0;
		virtual void ClearLine(BOOLEAN resetColors = FALSE) = 0;


		void operator << (const CCHAR* message) { Write(message); }
		void operator << (const CHAR8* message) { Write(message); }
		void operator << (const CHAR16* message) { Write(message); }

		UINTN operator >> (CCHAR* c)
		{
			UINTN i = 0;
			c = ReadASCIILine(&i);
			return i;
		}

		UINTN operator >> (CHAR8* c)
		{
			UINTN i = 0;
			c = ReadUTF8Line(&i);
			return i;
		}

		UINTN operator >> (CHAR16* c)
		{
			UINTN i = 0;
			c = ReadUTF16Line(&i);
			return i;
		}

	};
}