#pragma once
#include <string_view>

namespace util
{
	[[noreturn]] void exit();
	[[noreturn]] void error_no_return(std::string_view msg);
}