// Filter.cpp : Программа-фильтр, удаляющая из сообщений участников чата недопустимые слова
// "$(ProjectDir)test.bat" "$(TargetPath)"
#include <iostream>
#include <fstream>
#include <sstream>
#include <set>
#include <algorithm>

void GetFilterSet(std::ifstream &inputStream, std::set <std::string> &filterSet)
{
	std::string word = "";
	while (inputStream >> word)
	{
		filterSet.insert(word);
	}
}

std::string GetLowerString(std::string str)
{
	std::transform(str.begin(), str.end(), str.begin(), tolower);
	return str;
}

bool IsIterator(unsigned char charSimbol)
{
	if (charSimbol >= 192 || charSimbol == 168 || charSimbol == 184) // русские буквы
	{
		return false;
	}
	if ((charSimbol >= 65 && charSimbol <= 90) || (charSimbol >= 97 && charSimbol <= 122)) // английские буквы
	{
		return false;
	}
	if (isdigit(charSimbol))
	{
		return false;
	}
	return true;
}
std::string GetWordOrSeparatorFromLineAfterIterator(std::string inputLine, int iterator)
{
	unsigned char currentChar = 0;
	std::string outputString = "";
	if (inputLine.length() <= iterator)
	{
		return outputString;
	}
	currentChar = inputLine[iterator];
	if (IsIterator(currentChar))
	{
		return outputString += currentChar;
	}
	while (!IsIterator(currentChar) && inputLine.length() > iterator)
	{
		outputString += currentChar;
		iterator++;
		if (inputLine.length() > iterator)
		{
			currentChar = inputLine[iterator];
		}
	}
	return outputString;
}

bool IsObsceneWord(const std::set <std::string> &filterSet, const std::string &inputWord)
{
	return (filterSet.find(inputWord) == filterSet.end()) ? false : true;
}

void ProcessingIncomingLine(const std::set <std::string> &filterSet)
{
	std::string inputLine = "";
	std::string inputWordOrSeparator = "";
	int iterator = 0;
	getline(std::cin, inputLine);
	while (iterator < inputLine.length())
	{
		inputWordOrSeparator = GetWordOrSeparatorFromLineAfterIterator(inputLine, iterator);
		iterator += inputWordOrSeparator.length();
		if (inputWordOrSeparator.length() > 0)
		{
			if (!IsObsceneWord(filterSet, GetLowerString(inputWordOrSeparator)))
			{
				std::cout << inputWordOrSeparator;
			}
		}
	}
	std::cout << std::endl;
}

int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		std::cout << "Not correct parametres!" << std::endl;
		return 1;
	}
	std::string filePath = argv[1];
	std::ifstream inputFile(filePath);
	std::set <std::string> filterSet;
	if (inputFile.is_open())
	{
		GetFilterSet(inputFile, filterSet);
		if (filterSet.empty())
		{
			std::cout << "Empty set of obscene words!" << std::endl;
			return 1;
		}
	}
	ProcessingIncomingLine(filterSet);
}
