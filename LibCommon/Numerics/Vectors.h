#pragma once
#include <TypeDefs.h>
#include <Numerics/NumberBase.h>

namespace Common::Numerics
{
	template<typename Type>
		requires NumberBase<Type>
	struct Vect2D
	{
		Vect2D()
		{
			X = Type::Zero;
			Y = Type::Zero;
		}

		Vect2D(Type x, Type y)
		{
			X = x;
			Y = y;
		}

		Type X;
		Type Y;
	};

	template<typename Type>
		requires NumberBase<Type>
	struct Vect3D
	{
		Vect3D()
		{
			X = Type::Zero;
			Y = Type::Zero;
			Z = Type::Zero;
		}

		Vect3D(Type x, Type y, Type z)
		{
			X = x;
			Y = y;
			Z = z;
		}

		Type X;
		Type Y;
		Type Z;
	};

	template<typename Type>
		requires NumberBase<Type>
	struct Vect4D
	{
		Vect4D()
		{
			X = Type::Zero;
			Y = Type::Zero;
			Z = Type::Zero;
			W = Type::Zero;
		}

		Vect4D(Type x, Type y, Type z, Type w)
		{
			X = x;
			Y = y;
			Z = z;
			W = w;
		}

		Type X;
		Type Y;
		Type Z;
		Type W;
	};

}