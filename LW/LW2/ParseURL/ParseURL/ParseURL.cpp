// ParseURL.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
#include <iostream>
#include "ParserURL.h"

void GetParseLine(std::istream &input, std::ostream &output)
{
    std::string url;
    Protocol protocol;
    int port = 0;
    std::string host;
    std::string document;
    getline(input, url);
    if (ParseURL(url, protocol, port, host, document))
    {
        output << url << std::endl;
        output << "HOST: " << host << std::endl;
        output << "PORT: " << port << std::endl;
        output << "DOC: " << document << std::endl;
    }
    else
    {
        output << "Not correct URL!" << std::endl;
    }
}

int main()
{
    SetConsoleCP(1251);// установка кодовой страницы win-cp 1251 в поток ввода
    SetConsoleOutputCP(1251); // установка кодовой страницы win-cp 1251 в поток вывода
	while (!std::cin.eof() && !std::cin.fail())
	{	  
        GetParseLine(std::cin, std::cout);
	}
	return 0;
}

