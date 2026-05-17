using System.Runtime.InteropServices;

namespace EFI.Protocols.IO.Peripheral;

[StructLayout(LayoutKind.Sequential)]
public struct SimplePointerState
{
    public int RelativeMovementX;
    public int RelativeMovementY;
    public int RelativeMovementZ;
    public bool LeftButton;
    public bool RightButton;
}
