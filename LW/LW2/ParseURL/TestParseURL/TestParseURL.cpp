#include <iostream>
#include <fstream>
#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "../ParseURL/ParserURL.h"

TEST_CASE("Main test")
{
    std::string url;
    Protocol protocol;
    int port = 0;
    std::string host;
    std::string document;
    SECTION("Not correct values")
    {
        SECTION("Not correct protocol")
        {
            url = "htt://yandex.ru/";
            REQUIRE(!ParseURL(url, protocol, port, host, document));
        }
        SECTION("Not correct input value")
        {
            url = "http:/yandexr/";
            REQUIRE(!ParseURL(url, protocol, port, host, document));
        }
    }
    SECTION("Correct values")
    {    
        SECTION("Short hosts ftp")
        {
            url = "ftp://ftp.intel.com/";
            REQUIRE(ParseURL(url, protocol, port, host, document));
            REQUIRE(protocol == Protocol::FTP);
            REQUIRE(port == PortFTP);
            REQUIRE(host == "ftp.intel.com");
            REQUIRE(document == "");
        }
        SECTION("Short hosts http")
        {
            url = "http://www.google.com";
            REQUIRE(ParseURL(url, protocol, port, host, document));
            REQUIRE(protocol == Protocol::HTTP);
            REQUIRE(port == PortHTTP);
            REQUIRE(host == "www.google.com");
            REQUIRE(document == "");
        }
        SECTION("Short hosts https")
        {
            url = "https://yandex.ru/";
            REQUIRE(ParseURL(url, protocol, port, host, document));
            REQUIRE(protocol == Protocol::HTTPS);
            REQUIRE(port == PortHTTPS);
            REQUIRE(host == "yandex.ru");
            REQUIRE(document == "");
        }
        SECTION("Long hosts")
        {
            url = "https://mail.google.com/mail/";
            REQUIRE(ParseURL(url, protocol, port, host, document));
            REQUIRE(protocol == Protocol::HTTPS);
            REQUIRE(port == PortHTTPS);
            REQUIRE(host == "mail.google.com");
            REQUIRE(document == "mail/");
        }
        SECTION("Hosts with port")
        {
            url = "https://www.google.com:443/webhp?gws_rd=ssl";
            REQUIRE(ParseURL(url, protocol, port, host, document));
            REQUIRE(protocol == Protocol::HTTPS);
            REQUIRE(port == PortHTTPS);
            REQUIRE(host == "www.google.com");
            REQUIRE(document == "webhp?gws_rd=ssl");
        }
    }
}