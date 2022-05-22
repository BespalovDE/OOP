#pragma once
#include "pch.h"// не должно быть в заголовочных файлах

class CBody
{
	public:
		virtual double GetDensity() const = 0;
		virtual double GetVolume() const = 0;
		virtual double GetMass() const = 0;
		virtual std::string ToString() const;
		virtual std::string GetName() const = 0;
		virtual ~CBody() = default; // виртуальный деструктор для чего?
	private:
		virtual void AdditionalInfo(std::ostream &strm) const = 0;
};

