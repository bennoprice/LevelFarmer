#include "round_manager.hpp"

namespace sdk
{
	round_manager::round_manager(round_manager::process_t process, std::uint64_t base_ptr)
		: abstract_class(process, base_ptr)
	{ }

	round_state round_manager::get_game_state() const
	{
		return _process->rpm<round_state>(_base + 0x2e8);
	}
}