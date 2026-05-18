using System.Runtime.InteropServices;

namespace EFI.Protocols.Network;


// HTTP protocol delegates and struct (simplified)
public unsafe delegate Status HttpGetModeDataFunc(void* self, void* httpConfigData);
public unsafe delegate Status HttpConfigureFunc(void* self, void* httpConfigData);
public unsafe delegate Status HttpRequestFunc(void* self, void* request);
public unsafe delegate Status HttpCancelFunc(void* self, void* token);
public unsafe delegate Status HttpResponseFunc(void* self, void* response);
public unsafe delegate Status HttpPollFunc(void* self);

[StructLayout(LayoutKind.Sequential, Pack = 1)]
public unsafe struct HttpProtocol
{
    public nuint Revision;
    public HttpGetModeDataFunc GetModeData;
    public HttpConfigureFunc Configure;
    public HttpRequestFunc Request;
    public HttpCancelFunc Cancel;
    public HttpResponseFunc Response;
    public HttpPollFunc Poll;
}

public static partial class EFIConsts
{
    // HTTP protocol GUID from UEFI spec
    public static readonly Guid HttpProtocolGuid = new(0x7A59B29B, 0x910B, 0x4171, 0x82, 0x42, 0xA8, 0x5A, 0x0D, 0xF2, 0x5B, 0x5B);
    public static readonly Guid HttpServiceBindingProtocolGuid = new(0xBDC8E6AF, 0xD9BC, 0x4379, 0xA7, 0x2A, 0xE0, 0xC4, 0xE7, 0x5D, 0xAE, 0x1C);
    // HTTP Boot callback GUID from UEFI spec
    public static readonly Guid HttpBootCallbackProtocolGuid = new(0xBA23B311, 0x343D, 0x11E6, 0x91, 0x85, 0x58, 0x20, 0xB1, 0xD6, 0x52, 0x99);
}

