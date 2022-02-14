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

bool isByteNumber(int number)
{
    if (number < 0 || number > 255)
    {
        return false;
    }
    return true;
}

void showMessage(std::string message)
{
    std::cout << message << std::endl;
}

void getValue(std::string& value)
{
    showMessage("Enter a number from 0 to 255");
    getline(std::cin, value);
}

bool getByte(int& number, std::string& errorMessage)
{
    std::string value;
    getValue(value);
    if (value.empty() || value == "")
    {
        errorMessage = "Not correct value!";
        return 1;
    }
    try
    {
        number = stoi(value);
    }
    catch (const std::exception& error)
    {
        errorMessage = "It's not a number format of data!";
        return 1;
    }
    if (!isByteNumber(number))
    {
        errorMessage = "Is not a Byte!";
        return 1;
    }
    return 0;
}


int main(int argc, char* argv[])
{
    int number = 0;
    std::string errorMessage = "";
    if (getByte(number, errorMessage))
    {
        showMessage(errorMessage);
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
