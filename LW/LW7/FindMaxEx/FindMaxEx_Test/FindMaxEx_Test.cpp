#define CATCH_CONFIG_MAIN
#include <iostream>
#include <vector>
#include "../FindMaxEx/FindMaxEx.h"
#include "../../../catch2/catch.hpp"

TEST_CASE("Empty vector")
{
	std::vector<int> iVector;
	int iTest;
	CHECK((FindMax<int>(iVector, iTest, Less<int>())) == false);
}

TEST_CASE("Char vector")
{
	std::vector<char> cVector = { 'b', 'C', 'A', 'v', 'V', 'F', 'B'};
	char cTest = '\0';
	CHECK((FindMax<char>(cVector, cTest, Less<char>())) == true);
	CHECK(cTest == 'v');
}

TEST_CASE("Int vector")
{
	std::vector<int> iVector = { 35, 87, 14, -20, 0, 45, -7 };
	int iTest;
	CHECK((FindMax<int>(iVector, iTest, Less<int>())) == true);
	CHECK(iTest == 87);
}

TEST_CASE("Float vector")
{
	std::vector<float> fVector = { 1.4325, 56.532, -5.4534, 0.0, 0.0000001, -0.0000001, 12345.12345, 50.0, 77777.77, -9999.8 };
	float fTest;
	CHECK((FindMax<float>(fVector, fTest, Less<float>())) == true);
	CHECK(fTest == Approx(77777.77).margin(0.01));
}

TEST_CASE("String vector")
{
	std::vector<std::string> sVector = { "bird" "cat", "dog", "dogy", "large", "common", "pay"};
	std::string sTest;
	CHECK((FindMax<std::string>(sVector, sTest, Less<std::string>())) == true);
	CHECK(sTest == "pay");
}

TEST_CASE("Const char* vector")
{
	std::vector<const char*> stringVector = { "dog", "man", "length", "flat", "input" };
	const char* test;
	CHECK((FindMax<const char*>(stringVector, test, Less<const char*>())) == true);
	CHECK(test == "man");
}

TEST_CASE("Sportsman vector")
{
	std::vector<Sportsman> sportsmenVector =
	{
		{"Andrey", 28, 80},
		{"Sasha", 35, 106},
		{"Maksim", 42, 95},
		{"Vadim", 39, 96},
		{"Artur", 42, 106},
		{"Vladimir", 39, 98},
	};

	Sportsman test;

	CHECK(FindMax<Sportsman>(sportsmenVector, test, CompareWeight()) == true);
	CHECK(test.fio == "Sasha");

	CHECK(FindMax<Sportsman>(sportsmenVector, test, CompareAge()) == true);
	CHECK(test.fio == "Maksim");
}

TEST_CASE("Empty vector of sportsmen")
{
	std::vector<Sportsman> spVector;
	Sportsman spTest;
	CHECK(FindMax<Sportsman>(spVector, spTest, CompareWeight()) == false);
	CHECK(FindMax<Sportsman>(spVector, spTest, CompareAge()) == false);
}

TEST_CASE("Only one sportsman")
{
	std::vector<Sportsman> spVector =
	{
		{"Onlyone", 28, 80}
	};

	Sportsman spTest;

	CHECK(FindMax<Sportsman>(spVector, spTest, CompareWeight()) == true);
	CHECK(spTest.fio == "Onlyone");

	CHECK(FindMax<Sportsman>(spVector, spTest, CompareAge()) == true);
	CHECK(spTest.fio == "Onlyone");
}
