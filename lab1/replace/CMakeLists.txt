cmake_minimum_required(VERSION 3.30)
project(replace)

set(CMAKE_CXX_STANDARD 23)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${optimizations}")

add_executable(replace main.cpp)
