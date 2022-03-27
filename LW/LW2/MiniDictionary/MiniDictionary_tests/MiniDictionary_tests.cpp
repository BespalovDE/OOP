#include <iostream>
#include <fstream>
#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "../MiniDictionary/MiniDictionary.h"

TEST_CASE("Main test")
{
	std::ostringstream output;
	std::multimap <std::string, std::string> dictionary;
	SECTION("Dictionary not exists")
	{
		std::ifstream inputFileNotExists("DictionaryNotExists.txt");
		REQUIRE(FillDictionary(inputFileNotExists, dictionary, output));
		REQUIRE(dictionary.size() == 0);
		REQUIRE(output.str() == "");
	}
	SECTION("Dictionary is empty")
	{
		std::ifstream inputFileNotExists("EmptyDictionary.txt");
		REQUIRE(FillDictionary(inputFileNotExists, dictionary, output));
		REQUIRE(dictionary.size() == 0);
		REQUIRE(output.str() == "");
	}
	SECTION("Dictionary not correct")
	{
		std::ifstream inputFileNotExists("NotCorrectDictionary.txt");
		REQUIRE(!FillDictionary(inputFileNotExists, dictionary, output));
		REQUIRE(dictionary.size() == 0);
		REQUIRE(output.str() == "Not correct input dictionary!\n");
	}
	std::ifstream inputFileNotExists("Dictionary.txt");
	REQUIRE(FillDictionary(inputFileNotExists, dictionary, output));
	REQUIRE(dictionary.size() == 5);
	REQUIRE(dictionary.find("cat") != dictionary.end());
	REQUIRE(dictionary.find("man") != dictionary.end());
	REQUIRE(dictionary.find("map") != dictionary.end());
	REQUIRE(dictionary.find("red") != dictionary.end());


	bool changeState = false;
	SECTION("Check dictionary values")
	{
		std::istringstream input("cat\nman\nmap\nred\n...\n\n");
		std::string outStr = R"(кошка, кот
человек
Карта
красный
)";
		std::ostringstream dialogOutput;
		DictionaryDialog(dictionary, changeState, input, dialogOutput);
		REQUIRE(!changeState);
		REQUIRE(dialogOutput.str() == outStr);
	}
	SECTION("Show new value, not memorize")
	{
		std::istringstream input("cat\nsun\n\n...\n\n");
		std::string outStr = R"(кошка, кот
Unknown word "sun". Enter a translation or an empty line for rejection.
The word "sun" is ignored.
)";
		std::ostringstream dialogOutput;
		DictionaryDialog(dictionary, changeState, input, dialogOutput);
		REQUIRE(!changeState);
		REQUIRE(dialogOutput.str() == outStr);

	}
	SECTION("Add new value and memorize")
	{
		std::istringstream input("man\nsun\nСолнце\n...\n\n");
		std::string outStr = R"(человек
Unknown word "sun". Enter a translation or an empty line for rejection.
The word "sun" is saved in the dictionary as "Солнце".
)";
		std::ostringstream dialogOutput;
		DictionaryDialog(dictionary, changeState, input, dialogOutput);
		REQUIRE(changeState);
		REQUIRE(dialogOutput.str() == outStr);
		REQUIRE(dictionary.size() == 6);
		REQUIRE(dictionary.find("sun") != dictionary.end());
	}

	SECTION("Dictionary not save and state not save")
	{
		std::string filePath = "DictionaryNotExists.txt";
		changeState = false;
		std::istringstream input("\n");
		std::ostringstream dialogOutput;
		DictionarySaveDialog(dictionary, changeState, filePath, input, dialogOutput);
		REQUIRE(!changeState);
		std::ifstream inputFileNotExists("DictionaryNotExists.txt");
		REQUIRE(!inputFileNotExists.is_open());
		inputFileNotExists.close();
		REQUIRE(dictionary.size() == 5);
		REQUIRE(dictionary.find("sun") == dictionary.end());
	}

	SECTION("Dictionary not save and state on save")
	{
		REQUIRE(dictionary.size() == 5);
		dictionary.insert(std::pair<std::string, std::string>("sun", "Солнце"));
		REQUIRE(dictionary.size() == 6);
		REQUIRE(dictionary.find("sun") != dictionary.end());
		
		std::string filePath = "DictionaryNoSave.txt";
		changeState = true;
		std::istringstream input("n\n");
		std::ostringstream dialogOutput;
		std::string outStr = R"(Do you want to save changes? Сlick on 'y' if YES, or 'n' if NO
)";
		DictionarySaveDialog(dictionary, changeState, filePath, input, dialogOutput);
		REQUIRE(changeState);
		std::ifstream inputFileNotExists("DictionaryNoSave.txt");
		REQUIRE(!inputFileNotExists.is_open());
		REQUIRE(dialogOutput.str() == outStr);
		inputFileNotExists.close();
	}
	SECTION("Dictionary save changes")
	{
		REQUIRE(dictionary.size() == 5);
		dictionary.insert(std::pair<std::string, std::string>("sun", "Солнце"));
		REQUIRE(dictionary.size() == 6);
		REQUIRE(dictionary.find("sun") != dictionary.end());
		
		std::string filePath = "DictionarySave.txt";
		changeState = true;
		std::istringstream input("y\n");
		std::ostringstream dialogOutput;
		std::string outStr = R"(Do you want to save changes? Сlick on 'y' if YES, or 'n' if NO
)";
		DictionarySaveDialog(dictionary, changeState, filePath, input, dialogOutput);
		REQUIRE(changeState);
		std::ifstream inputFileNotExists("DictionaryNoSave.txt");
		REQUIRE(!inputFileNotExists.is_open());
		inputFileNotExists.close();
		REQUIRE(dialogOutput.str() == outStr);
	}

	std::ifstream inputFileNew("DictionarySave.txt");
	//dictionary.insert(std::pair<std::string, std::string>("sun", "Солнце"));
	std::multimap <std::string, std::string> newDictionary;
	std::ostringstream newOutput;
	REQUIRE(FillDictionary(inputFileNew, newDictionary, newOutput));
	REQUIRE(newDictionary.size() == 6);
	REQUIRE(newDictionary.find("cat") != newDictionary.end());
	REQUIRE(newDictionary.find("man") != newDictionary.end());
	REQUIRE(newDictionary.find("map") != newDictionary.end());
	REQUIRE(newDictionary.find("red") != newDictionary.end());
	REQUIRE(newDictionary.find("sun") != newDictionary.end());
}

