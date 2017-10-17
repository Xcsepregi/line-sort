#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "options.h"
#include "sort.h"

#include <sstream>

TEST_CASE("Options")
{
	SECTION("no options")
	{
		char * argv[] = { "line-sort" };
		REQUIRE(options::parse(1, argv) == std::make_tuple(Order::ascending, Filter::all, Case::sensitive, (char *) nullptr));
	}

	SECTION("reversed")
	{
		char * argv[] = { "line-sort" , "r" , "subor.txt" };
		REQUIRE(options::parse(2, argv) == std::make_tuple(Order::descending, Filter::all, Case::sensitive, (char *) nullptr));
		REQUIRE(options::parse(3, argv) == std::make_tuple(Order::descending, Filter::all, Case::sensitive, "subor.txt"));
	}

	SECTION("unique")
	{
		char * argv[] = { "line-sort" , "u" , "subor.txt" };
		REQUIRE(options::parse(2, argv) == std::make_tuple(Order::ascending, Filter::unique, Case::sensitive, (char *)nullptr));
		REQUIRE(options::parse(3, argv) == std::make_tuple(Order::ascending, Filter::unique, Case::sensitive, "subor.txt"));
	}

	SECTION("ignore case")
	{
		char * argv[] = { "line-sort" , "i" , "subor.txt" };
		REQUIRE(options::parse(2, argv) == std::make_tuple(Order::ascending, Filter::all, Case::ignore, (char *) nullptr));
		REQUIRE(options::parse(3, argv) == std::make_tuple(Order::ascending, Filter::all, Case::ignore, "subor.txt"));
	}

	SECTION("multiple")
	{
		{
			char * argv[] = { "line-sort" , "ru" , "subor.txt" };
			REQUIRE(options::parse(2, argv) == std::make_tuple(Order::descending, Filter::unique, Case::sensitive, (char *) nullptr));
		}


		{
			char * argv[] = { "line-sort" , "ri" };
			REQUIRE(options::parse(2, argv) == std::make_tuple(Order::descending, Filter::all, Case::ignore, (char *) nullptr));
		}

		{
			char * argv[] = { "line-sort" , "ui" };
			REQUIRE(options::parse(2, argv) == std::make_tuple(Order::ascending, Filter::unique, Case::ignore, (char *) nullptr));
		}

		{
			char * argv[] = { "line-sort" , "ru" , "subor.txt" };
			REQUIRE(options::parse(3, argv) == std::make_tuple(Order::descending, Filter::unique, Case::ignore, "subor.txt"));
		}
		
		{
			char * argv[] = { "line-sort" , "ri" , "subor.txt" };
			REQUIRE(options::parse(3, argv) == std::make_tuple(Order::descending, Filter::unique, Case::sensitive, "subor.txt"));
		}

		//u + i + ifstream
		//r + u + i + cin
		//r + u + i + ifstream
		//zle param
	}

	system("pause");
}

namespace
{
	namespace data
	{
		std::istringstream empty { R"()" };
		std::istringstream one_char { R"( )" };
		std::istringstream one_line { R"(
)" };
		std::istringstream numbered { R"(1
3
9
4
5
2
)" };
	}
}

TEST_CASE("Sorting")
{
	SECTION("ascending")
	{
		std::ostringstream output {};

		REQUIRE(sort::process(Order::ascending, Filter::all, Case::sensitive, data::empty, output) == true);
		REQUIRE(output.str() == "");

		//output.str("");
		//REQUIRE(sort::process(Order::ascending, Filter::all, Case::sensitive, data::one_char, output) == true);
		//REQUIRE(output.str() == " \n");

		//output.str("");
		//REQUIRE(sort::process(Order::ascending, Filter::all, Case::sensitive, data::one_line, output) == true);
		//REQUIRE(output.str() == "\n");

		//output.str("");
		//REQUIRE(sort::process(Order::ascending, Filter::all, Case::sensitive, data::numbered, output) == true);
		//REQUIRE(output.str() == "1\n2\n3\n4\n5\n9\n");
	}

	SECTION("ascending - unique")
	{
	}

	SECTION("ascending - unique - ignore case")
	{
	}

	SECTION("descending")
	{
	}

	SECTION("descending - unique")
	{
	}

	SECTION("descending - unique - ignore case")
	{
	}
}

