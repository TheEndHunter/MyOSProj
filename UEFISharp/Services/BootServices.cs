using System.Runtime.InteropServices;

using EFI.Protocols.Configuration;

namespace EFI.Services;

public static partial class EFIConsts
{
    public const ulong BootServicesSignature = 0x56524553544f4f42UL;
    public const ulong BootServicesRevision = EFIConsts.SpecificationVersion;

    public const uint OpenProtocolByHandleProtocol = 0x00000001;
    public const uint OpenProtocolGetProtocol = 0x00000002;
    public const uint OpenProtocolTestProtocol = 0x00000004;
    public const uint OpenProtocolByChildController = 0x00000008;
    public const uint OpenProtocolByDriver = 0x00000010;
    public const uint OpenProtocolExclusive = 0x00000020;


    public unsafe delegate Status RaiseTplFunc(TPL newTpl);
    public unsafe delegate Status RestoreTplFunc(TPL oldTpl);

    public unsafe delegate Status AllocatePagesFunc(AllocateType type, MemoryType memoryType, nuint pages, nint* memory);
    public unsafe delegate Status FreePagesFunc(nint memory, nuint pages);
    public unsafe delegate Status GetMemoryMapFunc(nuint* memoryMapSize, MemoryDescriptor* memoryMap, nuint* mapKey, nuint* descriptorSize, uint* descriptorVersion);
    public unsafe delegate Status AllocatePoolFunc(MemoryType poolType, nuint size, nint* buffer);
    public unsafe delegate Status FreePoolFunc(nint buffer);

    public unsafe delegate Status CreateEventFunc(uint type, TPL notifyTpl, EventNotify notifyFunction, nint notifyContext, Event* @event);
    public unsafe delegate Status SetTimerFunc(Event @event, TimerDelay type, ulong triggerTime);
    public unsafe delegate Status WaitForEventFunc(nuint numberOfEvents, Event* @event, nuint* index);
    public unsafe delegate Status SignalEventFunc(Event @event);
    public unsafe delegate Status CloseEventFunc(Event @event);
    public unsafe delegate Status CheckEventFunc(Event @event);

    public unsafe delegate Status InstallProtocolInterfaceFunc(nint* handle, Guid* protocol, InterfaceType interfaceType, nint @interface);
    public unsafe delegate Status ReinstallProtocolInterfaceFunc(nint handle, Guid* protocol, nint oldInterface, nint newInterface);
    public unsafe delegate Status UninstallProtocolInterfaceFunc(nint handle, Guid* protocol, nint @interface);
    public unsafe delegate Status HandleProtocolFunc(nint handle, Guid* protocol, nint* @interface);
    public unsafe delegate Status RegisterProtocolNotifyFunc(Guid* protocol, Event @event, nint* registration);
    public unsafe delegate Status LocateHandleFunc(LocateSearchType searchType, Guid* protocol, nint searchKey, nuint* bufferSize, nint* buffer);
    public unsafe delegate Status LocateDevicePathFunc(Guid* protocol, nint* devicePath, nint* device);
    public unsafe delegate Status InstallConfigurationTableFunc(Guid* guid, nint table);

    public unsafe delegate Status ImageLoadFunc(bool bootPolicy, nint parentImageHandle, nint devicePath, nint sourceBuffer, nuint sourceSize, nint* imageHandle);
    public unsafe delegate Status ImageStartFunc(nint imageHandle, nuint* exitDataSize, char** exitData);
    public unsafe delegate Status ExitFunc(nint imageHandle, Status exitStatus, nuint exitDataSize, char* exitData);
    public unsafe delegate Status ImageUnloadFunc(nint imageHandle);
    public unsafe delegate Status ExitBootServicesFunc(nint imageHandle, nuint mapKey);

    public unsafe delegate Status GetNextMonotonicCountFunc(ulong* count);
    public unsafe delegate Status StallFunc(nuint microseconds);
    public unsafe delegate Status SetWatchdogTimerFunc(nuint timeout, ulong watchdogCode, nuint dataSize, char* watchdogData);

    public unsafe delegate Status ConnectControllerFunc(nint controllerHandle, nint* driverImageHandle, nint remainingDevicePath, bool recursive);
    public unsafe delegate Status DisconnectControllerFunc(nint controllerHandle, nint driverImageHandle, nint childHandle);

    public unsafe delegate Status OpenProtocolFunc(nint handle, Guid* protocol, nint* @interface, nint agentHandle, nint controllerHandle, uint attributes);
    public unsafe delegate Status CloseProtocolFunc(nint handle, Guid* protocol, nint agentHandle, nint controllerHandle);
    public unsafe delegate Status OpenProtocolInformationFunc(
    BootServices* self,
    nint handle,
    Guid* protocol,
    OpenProtocolInformationEntry** entryBuffer,
    nuint* entryCount);

