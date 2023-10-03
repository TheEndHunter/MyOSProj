#pragma once
#include <UEFIDef.h>
namespace Bootloader
{
	class Environment
	{
	public:
		static const CHAR16  NULL = u'\0';
		static const CHAR16* NewLine;
		static const CHAR16  Space = u' ';
		static const CHAR16  Tab = u'\t';
		static const CHAR16  Backspace = u'\b';
	};

}