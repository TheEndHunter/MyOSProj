#include "CRT_Stubs.h"
// Mark this TU as the CRT stubs implementation so it may define anchors
#define CRT_STUBS_TU

// We implement explicit CRT init/term handling in this translation unit.
// Other modules should use CRT_ALLOCATE to place constructors/destructors
// Uunsigned into the proper sections.

// Minimal freestanding implementation of atexit/exit without using the
// C++ standard library (STL). Suitable for UEFI / freestanding environments.

// Forward-declare CRT termination function (defined in Bootloader/CRT_ENTRIES.cpp)
extern "C" void _CRT_TERM(void);

extern "C"
{
    // Platform exit handler can be registered by the bootloader to perform
    // environment-specific termination (UEFI exit, reset, etc.).
    static void (*_platform_exit_handler)(int) = nullptr;

    // Simple fixed-capacity storage for registered handlers to avoid dynamic
    // allocations and any dependency on the C++ runtime.
    static const int __ATEXIT_MAX = 256;
    static void (CDECL* __atexit_handlers[256])(void) = { 0 };
    static int __atexit_count = 0;
    static int __exit_code = 0;

    // Register a function to be called on exit. Returns 0 on success, non-zero on failure.
    int CDECL atexit(void (CDECL* func)(void))
    {
        if (func == nullptr)
        {
            return 1; // failure
        }
        if (__atexit_count >= __ATEXIT_MAX)
        {
            return 1; // capacity exhausted
        }
        __atexit_handlers[__atexit_count++] = func;
        return 0; // success
    }

    // Run registered handlers in reverse order (as required by the C runtime)
    static void __run_atexit_handlers()
    {
        while (__atexit_count > 0)
        {
            --__atexit_count;
            void (CDECL * fn)(void) = __atexit_handlers[__atexit_count];
            if (fn != nullptr)
            {
                fn();
            }
            __atexit_handlers[__atexit_count] = nullptr;
        }
    }

    // exit: store status, run handlers, call CRT termination, and invoke
    // platform exit if provided. In freestanding environments this function
    // should not attempt to return control to an OS; the platform handler
    // should perform system reset/shutdown. If none is provided, exit simply
    // returns after running handlers and CRT terminators.
    void CDECL exit(int status)
    {
        __exit_code = status;
        __run_atexit_handlers();
        // Run CRT terminators (static destructors)
        _CRT_TERM();

        if (_platform_exit_handler)
        {
            _platform_exit_handler(status);
        }

        // Otherwise, return to caller. Caller is expected to handle the stored
        // exit code appropriately in freestanding/UEFI flows.
    }

    void SetPlatformExitHandler(void (*handler)(int))
    {
        _platform_exit_handler = handler;
    }

    int GetExitCode()
    {
        return __exit_code;
    }
}

// Convenience wrappers
extern "C" {
	void CRT_Initialize(void)
	{
		// Call CRT initializers provided by the linker/sections
		_CRT_INIT();

		// Register CRT terminator to run on normal exit
		atexit(_CRT_TERM);
	}

	void CRT_Terminate(void)
	{
		// Manually run terminators
		_CRT_TERM();
	}
}

// Provide CRT initialization/termination arrays and functions here so that
// the same library that provides atexit/exit also supplies _CRT_INIT/_CRT_TERM.
#if defined(_MSC_VER)
// Define the sections for initializers and terminators
#pragma section(".CRT$XCA", long, read)
#pragma section(".CRT$XCZ", long, read)
#pragma section(".CRT$XIA", long, read)
#pragma section(".CRT$XIZ", long, read)
#pragma section(".CRT$XPA", long, read)
#pragma section(".CRT$XPZ", long, read)
#pragma section(".CRT$XTA", long, read)
#pragma section(".CRT$XTZ", long, read)

