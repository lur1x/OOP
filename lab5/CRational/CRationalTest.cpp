#include <gtest/gtest.h>
#include "CRational.h"

TEST(CRationalTest, DefaultConstructor)
{
    CRational r;
    EXPECT_EQ(r.GetNumerator(), 0);
    EXPECT_EQ(r.GetDenominator(), 1);
}

TEST(CRationalTest, IntConstructor)
{
    CRational r(7);
    EXPECT_EQ(r.GetNumerator(), 7);
    EXPECT_EQ(r.GetDenominator(), 1);
}

TEST(CRationalTest, FractionConstructor)
{
    CRational r(7, 8);
    EXPECT_EQ(r.GetNumerator(), 7);
    EXPECT_EQ(r.GetDenominator(), 8);
}

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}