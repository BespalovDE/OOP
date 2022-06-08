#include "CHttpUrl.h"
#include <iostream>


// http://xn--e1akicaccic2c.xn--p1ai/pdf/cppmingw/ch10-cpp-regulyarnye-vyrazheniya.html - äîêóìåíòàöèÿ
const std::regex urlRe("^(https|http):\\/\\/(?:www\\.)?([-a-zA-Zà-ÿÀ-ß¸¨\\d@%._\\+~#=]{2,256}|(?:[0-9]{1,3}[\\.]){3}[0-9]{1,3})(?::(\\d{1,5}))?(\\/[-a-zA-Zà-ÿÀ-ß¸¨0-9@:%_\\+.~#?&\\=\\/]*)?$", std::regex::icase);
const std::regex domainRe("^[-a-zA-Zà-ÿÀ-ß¸¨\\d@:%._\\+~#=]{2,256}\\.[a-zA-Zà-ÿÀ-ß¸¨]{2,6}$", std::regex::icase);
const std::regex documentRe("^[-a-zA-Zà-ÿÀ-ß¸¨0-9@:%_\\+.~#?&\\=\\/]+$", std::regex::icase);

std::string CHttpUrl::ToLower(const std::string &str)
{
	std::string newStr = str;
	std::transform(newStr.begin(), newStr.end(), newStr.begin(), [](unsigned char ch) { return std::tolower(static_cast<unsigned char>(ch), std::locale("Russian_Russia.1251")); });
	//std::transform(strInLowLetters.begin(), strInLowLetters.end(), strInLowLetters.begin(), tolower);
	return newStr;
}

CHttpUrl::CHttpUrl(std::string const &url)
{
	std::smatch matches;
	if (std::regex_match(url, matches, urlRe))
	{
		m_protocol = matches[1].str() == "http" ? Protocol::HTTP : Protocol::HTTPS;
		std::string domain = matches[2].str();
		std::string document = matches[4].str();
		m_domain = ToLower(domain);
		m_port = GetPort(matches[3].str(), m_protocol);
		m_document = document.empty() ? "/" : ToLower(document);
	}
	else
	{
		throw UrlParsingError("invalid url");
	}
}

CHttpUrl::CHttpUrl(std::string const &domain, std::string const &document, Protocol protocol)
	: m_protocol(protocol)
{
	if (std::regex_match(domain, domainRe) && std::regex_match(document, documentRe))
	{
		m_domain = ToLower(domain);
		m_document = ToLower(document);
		m_port = m_protocol == Protocol::HTTPS ? 443 : 80;
		if (m_document[0] != '/')
		{
			m_document.insert(0, std::string("/"));
		}
	}
	else
	{
		//throw std::invalid_argument("invalid url parameters");
		throw UrlParsingError("invalid url parameters");
	}
}

CHttpUrl::CHttpUrl(std::string const &domain, std::string const &document, Protocol protocol, unsigned short port)
	: m_protocol(protocol)
{
	if (port == 0)
	{
		//throw std::invalid_argument("invalid url parameters");
		throw UrlParsingError("invalid url parameters");
	}
	m_port = port;
	if (std::regex_match(domain, domainRe) && std::regex_match(document, documentRe))
	{
		m_domain = ToLower(domain);
		m_document = ToLower(document);
		if (m_document[0] != '/')
		{
			m_document.insert(0, std::string("/"));
		}
	}
	else
	{
		//throw std::invalid_argument("invalid url parameters");
		throw UrlParsingError("invalid url parameters");
	}
}

std::string CHttpUrl::GetDomain() const
{
	return m_domain;
}

std::string CHttpUrl::GetDocument() const
{
	return m_document;
}

Protocol CHttpUrl::GetProtocol() const
{
	return m_protocol;
}

unsigned short CHttpUrl::GetPort() const
{
	return m_port;
}

unsigned short CHttpUrl::GetPort(const std::string &portStr, Protocol protocol)
{
	if (portStr.empty())
	{
		return protocol == Protocol::HTTP ? 80 : 443;
	}
	unsigned int port = std::stoi(portStr);
	if (port == 0 || port > 65535)
	{
		throw UrlParsingError("invalid port value");
	}
	return port;
}

std::string CHttpUrl::GetURL() const
{
	std::string port = (m_port == 443 && m_protocol == Protocol::HTTPS || m_port == 80 && m_protocol == Protocol::HTTP) ? "" : (':' + std::to_string(m_port));
	std::string protocol = m_protocol == Protocol::HTTPS ? "https://" : "http://";
	std::string document = m_document;
	if (document == "/")
	{
		document = "";
	}
	return protocol + m_domain + port + document;
}