#define CATCH_CONFIG_MAIN  
#include "../../../catch2/catch.hpp"
//#include "../ClassAutomobile/Automobile.h"
#include "../ClassAutomobile/AutomobileInterface.h"


TEST_CASE("Test class Automobile")
{
	Automobile automobile;
	REQUIRE(!automobile.IsTurnedOn());
	REQUIRE(automobile.GetDirection() == Direction::HOLD);
	REQUIRE(automobile.GetSpeed() == 0);
	REQUIRE(automobile.GetGear() == 0);
	SECTION("Check TurnOn")
	{
		automobile.TurnOffEngine();
		REQUIRE(!automobile.IsTurnedOn());
		automobile.TurnOnEngine();
		REQUIRE(automobile.IsTurnedOn());
		automobile.TurnOffEngine();
		REQUIRE(!automobile.IsTurnedOn());
	}
	SECTION("Try change gear in On TurnOff Engine on Correct value")
	{
		REQUIRE(automobile.SetGear(0));
		REQUIRE(!automobile.SetGear(-1));
		REQUIRE(!automobile.SetGear(2));
		REQUIRE(!automobile.SetGear(3));
		REQUIRE(!automobile.SetGear(4));
		REQUIRE(!automobile.SetGear(5));
	}
	SECTION("Try change speed in On TurnOff Engine on Correct value")
	{
		REQUIRE(automobile.SetSpeed(0));
		REQUIRE(!automobile.SetSpeed(20));
		REQUIRE(!automobile.SetSpeed(50));
	}
	SECTION("Try change gear in On TurnOff Engine on NOT Correct value")
	{
		REQUIRE(!automobile.SetGear(6));
		REQUIRE(!automobile.SetGear(-2));
		REQUIRE(!automobile.SetGear(10));
		REQUIRE(!automobile.SetGear(-10));
	}
	SECTION("Try change speed in On TurnOff Engine on NOT Correct value")
	{
		REQUIRE(!automobile.SetSpeed(1));
		REQUIRE(!automobile.SetSpeed(-10));
		REQUIRE(!automobile.SetSpeed(151));
		REQUIRE(!automobile.SetSpeed(170));
	}
	SECTION("Turn Off Engin on Forward and Gear > 0")
	{
		automobile.TurnOnEngine();
		automobile.SetGear(1);
		automobile.SetSpeed(20);
		REQUIRE(!automobile.TurnOffEngine());
	}
	SECTION("Turn Off Engin on Gear > 0 and speed = 0")
	{
		automobile.TurnOnEngine();
		automobile.SetGear(1);
		REQUIRE(!automobile.TurnOffEngine());
	}
	SECTION("Turn Off Engin on Gear = 0 and speed > 0")
	{
		automobile.TurnOnEngine();
		automobile.SetGear(1);
		automobile.SetSpeed(20);
		automobile.SetGear(0);
		REQUIRE(!automobile.TurnOffEngine());
	}
	SECTION("Automobile Start on not correct gear")
	{
		automobile.TurnOnEngine();
		REQUIRE(!automobile.SetGear(2));
		REQUIRE(automobile.GetGear() == 0);
		REQUIRE(!automobile.SetGear(3));
		REQUIRE(automobile.GetGear() == 0);
		REQUIRE(!automobile.SetGear(4));
		REQUIRE(automobile.GetGear() == 0);
		REQUIRE(!automobile.SetGear(5));
		REQUIRE(automobile.GetGear() == 0);
		REQUIRE(!automobile.SetGear(6));
		REQUIRE(automobile.GetGear() == 0);
	}
	SECTION("Automobile Start on correct gear")
	{
		automobile.TurnOnEngine();
		REQUIRE(automobile.SetGear(1));
		REQUIRE(automobile.GetGear() == 1);
		REQUIRE(automobile.SetGear(0));
		REQUIRE(automobile.SetGear(-1));
		REQUIRE(automobile.SetGear(0));
	}
	SECTION("Automobile Start and go on 2 gear")
	{
		automobile.TurnOnEngine();
		REQUIRE(automobile.SetGear(1));
		REQUIRE(automobile.GetGear() == 1);
		REQUIRE(automobile.SetSpeed(20));
		REQUIRE(automobile.GetSpeed() == 20);
		REQUIRE(automobile.GetDirection() == Direction::FORWARD);
		REQUIRE(automobile.SetGear(2));
		REQUIRE(automobile.GetGear() == 2);
	}
	SECTION("Automobile Start and go on 3 gear")
	{
		automobile.TurnOnEngine();
		automobile.SetGear(1);
		automobile.SetSpeed(20);
		automobile.SetGear(2);
		REQUIRE(automobile.SetSpeed(50));
		REQUIRE(automobile.SetGear(3));
		REQUIRE(automobile.GetSpeed() == 50);
		REQUIRE(automobile.GetGear() == 3);
		REQUIRE(automobile.GetDirection() == Direction::FORWARD);

	}
	SECTION("Automobile Start on back and stop")
	{
		automobile.TurnOnEngine();
		REQUIRE(automobile.SetGear(-1));
		REQUIRE(automobile.GetDirection() == Direction::HOLD);
		REQUIRE(!automobile.SetSpeed(-5));
		REQUIRE(automobile.GetSpeed() == 0);

		REQUIRE(!automobile.SetSpeed(25));
		REQUIRE(automobile.GetSpeed() == 0);

		REQUIRE(automobile.SetSpeed(15));
		REQUIRE(automobile.GetSpeed() == 15);
		REQUIRE(automobile.GetDirection() == Direction::BACKWARD);
	}
	SECTION("Automobile stop from backward")
	{
		automobile.TurnOnEngine();
		automobile.SetGear(-1);
		automobile.SetSpeed(15);
		REQUIRE(automobile.GetSpeed() == 15);
		REQUIRE(automobile.GetDirection() == Direction::BACKWARD);

		REQUIRE(automobile.SetGear(0));
		REQUIRE(!automobile.SetSpeed(20));
		REQUIRE(automobile.GetSpeed() == 15);
		REQUIRE(automobile.SetSpeed(10));
		REQUIRE(automobile.GetSpeed() == 10);
		REQUIRE(automobile.SetSpeed(0));
		REQUIRE(automobile.GetSpeed() == 0);
		REQUIRE(automobile.GetDirection() == Direction::HOLD);
	}
	SECTION("Automobile Start and go")
	{
		automobile.TurnOnEngine();
		REQUIRE(!automobile.SetGear(2));
		REQUIRE(automobile.GetGear() == 0);
		REQUIRE(automobile.SetGear(1));
		REQUIRE(automobile.GetGear() == 1);
		REQUIRE(!automobile.SetSpeed(50));
		REQUIRE(automobile.GetSpeed() == 0);
		REQUIRE(automobile.SetSpeed(20));
		REQUIRE(automobile.GetSpeed() == 20);
		REQUIRE(automobile.GetDirection() == Direction::FORWARD);

		SECTION("Automobile go on from 1 gear to 5 and back")
		{
			REQUIRE(automobile.SetGear(2));
			REQUIRE(automobile.GetGear() == 2);
			REQUIRE(!automobile.SetSpeed(0));
			REQUIRE(!automobile.SetSpeed(80));
			REQUIRE(automobile.GetSpeed() == 20);
			REQUIRE(automobile.SetSpeed(40));
			REQUIRE(automobile.GetSpeed() == 40);

			REQUIRE(automobile.SetGear(3));
			REQUIRE(automobile.SetSpeed(50));
			REQUIRE(automobile.GetGear() == 3);
			REQUIRE(automobile.GetSpeed() == 50);

			REQUIRE(automobile.SetGear(4));
			REQUIRE(automobile.SetSpeed(80));
			REQUIRE(automobile.GetGear() == 4);
			REQUIRE(automobile.GetSpeed() == 80);

			REQUIRE(automobile.SetGear(5));
			REQUIRE(automobile.SetSpeed(150));
			REQUIRE(automobile.GetGear() == 5);
			REQUIRE(automobile.GetSpeed() == 150);
			REQUIRE(!automobile.SetSpeed(151));
			REQUIRE(automobile.GetSpeed() == 150);
			REQUIRE(automobile.SetSpeed(149));
			REQUIRE(automobile.GetSpeed() == 149);
			REQUIRE(!automobile.SetSpeed(-149));
			REQUIRE(automobile.GetSpeed() == 149);

			REQUIRE(automobile.SetSpeed(91));
			REQUIRE(!automobile.SetGear(4));
			REQUIRE(automobile.GetGear() == 5);
			REQUIRE(automobile.SetSpeed(90));
			REQUIRE(automobile.SetGear(4));
			REQUIRE(automobile.GetGear() == 4);
			REQUIRE(automobile.GetSpeed() == 90);

			REQUIRE(automobile.SetSpeed(40));
			REQUIRE(automobile.GetSpeed() == 40);
			REQUIRE(automobile.SetGear(2));
			REQUIRE(automobile.GetGear() == 2);

			REQUIRE(!automobile.SetGear(1));
			REQUIRE(automobile.SetGear(2));
			REQUIRE(automobile.SetSpeed(20));
			REQUIRE(automobile.GetSpeed() == 20);
			REQUIRE(automobile.SetGear(1));
			REQUIRE(automobile.GetGear() == 1);

			REQUIRE(automobile.GetDirection() == Direction::FORWARD);
		}
		SECTION("Automobile stop and go on back, then stop")
		{
			REQUIRE(automobile.SetGear(0));
			REQUIRE(automobile.SetSpeed(0));
			REQUIRE(automobile.SetGear(-1));
			REQUIRE(automobile.GetDirection() == Direction::HOLD);
			REQUIRE(!automobile.SetSpeed(-5));
			REQUIRE(automobile.GetSpeed() == 0);

			REQUIRE(!automobile.SetSpeed(25));
			REQUIRE(automobile.GetSpeed() == 0);

			REQUIRE(automobile.SetSpeed(15));
			REQUIRE(automobile.GetSpeed() == 15);
			REQUIRE(automobile.GetDirection() == Direction::BACKWARD);

			REQUIRE(automobile.SetGear(0));
			REQUIRE(!automobile.SetSpeed(20));
			REQUIRE(automobile.GetSpeed() == 15);
			REQUIRE(automobile.SetSpeed(10));
			REQUIRE(automobile.GetSpeed() == 10);
			REQUIRE(automobile.SetSpeed(0));
			REQUIRE(automobile.GetSpeed() == 0);
			REQUIRE(automobile.GetDirection() == Direction::HOLD);
		}
	}
}

