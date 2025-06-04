#include "../include/CRectangle.h"

double CRectangle::GetArea() const
{
    return m_width * m_height;
}

double CRectangle::GetPerimeter() const
{
    return 2 * (m_width + m_height);
}

std::string CRectangle::ToString() const
{
    return RECTANGLE_OUTPUT_FORMAT + LEFT_OUTPUT_FORMAT + m_leftTop.ToString() + "\n"
           + WIDTH_OUTPUT_FORMAT + std::to_string(m_width) + "\n"
           + HEIGHT_OUTPUT_FORMAT + std::to_string(m_height) + "\n"
           + FILL_COLOR_OUTPUT_FORMAT + GetColorHex(m_fillColor) + "\n"
           + OUTLINE_COLOR_OUTPUT_FORMAT + GetColorHex(m_outlineColor) + "\n";
}

uint32_t CRectangle::GetOutlineColor() const
{
    return m_outlineColor;
}

uint32_t CRectangle::GetFillColor() const
{
    return m_fillColor;
}

CPoint CRectangle::GetLeftTop() const
{
    return m_leftTop;
}

CPoint CRectangle::GetRightBottom() const
{
    return { m_leftTop.GetX() + m_width, m_leftTop.GetY() + m_height };
}

double CRectangle::GetWidth() const
{
    return m_width;
}

double CRectangle::GetHeight() const
{
    return m_height;
}
