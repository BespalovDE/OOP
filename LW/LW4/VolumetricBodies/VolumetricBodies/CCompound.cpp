#include "CCompound.h"

std::string CCompound::GetName() const
{
	return "Compound";
}

double CCompound::GetDensity() const
{
	double densityAvg = 0;
	double volumeSum = GetVolume();
	if (volumeSum)
	{
		densityAvg = GetMass() / volumeSum;
	}
	return densityAvg;
}

double CCompound::GetVolume() const
{
	return std::accumulate(m_children.begin(), m_children.end(), 0.0,
		[](double volumeSum, const std::shared_ptr<CBody> &child) 
			{ return volumeSum + child->GetVolume(); });
}

double CCompound::GetMass() const
{
	return std::accumulate(m_children.begin(), m_children.end(), 0.0,
		[](double massSum, const std::shared_ptr<CBody> &child) 
			{ return massSum + child->GetMass(); });
}

void CCompound::SetParentPtr(std::shared_ptr<CBody> parentPtr)
{
	m_parent_ptr = std::move(parentPtr);
}

std::weak_ptr<CBody> CCompound::GetParentPtr() const
{
	return m_parent_ptr;
}

bool CCompound::AddChildBody(std::shared_ptr<CBody> childPtr)
{
	// вместо имени pointer_cast
	if (childPtr->GetName() != "Compound")
	{
		//m_children.push_back(childPtr);
		m_children.emplace_back(std::move(childPtr));
		return true;
	}
	if (childPtr.get() == this) // сам в себ€
	{
		return false;
	}
	auto childCompoundPtr = std::dynamic_pointer_cast<CCompound>(childPtr); // получаем child указатель
	if (!childCompoundPtr)
	{
		return false;
	}
	if (childCompoundPtr->GetParentPtr().lock()) // если не удаетс€ получить родител€
	{
		return false;
	}
	// сразу в While!!!
	std::shared_ptr<CBody> parentPtr = GetParentPtr().lock(); // родитель this
	while (parentPtr != nullptr) // пока не обойдем всех родителей
	{
		if (childPtr == parentPtr) // родител€ в себ€
		{
			return false;
		}
		auto parentCompoundPtr = std::dynamic_pointer_cast<CCompound>(parentPtr);
		if (parentCompoundPtr)
		{
			parentPtr = parentCompoundPtr->GetParentPtr().lock(); // родитель родител€ и тд, пока не null
		}
		else
		{
			return false;
		}
	}
	childCompoundPtr->SetParentPtr(shared_from_this()); // —оздает shared_ptr, который владеет экземпл€ром совместно с существующими владельцами shared_ptr
	m_children.emplace_back(std::move(childPtr));
	return true;
}

void CCompound::AdditionalInfo(std::ostream &strm) const
{
	strm << "BEGIN_BODIES_IN_COMPOUND:\n";
	std::string compoundBodiesInfo = std::accumulate(m_children.begin(), m_children.end(), std::string{},
		[](std::string info, const std::shared_ptr<CBody> &child) { return info += child->ToString() + '\n'; });
	strm << compoundBodiesInfo;
	strm << "END_BODIES_IN_COMPOUND\n";
}