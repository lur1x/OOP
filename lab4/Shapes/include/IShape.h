#ifndef SHAPES_ISHAPE_H
#define SHAPES_ISHAPE_H

#include <string>
#include <cstdint>

class IShape
{
public:
    virtual double GetArea() const = 0;
    virtual double GetPerimeter() const = 0;
    virtual std::string ToString() const = 0;
    virtual uint32_t GetOutlineColor() const = 0;

    std::string GetColorHex(const uint32_t color) const;

    virtual ~IShape() = default;
};

#endif //SHAPES_ISHAPE_H
