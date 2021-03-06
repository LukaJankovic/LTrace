#include <iostream>
#include <fstream>
#include <future>

#include "progressbar.hpp"

#include "scene.h"

const int WIDTH = 2000;
const int HEIGHT = 1000;
const int SAMPLES = 10;

Vector<3> cast_ray(Scene s, Ray r, int depth) {
    if (depth < 50) {
        Intersection a;
        if (s.intersect_ray(r, a)) {
            Vector<3> target = a.position + a.normal + s.random_unit_vec();
            if (a.object->material.glow == false)
                return (((cast_ray(s, Ray(a.position, target - a.position), depth + 1) * 0.5f) * a.object->material.diffuse_color));
            else
                return a.object->material.diffuse_glow;
        } else {
            /*Vector<3> unit_dir = r.direction.normalize();
             
             float t = 0.5f * (unit_dir[1] + 1.0f);
             return (1.f - t) * Vector<3>{1.f, 1.f, 1.f} + t * Vector<3>{0.5f, 0.7f, 1.f};*/
            return {0, 0, 0};
        }
    }
    
    return {0, 0, 0};
}

int main() {

    int *fb = static_cast<int *>(malloc(WIDTH * HEIGHT * 3 * sizeof(Vector<3>)));

    auto sp = new Sphere({0, 1.95, 3}, 0.5);
    //sp->material.diffuse_color = {1, 0, 0};
    sp->material.diffuse_glow = {4, 4, 4};
    sp->material.glow = true;
    
    auto sp2 = new Sphere({-0.25, -0.25, 1}, 0.25);
    sp2->material.diffuse_color = {0, 1, 0};
    
    //auto *sp2 = new Sphere({0, -100.5, 1}, 100);
    //sp2->material.diffuse_color = {1, 0, 0};

    auto *p1 = new Plane({-2, 0, 1}, {1, 0, 0});
    auto *p2 = new Plane({2, 0, 1}, {-1, 0, 0});
    auto *p3 = new Plane({0, -2, 1}, {0, 1, 0});
    auto *p4 = new Plane({0, 2, 1}, {0, -1, 0});
    auto *p5 = new Plane({0, 0, 4}, {0, 0, -1});
    
    p1->material.diffuse_color = {0.3, 0.5, 1};
    p2->material.diffuse_color = {1, 0.2, 0.2};
    p3->material.diffuse_color = {1, 1, 1};
    p4->material.diffuse_color = {1, 1, 1};
    p5->material.diffuse_color = {1, 1, 1};

    Object *objs[6];
    objs[0] = sp;
    objs[1] = p1;
    objs[2] = p2;
    objs[3] = p3;
    objs[4] = p4;
    objs[5] = p5;

    Scene s(objs);
    s.size = 6;

    std::ofstream stream("out.ppm");
    stream << "P3\n" << WIDTH << " " << HEIGHT << "\n255\n";
    
    progressbar bar(HEIGHT);
    
#pragma omp parallel for
    for (int i = 0; i < HEIGHT; i++) {

        for (int j = 0; j < WIDTH; j++) {

            Vector<3> color{};

            for (int sam = 0; sam < SAMPLES; sam++) {

                float u = (2.f * static_cast<float>(j + drand48()) - WIDTH) / HEIGHT;
                float v = (-2.f * static_cast<float>(i + drand48()) + HEIGHT) / HEIGHT;

                Ray r({0, 0, 0}, {u, v, 1});

                color += cast_ray(s, r, 0);
            }

            color /= static_cast<float>(SAMPLES);

            int idx = i * WIDTH * 3 + j * 3;

            fb[idx] = static_cast<int>(255.59 * sqrt(color[0]));
            fb[idx + 1] = static_cast<int>(255.59 * sqrt(color[1]));
            fb[idx + 2] = static_cast<int>(255.59 * sqrt(color[2]));
        }
        
#pragma omp critical
        bar.update();
    }

    for (int i = 0; i < HEIGHT * WIDTH * 3; i += 3) {

        stream << fb[i] << " "
               << fb[i + 1] << " "
               << fb[i + 2] << "\n";

    }

    stream.close();

    return 0;
}
