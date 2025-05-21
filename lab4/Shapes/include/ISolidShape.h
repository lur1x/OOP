#ifndef SHAPES_ISOLIDSHAPE_H
#define SHAPES_ISOLIDSHAPE_H

#include "IShape.h"

class ISolidShape : public IShape
{
public:
    virtual uint32_t GetFillColor() const = 0;

    virtual ~ISolidShape() = default;
};

#endif //SHAPES_ISOLIDSHAPE_H
