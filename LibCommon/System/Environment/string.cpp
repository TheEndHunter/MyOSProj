#include <System/Environment/string.h>

namespace Common::System::Environment
{
	template<IsChar Type>
	string<Type>::string(const UINT64 length)
	{
		if (length > 0)
		{
			_length = length;
			_data = new Type[length];
			_data[length - 1] = 0;
		}
		else
		{
			_length = length;
			_data = nullptr;
		}
	}

	template<IsChar Type>
	
	string<Type>::string(const Array<Type> arr)
	{
		_length = arr.Length();
		_data = new Type[_length];
		for (UINT64 i = 0; i < _length; i++)
		{
			_data[i] = arr[i];
		}
	}

	template<IsChar Type>
	string<Type>::string(const Type* ptr)
	{
		if (ptr == nullptr)
		{
			_length = 0;
			_data = nullptr;
			return;
		}

		UINT64 dLen = 0;
		while (ptr[dLen] != 0)
		{
			dLen++;
		}

		_length = dLen + 1;
		_data = new Type[dLen];
		for (UINT64 i = 0; i < _length; i++)
		{
			_data[i] = ptr[i];
		}
		_data[_length] = 0;
	}

	template<IsChar Type>
	string<Type>::string(const Type& str)
	{
		UINT64 dLen = 0;
		while (str[dLen] != 0)
		{
			dLen++;
		}

		_length = dLen + 1;
		_data = new Type[dLen];
		for (UINT64 i = 0; i < _length; i++)
		{
			_data[i] = str[i];
		}
		_data[_length] = 0;
	}

	template<IsChar Type>
	string<Type>::string(const Type* ptr, UINT64 length)
	{
		if (ptr == nullptr)
		{
			_length = 0;
			_data = nullptr;
			return;
		}

		if (length == 0)
		{
			UINT64 dLen = 0;
			while (ptr[dLen] != 0)
			{
				dLen++;
			}

			_length = dLen + 1;
			_data = new Type[dLen];
			for (UINT64 i = 0; i < _length; i++)
			{
				_data[i] = ptr[i];
			}
			_data[_length] = 0;
		}
		else
		{
			_length = length;
			_data = new Type[length];
			for (UINT64 i = 0; i < _length; i++)
			{
				_data[i] = ptr[i];
			}
		}
	}

	template<IsChar Type>
	string<Type>::string(const Type& str, UINT64 length)
	{
		if (length == 0)
		{
			UINT64 dLen = 0;
			while (str[dLen] != 0)
			{
				dLen++;
			}

			_length = dLen + 1;
			_data = new Type[dLen];
			for (UINT64 i = 0; i < _length; i++)
			{
				_data[i] = str[i];
			}
			_data[_length] = 0;
		}
		else
		{
			_length = length;
			_data = new Type[length];
			for (UINT64 i = 0; i < _length; i++)
			{
				_data[i] = str[i];
			}
		}
	}

	template<IsChar Type>
	string<Type>::string(const string<Type>& other)
	{
		_length = other._length;
		_data = new Type[_length];
		for (UINT64 i = 0; i < _length; i++)
		{
			_data[i] = other._data[i];
		}
	}

	template<IsChar Type>
	string<Type>::~string()
	{
		delete[] _data;
	}
}