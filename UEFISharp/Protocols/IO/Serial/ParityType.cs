namespace EFI.Protocols.IO.Serial;

public enum ParityType : byte
{
    DefaultParity,
    NoParity,
    EvenParity,
    OddParity,
    MarkParity,
    SpaceParity
}
