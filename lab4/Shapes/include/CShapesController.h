#ifndef SHAPES_CSHAPESCONTROLLER_H
#define SHAPES_CSHAPESCONTROLLER_H

#include <iostream>
#include <map>
#include <functional>
#include <string>
#include <vector>
#include <memory>

#include "CShapesController.h"
#include "CCircle.h"
#include "CLineSegment.h"
#include "CRectangle.h"
#include "CTriangle.h"
#include "IShape.h"
#include "Constants.h"

class CShapesController
{
public:
    CShapesController(std::istream& input, std::ostream& output);

    void HandleUserInput();
    void PrintTaskResult();

private:
    std::istream& m_input;
    std::ostream& m_output;

    std::vector<std::unique_ptr<IShape>> m_shapes;

    using Handler = std::function<void()>;
    using ActionMap = std::map<std::string, Handler>;
    const ActionMap m_actionMap;

    void AddCircle();
    void AddRectangle();
    void AddTriangle();
    void AddLine();

    IShape* GetShapeWithMaxArea() const;
    IShape* GetShapeWithMinPerimeter() const;

    bool IsValidColorFormat(const std::string& colorStr);
    bool IsValidTriangle(const CPoint& v1, const CPoint& v2, const CPoint& v3);
    bool ReadColor(const std::string& colorStr, uint32_t& color);
    bool ReadPoint(std::istream& input, double& x, double& y);
    bool ReadPositiveDouble(std::istream& input, double& value);
};

#endif //SHAPES_CSHAPESCONTROLLER_H
