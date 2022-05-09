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
    Circle circle = Circle(Point(0.0,0.0), 2.0);
    std::vector<Point> vertices;
    vertices.push_back(Point(-0.51, 0.68));
    vertices.push_back(Point(-1.35, 0.09));
    vertices.push_back(Point(0.35, -1.77));
    vertices.push_back(Point(0.89, -1.14));
    vertices.push_back(Point(1.17, 0.74));
    vertices.push_back(Point(-0.19, 1.28));

    Polygon polygon = Polygon(vertices);
    //ASSERT_TRUE(circle.ContainedBy(polygon));
}

TEST(CirclePolygon, Outside)
{
    Circle circle = Circle(Point(0.0,0.0), 2.0);
    std::vector<Point> vertices;
    vertices.push_back(Point(-3.36, 0.9));
    vertices.push_back(Point(-4.17, 0.15));
    vertices.push_back(Point(-3.94, -0.74));
    vertices.push_back(Point(-2.39, -1.21));
    vertices.push_back(Point(-3.32, -0.66));
    vertices.push_back(Point(-2.42, -0.52));

    Polygon polygon = Polygon(vertices);
    //ASSERT_FALSE(circle.ContainedBy(polygon));
}

TEST(CirclePolygon, Surround)
{   
    Circle circle = Circle(Point(0.0,0.0), 2.0);
    std::vector<Point> vertices;
    vertices.push_back(Point(-2.48, 1.67));
    vertices.push_back(Point(-3.29, 0.92));
    vertices.push_back(Point(-3.06, -0.04));
    vertices.push_back(Point(-1.57, -2.29));
    vertices.push_back(Point(-2.52, -2.75));
    vertices.push_back(Point(-2.52, 2.8));

    Polygon polygon = Polygon(vertices);
    //ASSERT_FALSE(circle.ContainedBy(polygon));
}

TEST(CirclePolygon, Intersect)
{
    Circle circle = Circle(Point(0.0,0.0), 2.0);
    std::vector<Point> vertices;
    vertices.push_back(Point(-0.09, 2.19));
    vertices.push_back(Point(-0.91, 1.43));
    vertices.push_back(Point(-0.68, -0.55));
    vertices.push_back(Point(0.81, -1.78));
    vertices.push_back(Point(0.42, -2.81));
    vertices.push_back(Point(2.41, -0.15));

    Polygon polygon = Polygon(vertices);
    //ASSERT_FALSE(circle.ContainedBy(polygon));
}

TEST(CirclePolygon, TouchInside)
{
    Circle circle = Circle(Point(0.0,0.0), 2.0);
    std::vector<Point> vertices;
    vertices.push_back(Point(0.0, 2.0));
    vertices.push_back(Point(-0.82, 1.25));
    vertices.push_back(Point(-0.59, 0.36));
    vertices.push_back(Point(-2.0, 0.0));
    vertices.push_back(Point(-0.54, -0.82));
    vertices.push_back(Point(0.71, 1.21));

    Polygon polygon = Polygon(vertices);
    //ASSERT_TRUE(circle.ContainedBy(polygon));
}

TEST(CirclePolygon, TouchOutside)
{
    Circle circle = Circle(Point(0.0,0.0), 2.0);
    std::vector<Point> vertices;
    vertices.push_back(Point(4.16, 2.24));
    vertices.push_back(Point(1.8, 4.24));
    vertices.push_back(Point(1.25, 2.34));
    vertices.push_back(Point(2.31, 0.79));
    vertices.push_back(Point(2.0, 0.0));
    vertices.push_back(Point(4.87, 1.45));

    Polygon polygon = Polygon(vertices);
    //ASSERT_FALSE(circle.ContainedBy(polygon));
}

TEST(CirclePolygon, Conincedent)
{
    Circle circle = Circle(Point(0.0,0.0), 2.0);
    std::vector<Point> vertices;
    vertices.push_back(Point(1.04, 1.45));
    vertices.push_back(Point(-1.16, 1.16));
    vertices.push_back(Point(-1.25, -0.03));
    vertices.push_back(Point(0.0, -2.0));
    vertices.push_back(Point(0.78, 0.2));
    vertices.push_back(Point(2.0, 0.0));

    Polygon polygon = Polygon(vertices);
    //ASSERT_TRUE(circle.ContainedBy(polygon));
    //different shapes coincedent are considerting "touch inside"
}