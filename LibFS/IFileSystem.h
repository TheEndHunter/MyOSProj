#pragma once
#include "TypeDefs.h"

namespace LibFS
{
	class IFileSystem
	{
	public:
		virtual void Initialize() = 0;
		virtual void Shutdown() = 0;

		virtual void Mount(const char* path) = 0;
		virtual void Unmount(const char* path) = 0;

		virtual void CreateFile(const char* path) = 0;
		virtual void DeleteFile(const char* path) = 0;

		virtual void CreateDirectory(const char* path) = 0;
		virtual void DeleteDirectory(const char* path) = 0;

		virtual void Move(const char* src, const char* dst) = 0;
		virtual void Copy(const char* src, const char* dst) = 0;

		virtual void Mount(const CHAR16* path) = 0;
		virtual void Unmount(const CHAR16* path) = 0;

		virtual void CreateFile(const CHAR16* path) = 0;
		virtual void DeleteFile(const CHAR16* path) = 0;

		virtual void CreateDirectory(const CHAR16* path) = 0;
		virtual void DeleteDirectory(const CHAR16* path) = 0;

		virtual void Move(const CHAR16* src, const CHAR16* dst) = 0;
		virtual void Copy(const CHAR16* src, const CHAR16* dst) = 0;

	}
};