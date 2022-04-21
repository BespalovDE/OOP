#include "pch.h"
#include "CParallelepiped.h"

CParallelepiped::CParallelepiped(double density, double width, double height, double depth)
	: CSolidBody(density)
	, m_width(width)
	, m_height(height)
	, m_depth(depth)
{
}

std::string CParallelepiped::GetName() const
{
	return "Parallelepiped";
}

double CParallelepiped::GetWidth() const
{
	return m_width;
}

double CParallelepiped::GetHeight() const
{
	return m_height;
}

double CParallelepiped::GetDepth() const
{
	return m_depth;
}

double CParallelepiped::GetVolume() const
{
	return m_width * m_height * m_depth;
}