TEST_CASE("Test class AutomobileInterface")
{
	Automobile automobile;
	std::istringstream input("EngineOn\nSetGear 1\nSetSpeed 30\nSetGear 2\nSetGear 3\nSetSpeed 60\nInfo\nSetSpeed 0\nSetGear 1\nEngineOff\nSetSpeed 40\nSetGear 0\nSetSpeed 0\nEngineOff\n");
	std::ostringstream output;
	AutomobileInterface automobileInterface(automobile, input, output);

	automobileInterface.InterfaceCommand();
	REQUIRE("Engine is On\n" == output.str());
	output.str("");

	automobileInterface.InterfaceCommand();
	REQUIRE("Now gear is 1\n" == output.str());
	output.str("");

	automobileInterface.InterfaceCommand();
	REQUIRE("Now speed is 30\n" == output.str());
	output.str("");

	automobileInterface.InterfaceCommand();
	REQUIRE("Now gear is 2\n" == output.str());
	output.str("");

	automobileInterface.InterfaceCommand();
	REQUIRE("Now gear is 3\n" == output.str());
	output.str("");

	automobileInterface.InterfaceCommand();
	REQUIRE("Now speed is 60\n" == output.str());
	output.str("");

	automobileInterface.InterfaceCommand();
	REQUIRE("Engine: on\nDirection: forward\nSpeed: 60\nGear: 3\n" == output.str());
	output.str("");

	automobileInterface.InterfaceCommand();
	REQUIRE("Speed can`t be changed on 0\n" == output.str());
	output.str("");

	automobileInterface.InterfaceCommand();
	REQUIRE("Gear can`t be changed on 1\n" == output.str());
	output.str("");

	automobileInterface.InterfaceCommand();
	REQUIRE("Engine is can't be TurnOff\n" == output.str());
	output.str("");

	automobileInterface.InterfaceCommand();
	REQUIRE("Now speed is 40\n" == output.str());
	output.str("");

	automobileInterface.InterfaceCommand();
	REQUIRE("Now gear is 0\n" == output.str());
	output.str("");

	automobileInterface.InterfaceCommand();
	REQUIRE("Now speed is 0\n" == output.str());
	output.str("");

	automobileInterface.InterfaceCommand();
	REQUIRE("Engine is Off\n" == output.str());
	output.str("");
}

