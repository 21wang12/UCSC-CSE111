#include "Polygon.h"
#include "Circle.h"
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

TEST(PolygonCircle, Contained)
{
  std::vector<Point> vertices;
  vertices.push_back(Point(-3, 0));
  vertices.push_back(Point(0, 2));
  vertices.push_back(Point(3, 0));
  vertices.push_back(Point(0, -3));

  Polygon inner = Polygon(vertices);
  Circle outer = Circle(Point(0.0,0.0), 3.0);
  ASSERT_TRUE(inner.ContainedBy(outer));
}

TEST(PolygonCircle, Outside)
{
  std::vector<Point> vertices;
  vertices.push_back(Point(-5, 0));
  vertices.push_back(Point(0, 2));
  vertices.push_back(Point(3, 0));
  vertices.push_back(Point(0, -3));

  Polygon inner = Polygon(vertices);
  Circle outer = Circle(Point(5.0,0.0), 1.0);
  ASSERT_FALSE(inner.ContainedBy(outer));
}

TEST(PolygonCircle, Surround)
{
  std::vector<Point> vertices;
  vertices.push_back(Point(-5, 0));
  vertices.push_back(Point(0, 2));
  vertices.push_back(Point(3, 0));
  vertices.push_back(Point(0, -3));

  Polygon inner = Polygon(vertices);
  Circle outer = Circle(Point(0.0,0.0), 1.0);
  ASSERT_FALSE(inner.ContainedBy(outer));
}

TEST(PolygonCircle, Intersect)
{
  std::vector<Point> vertices;
  vertices.push_back(Point(-5, 0));
  vertices.push_back(Point(0, 2));
  vertices.push_back(Point(3, 0));
  vertices.push_back(Point(0, -3));

  Polygon inner = Polygon(vertices);
  Circle outer = Circle(Point(0.0,0.0), 2.5);
  ASSERT_FALSE(inner.ContainedBy(outer));
}

TEST(PolygonCircle, TouchInside)
{
  std::vector<Point> vertices;
  vertices.push_back(Point(-2.27, 1.97));
  vertices.push_back(Point(-0.96, -2.84));
  vertices.push_back(Point(3, 0));

  Polygon inner = Polygon(vertices);
  Circle outer = Circle(Point(0.0,0.0), 4.0);
  ASSERT_TRUE(inner.ContainedBy(outer));
}

TEST(PolygonCircle, TouchOutside)
{
  std::vector<Point> vertices;
  vertices.push_back(Point(-2.48, 3.14));
  vertices.push_back(Point(-4.87, 3.7));
  vertices.push_back(Point(-4.65, 2.51));
  vertices.push_back(Point(-4.24, 3.04));

  Polygon inner = Polygon(vertices);
  Circle outer = Circle(Point(0.0,0.0), 4.0);
  ASSERT_FALSE(inner.ContainedBy(outer));
}

TEST(PolygonCircle, Conincedent)
{
  std::vector<Point> vertices;
  vertices.push_back(Point(-2.27, 1.97));
  vertices.push_back(Point(-0.96, -2.84));
  vertices.push_back(Point(3, 0));
  vertices.push_back(Point(2.13, 2.11));

  Polygon inner = Polygon(vertices);
  Circle outer = Circle(Point(0.0,0.0), 4.0);
  ASSERT_TRUE(inner.ContainedBy(outer));
}