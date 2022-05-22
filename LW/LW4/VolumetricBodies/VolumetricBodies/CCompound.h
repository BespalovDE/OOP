#pragma once
#include "CBody.h"
#include "CSphere.h"
#include "CCylinder.h"
#include "CParallelepiped.h"
#include "CCone.h"

class CCompound final: 
    public CBody,
    public std::enable_shared_from_this<CCompound> // �������, ����������� �� enable_shared_from_this, ����� ������������ ������ shared_from_this � ��������-������ 
                                                   // ��� �������� ���������� shared_ptr ����������, ������� ������� �� ��������� � ������������� ����������� shared_ptr
{
    public:
        double GetDensity() const override;
        double GetVolume() const override;
        double GetMass() const override;
        std::string GetName() const override;
        bool AddChildBody(std::shared_ptr<CBody> childPtr);
    private:
        void SetParentPtr(std::shared_ptr<CBody> parentPtr);
        void AdditionalInfo(std::ostream &strm) const override;
        std::weak_ptr<CBody> GetParentPtr() const;
        std::vector<std::shared_ptr<CBody>> m_children;
        std::weak_ptr<CBody> m_parent_ptr; // m_parentPtr 
};

