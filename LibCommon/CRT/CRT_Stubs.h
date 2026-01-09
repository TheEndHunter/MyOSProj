#pragma once
#include <TypeDefs.h>

// Public freestanding CRT API used by bootloader and kernel. Use standard
// C signatures to avoid conflicts with compiler-provided declarations.
extern "C" {
    int CDECL atexit(void (CDECL* func)(void));
    void CDECL exit(int status);
    void SetPlatformExitHandler(void (*handler)(int));
    int GetExitCode(void);

    void _CRT_INIT(void);
    void _CRT_TERM(void);

    void CRT_Initialize(void);
    void CRT_Terminate(void);
}

// MSVC-compatible init helpers
extern "C" {
    void _initterm(void (**start)(void), void (**end)(void));
    unsigned int _initterm_e(void (**start)(void), void (**end)(void));
}

// Macro to place objects into a specific section so they are picked up by
// the CRT init/term iterators. Works for MSVC and GCC/Clang.
#if defined(_MSC_VER)
#define CRT_ALLOCATE(section) __declspec(allocate(section))
#elif defined(__GNUC__)
#define CRT_ALLOCATE(section) __attribute__((section(section)))
#else
#define CRT_ALLOCATE(section)
#endif

// Prevent accidental definition of anchors in other TUs. Only CRT_Stubs.cpp
// may define the anchor arrays and the guard symbol.
#if defined(CRT_ANCHORS_DEFINE) && !defined(CRT_STUBS_TU)
#error "CRT_ANCHORS_DEFINE may only be defined in CRT_Stubs.cpp (define CRT_STUBS_TU there)"
#endif

// Extern declarations for section anchor arrays so other modules can reference
// them without defining them. These are defined in CRT_Stubs.cpp.
extern "C" {
    extern void (*__xc_a[])(void);
    extern void (*__xc_z[])(void);
    extern void (*__xi_a[])(void);
    extern void (*__xi_z[])(void);
    extern void (*__xp_a[])(void);
    extern void (*__xp_z[])(void);
    extern void (*__xt_a[])(void);
    extern void (*__xt_z[])(void);

    extern unsigned int __CRT_ANCHORS_DEFINED;
}

#if defined(_MSC_VER)
// Force-link the TU that defines the CRT anchors so the linker sees the
// anchor definitions and stops warning about unhandled .CRT sections.
#if defined(_M_IX86)
#pragma comment(linker, "/include:___CRT_ANCHORS_DEFINED")
#else
#pragma comment(linker, "/include:__CRT_ANCHORS_DEFINED")
#endif

// Also force-link the standard CRT section anchor symbols and the sentinel.
#if defined(_M_IX86)
#pragma comment(linker, "/include:___xc_a")
#pragma comment(linker, "/include:___xc_z")
#pragma comment(linker, "/include:___xi_a")
#pragma comment(linker, "/include:___xi_z")
#pragma comment(linker, "/include:___xp_a")
#pragma comment(linker, "/include:___xp_z")
#pragma comment(linker, "/include:___xt_a")
#pragma comment(linker, "/include:___xt_z")
#pragma comment(linker, "/include:___CRT_STUBS_SENTINEL")
#else
#pragma comment(linker, "/include:__xc_a")
#pragma comment(linker, "/include:__xc_z")
#pragma comment(linker, "/include:__xi_a")
#pragma comment(linker, "/include:__xi_z")
#pragma comment(linker, "/include:__xp_a")
#pragma comment(linker, "/include:__xp_z")
#pragma comment(linker, "/include:__xt_a")
#pragma comment(linker, "/include:__xt_z")
#pragma comment(linker, "/include:CRT_STUBS_SENTINEL")
#endif
#endif

// Notes:
// - Only one TU (LibCommon/CRT/CRT_Stubs.cpp) should define the anchor
//   arrays and the guard symbol. Other TUs should include this header to
//   reference them.
// - Use `CRT_ALLOCATE(".CRT$XCU")` to place constructor pointers into the
//   proper MSVC subsection.
