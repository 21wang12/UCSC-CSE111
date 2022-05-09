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

TEST(CircleReuleaux, Contained)
{
  Circle circle = Circle(Point(0.0,1.0), 1.0);
  Point vertices[3] = {Point(-2,0), Point(0,sqrt(12)), Point(2,0)};
  ReuleauxTriangle rt = ReuleauxTriangle(vertices);
  ASSERT_TRUE(circle.ContainedBy(rt));
}

TEST(CircleReuleaux, Outside)
{
  Circle circle = Circle(Point(5.5,0.27), 1);
  Point vertices[3] = {Point(1.66,-1.9), Point(2.48,-0.85), Point(1.16,-0.67)};
  ReuleauxTriangle rt = ReuleauxTriangle(vertices);
  ASSERT_FALSE(circle.ContainedBy(rt));
}

TEST(CircleReuleaux, Surround)
{
  Circle circle = Circle(Point(5.5,0.27), 5);
  Point vertices[3] = {Point(1.66,-1.9), Point(2.48,-0.85), Point(1.16,-0.67)};
  ReuleauxTriangle rt = ReuleauxTriangle(vertices);
  ASSERT_FALSE(circle.ContainedBy(rt));
}

TEST(CircleReuleaux, Intersect)
{
  Circle circle = Circle(Point(5.5,0.27), sqrt(15.75));
  Point vertices[3] = {Point(1.66,-1.9), Point(2.48,-0.85), Point(1.16,-0.67)};
  ReuleauxTriangle rt = ReuleauxTriangle(vertices);
  ASSERT_FALSE(circle.ContainedBy(rt));
}

TEST(CircleReuleaux, TouchInside)
{
  Circle circle = Circle(Point(1.7,-1.14), sqrt(0.26));
  Point vertices[3] = {Point(1.66,-1.9), Point(2.48,-0.85), Point(1.16,-0.67)};
  ReuleauxTriangle rt = ReuleauxTriangle(vertices);
  ASSERT_TRUE(circle.ContainedBy(rt));
}

TEST(CircleReuleaux, TouchOutside)
{
  Circle circle = Circle(Point(-9.35, 5.04), sqrt(28.42));
  Point vertices[3] = {Point(-14.14,6.95), Point(-12.1,6.84), Point(-13.02,8.66)};
  ReuleauxTriangle rt = ReuleauxTriangle(vertices);
  ASSERT_FALSE(circle.ContainedBy(rt));
}

TEST(CircleReuleaux, Conincident)
{
  Point vertices[3] = {Point(-14.14,6.95), Point(-12.1,6.84), Point(-13.02,8.66)};
  ReuleauxTriangle rt = ReuleauxTriangle(vertices);
  Point rt_center = Geom::Centroid(rt);
  double radius = Geom::Separation(rt_center, rt.vertices[0]);
  Circle circle = Circle(rt_center, radius);
  ASSERT_FALSE(circle.ContainedBy(rt));
}

