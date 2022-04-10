#include <iostream>
#include <fstream>
#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "../MiniDictionary/MiniDictionary.h"

TEST_CASE("Main test")
{
	std::ostringstream output;
	Dictionary dictionary;
	SECTION("Dictionary is empty")
	{
		std::string outStr = R"(Not correct input dictionary!
)";
		//std::ifstream inputFileNotExists("EmptyDictionary.txt");
		std::istringstream inputFileNotExists("");
		REQUIRE(!FillDictionary(dictionary, { inputFileNotExists, output }));
		REQUIRE(dictionary.size() == 0);
		REQUIRE(output.str() == outStr);
	}
	SECTION("Dialog")
	{
		std::istringstream inputFile(">cat>кошка\n>cat>кот\n>man>человек\n>map>Карта\n>red>красный\n\n");
		REQUIRE(FillDictionary(dictionary, { inputFile, output }));
		SECTION("Check dictionary values is exists")
		{
			REQUIRE(dictionary.size() == 5);
			REQUIRE(dictionary.find("cat") != dictionary.end());
			REQUIRE(dictionary.find("man") != dictionary.end());
			REQUIRE(dictionary.find("map") != dictionary.end());
			REQUIRE(dictionary.find("red") != dictionary.end());
		}

		bool changeState = false;
		SECTION("Check dictionary values in dialog")
		{
			std::istringstream input("cat\nman\nmap\nred\n...\n\n");
			std::string outStr = R"(кошка, кот
человек
Карта
красный
)";
			std::ostringstream dialogOutput;
			int startDictionarySize = dictionary.size();
			DictionaryDialog(dictionary, { input, dialogOutput });
			REQUIRE(dictionary.size() == startDictionarySize);
			REQUIRE(dialogOutput.str() == outStr);
		}
		SECTION("Show new value, not memorize in dictionary")
		{
			std::istringstream input("cat\nsun\n\n...\n\n");
			std::string outStr = R"(кошка, кот
Unknown word "sun". Enter a translation or an empty line for rejection.
The word "sun" is ignored.
)";
			std::ostringstream dialogOutput;
			int startDictionarySize = dictionary.size();
			DictionaryDialog(dictionary, { input, dialogOutput });
			REQUIRE(dictionary.size() == startDictionarySize);
			REQUIRE(dialogOutput.str() == outStr);

		}
		SECTION("Add new value and memorize in dictionary")
		{
			std::istringstream input("man\nsun\nСолнце\n...\n\n");
			std::string outStr = R"(человек
Unknown word "sun". Enter a translation or an empty line for rejection.
The word "sun" is saved in the dictionary as "Солнце".
)";
			std::ostringstream dialogOutput;
			int startDictionarySize = dictionary.size();
			DictionaryDialog(dictionary, { input, dialogOutput });
			REQUIRE(dialogOutput.str() == outStr);
			REQUIRE(dictionary.size() == startDictionarySize + 1);
			REQUIRE(dictionary.find("sun") != dictionary.end());
		}

		SECTION("Dictionary Save Dialog")
		{
			SECTION("Dictionary save dialog: not save changes")
			{
				int startDictionarySize = dictionary.size();
				REQUIRE(dictionary.size() == startDictionarySize);
				dictionary.emplace("sun", "Солнце");
				REQUIRE(dictionary.size() == startDictionarySize + 1);
				REQUIRE(dictionary.find("sun") != dictionary.end());

				std::string filePath = "DictionaryNoSave.txt";
				std::istringstream input("n\n\n");
				std::ostringstream dialogOutput;
				std::string outStr = R"(Do you want to save changes? Сlick on 'y' if YES, or 'n' if NO
)";
				DictionarySaveDialog(dictionary, filePath, { input, dialogOutput });
				std::ifstream inputFileNotExists("DictionaryNoSave.txt");
				REQUIRE(!inputFileNotExists.is_open());
				REQUIRE(dialogOutput.str() == outStr);
				inputFileNotExists.close();
				REQUIRE(dictionary.size() == startDictionarySize + 1);
			}

			int startDictionarySize = dictionary.size();
			REQUIRE(dictionary.size() == startDictionarySize);
			dictionary.emplace("sun", "Солнце");
			REQUIRE(dictionary.size() == startDictionarySize + 1);
			REQUIRE(dictionary.find("sun") != dictionary.end());

			SECTION("Dictionary save dialog: Dictionary not save with double ask")
			{
				std::string filePath = "DictionaryNoSave.txt";
				changeState = true;
				std::istringstream input("PP\nn\n");
				std::ostringstream dialogOutput;
				std::string outStr = R"(Do you want to save changes? Сlick on 'y' if YES, or 'n' if NO
Do you want to save changes? Сlick on 'y' if YES, or 'n' if NO
)";
				DictionarySaveDialog(dictionary, filePath, { input, dialogOutput });
				std::ifstream inputFileNotExists("DictionaryNoSave.txt");
				REQUIRE(!inputFileNotExists.is_open());
				REQUIRE(dialogOutput.str() == outStr);
				inputFileNotExists.close();
				REQUIRE(dictionary.size() == startDictionarySize + 1);
			}

			SECTION("Dictionary save dialog: Dictionary save changes")
			{
				std::string filePath = "DictionarySave.txt";
				std::istringstream input("y\n");
				std::ostringstream dialogOutput;
				std::string outStr = R"(Do you want to save changes? Сlick on 'y' if YES, or 'n' if NO
)";
				DictionarySaveDialog(dictionary, filePath, { input, dialogOutput });
				std::ifstream inputFileNotExists("DictionarySave.txt");
				REQUIRE(inputFileNotExists.is_open());
				inputFileNotExists.close();
				REQUIRE(dialogOutput.str() == outStr);
			}
			SECTION("Open new saved dictionary to check values")
			{
				std::ifstream inputFileNew("DictionarySave.txt");
				//dictionary.insert(std::pair<std::string, std::string>("sun", "Солнце"));
				Dictionary newDictionary;
				std::ostringstream newOutput;
				REQUIRE(FillDictionary(newDictionary, { inputFileNew, newOutput }));
				REQUIRE(newDictionary.size() == startDictionarySize + 1);
				REQUIRE(newDictionary.find("cat") != newDictionary.end());
				REQUIRE(newDictionary.find("man") != newDictionary.end());
				REQUIRE(newDictionary.find("map") != newDictionary.end());
				REQUIRE(newDictionary.find("red") != newDictionary.end());
				REQUIRE(newDictionary.find("sun") != newDictionary.end());
			}
		}
	}
}

