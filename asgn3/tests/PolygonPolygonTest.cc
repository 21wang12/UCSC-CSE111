#include "Polygon.h"
#include <gtest/gtest.h>
#include "Geom.h"
#include <cmath>

// 1. Contained
// 2. Outside
// 3. Surround
// 6. Intersect
// 4. TouchInside
// 5. TouchOutside
// 7. Conincedent

TEST(PolygonPolygon, Contained)
{
    std::vector<Point> vertices;
    vertices.push_back(Point(-1, -1));
    vertices.push_back(Point(-1, 1));
    vertices.push_back(Point(1, 1));
    vertices.push_back(Point(1, -1));
    Polygon inner_polygon = Polygon(vertices);

    std::vector<Point> vertices2;
    vertices2.push_back(Point(-2, -2));
    vertices2.push_back(Point(-2, 2));
    vertices2.push_back(Point(2, 2));
    vertices2.push_back(Point(2,-2));
    Polygon outer_polygon = Polygon(vertices2);

    ASSERT_TRUE(inner_polygon.ContainedBy(outer_polygon));
}

TEST(PolygonPolygon, Outside)
{
    std::vector<Point> vertices;
    vertices.push_back(Point(8.42, 5.95));
    vertices.push_back(Point(8.31, 2.64));
    vertices.push_back(Point(13.1, 3.63));
    vertices.push_back(Point(13.42, 0.95));
    vertices.push_back(Point(4.69, 0.95));
    vertices.push_back(Point(4.36,5.3));
    Polygon inner_polygon = Polygon(vertices);

    std::vector<Point> vertices2;
    vertices2.push_back(Point(-2.93, 4.32));
    vertices2.push_back(Point(-4.72, -1.43));
    vertices2.push_back(Point(6.49, -3.25));
    vertices2.push_back(Point(2.36, 4.8));
    vertices2.push_back(Point(-1.63, 3.76));
    Polygon outer_polygon = Polygon(vertices2);

    ASSERT_FALSE(inner_polygon.ContainedBy(outer_polygon));
}

TEST(PolygonPolygon, Surround)
{
    std::vector<Point> vertices;
    vertices.push_back(Point(-2, -2));
    vertices.push_back(Point(-2, 2));
    vertices.push_back(Point(2, 2));
    vertices.push_back(Point(2,-2));
    
    Polygon inner_polygon = Polygon(vertices);

    std::vector<Point> vertices2;
    vertices2.push_back(Point(-1, -1));
    vertices2.push_back(Point(-1, 1));
    vertices2.push_back(Point(1, 1));
    vertices2.push_back(Point(1, -1));
    Polygon outer_polygon = Polygon(vertices2);

    ASSERT_FALSE(inner_polygon.ContainedBy(outer_polygon));
}

TEST(PolygonPolygon, Intersect)
{
    std::vector<Point> vertices;
    vertices.push_back(Point(-0.1, -2));
    vertices.push_back(Point(-0.1, 2));
    vertices.push_back(Point(0.1, 2));
    vertices.push_back(Point(0.1, -2));
    Polygon inner_polygon = Polygon(vertices);

    std::vector<Point> vertices2;
    vertices2.push_back(Point(-1, -1));
    vertices2.push_back(Point(-1, 1));
    vertices2.push_back(Point(1, 1));
    vertices2.push_back(Point(1, -1));
    Polygon outer_polygon = Polygon(vertices2);

    ASSERT_FALSE(inner_polygon.ContainedBy(outer_polygon));
}

TEST(PolygonPolygon, Intersect2)
{
    std::vector<Point> vertices;
    vertices.push_back(Point(-4, 10));
    vertices.push_back(Point(-6, 8));
    vertices.push_back(Point(-4, 6));
    vertices.push_back(Point(-2, 8));
    Polygon inner_polygon = Polygon(vertices);

    std::vector<Point> vertices2;
    vertices2.push_back(Point(-3.06, 9.66));
    vertices2.push_back(Point(-5.69, 6.96));
    vertices2.push_back(Point(-5.14, 6.43));
    vertices2.push_back(Point(-2.33, 8.95));
    Polygon outer_polygon = Polygon(vertices2);

    ASSERT_FALSE(inner_polygon.ContainedBy(outer_polygon));
}

TEST(PolygonPolygon, TouchInside)
{
    std::vector<Point> vertices;
    vertices.push_back(Point(-1, -1));
    vertices.push_back(Point(-1, 1));
    vertices.push_back(Point(1, 1));
    vertices.push_back(Point(1, -1));
    Polygon inner_polygon = Polygon(vertices);

    std::vector<Point> vertices2;
    vertices2.push_back(Point(-1, -0.5));
    vertices2.push_back(Point(-1, 0.5));
    vertices2.push_back(Point(0.5, 0.5));
    vertices2.push_back(Point(0.5, -0.5));
    Polygon outter_polygon = Polygon(vertices2);
    ASSERT_FALSE(inner_polygon.ContainedBy(outter_polygon));
}

TEST(PolygonPolygon, TouchOutside) //两个点在同一条线上，实际数值比较精准，但现在只input了两位数
{
    std::vector<Point> vertices;
    vertices.push_back(Point(-3.46, 3.18));
    vertices.push_back(Point(-5.68, 2.36));
    vertices.push_back(Point(4.02, -3.66));
    vertices.push_back(Point(4.54, 3.84));
    Polygon inner_polygon = Polygon(vertices);

    std::vector<Point> vertices2;
    vertices2.push_back(Point(-1.43, -2.93));
    vertices2.push_back(Point(-1.38, -2.94));
    vertices2.push_back(Point(0.94, -4.11));
    vertices2.push_back(Point(-3.55, -2.99));
    Polygon outer_polygon = Polygon(vertices2);

    ASSERT_FALSE(inner_polygon.ContainedBy(outer_polygon));
}

TEST(PolygonPolygon, Conincedent)
{
    std::vector<Point> vertices;
    vertices.push_back(Point(-1, -1));
    vertices.push_back(Point(-1, 1));
    vertices.push_back(Point(1, 1));
    vertices.push_back(Point(1, -1));
    Polygon inner_polygon = Polygon(vertices);

    std::vector<Point> vertices2;
    vertices2.push_back(Point(-1, -1));
    vertices2.push_back(Point(-1, 1));
    vertices2.push_back(Point(1, 1));
    vertices2.push_back(Point(1, -1));
    Polygon outer_polygon = Polygon(vertices2);

    ASSERT_FALSE(inner_polygon.ContainedBy(outer_polygon));
}