extern "C"
{
	typedef void(CDECL* _PVFV)();
    // Define the anchor arrays in this TU only
    // Allow multiple definitions across static libs to coalesce when linking
    // by marking these anchor objects as selectany/weak. This avoids link
    // errors when LibCommon and Bootloader both provide the CRT TU.
#if defined(_MSC_VER)
    __declspec(selectany) __declspec(allocate(".CRT$XCA")) _PVFV __xc_a[] = { nullptr };
    __declspec(selectany) __declspec(allocate(".CRT$XCZ")) _PVFV __xc_z[] = { nullptr };
    __declspec(selectany) __declspec(allocate(".CRT$XIA")) _PVFV __xi_a[] = { nullptr };
    __declspec(selectany) __declspec(allocate(".CRT$XIZ")) _PVFV __xi_z[] = { nullptr };
    __declspec(selectany) __declspec(allocate(".CRT$XPA")) _PVFV __xp_a[] = { nullptr };
    __declspec(selectany) __declspec(allocate(".CRT$XPZ")) _PVFV __xp_z[] = { nullptr };
    __declspec(selectany) __declspec(allocate(".CRT$XTA")) _PVFV __xt_a[] = { nullptr };
    __declspec(selectany) __declspec(allocate(".CRT$XTZ")) _PVFV __xt_z[] = { nullptr };
#else
    __attribute__((weak)) _PVFV __xc_a[] __attribute__((section(".CRT$XCA"))) = { nullptr };
    __attribute__((weak)) _PVFV __xc_z[] __attribute__((section(".CRT$XCZ"))) = { nullptr };
    __attribute__((weak)) _PVFV __xi_a[] __attribute__((section(".CRT$XIA"))) = { nullptr };
    __attribute__((weak)) _PVFV __xi_z[] __attribute__((section(".CRT$XIZ"))) = { nullptr };
    __attribute__((weak)) _PVFV __xp_a[] __attribute__((section(".CRT$XPA"))) = { nullptr };
    __attribute__((weak)) _PVFV __xp_z[] __attribute__((section(".CRT$XPZ"))) = { nullptr };
    __attribute__((weak)) _PVFV __xt_a[] __attribute__((section(".CRT$XTA"))) = { nullptr };
    __attribute__((weak)) _PVFV __xt_z[] __attribute__((section(".CRT$XTZ"))) = { nullptr };
#endif
	void _CRT_INIT() {
		// Run C++ and C initializers (match non-MSVC ordering)
		for (_PVFV* func = __xi_a; func != __xi_z; ++func) {
			if (*func != nullptr) {
				(*func)();
			}
		}
		for (_PVFV* func = __xc_a; func != __xc_z; ++func) {
			if (*func != nullptr) {
				(*func)();
			}
		}
	}

	void _CRT_TERM() {
		// Run pre-terminators and terminators
		for (_PVFV* func = __xp_a; func != __xp_z; ++func) {
			if (*func != nullptr) {
				(*func)();
			}
		}
		for (_PVFV* func = __xt_a; func != __xt_z; ++func) {
			if (*func != nullptr) {
				(*func)();
			}
		}
	}

	// MSVC-compatible helpers for initializing ranges of function poUunsigned inters
	void _initterm(void(**start)(void), void(**end)(void)) {
		while (start < end) {
			if (*start != nullptr) {
				(**start)();
			}
			++start;
		}
	}

	unsigned int _initterm_e(void(**start)(void), void(**end)(void)) {
		// Freestanding: no exception handling, execute initializers and return 0
		_initterm(start, end);
		return 0;
	}
}

#else
extern "C"
{
    // Define anchor arrays for non-MSVC toolchains (weak symbols not necessary
    // since this TU is the unique definition).
    void (*__xc_a[])(void) = { nullptr };
    void (*__xc_z[])(void) = { nullptr };
    void (*__xi_a[])(void) = { nullptr };
    void (*__xi_z[])(void) = { nullptr };
    void (*__xp_a[])(void) = { nullptr };
    void (*__xp_z[])(void) = { nullptr };
    void (*__xt_a[])(void) = { nullptr };
    void (*__xt_z[])(void) = { nullptr };

    // In non-MSVC freestanding builds we don't expect C++ exceptions.
    // Provide simple stubs for the MSVC-compatible helpers that call the
    // init ranges if present.
    void _initterm(void(**start)(void), void(**end)(void)) {
        while (start < end) {
            if (*start != nullptr) {
                (**start)();
            }
            ++start;
        }
    }

    unsigned int _initterm_e(void(**start)(void), void(**end)(void)) {
        _initterm(start, end);
        return 0;
    }

    void _CRT_INIT() {
        _initterm(__xi_a, __xi_z);
        _initterm(__xc_a, __xc_z);
    }

    void _CRT_TERM() {
        _initterm(__xp_a, __xp_z);
        _initterm(__xt_a, __xt_z);
    }
}
#endif

// Link-time guard symbol to detect accidental multiple definitions of CRT
// anchors. This symbol is defined here once; if another TU defines the
// anchors and also defines this symbol, the linker will report a duplicate
// symbol error which helps catch incorrect anchor definitions.
unsigned int __CRT_ANCHORS_DEFINED = 1;

// A simple undecorated sentinel symbol to force this TU unsigned int the final
// link when requested via /INCLUDE:CRT_STUBS_SENTINEL. Do NOT use dll
// exports here because the EFI subsystem does not support import libs.
extern "C" void CRT_STUBS_SENTINEL(void) { }
