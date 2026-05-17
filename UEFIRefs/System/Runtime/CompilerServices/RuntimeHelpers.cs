using System;

namespace System.Runtime.CompilerServices
{
    // Consolidated RuntimeHelpers used as compile-time facade.
    public static class RuntimeHelpers
    {
        public static void InitializeArray(System.Array array, System.RuntimeFieldHandle fldHandle) => throw null;
        public static void PrepareDelegate(System.Delegate d) => throw null;

        // Ensures the static constructor for the given type has been run.
        public static void RunClassConstructor(System.RuntimeTypeHandle type) => throw null;

        // Prepares a method (JIT/readying) - present in corelib as an intrinsic.
        public static void PrepareMethod(System.RuntimeMethodHandle method) => throw null;

        // Returns an instance of the specified type without running constructors.
        public static object GetUninitializedObject(System.Type type) => throw null;

        // Returns the hashcode for an object (intrinsic in some runtimes).
        public static int GetHashCode(object o) => throw null;

        // Ensures there is sufficient execution stack for recursion; intrinsic on some runtimes.
        public static bool TryEnsureSufficientExecutionStack() => throw null;

        // Low-level helper that the compiler or runtime may call for guaranteed cleanup patterns.
        public static void ExecuteCodeWithGuaranteedCleanup(Action tryCode, Action<object, bool> cleanupCode, object userData) => throw null;
    }

    // Note: RawCalliHelper moved to its own file RawCalliHelper.cs
}
