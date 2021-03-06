﻿// findtext.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.

#include <iostream>
#include <string>
#include <fstream>
#include <filesystem>


bool SearchTextFunc(std::istream &file, const std::string &searchText)
{
	bool isFind = false;
	std::string line = "";
	int rowNumber = 1;
	while (getline(file, line))
	{
		if (line.find(searchText) != std::string::npos)
		{
			if (!isFind)
			{
				std::cout << "Text found! Rows: " + std::to_string(rowNumber);
			}
			else
			{
				std::cout << ", " + std::to_string(rowNumber);
			}
			isFind = true;
		}
		rowNumber++;
	}
	return isFind;
}

bool CheckOptions(std::istream &file, std::string &searchText) // не выводить сообщения в функциях
{
	if (!file.is_open())
	{
		std::cout << "File not exists!";
		return false;
	}
	if (searchText.empty())
	{
		std::cout << "Empty text to find!";
		return false;
	}
	return true;
}

int main(int argc, char* argv[])
{
	if (argc != 3)
	{
		std::cout << "Not correct parametres!";
		return 1;
	}
	std::string searchText = argv[2];
	std::istream file(argv[1]); // поменяли ifstream
	if (!CheckOptions(file, searchText))
	{
		return 1;
	}
	if (!SearchTextFunc(file, searchText))
	{
		std::cout << "Text not found!";
		return 1;
	}
	return 0;
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
