#pragma once
#include "abstract_class.hpp"

namespace sdk
{
	class localplayer : public abstract_class
	{
	public:
		explicit localplayer(process_t process, std::uint64_t base_ptr);
		void set_experience(int val) const;
		void switch_team() const;
	};
}