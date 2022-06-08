#pragma once
#include <string>
#include <stdexcept>

class UrlParsingError : public std::invalid_argument
{
public:
	UrlParsingError(const std::string &message);
};
