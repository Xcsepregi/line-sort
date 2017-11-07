#pragma once

#include <fstream>
#include <ostream>

#include "defs.h"

namespace sort
{
	bool process(Order order, Filter filter, Case compare, std::istream & input, std::ostream & output);
	bool LessCaseInsensitive(const std::string &a, const std::string &b);
	bool LessCaseSensitive(const std::string &a, const std::string &b);
}

