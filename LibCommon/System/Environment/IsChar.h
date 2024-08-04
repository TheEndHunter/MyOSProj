#pragma once
#include <TypeDefs.h>

namespace Common::System::Environment
{
	template<typename Type>
	bool GetIsChar()
	{
		return false;
	}

	template<>
	bool GetIsChar<char8_t>()
	{
		return true;
	}

	template<>
	bool GetIsChar<char16_t>()
	{
		return true;
	}

	template<>
	bool GetIsChar<char>()
	{
		return true;
	}

	template<>
	bool GetIsChar<char32_t>()
	{
		return true;
	}

	template<>
	bool GetIsChar<wchar_t>()
	{
		return true;
	}

	template<>
	bool GetIsChar<INT8>()
	{
		return false;
	}

	template<>
	bool GetIsChar<UINT8>()
	{
		return false;
	}

	template<>
	bool GetIsChar<INT16>()
	{
		return false;
	}

	template<>
	bool GetIsChar<UINT16>()
	{
		return false;
	}
	template<>
	bool GetIsChar<INT32>()
	{
		return false;
	}

	template<>
	bool GetIsChar<UINT32>()
	{
		return false;
	}
	template<>
	bool GetIsChar<INT64>()
	{
		return false;
	}

	template<>
	bool GetIsChar<UINT64>()
	{
		return false;
	}

	template<typename Type>
	concept IsChar = requires(Type)
	{
		GetIsChar<Type>();
	};


	template<IsChar Type>
	UINT8 GetCharWidth()
	{
		return sizeof(Type);
	}
}