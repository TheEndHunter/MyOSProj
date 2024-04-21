#pragma once

#include <TypeDefs.h>

namespace Common::Numerics
{
	template<typename Type>
	concept hasAdditionOperator = requires(Type)
	{
		Type::operator+;
	};

	template<typename Type>
	concept hasSubtractionOperator = requires(Type)
	{
		Type::operator-;
	};

	template<typename Type>
	concept hasMultiplicationOperator = requires(Type)
	{
		Type::operator*;
	};

	template<typename Type>
	concept hasDivisionOperator = requires(Type)
	{
		Type::operator/;
	};

	template<typename Type>
	concept hasModulusOperator = requires(Type)
	{
		Type::operator%;
	};

	template<typename Type>
	concept hasIncrementOperator = requires(Type)
	{
		Type::operator++;
	};

	template<typename Type>
	concept hasDecrementOperator = requires(Type)
	{
		Type::operator--;
	};

	template<typename Type>
	concept hasAdditionAssignmentOperator = requires(Type)
	{
		Type::operator+=;
	};

	template<typename Type>
	concept hasSubtractionAssignmentOperator = requires(Type)
	{
		Type::operator-=;
	};

	template<typename Type>
	concept hasMultiplicationAssignmentOperator = requires(Type)
	{
		Type::operator*=;
	};

	template<typename Type>
	concept hasDivisionAssignmentOperator = requires(Type)
	{
		Type::operator/=;
	};

	template<typename Type>
	concept hasModulusAssignmentOperator = requires(Type)
	{
		Type::operator%=;
	};

	template<typename Type>
	concept hasEqualityOperator = requires(Type)
	{
		Type::operator==;
	};

	template<typename Type>
	concept hasInequalityOperator = requires(Type)
	{
		Type::operator!=;
	};

	template<typename Type>
	concept hasGreaterThanOperator = requires(Type)
	{
		Type::operator>;
	};

	template<typename Type>
	concept hasLessThanOperator = requires(Type)
	{
		Type::operator<;
	};

	template<typename Type>
	concept hasGreaterThanOrEqualOperator = requires(Type)
	{
		Type::operator>=;
	};

	template<typename Type>
	concept hasLessThanOrEqualOperator = requires(Type)
	{
		Type::operator<=;
	};

	template<typename Type>
	concept hasNegationOperator = requires(Type)
	{
		Type::operator!;
	};

	template<typename Type>
	concept hasBitwiseAndOperator = requires(Type)
	{
		Type::operator&;
	};

	template<typename Type>
	concept hasBitwiseOrOperator = requires(Type)
	{
		Type::operator|;
	};

	template<typename Type>
	concept hasBitwiseXorOperator = requires(Type)
	{
		Type::operator^;
	};

	template<typename Type>
	concept hasBitwiseNotOperator = requires(Type)
	{
		Type::operator~;
	};

	template<typename Type>
	concept hasBitwiseAndAssignmentOperator = requires(Type)
	{
		Type::operator&=;
	};

	template<typename Type>
	concept hasBitwiseOrAssignmentOperator = requires(Type)
	{
		Type::operator|=;
	};

	template<typename Type>
	concept hasBitwiseXorAssignmentOperator = requires(Type)
	{
		Type::operator^=;
	};

	template<typename Type>
	concept hasBitwiseLeftShiftOperator = requires(Type)
	{
		Type::operator<<;
	};


	template<typename Type>
	concept hasBitwiseRightShiftOperator = requires(Type)
	{
		Type::operator>>;
	};

	template<typename Type>
	concept hasBitwiseLeftShiftAssignmentOperator = requires(Type)
	{
		Type::operator<<=;
	};

	template<typename Type>
	concept hasBitwiseRightShiftAssignmentOperator = requires(Type)
	{
		Type::operator>>=;
	};

	template<typename Type>
	concept hasLogicalAndOperator = requires(Type)
	{
		Type::operator&&;
	};

	template<typename Type>
	concept hasLogicalOrOperator = requires(Type)
	{
		Type::operator||;
	};

	template<typename Type>
	concept hasLogicalNotOperator = requires(Type)
	{
		Type::operator!;
	};

	template<typename Type>
	concept hasIncrementPrefixOperator = requires(Type)
	{
		Type::operator++;
	};

	template<typename Type>

	concept hasIncrementPostfixOperator = requires(Type)
	{
		Type::operator++;
	};

	template<typename Type>
	concept hasDecrementPrefixOperator = requires(Type)
	{
		Type::operator--;
	};

	template<typename Type>
	concept hasDecrementPostfixOperator = requires(Type)
	{
		Type::operator--;
	};

	template<typename Type>
	concept NumberBase = requires(Type)
	{
		hasAdditionOperator<Type>;
		hasSubtractionOperator<Type>;
		hasMultiplicationOperator<Type>;
		hasDivisionOperator<Type>;
		hasModulusOperator<Type>;
		hasIncrementOperator<Type>;
		hasDecrementOperator<Type>;
		hasAdditionAssignmentOperator<Type>;
		hasSubtractionAssignmentOperator<Type>;
		hasMultiplicationAssignmentOperator<Type>;
		hasDivisionAssignmentOperator<Type>;
		hasModulusAssignmentOperator<Type>;
		hasEqualityOperator<Type>;
		hasInequalityOperator<Type>;
		hasGreaterThanOperator<Type>;
		hasLessThanOperator<Type>;
		hasGreaterThanOrEqualOperator<Type>;
		hasLessThanOrEqualOperator<Type>;
		hasBitwiseAndOperator<Type>;
		hasBitwiseOrOperator<Type>;
		hasBitwiseXorOperator<Type>;
		hasBitwiseNotOperator<Type>;
		hasBitwiseAndAssignmentOperator<Type>;
		hasBitwiseOrAssignmentOperator<Type>;
		hasBitwiseXorAssignmentOperator<Type>;
		hasBitwiseLeftShiftOperator<Type>;
		hasBitwiseRightShiftOperator<Type>;
		hasBitwiseLeftShiftAssignmentOperator<Type>;
		hasBitwiseRightShiftAssignmentOperator<Type>;
		hasLogicalAndOperator<Type>;
		hasLogicalOrOperator<Type>;
		hasLogicalNotOperator<Type>;
		hasIncrementPrefixOperator<Type>;
		hasIncrementPostfixOperator<Type>;
		hasDecrementPrefixOperator<Type>;
		hasDecrementPostfixOperator<Type>;
	};

	template<typename Type>
	concept SignedNumber = NumberBase<Type> && requires(Type a, Type b) {
		{ a + b } -> NumberBase;
		{ a - b } -> NumberBase;
		{ a* b } -> NumberBase;
		{ a / b } -> NumberBase;
		{ -a } -> NumberBase;
			requires((Type(-1) < Type(0))); // Check if T is signed
	};

	template<typename Type>
	concept UnsignedNumber = NumberBase<Type> && requires(Type a, Type b) {
		{ a + b } -> NumberBase;
		{ a - b } -> NumberBase;
		{ a* b } -> NumberBase;
		{ a / b } -> NumberBase;
		{ -a } -> NumberBase;
			requires(!(Type(-1) < Type(0))); // Check if T is unsigned
	};

}
