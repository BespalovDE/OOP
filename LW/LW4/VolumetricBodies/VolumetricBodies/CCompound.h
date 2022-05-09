#pragma once
#include "CBody.h"

class CCompound final: public CBody
{
    public:
        double GetDensity() const override;
        double GetVolume() const override;
        double GetMass() const override;
        std::string GetName() const override;
        bool AddChildBody(std::shared_ptr<CBody> childPtr);
    private:
        std::vector<std::shared_ptr<CBody>> m_children;
        std::vector<int> m_level;
};

