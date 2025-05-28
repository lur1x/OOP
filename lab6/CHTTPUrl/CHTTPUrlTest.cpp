#include <gtest/gtest.h>
#include "CHttpUrl.h"
#include "Constants.h"
#include <sstream>

TEST(HttpUrlConstructorTest, CorrectUrlCreation)
{
    EXPECT_NO_THROW(CHttpUrl("https://faceit.com"));
}

TEST(HttpUrlConstructorTest, CorrectUrlWithComplicatedDomain)
{
    EXPECT_NO_THROW(CHttpUrl("https://faceit.com/kvantero/ratings/solo"));
}

TEST(HttpUrlConstructorTest, CorrectUrlWithDocument)
{
    EXPECT_NO_THROW(CHttpUrl("https://faceit.com/stats"));
}

TEST(HttpUrlConstructorTest, CorrectUrlWithMinPort)
{
    EXPECT_NO_THROW(CHttpUrl("http://faceit.com:" + std::to_string(MIN_PORT) + "/stats"));
}

TEST(HttpUrlConstructorTest, CorrectUrlWithMaxPort)
{
    EXPECT_NO_THROW(CHttpUrl("https://faceit.com:" + std::to_string(MAX_PORT) + "/kvantero"));
}

TEST(HttpUrlConstructorTest, IncorrectUrlNoProtocol)
{
    EXPECT_THROW(CHttpUrl("//faceit.com/kvantero"), CUrlParsingError);
}

TEST(HttpUrlConstructorTest, IncorrectUrlNoDomain)
{
    EXPECT_THROW(CHttpUrl("http://"), CUrlParsingError);
}

TEST(HttpUrlConstructorTest, IncorrectUrlWrongProtocol)
{
    EXPECT_THROW(CHttpUrl("abcde://faceit.com/kvantero"), CUrlParsingError);
}

TEST(HttpUrlConstructorTest, IncorrectUrlWrongDomain)
{
    EXPECT_THROW(CHttpUrl("http://face it.com"), CUrlParsingError);
}

TEST(HttpUrlConstructorTest, IncorrectUrlWrongDocument)
{
    EXPECT_THROW(CHttpUrl("https://faceit.com/main / 123"), CUrlParsingError);
}

TEST(HttpUrlConstructorTest, IncorrectUrlPortNotNumber)
{
    EXPECT_THROW(CHttpUrl("http://faceit.com:string"), CUrlParsingError);
}

TEST(HttpUrlConstructorTest, IncorrectUrlPortLessThanMin)
{
    EXPECT_THROW(CHttpUrl("https://faceit.com:123abc"), CUrlParsingError);
}

TEST(HttpUrlConstructorTest, IncorrectUrlPortGreaterThanMax)
{
    EXPECT_THROW(CHttpUrl("http://faceit.com:" + std::to_string(MAX_PORT + 1)), CUrlParsingError);
}

TEST(ProtocolDomainDocumentConstructorTest, CorrectValuesEmptyDocument)
{
    EXPECT_NO_THROW(CHttpUrl("faceit.com", "", Protocol::HTTP));
}

TEST(ProtocolDomainDocumentConstructorTest, CorrectValuesWithDocument)
{
    EXPECT_NO_THROW(CHttpUrl("faceit.com", "stats/ratings", Protocol::HTTPS));
}

TEST(ProtocolDomainDocumentConstructorTest, IncorrectDomain)
{
    EXPECT_THROW(CHttpUrl("face i t .com", "", Protocol::HTTP), CUrlParsingError);
}

TEST(ProtocolDomainDocumentConstructorTest, IncorrectDocument)
{
    EXPECT_THROW(CHttpUrl("faceit.com", "st ats /kvanter o---", Protocol::HTTPS), CUrlParsingError);
}

TEST(ProtocolDomainDocumentPortConstructorTest, CorrectValuesWithRandomPort)
{
    EXPECT_NO_THROW(CHttpUrl("faceit.com", "", Protocol::HTTP, 52532));
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}