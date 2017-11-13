#include "sort.h"

#include <string>
#include <iterator>
#include <vector>
#include <algorithm>
#include <cctype>
#include <sstream>

bool LessCaseInSensitive(const std::string & a, const std::string & b)
{
	for (const char *ptrA = a.c_str(), *ptrB = b.c_str(); ; ++ptrA, ++ptrB)
		if (tolower(*ptrA) != tolower(*ptrB) || !*ptrA || !*ptrB) return tolower(*ptrA) < tolower(*ptrB);

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

bool Comp(const std::string & a, const std::string & b) {

	if (a.size() != b.size())
		return false;

	for (int i = 0; i < a.size(); ++i)
		if (tolower(a[i]) != tolower(b[i])) return false;

	return true;
}

namespace
{
	struct Line : public std::string {};

	std::istream & operator >> (std::istream & is, Line & line)
	{
		return std::getline(is, line);
	}
}

bool sort::process(Order order, Filter filter, Case compare,Efilter space, std::istream & input, std::ostream & output)
{
	std::vector<std::string> lines { std::istream_iterator<Line>(input), std::istream_iterator<Line>() };
	std::string line;
	std::vector<std::string> riadky;

	while (std::getline(input, line))
	{
		std::string new_line;
		new_line = line + "\n";
		riadky.push_back(new_line);
	}

	if (space == Efilter::empty) 
	{
		riadky.erase(std::remove_if(riadky.begin(), riadky.end(),[](const std::string& s) { return s.find(';', 0); }));
	}

	if (compare == Case::ignore) 
	{
		std::sort(riadky.begin(), riadky.end(), LessCaseInSensitive);
	}

	else 
	{
		std::sort(riadky.begin(), riadky.end(), sort::LessCaseSensitive);
	}

	if (order == Order::descending) 
	{
		std::reverse(riadky.begin(), riadky.end());
	}

	if (filter == Filter::unique && compare == Case::ignore) 
	{
		riadky.erase(std::unique(riadky.begin(), riadky.end(), Comp), lines.end());
	}

	else if (filter == Filter::unique && compare == Case::sensitive) 
	{
		riadky.erase(std::unique(riadky.begin(), riadky.end()), riadky.end());
	}

	for (int i = 0; i < line.size(); i++) {
		output << line[i] << std::endl;
	}

	return true;
}
