#pragma once


VOID_PTR operator new(UINTN length)
{
	auto* allocator = Common::System::MemoryManagement::Allocator::GetInstance();
	if (allocator == nullptr)
	{
		return nullptr;
	}
	if (!allocator->IsInitalized())
	{
		return nullptr;
	}
	return allocator->Allocate(length);
}

VOID_PTR operator new[](UINTN length)
{
	auto* allocator = Common::System::MemoryManagement::Allocator::GetInstance();
	if (allocator == nullptr)
	{
		return nullptr;
	}
	if (!allocator->IsInitalized())
	{
		return nullptr;
	}
	return allocator->Allocate(length);
}

VOID_PTR operator new(UINTN length, VOID_PTR ptr)
{
	return ptr;
}

VOID_PTR operator new[](UINTN length, VOID_PTR ptr)
{
	return ptr;
}

void operator delete(VOID_PTR ptr)
{
	auto* allocator = Common::System::MemoryManagement::Allocator::GetInstance();
	if (allocator == nullptr)
	{
		return;
	}
	if (!allocator->IsInitalized())
	{
		return;
	}
	return allocator->Free(ptr);
}

void operator delete[](VOID_PTR ptr)
{
	auto* allocator = Common::System::MemoryManagement::Allocator::GetInstance();
	if (allocator == nullptr)
	{
		return;
	}
	if (!allocator->IsInitalized())
	{
		return;
	}
	return allocator->Free(ptr);
}

void operator delete(VOID_PTR ptr, UINTN length)
{
	auto* allocator = Common::System::MemoryManagement::Allocator::GetInstance();
	if (allocator == nullptr)
	{
		return;
	}
	if (!allocator->IsInitalized())
	{
		return;
	}
	return allocator->Free(ptr);
}

void operator delete[](VOID_PTR ptr, UINTN length)
{
	auto* allocator = Common::System::MemoryManagement::Allocator::GetInstance();
	if (allocator == nullptr)
	{
		return;
	}
	if (!allocator->IsInitalized())
	{
		return;
	}
	return allocator->Free(ptr);
}

void operator delete(VOID_PTR ptr, VOID_PTR place)
{
	auto* allocator = Common::System::MemoryManagement::Allocator::GetInstance();
	if (allocator == nullptr)
	{
		return;
	}
	if (!allocator->IsInitalized())
	{
		return;
	}
	return allocator->Free(ptr);
}

void operator delete[](VOID_PTR ptr, VOID_PTR place)
{
	auto* allocator = Common::System::MemoryManagement::Allocator::GetInstance();
	if (allocator == nullptr)
	{
		return;
	}
	if (!allocator->IsInitalized())
	{
		return;
	}
	return allocator->Free(ptr);
}