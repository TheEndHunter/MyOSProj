#pragma once

#include <TypeDefs.h>

namespace Common::System
{
	template<typename T>
	struct Optional
	{
	private:
		BOOLEAN hasValue;
		T value;
	public:
		Optional() : hasValue(FALSE), value() {}
		Optional(const T& val) : hasValue(TRUE), value(val) {}
		BOOLEAN HasValue() const
		{
			return hasValue;
		}
		T GetValue() const
		{
			if (!hasValue)
			{
				// Handle the case where there is no value.
				// This could throw an exception or handle it in another way.
				// For simplicity, we'll just return a default-constructed T.
				return T();
			}
			return value;
		}
		void SetValue(const T& val)
		{
			value = val;
			hasValue = TRUE;
		}
		void Clear()
		{
			hasValue = FALSE;
			value = T();
		}
	};
}