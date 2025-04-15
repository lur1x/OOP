#include "StreamUtils.hpp"

void AssertStreamIsOpen(std::istream& input)
{
    if (input.fail())
    {
        throw std::invalid_argument("Wrong input stream");
    }
}

void AssertStreamIsEnded(std::istream& input)
{
    if (!input.eof())
    {
        throw std::runtime_error("Wrong input");
    }
}