#include "Reuleaux.h"
#include "Circle.h"
#include "Geom.h"
#include "Polygon.h"

ReuleauxTriangle::ReuleauxTriangle(const Point vertices[3]){
    for(int i = 0; i < 3; i++){
        this->vertices[i] = vertices[i];
    }
}

bool ReuleauxTriangle::ContainedBy(Circle &circle){
    if(circle.ContainedBy(*this)){
        return false;
    }
    for(int i = 0; i < 3; i++){
        if(!Geom::PointInCircle(circle, vertices[i])){
            return false;
        }
    }
    return true;
}

bool ReuleauxTriangle::ContainedBy(Polygon &polygon){
    if(polygon.ContainedBy(*this)){
        return false;
    }
    for(int i = 0; i < 3; i++){
        if(!Geom::PointInPolygon(polygon, vertices[i])){
            return false;
        }
    }
    return true;
}

bool ReuleauxTriangle::ContainedBy(ReuleauxTriangle &rt){
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            double radius = Geom::Separation(rt.vertices[0], rt.vertices[1]);
            Circle circle = Circle(rt.vertices[j], radius);
            if(!Geom::PointInCircle(circle, vertices[i])){
                return false;
            }
        }
    }
    return true;
}