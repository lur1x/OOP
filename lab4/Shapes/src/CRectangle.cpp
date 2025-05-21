#include "../include/CRectangle.h"


CRectangle::CRectangle(CPoint startPos, double width, double height, uint32_t fillColor, uint32_t outlineColor)
        : m_startPos(startPos), m_width(width), m_height(height), m_fillColor(fillColor), m_outlineColor(outlineColor)
{
}

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
    return "Left top: " + m_startPos.ToString() + "\n"
           + "Width: " + std::to_string(m_width) + "\n"
           + "Height: " + std::to_string(m_height) + "\n"
           + "Fill color: #" + GetColorHex(m_fillColor) + "\n"
           + "Outline color: #" + GetColorHex(m_outlineColor) + "\n";
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
    return m_startPos;
}

CPoint CRectangle::GetRightBottom() const
{
    return { m_startPos.GetX() + m_width, m_startPos.GetY() + m_height };
}

double CRectangle::GetWidth() const
{
    return m_width;
}

double CRectangle::GetHeight() const
{
    return m_height;
}
