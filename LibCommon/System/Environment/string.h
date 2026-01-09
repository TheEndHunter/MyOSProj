#pragma once
#include <TypeDefs.h>
#include <System/Array.h>
#include <System/Environment/IsChar.h>
#include <System/MemoryManagement/Allocator.h>

namespace Common::System::Environment
{
	template<IsChar StrType>
	class String
	{
	public:
		String(const UINT64 length = 0)
		{
			_autoInit();
			_length = length;
			if (_length == 0)
			{
				_data = nullptr;
			}
			else
			{
				_data = (StrType*)Common::System::MemoryManagement::Allocator::GetInstance()->AllocateZeroed(sizeof(StrType) * (_length + 1));
				if (_data)
				{
					_data[_length] = (StrType)0;
				}
			}
		}

		String(const Array<StrType> arr)
		{
			_autoInit();
			_length = arr.Length();
			_data = (StrType*)Common::System::MemoryManagement::Allocator::GetInstance()->AllocateZeroed(sizeof(StrType) * (_length + 1));
			if (_data)
			{
				for (UINT64 i = 0; i < _length; i++)
				{
					_data[i] = arr[i];
				}
				_data[_length] = (StrType)0;
			}
		}

		String(const StrType* ptr)
		{
			_autoInit();
			if (ptr == nullptr)
			{
				_length = 0;
				_data = nullptr;
				return;
			}
			_length = 0;
			while (ptr[_length] != (StrType)0) { _length++; }
			_data = (StrType*)Common::System::MemoryManagement::Allocator::GetInstance()->AllocateZeroed(sizeof(StrType) * (_length + 1));
			for (UINT64 i = 0; i < _length; i++) { _data[i] = ptr[i]; }
			_data[_length] = (StrType)0;
		}

		String(const StrType& str)
		{
			_autoInit();
			_length = 1;
			_data = (StrType*)Common::System::MemoryManagement::Allocator::GetInstance()->AllocateZeroed(sizeof(StrType) * (2));
			_data[0] = str;
			_data[1] = (StrType)0;
		}

		String(const StrType* ptr, UINT64 length)
		{
			_autoInit();
			_length = (ptr == nullptr) ? 0 : length;
			_data = (StrType*)Common::System::MemoryManagement::Allocator::GetInstance()->AllocateZeroed(sizeof(StrType) * (_length + 1));
			for (UINT64 i = 0; i < _length; i++) { _data[i] = ptr[i]; }
			_data[_length] = (StrType)0;
		}

		String(const StrType& str, UINT64 length)
		{
			_autoInit();
			_length = length;
			_data = (StrType*)Common::System::MemoryManagement::Allocator::GetInstance()->AllocateZeroed(sizeof(StrType) * (_length + 1));
			for (UINT64 i = 0; i < _length; i++) { _data[i] = str; }
			_data[_length] = (StrType)0;
		}

		String(const String<StrType>& other)
		{
			_autoInit();
			_length = other._length;
			_data = (StrType*)Common::System::MemoryManagement::Allocator::GetInstance()->AllocateZeroed(sizeof(StrType) * (_length + 1));
			for (UINT64 i = 0; i < _length; i++) { _data[i] = other._data[i]; }
			_data[_length] = (StrType)0;
		}

		~String()
		{
			if (_data)
			{
				Common::System::MemoryManagement::Allocator::GetInstance()->Free(_data);
				_data = nullptr;
				_length = 0;
			}
		}

		UINT64 Length()
		{
			return _length;
		}

		StrType& operator[](UINT64 index)
		{
			return _data[index];
		}

		BOOLEAN operator ==(const String<StrType>& right)
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

		BOOLEAN operator !=(const String<StrType>& right)
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

		String<StrType> operator +(const String<StrType>& right)
		{
			UINT64 newLen = _length + right._length;
			StrType* newData = (StrType*)Common::System::MemoryManagement::Allocator::GetInstance()->AllocateZeroed(sizeof(StrType) * (newLen + 1));
			for (UINT64 i = 0; i < _length; i++)
			{
				newData[i] = _data[i];
			}

			for (UINT64 i = 0; i < right._length; i++)
			{
				newData[_length + i] = right._data[i];
			}
			newData[newLen] = (StrType)0;
			return String<StrType>(newData);
		}

		String<StrType> operator +(const StrType* right)
		{
			UINT64 rLen = 0;
			while (right[rLen] != 0)
			{
				rLen++;
			}

			UINT64 newLen = _length + rLen;
			StrType* newData = (StrType*)Common::System::MemoryManagement::Allocator::GetInstance()->AllocateZeroed(sizeof(StrType) * (newLen + 1));
			for (UINT64 i = 0; i < _length; i++)
			{
				newData[i] = _data[i];
			}

			for (UINT64 i = 0; i < rLen; i++)
			{
				newData[_length + i] = right[i];
			}
			newData[newLen] = (StrType)0;
			return String<StrType>(newData);
		}

		String<StrType> operator +(const StrType right)
		{
			UINT64 newLen = _length + 1;
			StrType* newData = (StrType*)Common::System::MemoryManagement::Allocator::GetInstance()->AllocateZeroed(sizeof(StrType) * (newLen + 1));
			for (UINT64 i = 0; i < _length; i++)
			{
				newData[i] = _data[i];
			}

			newData[_length] = right;
			newData[newLen] = (StrType)0;
			return String<StrType>(newData);
		}

		// Append helper (mutating)
		void Append(const StrType* right)
		{
			if (right == nullptr) return;
			UINT64 rLen = 0; while (right[rLen] != (StrType)0) { rLen++; }
			UINT64 newLen = _length + rLen;
			StrType* newData = (StrType*)Common::System::MemoryManagement::Allocator::GetInstance()->AllocateZeroed(sizeof(StrType) * (newLen + 1));
			for (UINT64 i = 0; i < _length; i++) newData[i] = _data[i];
			for (UINT64 i = 0; i < rLen; i++) newData[_length + i] = right[i];
			newData[newLen] = (StrType)0;
			Common::System::MemoryManagement::Allocator::GetInstance()->Free(_data);
			_data = newData; _length = newLen;
		}

		void Clear()
		{
			if (_data)
			{
				Common::System::MemoryManagement::Allocator::GetInstance()->Free(_data);
				_data = nullptr; _length = 0;
			}
		}

		StrType* AsPointer()
		{
			return _data;
		}

		const UINT8 CharByteWidth = sizeof(StrType);
	private:
		inline void _autoInit()
		{
			if (Common::System::MemoryManagement::Allocator::GetInstance() == nullptr)
			{
				// leave _data nullptr; caller must set allocator before using string
			}
		}
		UINT64 _length;
		StrType* _data;
	};
}

