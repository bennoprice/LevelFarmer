#pragma once
#include <memory>
#include "process.hpp"

namespace sdk
{
	class abstract_class
	{
	protected:
		using process_t = std::shared_ptr<memory::process>;
	public:
		explicit abstract_class(process_t process, std::uint64_t base_ptr);
	protected:
		process_t _process;
		std::uint64_t _base;
	};
}