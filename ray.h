//
// Created by luka on 12/8/19.
//

#ifndef LTRACER_RAY_H
#define LTRACER_RAY_H

#include <iostream>

#include "vector.h"

class Ray {
public:
    Vector<3> origin;
    Vector<3> direction;

    Ray() = default;
    Ray(const Vector<3> &origin, const Vector<3> &direction) : origin(origin), direction(direction) {};
    Vector<3> extend(float d) {
        return origin + (direction * d);
    }
};

#endif //LTRACER_RAY_H