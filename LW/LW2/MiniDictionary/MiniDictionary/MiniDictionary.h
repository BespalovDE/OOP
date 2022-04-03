#pragma once
#include <iostream>
#include <sstream>
#include <map>
#include <algorithm>
#include <optional>

struct Args
{
	std::string fileName;
};

using Dictionary = std::multimap <std::string, std::string>; // псевдоним типа для словаря
const std::string COMMAND_DICTIONARY_EXIT = "...";
const std::string COMMAND_DICTIONARY_SAVE = "y";
const std::string COMMAND_DICTIONARY_DONT_SAVE = "n";


std::optional<Args> ParseArgs(int argc, char *argv[], std::ostream &outStream);
// через istream и тестирование через него
bool FillDictionary(std::istream &inputStream, Dictionary &inputDictionary, std::ostream &outStream);
void DictionaryDialog(Dictionary &dictionary, std::istream &inStream, std::ostream &outStream);
void DictionarySaveDialog(Dictionary &dictionary, const std::string &filePath, std::istream &inStream, std::ostream &outStream);