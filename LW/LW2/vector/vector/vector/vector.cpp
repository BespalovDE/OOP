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

bool GetVectorData(std::ifstream &inputFile, std::vector<double_t> &inputVector, double &multiplyValue)
{
	double maxVectorNumber = -DBL_MAX;
	double minVectorNumber = DBL_MAX;
	std::string inputLine;
	while (getline(inputFile, inputLine))
	{
		double inputNumber;
		std::istringstream strm(inputLine);
		while (strm >> inputNumber)
		{
				if (maxVectorNumber < inputNumber)
					maxVectorNumber = inputNumber;
				if (minVectorNumber > inputNumber)
					minVectorNumber = inputNumber;
				inputVector.push_back(inputNumber);
		}
		if (abs(minVectorNumber) < DBL_EPSILON)
		{
			return false;
		}
		try
		{
			multiplyValue = maxVectorNumber / minVectorNumber;
		}
		catch (const std::exception& /* error*/)
		{
			return false;
		}
	}
	return !(maxVectorNumber == -DBL_MAX && minVectorNumber == DBL_MAX);
}

void MultiplyVectorValuesOnNumber(std::vector<double_t> &v, const double Number)
{
	for (auto &num : v)
	{
		num = num * Number;
	}
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
	std::vector<double_t> inputVector;
	double multiplyValue = 0;
	if (!GetVectorData(inputFile, inputVector, multiplyValue))
	{
		std::cout << "Failed to reading vector data!" << std::endl;
		return 1;
	}
	MultiplyVectorValuesOnNumber(inputVector, multiplyValue);
	std::sort(inputVector.begin(), inputVector.end());
	WriteVecror(inputVector);
}