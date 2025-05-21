#include "./include/CShapesController.h"
#include <iostream>

int main()
{
    CShapesController shapesController(std::cin, std::cout);

    shapesController.HandleUserInput();

    shapesController.PrintTaskResult();

    return EXIT_SUCCESS;
}