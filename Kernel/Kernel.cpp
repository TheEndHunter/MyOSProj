// Kernel.cpp : This file contains the 'EfiMain' function. Program execution begins and ends there.
//
#include "TypeDefs.h"
#include <Graphics/GraphicsContext.h>

namespace kernel
{
    using namespace Common::Graphics;

     UINTN CDECL KrnlMain(GraphicsContext* context)
    {
        return 123;
    }
}
