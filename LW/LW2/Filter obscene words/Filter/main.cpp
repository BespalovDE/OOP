// Filter.cpp : Программа-фильтр, удаляющая из сообщений участников чата недопустимые слова
#include <Windows.h>
#include "Filter.h"
#include <fstream>

int main(int argc, char* argv[])
{
	//3. валидацию луче вынести, тогда ее можно протестировать
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	auto args = ParseArgs(argc, argv, std::cout);
	if (!args)
	{
		return 1;
	}
	std::ifstream inputFile(args->fileName);
	std::set <std::string> filterSet;
	if (!FillFilterSet(inputFile, filterSet, std::cout))
	{
		return 1;
	}
	ProcessingIncomingLine(filterSet, std::cin, std::cout);
}
