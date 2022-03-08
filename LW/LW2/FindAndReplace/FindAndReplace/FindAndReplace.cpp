// FindAndReplace.cpp : Программа, заменяющая все вхождения искомой строки в стандартном потоке ввода на строку-заменитель и выводящая результат в стандартный поток вывода
//

#include <iostream>

struct SearchAndReplaceText
{
	std::string search = "";
	std::string replace = "";
};

std::string FindAndReplace(const std::string& subject, const std::string& search, std::string& replace)
{
	std::string resultString = "";
	size_t startPos = 0;
	size_t pos = std::string::npos;
	pos = subject.find(search, startPos);
	while (pos != std::string::npos)
	{
		resultString.append(subject, startPos, pos - startPos);
		resultString.append(replace);
		startPos = pos + search.length();
		pos = subject.find(search, startPos);
	}
	resultString.append(subject, startPos, subject.length() - startPos);
	return resultString;
}

int main(int argc, char* argv[])
{
	if (argc != 3)
	{
		std::cout << "Not correct parametres!" << std::endl;
		return 1;
	}
	std::string search = argv[1];
	std::string replace = argv[2];
	std::string subject = "Find some text or not. Need text in file. Some file text.";
	subject = FindAndReplace(subject, search, replace);
	std::cout << subject << std::endl;
}

