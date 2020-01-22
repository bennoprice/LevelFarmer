#include "localplayer.hpp"

namespace sdk
{
	localplayer::localplayer(localplayer::process_t process, std::uint64_t base_ptr)
		: abstract_class(process, base_ptr)
	{ }

	void localplayer::set_experience(int val) const
	{
		auto unk = _process->rpm<std::uint64_t>(_base + 0xa8);
		_process->wpm<int>(unk + 0x12c, val);
	}

	void localplayer::switch_team() const
	{
		auto unk = _process->rpm<std::uint64_t>(_base, 0xa8, 0x68);
		if (_process->rpm<int>(unk + 0x30) == 3)
			_process->wpm<int>(unk + 0x30, 4);
		else
			_process->wpm<int>(unk + 0x30, 3);
	}
}