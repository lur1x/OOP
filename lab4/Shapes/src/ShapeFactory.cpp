#include "../include/ShapeFactory.h"

std::unique_ptr<IShape> ShapeFactory::CreateShape(const std::string& description)
{
    std::istringstream iss(description);
    std::string shapeType;
    iss >> shapeType;

    if (shapeType == RECTANGLE)
    {
        double x, y, width, height;
        std::string outlineColor, fillColor;
        if (iss >> x >> y >> width >> height >> outlineColor >> fillColor)
        {
            return std::make_unique<CRectangle>(
                    CPoint(x, y), width, height,
                    ParseColor(outlineColor), ParseColor(fillColor));
        }
    }
    else if (shapeType == TRIANGLE)
    {
        double x1, y1, x2, y2, x3, y3;
        std::string outlineColor, fillColor;
        if (iss >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> outlineColor >> fillColor)
        {
            return std::make_unique<CTriangle>(
                    CPoint(x1, y1), CPoint(x2, y2), CPoint(x3, y3),
                    ParseColor(outlineColor), ParseColor(fillColor));
        }
    }
    else if (shapeType == CIRCLE)
    {
        double x, y, radius;
        std::string outlineColor, fillColor;
        if (iss >> x >> y >> radius >> outlineColor >> fillColor)
        {
            return std::make_unique<CCircle>(
                    CPoint(x, y), radius,
                    ParseColor(outlineColor), ParseColor(fillColor));
        }
    }
    else if (shapeType == LINE)
    {
        double x1, y1, x2, y2;
        std::string outlineColor;
        if (iss >> x1 >> y1 >> x2 >> y2 >> outlineColor)
        {
            return std::make_unique<CLineSegment>(
                    CPoint(x1, y1), CPoint(x2, y2), ParseColor(outlineColor));
        }
    }

    throw std::invalid_argument(INVALID_SHAPE_DESCRIPTION + description);
}

uint32_t ShapeFactory::ParseColor(const std::string& colorStr)
{
    if (colorStr.size() != 6) {

        throw std::invalid_argument(INVALID_COLOR_FORMAT);
    }
    return std::stoul(colorStr, nullptr, 16);
}
