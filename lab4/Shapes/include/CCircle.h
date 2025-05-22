#ifndef SHAPES_CCIRCLE_H
#define SHAPES_CCIRCLE_H

#include "ISolidShape.h"
#include "CPoint.h"
#include "Constants.h"

class CCircle : public ISolidShape
{
public:
     CCircle(CPoint center, double radius, uint32_t fillColor, uint32_t outlineColor);

     double GetArea() const override;
     double GetPerimeter() const override;
     std::string ToString() const override;
     uint32_t GetOutlineColor() const override;
     uint32_t GetFillColor() const override;

     CPoint GetCenter() const;
     double GetRadius() const;

private:
    CPoint m_center;
    double m_radius;
    uint32_t m_fillColor;
    uint32_t m_outlineColor;
};

#endif //SHAPES_CCIRCLE_H
