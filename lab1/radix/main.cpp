#include <iostream>
#include <string>
#include <climits>

struct Args
{
    int destinationNotation;
    int value;
};


bool IsOverflow(const int& num, int& digit, const int& radix)
{
    return num > (INT_MAX - digit) / radix;
}

int CharToDigit(char ch)
{
    if (ch >= '0' && ch <= '9')
    {
        return ch - '0';
    }
    else if (ch >= 'A' && ch <= 'Z')
    {
        return 10 + (ch - 'A');
    }
    throw std::invalid_argument("Invalid digit");
}

bool IsValidDigit(const int& digit, const int& radix)
{
    return (digit >= 0 && digit < radix);
}

std::pair<size_t, bool> ParseSign(const std::string& str)
{
    size_t startIndex = 0;
    bool isNegative = false;

    if (!str.empty())
    {
        if (str[0] == '-')
        {
            isNegative = true;
            startIndex = 1;
        }
        else if (str[0] == '+')
        {
            startIndex = 1;
        }
    }

    return {startIndex, isNegative};
}
bool IsEmptyNumber(const size_t& startIndex, const std::string& str)
{
    return (startIndex >= str.size());
}

int StringToInt(const std::string& str, int radix)
{
    auto [startIndex, isNegative] = ParseSign(str);

    if (IsEmptyNumber(startIndex, str))
    {
        throw std::invalid_argument("Empty number");
    }

    int num = 0;
    for (size_t i = startIndex; i < str.size(); ++i)
    {
        int digit = CharToDigit(str[i]);
        if (!IsValidDigit(digit, radix))
        {
            throw std::invalid_argument("Invalid digit");
        }

        if (IsOverflow(num, digit, radix))
        {
            throw std::invalid_argument("Overflow");
        }
        num = num * radix + digit;
    }
    return isNegative ? -num : num;
}

bool IsAcceptRadix(const int& radix)
{
    const int MIN_ACCEPT_RADIX = 2;
    const int MAX_ACCEPT_RADIX = 36;
    return (radix < MIN_ACCEPT_RADIX || radix > MAX_ACCEPT_RADIX);
}

int ReadRadix(const std::string& str)
{
    const int DECIMAL_NOTATION = 10;

    int radix = StringToInt(str,DECIMAL_NOTATION);
    if (IsAcceptRadix(radix))
    {
        throw std::invalid_argument("Invalid radix");
    }

    return radix;
}

Args ParseArgs(int argc, char* argv[])
{
    const int EXPECTED_ARGS_COUNT= 4;

    if (argc != EXPECTED_ARGS_COUNT)
    {
        throw  std::invalid_argument("Invalid arguments");
    }

    int sourceNotation = ReadRadix(argv[1]);
    int destinationNotation = ReadRadix(argv[2]);
    int value = StringToInt(argv[3], sourceNotation);

    return
    {
        destinationNotation,
        value,
    };
}

char IntToChar(int digit)
{
    const int decimal = 10;
    return digit < decimal
           ? static_cast<char>('0' + digit)
           : static_cast<char>('A' + (digit - decimal));
}

std::string IntToString(int num, const int& radix)
{
    std::string newNumber;
    int positiveNumber = abs(num);
    do
    {
        int digit = positiveNumber % radix;

        newNumber.push_back(IntToChar(digit));
        positiveNumber /= radix;
    }
    while (positiveNumber > 0);

    if (num < 0)
    {
        newNumber.push_back('-');
    }

    std::reverse(newNumber.begin(), newNumber.end());
    return newNumber;

}
int main(int argc, char* argv[])
{
    try
    {
       Args args = ParseArgs(argc, argv);
       std::string newNum = IntToString(args.value, args.destinationNotation);
       std::cout << newNum << std::endl;
    }
    catch (const std::exception& exception)
    {
        std::cout << exception.what() << std::endl;
        return 1;
    }
    return 0;
}