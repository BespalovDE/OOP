// flipbyte.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <string>
#include <exception>

unsigned char reverseByte(unsigned char b)
{ // 1 - &   2 - >>   3 - |                                         00000110 = 6
    b = (b & 0xF0) >> 4 | (b & 0x0F) << 4; // 11110000 00001111     01100000
    b = (b & 0xCC) >> 2 | (b & 0x33) << 2; // 11001100 00110011     10010000
    b = (b & 0xAA) >> 1 | (b & 0x55) << 1; // 10101010 01010101     01100000 = 96
    return b;
}

bool isCorrectNumber(int number)
{
    if (number < 0 || number > 255)
    {
        return false;
    }
    return true;
}

int main(int argc, char* argv[])
{
    std::string value;
    // с коммандной строки
    // вывести всё в функцию проверки что это бит
    std::cout << "Enter a number from 0 to 255" << std::endl;
    getline(std::cin, value);
    if (value.empty())
    {
        std::cout << "Not correct value!" << std::endl;
        return 1;
    }
    int number = 0;
    try
    {
        number = stoi(value);
    }
    catch (const std::exception& error)
    {
        std::cout << "It's not a number!" /*error.what()*/ << std::endl;
        return 1;
    }
    if (!isCorrectNumber(number)) // IsByte - переименовать
    {
        std::cout << "Not correct number!" << std::endl;
        return 1;
    }
    unsigned char b = (unsigned char)number;
    b = reverseByte(b);
    std::cout << (int)b << std::endl;
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
