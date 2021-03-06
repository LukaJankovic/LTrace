//
// Created by luka on 12/8/19.
//

#include "object.h"

Material::Material() {}

Sphere::Sphere(const Vector<3> &center, float radius) : center(center), radius(radius) {}

float Sphere::intersect(Ray r) {

    Vector<3> OC = r.origin - center;
    float a = r.direction.length_squared();
    float b = dot(OC, r.direction);
    float c = OC.length_squared() - pow(radius, 2);

    float discriminant = pow(b, 2) - a * c;

    if (discriminant > 0) {
        float t0 = (-b - sqrt(discriminant)) / a;
        float t1 = (-b + sqrt(discriminant)) / a;

        return t0 > t1 ? t1 : t0;
    }
    return -1;
}

Vector<3> Sphere::normal_at_point(Vector<3> p) {
    return (p - center).normalize();
}

Plane::Plane(const Vector<3> &origin, const Vector<3> &normal) : origin(origin), normal(normal) {}

float Plane::intersect(Ray r) {
    float parallel = dot(r.direction, normal);

    if (parallel == 0)
        return -1.f;
    else {
        return dot(origin - r.origin, normal) / parallel;
    }
}

Vector<3> Plane::normal_at_point(Vector<3> p) {
    return dot(-1 * p, normal) * normal;
}
