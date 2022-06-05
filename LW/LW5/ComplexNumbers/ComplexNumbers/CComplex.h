#pragma once
#include <iostream>

class CComplex
{
public:
	CComplex(double real = 0, double image = 0);
	double Re()const;
	double Im()const;
	double GetMagnitude() const;
	double GetArgument() const;
	CComplex &operator +=(CComplex const &rightOperand);
	CComplex &operator -=(CComplex const &rightOperand);
	CComplex &operator *=(CComplex const &rightOperand);
	CComplex &operator /=(CComplex const &rightOperand);
	CComplex const operator +() const;
	CComplex const operator -() const;
private:
	double m_real;
	double m_image;
};

CComplex const operator +(CComplex lcn, const CComplex &rcn);
CComplex const operator -(CComplex lcn, const CComplex &rcn);
CComplex const operator *(CComplex lcn, const CComplex &rcn);
CComplex const operator /(CComplex lcn, const CComplex &rcn);

bool operator ==(CComplex lcn, const CComplex &rcn);
bool operator !=(CComplex lcn, const CComplex &rcn);
std::ostream &operator<<(std::ostream &stream, CComplex const &complexNumber);
std::istream &operator>>(std::istream &stream, CComplex &complexNumber);