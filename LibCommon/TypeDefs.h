#pragma once

#ifdef WIN32
#define x86
#endif // WIN32


#if defined(ARM) || defined(WIN32)
#define BITS_32
#elif defined(ARM64) || defined(x64)
#define BITS_64
#else
#error "Unknown architecture"
#endif

/*
*  Setup defines for Data Type Sizes Per Processor Bitness based on edk2, switching based on on of the following compilers being used:
* including wide character support
*  MSVC or GNU
*
* make sure that on 32 & 64 bit processors that the size of UINT64 and INT64 are defined as 8 bytes
*/

#define VOID void
#define VOID_PTR void*
#define VOID_PTR_PTR void**
#define PTR_SIZE (UINTN)sizeof(VOID_PTR)
#define CHAR char

#if defined(__cpp_unicode_characters)
#define CHAR8 char8_t
#define CHAR16 char16_t
#define CHAR32 char32_t
#define WCHAR wchar_t
#elif defined(_NATIVE_WCHAR_T_DEFINED)
#define CHAR8 char
#define CHAR16 wchar_t
#define CHAR32 INT32
#define WCHAR wchar_t
#else
#define CHAR8 INT8
#define CHAR16 INT16
#define CHAR16 INT32
#define WCHAR INT16
#endif

#define UINT8 unsigned char
#define UINT16 unsigned short
#define UINT32 unsigned int

#if defined(_MSC_VER)
#if defined(__int64)
#ifndef INT64
#define INT64 __int64
#endif // INT64
#ifndef UINT64
#define UINT64 unsigned __int64
#endif // UINT64
#else
#ifndef INT64
#define INT64 long long int
#endif // INT64
#ifndef UINT64
#define UINT64 unsigned long long int
#endif // UINT64
#endif
#elif defined(__GNUC__)
#ifndef INT64
#define INT64 long long int
#endif // INT64
#ifndef UINT64
#define UINT64 unsigned long long int
#endif // UINT64
#else
#error "Unknown compiler"
#endif


#define INT8 signed char
#define INT16 short
#define INT32 int


#define BOOLEAN bool
#define TRUE true
#define FALSE false

/*
* define declarations for UINTN and a INTN based on the ptr size of the compiler
*/
#if defined(BITS_32)
#if !defined(UINTN)
#define UINTN UINT32
#endif
#if !defined(INTN)
#define INTN INT32
#endif
#elif defined(BITS_64)
#if !defined(UINTN)
#define UINTN UINT64
#endif
#if !defined(INTN)
#define INTN INT64
#endif
#else
#error "Unknown architecture"
#endif


/* Define Alignment Attribute for aligning on byte,word, dword and qword boundaries for each compiler,*/

#if defined(_MSC_VER)
#define ALIGN(x) __declspec(align(x))
#elif defined(__GNUC__)
#define ALIGN(x) __attribute__((aligned(x)))
#else
#error "Unknown compiler"
#endif`



/*
*  Define Sizes for UINT128 and INT128 based for the following Compilers if they have datatypes accessible: MSVC & GCC
*/

#if defined(_MSC_VER)
#if !defined(STRUCT_INT128)
#define  STRUCT_INT128
struct int128
{
	UINT64 Low;
	INT64 High;
};
#define INT128 int128
#endif
#if !defined(STRUCT_UINT128)
#define  STRUCT_UINT128
struct uint128
{
	UINT64 Low;
	UINT64 High;
};
#define UINT128 uint128
#endif
#define MAX_UINT128 0xffffffffffffffffffffffffffffffff
#define MIN_INT128 0x80000000000000000000000000000000
#elif defined(__GNUC__) & defined(__int128)
#define UNICODE
#define UINT128 unsigned __int128
#define INT128 __int128
#else
#define MAX_UINT128 0xffffffffffffffffffffffffffffffff
#define MIN_INT128 0x80000000000000000000000000000000
#endif

/*Defines MAX and MIN values for all UINT and INT Types, including UINTN and INTN based on Bitness of CPU*/

#define MAX_UINT8 0xff
#define MAX_UINT16 0xffff
#define MAX_UINT32 0xffffffff
#define MAX_UINT64 0xffffffffffffffff

