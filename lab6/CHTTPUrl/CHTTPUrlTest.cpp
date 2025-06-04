#include <gtest/gtest.h>
#include "CHttpUrl.h"
#include "Constants.h"
#include "CUrlParsingError.h"

TEST(CHttpUrlTest, ConstructorFromString_ValidHttpUrl)
{
    CHttpUrl url("http://example.com/path");

    EXPECT_EQ(url.GetProtocol(), Protocol::HTTP);
    EXPECT_EQ(url.GetDomain(), "example.com");
    EXPECT_EQ(url.GetPort(), 80);
    EXPECT_EQ(url.GetDocument(), "/path");
    EXPECT_EQ(url.GetURL(), "http://example.com/path");
}

TEST(CHttpUrlTest, ConstructorFromString_ValidHttpsUrlWithPort)
{
    CHttpUrl url("https://example.com:8080/path/to/resource");

    EXPECT_EQ(url.GetProtocol(), Protocol::HTTPS);
    EXPECT_EQ(url.GetDomain(), "example.com");
    EXPECT_EQ(url.GetPort(), 8080);
    EXPECT_EQ(url.GetDocument(), "/path/to/resource");
    EXPECT_EQ(url.GetURL(), "https://example.com:8080/path/to/resource");
}

TEST(CHttpUrlTest, ConstructorFromString_ValidUrlWithUpperCaseProtocol)
{
    CHttpUrl url("HTTPS://example.com/path");

    EXPECT_EQ(url.GetProtocol(), Protocol::HTTPS);
    EXPECT_EQ(url.GetDomain(), "example.com");
    EXPECT_EQ(url.GetPort(), 443);
    EXPECT_EQ(url.GetDocument(), "/path");
    EXPECT_EQ(url.GetURL(), "https://example.com/path");
}

TEST(CHttpUrlTest, ConstructorFromString_ValidUrlWithoutDocument)
{
    CHttpUrl url("http://example.com");
    EXPECT_EQ(url.GetProtocol(), Protocol::HTTP);
    EXPECT_EQ(url.GetDomain(), "example.com");
    EXPECT_EQ(url.GetPort(), 80);
    EXPECT_EQ(url.GetDocument(), "/");
    EXPECT_EQ(url.GetURL(), "http://example.com/");
}

TEST(CHttpUrlTest, ConstructorFromString_ValidUrlWithEmptyDocument)
{
    CHttpUrl url("http://example.com/");
    EXPECT_EQ(url.GetDocument(), "/");
}

TEST(CHttpUrlTest, ConstructorFromString_ValidUrlWithRootDocument)
{
    CHttpUrl url("http://example.com////");
    EXPECT_EQ(url.GetDocument(), "///");
}

TEST(CHttpUrlTest, ConstructorFromString_InvalidUrl_MissingProtocol)
{
    EXPECT_THROW(CHttpUrl url("://example.com"), CUrlParsingError);
}

TEST(CHttpUrlTest, ConstructorFromString_InvalidUrl_UnknownProtocol)
{
    EXPECT_THROW(CHttpUrl url("ftp://example.com"), CUrlParsingError);
}

TEST(CHttpUrlTest, ConstructorFromString_InvalidUrl_InvalidPort)
{
    EXPECT_THROW(CHttpUrl url("http://example.com:0/path"), CUrlParsingError);
    EXPECT_THROW(CHttpUrl url("http://example.com:65536/path"), CUrlParsingError);
    EXPECT_THROW(CHttpUrl url("http://example.com:abc/path"), CUrlParsingError);
}

TEST(CHttpUrlTest, ConstructorFromString_InvalidUrl_EmptyDomain)
{
    EXPECT_THROW(CHttpUrl url("http:///path"), CUrlParsingError);
}

TEST(CHttpUrlTest, ConstructorFromString_InvalidUrl_InvalidDomainChars)
{
    EXPECT_THROW(CHttpUrl url("http://exa mple.com/path"), CUrlParsingError);
    EXPECT_THROW(CHttpUrl url("http://example..com/path"), CUrlParsingError);
}

TEST(CHttpUrlTest, ConstructorFromString_ValidDomainAsUrl)
{

    CHttpUrl url("example.com");
    EXPECT_EQ(url.GetProtocol(), Protocol::HTTP);
    EXPECT_EQ(url.GetDomain(), "example.com");
    EXPECT_EQ(url.GetPort(), 80);
    EXPECT_EQ(url.GetDocument(), "/");
}

TEST(CHttpUrlTest, ConstructorFromParts_ValidHttp) {
    CHttpUrl url("example.com", "/path", "http");

    EXPECT_EQ(url.GetProtocol(), Protocol::HTTP);
    EXPECT_EQ(url.GetDomain(), "example.com");
    EXPECT_EQ(url.GetPort(), 80);
    EXPECT_EQ(url.GetDocument(), "/path");
    EXPECT_EQ(url.GetURL(), "http://example.com/path");
}

