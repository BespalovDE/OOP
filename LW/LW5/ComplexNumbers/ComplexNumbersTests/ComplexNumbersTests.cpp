// CComplexNumbers_tests.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include <iostream>
#include <string>
#include "../ComplexNumbers/CComplex.h"

TEST_CASE("Complex number getting magnitude and argument")
{
	SECTION("0 real and image parts")
	{
		CComplex cNumber;
		CHECK(cNumber.Re() == 0.0);
		CHECK(cNumber.Im() == 0.0);
		CHECK(cNumber.GetMagnitude() == 0.0);
		double arg = cNumber.GetArgument();
		CHECK(arg != arg); // nan проверяется так
		CComplex res = cNumber + CComplex(1, 2);
		CHECK(res.Re() == 1);
		CHECK(res.Im() == 2);
	}

	SECTION("0 real and negative image parts")
	{
		CComplex cNumber(0, -2);
		CHECK(cNumber.Re() == 0.0);
		CHECK(cNumber.Im() == -2);
		CHECK(cNumber.GetMagnitude() == 2.0);
		double arg = cNumber.GetArgument();
		CHECK(arg == Approx(-1.57).margin(0.01));
		CComplex res = cNumber + CComplex(1, 2);
		CHECK(res.Re() == 1);
		CHECK(res.Im() == 0);
	}

	SECTION("positive real and 0 image part")
	{
		CComplex cNumber(2, 0);
		CHECK(cNumber.Re() == 2);
		CHECK(cNumber.Im() == 0);
		CHECK(cNumber.GetMagnitude() == 2.0);
		CHECK(cNumber.GetArgument() == 0);
	}

	SECTION("negative real and 0 image part")
	{
		CComplex cNumber(-2, 0);
		CHECK(cNumber.Re() == -2);
		CHECK(cNumber.Im() == 0);
		CHECK(cNumber.GetMagnitude() == 2.0);
		CHECK(cNumber.GetArgument() == Approx(3.14).margin(0.01));
	}

	SECTION("negative real and image parts")
	{
		CComplex cNumber(-3, -2);
		CHECK(cNumber.Re() == -3);
		CHECK(cNumber.Im() == -2);
		CHECK(cNumber.GetMagnitude() == Approx(3.61).margin(0.01));
		CHECK(cNumber.GetArgument() == Approx(-2.55).margin(0.01));
		CComplex res = cNumber + CComplex(1, 2);
		CHECK(res.Re() == -2);
		CHECK(res.Im() == 0);
	}

	SECTION("negative real and positive image parts")
	{
		CComplex cNumber(-5, 4);
		CHECK(cNumber.Re() == -5);
		CHECK(cNumber.Im() == 4);
		CHECK(cNumber.GetMagnitude() == Approx(6.41).margin(0.01));
		CHECK(cNumber.GetArgument() == Approx(2.47).margin(0.01));
		CComplex res1 = cNumber + CComplex(1, 2);
		CHECK(res1.Re() == -4);
		CHECK(res1.Im() == 6);
	}

	SECTION("positive real and negative image parts")
	{
		CComplex cNumber(7, -4);
		CHECK(cNumber.Re() == 7);
		CHECK(cNumber.Im() == -4);
		CHECK(cNumber.GetMagnitude() == Approx(8.06).margin(0.01));
		CHECK(cNumber.GetArgument() == Approx(-0.52).margin(0.01));
		CComplex res1 = cNumber + CComplex(1, 2);
		CHECK(res1.Re() == 8);
		CHECK(res1.Im() == -2);
	}

	SECTION("positive real and image parts")
	{
		CComplex cNumber(7, 9);
		CHECK(cNumber.Re() == 7);
		CHECK(cNumber.Im() == 9);
		CHECK(cNumber.GetMagnitude() == Approx(11.40).margin(0.01));
		CHECK(cNumber.GetArgument() == Approx(0.91).margin(0.01));
	}
}

TEST_CASE("Binary +")
{
	CComplex res1 = CComplex(7, 9) + 1.15;
	CHECK(res1.Re() == 8.15);
	CHECK(res1.Im() == 9);

	CComplex res2 = CComplex(-4, -2) + CComplex(11.5, 16.4);
	CHECK(res2.Re() == 7.5);
	CHECK(res2.Im() == Approx(14.4).margin(0.01));
}

TEST_CASE("Binary -")
{
	CComplex res1 = CComplex(7, 9) - 1.15;
	CHECK(res1.Re() == 5.85);
	CHECK(res1.Im() == 9);

	CComplex res2 = CComplex(-4, -2) - CComplex(11.5, 16.4);
	CHECK(res2.Re() == -15.5);
	CHECK(res2.Im() == Approx(-18.4).margin(0.01));

	CComplex res3 = 11 - CComplex(8, 17);
	CHECK(res3.Re() == 3);
	CHECK(res3.Im() == -17);
}

