#ifndef SHAPES_SHAPEFACTORY_H
#define SHAPES_SHAPEFACTORY_H

#include "CPoint.h"
#include "IShape.h"
#include "CRectangle.h"
#include "CCircle.h"
#include "CTriangle.h"
#include "CLineSegment.h"
#include <stdexcept>
#include <memory>
#include <sstream>

class ShapeFactory
{
public:
    static std::unique_ptr<IShape> CreateShape(const std::string& description);

private:
    static uint32_t ParseColor(const std::string& colorStr);
};

#endif
