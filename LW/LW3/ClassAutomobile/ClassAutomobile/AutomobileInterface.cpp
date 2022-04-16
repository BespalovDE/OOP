#include "AutomobileInterface.h"
#include <sstream>

std::string DirectionName(Direction direction)
{
	switch (direction)
	{
		case Direction::BACKWARD:
			return "backward";
		case Direction::FORWARD:
			return "forward";
		case Direction::HOLD:
			return "hold";
		default:
			return "";
	}
}

bool ConvertStrToIntNumber(std::string inputStr, int &outputNum)
{
	try
	{
		outputNum = stoi(inputStr);
	}
	catch (std::exception &)
	{
		return false;
	}
	return true;
}


AutomobileInterface::AutomobileInterface(Automobile &automobile, std::istream &input, std::ostream &output)
	: m_automobile(automobile)
	, m_input(input)
	, m_output(output)
	, m_actionMap(
		{
			{ 
				"Info", 
				[this](std::istream &args) 
				{
					return Info();
				} 
			},
			{ 
				"EngineOn", 
				[this](std::istream &args) 
				{
				   return EngineOn();
				} 
			},
			{ 
				"EngineOff", 
				[this](std::istream &args) 
				{
				   return EngineOff();
				} 
			},
			{ 
				"SetGear", 
				[this](std::istream &args) 
				{
				   return SetGear(args);
				} 
			},
			{ 
				"SetSpeed", 
				[this](std::istream &args) 
				{
				   return SetSpeed(args);
				} 
			},
		}
	)
{
}

bool AutomobileInterface::InterfaceCommand()
{
	std::string commandLine;
	getline(m_input, commandLine);
	std::istringstream strm(commandLine);

	std::string command;
	strm >> command;

	auto it = m_actionMap.find(command);
	if (it != m_actionMap.end())
	{
		return it -> second(strm);
	}
	else
	{
		m_output << "Unknown command!\n";
		return false;
	}	
}

bool AutomobileInterface::Info()
{
	if (m_automobile.IsTurnedOn())
	{
		m_output << "Engine: on\n";
	}
	else
	{
		m_output << "Engine: off\n";
	}
	m_output << "Direction: " << DirectionName(m_automobile.GetDirection()) << "\n";
	m_output << "Speed: " << m_automobile.GetSpeed() << "\n";
	m_output << "Gear: " << m_automobile.GetGear() << "\n";
	return true;
}

bool AutomobileInterface::EngineOn()
{
	if (m_automobile.TurnOnEngine())
	{
		m_output << "Engine is On\n";
		return true;
	}
	m_output << "Engine is can't be TurnOn\n";
	return false;
}

bool AutomobileInterface::EngineOff()
{
	if (m_automobile.TurnOffEngine())
	{
		m_output << "Engine is Off\n";
		return true;
	}
	m_output << "Engine is can't be TurnOff\n";
	return false;
}

bool AutomobileInterface::SetGear(std::istream &args)
{
	std::string inputStr;
	args >> inputStr;
	int gear;
	if (ConvertStrToIntNumber(inputStr, gear))
	{
		if (m_automobile.SetGear(gear))
		{
			m_output << "Now gear is " << gear << "\n";
			return true;
		}
	}
	m_output << "Gear can`t be changed on " << inputStr << "\n";
	return false;
}

bool AutomobileInterface::SetSpeed(std::istream& args)
{
	std::string inputStr;
	args >> inputStr;
	int speed;
	if (ConvertStrToIntNumber(inputStr, speed))
	{
		if (m_automobile.SetSpeed(speed))
		{
			m_output << "Now speed is " << speed << "\n";
			return true;
		}
	}
	m_output << "Speed can`t be changed on " << inputStr << "\n";
	return false;
}