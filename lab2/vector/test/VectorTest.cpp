#include <gtest/gtest.h>
#include "../Vector.hpp"
#include "../VectorUtils.hpp"
#include <cmath>

double GetEpsilon(double number)
{
    std::string numberString = std::to_string(number);
    auto dotPosition = numberString.find('.');
    if (dotPosition == std::string::npos)
    {
        return 0;
    }
    auto countDecimalPlaces = numberString.size() - dotPosition - 1;

    return std::pow(10, (-1 * countDecimalPlaces));
}

TEST (process_numbers, pos_numbers)
{
    std::vector<double> numbers = {1, 2, 3, 4, 5};
    std::vector<double> expected = {1, 2, 3, 4, 5};

    std::vector<double> processedNumbers = ProcessNumbers(numbers);

    for (int i = 0; i < expected.size(); ++i)
    {
        EXPECT_EQ(expected[i], processedNumbers[i]);
    }
}

TEST (process_numbers, neg_numbers)
{
    std::vector<double> numbers = {-1, -2, -3, -4, -5};
    std::vector<double> expected = {5, 10, 15, 20, 25};

    std::vector<double> processedNumbers = ProcessNumbers(numbers);

    for (int i = 0; i < expected.size(); ++i)
    {
        EXPECT_EQ(expected[i], processedNumbers[i]);
    }
}

TEST (process_numbers, empty_numbers)
{
    std::vector<double> numbers = {};

    std::vector<double> processedNumbers = ProcessNumbers(numbers);

    EXPECT_TRUE(numbers.empty());
}

TEST (process_numbers, one_pos_number_in_neg_numbers)
{
    std::vector<double> numbers = {-1, -2, -3, -4, 5};
    std::vector<double> expected = {4, 8, 12, 16, -20};

    std::vector<double> processedNumbers = ProcessNumbers(numbers);

    for (int i = 0; i < expected.size(); ++i)
    {
        EXPECT_EQ(expected[i], processedNumbers[i]);
    }
}

TEST (process_numbers, double_numbers_by_1_count_places)
{
    std::vector<double> numbers = {1.5, -2.5, 4.5};
    std::vector<double> expected = {-3.75, 6.25, -11.25};

    std::vector<double> processedNumbers = ProcessNumbers(numbers);

    for (int i = 0; i < expected.size(); ++i)
    {
        EXPECT_NEAR(expected[i], processedNumbers[i], GetEpsilon(expected[i]));
    }
}

TEST (process_numbers, double_numbers_by_3_count_places)
{
    std::vector<double> numbers = {-1., 0., 2.5, 3.005, -.9};
    std::vector<double> expected = {-1., 0., 2.5, 3.005, -.9};

    std::vector<double> processedNumbers = ProcessNumbers(numbers);

    for (int i = 0; i < expected.size(); ++i)
    {
        EXPECT_NEAR(expected[i], processedNumbers[i], GetEpsilon(expected[i]));
    }
}

TEST (sort_numbers, handle_sort_numbers)
{
    std::vector<double> numbers = {-1., 0., 2.5, 3.005, -.9};
    std::vector<double> expected = {-1, -0.9, 0, 2.5, 3.005};

    std::vector<double> processedNumbers = SortNumbers(numbers);

    for (int i = 0; i < expected.size(); ++i)
    {
        EXPECT_NEAR(expected[i], processedNumbers[i], GetEpsilon(expected[i]));
    }
}

GTEST_API_ int main(int argc, char* argv[])
{
    std::cout << "Running test.." << std::endl;
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}