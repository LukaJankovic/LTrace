//
// Created by luka on 12/8/19.
//

#pragma warning disable 0169

#ifndef LTRACER_VECTOR_H
#define LTRACER_VECTOR_H

#include <iostream>
#include <vector>
#include <cmath>
#include <random>

template<std::size_t vector_size>
class Vector {
public:
    float v[vector_size]{};
    std::size_t dimension = vector_size;

    Vector<vector_size> operator+(Vector<vector_size> u) {

        for (int i = 0; i < this->dimension; i++) {
            v[i] = v[i] + u[i];
        }

        return *this;
    };

    Vector<vector_size> operator-(Vector<vector_size> u) {

        for (int i = 0; i < this->dimension; i++) {
            v[i] = v[i] - u[i];
        }

        return *this;
    };

    Vector operator+=(Vector<vector_size> u) {
        return *this + u;
    }

    Vector operator-=(Vector<vector_size> u) {
        return *this - u;
    }

    float operator[](int i) const {
        return v[i];
    };

    float &operator[](int i) {
        return v[i];
    };

    friend std::ostream &operator<<(std::ostream &out, const Vector<vector_size> &u) {
        out << "[";

        for (int i = 0; i < u.dimension; i++) {
            out << u[i];
            out << ",";
        }

        out << "\b]";

        return out;
    };

    float length_squared() {
        float s = 0.f;

        for (int i = 0; i < dimension; i++) {
            s += pow(v[i], 2);
        }

        return s;
    }

    float length() {
        return sqrt(length_squared());
    }

    Vector<vector_size> normalize() {
        return *this / length();
    }
};

template<std::size_t vector_size>
Vector<vector_size> operator*(Vector<vector_size> v, float d) {
    for (int i = 0; i < v.dimension; i++) {
        v[i] = v[i] * d;
    }

    return v;
}

template<std::size_t vector_size>
Vector<vector_size> operator*(float d, Vector<vector_size> v) {
    return v * d;
}

template<std::size_t vector_size>
Vector<vector_size> operator/(Vector<vector_size> v, float d) {
    for (int i = 0; i < v.dimension; i++) {
        v[i] = v[i] / d;
    }

    return v;
}

template<std::size_t vector_size>
Vector<vector_size> operator*=(Vector<vector_size> v, float d) {
    return v * d;
}

template<std::size_t vector_size>
Vector<vector_size> operator*=(float d, Vector<vector_size> v) {
    return v * d;
}

template<std::size_t vector_size>
Vector<vector_size> operator/=(Vector<vector_size> v, float d) {
    return v / d;
}

template<std::size_t vector_size>
float dot(Vector<vector_size> v, Vector<vector_size> u) {
    float res = 0.f;

    for (int i = 0; i < v.dimension; i++) {
        res += (v[i] * u[i]);
    }

    return res;
}

template<std::size_t vector_size>
Vector<vector_size> cross(Vector<vector_size> u, Vector<vector_size> v) {
    if (u.dimension != 3 || v.dimension != 3)
        throw std::invalid_argument("Cross product only defined for 3 dimensions");

    return Vector<3>{(u[1] * v[2]) - (u[2] * v[1]),
                     -((u[0] * v[2]) - (u[2] * v[0])),
                     (u[0] * v[1]) - (u[1] * v[0])};
}

#endif // LTRACER_VECTOR_H