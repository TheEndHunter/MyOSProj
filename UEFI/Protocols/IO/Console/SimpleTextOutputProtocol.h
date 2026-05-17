#pragma once
#include "UEFIDef.h"
#include <Status.h>
#include <Guid.h>

namespace Efi
{
	struct SimpleTextOutputProtocol;

constinit  const ALIGN(8) Guid SimpleTextOutputProtocolGuid = { 0x387477c2, 0x69c7, 0x11d2,{ 0x8e, 0x39, 0x00, 0xa0, 0xc9, 0x69, 0x72, 0x3b }};

	struct SimpleTextOutputMode
	{
	public:
		INT32 MaxMode;
		INT32 Mode;
		INT32 Attribute;
		INT32 CursorColumn;
		INT32 CursorRow;
		BOOLEAN CursorVisible;
	};

	/*
	* SimpleTextOutputProtocol function Delegates
	*/
	typedef Status(EFIAPI* TextResetFunc)(SimpleTextOutputProtocol* self, BOOLEAN ExtendedVerification);
	typedef Status(EFIAPI* TextStringFunc)(SimpleTextOutputProtocol* self, CONST CHAR16* String);
	typedef Status(EFIAPI* TextTestStringFunc)(SimpleTextOutputProtocol* self, CONST CHAR16* String);
	typedef Status(EFIAPI* TextQueryModeFunc)(SimpleTextOutputProtocol* self, UINTN Modenumber, UINTN* Columns, UINTN* Rows);
	typedef Status(EFIAPI* TextSetModeFunc)(SimpleTextOutputProtocol* self, UINTN Modenumber);
	typedef Status(EFIAPI* TextSetAttributeFunc)(SimpleTextOutputProtocol* self, UINTN Attribute);
	typedef Status(EFIAPI* TextClearScreenFunc)(SimpleTextOutputProtocol* self);
	typedef Status(EFIAPI* TextSetCursorPositionFunc)(SimpleTextOutputProtocol* self, UINTN Column, UINTN Row);
	typedef Status(EFIAPI* TextEnableCursorFunc)(SimpleTextOutputProtocol* self, BOOLEAN Visible);

	struct SimpleTextOutputProtocol
	{
	public:
		TextResetFunc Reset;
		TextStringFunc OutputString;
		TextTestStringFunc TestString;
		TextQueryModeFunc QueryMode;
		TextSetModeFunc SetMode;
		TextSetAttributeFunc SetAttribute;
		TextClearScreenFunc ClearScreen;
		TextSetCursorPositionFunc SetCursorPosition;
		TextEnableCursorFunc EnableCursor;
		SimpleTextOutputMode* Mode;
	};

	
}
