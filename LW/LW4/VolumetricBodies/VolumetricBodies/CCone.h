#pragma once
#include "CSolidBody.h"

class CCone final: public CSolidBody
{
    public:
        CCone(double density, double baseRadius, double height);
        std::string GetName() const override;
        double GetVolume() const override;
        double GetHeight() const;
        double GetBaseRadius() const;
    private:
        void AdditionalInfo(std::ostream &strm) const override;
        double m_baseRadius;
        double m_height;
};
