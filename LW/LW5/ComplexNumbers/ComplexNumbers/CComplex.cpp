#include "CComplex.h"

CComplex::CComplex(double real, double image)
	: m_real(real)
	, m_image(image)
{
}

double CComplex::Re() const
{
	return m_real;
}

double CComplex::Im() const
{
	return m_image;
}

double CComplex::GetMagnitude() const
{
	return sqrt(pow(m_real, 2) + pow(m_image, 2));
}

double CComplex::GetArgument() const
{
	if (fabs(m_real) < DBL_EPSILON && fabs(m_image) < DBL_EPSILON)
	{
		return std::numeric_limits<double>::quiet_NaN();
	}
	return atan2(m_image, m_real);
}

CComplex &CComplex::operator +=(CComplex const &rightOperand)
{
	m_real += rightOperand.m_real;
	m_image += rightOperand.m_image;
	return *this;
}

CComplex &CComplex::operator -=(CComplex const &rightOperand)
{
	m_real -= rightOperand.m_real;
	m_image -= rightOperand.m_image;
	return *this;
}

CComplex &CComplex::operator *=(CComplex const &rightOperand)
{
	double real = m_real * rightOperand.m_real - m_image * rightOperand.m_image;
	m_image = m_image * rightOperand.m_real + m_real * rightOperand.m_image;
	m_real = real;
	return *this;
}

CComplex &CComplex::operator /=(CComplex const &rightOperand)
{
	if (fabs(rightOperand.m_real) < DBL_EPSILON && fabs(rightOperand.m_image) < DBL_EPSILON)
	{
		throw std::invalid_argument("Division by zero is prohibited!");
	}
	const double &re = rightOperand.m_real;
	const double &im = rightOperand.m_image;
	double divider = re * re + im * im;
	double divisibleRe = m_real * re + m_image * im;
	double divisibleIm = m_image * re - m_real * im;
	m_real = divisibleRe / divider;
	m_image = divisibleIm / divider;
	return *this;
}

CComplex const CComplex::operator +() const
{
	return CComplex(m_real, m_image);
}

CComplex const CComplex::operator -() const
{
	return CComplex(-m_real, -m_image);
}

bool operator ==(CComplex lcn, const CComplex &rcn)
{
	return (fabs(lcn.Re() - rcn.Re()) < DBL_EPSILON) && (fabs(lcn.Im() - rcn.Im()) < DBL_EPSILON);
}

bool operator !=(CComplex lcn, const CComplex &rcn)
{
	return !(lcn == rcn);
}

CComplex const operator +(CComplex lcn, const CComplex &rcn)
{
	return lcn += rcn;
}

CComplex const operator -(CComplex lcn, const CComplex &rcn)
{
	return lcn -= rcn;
}

CComplex const operator *(CComplex lcn, const CComplex &rcn)
{
	return lcn *= rcn;
}

CComplex const operator /(CComplex lcn, const CComplex &rcn)
{
	return lcn /= rcn;
}

std::ostream &operator<<(std::ostream &stream, CComplex const &complexNumber)
{
	std::string signRe;
	std::string signIm;
	signRe = complexNumber.Re() >= 0 ? "" : "-";
	signIm = complexNumber.Im() >= 0 ? "+" : "-";
	double re = fabs(complexNumber.Re());
	double im = fabs(complexNumber.Im());
	stream << signRe << re << signIm << im << 'i';
	return stream;
}

std::istream &operator>>(std::istream &stream, CComplex &complexNumber)
{
	double re;
	double im;
	if ((stream >> re) && (stream >> im) && (stream.get() == 'i'))
	{
		CComplex newComplex(re, im);
		complexNumber = newComplex;
	}
	else
	{
		stream.setstate(std::ios_base::failbit | stream.rdstate()); // установка флага состояния ошибки https://www.cplusplus.com/reference/ios/ios/setstate/
	}
	return stream;
	// функция rdstate	Считывает состояние битов для флагов.
	/*тип битовой маски, описывающий объект, который может хранить данные о состоянии потока
	* badbit регистрирует потерю целостности буфера потока.
	* eofbit регистрирует конец файла при извлечении из потока.
	* failbit регистрирует ошибку извлечения корректного поля из потока.*/
}