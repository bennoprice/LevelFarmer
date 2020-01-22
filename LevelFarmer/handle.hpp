#pragma once
#include <Windows.h>

namespace memory
{
	class safe_handle
	{
	public:
		explicit safe_handle();
		explicit safe_handle(HANDLE handle);
		~safe_handle() noexcept;
		bool operator!() const;
		void operator=(HANDLE handle);
		HANDLE get_handle() const;
	private:
		HANDLE _handle;
	};
}