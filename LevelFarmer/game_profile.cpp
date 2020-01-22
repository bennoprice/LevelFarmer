#include "game_profile.hpp"

namespace sdk
{
	game_profile::game_profile(game_profile::process_t process, std::uint64_t base_ptr)
		: abstract_class(process, base_ptr)
	{ }

	localplayer game_profile::get_localplayer() const
	{
		return localplayer
		(
			_process,
			_process->rpm<std::uint64_t>(_base, 0x68, 0, 0x28)
		);
	}
}