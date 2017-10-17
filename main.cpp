
#include <iostream>
#include <fstream>
#include <ostream>

#include "options.h"
#include "sort.h"

int main(int argc, char * argv[])
{
	auto options = options::parse(argc, argv);
	if (!options)
	{
		std::cout << "Zle zadane vstupne argumenty!";
		std::cout << "Mozne argumenty:";
		std::cout << "-r pre triedenie riadkov zostupne";
		std::cout << "-i case insensitive triedenie";
		std::cout << "-u filtrovanie unikatnych riadkov";
		return -1;
	}

	Order order;
	Filter filter;
	Case compare;
	char * file;

	std::tie(order, filter, compare, file) = options.value();

	std::fstream fs;
	if (file)
	{
		fs.open(file);
		if (fs.bad())
		{
			std::cerr << "Zlyhanie otvorenia suboru!" << std::endl;
			return -1;
		}
	}

	std::istream & input = file ? fs : std::cin;

	if (!sort::process(order, filter, compare, input, std::cout))
	{
		std::cerr << "Chyba pri triedeni!" << std::endl;
		return -1;
	}

	return 0;
}

