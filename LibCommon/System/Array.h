#pragma once
#include <TypeDefs.h>

namespace Common::System
{
	template<typename Type>
	struct Array
	{
	public:

		Array(const UINT64 length)
		{
			_length = length;
			_data = new Type[length];
		}

		Array(Type value, const UINT64 length)
		{
			_length = length;
			_data = new Type[length];
			for (UINT64 i = 0; i < length; i++)
			{
				_data[i] = value;
			}
		}

		Array(Type* data, UINT64 length)
		{
			_length = length;
			_data = new Type[length];
			for (UINT64 i = 0; i < length; i++)
			{
				_data[i] = data[i];
			}
		}

		Array(const Array<Type>& other)
		{
			_length = other._length;
			_data = new Type[_length];
			for (UINT64 i = 0; i < _length; i++)
			{
				_data[i] = other._data[i];
			}
		}

		~Array()
		{
			delete[] _data;
		}

		UINT64 Length()
		{
			return _length;
		}

		Type& operator[](UINT64 index)
		{
			return _data[index];
		}

		BOOLEAN Contains(const Type& value)
		{
			for (UINT64 i = 0; i < _length; i++)
			{
				if (_data[i] == value)
				{
					return TRUE;
				}
			}
			return FALSE;
		}

		Type& First()
		{
			return _data[0];
		}

		Type& Last()
		{
			return _data[_length - 1];
		}

	private:
		UINT64 _length;
		Type* _data;
	};
}
