#include "Polygon.h"
#include "Circle.h"
#include "Geom.h"
#include "Arithmetic.h"
#include "Reuleaux.h"

Polygon::Polygon(std::vector<Point> vertices){
    // copy assignment
    // ref: https://www.cplusplus.com/reference/vector/vector/operator=/
    this->vertices = vertices;
}

bool Polygon::ContainedBy(Circle &circle) {
    for(int i = 0; i < vertices.size(); i++){
        if(! (Geom::Separation(vertices[i], circle.center) <= circle.radius + EPS) ) {
            return false;
        }
    }
    return true;
}

// Ref: https://stackoverflow.com/a/4833823
bool Polygon::ContainedBy(Polygon &polygon) {
    int outter_sz = polygon.vertices.size();
    for(int i = 0; i < outter_sz; i++) {
        Point outter_curr_point = polygon.vertices[i];
        Point outter_next_point = polygon.vertices[(i+1)%outter_sz];
        Line outter_line = Line(outter_curr_point, outter_next_point);
        int inner_sz = vertices.size();
        for(int j = 0; j < inner_sz; j++) {
            Point inner_curr_point = polygon.vertices[i];
            Point inner_next_point = polygon.vertices[(i+1)%outter_sz];
            Line inner_line = Line(outter_curr_point, outter_next_point);
            if(Geom::Intersect(outter_line, inner_line) == collision_type::CROSS_TYPE) {
                return false;
            }
        }
    }
    if(Geom::PointInPolygon(polygon, vertices[0])){
        return true;
    }
    return false;
}

bool Polygon::ContainedBy(ReuleauxTriangle &rt){
    double radius = Geom::Separation(rt.vertices[0], rt.vertices[1]);
    for(int i = 0; i < 3; i++){
        Circle reuleaux_circle = Circle(rt.vertices[i], radius);
        for(int i = 0; i < vertices.size(); i++){
            if(! (Geom::Separation(reuleaux_circle.center, vertices[i]) <= reuleaux_circle.radius + EPS)){
                return false;
            }
        }
    }
    return true;
}