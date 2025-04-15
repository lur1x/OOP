#include <iostream>
#include "Decoder.hpp"

int main()
{
    try {
        CopyStreamWithHTMLDecode(std::cin, std::cout);
    }
    catch (std::exception &exception)
    {
        std::cout << exception.what() << std::endl;
        return 1;
    }
    return 0;
}