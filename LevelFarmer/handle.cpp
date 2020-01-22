#include "handle.hpp"

namespace memory
{
	safe_handle::safe_handle()
		: _handle(INVALID_HANDLE_VALUE)
	{ }

	safe_handle::safe_handle(HANDLE handle)
		: _handle(handle)
	{ }

	safe_handle::~safe_handle() noexcept
	{
		if(_handle != INVALID_HANDLE_VALUE)
			::CloseHandle(_handle);
	}

	bool safe_handle::operator!() const
	{
		return _handle == INVALID_HANDLE_VALUE;
	}

	void safe_handle::operator=(HANDLE handle)
	{
		_handle = handle;
	}

	HANDLE safe_handle::get_handle() const
	{
		return _handle;
	}
}