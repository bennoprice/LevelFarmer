#include <iostream>
#include <Windows.h>
#include <TlHelp32.h>
#include "util.hpp"
#include "process.hpp"

namespace memory
{
	process::process(std::uint32_t proc_id)
	{
		if (!proc_id)
			util::error_no_return("[-] failed to find process id");
		std::cout << "[+] found process id: " << std::dec << proc_id << std::endl;

		_handle = ::OpenProcess(PROCESS_ALL_ACCESS, false, proc_id);
		if(!_handle)
			util::error_no_return("[-] process handle invalid");
		std::cout << "[+] opened handle to process: 0x" << std::hex << reinterpret_cast<std::uint64_t>(_handle.get_handle()) << std::endl;
	}

	process::process(std::wstring_view proc_name)
		: process(get_pid_from_name(proc_name))
	{ }

	void process::rpm(std::uint64_t dest, std::uint64_t src, std::size_t size) const
	{
		::ReadProcessMemory(_handle.get_handle(), reinterpret_cast<void*>(src), reinterpret_cast<void*>(dest), size, nullptr);
	}

	void process::wpm(std::uint64_t dest, std::uint64_t src, std::size_t size) const
	{
		::WriteProcessMemory(_handle.get_handle(), reinterpret_cast<void*>(dest), reinterpret_cast<void*>(src), size, nullptr);
	}

	std::uint32_t process::get_pid_from_name(std::wstring_view proc_name)
	{
		auto cur_proc_id = ::GetCurrentProcessId();
		auto entry = PROCESSENTRY32{ sizeof(PROCESSENTRY32) };
		auto snapshot = safe_handle(::CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0));

		if (::Process32First(snapshot.get_handle(), &entry))
		{
			do
			{
				if (entry.th32ProcessID != cur_proc_id && proc_name == std::wstring_view(entry.szExeFile))
					return entry.th32ProcessID;
			}
			while (::Process32Next(snapshot.get_handle(), &entry));
		}
		return 0;
	}

	std::uint64_t process::get_module_from_name(std::wstring_view module_name) const
	{
		auto entry = MODULEENTRY32{ sizeof(MODULEENTRY32) };
		auto snapshot = safe_handle(::CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, ::GetProcessId(_handle.get_handle())));

		if (::Module32First(snapshot.get_handle(), &entry))
		{
			do
			{
				if (module_name == std::wstring_view(entry.szModule))
					return reinterpret_cast<std::uint64_t>(entry.modBaseAddr);
			} while (::Module32Next(snapshot.get_handle(), &entry));
		}
		return 0;
	}
}