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
        double m_radius;
};