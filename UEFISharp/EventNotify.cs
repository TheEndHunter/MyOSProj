namespace EFI;

// Delegate matching EFIAPI EventNotify signature
public delegate void EventNotify(Event e, nint context);
