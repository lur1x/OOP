#include "VectorUtils.hpp"
#include <algorithm>

std::vector<double> SortNumbers(const std::vector<double>& numbers)
{
    std::vector<double> sortedNumbers = numbers;
    std::sort(sortedNumbers.begin(), sortedNumbers.end());

    return sortedNumbers;
}
