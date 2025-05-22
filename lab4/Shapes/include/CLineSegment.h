#ifndef SHAPES_CLINESEGMENT_H
#define SHAPES_CLINESEGMENT_H

#include "IShape.h"
#include "CPoint.h"
#include "Constants.h"

class CLineSegment : public IShape
{
public:
    CLineSegment(CPoint startPoint, CPoint endPoint, uint32_t lineColor);

    double GetArea() const override;
    double GetPerimeter() const override;
    uint32_t GetOutlineColor() const override;
    CPoint GetStartPoint() const;
    CPoint GetEndPoint() const;
    std::string ToString() const override;


private:
    CPoint m_startPoint, m_endPoint;
    uint32_t m_color;
};

#endif //SHAPES_CLINESEGMENT_H
