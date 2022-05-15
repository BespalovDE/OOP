#pragma once
#include "CSolidBody.h"

class CSphere final: public CSolidBody
{
    public:
        CSphere(double density, double radius);
        double GetVolume() const override;
        std::string GetName() const override;
        double GetRadius() const;
    private:
        void AdditionalInfo(std::ostream &strm) const override;
        double m_radius;
};