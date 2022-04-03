// Filter.cpp : Программа-фильтр, удаляющая из сообщений участников чата недопустимые слова
#include "Filter.h"
#include <fstream>

std::optional<Args> ParseArgs(int argc, char *argv[], std::ostream &outStream)
{
	if (argc != 1)
	{
		outStream << "Invalid arguments count.\n";
		outStream << "Usage: Filter.exe <input file name>\n";
		return std::nullopt;
	}
	Args args;
	args.fileName = argv[1];
	return args;
}

std::set <std::string> GetFilterSet(std::ifstream &inputStream)
{
	std::string word = "";
	std::set <std::string> filterSet;
	while (inputStream >> word)
	{
		filterSet.insert(word);
	}
	return filterSet;
}

bool FillFilterSet(std::ifstream &inputStream, std::set <std::string> &filterSet, std::ostream &outStream)
{
	bool filterSetIsExist = false;
	if (inputStream.is_open())
	{
		filterSet = GetFilterSet(inputStream);
		if (filterSet.empty())
		{
			outStream << "Empty set of obscene words!" << std::endl;
		}
		else
		{
			filterSetIsExist = true;
		}
	}
	else
	{
		outStream << "Input file is empty!" << std::endl;
	}
	return filterSetIsExist;
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

void ProcessingLine(const std::set <std::string> &filterSet, const std::string &stringLine, std::ostream &outStream)
{
	std::string inputWordOrSeparator = "";
	int iterator = 0;
	while (iterator < stringLine.length())
	{
		inputWordOrSeparator = GetWordOrSeparatorFromLineAfterIterator(stringLine, iterator);
		iterator += inputWordOrSeparator.length();
		if (inputWordOrSeparator.length() > 0)
		{
			if (!IsObsceneWord(filterSet, GetLowerString(inputWordOrSeparator)))
			{
				outStream << inputWordOrSeparator;
			}
		}
	}
	outStream << std::endl;
}

void ProcessingIncomingLine(const std::set <std::string> &filterSet, std::istream &inStream, std::ostream &outStream)
{
	std::string inputLine = "";
	std::string inputWordOrSeparator = "";
	int iterator = 0;
	getline(inStream, inputLine);
	ProcessingLine(filterSet, inputLine, outStream);
}
