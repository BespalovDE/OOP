#pragma once
#include "CBody.h"

class CSolidBody: public CBody
{
	public:
		double GetDensity() const override final;
		double GetMass() const override final;
	protected:
		explicit CSolidBody(double density);
	private:
		double m_density;
};