#include <System/Environment/String.h>

namespace Common::System::Environment
{
	template<IsChar StrType>
	string<StrType>::string(const UINT64 length)
	{
		if (length > 0)
		{
			_length = length;
			_data = new StrType[length];
			_data[length - 1] = 0;
		}
		else
		{
			_length = length;
			_data = nullptr;
		}
	}

	template<IsChar StrType>
	
	string<StrType>::string(const Array<StrType> arr)
	{
		_length = arr.Length();
		_data = new StrType[_length];
		for (UINT64 i = 0; i < _length; i++)
		{
			_data[i] = arr[i];
		}
	}

	template<IsChar StrType>
	string<StrType>::string(const StrType* ptr)
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
		_data = new StrType[dLen];
		for (UINT64 i = 0; i < _length; i++)
		{
			_data[i] = ptr[i];
		}
		_data[_length] = 0;
	}

	template<IsChar StrType>
	string<StrType>::string(const StrType& str)
	{
		UINT64 dLen = 0;
		while (str[dLen] != 0)
		{
			dLen++;
		}

		_length = dLen + 1;
		_data = new StrType[dLen];
		for (UINT64 i = 0; i < _length; i++)
		{
			_data[i] = str[i];
		}
		_data[_length] = 0;
	}

	template<IsChar StrType>
	string<StrType>::string(const StrType* ptr, UINT64 length)
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
			_data = new StrType[dLen];
			for (UINT64 i = 0; i < _length; i++)
			{
				_data[i] = ptr[i];
			}
			_data[_length] = 0;
		}
		else
		{
			_length = length;
			_data = new StrType[length];
			for (UINT64 i = 0; i < _length; i++)
			{
				_data[i] = ptr[i];
			}
		}
	}

	template<IsChar StrType>
	string<StrType>::string(const StrType& str, UINT64 length)
	{
		if (length == 0)
		{
			UINT64 dLen = 0;
			while (str[dLen] != 0)
			{
				dLen++;
			}

			_length = dLen + 1;
			_data = new StrType[dLen];
			for (UINT64 i = 0; i < _length; i++)
			{
				_data[i] = str[i];
			}
			_data[_length] = 0;
		}
		else
		{
			_length = length;
			_data = new StrType[length];
			for (UINT64 i = 0; i < _length; i++)
			{
				_data[i] = str[i];
			}
		}
	}

	template<IsChar StrType>
	string<StrType>::string(const string<StrType>& other)
	{
		_length = other._length;
		_data = new StrType[_length];
		for (UINT64 i = 0; i < _length; i++)
		{
			_data[i] = other._data[i];
		}
	}

	template<IsChar StrType>
	string<StrType>::~string()
	{
		delete[] _data;
	}
}