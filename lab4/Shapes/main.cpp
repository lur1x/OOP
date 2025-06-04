#include "./include/ShapeFactory.h"
#include <iostream>
#include <vector>

int main()
{
    std::vector<std::unique_ptr<IShape>> shapes;
    std::string line;

    while (std::getline(std::cin, line))
    {
        try
        {
            auto shape = ShapeFactory::CreateShape(line);
            shapes.push_back(std::move(shape));
        }
        catch (const std::exception& e)
        {
            std::cerr << ERROR << e.what() << "\n";
        }
    }

    if (shapes.empty())
    {
        std::cout << NO_SHAPES_ENTERED << "\n";
        return 0;
    }

    auto maxAreaIt = std::max_element(shapes.begin(), shapes.end(),
                                      [](const auto& a, const auto& b) { return a->GetArea() < b->GetArea(); });

    auto minPerimeterIt = std::min_element(shapes.begin(), shapes.end(),
                                           [](const auto& a, const auto& b) { return a->GetPerimeter() < b->GetPerimeter(); });

    std::cout << MAX_AREA_SHAPE_MESSAGE << (*maxAreaIt)->ToString() << "\n";
    std::cout << MIN_PERIMETER_SHAPE_MESSAGE << (*minPerimeterIt)->ToString() << "\n";

    return 0;

}