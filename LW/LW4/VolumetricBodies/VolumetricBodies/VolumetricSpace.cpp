#include "pch.h"
#include "VolumetricSpace.h"

using namespace std::placeholders;

VolumetricSpace::VolumetricSpace(std::istream& input, std::ostream& output)
	: m_input(input)
	, m_output(output)
	, m_actionMap({
		  { "sphere", bind(&VolumetricSpace::AddSphere, this, std::placeholders::_1) }, // std::bind Ч шаблонна€ функци€, котора€ принимает на вход указатель на callable-объект и аргументы, которые могут быть константами, переменными или плейсхолдерами (placeholder).
		  { "parallelepiped", bind(&VolumetricSpace::AddParallelepiped, this, std::placeholders::_1) },
		  { "cone", bind(&VolumetricSpace::AddCone, this, std::placeholders::_1) },
		  { "cylinder", bind(&VolumetricSpace::AddCylinder, this, std::placeholders::_1) },
		  { "compound", bind(&VolumetricSpace::AddCompound, this, std::placeholders::_1) },
		  { "endCompound", bind(&VolumetricSpace::RemoveLastCompoundPtr, this, std::placeholders::_1) },
		  { "help", bind(&VolumetricSpace::Info, this, std::placeholders::_1) }
		})
{
}

bool VolumetricSpace::HandleCommand()
{
	std::string inputCommandLine;
	std::getline(m_input, inputCommandLine);
	std::istringstream strm(inputCommandLine);

	std::string action;
	strm >> action;

	auto it = m_actionMap.find(action);
	if (it != m_actionMap.end())
	{
		return it->second(strm);
	}
	return false;
}

std::optional<std::vector<double>> ParseArgs(std::istream& args)
{
	std::string stringLine;
	getline(args, stringLine);
	std::istringstream strm(stringLine);
	std::vector<double> optionArray;
	double number;
	while (strm >> number)
	{
		if (number <= DBL_EPSILON)
		{
			return std::nullopt;
		}
		optionArray.push_back(number);
	}
	if (!strm.eof())
	{
		return std::nullopt;
	}
	return optionArray;
}

bool VolumetricSpace::AddSphere(std::istream& args)
{

	return true;
}

bool VolumetricSpace::AddParallelepiped(std::istream& args)
{

	return true;
}

bool VolumetricSpace::AddCone(std::istream& args)
{

	return true;
}

bool VolumetricSpace::AddCylinder(std::istream& args)
{

	return true;
}

bool VolumetricSpace::AddCompound(std::istream& args)
{

	return true;
}

bool VolumetricSpace::RemoveLastCompoundPtr(std::istream& args)
{

	return true;
}

bool VolumetricSpace::Info(std::istream& args)
{

	return true;
}

void VolumetricSpace::PrintBodiesInfo()
{

}

void VolumetricSpace::PrintMaxMassBody() const
{

}

void VolumetricSpace::PrintBodyWithLeastWeightInWater() const
{

}