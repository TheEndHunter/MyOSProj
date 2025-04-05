#pragma once
#include <TypeDefs.h>

extern "C" {

    // Custom CRT initialization function
    VOID _CRT_INIT();

    // Custom CRT termination function
    void _CRT_TERM();
};
