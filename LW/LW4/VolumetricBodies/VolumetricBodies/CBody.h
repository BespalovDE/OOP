#pragma once
#include "pch.h"

class CBody
{
	public:
		virtual double GetDensity() const = 0;
		virtual double GetVolume() const = 0;
		virtual double GetMass() const = 0;
		virtual std::string ToString() const;
		virtual std::string GetName() const = 0;
		virtual ~CBody() = default;
};

