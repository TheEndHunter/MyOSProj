namespace EFI;

public static partial class EFIConsts
{
    public const ulong ErrorMask = 0x8000000000000000UL;
    public const ulong WarningMask = 0UL;
}

// Mirrors Efi::Status using 64-bit values and masks.
public enum Status : ulong
{
    Success = 0,
    LoadError = 1 | EFIConsts.ErrorMask,
    InvalidParameter = 2 | EFIConsts.ErrorMask,
    Unsupported = 3 | EFIConsts.ErrorMask,
    BadBufferSize = 4 | EFIConsts.ErrorMask,
    BufferTooSmall = 5 | EFIConsts.ErrorMask,
    NotReady = 6 | EFIConsts.ErrorMask,
    DeviceError = 7 | EFIConsts.ErrorMask,
    WriteProtected = 8 | EFIConsts.ErrorMask,
    OutOfResources = 9 | EFIConsts.ErrorMask,
    VolumeCorrupted = 10 | EFIConsts.ErrorMask,
    VolumeFull = 11 | EFIConsts.ErrorMask,
    NoMedia = 12 | EFIConsts.ErrorMask,
    MediaChanged = 13 | EFIConsts.ErrorMask,
    NotFound = 14 | EFIConsts.ErrorMask,
    AccessDenied = 15 | EFIConsts.ErrorMask,
    NoResponse = 16 | EFIConsts.ErrorMask,
    NoMapping = 17 | EFIConsts.ErrorMask,
    Timeout = 18 | EFIConsts.ErrorMask,
    NotStarted = 19 | EFIConsts.ErrorMask,
    AlreadyStarted = 20 | EFIConsts.ErrorMask,
    Aborted = 21 | EFIConsts.ErrorMask,
    IcmpError = 22 | EFIConsts.ErrorMask,
    TftpError = 23 | EFIConsts.ErrorMask,
    ProtocolError = 24 | EFIConsts.ErrorMask,
    IncompatibleVersion = 25 | EFIConsts.ErrorMask,
    SecurityViolation = 26 | EFIConsts.ErrorMask,
    CrcError = 27 | EFIConsts.ErrorMask,
    EndOfMedia = 28 | EFIConsts.ErrorMask,
    EndOfFile = 31 | EFIConsts.ErrorMask,
    InvalidLanguage = 32 | EFIConsts.ErrorMask,
    CompromisedData = 33 | EFIConsts.ErrorMask,
    IpAddressConflict = 34 | EFIConsts.ErrorMask,
    HttpError = 35 | EFIConsts.ErrorMask,

    WarnUnknownGlyph = 1 | EFIConsts.WarningMask,
    WarnDeleteFailure = 2 | EFIConsts.WarningMask,
    WarnWriteFailure = 3 | EFIConsts.WarningMask,
    WarnBufferTooSmall = 4 | EFIConsts.WarningMask,
    WarnStaleData = 5 | EFIConsts.WarningMask,
    WarnFileSystem = 6 | EFIConsts.WarningMask,
    WarnResetRequired = 7 | EFIConsts.WarningMask
}
