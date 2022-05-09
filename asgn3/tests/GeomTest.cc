#include <gtest/gtest.h>
#include "Polygon.h"
#include "Geom.h"
#include <cmath>

TEST(Geom, Centroid)
{
    std::vector<Point> vertices;
    vertices.push_back(Point(-1, -1));
    vertices.push_back(Point(-1, 1));
    vertices.push_back(Point(1, 1));
    vertices.push_back(Point(1, -1));
    Polygon polygon = Polygon(vertices);
    Point center = Geom::Centroid(polygon);
    ASSERT_TRUE(center.x == 0.0 && center.y == 0.0);
}