#define MAX_INT8 0x7f
#define MAX_INT16 0x7fff
#define MAX_INT32 0x7fffffff
#define MAX_INT64 0x7fffffffffffffff
#define MAX_INT128 0x7fffffffffffffffffffffffffffffff

#define MIN_UINT8 0x00
#define MIN_UINT16 0x0000
#define MIN_UINT32 0x00000000
#define MIN_UINT64 0x0000000000000000
#define MIN_UINT128 0x00000000000000000000000000000000

#define MIN_INT8 0x80
#define MIN_INT16 0x8000
#define MIN_INT32 0x80000000
#define MIN_INT64 0x8000000000000000

#ifdef BITS_32
#define MAX_UINTN MAX_UINT32
#define MAX_INTN MAX_INT32
#define MIN_UINTN MIN_UINT32
#define MIN_INTN MIN_INT32
#elif defined(BITS_64)
#define MAX_UINTN MAX_UINT64
#define MAX_INTN MAX_INT64
#define MIN_UINTN MIN_UINT64
#define MIN_INTN MIN_INT64
#else
#error "Unknown architecture"
#endif


/*
*  Per compiler definitions for dllexport and dllimport with switch for detecting static imports
*/

#if defined(_MSC_VER)
#if defined(StaticLibrary)
#define DllExport __declspec(dllexport)
#define DllImport __declspec(dllimport)
#elif defined(DynamicLibrary)
#define DllImport __declspec(dllimport)
#define DllExport __declspec(dllexport)
#else
#define DllImport 
#define DllExport
#endif
#elif defined(__GNUC__)
#if(_WINDLL)
#define DllExport __attribute__((visibility("default")))
#define DllImport __attribute__((visibility("default")))
#else
#define DllImport
#define DllExport
#endif
#else
#error "Unknown compiler"
#endif

#ifndef StaticLibrary
#ifdef IMPORT_DLL
#define API_DLL DllImport
#else
#define API_DLL DllExport
#endif // IMPORT_DLL
#else
#define API_DLL
#endif // !StaticLibary

/*
*  Setup Calling conventions and attributes for EFIAPI
*/

#if defined(_MSC_VER)
#if defined(x86)
#define EFIAPI  __cdecl
#define EFIAPIV  __cdecl
#endif
#if defined(x64)
#define EFIAPI  __vectorcall
#define EFIAPIV  __vectorcall
#endif

#if defined(ARM) || defined(ARM64)
#define EFIAPI
#define EFIAPIV
#endif

#define VARARGS  __cdecl
#define CDECL  __cdecl
#define STDCALL  __stdcall
#define VECTORCALL  __vectorcall
#define INLINE __inline
#define STATIC static
#define CONST const

#elif defined(__GNUC__)
#if defined(x64)
#define EFIAPI __attribute__((ms_abi))
#define EFIAPIV  __attribute__((ms_abi))
#endif
#if defined(x86)
#define EFIAPI __attribute__((cdecl))
#define EFIAPIV  __attribute__((cdecl))
#endif
#if defined(ARM) || defined(ARM64)
#define EFIAPI
#define EFIAPIV
#endif
#define VARARGS  __attribute__((cdecl))
#define CDECL  __attribute__((cdecl))
#define STDCALL  __attribute__((stdcall))
#define VECTORCALL  __attribute__((ms_abi))

#if defined(BITS_32)
#define INLINE __inline__
#elif defined(BITS_64)
#define INLINE inline
#endif

#define STATIC static
#define CONST const

#else
#error "Unknown compiler"
#endif

/*
* IN/OUT /INOUT macros for function parameters
*/

#define IN
#define OUT
#define INOUT
#define OPTIONAL

/*
*  define a NORETURN attribute for functions that do not return for the following compilers: MSVC & GCC
*/

#if defined(_MSC_VER)
#define NORETURN __declspec(noreturn)

#elif defined(__GNUC__)
#define NORETURN __attribute__((noreturn))
#else
#error "Unknown compiler"
#endif

/*
* define an ALLOCATE attribute for marking functions as constructors for the following compilers: MSVC & GCC
*/

#if defined(_MSC_VER)
#define ALLOCATE(x) __declspec(allocate(x))
#elif defined(__GNUC__)
#define ALLOCATE(x) __attribute__((section(x)))
#else
#error "Unknown compiler"
#endif

