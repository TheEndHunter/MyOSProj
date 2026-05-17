#pragma once

#include <TypeDefs.h>
#include <Graphics/MonitorMode.h>
#include <Protocols/Graphics/GraphicsOutputProtocol.h>

namespace Common::Graphics
{
	struct MonitorContext
	{
		friend struct RenderContext;

	public:
		BOOLEAN SetMode(UINT32 modeNumber);
		MonitorMode* GetCurrentMode();
		MonitorMode* GetMode(UINT32 modeNumber);

		UINT32 GetMaxMode();
		UINTN GetFrameBufferSize();
		UINT32 GetHorizontalResolution();
		UINT32 GetVerticalResolution();
		UINT32 GetPixelsPerScanLine();
		VOID_PTR GetFrameBuffer();
		PixelFormat GetPixelFormat();
		PixelBitMask GetPixelBitMask();
		void Terminate();


	private:
		MonitorContext();
		MonitorContext(Efi::GraphicsOutputProtocol* ptr);
		Efi::GraphicsOutputProtocol* protocol;
		UINT32 maxMode;
		UINT32 currentModeNumber;
		MonitorMode* currentMode;
		MonitorMode* modes;

	};


}
