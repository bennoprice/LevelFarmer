#include "abstract_class.hpp"

namespace sdk
{
	abstract_class::abstract_class(process_t process, std::uint64_t base)
		: _process(process)
		, _base(base)
	{ }
}