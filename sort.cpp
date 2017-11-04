#include "sort.h"

#include <string>
#include <iterator>
#include <vector>
#include <algorithm>
#include <cctype>
#include <sstream>

class StringCompare
{
public:
	StringCompare(bool is_case_sensitive = true) : is_case_sensitive(is_case_sensitive) {}
	bool operator()(const std::string&, const std::string&);
private:
	bool is_case_sensitive;
};

void sort_ascend_descend(int ord, std::vector<std::string> &lines)
{
	(ord == 0) ? std::sort(lines.begin(), lines.end()) : std::reverse(lines.begin(), lines.end());
}

void sort_case_ignore(std::vector<std::string> &lines)
{
	std::sort(lines.begin(), lines.end(), StringCompare(false));
}

template <class T>
void UniqueSort(std::vector<T> & lines)
{
	set<T> values;
	lines.erase(std::remove_if(lines.begin(), lines.end(), [&](const T & value) { return !values.insert(value).second; }), lines.end());
}

void main_sort(int stat_ord, int stat_fil, int stat_comp,std::vector<std::string> &lines)
{
	
}

namespace
{
	struct Line : public std::string {};

	std::istream & operator >> (std::istream & is, Line & line)
	{
		return std::getline(is, line);
	}
}

bool sort::process(Order order, Filter filter, Case compare, std::istream & input, std::ostream & output)
{
	std::vector<std::string> lines { std::istream_iterator<Line>(input), std::istream_iterator<Line>() };
	int stat_ord,stat_fil,stat_comp;
	std::string line;
	std::vector<std::string> riadky;

	while (std::getline(input, line))
	{
		std::string new_line;
		new_line = line + "\n";
		riadky.push_back(new_line);
	}

	(order == Order::ascending) ? stat_ord = 0 : stat_ord = 1;
	(filter == Filter::all) ? stat_fil = 0 : stat_fil = 1;
	(compare == Case::ignore) ? stat_comp = 0 : stat_comp = 1;

	main_sort(stat_ord, stat_fil, stat_comp,riadky);

	return true;
}

bool StringCompare::operator()(const std::string &, const std::string &)
{
	return false;
}
