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

TEST(CircleCircle, Contained)
{
  Circle inner = Circle(Point(0.0,0.0), 2.0);
  Circle outer = Circle(Point(0.0,0.0), 4.0);
  ASSERT_TRUE(inner.ContainedBy(outer));
}

TEST(CircleCircle, Outside)
{
  Circle inner = Circle(Point(12.0,12.0), 4.0);
  Circle outer = Circle(Point(0.0,0.0), 4.0);
  ASSERT_FALSE(inner.ContainedBy(outer));
}

TEST(CircleCircle, Surround)
{
  Circle inner = Circle(Point(0.0,0.0), 4.0);
  Circle outer = Circle(Point(0.0,0.0), 2.0);
  ASSERT_FALSE(inner.ContainedBy(outer));
}

TEST(CircleCircle, TouchInside)
{
  Circle inner = Circle(Point(-12.1, 6.84), sqrt(4.19));
  Circle outer = Circle(Point(-9.35, 5.04), sqrt(28.42));
  ASSERT_TRUE(inner.ContainedBy(outer));
}

TEST(CircleCircle, TouchOutside)
{
  Circle inner = Circle(Point(0.0,8.0), 4.0);
  Circle outer = Circle(Point(0.0,0.0), 4.0);
  ASSERT_FALSE(inner.ContainedBy(outer));
}

TEST(CircleCircle, Intersect)
{
  Circle inner = Circle(Point(1.0,1.0), 4.0);
  Circle outer = Circle(Point(0.0,0.0), 4.0);
  ASSERT_FALSE(inner.ContainedBy(outer));
}

TEST(CircleCircle, Conincedent)
{
  Circle inner = Circle(Point(1.0,1.0), 4.0);
  Circle outer = Circle(Point(1.0,1.0), 4.0);
  ASSERT_TRUE(inner.ContainedBy(outer));
}