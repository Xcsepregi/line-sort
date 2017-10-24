#include "options.h"
#include <vector>
#include <iostream>

std::vector<char> split(char *phrase)
{
	std::vector<char> list;
	std::string s = std::string(phrase);
	std::string token;

	for (char znak : s)
	{
		if (znak >= 'a' && znak <= 'z')
		{
			list.push_back(znak);
		}
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

	std::vector<char> settings;

	settings = split(argv[1]);
	for(char znak : settings)
	{
		if (znak == 'r') order = Order::descending;
		else if (znak == 'u') filter = Filter::unique;
		else if (znak == 'i') compare = Case::ignore;

		else
		{
			Order ord;
			Filter fil;
			Case cas;
			return std::make_tuple(ord, fil, cas, input);
		}
			
	}

	if (argc == 3)
	{
		input = argv[2];
	}

	return std::make_tuple(order, filter, compare, input);
}
