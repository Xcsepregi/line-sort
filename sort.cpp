#include "sort.h"

#include <string>
#include <iterator>
#include <vector>
#include <algorithm>
#include <cctype>
#include <sstream>

bool sort::LessCaseInsensitive(const std::string &a, const std::string &b)
{
	for (const char* ptrA = a.c_str(),*ptrB = b.c_str(); ;ptrA++,ptrB++) 
	{
		if(std::tolower(*ptrA) != std::tolower(*ptrB) || !*ptrA || !*ptrB) return std::tolower(*ptrA) < std::tolower(*ptrB);
	}
	return false;
}

bool sort::LessCaseSensitive(const std::string &a, const std::string &b)
{
	for (const char* ptrA = a.c_str(),*ptrB = b.c_str(); ; ptrA++,ptrB++)
	{
		if(*ptrA != *ptrB || !*ptrA || !*ptrB) return *ptrA < *ptrB;
	}
	return false;
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
//	int stat_ord,stat_fil,stat_comp;
	std::string line;
	std::vector<std::string> riadky;

	while (std::getline(input, line))
	{
		std::string new_line;
		new_line = line + "\n";
		riadky.push_back(new_line);
	}


	for (std::string ret : lines) output << ret << std::endl;
	
	return true;
}
