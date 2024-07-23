#pragma once

#include <TypeDefs.h>

namespace Common::System
{
	template<typename Type>
	struct Array
	{
	public:

		Array(UINT64 size)
		{
			_size = size;
			_data = new Type[size];
		}

		Array(UINT64 size, Type value)
		{
			_size = size;
			_data = new Type[size];
			for (UINT64 i = 0; i < size; i++)
			{
				_data[i] = value;
			}
		}

		Array(UINT64 size, Type[size] data)
		{
			_size = size;
			_data = new Type[size];
			for (UINT64 i = 0; i < size; i++)
			{
				_data[i] = data[i];
			}
		}

		Array(const Array<Type>& other)
		{
			_size = other._size;
			_data = new Type[_size];
			for (UINT64 i = 0; i < _size; i++)
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
			return _size;
		}

		Type& operator[](UINT64 index)
		{
			return _data[index];
		}

		BOOLEAN Contains(const Type& value)
		{
			for (UINT64 i = 0; i < _size; i++)
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
			return _data[_size - 1];
		}

	private:
		UINT64 _size;
		Type* _data;

	};
}
