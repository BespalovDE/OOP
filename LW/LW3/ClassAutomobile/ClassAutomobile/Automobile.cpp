#include "Automobile.h"

const std::pair<int, int> ReverseSpeedRange = { 0, 20 };
const std::pair<int, int> FirstSpeedRange = { 0, 30 };
const std::pair<int, int> SecondSpeedRange = { 20, 50 };
const std::pair<int, int> ThirdSpeedRange = { 30,60 };
const std::pair<int, int> FourthSpeedRange = { 40, 90 };
const std::pair<int, int> FifthSpeedRange = { 50, 150 };

bool Automobile::IsTurnedOn() const
{
	return m_isOnEngine;
}

Direction Automobile::GetDirection() const
{
	return m_direction;
}

int Automobile::GetSpeed() const
{
	return m_speed;
}

int Automobile::GetGear() const
{
	return m_gear;
}

bool Automobile::TurnOnEngine()
{
	if (m_isOnEngine)
	{
		return true;
	}
	if (m_gear == 0 && m_speed == 0)
	{
		m_isOnEngine = true;
		return true;
	}
	return false;
}

bool Automobile::TurnOffEngine()
{
	if (!m_isOnEngine)
	{
		return true;
	}
	if (m_gear == 0 && m_speed == 0)
	{
		m_isOnEngine = false;
		return true;
	}
	return false;
}


bool InRange(int speed, const std::pair<int, int> &range)
{
	return speed >= range.first && speed <= range.second;
}

bool IsCorrectSpeedForGear(int gear, int speed)
{
	switch(gear)
	{
	    case -1:
		    return (InRange(speed, ReverseSpeedRange)) ? true : false;
		case 0: 
			return true;
	    case 1: 
			return (InRange(speed, FirstSpeedRange)) ? true : false;
		case 2:
			return (InRange(speed, SecondSpeedRange)) ? true : false;
		case 3:
			return (InRange(speed, ThirdSpeedRange)) ? true : false;
		case 4:
			return (InRange(speed, FourthSpeedRange)) ? true : false;
		case 5:
			return (InRange(speed, FifthSpeedRange)) ? true : false;
		default: 
			return false;
	}
}

bool Automobile::SetGear(int gear)
{
	if (!m_isOnEngine)
	{
		if (gear == 0)
		{
			m_gear = gear;
			return true;
		}
		return false;
	}
	if (gear == 0)
	{
		m_gear = gear;
		return true;
	}
	if (gear == -1)
	{
		if (m_direction == Direction::HOLD)
		{
			m_gear = gear;
			return true;
		}
		return false;
	}
	if (m_gear == gear)
	{
		return true;
	}
	if (gear < -1 || gear > 5)
	{
		return false;
	}
	if ((m_direction == Direction::HOLD || m_direction == Direction::FORWARD) && gear == 1)
	{
		if (IsCorrectSpeedForGear(gear, m_speed))
		{
			m_gear = gear;
			return true;
		}
	}
	else if (m_direction == Direction::FORWARD)
	{
		if (IsCorrectSpeedForGear(gear, m_speed))
		{
			m_gear = gear;
			return true;
		}
	}
	return false;
}

bool Automobile::SetSpeed(int speed)
{
	if (speed < 0 || speed > 150)
	{
		return false;
	}
	if ((m_gear == -1 || m_gear == 0 || m_gear == 1) && (speed == 0))
	{
		m_direction = Direction::HOLD;
		m_speed = speed;
		return true;
	}
	if (m_gear == -1 && IsCorrectSpeedForGear(m_gear, speed))
	{
		m_direction = Direction::BACKWARD;
		m_speed = speed;
		return true;
	}
	if (m_gear == 0)
	{
		if (speed <= m_speed)
		{
			m_speed = speed;
			return true;
		}
		return false;
	}
	if (IsCorrectSpeedForGear(m_gear, speed))
	{
		if (m_gear == 1)
		{
			m_direction = Direction::FORWARD;
		}
		m_speed = speed;
		return true;
	}
	return false;
}