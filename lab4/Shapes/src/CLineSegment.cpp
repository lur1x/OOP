#include "../include/CLineSegment.h"

CLineSegment::CLineSegment(CPoint startPoint, CPoint endPoint, uint32_t lineColor)
        : m_startPoint(startPoint), m_endPoint(endPoint), m_color(lineColor)
{
}

double CLineSegment::GetArea() const
{
    return 0.0;
}

double CLineSegment::GetPerimeter() const
{
    return m_startPoint.GetDistanceTo(m_endPoint);
}

uint32_t CLineSegment::GetOutlineColor() const
{
    return m_color;
}

CPoint CLineSegment::GetStartPoint() const
{
    return m_startPoint;
}

CPoint CLineSegment::GetEndPoint() const
{
    return m_endPoint;
}

std::string CLineSegment::ToString() const
{
    return LINE_OUTPUT_FORMAT + START_POINT_OUTPUT_FORMAT + m_startPoint.ToString() + "\n"
           + END_POINT_OUTPUT_FORMAT + m_endPoint.ToString() + "\n";
}
