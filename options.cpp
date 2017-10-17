#include "options.h"
#include <vector>
#include <iostream>

std::vector<std::string> split(char *phrase, std::string delimiter) 
{
	std::vector<std::string> list;
	std::string s = std::string(phrase);
	size_t pos = 0;
	std::string token;

	while ((pos = s.find(delimiter)) != std::string::npos)
	{
		token = s.substr(1, 1);
		list.push_back(token);
		s.erase(0, pos + delimiter.length() + 1 );
	}

	return list;
}

std::optional<std::tuple<Order, Filter, Case, char *>> options::parse(int argc, char * argv[])
{
	Order order { Order::ascending };
	Filter filter { Filter::all };
	Case compare { Case::sensitive };
	char * input { nullptr };

	if (argc == 1) return std::make_tuple(order, filter, compare, input);

	std::vector<std::string> settings;

	settings = split(argv[1], "-");
	for (std::string ret : settings)
	{
		if (ret == "r") order = Order::descending;
		else if (ret == "u") filter = Filter::unique;
		else if (ret == "i") compare = Case::sensitive;
		else return {};
	}

	if (argc == 3)
	{
		input = argv[2];
	}

	return std::make_tuple(order, filter, compare, input);
}
