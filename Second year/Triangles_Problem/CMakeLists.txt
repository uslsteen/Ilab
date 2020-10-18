cmake_minimum_required(VERSION 3.16)
project(New_tr)

set(CMAKE_CXX_STANDARD 14)

add_executable(New_tr main.cpp Intersect_algo.h Line.h Plane.h Triangle.h Vec.h)