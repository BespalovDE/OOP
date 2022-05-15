#include "pch.h"
#include "CCylinder.h"

CCylinder::CCylinder(double density, double radius, double height)
	: CSolidBody(density)
	, m_baseRadius(radius)
	, m_height(height)
{
}

std::string CCylinder::GetName() const
{
	return "Cylinder";
}

double CCylinder::GetHeight() const
{
	return m_height;
}

double CCylinder::GetBaseRadius() const
{
	return m_baseRadius;
}

double CCylinder::GetVolume() const
{
	return M_PI * pow(m_baseRadius, 2) * m_height;
}

void CCylinder::AdditionalInfo(std::ostream& strm) const
{
	strm << "Height: " << GetHeight() << "\n";
	strm << "BaseRadius: " << GetBaseRadius() << "\n";
}