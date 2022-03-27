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
	std::transform(str.begin(), str.end(), str.begin(), tolower);
	return str;
}

std::multimap <std::string, std::string> GetDictionary(std::ifstream &inputStream)
{
	std::string key = "";
	std::string value = "";
	std::multimap <std::string, std::string> inputDictionary;
	while (inputStream >> key >> value)
	{
		inputDictionary.insert(std::pair<std::string, std::string>(GetLowerString(key), value));
	}
	return inputDictionary;
}

bool FillDictionary(std::ifstream &inputStream, std::multimap <std::string, std::string> &inputDictionary, std::ostream &outStream)
{
	if (inputStream.is_open() && inputStream.peek() != EOF)
	{
		inputDictionary = GetDictionary(inputStream);
		if (inputDictionary.empty())
		{
			outStream << "Not correct input dictionary!" << std::endl;
			return false;
		}
	}
	return true;
}

void DictionaryChangesSave(std::multimap <std::string, std::string> &dictionary, const std::string &filePath)
{
	std::ofstream inputFile(filePath);
	for (auto outputDictionary = dictionary.begin(); outputDictionary != dictionary.end(); ++outputDictionary)
	{
		inputFile << outputDictionary->first << " " << outputDictionary->second << std::endl;
	}
	inputFile.close();
}

std::string SearchWordInDictionary(const std::multimap <std::string, std::string>& dictionary, const std::string &inputString)
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

void SaveNewWordDialog(std::multimap <std::string, std::string> &dictionary, const std::string &inputString, bool & changeState, std::istream &inStream, std::ostream &outStream)
{
	outStream << "Unknown word \"" + inputString + "\". Enter a translation or an empty line for rejection." << std::endl;
	std::string newWord = "";
	getline(inStream, newWord);
	if (newWord.length() > 0)
	{
		dictionary.insert(std::pair<std::string, std::string>(GetLowerString(inputString), newWord));
	    changeState = true;
		outStream << "The word \"" + inputString + "\" is saved in the dictionary as \"" + newWord + "\"." << std::endl;
	}
	else
	{
		outStream << "The word \"" + inputString + "\" is ignored." << std::endl;
	}
}

void DictionaryDialog(std::multimap <std::string, std::string> &dictionary, bool &changeState, std::istream &inStream, std::ostream &outStream)
{
	std::string inputString = "";
	while (inputString != "...")
	{
		inputString = "";
		getline(inStream, inputString);
		if (inputString.length() > 0 && inputString != "...")
		{
			std::string stringFromDictionary = SearchWordInDictionary(dictionary, inputString);
			if (stringFromDictionary.length() > 0)
			{
				outStream << stringFromDictionary << std::endl;
			}
			else
			{
				SaveNewWordDialog(dictionary, inputString, changeState, inStream, outStream);
			}
		}

	}
}

void DictionarySaveDialog(std::multimap <std::string, std::string> &dictionary, bool changeState, const std::string &filePath, std::istream &inStream, std::ostream &outStream)
{
	if (changeState)
	{
		std::string inputString = "";
		do
		{
			outStream << "Do you want to save changes? Сlick on \'y\' if YES, or \'n\' if NO" << std::endl;;
			getline(inStream, inputString);
			inputString = GetLowerString(inputString);
			if (inputString == "y")
			{
				DictionaryChangesSave(dictionary, filePath);
			}
		} while (inputString != "y" && inputString != "n");
	}
}