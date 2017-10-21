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
		char * argv[] = { "line-sort" , "-r" , "subor.txt" };
		REQUIRE(options::parse(2, argv) == std::make_tuple(Order::descending, Filter::all, Case::sensitive, (char *) nullptr));
		REQUIRE(options::parse(3, argv) == std::make_tuple(Order::descending, Filter::all, Case::sensitive, "subor.txt"));
	}

	SECTION("unique")
	{
		char * argv[] = { "line-sort" , "-u" , "subor.txt" };
		REQUIRE(options::parse(2, argv) == std::make_tuple(Order::ascending, Filter::unique, Case::sensitive, (char *)nullptr));
		REQUIRE(options::parse(3, argv) == std::make_tuple(Order::ascending, Filter::unique, Case::sensitive, "subor.txt"));
	}

	SECTION("ignore case")
	{
		char * argv[] = { "line-sort" , "-i" , "subor.txt" };
		REQUIRE(options::parse(2, argv) == std::make_tuple(Order::ascending, Filter::all, Case::ignore, (char *) nullptr));
		REQUIRE(options::parse(3, argv) == std::make_tuple(Order::ascending, Filter::all, Case::ignore, "subor.txt"));
	}

	SECTION("multiple")
	{
		{
			char * argv[] = { "line-sort" , "-r-u" , "subor.txt" };
			REQUIRE(options::parse(2, argv) == std::make_tuple(Order::descending, Filter::unique, Case::sensitive, (char *) nullptr));
		}

		{
			char * argv[] = { "line-sort" , "-r-i" };
			REQUIRE(options::parse(2, argv) == std::make_tuple(Order::descending, Filter::all, Case::ignore, (char *) nullptr));
		}

		{
			char * argv[] = { "line-sort" , "-u-i" };
			REQUIRE(options::parse(2, argv) == std::make_tuple(Order::ascending, Filter::unique, Case::ignore, (char *) nullptr));
		}

		{
			char * argv[] = { "line-sort" , "-r-u" , "subor.txt" };
			REQUIRE(options::parse(3, argv) == std::make_tuple(Order::descending, Filter::unique, Case::sensitive, "subor.txt"));
		}

		{
			char * argv[] = { "line-sort" , "-r-i" , "subor.txt" };
			REQUIRE(options::parse(3, argv) == std::make_tuple(Order::descending, Filter::all, Case::ignore, "subor.txt"));
		}

		{
			char * argv[] = { "line-sort" , "-u-i" , "subor.txt" };
			REQUIRE(options::parse(3, argv) == std::make_tuple(Order::ascending, Filter::unique, Case::ignore, "subor.txt"));
		}

		{
			char * argv[] = { "line-sort" , "-r-u-i" };
			REQUIRE(options::parse(2, argv) == std::make_tuple(Order::descending, Filter::unique, Case::ignore, (char *) nullptr));
		}

		{
			char * argv[] = { "line-sort" , "-r-u-i" , "subor.txt" };
			REQUIRE(options::parse(3, argv) == std::make_tuple(Order::descending, Filter::unique, Case::ignore, "subor.txt"));
		}
	}
	
	SECTION("bad args")
	{
		Order order;
		Filter filter;
		Case pripad;
		char *ch{ nullptr };

		{
			char * argv[] = { "line-sort" , "-g-u-i" };
			REQUIRE(options::parse(2, argv) == std::make_tuple(order, filter, pripad, ch));
		}

		{
			char * argv[] = { "line-sort" , "-r-g-i" };
			REQUIRE(options::parse(2, argv) == std::make_tuple(order, filter, pripad, ch));
		}

		{
			char * argv[] = { "line-sort" , "-r-u-g" };
			REQUIRE(options::parse(2, argv) == std::make_tuple(order, filter, pripad, ch));
		}

		{
			char * argv[] = { "line-sort" , "-r-c-w" };
			REQUIRE(options::parse(2, argv) == std::make_tuple(order, filter, pripad, ch));
		}
	}

	SECTION("file testing")
	{
		std::ifstream subor;
		std::string filename;
		std::stringstream file_content;

		{
			filename = { "bad_file.txt" };
			subor.open(filename.c_str());
			REQUIRE(subor.fail());
		}

		{
			filename = { "empty_file.txt" };
			subor.open(filename.c_str());
			REQUIRE(!subor.fail());
			subor.close();
		}

		{
			filename = { "file.txt" };
			subor.open(filename.c_str());
			REQUIRE(!subor.fail());
			file_content << subor.rdbuf();
			REQUIRE(file_content.peek() != EOF);
			subor.close();
		}
	}
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

//0.45