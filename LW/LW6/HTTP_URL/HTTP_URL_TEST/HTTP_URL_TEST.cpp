// HTTP_URL_test.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#define CATCH_CONFIG_MAIN
#include <iostream>
#include "../HTTP_URL/CHttpUrl.h"
#include "../HTTP_URL/UrlParsingError.h"
#include "../../../catch2/catch.hpp"
#include <Windows.h>

TEST_CASE("Url by low letters on english")
{
	CHttpUrl url("http://testurl.ru:8025/image.png/");
	CHECK(url.GetURL() == "http://testurl.ru:8025/image.png/");
	CHECK(url.GetProtocol() == Protocol::HTTP);
	CHECK(url.GetPort() == 8025);
	CHECK(url.GetDomain() == "testurl.ru");
	CHECK(url.GetDocument() == "/image.png/");
}

TEST_CASE("Url by low letters on russian")
{
	CHttpUrl url2("http://тестовыйurl.ру:8025/картинка.png/");
	CHECK(url2.GetURL() == "http://тестовыйurl.ру:8025/картинка.png/");
	CHECK(url2.GetProtocol() == Protocol::HTTP);
	CHECK(url2.GetPort() == 8025);
	CHECK(url2.GetDomain() == "тестовыйurl.ру");
	CHECK(url2.GetDocument() == "/картинка.png/");
}

TEST_CASE("Url by capital letters on english")
{
	CHttpUrl url("https://TESTURL.RU:8025/image.png/");
	CHECK(url.GetURL() == "https://testurl.ru:8025/image.png/");
	CHECK(url.GetProtocol() == Protocol::HTTPS);
	CHECK(url.GetPort() == 8025);
	CHECK(url.GetDomain() == "testurl.ru");
	CHECK(url.GetDocument() == "/image.png/");
}

TEST_CASE("Url by capital letters on russian")
{
	CHttpUrl url2("http://ТЕСТОВЫЙURL.РУ:8025/картинка.png/");
	CHECK(url2.GetURL() == "http://тестовыйurl.ру:8025/картинка.png/");
	CHECK(url2.GetProtocol() == Protocol::HTTP);
	CHECK(url2.GetPort() == 8025);
	CHECK(url2.GetDomain() == "тестовыйurl.ру");
	CHECK(url2.GetDocument() == "/картинка.png/");
}

TEST_CASE("Url without port")
{
	SECTION("url without port - http")
	{
		CHttpUrl url("http://testurl.ru/image.png/");
		CHECK(url.GetURL() == "http://testurl.ru/image.png/");
		CHECK(url.GetProtocol() == Protocol::HTTP);
		CHECK(url.GetPort() == 80);
		CHECK(url.GetDomain() == "testurl.ru");
		CHECK(url.GetDocument() == "/image.png/");
	}
	SECTION("url without port - https")
	{
		CHttpUrl url("https://testurl.ru/image.png/");
		CHECK(url.GetURL() == "https://testurl.ru/image.png/");
		CHECK(url.GetProtocol() == Protocol::HTTPS);
		CHECK(url.GetPort() == 443);
		CHECK(url.GetDomain() == "testurl.ru");
		CHECK(url.GetDocument() == "/image.png/");
	}
	SECTION("url with 0 port - https")
	{
		REQUIRE_THROWS_WITH(CHttpUrl("https://testurl.ru:0/image.png/"), "invalid port value");
	}
	SECTION("url with port 65535 - https")
	{
		CHttpUrl url("https://testurl.ru:65535/image.png/");
		CHECK(url.GetURL() == "https://testurl.ru:65535/image.png/");
		CHECK(url.GetProtocol() == Protocol::HTTPS);
		CHECK(url.GetPort() == 65535);
		CHECK(url.GetDomain() == "testurl.ru");
		CHECK(url.GetDocument() == "/image.png/");
	}
	SECTION("ip address")
	{
		CHttpUrl url("https://127.0.0.1:65535/image.png/");
		CHECK(url.GetURL() == "https://127.0.0.1:65535/image.png/");
		CHECK(url.GetProtocol() == Protocol::HTTPS);
		CHECK(url.GetPort() == 65535);
		CHECK(url.GetDomain() == "127.0.0.1");
		CHECK(url.GetDocument() == "/image.png/");
	}
	SECTION("ip address - 2")
	{
		CHttpUrl url("https://255.255.255.255:65535/image.png/");
		CHECK(url.GetURL() == "https://255.255.255.255:65535/image.png/");
		CHECK(url.GetProtocol() == Protocol::HTTPS);
		CHECK(url.GetPort() == 65535);
		CHECK(url.GetDomain() == "255.255.255.255");
		CHECK(url.GetDocument() == "/image.png/");
	}
	SECTION("url - localhost")
	{
		CHttpUrl url("https://localhost/image.png/");
		CHECK(url.GetURL() == "https://localhost/image.png/");
		CHECK(url.GetProtocol() == Protocol::HTTPS);
		CHECK(url.GetPort() == 443);
		CHECK(url.GetDomain() == "localhost");
		CHECK(url.GetDocument() == "/image.png/");
	}
}