TEST_CASE("Binary *")
{
	CComplex res1 = CComplex(7, 9) * 1.15;
	CHECK(res1.Re() == Approx(8.05).margin(0.01));
	CHECK(res1.Im() == Approx(10.35).margin(0.01));

	CComplex res2 = CComplex(2, 1) * CComplex(3, 4);
	CHECK(res2.Re() == 2);
	CHECK(res2.Im() == 11);

	CComplex res3 = 11 * CComplex(8, 17);
	CHECK(res3.Re() == 88);
	CHECK(res3.Im() == 187);

	CComplex res4 = CComplex(-8.46, 13.25) * CComplex(-5.4, 2.7);
	CHECK(res4.Re() == Approx(9.91).margin(0.01));
	CHECK(res4.Im() == Approx(-94.39).margin(0.01));
}

TEST_CASE("Binary /")
{
	CComplex res1 = CComplex(3, 4) / CComplex(2, 1);
	CHECK(res1.Re() == 2);
	CHECK(res1.Im() == 1);

	CComplex res2 = CComplex(23, 1) / CComplex(3, 1);
	CHECK(res2.Re() == 7);
	CHECK(res2.Im() == -2);

	CComplex res3 = CComplex(-2, 1) / CComplex(1, -1);
	CHECK(res3.Re() == -1.5);
	CHECK(res3.Im() == -0.5);

	CComplex res4 = CComplex(3, 4) / CComplex(5, -6);
	CHECK(res4.Re() == Approx(-0.15).margin(0.01));
	CHECK(res4.Im() == Approx(0.62).margin(0.01));

	CComplex res5 = CComplex(-7, 4) / 3;
	CHECK(res5.Re() == Approx(-2.33).margin(0.01));
	CHECK(res5.Im() == Approx(1.33).margin(0.01));

	CComplex res6 = CComplex(0, 0) / CComplex(5, -6);
	CHECK(res6.Re() == 0);
	CHECK(res6.Im() == 0);

	CComplex res7 = 0 / CComplex(5, -6);
	CHECK(res7.Re() == 0);
	CHECK(res7.Im() == 0);

	CComplex res8 = 5 / CComplex(5, -6);
	CHECK(res8.Re() == Approx(0.41).margin(0.01));
	CHECK(res8.Im() == Approx(0.49).margin(0.01));

	REQUIRE_THROWS_AS(CComplex(3, 4) / 0, std::invalid_argument);
	REQUIRE_THROWS_AS(CComplex(3, 4) / CComplex(0, 0), std::invalid_argument);
}

TEST_CASE("Unary +")
{
	CComplex res1 = +CComplex(7, 9);
	CHECK(res1.Re() == 7);
	CHECK(res1.Im() == 9);
	CComplex res2 = +CComplex(-7, -9);
	CHECK(res2.Re() == -7);
	CHECK(res2.Im() == -9);
}

TEST_CASE("Operator -")
{
	CComplex res1 = -CComplex(-5, 2);
	CHECK(res1.Re() == 5);
	CHECK(res1.Im() == -2);
	CComplex res2 = -CComplex(5, -2);
	CHECK(res2.Re() == -5);
	CHECK(res2.Im() == 2);
}

TEST_CASE("Operator +=")
{
	CComplex res1(5.6, 7.9);
	res1 += CComplex(-5, 2);
	CHECK(res1.Re() == Approx(0.6).margin(0.01));
	CHECK(res1.Im() == 9.9);

	CComplex res2(5.6, 7.9);
	res2 += 8.7;
	CHECK(res2.Re() == Approx(14.3).margin(0.01));
	CHECK(res2.Im() == Approx(7.9).margin(0.01));

	CComplex res3;
	res3 += -9.4;
	CHECK(res3.Re() == Approx(-9.4).margin(0.01));
	CHECK(res3.Im() == 0);
}

TEST_CASE("Operator *=")
{
	CComplex res1(-8.46, 13.25);
	res1 *= CComplex(-5.4, 2.7);
	CHECK(res1.Re() == Approx(9.91).margin(0.01));
	CHECK(res1.Im() == Approx(-94.39).margin(0.01));

	CComplex res2(15.46, -11.81);
	res2 *= 4.25;
	CHECK(res2.Re() == Approx(65.71).margin(0.01));
	CHECK(res2.Im() == Approx(-50.19).margin(0.01));
}

