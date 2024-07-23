#pragma once
#include <TypeDefs.h>
#include <Numerics/NumberBase.h>

namespace Common::Numerics
{
	template<typename Type>
		requires NumberBase<Type>
	struct Vect2D;

	template<typename Type>
		requires NumberBase<Type>
	struct Vect3D;

	template<typename Type>
		requires NumberBase<Type>
	struct Vect4D;

	template<typename Type>
		requires NumberBase<Type>
	struct Vect2D
	{
	public:
		Type X;
		Type Y;

		Vect2D()
		{
			X = Type{};
			Y = Type{};
		}

		Vect2D(Type x, Type y)
		{
			X = x;
			Y = y;
		}

		operator Vect4D<Type>();

		operator Vect3D<Type>();
	};

	template<typename Type>
		requires NumberBase<Type>
	struct Vect3D
	{
	public:
		Type X;
		Type Y;
		Type Z;

		Vect3D()
		{
			X = Type{};
			Y = Type{};
			Z = Type{};
		}

		Vect3D(Type x, Type y, Type z)
		{
			X = x;
			Y = y;
			Z = z;
		}

		operator Vect2D<Type>();

		operator Vect4D<Type>();
	};

	template<typename Type>
		requires NumberBase<Type>
	struct Vect4D
	{
	public:
		Type X;
		Type Y;
		Type Z;
		Type W;

		Vect4D()
		{
			X = Type{};
			Y = Type{};
			Z = Type{};
			W = Type{};

		}

		Vect4D(Type x, Type y, Type z, Type w)
		{
			X = x;
			Y = y;
			Z = z;
			W = w;
		}

		operator Vect2D<Type>();

		operator Vect3D<Type>();
	};
}