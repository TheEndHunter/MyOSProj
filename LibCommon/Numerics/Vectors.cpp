#include <Numerics/Vectors.h>

namespace Common::Numerics
{
	template<typename Type>
		requires NumberBase<Type>
	Vect2D<Type>::operator Common::Numerics::Vect3D<Type>()
	{
		return Vect3D<Type>(X, Y, default(Type));
	}

	template<typename Type>
		requires NumberBase<Type>
	Vect2D<Type>::operator Common::Numerics::Vect4D<Type>()
	{
		return Vect4D<Type>(X, Y, default(Type), default(Type));
	}

	template<typename Type>
		requires NumberBase<Type>
	Vect3D<Type>::operator Common::Numerics::Vect2D<Type>()
	{
		return Vect2D<Type>(X, Y);
	}

	template<typename Type>
		requires NumberBase<Type>
	Vect3D<Type>::operator Common::Numerics::Vect4D<Type>()
	{
		return Vect4D<Type>(X, Y, Z, default(Type));
	}

	template<typename Type>
		requires NumberBase<Type>
	Vect4D<Type>::operator Common::Numerics::Vect2D<Type>()
	{
		return Vect2D<Type>(X, Y);
	}

	template<typename Type>
		requires NumberBase<Type>
	Vect4D<Type>::operator Common::Numerics::Vect3D<Type>()
	{
		return Vect3D<Type>(X, Y, Z);
	}
}