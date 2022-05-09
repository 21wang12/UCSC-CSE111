#include "Geom.h"
#include "Point.h"
#include "Line.h"
#include "Polygon.h"
#include "Reuleaux.h"
#include "Circle.h"
#include <cstdlib>
#include <cmath>
#include <vector>

double Geom::Separation(const Point &a, const Point &b){
    return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}

bool Geom::PointInCircle(const Circle &Circle, const Point &point){
    double a = Geom::Separation(point, Circle.center);
    double b = Circle.radius;
    return a <= b || EQ(a, b);
}


bool Geom::PointInPolygon(const Polygon &polygon, const Point &point){
    std::vector<Point> points = polygon.vertices;
    int i, j, nvert = points.size();
    bool c = false;

    for(i = 0, j = nvert - 1; i < nvert; j = i++) {
        if( ( (points[i].y >= point.y ) != (points[j].y >= point.y) ) &&
            (point.x <= (points[j].x - points[i].x) * (point.y - points[i].y) / (points[j].y - points[i].y) + points[i].x)
        )
        c = !c;
    }
    return c;
}

bool Geom::Intersect(const Line &line, const Point &point){
    double zero = (line.points[0].x - line.points[1].x) * (point.y - line.points[1].y) -\
                  (point.x - line.points[1].x) * (line.points[0].y - line.points[1].y);
    if(EQ(zero, 0.0)){
        return false;
    }

    if(!EQ(line.points[0].x, line.points[1].x)){
        return line.points[1].x > line.points[0].x\
            ? point.x + EPS > line.points[0].x && point.x - EPS < line.points[1].x\
            : point.x + EPS > line.points[1].x && point.x - EPS < line.points[0].x;
    }

    return line.points[1].y > line.points[0].y\
        ? point.y + EPS > line.points[0].y && point.y - EPS > line.points[1].y\
        : point.y + EPS > line.points[1].y && point.y - EPS > line.points[0].y;
}

collision_type Geom::Intersect(const Line &line1, const Line &line2){
    // Y = k * X + b
    // k = dy / dx
    double line1_dx = line1.points[0].x - line1.points[1].x;
    double line2_dx = line2.points[0].x - line2.points[1].x;
    double line1_dy = line1.points[0].y - line1.points[1].y;
    double line2_dy = line2.points[0].y - line2.points[1].y;

    double line1_k = line1_dy / line1_dx;
    double line2_k = line2_dy / line2_dx;
    
    double line1_b = line1.points[0].y - line1_k * line1.points[0].x;
    double line2_b = line2.points[0].y - line2_k * line2.points[0].x;

    if(EQ(line1_k, line2_k)){
        // Parellel
        if(!Geom::Intersect(line1, line2.points[0])){
            return collision_type::SEPARATE_TYPE;
        }
        // Tangent
        return collision_type::TANGENT_TYPE;
    }

    double cross_x = (line2_b - line1_b) / (line1_k - line2_k);
    double cross_y = line1_k * cross_x + line1_b;
    Point corss_point = Point(cross_x, cross_y);

    // Cross
    if(Intersect(line1, corss_point)){
        return collision_type::CROSS_TYPE;
    }

    // Line segment is separate
    return collision_type::SEPARATE_TYPE;
}

collision_type Geom::Intersect(const Circle &circle, const Line &line){
    // Y = k * X + b
    // k = dy / dx
    double dx = line.points[1].x - line.points[0].x;
    double dy = line.points[1].y - line.points[0].y;
    double a = dx * dx + dy * dy;
    double b = 2 * (dx * (line.points[0].x - circle.center.x) + dy * (line.points[0].y - circle.center.y));
    double c = circle.center.x * circle.center.x + circle.center.y * circle.center.y;
    c += line.points[0].x * line.points[0].x + line.points[0].y * line.points[0].y;
    c -= 2 * (circle.center.x * line.points[0].x + circle.center.y * line.points[0].y);
    c -= circle.radius * circle.radius;
    double det = b * b - 4 * a * c;
    if(det < 0){
        return collision_type::SEPARATE_TYPE;
    }else if(EQ(det, 0.0)){
        return collision_type::TANGENT_TYPE;
    }
    return collision_type::CROSS_TYPE;
}

Point Geom::Centroid(const Polygon &polygon){
    Point center = Point(0, 0);
    int i = 0;
    for(i = 0; i < polygon.vertices.size(); i++){
        Point vertex = polygon.vertices[i];
        center.x += vertex.x;
        center.y += vertex.y;
    }
    center.x /= i;
    center.y /= i;
    return center;
}

Point Geom::Centroid(const ReuleauxTriangle &rt){
    Point center = Point(0, 0);
    int i = 0;
    for(i = 0; i < 3; i++){
        Point vertex = rt.vertices[i];
        center.x += vertex.x;
        center.y += vertex.y;
    }
    center.x /= i;
    center.y /= i;
    return center;
}