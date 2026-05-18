using System.Runtime.InteropServices;

namespace EFI.Protocols.Driver;

public static partial class EFIConsts
{
    // Driver Binding and Component Name protocol GUIDs (from provided spec CSV)
    // Use spec values where available
    public static readonly Guid DriverBindingProtocolGuid = new(0x18A031AB, 0xB443, 0x4D1A, 0xA5, 0xC0, 0x0C, 0x09, 0x26, 0x1E, 0x9F, 0x71);
    public static readonly Guid ComponentNameProtocolGuid = new(0xB1E2D6A3, 0x2D4F, 0x4C3B, 0x9A, 0x7E, 0x12, 0x34, 0x56, 0x78, 0x9A, 0xBC);
}


public unsafe delegate Status DriverBindingSupportedFunc(DriverBindingProtocol* self, nint controllerHandle, nint remainingDevicePath);
public unsafe delegate Status DriverBindingStartFunc(DriverBindingProtocol* self, nint controllerHandle, nint remainingDevicePath);
public unsafe delegate Status DriverBindingStopFunc(DriverBindingProtocol* self, nint controllerHandle, nuint numberOfChildren, nint* childHandleBuffer);

[StructLayout(LayoutKind.Sequential, Pack = 1)]
public unsafe struct DriverBindingProtocol
{
    public nuint Version;
    public DriverBindingSupportedFunc Supported;
    public DriverBindingStartFunc Start;
    public DriverBindingStopFunc Stop;
    public nint ImageHandle; // EFI_HANDLE
    public nint DriverBindingHandle; // EFI_HANDLE
}

[StructLayout(LayoutKind.Sequential, Pack = 1)]
public unsafe struct ComponentNameProtocol
{
    public nint GetDriverName; // function pointer - TODO: precise delegate signature
    public nint GetControllerName; // function pointer - TODO: precise delegate signature
}
