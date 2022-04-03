// MiniDictionary.cpp : Разработайте программу-словарь, осуществляющую перевод слов и словосочетаний, поступающих со стандартного потока ввода, 
// с английского языка на русский с использованием заданного файласловаря и выводящую результат перевода в стандартный поток вывода.
#include <fstream>
#include <Windows.h>
#include "MiniDictionary.h"
//словосочетания не обрабатываются

int main(int argc, char* argv[])
{
	SetConsoleCP(1251);// установка кодовой страницы win-cp 1251 в поток ввода
	SetConsoleOutputCP(1251); // установка кодовой страницы win-cp 1251 в поток вывода
	auto args = ParseArgs(argc, argv, std::cout);
	std::ifstream inputFile(args->fileName);
	Dictionary dictionary;
	if (inputFile.is_open() && inputFile.peek() != EOF)
	{
		if (!FillDictionary(inputFile, dictionary, std::cout))
		{
			return 1;
		}
	}
	int startDictionarySize = dictionary.size();
	inputFile.close();
	DictionaryDialog(dictionary, std::cin, std::cout);
	if (dictionary.size() != startDictionarySize)
	{
		DictionarySaveDialog(dictionary, args->fileName, std::cin, std::cout);
	}
}