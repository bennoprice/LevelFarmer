#include <utility>
#include "handle.hpp"

namespace memory
{
	safe_handle::safe_handle()
		: _handle(INVALID_HANDLE_VALUE)
	{ }

	safe_handle::safe_handle(HANDLE handle)
		: _handle(handle)
	{ }

	safe_handle::safe_handle(safe_handle&& other) noexcept
		: _handle(std::exchange(other._handle, INVALID_HANDLE_VALUE))
	{ }

	safe_handle::~safe_handle() noexcept
	{
		if (*this)
			close_handle();
	}

	safe_handle& safe_handle::operator=(safe_handle&& other) noexcept
	{
		if (&other != this)
		{
			if (*this)
				close_handle();
			_handle = std::exchange(other._handle, INVALID_HANDLE_VALUE);
		}
		return *this;
	}

	void safe_handle::close_handle()
	{
		::CloseHandle(_handle);
		_handle = INVALID_HANDLE_VALUE;
	}

	safe_handle::operator bool() const
	{
		return _handle && _handle != INVALID_HANDLE_VALUE;
	}

	HANDLE safe_handle::get_handle() const
	{
		return _handle;
	}
}