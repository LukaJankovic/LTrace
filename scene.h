//
// Created by luka on 12/10/19.
//

#ifndef LTRACER_SCENE_H
#define LTRACER_SCENE_H

#include <iostream>

#include "vector.h"
#include "ray.h"
#include "object.h"

class Intersection {
public:
    Object *object;
    Vector<3> position;
    Vector<3> normal;
    Ray ray;

    float  t;

    Intersection();
    Intersection(Object *object, const Ray &ray, float t);
};

class Scene {
public:
    std::vector<Object *> obj_list;

    Scene();
    Scene(const std::vector<Object *> &objList);

    static Vector<3> random_unit_vec();
    bool intersect_ray(Ray r, Intersection &intersection);
};

#endif //LTRACER_SCENE_H