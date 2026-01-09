#pragma once
#include <TypeDefs.h>

extern "C" {
    // Called to run static initializers
    void _CRT_INIT(void);

    // Called to run static terminators
    void _CRT_TERM(void);
}
