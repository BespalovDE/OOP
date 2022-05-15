#include "pch.h"
#include "CBody.h"

std::string CBody::ToString() const
{
	std::ostringstream info;
	info << std::fixed << std::setprecision(2);
	info << GetName() << '\n';
	info << "Density: " << GetDensity() << '\n';
	info << "Volume: " << GetVolume() << '\n';
	info << "Mass: " << GetMass() << '\n';
	AdditionalInfo(info);
	return info.str();
}