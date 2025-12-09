#pragma once

#include "UEFIDef.h"

namespace EFI
{
	ALIGN(8) struct EFI_GUID
	{
	public:
		UINT32 Data1;
		UINT16 Data2;
		UINT16 Data3;
		UINT8 Data4[8];

		EFI_GUID& operator=(const EFI_GUID& guid)
		{
			Data1 = guid.Data1;
			Data2 = guid.Data2;
			Data3 = guid.Data3;
			Data4[0] = guid.Data4[0];
			Data4[1] = guid.Data4[1];
			Data4[2] = guid.Data4[2];
			Data4[3] = guid.Data4[3];
			return *this;
		}

		BOOLEAN operator==(const EFI_GUID& guid)
		{
			return Data1 == guid.Data1 && Data2 == guid.Data2 && Data3 == guid.Data3 && Data4[0] == guid.Data4[0] && Data4[1] == guid.Data4[1] && Data4[2] == guid.Data4[2] && Data4[3] == guid.Data4[3];
		}

		BOOLEAN operator!=(const EFI_GUID& guid)
		{
			return Data1 != guid.Data1 || Data2 != guid.Data2 || Data3 != guid.Data3 || Data4[0] != guid.Data4[0] || Data4[1] != guid.Data4[1] || Data4[2] != guid.Data4[2] || Data4[3] != guid.Data4[3];
		}

		BOOLEAN operator<(const EFI_GUID& guid)
		{
			if (Data1 < guid.Data1)
			{
				return TRUE;
			}
			else if (Data1 == guid.Data1)
			{
				if (Data2 < guid.Data2)
				{
					return TRUE;
				}
				else if (Data2 == guid.Data2)
				{
					if (Data3 < guid.Data3)
					{
						return TRUE;
					}
					else if (Data3 == guid.Data3)
					{
						for (int i = 0; i < 8; i++)
						{
							if (Data4[i] < guid.Data4[i])
							{
								return TRUE;
							}
							else if (Data4[i] > guid.Data4[i])
							{
								return FALSE;
							}
						}
					}
				}
			}
			return FALSE;
		}

		BOOLEAN operator>(const EFI_GUID& guid)
		{
			if (Data1 > guid.Data1)
			{
				return TRUE;
			}
			else if (Data1 == guid.Data1)
			{
				if (Data2 > guid.Data2)
				{
					return TRUE;
				}
				else if (Data2 == guid.Data2)
				{
					if (Data3 > guid.Data3)
					{
						return TRUE;
					}
					else if (Data3 == guid.Data3)
					{
						for (int i = 0; i < 8; i++)
						{
							if (Data4[i] > guid.Data4[i])
							{
								return TRUE;
							}
							else if (Data4[i] < guid.Data4[i])
							{
								return FALSE;
							}
						}
					}
				}
			}
			return FALSE;
		}

		BOOLEAN operator<=(const EFI_GUID& guid)
		{
			if (Data1 < guid.Data1)
			{
				return TRUE;
			}
			else if (Data1 == guid.Data1)
			{
				if (Data2 < guid.Data2)
				{
					return TRUE;
				}
				else if (Data2 == guid.Data2)
				{
					if (Data3 < guid.Data3)
					{
						return TRUE;
					}
					else if (Data3 == guid.Data3)
					{
						for (int i = 0; i < 8; i++)
						{
							if (Data4[i] < guid.Data4[i])
							{
								return TRUE;
							}
							else if (Data4[i] > guid.Data4[i])
							{
								return FALSE;
							}
						}
					}
				}
			}
			return TRUE;
		}

		BOOLEAN operator>=(const EFI_GUID& guid)
		{
			if (Data1 > guid.Data1)
			{
				return TRUE;
			}
			else if (Data1 == guid.Data1)
			{
				if (Data2 > guid.Data2)
				{
					return TRUE;
				}
				else if (Data2 == guid.Data2)
				{
					if (Data3 > guid.Data3)
					{
						return TRUE;
					}
					else if (Data3 == guid.Data3)
					{
						for (int i = 0; i < 8; i++)
						{
							if (Data4[i] > guid.Data4[i])
							{
								return TRUE;
							}
							else if (Data4[i] < guid.Data4[i])
							{
								return FALSE;
							}
						}
					}
				}
			}
			return TRUE;
		}

	
	};
}
