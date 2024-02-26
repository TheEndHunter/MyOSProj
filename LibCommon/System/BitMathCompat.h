#pragma once

#include <TypeDefs.h>

/*
*  Add overrides for math functions to work on 64 bit numbers on 32 bit systems
*  all the function  that are overriden are in the std namespace, but we don't
*  have access to std Libraries
*/

#if defined(BITS_32)

INT64 __alldiv(INT64 a, INT64 b)
{

}



#endif


