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

std::optional<Args> ParseArgs(int argc, char *argv[], std::ostream &outStream);
bool FillDictionary(std::ifstream &inputStream, std::multimap <std::string, std::string> &inputDictionary, std::ostream &outStream);
void DictionaryDialog(std::multimap <std::string, std::string> &dictionary, bool &changeState, std::istream &inStream, std::ostream &outStream);
void DictionarySaveDialog(std::multimap <std::string, std::string> &dictionary, bool changeState, const std::string &filePath, std::istream &inStream, std::ostream &outStream);