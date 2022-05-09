#include "Circle.h"
#include "Polygon.h"
#include <gtest/gtest.h>
#include "Geom.h"
#include <cmath>
// Test should consider at least 7 conditions.
// 1. Contained
// 2. Outside
// 3. Surround
// 6. Intersect
// 4. TouchInside
// 5. TouchOutside
// 7. Conincedent

TEST(CirclePolygon, Contained)
{
    Circle circle = Circle(Point(9.15,6.0), std::sqrt(2.86));

    std::vector<Point> vertices;
    vertices.push_back(Point(4, 12));
    vertices.push_back(Point(4, 0));
    vertices.push_back(Point(16, 0));
    vertices.push_back(Point(16, 12));
    Polygon polygon = Polygon(vertices);

    ASSERT_TRUE(circle.ContainedBy(polygon));
}

TEST(CirclePolygon, Outside)
{
    Circle circle = Circle(Point(-100,6.0), std::sqrt(2.86));
    std::vector<Point> vertices;
    vertices.push_back(Point(4, 12));
    vertices.push_back(Point(4, 0));
    vertices.push_back(Point(16, 0));
    vertices.push_back(Point(16, 12));

    Polygon polygon = Polygon(vertices);
    ASSERT_FALSE(circle.ContainedBy(polygon));
}

TEST(CirclePolygon, Surround)
{   
    Circle circle = Circle(Point(9.15,6.0), 100);
    std::vector<Point> vertices;
    vertices.push_back(Point(4, 12));
    vertices.push_back(Point(4, 0));
    vertices.push_back(Point(16, 0));
    vertices.push_back(Point(16, 12));

    Polygon polygon = Polygon(vertices);
    ASSERT_FALSE(circle.ContainedBy(polygon));
}

TEST(CirclePolygon, Intersect)
{
    Circle circle = Circle(Point(9.15,6.0), std::sqrt(2.86));
    std::vector<Point> vertices;
    vertices.push_back(Point(4, 7));
    vertices.push_back(Point(4, 5));
    vertices.push_back(Point(16, 5));
    vertices.push_back(Point(16, 7));
    Polygon polygon = Polygon(vertices);
    ASSERT_FALSE(circle.ContainedBy(polygon));
}

TEST(CirclePolygon, TouchInside)
{
    Circle circle = Circle(Point(8,8), 4.0);
    std::vector<Point> vertices;
    vertices.push_back(Point(4, 12));
    vertices.push_back(Point(4, 0));
    vertices.push_back(Point(16, 0));
    vertices.push_back(Point(16, 12));
    Polygon polygon = Polygon(vertices);
    ASSERT_TRUE(circle.ContainedBy(polygon));
}

TEST(CirclePolygon, TouchOutside)
{
    Circle circle = Circle(Point(0,8), 4.0);
    std::vector<Point> vertices;
    vertices.push_back(Point(4, 12));
    vertices.push_back(Point(4, 0));
    vertices.push_back(Point(16, 0));
    vertices.push_back(Point(16, 12));
    Polygon polygon = Polygon(vertices);
    ASSERT_FALSE(circle.ContainedBy(polygon));
}

TEST(CirclePolygon, Conincedent)
{
    Circle circle = Circle(Point(8,8), 4.0);
    std::vector<Point> vertices;
    vertices.push_back(Point(4, 12));
    vertices.push_back(Point(4, 4));
    vertices.push_back(Point(12, 4));
    vertices.push_back(Point(12, 12));
    Polygon polygon = Polygon(vertices);
    ASSERT_TRUE(circle.ContainedBy(polygon));
}