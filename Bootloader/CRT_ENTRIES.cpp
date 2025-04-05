#include <CRT_ENTRIES.h>

#ifdef  _MSC_VER
// Define the sections for initializers and terminators
#pragma section(".CRT$XCA", long, read)
#pragma section(".CRT$XCZ", long, read)
#pragma section(".CRT$XTA", long, read)
#pragma section(".CRT$XTZ", long, read)

extern "C"
{
    typedef void(__cdecl* _PVFV)();
// Place the pointers in the correct sections
__declspec(allocate(".CRT$XCA")) _PVFV __xc_a[] = { nullptr };
__declspec(allocate(".CRT$XCZ")) _PVFV __xc_z[] = { nullptr };
__declspec(allocate(".CRT$XTA")) _PVFV __xt_a[] = { nullptr };
__declspec(allocate(".CRT$XTZ")) _PVFV __xt_z[] = { nullptr };

    // Function to call all static initializers
    void _CRT_INIT() {
        for (_PVFV* func = __xc_a; func != __xc_z; ++func) {
            if (*func != nullptr) {
                (*func)();
            }
        }
    }

    // Function to call all static terminators
    void _CRT_TERM() {
        for (_PVFV* func = __xt_a; func != __xt_z; ++func) {
            if (*func != nullptr) {
                (*func)();
            }
        }
    }
}

#else
// Declare the arrays for initializers and terminators

extern "C"
{
    // Define function pointers for CRT initializers and finalizers
    void (*__xc_a[])(void) = { nullptr };
    void (*__xc_z[])(void) = { nullptr };
    void (*__xi_a[])(void) = { nullptr };
    void (*__xi_z[])(void) = { nullptr };
    void (*__xp_a[])(void) = { nullptr };
    void (*__xp_z[])(void) = { nullptr };
    void (*__xt_a[])(void) = { nullptr };
    void (*__xt_z[])(void) = { nullptr };

    // Custom initialization function
    void _initterm(void(**start)(void), void(**end)(void)) {
        while (start < end) {
            if (*start != nullptr) {
                (**start)();
            }
            ++start;
        }
    }

    // Custom CRT initialization function
    VOID _CRT_INIT() {
        // Call the initializers
        _initterm(__xi_a, __xi_z); // Initialize C++ constructors
        _initterm(__xc_a, __xc_z); // Initialize C++ static constructors
    }

    // Custom CRT termination function
    VOID _CRT_TERM() {
        // Call the finalizers
        _initterm(__xp_a, __xp_z); // Call C++ static destructors
        _initterm(__xt_a, __xt_z); // Call C++ destructors
    }
}
#endif //  MSVC

