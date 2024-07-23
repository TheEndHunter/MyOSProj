#pragma once
#include <TypeDefs.h>
#include <Numerics/NumberBase.h>

namespace Common::Numerics
{
	class Math
	{
	public:
		template<typename SingedType>
			requires SignedNumber<SingedType>
		static SingedType Abs(SingedType num)
		{
			return num >= 0 ? num : -num;
		};

		template<typename SingedType>
			requires SignedNumber<SingedType>
		static SingedType AbsDiff(SingedType a, SingedType b)
		{
			return Abs(a - b);
		};

		template<typename Type>
			requires NumberBase<Type>
		static Type Min(Type a, Type b)
		{
			return a < b ? a : b;
		}
		template<typename Type>
			requires NumberBase<Type>
		static Type Max(Type a, Type b)
		{
			return a > b ? a : b;
		}
		template<typename Type>
			requires NumberBase<Type>
		static Type Clamp(Type value, Type min, Type max)
		{
			return value < min ? min : value > max ? max : value;
		}

		template<typename SingedType>
			requires SignedNumber<SingedType>
		static SingedType Sign(SingedType value)
		{
			return value > 0 ? 1 : value < 0 ? -1 : 0;
		}

		template<typename Type>
			requires NumberBase<Type>
		constexpr static Type Zero = Type(0);
		template<typename Type>
			requires NumberBase<Type>
		constexpr static Type One = Type(1);
		template<typename Type>
			requires SignedNumber<Type>
		constexpr static Type NegativeOne = Type(-1);
	};
}
