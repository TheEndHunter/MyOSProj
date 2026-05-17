# UEFI Header Conversion Status

## Batch Tracking

| Batch | Description                                    | Status      |
|-------|------------------------------------------------|------------|
| 1     | Core UEFI (non-services, non-protocol) headers | Completed  |
| 2     | IO/Media protocols (`UEFI/Protocols/IO/Media/*`) | Completed  |
| 3     | Graphics protocols (`UEFI/Protocols/Graphics/*`) | Completed |
| 4     | Debug protocols (`UEFI/Protocols/Debug/*`) | Completed |
| 5     | Remaining IO (Peripheral/Console/Serial), Time, and Configuration/Runtime | Completed |

## Per-Header Mapping

| UEFI Header | UEFISharp C# File | Completeness |
|------------|-------------------|--------------|
| UEFI/AllocateType.h | UEFISharp/AllocateType.cs | ~100% |
| UEFI/Event.h | UEFISharp/Event.cs | ~100% (constants + typedef; behaviour not applicable) |
| UEFI/EventNotify.h | UEFISharp/EventNotify.cs | ~100% |
| UEFI/Guid.h | UEFISharp/Guid.cs | ~100% (struct layout only; C++ operators not ported) |
| UEFI/Handle.h | UEFISharp/Handle.cs | ~100% |
| UEFI/IPAddress.h | UEFISharp/IPAddress.cs | ~100% |
| UEFI/LBA.h | UEFISharp/LBA.cs | ~100% |
| UEFI/LocateSearchType.h | UEFISharp/LocateSearchType.cs | ~100% |
| UEFI/MACAddress.h | UEFISharp/MACAddress.cs | ~100% |
| UEFI/MemoryAddress.h | UEFISharp/MemoryAddress.cs | ~100% |
| UEFI/MemoryDescriptor.h | UEFISharp/MemoryDescriptor.cs | ~100% |
| UEFI/MemoryType.h | UEFISharp/MemoryType.cs | ~100% |
| UEFI/Protocols/Configuration/CapsuleBlockDescriptor.h | UEFISharp/Protocols/Configuration/CapsuleBlockDescriptor.cs | ~100% |
| UEFI/Protocols/Configuration/CapsuleHeader.h          | UEFISharp/Protocols/Configuration/CapsuleHeader.cs          | ~100% |
| UEFI/Protocols/Configuration/CapsuleTable.h           | UEFISharp/Protocols/Configuration/CapsuleTable.cs           | ~100% |
| UEFI/Protocols/Configuration/ConfigurationTable.h     | UEFISharp/Protocols/Configuration/ConfigurationTable.cs     | ~100% |
| UEFI/Protocols/Configuration/ConformanceProfilesTable.h | UEFISharp/Protocols/Configuration/ConformanceProfilesTable.cs | ~100% |
| UEFI/Protocols/Configuration/MemoryAttributesTable.h  | UEFISharp/Protocols/Configuration/MemoryAttributesTable.cs  | ~100% |
| UEFI/Protocols/Configuration/MemoryRangeCapsule.h     | UEFISharp/Protocols/Configuration/MemoryRangeCapsule.cs     | ~100% |
| UEFI/Protocols/Configuration/OpenProtocolInformationEntry.h | UEFISharp/Protocols/Configuration/OpenProtocolInformationEntry.cs | ~100% |
| UEFI/Protocols/Configuration/RTProperties.h           | UEFISharp/Protocols/Configuration/RTProperties.cs           | ~100% |
| UEFI/Protocols/Debug/DebugImageInfo.h | UEFISharp/Protocols/Debug/DebugImageInfo.cs | ~100% |
| UEFI/Protocols/Debug/DebugImageInfoNormal.h | UEFISharp/Protocols/Debug/DebugImageInfoNormal.cs | ~100% |
| UEFI/Protocols/Debug/DebugImageInfoTable.h | UEFISharp/Protocols/Debug/DebugImageInfoTable.cs | ~100% |
| UEFI/Protocols/Debug/DebugportProtocol.h | UEFISharp/Protocols/Debug/DebugportProtocol.cs | ~100% |
| UEFI/Protocols/Debug/DebugSupportProtocol.h | UEFISharp/Protocols/Debug/DebugSupportProtocol.cs | ~100% |
| UEFI/Protocols/Debug/ExceptionType.h | UEFISharp/Protocols/Debug/ExceptionType.cs | ~100% |
| UEFI/Protocols/Debug/FxSaveStateIA32.h | UEFISharp/Protocols/Debug/FxSaveStateIA32.cs | ~100% |
| UEFI/Protocols/Debug/FxSaveStateX64.h | UEFISharp/Protocols/Debug/FxSaveStateX64.cs | ~100% |
| UEFI/Protocols/Debug/InstructionSetArchitecture.h | UEFISharp/Protocols/Debug/InstructionSetArchitecture.cs | ~100% |
| UEFI/Protocols/Debug/SystemContext.h | UEFISharp/Protocols/Debug/SystemContext.cs | ~100% |
| UEFI/Protocols/Debug/SystemContextAARCH64.h | UEFISharp/Protocols/Debug/SystemContextAARCH64.cs | ~100% |
| UEFI/Protocols/Debug/SystemContextARM.h | UEFISharp/Protocols/Debug/SystemContextARM.cs | ~100% |
| UEFI/Protocols/Debug/SystemContextEBC.h | UEFISharp/Protocols/Debug/SystemContextEBC.cs | ~100% |
| UEFI/Protocols/Debug/SystemContextIA32.h | UEFISharp/Protocols/Debug/SystemContextIA32.cs | ~100% |
| UEFI/Protocols/Debug/SystemContextIFP.h | UEFISharp/Protocols/Debug/SystemContextIPF.cs | ~100% |
| UEFI/Protocols/Debug/SystemContextLOONGARCH64.h | UEFISharp/Protocols/Debug/SystemContextLOONGARCH64.cs | ~100% |
| UEFI/Protocols/Debug/SystemContextRISCV128.h | UEFISharp/Protocols/Debug/SystemContextRISCV128.cs | ~100% |
| UEFI/Protocols/Debug/SystemContextRISCV32.h | UEFISharp/Protocols/Debug/SystemContextRISCV32.cs | ~100% |
| UEFI/Protocols/Debug/SystemContextRISCV64.h | UEFISharp/Protocols/Debug/SystemContextRISCV64.cs | ~100% |
| UEFI/Protocols/Debug/SystemContextX64.h | UEFISharp/Protocols/Debug/SystemContextX64.cs | ~100% |
| UEFI/Protocols/Debug/SystemTablePointer.h | UEFISharp/Protocols/Debug/SystemTablePointer.cs | ~100% |
| UEFI/Protocols/Graphics/EdidDiscoveredProtocol.h | UEFISharp/Protocols/Graphics/EdidProtocols.cs | ~100% |
| UEFI/Protocols/Graphics/GraphicsOutputBLTOperation.h | UEFISharp/Protocols/Graphics/GraphicsOutputBLTOperation.cs | ~100% |
| UEFI/Protocols/Graphics/GraphicsOutputBLTPixel.h | UEFISharp/Protocols/Graphics/GraphicsOutputBLTPixel.cs | ~100% |
| UEFI/Protocols/Graphics/GraphicsOutputModeInformation.h | UEFISharp/Protocols/Graphics/GraphicsOutputModeInformation.cs | ~100% |
| UEFI/Protocols/Graphics/GraphicsOutputProtocol.h | UEFISharp/Protocols/Graphics/GraphicsOutputProtocol.cs | ~100% |
| UEFI/Protocols/Graphics/GraphicsOutputProtocolMode.h | UEFISharp/Protocols/Graphics/GraphicsOutputProtocolMode.cs | ~100% |
| UEFI/Protocols/Graphics/GraphicsPixelFormat.h | UEFISharp/Protocols/Graphics/GraphicsPixelFormat.cs | ~100% |
| UEFI/Protocols/Graphics/PixelBitmask.h | UEFISharp/Protocols/Graphics/PixelBitmask.cs | ~100% |
| UEFI/Protocols/IO/Console/ConsoleColor.h             | UEFISharp/Protocols/IO/Console/ConsoleColor.cs             | ~100% |
| UEFI/Protocols/IO/Console/SimpleTextInputEXProtocol.h| UEFISharp/Protocols/IO/Console/SimpleTextInputExProtocol.cs| ~100% |
| UEFI/Protocols/IO/Console/SimpleTextInputProtocol.h  | UEFISharp/Protocols/IO/Console/SimpleTextInputProtocol.cs  | ~100% |
| UEFI/Protocols/IO/Console/SimpleTextOutputProtocol.h | UEFISharp/Protocols/IO/Console/SimpleTextOutputProtocol.cs | ~100% |
| UEFI/Protocols/IO/Console/UnicodeCtrlChar.h          | UEFISharp/Protocols/IO/Console/UnicodeChars.cs             | ~100% |
| UEFI/Protocols/IO/DevicePathProtocol.h | UEFISharp/Protocols/IO/DevicePathProtocol.cs | ~100% |
| UEFI/Protocols/IO/Media/FileAttributes.h | UEFISharp/Protocols/IO/Media/FileAttributes.cs | ~100% |
| UEFI/Protocols/IO/Media/FileInfo.h | UEFISharp/Protocols/IO/Media/FileInfo.cs | ~100% |
| UEFI/Protocols/IO/Media/FileIOToken.h | UEFISharp/Protocols/IO/Media/FileIOToken.cs | ~100% |
| UEFI/Protocols/IO/Media/FileModes.h | UEFISharp/Protocols/IO/Media/FileModes.cs | ~100% |
| UEFI/Protocols/IO/Media/FileProtocol.h | UEFISharp/Protocols/IO/Media/FileProtocol.cs | ~100% |
| UEFI/Protocols/IO/Media/FileSystemInfo.h | UEFISharp/Protocols/IO/Media/FileSystemInfo.cs | ~100% |
| UEFI/Protocols/IO/Media/FileSystemVolumeLabel.h | UEFISharp/Protocols/IO/Media/FileSystemVolumeLabel.cs | ~100% |
| UEFI/Protocols/IO/Media/LoadFile2Protocol.h | UEFISharp/Protocols/IO/Media/LoadFile2Protocol.cs | ~100% |
| UEFI/Protocols/IO/Media/LoadFileProtocol.h | UEFISharp/Protocols/IO/Media/LoadFileProtocol.cs | ~100% |
| UEFI/Protocols/IO/Media/SimpleFileSystemProtocol.h | UEFISharp/Protocols/IO/Media/SimpleFileSystemProtocol.cs | ~100% |
| UEFI/Protocols/IO/Peripheral/AbsolutePointerMode.h    | UEFISharp/Protocols/IO/Peripheral/AbsolutePointerMode.cs    | ~100% |
| UEFI/Protocols/IO/Peripheral/AbsolutePointerProtocol.h| UEFISharp/Protocols/IO/Peripheral/AbsolutePointerProtocol.cs| ~100% |
| UEFI/Protocols/IO/Peripheral/AbsolutePointerState.h   | UEFISharp/Protocols/IO/Peripheral/AbsolutePointerState.cs   | ~100% |
| UEFI/Protocols/IO/Peripheral/InputKey.h               | UEFISharp/Protocols/IO/Peripheral/InputKey.cs               | ~100% |
| UEFI/Protocols/IO/Peripheral/KeyData.h                | UEFISharp/Protocols/IO/Peripheral/KeyData.cs                | ~100% |
| UEFI/Protocols/IO/Peripheral/KeyShiftState.h          | UEFISharp/Protocols/IO/Peripheral/KeyShiftState.cs          | ~100% |
| UEFI/Protocols/IO/Peripheral/KeyState.h               | UEFISharp/Protocols/IO/Peripheral/KeyState.cs               | ~100% |
| UEFI/Protocols/IO/Peripheral/KeyToggleState.h         | UEFISharp/Protocols/IO/Peripheral/KeyToggleState.cs         | ~100% |
| UEFI/Protocols/IO/Peripheral/SimplePointerMode.h      | UEFISharp/Protocols/IO/Peripheral/SimplePointerMode.cs      | ~100% |
| UEFI/Protocols/IO/Peripheral/SimplePointerProtocol.h  | UEFISharp/Protocols/IO/Peripheral/SimplePointerProtocol.cs  | ~100% |
| UEFI/Protocols/IO/Peripheral/SimplePointerState.h     | UEFISharp/Protocols/IO/Peripheral/SimplePointerState.cs     | ~100% |
| UEFI/Protocols/IO/Serial/ParityType.h | UEFISharp/Protocols/IO/Serial/ParityType.cs | ~100% |
| UEFI/Protocols/IO/Serial/SerialControlBits.h | UEFISharp/Protocols/IO/Serial/SerialControlBits.cs | ~100% |
| UEFI/Protocols/IO/Serial/SerialIOMode.h | UEFISharp/Protocols/IO/Serial/SerialIOMode.cs | ~100% |
| UEFI/Protocols/IO/Serial/SerialIOProtocol.h | UEFISharp/Protocols/IO/Serial/SerialIOProtocol.cs | ~100% |
| UEFI/Protocols/IO/Serial/StopBitsType.h | UEFISharp/Protocols/IO/Serial/StopBitsType.cs | ~100% |
| UEFI/Protocols/Time/Time.h | UEFISharp/Protocols/Time/Time.cs | ~100% |
| UEFI/Protocols/Time/TimeCapabilities.h | UEFISharp/Protocols/Time/TimeCapabilities.cs | ~100% |
| UEFI/Protocols/Time/TimerDelay.h | UEFISharp/Protocols/Time/TimerDelay.cs | ~100% |
| UEFI/ResetType.h | UEFISharp/ResetType.cs | ~100% (UEFI reset types enum) |
| UEFI/Services/BootServices.h | UEFISharp/Services/BootServices.cs | ~100% |
| UEFI/Services/RuntimeServices.h | UEFISharp/RuntimeServices.cs | ~100% |
| UEFI/Status.h | UEFISharp/Status.cs | ~100% |
| UEFI/SystemTable.h | UEFISharp/SystemTable.cs | ~100% |
| UEFI/TableHeader.h | UEFISharp/TableHeader.cs | ~100% |
| UEFI/TPL.h | UEFISharp/TPL.cs | ~100% |
| UEFI/UEFIDef.h | *(not yet mapped; core type system pending)* | 0% |

> Percentages are rough estimates of how much of the native header (and any obvious accompanying semantics) have a direct C# representation. This file is intended as a living document; as more headers are converted, new rows should be added and completeness updated.
