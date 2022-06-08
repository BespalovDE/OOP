#pragma once

#include <string>
#include <iostream>
#include <regex>
#include "UrlParsingError.h"

enum class Protocol
{
	HTTP,
	HTTPS
};

class CHttpUrl
{
public:
	CHttpUrl(std::string const &url);
	CHttpUrl(std::string const &domain, std::string const &document, Protocol protocol = Protocol::HTTP);
	CHttpUrl(std::string const &domain, std::string const &document, Protocol protocol, unsigned short port);
	std::string GetURL() const;
	std::string GetDomain() const;
	std::string GetDocument() const;
	Protocol GetProtocol() const;
	unsigned short GetPort() const;
private:
	unsigned short GetPort(const std::string &portStr, Protocol protocol);
	std::string ToLower(const std::string &str);
	Protocol m_protocol;
	std::string m_domain;
	unsigned short m_port;
	std::string m_document;
};

/*unsigned short GetPort(const std::string& portStr, Protocol protocol);
std::string ToLowLetters(const std::string &str);*/