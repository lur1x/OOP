#include "../include/CPoint.h"
#include <cmath>

double CPoint::GetX() const
{
    return m_x;
}

double CPoint::GetY() const
{
    return m_y;
}

double CPoint::GetDistanceTo(const CPoint& other) const
{
    return std::hypot(m_x - other.m_x, m_y - other.m_y);
}

std::string CPoint::ToString() const
{
    return "(" + std::to_string(m_x) + ", " + std::to_string(m_y) + ")";
}