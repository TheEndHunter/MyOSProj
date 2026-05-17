#pragma once
#include "UEFIDef.h"

namespace Efi
{	
	/// <summary>
	/// Specifies the type of search to perform
	/// </summary>
	enum class LocateSearchType
	{		
		/// <summary>
		/// Protocol and SearchKey are ignored and the function returns an array of every handle in the system.
		/// </summary>
		AllHandles,		
		/// <summary>
		/// SearchKey supplies the Registration value returned by BootServices.RegisterProtocolNotify() .
		/// The function returns the next handle that is new for the registration.
		/// Only one handle is returned at a time, starting with the first, and the caller must loop until no more handles are returned.
		/// Protocol is ignored for this search type.
		/// </summary>
		ByRegisterNotify,		
		/// <summary>
		/// All handles that support Protocol are returned.
		/// SearchKey is ignored for this search type.
		/// </summary>
		ByProtocol
	} ;
}