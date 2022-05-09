#ifndef _GEOM_H_
#define _GEOM_H_

#include "Arithmetic.h"
#include "Containable.h"
#include "Line.h"

enum class collision_type {SEPARATE_TYPE, TANGENT_TYPE, CROSS_TYPE};

class Geom {
    public:
      // Calculate the distance between two points
      static double Separation(const Point &a, const Point &b);

      // Ref: https://stackoverflow.com/a/15599478
      // Determine if a point lies in a polygon.
      // Return value:
      //     - true: point is in polygon
      //     - false: point is not in polygon.
      static bool PointInPolygon(const Polygon &polygon, const Point &point);

      // Determine if a point lies in a polygon.
      // Return value:
      //     - true: point is in circle
      //     - false: point is not in circle.
      static bool PointInCircle(const Circle &circle, const Point &point);
      
      // Ref: https://stackoverflow.com/a/35328261
      // Determine if point lies on line-segments.
      // Return type:
      //     - true: point lies on line-segments
      //     - false: point not lies on line-segments.
      static bool Intersect(const Line &line, const Point &point);

      // Determine if two line-segments intersect
      // Return value:
      //     - SEPARATE_TYPE: Two line-segments have no conincendent part
      //     - TANGENT_TYPE: Two line-segment have conincendent part
      //     - CROSS_TYPE: Two line-segment have Intersect point.
      static collision_type Intersect(const Line &line1, const Line &line2);

      // Ref: https://stackoverflow.com/questions/1073336/circle-line-segment-collision-detection-algorithm
      // Ref: https://localcoder.org/line-segment-circle-intersection
      // Determine if a line-segment and a circle have intersect point
      // Return value:
      //     - SEPARATE_TYPE: Line-segment and circle have no conincendent part
      //     - TANGENT_TYPE: Line-segment and circle have a tangent point
      //     - CROSS_TYPE: Line-segment and circle have at least a intersect point
      static collision_type Intersect(const Circle &circle, const Line &line);

      // Find the centroid of a polygon
      static Point Centroid(const Polygon &polygon);
      
      // Find the centroid of a reuleaux triangle
      static Point Centroid(const ReuleauxTriangle &rt);

};

#endif