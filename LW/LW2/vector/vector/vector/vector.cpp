// vector.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//Программа, выполняющая считывание массива чисел с плавающей запятой, разделяемых пробелами, из стандартного потока ввода в vector, обрабатывающую его согласно заданию Вашего варианта(*max  /min) 
// и выводящую в стандартный поток полученный массив (разделенный пробелами).
//"$(ProjectDir)test.bat" "$(TargetPath)"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <string>


struct MaxAndMinVectorNumber
{
	double minVectorNumber;
	double maxVectorNumber;
};

bool GetVectorData(std::ifstream &inputFile, std::vector<double_t> &v, MaxAndMinVectorNumber &VectorNumbers)
{
	VectorNumbers.maxVectorNumber = -DBL_MAX;
	VectorNumbers.minVectorNumber = DBL_MAX;
	std::string inputLine;
	while (getline(inputFile, inputLine))
	{
		double inputNumber = NULL;
		std::istringstream strm(inputLine);
		do
		{
			inputNumber = NULL;
			try
			{
				strm >> inputNumber;
			}
			catch (const std::exception& /* error*/)
			{
				return false;
			}
			if (inputNumber != NULL)
			{
				if (VectorNumbers.maxVectorNumber < inputNumber)
					VectorNumbers.maxVectorNumber = inputNumber;
				if (VectorNumbers.minVectorNumber > inputNumber)
					VectorNumbers.minVectorNumber = inputNumber;
				v.push_back(inputNumber);
			}
		} while (inputNumber != NULL);
	}
	if (VectorNumbers.maxVectorNumber == -DBL_MAX && VectorNumbers.minVectorNumber == DBL_MAX)
		return false;
	return true;
}

void MultiplyVectorValuesOnMaxMinVectorNumbers(std::vector<double_t> &v, const MaxAndMinVectorNumber &VectorNumbers)
{
	for (auto &num : v) {

		num = num * VectorNumbers.maxVectorNumber / VectorNumbers.minVectorNumber;
	}
}

void SortVector(std::vector<double_t> &v)
{
	std::sort(v.begin(), v.end());
}

void WriteVecror(std::vector<double_t> &v)
{
	copy(v.begin(), v.end(), std::ostream_iterator<double_t>(std::cout, " "));
	std::cout << std::endl;
}

int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		std::cout << "Not correct parametres!" << std::endl;
		return 1;
	}
	std::string inputPath = argv[1];
	std::ifstream inputFile(inputPath);
	if (!inputFile.is_open())
	{
		std::cout << "Failed to open file for reading!" << std::endl;
		return 1;
	}
	std::vector<double_t> v;
	MaxAndMinVectorNumber maxMinVectorNumbers;
	if (!GetVectorData(inputFile, v, maxMinVectorNumbers))
	{
		std::cout << "Failed to reading vector!" << std::endl;
		return 1;
	}
	MultiplyVectorValuesOnMaxMinVectorNumbers(v, maxMinVectorNumbers);
	SortVector(v);
	WriteVecror(v);
}

