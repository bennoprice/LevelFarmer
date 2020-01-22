#pragma once
#include <string_view>

namespace util
{
	[[noreturn]] void exit();
	[[noreturn]] void exception(std::string_view msg);
}