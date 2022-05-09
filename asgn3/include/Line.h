#ifndef _LINE_H_
#define _LINE_H_

#include "Point.h"

class Line {
  public:
    
    Point points[2];

    Line() { points[0] = Point(0, 0), points[1] = Point(0, 0); }
    Line(Point p1, Point p2) { points[0] = p1; points[1] = p2; }
};

#endif
