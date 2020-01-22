#pragma once
#include "abstract_class.hpp"

namespace sdk
{
	enum class round_state : std::uint8_t
	{
		round_swap,
		operator_selection_phase,
		prep_phase,
		action_phase,
		round_end,
		main_menu
	};

	class round_manager : public abstract_class
	{
	public:
		explicit round_manager(process_t process, std::uint64_t base_ptr);
		round_state get_game_state() const;
	};
}