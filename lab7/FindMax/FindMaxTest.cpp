#include "gtest/gtest.h"
#include "FindMax.h"

TEST(FindMaxTest, EmptyVector)
{
    std::vector<int> emptyVector{};
    int maxValue;
    EXPECT_FALSE(FindMax(emptyVector, maxValue));
}

TEST(FindMaxTest, OneValueInVector)
{
    std::vector<int> emptyVector{5};
    int maxValue;
    EXPECT_TRUE(FindMax(emptyVector, maxValue));
    EXPECT_EQ(maxValue, 5);
}

TEST(FindMaxTest, IntVector)
{
    const std::vector<int> intVector = {5, 2, 9, 1, 7};
    int intMax;
    EXPECT_TRUE(FindMax(intVector, intMax));
    EXPECT_EQ(intMax, 9);
}

TEST(FindMaxTest, DoubleVector)
{
    const std::vector<double> doubleVector = {3.14, 2.71, 1.62};
    double doubleMax;
    EXPECT_TRUE(FindMax(doubleVector, doubleMax));
    EXPECT_EQ(doubleMax, 3.14);
}

TEST(FindMaxTest, StringVector)
{
    const std::vector<std::string> strVector = {"apple", "banana", "cherry"};
    std::string strMax;
    EXPECT_TRUE(FindMax(strVector, strMax));
    EXPECT_EQ(strMax, "cherry");
}

TEST(SpecializedFindMaxTest, EmptyVector)
{
    const std::vector<const char*> charPtrArr = {};
    const char* charPtrMax;
    EXPECT_FALSE(FindMax(charPtrArr, charPtrMax));
}

TEST(SpecializedFindMaxTest, OneValueInVector)
{
    const std::vector<const char*> charPtrArr = {"cherry"};
    const char* charPtrMax;
    EXPECT_TRUE(FindMax(charPtrArr, charPtrMax));
    EXPECT_EQ(charPtrMax, "cherry");
}

TEST(SpecializedFindMaxTest, ManyValueInVector)
{
    const std::vector<const char*> charPtrArr = {"apple", "cherry", "banana"};
    const char* charPtrMax;
    EXPECT_TRUE(FindMax(charPtrArr, charPtrMax));
    EXPECT_EQ(charPtrMax, "cherry");
}
int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}