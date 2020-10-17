cmake_minimum_required(VERSION 3.16)
project(Triangles)

set(CMAKE_CXX_STANDARD 14)

add_executable(Triangles main.cpp Vector.h Plane.h Line.h Triangle.h Intersect_algo.h Intersect_algo.cpp)