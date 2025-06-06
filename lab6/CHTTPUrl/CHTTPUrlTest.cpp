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

TEST(CHttpUrlTest, ConstructorFromString_ValidHttpsUrlWithPort)
{
    CHttpUrl url("https://example.com:443/path/to/resource");

    EXPECT_EQ(url.GetProtocol(), Protocol::HTTPS);
    EXPECT_EQ(url.GetDomain(), "example.com:443");
    EXPECT_EQ(url.GetPort(), 443);
    EXPECT_EQ(url.GetDocument(), "/path/to/resource");
    EXPECT_EQ(url.GetURL(), "https://example.com:8080/path/to/resource");
}

TEST(CHttpUrlTest, ConstructorFromString_ValidUrlWithEmptyDocument)
{
    CHttpUrl url("http://example.com/");
    EXPECT_EQ(url.GetDocument(), "/");
}

TEST(CHttpUrlTest, ConstructorFromString_ValidUrlWithRootDocument)
{
    CHttpUrl url("http://example.com////");
    EXPECT_EQ(url.GetDocument(), "////");
}

TEST(CHttpUrlTest, ConstructorFromString_InvalidUrl_MissingProtocol)
{
    EXPECT_THROW(CHttpUrl url("://example.com"), CUrlParsingError);
}

TEST(CHttpUrlTest, ConstructorFromString_InvalidUrl_UnknownProtocol)
{
    EXPECT_THROW(CHttpUrl url("ftp://example.com"), CUrlParsingError);
}

TEST(CHttpUrlTest, ConstructorFromString_InvalidUrl_EmptyDomain)
{
    EXPECT_THROW(CHttpUrl url("http:///path"), CUrlParsingError);
}


TEST(CHttpUrlTest, ConstructorFromParts_ValidHttp) {
    CHttpUrl url("example.com", "/path", Protocol::HTTP);

    EXPECT_EQ(url.GetProtocol(), Protocol::HTTP);
    EXPECT_EQ(url.GetDomain(), "example.com");
    EXPECT_EQ(url.GetPort(), 80);
    EXPECT_EQ(url.GetDocument(), "/path");
    EXPECT_EQ(url.GetURL(), "http://example.com/path");
}

TEST(CHttpUrlTest, ConstructorFromParts_ValidHttpsWithCustomPort)
{
    CHttpUrl url("example.com", "/path", Protocol::HTTPS, 8080);

    EXPECT_EQ(url.GetProtocol(), Protocol::HTTPS);
    EXPECT_EQ(url.GetDomain(), "example.com");
    EXPECT_EQ(url.GetPort(), 8080);
    EXPECT_EQ(url.GetDocument(), "/path");
    EXPECT_EQ(url.GetURL(), "https://example.com/path:8080");
}

TEST(CHttpUrlTest, ConstructorFromParts_DocumentWithoutLeadingSlash)
{
    CHttpUrl url("example.com", "path", Protocol::HTTP);
    EXPECT_EQ(url.GetDocument(), "path");
}

TEST(CHttpUrlTest, ConstructorFromParts_EmptyDocument)
{
    CHttpUrl url("example.com", "", Protocol::HTTP);
    EXPECT_EQ(url.GetDocument(), "");
}

TEST(CHttpUrlTest, ConstructorFromParts_InvalidDomain)
{
    EXPECT_THROW(CHttpUrl url("", "/path", Protocol::HTTP), CUrlParsingError);
    EXPECT_THROW(CHttpUrl url("example com", "/path", Protocol::HTTP), CUrlParsingError);
}


TEST(CHttpUrlTest, GetURL_OmitsDefaultPort)
{
    CHttpUrl httpUrl("http://example.com/path");
    EXPECT_EQ(httpUrl.GetURL(), "http://example.com/path");

    CHttpUrl httpsUrl("https://example.com:443/path");
    EXPECT_EQ(httpsUrl.GetURL(), "https://example.com:443/path");
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
    EXPECT_EQ(url.GetDomain(), "example.com:8080");
    EXPECT_EQ(url.GetPort(), 443);
    EXPECT_EQ(url.GetDocument(), "/path/to/resource?query=value");
}

TEST(CHttpUrlTest, EdgeCases_MaxPortNumber)
{
    CHttpUrl url("http://example.com:65535/path");
    EXPECT_EQ(url.GetPort(), 80);
}

TEST(CHttpUrlTest, EdgeCases_MinPortNumber)
{
    CHttpUrl url("http://example.com:1/path");
    EXPECT_EQ(url.GetPort(), 80);
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
        CHttpUrl url("", "/path", Protocol::HTTP);
        FAIL() << "Expected CUrlParsingError";
    }
    catch (const CUrlParsingError& e)
    {
        EXPECT_STREQ(e.what(), "Invalid domain: Can't find dot in domain");
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