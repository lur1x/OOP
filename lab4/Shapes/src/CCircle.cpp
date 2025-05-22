#include "../include/CCircle.h"
#include <math.h>


CCircle::CCircle(CPoint center, double radius, uint32_t fillColor, uint32_t outlineColor)
        : m_center(center), m_radius(radius), m_fillColor(fillColor), m_outlineColor(outlineColor)
{
}

double CCircle::GetArea() const
{
    return M_PI * m_radius * m_radius;
}

double CCircle::GetPerimeter() const
{
    return 2 * M_PI * m_radius;
}
double CCircle::GetRadius() const {
    return m_radius;
}

std::string CCircle::ToString() const
{
    return CIRCLE_OUTPUT_FORMAT + CENTER_OUTPUT_FORMAT + m_center.ToString() + "\n"
           + RADIUS_OUTPUT_FORMAT + std::to_string(GetRadius()) + "\n"
           + FILL_COLOR_OUTPUT_FORMAT + GetColorHex(GetFillColor()) + "\n"
           + OUTLINE_COLOR_OUTPUT_FORMAT + GetColorHex(GetOutlineColor()) + "\n";
}

uint32_t CCircle::GetOutlineColor() const
{
    return m_outlineColor;
}

uint32_t CCircle::GetFillColor() const
{
    return m_fillColor;
}

CPoint CCircle::GetCenter() const
{
    return m_center;
}
