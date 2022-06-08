#include "UrlInterface.h"
#include <string>
#include "CHttpUrl.h"
#include "UrlParsingError.h"
#include <Windows.h>

UrlInterface::UrlInterface(std::istream& input, std::ostream& output)
	: m_input(input)
	, m_output(output)
{
	/*SetConsoleCP(1251);// ��������� ������� �������� win-cp 1251 � ����� �����
	SetConsoleOutputCP(1251); // ��������� ������� �������� win-cp 1251 � ����� ������*/
}

bool UrlInterface::InterfaceUrl()
{
	std::string line;
	std::getline(m_input, line);
	if (line.empty())
	{
		return false;
	}
	try
	{
		CHttpUrl url(line);
		m_output << url.GetURL() << '\n';
		std::string protocol = url.GetProtocol() == Protocol::HTTPS ? "https" : "http";
		m_output << "Protocol: " << protocol << '\n';
		m_output << "Port: " << url.GetPort() << '\n';
		m_output << "Domain: " << url.GetDomain() << '\n';
		m_output << "Document: " << url.GetDocument() << '\n';
	}
	catch (UrlParsingError const& exception)
	{
		m_output << exception.what() << '\n';
	}
	return true;
}