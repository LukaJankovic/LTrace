//
// Created by luka on 12/8/19.
//

#ifndef LTRACER_OBJECT_H
#define LTRACER_OBJECT_H

#include <iostream>

#include "vector.h"
#include "ray.h"

class Material {
public:
    Vector<3> diffuse_color;
    Vector<3> diffuse_glow;
    
    bool glow;

    Material();
};

class Object {
public:
    Material material;

    virtual float intersect(Ray r) = 0;
    virtual Vector<3> normal_at_point(Vector<3> p) = 0;
};

class Sphere : public Object {
public:
    Vector<3> center;
    float radius;

    Sphere(const Vector<3> &center, float radius);

    virtual float intersect(Ray r);
    virtual Vector<3> normal_at_point(Vector<3> p);
};

class Plane : public Object {
public:
    Vector<3> origin;
    Vector<3> normal;

    Plane(const Vector<3> &origin, const Vector<3> &normal);

    virtual float intersect(Ray r);
    virtual Vector<3> normal_at_point(Vector<3> p);
};

#endif //LTRACER_OBJECT_H
