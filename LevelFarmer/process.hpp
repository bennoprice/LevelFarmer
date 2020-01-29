#pragma once
#include <cstdint>
#include <string_view>
#include "handle.hpp"

namespace memory
{
	class process
	{
	public:
		explicit process(std::uint32_t proc_id);
		explicit process(std::wstring_view proc_name);

		static std::uint32_t get_pid_from_name(std::wstring_view proc_name);
		std::uint64_t get_module_from_name(std::wstring_view module_name) const;

		void rpm(std::uint64_t dest, std::uint64_t src, std::size_t size) const;
		void wpm(std::uint64_t dest, std::uint64_t src, std::size_t size) const;

		template <typename T>
		T rpm(std::uint64_t addr) const
		{
			T val;
			rpm(reinterpret_cast<std::uint64_t>(&val), addr, sizeof(T));
			return val;
		}

		template <typename T>
		void wpm(std::uint64_t addr, T val) const
		{
			wpm(addr, reinterpret_cast<std::uint64_t>(&val), sizeof(T));
		}

		template<typename T>
		T rpm(std::uint64_t addr, std::uint64_t last) const
		{
			return rpm<T>(addr + last);
		}

		template<typename T, typename... Args>
		T rpm(std::uint64_t addr, std::uint64_t first, Args... args) const
		{
			return rpm<T>(rpm<std::uint64_t>(addr + first), args...);
		}
	private:
		safe_handle _handle;
	};
}