// rle.cpp "$(ProjectDir)test.bat" "$(TargetPath)"

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;
const int maxCount = 255;

bool CompressFile(ifstream &inputFile, ofstream &outputFile)
{
	string inputLine;
	bool firstLine = true;
	while (getline(inputFile, inputLine))
	{
		if (!firstLine)
			outputFile << endl;
		firstLine = false;
		int i = 0;
		int count = 0;
		char symbol;
		char currentSybmol = inputLine[0];
		while (i < inputLine.length())
		{
			symbol = inputLine[i];
			if (isdigit(symbol))
			{
				return 1;
			}
			if (symbol == currentSybmol)
			{
				if (count == maxCount)
				{
					outputFile << count << currentSybmol;
					count = 0;
				}
				count++;
			}
			else
			{
				outputFile << count << currentSybmol;
				currentSybmol = symbol;
				count = 1;
			}
			++i;
	    }
		outputFile << count << currentSybmol;
	}
	return 0;
}

bool DecompressFile(ifstream& inputFile, ofstream& outputFile)
{
	string inputLine;
	bool firstLine = true;
	while (getline(inputFile, inputLine))
	{
		if (inputLine.length() < 2 || isdigit(inputLine[inputLine.length() - 1]) || !isdigit(inputLine[inputLine.length() - 2]))
			return 1;
		if (!firstLine)
			outputFile << endl;
		firstLine = false;
		int inputNumber = 0;
		char inputChar = 0;
		istringstream strm(inputLine);
		do
		{
			inputNumber = 0;
			inputChar = 0;
			strm >> inputNumber >> inputChar;
			if (inputNumber > 255)
			{
				return 1;
			}
			if (inputNumber > 0 && inputChar > 0)
			{
				for (int i = 0; i < inputNumber; i++)
					outputFile << inputChar;
			}
		} while (inputNumber > 0 && inputChar > 0);
		if (inputNumber > 0 || inputChar > 0)
		{
			return 1;
		}
	}
	return 0;
}

int main(int argc, char* argv[])
{
	if (argc != 4)
	{
		std::cout << "Not correct parametres!" << endl;
		return 1;
	}
	string packParam = argv[1];
	if (packParam != "pack" && packParam != "unpack")
	{
		std::cout << "Not correct pack parameter!" << endl;
		return 1;
	}
	ifstream inputFile(argv[2]);
	ofstream outputFile(argv[3]);
	if (!inputFile.is_open())
	{
		cout << "Failed to open file for reading!" << endl;
		return 1;
	}
	if (!outputFile.is_open())
	{
		cout << "Failed to open file for writing!" << endl;
		return 1;
	}
	if (packParam == "pack" )
	{
		if (CompressFile(inputFile, outputFile))
		{
			cout << "Input file has a numbers!" << endl;
			return 1;
		}
	}
	else
	{
		if (DecompressFile(inputFile, outputFile))
		{
			cout << "Input file has the not correct structure!" << endl;
		    return 1;
		}
	}
	outputFile.close();
}

