// Разработайте функцию FindMaxEx, являющуюся расширенной версией функции FindMax и позволяющую задавать критерий сравнения элементов при помощи дополнительного параметра less.
//Предикат Less – функция или функтор, принимающий 2 аргумента типа T и возвращающая true, если левый аргумент предшествует правому, в противном случае - false.Данный предикат задает критерий сравнения элементов, используемый для поиска максимального элемента.

#include <iostream>
#include <vector>
#include "FindMaxEx.h"

int main()
{
    std::vector<Sportsman> sportsmanVector =
    {
        {"Daniel Petrov", 32, 82},
        {"Viktor Sapogov", 27, 73},
        {"Dmitry Stoyanov", 37, 88},
    };

    Sportsman sportsmen;

    FindMax<Sportsman>(sportsmanVector, sportsmen, CompareWeight());
    std::cout << sportsmen.fio << std::endl;

    FindMax<Sportsman>(sportsmanVector, sportsmen, CompareAge());
    std::cout << sportsmen.fio << std::endl;
}

