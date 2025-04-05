#pragma once
#include <TypeDefs.h>
#include <System/Array.h>
#include <System/Environment/IsChar.h>

namespace Common::System::Environment
{
	template<IsChar StrType>
	class string
	{
	public:
		string(const UINT64 length = 0);

		string(const Array<StrType> arr);

		string(const StrType* ptr);

		string(const StrType& str);

		string(const StrType* ptr, UINT64 length);

		string(const StrType& str, UINT64 length);

		string(const string<StrType>& other);

		~string();

		UINT64 Length()
		{
			return _length;
		}

		StrType& operator[](UINT64 index)
		{
			return _data[index];
		}

		BOOLEAN operator ==(const string<StrType>& right)
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

		BOOLEAN operator !=(const string<StrType>& right)
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

		string<StrType> operator +(const string<StrType>& right)
		{
			UINT64 newLen = _length + right._length;
			StrType* newData = new StrType[newLen];
			for (UINT64 i = 0; i < _length; i++)
			{
				newData[i] = _data[i];
			}

			for (UINT64 i = 0; i < right._length; i++)
			{
				newData[_length + i] = right._data[i];
			}

			return string<StrType>(newData);
		}

		string<StrType> operator +(const StrType* right)
		{
			UINT64 rLen = 0;
			while (right[rLen] != 0)
			{
				rLen++;
			}

			UINT64 newLen = _length + rLen;
			StrType* newData = new StrType[newLen];
			for (UINT64 i = 0; i < _length; i++)
			{
				newData[i] = _data[i];
			}

			for (UINT64 i = 0; i < rLen; i++)
			{
				newData[_length + i] = right[i];
			}

			return string<StrType>(newData);
		}

		string<StrType> operator +(const StrType right)
		{
			UINT64 newLen = _length + 1;
			StrType* newData = new StrType[newLen];
			for (UINT64 i = 0; i < _length; i++)
			{
				newData[i] = _data[i];
			}

			newData[_length] = right;

			return string<StrType>(newData);
		}

		StrType* AsPointer()
		{
			return _data;
		}

		const UINT8 CharByteWidth = sizeof(StrType);
	private:
		UINT64 _length;
		StrType* _data;
	};
}

