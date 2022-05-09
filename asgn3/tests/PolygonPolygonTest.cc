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
    vertices.push_back(Point(-2.27, 3.25));
    vertices.push_back(Point(1.42, 3.17));
    vertices.push_back(Point(2.41, 0.92));
    vertices.push_back(Point(2.73, -1.75));
    vertices.push_back(Point(-1.9, -1.24));
    vertices.push_back(Point(-2.79,1.77));
    Polygon inner_polygon = Polygon(vertices);

    std::vector<Point> vertices2;
    vertices.push_back(Point(-2.93, 4.32));
    vertices.push_back(Point(-4.72, -1.43));
    vertices.push_back(Point(6.49, -3.25));
    vertices.push_back(Point(2.36, 4.8));
    vertices.push_back(Point(-1.63, 3.76));
    Polygon outer_polygon = Polygon(vertices2);

    //ASSERT_TRUE(inner_polygon.ContainedBy(outer_polygon));
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
    vertices.push_back(Point(-2.93, 4.32));
    vertices.push_back(Point(-4.72, -1.43));
    vertices.push_back(Point(6.49, -3.25));
    vertices.push_back(Point(2.36, 4.8));
    vertices.push_back(Point(-1.63, 3.76));
    Polygon outer_polygon = Polygon(vertices2);

    //ASSERT_FALSE(inner_polygon.ContainedBy(outer_polygon));
}

TEST(PolygonPolygon, Surround)
{
    std::vector<Point> vertices;
    vertices.push_back(Point(0.58, -0.2));
    vertices.push_back(Point(-0.2, -0.56));
    vertices.push_back(Point(0.7, -1.0));
    vertices.push_back(Point(1.56, -0.66));
    vertices.push_back(Point(1.54, 0.18));
    vertices.push_back(Point(0.96,-0.32));
    Polygon inner_polygon = Polygon(vertices);

    std::vector<Point> vertices2;
    vertices.push_back(Point(-1.2, 3.78));
    vertices.push_back(Point(-8.4, -1.16));
    vertices.push_back(Point(-1.26, -5.84));
    vertices.push_back(Point(11.0, -1.0));
    Polygon outer_polygon = Polygon(vertices2);

    //ASSERT_FALSE(inner_polygon.ContainedBy(outer_polygon));
}

TEST(PolygonPolygon, Intersect)
{
    std::vector<Point> vertices;
    vertices.push_back(Point(-0.53, 0.53));
    vertices.push_back(Point(-5.53, 3.93));
    vertices.push_back(Point(-5.53, -4.18));
    vertices.push_back(Point(4.47, -4.47));
    vertices.push_back(Point(4.47, 5.09));
    vertices.push_back(Point(-3.28,2.59));
    Polygon inner_polygon = Polygon(vertices);

    std::vector<Point> vertices2;
    vertices.push_back(Point(-1.2, 3.78));
    vertices.push_back(Point(-8.4, -1.16));
    vertices.push_back(Point(-1.26, -5.84));
    vertices.push_back(Point(11.0, -1.0));
    Polygon outer_polygon = Polygon(vertices2);

    //ASSERT_FALSE(inner_polygon.ContainedBy(outer_polygon));
}

TEST(PolygonPolygon, TouchInside)
{
    std::vector<Point> vertices;
    vertices.push_back(Point(-1.2, 3.78));
    vertices.push_back(Point(-8.4, -1.16));
    vertices.push_back(Point(-1.26, -5.84));
    vertices.push_back(Point(11.0, -1.0));
    Polygon inner_polygon = Polygon(vertices);

    std::vector<Point> vertices2;
    vertices.push_back(Point(-1.2, 3.78));
    vertices.push_back(Point(-2.02, -1.21));
    vertices.push_back(Point(0.31, -0.45));
    vertices.push_back(Point(3.8, -1.22));
    Polygon outer_polygon = Polygon(vertices2);

    //ASSERT_TRUE(inner_polygon.ContainedBy(outer_polygon));
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
    vertices.push_back(Point(-1.43, -2.93));
    vertices.push_back(Point(-1.38, -2.94));
    vertices.push_back(Point(0.94, -4.11));
    vertices.push_back(Point(-3.55, -2.99));
    Polygon outer_polygon = Polygon(vertices2);

    //ASSERT_FALSE(inner_polygon.ContainedBy(outer_polygon));
}

TEST(PolygonPolygon, Conincedent)
{
    std::vector<Point> vertices;
    vertices.push_back(Point(-3.46, 3.18));
    vertices.push_back(Point(-5.68, 2.36));
    vertices.push_back(Point(4.02, -3.66));
    vertices.push_back(Point(4.54, 3.84));
    Polygon inner_polygon = Polygon(vertices);

    std::vector<Point> vertices2;
    vertices.push_back(Point(-1.43, -2.93));
    vertices.push_back(Point(-1.38, -2.94));
    vertices.push_back(Point(1.02, 0.35));
    vertices.push_back(Point(-1.27, 0.71));
    Polygon outer_polygon = Polygon(vertices2);

    //ASSERT_TRUE(inner_polygon.ContainedBy(outer_polygon));
}