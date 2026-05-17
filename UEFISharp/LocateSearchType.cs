namespace EFI;

/// <summary>
/// Specifies the type of search to perform (mirrors Efi::LocateSearchType)
/// </summary>
public enum LocateSearchType
{
    /// <summary>Return an array of every handle in the system.</summary>
    AllHandles,
    /// <summary>Use a registration value from RegisterProtocolNotify and return one handle at a time.</summary>
    ByRegisterNotify,
    /// <summary>Return all handles that support a given protocol.</summary>
    ByProtocol
}