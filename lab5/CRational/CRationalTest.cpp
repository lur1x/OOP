#include <gtest/gtest.h>
#include "CRational.h"

TEST(CRationalTest, GetNumerator)
{
    CRational r(5, 6);
    EXPECT_EQ(r.GetNumerator(), 5);
}

TEST(CRationalTest, GetDenominator)
{
    CRational r(5, 6);
    EXPECT_EQ(r.GetDenominator(), 6);
}

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

TEST(CRationalTest, Normalization)
{
    CRational c(4, 6);
    EXPECT_EQ(c.GetNumerator(), 2);
    EXPECT_EQ(c.GetDenominator(), 3);

}

TEST(CRationalTest, ZeroDenominator)
{
    EXPECT_THROW(CRational r(1, 0), std::invalid_argument);
}

TEST(CRationalTest, RationalToDouble)
{
    CRational r(1, 2);
    EXPECT_DOUBLE_EQ(r.ToDouble(), 0.5);
}

TEST(CRationalTest, PeriodicToDouble)
{
    CRational r(1, 3);
    EXPECT_NEAR(r.ToDouble(), 0.3333333333333333, 1e-6);
}

TEST(CRationalTest, UnaryPlus)
{
    CRational a(-1, 3);
    CRational result = +a;
    EXPECT_EQ(result.GetNumerator(), -1);
    EXPECT_EQ(result.GetDenominator(), 3);

    CRational b(1, 3);
    result = +b;
    EXPECT_EQ(result.GetNumerator(), 1);
    EXPECT_EQ(result.GetDenominator(), 3);
}

TEST(CRationalTest, UnaryMinus)
{
    CRational a(-1, 3);
    CRational result = -a;
    EXPECT_EQ(result.GetNumerator(), 1);
    EXPECT_EQ(result.GetDenominator(), 3);

    CRational b(1, 3);
    result = -b;
    EXPECT_EQ(result.GetNumerator(), -1);
    EXPECT_EQ(result.GetDenominator(), 3);
}

TEST(CRationalTest, BinaryPlus)
{
    CRational first(1, 3);
    CRational second(1, 3);
    CRational result = first + second;
    EXPECT_EQ(result.GetNumerator(), 2);
    EXPECT_EQ(result.GetDenominator(), 3);

    CRational third(-1, 3);
    CRational four(-2, 3);
    result = third + four;
    EXPECT_EQ(result.GetNumerator(), -1);
    EXPECT_EQ(result.GetDenominator(), 1);

    CRational five(-1, 3);
    CRational six(1, 3);
    result = five + six;
    EXPECT_EQ(result.GetNumerator(), 0);
    EXPECT_EQ(result.GetDenominator(), 1);

    CRational seven(1, 3);
    result = seven + 1;
    EXPECT_EQ(result.GetNumerator(), 4);
    EXPECT_EQ(result.GetDenominator(), 3);

    CRational eight(1, 2);
    CRational nine(1, 6);
    result = eight + nine;
    EXPECT_EQ(result.GetNumerator(), 2);
    EXPECT_EQ(result.GetDenominator(), 3);

    CRational ten(1, 3);
    result = 1 + ten;
    EXPECT_EQ(result.GetNumerator(), 4);
    EXPECT_EQ(result.GetDenominator(), 3);
}

TEST(CRationalTest, BinaryMinus)
{
    CRational first(-1, 3);
    CRational second(1, 3);
    CRational result = first - second;
    EXPECT_EQ(result.GetNumerator(), -2);
    EXPECT_EQ(result.GetDenominator(), 3);

    CRational third(-1, 3);
    CRational four(2, 3);
    result = third - four;
    EXPECT_EQ(result.GetNumerator(), -1);
    EXPECT_EQ(result.GetDenominator(), 1);

    CRational five(1, 3);
    CRational six(1, 3);
    result = five - six;
    EXPECT_EQ(result.GetNumerator(), 0);
    EXPECT_EQ(result.GetDenominator(), 1);

    CRational seven(1, 3);
    result = seven - 1;
    EXPECT_EQ(result.GetNumerator(), -2);
    EXPECT_EQ(result.GetDenominator(), 3);

    CRational eight(1, 2);
    CRational nine(1, 6);
    result = eight - nine;
    EXPECT_EQ(result.GetNumerator(), 1);
    EXPECT_EQ(result.GetDenominator(), 3);

    CRational ten(1, 3);
    result = 1 - ten;
    EXPECT_EQ(result.GetNumerator(), 2);
    EXPECT_EQ(result.GetDenominator(), 3);
}

TEST(CRationalTest, AdditionCompound)
{
    CRational first(1, 3);
    CRational second(1, 3);
    first += second;
    EXPECT_EQ(first.GetNumerator(), 2);
    EXPECT_EQ(first.GetDenominator(), 3);
}

TEST(CRationalTest, DifferenceCompound)
{
    CRational first(-1, 3);
    CRational second(1, 3);
    first -= second;
    EXPECT_EQ(first.GetNumerator(), -2);
    EXPECT_EQ(first.GetDenominator(), 3);
}

