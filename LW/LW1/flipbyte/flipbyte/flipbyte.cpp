// flipbyte.cpp 0.6
//Приложение flipbyte.exe, выполняющее изменение порядка следования двоичных битов в 8 - битовом целом числе(байте), 
//заданном в десятичном представлении, на противоположный.

#include <iostream>
#include <string>
#include <exception>
#include <fstream>
#include <sstream>

unsigned char ReverseByte(unsigned char b)
{ // 1 - &   2 - >>   3 - |                                        
    b = (b & 0b11110000) >> 4 | (b & 0b00001111) << 4;
    b = (b & 0b11001100) >> 2 | (b & 0b00110011) << 2;
    b = (b & 0b10101010) >> 1 | (b & 0b01010101) << 1;
    return b;
}
/*%program% < "%~dp0XXX.txt" >%OUT%
fc.exe %OUT% "%~dp0notOpened.txt" >nul
IF ERRORLEVEL 1 goto :testFailed
echo OK1*/
bool IsByteNumber(int number)
{
    if (number < 0 || number > 255)
    {
        return false;
    }
    return true;
}

bool GetByte(int& number, const std::string& inputValue, std::string& errorMessage)
{
    std::ifstream inputFile(inputValue);
    if (!inputFile.is_open())
    {
        errorMessage = "Failed to open file for reading!";
        return false;
    }
    std::string inputLine = "";
    getline(inputFile, inputLine);
    try
    {
        number = stoi(inputLine);
    }
    catch (const std::exception& /*error*/)
    {
        errorMessage = "It's not a number format of data!";
        return false;
    }
    if (!IsByteNumber(number))
    {
        errorMessage = "Is not a Byte!";
        return false;
    }
    return true;
}


int main(int argc, char* argv[])
{
    int number = 0;
    if (argc != 2)
    {
        std::cout << "Not enough parameters!" << std::endl;
        return 1;
    }
    std::string errorMessage = "";
    std::string inputValue = argv[1];
    if (!GetByte(number, inputValue, errorMessage))
    {
        std::cout << errorMessage << std::endl;
         return 1;
    }
    unsigned char b = (unsigned char)number;
    b = ReverseByte(b);
    std::cout << (int)b << std::endl;
    return 0;
}