    public unsafe delegate Status ProtocolsPerHandleFunc(nint handle, Guid*** protocolBuffer, nuint* protocolBufferCount);
    public unsafe delegate Status LocateHandleBufferFunc(LocateSearchType searchType, Guid* protocol, nint searchKey, nuint* noHandles, nint** buffer);
    public unsafe delegate Status LocateProtocolFunc(Guid* protocol, nint registration, nint* @interface);
    public unsafe delegate Status InstallMultipleProtocolInterfacesFunc(nint* handle, nint firstInterface);
    public unsafe delegate Status UninstallMultipleProtocolInterfacesFunc(nint handle, nint firstInterface);

    public unsafe delegate Status CalculateCrc32Func(nint data, nuint dataSize, uint* crc32);
    public unsafe delegate Status CopyMemFunc(nint destination, nint source, nuint length);
    public unsafe delegate Status SetMemFunc(nint buffer, nuint size, byte value);
    public unsafe delegate Status CreateEventExFunc(uint type, TPL notifyTpl, EventNotify notifyFunction, nint notifyContext, Guid* eventGroup, Event* @event);
}

[StructLayout(LayoutKind.Sequential)]
public unsafe struct BootServices
{
    public TableHeader Hdr;

    public EFIConsts.RaiseTplFunc RaiseTPL;
    public EFIConsts.RestoreTplFunc RestoreTPL;

    public EFIConsts.AllocatePagesFunc AllocatePages;
    public EFIConsts.FreePagesFunc FreePages;
    public EFIConsts.GetMemoryMapFunc GetMemoryMap;
    public EFIConsts.AllocatePoolFunc AllocatePool;
    public EFIConsts.FreePoolFunc FreePool;

    public EFIConsts.CreateEventFunc CreateEvent;
    public EFIConsts.SetTimerFunc SetTimer;
    public EFIConsts.WaitForEventFunc WaitForEvent;
    public EFIConsts.SignalEventFunc SignalEvent;
    public EFIConsts.CloseEventFunc CloseEvent;
    public EFIConsts.CheckEventFunc CheckEvent;

    public EFIConsts.InstallProtocolInterfaceFunc InstallProtocolInterface;
    public EFIConsts.ReinstallProtocolInterfaceFunc ReinstallProtocolInterface;
    public EFIConsts.UninstallProtocolInterfaceFunc UninstallProtocolInterface;
    public EFIConsts.HandleProtocolFunc HandleProtocol;
    public nint Reserved;
    public EFIConsts.RegisterProtocolNotifyFunc RegisterProtocolNotify;
    public EFIConsts.LocateHandleFunc LocateHandle;
    public EFIConsts.LocateDevicePathFunc LocateDevicePath;
    public EFIConsts.InstallConfigurationTableFunc InstallConfigurationTable;

    public EFIConsts.ImageLoadFunc LoadImage;
    public EFIConsts.ImageStartFunc StartImage;
    public EFIConsts.ExitFunc Exit;
    public EFIConsts.ImageUnloadFunc UnloadImage;
    public EFIConsts.ExitBootServicesFunc ExitBootServices;

    public EFIConsts.GetNextMonotonicCountFunc GetNextMonotonicCount;
    public EFIConsts.StallFunc Stall;
    public EFIConsts.SetWatchdogTimerFunc SetWatchdogTimer;

    public EFIConsts.ConnectControllerFunc ConnectController;
    public EFIConsts.DisconnectControllerFunc DisconnectController;

    public EFIConsts.OpenProtocolFunc OpenProtocol;
    public EFIConsts.CloseProtocolFunc CloseProtocol;
    public EFIConsts.OpenProtocolInformationFunc OpenProtocolInformation;
    public EFIConsts.ProtocolsPerHandleFunc ProtocolsPerHandle;
    public EFIConsts.LocateHandleBufferFunc LocateHandleBuffer;
    public EFIConsts.LocateProtocolFunc LocateProtocol;
    public EFIConsts.InstallMultipleProtocolInterfacesFunc InstallMultipleProtocolInterfaces;
    public EFIConsts.UninstallMultipleProtocolInterfacesFunc UninstallMultipleProtocolInterfaces;
    public EFIConsts.CalculateCrc32Func CalculateCrc32;
    public EFIConsts.CopyMemFunc CopyMem;
    public EFIConsts.SetMemFunc SetMem;
    public EFIConsts.CreateEventExFunc CreateEventEx;
}
