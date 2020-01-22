#pragma once
#include "localplayer.hpp"
#include "abstract_class.hpp"

namespace sdk
{
	class game_profile : public abstract_class
	{
	public:
		explicit game_profile(process_t process, std::uint64_t base_ptr);
		localplayer get_localplayer() const;
	};
}