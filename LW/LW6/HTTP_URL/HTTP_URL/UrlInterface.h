#pragma once
#include <istream>

class UrlInterface
{
public:
	UrlInterface(std::istream& input, std::ostream& output);
	bool InterfaceUrl();
private:
	std::istream &m_input;
	std::ostream &m_output;
};

