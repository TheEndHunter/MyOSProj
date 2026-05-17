using System.Runtime.InteropServices;

namespace EFI;

public static partial class EFIConsts
{
    // Event types (can be ORed together)
    public const uint EVT_TIMER = 0x80000000;
    public const uint EVT_RUNTIME = 0x40000000;
    public const uint EVT_NOTIFY_WAIT = 0x00000100;
    public const uint EVT_NOTIFY_SIGNAL = 0x00000200;
    public const uint EVT_SIGNAL_EXIT_BOOT_SERVICES = 0x00000201;
    public const uint EVT_SIGNAL_VIRTUAL_ADDRESS_CHANGE = 0x60000202;
}

// Represents EFI Event handle (VOID_PTR)
[StructLayout(LayoutKind.Sequential)]
public readonly struct Event
{
    public readonly nint Value;

    public Event(nint value)
    {
        Value = value;
    }
}
