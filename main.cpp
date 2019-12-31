#include <iostream>
#include <fstream>

#include "scene.h"

const int WIDTH = 2000;
const int HEIGHT = 1000;
const int SAMPLES = 5;

Vector<3> cast_ray(Scene s, Ray r) {
    Intersection a;
    if (s.intersect_ray(r, a)) {
        Vector<3> target = a.position + a.normal + s.random_unit_vec();
        return cast_ray(s, Ray(a.position, target - a.position)) * 0.5f;
    } else {
        Vector<3> unit_dir = r.direction.normalize();
        float t = 0.5f * (unit_dir[1] + 1.0f);
        return (1.f - t) * Vector<3>{1.f, 1.f, 1.f} + t * Vector<3>{0.5f, 0.7f, 1.f};
    }
}

int main() {

    std::vector<Object *> objs;

    auto *sp = new Sphere({0, 0, 1}, 0.5);
    sp->material.diffuse_color = {0, 1, 1};
    objs.push_back(sp);

    auto *sp2 = new Sphere({0, -100.5, 1}, 100);
    sp2->material.diffuse_color = {1, 0, 0};
    objs.push_back(sp2);

    auto *pl = new Plane({-2, 0, 0}, {1, 0, 0});
    pl->material.diffuse_color = {1, 1, 1};
    //objs.push_back(pl);

    auto *pl2 = new Plane({2, 0, 0,}, {-1, 0, 0});
    pl2->material.diffuse_color = {1, 1, 1,};
    //objs.push_back(pl2);

    auto *pl3 = new Plane({0, 0, 4}, {0, 0, 60});
    pl3->material.diffuse_color = {1, 1, 1};
    //objs.push_back(pl3);

    auto *pl4 = new Plane({0, -2, 0}, {0, 1, 0});
    pl4->material.diffuse_color = {1, 0.2, 0.2};
    //objs.push_back(pl4);

    auto *pl5 = new Plane({0, 2, 0}, {0, -1, 0});
    pl5->material.diffuse_color = {0.3, 0.5, 1};
    //objs.push_back(pl5);

    Scene s(objs);

    std::ofstream stream("out.ppm");
    stream << "P3\n" << WIDTH << " " << HEIGHT << "\n255\n";

    for (int i = 0; i < HEIGHT; i++) {
        //std::cout << "Row: " << i << std::endl;
        for (int j = 0; j < WIDTH; j++) {

            Vector<3> color{};

            for (int sam = 0; sam < SAMPLES; sam++) {

                float u = (2.f * static_cast<float>(j + drand48()) - WIDTH) / HEIGHT;
                float v = (-2.f * static_cast<float>(i + drand48()) + HEIGHT) / HEIGHT;

                Ray r({0, 0, 0}, {u, v, 1});

                color += cast_ray(s, r);
            }

            color /= static_cast<float>(SAMPLES);

            stream << static_cast<int>(255.59 * sqrt(color[0])) << " "
                   << static_cast<int>(255.59 * sqrt(color[1])) << " "
                   << static_cast<int>(255.59 * sqrt(color[2])) << "\n";
        }
    }

    return 0;
}