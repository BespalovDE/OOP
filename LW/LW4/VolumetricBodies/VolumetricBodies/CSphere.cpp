#include "pch.h"
#include "CSphere.h"

CSphere::CSphere(double density, double radius)
	: CSolidBody(density)
	, m_radius(radius)
{
}

std::string CSphere::GetName() const
{
	return "Sphere";
}

double CSphere::GetRadius() const
{
	return m_radius;
}

double CSphere::GetVolume() const
{
	return (4 * M_PI * pow(m_radius, 3)) / 3;
}