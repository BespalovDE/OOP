#pragma once
#include "CSolidBody.h"

class CParallelepiped final: public CSolidBody
{
    public:
        CParallelepiped(double density, double width, double height, double depth);
        std::string GetName() const override;
        double GetVolume() const override;
        double GetWidth() const;
        double GetHeight() const;
        double GetDepth() const;
    private:
        void AdditionalInfo(std::ostream &strm) const override;
        double m_width;
        double m_height;
        double m_depth;
};