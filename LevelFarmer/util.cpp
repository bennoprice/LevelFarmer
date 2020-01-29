#include <iostream>
#include "util.hpp"

namespace util
{
	[[noreturn]] void exit()
	{
		std::cout << std::endl;
		system("pause");
		std::exit(0);
	}

	[[noreturn]] void error_no_return(std::string_view msg)
	{
		std::cerr << msg.data() << std::endl;
		exit();
	}
}