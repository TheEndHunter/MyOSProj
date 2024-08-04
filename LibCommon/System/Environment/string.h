#pragma once
#include <TypeDefs.h>
#include <System/Array.h>
#include <System/Environment/IsChar.h>

namespace Common::System::Environment
{
	template<IsChar Type>
	class string
	{
	public:
		string(const UINT64 length = 0);

		string(const Array<Type> arr);

		string(const Type* ptr);

		string(const Type& str);

		string(const Type* ptr, UINT64 length);

		string(const Type& str, UINT64 length);

		string(const string<Type>& other);

		~string();

		UINT64 Length()
		{
			return _length;
		}

		Type& operator[](UINT64 index)
		{
			return _data[index];
		}

		bool operator ==(const string<Type>& right)
		{
			if (_length != right._length)
				return false;

			for (UINT64 i = 0; i < _length; i++)
			{
				if (_data[i] != right._data[i])
					return false;
			}

			return true;
		}

		bool operator !=(const string<Type>& right)
		{
			if (_length != right._length)
				return true;

			for (UINT64 i = 0; i < _length; i++)
			{
				if (_data[i] != right._data[i])
					return true;
			}

			return false;
		}

		string<Type> operator +(const string<Type>& right)
		{
			UINT64 newLen = _length + right._length;
			Type* newData = new Type[newLen];
			for (UINT64 i = 0; i < _length; i++)
			{
				newData[i] = _data[i];
			}

			for (UINT64 i = 0; i < right._length; i++)
			{
				newData[_length + i] = right._data[i];
			}

			return string<Type>(newData);
		}

		string<Type> operator +(const Type* right)
		{
			UINT64 rLen = 0;
			while (right[rLen] != 0)
			{
				rLen++;
			}

			UINT64 newLen = _length + rLen;
			Type* newData = new Type[newLen];
			for (UINT64 i = 0; i < _length; i++)
			{
				newData[i] = _data[i];
			}

			for (UINT64 i = 0; i < rLen; i++)
			{
				newData[_length + i] = right[i];
			}

			return string<Type>(newData);
		}

		string<Type> operator +(const Type right)
		{
			UINT64 newLen = _length + 1;
			Type* newData = new Type[newLen];
			for (UINT64 i = 0; i < _length; i++)
			{
				newData[i] = _data[i];
			}

			newData[_length] = right;

			return string<Type>(newData);
		}

		Type* AsPointer()
		{
			return _data;
		}
	private:
		UINT64 _length;
		Type* _data;
	};
}

