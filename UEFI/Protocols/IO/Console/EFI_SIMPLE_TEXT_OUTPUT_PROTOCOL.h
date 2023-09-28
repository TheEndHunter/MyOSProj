#pragma once
#include <UEFIDef.h>
#include <EFI_STATUS.h>
#include <EFI_GUID.h>

namespace EFI
{
	constinit const EFI_GUID EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL_GUID = { 0x387477c2, 0x69c7, 0x11d2,{ 0x8e, 0x39, 0x00, 0xa0, 0xc9, 0x69, 0x72, 0x3b }};

	struct EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL;

	struct EFI_SIMPLE_TEXT_OUTPUT_MODE
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
	* EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL function Delegates
	*/
	typedef EFI::EFI_STATUS(EFIAPI* EFI_TEXT_RESET)(EFI::EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL* self, BOOLEAN ExtendedVerification);
	typedef EFI::EFI_STATUS(EFIAPI* EFI_TEXT_STRING)(EFI::EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL* self,const CHAR16* String);
	typedef EFI::EFI_STATUS(EFIAPI* EFI_TEXT_TEST_STRING)(EFI::EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL* self,const CHAR16* String);
	typedef EFI::EFI_STATUS(EFIAPI* EFI_TEXT_QUERY_MODE)(EFI::EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL* self, UINTN Modenumber, UINTN* Columns, UINTN* Rows);
	typedef EFI::EFI_STATUS(EFIAPI* EFI_TEXT_SET_MODE)(EFI::EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL* self, UINTN Modenumber);
	typedef EFI::EFI_STATUS(EFIAPI* EFI_TEXT_SET_ATTRIBUTE)(EFI::EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL* self, UINTN Attribute);
	typedef EFI::EFI_STATUS(EFIAPI* EFI_TEXT_CLEAR_SCREEN)(EFI::EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL* self);
	typedef EFI::EFI_STATUS(EFIAPI* EFI_TEXT_SET_CURSOR_POSITION)(EFI::EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL* self, UINTN Column, UINTN Row);
	typedef EFI::EFI_STATUS(EFIAPI* EFI_TEXT_ENABLE_CURSOR)(EFI::EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL* self, BOOLEAN Visible);

	struct EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL
	{
	public:
		EFI::EFI_TEXT_RESET Reset;
		EFI::EFI_TEXT_STRING OutputString;
		EFI::EFI_TEXT_TEST_STRING TestString;
		EFI::EFI_TEXT_QUERY_MODE QueryMode;
		EFI::EFI_TEXT_SET_MODE SetMode;
		EFI::EFI_TEXT_SET_ATTRIBUTE SetAttribute;
		EFI::EFI_TEXT_CLEAR_SCREEN ClearScreen;
		EFI::EFI_TEXT_SET_CURSOR_POSITION SetCursorPosition;
		EFI::EFI_TEXT_ENABLE_CURSOR EnableCursor;
		EFI::EFI_SIMPLE_TEXT_OUTPUT_MODE* Mode;
	};

	
}
