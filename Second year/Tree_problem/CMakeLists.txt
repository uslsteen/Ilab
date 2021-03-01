cmake_minimum_required(VERSION 3.17)
project(Tree_problem)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS "-O2")

add_executable(Tree_problem main_vers/main_correct.cpp)
