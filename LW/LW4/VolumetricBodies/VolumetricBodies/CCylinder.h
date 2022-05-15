#pragma once
#include "CSolidBody.h"

class CCylinder final: public CSolidBody
{
    public:
        CCylinder(double density, double baseRadius, double height);
        std::string GetName() const override;
        double GetVolume() const override;
        double GetHeight() const;
        double GetBaseRadius() const;
    private:
        void AdditionalInfo(std::ostream &strm) const override;
        double m_height;
        double m_baseRadius;
};