TEST(CRationalTest, Multiplication)
{
    CRational first(-1, 3);
    CRational second(1, 3);
    CRational result = first * second;
    EXPECT_EQ(result.GetNumerator(), -1);
    EXPECT_EQ(result.GetDenominator(), 9);
}

TEST(CRationalTest, Division)
{
    CRational first(-1, 3);
    CRational second(2, 3);
    CRational result = first / second;
    EXPECT_EQ(result.GetNumerator(), -1);
    EXPECT_EQ(result.GetDenominator(), 2);

    CRational third(-1, 3);
    CRational four(0, 3);
    EXPECT_THROW(third / four, std::invalid_argument);
}

TEST(CRationalTest, MultiplicationCompound)
{
    CRational first(-1, 3);
    CRational second(1, 3);
    first *= second;
    EXPECT_EQ(first.GetNumerator(), -1);
    EXPECT_EQ(first.GetDenominator(), 9);
}

TEST(CRationalTest, DivisionCompound)
{
    CRational first(-1, 3);
    CRational second(2, 3);
    first /= second;
    EXPECT_EQ(first.GetNumerator(), -1);
    EXPECT_EQ(first.GetDenominator(), 2);
}

TEST(CRationalTest, EqualityOperator)
{
    EXPECT_FALSE(CRational(-1, 3) == CRational(2, 3));
    EXPECT_TRUE(CRational(-1, 3) == CRational(-1, 3));

    EXPECT_FALSE(CRational(-1, 3) == 1);
    EXPECT_FALSE(1 == CRational(2, 3));

    EXPECT_TRUE(CRational(3, 3) == 1);
}

TEST(CRationalTest, InequalityOperator)
{
    EXPECT_TRUE(CRational(-1, 3) != CRational(2, 3));
    EXPECT_FALSE(CRational(-1, 3) != CRational(-1, 3));

    EXPECT_TRUE(CRational(-1, 3) != 1);
    EXPECT_TRUE(1 != CRational(2, 3));

    EXPECT_FALSE(CRational(3, 3) != 1);
}

TEST(CRationalTest, LessOperator)
{
    EXPECT_TRUE(CRational(-1, 3) < CRational(2, 3));
    EXPECT_FALSE(CRational(1, 3) < CRational(-1, 3));

    EXPECT_TRUE(CRational(-1, 3) < 1);
    EXPECT_TRUE(1 < CRational(4, 3));

    EXPECT_FALSE(CRational(4, 3) < 1);
    EXPECT_FALSE(1 < CRational(2, 3));

    EXPECT_FALSE(CRational(3, 3) < 1);

}

TEST(CRationalTest, LessEnqualOperator)
{
    EXPECT_TRUE(CRational(-1, 3) <= CRational(2, 3));
    EXPECT_FALSE(CRational(1, 3) <= CRational(-1, 3));

    EXPECT_TRUE(CRational(2, 3) <= CRational(2, 3));
    EXPECT_FALSE(CRational(3, 3) <= CRational(2, 3));

    EXPECT_TRUE(CRational(-1, 3) <= 1);
    EXPECT_TRUE(1 <= CRational(4, 3));

    EXPECT_TRUE(CRational(3, 3) <= 1);
    EXPECT_TRUE(1 <= CRational(3, 3));

}

TEST(CRationalTest, GreaterOperator)
{
    EXPECT_FALSE(CRational(-1, 3) > CRational(2, 3));
    EXPECT_TRUE(CRational(1, 3) > CRational(-1, 3));

    EXPECT_FALSE(CRational(-1, 3) > 1);
    EXPECT_FALSE(1 > CRational(4, 3));

    EXPECT_TRUE(CRational(4, 3) > 1);
    EXPECT_TRUE(1 > CRational(2, 3));

    EXPECT_FALSE(CRational(3, 3) > 1);
}

TEST(CRationalTest, GreaterEnqualOperator)
{
    EXPECT_FALSE(CRational(-1, 3) >= CRational(2, 3));
    EXPECT_TRUE(CRational(1, 3) >= CRational(-1, 3));

    EXPECT_FALSE(CRational(-1, 3) >= 1);
    EXPECT_FALSE(1 >= CRational(4, 3));

    EXPECT_TRUE(CRational(4, 3) >= 1);
    EXPECT_TRUE(1 >= CRational(2, 3));

    EXPECT_TRUE(CRational(3, 3) >= 1);
}

TEST(CRationalTest, OutputOperator) {
    CRational r(3, 4);
    std::ostringstream oss;
    oss << r;
    EXPECT_EQ(oss.str(), "3/4");
}

TEST(CRationalTest, InputOperator) {
    CRational r;
    std::istringstream iss("5/6");
    iss >> r;
    EXPECT_EQ(r.GetNumerator(), 5);
    EXPECT_EQ(r.GetDenominator(), 6);

    std::istringstream is("5");
    is >> r;
    EXPECT_EQ(r.GetNumerator(), 5);
    EXPECT_EQ(r.GetDenominator(), 1);
}


int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}