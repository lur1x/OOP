#include <math.h>
#include <gtest/gtest.h>

#include "../include/CPoint.h"
#include "../include/CCircle.h"
#include "../include/CRectangle.h"
#include "../include/CLineSegment.h"
#include "../include/CTriangle.h"

namespace
{
    constexpr uint32_t outlineColor = 0xffffff;
    constexpr uint32_t fillColor = 0xababab;
    constexpr double width = 100.0;
    constexpr double height = 50.0;
    constexpr double validRadius = 25.0;
    constexpr double triangleArea = 6.0;
    constexpr double trianglePerimetr = 12;

    CPoint firstPos = CPoint{ 3.0, 0.0 };
    CPoint secondPos = CPoint{ 0.0, 4.0 };
    CPoint thirdPos = CPoint{ 0.0, 0.0 };
}

TEST(CircleTest, Properties)
{
    CCircle circle(firstPos, validRadius, fillColor, outlineColor);
    EXPECT_DOUBLE_EQ(circle.GetCenter().GetX(), firstPos.GetX());
    EXPECT_DOUBLE_EQ(circle.GetCenter().GetY(), firstPos.GetY());

    EXPECT_DOUBLE_EQ(circle.GetArea(), (validRadius * M_PI * validRadius));
    EXPECT_DOUBLE_EQ(circle.GetPerimeter(), (2 * M_PI * validRadius));

    EXPECT_EQ(circle.GetFillColor(), fillColor);
    EXPECT_EQ(circle.GetOutlineColor(), outlineColor);
}

TEST(RectangleTest, Properties)
{
    CRectangle rect(firstPos, width, height, fillColor, outlineColor);
    EXPECT_DOUBLE_EQ(rect.GetLeftTop().GetX(), firstPos.GetX());
    EXPECT_DOUBLE_EQ(rect.GetLeftTop().GetY(), firstPos.GetY());

    EXPECT_DOUBLE_EQ(rect.GetRightBottom().GetX(), rect.GetLeftTop().GetX() + width);
    EXPECT_DOUBLE_EQ(rect.GetRightBottom().GetY(), rect.GetLeftTop().GetY() + height);

    EXPECT_DOUBLE_EQ(rect.GetHeight(), height);
    EXPECT_DOUBLE_EQ(rect.GetWidth(), width);

    EXPECT_DOUBLE_EQ(rect.GetArea(), height * width);
    EXPECT_DOUBLE_EQ(rect.GetPerimeter(), 2 * (height + width));

    EXPECT_EQ(rect.GetFillColor(), fillColor);
    EXPECT_EQ(rect.GetOutlineColor(), outlineColor);
}

TEST(LineTest, Properties)
{
    CLineSegment line(firstPos, secondPos, outlineColor);

    EXPECT_DOUBLE_EQ(line.GetArea(), 0);
    EXPECT_DOUBLE_EQ(line.GetStartPoint().GetX(), firstPos.GetX());
    EXPECT_DOUBLE_EQ(line.GetStartPoint().GetY(), firstPos.GetY());

    EXPECT_DOUBLE_EQ(line.GetEndPoint().GetX(), secondPos.GetX());
    EXPECT_DOUBLE_EQ(line.GetEndPoint().GetY(), secondPos.GetY());

    EXPECT_DOUBLE_EQ(line.GetPerimeter(), firstPos.GetDistanceTo(secondPos));

    EXPECT_EQ(line.GetOutlineColor(), outlineColor);
}

TEST(TriangleTest, Properties)
{
    CTriangle triangle(firstPos, secondPos, thirdPos, fillColor, outlineColor);

    EXPECT_DOUBLE_EQ(triangle.GetVertex1().GetX(), firstPos.GetX());
    EXPECT_DOUBLE_EQ(triangle.GetVertex1().GetY(), firstPos.GetY());

    EXPECT_DOUBLE_EQ(triangle.GetVertex2().GetX(), secondPos.GetX());
    EXPECT_DOUBLE_EQ(triangle.GetVertex2().GetY(), secondPos.GetY());

    EXPECT_DOUBLE_EQ(triangle.GetVertex3().GetX(), thirdPos.GetX());
    EXPECT_DOUBLE_EQ(triangle.GetVertex3().GetY(), thirdPos.GetY());

    EXPECT_DOUBLE_EQ(triangle.GetArea(), triangleArea);
    EXPECT_DOUBLE_EQ(triangle.GetPerimeter(), trianglePerimetr);

    EXPECT_EQ(triangle.GetFillColor(), fillColor);
    EXPECT_EQ(triangle.GetOutlineColor(), outlineColor);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}