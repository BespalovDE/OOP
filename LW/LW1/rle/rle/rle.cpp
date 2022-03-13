// rle.cpp
//Приложение rle.exe, выполняющее RLE-компрессию бинарных файлов с сильно разреженным содержимым, а также декомпрессию 
//упакованных ею файлов.
//"$(ProjectDir)test.bat" "$(TargetPath)"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;
const unsigned char MAX_COUNT = 255;

struct InputParams
{
	//1. лучше использовать enum
	string actionPar;
	string inputPath;
	string outputPath;
};

bool CompressFile(ifstream &inputFile, ofstream &outputFile)
{
	string inputLine;
	bool firstLine = true;
	while (getline(inputFile, inputLine))
	{
		if (!firstLine)
			//поищи стандартный аналог getline, только для записи, избавит от лишний проверок
			outputFile << endl;
		firstLine = false;
		int i = 0;
		unsigned char count = 0;
		unsigned char symbol;
		unsigned char currentSybmol = inputLine[0];
		while (i < inputLine.length())
		{
			symbol = inputLine[i];
			// убрал проверку на цифры
			if (symbol == currentSybmol)
			{
				if (count == MAX_COUNT)
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
	return true;
}

bool DecompressFile(ifstream& inputFile, ofstream& outputFile)
{
	string inputLine;
	bool firstLine = true;
	while (getline(inputFile, inputLine))
	{
		if (inputLine.length() % 2 != 0)
			return false;
		if (!firstLine)
			outputFile << endl;
		firstLine = false;
		unsigned char inputNumber = 0;
		unsigned char inputChar = 0;
		int i = 0;
		while (i < inputLine.length())
		{
			inputNumber = 0;
			inputChar = 0;
			inputNumber = inputLine[i]; 
			inputChar = inputLine[i + 1];
			if (inputNumber > 0 && inputChar > 0)
			{
				for (unsigned char j = 0; j < inputNumber; j++)
					outputFile << inputChar;
			}
			if (inputNumber == 0 || inputChar == 0)
			{
				return false;
			}
			i += 2;
		} 
	}
	return true;
}

// Возможно стоит как-то разделить на функции, сейчас трудно читать
// GetInpPar предполаает что функция вернет InptParams а не bool, это может запутать. Ошибку можно выводить, например, выбрасывая исключение (поисследовать самостоятельно)
bool GetInputPar(char* argv[], InputParams &inputParams)
{
	//2. лучше проверку количества перенести сюда
	inputParams.actionPar = argv[1];
	if (inputParams.actionPar != "pack" && inputParams.actionPar != "unpack")
		return false;
	inputParams.inputPath = argv[2];
	inputParams.outputPath = argv[3];
	return true;
}

int main(int argc, char* argv[])
{
	if (argc != 4)
	{
		std::cout << "Not correct parametres!" << endl;
		return 1;
	}
	InputParams inputParams;
	if (!GetInputPar(argv, inputParams))
	{
		std::cout << "Not correct pack parameter!" << endl;
		return 1;
	}
	ifstream inputFile(inputParams.inputPath);
	ofstream outputFile(inputParams.outputPath);
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
	if (inputParams.actionPar == "pack" )
	{
		if (!CompressFile(inputFile, outputFile))
		{
			cout << "Input file has a numbers!" << endl;
			return 1;
		}
	}
	else
	{
		if (!DecompressFile(inputFile, outputFile))
		{
			cout << "Input file has the not correct structure!" << endl;
		    return 1;
		}
	}
	outputFile.close();
}

