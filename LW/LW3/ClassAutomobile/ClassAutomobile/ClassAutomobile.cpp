// ClassAutomobile.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
#include <iostream>
#include "AutomobileInterface.h"

int main()
{
    Automobile automobile;
    AutomobileInterface automobileInterface(automobile, std::cin, std::cout);
	while (!std::cin.eof() && !std::cin.fail())
	{
		std::cout << "> ";
		if (!automobileInterface.InterfaceCommand())
		{
			//std::cout << "Unknown command!\n";
		}
	}
	return 0;
}
