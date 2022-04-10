#pragma once
#include <iostream>
#include <sstream>
#include <map>
#include <algorithm>
#include <optional>
#include <locale>

struct Args
{
	std::string fileName;
};

struct ConsoleDialog
{
	std::istream &inStream; 
	std::ostream &outStream;
};

using Dictionary = std::multimap <std::string, std::string>; // псевдоним типа для словаря
const std::string COMMAND_DICTIONARY_EXIT = "...";
const std::string COMMAND_DICTIONARY_SAVE = "y";
const std::string COMMAND_DICTIONARY_DONT_SAVE = "n";
const std::string DELIMITER = ">";


std::optional<Args> ParseArgs(int argc, char *argv[], std::ostream &outStream);
// через istream и тестирование через него
bool FillDictionary(Dictionary &inputDictionary, ConsoleDialog consoleDialog);
void DictionaryDialog(Dictionary &dictionary, ConsoleDialog consoleDialog);
void DictionarySaveDialog(Dictionary &dictionary, const std::string &filePath, ConsoleDialog consoleDialog);