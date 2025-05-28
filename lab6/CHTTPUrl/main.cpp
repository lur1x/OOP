#include "Controller.h"
#include <iostream>

int main()
{
    Controller controller(std::cin, std::cout);
    controller.Run();
    return 0;
}