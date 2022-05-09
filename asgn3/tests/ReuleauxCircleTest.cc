#include "Circle.h"
#include "Reuleaux.h"
#include "Geom.h"
#include <cmath>
#include <gtest/gtest.h>

// 1. Contained
// 2. Outside
// 3. Surround
// 6. Intersect
// 4. TouchInside
// 5. TouchOutside
// 7. Conincedent

TEST(ReuleauxCircle, Contained)
{
    Point rt_vertices[3] = {Point(8,8), Point(8,4), Point(11.46,6)};
    ReuleauxTriangle rt = ReuleauxTriangle(rt_vertices);
    Circle circle = Circle(Point(9.15,6), std::sqrt(5.45));

    ASSERT_TRUE(rt.ContainedBy(circle));
}

TEST(ReuleauxCircle, Outside)
{
    Point rt_vertices[3] = {Point(8,8), Point(8,4), Point(11.46,6)};
    ReuleauxTriangle rt = ReuleauxTriangle(rt_vertices);
    Circle circle = Circle(Point(19.15,6), std::sqrt(5.45));

    ASSERT_FALSE(rt.ContainedBy(circle));
}

TEST(ReuleauxCircle, Surround)
{
    Point rt_vertices[3] = {Point(8,8), Point(8,4), Point(11.46,6)};
    ReuleauxTriangle rt = ReuleauxTriangle(rt_vertices);
    Circle circle = Circle(Point(9.15,6), std::sqrt(1.45));

    ASSERT_FALSE(rt.ContainedBy(circle));
}

TEST(ReuleauxCircle, Intersect)
{
    Point rt_vertices[3] = {Point(8,8), Point(8,4), Point(11.46,6)};
    ReuleauxTriangle rt = ReuleauxTriangle(rt_vertices);
    Circle circle = Circle(Point(10.15,6), std::sqrt(5.45));

    ASSERT_FALSE(rt.ContainedBy(circle));
}

TEST(ReuleauxCircle, TouchInside)
{
    Point rt_vertices[3] = {Point(8,8), Point(8,4), Point(11.46,6)};
    ReuleauxTriangle rt = ReuleauxTriangle(rt_vertices);
    Circle circle = Circle(Point(11.46,6), 4);

    ASSERT_TRUE(rt.ContainedBy(circle));
}

TEST(ReuleauxCircle, TouchOutside)
{
    Point rt_vertices[3] = {Point(8,8), Point(8,4), Point(11.46,6)};
    ReuleauxTriangle rt = ReuleauxTriangle(rt_vertices);
    Circle circle = Circle(Point(4.54,6), std::sqrt(8.56));

    ASSERT_FALSE(rt.ContainedBy(circle));
}

TEST(ReuleauxCircle, Conincedent)
{   
    Point rt_vertices[3] = {Point(8,8), Point(8,4), Point(11.46,6)};
    ReuleauxTriangle rt = ReuleauxTriangle(rt_vertices);
    Circle circle = Circle(Point(9.15,6), std::sqrt(1.45));

    ASSERT_FALSE(rt.ContainedBy(circle));
}