TEST_CASE("Operator /=")
{
	CComplex res1(11.78, 16.45);
	res1 /= CComplex(-9.41, 0.87);
	CHECK(res1.Re() == Approx(-1.08).margin(0.01));
	CHECK(res1.Im() == Approx(-1.85).margin(0.01));

	CComplex res2(19.87, -1.40);
	res2 /= -5.95;
	CHECK(res2.Re() == Approx(-3.34).margin(0.01));
	CHECK(res2.Im() == Approx(0.24).margin(0.01));

	REQUIRE_THROWS_AS(res1 /= 0, std::invalid_argument);
	REQUIRE_THROWS_AS(res1 /= CComplex(0, 0), std::invalid_argument);
}

TEST_CASE("Operator ==")
{
	CComplex op1(19.45, -11.21);
	CHECK((op1 == CComplex(19.45, -11.21)) == true);
	CHECK((op1 == CComplex(19.46, -11.20)) == false);
	CHECK((op1 == CComplex(19.45, -11.20)) == false);
	CHECK((op1 == CComplex(19.46, -11.21)) == false);
	CHECK((19.45 == op1) == false);

	CComplex op2(15.45);
	CHECK((op2 == 15.45) == true);
	CHECK((op2 == CComplex(15.45, 0)) == true);

	CComplex op3(15.72);
	CHECK((15.72 == op3) == true);

	CComplex op4(15.72, 0.01);
	CHECK((15.72 == op4) == false);

	CComplex op5(0.00000000001, -0.00000000001);
	CHECK((op5 == CComplex(0.00000000002, -0.00000000002)) == false);
}

TEST_CASE("Operator !=")
{
	CComplex op1(19.45, -11.21);
	CHECK((op1 != CComplex(19.45, -11.21)) == false);
	CHECK((op1 != CComplex(19.46, -11.20)) == true);
	CHECK((op1 != CComplex(19.45, -11.20)) == true);
	CHECK((op1 != CComplex(19.46, -11.21)) == true);
	CHECK((19.45 != op1) == true);

	CComplex op2(15.45);
	CHECK((op2 != 15.45) == false);
	CHECK((op2 != CComplex(15.45, 0)) == false);

	CComplex op3(15.72);
	CHECK((15.72 != op3) == false);

	CComplex op4(15.72, 0.01);
	CHECK((15.72 != op4) == true);

	CComplex op5(0.00000000001, -0.00000000001);
	CHECK((op5 != CComplex(0.00000000002, -0.00000000002)) == true);
}


TEST_CASE("Operator <<")
{
	CComplex CComplex1(19, 11.21);
	std::ostringstream output;
	output << CComplex1;
	CHECK(output.str() == "19+11.21i");

	output.str("");
	CComplex CComplex2(0.04, -11.05);
	output << CComplex2;
	CHECK(output.str() == "0.04-11.05i");

	output.str("");
	CComplex CComplex3(0.05, -0.04);
	output << CComplex3;
	CHECK(output.str() == "0.05-0.04i");

	output.str("");
	CComplex CComplex4(-0.049, -0.049);
	output << CComplex4;
	CHECK(output.str() == "-0.049-0.049i");

	output.str("");
	CComplex CComplex5(14.4, -15.4);
	output << CComplex5;
	CHECK(output.str() == "14.4-15.4i");

	output.str("");
	CComplex CComplex6(-0.05, 0.05);
	output << CComplex6;
	CHECK(output.str() == "-0.05+0.05i");

	output.str("");
	CComplex CComplex7(5);
	output << CComplex7;
	CHECK(output.str() == "5+0i");

	output.str("");
	CComplex CComplex8;
	output << CComplex8;
	CHECK(output.str() == "0+0i");
}

TEST_CASE("Operator >>")
{
	CComplex CComplex1;
	std::istringstream input;
	input.str("2-4i");
	input >> CComplex1;
	CHECK(CComplex1.Re() == 2);
	CHECK(CComplex1.Im() == -4);

	CComplex CComplex2;
	input.str("");
	input.str("2-4");
	input >> CComplex2;
	CHECK(input.fail() == true);

	CComplex CComplex3;
	input.clear();
	input.str("2.56+4.27i");
	input >> CComplex3;
	CHECK(CComplex3.Re() == 2.56);
	CHECK(CComplex3.Im() == 4.27);

	CComplex CComplex4;
	input.str("-0.009-4.559i");
	input >> CComplex4;
	CHECK(CComplex4.Re() == -0.009);
	CHECK(CComplex4.Im() == -4.559);

	CComplex CComplex5;
	input.str("0-0i");
	input >> CComplex5;
	CHECK(CComplex5.Re() == 0);
	CHECK(CComplex5.Im() == 0);
}