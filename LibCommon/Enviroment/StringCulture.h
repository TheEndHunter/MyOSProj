#pragma once
#include "TypeDefs.h"

namespace Common::Enviroment
{
	enum StringCulture
	{
		//sensitive sort rules and the current culture.
		CurrentCulture = 0,
		//sensitive sort rules, the current culture, and ignoring the case of the strings being compared.
		CurrentCultureIgnoreCase = 1,
		//sensitive sort rules and the invariant culture.
		InvariantCulture = 2,
		//sensitive sort rules, the invariant culture, and ignoring the case of the strings being compared.
		InvariantCultureIgnoreCase = 3,
		//binary sort rules.
		Ordinal = 4,
		//binary sort rules and ignoring the case of the strings being compared.
		OrdinalIgnoreCase = 5,
	};
}
