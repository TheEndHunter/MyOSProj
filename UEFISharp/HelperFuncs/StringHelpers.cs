using System;
using System.Runtime.InteropServices;

namespace EFI.HelperFuncs;

public static unsafe class StringHelpers
{
    // Minimal P/Invoke-style helpers signatures mirroring the native ones; implementations are not required
    // for header mapping but adding stubs eases usage from managed code.
    public static bool CompareStringLengths(byte* left, byte* right, ulong* lLen, ulong* rLen)
    {
        if (lLen is null || rLen is null) throw new ArgumentNullException();
        ulong a = 0, b = 0;
        if (left != null)
        {
            byte* p = left;
            while (*p != 0)
            {
                a++;
                p++;
            }
        }

        if (right != null)
        {
            byte* p = right;
            while (*p != 0)
            {
                b++;
                p++;
            }
        }

        *lLen = a;
        *rLen = b;
        return a == b;
    }

    public static bool CompareStringLengths(char* left, char* right, ulong* lLen, ulong* rLen)
    {
        if (lLen is null || rLen is null) throw new ArgumentNullException();
        ulong a = 0, b = 0;
        if (left != null)
        {
            char* p = left;
            while (*p != '\0')
            {
                a++;
                p++;
            }
        }

        if (right != null)
        {
            char* p = right;
            while (*p != '\0')
            {
                b++;
                p++;
            }
        }

        *lLen = a;
        *rLen = b;
        return a == b;
    }

    public static bool CompareStringLengths(sbyte* left, sbyte* right, ulong* lLen, ulong* rLen)
    {
        if (lLen is null || rLen is null) throw new ArgumentNullException();
        ulong a = 0, b = 0;
        if (left != null)
        {
            sbyte* p = left;
            while (*p != 0)
            {
                a++;
                p++;
            }
        }

        if (right != null)
        {
            sbyte* p = right;
            while (*p != 0)
            {
                b++;
                p++;
            }
        }

        *lLen = a;
        *rLen = b;
        return a == b;
    }

    public static bool CompareStrings(byte* left, byte* right)
    {
        if (left == right) return true;
        if (left == null || right == null) return false;

        byte* a = left;
        byte* b = right;
        while (*a != 0 && *b != 0)
        {
            if (*a != *b) return false;
            a++; b++;
        }

        return *a == *b; // both zero => equal
    }

    public static bool CompareStrings(char* left, char* right)
    {
        if (left == right) return true;
        if (left == null || right == null) return false;

        char* a = left;
        char* b = right;
        while (*a != '\0' && *b != '\0')
        {
            if (*a != *b) return false;
            a++; b++;
        }

        return *a == *b;
    }

    public static bool CompareStrings(sbyte* left, sbyte* right)
    {
        if (left == right) return true;
        if (left == null || right == null) return false;

        sbyte* a = left;
        sbyte* b = right;
        while (*a != 0 && *b != 0)
        {
            if (*a != *b) return false;
            a++; b++;
        }

        return *a == *b;
    }
}
