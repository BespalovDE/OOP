// findtext.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.

#include <iostream>
#include <string>
#include <fstream>
#include <filesystem>


void searchTextFunc(std::ifstream &file, std::string &searchText, int &numberOfFind)
{
	std::string line = "";
	int rowNumber = 1;
	while (getline(file, line))
	{
		size_t found = line.find(searchText);
		if (found != std::string::npos)
		{
			if (numberOfFind == 0)
			{
				std::cout << "Text found! Rows: " + std::to_string(rowNumber);
			}
			else
			{
				std::cout << ", " + std::to_string(rowNumber);
			}
			numberOfFind++;
		}
		rowNumber++;
	}
}

int main(int argc, char* argv[])
{
	if (argc != 3)
	{
		std::cout << "Not correct parametres!";
		return 1;
	}
	else
	{
		std::string fileName = argv[1];
		std::string searchText = argv[2];
		std::ifstream file(fileName.c_str());
		if (!file.is_open())
		{
			std::cout << "File not exists!";
			return 1;
		}
		if (searchText.length() < 1)
		{
			std::cout << "Empty text to find!";
			return 1;
		}
		int numberOfFind = 0;
		searchTextFunc(file, searchText, numberOfFind);
		if (numberOfFind == 0)
		{
			std::cout << "Text not found!";
			return 1;
		}
		return 0;
	}
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
