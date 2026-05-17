#nullable disable
namespace System
{
    // Basic delegate placeholders used for compile-time facades
    public delegate void Action();
    public delegate void Action<T>(T obj);
    public delegate void Action<T1, T2>(T1 a, T2 b);
}
