#include <iostream>
#include <string>
#include "FindMax.h"

const std::string OUTPUT_MAX_INT = "Максимум (int): ";
const std::string OUTPUT_MAX_DOUBLE = "Максимум (double): ";
const std::string OUTPUT_MAX_STRING = "Максимум (string): ";
const std::string OUTPUT_MAX_CONST_CHAR = "Максимум (const char*): ";

int main()
{

    const std::vector<int> intArr = {5, 2, 9, 1, 7};
    int intMax;
    if (FindMax(intArr, intMax))
    {
        std::cout << OUTPUT_MAX_INT << intMax << std::endl;
    }

    const std::vector<double> doubleArr = {3.14, 2.71, 1.62};
    double doubleMax;
    if (FindMax(doubleArr, doubleMax))
    {
        std::cout << OUTPUT_MAX_DOUBLE << doubleMax << std::endl;
    }

    const std::vector<std::string> strArr = {"apple", "banana", "cherry"};
    std::string strMax;
    if (FindMax(strArr, strMax))
    {
        std::cout << OUTPUT_MAX_STRING << strMax << std::endl;
    }

    const std::vector<const char*> charPtrArr = {"apple", "cherry", "banana"};
    const char* charPtrMax;
    if (FindMax(charPtrArr, charPtrMax))
    {
        std::cout << OUTPUT_MAX_CONST_CHAR << charPtrMax << std::endl;
    }

    return 0;
}