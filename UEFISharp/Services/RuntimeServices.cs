using System.Runtime.InteropServices;

using EFI.Protocols.Configuration;

namespace EFI.Services;

public static partial class EFIConsts
{
    public const ulong RuntimeServicesSignature = 0x56524553544e5552UL;
    public const ulong RuntimeServicesRevision = SpecificationVersion;

    public const nuint EFI_OPTIONAL_PTR = 1;


    public unsafe delegate Status GetTimeFunc(Time* t, TimeCapabilities* capabilities);
    public unsafe delegate Status SetTimeFunc(Time* t);
    public unsafe delegate Status GetWakeupTimeFunc(bool* enabled, bool* pending, Time* t);
    public unsafe delegate Status SetWakeupTimeFunc(bool enable, Time* t);

    public unsafe delegate Status SetVirtualAddressMapFunc(nuint memoryMapSize, nuint descriptorSize, uint descriptorVersion, MemoryDescriptor* virtualMap);
    public unsafe delegate Status ConvertPointerFunc(nuint debugDisposition, void** address);

    public unsafe delegate Status GetVariableFunc(char* variableName, Guid* vendorGuid, uint* attributes, nuint* dataSize, void* data);
    public unsafe delegate Status GetNextVariableNameFunc(nuint* variableNameSize, char* variableName, Guid* vendorGuid);
    public unsafe delegate Status SetVariableFunc(char* variableName, Guid* vendorGuid, uint attributes, nuint dataSize, void* data);

    public unsafe delegate Status GetNextHighMonoCountFunc(uint* highCount);
    public unsafe delegate void ResetSystemFunc(ResetType resetType, Status resetStatus, nuint dataSize, void* resetData);

    public unsafe delegate Status UpdateCapsuleFunc(CapsuleHeader** capsuleHeaderArray, nuint capsuleCount, nint scatterGatherList);
    public unsafe delegate Status QueryCapsuleCapabilitiesFunc(CapsuleHeader** capsuleHeaderArray, nuint capsuleCount, ulong* maximumCapsuleSize, ResetType* resetType);

    public unsafe delegate Status QueryVariableInfoFunc(uint attributes, ulong* maximumVariableStorageSize, ulong* remainingVariableStorageSize, ulong* maximumVariableSize);
}

[StructLayout(LayoutKind.Sequential)]
public unsafe struct RuntimeServices
{
    public TableHeader Hdr;

    public EFIConsts.GetTimeFunc GetTime;
    public EFIConsts.SetTimeFunc SetTime;
    public EFIConsts.GetWakeupTimeFunc GetWakeupTime;
    public EFIConsts.SetWakeupTimeFunc SetWakeupTime;

    public EFIConsts.SetVirtualAddressMapFunc SetVirtualAddressMap;
    public EFIConsts.ConvertPointerFunc ConvertPointer;

    public EFIConsts.GetVariableFunc GetVariable;
    public EFIConsts.GetNextVariableNameFunc GetNextVariableName;
    public EFIConsts.SetVariableFunc SetVariable;
    public EFIConsts.GetNextHighMonoCountFunc GetNextHighMonotonicCount;
    public EFIConsts.ResetSystemFunc ResetSystem;

    public EFIConsts.UpdateCapsuleFunc UpdateCapsule;
    public EFIConsts.QueryCapsuleCapabilitiesFunc QueryCapsuleCapabilities;
    public EFIConsts.QueryVariableInfoFunc QueryVariableInfo;
}
