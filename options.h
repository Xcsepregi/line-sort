#pragma once

#include "defs.h"
#include <tuple>
#include <optional>

namespace options
{
	std::optional<std::tuple<Order, Filter, Case, Efilter, char *>> parse(int argc, char * argv[]);
}
