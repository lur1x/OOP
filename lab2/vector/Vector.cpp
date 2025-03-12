#include "StreamUtils.hpp"
#include "VectorUtils.hpp"
#include "Vector.hpp"
#include <iomanip>

std::vector<double> ReadNumbers(std::istream& input)
{
    AssertStreamIsOpen(input);

    std::vector<double> numbers;

    double number;
    while (input >> number)
    {
        numbers.push_back(number);
    }

    AssertStreamIsEnded(input);

    return numbers;
}

std::vector<double> ProcessNumbers(const std::vector<double>& numbers)
{
    if (numbers.empty())
    {
        return numbers;
    }

    const double MIN_NUMBERS = *std::min_element(numbers.begin(), numbers.end());
    std::vector<double> processedNumbers;

    for (auto& number : numbers)
    {
        processedNumbers.push_back(number * MIN_NUMBERS);
    }

    return processedNumbers;
}

std::vector<double> SortNumbers(const std::vector<double>& numbers)
{
    std::vector<double> sortedNumbers = numbers;
    std::sort(sortedNumbers.begin(), sortedNumbers.end());

    return sortedNumbers;
}


void PrintSortedNumbers(const std::vector<double>& numbers, std::ostream& output)
{
    std::vector<double> sortedNumbers = SortNumbers(numbers);
    const int COUNT_DIGITS_AFTER_POINT = 3;
    output << std::fixed << std::setprecision(COUNT_DIGITS_AFTER_POINT);

    for (auto& number : numbers)
    {
        output << number << " ";
    }
    output << std::endl;
}