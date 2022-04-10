#include "MiniDictionary.h"
#include <fstream>

std::optional<Args> ParseArgs(int argc, char* argv[], std::ostream& outStream)
{
	if (argc != 2)
	{
		outStream << "Invalid arguments count.\n";
		outStream << "Usage: MiniDictionary.exe <input file name>\n";
		return std::nullopt;
	}
	Args args;
	args.fileName = argv[1];
	return args;
}

std::string GetLowerString(std::string str)
{
	//c tolower надо через unsigned char +
	std::transform(str.begin(), str.end(), str.begin(), [](unsigned char ch) { return std::tolower(static_cast<unsigned char>(ch), std::locale("Russian_Russia.1251")); });
	return str;
}

//считывать из потока а не файла +
Dictionary GetDictionary(std::istream &inputStream)
{
	std::string line;
	Dictionary inputDictionary;
	const int offset = DELIMITER.length();
	while (getline(inputStream, line))
	{
		size_t posBeforeWord, posBeforeTranslation;
		if (((posBeforeWord = line.find(DELIMITER)) == 0) && ((posBeforeTranslation = line.find(DELIMITER, offset)) != std::string::npos))
		{
			inputDictionary.emplace(GetLowerString(line.substr(posBeforeWord + offset, posBeforeTranslation - offset)), line.substr(posBeforeTranslation + offset));
		}
	}
	return inputDictionary;
}

bool FillDictionary(Dictionary &inputDictionary, ConsoleDialog consoleDialog)
{
	inputDictionary = GetDictionary(consoleDialog.inStream);
	if (inputDictionary.empty())
	{
		consoleDialog.outStream << "Not correct input dictionary!" << std::endl;
		return false;
	}
	return true;
}

void SaveDictionary(Dictionary &dictionary, const std::string &filePath)
{
	std::ofstream inputFile(filePath);
	for (auto outputDictionary = dictionary.begin(); outputDictionary != dictionary.end(); ++outputDictionary)
	{
		inputFile << DELIMITER << outputDictionary->first << DELIMITER << outputDictionary->second << std::endl;
	}
	inputFile.close();
}

std::string SearchWordInDictionary(const Dictionary &dictionary, const std::string &inputString)
{
	std::string resultString = "";
	std::string keyString = GetLowerString(inputString);
	for (auto it = dictionary.equal_range(keyString).first; it != dictionary.equal_range(keyString).second; ++it)
	{
		if (resultString.length() > 0)
		{
			resultString += ", ";
		}
		resultString += it->second;
	}
	return resultString;
}
// лучше возвращать признак тоо что словарь изменен, чем тащить переменную +
// узнать что словарь изменился можно по его размеру +
void SaveNewWordDialog(Dictionary &dictionary, const std::string &inputString, ConsoleDialog consoleDialog)
{
	consoleDialog.outStream << "Unknown word \"" + inputString + "\". Enter a translation or an empty line for rejection." << std::endl;
	std::string newWord = "";
	getline(consoleDialog.inStream, newWord);
	if (newWord.length() > 0)
	{
		dictionary.emplace(GetLowerString(inputString), newWord); //было: dictionary.insert(std::pair<std::string, std::string>(GetLowerString(inputString), newWord)); +
		consoleDialog.outStream << "The word \"" + inputString + "\" is saved in the dictionary as \"" + newWord + "\"." << std::endl;
	}
	else
	{
		consoleDialog.outStream << "The word \"" + inputString + "\" is ignored." << std::endl;
	}
}

void DictionaryDialog(Dictionary &dictionary, ConsoleDialog consoleDialog)
{
	std::string inputString = "";
	while (inputString != COMMAND_DICTIONARY_EXIT)
	{
		inputString = "";
		getline(consoleDialog.inStream, inputString);
		if (!inputString.empty() && inputString != COMMAND_DICTIONARY_EXIT) // empty на строку, было inputString.length() > 0 +
		{
			std::string stringFromDictionary = SearchWordInDictionary(dictionary, inputString);
			if (stringFromDictionary.length() > 0)
			{
				consoleDialog.outStream << stringFromDictionary << std::endl;
			}
			else
			{
				SaveNewWordDialog(dictionary, inputString, consoleDialog);
			}
		}

	}
}

// changeState здесь не нужен +
// вход и выход в одну структуру с 2я ссылками +
void DictionarySaveDialog(Dictionary &dictionary, const std::string &filePath, ConsoleDialog consoleDialog)
{
		std::string inputString;
		do
		{
			consoleDialog.outStream << "Do you want to save changes? Сlick on \'y\' if YES, or \'n\' if NO" << std::endl;;
			getline(consoleDialog.inStream, inputString);
			inputString = GetLowerString(inputString);
			if (inputString == COMMAND_DICTIONARY_SAVE)
			{
				SaveDictionary(dictionary, filePath);
			}
		} while (inputString != COMMAND_DICTIONARY_SAVE && inputString != COMMAND_DICTIONARY_DONT_SAVE);
}