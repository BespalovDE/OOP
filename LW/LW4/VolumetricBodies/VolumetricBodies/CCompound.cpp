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
	return std::accumulate(m_children.begin(), m_children.end(), 0.0f,
		[](double volumeSum, const std::shared_ptr<CBody> &child) 
			{ return volumeSum + child->GetVolume(); });
}

double CCompound::GetMass() const
{
	return std::accumulate(m_children.begin(), m_children.end(), 0.0f,
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
	if (childPtr->GetName() != "Compound")
	{
		//m_children.push_back(childPtr);
		m_children.emplace_back(std::move(childPtr));
		return true;
	}
	if (childPtr.get() == this) // ��� � ����
	{
		return false;
	}
	auto childCompoundPtr = std::dynamic_pointer_cast<CCompound>(childPtr); // �������� child ���������
	if (!childCompoundPtr)
	{
		return false;
	}
	if (childCompoundPtr->GetParentPtr().lock()) // ���� �� ������� �������� ��������
	{
		return false;
	}
	std::shared_ptr<CBody> parentPtr = GetParentPtr().lock(); // �������� this
	while (parentPtr != nullptr) // ���� �� ������� ���� ���������
	{
		if (childPtr == parentPtr) // �������� � ����
		{
			return false;
		}
		auto parentCompoundPtr = std::dynamic_pointer_cast<CCompound>(parentPtr);
		if (parentCompoundPtr)
		{
			parentPtr = parentCompoundPtr->GetParentPtr().lock(); // �������� �������� � ��, ���� �� null
		}
		else
		{
			return false;
		}
	}
	childCompoundPtr->SetParentPtr(shared_from_this()); // ������� shared_ptr, ������� ������� ����������� ��������� � ������������� ����������� shared_ptr
	return true;
}