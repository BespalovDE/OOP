// Разработайте класс CHttpUrl, выполняющий хранение httpи https–URL-ов.

#include <iostream>
#include "UrlInterface.h"

int main()
{
	UrlInterface urlInterface(std::cin, std::cout);
	while (!std::cin.eof() && !std::cin.fail())
	{
		if (!urlInterface.InterfaceUrl())
		{
			std::cout << "Empty string" << std::endl;
		}
	}
	return 0;
}
