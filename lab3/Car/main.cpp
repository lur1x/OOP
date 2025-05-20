#include "CarController.h"
#include <iostream>

int main()
{
    CarController carController(std::cin, std::cout);
    carController.Run();

    return 0;
}