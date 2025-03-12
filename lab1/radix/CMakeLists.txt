cmake_minimum_required(VERSION 3.30)
project(radix)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${optimizations}")

add_executable(radix main.cpp)
