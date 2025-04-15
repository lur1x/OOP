#include <gtest/gtest.h>
#include "../Decoder.hpp"
#include "../HTMLDecodeCore.hpp"
#include <cmath>

TEST (html_decode, decode_empty_string)
{
    std::string encodedHTML = "";
    std::string expectedDecodedHTML = "";

    std::string decodedHTML = HTMLDecode(encodedHTML);
    EXPECT_EQ(expectedDecodedHTML, decodedHTML);
}

TEST (html_decode, decode_correct_html_entities)
{
    std::string encodedHTML = "Cat &lt;says&gt; &quot;Meow&quot;. M&amp;M&apos;s";
    std::string expectedDecodedHTML = "Cat <says> \"Meow\". M&M's";

    std::string decodedHTML = HTMLDecode(encodedHTML);
    EXPECT_EQ(expectedDecodedHTML, decodedHTML);
}

TEST (html_decode, decode_invalid_html_entities)
{
    std::string encodedHTML = "This is &invalid;";
    std::string expectedDecodedHTML = "This is &invalid;";

    std::string decodedHTML = HTMLDecode(encodedHTML);
    EXPECT_EQ(expectedDecodedHTML, decodedHTML);
}

TEST (html_decode, decode_without_html_entities)
{
    std::string encodedHTML = "Hello, World!";
    std::string expectedDecodedHTML = "Hello, World!";

    std::string decodedHTML = HTMLDecode(encodedHTML);
    EXPECT_EQ(expectedDecodedHTML, decodedHTML);
}

TEST (html_decode, decode_multiple_html_entities)
{
    std::string encodedHTML = "&lt;&gt;&amp;&quot;&apos;";
    std::string expectedDecodedHTML = "<>&\"'";

    std::string decodedHTML = HTMLDecode(encodedHTML);
    EXPECT_EQ(expectedDecodedHTML, decodedHTML);
}

TEST (html_decode, decode_nested_html_entities)
{
    std::string encodedHTML = "&amp;lt;";
    std::string expectedDecodedHTML = "&lt;";

    std::string decodedHTML = HTMLDecode(encodedHTML);
    EXPECT_EQ(expectedDecodedHTML, decodedHTML);
}

TEST (html_decode, decode_repeating_html_entities)
{
    std::string encodedHTML = "&amp;&amp;&amp;";
    std::string expectedDecodedHTML = "&&&";

    std::string decodedHTML = HTMLDecode(encodedHTML);
    EXPECT_EQ(expectedDecodedHTML, decodedHTML);
}

TEST (html_decode, decode_partially_html_entities)
{
    std::string encodedHTML = "&amp;amp;";
    std::string expectedDecodedHTML = "&amp;";

    std::string decodedHTML = HTMLDecode(encodedHTML);
    EXPECT_EQ(expectedDecodedHTML, decodedHTML);
}

TEST (html_decode, decode_with_html_entity_in_begin)
{
    std::string encodedHTML = "&lt; The start";
    std::string expectedDecodedHTML = "< The start";

    std::string decodedHTML = HTMLDecode(encodedHTML);
    EXPECT_EQ(expectedDecodedHTML, decodedHTML);
}

TEST (html_decode, decode_with_html_entity_in_end)
{
    std::string encodedHTML = "The end &gt;";
    std::string expectedDecodedHTML = "The end >";

    std::string decodedHTML = HTMLDecode(encodedHTML);
    EXPECT_EQ(expectedDecodedHTML, decodedHTML);
}

TEST (html_decode, decode_all_html_entities)
{
    std::string encodedHTML = "&lt;&gt;&quot;&amp;&apos;";
    std::string expectedDecodedHTML = "<>\"&'";

    std::string decodedHTML = HTMLDecode(encodedHTML);
    EXPECT_EQ(expectedDecodedHTML, decodedHTML);
}

GTEST_API_ int main(int argc, char* argv[])
{
    std::cout << "Running test.." << std::endl;
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}