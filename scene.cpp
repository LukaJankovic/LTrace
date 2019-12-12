//
// Created by luka on 12/10/19.
//

#include "scene.h"

#include <cmath>
#include <random>

Intersection::Intersection() {}

Intersection::Intersection(Object *object, const Ray &ray, float t) : object(object), ray(ray), t(t) {
    this->position = static_cast<Vector<3>>(ray.origin) + ray.direction * t;
}

Scene::Scene() = default;
Scene::Scene(const std::vector<Object *> &objList) : obj_list(objList) {}

bool Scene::intersect_ray(Ray r, Intersection &intersection) {
    bool hit = false;
    Intersection closest(nullptr, r, MAXFLOAT);

    for (Object *object : obj_list) {
        float intersect_t = object->intersect(r);
        if (intersect_t > 0 & intersect_t < closest.t) {
            hit = true;
            closest = Intersection(object, r, intersect_t);
        }
    }

    if (hit) {
        intersection = closest;
        intersection.normal = intersection.object->normal_at_point(intersection.position);
    }

    return hit;
}

Vector<3> Scene::random_unit_vec() {

    Vector<3> vec{};
    do {
        vec = (Vector<3>{static_cast<float>(drand48()),
                         static_cast<float>(drand48()),
                         static_cast<float>(drand48())} * 2.f) - Vector<3>{1, 1, 1};
    } while (vec.length_squared() > 1);

    return vec;
}