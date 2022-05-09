#include "Polygon.h"
#include "Reuleaux.h"
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

// Modified by Shuowang
TEST(PolygonReuleaux, Contained)
{
    std::vector<Point> vertices;
    vertices.push_back(Point(8.56, 7.46));
    vertices.push_back(Point(10 , 6));
    vertices.push_back(Point(8.77, 4.68));
    Polygon polygon = Polygon(vertices);

    Point rt_vertices[3] = {Point(8,8), Point(8,4), Point(11.46,6)};
    ReuleauxTriangle rt = ReuleauxTriangle(rt_vertices);
    ASSERT_TRUE(polygon.ContainedBy(rt));
}

TEST(PolygonReuleaux, Outside)
{
    std::vector<Point> vertices;
    vertices.push_back(Point(7.58, 7.46));
    vertices.push_back(Point(5.16, 0.02));
    vertices.push_back(Point(12.92, -8.12));
    vertices.push_back(Point(28.02, 3.58));
    vertices.push_back(Point(20.24, 8.66));
    Polygon polygon = Polygon(vertices);

    Point rt_vertices[3] = {Point(-4,0), Point(0,0), Point(-2,3.46)};
    ReuleauxTriangle rt = ReuleauxTriangle(rt_vertices);
    ASSERT_FALSE(polygon.ContainedBy(rt));
}

// Modified by Shuowang
TEST(PolygonReuleaux, Surround)
{
    std::vector<Point> vertices;
    vertices.push_back(Point(4, 12));
    vertices.push_back(Point(4, 0));
    vertices.push_back(Point(16, 0));
    vertices.push_back(Point(16, 12));
    Polygon polygon = Polygon(vertices);

    Point rt_vertices[3] = {Point(8,8), Point(8,4), Point(11.46,6)};
    ReuleauxTriangle rt = ReuleauxTriangle(rt_vertices);
    ASSERT_FALSE(polygon.ContainedBy(rt));
}

TEST(PolygonReuleaux, Intersect)
{
    std::vector<Point> vertices;
    vertices.push_back(Point(-3.43, 3.18));
    vertices.push_back(Point(-5.16, 2.55));
    vertices.push_back(Point(-3.5, 1.77));
    vertices.push_back(Point(-4.29, 2.26));
    vertices.push_back(Point(-3.09, 2.18));
    Polygon polygon = Polygon(vertices);

    Point rt_vertices[3] = {Point(-4,0), Point(0,0), Point(-2,3.46)};
    ReuleauxTriangle rt = ReuleauxTriangle(rt_vertices);
    ASSERT_FALSE(polygon.ContainedBy(rt));
}

TEST(PolygonReuleaux, TouchInside)
{
    std::vector<Point> vertices;
    vertices.push_back(Point(-4,0));
    vertices.push_back(Point(0,0));
    vertices.push_back(Point(-2,3.46));
    Polygon polygon = Polygon(vertices);

    Point rt_vertices[3] = {Point(-4,0), Point(0,0), Point(-2,3.46)};
    ReuleauxTriangle rt = ReuleauxTriangle(rt_vertices);
    ASSERT_TRUE(polygon.ContainedBy(rt));
}

TEST(PolygonReuleaux, TouchOutside)
{
    std::vector<Point> vertices;
    vertices.push_back(Point(-0.31, 3.2));
    vertices.push_back(Point(-0.57, 2.06));
    vertices.push_back(Point(-0.15, 1.93));
    vertices.push_back(Point(0.27, 1.68));
    vertices.push_back(Point(0.03, 2.2));
    Polygon polygon = Polygon(vertices);

    Point rt_vertices[3] = {Point(-4,0), Point(0,0), Point(-2,3.46)};
    ReuleauxTriangle rt = ReuleauxTriangle(rt_vertices);
    ASSERT_FALSE(polygon.ContainedBy(rt));
}

TEST(PolygonReuleaux, Conincedent)
{
    std::vector<Point> vertices;
    vertices.push_back(Point(-1.58, 2.02));
    vertices.push_back(Point(-4.0, 0.0));
    vertices.push_back(Point(-1.65, 0.61));
    vertices.push_back(Point(-1, 0.5));
    vertices.push_back(Point(-1.24, 1.02));
    Polygon polygon = Polygon(vertices);

    Point rt_vertices[3] = {Point(-4,0), Point(0,0), Point(-2,3.46)};
    ReuleauxTriangle rt = ReuleauxTriangle(rt_vertices);
    ASSERT_TRUE(polygon.ContainedBy(rt));
}
