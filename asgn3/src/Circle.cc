#include "Circle.h"
#include "Polygon.h"
#include "Geom.h"
#include "Line.h"
#include "Reuleaux.h"

Circle::Circle(const Point &center, double radius) {
    this->center = center;
    this->radius = radius;
}

bool Circle::ContainedBy(Circle &circle) {
    double a = Geom::Separation(center, circle.center);
    double b = (circle.radius - radius);
    // Ref: https://stackoverflow.com/a/24999897
    return a < b || EQ(a, b);
}

bool Circle::ContainedBy(Polygon &polygon) {
    int sz = polygon.vertices.size();
    for(int i = 0; i < sz; i++){
        Point curr_point = polygon.vertices[i];
        Point next_point = polygon.vertices[(i+1)%sz];
        Line edge = Line(curr_point, next_point);
        // TODO: unimplementation of Intersect
        if(Geom::Intersect(*this, edge) == collision_type::CROSS_TYPE){
            return false;
        }
    }
    if(Geom::PointInPolygon(polygon, center)){
        return true;
    }
    return false;
}

bool Circle::ContainedBy(ReuleauxTriangle &rt) {
    double radius = Geom::Separation(rt.vertices[0], rt.vertices[1]);
    for(int i = 0; i < 3; i++){
        Circle reuleaux_circle = Circle(rt.vertices[i], radius);
        if(!ContainedBy(reuleaux_circle)){
            return false;
        }
    }
    return true;
}