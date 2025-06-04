#ifndef SHAPES_CRECTANGLE_H
#define SHAPES_CRECTANGLE_H

#include "CPoint.h"
#include "ISolidShape.h"
#include "Constants.h"
#include <string>

class CRectangle : public ISolidShape
{
public:
    CRectangle(CPoint leftTop, double width, double height,
               uint32_t outlineColor, uint32_t fillColor)
            : m_leftTop(leftTop), m_width(width), m_height(height),
              m_outlineColor(outlineColor), m_fillColor(fillColor) {}

    double GetArea() const override;
    double GetPerimeter() const override;
    std::string ToString() const override;
    uint32_t GetOutlineColor() const override;
    uint32_t GetFillColor() const override;

    CPoint GetLeftTop() const;
    CPoint GetRightBottom() const;
    double GetWidth() const;
    double GetHeight() const;

private:
    CPoint m_leftTop;
    double m_width;
    double m_height;

    uint32_t m_fillColor;
    uint32_t m_outlineColor;
};

#endif //SHAPES_CRECTANGLE_H
