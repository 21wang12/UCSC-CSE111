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

    double radius = Geom::Separation(vertices[0], vertices[1]);
    if(radius<circle.radius){
        Circle rt_circle1 = Circle(vertices[0], radius);
        Circle rt_circle2 = Circle(vertices[1], radius);
        Circle rt_circle3 = Circle(vertices[2], radius);
        if(rt_circle1.ContainedBy(circle) || rt_circle2.ContainedBy(circle) ||rt_circle3.ContainedBy(circle)){
            for(int i = 0; i < 3; i++){
                if(!Geom::PointInCircle(circle, vertices[i])){
                    return false;
                }
            return true;
            }
        }
        else{
            return false;
        }
        
    }
    else{
        for(int i = 0; i < 3; i++){
            if(!Geom::PointInCircle(circle, vertices[i])){
                return false;
            }
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