#pragma once
#include <Windows.h>

namespace memory
{
	class safe_handle
	{
	public:
		safe_handle();
		safe_handle(HANDLE handle);
		safe_handle(safe_handle&& other) noexcept;
		safe_handle(safe_handle& other) = delete;
		safe_handle& operator=(safe_handle&& other) noexcept;
		safe_handle& operator=(safe_handle& other) = delete;
		operator bool() const;
		~safe_handle() noexcept;
		void close_handle();
		HANDLE get_handle() const;
	private:
		HANDLE _handle;
	};
}