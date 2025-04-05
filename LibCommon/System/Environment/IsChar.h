#pragma once
#include <TypeDefs.h>

namespace Common::System::Environment
{
	template<typename StrType>
	inline BOOLEAN  GetIsChar()
	{
		return false;
	}

	template<>
	inline BOOLEAN  GetIsChar<char8_t>()
	{
		return true;
	}

	template<>
	inline BOOLEAN  GetIsChar<char16_t>()
	{
		return true;
	}

	template<>
	inline BOOLEAN  GetIsChar<char>()
	{
		return true;
	}

	template<>
	inline BOOLEAN  GetIsChar<char32_t>()
	{
		return true;
	}

	template<>
	inline BOOLEAN  GetIsChar<wchar_t>()
	{
		return true;
	}

	template<>
	inline BOOLEAN  GetIsChar<INT8>()
	{
		return false;
	}

	template<>
	inline BOOLEAN  GetIsChar<UINT8>()
	{
		return false;
	}

	template<>
	inline BOOLEAN  GetIsChar<INT16>()
	{
		return false;
	}

	template<>
	inline BOOLEAN  GetIsChar<UINT16>()
	{
		return false;
	}
	template<>
	inline BOOLEAN  GetIsChar<INT32>()
	{
		return false;
	}

	template<>
	inline BOOLEAN  GetIsChar<UINT32>()
	{
		return false;
	}
	template<>
	inline BOOLEAN  GetIsChar<INT64>()
	{
		return false;
	}

	template<>
	inline BOOLEAN  GetIsChar<UINT64>()
	{
		return false;
	}

	template<typename StrType>
	concept IsChar = requires(StrType)
	{
		GetIsChar<StrType>();
	};
}