TEST_CASE("Test class AutomobileInterface go back")
{
	Automobile automobile;
	std::istringstream input("EngineOn\nSetGear -1\nSetSpeed 30\nSetSpeed 15\nInfo\nSetSpeed 20\nEngineOff\nSetGear 0\nSetSpeed 0\nEngineOff\n");
	std::ostringstream output;
	AutomobileInterface automobileInterface(automobile, input, output);

	automobileInterface.InterfaceCommand();
	REQUIRE("Engine is On\n" == output.str());
	output.str("");

	automobileInterface.InterfaceCommand();
	REQUIRE("Now gear is -1\n" == output.str());
	output.str("");

	automobileInterface.InterfaceCommand();
	REQUIRE("Speed can`t be changed on 30\n" == output.str());
	output.str("");

	automobileInterface.InterfaceCommand();
	REQUIRE("Now speed is 15\n" == output.str());
	output.str("");

	automobileInterface.InterfaceCommand();
	REQUIRE("Engine: on\nDirection: backward\nSpeed: 15\nGear: -1\n" == output.str());
	output.str("");

	automobileInterface.InterfaceCommand();
	REQUIRE("Now speed is 20\n" == output.str());
	output.str("");

	automobileInterface.InterfaceCommand();
	REQUIRE("Engine is can't be TurnOff\n" == output.str());
	output.str("");

	automobileInterface.InterfaceCommand();
	REQUIRE("Now gear is 0\n" == output.str());
	output.str("");

	automobileInterface.InterfaceCommand();
	REQUIRE("Now speed is 0\n" == output.str());
	output.str("");

	automobileInterface.InterfaceCommand();
	REQUIRE("Engine is Off\n" == output.str());
	output.str("");
}