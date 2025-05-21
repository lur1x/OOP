#include "../include/CShapesController.h"
#include <sstream>
#include <regex>
#include <limits>
#include <cmath>

namespace
{

    bool IsValidColorFormat(const std::string& colorStr)
    {
        static const std::regex colorRegex("^[0-9a-fA-F]{6}$");
        return std::regex_match(colorStr, colorRegex);
    }

    bool IsValidTriangle(const CPoint& v1, const CPoint& v2, const CPoint& v3)
    {
        const double area = std::abs(
                (v2.GetX() - v1.GetX()) * (v3.GetY() - v1.GetY()) -
                (v3.GetX() - v1.GetX()) * (v2.GetY() - v1.GetY())
        );
        return area > 1e-10; // Эпсилон-проверка для double
    }

    bool ReadColor(const std::string& colorStr, uint32_t& color, std::ostream& errors)
    {
        if (!IsValidColorFormat(colorStr))
        {
            errors << "Invalid color format. Expected RRGGBB (6 hex digits)\n";
            return false;
        }

        std::stringstream ss;
        ss << std::hex << colorStr << "FF";
        ss >> color;
        return true;
    }

    bool ReadPoint(std::istream& input, double& x, double& y, std::ostream& errors)
    {
        if (!(input >> x >> y))
        {
            errors << "Invalid point coordinates\n";
            input.clear();
            input.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return false;
        }
        return true;
    }

    bool ReadPositiveDouble(std::istream& input, double& value, const std::string& name, std::ostream& errors)
    {
        if (!(input >> value) || value <= 0)
        {
            errors << name << " must be positive number\n";
            input.clear();
            input.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return false;
        }
        return true;
    }
}

CShapesController::CShapesController(std::istream& input, std::ostream& output)
        : m_input(input), m_output(output),
          m_actionMap({
                              {"circle", [this] { AddCircle(); }},
                              {"rectangle", [this] { AddRectangle(); }},
                              {"triangle", [this] { AddTriangle(); }},
                              {"line", [this] { AddLine(); }}
                      }) {}

void CShapesController::HandleUserInput()
{
    std::string command;
    while (m_output << "> " && std::getline(m_input, command))
    {
        if (auto it = m_actionMap.find(command); it != m_actionMap.end())
        {
            it->second();
        }
        else
        {
            m_output << "Unknown command '" << command << "'\n";
        }
    }
}

void CShapesController::AddCircle()
{
    m_output << "Enter: <fillColor> <outlineColor> <x> <y> <radius>\n";

    std::string fillColorStr, outlineColorStr;
    double x, y, radius;
    uint32_t fillColor, outlineColor;

    if (!(m_input >> fillColorStr >> outlineColorStr) ||
        !ReadPoint(m_input, x, y, m_output) ||
        !ReadPositiveDouble(m_input, radius, "Radius", m_output) ||
        !ReadColor(fillColorStr, fillColor, m_output) ||
        !ReadColor(outlineColorStr, outlineColor, m_output))
    {
        return;
    }

    m_shapes.push_back(std::make_unique<CCircle>(CPoint(x, y), radius, fillColor, outlineColor));
}

void CShapesController::AddRectangle()
{
    m_output << "Enter: <fillColor> <outlineColor> <x> <y> <width> <height>\n";

    std::string fillColorStr, outlineColorStr;
    double x, y, width, height;
    uint32_t fillColor, outlineColor;

    if (!(m_input >> fillColorStr >> outlineColorStr) ||
        !ReadPoint(m_input, x, y, m_output) ||
        !ReadPositiveDouble(m_input, width, "Width", m_output) ||
        !ReadPositiveDouble(m_input, height, "Height", m_output) ||
        !ReadColor(fillColorStr, fillColor, m_output) ||
        !ReadColor(outlineColorStr, outlineColor, m_output))
    {
        return;
    }

    m_shapes.push_back(std::make_unique<CRectangle>(CPoint(x, y), width, height, fillColor, outlineColor));
}

void CShapesController::AddTriangle()
{
    m_output << "Enter: <fillColor> <outlineColor> <x1> <y1> <x2> <y2> <x3> <y3>\n";

    std::string fillColorStr, outlineColorStr;
    double x1, y1, x2, y2, x3, y3;
    uint32_t fillColor, outlineColor;

    if (!(m_input >> fillColorStr >> outlineColorStr) ||
        !ReadPoint(m_input, x1, y1, m_output) ||
        !ReadPoint(m_input, x2, y2, m_output) ||
        !ReadPoint(m_input, x3, y3, m_output) ||
        !ReadColor(fillColorStr, fillColor, m_output) ||
        !ReadColor(outlineColorStr, outlineColor, m_output))
    {
        return;
    }

    if (!IsValidTriangle(CPoint(x1, y1), CPoint(x2, y2), CPoint(x3, y3)))
    {
        m_output << "Error: Points must not be collinear\n";
        return;
    }

    m_shapes.push_back(std::make_unique<CTriangle>(
            CPoint(x1, y1), CPoint(x2, y2), CPoint(x3, y3), fillColor, outlineColor));
}

void CShapesController::AddLine()
{
    m_output << "Enter: <color> <x1> <y1> <x2> <y2>\n";

    std::string colorStr;
    double x1, y1, x2, y2;
    uint32_t color;

    if (!(m_input >> colorStr) ||
        !ReadPoint(m_input, x1, y1, m_output) ||
        !ReadPoint(m_input, x2, y2, m_output) ||
        !ReadColor(colorStr, color, m_output)) {
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
        m_output << "No shapes added" << std::endl;
        return;
    }

    const auto maxAreaShape = GetShapeWithMaxArea();
    m_output << "Shape with max area: " << maxAreaShape->ToString() << "\n";

    const auto minPerimetrShape = GetShapeWithMinPerimeter();
    m_output << "Shape with min perimeter:" << minPerimetrShape->ToString() << "\n";
}