TEST(CHttpUrlTest, ConstructorFromParts_ValidHttpsWithCustomPort)
{
    CHttpUrl url("example.com", "/path", HTTPS, "8080");

    EXPECT_EQ(url.GetProtocol(), Protocol::HTTPS);
    EXPECT_EQ(url.GetDomain(), "example.com");
    EXPECT_EQ(url.GetPort(), 8080);
    EXPECT_EQ(url.GetDocument(), "/path");
    EXPECT_EQ(url.GetURL(), "https://example.com:8080/path");
}

TEST(CHttpUrlTest, ConstructorFromParts_DocumentWithoutLeadingSlash)
{
    CHttpUrl url("example.com", "path", "http");
    EXPECT_EQ(url.GetDocument(), "/path");
}

TEST(CHttpUrlTest, ConstructorFromParts_EmptyDocument)
{
    CHttpUrl url("example.com", "", "http");
    EXPECT_EQ(url.GetDocument(), "/");
}

TEST(CHttpUrlTest, ConstructorFromParts_InvalidDomain)
{
    EXPECT_THROW(CHttpUrl url("", "/path", "http"), CUrlParsingError);
    EXPECT_THROW(CHttpUrl url("example..com", "/path", "http"), CUrlParsingError);
}

TEST(CHttpUrlTest, ConstructorFromParts_InvalidPort)
{
    EXPECT_THROW(CHttpUrl url("example.com", "/path", "http", "0"), CUrlParsingError);
    EXPECT_THROW(CHttpUrl url("example.com", "/path", "http", "65536"), CUrlParsingError);
}

TEST(CHttpUrlTest, GetURL_OmitsDefaultPort)
{
    CHttpUrl httpUrl("http://example.com:80/path");
    EXPECT_EQ(httpUrl.GetURL(), "http://example.com/path");

    CHttpUrl httpsUrl("https://example.com:443/path");
    EXPECT_EQ(httpsUrl.GetURL(), "https://example.com/path");
}

TEST(CHttpUrlTest, GetURL_IncludesNonDefaultPort)
{
    CHttpUrl httpUrl("http://example.com:8080/path");
    EXPECT_EQ(httpUrl.GetURL(), "http://example.com:8080/path");

    CHttpUrl httpsUrl("https://example.com:80/path");
    EXPECT_EQ(httpsUrl.GetURL(), "https://example.com:80/path");
}

TEST(CHttpUrlTest, GetMethods)
{
    CHttpUrl url("https://example.com:8080/path/to/resource?query=value");
    EXPECT_EQ(url.GetProtocol(), Protocol::HTTPS);
    EXPECT_EQ(url.GetDomain(), "example.com");
    EXPECT_EQ(url.GetPort(), 8080);
    EXPECT_EQ(url.GetDocument(), "/path/to/resource?query=value");
}

TEST(CHttpUrlTest, EdgeCases_MaxPortNumber)
{
    CHttpUrl url("http://example.com:65535/path");
    EXPECT_EQ(url.GetPort(), 65535);
}

TEST(CHttpUrlTest, EdgeCases_MinPortNumber)
{
    CHttpUrl url("http://example.com:1/path");
    EXPECT_EQ(url.GetPort(), 1);
}

TEST(CHttpUrlTest, EdgeCases_LongDomain)
{
    std::string longDomain(253, 'a');
    CHttpUrl url(longDomain, "/path", "http");
    EXPECT_EQ(url.GetDomain(), longDomain);
}

TEST(CHttpUrlTest, EdgeCases_ComplexDocument)
{
    CHttpUrl url("http://example.com/path/with/multiple/parts?and=query&params=too#fragment");
    EXPECT_EQ(url.GetDocument(), "/path/with/multiple/parts?and=query&params=too#fragment");
}

TEST(CHttpUrlTest, ErrorMessages)
{
    try
    {
        CHttpUrl url("http://example.com:0/path");
        FAIL() << "Expected CUrlParsingError";
    }
    catch (const CUrlParsingError& e)
    {
        EXPECT_STREQ(e.what(), "Invalid Url.");
    }
    catch (...)
    {
        FAIL() << "Expected CUrlParsingError";
    }

    try
    {
        CHttpUrl url("", "/path", "http");
        FAIL() << "Expected CUrlParsingError";
    }
    catch (const CUrlParsingError& e)
    {
        EXPECT_STREQ(e.what(), "Domain cannot be empty.");
    }
    catch (...)
    {
        FAIL() << "Expected CUrlParsingError";
    }
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}