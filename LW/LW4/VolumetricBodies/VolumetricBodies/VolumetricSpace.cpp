#include "pch.h"
#include "VolumetricSpace.h"

using namespace std::placeholders;

VolumetricSpace::VolumetricSpace(std::istream &input, std::ostream &output)
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

std::optional<std::vector<double>> ParseArgs(std::istream &args)
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

bool VolumetricSpace::AddSphere(std::istream &inputArgs)
{
	auto args = ParseArgs(inputArgs);
	if (!args)
	{
		return false;
	}
	std::vector<double> arguments = args.value();
	if (arguments.size() != 2)
	{
		return false;
	}
	auto sphere = std::make_shared<CSphere>(arguments[0], arguments[1]);
	if (m_compounds.empty())
	{
		m_bodies.emplace_back(std::move(sphere));
		return true;
	}
	std::weak_ptr<CCompound> it = m_compounds.back();
	it.lock()->AddChildBody(sphere);
	return true;
}

bool VolumetricSpace::AddParallelepiped(std::istream &inputArgs)
{
	auto args = ParseArgs(inputArgs);
	if (!args)
	{
		return false;
	}
	std::vector<double> arguments = args.value();
	if (arguments.size() != 4)
	{
		return false;
	}
	auto parallelepiped = std::make_shared<CParallelepiped>(arguments[0], arguments[1], arguments[2], arguments[3]);
	if (m_compounds.empty())
	{
		m_bodies.push_back(std::move(parallelepiped));
		return true;
	}
	std::weak_ptr<CCompound> it = m_compounds.back();
	it.lock()->AddChildBody(parallelepiped);
	return true;
}

bool VolumetricSpace::AddCone(std::istream &inputArgs)
{
	auto args = ParseArgs(inputArgs);
	if (!args)
	{
		return false;
	}
	std::vector<double> arguments = args.value();
	if (arguments.size() != 3)
	{
		return false;
	}
	auto cone = std::make_shared<CCone>(arguments[0], arguments[1], arguments[2]);
	if (m_compounds.empty())
	{
		m_bodies.emplace_back(std::move(cone));
		return true;
	}
	std::weak_ptr<CCompound> it = m_compounds.back();
	it.lock()->AddChildBody(cone);
	return true;
}

bool VolumetricSpace::AddCylinder(std::istream &inputArgs)
{
	auto args = ParseArgs(inputArgs);
	if (!args)
	{
		return false;
	}
	std::vector<double> arguments = args.value();
	if (arguments.size() != 3)
	{
		return false;
	}
	auto cylinder = std::make_shared<CCylinder>(arguments[0], arguments[1], arguments[2]);
	if (m_compounds.empty())
	{
		m_bodies.emplace_back(std::move(cylinder));
		return true;
	}
	std::weak_ptr<CCompound> it = m_compounds.back();
	it.lock()->AddChildBody(cylinder);
	return true;
}

bool VolumetricSpace::AddCompound(std::istream &inputArgs)
{
	auto args = ParseArgs(inputArgs);
	if (!args)
	{
		return false;
	}
	std::vector<double> arguments = args.value();
	if (!arguments.empty())
	{
		return false;
	}
	auto compound = std::make_shared<CCompound>();
	if (m_compounds.empty())
	{
		m_bodies.emplace_back(compound);
	}
	else
	{
		std::weak_ptr<CCompound> it = m_compounds.back();
		it.lock()->AddChildBody(compound);
	}
	m_compounds.emplace_back(compound);
	return true;
}

bool VolumetricSpace::RemoveLastCompoundPtr(std::istream &inputArgs)
{
	if (!inputArgs.eof())
	{
		return false;
	}
	if (m_compounds.empty())
	{
		return false;
	}
	m_compounds.pop_back();
	return true;
}

bool VolumetricSpace::Info(std::istream &InputArgs)
{
	m_output << "sphere <density> <radius>\n";
	m_output << "cone <density> <base_radius> <height>\n";
	m_output << "cylinder <density> <base_radius> <height>\n";
	m_output << "parallelepiped <density> <width> <height> <depth>\n";
	m_output << "compound\n";
	m_output << "endCompound\n";
	return true;
}

void VolumetricSpace::PrintBodiesInfo()
{
	m_output << std::accumulate(m_bodies.begin(), m_bodies.end(), std::string{},
		[](std::string info, const std::shared_ptr<CBody> &body) { return info += body->ToString() + '\n'; });
}

void VolumetricSpace::PrintMaxMassBody() const
{
	auto CompareWeight = [](const std::shared_ptr<CBody> &cBody1, const std::shared_ptr<CBody> &cBody2)
	{
		return cBody1->GetMass() < cBody2->GetMass();
	};
	auto maxWeightBody = std::max_element(m_bodies.cbegin(), m_bodies.cend(), CompareWeight);
	m_output << biggestMass << "\n" << (*maxWeightBody)->ToString();
}

void VolumetricSpace::PrintBodyWithLeastWeightInWater() const
{
	// константы объ€влены тут, чтоб их можно было поместить в л€мбду
	const double gravity(9.8);
	const double waterDensity(1000.0);
	auto CompareWeigtInWater = [gravity, waterDensity](const std::shared_ptr<CBody>& cBody1, const std::shared_ptr<CBody>& cBody2)
	{
		return (cBody1->GetDensity() - waterDensity) * cBody1->GetVolume() * gravity < (cBody2->GetDensity() - waterDensity)* cBody2->GetVolume() * gravity;
	};
	auto body = std::min_element(m_bodies.cbegin(), m_bodies.cend(), CompareWeigtInWater);
	m_output << leastWeightWater << "\n" << (*body)->ToString();
}