TEST_CASE("Url without document")
{
	CHttpUrl url("https://test.com:8025/");
	CHECK(url.GetURL() == "https://test.com:8025");
	CHECK(url.GetProtocol() == Protocol::HTTPS);
	CHECK(url.GetPort() == 8025);
	CHECK(url.GetDomain() == "test.com");
	CHECK(url.GetDocument() == "/");
}

TEST_CASE("Invalid url in capital letters")
{
	REQUIRE_THROWS_WITH(CHttpUrl("htt://invalirurl:8025/testdocument/"), "invalid url");
	REQUIRE_THROWS_WITH(CHttpUrl("https:/invalirurl:8025/testdocument/"), "invalid url");
	REQUIRE_THROWS_WITH(CHttpUrl("https:invalirurl:8025/testdocument/"), "invalid url");
	REQUIRE_THROWS_WITH(CHttpUrl("https://invalidurl.com:65536/testdocument/"), "invalid port value");
}

TEST_CASE("Url constructor with 3 parameters")
{
	SECTION("url with domain and document")
	{
		CHttpUrl url("test.com", "image");
		CHECK(url.GetURL() == "http://test.com/image");
		CHECK(url.GetProtocol() == Protocol::HTTP);
		CHECK(url.GetPort() == 80);
		CHECK(url.GetDomain() == "test.com");
		CHECK(url.GetDocument() == "/image");
	}
	SECTION("url with domain, document and protocol")
	{
		CHttpUrl url("test.com", "/image.png", Protocol::HTTP);
		CHECK(url.GetURL() == "http://test.com/image.png");
		CHECK(url.GetProtocol() == Protocol::HTTP);
		CHECK(url.GetPort() == 80);
		CHECK(url.GetDomain() == "test.com");
		CHECK(url.GetDocument() == "/image.png");
	}
	SECTION("url with domain, document and protocol")
	{
		CHttpUrl url("test.com", "/image.png", Protocol::HTTP);
		CHECK(url.GetURL() == "http://test.com/image.png");
		CHECK(url.GetProtocol() == Protocol::HTTP);
		CHECK(url.GetPort() == 80);
		CHECK(url.GetDomain() == "test.com");
		CHECK(url.GetDocument() == "/image.png");
	}
	SECTION("url with domain, document and protocol")
	{
		CHttpUrl url("test.ru", "/path/to/document/", Protocol::HTTP);
		CHECK(url.GetURL() == "http://test.ru/path/to/document/");
		CHECK(url.GetProtocol() == Protocol::HTTP);
		CHECK(url.GetPort() == 80);
		CHECK(url.GetDomain() == "test.ru");
		CHECK(url.GetDocument() == "/path/to/document/");
	}
	SECTION("invalid parameters")
	{
		REQUIRE_THROWS_WITH(CHttpUrl("test.ru", "", Protocol::HTTP), "invalid url parameters");
		REQUIRE_THROWS_WITH(CHttpUrl("", "path", Protocol::HTTP), "invalid url parameters");
		REQUIRE_THROWS_WITH(CHttpUrl("", "path"), "invalid url parameters");
	}
}

TEST_CASE("url constructor with 4 parameters")
{
	SECTION("url with domain, document, protocol, port")
	{
		CHttpUrl url("test.com", "path/to/image.png", Protocol::HTTP, 8080);
		CHECK(url.GetURL() == "http://test.com:8080/path/to/image.png");
		CHECK(url.GetProtocol() == Protocol::HTTP);
		CHECK(url.GetPort() == 8080);
		CHECK(url.GetDomain() == "test.com");
		CHECK(url.GetDocument() == "/path/to/image.png");
	}
	SECTION("url with domain, document, protocol, port")
	{
		CHttpUrl url("test.com", "/image.png", Protocol::HTTPS, 80);
		CHECK(url.GetURL() == "https://test.com:80/image.png");
		CHECK(url.GetProtocol() == Protocol::HTTPS);
		CHECK(url.GetPort() == 80);
		CHECK(url.GetDomain() == "test.com");
		CHECK(url.GetDocument() == "/image.png");
	}
	SECTION("url with domain, document, protocol, port")
	{
		CHttpUrl url("test.com", "/image.png", Protocol::HTTP, 8080);
		CHECK(url.GetURL() == "http://test.com:8080/image.png");
		CHECK(url.GetProtocol() == Protocol::HTTP);
		CHECK(url.GetPort() == 8080);
		CHECK(url.GetDomain() == "test.com");
		CHECK(url.GetDocument() == "/image.png");
	}
	SECTION("url with domain, document, protocol, port 0")
	{
		REQUIRE_THROWS_WITH(CHttpUrl("test.ru", "/path/to/document/", Protocol::HTTP, 0), "invalid url parameters");
	}

	SECTION("invalid parameters")
	{
		REQUIRE_THROWS_AS(CHttpUrl("test.ru", "", Protocol::HTTP, 8080), std::invalid_argument);
		REQUIRE_THROWS_AS(CHttpUrl("", "path", Protocol::HTTP, 200), std::invalid_argument);
		REQUIRE_THROWS_AS(CHttpUrl("", "", Protocol::HTTP, 200), std::invalid_argument);
	}
}
