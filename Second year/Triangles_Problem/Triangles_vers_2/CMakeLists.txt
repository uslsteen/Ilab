cmake_minimum_required(VERSION 3.16)
project(Triangles_vers_2)

set(CMAKE_CXX_STANDARD 14)

add_executable(Triangles_vers_2 main.cpp Intersect_algo.cpp Vec.h Plane.h Line.h Triangle.h Intersect_algo.h)
