#include "../include/CShapesController.h"
#include <sstream>
#include <regex>
#include <cmath>

CShapesController::CShapesController(std::istream& input, std::ostream& output)
        : m_input(input), m_output(output),
          m_actionMap({
                              {CIRCLE, [this] { AddCircle(); }},
                              {RECTANGLE, [this] { AddRectangle(); }},
                              {TRIANGLE, [this] { AddTriangle(); }},
                              {LINE, [this] { AddLine(); }}
                      }) {}

bool CShapesController::IsValidColorFormat(const std::string& colorStr)
{
    static const std::regex colorRegex("^[0-9a-fA-F]{6}$");
    return std::regex_match(colorStr, colorRegex);
}

bool CShapesController::IsValidTriangle(const CPoint& v1, const CPoint& v2, const CPoint& v3)
{
    const double area = std::abs(
            (v2.GetX() - v1.GetX()) * (v3.GetY() - v1.GetY()) -
            (v3.GetX() - v1.GetX()) * (v2.GetY() - v1.GetY()));
    return area > 0;
}

bool CShapesController::ReadColor(const std::string& colorStr, uint32_t& color)
{
    if (!IsValidColorFormat(colorStr))
    {
        m_output << INVALID_COLOR_FORMAT;
        return false;
    }

    std::stringstream ss;
    ss << std::hex << colorStr << "FF";
    ss >> color;
    return true;
}

bool CShapesController::ReadPoint(std::istream& input, double& x, double& y)
{
    if (!(input >> x >> y))
    {
        m_output << INVALID_POINT;
        return false;
    }
    return true;
}

bool CShapesController::ReadPositiveDouble(std::istream& input, double& value)
{
    if (!(input >> value) || value <= 0)
    {
        m_output << POSITIVE_NUMBER_REQUIRED;
        return false;
    }
    return true;
}

void CShapesController::HandleUserInput()
{
    std::string command;
    while (true)
    {
        if (!std::getline(m_input, command))
        {
            break;
        }

        if (command.empty())
            continue;

        if (auto it = m_actionMap.find(command); it != m_actionMap.end())
        {
            it->second();
        }
        else
        {
            m_output << UNKNOWN_COMMAND << command << "'\n";
        }
    }
}

void CShapesController::AddCircle()
{
    m_output << CIRCLE_INPUT_FORMAT;

    std::string fillColorStr, outlineColorStr;
    double x, y, radius;
    uint32_t fillColor, outlineColor;

    if (!(m_input >> fillColorStr >> outlineColorStr >> x >> y >> radius) ||
        !ReadColor(fillColorStr, fillColor) ||
        !ReadColor(outlineColorStr, outlineColor))
    {
        m_output << INVALID_CIRCLE_INPUT;
        return;
    }

    if (radius <= 0)
    {
        m_output << INVALID_CIRCLE_RADIUS;
        return;
    }

    m_shapes.push_back(std::make_unique<CCircle>(CPoint(x, y), radius, fillColor, outlineColor));
}

void CShapesController::AddRectangle()
{
    m_output << RECTANGLE_INPUT_FORMAT;

    std::string fillColorStr, outlineColorStr;
    double x, y, width, height;
    uint32_t fillColor, outlineColor;

    if (!(m_input >> fillColorStr >> outlineColorStr) ||
        !ReadPoint(m_input, x, y) ||
        !ReadPositiveDouble(m_input, width) ||
        !ReadPositiveDouble(m_input, height) ||
        !ReadColor(fillColorStr, fillColor) ||
        !ReadColor(outlineColorStr, outlineColor))
    {
        return;
    }

    m_shapes.push_back(std::make_unique<CRectangle>(CPoint(x, y), width, height, fillColor, outlineColor));
}

void CShapesController::AddTriangle()
{
    m_output << TRIANGLE_INPUT_FORMAT;

    std::string fillColorStr, outlineColorStr;
    double x1, y1, x2, y2, x3, y3;
    uint32_t fillColor, outlineColor;

    if (!(m_input >> fillColorStr >> outlineColorStr) ||
        !ReadPoint(m_input, x1, y1) ||
        !ReadPoint(m_input, x2, y2) ||
        !ReadPoint(m_input, x3, y3) ||
        !ReadColor(fillColorStr, fillColor) ||
        !ReadColor(outlineColorStr, outlineColor))
    {
        return;
    }

    if (!IsValidTriangle(CPoint(x1, y1), CPoint(x2, y2), CPoint(x3, y3)))
    {
        m_output << COLLINEAR_POINTS;
        return;
    }

    m_shapes.push_back(std::make_unique<CTriangle>(
            CPoint(x1, y1), CPoint(x2, y2), CPoint(x3, y3), fillColor, outlineColor));
}

void CShapesController::AddLine()
{
    m_output << LINE_INPUT_FORMAT;

    std::string colorStr;
    double x1, y1, x2, y2;
    uint32_t color;

    if (!(m_input >> colorStr) ||
        !ReadPoint(m_input, x1, y1) ||
        !ReadPoint(m_input, x2, y2) ||
        !ReadColor(colorStr, color)) {
        return;
    }

    m_shapes.push_back(std::make_unique<CLineSegment>(CPoint(x1, y1), CPoint(x2, y2), color));
}


IShape* CShapesController::GetShapeWithMaxArea() const
{
    auto result = std::max_element(m_shapes.begin(), m_shapes.end(), [](auto& a, auto& b)
    {
        return a->GetArea() < b->GetArea();
    });

    if (result != m_shapes.end())
    {
        return result->get();
    }

    return nullptr;
}


IShape* CShapesController::GetShapeWithMinPerimeter() const
{
    auto result = std::min_element(m_shapes.begin(), m_shapes.end(), [](auto& a, auto& b)
    {
        return a->GetPerimeter() < b->GetPerimeter();
    });

    if (result != m_shapes.end())
    {
        return result->get();
    }

    return nullptr;
}

void CShapesController::PrintTaskResult()
{
    if (m_shapes.empty())
    {
        m_output << NO_SHAPES_ADDED;
        return;
    }

    const auto maxAreaShape = GetShapeWithMaxArea();
    m_output << MAX_AREA_HEADER << maxAreaShape->ToString() << "\n";

    const auto minPerimetrShape = GetShapeWithMinPerimeter();
    m_output << MIN_PERIMETER_HEADER<< minPerimetrShape->ToString() << "\n";
}

