cmake_minimum_required(VERSION 3.15)
project(LTracer)

set(CMAKE_CXX_STANDARD 20)

add_executable(LTracer vector.h main.cpp ray.h object.cpp object.h scene.cpp scene.h)