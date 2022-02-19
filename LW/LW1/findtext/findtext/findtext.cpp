// findtext.cpp
#include <iostream>
#include <string>
#include <fstream>
#include <filesystem>
//отделить вывод от поиска

void ShowMessage(const std::string &message)
{
	std::cout << message;
}

bool SearchText(std::istream &file, const std::string &searchText)
{
	bool isFound = false;
	std::string line = "";
	int rowNumber = 1;
	while (getline(file, line))
	{
		if (line.find(searchText) != std::string::npos)
		{
			if (!isFound)
			{
				ShowMessage("Text found! Rows: " + std::to_string(rowNumber));
			}
			else
			{
				ShowMessage(", " + std::to_string(rowNumber));
			}
			isFound = true;
		}
		rowNumber++;
	}
	return isFound;
}

bool CheckOptions(std::ifstream &file, std::string &searchText)
{
	if (!file.is_open())
	{
		ShowMessage("File not exists!");
		return false;
	}
	if (searchText.empty())
	{
		ShowMessage("Empty text to find!");
		return false;
	}
	return true;
}

int main(int argc, char* argv[])
{
	if (argc != 3)
	{
		ShowMessage("Not correct parametres!");
		return 1;
	}
	std::string searchText = argv[2];
	std::ifstream file(argv[1]);
	if (!CheckOptions(file, searchText))
	{
		return 1;
	}
	if (!SearchText(file, searchText))
	{
		ShowMessage("Text not found!");
		return 1;
	}
	return 0;
}