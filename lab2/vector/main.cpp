#include <iostream>
#include "Vector.hpp"

int main()
{
    try
    {
        std::vector<double> numbers = ReadNumbers(std::cin);
        std::vector<double> processedNumbers = ProcessNumbers(numbers);
        PrintSortedNumbers(processedNumbers, std::cout);
    }
    catch (const std::exception& exception)
    {
        std::cout << exception.what() << std::endl;
        std::cout << "ERROR" << std::endl;
    }
    return 0;
}