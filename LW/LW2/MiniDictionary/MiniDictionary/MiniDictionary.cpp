// MiniDictionary.cpp : Разработайте программу-словарь, осуществляющую перевод слов и словосочетаний, поступающих со стандартного потока ввода, 
// с английского языка на русский с использованием заданного файласловаря и выводящую результат перевода в стандартный поток вывода.

#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <algorithm>
#include <Windows.h>

std::string GetLowerString(std::string str)
{
	std::transform(str.begin(), str.end(), str.begin(), tolower);
	return str;
}

bool GetDictionary(std::ifstream &inputStream, std::multimap <std::string, std::string> &inputDictionary)
{
	bool existValues = false;
	std::string key = "";
	std::string value = "";
	while (inputStream >> key >> value)
	{
		inputDictionary.insert(std::pair<std::string, std::string>(GetLowerString(key), value));
		existValues = true;
	}
	return existValues;
}

void DictionaryChangesSave(std::multimap <std::string, std::string> &dictionary, const std::string &filePath)
{
	std::ofstream inputFile(filePath);
	//inputFile << outputDictionary->first << " " << outputDictionary->second << std::endl;
	for (auto outputDictionary = dictionary.begin(); outputDictionary != dictionary.end(); ++outputDictionary)
	{
		inputFile << outputDictionary->first << " " << outputDictionary->second << std::endl;
	}
	inputFile.close();
}

std::string SearchStringInDictionary(const std::multimap <std::string, std::string>& dictionary, const std::string &inputString)
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

void SaveNewWordDialog(std::multimap <std::string, std::string> &dictionary, const std::string &inputString, bool & changeState)
{
	std::cout << "Unknown word \"" + inputString + "\". Enter a translation or an empty line for rejection." << std::endl;
	std::string newWord = "";
	getline(std::cin, newWord);
	if (newWord.length() > 0)
	{
		dictionary.insert(std::pair<std::string, std::string>(GetLowerString(inputString), newWord));
	    changeState = true;
		"The word \"" + inputString + "\" is saved in the dictionary as \"" + newWord + "\".";
	}
	else
	{
		std::cout << "The word \"" + inputString + "\" is ignored." << std::endl;
	}
}

void DictionaryDialog(std::multimap <std::string, std::string> &dictionary, bool& changeState)
{
	std::string inputString = "";
	while (inputString != "...")
	{
		inputString = "";
		getline(std::cin, inputString);
		if (inputString.length() > 0 && inputString != "...")
		{
			std::string stringFromDictionary = SearchStringInDictionary(dictionary, inputString);
			if (stringFromDictionary.length() > 0)
			{
				std::cout << stringFromDictionary << std::endl;
			}
			else
			{
				SaveNewWordDialog(dictionary, inputString, changeState);
			}
		}

	}
}

void DictionarySaveDialog(std::multimap <std::string, std::string> &dictionary, bool changeState, const std::string &filePath)
{
	DictionaryDialog(dictionary, changeState);
	if (changeState)
	{
		std::string inputString = "";
		do
		{
			std::cout << "Do you want to save changes? Сlick on \'y\' if YES, or \'n\' if NO" << std::endl;;
			getline(std::cin, inputString);
			inputString = GetLowerString(inputString);
			if (inputString == "y")
			{
				DictionaryChangesSave(dictionary, filePath);
			}
		} while (inputString != "y" && inputString != "n");
	}
}

int main(int argc, char* argv[])
{
	SetConsoleCP(1251);// установка кодовой страницы win-cp 1251 в поток ввода
	SetConsoleOutputCP(1251); // установка кодовой страницы win-cp 1251 в поток вывода
	if (argc != 2)
	{
		std::cout << "Not correct parametres!" << std::endl;
		return 1;
	}
	bool changeState = false;
	std::string filePath = argv[1];
	std::ifstream inputFile(filePath);
	std::multimap <std::string, std::string> dictionary;
	if (inputFile.is_open())
	{
		if (!GetDictionary(inputFile, dictionary))
		{
			std::cout << "Not correct input dictionary!" << std::endl;
			return 1;
		}
	}
	else
	{
		changeState = true;
	}
	inputFile.close();
	DictionarySaveDialog(dictionary, changeState, filePath);
}

// "$(ProjectDir)test.bat" "$(TargetPath)"

/*
%program% "text" "cat" < inputEmpty.txt >%OUT%
fc.exe %OUT% "%~dp0notCorrectInputString.txt" >nul
IF ERRORLEVEL 1 goto :testFailed
echo OK3

%program% "text" "cat" < inputText.txt >%OUT%
fc.exe %OUT% "%~dp0catResult.txt" >nul
IF ERRORLEVEL 1 goto :testFailed
echo OK4

%program% "Summer" "cat" < inputText2.txt >%OUT%
fc.exe %OUT% "%~dp0notFound.txt" >nul
IF ERRORLEVEL 1 goto :testFailed
echo OK5
*/
