#pragma once
#include <fstream>
#include <Windows.h>
#include <boost/regex.hpp>

enum class Protocol
{
    HTTP,
    HTTPS,
    FTP
};

const int PortHTTP = 80;
const int PortHTTPS = 443;
const int PortFTP = 21;

bool ParseURL(std::string const &url, Protocol &protocol, int &port, std::string &host, std::string &document);