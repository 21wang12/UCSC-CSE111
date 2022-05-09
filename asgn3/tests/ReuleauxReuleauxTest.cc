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

TEST(ReuleauxReuleaux, Contained)
{
    Point inner_vertices[3] = {Point(8,8), Point(8,4), Point(11.46,6)};
    Point outter_vertices[3] = {Point(8,8), Point(8,4), Point(11.46,6)};

    ReuleauxTriangle inner = ReuleauxTriangle(inner_vertices);
    ReuleauxTriangle outter = ReuleauxTriangle(outter_vertices);

    ASSERT_TRUE(inner.ContainedBy(outter));
}

TEST(ReuleauxReuleaux, Outside)
{
    Point inner_vertices[3] = {Point(8,8), Point(8,4), Point(11.46,6)};
    Point outter_vertices[3] = {Point(0,8), Point(0,4), Point(3.46,6)};

    ReuleauxTriangle inner = ReuleauxTriangle(inner_vertices);
    ReuleauxTriangle outter = ReuleauxTriangle(outter_vertices);

    ASSERT_FALSE(inner.ContainedBy(outter));
}

TEST(ReuleauxReuleaux, Surround)
{
    Point inner_vertices[3] = {Point(7,9), Point(7,3), Point(11.46,6)};
    Point outter_vertices[3] = {Point(0,8), Point(0,4), Point(3.46,6)};

    ReuleauxTriangle inner = ReuleauxTriangle(inner_vertices);
    ReuleauxTriangle outter = ReuleauxTriangle(outter_vertices);

    ASSERT_FALSE(inner.ContainedBy(outter));
}

TEST(ReuleauxReuleaux, Intersect)
{
    Point inner_vertices[3] = {Point(8,8), Point(8,4), Point(3.46,6)};
    Point outter_vertices[3] = {Point(8,8), Point(8,4), Point(11.46,6)};

    ReuleauxTriangle inner = ReuleauxTriangle(inner_vertices);
    ReuleauxTriangle outter = ReuleauxTriangle(outter_vertices);

    ASSERT_FALSE(inner.ContainedBy(outter));
}

TEST(ReuleauxReuleaux, TouchInside)
{
    Point inner_vertices[3] = {Point(8,8), Point(8,4), Point(11.46,6)};
    Point outter_vertices[3] = {Point(8,8), Point(8,4), Point(11.46,6)};

    ReuleauxTriangle inner = ReuleauxTriangle(inner_vertices);
    ReuleauxTriangle outter = ReuleauxTriangle(outter_vertices);

    ASSERT_TRUE(inner.ContainedBy(outter));
}

TEST(ReuleauxReuleaux, TouchOutside)
{
    Point inner_vertices[3] = {Point(4,8), Point(4,4), Point(7.46,6)};
    Point outter_vertices[3] = {Point(8,8), Point(8,4), Point(11.46,6)};

    ReuleauxTriangle inner = ReuleauxTriangle(inner_vertices);
    ReuleauxTriangle outter = ReuleauxTriangle(outter_vertices);

    ASSERT_FALSE(inner.ContainedBy(outter));
}

TEST(ReuleauxReuleaux, Conincedent)
{
    Point inner_vertices[3] = {Point(8,8), Point(8,4), Point(11.46,6)};
    Point outter_vertices[3] = {Point(8,8), Point(8,4), Point(11.46,6)};

    ReuleauxTriangle inner = ReuleauxTriangle(inner_vertices);
    ReuleauxTriangle outter = ReuleauxTriangle(outter_vertices);

    ASSERT_TRUE(inner.ContainedBy(outter));
}