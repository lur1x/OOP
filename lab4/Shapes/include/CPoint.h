#ifndef SHAPES_CPOINT_H
#define SHAPES_CPOINT_H

#include <string>

class CPoint
{
public:
    CPoint(double x, double y) : m_x(x), m_y(y) {};

    double GetX() const;
    double GetY() const;
    double GetDistanceTo(const CPoint& other) const;
    std::string ToString() const;
private:
    double m_x;
    double m_y;
};


#endif //SHAPES_CPOINT_H
