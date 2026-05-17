using System;

// Core UEFI type aliases to help the converted headers compile and be explicit about sizes.
// These are simple C# using-aliases that mirror the C typedefs used across the converted code.
// Keep this file minimal: it provides aliases and a small constants holder.

using UINT8 = System.Byte;
using UINT16 = System.UInt16;
using UINT32 = System.UInt32;
using UINT64 = System.UInt64;

using INT8 = System.SByte;
using INT16 = System.Int16;
using INT32 = System.Int32;
using INT64 = System.Int64;

using UINTN = System.UIntPtr;
using INTN = System.IntPtr;

using CHAR16 = System.Char; // UTF-16 code unit
using CHAR8 = System.Byte;  // raw 8-bit character / UTF-8 byte

using BOOLEAN = System.Boolean;

namespace EFI;

public static partial class EFIConsts
{
    // Max/min helpers mirroring UEFI definitions where useful in C# code.
    public const ulong MAX_UINT64 = UInt64.MaxValue;
    public const long MAX_INT64 = Int64.MaxValue;
}
