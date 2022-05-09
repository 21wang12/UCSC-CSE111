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

TEST(ReuleauxPolygon, Contained)
{
    Point rt_vertices[3] = {Point(-4,0), Point(0,0), Point(-2,3.46)};
    ReuleauxTriangle rt = ReuleauxTriangle(rt_vertices);
    std::vector<Point> vertices;
    vertices.push_back(Point(-2.34, 2.04));
    vertices.push_back(Point(-2.89, 1.65));
    vertices.push_back(Point(-2.18, 0.76));
    vertices.push_back(Point(-1.5, 1.5));
    vertices.push_back(Point(-1.72, 2.82));
    Polygon polygon = Polygon(vertices);
    //ASSERT_TRUE(rt.ContainedBy(polygon));
}

TEST(ReuleauxPolygon, Outside)
{
    Point rt_vertices[3] = {Point(-4,0), Point(0,0), Point(-2,3.46)};
    ReuleauxTriangle rt = ReuleauxTriangle(rt_vertices);
    std::vector<Point> vertices;
    vertices.push_back(Point(0.29, 2.81));
    vertices.push_back(Point(-0.27, 2.41));
    vertices.push_back(Point(0.44, 1.53));
    vertices.push_back(Point(0.54, 0.93));
    vertices.push_back(Point(0.91, 3.59));
    Polygon polygon = Polygon(vertices);
    //ASSERT_FALSE(rt.ContainedBy(polygon));
}

TEST(ReuleauxPolygon, Surround)
{
    Point rt_vertices[3] = {Point(-4,0), Point(0,0), Point(-2,3.46)};
    ReuleauxTriangle rt = ReuleauxTriangle(rt_vertices);
    std::vector<Point> vertices;
    vertices.push_back(Point(-2.34, 2.04));
    vertices.push_back(Point(-2.89, 1.65));
    vertices.push_back(Point(-2.18, 0.76));
    vertices.push_back(Point(-1.5, 1.5));
    vertices.push_back(Point(-1.72, 2.82));
    Polygon polygon = Polygon(vertices);
    //ASSERT_FALSE(rt.ContainedBy(polygon));
}

TEST(ReuleauxPolygon, Intersect)
{
    Point rt_vertices[3] = {Point(-4,0), Point(0,0), Point(-2,3.46)};
    ReuleauxTriangle rt = ReuleauxTriangle(rt_vertices);
    std::vector<Point> vertices;
    vertices.push_back(Point(-2.34, 2.04));
    vertices.push_back(Point(-2.89, 1.65));
    vertices.push_back(Point(-2.18, 0.76));
    vertices.push_back(Point(-1.5, 1.5));
    vertices.push_back(Point(-1.72, 2.82));
    Polygon polygon = Polygon(vertices);
    //ASSERT_FALSE(rt.ContainedBy(polygon));
}

TEST(ReuleauxPolygon, TouchInside)
{
    Point rt_vertices[3] = {Point(-4,0), Point(0,0), Point(-2,3.46)};
    ReuleauxTriangle rt = ReuleauxTriangle(rt_vertices);
    std::vector<Point> vertices;
    vertices.push_back(Point(-2.34, 2.04));
    vertices.push_back(Point(-2.89, 1.65));
    vertices.push_back(Point(-2.18, 0.76));
    vertices.push_back(Point(-1.5, 1.5));
    vertices.push_back(Point(-1.72, 2.82));
    Polygon polygon = Polygon(vertices);
    //ASSERT_TRUE(rt.ContainedBy(polygon));
}

TEST(ReuleauxPolygon, TouchOutside)
{
    Point rt_vertices[3] = {Point(-4,0), Point(0,0), Point(-2,3.46)};
    ReuleauxTriangle rt = ReuleauxTriangle(rt_vertices);
    std::vector<Point> vertices;
    vertices.push_back(Point(-2.34, 2.04));
    vertices.push_back(Point(-2.89, 1.65));
    vertices.push_back(Point(-2.18, 0.76));
    vertices.push_back(Point(-1.5, 1.5));
    vertices.push_back(Point(-1.72, 2.82));
    Polygon polygon = Polygon(vertices);
    //ASSERT_FALSE(rt.ContainedBy(polygon));
}

TEST(ReuleauxPolygon, Conincedent)
{
    Point rt_vertices[3] = {Point(-4,0), Point(0,0), Point(-2,3.46)};
    ReuleauxTriangle rt = ReuleauxTriangle(rt_vertices);
    std::vector<Point> vertices;
    vertices.push_back(Point(-2.34, 2.04));
    vertices.push_back(Point(-2.89, 1.65));
    vertices.push_back(Point(-2.18, 0.76));
    vertices.push_back(Point(-1.5, 1.5));
    vertices.push_back(Point(-1.72, 2.82));
    Polygon polygon = Polygon(vertices);
    //ASSERT_TRUE(rt.ContainedBy(polygon));
}