#include <iostream>

int main()
{
    try
    {

    }
    catch (std::exception &exception)
    {
        std::cout << exception.what() << std::endl;
        return 1;
    }
    return 0;
}