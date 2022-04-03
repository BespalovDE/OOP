
#include <iostream>
#include <fstream>
#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "../Filter/Filter.h"


TEST_CASE("Open file")
{
	std::set <std::string> filterSet;
	std::ostringstream output;
	bool state;
	SECTION("OpenFile: note exists file")
	{
		std::ifstream inputFileNotExists("DictionaryNotExists.txt");
		state = FillFilterSet(inputFileNotExists, filterSet, output);
	    REQUIRE(!state);
		//1. вынести в константу
		REQUIRE(output.str() == "Input file is empty!\n");
	}
	SECTION("OpenFile: empty file")
	{
		std::ifstream inputFileNotExists("EmptyDictionary.txt");
		state = FillFilterSet(inputFileNotExists, filterSet, output);
		REQUIRE(!state);
		REQUIRE(output.str() == "Empty set of obscene words!\n");
	}
	//возможно тоже лучше вынести в секцию
	std::ifstream inputFile("Dictionary.txt");
	state = FillFilterSet(inputFile, filterSet, output);
	REQUIRE(state);
	std::set <std::string> filterSetConst = {"idiot","nigga","shit"};
	REQUIRE(filterSet == filterSetConst);
}

TEST_CASE("Processing Incoming Line")
{
	std::set <std::string> filterSetConst = { "idiot","nigga","shit" };
	//тестируют одно и тоже
	SECTION("Check idiot")// фильр слова
	{
		std::istringstream input("I hate this idiot!\n");
		std::ostringstream output;
		//думаю лучше подойде handle a не processing
		ProcessingIncomingLine(filterSetConst, input, output);
		REQUIRE(output.str() == "I hate this !\n");
	}
	SECTION("Check nigga")
	{
		std::istringstream input("what this niGga allows himself!\n");
		std::ostringstream output;
		ProcessingIncomingLine(filterSetConst, input, output);
		REQUIRE(output.str() == "what this  allows himself!\n");
	}
	SECTION("Check shit")
	{
		std::istringstream input("Shit in the pool!\n");
		std::ostringstream output;
		ProcessingIncomingLine(filterSetConst, input, output);
		REQUIRE(output.str() == " in the pool!\n");
	}
	SECTION("Check 3 words") //доработать названия тестов
	{
		//тестирования реистра лучше вынести в отдельный тест
		std::istringstream input("This IdioT gone to nIgGa and give up the sHit!\n");
		std::ostringstream output;
		ProcessingIncomingLine(filterSetConst, input, output);
		REQUIRE(output.str() == "This  gone to  and give up the !\n");
	}
}

