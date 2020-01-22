#include <thread>
#include <iostream>
#include "util.hpp"
#include "process.hpp"
#include "game_profile.hpp"
#include "round_manager.hpp"

int main()
{
	auto process = std::make_shared<memory::process>(L"RainbowSix.exe");
	auto module_base = process->get_module_from_name(L"RainbowSix.exe");

	auto game_profile = sdk::game_profile(process, process->rpm<std::uint64_t>(module_base + 0x52a8e68));
	auto round_manager = sdk::round_manager(process, process->rpm<std::uint64_t>(module_base + 0x52a8e98));

	std::cout << "[+] successfully initialised" << std::endl;

	while (!::GetAsyncKeyState(VK_F10))
	{
		static auto has_slept = false;
		auto game_state = round_manager.get_game_state();

		switch (game_state)
		{
			case sdk::round_state::action_phase:
			{
				has_slept = false;
				auto localplayer = game_profile.get_localplayer();
				localplayer.set_experience(99999);
				localplayer.switch_team();
				std::cout << "[+] set experience and ended round" << std::endl;
				break;
			}
			case sdk::round_state::round_end:
			{
				if (!has_slept)
				{
					std::cout << "[~] waiting to restart round..." << std::endl;
					std::this_thread::sleep_for(std::chrono::seconds(17));
					has_slept = true;
				}
				else
				{
					keybd_event(VK_ESCAPE, 1, 0, 0);
					keybd_event(VK_ESCAPE, 1, KEYEVENTF_KEYUP, 0);

					keybd_event(VK_RETURN, 156, 0, 0);
					keybd_event(VK_RETURN, 156, KEYEVENTF_KEYUP, 0);
				}
				break;
			}
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}

	util::exit();
}