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
* define declarations for UINTN and a INTN based on the ptr size of the compiler
*/
#if defined(BITS_32)
#if !defined(UINTN)
#define UINTN unsigned long int
#endif
#if !defined(INTN)
#define INTN long int
#endif
#elif defined(BITS_64)
#if !defined(UINTN)
#define UINTN unsigned long long int
#endif
#if !defined(INTN)
#define INTN long long int
#endif
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
#define CHAR8 char

#if defined(__cpp_unicode_characters)
#define CHAR16 char16_t
#elif defined(_NATIVE_WCHAR_T_DEFINED)
#define CHAR16 wchar_t
#else
#define CHAR16 INT16
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
#elif defined(__GNUC__) & defined(__int128)
#define UNICODE
#define UINT128 unsigned __int128
#define INT128 __int128
#else
#endif



/*
*  Per compiler definitions for dllexport and dllimport with switch for detecting static imports
*/

#if defined(_MSC_VER)
#if defined(StaticLibrary)
#define DllExport __declspec(dllexport)
#define DllImport __declspec(dllimport)
#elif defined(DynamicLibrary)
#define DllImport
#define DllExport
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





