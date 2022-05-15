#include "pch.h"
#include "CCone.h"

CCone::CCone(double density, double radius, double height)
	: CSolidBody(density)
	, m_baseRadius(radius)
	, m_height(height)
{
}

std::string CCone::GetName() const
{
	return "Cone";
}

double CCone::GetHeight() const
{
	return m_height;
}

double CCone::GetVolume() const
{
	return M_PI * pow(m_baseRadius, 2) * m_height / 3;
}

double CCone::GetBaseRadius() const
{
	return m_baseRadius;
}

void CCone::AdditionalInfo(std::ostream &strm) const
{
	strm << "Height: " << GetHeight() << "\n";
	strm << "BaseRadius: " << GetBaseRadius() << "\n";
}