#ifndef SHAPES_CTRIANGLE_H
#define SHAPES_CTRIANGLE_H

#include "CPoint.h"
#include "ISolidShape.h"

class CTriangle : public ISolidShape
{
public:
    CTriangle(CPoint vertex1, CPoint vertex2, CPoint vertex3, uint32_t fillColor, uint32_t outlineColor);

    double GetArea() const override;
    double GetPerimeter() const override;
    std::string ToString() const override;
    uint32_t GetOutlineColor() const override;
    uint32_t GetFillColor() const override;

    CPoint GetVertex1() const;
    CPoint GetVertex2() const;
    CPoint GetVertex3() const;

private:
    CPoint m_vertex1, m_vertex2, m_vertex3;
    uint32_t m_fillColor;
    uint32_t m_outlineColor;
};
#endif //SHAPES_CTRIANGLE_H
