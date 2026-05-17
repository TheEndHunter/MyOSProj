#pragma once

namespace Efi
{
	typedef VOID_PTR Event;

	//******************************************************
	// Event Types
	//******************************************************
	// These types can be "ORed" together as needed - for example,
	// EVT_TIMER might be "Ored" with EVT_NOTIFY_WAIT or
	// EVT_NOTIFY_SIGNAL.
	//******************************************************
	CONST UINT32 EVT_TIMER = 0x80000000;
	CONST UINT32 EVT_RUNTIME = 0x40000000;
	CONST UINT32 EVT_NOTIFY_WAIT = 0x00000100;
	CONST UINT32 EVT_NOTIFY_SIGNAL = 0x00000200;
	CONST UINT32 EVT_SIGNAL_EXIT_BOOT_SERVICES = 0x00000201;
	CONST UINT32 EVT_SIGNAL_VIRTUAL_ADDRESS_CHANGE = 0x60000202;
}
