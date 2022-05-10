#include "ParserURL.h"

std::string GetLowerString(std::string str)
{
    std::transform(str.begin(), str.end(), str.begin(), [](unsigned char ch) { return std::tolower(static_cast<unsigned char>(ch), std::locale("Russian_Russia.1251")); });
    return str;
}

bool CheckProtocol(std::string &strProtocol, Protocol &protocol)
{
    if (strProtocol == "http")
    {
        protocol = Protocol::HTTP;
    }
    else if (strProtocol == "https")
    {
        protocol = Protocol::HTTPS;
    }
    else if (strProtocol == "ftp")
    {
        protocol = Protocol::FTP;
    }
    else
    {
        return false;
    }
}

int GetPort(Protocol &protocol, std::string &stringPort)
{
    int port;
    if (!stringPort.empty())
    {
        port = stoi(stringPort);
    }
    else
    {
        if (protocol == Protocol::HTTP)
        {
            port = PortHTTP;
        }
        else if (protocol == Protocol::HTTPS)
        {
            port = PortHTTPS;
        }
        else
        {
            port = PortFTP;
        }
    }
    return port;
}

bool ParseURL(std::string const &url, Protocol &protocol, int &port, std::string &host, std::string &document)
{
    //boost::regex ex("(http|https|ftp)://([^/ :]+):?([^/ ]*)(/?[^ #?]*)\\x3f?([^ #]*)#?([^ ]*)"); // пример
    boost::regex ex("(http|https|ftp)://([^/ :]+):?(:?[^/ ]*)/?(/?[^ ]*)");
    boost::cmatch what;
    std::string stringPort;
    std::string urlRegex = GetLowerString(url);
    if (regex_match(urlRegex.c_str(), what, ex))
    {
        std::string strProtocol = std::string(what[1].first, what[1].second);
        host = std::string(what[2].first, what[2].second);
        stringPort = std::string(what[3].first, what[3].second);
        document = std::string(what[4].first, what[4].second);
        if (!CheckProtocol(strProtocol, protocol) || host.empty())
        {
            return false;
        }
        port = GetPort(protocol, stringPort);
    }
    else
    {
        return false;
    }
    return true;
}
