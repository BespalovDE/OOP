#pragma once
#include <string>

enum class Direction
{
	FORWARD,
	BACKWARD,
	HOLD
};

class Automobile
{
	public:
		bool IsTurnedOn() const;
		Direction GetDirection() const;
		int GetSpeed() const;
		int GetGear() const;
	
		bool TurnOnEngine();
		bool TurnOffEngine();
		bool SetGear(int gear);
		bool SetSpeed(int speed);

	private:
		bool m_isOnEngine = false;
		Direction m_direction = Direction::HOLD;
		int m_speed = 0;
		int m_gear = 0;
};

