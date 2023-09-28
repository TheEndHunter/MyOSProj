#pragma once

namespace EFI
{
	typedef VOID_PTR EFI_EVENT;

	//******************************************************
	// Event Types
	//******************************************************
	// These types can be "ORed" together as needed - for example,
	// EVT_TIMER might be "Ored" with EVT_NOTIFY_WAIT or
	// EVT_NOTIFY_SIGNAL.
	//******************************************************
	const UINT32 EVT_TIMER = 0x80000000;
	const UINT32 EVT_RUNTIME = 0x40000000;
	const UINT32 EVT_NOTIFY_WAIT = 0x00000100;
	const UINT32 EVT_NOTIFY_SIGNAL = 0x00000200;
	const UINT32 EVT_SIGNAL_EXIT_BOOT_SERVICES = 0x00000201;
	const UINT32 EVT_SIGNAL_VIRTUAL_ADDRESS_CHANGE = 0x60000202;
}
