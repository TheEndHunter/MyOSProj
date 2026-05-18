using System.Runtime.InteropServices;

namespace EFI.Services;

[StructLayout(LayoutKind.Sequential, Pack = 1)]
public unsafe struct SystemTable
{
    public TableHeader Hdr;
    public char* FirmwareVendor; // CHAR16*, caller handles encoding
    public uint FirmwareRevision;

    public nint ConsoleInHandle; // Handle
    public nint ConIn;           // SimpleTextInputProtocol*

    public nint ConsoleOutHandle; // Handle
    public nint ConOut;           // SimpleTextOutputProtocol*

    public nint StandardErrorHandle; // Handle
    public nint StdErr;              // SimpleTextOutputProtocol*

    public RuntimeServices* RuntimeServices;
    public BootServices* BootServices;

    public nuint NumberOfTableEntries;
    public nint ConfigurationTable; // Efi::ConfigurationTable*
}
